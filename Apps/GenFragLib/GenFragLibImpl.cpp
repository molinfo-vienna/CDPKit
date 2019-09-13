/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GenFragLibImpl.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <functional>
#include <iterator>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/FragmentList.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Lib/HelperFunctions.hpp"

#include "GenFragLibImpl.hpp"


using namespace GenFragLib;


class GenFragLibImpl::InputScanProgressCallback
{

public:
	class Terminated : public std::exception {};

	InputScanProgressCallback(GenFragLibImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

	void operator()(const CDPL::Base::DataIOBase&, double progress) const {
		if (GenFragLibImpl::termSignalCaught())
			throw Terminated();

		parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
	}

private:
	GenFragLibImpl* parent;
	double          offset;
	double          scale;
};


class GenFragLibImpl::FragLibGenerationWorker
{

public:
	FragLibGenerationWorker(GenFragLibImpl* parent):
		parent(parent), fragLibGen(parent->fragmentLibPtr), numProcMols(0),
		numProcFrags(0), numErrorFrags(0), numAddedFrags(0), totalNumConfs(0)  
	{
		fragLibGen.setProgressCallback(boost::bind(&FragLibGenerationWorker::progress, this));
		fragLibGen.setEnergyWindow(parent->eWindow);
		fragLibGen.setMinRMSD(parent->minRMSD);
		fragLibGen.setRingConformerTrialFactor(parent->confGenTrialFactor);
		fragLibGen.setTimeout(parent->timeout * 1000);
		fragLibGen.reuseExistingCoordinates(parent->useInputCoords);
		fragLibGen.setForceFieldType(parent->forceFieldType);
		fragLibGen.performStrictAtomTyping(parent->strictMMFF94AtomTypes);
	}

	void operator()() {
		using namespace CDPL;

		try {
			while (true) {
				if (!parent->readNextMolecule(molecule))
					return;

				ConfGen::prepareForConformerGeneration(molecule);

				fragList.generate(molecule);

				for (ConfGen::FragmentList::ConstElementIterator it = fragList.getElementsBegin(), end = fragList.getElementsEnd(); it != end; ++it) {
					const Chem::Fragment& frag = *it;
					unsigned int ret_code = fragLibGen.process(frag);

					if (ret_code == ConfGen::ReturnCode::SUCCESS)
						fragmentProcessed(frag);
					else
						handleError(frag, ret_code);
				}

				numProcMols++;
			}

		} catch (const std::exception& e) {
			parent->setErrorMessage(std::string("error while processing molecule: ") + e.what());

		} catch (...) {
			parent->setErrorMessage("unspecified error while processing molecule");
		}
	}

	std::size_t getNumProcMolecules() const {
		return numProcMols;
	}

	std::size_t getNumProcFragments() const {
		return numProcFrags;
	}

	std::size_t getNumErrorFragments() const {
		return numErrorFrags;
	}

	std::size_t getNumAddedFragments() const {
		return numAddedFrags;
	}

	std::size_t getNumGeneratedConfs() const {
		return totalNumConfs;
	}

private:
	void fragmentProcessed(const CDPL::Chem::MolecularGraph& frag) {
		numProcFrags++;

		CDPL::Base::uint64 hash_code = fragLibGen.getLibraryEntryHashCode();
		std::size_t num_confs = fragLibGen.getNumGeneratedConformers();

		parent->updateOccurrenceCount(hash_code);

		if (num_confs != 0) {
			numAddedFrags++;
			totalNumConfs += num_confs;

			if (parent->getVerbosityLevel() >= VERBOSE) {
				parent->printMessage(VERBOSE, "Fragment '" + getSMILES(frag) + "': " + boost::lexical_cast<std::string>(num_confs) + 
									 (num_confs == 1 ? " Conf." : " Confs."));
			}

		} else if (parent->getVerbosityLevel() >= DEBUG) 
			parent->printMessage(DEBUG, "Fragment '" + getSMILES(frag) + "': already processed");
	}

	void handleError(const CDPL::Chem::MolecularGraph& frag, unsigned int ret_code) {
		using namespace CDPL;

		numErrorFrags++;

		std::string err_msg;

		switch (ret_code) {

			case ConfGen::ReturnCode::FORCEFIELD_SETUP_FAILED:
				err_msg = "Force field setup failed";
				break;

			case ConfGen::ReturnCode::FORCEFIELD_MINIMIZATION_FAILED:
				err_msg = "Raw structure minimization failed";
				break;

			case ConfGen::ReturnCode::MAX_NUM_TRIALS_EXCEEDED:
				err_msg = "Could not generated conformer within max. number of trials";
				break;

			case ConfGen::ReturnCode::TIMEOUT_EXCEEDED:
				err_msg = "Could not generated conformer within timeout period";
				break;

			default:
				err_msg = "Unspecified error";	
		}

		parent->printMessage(ERROR, "Error while processing " + std::string(&frag == &molecule ? "molecule" : "fragment") + 
							 " '" + getSMILES(frag) + "':\n" + err_msg);
	}

	std::string getSMILES(const CDPL::Chem::MolecularGraph& molgraph) const {
		using namespace CDPL;

		try {
			std::string smiles;

			perceiveComponents(const_cast<Chem::MolecularGraph&>(molgraph), false);
			generateSMILES(molgraph, smiles, false);

			return smiles;

		} catch (const std::exception& e) {
			return "????";
		}
	}

	bool progress() const {
		if (parent->haveErrorMessage() || GenFragLibImpl::termSignalCaught())
			return false;

		return true;
	}

	GenFragLibImpl*                         parent;
	CDPL::ConfGen::FragmentList             fragList;
	CDPL::ConfGen::FragmentLibraryGenerator fragLibGen;
	CDPL::Chem::BasicMolecule               molecule;
	std::size_t                             numProcMols;
	std::size_t                             numProcFrags;
	std::size_t                             numErrorFrags;
	std::size_t                             numAddedFrags;
	std::size_t                             totalNumConfs;
};


GenFragLibImpl::GenFragLibImpl(): 
	multiThreading(false), numThreads(boost::thread::hardware_concurrency()), 
	mode(CREATE), minRMSD(CDPL::ConfGen::FragmentConformerGenerator::DEF_MIN_RMSD),
	timeout(CDPL::ConfGen::FragmentConformerGenerator::DEF_TIMEOUT / 1000), 
	eWindow(CDPL::ConfGen::FragmentConformerGenerator::DEF_ENERGY_WINDOW), 
	confGenTrialFactor(CDPL::ConfGen::FragmentConformerGenerator::DEF_RING_CONFORMER_TRIAL_FACTOR), 
	forceFieldType(CDPL::ConfGen::FragmentConformerGenerator::DEF_FORCEFIELD_TYPE), 
	useInputCoords(false), strictMMFF94AtomTypes(true), maxLibSize(0), inputHandler(), 
	fragmentLibPtr(new CDPL::ConfGen::FragmentLibrary())
{
	addOption("input,i", "Input file(s).", 
			  value<StringList>(&inputFiles)->multitoken()->required());
	addOption("output,o", "Output fragment library file.", 
			  value<std::string>(&outputFile)->required());
	addOption("mode,m", "Processing mode (CREATE, UPDATE, MERGE default: CREATE).", 
			  value<std::string>()->notifier(boost::bind(&GenFragLibImpl::setMode, this, _1)));
	addOption("multi-threading,t", "Enable multi-threaded processing (default: false).", 
			  value<bool>(&multiThreading)->implicit_value(true));
	addOption("num-threads,n", "Number of parallel threads (default: " + boost::lexical_cast<std::string>(numThreads) + " threads, must be > 0).", 
			  value<unsigned int>()->notifier(boost::bind(&GenFragLibImpl::setMaxNumThreads, this, _1)));
	addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&GenFragLibImpl::setInputFormat, this, _1)));
	addOption("rmsd,r", "Minimum RMSD of two conformations to be considered dissimilar (default: " + 
			  boost::lexical_cast<std::string>(minRMSD) + ", must be >= 0).",
			  value<double>()->notifier(boost::bind(&GenFragLibImpl::setRMSD, this, _1)));
	addOption("timeout,T", "Time in seconds after which fragment conformer generation will be stopped (default: " + 
			  boost::lexical_cast<std::string>(timeout) + ", must be >= 0, 0 disables timeout).",
			  value<std::size_t>(&timeout));
	addOption("max-lib-size,x", "Maximum number of output fragments (default: 0, must be >= 0, 0 disables limit, only valid in CREATE mode).",
			  value<std::size_t>(&maxLibSize));
	addOption("use-input-coords,u", "If available, use existing input 3D coordinates for chain fragments (default: false).", 
			  value<bool>(&useInputCoords)->implicit_value(true));
	addOption("e-window,e", "Output energy window for ring conformers (default: " + 
			  boost::lexical_cast<std::string>(eWindow) + ", must be > 0).",
			  value<double>()->notifier(boost::bind(&GenFragLibImpl::setEnergyWindow, this, _1)));
	addOption("trial-factor,g", "Ring conformer generation trial factor (default: " + 
			  boost::lexical_cast<std::string>(confGenTrialFactor) + ", must be > 1).",
			  value<std::size_t>()->notifier(boost::bind(&GenFragLibImpl::setConfGenTrialFactor, this, _1)));
	addOption("forcefield,f", "Build force field type (MMFF94, MMFF94_NO_ESTAT, MMFF94S, MMFF94S_NO_ESTAT, default: " + getForceFieldTypeString() + ").", 
			  value<std::string>()->notifier(boost::bind(&GenFragLibImpl::setForceFieldType, this, _1)));
	addOption("strict-atom-typing,s", "Perform strict MMFF94 atom typing (default: true).", 
			  value<bool>(&strictMMFF94AtomTypes)->implicit_value(true));

	addOptionLongDescriptions();
}

const char* GenFragLibImpl::getProgName() const
{
    return "GenFragLib";
}

const char* GenFragLibImpl::getProgCopyright() const
{
    return "Thomas A. Seidel";
}

const char* GenFragLibImpl::getProgAboutText() const
{
	return "Creates, updates or merges fragment libraries for conformer generation.";
}

void GenFragLibImpl::addOptionLongDescriptions()
{
	StringList formats;
	std::string formats_str = "Supported Input Formats:\n";

	AppUtils::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

	for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

	addOptionLongDescription("input", 
							 "When operating in CREATE or UPDATE mode, specifies one or more input file(s) with molecules whose fragments shall be stored in the created fragment library.\n\n" +
							 formats_str +
							 "In MERGE mode, specifies multiple existing fragment libraries in CDF format.");

	addOptionLongDescription("input-format", 
							 "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
							 "(because missing, misleading or not supported).");
}

void GenFragLibImpl::setRMSD(double rmsd)
{
	if (rmsd < 0)
		throwValidationError("rmsd");

	minRMSD = rmsd;
}

void GenFragLibImpl::setEnergyWindow(double ewin)
{
	if (ewin <= 0)
		throwValidationError("e-window");

	eWindow = ewin;
}

void GenFragLibImpl::setConfGenTrialFactor(std::size_t factor)
{
	if (factor < 1)
		throwValidationError("retrial-factor");

	confGenTrialFactor = factor;
}

void GenFragLibImpl::setForceFieldType(const std::string& type_str)
{
	using namespace CDPL;
	using namespace ConfGen;

	std::string uc_type = type_str;
	boost::to_upper(uc_type);

	if (uc_type == "MMFF94")
		forceFieldType= ForceFieldType::MMFF94;
	else if (uc_type == "MMFF94_NO_ESTAT")
		forceFieldType= ForceFieldType::MMFF94_NO_ESTAT;
	else if (uc_type == "MMFF94S")
		forceFieldType= ForceFieldType::MMFF94S;
	else if (uc_type == "MMFF94S_NO_ESTAT")
		forceFieldType= ForceFieldType::MMFF94S_NO_ESTAT;
	else
		throwValidationError("forcefield");
}

void GenFragLibImpl::setMode(const std::string& mode_str)
{
	using namespace CDPL::Pharm;

	std::string uc_mode = mode_str;
	boost::to_upper(uc_mode);

	if (uc_mode == "CREATE")
		mode = CREATE;
	else if (uc_mode == "UPDATE")
		mode = UPDATE;
	else if (uc_mode == "MERGE")
		mode = MERGE;
	else
		throwValidationError("mode");
}

void GenFragLibImpl::setInputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	inputHandler = Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext);

	if (!inputHandler)
		throwValidationError("input-format");
}

void GenFragLibImpl::setMaxNumThreads(unsigned int num_threads)
{
	if (num_threads < 1)
		throwValidationError("num-threads");

	numThreads = num_threads;
}

int GenFragLibImpl::process()
{
	startTime = Clock::now();

	printMessage(INFO, getProgTitleString());
	printMessage(INFO, "");

	checkInputFiles();
	printOptionSummary();

	if (mode == MERGE) {
		mergeFragmentLibraries();

	} else {
		initInputReader();

		if (termSignalCaught())
			return EXIT_FAILURE;

		if (mode == UPDATE)
			loadFragmentLibrary(outputFile, *fragmentLibPtr);

		if (termSignalCaught())
			return EXIT_FAILURE;

		if (progressEnabled()) {
			initProgress();
			printMessage(INFO, "Processing Input Molecules...", true, true);
		} else
			printMessage(INFO, "Processing Input Molecules...");

		if (multiThreading)
			processMultiThreaded();
		else
			processSingleThreaded();

		if (haveErrorMessage()) {
			printMessage(ERROR, "Error: " + errorMessage); 
			return EXIT_FAILURE;
		}
	}

	if (termSignalCaught())
		return EXIT_FAILURE;

	return saveFragmentLibrary();
}

void GenFragLibImpl::mergeFragmentLibraries()
{
	FragmentLibrary input_lib;

	for (StringList::const_iterator it = inputFiles.begin(), end = inputFiles.end(); it != end; ++it) {
		if (GenFragLibImpl::termSignalCaught())
			return;

		loadFragmentLibrary(*it, input_lib);

		if (GenFragLibImpl::termSignalCaught())
			return;

		std::size_t old_num_frags = fragmentLibPtr->getNumEntries();

		printMessage(INFO, "Adding fragments to output library...");

		fragmentLibPtr->addEntries(input_lib);

		printMessage(INFO, " - Added " + boost::lexical_cast<std::string>(fragmentLibPtr->getNumEntries() - old_num_frags) + " fragment(s)");
		printMessage(INFO, "");
	}
}

void GenFragLibImpl::processSingleThreaded()
{
	using namespace CDPL;

	FragLibGenerationWorker worker(this);

	worker();

	printMessage(INFO, "");

	if (haveErrorMessage())
		return;

	if (termSignalCaught())
		return;

	printStatistics(worker.getNumProcMolecules(), worker.getNumProcFragments(), worker.getNumErrorFragments(),
					worker.getNumAddedFragments(), worker.getNumGeneratedConfs(),
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void GenFragLibImpl::processMultiThreaded()
{
	using namespace CDPL;

	typedef boost::shared_ptr<FragLibGenerationWorker> FragLibGenerationWorkerPtr;
	typedef std::vector<FragLibGenerationWorkerPtr> FragLibGenerationWorkerList;

	boost::thread_group thread_grp;
	FragLibGenerationWorkerList worker_list;

	try {
		for (std::size_t i = 0; i < numThreads; i++) {
			if (termSignalCaught())
				break;

			FragLibGenerationWorkerPtr worker_ptr(new FragLibGenerationWorker(this));

			thread_grp.create_thread(boost::bind(&FragLibGenerationWorker::operator(), worker_ptr));
			worker_list.push_back(worker_ptr);
		}

	} catch (const std::exception& e) {
		setErrorMessage(std::string("error while creating worker-threads: ") + e.what());

	} catch (...) {
		setErrorMessage("unspecified error while creating worker-threads");
	}

	try {
		thread_grp.join_all();

	} catch (const std::exception& e) {
		setErrorMessage(std::string("error while waiting for worker-threads to finish: ") + e.what());

	} catch (...) {
		setErrorMessage("unspecified error while waiting for worker-threads to finish");
	}
	
	printMessage(INFO, "");

	if (haveErrorMessage())
		return;

	if (termSignalCaught())
		return;
	
	std::size_t num_proc_mols = 0;
	std::size_t num_proc_frags = 0;
	std::size_t num_error_frags = 0;
	std::size_t num_added_frags = 0;
	std::size_t num_gen_confs = 0;

	for (std::size_t i = 0; i < numThreads; i++) {
		const FragLibGenerationWorker& worker = *worker_list[i];

		num_proc_mols += worker.getNumProcMolecules();
		num_proc_frags += worker.getNumProcFragments();
		num_error_frags += worker.getNumErrorFragments();
		num_added_frags += worker.getNumAddedFragments();
		num_gen_confs += worker.getNumGeneratedConfs();
	}

	printStatistics(num_proc_mols, num_proc_frags, num_error_frags, num_added_frags, num_gen_confs,
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());

}

void GenFragLibImpl::loadFragmentLibrary(const std::string& fname, FragmentLibrary& lib)
{
	using namespace CDPL;

	std::ifstream is(fname);

	if (!is) 
		throw Base::IOError("opening fragment library '" + fname + "' failed");
	
	printMessage(INFO, "Loading fragments from library '" + fname + "'...");

	lib.clear();
	lib.load(is);

	if (GenFragLibImpl::termSignalCaught())
		return;

	if (!is)
		throw Base::IOError("loading fragments from library '" + fname + "' failed");

	printMessage(INFO, " - Loaded " + boost::lexical_cast<std::string>(lib.getNumEntries()) + " fragments");
	printMessage(INFO, "");
}

void GenFragLibImpl::updateOccurrenceCount(CDPL::Base::uint64 hash_code)
{
	if (maxLibSize == 0)
		return;

	if (multiThreading) {
		boost::lock_guard<boost::mutex> lock(mutex);

		fragmentOccCounts[hash_code]++;
		return;
	}
	
	fragmentOccCounts[hash_code]++;
}

int GenFragLibImpl::saveFragmentLibrary()
{
	using namespace CDPL;

	std::ofstream os(outputFile, std::ios_base::out | std::ios_base::trunc);

	if (!os)
		throw Base::IOError("opening output fragment library '" + outputFile + "' failed");

	printMessage(INFO, "Saving fragments to library '" + outputFile + "'...");

	if (mode == CREATE && maxLibSize > 0) {
		typedef std::pair<Base::uint64, std::size_t> HashCodeOccCountPair;
		typedef std::vector<HashCodeOccCountPair> HashCodeOccCountPairArray;

		HashCodeOccCountPairArray occ_sorted_frags(fragmentOccCounts.begin(), fragmentOccCounts.end());

		std::sort(occ_sorted_frags.begin(), occ_sorted_frags.end(), 
				  boost::bind(std::less<std::size_t>(),
							  boost::bind(&HashCodeOccCountPair::second, _1),
							  boost::bind(&HashCodeOccCountPair::second, _2)));
																				
		for (HashCodeOccCountPairArray::const_iterator it = occ_sorted_frags.begin(), end = occ_sorted_frags.end(); 
			 it != end && fragmentLibPtr->getNumEntries() > maxLibSize; ++it)
			fragmentLibPtr->removeEntry(it->first);
	}

	fragmentLibPtr->save(os);

	if (!os)
		throw Base::IOError("saving fragments failed");

	printMessage(INFO, " - Saved " + boost::lexical_cast<std::string>(fragmentLibPtr->getNumEntries()) + " fragments");

	return EXIT_SUCCESS;
}

void GenFragLibImpl::setErrorMessage(const std::string& msg)
{
	if (multiThreading) {
		boost::lock_guard<boost::mutex> lock(mutex);

		if (errorMessage.empty())
			errorMessage = msg;
		return;
	}

	if (errorMessage.empty())
		errorMessage = msg;
}

bool GenFragLibImpl::haveErrorMessage()
{
	if (multiThreading) {
		boost::lock_guard<boost::mutex> lock(mutex);
		return !errorMessage.empty();
	}

	return !errorMessage.empty();
}

void GenFragLibImpl::printStatistics(std::size_t num_proc_mols, std::size_t num_proc_frags,  std::size_t num_error_frags, 
									 std::size_t num_added_frags, std::size_t num_gen_confs, std::size_t proc_time)
{
	printMessage(INFO, "Statistics:");
	printMessage(INFO, " Processed Molecules:       " + boost::lexical_cast<std::string>(num_proc_mols));
	printMessage(INFO, " Succ. Processed Fragments: " + boost::lexical_cast<std::string>(num_proc_frags));
	printMessage(INFO, " Fragments With Errors:     " + boost::lexical_cast<std::string>(num_error_frags));
	printMessage(INFO, " Unique Output Fragments:   " + boost::lexical_cast<std::string>(num_added_frags));
	printMessage(INFO, " Generated Conformers:      " + boost::lexical_cast<std::string>(num_gen_confs));
	printMessage(INFO, " Processing Time:           " + AppUtils::formatTimeDuration(proc_time));
	printMessage(INFO, "");
}

bool GenFragLibImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
	if (termSignalCaught())
		return false;

	if (multiThreading) {
		boost::lock_guard<boost::mutex> lock(mutex);

		return doReadNextMolecule(mol);
	}

	return doReadNextMolecule(mol);
}

bool GenFragLibImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
{
	if (!errorMessage.empty())
		return false;

	while (true) {
		try {
			if (inputReader.getRecordIndex() >= inputReader.getNumRecords()) 
				return false;

			CmdLineBase::printMessage(DEBUG, "Starting to process molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) + '/' +
									  boost::lexical_cast<std::string>(inputReader.getNumRecords()) + "...");

			if (!inputReader.read(mol)) {
				CmdLineBase::printMessage(ERROR, "Reading molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) + '/' +
										  boost::lexical_cast<std::string>(inputReader.getNumRecords()) + " failed");			
				
				inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
				return false;
			}

			printProgress("Processing molecules...        ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());
			return true;

		} catch (const std::exception& e) {
			CmdLineBase::printMessage(ERROR, "Error while reading molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) + '/' +
									  boost::lexical_cast<std::string>(inputReader.getNumRecords()) + ": " + e.what());


		} catch (...) {
			CmdLineBase::printMessage(ERROR, "Error while reading molecule " + boost::lexical_cast<std::string>(inputReader.getRecordIndex() + 1) + '/' +
									  boost::lexical_cast<std::string>(inputReader.getNumRecords()));
		}

		inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
	}

	return false;
}

void GenFragLibImpl::checkInputFiles() const
{
	using namespace CDPL;

	StringList::const_iterator it = std::find_if(inputFiles.begin(), inputFiles.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
	if (it != inputFiles.end())
		throw Base::IOError("file '" + *it + "' does not exist");

	if (mode == UPDATE && !Util::fileExists(outputFile))
		throw Base::IOError("updated output library '" + outputFile + "' does not exist");
}

void GenFragLibImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
	if (!multiThreading) {
		CmdLineBase::printMessage(level, msg, nl, file_only);
		return;
	}

	boost::lock_guard<boost::mutex> lock(mutex);

	CmdLineBase::printMessage(level, msg, nl, file_only);
}

void GenFragLibImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE, " Input File(s):                " + inputFiles[0]);
	
	for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(31, ' ') + *it);

	printMessage(VERBOSE, " Output File:                  " + outputFile);
 	printMessage(VERBOSE, " Mode:                         " + getModeString());

	if (mode != MERGE) {
		printMessage(VERBOSE, " Multi-threading:              " + std::string(multiThreading ? "Yes" : "No"));
		printMessage(VERBOSE, " Number of Threads:            " + boost::lexical_cast<std::string>(numThreads));
		printMessage(VERBOSE, " Input File Format:            " + (inputHandler ? inputHandler->getDataFormat().getName() : std::string("Auto-detect")));
		printMessage(VERBOSE, " Max. Output Library Size:     " + boost::lexical_cast<std::string>(maxLibSize));
		printMessage(VERBOSE, " Timeout:                      " + boost::lexical_cast<std::string>(timeout) + "s");
		printMessage(VERBOSE, " RMSD:                         " + (boost::format("%.4f") % minRMSD).str());
		printMessage(VERBOSE, " Energy Window:                " + boost::lexical_cast<std::string>(eWindow));
		printMessage(VERBOSE, " Use Input Coordinates:        " + std::string(useInputCoords ? "Yes" : "No"));
		printMessage(VERBOSE, " Strict MMFF94 Atom Typing:    " + std::string(strictMMFF94AtomTypes ? "Yes" : "No"));
		printMessage(VERBOSE, " Ring Conf. Gen. Trial Factor: " + boost::lexical_cast<std::string>(confGenTrialFactor));
		printMessage(VERBOSE, " Build Force Field Type:       " + getForceFieldTypeString());
	}

	printMessage(VERBOSE, "");
}

void GenFragLibImpl::initInputReader()
{
	using namespace CDPL;

	std::size_t num_in_files = inputFiles.size();
	
	if (progressEnabled()) {
		initProgress();
		printMessage(INFO, "Scanning Input File(s)...", true, true);
	} else
		printMessage(INFO, "Scanning Input File(s)...");

	setMultiConfImportParameter(inputReader, false);
	setSMILESRecordFormatParameter(inputReader, "SN");

	for (std::size_t i = 0; i < num_in_files; i++) {
		if (termSignalCaught())
			return;

		const std::string& file_path = inputFiles[i];
		InputHandlerPtr input_handler = getInputHandler(file_path);

		if (!input_handler)
			throw Base::IOError("no input handler found for file '" + file_path + '\'');

		MoleculeReader::SharedPointer reader_ptr = input_handler->createReader(file_path);

		setMultiConfImportParameter(*reader_ptr, false);

		std::size_t cb_id = reader_ptr->registerIOCallback(InputScanProgressCallback(this, i * 1.0 / num_in_files, 1.0 / num_in_files));

		try {
			inputReader.addReader(reader_ptr);

		} catch (const InputScanProgressCallback::Terminated&) {
			reader_ptr->unregisterIOCallback(cb_id);
			break;
		}

		reader_ptr->unregisterIOCallback(cb_id);
	}

	if (GenFragLibImpl::termSignalCaught())
		return;

	printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(inputReader.getNumRecords()) + " input molecule(s)");
	printMessage(INFO, "");
}

GenFragLibImpl::InputHandlerPtr GenFragLibImpl::getInputHandler(const std::string& file_path) const
{
	if (inputHandler)
		return inputHandler;

	return AppUtils::getInputHandler<CDPL::Chem::Molecule>(file_path);
}

std::string GenFragLibImpl::getModeString() const
{
	using namespace CDPL;

	if (mode == CREATE)
		return "CREATE";

	if (mode == UPDATE)
		return "UPDATE";

	if (mode == MERGE)
		return "MERGE";
	
	return "UNKNOWN";
}

std::string GenFragLibImpl::getForceFieldTypeString() const
{
	using namespace CDPL;
	using namespace ConfGen;

	if (forceFieldType == ForceFieldType::MMFF94)
		return "MMFF94";
	
	if (forceFieldType == ForceFieldType::MMFF94_NO_ESTAT)
		return "MMFF94_NO_ESTAT";

	if (forceFieldType == ForceFieldType::MMFF94S)
		return "MMFF94S";
	
	if (forceFieldType == ForceFieldType::MMFF94S_NO_ESTAT)
		return "MMFF94S_NO_ESTAT";
	
	return "UNKNOWN";
}
