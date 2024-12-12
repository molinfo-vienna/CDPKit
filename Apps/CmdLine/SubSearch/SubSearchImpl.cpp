/* 
 * SubSearchImpl.cpp
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


#include <algorithm>
#include <chrono>
#include <iterator>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/MultiSubstructureSearch.hpp"
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"

#include "SubSearchImpl.hpp"


using namespace SubSearch;


class SubSearchImpl::InputScanProgressCallback
{

public:
    class Terminated : public std::exception {};

    InputScanProgressCallback(SubSearchImpl* parent, double offset, double scale): 
        parent(parent), offset(offset), scale(scale) {}

    void operator()(const CDPL::Base::DataIOBase&, double progress) const {
        if (SubSearchImpl::termSignalCaught())
            throw Terminated();

        parent->printProgress("Scanning Input File(s)...", offset + scale * progress);
    }

  private:
    SubSearchImpl* parent;
    double         offset;
    double         scale;
};


class SubSearchImpl::SubSearchWorker
{

public:
    SubSearchWorker(SubSearchImpl* parent):
        parent(parent) {}

    void operator()() {
        try {
            init();
    
            while (processNextMolecule());
    
        } catch (const std::exception& e) {
            parent->setErrorMessage(std::string("unexpected exception while performing substructure matching: ") + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while performing substructure matching");
        }
    }

private:
    void init() {
        for (auto& ptn : parent->substrPatterns)
            subSearch.addSubstructure(ptn);

        subSearch.setup(parent->matchExpression);
    }
    
    bool processNextMolecule() {
        using namespace CDPL;
        
        auto rec_idx = parent->readNextMolecule(molecule);

        if (!rec_idx)
            return false;

        auto orig_mol_name = getName(molecule);

        try {
            Chem::initSubstructureSearchTarget(molecule, false);

            if (subSearch.matches(molecule)) {
                parent->writeMolecule(molecule, true);
                parent->printMessage(VERBOSE, "Molecule " + parent->createMoleculeIdentifier(rec_idx, orig_mol_name) + ": match");
                
            } else {
                parent->writeMolecule(molecule, false);
                parent->printMessage(VERBOSE, "Molecule " + parent->createMoleculeIdentifier(rec_idx, orig_mol_name) + ": no match");
            }
            
            parent->numProcMols++;
            return true;

        } catch (const std::exception& e) {
            parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, orig_mol_name) + ": " + e.what());

        } catch (...) {
            parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, orig_mol_name));
        }

        return false;
    }

    SubSearchImpl*                      parent;
    CDPL::Chem::MultiSubstructureSearch subSearch;
    CDPL::Chem::BasicMolecule           molecule;
};


SubSearchImpl::SubSearchImpl(): 
    nonMatchingOutFile(), matchExpression(), inputFormat(), matchingOutFormat(),
    nonMatchingOutFormat(), matchingWriter(), nonMatchingWriter(), numProcMols(0),
    numMatches(0)
{
    addOption("input,i", "Molecule input file(s).", 
              value<StringList>(&inputFiles)->multitoken()->required());
    addOption("output,o", "Matching molecule output file.", 
              value<std::string>(&matchingOutFile)->required());
    addOption("nm-output,n", "Non-matching molecule output file.", 
              value<std::string>(&nonMatchingOutFile));
    addOption("input-format,I", "Molecule Input file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier([this](const std::string& fmt) { setInputFormat(fmt); }));
    addOption("output-format,O", "Matching molecule output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier([this](const std::string& fmt) { setMatchingOutputFormat(fmt); }));
    addOption("nm-output-format,N", "Non-matching molecule output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier([this](const std::string& fmt) { setNonMatchingOutputFormat(fmt); }));
    addOption("substructs,s", "Substructure SMARTS pattern(s).", 
              value<StringList>(&substrSMARTSPatterns)->multitoken()->required());
    addOption("match-expr,e", "Substructure matching expression (default: one of the spec. patterns has to match).", 
              value<std::string>(&matchExpression));
    addOptionLongDescriptions();
}

const char* SubSearchImpl::getProgName() const
{
    return "SubSearch";
}

const char* SubSearchImpl::getProgAboutText() const
{
    return "Performs substructure searching on a set of input molecules.";
}

void SubSearchImpl::addOptionLongDescriptions()
{
    addOptionLongDescription("match-expr",
                             "Allows to define a complex substructure query in the form of a logical expression that specifies how "
                             "the individual SMARTS pattern matching results have to be merged into a single overall molecule matching result. "
                             "When no expression is specified the default logic is an OR combination. That is, at least one of the "
                             "given SMARTS patterns has to match for a positive molecule matching result.\n\n"
                             "Supported logical operations:\n"
                             " - AND (symbol: &)\n"
                             " - OR  (symbol: |)\n"
                             " - XOR (symbol: ^)\n"
                             " - NOT (symbol: !)\n\n"
                             "Parentheses can be used for grouping without limit on nesting depth. Any whitespace characters "
                             "will be stripped before expression evaluation and thus can be used freely.\n"
                             "SMARTS patterns specified by option -s are referenced by positive integer numbers >= 1. "
                             "The numeric id of a pattern corresponds to its position in the argument list of option -s.\n\n"
                             "Example: -e '!(1&(2^3)) | 4'");

    StringList formats;
    std::string formats_str = "Supported Input Formats:";

    CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

    for (const auto& fmt : formats)
        formats_str.append("\n - ").append(fmt);

    addOptionLongDescription("input-format", 
                             "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
                             "(because missing, misleading or not supported).");

    addOptionLongDescription("input", 
                             "Specifies one or more molecule input file(s) to be searched for matching substructures.\n\n" +
                             formats_str);

    formats.clear();
    formats_str = "Supported Output Formats:";

    CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

    for (const auto& fmt : formats)
        formats_str.append("\n - ").append(fmt);

    addOptionLongDescription("output-format", 
                             "Allows to explicitly specify the matching molecule output format by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    addOptionLongDescription("output", 
                             "Specifies the output file where the matching molecules will be stored.\n\n" +
                             formats_str);

    addOptionLongDescription("nm-output-format", 
                             "Allows to explicitly specify the non-matching molecule output format by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    addOptionLongDescription("nm-output", 
                             "Specifies the output file where the non-matching molecules will be stored.\n\n" +
                             formats_str);
}

void SubSearchImpl::setInputFormat(const std::string& file_ext)
{
    using namespace CDPL;
    
    if (Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext))
        throwValidationError("input-format");

    inputFormat = file_ext;
}

void SubSearchImpl::setMatchingOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;
    
    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("output-format");

    matchingOutFormat = file_ext;
}

void SubSearchImpl::setNonMatchingOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;
    
    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("nm-output-format");

    nonMatchingOutFormat = file_ext;
}

int SubSearchImpl::process()
{
    timer.reset();

    printMessage(INFO, getProgTitleString());
    printMessage(INFO, "");

    checkInputFiles();
    parseSubstructPatterns();
    checkMatchExpression();
    printOptionSummary();

    initInputReader();
    initOutputWriters();

    if (termSignalCaught())
        return EXIT_FAILURE;

    if (progressEnabled()) {
        initProgress();
        printMessage(INFO, "Searching for Matches...", true, true);
    } else
        printMessage(INFO, "Searching for Matches...");

    findMatches();

    if (haveErrorMessage()) {
        printMessage(ERROR, "Error: " + errorMessage); 
        return EXIT_FAILURE;
    }

    if (termSignalCaught())
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

void SubSearchImpl::findMatches()
{
    using namespace CDPL;

    SubSearchWorker(this)();

    printMessage(INFO, "");

    if (haveErrorMessage())
        return;

    if (termSignalCaught())
        return;

    printStatistics();
}

void SubSearchImpl::setErrorMessage(const std::string& msg)
{
    if (errorMessage.empty())
        errorMessage = msg;
}

bool SubSearchImpl::haveErrorMessage()
{
    return !errorMessage.empty();
}

void SubSearchImpl::printStatistics()
{
    std::size_t proc_time = std::chrono::duration_cast<std::chrono::seconds>(timer.elapsed()).count();
    
    printMessage(INFO, "Statistics:");
    printMessage(INFO, " Processed Molecules: " + std::to_string(numProcMols));
    printMessage(INFO, " Matching Molecules:  " + std::to_string(numMatches));
    printMessage(INFO, " Processing Time:     " + CmdLineLib::formatTimeDuration(proc_time));
    printMessage(INFO, "");
}

std::size_t SubSearchImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
    if (termSignalCaught())
        return 0;

    if (haveErrorMessage())
        return 0;

    while (true) {
        try {
            printProgress("Searching for Matches... ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());

            if (inputReader.getRecordIndex() >= inputReader.getNumRecords()) 
                return 0;

            if (!inputReader.read(mol)) {
                printMessage(ERROR, "Reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1) + " failed");            
                
                inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
                continue;
            }
            
            return inputReader.getRecordIndex();

        } catch (const std::exception& e) {
            printMessage(ERROR, "Error while reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1) + ": " + e.what());

        } catch (...) {
            printMessage(ERROR, "Unspecified error while reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1));
        }

        inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
    }

    return 0;
}

void SubSearchImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol, bool match)
{
    if (match) {
        if (!matchingWriter->write(mol))
            throw CDPL::Base::IOError("could not write output molecule");

        numMatches++;
        
    } else if (nonMatchingWriter) {
        if (!nonMatchingWriter->write(mol))
            throw CDPL::Base::IOError("could not write output molecule");
    }
}

void SubSearchImpl::checkInputFiles() const
{
    using namespace CDPL;
    using namespace std::placeholders;
    
    auto it = std::find_if(inputFiles.begin(), inputFiles.end(),
                           [](const std::string& file) {
                               return !Util::fileExists(file);
                           });
    
    if (it != inputFiles.end())
        throw Base::IOError("file '" + *it + "' does not exist");

    if (std::find_if(inputFiles.begin(), inputFiles.end(),
                     [&](const std::string& file) {
                         return Util::checkIfSameFile(matchingOutFile, file);
                     }) != inputFiles.end())
        throw Base::ValueError("output file must not occur in list of input files");

    if (!nonMatchingOutFile.empty() && (std::find_if(inputFiles.begin(), inputFiles.end(),
                                                     [&](const std::string& file) {
                                                         return Util::checkIfSameFile(nonMatchingOutFile, file);
                                                     }) != inputFiles.end()))
        throw Base::ValueError("output file must not occur in list of input files");
}

void SubSearchImpl::parseSubstructPatterns()
{
    using namespace CDPL;

    for (auto& ptn : substrSMARTSPatterns) {
        try {
            substrPatterns.emplace_back(Chem::parseSMARTS(ptn));
            
        } catch (const Base::IOError& e) {
            std::string e_what(e.what());
            
            throw Base::ValueError("SMARTS pattern '" + ptn + '\'' + e_what.substr(e_what.find_last_of(':')));
        }
    }
}

void SubSearchImpl::checkMatchExpression() const
{
    using namespace CDPL;

    if (matchExpression.empty())
        return;

    auto err_msg = Chem::MultiSubstructureSearch().validate(matchExpression, substrSMARTSPatterns.size() + 1);

    if (!err_msg.empty())
        throw Base::ValueError("invalid substructure match expression: " +  err_msg);
}

void SubSearchImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
    CmdLineBase::printMessage(level, msg, nl, file_only);
}

void SubSearchImpl::printOptionSummary()
{
    printMessage(VERBOSE, "Option Summary:");
    printMessage(VERBOSE, " Input File(s):                            " + inputFiles[0]);
    
    for (auto it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
        printMessage(VERBOSE, std::string(43, ' ') + *it);

    printMessage(VERBOSE, " Matching Molecule Output File:            " + matchingOutFile);
    printMessage(VERBOSE, " Non-Matching Molecule Output File:        " + (nonMatchingOutFile.empty() ? std::string("None") : nonMatchingOutFile));
    printMessage(VERBOSE, " Substructure Patterns:                    " + substrSMARTSPatterns[0]);
    
    for (auto it = ++substrSMARTSPatterns.begin(), end = substrSMARTSPatterns.end(); it != end; ++it)
        printMessage(VERBOSE, std::string(43, ' ') + *it);

    printMessage(VERBOSE, " Substructure Pattern Match Expression:    " + (!matchExpression.empty() ? matchExpression : std::string("Default")));
    printMessage(VERBOSE, " Input File Format:                        " + (!inputFormat.empty() ? inputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Matching Molecule Output File Format:     " + (!matchingOutFormat.empty() ? matchingOutFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Non-Matching Molecule Output File Format: " + (!nonMatchingOutFormat.empty() ? nonMatchingOutFormat : std::string("Auto-detect")));
    
    printMessage(VERBOSE, "");
}

void SubSearchImpl::initInputReader()
{
    using namespace CDPL;

    auto num_in_files = inputFiles.size();
    
    if (progressEnabled()) {
        initProgress();
        printMessage(INFO, "Scanning Input File(s)...", true, true);
    } else
        printMessage(INFO, "Scanning Input File(s)...");

    setMultiConfImportParameter(inputReader, true);
    setSMILESRecordFormatParameter(inputReader, "SN");

    for (std::size_t i = 0; i < num_in_files; i++) {
        if (termSignalCaught())
            return;

        auto& file_path = inputFiles[i];
        Chem::MoleculeReader::SharedPointer reader_ptr;
        
        try {
            reader_ptr.reset(inputFormat.empty() ? new Chem::MoleculeReader(file_path) :
                             new Chem::MoleculeReader(file_path, inputFormat));

        } catch (const Base::IOError& e) {
            throw Base::IOError("no input handler found for file '" + file_path + '\'');
        }
        
        setMultiConfImportParameter(*reader_ptr, false);

        auto cb_id = reader_ptr->registerIOCallback(InputScanProgressCallback(this, i * 1.0 / num_in_files, 1.0 / num_in_files));

        try {
            inputReader.addReader(reader_ptr);

        } catch (const InputScanProgressCallback::Terminated&) {
            reader_ptr->unregisterIOCallback(cb_id);
            break;
        }
       
        reader_ptr->unregisterIOCallback(cb_id);
    }

    if (SubSearchImpl::termSignalCaught())
        return;

    printMessage(INFO, " - Found " + std::to_string(inputReader.getNumRecords()) + " input molecule(s)");
    printMessage(INFO, "");
}

void SubSearchImpl::initOutputWriters()
{
    using namespace CDPL;

    try {
        matchingWriter.reset(matchingOutFormat.empty() ? new Chem::MolecularGraphWriter(matchingOutFile) :
                             new Chem::MolecularGraphWriter(matchingOutFile, matchingOutFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no output handler found for file '" + matchingOutFile + '\'');
    }

    setSMILESRecordFormatParameter(*matchingWriter, "SN");
    setSMILESOutputCanonicalFormParameter(*matchingWriter, true);
    setMultiConfExportParameter(*matchingWriter, true);

    if (nonMatchingOutFile.empty())
        return;

    try {
        nonMatchingWriter.reset(nonMatchingOutFormat.empty() ? new Chem::MolecularGraphWriter(nonMatchingOutFile) :
                             new Chem::MolecularGraphWriter(nonMatchingOutFile, nonMatchingOutFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no output handler found for file '" + nonMatchingOutFile + '\'');
    }

    setSMILESRecordFormatParameter(*nonMatchingWriter, "SN");
    setSMILESOutputCanonicalFormParameter(*nonMatchingWriter, true);
    setMultiConfExportParameter(*nonMatchingWriter, true);
}

std::string SubSearchImpl::createMoleculeIdentifier(std::size_t rec_idx, const std::string& mol_name)
{
    if (!mol_name.empty())
        return ('\'' + mol_name + "' (" + createMoleculeIdentifier(rec_idx) + ')');

    return createMoleculeIdentifier(rec_idx);
}

std::string SubSearchImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
    return (std::to_string(rec_idx) + '/' + std::to_string(inputReader.getNumRecords()));
}
