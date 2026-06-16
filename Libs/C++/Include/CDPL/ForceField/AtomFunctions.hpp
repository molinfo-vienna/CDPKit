/*
 * AtomFunctions.hpp
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
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_FORCEFIELD_ATOMFUNCTIONS_HPP
#define CDPL_FORCEFIELD_ATOMFUNCTIONS_HPP

#include <string>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Atom;
        class MolecularGraph;
    } // namespace Chem

    namespace ForceField
    {

        /**
         * \brief Returns the value of the ForceField::AtomProperty::MMFF94_SYMBOLIC_TYPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The symbolic MMFF94 atom type.
         */
        CDPL_FORCEFIELD_API const std::string& getMMFF94SymbolicType(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the ForceField::AtomProperty::MMFF94_SYMBOLIC_TYPE property of the atom \a atom to \a type.
         * \param atom The atom for which to set the property value.
         * \param type The new symbolic MMFF94 atom type.
         */
        CDPL_FORCEFIELD_API void setMMFF94SymbolicType(Chem::Atom& atom, const std::string& type);

        /**
         * \brief Clears the value of the ForceField::AtomProperty::MMFF94_SYMBOLIC_TYPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_FORCEFIELD_API void clearMMFF94SymbolicType(Chem::Atom& atom);

        /**
         * \brief Tells whether the ForceField::AtomProperty::MMFF94_SYMBOLIC_TYPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the symbolic MMFF94 atom type is set, and \c false otherwise.
         */
        CDPL_FORCEFIELD_API bool hasMMFF94SymbolicType(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the ForceField::AtomProperty::MMFF94_NUMERIC_TYPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The numeric MMFF94 atom type.
         */
        CDPL_FORCEFIELD_API unsigned int getMMFF94NumericType(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the ForceField::AtomProperty::MMFF94_NUMERIC_TYPE property of the atom \a atom to \a type.
         * \param atom The atom for which to set the property value.
         * \param type The new numeric MMFF94 atom type.
         */
        CDPL_FORCEFIELD_API void setMMFF94NumericType(Chem::Atom& atom, unsigned int type);

        /**
         * \brief Clears the value of the ForceField::AtomProperty::MMFF94_NUMERIC_TYPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_FORCEFIELD_API void clearMMFF94NumericType(Chem::Atom& atom);

        /**
         * \brief Tells whether the ForceField::AtomProperty::MMFF94_NUMERIC_TYPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the numeric MMFF94 atom type is set, and \c false otherwise.
         */
        CDPL_FORCEFIELD_API bool hasMMFF94NumericType(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the ForceField::AtomProperty::MMFF94_CHARGE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The MMFF94 partial atomic charge.
         */
        CDPL_FORCEFIELD_API double getMMFF94Charge(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the ForceField::AtomProperty::MMFF94_CHARGE property of the atom \a atom to \a charge.
         * \param atom The atom for which to set the property value.
         * \param charge The new MMFF94 partial atomic charge.
         */
        CDPL_FORCEFIELD_API void setMMFF94Charge(Chem::Atom& atom, double charge);

        /**
         * \brief Clears the value of the ForceField::AtomProperty::MMFF94_CHARGE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_FORCEFIELD_API void clearMMFF94Charge(Chem::Atom& atom);

        /**
         * \brief Tells whether the ForceField::AtomProperty::MMFF94_CHARGE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the MMFF94 partial atomic charge is set, and \c false otherwise.
         */
        CDPL_FORCEFIELD_API bool hasMMFF94Charge(const Chem::Atom& atom);


        /**
         * \brief Returns the value of the ForceField::AtomProperty::UFF_TYPE property of the atom \a atom.
         * \param atom The atom for which to return the property value.
         * \return The numeric UFF atom type.
         */
        CDPL_FORCEFIELD_API unsigned int getUFFType(const Chem::Atom& atom);

        /**
         * \brief Sets the value of the ForceField::AtomProperty::UFF_TYPE property of the atom \a atom to \a type.
         * \param atom The atom for which to set the property value.
         * \param type The new numeric UFF atom type.
         */
        CDPL_FORCEFIELD_API void setUFFType(Chem::Atom& atom, unsigned int type);

        /**
         * \brief Clears the value of the ForceField::AtomProperty::UFF_TYPE property of the atom \a atom.
         * \param atom The atom for which to clear the property value.
         */
        CDPL_FORCEFIELD_API void clearUFFType(Chem::Atom& atom);

        /**
         * \brief Tells whether the ForceField::AtomProperty::UFF_TYPE property of the atom \a atom is set.
         * \param atom The atom for which to query the property value.
         * \return \c true if the numeric UFF atom type is set, and \c false otherwise.
         */
        CDPL_FORCEFIELD_API bool hasUFFType(const Chem::Atom& atom);

        /**
         * \brief Perceives the UFF atom type of the atom \a atom in the context of the molecular graph \a molgraph.
         * \param atom The atom whose UFF type is to be perceived.
         * \param molgraph The molecular graph providing the atom environment for type perception.
         * \return The perceived numeric UFF atom type (see namespace ForceField::UFFAtomType).
         */
        CDPL_FORCEFIELD_API unsigned int perceiveUFFType(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
    } // namespace ForceField
} // namespace CDPL

#endif // CDPL_FORCEFIELD_ATOMFUNCTIONS_HPP
