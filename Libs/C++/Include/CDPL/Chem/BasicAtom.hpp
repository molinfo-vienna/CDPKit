/* 
 * BasicAtom.hpp
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
 * \brief Definition of class CDPL::Chem::BasicAtom.
 */

#ifndef CDPL_CHEM_BASICATOM_HPP
#define CDPL_CHEM_BASICATOM_HPP

#include <vector>
#include <utility>

#include <boost/iterator/transform_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Atom.hpp"


namespace CDPL
{

    namespace Chem
    {

        class BasicMolecule;
        class BasicBond;

        /**
         * \brief Concrete Chem::Atom implementation used as the atom type of Chem::BasicMolecule.
         *
         * Stores its own incident-bond list and provides constant-time access to neighbor atoms and bonds
         * via the inherited Chem::Atom interface. \c %BasicAtom instances are owned by a Chem::BasicMolecule
         * and are not constructed directly by client code; use Chem::BasicMolecule::addAtom() instead.
         */
        class CDPL_CHEM_API BasicAtom : public Atom
        {

            friend class BasicMolecule;

            typedef std::pair<BasicAtom*, BasicBond*> AtomBondPair;
            typedef std::vector<AtomBondPair>         NeighborList;

            template <typename AtomType>
            struct AtomAccessor
            {

                typedef AtomType& result_type;

                AtomType& operator()(const AtomBondPair& ab_pair) const
                {
                    return *ab_pair.first;
                }
            };

            template <typename BondType>
            struct BondAccessor
            {

                typedef BondType& result_type;

                BondType& operator()(const AtomBondPair& ab_pair) const
                {
                    return *ab_pair.second;
                }
            };

          public:
            /** \brief Mutable random-access iterator over the connected (neighbor) atoms. */
            typedef boost::transform_iterator<AtomAccessor<BasicAtom>, NeighborList::iterator>             AtomIterator;
            /** \brief Constant random-access iterator over the connected (neighbor) atoms. */
            typedef boost::transform_iterator<AtomAccessor<const BasicAtom>, NeighborList::const_iterator> ConstAtomIterator;
            /** \brief Mutable random-access iterator over the incident bonds. */
            typedef boost::transform_iterator<BondAccessor<BasicBond>, NeighborList::iterator>             BondIterator;
            /** \brief Constant random-access iterator over the incident bonds. */
            typedef boost::transform_iterator<BondAccessor<const BasicBond>, NeighborList::const_iterator> ConstBondIterator;

            /**
             * \brief Returns a \c const reference to the molecule owning this atom.
             * \return A \c const reference to the owning molecule.
             */
            const Molecule& getMolecule() const;

            /**
             * \brief Returns a mutable reference to the molecule owning this atom.
             * \return A mutable reference to the owning molecule.
             */
            Molecule& getMolecule();

            /**
             * \brief Returns the number of connected (neighbor) atoms.
             * \return The neighbor count.
             */
            std::size_t getNumAtoms() const;

            /**
             * \brief Returns the number of incident bonds (equal to getNumAtoms()).
             * \return The incident-bond count.
             */
            std::size_t getNumBonds() const;

            /**
             * \brief Returns a \c const reference to the incident bond at index \a idx.
             * \param idx The zero-based index of the bond.
             * \return A \c const reference to the bond.
             * \throw Base::IndexError if \a idx is not less than getNumBonds().
             */
            const Bond& getBond(std::size_t idx) const;

            /**
             * \brief Returns a mutable reference to the incident bond at index \a idx.
             * \param idx The zero-based index of the bond.
             * \return A mutable reference to the bond.
             * \throw Base::IndexError if \a idx is not less than getNumBonds().
             */
            Bond& getBond(std::size_t idx);

            /**
             * \brief Returns the incident bond that connects this atom with \a atom.
             * \param atom The other end-atom of the requested bond.
             * \return A \c const reference to the connecting bond.
             * \throw Base::ItemNotFound if there is no such bond.
             */
            const Bond& getBondToAtom(const Atom& atom) const;

            /**
             * \brief Returns the incident bond that connects this atom with \a atom.
             * \param atom The other end-atom of the requested bond.
             * \return A mutable reference to the connecting bond.
             * \throw Base::ItemNotFound if there is no such bond.
             */
            Bond& getBondToAtom(const Atom& atom);

            /**
             * \brief Looks up the incident bond that connects this atom with \a atom without throwing.
             * \param atom The other end-atom of the requested bond.
             * \return A pointer to the connecting bond, or \c nullptr if no such bond exists.
             */
            const Bond* findBondToAtom(const Atom& atom) const;

            /**
             * \brief Looks up the incident bond that connects this atom with \a atom without throwing.
             * \param atom The other end-atom of the requested bond.
             * \return A pointer to the connecting bond, or \c nullptr if no such bond exists.
             */
            Bond* findBondToAtom(const Atom& atom);

            /**
             * \brief Returns a \c const reference to the connected (neighbor) atom at index \a idx.
             * \param idx The zero-based index of the neighbor atom.
             * \return A \c const reference to the neighbor atom.
             * \throw Base::IndexError if \a idx is not less than getNumAtoms().
             */
            const Atom& getAtom(std::size_t idx) const;

            /**
             * \brief Returns a mutable reference to the connected (neighbor) atom at index \a idx.
             * \param idx The zero-based index of the neighbor atom.
             * \return A mutable reference to the neighbor atom.
             * \throw Base::IndexError if \a idx is not less than getNumAtoms().
             */
            Atom& getAtom(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the beginning of the connected atoms.
             * \return A constant iterator pointing to the beginning of the connected atoms.
             */
            ConstAtomIterator getAtomsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the connected atoms.
             * \return A mutable iterator pointing to the beginning of the connected atoms.
             */
            AtomIterator getAtomsBegin();

            /**
             * \brief Returns a constant iterator pointing to the end of the connected atoms.
             * \return A constant iterator pointing to the end of the connected atoms.
             */
            ConstAtomIterator getAtomsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the connected atoms.
             * \return A mutable iterator pointing to the end of the connected atoms.
             */
            AtomIterator getAtomsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the incident bonds.
             * \return A constant iterator pointing to the beginning of the incident bonds.
             */
            ConstBondIterator getBondsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the incident bonds.
             * \return A mutable iterator pointing to the beginning of the incident bonds.
             */
            BondIterator getBondsBegin();

            /**
             * \brief Returns a constant iterator pointing to the end of the incident bonds.
             * \return A constant iterator pointing to the end of the incident bonds.
             */
            ConstBondIterator getBondsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the incident bonds.
             * \return A mutable iterator pointing to the end of the incident bonds.
             */
            BondIterator getBondsEnd();

            /**
             * \brief Tells whether \a atom is a neighbor of this atom.
             * \param atom The atom to look up.
             * \return \c true if \a atom is in the neighbor list, and \c false otherwise.
             */
            bool containsAtom(const Atom& atom) const;

            /**
             * \brief Tells whether \a bond is an incident bond of this atom.
             * \param bond The bond to look up.
             * \return \c true if \a bond is in the incident-bond list, and \c false otherwise.
             */
            bool containsBond(const Bond& bond) const;

            /**
             * \brief Returns the index of the neighbor atom \a atom in the connected-atoms list.
             * \param atom The neighbor atom to look up.
             * \return The zero-based neighbor index.
             * \throw Base::ItemNotFound if \a atom is not a neighbor.
             */
            std::size_t getAtomIndex(const Atom& atom) const;

            /**
             * \brief Returns the index of the incident bond \a bond.
             * \param bond The bond to look up.
             * \return The zero-based incident-bond index.
             * \throw Base::ItemNotFound if \a bond is not incident.
             */
            std::size_t getBondIndex(const Bond& bond) const;

            /**
             * \brief Returns the index of this atom in its owning molecule's atom list.
             * \return The zero-based atom index.
             */
            std::size_t getIndex() const;

            /**
             * \brief Reorders the connected (neighbor) atom list using the binary comparator \a func.
             * \param func The strict-weak-ordering comparator used to sort the neighbor list.
             */
            void orderAtoms(const AtomCompareFunction& func);

            /**
             * \brief Reorders the incident bond list using the binary comparator \a func.
             * \param func The strict-weak-ordering comparator used to sort the bond list.
             */
            void orderBonds(const BondCompareFunction& func);

            /**
             * \brief Assignment operator that replaces the current set of properties with the properties of \a atom;
             * \param atom The atom whose properties get copied.
             * \return A reference to itself.
             */
            BasicAtom& operator=(const BasicAtom& atom);

            using Atom::operator=;

          private:
            BasicAtom(BasicMolecule* mol);

            BasicAtom(const BasicAtom& atom);

            ~BasicAtom();

            void setIndex(std::size_t idx);

            void clearAdjacencyLists();

            static void reserveMemForNewBond(BasicAtom& atom1, BasicAtom& atom2);
            static void connectAtoms(BasicAtom& atom1, BasicAtom& atom2, BasicBond& bond);
            static void disconnectAtoms(BasicBond& bond);

            BasicMolecule* molecule;
            std::size_t    index;
            NeighborList   neighbors;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BASICATOM_HPP
