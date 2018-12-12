/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPropertyFunctions.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphProperty.hpp"
#include "CDPL/Biomol/MolecularGraphPropertyDefault.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


using namespace CDPL; 


#define MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX) \
	void Biomol::set##FUNC_SUFFIX(Chem::MolecularGraph& molgraph, TYPE arg)	\
	{																	\
		molgraph.setProperty(MolecularGraphProperty::PROP_NAME, arg);	\
	}																	\
																		\
	bool Biomol::has##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)	\
	{																	\
		return molgraph.isPropertySet(MolecularGraphProperty::PROP_NAME); \
	}																	\
																		\
	void Biomol::clear##FUNC_SUFFIX(Chem::MolecularGraph& molgraph)		\
	{																	\
		molgraph.removeProperty(MolecularGraphProperty::PROP_NAME);		\
	}

#define MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(PROP_NAME, TYPE, FUNC_SUFFIX)	\
	TYPE Biomol::get##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)	\
	{																	\
		return molgraph.getProperty<TYPE>(MolecularGraphProperty::PROP_NAME); \
	}																	\
																		\
	MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)

#define MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(PROP_NAME, TYPE, FUNC_SUFFIX)	\
	TYPE Biomol::get##FUNC_SUFFIX(const Chem::MolecularGraph& molgraph)	\
	{																	\
		return molgraph.getPropertyOrDefault<TYPE>(MolecularGraphProperty::PROP_NAME, \
												   MolecularGraphPropertyDefault::PROP_NAME); \
	}																	\
																		\
	MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_COMMON(PROP_NAME, TYPE, FUNC_SUFFIX)


MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(RESIDUE_CODE, const std::string&, ResidueCode)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(RESIDUE_SEQUENCE_NUMBER, long, ResidueSequenceNumber)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(RESIDUE_INSERTION_CODE, char, ResidueInsertionCode)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(CHAIN_ID, const std::string&, ChainID)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS_WITH_DEF(MODEL_NUMBER, std::size_t, ModelNumber)
MAKE_MOLGRAPH_PROPERTY_FUNCTIONS(PDB_DATA, const Biomol::PDBData::SharedPointer&, PDBData)
