/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionType.hpp 
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
 * \brief Definition of constants in namespace CDPL::ForceField::InteractionType.
 */

#ifndef CDPL_FORCEFIELD_INTERACTIONTYPE_HPP
#define CDPL_FORCEFIELD_INTERACTIONTYPE_HPP


namespace CDPL
{

    namespace ForceField
    {

		/**
		 * \addtogroup CDPL_FORCEFIELD_CONSTANTS
		 * @{
		 */

		/**
		 * \brief Provides flags for the specification of a set of force field interaction types.
		 */
		namespace InteractionType
		{

			const unsigned int NONE                   = 0x00;
			const unsigned int BOND_STRETCHING        = 0x01;
			const unsigned int ANGLE_BENDING          = 0x02;
			const unsigned int STRETCH_BEND           = 0x04;
			const unsigned int OUT_OF_PLANE_BENDING   = 0x08;
			const unsigned int TORSION                = 0x10;
			const unsigned int VAN_DER_WAALS          = 0x20;
			const unsigned int ELECTROSTATIC          = 0x40;
			const unsigned int ALL                    = 0x7f;
		}

		/**
		 * @}
		 */
    }
}

#endif // CDPL_FORCEFIELD_INTERACTIONTYPE_HPP
