/* 
 * Bond.hpp 
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
 * \brief Definition of the class CDPL::Chem::Bond.
 */

#ifndef CDPL_CHEM_BOND_HPP
#define CDPL_CHEM_BOND_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL
{

    namespace Chem
    {

        class Molecule;

        /**
         * \brief Bond.
         */
        class CDPL_CHEM_API Bond : public AtomContainer,
                                   public Base::PropertyContainer
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

            using AtomContainer::getAtomsBegin;
            using AtomContainer::getAtomsEnd;

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
             * \brief Returns a \c const reference to the start atom of the bond.
             * \return A \c const reference to the start atom of the bond.
             */
            virtual const Atom& getBegin() const = 0;

            /**
             * \brief Returns a non-\c const reference to the start atom of the bond.
             * \return A non-\c const reference to the start atom of the bond.
             */
            virtual Atom& getBegin() = 0;

            /**
             * \brief Returns a \c const reference to the end atom of the bond.
             * \return A \c const reference to the end atom of the bond.
             */
            virtual const Atom& getEnd() const = 0;

            /**
             * \brief Returns a non-\c const reference to the end atom of the bond.
             * \return A non-\c const reference to the end atom of the bond.
             */
            virtual Atom& getEnd() = 0;

            /**
             * \brief Returns a \c const reference to the connected neighbor of the argument atom.
             * \param atom The atom for which to return the connected neighbor atom.
             * \return A \c const reference to the connected neighbor of the argument atom.
             * \throw Base::ItemNotFound if the bond is not incident to the specified atom.
             */
            virtual const Atom& getNeighbor(const Atom& atom) const = 0;

            /**
             * \brief Returns a non-\c const reference to the connected neighbor of the argument atom.
             * \param atom The atom for which to return the connected neighbor atom.
             * \return A non-\c const reference to the connected neighbor atom of the argument atom.
             * \throw Base::ItemNotFound if the specified atom is not involved in the bond.
             */
            virtual Atom& getNeighbor(const Atom& atom) = 0;

            /**
             * \brief Returns the index of the bond in its parent molecule.
             * \return The zero-based index of the bond.
             */
            virtual std::size_t getIndex() const = 0;

            /**
             * \brief Returns the number of atoms connected by the bond.
             *
             * Since a bond connects exactly two atoms, the return value is always \e 2.
             *
             * \return The number of atoms connected by the bond (always \e 2).
             */
            virtual std::size_t getNumAtoms() const = 0;

            /**
             * \brief Returns a \c const reference to the atom at index \a idx.
             *
             * The index \e 0 specifies the start atom (see getBegin() const) and
             * \e 1 the end atom of the bond (see getEnd() const).
             *
             * \param idx The index of the atom to return.
             * \return A \c const reference to the atom at index \a idx.
             * \throw Base::IndexError if \a idx is not in the range [0, 1].
             */
            virtual const Atom& getAtom(std::size_t idx) const = 0;

            /**
             * \brief Returns a non-\c const reference to the atom at index \a idx.
             *
             * The index \e 0 specifies the start atom (see getBegin() const) and
             * \e 1 the end atom of the bond (see getEnd() const).
             *
             * \param idx The index of the atom to return.
             * \return A non-\c const reference to the atom at index \a idx.
             * \throw Base::IndexError if \a idx is not in the range [0, 1].
             */
            virtual Atom& getAtom(std::size_t idx) = 0;

            /**
             * \brief Tells whether the bond is incident to the specified atom.
             * \param atom The atom to check.
             * \return \c true if the bond is incident to the specified atom, and \c false otherwise.
             */
            virtual bool containsAtom(const Atom& atom) const = 0;

            /**
             * \brief Returns the index of the specified atom.
             *
             * If the specified atom is the start atom of the bond, the index \e 0 is returned.
             * For the end atom of the bond, the value \e 1 will be returned.
             *
             * \param atom The atom for which to return the index.
             * \return The zero-based index of the specified atom.
             * \throw Base::ItemNotFound if the bond is not incident to the specified atom.
             */
            virtual std::size_t getAtomIndex(const Atom& atom) const = 0;

            /**
             * \brief Assignment operator that replaces the current set of properties with the properties of \a bond;
             * \param bond The bond whose properties get copied.
             * \return A reference to itself.
             */
            Bond& operator=(const Bond& bond);

          protected:
            /**
             * \brief Virtual destructor.
             */
            virtual ~Bond() {}
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BOND_HPP
