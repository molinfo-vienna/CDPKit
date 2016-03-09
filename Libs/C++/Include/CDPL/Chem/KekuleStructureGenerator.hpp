/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * KekuleStructureGenerator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Chem::KekuleStructureGenerator.
 */

#ifndef CDPL_CHEM_KEKULESTRUCTUREGENERATOR_HPP
#define CDPL_CHEM_KEKULESTRUCTUREGENERATOR_HPP

#include <cstddef>
#include <vector>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;

		/**
		 * \addtogroup CDPL_CHEM_BOND_ORDERS
		 * @{
		 */

		/**
		 * \brief KekuleStructureGenerator.
		 */
		class CDPL_CHEM_API KekuleStructureGenerator 
		{

		public:
			/**
			 * \brief Constructs the \c %KekuleStructureGenerator instance.
			 */
			KekuleStructureGenerator();

			/**
			 * \brief Constructs the \c %KekuleStructureGenerator instance and generates an alternating
			 *        single/double bond pattern for all undefined bonds of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the alternating single/double bond pattern.
			 * \param orders An array containing the assigned bond orders. The orders are stored in the same sequence
			 *         as the bonds appear in the input molecular graph, i.e. the order of a particular bond is
			 *         accessible via its index in the molecular graph.
			 */
			KekuleStructureGenerator(const MolecularGraph& molgraph, Util::STArray& orders);

			/**
			 * \brief Generates an alternating single/double bond pattern for all undefined bonds of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the alternating single/double bond pattern.
			 * \param orders An array containing the assigned bond orders. The orders are stored in the same sequence
			 *         as the bonds appear in the input molecular graph, i.e. the order of a particular bond is
			 *         accessible via its index in the molecular graph.
			 */
			void generate(const MolecularGraph& molgraph, Util::STArray& orders);

		private:
			/** \cond CDPL_PRIVATE_SECTION_DOC */
		
			void init(const MolecularGraph& molgraph, Util::STArray& orders);

			void defineNbrBondOrders(const Atom& atom);
			void getConnectedUndefBonds(const Atom& atom);

			typedef std::vector<const Bond*> BondList;

			const MolecularGraph*  molGraph;
			std::size_t            startAtomIdx;
			Util::BitSet           defOrderMask;
			BondList               conctdUndefBonds;

			/** \endcond */
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_KEKULESTRUCTUREGENERATOR_HPP
 
