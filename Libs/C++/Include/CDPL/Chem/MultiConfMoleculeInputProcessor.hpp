/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MultiConfMoleculeInputProcessor.hpp 
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
 * \brief Definition of the class CDPL::Chem::MultiConfMoleculeInputProcessor.
 */

#ifndef CDPL_CHEM_MULTICONFMOLECULEINPUTPROCESSOR_HPP
#define CDPL_CHEM_MULTICONFMOLECULEINPUTPROCESSOR_HPP

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;

		/**
		 * \addtogroup CDPL_CHEM_DATA_IO_INTERFACES
		 * @{
		 */

		/**
		 * \brief MultiConfMoleculeInputProcessor.
		 */
		class CDPL_CHEM_API MultiConfMoleculeInputProcessor
		{

		public:
			/**	
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated 
			 *        \c %MultiConfMoleculeInputProcessor implementations.
			 */
			typedef boost::shared_ptr<MultiConfMoleculeInputProcessor> SharedPointer;

			/**
			 * \brief Virtual destructor.
			 *
			 * Destroys the \c %MultiConfMoleculeInputProcessor instance and frees all allocated resources.
			 */
			virtual ~MultiConfMoleculeInputProcessor()  {}

			/**
			 * \brief Performs initial tests and necessary setup tasks for a newly read-in potential multi-conformer molecule. 
			 * \param tgt_molgraph The concerned part of the read-in molecule that stores the conformations.
			 * \return \c true if \a tgt_molgraph is a possible multi-conformer molecule, and \c false otherwise.
			 */
			virtual bool init(MolecularGraph& tgt_molgraph) const = 0;

			/**
			 * \brief Checks if \a conf_molgraph represents a conformation of \a tgt_molgraph.
			 * \param tgt_molgraph The molecular graph for which to check if \a conf_molgraph represents a ne conformation.
			 * \param conf_molgraph A molecular graph representing a possible conformation of \a tgt_molgraph.
			 * \return \c false if \a conf_molgraph does not represent a conformer of \a tgt_molgraph, and \c true otherwise.
			 */
			virtual bool isConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const = 0;

			/**
			 * \brief Tries to append a new conformation to the list of previously read-in conformers of \a tgt_molgraph.
			 * \param tgt_molgraph The concerned part of target molecule that stores the read-in conformations.
			 * \param conf_molgraph A molecular graph storing the conformation to append.
			 * \return \c false if \a conf_molgraph does not represent a conformer of \a tgt_molgraph, and \c true if the
			 *         new conformation was successfully appended.
			 */
			virtual bool addConformation(MolecularGraph& tgt_molgraph, MolecularGraph& conf_molgraph) const = 0;
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MULTICONFMOLECULEINPUTPROCESSOR_HPP
