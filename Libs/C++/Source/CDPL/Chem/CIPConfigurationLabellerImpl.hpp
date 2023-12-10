/* 
 * CIPConfigurationLabellerImpl.hpp 
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
 * \brief Definition of the class CDPL::Chem::CIPConfigurationLabellerImpl.
 */

#ifndef CDPL_CHEM_CIPCONFIGURATIONLABELLERIMPL_HPP
#define CDPL_CHEM_CIPCONFIGURATIONLABELLERIMPL_HPP

#include <unordered_map>
#include <memory>

#include "CIPDigraph.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;
        class AtomContainer;;
        class CIPStereoCenter;
        
        class CIPConfigurationLabellerImpl
        {

          public:
            CIPConfigurationLabellerImpl();

            CIPConfigurationLabellerImpl(const CIPConfigurationLabellerImpl& labeller);

            ~CIPConfigurationLabellerImpl();
            
            void setup(const MolecularGraph& molgraph);

            unsigned int getLabel(const Atom& atom);

            unsigned int getLabel(const Bond& bond);
            
            void copy(const CIPConfigurationLabellerImpl& labeller);
            
          private:
            void extractAtomCenters();
            void extractBondCenters();
            
            typedef std::unique_ptr<CIPStereoCenter> StereoCenterPtr;
            typedef std::unordered_map<const AtomContainer*, StereoCenterPtr> StereoCenterMap;

            const MolecularGraph* molGraph;
            CIPDigraph            digraph;
            StereoCenterMap       stereoCenters;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPCONFIGURATIONLABELLERIMPL_HPP
