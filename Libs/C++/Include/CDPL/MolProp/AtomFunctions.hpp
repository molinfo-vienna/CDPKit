/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_MOLPROP_ATOMFUNCTIONS_HPP
#define CDPL_MOLPROP_ATOMFUNCTIONS_HPP

#include "CDPL/MolProp/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem 
	{

		class Atom;
		class MolecularGraph;
	}

	namespace MolProp
	{
		
		CDPL_MOLPROP_API double getHydrophobicity(const Chem::Atom& atom);

		CDPL_MOLPROP_API void setHydrophobicity(Chem::Atom& atom, double hyd);

		CDPL_MOLPROP_API void clearHydrophobicity(Chem::Atom& atom);	

		CDPL_MOLPROP_API bool hasHydrophobicity(const Chem::Atom& atom);


		CDPL_MOLPROP_API double getPEOECharge(const Chem::Atom& atom);

		CDPL_MOLPROP_API void setPEOECharge(Chem::Atom& atom, double charge);

		CDPL_MOLPROP_API void clearPEOECharge(Chem::Atom& atom);
	
		CDPL_MOLPROP_API bool hasPEOECharge(const Chem::Atom& atom);
	

		CDPL_MOLPROP_API double getHybridPolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);

		CDPL_MOLPROP_API double calcEffectivePolarizability(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, double damping = 0.75);
	}
}

#endif // CDPL_MOLPROP_ATOMFUNCTIONS_HPP
 
