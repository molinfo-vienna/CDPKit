/* 
 * CIPPairList.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * Code based on a Java implementation of the CIP sequence rules by John Mayfield
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
 * \brief Definition of the class CDPL::Chem::CIPPairList.
 */

#ifndef CDPL_CHEM_CIPPAIRLIST_HPP
#define CDPL_CHEM_CIPPAIRLIST_HPP

#include <vector>


namespace CDPL
{

    namespace Chem
    {

        /**
         * Implementation of a descriptor list that allows descriptors to be added and
         * ignored. 
         */
        class CIPPairList
        {

          public:
            typedef std::vector<unsigned int> DescriptorList;

            CIPPairList() {}
            
            CIPPairList(unsigned int ref);

            unsigned int getRefDescriptor() const;
            
            /**
             * Adds a descriptor to the descriptor list. 
             *
             * If the provided descriptor is present in the ignore set the descriptor will not be added.
             *
             * @param descriptor the descriptor to add.
             * @return whether the descriptor was added to the list
             */
            bool add(unsigned int descriptor);

            /**
             * Clear the descriptor list and resets the pair value. 
             */
            void clear();
          
            int compareTo(const CIPPairList& that) const;

            static unsigned int ref(unsigned int descriptor);
            
          private:
            DescriptorList descriptors;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_CIPPAIRLIST_HPP
