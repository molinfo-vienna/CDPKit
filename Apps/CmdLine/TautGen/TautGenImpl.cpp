/* 
 * TautGenImpl.cpp
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
#include <thread>
#include <cstdint>
#include <chrono>
#include <functional>
#include <unordered_set>

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
#include "CDPL/Chem/MoleculeReader.hpp"
#include "CDPL/Util/FileFunctions.hpp"
#include "CDPL/Util/ObjectStack.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "CmdLine/Lib/HelperFunctions.hpp"

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

        parent->printProgress("Scanning Input File(s)... ", offset + scale * progress);
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
        molCache(100), parent(parent), numProcMols(0), numGenTauts(0) {

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
        hashCalc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(bond_flags));
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
        using namespace std::placeholders;
        
        switch (parent->mode) {

            case ALL_UNIQUE:
                tautGen.setMode(TautomerGenerator::TOPOLOGICALLY_UNIQUE);
                break;

            case STANDARDIZE:
                tautGen.removeResonanceDuplicates(false);
                
            default:
                tautGen.setMode(TautomerGenerator::GEOMETRICALLY_UNIQUE);
        }

        tautGen.setCallbackFunction(std::bind(&TautGenerationWorker::tautomerGenerated, this, _1));
        tautGen.regardIsotopes(parent->regardIsotopes);
        tautGen.regardStereochemistry(parent->regardStereo);
        tautGen.setCustomSetupFunction(std::bind(&setRingFlags, _1, false));
   
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
                parent->neutralizer.standardize(molecule, CDPL::Chem::ProtonationStateStandardizer::MIN_CHARGED_ATOM_COUNT);

            if (parent->regardStereo) {
                calcImplicitHydrogenCounts(molecule, false);
        
                initMolecule(molecule);

                perceiveAtomStereoCenters(molecule, false, false);
                perceiveBondStereoCenters(molecule, false, false);
                calcAtomStereoDescriptors(molecule, false);
                calcBondStereoDescriptors(molecule, false);
            }

            numGenMolTauts = 0;
            numWrittenMolTauts = 0;
            
            if (parent->mode == STANDARDIZE || parent->mode == BEST_SCORING || parent->mode == BEST_SCORING_UNIQUE) {
                bestScore = -1.0;
                
                bestTautomers.clear();
                hashCodes.clear();
                molCache.putAll();
            }

            tautGen.generate(molecule);

            if ((parent->mode == STANDARDIZE || parent->mode == BEST_SCORING || parent->mode == BEST_SCORING_UNIQUE) && !bestTautomers.empty())
                for (std::size_t i = 0, num_tauts = bestTautomers.size(); i < num_tauts; i++)
                    outputMolecule(*bestTautomers[i], bestScore, i + 1);

            parent->printMessage(VERBOSE, "Molecule " + parent->createMoleculeIdentifier(rec_idx, molecule) + ": " +
                                 std::to_string(numGenMolTauts) + (numGenMolTauts == 1 ? " tautomer" : " tautomers") +
                                 " generated, " + std::to_string(numWrittenMolTauts) + " written");
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

        initMolecule(taut);

        double score = tautScoreCalc(taut);

        if (parent->mode == ALL || parent->mode == ALL_UNIQUE) {
            outputMolecule(taut, score, numGenMolTauts);

            return (parent->maxNumTautomers == 0 || numGenMolTauts < parent->maxNumTautomers);
        }
        
        if (score >= bestScore) {
            if (parent->mode == STANDARDIZE) {
                if (parent->regardStereo) {
                    calcAtomCIPConfigurations(taut, false);
                    calcBondCIPConfigurations(taut, false);
                }

                std::uint64_t hash = hashCalc.calculate(taut);
                
                if (score > bestScore || hash > hashCode) {
                    if (bestTautomers.empty())
                        bestTautomers.push_back(molCache.get());

                    *bestTautomers.front() = taut;
                    hashCode = hash;
                }
                
            } else if (score > bestScore) {
                if (parent->mode == BEST_SCORING_UNIQUE) {
                    if (parent->regardStereo) {
                        calcAtomCIPConfigurations(taut, false);
                        calcBondCIPConfigurations(taut, false);
                    }

                    hashCodes.clear();
                    hashCodes.insert(hashCalc.calculate(taut));
                }

                bestTautomers.clear();
                molCache.putAll();

                bestTautomers.push_back(&(*molCache.get() = taut));

            } else {
                if (parent->mode == BEST_SCORING_UNIQUE) {
                    if (parent->regardStereo) {
                        calcAtomCIPConfigurations(taut, false);
                        calcBondCIPConfigurations(taut, false);
                    }

                    std::uint64_t hash = hashCalc.calculate(taut);

                    if (hashCodes.insert(hash).second)
                        bestTautomers.push_back(&(*molCache.get() = taut));

                } else
                    bestTautomers.push_back(&(*molCache.get() = taut));
            }
            
            bestScore = score;
        }

        return true;
    }

    void initMolecule(CDPL::Chem::MolecularGraph& molgraph) const {
        using namespace CDPL;
        using namespace Chem;

        setRingFlags(molgraph, false);
        perceiveHybridizationStates(molgraph, false);
        perceiveSSSR(molgraph, false);
        setAromaticityFlags(molgraph, false);
    }

    void outputMolecule(CDPL::Chem::MolecularGraph& molgraph, double score, std::size_t idx) {
        using namespace CDPL;
        using namespace Chem;

        StringDataBlock::SharedPointer sd(hasStructureData(molecule) ?
                                          new StringDataBlock(*getStructureData(molecule)) :
                                          new StringDataBlock());

        sd->addEntry("<Tautomer Score>", std::to_string(score));

        setStructureData(molgraph, sd);
        perceiveComponents(molgraph, false);
        setAtomSymbolsFromTypes(molgraph, false);

        if (parent->titleSuffix)
            setName(molgraph, getName(molecule) + '_' + std::to_string(idx));
        else
            setName(molgraph, getName(molecule));

        parent->writeMolecule(molgraph);

        numWrittenMolTauts++;
    }

    typedef CDPL::Util::ObjectStack<CDPL::Chem::BasicMolecule> MoleculeCache;
    typedef std::vector<CDPL::Chem::Molecule*> MoleculeList;
    typedef std::unordered_set<std::uint64_t> HashCodeSet;
    
    MoleculeCache                  molCache;
    TautGenImpl*                   parent;
    CDPL::Chem::TautomerGenerator  tautGen;
    CDPL::Chem::TautomerScore      tautScoreCalc;
    CDPL::Chem::HashCodeCalculator hashCalc;
    CDPL::Chem::BasicMolecule      molecule;
    MoleculeList                   bestTautomers;
    double                         bestScore;
    std::uint64_t                  hashCode;
    HashCodeSet                    hashCodes;
    std::size_t                    numProcMols;
    std::size_t                    numGenTauts;
    std::size_t                    numGenMolTauts;
    std::size_t                    numWrittenMolTauts;
};


TautGenImpl::TautGenImpl(): 
    regardStereo(true), regardIsotopes(true), neutralize(false), ketoEnol(true), 
    imineEnamine(true), nitrosoOxime(true), amideImidicAcid(true),
    lactamLactim(true), keteneYnol(true), nitroAci(true), phosphinicAcid(true),
    sulfenicAcid(true), genericH13Shift(true), genericH15Shift(false), titleSuffix(false),
    numThreads(0), maxNumTautomers(0), mode(Mode::BEST_SCORING_UNIQUE), 
    inputFormat(), outputFormat(), outputWriter(), numOutTautomers(0)
{
    using namespace std::placeholders;
    
    addOption("input,i", "Input file(s).", 
              value<StringList>(&inputFiles)->multitoken()->required());
    addOption("output,o", "Tautomers output file.", 
              value<std::string>(&outputFile)->required());
    addOption("mode,m", "Tautomer generation mode (STANDARDIZE, BEST_SCORING, BEST_SCORING_UNIQUE, ALL_UNIQUE, "
              "ALL default: BEST_SCORING_UNIQUE).", 
              value<std::string>()->notifier(std::bind(&TautGenImpl::setMode, this, _1)));
    addOption("num-threads,t", "Number of parallel execution threads (default: no multithreading, implicit value: " +
              std::to_string(std::thread::hardware_concurrency()) + 
              " threads, must be >= 0, 0 disables multithreading).", 
              value<std::size_t>(&numThreads)->implicit_value(std::thread::hardware_concurrency()));
    addOption("input-format,I", "Input file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&TautGenImpl::setInputFormat, this, _1)));
    addOption("output-format,O", "Output file format (default: auto-detect from file extension).", 
              value<std::string>()->notifier(std::bind(&TautGenImpl::setOutputFormat, this, _1)));
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
    addOption("generic-h15-shift", "Enable generic hydrogen 1 <-> 5 shift tautomerization (default: false).", 
              value<bool>(&genericH15Shift)->implicit_value(true));
    addOption("title-suffix,S", "Append tautomer number to the title of the output molecules (default: false).", 
              value<bool>(&titleSuffix)->implicit_value(true));
    addOptionLongDescriptions();
}

const char* TautGenImpl::getProgName() const
{
    return "TautGen";
}

const char* TautGenImpl::getProgAboutText() const
{
    return "Performs tautomer generation for a set of input molecules.";
}

void TautGenImpl::addOptionLongDescriptions()
{
    StringList formats;
    std::string formats_str = "Supported Input Formats:";

    CmdLineLib::getSupportedInputFormats<CDPL::Chem::Molecule>(std::back_inserter(formats));

    for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
        formats_str.append("\n - ").append(*it);

    addOptionLongDescription("input-format", 
                             "Allows to explicitly specify the format of the input file(s) by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file(s) "
                             "(because missing, misleading or not supported).");

    formats_str.pop_back();

    addOptionLongDescription("input", 
                             "Specifies one or more input file(s) with molecules for which tautomers have to be generated.\n\n" +
                             formats_str);

    formats.clear();
    formats_str = "Supported Output Formats:";

    CmdLineLib::getSupportedOutputFormats<CDPL::Chem::MolecularGraph>(std::back_inserter(formats));

    for (StringList::const_iterator it = formats.begin(), end = formats.end(); it != end; ++it)
        formats_str.append("\n - ").append(*it);

    addOptionLongDescription("output-format", 
                             "Allows to explicitly specify the output format by providing one of the supported "
                             "file-extensions (without leading dot!) as argument.\n\n" +
                             formats_str +
                             "\n\nThis option is useful when the format cannot be auto-detected from the actual extension of the file "
                             "(because missing, misleading or not supported).");

    formats_str.pop_back();

    addOptionLongDescription("output", 
                             "Specifies the output file where the generated tautomers will be stored.\n\n" +
                             formats_str);
}

void TautGenImpl::setMode(const std::string& mode_str)
{
    using namespace CDPL::Pharm;
    using namespace CDPL;
    
    if (Internal::isEqualCI(mode_str, "STANDARDIZE"))
        mode = Mode::STANDARDIZE;
    else if (Internal::isEqualCI(mode_str, "BEST_SCORING"))
        mode = Mode::BEST_SCORING;
    else if (Internal::isEqualCI(mode_str, "BEST_SCORING_UNIQUE"))
        mode = Mode::BEST_SCORING_UNIQUE;
    else if (Internal::isEqualCI(mode_str, "ALL_UNIQUE"))
        mode = Mode::ALL_UNIQUE;
    else if (Internal::isEqualCI(mode_str, "ALL"))
        mode = Mode::ALL_UNIQUE;
    else
        throwValidationError("mode");
}

void TautGenImpl::setInputFormat(const std::string& file_ext)
{
    using namespace CDPL;
    
    if (Base::DataIOManager<Chem::Molecule>::getInputHandlerByFileExtension(file_ext))
        throwValidationError("input-format");

    inputFormat = file_ext;
}

void TautGenImpl::setOutputFormat(const std::string& file_ext)
{
    using namespace CDPL;
    
    if (!Base::DataIOManager<Chem::MolecularGraph>::getOutputHandlerByFileExtension(file_ext))
        throwValidationError("output-format");

    outputFormat = file_ext;
}

int TautGenImpl::process()
{
    timer.reset();

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
        printMessage(INFO, "Generating Tautomers...", true, true);
    } else
        printMessage(INFO, "Generating Tautomers...");

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

    printStatistics(worker.getNumProcMolecules(), worker.getNumGenTautomers());
}

void TautGenImpl::processMultiThreaded()
{
    using namespace CDPL;

    typedef std::shared_ptr<TautGenerationWorker> TautGenerationWorkerPtr;
    typedef std::vector<TautGenerationWorkerPtr> TautGenerationWorkerList;
    typedef std::vector<std::thread> ThreadGroup;
    
    ThreadGroup thread_grp;
    TautGenerationWorkerList worker_list;

    try {
        for (std::size_t i = 0; i < numThreads; i++) {
            if (termSignalCaught())
                break;

            TautGenerationWorkerPtr worker_ptr(new TautGenerationWorker(this));

            thread_grp.emplace_back(std::bind(&TautGenerationWorker::operator(), worker_ptr));
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
    std::size_t num_gen_tauts = 0;

    for (std::size_t i = 0; i < numThreads; i++) {
        const TautGenerationWorker& worker = *worker_list[i];

        num_proc_mols += worker.getNumProcMolecules();
        num_gen_tauts += worker.getNumGenTautomers();
    }

    printStatistics(num_proc_mols, num_gen_tauts);
}

void TautGenImpl::setErrorMessage(const std::string& msg)
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

bool TautGenImpl::haveErrorMessage()
{
    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(mutex);
        return !errorMessage.empty();
    }

    return !errorMessage.empty();
}

void TautGenImpl::printStatistics(std::size_t num_proc_mols, std::size_t num_gen_tauts)
{
    std::size_t proc_time = std::chrono::duration_cast<std::chrono::seconds>(timer.elapsed()).count();
    
    printMessage(INFO, "Statistics:");
    printMessage(INFO, " Processed Molecules: " + std::to_string(num_proc_mols));
    printMessage(INFO, " Generated Tautomers: " + std::to_string(num_gen_tauts));
    printMessage(INFO, " Output Tautomers:    " + std::to_string(numOutTautomers));
    printMessage(INFO, " Processing Time:     " + CmdLineLib::formatTimeDuration(proc_time));
    printMessage(INFO, "");
}

std::size_t TautGenImpl::readNextMolecule(CDPL::Chem::Molecule& mol)
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

std::size_t TautGenImpl::doReadNextMolecule(CDPL::Chem::Molecule& mol)
{
    while (true) {
        try {
            printProgress("Generating Tautomers...   ", double(inputReader.getRecordIndex()) / inputReader.getNumRecords());

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

void TautGenImpl::writeMolecule(const CDPL::Chem::MolecularGraph& mol)
{
    if (numThreads > 0) {
        std::lock_guard<std::mutex> lock(writeMolMutex);

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
    using namespace std::placeholders;
    
    StringList::const_iterator it = std::find_if(inputFiles.begin(), inputFiles.end(),
                                                 std::bind(std::logical_not<bool>(), 
                                                           std::bind(Util::fileExists, _1)));
    if (it != inputFiles.end())
        throw Base::IOError("file '" + *it + "' does not exist");

    if (std::find_if(inputFiles.begin(), inputFiles.end(),
                     std::bind(Util::checkIfSameFile, boost::ref(outputFile),
                               _1)) != inputFiles.end())
        throw Base::ValueError("output file must not occur in list of input files");
}

void TautGenImpl::printMessage(VerbosityLevel level, const std::string& msg, bool nl, bool file_only)
{
    if (numThreads == 0) {
        CmdLineBase::printMessage(level, msg, nl, file_only);
        return;
    }

    std::lock_guard<std::mutex> lock(mutex);

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
        printMessage(VERBOSE, " Number of Threads:                 " + std::to_string(numThreads));

    printMessage(VERBOSE, " Input File Format:                 " + (!inputFormat.empty() ? inputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Output File Format:                " + (!outputFormat.empty() ? outputFormat : std::string("Auto-detect")));
    printMessage(VERBOSE, " Stereochemistry Aware:             " + std::string(regardStereo ? "Yes" : "No"));
    printMessage(VERBOSE, " Isotope Aware:                     " + std::string(regardIsotopes ? "Yes" : "No"));
    printMessage(VERBOSE, " Neutralize Charges:                " + std::string(neutralize ? "Yes" : "No"));
    printMessage(VERBOSE, " Max. Num. Tautomers:               " + std::to_string(maxNumTautomers));
    printMessage(VERBOSE, " Append Taut. No. to Mol. Title:    " + std::string(titleSuffix ? "Yes" : "No"));
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
        Chem::MoleculeReader::SharedPointer reader_ptr;
        
        try {
            reader_ptr.reset(inputFormat.empty() ? new Chem::MoleculeReader(file_path) :
                             new Chem::MoleculeReader(file_path, inputFormat));

        } catch (const Base::IOError& e) {
            throw Base::IOError("no input handler found for file '" + file_path + '\'');
        }
        
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

    printMessage(INFO, " - Found " + std::to_string(inputReader.getNumRecords()) + " input molecule(s)");
    printMessage(INFO, "");
}

void TautGenImpl::initOutputWriter()
{
    using namespace CDPL;

    try {
        outputWriter.reset(outputFormat.empty() ? new Chem::MolecularGraphWriter(outputFile) :
                           new Chem::MolecularGraphWriter(outputFile, outputFormat));

    } catch (const Base::IOError& e) {
        throw Base::IOError("no output handler found for file '" + outputFile + '\'');
    }

    setSMILESRecordFormatParameter(*outputWriter, "SN");
    setSMILESOutputCanonicalFormParameter(*outputWriter, true);
    setMultiConfExportParameter(*outputWriter, false);
}

std::string TautGenImpl::getModeString() const
{
    using namespace CDPL;

    if (mode == STANDARDIZE)
        return "STANDADIZE";

    if (mode == BEST_SCORING)
        return "BEST_SCORING";

    if (mode == BEST_SCORING_UNIQUE)
        return "BEST_SCORING_UNIQUE";

    if (mode == ALL_UNIQUE)
        return "ALL_UNIQUE";

    if (mode == ALL)
        return "ALL";
    
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
    return (std::to_string(rec_idx) + '/' + std::to_string(inputReader.getNumRecords()));
}
