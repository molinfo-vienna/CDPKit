/* 
 * CmdLineBase.hpp
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


#ifndef CMDLINE_LIB_CMDLINEBASE_HPP
#define CMDLINE_LIB_CMDLINEBASE_HPP

#include <string>
#include <fstream>
#include <cstddef>
#include <map>

#include "CDPL/Internal/Timer.hpp"

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>


namespace CmdLineLib
{

    class CmdLineBase
    {

      public:
        CmdLineBase();

        virtual ~CmdLineBase();

        int run(int argc, char* argv[]);

      protected:
        enum VerbosityLevel
        {

            QUIET   = -1,
            ERROR   = 0,
            INFO    = 1,
            VERBOSE = 2,
            DEBUG   = 3,
        };

        static bool termSignalCaught();

        virtual int process() = 0;

        VerbosityLevel getVerbosityLevel() const;

        void addOption(const char* name, const std::string& descr);

        void addOption(const char* name, const std::string& descr,
                       const boost::program_options::value_semantic* sem);

        void addOptionLongDescription(const char* name, const std::string& descr);

        bool wasOptionSet(const char* name) const;

        template <typename T>
        const T& getOptionValue(const char* name) const;

        void printMessage(VerbosityLevel level, const std::string& msg, bool nl = true, bool file_only = false);

        std::ostream& logStream() const;

        bool progressEnabled() const;

        void initProgress(std::size_t prog_bar_len = 40);
        void initInfiniteProgress(std::size_t prog_update_interv = 1000, std::size_t max_num_dots = 4);

        void printProgress(const std::string& prefix, double progress);
        void printInfiniteProgress(const std::string& prefix, bool force = false);

        std::string getProgTitleString() const;

        void throwValidationError(const std::string& opt_name) const;

        template <typename T>
        static boost::program_options::typed_value<T>* value();

        template <typename T>
        static boost::program_options::typed_value<T>* value(T* v);

        static boost::program_options::typed_value<bool>* boolSwitch();
        static boost::program_options::typed_value<bool>* boolSwitch(bool* v);

        virtual const char* getProgName() const = 0;
        virtual const char* getProgVersion() const;
        virtual const char* getProgCopyright() const;
        virtual const char* getProgAboutText() const;

        virtual void init(){};
        virtual void processOptions(){};

      private:
        typedef boost::program_options::option_description OptionDescription;

        void setVerbosityLevel(const std::string& level);
        void openLogFile();

        void printVersion() const;
        void printHelp(const char* bin_path, const std::string& what) const;
        void printOptionsShortHelp() const;
        void printOptionsLongHelp() const;
        void printHelpForOption(const std::string& name) const;
        void printAbout() const;
        void printUsage(const char* bin_path) const;

        std::string formatTextBlock(const std::string& text, std::size_t ident, std::size_t width) const;

        const std::string& getOptionDescription(const std::string& name) const;

        const OptionDescription* getOptionDescriptor(const std::string& name) const;

        typedef boost::program_options::options_description OptionsDescription;
        typedef boost::program_options::variables_map       VariablesMap;
        typedef std::map<std::string, std::string>          StringMap;
        typedef CDPL::Internal::Timer                       Timer;

        OptionsDescription optOptions;
        OptionsDescription mandOptions;
        VariablesMap       parsedOptions;
        StringMap          optionLongDescrs;
        VerbosityLevel     verbLevel;
        std::ostream*      logStreamPtr;
        std::ofstream      logFile;
        bool               showProgress;
        std::size_t        progressBarLen;
        long               lastProgressValue;
        std::size_t        progressUpdateInterv;
        std::size_t        lastProgressDotCount;
        std::size_t        maxProgressDotCount;
        bool               inProgressLine;
        bool               inNewLine;
        Timer              progTimer;
    };


    // Implementation

    template <typename T>
    const T& CmdLineBase::getOptionValue(const char* name) const
    {
        return parsedOptions[name].as<T>();
    }

    template <typename T>
    boost::program_options::typed_value<T>* CmdLineBase::value()
    {
        return boost::program_options::value<T>();
    }

    template <typename T>
    boost::program_options::typed_value<T>* CmdLineBase::value(T* v)
    {
        return boost::program_options::value(v);
    }
} // namespace CmdLineLib

#endif // CMDLINE_LIB_CMDLINEBASE_HPP
