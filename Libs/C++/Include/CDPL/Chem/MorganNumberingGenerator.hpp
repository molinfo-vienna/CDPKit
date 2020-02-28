/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MorganNumberingGenerator.hpp 
 *
 * Morgan Algorithm for canonical numbering
 * (H. L. Morgan, J. Chem. Doc. 1965, 5, 107)
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
 * \brief Definition of the class CDPL::Chem::MorganNumberingGenerator.
 */

#ifndef CDPL_CHEM_MORGANNUMBERINGGENERATOR_HPP
#define CDPL_CHEM_MORGANNUMBERINGGENERATOR_HPP

#include <vector>
#include <string>
#include <utility>
#include <cstddef>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Math/Matrix.hpp"
#include "CDPL/Util/Array.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_CANONICAL_NUMBERING
		 * @{
		 */

		/**
		 * \brief MorganNumberingGenerator.
		 * \see [\ref MOCAN]
		 */
		class CDPL_CHEM_API MorganNumberingGenerator 
		{

		public:
			/**
			 * \brief Constructs the \c %MorganNumberingGenerator instance.
			 */
			MorganNumberingGenerator();

			/**
			 * \brief Constructs the \c %MorganNumberingGenerator instance and performs a canonical numbering
			 *        of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perform the canonical numbering.
			 * \param numbering An array that contains the generated canonical atom numbering. The numbers
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the canonical number of an atom is accessible via its index).
			 */
			MorganNumberingGenerator(const MolecularGraph& molgraph, Util::STArray& numbering);

			/**
			 * \brief Performs a canonical numbering of the atoms in the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to perform the canonical numbering.
			 * \param numbering An array that contains the generated canonical atom numbering. The numbers
			 *         are stored in the same order as the atoms appear in the atom list of the molecular graph
			 *         (i.e. the canonical number of an atom is accessible via its index).
			 */
			void generate(const MolecularGraph& molgraph, Util::STArray& numbering);

		private:
			MorganNumberingGenerator(const MorganNumberingGenerator&);

			MorganNumberingGenerator& operator=(const MorganNumberingGenerator&);

			typedef std::pair<std::size_t, std::size_t> STPair;		 

			typedef std::vector<STPair> STPairArray;
			typedef std::vector<std::size_t> STArray;
			typedef std::vector<long> LArray;
			typedef std::vector<std::string> SArray;

			class NumberingState
			{

			public:
				NumberingState(STPairArray* sym_class_ids, SArray* symbols, 
							   LArray* charges, STArray* isotopes, Math::ULMatrix* bond_mtx): 
					symClassIDs(sym_class_ids), atomSymbols(symbols), 
					atomCharges(charges), atomIsotopes(isotopes), bondMatrix(bond_mtx) {}

				void generate(const MolecularGraph&, Util::STArray&);	

			private:
				NumberingState() {}

				void init(const MolecularGraph&);

				void perceiveSymClasses();

				void distributeNumbers(Util::STArray&);
				void distributeNumbers(std::size_t);

				void getNextAtomIndices(STArray&);

				void addListEntriesForAtom(std::size_t, std::size_t);

				void copy(NumberingState&);

				typedef STPairArray::const_iterator STPairArrayIterator;

				STPairArray*             symClassIDs;
				SArray*                  atomSymbols;
				LArray*                  atomCharges;
				STArray*                 atomIsotopes;
				Math::ULMatrix*          bondMatrix;
				const MolecularGraph*    molGraph;
				STPairArray              atomNumbering;
				STArray                  indexLookupTable;
				STArray                  fromList;
				STArray                  ringClosures;
				std::string              nodeValues;
				STArray                  lineValues;
				LArray                   modifications;
				STPairArrayIterator      lastSymClass;
				std::size_t              fromAtomNumber;
				std::size_t              centerAtomNumber;
				std::size_t              nextAtomNumber;
				bool                     sortRCList;
			};	

			STPairArray    symClassIDs;
			SArray         atomSymbols;
			LArray         atomCharges;
			STArray        atomIsotopes;
			Math::ULMatrix bondMatrix;
			NumberingState numbering;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MORGANNUMBERINGGENERATOR_HPP
