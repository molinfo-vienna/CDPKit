/* 
 * AtomPropertyFunctions.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/AtomProperty.hpp"
#include "CDPL/Biomol/AtomPropertyDefault.hpp"
#include "CDPL/Chem/Atom.hpp"


using namespace CDPL;


#define MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
    void Biomol::set##FUNC_SUFFIX(Chem::Atom& atom, TYPE arg)             \
    {                                                                     \
        atom.setProperty(AtomProperty::PROP_NAME, arg);                   \
    }                                                                     \
                                                                          \
    bool Biomol::has##FUNC_SUFFIX(const Chem::Atom& atom)                 \
    {                                                                     \
        return atom.isPropertySet(AtomProperty::PROP_NAME);               \
    }                                                                     \
                                                                          \
    void Biomol::clear##FUNC_SUFFIX(Chem::Atom& atom)                     \
    {                                                                     \
        atom.removeProperty(AtomProperty::PROP_NAME);                     \
    }

#define MAKE_ATOM_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX) \
    TYPE Biomol::get##FUNC_SUFFIX(const Chem::Atom& atom)          \
    {                                                              \
        return atom.getProperty<TYPE>(AtomProperty::PROP_NAME);    \
    }                                                              \
                                                                   \
    MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX)     \
    TYPE Biomol::get##FUNC_SUFFIX(const Chem::Atom& atom)                       \
    {                                                                           \
        return atom.getPropertyOrDefault<TYPE>(AtomProperty::PROP_NAME,         \
                                               AtomPropertyDefault::PROP_NAME); \
    }                                                                           \
                                                                                \
    MAKE_ATOM_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_ATOM_PROPERTY_FUNCTIONS(RESIDUE_ATOM_NAME, const std::string&, ResidueAtomName)
MAKE_ATOM_PROPERTY_FUNCTIONS(RESIDUE_ALT_ATOM_NAME, const std::string&, ResidueAltAtomName)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(RESIDUE_LEAVING_ATOM_FLAG, bool, ResidueLeavingAtomFlag)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(RESIDUE_LINKING_ATOM_FLAG, bool, ResidueLinkingAtomFlag)
MAKE_ATOM_PROPERTY_FUNCTIONS(RESIDUE_CODE, const std::string&, ResidueCode)
MAKE_ATOM_PROPERTY_FUNCTIONS(RESIDUE_SEQUENCE_NUMBER, long, ResidueSequenceNumber)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(RESIDUE_INSERTION_CODE, char, ResidueInsertionCode)
MAKE_ATOM_PROPERTY_FUNCTIONS(HETERO_ATOM_FLAG, bool, HeteroAtomFlag)
MAKE_ATOM_PROPERTY_FUNCTIONS(SERIAL_NUMBER, long, SerialNumber)
MAKE_ATOM_PROPERTY_FUNCTIONS(CHAIN_ID, const std::string&, ChainID)
MAKE_ATOM_PROPERTY_FUNCTIONS(ALT_LOCATION_ID, char, AltLocationID)
MAKE_ATOM_PROPERTY_FUNCTIONS(ENTITY_ID, const std::string&, EntityID)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(MODEL_NUMBER, std::size_t, ModelNumber)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(OCCUPANCY, double, Occupancy)
MAKE_ATOM_PROPERTY_FUNCTIONS_WITH_DEF(B_FACTOR, double, BFactor)
