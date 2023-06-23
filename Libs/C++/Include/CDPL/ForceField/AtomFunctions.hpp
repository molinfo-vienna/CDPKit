/* 
 * AtomFunctions.hpp 
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
 * \brief Declaration of functions that operate on Chem::Atom instances.
 */

#ifndef CDPL_FORCEFIELD_ATOMFUNCTIONS_HPP
#define CDPL_FORCEFIELD_ATOMFUNCTIONS_HPP

#include <string>

#include "CDPL/ForceField/APIPrefix.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class Atom;
		class MolecularGraph;
	}

	namespace ForceField 
	{

		CDPL_FORCEFIELD_API const std::string& getMMFF94SymbolicType(const Chem::Atom& atom);

		CDPL_FORCEFIELD_API void setMMFF94SymbolicType(Chem::Atom& atom, const std::string& type);

		CDPL_FORCEFIELD_API void clearMMFF94SymbolicType(Chem::Atom& atom);

		CDPL_FORCEFIELD_API bool hasMMFF94SymbolicType(const Chem::Atom& atom);


		CDPL_FORCEFIELD_API unsigned int getMMFF94NumericType(const Chem::Atom& atom);

		CDPL_FORCEFIELD_API void setMMFF94NumericType(Chem::Atom& atom, unsigned int type);

		CDPL_FORCEFIELD_API void clearMMFF94NumericType(Chem::Atom& atom);

		CDPL_FORCEFIELD_API bool hasMMFF94NumericType(const Chem::Atom& atom);


		CDPL_FORCEFIELD_API double getMMFF94Charge(const Chem::Atom& atom);

		CDPL_FORCEFIELD_API void setMMFF94Charge(Chem::Atom& atom, double charge);

		CDPL_FORCEFIELD_API void clearMMFF94Charge(Chem::Atom& atom);

		CDPL_FORCEFIELD_API bool hasMMFF94Charge(const Chem::Atom& atom);

		CDPL_FORCEFIELD_API bool hasMMFF94Charge(const Chem::Atom& atom);


		CDPL_FORCEFIELD_API unsigned int getUFFType(const Chem::Atom& atom);

		CDPL_FORCEFIELD_API void setUFFType(Chem::Atom& atom, unsigned int type);

		CDPL_FORCEFIELD_API void clearUFFType(Chem::Atom& atom);

		CDPL_FORCEFIELD_API bool hasUFFType(const Chem::Atom& atom);

		CDPL_FORCEFIELD_API unsigned int perceiveUFFType(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph);
	}
}

#endif // CDPL_FORCEFIELD_ATOMFUNCTIONS_HPP
 
