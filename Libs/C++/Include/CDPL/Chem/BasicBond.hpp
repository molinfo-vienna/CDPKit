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
 * \brief Definition of the class CDPL::Chem::BasicBond.
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
		 * \brief BasicBond.
		 */
		class CDPL_CHEM_API BasicBond : public Bond
		{

			friend class BasicMolecule;
			friend class BasicAtom;

		public:
			std::size_t getNumAtoms() const;

			const Molecule& getMolecule() const;

			Molecule& getMolecule();

			const Atom& getBegin() const;

			Atom& getBegin();

			const Atom& getEnd() const;

			Atom& getEnd();

			const Atom& getAtom(std::size_t idx) const;

			Atom& getAtom(std::size_t idx);

			bool containsAtom(const Atom& atom) const;
		
			std::size_t getAtomIndex(const Atom& atom) const;
		
			const Atom& getNeighbor(const Atom& atom) const;
	
			Atom& getNeighbor(const Atom& atom);

			std::size_t getIndex() const;

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
	}
}

#endif // CDPL_CHEM_BASICBOND_HPP
