/* 
 * ForceFieldType.hpp 
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
 * \brief Definition of constants in namespace CDPL::ConfGen::ForceFieldType.
 */

#ifndef CDPL_CONFGEN_FORCEFIELDTYPE_HPP
#define CDPL_CONFGEN_FORCEFIELDTYPE_HPP


namespace CDPL 
{

    namespace ConfGen
    {

        /**
         * \brief Provides constants that are used to specify the forcefield that shall be used 
         *        for 3D coordinates refinement and energy calculations.
         */
        namespace ForceFieldType
        {
                    
            const unsigned int MMFF94                     = 0;
            const unsigned int MMFF94_NO_ESTAT            = 1;
            const unsigned int MMFF94S                    = 2;
            const unsigned int MMFF94S_NO_ESTAT           = 3;
            const unsigned int MMFF94S_XOOP               = 4;
            const unsigned int MMFF94S_XOOP_NO_ESTAT      = 5;
            const unsigned int MMFF94S_RTOR               = 6;
            const unsigned int MMFF94S_RTOR_NO_ESTAT      = 7;
            const unsigned int MMFF94S_RTOR_XOOP          = 8;
            const unsigned int MMFF94S_RTOR_XOOP_NO_ESTAT = 9;
        }
    }
}

#endif // CDPL_CONFGEN_FORCEFIELDTYPE_HPP
