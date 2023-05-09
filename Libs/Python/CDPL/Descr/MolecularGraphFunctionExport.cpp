/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphFunctionExport.cpp 
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

#include "CDPL/Descr/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "FunctionExports.hpp"


void CDPLPythonDescr::exportMolecularGraphFunctions()
{
	using namespace boost;
	using namespace CDPL;

 	python::def("calcTopologicalRadius", &Descr::calcTopologicalRadius, python::arg("molgraph"));
	python::def("calcTopologicalDiameter", &Descr::calcTopologicalDiameter, python::arg("molgraph"));
	python::def("calcRingComplexity", &Descr::calcRingComplexity, python::arg("molgraph"));
	python::def("calcMolecularComplexity", &Descr::calcMolecularComplexity, python::arg("molgraph"));
	python::def("calcKierShape1", &Descr::calcKierShape1, python::arg("molgraph"));
	python::def("calcKierShape2", &Descr::calcKierShape2, python::arg("molgraph"));
	python::def("calcKierShape3", &Descr::calcKierShape3, python::arg("molgraph"));
	python::def("calcWienerIndex", &Descr::calcWienerIndex, python::arg("molgraph"));
	python::def("calcRandicIndex", &Descr::calcRandicIndex, python::arg("molgraph"));
	python::def("calcZagrebIndex1", &Descr::calcZagrebIndex1, python::arg("molgraph"));
	python::def("calcZagrebIndex2", &Descr::calcZagrebIndex2, python::arg("molgraph"));
	python::def("calcTotalWalkCount", &Descr::calcTotalWalkCount, python::arg("molgraph"));
}
