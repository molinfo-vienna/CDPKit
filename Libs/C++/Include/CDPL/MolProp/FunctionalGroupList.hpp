/* 
 * FunctionalGroupList.hpp 
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
 * \brief Definition of the class CDPL::MolProp::FunctionalGroupList.
 */

#ifndef CDPL_MOLPROP_FUNCTIONALGROUPLIST_HPP
#define CDPL_MOLPROP_FUNCTIONALGROUPLIST_HPP

#include <memory>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Chem/FragmentList.hpp"


namespace CDPL
{

    namespace MolProp
    {

        /**
         * \brief Implementation of Ertl's algorithm [\ref FGPE] for the identification of functional groups in organic molecules.
         * \since 1.3
         */
        class CDPL_MOLPROP_API FunctionalGroupList : public Chem::FragmentList
        {

          public:
            typedef std::shared_ptr<FunctionalGroupList> SharedPointer;

            FunctionalGroupList();

            FunctionalGroupList(const FunctionalGroupList& fg_list);
 
            FunctionalGroupList(const Chem::MolecularGraph& molgraph);

            FunctionalGroupList& operator=(FunctionalGroupList& fg_list);
            
            void extract(const Chem::MolecularGraph& molgraph);

          private:
            const char* getClassName() const
            {
                return "FunctionalGroupList";
            }

        };
    } // namespace MolProp
} // namespace CDPL

#endif // CDPL_MOLPROP_FUNCTIONALGROUPLIST_HPP
