/* 
 * ForceFieldTypeExport.cpp 
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

#include "CDPL/ConfGen/ForceFieldType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct ForceFieldType {};
}


void CDPLPythonConfGen::exportForceFieldTypes()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<ForceFieldType, boost::noncopyable>("ForceFieldType", python::no_init)
		.def_readonly("MMFF94", &ConfGen::ForceFieldType::MMFF94)
		.def_readonly("MMFF94_NO_ESTAT", &ConfGen::ForceFieldType::MMFF94_NO_ESTAT)
		.def_readonly("MMFF94S", &ConfGen::ForceFieldType::MMFF94S)
		.def_readonly("MMFF94S_NO_ESTAT", &ConfGen::ForceFieldType::MMFF94S_NO_ESTAT)
		.def_readonly("MMFF94S_XOOP", &ConfGen::ForceFieldType::MMFF94S_XOOP)
		.def_readonly("MMFF94S_XOOP_NO_ESTAT", &ConfGen::ForceFieldType::MMFF94S_XOOP_NO_ESTAT)
		.def_readonly("MMFF94S_RTOR", &ConfGen::ForceFieldType::MMFF94S_RTOR)
		.def_readonly("MMFF94S_RTOR_NO_ESTAT", &ConfGen::ForceFieldType::MMFF94S_RTOR_NO_ESTAT)
		.def_readonly("MMFF94S_RTOR_XOOP", &ConfGen::ForceFieldType::MMFF94S_RTOR_XOOP)
		.def_readonly("MMFF94S_RTOR_XOOP_NO_ESTAT", &ConfGen::ForceFieldType::MMFF94S_RTOR_XOOP_NO_ESTAT);
}
