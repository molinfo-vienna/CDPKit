/* 
 * BondStereoFlagCalculator.hpp 
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
 * \brief Definition of class CDPL::Chem::BondStereoFlagCalculator.
 */

#ifndef CDPL_CHEM_BONDSTEREOFLAGCALCULATOR_HPP
#define CDPL_CHEM_BONDSTEREOFLAGCALCULATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>
#include <memory>
#include <functional>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Math/VectorArray.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;

        /**
         * \brief BondStereoFlagCalculator.
         */
        class CDPL_CHEM_API BondStereoFlagCalculator
        {

          public:
            typedef std::function<const Math::Vector2D&(const Atom&)> Atom2DCoordinatesFunction;

            /**
             * \brief Constructs the \c %BondStereoFlagCalculator instance.
             */
            BondStereoFlagCalculator();

            /**
             * \brief Constructs the \c %BondStereoFlagCalculator instance and calculates the 2D stereo flags of the
             *        bonds in the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to calculate the stereo flags. 
             * \param flags An array containing the calculated stereo flags (possible values are defined
             *         as constants in namespace Chem::BondStereoFlag). The stereo flags
             *         are stored in the same order as the bonds appear in the bond list of
             *         the molecular graph (i.e. the 2D stereo flag of a bond is accessible via
             *         its index).
             */
            BondStereoFlagCalculator(const MolecularGraph& molgraph, Util::UIArray& flags);

            BondStereoFlagCalculator(const BondStereoFlagCalculator&) = delete;

            BondStereoFlagCalculator& operator=(const BondStereoFlagCalculator&) = delete;

            /**
             * \brief Specifies a function for the retrieval of atom 2D-coordinates.
             * \param func The atom 2D-coordinates function.
             */
            void setAtom2DCoordinatesFunction(const Atom2DCoordinatesFunction& func);

            /**
             * \brief Returns the function that was registered for the retrieval of atom 2D-coordinates.
             * \return The registered atom 2D-coordinates function.
             */
            const Atom2DCoordinatesFunction& getAtom2DCoordinatesFunction() const;

            /**
             * \brief Calculates the 2D stereo flags of the bonds in the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to calculate the stereo flags. 
             * \param flags An array containing the calculated stereo flags (possible values are defined
             *         as constants in namespace Chem::BondStereoFlag). The stereo flags
             *         are stored in the same order as the bonds appear in the bond list of
             *         the molecular graph (i.e. the 2D stereo flag of a bond is accessible via
             *         its index).
             */
            void calculate(const MolecularGraph& molgraph, Util::UIArray& flags);

          private:
            class StereoAtomInfo;

            void init(const MolecularGraph&, Util::UIArray&);

            void assignStereoFlags(Util::UIArray&);

            void assignFlagsForEitherDoubleBonds(Util::UIArray&);
            void assignFlagsForIsolatedCenter(const StereoAtomInfo*, Util::UIArray&);
            bool assignFlagsForNonIsolatedCenters(std::size_t, std::size_t, Util::UIArray&);

            void switchStereoFlag(std::size_t);

            class StereoAtomInfo
            {

              public:
                typedef std::shared_ptr<StereoAtomInfo> SharedPointer;

                StereoAtomInfo(const MolecularGraph*, const Atom2DCoordinatesFunction& coords_func,
                               const Atom*, unsigned int, std::size_t, const Atom**, const Bond**);

                unsigned int getConfiguration() const;

                void findBestBondOrder(const Util::BitSet&, const Util::BitSet&);

                bool hasStereoAtomNbrs() const;

                bool configMatches(const Util::UIArray&) const;

                std::size_t getNumBonds() const;

                std::size_t getBondIndex(std::size_t) const;
                std::size_t getNbrAtomIndex(std::size_t) const;

                std::size_t getAtomIndex() const;

              private:
                typedef std::pair<const Atom*, std::size_t> Ligand;

                const MolecularGraph* molGraph;
                const Atom*           atom;
                unsigned int          configuration;
                std::size_t           numBonds;
                bool                  hasStereoNbrs;
                double                configCalcTerms[4];
                bool                  bondEndFlags[4];
                Ligand                ligands[4];
                Ligand                orderedLigands[4];
            };

            typedef std::vector<StereoAtomInfo*>               StereoAtomInfoList;
            typedef std::vector<StereoAtomInfo::SharedPointer> StereoAtomInfoPtrTable;
            typedef std::vector<const Bond*>                   BondList;

            const MolecularGraph*     molGraph;
            Atom2DCoordinatesFunction coordsFunc;
            Util::UIArray             currentStereoFlags;
            StereoAtomInfoPtrTable    stereoAtomTable;
            StereoAtomInfoList        stereoAtomList;
            BondList                  eitherBondList;
            Util::BitSet              stereoAtomMask;
            Util::BitSet              configMatchMask;
            Util::BitSet              stereoDBAtomMask;
            Util::BitSet              ringBondMask;
            Util::BitSet              singleBondMask;
            std::size_t               numMismatchingCtrs;
            std::size_t               minNumMismatchingCtrs;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BONDSTEREOFLAGCALCULATOR_HPP
