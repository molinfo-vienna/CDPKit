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
 * \brief Definition of class CDPL::Chem::TautomerGenerator.
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
         * \brief Enumerates the tautomers of a molecular graph by iteratively applying a configurable set of
         *        Chem::TautomerizationRule instances and reporting each accepted tautomer to a user-supplied callback.
         *
         * After registering tautomerization rules (via addTautomerizationRule()) and a callback (via
         * setCallbackFunction()), each call to generate() seeds the enumeration with the input molecular graph,
         * applies every registered rule to every intermediate tautomer to derive the next generation, and
         * reports each newly-generated tautomer to the callback. The Mode setting controls how aggressively
         * duplicates are filtered.
         */
        class CDPL_CHEM_API TautomerGenerator
        {

          public:
            /**
             * \brief Selects the duplicate-filtering strategy applied during tautomer enumeration.
             */
            enum Mode
            {

                /** \brief Two tautomers are considered equal if they share the same constitutional (topological) connection table. */
                TOPOLOGICALLY_UNIQUE,
                /** \brief Two tautomers are considered equal if they share the same connection table AND the same stereo-configuration. */
                GEOMETRICALLY_UNIQUE,
                /** \brief Every accepted tautomer is reported, even if topologically/geometrically equivalent to an already-reported one. */
                EXHAUSTIVE
            };

            /** \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %TautomerGenerator instances. */
            typedef std::shared_ptr<TautomerGenerator> SharedPointer;

            /** \brief Type of the callback invoked for every accepted tautomer (returning \c false aborts the enumeration). */
            typedef std::function<bool(MolecularGraph&)> CallbackFunction;
            /** \brief Type of the optional setup function invoked on the input molecular graph before enumeration starts. */
            typedef std::function<void(MolecularGraph&)> CustomSetupFunction;

            /**
             * \brief Constructs the \c %TautomerGenerator instance.
             */
            TautomerGenerator();

            /**
             * \brief Constructs a copy of the \c %TautomerGenerator instance \a gen.
             * \param gen The \c %TautomerGenerator to copy.
             */
            TautomerGenerator(const TautomerGenerator& gen);

            /**
             * \brief Virtual destructor.
             */
            virtual ~TautomerGenerator() {}

            /**
             * \brief Replaces the state of this generator by a copy of the state of \a gen.
             * \param gen The source \c %TautomerGenerator.
             * \return A reference to itself.
             */
            TautomerGenerator& operator=(const TautomerGenerator& gen);

            /**
             * \brief Registers a new tautomerization rule.
             * \param rule The tautomerization rule to register.
             */
            void addTautomerizationRule(const TautomerizationRule::SharedPointer& rule);

            /**
             * \brief Returns the registered tautomerization rule at index \a idx.
             * \param idx The zero-based rule index.
             * \return A \c const reference to the rule smart pointer.
             * \throw Base::IndexError if the number of rules is zero or \a idx is not in the range [0, getNumTautomerizationRules() - 1].
             */
            const TautomerizationRule::SharedPointer& getTautomerizationRule(std::size_t idx) const;

            /**
             * \brief Removes the registered tautomerization rule at index \a idx.
             * \param idx The zero-based rule index.
             * \throw Base::IndexError if the number of rules is zero or \a idx is not in the range [0, getNumTautomerizationRules() - 1].
             */
            void removeTautomerizationRule(std::size_t idx);

            /**
             * \brief Returns the number of registered tautomerization rules.
             * \return The rule count.
             */
            std::size_t getNumTautomerizationRules() const;

            /**
             * \brief Sets the callback invoked for every accepted tautomer.
             *
             * The callback receives the tautomer molecular graph as its argument and returns a boolean:
             * returning \c false aborts the enumeration.
             *
             * \param func The new callback function.
             */
            void setCallbackFunction(const CallbackFunction& func);

            /**
             * \brief Returns the currently configured callback.
             * \return A \c const reference to the callback function.
             */
            const CallbackFunction& getCallbackFunction() const;

            /**
             * \brief Sets the duplicate-filtering mode.
             * \param mode The new Mode value.
             */
            void setMode(Mode mode);

            /**
             * \brief Returns the currently configured duplicate-filtering mode.
             * \return The Mode value.
             */
            Mode getMode() const;

            /**
             * \brief Specifies whether tautomer stereochemistry shall be preserved/regarded during duplicate filtering.
             * \param regard If \c true, stereo-configurations are taken into account.
             */
            void regardStereochemistry(bool regard);

            /**
             * \brief Tells whether stereochemistry is regarded during duplicate filtering.
             * \return \c true if stereochemistry is regarded, and \c false otherwise.
             */
            bool stereochemistryRegarded() const;

            /**
             * \brief Specifies whether atom isotope information shall be regarded during duplicate filtering.
             * \param regard If \c true, isotopes are taken into account.
             */
            void regardIsotopes(bool regard);

            /**
             * \brief Tells whether isotope information is regarded during duplicate filtering.
             * \return \c true if isotopes are regarded, and \c false otherwise.
             */
            bool isotopesRegarded() const;

            /**
             * \brief Specifies whether 2D atom coordinates shall be cleared from the generated tautomers (the input remains untouched).
             * \param clear If \c true, the output tautomers have no 2D coordinates.
             * \since 1.3
             */
            void clearCoordinates2D(bool clear);

            /**
             * \brief Tells whether 2D atom coordinates are cleared from the generated tautomers.
             * \return \c true if 2D coordinates are cleared, and \c false otherwise.
             * \since 1.3
             */
            bool coordinates2DCleared() const;

            /**
             * \brief Specifies whether 3D atom coordinates shall be cleared from the generated tautomers.
             * \param clear If \c true, the output tautomers have no 3D coordinates.
             * \since 1.3
             */
            void clearCoordinates3D(bool clear);

            /**
             * \brief Tells whether 3D atom coordinates are cleared from the generated tautomers.
             * \return \c true if 3D coordinates are cleared, and \c false otherwise.
             * \since 1.3
             */
            bool coordinates3DCleared() const;

            /**
             * \brief Specifies whether tautomers that differ only by resonance (no atom-connectivity change) shall be filtered out.
             * \param remove If \c true, resonance-only duplicates are not reported.
             * \since 1.1
             */
            void removeResonanceDuplicates(bool remove);

            /**
             * \brief Tells whether resonance-only duplicates are filtered out.
             * \return \c true if resonance duplicates are removed, and \c false otherwise.
             * \since 1.1
             */
            bool resonanceDuplicatesRemoved() const;

            /**
             * \brief Sets the optional setup function invoked on the input molecular graph before enumeration starts.
             *
             * The setup function may modify the input (e.g. add explicit hydrogens, perceive aromaticity) prior to enumeration.
             *
             * \param func The new custom-setup function.
             */
            void setCustomSetupFunction(const CustomSetupFunction& func);

            /**
             * \brief Enumerates the tautomers of \a molgraph and reports each accepted one to the registered callback.
             * \param molgraph The molecular graph whose tautomers shall be generated.
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
