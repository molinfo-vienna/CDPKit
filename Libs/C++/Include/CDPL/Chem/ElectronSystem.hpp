/* 
 * ElectronSystem.hpp 
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
 * \brief Definition of class CDPL::Chem::ElectronSystem.
 */

#ifndef CDPL_CHEM_ELECTRONSYSTEM_HPP
#define CDPL_CHEM_ELECTRONSYSTEM_HPP

#include <vector>
#include <utility>
#include <unordered_map>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomContainer.hpp"


namespace CDPL
{

    namespace Chem
    {

        class BondContainer;

        /**
         * \brief Describes an electron system of a molecule in terms of involved atoms and their electron contributions.
         */
        class CDPL_CHEM_API ElectronSystem : public AtomContainer
        {

            typedef std::vector<Atom*> AtomList;

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ElectronSystem instances.
             */
            typedef std::shared_ptr<ElectronSystem> SharedPointer;

            /**
             * \brief A constant random access iterator used to iterate over the stored \c const Chem::Atom objects.
             */
            typedef boost::indirect_iterator<AtomList::const_iterator, const Atom> ConstAtomIterator;

            /**
             * \brief A mutable random access iterator used to iterate over the stored \c const Chem::Atom objects.
             */
            typedef boost::indirect_iterator<AtomList::iterator, Atom> AtomIterator;

            /**
             * \brief Constructs an empty \c %ElectronSystem instance.
             */
            ElectronSystem();

            /**
             * \brief Returns the number of atoms contributing to the electron system.
             * \return The number of atoms.
             */
            std::size_t getNumAtoms() const;

            /**
             * \brief Tells whether the specified atom is part of the electron system.
             * \param atom The atom to look for.
             * \return \c true if \a atom is part of the electron system and \c false, otherwise.
             */
            bool containsAtom(const Atom& atom) const;

            /**
             * \brief Returns the index of the specified atom.
             * \param atom The atom for which to return the index.
             * \return The zero-based index of the specified atom.
             * \throw Base::ItemNotFound if the specified atom is not part of this electron system.
             */
            std::size_t getAtomIndex(const Atom& atom) const;

            /**
             * \brief Returns a \c const reference to the atom at index \a idx.
             * \param idx The zero-based index of the atom to return.
             * \return A \c const reference to the atom at the specified index.
             * \throw Base::IndexError if the number of atoms is zero or \a idx is not in the range [0, getNumAtoms() - 1].
             */
            const Atom& getAtom(std::size_t idx) const;

            /**
             * \brief Returns a \c non-const reference to the atom at index \a idx.
             * \param idx The zero-based index of the atom to return.
             * \return A \c non-const reference to the atom at the specified index.
             * \throw Base::IndexError if the number of atoms is zero or \a idx is not in the range [0, getNumAtoms() - 1].
             */
            Atom& getAtom(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             * \return A constant iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             */
            ConstAtomIterator getAtomsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             * \return A mutable iterator pointing to the beginning of the stored \c const Chem::Atom objects.
             */
            AtomIterator getAtomsBegin();

            /**
             * \brief Returns a constant iterator pointing to the end of the stored \c const Chem::Atom objects.
             * \return A constant iterator pointing to the end of the stored \c const Chem::Atom objects.
             */
            ConstAtomIterator getAtomsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the stored \c const Chem::Atom objects.
             * \return A mutable iterator pointing to the end of the stored \c const Chem::Atom objects.
             */
            AtomIterator getAtomsEnd();

            /**
             * \brief Removes all atoms.
             */
            void clear();

            /**
             * \brief Orders the stored atoms according to criteria implemented by the provided atom comparison function.
             * \param func The atom comparison function implementing the applied ordering criteria.
             */
            void orderAtoms(const AtomCompareFunction& func);

            /**
             * \brief Extends the electron system by the specified atom and its electron contributions.
             * \param atom The atom to add.
             * \param elec_contrib The number of electrons contributed by the added atom.
             * \return \c true if the atom was not already involved in this electron system and \c false, otherwise.
             * \note If the atom is already part of the system no changes will be made.
             */
            bool addAtom(const Chem::Atom& atom, std::size_t elec_contrib);

            /**
             * \brief Adds the atoms and associated electron contributions in the electron system \a elec_sys to this system.
             *
             * The method is equivalent to repeatedly calling addAtom() for each atom in \a elec_sys.
             *
             * \param elec_sys The electron system to add.
             * \return \c true if the electron system was extended by atoms from \a elec_sys and \c false, otherwise.
             */
            bool addAtoms(const ElectronSystem& elec_sys);

            /**
             * \brief Removes the atom at the specified index.
             * \param idx The zero-based index of the atom to remove.
             * \throw Base::IndexError if the number of atoms is zero or \a idx is not in the range [0, getNumAtoms() - 1].
             */
            void removeAtom(std::size_t idx);

            /**
             * \brief Removes the atom specified by the iterator \a it.
             * \param it An iterator that specifies the atom to remove.
             * \return A mutable iterator pointing to the next atom in the list.
             * \throw Base::RangeError if the number of atoms is zero or \a it is not in the range
             *        [getAtomsBegin(), getAtomsEnd() - 1].
             */
            AtomIterator removeAtom(const AtomIterator& it);

            /**
             * \brief Removes the specified atom.
             * \param atom The atom to remove.
             * \return \c true if the atom was part of the electron system and has been removed, and \c false otherwise.
             */
            bool removeAtom(const Atom& atom);

            /**
             * \brief Returns the total number of electrons contributed by the involved atoms.
             * \return The total electron count of this system.
             */
            std::size_t getNumElectrons() const;

            /**
             * \brief Returns the number of electrons contributed by the specified atom.
             * \param atom The atom for which to return the contributed electron count.
             * \return The number of electrons contributed by the specified atom.
             * \throw Base::ItemNotFound if the specified atom is not part of the electron system.
             */
            std::size_t getElectronContrib(const Atom& atom) const;

            /**
             * \brief Returns the number of electrons contributed by the atom at the specified index.
             * \param idx The index of the atom for which to return the contributed electron count.
             * \return The number of electrons contributed by the specified atom.
             * \throw Base::IndexError if the number of atoms is zero or \a idx is not in the range [0, getNumAtoms() - 1].
             */
            std::size_t getElectronContrib(std::size_t idx) const;

            /**
             * \brief Changes the number of electrons that are contributed by the specified atom.
             * \param atom The atom for which to update the electron contribution.
             * \param elec_contrib The number of electrons contributed by the specified atom.
             * \throw Base::ItemNotFound if the specified atom is not part of the electron system.
             */
            void setElectronContrib(const Atom& atom, std::size_t elec_contrib);

            /**
             * \brief Changes the number of electrons that are contributed by the atom at the specified index.
             * \param idx The index of the atom for which to update the electron contribution.             
             * \param elec_contrib The number of electrons contributed by the specified atom.
             * \throw Base::IndexError if the number of atoms is zero or \a idx is not in the range [0, getNumAtoms() - 1].
             */
            void setElectronContrib(std::size_t idx, std::size_t elec_contrib);

            /**
             * \brief Merges the atoms and associated electron contributions in the electron system \a elec_sys with this system.
             *
             * For atoms that are present in both electron systems, the resulting electron contribution will be the sum of their
             * contributions to the respective systems!
             *
             * \param elec_sys The electron system to merge.
             */
            void merge(const ElectronSystem& elec_sys);

            /**
             * \brief Checks if the electron system shares at least one atom with the system \a elec_sys.
             * \param elec_sys The electron system to check for atom set intersection.
             * \return \c true if at least one atom in \a elec_sys is also part of this electron system and \c false, otherwise.
             */
            bool overlaps(const ElectronSystem& elec_sys) const;

            /**
             * \brief Checks if all atoms in the electron system \a elec_sys are also part of this electron system.
             * \param elec_sys The electron system to check for atom set containment.
             * \return \c true if all atoms in \a elec_sys are also part of this electron system and \c false, otherwise.
             */
            bool contains(const ElectronSystem& elec_sys) const;

            /**
             * \brief Checks if the atom sets of the electron systems do not intersect but are linked by at least one bond.
             * \param elec_sys The electron system to check.
             * \param bonds The set of available bonds.
             * \return \c true if the electron systems do not share any atoms but are linked by at least one bond and \c false, otherwise.
             */
            bool connected(const ElectronSystem& elec_sys, const BondContainer& bonds) const;

            /**
             * \brief Exchanges the state of this electron system with the state of the system \a elec_sys.
             * \param elec_sys The other \c %ElectronSystem instance.
             */
            void swap(ElectronSystem& elec_sys);

          private:
            typedef std::pair<std::size_t, std::size_t>     UIPair;
            typedef std::unordered_map<const Atom*, UIPair> AtomIdxAndElecContribMap;

            AtomList                 atoms;
            AtomIdxAndElecContribMap atomIndsAndElecContribs;
            std::size_t              numElectrons;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_ELECTRONSYSTEM_HPP
