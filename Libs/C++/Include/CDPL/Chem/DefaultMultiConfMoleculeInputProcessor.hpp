/* 
 * DefaultMultiConfMoleculeInputProcessor.hpp 
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
 * \brief Definition of class CDPL::Chem::DefaultMultiConfMoleculeInputProcessor.
 */

#ifndef CDPL_CHEM_DEFAULTMULTICONFMOLECULEINPUTPROCESSOR_HPP
#define CDPL_CHEM_DEFAULTMULTICONFMOLECULEINPUTPROCESSOR_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief MultiConfMoleculeInputProcessor.
         */
        class CDPL_CHEM_API DefaultMultiConfMoleculeInputProcessor : public MultiConfMoleculeInputProcessor
        {

          public:
            typedef std::shared_ptr<DefaultMultiConfMoleculeInputProcessor> SharedPointer;

            static constexpr unsigned int DEF_ATOM_PROPERTY_FLAGS =
                AtomPropertyFlag::TYPE | AtomPropertyFlag::ISOTOPE |
                AtomPropertyFlag::FORMAL_CHARGE;

            static constexpr unsigned int DEF_BOND_PROPERTY_FLAGS =
                BondPropertyFlag::ORDER;

            DefaultMultiConfMoleculeInputProcessor(bool comp_names = true, unsigned int atom_flags = DEF_ATOM_PROPERTY_FLAGS, unsigned int bond_flags = DEF_BOND_PROPERTY_FLAGS);

            bool init(MolecularGraph& tgt_molgraph) const;

            bool isConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const;

            bool addConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const;

          private:
            bool         compareNames;
            unsigned int atomFlags;
            unsigned int bondFlags;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_DEFAULTMULTICONFMOLECULEINPUTPROCESSOR_HPP
