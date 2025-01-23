/* 
 * CmdLineBase.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <csignal>
#include <iostream>
#include <atomic>
#include <chrono>
#include <functional>

#ifdef HAVE_CXX17_FILESYSTEM_SUPPORT
# include <filesystem>
# define FILESYSTEM_NS std::filesystem
#else
# include <boost/filesystem.hpp>
# define FILESYSTEM_NS boost::filesystem
#endif

#include <boost/program_options/parsers.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tokenizer.hpp>

#ifdef _WIN32
# define WIN32_LEAN_AND_MEAN
# define VC_EXTRALEAN
# define NOMINMAX
# include <windows.h>
# undef ERROR
#endif // !defined _WIN32

#include "CDPL/Version.hpp"
#include "CDPL/BuildInfo.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "CmdLineBase.hpp"
#include "HelperFunctions.hpp"


using namespace CmdLineLib;


namespace
{

    const std::size_t TEXT_BLOCK_WIDTH = 80;

    std::atomic<bool> signalCaught(false);

    const char* sigNumberToString(int sig)
    {

        switch (sig) {

            case SIGTERM:
                return "Terminated";
                
            case SIGINT:
                return "Interrupt";
#ifndef _WIN32                
            case SIGHUP:
                return "Hangup";
                
            case SIGQUIT:
                return "Quit";
#endif // !defined _WIN32                
            default:
                return "Unknown";
        }

        return 0;
    }
    
    void handleSignal(int sig) 
    {
        if (signalCaught.load()) {
            std::cerr << std::endl << "Caught signal (" << sigNumberToString(sig) << ") - exiting..." << std::endl;

            CmdLineBase::setCursorVisible(true);
            std::exit(EXIT_FAILURE);
        }
            
        std::cerr << std::endl << "Caught signal (" << sigNumberToString(sig) << ") - attempting graceful shutdown..." << std::endl;
        signalCaught.store(true);
    }

    bool enableWinVTermProcessing()
    {
#ifdef _WIN32
        // set output mode to handle virtual terminal sequences
        HANDLE hOut = GetStdHandle(STD_ERROR_HANDLE);

        if (hOut == INVALID_HANDLE_VALUE)
            return false;

        DWORD dwMode = 0;

        if (!GetConsoleMode(hOut, &dwMode))
            return false;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

        if (!SetConsoleMode(hOut, dwMode))
            return false;
#endif // defined _WIN32
        return true;    
    }
    
    const std::string INFINITY_SYM_CHAR("\u221E");
    const std::string FULL_LINE_CHAR("\u2501");       // box drawings heavy horizontal
    const std::string LEFT_HALF_LINE_CHAR("\u2578");  // box drawings heavy left
    const std::string RIGHT_HALF_LINE_CHAR("\u257A"); // box drawings heavy right
    const std::string GRAY("\033[38;5;248m");
    const std::string PURPLE("\033[35m");
    const std::string GREEN("\033[32m");
    const std::string DEF_COLOR("\033[39m");
}


CmdLineBase::CmdLineBase(): 
    optOptions("Other Options"), mandOptions("Mandatory Options"), verbLevel(INFO), 
    logStreamPtr(&std::cerr), showProgress(true), progressBarLen(50), lastProgressValue(-1),
    inProgressLine(false), inNewLine(true), haveEscSeqSupport(enableWinVTermProcessing())
{
    addOption("help,h", "Print help message and exit (ABOUT, USAGE, SHORT, ALL or 'name of option', default: SHORT).", 
              value<std::string>()->implicit_value("SHORT"));
    addOption("version,V", "Print version information and exit.");
    addOption("verbosity,v", "Verbosity level of information output (QUIET, ERROR, INFO, VERBOSE, DEBUG, default: INFO).", 
              value<std::string>()->implicit_value("VERBOSE")->notifier(std::bind(&CmdLineBase::setVerbosityLevel, this, std::placeholders::_1)));
    addOption("config,c", "Use file with program options.", 
              value<std::string>());
    addOption("log-file,l", "Redirect text-output to file.", 
              value<std::string>());
    addOption("progress,p", "Show progress bar (default: true).", 
               value<bool>(&showProgress)->implicit_value(true));

    std::signal(SIGTERM, &handleSignal);
    std::signal(SIGINT, &handleSignal);

#ifndef _WIN32
    std::signal(SIGHUP, &handleSignal);
    std::signal(SIGQUIT, &handleSignal);
#else
    SetConsoleOutputCP(CP_UTF8);
#endif // !defined _WIN32
}

CmdLineBase::~CmdLineBase()
{
    setCursorVisible(true);
}
    
int CmdLineBase::run(int argc, char* argv[])
{
    namespace po = boost::program_options;

    try {
        init();

        parsedOptions.clear();
        logStreamPtr = &std::cerr;

        OptionsDescription options;

        options
            .add(optOptions)
            .add(mandOptions);

        po::store(po::parse_command_line(argc, argv, options), parsedOptions);

        if (wasOptionSet("config"))
            po::store(po::parse_config_file<char>(getOptionValue<std::string>("config").c_str(), options), parsedOptions);

        if (wasOptionSet("help")) {
            printHelp(argv[0], getOptionValue<std::string>("help"));
            return EXIT_SUCCESS;
        }

        if (wasOptionSet("version")) {
            printVersion();
            return EXIT_SUCCESS;
        }

        po::notify(parsedOptions);    

        processOptions();
        openLogFile();

    } catch (const std::exception& e) {
        std::cerr << "Error while processing command line: " << e.what() << std::endl;
        std::cerr << "Try '" << FILESYSTEM_NS::path(argv[0]).filename().string()
                  <<  " -h' for more information." << std::endl;
        return EXIT_FAILURE;
    }

    int result = EXIT_FAILURE;

    try {
        result = process();

    } catch (const std::exception& e) {
        printMessage(ERROR, std::string("Error: ") + e.what());

    } catch (...) {
        printMessage(ERROR, "Unspecified Error");
    }

    if (logFile.is_open())
        logFile.close();

    if (termSignalCaught())
        return EXIT_FAILURE;
    
    return result;
}

CmdLineBase::VerbosityLevel CmdLineBase::getVerbosityLevel() const
{
    return verbLevel;
}

bool CmdLineBase::termSignalCaught()
{
    return signalCaught.load();
}

void CmdLineBase::setCursorVisible(bool visible)
{
#ifndef _WIN32
    std::cerr << (visible ? "\033[?25h" : "\033[?25l");
#else
    static const HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;

    GetConsoleCursorInfo(handle, &cci);
    cci.bVisible = visible;
    SetConsoleCursorInfo(handle, &cci);
#endif // !defined _WIN32 
}

void CmdLineBase::addOption(const char* name, const std::string& descr)
{
    optOptions.add_options()(name, descr.empty() ? static_cast<const char*>(0) : descr.c_str());
}

void CmdLineBase::addOption(const char* name, const std::string& descr, 
                            const boost::program_options::value_semantic* sem)
{
    if (sem->is_required())
        mandOptions.add_options()(name, sem, descr.empty() ? static_cast<const char*>(0) : descr.c_str());
    else
        optOptions.add_options()(name, sem, descr.empty() ? static_cast<const char*>(0) : descr.c_str());
}

void CmdLineBase::addOptionLongDescription(const char* name, const std::string& descr)
{
    optionLongDescrs[name] = descr;
}

bool CmdLineBase::wasOptionSet(const char* name) const
{
    return (parsedOptions.count(name) > 0);
}

boost::program_options::typed_value<bool>* CmdLineBase::boolSwitch()
{
    return boost::program_options::bool_switch();
}

boost::program_options::typed_value<bool>* CmdLineBase::boolSwitch(bool* v)
{
    return boost::program_options::bool_switch(v);
}

const char* CmdLineBase::getProgVersion() const
{
    return CDPL_VERSION_STRING;
}

const char* CmdLineBase::getProgCopyright() const
{
    return "Thomas Seidel";
}

std::string CmdLineBase::getProgTitleString() const
{
    std::string title(getProgName());

    if (getProgVersion()) {
        title += " v";
        title += getProgVersion();
    }
    
    if (getProgCopyright()) {
        title += " \u00A9 ";
        title += getProgCopyright();
    }

    return title;
}

const char* CmdLineBase::getProgAboutText() const
{
    return "";
}

void CmdLineBase::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
    if (level > verbLevel || (termSignalCaught() && level != ERROR))
        return;

    if (file_only && logStreamPtr == &std::cerr)
        return;

    if (logStreamPtr == &std::cerr && inProgressLine)
        logStream() << std::endl;

    logStream() << msg;

    if (nl) 
        logStream() << std::endl;
    
    inNewLine = nl;
    inProgressLine = false;

    logStream().flush();
}

std::ostream& CmdLineBase::logStream() const 
{
    return *logStreamPtr;
}

bool CmdLineBase::progressEnabled() const
{
    return showProgress;
}

void CmdLineBase::initProgress(std::size_t prog_bar_len)
{
    progressBarLen = prog_bar_len;
    lastProgressValue = -1;
    progTimer.reset();

    if (showProgress)
        setCursorVisible(false);
}

void CmdLineBase::printProgress(const std::string& prefix, double progress)
{
    if (!showProgress || verbLevel == QUIET || termSignalCaught())
        return;

    progress = std::min(1.0, progress);
    progress = std::max(0.0, progress);
    
    long curr_prog_value = progress * 10000;

    if (curr_prog_value <= lastProgressValue)
        return;

    lastProgressValue = curr_prog_value;
    std::size_t curr_prog_bar_len = progressBarLen * progress;

    if (logStreamPtr == &std::cerr && !inProgressLine && !inNewLine)
        std::cerr << std::endl;

    std::cerr << prefix << std::fixed << std::setw(7) << std::setprecision(2)
              << (double(lastProgressValue) / 100) << "% ";

    bool fractional = (progressBarLen * progress - curr_prog_bar_len) >= 0.5;
    
    if (!haveEscSeqSupport) {
        progressBar.clear();
        progressBar.push_back('|');

        if ((curr_prog_bar_len > 0) || fractional) {
            for (std::size_t i = 0; i < curr_prog_bar_len; i++)
                progressBar.append(FULL_LINE_CHAR);

            if (progressBarLen != curr_prog_bar_len) {
                if (fractional)
                    progressBar.append(LEFT_HALF_LINE_CHAR);
                else
                    progressBar.push_back(' ');

                for (std::size_t i = 1; i < (progressBarLen - curr_prog_bar_len); i++)
                    progressBar.push_back(' ');
            }

        } else
            for (std::size_t i = 0; i < progressBarLen; i++)
                progressBar.push_back(' ');

        progressBar.push_back('|');

    } else {
        progressBar = (curr_prog_bar_len == 0 ? fractional ? PURPLE : GRAY : progressBarLen == curr_prog_bar_len ? GREEN :
                       PURPLE);

        if ((curr_prog_bar_len > 0) || fractional) {
            for (std::size_t i = 0; i < curr_prog_bar_len; i++)
                progressBar.append(FULL_LINE_CHAR);

            if (progressBarLen != curr_prog_bar_len) {
                if (fractional) {
                    progressBar.append(LEFT_HALF_LINE_CHAR);
                    progressBar.append(GRAY);

                } else {
                    progressBar.append(GRAY);
                    progressBar.append(RIGHT_HALF_LINE_CHAR);
                }

                for (std::size_t i = 1; i < (progressBarLen - curr_prog_bar_len); i++)
                    progressBar.append(FULL_LINE_CHAR);
            }

        } else
            for (std::size_t i = 0; i < progressBarLen; i++)
                progressBar.append(FULL_LINE_CHAR);

        progressBar.append(DEF_COLOR);
    }

    std::cerr << progressBar;
    
    if (progress > 0.0) {
        std::size_t tot_eta_secs = (std::chrono::duration_cast<std::chrono::seconds>(progTimer.elapsed()).count() + 1) / progress * (1.0 - progress);

        std::cerr << " ETA: " << std::setw(13) << std::left << formatTimeDuration(tot_eta_secs) << std::right << '\r';

        if (progressBarLen == curr_prog_bar_len)
            setCursorVisible(true);

    } else
        std::cerr << " ETA: " << INFINITY_SYM_CHAR << '\r';
    
    inProgressLine = true;
    inNewLine = false;
}

void CmdLineBase::printInfiniteProgress(const std::string& prefix, bool force)
{
    if (!showProgress || verbLevel == QUIET || termSignalCaught() || maxProgressDotCount == 0)
        return;

    if (!force) {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(progTimer.elapsed()) < std::chrono::milliseconds(progressUpdateInterv))
            return;
    }

    if (logStreamPtr == &std::cerr && !inProgressLine && !inNewLine)
        std::cerr << std::endl;

    std::cerr << prefix << std::setfill('.') << std::setw(lastProgressDotCount) << ""
              << std::setfill(' ') << std::setw(maxProgressDotCount - lastProgressDotCount) << ""<< '\r';

    if (++lastProgressDotCount > maxProgressDotCount)
        lastProgressDotCount = 1;

    progTimer.reset();
    inProgressLine = true;
    inNewLine = false;
}

void CmdLineBase::initInfiniteProgress(std::size_t prog_update_interv, std::size_t max_num_dots)
{
    progressUpdateInterv = prog_update_interv;
    lastProgressDotCount = 1;
    maxProgressDotCount = max_num_dots;
}

void CmdLineBase::throwValidationError(const std::string& opt_name) const
{
    namespace po = boost::program_options;

    throw po::validation_error(po::validation_error::invalid_option_value, opt_name);
}

void CmdLineBase::setVerbosityLevel(const std::string& level)
{
    using namespace CDPL;

    if (Internal::isEqualCI(level, "QUIET"))
        verbLevel = QUIET;
    else if (Internal::isEqualCI(level, "ERROR"))
        verbLevel = ERROR;
    else if (Internal::isEqualCI(level, "INFO"))
        verbLevel = INFO;
    else if (Internal::isEqualCI(level, "VERBOSE"))
        verbLevel = VERBOSE;
    else if (Internal::isEqualCI(level, "DEBUG"))
        verbLevel = DEBUG;
    else
        throwValidationError("verbosity");
}

void CmdLineBase::openLogFile()
{
    if (!wasOptionSet("log-file"))
        return; 
        
    logFile.open(getOptionValue<std::string>("log-file").c_str(), std::ios_base::out | std::ios_base::trunc);

    if (!logFile)
        throw CDPL::Base::IOError("opening log-file failed");

    logStreamPtr = &logFile;
}

void CmdLineBase::printVersion() const
{
    std::cerr << getProgTitleString() 
              << " (Compiler: " << CDPL_COMPILER_ID << " " << CDPL_COMPILER_VERSION 
              << ", Build OS: " << CDPL_BUILD_SYSTEM 
              << ", Build Date: " << ((CDPL_BUILD_TIME / 1000000) % 100) << '/' << ((CDPL_BUILD_TIME / 10000) % 100) << '/' << (CDPL_BUILD_TIME / 100000000)
              << ")" << std::endl;
}

void CmdLineBase::printHelp(const char* bin_path, const std::string& what) const
{
    std::string lc_what = what;
    boost::to_lower(lc_what);

    if (lc_what == "usage") {
        printUsage(bin_path); 
        return;
    }

    if (lc_what == "about") {
        printAbout();
        return;
    }

    if (lc_what == "short") {
        printUsage(bin_path); 

        std::cerr << std::endl;

        printOptionsShortHelp();
        return;
    }

    if (lc_what == "all") {
        printAbout();

        std::cerr << std::endl;

        printUsage(bin_path); 

        std::cerr << std::endl;

        printOptionsLongHelp();
        return;
    }

    printHelpForOption(lc_what);
}

void CmdLineBase::printOptionsShortHelp() const
{
    std::cerr << mandOptions << std::endl << optOptions;
}

void CmdLineBase::printOptionsLongHelp() const
{
    namespace po = boost::program_options;

    std::cerr << "Mandatory Options:" << std::endl;

    const std::vector<boost::shared_ptr<po::option_description> >& mand_options = mandOptions.options();

    for (std::size_t i = 0; i < mand_options.size(); i++) {
        std::cerr << "  " << mand_options[i]->format_name() << ' ' << mand_options[i]->format_parameter() 
                  << std::endl << std::endl;
        std::cerr << formatTextBlock(getOptionDescription(mand_options[i]->key("*")), 4, TEXT_BLOCK_WIDTH) << std::endl << std::endl;
    }

    std::cerr << "Other Options:" << std::endl;

    const std::vector<boost::shared_ptr<po::option_description> >& opt_options = optOptions.options();

    for (std::size_t i = 0; i < opt_options.size(); i++) {
        std::cerr << "  " << opt_options[i]->format_name() << ' ' << opt_options[i]->format_parameter() 
                  << std::endl << std::endl;
        std::cerr << formatTextBlock(getOptionDescription(opt_options[i]->key("*")), 4, TEXT_BLOCK_WIDTH) << std::endl << std::endl;
    }
}

void CmdLineBase::printHelpForOption(const std::string& name) const
{
    namespace po = boost::program_options;

    const OptionDescription* opt_desc = getOptionDescriptor(name);

    if (!opt_desc)
        throwValidationError(name);

    std::cerr << opt_desc->format_name() << ' ' << opt_desc->format_parameter() 
              << std::endl << std::endl;
    std::cerr << formatTextBlock(getOptionDescription(name), 0, TEXT_BLOCK_WIDTH) << std::endl;
}

void CmdLineBase::printAbout() const
{
    std::cerr << getProgTitleString() << std::endl;

    std::string about(getProgAboutText());

    if (!about.empty())
        std::cerr << std::endl << formatTextBlock(about, 0, TEXT_BLOCK_WIDTH) << std::endl;
}

void CmdLineBase::printUsage(const char* bin_path) const
{
    namespace po = boost::program_options;

    std::cerr << "Usage: " << std::endl;
    std::cerr << "  " << FILESYSTEM_NS::path(bin_path).filename().string();

    const std::vector<boost::shared_ptr<po::option_description> >& opt_options = optOptions.options();

    bool first_short = true;

    for (std::size_t i = 0; i < opt_options.size(); i++) {
        if (opt_options[i]->semantic()->min_tokens() != 0)
            continue;

        std::string name = opt_options[i]->canonical_display_name(4);

        if (name.size() == 2 && name[0] == '-') {
            if (first_short) {
                std::cerr << " [-";
                first_short = false;
            }

            std::cerr << name[1];
        }
    }

    if (!first_short)
        std::cerr << ']';

    for (std::size_t i = 0; i < opt_options.size(); i++) {
        std::string name = opt_options[i]->canonical_display_name(4);

        if (name.size() != 2 || name[0] != '-')
            std::cerr << " [--" << name;

        else {
            if (opt_options[i]->semantic()->min_tokens() == 0)
                continue;

            std::cerr << " [" << name;
        }

        if (opt_options[i]->semantic()->min_tokens() > 0)
            std::cerr << " arg";

        if (opt_options[i]->semantic()->max_tokens() > 1)
            std::cerr << " [arg]...";

        std::cerr << ']';
    }

    const std::vector<boost::shared_ptr<po::option_description> >& mand_options = mandOptions.options();

    for (std::size_t i = 0; i < mand_options.size(); i++) {
        std::string name = mand_options[i]->canonical_display_name(4);

        if (name.size() != 2 || name[0] != '-')
            std::cerr << " --" << name;
        else
            std::cerr << ' ' << name;

        if (mand_options[i]->semantic()->min_tokens() > 0)
            std::cerr << " arg";

        if (mand_options[i]->semantic()->max_tokens() > 1)
            std::cerr << " [arg]...";
    }

    std::cerr << std::endl;
}

const std::string& CmdLineBase::getOptionDescription(const std::string& name) const
{
    namespace po = boost::program_options;

    StringMap::const_iterator it = optionLongDescrs.find(name);

    if (it != optionLongDescrs.end())
        return it->second;

    const OptionDescription* opt_desc = getOptionDescriptor(name);

    if (opt_desc)
        return opt_desc->description();

    throwValidationError(name);

    return name;
}

const CmdLineBase::OptionDescription* CmdLineBase::getOptionDescriptor(const std::string& name) const
{
    const OptionDescription* opt_desc = mandOptions.find_nothrow(name, false);

    if (opt_desc)
        return opt_desc;

    return optOptions.find_nothrow(name, false);
}

std::string CmdLineBase::formatTextBlock(const std::string& text, std::size_t ident, std::size_t width) const
{
    typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

    std::string ident_fill(ident, ' ');
    std::string form_text(ident_fill);
    std::string delim = " -+\n";
    std::string word;

    Tokenizer tokenizer(text, boost::char_separator<char>("", delim.c_str()));
    std::size_t line_len = 0;

    for (Tokenizer::iterator it = tokenizer.begin(); it != tokenizer.end(); ++it) {
        std::string token = *it;

        if (token.length() == 1 && delim.find(token[0]) != std::string::npos) {
            word.append(token);

            if (token[0] == '\n') {
                line_len = 0;
                form_text.append(word);
                form_text.append(ident_fill);
                word.clear();
            }                

            continue;
        }

        form_text.append(word);
        line_len += word.length();

        std::swap(word, token);

        if (line_len >= width) {
            line_len = 0;
            form_text.push_back('\n');
            form_text.append(ident_fill);
        }
    }
    
    form_text.append(word);

    return form_text;
}
