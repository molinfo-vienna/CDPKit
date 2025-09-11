/* 
 * CIPConfigurationLabeler.hpp 
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
 * \brief Definition of class CDPL::Chem::CIPConfigurationLabeler.
 */

#ifndef CDPL_CHEM_CIPCONFIGURATIONLABELER_HPP
#define CDPL_CHEM_CIPCONFIGURATIONLABELER_HPP

#include <memory>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class MolecularGraph;
        class Atom;
        class Bond;
        class CIPConfigurationLabelerImpl;
        
        /**
         * \brief CIPConfigurationLabeler.
         *
         * Code is largely based on a Java implementation of the CIP sequence rules by John Mayfield [\ref CIPJM].
         * \since 1.1
         */
        class CDPL_CHEM_API CIPConfigurationLabeler
        {

          public:
            typedef std::shared_ptr<CIPConfigurationLabeler> SharedPointer;
            
            CIPConfigurationLabeler();

            CIPConfigurationLabeler(const MolecularGraph& molgraph);

            CIPConfigurationLabeler(const CIPConfigurationLabeler& labeler);

            ~CIPConfigurationLabeler();
            
            void setup(const MolecularGraph& molgraph);

            unsigned int getLabel(const Atom& atom);

            unsigned int getLabel(const Bond& bond);
            
            CIPConfigurationLabeler& operator=(const CIPConfigurationLabeler& labeler);
            
          private:
            typedef std::unique_ptr<CIPConfigurationLabelerImpl> ImplementationPointer;

            ImplementationPointer impl;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPCONFIGURATIONLABELER_HPP
