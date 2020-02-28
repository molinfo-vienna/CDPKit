/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphMatchConstraint.hpp 
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
 * \brief Definition of constants in namespace CDPL::Chem::MolecularGraphMatchConstraint.
 */

#ifndef CDPL_CHEM_MOLECULARGRAPHMATCHCONSTRAINT_HPP
#define CDPL_CHEM_MOLECULARGRAPHMATCHCONSTRAINT_HPP


namespace CDPL
{

	namespace Chem
	{

		/**
		 * \addtogroup CDPL_CHEM_CONSTANTS
		 * @{
		 */

		/**
		 * \brief Provides numerical identifiers for built-in Chem::MolecularGraph matching constraints.
		 */
		namespace MolecularGraphMatchConstraint
		{

			/**
			 * \brief Specifies a constraint which requires the target olecular graph to fulfill additional contraints
			 *        specified by a Chem::MatchConstraintList object.
			 */
			const unsigned int CONSTRAINT_LIST    = 0;

			/**
			 * \brief Specifies a constraint which requires the target molecular graph to match any component level groupings
			 *        defined by the query.
			 * 
			 * Component level groupings specify whether the components of a query molecular graph have to be matched by a single
			 * target molecular graph component or by different components of the target.
			 * <em>Daylight SMARTS</em> patterns [\ref SMARTS] allow to specify component groupings by parentheses that
			 * enclose those components of the query which have to be part of the same target molecular graph component.
			 */
			const unsigned int COMPONENT_GROUPING = 1;
		}

		/**
		 * @}
		 */
	}
}

#endif // CDPL_CHEM_MOLECULARGRAPHMATCHCONSTRAINT_HPP
