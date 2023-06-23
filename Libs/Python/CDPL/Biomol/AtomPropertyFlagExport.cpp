/* 
 * AtomPropertyFlagExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Biomol/AtomPropertyFlag.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomPropertyFlag {};
}


void CDPLPythonBiomol::exportAtomPropertyFlags()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomPropertyFlag, boost::noncopyable>("AtomPropertyFlag", python::no_init)
		.def_readonly("RESIDUE_CODE", &Biomol::AtomPropertyFlag::RESIDUE_CODE)
		.def_readonly("RESIDUE_SEQ_NO", &Biomol::AtomPropertyFlag::RESIDUE_SEQ_NO)
		.def_readonly("RESIDUE_INS_CODE", &Biomol::AtomPropertyFlag::RESIDUE_INS_CODE)
		.def_readonly("CHAIN_ID", &Biomol::AtomPropertyFlag::CHAIN_ID)
		.def_readonly("MODEL_NUMBER", &Biomol::AtomPropertyFlag::MODEL_NUMBER);
}
