/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerFunctions.hpp 
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
 * \brief Declaration of functions that operate on MolProp::AtomContainer instances.
 */

#ifndef CDPL_MOLPROP_ATOMCONTAINERFUNCTIONS_HPP
#define CDPL_MOLPROP_ATOMCONTAINERFUNCTIONS_HPP

#include <string>

#include "CDPL/MolProp/APIPrefix.hpp"
#include "CDPL/MolProp/MassComposition.hpp"
#include "CDPL/MolProp/ElementHistogram.hpp"


namespace CDPL 
{

	namespace Chem 
	{
	
		class AtomContainer;
	}

	namespace MolProp
	{
		
		/**
		 * \addtogroup CDPL_MOLPROP_ATOM_CONTAINER_FUNCTIONS
		 * @{
		 */

		CDPL_MOLPROP_API double calcExplicitMass(const Chem::AtomContainer& cntnr);

		CDPL_MOLPROP_API void calcExplicitMassComposition(const Chem::AtomContainer& cntnr, MassComposition& mass_comp);

		CDPL_MOLPROP_API void buildExplicitMassCompositionString(const Chem::AtomContainer& cntnr, std::string& comp_str);

		CDPL_MOLPROP_API void buildExplicitMolecularFormula(const Chem::AtomContainer& cntnr, std::string& formula);

		CDPL_MOLPROP_API void buildExplicitElementHistogram(const Chem::AtomContainer& cntnr, ElementHistogram& hist, bool append = false);

		/**
		 * @}
		 */
	}
}

#endif // CDPL_MOLPROP_ATOMCONTAINERFUNCTIONS_HPP
 
