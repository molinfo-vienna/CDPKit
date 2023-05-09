/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Atom.hpp
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
 * \brief Definition of the class CDPL::Chem::Atom.
 */

#ifndef CDPL_CHEM_ATOM_HPP
#define CDPL_CHEM_ATOM_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/BondContainer.hpp"
#include "CDPL/Chem/Entity3D.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		class Molecule;

		/**
		 * \brief Atom.
		 */
		class CDPL_CHEM_API Atom : public AtomContainer, public BondContainer, public Entity3D
		{

		public:
			/**
			 * \brief A mutable random access iterator used to iterate over the connected atoms.
			 */
			typedef AtomContainer::AtomIterator AtomIterator;

			/**
			 * \brief A constant random access iterator used to iterate over the connected atoms.
			 */
			typedef AtomContainer::ConstAtomIterator ConstAtomIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the incident bonds.
			 */
			typedef BondContainer::BondIterator BondIterator;

			/**
			 * \brief A constant random access iterator used to iterate over the incident bonds.
			 */
			typedef BondContainer::ConstBondIterator ConstBondIterator;

			using AtomContainer::getAtomsBegin;
			using AtomContainer::getAtomsEnd;

			using BondContainer::getBondsBegin;
			using BondContainer::getBondsEnd;

			/**
			 * \brief Returns a \c const reference to the parent molecule.
			 * \return A \c const reference to the parent molecule.
			 */
			virtual const Molecule& getMolecule() const = 0;

			/**
			 * \brief Returns a non-\c const reference to the parent molecule.
			 * \return A non-\c const reference to the parent molecule.
			 */
			virtual Molecule& getMolecule() = 0;
		
			/**
			 * \brief Returns a \c const reference to the Chem::Bond object that connects this atom to the argument atom.
			 * \param atom The adjacent atom for which to return the connecting bond.
			 * \return A \c const reference to the Chem::Bond object connecting this atom and the argument atom.
			 * \throw Base::ItemNotFound if the argument atom is not connected to this atom. 
			 */
			virtual const Bond& getBondToAtom(const Atom& atom) const = 0;

			/**
			 * \brief Returns a non-\c const reference to the Chem::Bond object that connects this atom to the argument atom.
			 * \param atom The adjacent atom for which to return the connecting bond.
			 * \return A non-\c const reference to the Chem::Bond object connecting this atom and the argument atom.
			 * \throw Base::ItemNotFound if the argument atom is not connected to this atom. 
			 */
			virtual Bond& getBondToAtom(const Atom& atom) = 0;

			/**
			 * \brief Returns a pointer to the \c const Chem::Bond object that connects this atom to the argument atom.
			 * \param atom The adjacent atom for which to return a pointer to the connecting bond.
			 * \return A pointer to the \c const Chem::Bond object that connects this atom to the argument atom, or \e null
			 *         if the argument atom is not connected.
			 */
			virtual const Bond* findBondToAtom(const Atom& atom) const = 0;

			/**
			 * \brief Returns a pointer to the non-\c const Chem::Bond object that connects this atom to the argument atom.
			 * \param atom The adjacent atom for which to return a pointer to the connecting bond.
			 * \return A pointer to the non-\c const Chem::Bond object that connects this atom to the argument atom, or \e null
			 *         if the argument atom is not connected.
			 */
			virtual Bond* findBondToAtom(const Atom& atom) = 0;

			/**
			 * \brief Returns the index of the atom in its parent molecule.
			 * \return The zero-based index of the atom.
			 */
			virtual std::size_t getIndex() const = 0;
	
			/**
			 * \brief Returns the number of connected atoms.
			 *
			 * Equivalent to getNumBonds().
			 *
			 * \return The number of connected atoms.
			 */
			virtual std::size_t getNumAtoms() const = 0;

			/**
			 * \brief Returns the number of incident bonds.
			 *
			 * Equivalent to getNumAtoms().
			 *
			 * \return The number of incident bonds.
			 */
			virtual std::size_t getNumBonds() const = 0;
	   
			/**
			 * \brief Returns a \c const reference to the incident bond at index \a idx.
			 * \param idx The index of the incident bond to return.
			 * \return A \c const reference to the incident bond at index \a idx.
			 * \throw Base::IndexError if \a idx is not in the range [0, getNumBonds() - 1].
			 * \note The order of incident bonds corresponds to the order of the connected atoms.
			 */
			virtual const Bond& getBond(std::size_t idx) const = 0;

			/**
			 * \brief Returns a non-\c const reference to the incident bond at index \a idx.
			 * \param idx The index of the incident bond to return.
			 * \return A non-\c const reference to the incident bond at index \a idx.
			 * \throw Base::IndexError if \a idx is not in the range [0, getNumBonds() - 1].
			 * \note The order of incident bonds corresponds to the order of connected atoms.
			 */
			virtual Bond& getBond(std::size_t idx) = 0;

			/**
			 * \brief Returns a \c const reference to the connected atom at index \a idx.
			 * \param idx The index of the atom to return.
			 * \return A \c const reference to the connected atom at index \a idx.
			 * \throw Base::IndexError if \a idx is not in the range [0, getNumAtoms() - 1].
			 * \note The order of connected atoms corresponds to the order of connecting bonds.
			 */
			virtual const Atom& getAtom(std::size_t idx) const = 0;

			/**
			 * \brief Returns a non-\c const reference to the connected atom at index \a idx.
			 * \param idx The index of the atom to return.
			 * \return A non-\c const reference to the connected atom at index \a idx.
			 * \throw Base::IndexError if \a idx is not in the range [0, getNumAtoms() - 1].
			 * \note The order of connected atoms corresponds to the order of connecting bonds.
			 */
			virtual Atom& getAtom(std::size_t idx) = 0;
		
			/**
			 * \brief Tells whether this atom and the argument atom are connected by a bond.
			 * \param atom The atom to test for adjacency.
			 * \return \c true if the argument atom is connected to this atom, and \c false otherwise.
			 */
			virtual bool containsAtom(const Atom& atom) const = 0;

			/**
			 * \brief Tells whether the specified bond is incident to this atom.
			 * \param bond The bond to test for incidence.
			 * \return \c true if the argument bond is incident to this atom, and \c false otherwise.
			 */
			virtual bool containsBond(const Bond& bond) const = 0;

			/**
			 * \brief Returns the index of the specified connected atom.
			 * \param atom The connected atom for which to return the index.
			 * \return The zero-based index of the specified atom.
			 * \throw Base::ItemNotFound if the specified atom is not connected to this atom.
			 */
			virtual std::size_t getAtomIndex(const Atom& atom) const = 0;

			/**
			 * \brief Returns the index of the specified incident bond.
			 * \param bond The bond for which to return the index.
			 * \return The zero-based index of the specified bond.
			 * \throw Base::ItemNotFound if the specified bond is not incident to this atom.
			 */
			virtual std::size_t getBondIndex(const Bond& bond) const = 0;
	
			/**
			 * \brief Assignment operator that replaces the current set of properties with the properties of \a atom;
			 * \param atom The atom whose properties get copied.
			 * \return A reference to itself.
			 */
			Atom& operator=(const Atom& atom);

		protected:
			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Atom() {}
		};
	}
}

#endif // CDPL_CHEM_ATOM_HPP
