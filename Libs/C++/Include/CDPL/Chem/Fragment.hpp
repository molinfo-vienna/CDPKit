/* 
 * Fragment.hpp 
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
 * \brief Definition of the class CDPL::Chem::Fragment.
 */

#ifndef CDPL_CHEM_FRAGMENT_HPP
#define CDPL_CHEM_FRAGMENT_HPP

#include <vector>
#include <unordered_map>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \brief Fragment.
		 */
		class CDPL_CHEM_API Fragment : public MolecularGraph
		{

			typedef std::vector<Atom*> AtomList;
			typedef std::vector<Bond*> BondList;

		public:
			/**	
			 * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %Fragment instances.
			 */
			typedef std::shared_ptr<Fragment> SharedPointer;

			/**
			 * \brief A constant random access iterator used to iterate over the stored \c const Chem::Atom objects.
			 */
			typedef boost::indirect_iterator<AtomList::const_iterator, const Atom> ConstAtomIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the stored \c const Chem::Atom objects.
			 */
			typedef boost::indirect_iterator<AtomList::iterator, Atom> AtomIterator;

			/**
			 * \brief A constant random access iterator used to iterate over the stored \c const Chem::Bond objects.
			 */
			typedef boost::indirect_iterator<BondList::const_iterator, const Bond> ConstBondIterator;

			/**
			 * \brief A mutable random access iterator used to iterate over the stored \c const Chem::Bond objects.
			 */
			typedef boost::indirect_iterator<BondList::iterator, Bond> BondIterator;

			/**
			 * \brief Constructs an empty \c %Fragment instance.
			 */
			Fragment();

			/**
			 * \brief Constructs a copy of the \c %Fragment instance \a frag.
			 * \param frag The other \c %Fragment instance to copy.
			 */
			Fragment(const Fragment& frag);

			/**
			 * \brief Constructs a \c %Fragment instance storing the atoms, bonds and properties of the molecular graph \a molgraph.
			 * \param molgraph The Chem::MolecularGraph instance providing the atoms, bonds and properties to store.
			 */
			explicit Fragment(const MolecularGraph& molgraph);

			/**
			 * \brief Destructor.
			 *
			 * Destroys the \c %Fragment instance and frees all allocated resources.
			 */
			~Fragment();

			/**
			 * \brief Returns the number of atoms.
			 * \return The number of atoms.
			 */
			std::size_t getNumAtoms() const;

			/**
			 * \brief Returns the number of bonds.
			 * \return The number of bonds.
			 */
			std::size_t getNumBonds() const;

			/**
			 * \brief Tells whether the specified atom is part of this fragment.
			 * \param atom The atom to look for.
			 * \return \c true if \a atom is part of this fragment, and \c false otherwise.
			 */
			bool containsAtom(const Atom& atom) const;

			/**
			 * \brief Tells whether the specified bond is part of this fragment.
			 * \param bond The bond to look for.
			 * \return \c true if \a bond is part of this fragment, and \c false otherwise.
			 */
			bool containsBond(const Bond& bond) const;

			/**
			 * \brief Returns the index of the specified atom.
			 * \param atom The atom for which to return the index.
			 * \return The zero-based index of the specified atom.
			 * \throw Base::ItemNotFound if the specified atom is not part of the fragment.
			 */
			std::size_t getAtomIndex(const Atom& atom) const;

			/**
			 * \brief Returns the index of the specified bond.
			 * \param bond The bond for which to return the index.
			 * \return The zero-based index of the specified bond.
			 * \throw Base::ItemNotFound if the specified bond is not part of the fragment.
			 */
			std::size_t getBondIndex(const Bond& bond) const;

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
			 * \brief Returns a constant iterator pointing to the beginning of the stored \c const Chem::Bond objects.
			 * \return A constant iterator pointing to the beginning of the stored \c const Chem::Bond objects.
			 */
			ConstBondIterator getBondsBegin() const; 

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the stored \c const Chem::Bond objects.
			 * \return A mutable iterator pointing to the beginning of the stored \c const Chem::Bond objects.
			 */
			BondIterator getBondsBegin(); 

			/**
			 * \brief Returns a constant iterator pointing to the end of the stored \c const Chem::Bond objects.
			 * \return A constant iterator pointing to the end of the stored \c const Chem::Bond objects.
			 */
			ConstBondIterator getBondsEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the stored \c const Chem::Bond objects.
			 * \return A mutable iterator pointing to the end of the stored \c const Chem::Bond objects.
			 */
			BondIterator getBondsEnd();

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
			 * \brief Returns a \c const reference to the bond at index \a idx.
			 * \param idx The zero-based index of the bond to return.
			 * \return A \c const reference to the bond at the specified index.
			 * \throw Base::IndexError if the number of bonds is zero or \a idx is not in the range [0, getNumBonds() - 1].
			 */
			const Bond& getBond(std::size_t idx) const;

			/**
			 * \brief Returns a \c non-const reference to the bond at index \a idx.
			 * \param idx The zero-based index of the bond to return.
			 * \return A \c non-const reference to the bond at the specified index.
			 * \throw Base::IndexError if the number of bonds is zero or \a idx is not in the range [0, getNumBonds() - 1].
			 */
			Bond& getBond(std::size_t idx);

			/**
			 * \brief Extends the fragment by the specified atom.
			 * \param atom The atom to add.
			 * \return \c true if the atom was not already a part of the fragment, and \c false otherwise.
			 */
			bool addAtom(const Atom& atom);

			/**
			 * \brief Extends the fragment by the specified bond.
			 *
			 * If the atoms of the bond are not already part of the fragment, they will be
			 * added automatically.
			 *
			 * \param bond The bond to add.
			 * \return \c true if the bond was not already a part of the fragment, and \c false otherwise.
			 */
			bool addBond(const Bond& bond);

			/**
			 * \brief Removes the atom at the specified index.
			 *
			 * If the specified atom is connected to any other atoms of the fragment, the connecting bonds
			 * will also be removed.
			 *
			 * \param idx The zero-based index of the atom to remove.
			 * \throw Base::IndexError if the number of atoms is zero or \a idx is not in the range [0, getNumAtoms() - 1].
			 */
			void removeAtom(std::size_t idx);

			/**
			 * \brief Removes the atom specified by the iterator \a it.
			 *
			 * If the specified atom is connected to any other atoms of the fragment, the connecting bonds
			 * will also be removed.
			 *
			 * \param it An iterator that specifies the atom to remove.
			 * \return A mutable iterator pointing to the next atom in the list.
			 * \throw Base::RangeError if the number of atoms is zero or \a it is not in the range
			 *        [getAtomsBegin(), getAtomsEnd() - 1].
			 */
			AtomIterator removeAtom(const AtomIterator& it);

			/**
			 * \brief Removes the specified atom.
			 *
			 * If the specified atom is connected to any other atoms of the fragment, the connecting bonds
			 * will also be removed.
			 *
			 * \param atom The atom to remove.
			 * \return \c true if the atom was part of the fragment and has been removed, and \c false otherwise.
			 */
			bool removeAtom(const Atom& atom);

			/**
			 * \brief Removes the bond at the specified index.
			 * \param idx The zero-based index of the bond to remove.
			 * \throw Base::IndexError if the number of bonds is zero or \a idx is not in the range [0, getNumBonds() - 1].
			 */
			void removeBond(std::size_t idx);

			/**
			 * \brief Removes the bond specified by the iterator \a it.
			 * \param it An iterator that specifies the bond to remove.
			 * \return A mutable iterator pointing to the next bond in the list.
			 * \throw Base::RangeError if the number of bonds is zero or \a it is not in the range
			 *        [getBondsBegin(), getBondsEnd() - 1].
			 */
			BondIterator removeBond(const BondIterator& it);

			/**
			 * \brief Removes the specified bond.
			 * \param bond The bond to remove.
			 * \return \c true if the bond was removed, and \c false otherwise.
			 */
			bool removeBond(const Bond& bond);		

			/**
			 * \brief Removes all atoms and bonds.
			 */
			void clear();

			using Base::PropertyContainer::swap;
			
			/**
			 * \brief Exchanges the atoms, bonds and properties of this fragment with the atoms, bonds and
			 *        properties of the fragment \a frag.
			 * \param frag The fragment the atoms, bonds and properties get exchanged with.
			 */
			void swap(Fragment& frag);

			/**
			 * \brief Orders the stored atoms according to criteria implemented by the provided atom comparison function.
			 * \param func The atom comparison function implementing the applied ordering criteria.
			 */
			void orderAtoms(const AtomCompareFunction& func);

			/**
			 * \brief Orders the stored bonds according to criteria implemented by the provided bond comparison function.
			 * \param func The bond comparison function implementing the applied ordering criteria.
			 */
			void orderBonds(const BondCompareFunction& func);

			/**
			 * \brief Replaces the current set of atoms, bonds and properties by the atoms, bonds and properties
			 *        of the fragment \a frag.
			 * \param frag The fragment to copy.
			 * \return A reference to itself.
			 */
			Fragment& operator=(const Fragment& frag);

			/**
			 * \brief Replaces the current set of atoms, bonds and properties by the atoms, bonds and properties
			 *        of the molecular graph \a molgraph.
			 * \param molgraph The Chem::MolecularGraph instance providing the atoms, bonds and properties to copy.
			 * \return A reference to itself.
			 */
			Fragment& operator=(const MolecularGraph& molgraph);

			/**
			 * \brief Extends the current set of atoms and bonds by the atoms and bonds in the
			 *        molecular graph \a molgraph.
			 * \param molgraph The Chem::MolecularGraph instance providing the atoms and bonds to add.
			 * \return A reference to itself.
			 * \note Does not affect any properties.
			 */
			Fragment& operator+=(const MolecularGraph& molgraph);

			/**
			 * \brief Removes the atoms and bonds referenced by the molecular graph \a molgraph from this \c %Fragment instance.
			 * \param molgraph The Chem::MolecularGraph instance specifying the atoms and bonds to remove.
			 * \return A reference to itself.
			 * \note Does not affect any properties if <tt>this != &molgraph</tt>.
			 */
			Fragment& operator-=(const MolecularGraph& molgraph);

			MolecularGraph::SharedPointer clone() const;

			void reserveMemoryForAtoms(std::size_t num_atoms);

			void reserveMemoryForBonds(std::size_t num_bonds);

		private:
			typedef std::unordered_map<const Atom*, std::size_t> AtomIndexMap;
			typedef std::unordered_map<const Bond*, std::size_t> BondIndexMap;

			AtomList     atoms;
			BondList     bonds;
			AtomIndexMap atomIndices;
			BondIndexMap bondIndices;
		};
	}
}

#endif // CDPL_CHEM_FRAGMENT_HPP
