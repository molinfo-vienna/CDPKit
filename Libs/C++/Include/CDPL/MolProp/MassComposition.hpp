/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MassComposition.hpp 
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
 * \brief Definition of the type CDPL::MolProp::MassComposition.
 */

#ifndef CDPL_MOLPROP_MASSCOMPOSITION_HPP
#define CDPL_MOLPROP_MASSCOMPOSITION_HPP

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/Util/Map.hpp"


namespace CDPL 
{

	namespace MolProp
	{

		/**
		 * \addtogroup CDPL_MOLPROP_DATA_STRUCTURES
		 * @{
		 */

		/**
		 * \brief A data type for the storage of mass percent compositions of chemical compounds.
		 *
		 * \c %MassComposition is an unique associative map where the keys specify the atom type
		 * (defined in namespace Chem::AtomType) of the chemical elements and the mapped floating-point
		 * values correspond to the percentage contribution of the elements to the total
		 * mass of the compound.
		 */
		class CDPL_MOLPROP_API MassComposition : public Util::Map<unsigned int, double, true>
		{

		  public:
			typedef boost::shared_ptr<MassComposition> SharedPointer;

		  private:
			const char* getClassName() const {
				return "MassComposition";
			}
		};

		/**
		 * @}
		 */
	}
}

#endif // CDPL_MOLPROP_MASSCOMPOSITION_HPP
