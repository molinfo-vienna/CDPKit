/* 
 * BasicBond.hpp 
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
 * \brief Definition of class CDPL::Chem::BasicBond.
 */

#ifndef CDPL_CHEM_BASICBOND_HPP
#define CDPL_CHEM_BASICBOND_HPP

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Bond.hpp"


namespace CDPL
{

    namespace Chem
    {

        class BasicMolecule;
        class BasicAtom;

        /**
         * \brief Default implementation of the Chem::Bond interface.
         *
         * Instances of \c %BasicBond are owned and constructed exclusively by a Chem::BasicMolecule instance
         * and reference two Chem::BasicAtom instances that represent the bonded atoms.
         */
        class CDPL_CHEM_API BasicBond : public Bond
        {

            friend class BasicMolecule;
            friend class BasicAtom;

          public:
            /**
             * \brief Returns the number of atoms incident to this bond (always \e 2).
             * \return The atom count (\e 2).
             */
            std::size_t getNumAtoms() const;

            /**
             * \brief Returns the parent molecule.
             * \return A \c const reference to the parent molecule.
             */
            const Molecule& getMolecule() const;

            /**
             * \brief Returns the parent molecule.
             * \return A reference to the parent molecule.
             */
            Molecule& getMolecule();

            /**
             * \brief Returns the first atom of the bond.
             * \return A \c const reference to the first atom.
             */
            const Atom& getBegin() const;

            /**
             * \brief Returns the first atom of the bond.
             * \return A reference to the first atom.
             */
            Atom& getBegin();

            /**
             * \brief Returns the second atom of the bond.
             * \return A \c const reference to the second atom.
             */
            const Atom& getEnd() const;

            /**
             * \brief Returns the second atom of the bond.
             * \return A reference to the second atom.
             */
            Atom& getEnd();

            /**
             * \brief Returns the bond atom at index \a idx.
             * \param idx The zero-based atom index (\e 0 = begin, \e 1 = end).
             * \return A \c const reference to the atom.
             * \throw Base::IndexError if \a idx is not in the range [0, 1].
             */
            const Atom& getAtom(std::size_t idx) const;

            /**
             * \brief Returns the bond atom at index \a idx.
             * \param idx The zero-based atom index (\e 0 = begin, \e 1 = end).
             * \return A reference to the atom.
             * \throw Base::IndexError if \a idx is not in the range [0, 1].
             */
            Atom& getAtom(std::size_t idx);

            /**
             * \brief Tells whether \a atom is one of the two bonded atoms.
             * \param atom The atom to test.
             * \return \c true if \a atom is incident to this bond, and \c false otherwise.
             */
            bool containsAtom(const Atom& atom) const;

            /**
             * \brief Returns the index of \a atom within this bond.
             * \param atom The atom whose index is requested.
             * \return The atom index (\e 0 for the begin atom, \e 1 for the end atom).
             * \throw Base::ItemNotFound if \a atom is not incident to this bond.
             */
            std::size_t getAtomIndex(const Atom& atom) const;

            /**
             * \brief Returns the atom on the opposite side of \a atom.
             * \param atom One of the two bonded atoms.
             * \return A \c const reference to the other bonded atom.
             * \throw Base::ItemNotFound if \a atom is not incident to this bond.
             */
            const Atom& getNeighbor(const Atom& atom) const;

            /**
             * \brief Returns the atom on the opposite side of \a atom.
             * \param atom One of the two bonded atoms.
             * \return A reference to the other bonded atom.
             * \throw Base::ItemNotFound if \a atom is not incident to this bond.
             */
            Atom& getNeighbor(const Atom& atom);

            /**
             * \brief Returns the zero-based index of this bond within the parent molecule.
             * \return The bond index.
             */
            std::size_t getIndex() const;

            /**
             * \brief Reorders the begin/end atoms of this bond according to the comparison function \a func.
             * \param func The comparison function defining the desired order.
             */
            void orderAtoms(const AtomCompareFunction& func);

            /**
             * \brief Assignment operator that replaces the current set of properties with the properties of \a bond;
             * \param bond The bond whose properties get copied.
             * \return A reference to itself.
             */
            BasicBond& operator=(const BasicBond& bond);

            using Bond::operator=;

          private:
            BasicBond(BasicMolecule* mol);

            BasicBond(const BasicBond& bond);

            ~BasicBond();

            void setIndex(std::size_t idx);

            void setBegin(BasicAtom& atom);
            void setEnd(BasicAtom& atom);

            BasicMolecule* molecule;
            std::size_t    index;
            BasicAtom*     atoms[2];
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BASICBOND_HPP
