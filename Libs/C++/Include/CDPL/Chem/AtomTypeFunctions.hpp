/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomTypeFunctions.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Declaration of functions for the lookup of meta-data associated with the atom
 *        types defined in namespace Chem::AtomType.
 */

#ifndef CDPL_CHEM_ATOMTYPEFUNCTIONS_HPP
#define CDPL_CHEM_ATOMTYPEFUNCTIONS_HPP

#include <cstddef>
#include <string>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		/**
		 * \addtogroup CDPL_CHEM_ATOM_TYPE_FUNCTIONS
		 * @{
		 */

		/**
		 * \brief Returns the symbol that is associated with the specified atom type and isotope.
		 *
		 * The \a isotope argument has only an effect for hydrogen whose isotopes have different symbols
		 * (D for \e Deuterium and T for \e Tritium).
		 *
		 * \param type The atom type.
		 * \param isotope The mass number of the isotope, or \e 0 if not specified.
		 * \return The atom type symbol, or an empty string if the symbol for the specified type and isotope is not
		 *         available.
		 */
		CDPL_CHEM_API const std::string& getAtomTypeSymbol(unsigned int type, std::size_t isotope = 0);

		/**
		 * \brief Returns the name of the chemical element that is associated with the specified atom type
		 *        and isotope.
		 *
		 * The \a isotope argument has only an effect for hydrogen whose isotopes are named differently
		 * (\e Deuterium and \e Tritium).
		 *
		 * \param type The atom type specifying the chemical element.
		 * \param isotope The mass number of the element's isotope, or \e 0 if not specified.
		 * \return The name of the element isotope, or an empty string if \a type does not specify a
		 *         supported chemical element.
		 */
		CDPL_CHEM_API const std::string& getElementName(unsigned int type, std::size_t isotope = 0);

		/**
		 * \brief Returns the numeric atom type that is associated with the specified atom type symbol.
		 * \param symbol The atom type symbol.
		 * \return The numeric atom type, or AtomType::UNKNOWN if \a symbol does not specify a
		 *         supported atom type.
		 */
		CDPL_CHEM_API unsigned int getAtomType(const std::string& symbol);

		/**
		 * \brief Returns the mass number of the most abundant isotope of the chemical element specified by
		 *        \a type.
		 * \param type The atom type specifying the chemical element.
		 * \return The mass number of the most abundant isotope of the element, or \e 0 if \a type
		 *         does not specify a supported chemical element.
		 */
		CDPL_CHEM_API std::size_t getMostAbundantIsotope(unsigned int type);

		/**
		 * \brief Returns the IUPAC group of the chemical element specified by \a type.
		 * \param type The atom type specifying the chemical element.
		 * \return The IUPAC group of the element, or \e 0 if \a type
		 *         does not specify a supported chemical element.
		 */
		CDPL_CHEM_API std::size_t getIUPACGroup(unsigned int type);

		/**
		 * \brief Returns the number of valence electrons of the chemical element specified by \a type.
		 * \param type The atom type specifying the chemical element.
		 * \return The number of valence electrons, or \e 0 if \a type
		 *         does not specify a supported chemical element.
		 */
		CDPL_CHEM_API std::size_t getNumValenceElectrons(unsigned int type);

		/**
		 * \brief Returns the standard atomic weight or the relative isotopic mass of an isotope of the
		 *        chemical element specified by \a type.
		 *
		 * If the element isotope is left unspecified, i.e. the argument \a isotope is zero, then the standard
		 * atomic weight of the chemical element will be returned.
		 * If an isotope is specified and the exact relative isotopic mass of the specified isotope is not available, the
		 * relative isotopic mass is approximated by the provided mass number of the isotope.
		 *
		 * \param type The atom type specifying the chemical element.
		 * \param isotope The mass number of the element's isotope, or \e 0 if not specified.
		 * \return The relative isotopic mass of the specified element isotope, or the standard atomic weight of
		 *         the element if \a isotope is zero.
		 */
		CDPL_CHEM_API double getAtomicWeight(unsigned int type, std::size_t isotope = 0);

		/**
		 * \brief Returns the <em>van der Waals</em> radius of the chemical element specified by \a type.
		 * \param type The atom type specifying the chemical element.
		 * \return The <em>van der Waals</em> radius, or \e 0.0 if \a type
		 *         does not specify a supported chemical element.
		 */
		CDPL_CHEM_API double getVdWRadius(unsigned int type);

		/**
		 * \brief Returns the covalent radius of the chemical element specified by \a type for the given bond order.
		 * \param type The atom type specifying the chemical element.
		 * \param order The bond order.
		 * \return The covalent radius for the specified bond order, or \e 0.0 if \a type
		 *         does not specify a supported chemical element, \a order is not valid or the radius is unknown.
		 */
		CDPL_CHEM_API double getCovalentRadius(unsigned int type, std::size_t order = 1);

		/**
		 * \brief Returns the <em>Allred-Rochow</em> electronegativity of the chemical element specified
		 *        by \a type.
		 * \param type The atom type specifying the chemical element.
		 * \return The <em>Allred-Rochow</em> electronegativity, or \e 0.0 if the electronegativity of the
		 *         specified element is not available.
		 */
		CDPL_CHEM_API double getAllredRochowElectronegativity(unsigned int type);

		/**
		 * \brief Returns an array with the valence states of the chemical element specified by \a type.
		 *
		 * The returned array is terminated by the value \e -1,
		 *
		 * \param type The atom type specifying the chemical element.
		 * \return An array with the valence states of the specified chemical element.
		 */
		CDPL_CHEM_API const int* getValenceStates(unsigned int type);
			
		/**
		 * \brief Tells whether the specified atom type represents a chemical element.
		 * \param type The atom type.
		 * \return \c true if \a type specifies a chemical element, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isChemicalElement(unsigned int type);

		/**
		 * \brief Tells whether the chemical element specified by \a type is a main group element.
		 * \param type The atom type specifying the chemical element.
		 * \return \c true if \a type specifies a main group element, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isMainGroupElement(unsigned int type);

		/**
		 * \brief Tells whether the chemical element specified by \a type is a transition metal.
		 * \param type The atom type specifying the chemical element.
		 * \return \c true if \a type specifies a transition metal, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isTransitionMetal(unsigned int type);

		/**
		 * \brief Tells whether the chemical element specified by \a type is a metal.
		 * \param type The atom type specifying the chemical element.
		 * \return \c true if \a type specifies a metal, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isMetal(unsigned int type);

		/**
		 * \brief Tells whether the chemical element specified by \a type is a semi-metal.
		 * \param type The atom type specifying the chemical element.
		 * \return \c true if \a type specifies a semi-metal, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isSemiMetal(unsigned int type);

		/**
		 * \brief Tells whether the chemical element specified by \a type is a non-metal.
		 * \param type The atom type specifying the chemical element.
		 * \return \c true if \a type specifies a non-metal, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isNonMetal(unsigned int type);

		/**
		 * \brief Tells whether the chemical element specified by \a type is a halogen.
		 * \param type The atom type specifying the chemical element.
		 * \return \c true if \a type specifies a halogen, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isHalogen(unsigned int type);

		/**
		 * \brief Tells whether the chemical element specified by \a type is a noble gas.
		 * \param type The atom type specifying the chemical element.
		 * \return \c true if \a type specifies a noble gas, and \c false otherwise.
		 */
		CDPL_CHEM_API bool isNobleGas(unsigned int type);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_ATOMTYPEFUNCTIONS_HPP
