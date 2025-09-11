/* 
 * MMFF94PropertyFunctions.hpp 
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
 * \brief Type declaration of generic wrapper classes for storing user-defined functions
 *        for the retrieval of MMFF94 related properties.
 */

#ifndef CDPL_FORCEFIELD_MMFF94PROPERTYFUNCTIONS_HPP
#define CDPL_FORCEFIELD_MMFF94PROPERTYFUNCTIONS_HPP

#include <string>
#include <functional>

#include "CDPL/Chem/FragmentList.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
        class Bond;
        class MolecularGraph;
    } // namespace Chem

    namespace ForceField
    {

        /**
         * \brief A generic wrapper class used to store a user-defined numeric MMFF94 atom type function.
         */
        typedef std::function<unsigned int(const Chem::Atom&)> MMFF94NumericAtomTypeFunction;

        /**
         * \brief A generic wrapper class used to store a user-defined symbolic MMFF94 atom type function.
         */
        typedef std::function<const std::string&(const Chem::Atom&)> MMFF94SymbolicAtomTypeFunction;

        /**
         * \brief A generic wrapper class used to store a user-defined MMFF94 partial atom charge function.
         */
        typedef std::function<double(const Chem::Atom&)> MMFF94AtomChargeFunction;

        /**
         * \brief A generic wrapper class used to store a user-defined MMFF94 bond type index function.
         */
        typedef std::function<unsigned int(const Chem::Bond&)> MMFF94BondTypeIndexFunction;

        /**
         * \brief A generic wrapper class used to store a user-defined MMFF94 ring set function.
         */
        typedef std::function<const Chem::FragmentList::SharedPointer&(const Chem::MolecularGraph&)> MMFF94RingSetFunction;
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_MMFF94PROPERTYFUNCTIONS_HPP
