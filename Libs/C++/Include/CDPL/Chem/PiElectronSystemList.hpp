/* 
 * PiElectronSystemList.hpp 
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
 * \brief Definition of class CDPL::Chem::PiElectronSystemList.
 */

#ifndef CDPL_CHEM_PIELECTRONSYSTEMLIST_HPP
#define CDPL_CHEM_PIELECTRONSYSTEMLIST_HPP

#include <list>
#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/ElectronSystemList.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;

        /**
         * \brief Implements the perception of all pi electron systems present in a molecule.
         */
        class CDPL_CHEM_API PiElectronSystemList : public ElectronSystemList
        {

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %PiElectronSystemList instances.
             */
            typedef std::shared_ptr<PiElectronSystemList> SharedPointer;

            /**
             * \brief Constructs an empty \c %PiElectronSystemList instance.
             */
            PiElectronSystemList();

            /**
             * \brief Constructs a \c %PiElectronSystemList instance storing all pi electron systems of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the pi electron systems.
             */
            PiElectronSystemList(const MolecularGraph& molgraph);

            /**
             * \brief Perceives all pi electron systems present in the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to perceive the pi electron systems.
             */
            void perceive(const MolecularGraph& molgraph);

          private:
            typedef std::list<ElectronSystem::SharedPointer> WorkingElecSysList;

            void initStartElecSystems(const MolecularGraph& molgraph);

            void mergeElecSystems(const MolecularGraph& molgraph);

            void mergeElecSystemsPass1(const MolecularGraph& molgraph);
            void mergeElecSystemsPass2(const MolecularGraph& molgraph);

            bool isCumuleneSubPiSystem(const ElectronSystem& sub_e_sys, const ElectronSystem& parent_e_sys,
                                       const MolecularGraph& molgraph) const;
            bool isLinChainPiSysWith1ElecPerAtom(const ElectronSystem& e_sys,
                                                 const MolecularGraph& molgraph) const;
            bool has2NeighborsWith1Elec(const Atom& atom, const ElectronSystem& e_sys,
                                        const MolecularGraph& molgraph) const;

            WorkingElecSysList workingElecSystems;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_PIELECTRONSYSTEMLIST_HPP
