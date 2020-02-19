/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautGenImpl.cpp
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
#include <iterator>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/TautomerScore.hpp"
#include "CDPL/Chem/TautomerGenerator.hpp"
#include "CDPL/Chem/KetoEnolTautomerization.hpp"  
#include "CDPL/Chem/ImineEnamineTautomerization.hpp"  
#include "CDPL/Chem/NitrosoOximeTautomerization.hpp"  
#include "CDPL/Chem/NitroAciTautomerization.hpp"  
#include "CDPL/Chem/AmideImidicAcidTautomerization.hpp"  
#include "CDPL/Chem/LactamLactimTautomerization.hpp"  
#include "CDPL/Chem/KeteneYnolTautomerization.hpp"  
#include "CDPL/Chem/PhosphinicAcidTautomerization.hpp"  
#include "CDPL/Chem/SulfenicAcidTautomerization.hpp"  
#include "CDPL/Chem/GenericHydrogen13ShiftTautomerization.hpp"  
#include "CDPL/Chem/GenericHydrogen15ShiftTautomerization.hpp"  
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"  
#include "CDPL/Chem/AtomPropertyFlag.hpp"  
#include "CDPL/Chem/BondPropertyFlag.hpp"  
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Lib/HelperFunctions.hpp"

#include "TautGenImpl.hpp"


using namespace TautGen;


class TautGenImpl::InputScanProgressCallback
{

public:
	class Terminated : public std::exception {};

	InputScanProgressCallback(TautGenImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

	void operator()(const CDPL::Base::DataIOBase&, double progress) const {
		if (TautGenImpl::termSignalCaught())
			throw Terminated();

		parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
	}

private:
	TautGenImpl* parent;
	double       offset;
	double       scale;
};


class TautGenImpl::TautGenerationWorker
{

public:
	TautGenerationWorker(TautGenImpl* parent):
		parent(parent), numProcMols(0),	numGenTauts(0), numGenMolTauts(0) {

		if (parent->mode != STANDARDIZE)
			return;

		using namespace CDPL;
		using namespace Chem;
		
		unsigned int atom_flags = AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE;
		unsigned int bond_flags = BondPropertyFlag::ORDER;

		if (parent->regardIsotopes) 
			atom_flags |= AtomPropertyFlag::ISOTOPE;

		if (parent->regardStereo) {
			atom_flags |= AtomPropertyFlag::CIP_CONFIGURATION;
			bond_flags |= BondPropertyFlag::CIP_CONFIGURATION;
		}

		hashCalc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hashCalc, atom_flags));
		hashCalc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(hashCalc, bond_flags));
		hashCalc.includeGlobalStereoFeatures(parent->regardStereo);
	}

	void operator()() {
		try {
			init();
	
			while (processNextMolecule());
	
		} catch (const std::exception& e) {
			parent->setErrorMessage(std::string("unexpected exception while generating tautomers: ") + e.what());

		} catch (...) {
			parent->setErrorMessage("unexpected exception while generating tautomers");
		}
	}

	std::size_t getNumProcMolecules() const {
		return numProcMols;
	}

	std::size_t getNumGenTautomers() const {
		return numGenTauts;
	}

private:
	void init() {
		using namespace CDPL;
		using namespace Chem;

		switch (parent->mode) {

			case GEOMETRICALLY_UNIQUE:
				tautGen.setMode(TautomerGenerator::GEOMETRICALLY_UNIQUE);
				break;

			case EXHAUSTIVE:
				tautGen.setMode(TautomerGenerator::EXHAUSTIVE);
				break;

			default:
				tautGen.setMode(TautomerGenerator::TOPOLOGICALLY_UNIQUE);
		}

		tautGen.setCallbackFunction(boost::bind(&TautGenerationWorker::tautomerGenerated, this, _1));
		tautGen.regardIsotopes(parent->regardIsotopes);
		tautGen.regardStereochemistry(parent->regardStereo);
		tautGen.setCustomSetupFunction(boost::bind(&setRingFlags, _1, false));

		PatternBasedTautomerizationRule::SharedPointer h13_shift(new GenericHydrogen13ShiftTautomerization());
		PatternBasedTautomerizationRule::SharedPointer h15_shift(new GenericHydrogen15ShiftTautomerization());
		PatternBasedTautomerizationRule::SharedPointer keto_enol(new KetoEnolTautomerization());
		PatternBasedTautomerizationRule::SharedPointer imine_enamine(new ImineEnamineTautomerization());  
		PatternBasedTautomerizationRule::SharedPointer nitroso_oxime(new NitrosoOximeTautomerization());  
		PatternBasedTautomerizationRule::SharedPointer nitro_aci(new NitroAciTautomerization());  
		PatternBasedTautomerizationRule::SharedPointer amide_imidic(new AmideImidicAcidTautomerization());  
		PatternBasedTautomerizationRule::SharedPointer lactam_lactim(new LactamLactimTautomerization());  
		PatternBasedTautomerizationRule::SharedPointer ketene_ynol(new KeteneYnolTautomerization());
		PatternBasedTautomerizationRule::SharedPointer posph_acid(new PhosphinicAcidTautomerization());
		PatternBasedTautomerizationRule::SharedPointer sulf_acid(new SulfenicAcidTautomerization());

		h13_shift->addExcludePatterns(*keto_enol);
		h13_shift->addExcludePatterns(*imine_enamine);
		h13_shift->addExcludePatterns(*nitroso_oxime);
		h13_shift->addExcludePatterns(*amide_imidic);
		h13_shift->addExcludePatterns(*lactam_lactim);
		h13_shift->addExcludePatterns(*nitro_aci);

		if (parent->ketoEnol)
			tautGen.addTautomerizationRule(keto_enol);
		else
			h15_shift->addExcludePatterns(*keto_enol);

		if (parent->imineEnamine)
			tautGen.addTautomerizationRule(imine_enamine);
		else
			h15_shift->addExcludePatterns(*imine_enamine);

		if (parent->amideImidicAcid)
			tautGen.addTautomerizationRule(amide_imidic);
		else
			h15_shift->addExcludePatterns(*amide_imidic);

		if (parent->lactamLactim)
			tautGen.addTautomerizationRule(lactam_lactim);
		else
			h15_shift->addExcludePatterns(*lactam_lactim);

		if (parent->nitrosoOxime)
			tautGen.addTautomerizationRule(nitroso_oxime);
		else
			h15_shift->addExcludePatterns(*nitroso_oxime);

		if (parent->keteneYnol)
			tautGen.addTautomerizationRule(ketene_ynol);

		if (parent->nitroAci)
			tautGen.addTautomerizationRule(nitro_aci);
		else
			h15_shift->addExcludePatterns(*nitro_aci);

		if (parent->phosphinicAcid)
			tautGen.addTautomerizationRule(posph_acid);

		if (parent->sulfenicAcid)
			tautGen.addTautomerizationRule(sulf_acid);

		if (parent->genericH13Shift)
			tautGen.addTautomerizationRule(h13_shift);

		if (parent->genericH15Shift)
			tautGen.addTautomerizationRule(h15_shift);
	}

	bool processNextMolecule() {
		std::size_t rec_idx = parent->readNextMolecule(molecule);

		if (!rec_idx)
			return false;

		try {
			if (parent->neutralize)
				CDPL::Chem::neutralize(molecule);

			if (parent->regardStereo) {
				calcImplicitHydrogenCounts(molecule, false);
		
				initMolecule(molecule, false);
				
				calcAtomStereoDescriptors(molecule, false);
				calcBondStereoDescriptors(molecule, false);
			}

			numGenMolTauts = 0;
			tautScore = -1.0;

			tautGen.generate(molecule);

			if (parent->mode == STANDARDIZE && numGenMolTauts > 0) {
				perceiveComponents(stdTautomer, true);
				perceiveSSSR(stdTautomer, true);

				outputMolecule(stdTautomer, tautScore, hashCode);
			}

			parent->printMessage(VERBOSE, "Molecule " + parent->createMoleculeIdentifier(rec_idx, molecule) + ": " +
								 boost::lexical_cast<std::string>(numGenMolTauts) + (numGenMolTauts == 1 ? " tautomer" : " tautomers"));
			numProcMols++;

			return true;

		} catch (const std::exception& e) {
			parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, molecule) + ": " + e.what());

		} catch (...) {
			parent->setErrorMessage("unexpected exception while processing molecule " + parent->createMoleculeIdentifier(rec_idx, molecule));
		}

		return false;
	}

	bool tautomerGenerated(CDPL::Chem::MolecularGraph& taut) {
		using namespace CDPL;
		using namespace Chem;

		if (parent->haveErrorMessage() || TautGenImpl::termSignalCaught())
			return false;

		numGenTauts++;
		numGenMolTauts++;

		initMolecule(taut, false);

		if (parent->regardStereo) {
			calcCIPPriorities(taut, false);
			calcAtomCIPConfigurations(taut, false);
			calcBondCIPConfigurations(taut, false);
		}

		double score = tautScoreCalc(taut);

		if (parent->mode != STANDARDIZE) {
			outputMolecule(taut, score, hashCalc.calculate(taut));

		} else if (score >= tautScore) {
			Base::uint64 hash = hashCalc.calculate(taut);

			if (score > tautScore || hash > hashCode) {
				stdTautomer = taut;
				tautScore = score;
				hashCode = hash;

				copyAtomStereoDescriptors(stdTautomer, taut, 0);
				copyBondStereoDescriptors(stdTautomer, taut, 0, 0);
			}
		}

		return (parent->maxNumTautomers == 0 || numGenMolTauts < parent->maxNumTautomers);
	}

	void initMolecule(CDPL::Chem::MolecularGraph& molgraph, bool override) const {
		using namespace CDPL;
		using namespace Chem;

		setRingFlags(molgraph, override);
		perceiveHybridizationStates(molgraph, override);
		perceiveSSSR(molgraph, override);
		setAromaticityFlags(molgraph, override);
	}

	void outputMolecule(CDPL::Chem::MolecularGraph& molgraph, double score, CDPL::Base::uint64 hash) {
		using namespace CDPL;
		using namespace Chem;

		StringDataBlock::SharedPointer sd(new StringDataBlock());

		sd->addEntry("<Tautomer Score>", boost::lexical_cast<std::string>(score));
		sd->addEntry("<Tautomer ID>", boost::lexical_cast<std::string>(hash));

		setStructureData(molgraph, sd);

		perceiveComponents(molgraph, false);
		setAtomSymbolsFromTypes(molgraph, false);
		setName(molgraph, getName(molecule));

		parent->writeMolecule(molgraph);
	}

	TautGenImpl*                         parent;
	CDPL::Chem::TautomerGenerator        tautGen;
	CDPL::Chem::TautomerScore            tautScoreCalc;
	CDPL::Chem::HashCodeCalculator       hashCalc;
	CDPL::Chem::BasicMolecule            molecule;
	CDPL::Chem::BasicMolecule            stdTautomer;
	double                               tautScore;
	CDPL::Base::uint64                   hashCode;
	std::size_t                          numProcMols;
	std::size_t                          numGenTauts;
	std::size_t                          numGenMolTauts;
};


TautGenImpl::TautGenImpl(): 
	regardStereo(true), regardIsotopes(true), neutralize(false), ketoEnol(true), 
	imineEnamine(true), nitrosoOxime(true), amideImidicAcid(true),
	lactamLactim(true), keteneYnol(true), nitroAci(true), phosphinicAcid(true),
	sulfenicAcid(true), genericH13Shift(true), genericH15Shift(true),
	numThreads(0), maxNumTautomers(0), mode(Mode::TOPOLOGICALLY_UNIQUE), 
	inputHandler(), outputHandler(), outputWriter(), numOutTautomers(0)
{
	addOption("input,i", "Input file(s).", 
			  value<StringList>(&inputFiles)->multitoken()->required());
	addOption("output,o", "Output fragment library file.", 
			  value<std::string>(&outputFile)->required());
	addOption("mode,m", "Tautomer generation mode (STANDARDIZE, TOP_UNIQUE, GEO_UNIQUE, EXHAUSTIVE default: TOP_UNIQUE).", 
			  value<std::string>()->notifier(boost::bind(&TautGenImpl::setMode, this, _1)));
	addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
			  boost::lexical_cast<std::string>(boost::thread::hardware_concurrency()) + 
			  " threads, must be >= 0, 0 disables multithreading).", 
			  value<std::size_t>(&numThreads)->implicit_value(boost::thread::hardware_concurrency()));
	addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&TautGenImpl::setInputFormat, this, _1)));
	addOption("output-format,O", "Output file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&TautGenImpl::setOutputFormat, this, _1)));
	addOption("regard-stereo,s", "Consider stereochemistry in topological duplicate detection (default: true).", 
			  value<bool>(&regardStereo)->implicit_value(true));
	addOption("regard-iso,d", "Whether or not isotope information matters in topological duplicate detection (default: true).", 
			  value<bool>(&regardIsotopes)->implicit_value(true));
	addOption("neutralize,z", "Neutralize molecule before generating tautomers (default: false).", 
			  value<bool>(&neutralize)->implicit_value(true));
	addOption("max-num-tautomers,n", "Maximum number of output tautomers for each molecule (default: 0, must be >= 0, 0 disables limit).",
			  value<std::size_t>(&maxNumTautomers));
	addOption("keto-enol", "Enable keto <-> enol tautomerization (default: true).", 
			  value<bool>(&ketoEnol)->implicit_value(true));
	addOption("imine-enamine", "Enable imine <-> enamine tautomerization (default: true).", 
			  value<bool>(&imineEnamine)->implicit_value(true));
	addOption("nitroso-oxime", "Enable nitroso <-> oxime tautomerization (default: true).", 
			  value<bool>(&nitrosoOxime)->implicit_value(true));
	addOption("amide-imidic-acid", "Enable amide <-> imidic acid tautomerization (default: true).", 
			  value<bool>(&amideImidicAcid)->implicit_value(true));
	addOption("lactam-lactim", "Enable lactam <-> lactim tautomerization (default: true).", 
			  value<bool>(&lactamLactim)->implicit_value(true));
	addOption("ketene-ynol", "Enable ketene <-> ynol form tautomerization (default: true).", 
			  value<bool>(&keteneYnol)->implicit_value(true));
	addOption("nitro-aci", "Enable nitro <-> aci form tautomerization (default: true).", 
			  value<bool>(&nitroAci)->implicit_value(true));
	addOption("phosphinic-acid", "Enable phosphinic acid tautomerization (default: true).", 
			  value<bool>(&phosphinicAcid)->implicit_value(true));
	addOption("sulfenic-acid", "Enable sulfenic acid tautomerization (default: true).", 
			  value<bool>(&sulfenicAcid)->implicit_value(true));
	addOption("generic-h13-shift", "Enable generic hydrogen 1 <-> 3 shift tautomerization (default: true).", 
			  value<bool>(&genericH13Shift)->implicit_value(true));
	addOption("generic-h15-shift", "Enable generic hydrogen 1 <-> 5 shift tautomerization (default: true).", 
			  value<bool>(&genericH15Shift)->implicit_value(true));

	addOptionLongDescriptions();
}

const char* TautGenImpl::getProgName() const
{
    return "TautGen";
}

const char* TautGenImpl::getProgCopyright() const
{
    return "Thomas A. Seidel";
}

const char* TautGenImpl::getProgAboutText() const
{
	return "Performs tautomer generation for a set of input molecules.";
}

void TautGenImpl::addOptionLongDescriptions()
{
	StringList formats;
	std::string formats_str = "Supported Input Formats:\n";

	AppUtils::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

	for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

	addOptionLongDescription("input-format", 
							 "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
							 "(because missing, misleading or not supported).");

	formats_str.pop_back();

	addOptionLongDescription("input", 
							 "Specifies one or more input file(s) with molecules for which tautomers have to be generated.\n\n" +
							 formats_str);

	formats.clear();
	formats_str = "Supported Output Formats:\n";

	AppUtils::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

	for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

	addOptionLongDescription("output-format", 
							 "Allows to explicitly specify the output format by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
							 "(because missing, misleading or not supported).");

	formats_str.pop_back();

	addOptionLongDescription("output", 
							 "Specifies the output file where the generated tautomers will be stored.\n\n" +
							 formats_str);
}

void TautGenImpl::setMode(const std::string& mode_str)
{
	using namespace CDPL::Pharm;

	std::string uc_mode = mode_str;
	boost::to_upper(uc_mode);

	if (uc_mode == "STANDARDIZE")
		mode = Mode::STANDARDIZE;
	else if (uc_mode == "TOP_UNIQUE")
		mode = Mode::TOPOLOGICALLY_UNIQUE;
	else if (uc_mode == "GEO_UNIQUE")
		mode = Mode::GEOMETRICALLY_UNIQUE;
	else if (uc_mode == "EXHAUSTIVE")
		mode = Mode::EXHAUSTIVE;
	else
		throwValidationError("mode");
}

void TautGenImpl::setInputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	inputHandler = Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext);

	if (!inputHandler)
		throwValidationError("input-format");
}

void TautGenImpl::setOutputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	outputHandler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext);

	if (!outputHandler)
		throwValidationError("output-format");
}

int TautGenImpl::process()
{
	startTime = Clock::now();

	printMessage(INFO, getProgTitleString());
	printMessage(INFO, "");

	checkInputFiles();
	printOptionSummary();

	initInputReader();
	initOutputWriter();

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

	if (termSignalCaught())
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

void TautGenImpl::processSingleThreaded()
{
	using namespace CDPL;

	TautGenerationWorker worker(this);

	worker();

	printMessage(INFO, "");

	if (haveErrorMessage())
		return;

	if (termSignalCaught())
		return;

	printStatistics(worker.getNumProcMolecules(), worker.getNumGenTautomers(),
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void TautGenImpl::processMultiThreaded()
{
	using namespace CDPL;

	typedef boost::shared_ptr<TautGenerationWorker> TautGenerationWorkerPtr;
	typedef std::vector<TautGenerationWorkerPtr> TautGenerationWorkerList;

	boost::thread_group thread_grp;
	TautGenerationWorkerList worker_list;

	try {
		for (std::size_t i = 0; i < numThreads; i++) {
			if (termSignalCaught())
				break;

			TautGenerationWorkerPtr worker_ptr(new TautGenerationWorker(this));

			thread_grp.create_thread(boost::bind(&TautGenerationWorker::operator(), worker_ptr));
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
	std::size_t num_gen_tauts = 0;

	for (std::size_t i = 0; i < numThreads; i++) {
		const TautGenerationWorker& worker = *worker_list[i];

		num_proc_mols += worker.getNumProcMolecules();
		num_gen_tauts += worker.getNumGenTautomers();
	}

	printStatistics(num_proc_mols, num_gen_tauts,
					boost::chrono::duration_cast<boost::chrono::duration<std::size_t> >(Clock::now() - startTime).count());

}

void TautGenImpl::setErrorMessage(const std::string& msg)
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

bool TautGenImpl::haveErrorMessage()
{
	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(mutex);
		return !errorMessage.empty();
	}

	return !errorMessage.empty();
}

void TautGenImpl::printStatistics(std::size_t num_proc_mols, std::size_t num_gen_tauts, std::size_t proc_time)
{
	printMessage(INFO, "Statistics:");
	printMessage(INFO, " Processed Molecules: " + boost::lexical_cast<std::string>(num_proc_mols));
	printMessage(INFO, " Generated Tautomers: " + boost::lexical_cast<std::string>(num_gen_tauts));
	printMessage(INFO, " Output Tautomers:    " + boost::lexical_cast<std::string>(numOutTautomers));
	printMessage(INFO, " Processing Time:     " + AppUtils::formatTimeDuration(proc_time));
	printMessage(INFO, "");
}

std::size_t TautGenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
	if (termSignalCaught())
		return 0;

	if (haveErrorMessage())
		return 0;

	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(readMolMutex);

		return doReadNextMolecule(mol);
	}

	return doReadNextMolecule(mol);
}

std::size_t TautGenImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
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

void TautGenImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol)
{
	if (numThreads > 0) {
		boost::lock_guard<boost::mutex> lock(writeMolMutex);

		doWriteMolecule(mol);

	} else
		doWriteMolecule(mol);
}

void TautGenImpl::doWriteMolecule(const CDPL::Chem::MolecularGraph& mol)
{
	if (!outputWriter->write(mol))
		throw CDPL::Base::IOError("could not write generated tautomer");

	numOutTautomers++;
}

void TautGenImpl::checkInputFiles() const
{
	using namespace CDPL;

	StringList::const_iterator it = std::find_if(inputFiles.begin(), inputFiles.end(),
												 boost::bind(std::logical_not<bool>(), 
															 boost::bind(Util::fileExists, _1)));
	if (it != inputFiles.end())
		throw Base::IOError("file '" + *it + "' does not exist");

	if (std::find_if(inputFiles.begin(), inputFiles.end(),
					 boost::bind(Util::checkIfSameFile, boost::ref(outputFile),
								 _1)) != inputFiles.end())
		throw Base::ValueError("output file must not occur in list of input files");
}

void TautGenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
	if (numThreads == 0) {
		CmdLineBase::printMessage(level, msg, nl, file_only);
		return;
	}

	boost::lock_guard<boost::mutex> lock(mutex);

	CmdLineBase::printMessage(level, msg, nl, file_only);
}

void TautGenImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE, " Input File(s):                     " + inputFiles[0]);
	
	for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(36, ' ') + *it);

	printMessage(VERBOSE, " Output File:                       " + outputFile);
 	printMessage(VERBOSE, " Mode:                              " + getModeString());
	printMessage(VERBOSE, " Multithreading:                    " + std::string(numThreads > 0 ? "Yes" : "No"));

	if (numThreads > 0)
		printMessage(VERBOSE, " Number of Threads:                 " + boost::lexical_cast<std::string>(numThreads));

	printMessage(VERBOSE, " Input File Format:                 " + (inputHandler ? inputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Output File Format:                " + (outputHandler ? outputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Stereochemistry Aware:             " + std::string(regardStereo ? "Yes" : "No"));
	printMessage(VERBOSE, " Isotope Aware:                     " + std::string(regardIsotopes ? "Yes" : "No"));
	printMessage(VERBOSE, " Neutralize Charges:                " + std::string(neutralize ? "Yes" : "No"));
	printMessage(VERBOSE, " Max. Num. Tautomers:               " + boost::lexical_cast<std::string>(maxNumTautomers));
	printMessage(VERBOSE, " Keto-Enol Tautomerization:         " + std::string(ketoEnol ? "Yes" : "No"));
	printMessage(VERBOSE, " Imine-Enamine Tautomerization:     " + std::string(imineEnamine ? "Yes" : "No"));
	printMessage(VERBOSE, " Nitroso-Oxime Tautomerization:     " + std::string(nitrosoOxime ? "Yes" : "No"));
	printMessage(VERBOSE, " Amide-Imidic Acid Tautomerization: " + std::string(amideImidicAcid ? "Yes" : "No"));
	printMessage(VERBOSE, " Lactam-Lactim Tautomerization:     " + std::string(lactamLactim ? "Yes" : "No"));
	printMessage(VERBOSE, " Ketene-Ynol Tautomerization:       " + std::string(keteneYnol ? "Yes" : "No"));
	printMessage(VERBOSE, " Nitro-Aci Tautomerization:         " + std::string(nitroAci ? "Yes" : "No"));
	printMessage(VERBOSE, " Phosphinic Acid Tautomerization:   " + std::string(phosphinicAcid ? "Yes" : "No"));
	printMessage(VERBOSE, " Sulfenic Acid Tautomerization:     " + std::string(sulfenicAcid ? "Yes" : "No"));
	printMessage(VERBOSE, " Gen. H-1,3-Shift Tautomerization:  " + std::string(genericH13Shift ? "Yes" : "No"));
	printMessage(VERBOSE, " Gen. H-1,5-Shift Tautomerization:  " + std::string(genericH15Shift ? "Yes" : "No"));
	printMessage(VERBOSE, "");
}

void TautGenImpl::initInputReader()
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

	if (TautGenImpl::termSignalCaught())
		return;

	printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(inputReader.getNumRecords()) + " input molecule(s)");
	printMessage(INFO, "");
}

void TautGenImpl::initOutputWriter()
{
	using namespace CDPL;

	OutputHandlerPtr output_handler = getOutputHandler(outputFile);

	if (!output_handler)
		throw Base::IOError("no output handler found for file '" + outputFile + '\'');

	outputWriter = output_handler->createWriter(outputFile);

	setSMILESRecordFormatParameter(*outputWriter, "SN");
	setSMILESWriteCanonicalFormParameter(*outputWriter, true);
	setMultiConfExportParameter(*outputWriter, false);
}

TautGenImpl::InputHandlerPtr TautGenImpl::getInputHandler(const std::string& file_path) const
{
	if (inputHandler)
		return inputHandler;

	return AppUtils::getInputHandler<CDPL::Chem::Molecule>(file_path);
}

TautGenImpl::OutputHandlerPtr TautGenImpl::getOutputHandler(const std::string& file_path) const
{
	if (outputHandler)
		return outputHandler;

	return AppUtils::getOutputHandler<CDPL::Chem::MolecularGraph>(file_path);
}

std::string TautGenImpl::getModeString() const
{
	using namespace CDPL;

	if (mode == STANDARDIZE)
		return "STANDADIZE";

	if (mode == TOPOLOGICALLY_UNIQUE)
		return "TOP_UNIQUE";

	if (mode == GEOMETRICALLY_UNIQUE)
		return "GEO_UNIQUE";

	if (mode == EXHAUSTIVE)
		return "EXHAUSTIVE";
	
	return "UNKNOWN";
}

std::string TautGenImpl::createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol)
{
	if (!getName(mol).empty())
		return ('\'' + getName(mol) + "' (" + createMoleculeIdentifier(rec_idx) + ')');

	return createMoleculeIdentifier(rec_idx);
}

std::string TautGenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
	return (boost::lexical_cast<std::string>(rec_idx) + '/' + boost::lexical_cast<std::string>(inputReader.getNumRecords()));
}
