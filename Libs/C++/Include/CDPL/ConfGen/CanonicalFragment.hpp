/* 
 * CanonicalFragment.hpp 
 *
 * This file is part of the ConfGenical Data Processing Toolkit
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
 * \brief Definition of class CDPL::ConfGen::CanonicalFragment.
 */

#ifndef CDPL_CONFGEN_CANONICALFRAGMENT_HPP
#define CDPL_CONFGEN_CANONICALFRAGMENT_HPP

#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/CanonicalNumberingCalculator.hpp"
#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL
{

    namespace ConfGen
    {

        /**
         * \brief Data structure representing a canonicalized molecular fragment.
         *
         * A \c %CanonicalFragment is constructed from a fragment of a parent molecular graph and stores
         * a canonicalized copy of the fragment's atoms and bonds. Canonicalization yields a stable
         * atom ordering and an associated hash code that uniquely identifies the topology (and,
         * optionally, the stereochemistry) of the fragment. 
         *
         * \see ConfGen::FragmentLibrary
         */
        class CDPL_CONFGEN_API CanonicalFragment : public Chem::MolecularGraph
        {

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %CanonicalFragment instances.
             */
            typedef std::shared_ptr<CanonicalFragment> SharedPointer;

            /**
             * \brief A mutable iterator over the contained atoms.
             */
            typedef Chem::BasicMolecule::AtomIterator      AtomIterator;

            /**
             * \brief A constant iterator over the contained atoms.
             */
            typedef Chem::BasicMolecule::ConstAtomIterator ConstAtomIterator;

            /**
             * \brief A mutable iterator over the contained bonds.
             */
            typedef Chem::BasicMolecule::BondIterator      BondIterator;

            /**
             * \brief A constant iterator over the contained bonds.
             */
            typedef Chem::BasicMolecule::ConstBondIterator ConstBondIterator;

            /**
             * \brief Maps each atom of the fragment (in canonical order) to the corresponding atom of the parent molecular graph.
             */
            typedef std::vector<const Chem::Atom*> AtomMapping;

            /**
             * \brief Constructs an empty \c %CanonicalFragment instance.
             */
            CanonicalFragment();

            /**
             * \brief Constructs a \c %CanonicalFragment instance from the fragment \a molgraph of the parent molecular graph \a parent.
             * \param molgraph The molecular graph defining the fragment to canonicalize.
             * \param parent The parent molecular graph the fragment was derived from.
             */
            CanonicalFragment(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent);

            /**
             * \brief Constructs a copy of the \c %CanonicalFragment instance \a frag.
             * \param frag The \c %CanonicalFragment to copy.
             */
            CanonicalFragment(const CanonicalFragment& frag);

            /**
             * \brief Removes all atoms and bonds and resets the hash code.
             */
            void clear();

            /**
             * \brief Returns the number of atoms in the fragment.
             * \return The number of atoms.
             */
            std::size_t getNumAtoms() const;

            /**
             * \brief Returns a \c const reference to the atom at index \a idx.
             * \param idx The index of the atom.
             * \return A \c const reference to the atom.
             */
            const Chem::Atom& getAtom(std::size_t idx) const;

            /**
             * \brief Returns a reference to the atom at index \a idx.
             * \param idx The index of the atom.
             * \return A reference to the atom.
             */
            Chem::Atom& getAtom(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first atom.
             * \return A constant iterator pointing to the first atom.
             */
            ConstAtomIterator getAtomsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last atom.
             * \return A constant iterator pointing one past the last atom.
             */
            ConstAtomIterator getAtomsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first atom.
             * \return A mutable iterator pointing to the first atom.
             */
            AtomIterator getAtomsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last atom.
             * \return A mutable iterator pointing one past the last atom.
             */
            AtomIterator getAtomsEnd();

            /**
             * \brief Tells whether the fragment contains \a atom.
             * \param atom The atom to look up.
             * \return \c true if the atom is part of the fragment, and \c false otherwise.
             */
            bool containsAtom(const Chem::Atom& atom) const;

            /**
             * \brief Returns the index of \a atom in the fragment.
             * \param atom The atom whose index is requested.
             * \return The index of the atom.
             */
            std::size_t getAtomIndex(const Chem::Atom& atom) const;

            /**
             * \brief Returns the number of 3D entities in the fragment.
             * \return The number of 3D entities (equal to getNumAtoms()).
             */
            std::size_t getNumEntities() const;

            /**
             * \brief Returns a \c const reference to the 3D entity at index \a idx.
             * \param idx The index of the entity.
             * \return A \c const reference to the entity.
             */
            const Chem::Entity3D& getEntity(std::size_t idx) const;

            /**
             * \brief Returns a reference to the 3D entity at index \a idx.
             * \param idx The index of the entity.
             * \return A reference to the entity.
             */
            Chem::Entity3D& getEntity(std::size_t idx);

            /**
             * \brief Returns the number of bonds in the fragment.
             * \return The number of bonds.
             */
            std::size_t getNumBonds() const;

            /**
             * \brief Returns a \c const reference to the bond at index \a idx.
             * \param idx The index of the bond.
             * \return A \c const reference to the bond.
             */
            const Chem::Bond& getBond(std::size_t idx) const;

            /**
             * \brief Returns a reference to the bond at index \a idx.
             * \param idx The index of the bond.
             * \return A reference to the bond.
             */
            Chem::Bond& getBond(std::size_t idx);

            /**
             * \brief Returns a constant iterator pointing to the first bond.
             * \return A constant iterator pointing to the first bond.
             */
            ConstBondIterator getBondsBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last bond.
             * \return A constant iterator pointing one past the last bond.
             */
            ConstBondIterator getBondsEnd() const;

            /**
             * \brief Returns a mutable iterator pointing to the first bond.
             * \return A mutable iterator pointing to the first bond.
             */
            BondIterator getBondsBegin();

            /**
             * \brief Returns a mutable iterator pointing one past the last bond.
             * \return A mutable iterator pointing one past the last bond.
             */
            BondIterator getBondsEnd();

            /**
             * \brief Tells whether the fragment contains \a bond.
             * \param bond The bond to look up.
             * \return \c true if the bond is part of the fragment, and \c false otherwise.
             */
            bool containsBond(const Chem::Bond& bond) const;

            /**
             * \brief Returns the index of \a bond in the fragment.
             * \param bond The bond whose index is requested.
             * \return The index of the bond.
             */
            std::size_t getBondIndex(const Chem::Bond& bond) const;

            /**
             * \brief Reorders the atoms of the fragment according to \a func.
             * \param func The comparison function used to define the new atom order.
             */
            void orderAtoms(const Chem::AtomCompareFunction& func);

            /**
             * \brief Reorders the bonds of the fragment according to \a func.
             * \param func The comparison function used to define the new bond order.
             */
            void orderBonds(const Chem::BondCompareFunction& func);

            /**
             * \brief Returns the hash code of the fragment.
             * \return The fragment hash code (\e 0 if not yet computed).
             */
            std::uint64_t getHashCode() const;

            /**
             * \brief Creates and returns a deep copy of the fragment.
             * \return A smart pointer to the cloned fragment.
             */
            Chem::MolecularGraph::SharedPointer clone() const;

            /**
             * \brief Replaces the contents of this fragment with a copy of \a frag.
             * \param frag The source \c %CanonicalFragment.
             * \return A reference to itself.
             */
            CanonicalFragment& operator=(const CanonicalFragment& frag);

            /**
             * \brief Builds the canonical fragment from the fragment \a molgraph of the parent molecular graph \a parent.
             * \param molgraph The molecular graph defining the fragment to canonicalize.
             * \param parent The parent molecular graph the fragment was derived from.
             * \param modify If \c true, the fragment is modified prior to canonicalization (e.g. ring perception, hydrogenization).
             * \param strip_aro_subst If \c true, aromatic-ring substituents are stripped during fragment construction.
             */
            void create(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent,
                        bool modify = true, bool strip_aro_subst = true);

            /**
             * \brief Returns the atom mapping from this fragment to the parent molecular graph.
             * \return A \c const reference to the atom mapping.
             */
            const AtomMapping& getAtomMapping() const;

            /**
             * \brief Perceives the smallest set of smallest rings of the fragment.
             */
            void perceiveSSSR();

          private:
            void copyAtoms(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent,
                           bool modify, bool strip_aro_subst);
            bool copyBonds(const Chem::MolecularGraph& molgraph);

            void fixStereoDescriptors(const Chem::MolecularGraph& molgraph, bool clear_stereo);
            void hydrogenize();
            void canonicalize(bool stereo);
            void calcHashCode(bool stereo);

            bool compareCanonNumber(const Chem::Atom& atom1, const Chem::Atom& atom2) const;

            typedef std::vector<std::uint32_t>                      HashInputData;
            typedef Chem::SmallestSetOfSmallestRings::SharedPointer SmallestSetOfSmallestRingsPtr;

            Chem::BasicMolecule                molecule;
            std::uint64_t                      hashCode;
            Chem::CanonicalNumberingCalculator canonNumCalc;
            SmallestSetOfSmallestRingsPtr      sssr;
            Util::STArray                      canonNumbers;
            HashInputData                      hashInputData;
            AtomMapping                        atomMapping;
        };
    } // namespace ConfGen
} // namespace CDPL

#endif // CDPL_CONFGEN_CANONICALFRAGMENT_HPP
