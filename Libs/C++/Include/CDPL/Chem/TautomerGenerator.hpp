/* 
 * TautomerGenerator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::TautomerGenerator.
 */

#ifndef CDPL_CHEM_TAUTOMERGENERATOR_HPP
#define CDPL_CHEM_TAUTOMERGENERATOR_HPP

#include <vector>
#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <array>
#include <memory>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/TautomerizationRule.hpp"
#include "CDPL/Chem/HashCodeCalculator.hpp"
#include "CDPL/Chem/CIPConfigurationLabeler.hpp"
#include "CDPL/Chem/AromaticSubstructure.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief TautomerGenerator.
         */
        class CDPL_CHEM_API TautomerGenerator
        {

          public:
            enum Mode
            {

                TOPOLOGICALLY_UNIQUE,
                GEOMETRICALLY_UNIQUE,
                EXHAUSTIVE
            };

            typedef std::shared_ptr<TautomerGenerator> SharedPointer;

            typedef std::function<bool(MolecularGraph&)> CallbackFunction;
            typedef std::function<void(MolecularGraph&)> CustomSetupFunction;

            /**
             * \brief Constructs the \c %TautomerGenerator instance.
             */
            TautomerGenerator();

            TautomerGenerator(const TautomerGenerator& gen);

            virtual ~TautomerGenerator() {}

            TautomerGenerator& operator=(const TautomerGenerator& gen);

            void addTautomerizationRule(const TautomerizationRule::SharedPointer& rule);

            const TautomerizationRule::SharedPointer& getTautomerizationRule(std::size_t idx) const;

            void removeTautomerizationRule(std::size_t idx);

            std::size_t getNumTautomerizationRules() const;

            void setCallbackFunction(const CallbackFunction& func);

            const CallbackFunction& getCallbackFunction() const;

            void setMode(Mode mode);

            Mode getMode() const;

            void regardStereochemistry(bool regard);

            bool stereochemistryRegarded() const;

            void regardIsotopes(bool regard);

            bool isotopesRegarded() const;

            /**
             * \since 1.3
             */
            void clearCoordinates2D(bool clear);

            /**
             * \since 1.3
             */
            bool coordinates2DCleared() const;

            /**
             * \since 1.3
             */
            void clearCoordinates3D(bool clear);

            /**
             * \since 1.3
             */
            bool coordinates3DCleared() const;
            
            /**
             * \since 1.1
             */
            void removeResonanceDuplicates(bool remove);

            /**
             * \since 1.1
             */
            bool resonanceDuplicatesRemoved() const;
            
            void setCustomSetupFunction(const CustomSetupFunction& func);

            /**
             * \brief Generates all unique tautomers of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to generate the tautomers.
             */
            void generate(const MolecularGraph& molgraph);

          private:
            typedef Util::ObjectPool<BasicMolecule>    MoleculeCache;
            typedef MoleculeCache::SharedObjectPointer MoleculePtr;

            bool init(const MolecularGraph& molgraph);
            void initHashCalculator();

            MoleculePtr copyInputMolGraph(const MolecularGraph& molgraph);

            void extractStereoCenters(const MolecularGraph& molgraph);
            void extractAtomStereoCenters(const MolecularGraph& molgraph);
            void extractBondStereoCenters(const MolecularGraph& molgraph);

            bool addNewTautomer(const MoleculePtr& mol_ptr);
            bool outputTautomer(const MoleculePtr& mol_ptr);

            std::uint64_t calcConTabHashCode(const MolecularGraph& molgraph, bool arom_bonds);

            void generateSSSR(MolecularGraph& molgraph);
            void setAromaticityFlags(MolecularGraph& molgraph);
            void calcCIPConfigurations(MolecularGraph& molgraph);
            
            typedef std::array<std::size_t, 3>                      BondDescriptor;
            typedef std::vector<MoleculePtr>                        MoleculeList;
            typedef std::vector<TautomerizationRule::SharedPointer> TautRuleList;
            typedef std::vector<BondDescriptor>                     BondDescrArray;
            typedef std::vector<std::size_t>                        SizeTArray;
            typedef std::unordered_set<std::uint64_t>               HashCodeSet;
            typedef std::array<std::size_t, 6>                      StereoCenter;
            typedef std::vector<StereoCenter>                       StereoCenterList;

            MoleculeCache              molCache;
            CallbackFunction           callbackFunc;
            Mode                       mode;
            bool                       regStereo;
            bool                       regIsotopes;
            bool                       remResDuplicates;
            bool                       clear2DCoords;
            bool                       clear3DCoords;
            CustomSetupFunction        customSetupFunc;
            TautRuleList               tautRules;
            MoleculeList               currGeneration;
            MoleculeList               nextGeneration;
            StereoCenterList           atomStereoCenters;
            StereoCenterList           bondStereoCenters;
            HashCodeSet                intermTautHashCodes;
            HashCodeSet                outputTautHashCodes;
            HashCodeCalculator         hashCalculator;
            AromaticSubstructure       aromSubstruct;
            CIPConfigurationLabeler    cipLabeler;
            BondDescrArray             tautomerBonds;
            SizeTArray                 shaInput;
            const MolecularGraph*      molGraph;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_TAUTOMERGENERATOR_HPP
