/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicAtom.hpp
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::BasicAtom.
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
		 * \addtogroup CDPL_CHEM_STRUCTURE_IMPLEMENTATIONS
		 * @{
		 */

		/**
		 * \brief BasicAtom.
		 */
		class CDPL_CHEM_API BasicAtom : public Atom
		{

			friend class BasicMolecule;

			typedef std::pair<BasicAtom*, BasicBond*> AtomBondPair;
			typedef std::vector<AtomBondPair> NeighborList;

			template <typename AtomType>
			struct AtomAccessor
			{

				typedef AtomType& result_type;

				AtomType& operator()(const AtomBondPair& ab_pair) const {
					return *ab_pair.first;
				}
			};

			template <typename BondType>
			struct BondAccessor
			{

				typedef BondType& result_type;

				BondType& operator()(const AtomBondPair& ab_pair) const {
					return *ab_pair.second;
				}
			};

		public:
			typedef boost::transform_iterator<AtomAccessor<BasicAtom>, NeighborList::iterator> AtomIterator;
			typedef boost::transform_iterator<AtomAccessor<const BasicAtom>, NeighborList::const_iterator> ConstAtomIterator;
			typedef boost::transform_iterator<BondAccessor<BasicBond>, NeighborList::iterator> BondIterator;
			typedef boost::transform_iterator<BondAccessor<const BasicBond>, NeighborList::const_iterator> ConstBondIterator;
	
			const Molecule& getMolecule() const;

			Molecule& getMolecule();
		
			std::size_t getNumAtoms() const;
		
			std::size_t getNumBonds() const;
	
			const Bond& getBond(std::size_t idx) const;
		
			Bond& getBond(std::size_t idx);
			
			const Bond& getBondToAtom(const Atom& atom) const;
		
			Bond& getBondToAtom(const Atom& atom);

			const Bond* findBondToAtom(const Atom& atom) const;

			Bond* findBondToAtom(const Atom& atom);

			const Atom& getAtom(std::size_t idx) const;

			Atom& getAtom(std::size_t idx);
		
			/*
			 * \brief Returns a constant iterator pointing to the beginning of the connected atoms.
			 * \return A constant iterator pointing to the beginning of the connected atoms.
			 */
			ConstAtomIterator getAtomsBegin() const;

			/*
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

			bool containsAtom(const Atom& atom) const;

			bool containsBond(const Bond& bond) const;

			std::size_t getAtomIndex(const Atom& atom) const;

			std::size_t getBondIndex(const Bond& bond) const;

			std::size_t getIndex() const;

			void orderAtoms(const AtomCompareFunction& func);

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

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_BASICATOM_HPP
