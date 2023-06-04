/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConfGenImpl.cpp
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
#include <iterator>
#include <fstream>
#include <sstream>
#include <thread>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/ConformerGenerator.hpp"
#include "CDPL/ConfGen/MoleculeFunctions.hpp"
#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/ConfGen/ForceFieldType.hpp"
#include "CDPL/ConfGen/ConformerSamplingMode.hpp"
#include "CDPL/ConfGen/NitrogenEnumerationMode.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"

#include "ConfGenImpl.hpp"
#include "CommonFunctions.hpp"


using namespace ConfGen;


class ConfGenImpl::InputScanProgressCallback
{

public:
	class Terminated : public std::exception {};

	InputScanProgressCallback(ConfGenImpl* parent, double offset, double scale): 
		parent(parent), offset(offset), scale(scale) {}

	void operator()(const CDPL::Base::DataIOBase&, double progress) const {
		if (termSignalCaught())
			throw Terminated();

		parent->printProgress("Scanning Input File(s)...      ", offset + scale * progress);
	}

private:
	ConfGenImpl* parent;
	double       offset;
	double       scale;
};


class ConfGenImpl::ConformerGenerationWorker
{

public:
	ConformerGenerationWorker(ConfGenImpl* parent):
		parent(parent), verbLevel(parent->getVerbosityLevel()), numProcMols(0),
		numFailedMols(0), numGenConfs(0) {

		confGen.setAbortCallback(boost::bind(&ConformerGenerationWorker::abort, this));
		confGen.getSettings() = parent->settings;

		if (parent->getVerbosityLevel() >= DEBUG)  
			confGen.setLogMessageCallback(boost::bind(&ConformerGenerationWorker::appendToLogRecord, this, _1));

		if (parent->torsionLib) {
			if (parent->replaceBuiltinTorLib)
				confGen.clearTorsionLibraries();

			confGen.addTorsionLibrary(parent->torsionLib);
		}

		if (parent->fragmentLib) {
			if (parent->replaceBuiltinFragLib)
				confGen.clearFragmentLibraries();

			confGen.addFragmentLibrary(parent->fragmentLib);
		}
	}

	void operator()() {
		try {
			while (processNextMolecule());
		
		} catch (const std::exception& e) {
			parent->setErrorMessage(std::string("unexpected exception while generating conformers: ") + e.what());

		} catch (...) {
			parent->setErrorMessage("unexpected exception while generating conformers");
		}
	}

	std::size_t getNumProcMolecules() const {
		return numProcMols;
	}

	std::size_t getNumFailedMolecules() const {
		return numFailedMols;
	}

	std::size_t getNumGenConformers() const {
		return numGenConfs;
	}

private:
	bool processNextMolecule() {
		using namespace CDPL::ConfGen;

		timer.start();

		std::size_t rec_idx = parent->readNextMolecule(molecule);

		if (!rec_idx)
			return false;

		try {
			logRecordStream.str(std::string());

			if (verbLevel >= DEBUG) 
				logRecordStream << std::endl << "- Molecule " << 
					parent->createMoleculeIdentifier(rec_idx, molecule) << ':' << std::endl;	

			if (parent->failedOutputWriter)
				origMolecule = molecule;

			prepareForConformerGeneration(molecule, parent->canonicalize);
			
			if (checkRotorBondCount(rec_idx)) {
				unsigned int ret_code = confGen.generate(molecule);

				switch (ret_code) {

					case ReturnCode::ABORTED:
						return false;

					case ReturnCode::SUCCESS:
					case ReturnCode::TOO_MUCH_SYMMETRY:
						outputConformers(rec_idx, ret_code);
						break;

					default:
						handleError(rec_idx, ret_code);
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

	bool checkRotorBondCount(std::size_t rec_idx) {
		using namespace CDPL::ConfGen;

		if (parent->maxNumRotorBonds < 0)
			return true;

		if (getRotatableBondCount(molecule, confGen.getSettings().sampleHeteroAtomHydrogens()) <= std::size_t(parent->maxNumRotorBonds))
			return true;

		if (verbLevel >= DEBUG) 
			logRecordStream << "Maximum allowed rotatable bond count exceeded!" << std::endl;

		else if (verbLevel >= ERROR) 
			logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": maximum allowed rotatable bound count exceeded" << std::endl; 

		numFailedMols++;

		if (parent->failedOutputWriter)
			parent->writeMolecule(origMolecule, true);

		return false;
	}

	void outputConformers(std::size_t rec_idx, unsigned int ret_code) {
		using namespace CDPL::ConfGen;

		setMDLDimensionality(molecule, 3);

		std::size_t num_confs = confGen.getNumConformers();

		if (verbLevel == VERBOSE) {
			logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": " << 
				num_confs << (num_confs == 1 ? " conf., " : " confs., ") << timer.format(3, "%w") << 's' << std::endl;

			if (ret_code == ReturnCode::TOO_MUCH_SYMMETRY)
				logRecordStream << "Warning: not all top. symmetry mappings could be considered, output ensemble may contain confs. violating the specified RMSD threshold" << std::endl;

		} else if (verbLevel == ERROR && ret_code == ReturnCode::TOO_MUCH_SYMMETRY) {
			logRecordStream << "Molecule " <<  parent->createMoleculeIdentifier(rec_idx, molecule) << ": " <<
				"not all top. symmetry mappings could be considered, output ensemble may contain confs. violating the specified RMSD threshold" << std::endl;
		}

		confGen.setConformers(molecule);

		parent->writeMolecule(molecule, false);

		numGenConfs += num_confs;
	}

	void handleError(std::size_t rec_idx, unsigned int ret_code) {
		using namespace CDPL::ConfGen;

		numFailedMols++;

		if (parent->failedOutputWriter) {
			calcImplicitHydrogenCounts(origMolecule, true);
			perceiveComponents(origMolecule, true);
			perceiveSSSR(origMolecule, true);

			try {
				parent->writeMolecule(origMolecule, true);

			} catch (const std::exception& e) {
				if (verbLevel >= ERROR)
					logRecordStream << "Error while writing failed molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) <<
						": " << e.what() << std::endl;
			}
		}

		if (verbLevel < ERROR)
			return;

		if (verbLevel >= DEBUG)
			return;

		std::string err_msg;

		switch (ret_code) {

			case ReturnCode::FORCEFIELD_SETUP_FAILED:
				err_msg = "force field setup failed";
				break;

			case ReturnCode::FORCEFIELD_MINIMIZATION_FAILED:
				err_msg = "structure refinement failed";
				break;

			case ReturnCode::CONF_GEN_FAILED:
				err_msg = "could not generate any conformers";
				break;
		
			case ReturnCode::FRAGMENT_CONF_GEN_FAILED:
				err_msg = "fragment conformer generation failed";
				break;

			case ReturnCode::TIMEOUT:
				err_msg = "time limit exceeded";
				break;

			default:
				err_msg = "unspecified error: " + boost::lexical_cast<std::string>(ret_code);
				break;
		}

		logRecordStream << "Molecule " << parent->createMoleculeIdentifier(rec_idx, molecule) << ": " << err_msg << std::endl; 
	}

	void appendToLogRecord(const std::string& msg) {
		logRecordStream << msg;
	}

	bool abort() const {
		if (parent->haveErrorMessage() || termSignalCaught())
			return true;

		return false;
	}

	typedef std::chrono::system_clock Clock;

	ConfGenImpl*                         parent;
	CDPL::ConfGen::ConformerGenerator    confGen;
	CDPL::Chem::BasicMolecule            molecule;
	CDPL::Chem::Fragment                 origMolecule;
	std::stringstream                    logRecordStream;
	VerbosityLevel                       verbLevel;
	boost::timer::cpu_timer              timer;
	std::size_t                          numProcMols;
	std::size_t                          numFailedMols;
	std::size_t                          numGenConfs;
};


ConfGenImpl::ConfGenImpl(): 
	numThreads(0), settings(ConformerGeneratorSettings::MEDIUM_SET_DIVERSE), 
	confGenPreset("MEDIUM_SET_DIVERSE"), fragBuildPreset("FAST"), canonicalize(false), energySDEntry(false), 
	energyComment(false), confIndexSuffix(false), maxNumRotorBonds(-1), torsionLib(), fragmentLib(),
	inputHandler(), outputHandler(), outputWriter(), failedOutputHandler(), failedOutputWriter()
{
	addOption("input,i", "Input file(s).", 
			  value<StringList>(&inputFiles)->multitoken()->required());
	addOption("output,o", "Output file.", 
			  value<std::string>(&outputFile)->required());
	addOption("failed,f", "Failed molecule output file.",
			  value<std::string>(&failedFile));
	addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
			  boost::lexical_cast<std::string>(std::thread::hardware_concurrency()) + 
			  " threads, must be >= 0, 0 disables multithreading).", 
			  value<std::size_t>(&numThreads)->implicit_value(std::thread::hardware_concurrency()));
	addOption("conf-gen-preset,C", "Conformer generation preset to use (SMALL_SET_DIVERSE, MEDIUM_SET_DIVERSE, " 
			  "LARGE_SET_DIVERSE, SMALL_SET_DENSE, MEDIUM_SET_DENSE, LARGE_SET_DENSE, default: MEDIUM_SET_DIVERSE).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::applyConfGenPreset, this, _1)));
	addOption("mode,m", "Conformer sampling mode (AUTO, STOCHASTIC, SYSTEMATIC, default: " + getSamplingModeString() + ").", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setSamplingMode, this, _1)));
	addOption("e-window,e", "Output energy window for generated conformers (default: " + 
			  boost::lexical_cast<std::string>(settings.getEnergyWindow()) + ", must be >= 0).",
			  value<double>()->notifier(boost::bind(&ConfGenImpl::setEnergyWindow, this, _1)));
	addOption("rmsd,r", "Minimum RMSD for output conformer selection (default: " + 
			  (boost::format("%.4f") % settings.getMinRMSD()).str() + ", must be >= 0, 0 disables RMSD checking).",
			  value<double>()->notifier(boost::bind(&ConfGenImpl::setRMSD, this, _1)));
	addOption("max-num-out-confs,n", "Maximum number of output conformers per molecule (default: " + 
			  boost::lexical_cast<std::string>(settings.getMaxNumOutputConformers()) + ", must be >= 0, 0 disables limit).",
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setMaxNumConfs, this, _1)));
	addOption("nitrogen-enum-mode,N", "Invertible nitrogen enumeration mode (NONE, ALL, UNSPECIFIED, default: " + 
			  getNitrogenEnumModeString() + ").", value<std::string>()->notifier(boost::bind(&ConfGenImpl::setNitrogenEnumMode, this, _1)));
	addOption("enum-rings,R", "Enumerate ring conformers (only effective in systematic sampling mode, default: true).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ConfGenImpl::setEnumRings, this, _1)));
	addOption("sample-het-hydrogens,H", "Perform torsion sampling for hydrogens on hetero atoms (default: false).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ConfGenImpl::setSampleHetAtomHydrogens, this, _1)));
	addOption("tol-range-sampling,A", "Additionally generate conformers for angles at the boundaries of the first "
			  "torsion angle tolerance range (only effective in systematic sampling mode, default: false).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ConfGenImpl::setSampleAngleTolRanges, this, _1)));
	addOption("include-input,u", "Add input 3D-structure to output conformer ensemble (default: false).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ConfGenImpl::setIncludeInput, this, _1)));
	addOption("from-scratch,S", "Discard input 3D-coordinates and generate conformers from scratch (default: true).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ConfGenImpl::setGenerateFromScratch, this, _1)));
	addOption("systematic-search-force-field,d", "Search force field used in systematic sampling (MMFF94, MMFF94_NO_ESTAT, "
			  "MMFF94S, MMFF94S_XOOP, MMFF94S_RTOR, MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, MMFF94S_RTOR_NO_ESTAT, MMFF94S_RTOR_XOOP_NO_ESTAT, default: " +
			  getForceFieldTypeString(settings.getForceFieldTypeSystematic()) + ").", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setSystematicSearchForceFieldType, this, _1)));
	addOption("stochastic-search-force-field,q", "Search force field used in stochastic smapling (MMFF94, MMFF94_NO_ESTAT, "
			  "MMFF94S, MMFF94S_XOOP, MMFF94S_RTOR, MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, MMFF94S_RTOR_NO_ESTAT, MMFF94S_RTOR_XOOP_NO_ESTAT, default: " +
			  getForceFieldTypeString(settings.getForceFieldTypeStochastic()) + ").", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setStochasticSearchForceFieldType, this, _1)));
	addOption("strict-param,s", "Perform strict MMFF94 parameterization (default: true).", 
			  value<bool>()->implicit_value(true)->notifier(boost::bind(&ConfGenImpl::setStrictParameterization, this, _1)));
	addOption("dielectric-const,D", "Dielectric constant used for the calculation of electrostatic interaction energies (default: " +
			  (boost::format("%.4f") % settings.getDielectricConstant()).str() + ").", 
			  value<double>()->notifier(boost::bind(&ConfGenImpl::setDielectricConst, this, _1)));
	addOption("dist-exponent,E", "Distance exponent used for the calculation of electrostatic interaction energies (default: " +
			  (boost::format("%.4f") % settings.getDistanceExponent()).str() + ").", 
			  value<double>()->notifier(boost::bind(&ConfGenImpl::setDistExponent, this, _1)));
	addOption("timeout,T", "Time in seconds after which molecule conformer generation will be stopped (default: " + 
			  boost::lexical_cast<std::string>(settings.getTimeout() / 1000) + " s, must be >= 0, 0 disables timeout).",
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setTimeout, this, _1)));
	addOption("max-num-rot-bonds,X", "Maximum number of allowed rotatable bonds, exceeding this limit causes molecule conf. generation to fail (default: " +
			  boost::lexical_cast<std::string>(maxNumRotorBonds) + ", negative values disable limit).", 
			  value<long>(&maxNumRotorBonds));
	addOption("max-pool-size,L", "Puts an upper limit on the number of generated output conformer candidates (only effective in systematic sampling mode, default: " +
			  boost::lexical_cast<std::string>(settings.getMaxPoolSize()) + ", must be >= 0, 0 disables limit).", 
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setMaxPoolSize, this, _1)));
	addOption("max-num-sampled-confs,x", "Maximum number of sampled conformers (only effective in stochastic sampling mode, default: " +
			  boost::lexical_cast<std::string>(settings.getMaxNumSampledConformers()) + ", must be >= 0, 0 disables limit).", 
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setMaxNumSampledConfs, this, _1)));
	addOption("conv-check-cycle-size,y", "Minimum number of duplicate conformers that have to be generated in succession to "
			  " consider convergence to be reached (only effective in stochastic sampling mode, default: " +
			  boost::lexical_cast<std::string>(settings.getConvergenceCheckCycleSize()) + ", must be > 0).", 
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setConvergenceCheckCycleSize, this, _1)));
	addOption("mc-rot-bond-count-thresh,Z", "Number of rotatable bonds in a ring above which stochastic sampling will be performed"
			  "(only effective in sampling mode AUTO, default: " +
			  boost::lexical_cast<std::string>(settings.getMacrocycleRotorBondCountThreshold()) + ", must be > 0).", 
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setMacrocycleRotorBondCountThreshold, this, _1)));
	addOption("ref-tol,P", "Energy tolerance at which force field structure refinement stops (only effective in stochastic sampling mode, default: " +
			  (boost::format("%.4f") % settings.getRefinementTolerance()).str() + ", must be >= 0, 0 results in refinement until convergence).", 
			  value<double>()->notifier(boost::bind(&ConfGenImpl::setRefTolerance, this, _1)));
	addOption("max-ref-iter,w", "Maximum number of force field structure refinement iterations (only effective in stochastic sampling mode, default: " +
			  boost::lexical_cast<std::string>(settings.getMaxNumRefinementIterations()) + ", must be >= 0, 0 disables limit).", 
			  value<std::size_t>()->notifier(boost::bind(&ConfGenImpl::setMaxNumRefIterations, this, _1)));
	addOption("add-tor-lib,k", "Torsion library to be used in addition to the built-in library (only effective in systematic sampling mode).",
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::addTorsionLib, this, _1)));
	addOption("set-tor-lib,K", "Torsion library used as a replacement for the built-in library (only effective in systematic sampling mode).",
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setTorsionLib, this, _1)));
	addOption("frag-build-preset,B", "Fragment build preset to use (FAST, THOROUGH, only effective in systematic sampling mode, default: FAST).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::applyFragBuildPreset, this, _1)));
	addOption("build-force-field,b", "Fragment build force field (MMFF94, MMFF94_NO_ESTAT, MMFF94S, "
			  "MMFF94S_XOOP, MMFF94S_RTOR, MMFF94S_RTOR_XOOP, MMFF94S_NO_ESTAT, MMFF94S_XOOP_NO_ESTAT, MMFF94S_RTOR_NO_ESTAT, "
			  "MMFF94S_RTOR_XOOP_NO_ESTAT, only effective in systematic sampling mode, default: " +
			  getForceFieldTypeString(settings.getFragmentBuildSettings().getForceFieldType()) + ").", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setBuildForceFieldType, this, _1)));
	addOption("add-frag-lib,g", "Fragment library to be used in addition to the built-in library (only effective in systematic sampling mode).",
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::addFragmentLib, this, _1)));
	addOption("set-frag-lib,G", "Fragment library used as a replacement for the built-in library (only effective in systematic sampling mode).",
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setFragmentLib, this, _1)));
	addOption("canonicalize,z", "Canonicalize input molecules (default: false).", 
			  value<bool>(&canonicalize)->implicit_value(true));
	addOption("energy-sd-entry,Y", "Output conformer energy in the structure data section of SD-files (default: false).", 
			  value<bool>(&energySDEntry)->implicit_value(true));
	addOption("energy-comment,M", "Output conformer energy in the comment field (if supported by output format, default: false).", 
			  value<bool>(&energyComment)->implicit_value(true));
	addOption("conf-idx-suffix,W", "Append conformer index to the title of multiconf. output molecules (default: false).", 
			  value<bool>(&confIndexSuffix)->implicit_value(true));
	addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setInputFormat, this, _1)));
	addOption("output-format,O", "Output file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setOutputFormat, this, _1)));
	addOption("failed-format,F", "Failed molecule output file format (default: auto-detect from file extension).", 
			  value<std::string>()->notifier(boost::bind(&ConfGenImpl::setFailedOutputFormat, this, _1)));

	addOptionLongDescriptions();
}

const char* ConfGenImpl::getProgName() const
{
    return "ConfGen";
}

const char* ConfGenImpl::getProgCopyright() const
{
    return "Thomas Seidel";
}

const char* ConfGenImpl::getProgAboutText() const
{
	return "Performs high-quality conformer generation for a set of input molecules.\n\n"
		"Built-in torsion rules are based on the torsion library jointly developed by the\n"
		"University of Hamburg, Center for Bioinformatics, Hamburg, Germany and\n"
		"F. Hoffmann-La-Roche Ltd., Basel, Switzerland.\n\n"
		"References:\n"
		" -  Schaerfer, C., Schulz-Gasch, T., Ehrlich, H.C., Guba, W., Rarey, M.,\n"
		"    Stahl, M. (2013). Torsion Angle Preferences in Drug-like Chemical Space:\n"
		"    A Comprehensive Guide. Journal of Medicinal Chemistry, 56(6):2016-28.\n"
		" -  Guba, W., Meyder, A., Rarey, M., and Hert, J. (2015). Torsion Library Reloaded:\n"
		"    A New Version of Expert-Derived SMARTS Rules for Assessing Conformations of\n"
		"    Small Molecules. Journal of Chemical Information and Modeling, 56(1):1-5.";
}

void ConfGenImpl::addOptionLongDescriptions()
{
	StringList formats;
	std::string formats_str = "Supported Input Formats:\n";

	CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

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
							 "Specifies one or more input file(s) with molecules for which conformers have to be generated.\n\n" +
							 formats_str);

	formats.clear();
	formats_str = "Supported Output Formats:\n";

	CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

	for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
		formats_str.append(" - ").append(*it).push_back('\n');

	addOptionLongDescription("output-format", 
							 "Allows to explicitly specify the output format by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
							 "(because missing, misleading or not supported)." +
							 "\nNote that only storage formats make sense that allow to store atom 3D-coordinates!");

	addOptionLongDescription("failed-format", 
							 "Allows to explicitly specify the output format by providing one of the supported "
							 "file-extensions (without leading dot!) as argument.\n\n" +
							 formats_str +
							 "\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
							 "(because missing, misleading or not supported).");

	formats_str.pop_back();

	addOptionLongDescription("output", 
							 "Specifies the output file where the generated conformers will be stored.\n\n" +
							 formats_str +
							 "\nNote that only storage formats make sense that allow to store atom 3D-coordinates!");

	addOptionLongDescription("failed", 
							 "Specifies the output file for molecules where conformer generation failed.\n\n" +
							 formats_str);
}

void ConfGenImpl::applyConfGenPreset(const std::string& pres_str)
{
	using namespace CDPL::ConfGen;

	std::string pres = pres_str;
	boost::to_upper(pres);

	if (pres == "SMALL_SET_DIVERSE")
		settings = ConformerGeneratorSettings::SMALL_SET_DIVERSE;
	else if (pres == "MEDIUM_SET_DIVERSE")
		settings = ConformerGeneratorSettings::MEDIUM_SET_DIVERSE;
	else if (pres == "LARGE_SET_DIVERSE")
		settings = ConformerGeneratorSettings::LARGE_SET_DIVERSE;
	else if (pres == "SMALL_SET_DENSE")
		settings = ConformerGeneratorSettings::SMALL_SET_DENSE;
	else if (pres == "MEDIUM_SET_DENSE")
		settings = ConformerGeneratorSettings::MEDIUM_SET_DENSE;
	else if (pres == "LARGE_SET_DENSE")
		settings = ConformerGeneratorSettings::LARGE_SET_DENSE;
	else 
		throwValidationError("conf-gen-preset");

	confGenPreset = pres;
}

void ConfGenImpl::applyFragBuildPreset(const std::string& pres_str)
{
	std::string pres = pres_str;
	boost::to_upper(pres);

	if (pres == "FAST")
		settings.getFragmentBuildSettings() = FragmentConformerGeneratorSettings::FAST;
	else if (pres == "THOROUGH")
		settings.getFragmentBuildSettings() = FragmentConformerGeneratorSettings::THOROUGH;
	else
		throwValidationError("frag-build-preset");

	fragBuildPreset = pres;
}

void ConfGenImpl::setSamplingMode(const std::string& mode_str)
{
	using namespace CDPL::ConfGen;

	std::string smpl_mode = mode_str;
	boost::to_upper(smpl_mode);

	if (smpl_mode == "AUTO")
		settings.setSamplingMode(ConformerSamplingMode::AUTO);
	else if (smpl_mode == "SYSTEMATIC")
		settings.setSamplingMode(ConformerSamplingMode::SYSTEMATIC);
	else if (smpl_mode == "STOCHASTIC")
		settings.setSamplingMode(ConformerSamplingMode::STOCHASTIC);
	else
		throwValidationError("mode");
}

void ConfGenImpl::setTimeout(std::size_t timeout)
{
	settings.setTimeout(timeout * 1000);
}

void ConfGenImpl::setDielectricConst(double de_const)
{
	settings.setDielectricConstant(de_const);
}

void ConfGenImpl::setDistExponent(double exp)
{
	settings.setDistanceExponent(exp);
}

void ConfGenImpl::setMaxNumSampledConfs(std::size_t max_confs)
{
	settings.setMaxNumSampledConformers(max_confs);
}

void ConfGenImpl::setMaxPoolSize(std::size_t max_confs)
{
	settings.setMaxPoolSize(max_confs);
}

void ConfGenImpl::setConvergenceCheckCycleSize(std::size_t size)
{
	if (size == 0)
		throwValidationError("conv-check-cycle-size");

	settings.setConvergenceCheckCycleSize(size);
}

void ConfGenImpl::setMacrocycleRotorBondCountThreshold(std::size_t min_count)
{
	if (min_count == 0)
		throwValidationError("mc-rot-bond-count-thresh");

	settings.setMacrocycleRotorBondCountThreshold(min_count);
}

void ConfGenImpl::setRefTolerance(double tol)
{
	if (tol < 0.0)
		throwValidationError("ref-tol");

	settings.setRefinementTolerance(tol);
}

void ConfGenImpl::setMaxNumRefIterations(std::size_t num_iter)
{
	settings.setMaxNumRefinementIterations(num_iter);
}

void ConfGenImpl::setStrictParameterization(bool strict)
{
	settings.strictForceFieldParameterization(strict);
	settings.getFragmentBuildSettings().strictForceFieldParameterization(strict);
}

void ConfGenImpl::setSystematicSearchForceFieldType(const std::string& type_str)
{
	settings.setForceFieldTypeSystematic(stringToForceFieldType(type_str, "systematic-search-force-field"));
}

void ConfGenImpl::setStochasticSearchForceFieldType(const std::string& type_str)
{
	settings.setForceFieldTypeSystematic(stringToForceFieldType(type_str, "stochastic-search-force-field"));
}

void ConfGenImpl::setBuildForceFieldType(const std::string& type_str)
{
	settings.getFragmentBuildSettings().setForceFieldType(stringToForceFieldType(type_str, "build-force-field"));
}

void ConfGenImpl::setRMSD(double rmsd)
{
	if (rmsd < 0)
		throwValidationError("rmsd");

	settings.setMinRMSD(rmsd);
}

void ConfGenImpl::setEnergyWindow(double ewin)
{
	if (ewin < 0)
		throwValidationError("e-window");

	settings.setEnergyWindow(ewin);
}

void ConfGenImpl::setMaxNumConfs(std::size_t max_confs)
{
	settings.setMaxNumOutputConformers( max_confs);
}

void ConfGenImpl::setNitrogenEnumMode(const std::string& mode_str)
{
	using namespace CDPL::ConfGen;

	std::string uc_mode = mode_str;
	boost::to_upper(uc_mode);

	if (uc_mode == "NONE")
		settings.setNitrogenEnumerationMode(NitrogenEnumerationMode::NONE);
	else if (uc_mode == "ALL")
		settings.setNitrogenEnumerationMode(NitrogenEnumerationMode::ALL);
	else if (uc_mode == "UNSPECIFIED")
		settings.setNitrogenEnumerationMode(NitrogenEnumerationMode::UNSPECIFIED_STEREO);
	else
		throwValidationError("nitrogen-enum-mode");
}

void ConfGenImpl::setEnumRings(bool enumerate)
{
	settings.enumerateRings(enumerate);
}

void ConfGenImpl::setSampleHetAtomHydrogens(bool sample)
{
	settings.sampleHeteroAtomHydrogens(sample);
}

void ConfGenImpl::setSampleAngleTolRanges(bool sample)
{
	settings.sampleAngleToleranceRanges(sample);
}

void ConfGenImpl::setIncludeInput(bool include)
{
	settings.includeInputCoordinates(include);
}

void ConfGenImpl::setGenerateFromScratch(bool from_scratch)
{
	settings.generateCoordinatesFromScratch(from_scratch);
}

void ConfGenImpl::setInputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	inputHandler = Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext);

	if (!inputHandler)
		throwValidationError("input-format");
}

void ConfGenImpl::setOutputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	outputHandler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext);

	if (!outputHandler)
		throwValidationError("output-format");
}

void ConfGenImpl::setFailedOutputFormat(const std::string& file_ext)
{
	using namespace CDPL;

	std::string lc_file_ext = file_ext;
	boost::to_lower(lc_file_ext);

	failedOutputHandler = Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext);

	if (!outputHandler)
		throwValidationError("failed-output-format");
}

void ConfGenImpl::addTorsionLib(const std::string& lib_file)
{
	torsionLibName = lib_file;
	replaceBuiltinTorLib = false;
}

void ConfGenImpl::setTorsionLib(const std::string& lib_file)
{
	torsionLibName = lib_file;
	replaceBuiltinTorLib = true;
}

void ConfGenImpl::addFragmentLib(const std::string& lib_file)
{
	fragmentLibName = lib_file;
	replaceBuiltinFragLib = false;
}

void ConfGenImpl::setFragmentLib(const std::string& lib_file)
{
	fragmentLibName = lib_file;
	replaceBuiltinFragLib = true;
}

int ConfGenImpl::process()
{
	startTime = Clock::now();

	printMessage(INFO, getProgTitleString());
	printMessage(INFO, "");

	checkInputFiles();
	printOptionSummary();

	initInputReader();
	initOutputWriters();

	if (termSignalCaught())
		return EXIT_FAILURE;

	loadTorsionLibrary();

	if (termSignalCaught())
		return EXIT_FAILURE;

	loadFragmentLibrary();

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

void ConfGenImpl::processSingleThreaded()
{
	using namespace CDPL;

	ConformerGenerationWorker worker(this);

	worker();

	printMessage(INFO, "");

	if (haveErrorMessage())
		return;

	if (termSignalCaught())
		return;

	printStatistics(worker.getNumProcMolecules(), worker.getNumFailedMolecules(), worker.getNumGenConformers(),
					std::chrono::duration_cast<std::chrono::duration<std::size_t> >(Clock::now() - startTime).count());
}

void ConfGenImpl::processMultiThreaded()
{
	using namespace CDPL;

	typedef boost::shared_ptr<ConformerGenerationWorker> ConformerGenerationWorkerPtr;
	typedef std::vector<ConformerGenerationWorkerPtr> ConformerGenerationWorkerList;
	typedef std::vector<std::thread> ThreadGroup;
	
	ThreadGroup thread_grp;
	ConformerGenerationWorkerList worker_list;

	try {
		for (std::size_t i = 0; i < numThreads; i++) {
			if (termSignalCaught())
				break;

			ConformerGenerationWorkerPtr worker_ptr(new ConformerGenerationWorker(this));

			thread_grp.emplace_back(boost::bind(&ConformerGenerationWorker::operator(), worker_ptr));
			worker_list.push_back(worker_ptr);
		}

	} catch (const std::exception& e) {
		setErrorMessage(std::string("error while creating worker-threads: ") + e.what());

	} catch (...) {
		setErrorMessage("unspecified error while creating worker-threads");
	}

	try {
		for (auto& thread : thread_grp)
			thread.join();

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
	std::size_t num_failed_mols = 0;
	std::size_t num_gen_confs = 0;

	for (std::size_t i = 0; i < numThreads; i++) {
		const ConformerGenerationWorker& worker = *worker_list[i];

		num_proc_mols += worker.getNumProcMolecules();
		num_failed_mols += worker.getNumFailedMolecules();
		num_gen_confs += worker.getNumGenConformers();
	}

	printStatistics(num_proc_mols, num_failed_mols, num_gen_confs,
					std::chrono::duration_cast<std::chrono::duration<std::size_t> >(Clock::now() - startTime).count());

}

void ConfGenImpl::setErrorMessage(const std::string& msg)
{
	if (numThreads > 0) {
		std::lock_guard<std::mutex> lock(mutex);

		if (errorMessage.empty())
			errorMessage = msg;
		return;
	}

	if (errorMessage.empty())
		errorMessage = msg;
}

bool ConfGenImpl::haveErrorMessage()
{
	if (numThreads > 0) {
		std::lock_guard<std::mutex> lock(mutex);
		return !errorMessage.empty();
	}

	return !errorMessage.empty();
}

void ConfGenImpl::printStatistics(std::size_t num_proc_mols, std::size_t num_failed_mols, std::size_t num_gen_confs, std::size_t proc_time)
{
	printMessage(INFO, "Statistics:");
	printMessage(INFO, " Processed Molecules:  " + boost::lexical_cast<std::string>(num_proc_mols));
	printMessage(INFO, " Molecules Failed:     " + boost::lexical_cast<std::string>(num_failed_mols));

	if ((num_proc_mols - num_failed_mols) > 0) 
		printMessage(INFO, " Generated Conformers: " + boost::lexical_cast<std::string>(num_gen_confs) + 
					 " (" + (boost::format("%.2f") % (double(num_gen_confs) / (num_proc_mols - num_failed_mols))).str() + " Confs./Mol.)");
	else
		printMessage(INFO, " Generated Conformers: " + boost::lexical_cast<std::string>(num_gen_confs));

	if (num_proc_mols > 0) 
		printMessage(INFO, " Processing Time:      " + CmdLineLib::formatTimeDuration(proc_time) + 
					 " (" + (boost::format("%.3f") % (double(proc_time) / num_proc_mols)).str() + " s/Mol.)");
	else
		printMessage(INFO, " Processing Time:      " + CmdLineLib::formatTimeDuration(proc_time));

	printMessage(INFO, "");
}

std::size_t ConfGenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
{
	if (termSignalCaught())
		return 0;

	if (haveErrorMessage())
		return 0;

	if (numThreads > 0) {
		std::lock_guard<std::mutex> lock(readMolMutex);

		return doReadNextMolecule(mol);
	}

	return doReadNextMolecule(mol);
}

std::size_t ConfGenImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
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

			printProgress("Generating Conformers...       ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());

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

void ConfGenImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol, bool failed)
{
	if (numThreads > 0) {
		std::lock_guard<std::mutex> lock(writeMolMutex);

		doWriteMolecule(mol, failed);

	} else
		doWriteMolecule(mol, failed);
}

void ConfGenImpl::doWriteMolecule(const CDPL::Chem::MolecularGraph& mol, bool failed)
{
	if (failed) {
		if (!failedOutputWriter->write(mol))
			throw CDPL::Base::IOError("could not output molecule");

		return;
	}

	if (!outputWriter->write(mol))
		throw CDPL::Base::IOError("could not write generated conformers");
}

void ConfGenImpl::checkInputFiles() const
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

	if (!failedFile.empty() && std::find_if(inputFiles.begin(), inputFiles.end(),
											boost::bind(Util::checkIfSameFile, boost::ref(failedFile),
														_1)) != inputFiles.end())
		throw Base::ValueError("failed output file must not occur in list of input files");

	if (!torsionLibName.empty() && !Util::fileExists(torsionLibName))
		throw Base::IOError("torsion library file '" + torsionLibName + "' does not exist");

	if (!fragmentLibName.empty() && !Util::fileExists(fragmentLibName))
		throw Base::IOError("fragment library file '" + fragmentLibName + "' does not exist");
}

void ConfGenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
	if (numThreads == 0) {
		CmdLineBase::printMessage(level, msg, nl, file_only);
		return;
	}

	std::lock_guard<std::mutex> lock(mutex);

	CmdLineBase::printMessage(level, msg, nl, file_only);
}

void ConfGenImpl::printOptionSummary()
{
	printMessage(VERBOSE, "Option Summary:");
	printMessage(VERBOSE, " Input File(s):                       " + inputFiles[0]);
	
	for (StringList::const_iterator it = ++inputFiles.begin(), end = inputFiles.end(); it != end; ++it)
		printMessage(VERBOSE, std::string(38, ' ') + *it);

	printMessage(VERBOSE, " Output File:                         " + outputFile);
	printMessage(VERBOSE, " Failed Molecule Output File:         " + (failedFile.empty() ? std::string("None") : failedFile));
 	printMessage(VERBOSE, " Conformer Generation Preset:         " + confGenPreset);
 	printMessage(VERBOSE, " Fragment Build Preset:               " + fragBuildPreset);
 	printMessage(VERBOSE, " Conformer Sampling Mode:             " + getSamplingModeString());
	printMessage(VERBOSE, " Max. Num. Output Conformers:         " + boost::lexical_cast<std::string>(settings.getMaxNumOutputConformers()));

	if (settings.getMinRMSD() > 0.0)
		printMessage(VERBOSE, " Min. RMSD:                           " + (boost::format("%.3f") % settings.getMinRMSD()).str());
	else
		printMessage(VERBOSE, " Min. RMSD:                           RMSD Checking disabled");
	
	printMessage(VERBOSE, " Energy Window:                       " + (boost::format("%.3f") % settings.getEnergyWindow()).str());
 	printMessage(VERBOSE, " Nitrogen Enumeration Mode:           " + getNitrogenEnumModeString());
 	printMessage(VERBOSE, " Enumerate Ring Conformers:           " + std::string(settings.enumerateRings() ? "Yes" : "No"));
 	printMessage(VERBOSE, " Sample Hetero Atom Hydrogens:        " + std::string(settings.sampleHeteroAtomHydrogens() ? "Yes" : "No"));
 	printMessage(VERBOSE, " Sample Whole Tor. Angle Tol. Range:  " + std::string(settings.sampleAngleToleranceRanges() ? "Yes" : "No"));
 	printMessage(VERBOSE, " Include Input Structure:             " + std::string(settings.includeInputCoordinates() ? "Yes" : "No"));
 	printMessage(VERBOSE, " Generate Coordinates From Scratch:   " + std::string(settings.generateCoordinatesFromScratch() ? "Yes" : "No"));
	printMessage(VERBOSE, " Systematic Search Force Field Type:  " + getForceFieldTypeString(settings.getForceFieldTypeSystematic()));
	printMessage(VERBOSE, " Stochastic Search Force Field Type:  " + getForceFieldTypeString(settings.getForceFieldTypeStochastic()));
	printMessage(VERBOSE, " Build Force Field Type:              " + getForceFieldTypeString(settings.getFragmentBuildSettings().getForceFieldType()));
	printMessage(VERBOSE, " Strict Force Field Parameterization: " + std::string(settings.strictForceFieldParameterization() ? "Yes" : "No"));
	printMessage(VERBOSE, " Dielectric Constant:                 " + (boost::format("%.3f") % settings.getDielectricConstant()).str());
	printMessage(VERBOSE, " Distance Exponent:                   " + (boost::format("%.3f") % settings.getDistanceExponent()).str());
	printMessage(VERBOSE, " Max. Pool Size:                      " + boost::lexical_cast<std::string>(settings.getMaxPoolSize()));
	printMessage(VERBOSE, " Max. Num. Sampled Conformers:        " + boost::lexical_cast<std::string>(settings.getMaxNumSampledConformers()));
	printMessage(VERBOSE, " Convergence Check Cycle Size:        " + boost::lexical_cast<std::string>(settings.getConvergenceCheckCycleSize()));
	printMessage(VERBOSE, " Macrocycle Rot. Bond Count Theshold: " + boost::lexical_cast<std::string>(settings.getMacrocycleRotorBondCountThreshold()));
	printMessage(VERBOSE, " Refinement Energy Tolerance:         " + (boost::format("%.4f") % settings.getRefinementTolerance()).str());
	printMessage(VERBOSE, " Max. Num. Refinement Iterations:     " + boost::lexical_cast<std::string>(settings.getMaxNumRefinementIterations()));
	printMessage(VERBOSE, " Timeout:                             " + boost::lexical_cast<std::string>(settings.getTimeout() / 1000) + "s");
	printMessage(VERBOSE, " Max. Num. Allowed Rotatable Bonds:   " + (maxNumRotorBonds < 0 ? std::string("No Limit") : boost::lexical_cast<std::string>(maxNumRotorBonds)));
	printMessage(VERBOSE, " Multithreading:                      " + std::string(numThreads > 0 ? "Yes" : "No"));

	if (numThreads > 0)
		printMessage(VERBOSE, " Number of Threads:                   " + boost::lexical_cast<std::string>(numThreads));

	printMessage(VERBOSE, " Torsion Library:                     " + (torsionLibName.empty() ? std::string("Built-in") : replaceBuiltinTorLib ? torsionLibName : torsionLibName + " + Built-in"));
	printMessage(VERBOSE, " Fragment Library:                    " + (fragmentLibName.empty() ? std::string("Built-in") : replaceBuiltinFragLib ? fragmentLibName : fragmentLibName + " + Built-in"));
	printMessage(VERBOSE, " Input File Format:                   " + (inputHandler ? inputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Output File Format:                  " + (outputHandler ? outputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Failed Molecule File Format:         " + (failedOutputHandler ? failedOutputHandler->getDataFormat().getName() : std::string("Auto-detect")));
	printMessage(VERBOSE, " Canonicalize Input Molecules:        " + std::string(canonicalize ? "Yes" : "No"));
	printMessage(VERBOSE, " Output Conf. Energy SD-Entry:        " + std::string(energySDEntry ? "Yes" : "No"));
	printMessage(VERBOSE, " Output Conf. Energy Comment:         " + std::string(energyComment ? "Yes" : "No"));
	printMessage(VERBOSE, " Append Conf. Index to Mol. Title:    " + std::string(confIndexSuffix ? "Yes" : "No"));
	printMessage(VERBOSE, "");
}

void ConfGenImpl::loadTorsionLibrary()
{
	using namespace CDPL;
	using namespace CDPL::ConfGen;

	if (torsionLibName.empty())
		return;

	std::ifstream is(torsionLibName);

	if (!is) 
		throw Base::IOError("opening torsion library '" + torsionLibName + "' failed");

	printMessage(INFO, "Loading Torsion Library '" + torsionLibName + "'...");

	torsionLib.reset(new TorsionLibrary());
	torsionLib->load(is);

	if (termSignalCaught())
		return;

	if (!is)
		throw Base::IOError("loading torsion library '" + torsionLibName + "' failed");

	printMessage(INFO, " - Loaded " + boost::lexical_cast<std::string>(torsionLib->getNumRules(true)) + " torsion rules in " +
				 boost::lexical_cast<std::string>(torsionLib->getNumCategories(true)) + " categories");
	printMessage(INFO, "");
}

void ConfGenImpl::loadFragmentLibrary()
{
	using namespace CDPL;
	using namespace CDPL::ConfGen;

	if (fragmentLibName.empty())
		return;

	std::ifstream is(fragmentLibName);

	if (!is) 
		throw Base::IOError("opening fragment library '" + fragmentLibName + "' failed");

	printMessage(INFO, "Loading Fragment Library '" + fragmentLibName + "'...");

	fragmentLib.reset(new FragmentLibrary());
	fragmentLib->load(is);

	if (termSignalCaught())
		return;

	if (!is)
		throw Base::IOError("loading fragment library '" + fragmentLibName + "' failed");

	printMessage(INFO, " - Loaded " + boost::lexical_cast<std::string>(fragmentLib->getNumEntries()) + " fragments");
	printMessage(INFO, "");
}

void ConfGenImpl::initInputReader()
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

	if (termSignalCaught())
		return;

	printMessage(INFO, " - Found " + boost::lexical_cast<std::string>(inputReader.getNumRecords()) + " input molecule(s)");
	printMessage(INFO, "");
}

void ConfGenImpl::initOutputWriters()
{
	using namespace CDPL;

	OutputHandlerPtr output_handler = getOutputHandler(outputFile);

	if (!output_handler)
		throw Base::IOError("no output handler found for file '" + outputFile + '\'');

	outputWriter = output_handler->createWriter(outputFile);

	setMultiConfExportParameter(*outputWriter, true);
	setMDLOutputConfEnergyAsSDEntryParameter(*outputWriter, energySDEntry);
	setOutputConfEnergyAsCommentParameter(*outputWriter, energyComment);
	setSMILESRecordFormatParameter(*outputWriter, "SN");

	if (confIndexSuffix)
		setConfIndexNameSuffixPatternParameter(*outputWriter," %I%");

	if (!failedFile.empty()) {
		output_handler = getFailedOutputHandler(failedFile);

		if (!output_handler)
			throw Base::IOError("no output handler found for file '" + outputFile + '\'');

		failedOutputWriter = output_handler->createWriter(failedFile);

		setMultiConfExportParameter(*failedOutputWriter, false);
		setSMILESRecordFormatParameter(*failedOutputWriter, "SN");
	}
}

ConfGenImpl::InputHandlerPtr ConfGenImpl::getInputHandler(const std::string& file_path) const
{
	if (inputHandler)
		return inputHandler;

	return CmdLineLib::getInputHandler<CDPL::Chem::Molecule>(file_path);
}

ConfGenImpl::OutputHandlerPtr ConfGenImpl::getOutputHandler(const std::string& file_path) const
{
	if (outputHandler)
		return outputHandler;

	return CmdLineLib::getOutputHandler<CDPL::Chem::MolecularGraph>(file_path);
}

ConfGenImpl::OutputHandlerPtr ConfGenImpl::getFailedOutputHandler(const std::string& file_path) const
{
	if (failedOutputHandler)
		return failedOutputHandler;

	return CmdLineLib::getOutputHandler<CDPL::Chem::MolecularGraph>(file_path);
}

std::string ConfGenImpl::getSamplingModeString() const
{
	using namespace CDPL::ConfGen;

	unsigned int mode = settings.getSamplingMode();

	if (mode == ConformerSamplingMode::AUTO)
		return "AUTO";
	
	if (mode == ConformerSamplingMode::SYSTEMATIC)
		return "SYSTEMATIC";

	if (mode == ConformerSamplingMode::STOCHASTIC)
		return "STOCHASTIC";
	
	return "UNKNOWN";
}

std::string ConfGenImpl::getNitrogenEnumModeString() const
{
	using namespace CDPL::ConfGen;

	unsigned int mode = settings.getNitrogenEnumerationMode();

	if (mode == NitrogenEnumerationMode::NONE)
		return "NONE";
	
	if (mode == NitrogenEnumerationMode::ALL)
		return "ALL";

	if (mode == NitrogenEnumerationMode::UNSPECIFIED_STEREO)
		return "UNSPECIFIED";
	
	return "UNKNOWN";
}

std::string ConfGenImpl::createMoleculeIdentifier(std::size_t rec_idx, const CDPL::Chem::Molecule& mol)
{
	if (!getName(mol).empty())
		return ('\'' + getName(mol) + "' (" + createMoleculeIdentifier(rec_idx) + ')');

	return createMoleculeIdentifier(rec_idx);
}

std::string ConfGenImpl::createMoleculeIdentifier(std::size_t rec_idx)
{
	return (boost::lexical_cast<std::string>(rec_idx) + '/' + boost::lexical_cast<std::string>(inputReader.getNumRecords()));
}
