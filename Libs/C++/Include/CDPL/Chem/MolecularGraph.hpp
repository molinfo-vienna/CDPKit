/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraph.hpp 
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
 * \brief Definition of the class CDPL::Chem::MolecularGraph.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPH_HPP
#define CDPL_CHEM_MOLECULARGRAPH_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/BondContainer.hpp"
#include "CDPL/Base/PropertyContainer.hpp"


namespace CDPL 
{

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_STRUCTURE_INTERFACES
		 * @{
		 */

		/**
		 * \brief MolecularGraph.
		 */
		class CDPL_CHEM_API MolecularGraph : public AtomContainer, public BondContainer, public Base::PropertyContainer
		{


		public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %MolecularGraph instances.
			 */
			typedef boost::shared_ptr<MolecularGraph> SharedPointer;

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~MolecularGraph() {}

			/**
			 * \brief Creates a copy of the molecular graph.
			 * \return A smart pointer to the copy of the molecular graph.
			 */
			virtual SharedPointer clone() const = 0;

		protected:	
			/**
			 * \brief Assignment operator.
			 * \param molgraph The other \c MolecularGraph instance to copy.
			 * \return A reference to itself.
			 */
			MolecularGraph& operator=(const MolecularGraph& molgraph);
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MOLECULARGRAPH_HPP
