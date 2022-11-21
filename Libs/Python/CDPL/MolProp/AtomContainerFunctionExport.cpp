/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerFunctionExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/MolProp/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomContainer.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


namespace
{

	MAKE_FUNCTION_WRAPPER1(std::size_t, getExplicitAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getExplicitChainAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getRingAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getAromaticAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getHeavyAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(long, getNetFormalCharge, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(double, calcExplicitMass, CDPL::Chem::AtomContainer&)

	MAKE_FUNCTION_WRAPPER2(void, calcExplicitMassComposition, CDPL::Chem::AtomContainer&, CDPL::MolProp::MassComposition&)
	MAKE_FUNCTION_WRAPPER2(bool, calcDipoleMoment, CDPL::Chem::AtomContainer&, CDPL::Math::Vector3D&);
	
	MAKE_FUNCTION_WRAPPER3(std::size_t, getExplicitAtomCount, CDPL::Chem::AtomContainer&, unsigned int, bool)
	MAKE_FUNCTION_WRAPPER3(void, buildExplicitElementHistogram, CDPL::Chem::AtomContainer&, CDPL::MolProp::ElementHistogram&, bool);
	MAKE_FUNCTION_WRAPPER3(bool, calcDipoleMoment, CDPL::Chem::AtomContainer&, const CDPL::Chem::Atom3DCoordinatesFunction&, CDPL::Math::Vector3D&);

	std::string buildExplicitMassCompositionStringWrapper(CDPL::Chem::AtomContainer& cntnr)
	{
		std::string str;

		CDPL::MolProp::	buildExplicitMassCompositionString(cntnr, str);
		return str;
	}

	std::string buildExplicitMolecularFormulaWrapper(CDPL::Chem::AtomContainer& cntnr)
	{
		std::string str;

		CDPL::MolProp::buildExplicitMolecularFormula(cntnr, str);
		return str;
	}
}


void CDPLPythonMolProp::exportAtomContainerFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("getExplicitAtomCount", &getExplicitAtomCountWrapper1, python::arg("cntnr"));
	python::def("getExplicitAtomCount", &getExplicitAtomCountWrapper3, (python::arg("cntnr"), python::arg("type"), python::arg("strict") = true));
	python::def("getExplicitChainAtomCount", &getExplicitChainAtomCountWrapper1, python::arg("cntnr"));
	python::def("getRingAtomCount", &getRingAtomCountWrapper1, python::arg("cntnr"));
	python::def("getAromaticAtomCount", &getAromaticAtomCountWrapper1, python::arg("cntnr"));
	python::def("getHeavyAtomCount", &getHeavyAtomCountWrapper1, python::arg("cntnr"));
	python::def("getNetFormalCharge", &getNetFormalChargeWrapper1, python::arg("cntnr"));
	python::def("calcExplicitMass", &calcExplicitMassWrapper1, python::arg("cntnr"));

	python::def("calcExplicitMassComposition", &calcExplicitMassCompositionWrapper2, (python::arg("cntnr"), python::arg("mass_comp")));
	python::def("buildExplicitMassCompositionString", &buildExplicitMassCompositionStringWrapper, python::arg("cntnr"));

	python::def("buildExplicitMolecularFormula", &buildExplicitMolecularFormulaWrapper, python::arg("cntnr"));
	python::def("buildExplicitElementHistogram", &buildExplicitElementHistogramWrapper3, (python::arg("cntnr"), python::arg("hist"), python::arg("append") = false));

	python::def("calcDipoleMoment", &calcDipoleMomentWrapper2, (python::arg("cntnr"), python::arg("moment")));
	python::def("calcDipoleMoment", &calcDipoleMomentWrapper3, (python::arg("cntnr"), python::arg("coords_func"), python::arg("moment")));
}
