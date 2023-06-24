/* 
 * BasicMolecule.hpp 
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
 * \brief Definition of the class CDPL::Chem::BasicMolecule.
 */

#ifndef CDPL_CHEM_BASICMOLECULE_HPP
#define CDPL_CHEM_BASICMOLECULE_HPP

#include <vector>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/BasicAtom.hpp"
#include "CDPL/Chem/BasicBond.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL
{

    namespace Chem
    {

        /**
         * \brief BasicMolecule.
         */
        class CDPL_CHEM_API BasicMolecule : public Molecule
        {

            typedef Util::ObjectPool<BasicAtom>    AtomCache;
            typedef Util::ObjectPool<BasicBond>    BondCache;
            typedef AtomCache::SharedObjectPointer AtomPtr;
            typedef BondCache::SharedObjectPointer BondPtr;
            typedef std::vector<AtomPtr>           AtomList;
            typedef std::vector<BondPtr>           BondList;

          public:
            /**    
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %BasicMolecule instances.
             */
            typedef std::shared_ptr<BasicMolecule> SharedPointer;

            typedef boost::indirect_iterator<AtomList::iterator, BasicAtom>             AtomIterator;
            typedef boost::indirect_iterator<AtomList::const_iterator, const BasicAtom> ConstAtomIterator;
            typedef boost::indirect_iterator<BondList::iterator, BasicBond>             BondIterator;
            typedef boost::indirect_iterator<BondList::const_iterator, const BasicBond> ConstBondIterator;

            /**
             * \brief Constructs an empty \c %BasicMolecule instance.
             */
            BasicMolecule();

            /**
             * \brief Constructs a copy of the \c %BasicMolecule instance \a mol.
             * \param mol The other \c %BasicMolecule instance to copy.
             */
            BasicMolecule(const BasicMolecule& mol);

            /**
             * \brief Constructs a copy of the Chem::Molecule instance \a mol.
             * \param mol The other Chem::Molecule instance to copy.
             */
            BasicMolecule(const Molecule& mol);

            /**
             * \brief Constructs a \c %BasicMolecule instance with copies of the atoms and bonds 
             *        of the Chem::MolecularGraph instance \a molgraph.
             * \param molgraph The Chem::MolecularGraph instance providing the atoms and bonds to copy.
             */
            explicit BasicMolecule(const MolecularGraph& molgraph);

            /**
             * \brief Destructor.
             *
             * Destroys the \c %BasicMolecule instance and frees all allocated resources.
             */
            ~BasicMolecule();

            void clear();

            std::size_t getNumAtoms() const;

            std::size_t getNumBonds() const;

            /**
             * \brief Returns a constant iterator pointing to the beginning of the atoms.
             * \return A constant iterator pointing to the beginning of the atoms.
             */
            ConstAtomIterator getAtomsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the atoms.
             * \return A mutable iterator pointing to the beginning of the atoms.
             */
            AtomIterator getAtomsBegin();

            /**
             * \brief Returns a constant iterator pointing to the end of the atoms.
             * \return A constant iterator pointing to the end of the atoms.
             */
            ConstAtomIterator getAtomsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the atoms.
             * \return A mutable iterator pointing to the end of the atoms.
             */
            AtomIterator getAtomsEnd();

            /**
             * \brief Returns a constant iterator pointing to the beginning of the bonds.
             * \return A constant iterator pointing to the beginning of the bonds.
             */
            ConstBondIterator getBondsBegin() const;

            /**
             * \brief Returns a mutable iterator pointing to the beginning of the bonds.
             * \return A mutable iterator pointing to the beginning of the bonds.
             */
            BondIterator getBondsBegin();

            /**
             * \brief Returns a constant iterator pointing to the end of the bonds.
             * \return A constant iterator pointing to the end of the bonds.
             */
            ConstBondIterator getBondsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the end of the bonds.
             * \return A mutable iterator pointing to the end of the bonds.
             */
            BondIterator getBondsEnd();

            const BasicAtom& getAtom(std::size_t idx) const;

            BasicAtom& getAtom(std::size_t idx);

            BasicAtom& addAtom();

            void removeAtom(std::size_t idx);

            /**
             * \brief Removes the atom specified by the iterator \a it.
             *
             * If the specified atom is connected to any other atoms of the molecule, the connecting bonds
             * will also be removed.
             *
             * \param it An iterator that specifies the atom to remove.
             * \return A mutable iterator pointing to the next atom in the list.
             * \throw Base::RangeError if the number of atoms is zero or \a it is not in the range
             *        [getAtomsBegin(), getAtomsEnd() - 1].
             */
            AtomIterator removeAtom(const AtomIterator& it);

            const BasicBond& getBond(std::size_t idx) const;

            BasicBond& getBond(std::size_t idx);

            BasicBond& addBond(std::size_t atom1_idx, std::size_t atom2_idx);

            void removeBond(std::size_t idx);

            /**
             * \brief Removes the bond specified by the iterator \a it.
             * \param it An iterator that specifies the bond to remove.
             * \return A mutable iterator pointing to the next bond in the list.
             * \throw Base::RangeError if the number of bonds is zero or \a it is not in the range
             *        [getBondsBegin(), getBondsEnd() - 1].
             */
            BondIterator removeBond(const BondIterator& it);

            bool containsAtom(const Atom& atom) const;

            bool containsBond(const Bond& bond) const;

            std::size_t getAtomIndex(const Atom& atom) const;

            std::size_t getBondIndex(const Bond& bond) const;

            void orderAtoms(const AtomCompareFunction& func);

            void orderBonds(const BondCompareFunction& func);

            /**
             * \brief Replaces the current set of atoms, bonds and properties by a copy of the
             *        atoms, bonds and properties of the molecule \a mol.
             *
             * Internally calls copy() to perform the actual work.
             *
             * \param mol The molecule to copy.
             * \return A reference to itself.
             */
            BasicMolecule& operator=(const BasicMolecule& mol);

            using Molecule::operator=;

            /**
             * \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the
             *        molecule \a mol.
             *
             * Internally calls append() to perform the actual work.
             *
             * \param mol The molecule providing the atoms and bonds to append.
             * \return A reference to itself.
             */
            BasicMolecule& operator+=(const BasicMolecule& mol);

            using Molecule::operator+=;

            MolecularGraph::SharedPointer clone() const;

            /**
             * \brief Replaces the current set of atoms, bonds and properties by a copy of the
             *        atoms, bonds and properties of the molecule \a mol.
             * \param mol The molecule to copy.
             */
            void copy(const BasicMolecule& mol);

            void copy(const Molecule& mol);

            void copy(const MolecularGraph& molgraph);

            /**
             * \brief Extends the current set of atoms and bonds by a copy of the atoms and bonds in the
             *        molecule \a mol.
             * \param mol The molecule providing the atoms and bonds to append.
             * \note Does not affect any properties.
             */
            void append(const BasicMolecule& mol);

            void append(const Molecule& mol);

            void append(const MolecularGraph& molgraph);

            void remove(const MolecularGraph& molgraph);

            void reserveMemoryForAtoms(std::size_t num_atoms);

            void reserveMemoryForBonds(std::size_t num_bonds);

          private:
            template <typename T>
            void doCopy(const T& mol);

            template <typename T>
            void doAppend(const T& mol);

            void clearAtomsAndBonds();

            void renumberAtoms(std::size_t idx);
            void renumberBonds(std::size_t idx);

            BasicAtom* createAtom();
            BasicBond* createBond();

            static void destroyAtom(BasicAtom* atom);
            static void destroyBond(BasicBond* bond);

            static void clearAtom(BasicAtom& atom);
            static void clearBond(BasicBond& bond);

            AtomCache atomCache;
            BondCache bondCache;
            AtomList  atoms;
            BondList  bonds;
        };
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_BASICMOLECULE_HPP
