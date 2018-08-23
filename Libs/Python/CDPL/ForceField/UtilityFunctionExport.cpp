/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctionExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/Math/Vector.hpp"

#include "FunctionExports.hpp"


namespace
{

	boost::python::tuple calcBondLengthsAndAngleCos(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
													const CDPL::Math::Vector3D& term_atom2_pos)
	{
		double bond_len1 = 0.0;
		double bond_len2 = 0.0;
		double ang_cos = CDPL::ForceField::calcBondLengthsAndAngleCos(term_atom1_pos, ctr_atom_pos, term_atom2_pos, bond_len1, bond_len2);

		return boost::python::make_tuple(bond_len1, bond_len2, ang_cos);
	}

	boost::python::tuple calcBondLengthsAndAngle(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
												 const CDPL::Math::Vector3D& term_atom2_pos)
	{
		double bond_len1 = 0.0;
		double bond_len2 = 0.0;
		double ang = CDPL::ForceField::calcBondLengthsAndAngle(term_atom1_pos, ctr_atom_pos, term_atom2_pos, bond_len1, bond_len2);

		return boost::python::make_tuple(bond_len1, bond_len2, ang);
	}
}


void CDPLPythonForceField::exportUtilityFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("calcSquaredDistance", &ForceField::calcSquaredDistance<double, Math::Vector3D>, 
				(python::arg("atom1_pos"), python::arg("atom2_pos")));
	python::def("calcDistance", &ForceField::calcDistance<double, Math::Vector3D>, 
				(python::arg("atom1_pos"), python::arg("atom2_pos")));
	python::def("calcBondLengthsAndAngleCos", &calcBondLengthsAndAngleCos, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos")));
	python::def("calcBondLengthsAndAngle", &calcBondLengthsAndAngle, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos")));
	python::def("calcBondAngleCos", &ForceField::calcBondAngleCos<double, Math::Vector3D>, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos")));
	python::def("calcBondAngle", &ForceField::calcBondAngle<double, Math::Vector3D>, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos")));
	python::def("calcOutOfPlaneAngle", &ForceField::calcOutOfPlaneAngle<double, Math::Vector3D>, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
				 python::arg("oop_atom_pos")));
	python::def("calcDihedralAngleCos", &ForceField::calcDihedralAngleCos<double, Math::Vector3D>, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom1_pos"), python::arg("ctr_atom2_pos"),
				 python::arg("term_atom2_pos")));

	python::def("calcDistanceDerivatives", &ForceField::calcDistanceDerivatives<double, Math::Vector3D, Math::Vector3D>, 
				(python::arg("atom1_pos"), python::arg("atom2_pos"), python::arg("atom1_deriv"), python::arg("atom2_deriv")));
	python::def("calcBondAngleCosDerivatives", &ForceField::calcBondAngleCosDerivatives<double, Math::Vector3D, Math::Vector3D>, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"),
				 python::arg("term_atom1_deriv"), python::arg("ctr_atom_deriv"), python::arg("term_atom2_deriv")));
	python::def("calcDihedralAngleCosDerivatives", &ForceField::calcDihedralAngleCosDerivatives<double, Math::Vector3D, Math::Vector3D>, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom1_pos"), python::arg("ctr_atom2_pos"), python::arg("term_atom2_pos"),
				 python::arg("term_atom1_deriv"), python::arg("ctr_atom1_deriv"), python::arg("ctr_atom2_deriv"), python::arg("term_atom2_deriv")));
	python::def("calcOutOfPlaneAngleCosDerivatives", &ForceField::calcOutOfPlaneAngleCosDerivatives<double, Math::Vector3D, Math::Vector3D>, 
				(python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), python::arg("oop_atom_pos"),
				 python::arg("term_atom1_deriv"), python::arg("ctr_atom_deriv"), python::arg("term_atom2_deriv"), python::arg("oop_atom_deriv")));
}
