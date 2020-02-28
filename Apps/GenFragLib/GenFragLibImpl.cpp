/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GenFragLibImpl.cpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <sstream>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/ConfGen/MoleculeFunctions.hpp"
#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/FragmentLibraryGenerator.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
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
		parent(parent), fragLibGen(parent->fragmentLibPtr), verbLevel(parent->getVerbosityLevel()),
		numProcMols(0), numProcFrags(0), numErrorFrags(0), numAddedFrags(0), totalNumConfs(0)  
	{
		fragLibGen.setAbortCallback(boost::bind(&FragLibGenerationWorker::abort, this));
		fragLibGen.getSettings() = parent->settings;

		if (parent->getVerbosityLevel() >= DEBUG)  
			fragLibGen.setLogMessageCallback(boost::bind(&FragLibGenerationWorker::appendToLogRecord, this, _1));
	}

	void operator()() {
		try {
			while (processNextMolecule());
			
		} catch (const std::exception& e) {
			parent->setErrorMessage(std::string("unexpected exception while creating fragment library: ") + e.what());

		} catch (...) {
			parent->setErrorMessage("unexpected exception while creating fragment library");
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
	bool processNextMolecule() {
		using namespace CDPL;
		using namespace Chem;
		using namespace ConfGen;

		std::size_t rec_idx = parent->readNextMolecule(molecule);

		if (!rec_idx)
			return false;

		try {
			logRecordStream.str(std::string());

			if (verbLevel >= DEBUG) 
				logRecordStream << std::endl << "- Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ':' << std::endl;

			prepareForConformerGeneration(molecule);
			buildFragmentLinkBondMask(molecule, fragLinkBondMask);

			splitIntoFragments(molecule, fragList, fragLinkBondMask);

			for (FragmentList::ConstElementIterator it = fragList.getElementsBegin(), end = fragList.getElementsEnd(); it != end; ++it) {
				const Fragment& frag = *it;

				if (verbLevel >= DEBUG) 
					logRecordStream << "Fragment " << getSMILES(frag) << ':' << std::endl;

				unsigned int ret_code = fragLibGen.process(frag, molecule);

				switch (ret_code) {

					case ReturnCode::ABORTED:
						return false;
							
					case ReturnCode::SUCCESS:
					case ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT:
					case ReturnCode::FRAGMENT_ALREADY_PROCESSED:
						fragmentProcessed(frag, ret_code);
						break;
							
					default:
						handleError(frag, ret_code);
				}
			}

			std::string log_rec = logRecordStream.str();

			if (!log_rec.empty()) 
				parent->printMessage(verbLevel, log_rec, false);

			numProcMols++;
			
			return true;

		} catch (const std::exception& e) {
			parent->setErrorMessage("unexpected exception while processing molecule " + 
									parent->createMoleculeIdentifier(rec_idx, molecule) + ": " + e.what());

		} catch (...) {
			parent->setErrorMessage("unexpected exception while processing molecule " + 
									parent->createMoleculeIdentifier(rec_idx, molecule));
		}

		return false;
	}

	void fragmentProcessed( const CDPL::Chem::MolecularGraph& frag, unsigned int ret_code) {
		using namespace CDPL::ConfGen;

		numProcFrags++;

		CDPL::Base::uint64 hash_code = fragLibGen.getLibraryEntryHashCode();
		std::size_t num_confs = fragLibGen.getNumGeneratedConformers();

		parent->updateOccurrenceCount(hash_code);

		if (ret_code == ReturnCode::SUCCESS || ret_code == ReturnCode::FRAGMENT_CONF_GEN_TIMEOUT) {
			numAddedFrags++;
			totalNumConfs += num_confs;

			if (verbLevel == VERBOSE) 
				logRecordStream << "Fragment " << getSMILES(frag) << ": " << 
					num_confs << (num_confs == 1 ? " conf." : " confs.") << std::endl;
			
		} else if (verbLevel == VERBOSE) 
			logRecordStream << "Fragment " << getSMILES(frag) << ": already in library" << std::endl;

		else if (verbLevel >= DEBUG) 
			logRecordStream << " Already in library!" << std::endl;
	}

	void handleError(const CDPL::Chem::MolecularGraph& frag, unsigned int ret_code) {
		using namespace CDPL;
		using namespace ConfGen;

		numErrorFrags++;

		if (verbLevel < ERROR || verbLevel >= DEBUG)
			return;

		std::string err_msg;

		switch (ret_code) {

			case ReturnCode::FORCEFIELD_SETUP_FAILED:
				err_msg = "force field setup failed";
				break;

			case ReturnCode::FORCEFIELD_MINIMIZATION_FAILED:
				err_msg = "structure refinement failed";
				break;

			case ReturnCode::FRAGMENT_CONF_GEN_FAILED:
				err_msg = "could not generate any conformers";
				break;

			case ReturnCode::TIMEOUT:
				err_msg = "time limit exceeded";
				break;

			default:
				err_msg = "unspecified error";
				break;
		}

		logRecordStream << "Fragment " << getSMILES(frag) << ": " << err_msg << std::endl;
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

	void appendToLogRecord(const std::string& msg) {
		logRecordStream << ' ' << msg;
	}

	bool abort() const {
		if (parent->haveErrorMessage() || GenFragLibImpl::termSignalCaught())
			return true;

		return false;
	}

	GenFragLibImpl*                         parent;
	CDPL::Chem::FragmentList                fragList;
	CDPL::Util::BitSet                      fragLinkBondMask;
	CDPL::ConfGen::FragmentLibraryGenerator fragLibGen;
	CDPL::Chem::BasicMolecule               molecule;
	std::stringstream                       logRecordStream;
	VerbosityLevel                          verbLevel;
	std::size_t                             numProcMols;
	std::size_t                             numProcFrags;
	std::size_t                             numErrorFrags;
	std::size_t                             numAddedFrags;
	std::size_t                             totalNumConfs;
};


GenFragLibImpl::GenFragLibImpl(): 
	numThreads(0), mode(CREATE), settings(ConformerGeneratorSettings::THOROUGH), preset("THOROUGH"),
	maxLibSize(0), inputHandler(), fragmentLibPtr(new CDPL::ConfGen::FragmentLibrary())
{
	addOption("input,i", "Input file(s).", 
			  value<StringList>(&inputFiles)->multitoken()->required());
	addOption("output,o", "Output fragment library file.", 
			  value<std::string>(&outputFile)->required());
	addOption("mode,m", "Processing mode (CREATE, UPDATE, MERGE default: CREATE).", 
			  value<std::string>()->notifier(boost::bind(&GenFragLibImpl::setMode, this, _1)));
	addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
			  boost::lexical_cast<std::string>(boost::thread::hardware_concurrency()) + 
			  " threads, must be >= 0, 0 disables multithreading).", 
			  value<std::size_t>(&numThreads)->implicit_value(boost::thread::hardware_concurrency()));
	addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&GenFragLibImpl::setInputFormat, this, _1)));
	addOption("preset,F", "Fragment conformer generation preset to use (FAST, THROUGH, default: THOROUGH).", 
			  value<std::string>()->notifier(boost::bind(&GenFragLibImpl::applyPreset, this, _1)));
	addOption("rmsd,r", "Minimum RMSD of two small ring system conformations to be considered dissimilar (default: " + 
			  (boost::format("%.4f") % settings.getSmallRingSystemSettings().getMinRMSD()).str() + ", must be >= 0).",
			  value<double>()->notifier(boost::bind(&GenFragLibImpl::setRMSD, this, _1)));
	addOption("timeout,T", "Time in seconds after which fragment conformer generation will be stopped (default: " + 
			  boost::lexical_cast<std::string>(settings.getMacrocycleSettings().getTimeout() / 1000) + "s, must be >= 0, 0 disables timeout).",
			  value<std::size_t>()->notifier(boost::bind(&GenFragLibImpl::setTimeout, this, _1)));
	addOption("max-lib-size,n", "Maximum number of output fragments (default: 0, must be >= 0, 0 disables limit, only valid in CREATE mode).",
			  value<std::size_t>(&maxLibSize));
	addOption("e-window,e", "Output energy window for small ring system conformers (default: " + 
			  boost::lexical_cast<std::string>(settings.getSmallRingSystemSettings().getEnergyWindow()) + ", must be >= 0).",
			  value<double>()->notifier(boost::bind(&GenFragLibImpl::setEnergyWindow, this, _1)));
	addOption("small-rsys-sampling-factor,g", "Small ring system conformer sampling factor (default: " + 
			  boost::lexical_cast<std::string>(settings.getSmallRingSystemSamplingFactor()) + ", must be > 1).",
			  value<std::size_t>()->notifier(boost::bind(&GenFragLibImpl::setSmallRingSystemSamplingFactor, this, _1)));
	addOption("force-field,f", "Build force field (MMFF94, MMFF94_NO_ESTAT, MMFF94S, MMFF94S_EXT, MMFF94S_NO_ESTAT, MMFF94S_EXT_NO_ESTAT, default: " + getForceFieldTypeString() + ").", 
			  value<std::string>()->notifier(boost::bind(&GenFragLibImpl::setForceFieldType, this, _1)));
	addOption("strict-param,s", "Perform strict MMFF94 parameterization (default: true).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&GenFragLibImpl::setStrictParameterization, this, _1)));
	addOption("dielectric-const,D", "Dielectric constant used for the calculation of electrostatic interaction energies (default: " +
			  (boost::format("%.4f") % settings.getDielectricConstant()).str() + ").", 
			  value<double>()->notifier(boost::bind(&GenFragLibImpl::setDielectricConst, this, _1)));
	addOption("dist-exponent,E", "Distance exponent used for the calculation of electrostatic interaction energies (default: " +
			  (boost::format("%.4f") % settings.getDistanceExponent()).str() + ").", 
			  value<double>()->notifier(boost::bind(&GenFragLibImpl::setDistExponent, this, _1)));
	addOption("pres-bonding-geom,b", "Preserve input bond lengths and angles (default: false).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&GenFragLibImpl::setPreserveBondingGeometry, this, _1)));

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

void GenFragLibImpl::applyPreset(const std::string& pres_str)
{
	std::string pres = pres_str;
	boost::to_upper(pres);

	if (pres == "FAST")
		settings = ConformerGeneratorSettings::FAST;
	else if (pres == "THOROUGH")
		settings = ConformerGeneratorSettings::THOROUGH;
	else
		throwValidationError("preset");

	preset = pres;
}

void GenFragLibImpl::setTimeout(std::size_t timeout)
{
	settings.getSmallRingSystemSettings().setTimeout(timeout * 1000);
	settings.getMacrocycleSettings().setTimeout(timeout * 1000);
	settings.getChainSettings().setTimeout(timeout * 1000);
}

void GenFragLibImpl::setStrictParameterization(bool strict)
{
	settings.strictForceFieldParameterization(strict);
}

void GenFragLibImpl::setPreserveBondingGeometry(bool preserve)
{
	settings.preserveInputBondingGeometries(preserve);
}

void GenFragLibImpl::setRMSD(double rmsd)
{
	if (rmsd < 0)
		throwValidationError("rmsd");

	settings.getSmallRingSystemSettings().setMinRMSD(rmsd);
}

void GenFragLibImpl::setEnergyWindow(double ewin)
{
	if (ewin < 0)
		throwValidationError("e-window");

	settings.getSmallRingSystemSettings().setEnergyWindow(ewin);
}

void GenFragLibImpl::setSmallRingSystemSamplingFactor(std::size_t factor)
{
	if (factor < 1)
		throwValidationError("small-rsys-sampling-factor");

	settings.setSmallRingSystemSamplingFactor(factor);
}

void GenFragLibImpl::setForceFieldType(const std::string& type_str)
{
	using namespace CDPL;
	using namespace ConfGen;

	std::string uc_type = type_str;
	boost::to_upper(uc_type);

	if (uc_type == "MMFF94")
		settings.setForceFieldType(ForceFieldType::MMFF94);
	else if (uc_type == "MMFF94_NO_ESTAT")
		settings.setForceFieldType(ForceFieldType::MMFF94_NO_ESTAT);
	else if (uc_type == "MMFF94S")
		settings.setForceFieldType(ForceFieldType::MMFF94S);
	else if (uc_type == "MMFF94S_EXT")
		settings.setForceFieldType(ForceFieldType::MMFF94S_EXT);
	else if (uc_type == "MMFF94S_NO_ESTAT")
		settings.setForceFieldType(ForceFieldType::MMFF94S_NO_ESTAT);
	else if (uc_type == "MMFF94S_EXT_NO_ESTAT")
		settings.setForceFieldType(ForceFieldType::MMFF94S_EXT_NO_ESTAT);
	else
		throwValidationError("forcefield");
}

void GenFragLibImpl::setDielectricConst(double de_const)
{
	settings.setDielectricConstant(de_const);
}

void GenFragLibImpl::setDistExponent(double exp)
{
	settings.setDistanceExponent(exp);
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

		if (numThreads > 0)
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

		printMessage(INFO, "Adding Fragments to Output Library...");

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
	
	printMessage(INFO, "Loading Fragments from Library '" + fname + "'...");

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

	if (numThreads > 0) {
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

	printMessage(INFO, "Saving Fragments to Library '" + outputFile + "'...");

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
		throw Base::IOError("saving fragments to library '" + outputFile + "' failed");

	printMessage(INFO, " - Saved " + boost::lexical_cast<std::string>(fragmentLibPtr->getNumEntries()) + " fragments", false);

	return EXIT_SUCCESS;
}

void GenFragLibImpl::setErrorMessage(const std::string& msg)
{
	if (numThreads > 0) {
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
	if (numThreads > 0) {
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

std::size_t GenFragLibImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
	if (termSignalCaught())
		return 0;

	if (haveErrorMessage())
		return 0;

	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(molReadMutex);

		return doReadNextMolecule(mol);
	}

	return doReadNextMolecule(mol);
}

std::size_t GenFragLibImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
{
	while (true) {
		try {
			if (inputReader.getRecordIndex() >= inputReader.getNumRecords()) 
				return 0;

			if (!inputReader.read(mol)) {
				printMessage(ERROR, "Reading molecule " + createMoleculeIdentifier(inputReader.getRecordIndex() + 1) + " failed");			
				
				inputReader.setRecordIndex(inputReader.getRecordIndex() + 1);
				continue;
			}

			printProgress("Processing Molecules...        ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());

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
	if (numThreads == 0) {
		CmdLineBase::printMessage(level, msg, nl, file_only);
		return;
	}

	boost::lock_guard<boost::mutex> lock(mutex);

	CmdLineBase::printMessage(level, msg, nl, file_only);
}

void GenFragLibImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE,     " Input File(s):                       " + inputFiles[0]);
	
	for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(38, ' ') + *it);

	printMessage(VERBOSE,     " Output File:                         " + outputFile);
 	printMessage(VERBOSE,     " Mode:                                " + getModeString());
 	printMessage(VERBOSE,     " Preset:                              " + preset);

	if (mode != MERGE) {
		printMessage(VERBOSE, " Multithreading:                      " + std::string(numThreads > 0 ? "Yes" : "No"));

		if (numThreads > 0)
			printMessage(VERBOSE, " Number of Threads:                   " + boost::lexical_cast<std::string>(numThreads));

		printMessage(VERBOSE, " Input File Format:                   " + (inputHandler ? inputHandler->getDataFormat().getName() : std::string("Auto-detect")));
		printMessage(VERBOSE, " Max. Output Library Size:            " + boost::lexical_cast<std::string>(maxLibSize));
		printMessage(VERBOSE, " Timeout:                             " + boost::lexical_cast<std::string>(settings.getMacrocycleSettings().getTimeout() / 1000) + "s");
		printMessage(VERBOSE, " Min. RMSD:                           " + (boost::format("%.4f") % settings.getMacrocycleSettings().getMinRMSD()).str());
		printMessage(VERBOSE, " Energy Window:                       " + boost::lexical_cast<std::string>(settings.getSmallRingSystemSettings().getEnergyWindow()));
		printMessage(VERBOSE, " Strict Force Field Parameterization: " + std::string(settings.strictForceFieldParameterization() ? "Yes" : "No"));
		printMessage(VERBOSE, " Build Force Field:                   " + getForceFieldTypeString());
		printMessage(VERBOSE, " Dielectric Constant:                 " + (boost::format("%.4f") % settings.getDielectricConstant()).str());
		printMessage(VERBOSE, " Distance Exponent:                   " + (boost::format("%.4f") % settings.getDistanceExponent()).str());
		printMessage(VERBOSE, " Small Ring Sys. Sampling Factor:     " + boost::lexical_cast<std::string>(settings.getSmallRingSystemSamplingFactor()));
		printMessage(VERBOSE, " Preserve Input Bonding Geometries:   " + std::string(settings.preserveInputBondingGeometries() ? "Yes" : "No"));
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

	unsigned int ff_type = settings.getForceFieldType();

	if (ff_type == ForceFieldType::MMFF94)
		return "MMFF94";
	
	if (ff_type == ForceFieldType::MMFF94_NO_ESTAT)
		return "MMFF94_NO_ESTAT";

	if (ff_type == ForceFieldType::MMFF94S)
		return "MMFF94S";

	if (ff_type == ForceFieldType::MMFF94S_EXT)
		return "MMFF94S_EXT";
	
	if (ff_type == ForceFieldType::MMFF94S_NO_ESTAT)
		return "MMFF94S_NO_ESTAT";

	if (ff_type == ForceFieldType::MMFF94S_EXT_NO_ESTAT)
		return "MMFF94S_EXT_NO_ESTAT";
	
	return "UNKNOWN";
}

std::string GenFragLibImpl::createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol)
{
	if (!getName(mol).empty())
		return ('\'' + getName(mol) + "' (" + createMoleculeIdentifier(rec_idx) + ')');

	return createMoleculeIdentifier(rec_idx);
}

std::string GenFragLibImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
	return (boost::lexical_cast<std::string>(rec_idx) + '/' + boost::lexical_cast<std::string>(inputReader.getNumRecords()));
}
