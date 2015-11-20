/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerFunctionExport.cpp 
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

#include "CDPL/Chem/AtomContainer.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


namespace
{

	MAKE_FUNCTION_WRAPPER1(std::size_t, getExplicitAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER2(std::size_t, getExplicitAtomCount, CDPL::Chem::AtomContainer&, unsigned int)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getExplicitChainAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getRingAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getAromaticAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getHeavyAtomCount, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getMaxReactionAtomMappingID, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getMaxComponentGroupID, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(long, calcFormalCharge, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(double, calcExplicitMass, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getNumConformations, CDPL::Chem::AtomContainer&)

	MAKE_FUNCTION_WRAPPER2(void, calcExplicitMassComposition, CDPL::Chem::AtomContainer&, CDPL::Chem::MassComposition&)
	MAKE_FUNCTION_WRAPPER2(void, buildExplicitElementHistogram, CDPL::Chem::AtomContainer&, CDPL::Chem::ElementHistogram&);
	MAKE_FUNCTION_WRAPPER2(void, calcGeometricalDistanceMatrix, CDPL::Chem::AtomContainer&, CDPL::Math::DMatrix&);
	MAKE_FUNCTION_WRAPPER1(double, calcGeometricalRadius, CDPL::Chem::AtomContainer&);
	MAKE_FUNCTION_WRAPPER1(double, calcGeometricalDiameter, CDPL::Chem::AtomContainer&);
	MAKE_FUNCTION_WRAPPER2(bool, hasCoordinates, CDPL::Chem::AtomContainer&, std::size_t);
	MAKE_FUNCTION_WRAPPER2(void, get2DCoordinates, CDPL::Chem::AtomContainer&, CDPL::Math::Vector2DArray&);
	MAKE_FUNCTION_WRAPPER2(void, get3DCoordinates, CDPL::Chem::AtomContainer&, CDPL::Math::Vector3DArray&);

	MAKE_FUNCTION_WRAPPER3(void, getConformationData, CDPL::Chem::AtomContainer&, std::size_t, CDPL::Math::Vector3DArray&);

	std::string buildExplicitMassCompositionStringWrapper(CDPL::Chem::AtomContainer& cntnr)
	{
		std::string str;

		buildExplicitMassCompositionString(cntnr, str);
		return str;
	}

	std::string buildExplicitMolecularFormulaWrapper(CDPL::Chem::AtomContainer& cntnr)
	{
		std::string str;

		buildExplicitMolecularFormula(cntnr, str);
		return str;
	}
}


void CDPLPythonChem::exportAtomContainerFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("getExplicitAtomCount", &getExplicitAtomCountWrapper1, python::arg("cntnr"));
	python::def("getExplicitAtomCount", &getExplicitAtomCountWrapper2, (python::arg("cntnr"), python::arg("type")));
	python::def("getExplicitChainAtomCount", &getExplicitChainAtomCountWrapper1, python::arg("cntnr"));
	python::def("getRingAtomCount", &getRingAtomCountWrapper1, python::arg("cntnr"));
	python::def("getAromaticAtomCount", &getAromaticAtomCountWrapper1, python::arg("cntnr"));
	python::def("getHeavyAtomCount", &getHeavyAtomCountWrapper1, python::arg("cntnr"));
	python::def("getMaxComponentGroupID", &getMaxComponentGroupIDWrapper1, python::arg("cntnr"));
	python::def("getMaxReactionAtomMappingID", &getMaxReactionAtomMappingIDWrapper1, python::arg("cntnr"));
	python::def("calcFormalCharge", &calcFormalChargeWrapper1, python::arg("cntnr"));
	python::def("calcExplicitMass", &calcExplicitMassWrapper1, python::arg("cntnr"));
	python::def("calcExplicitMassComposition", &calcExplicitMassCompositionWrapper2, (python::arg("cntnr"), python::arg("mass_comp")));
	python::def("buildExplicitMassCompositionString", &buildExplicitMassCompositionStringWrapper, python::arg("cntnr"));
	python::def("buildExplicitMolecularFormula", &buildExplicitMolecularFormulaWrapper, python::arg("cntnr"));
	python::def("buildExplicitElementHistogram", &buildExplicitElementHistogramWrapper2, (python::arg("cntnr"), python::arg("hist")));
	python::def("calcGeometricalDistanceMatrix", &calcGeometricalDistanceMatrixWrapper2, (python::arg("cntnr"), python::arg("mtx")));
	python::def("calcGeometricalRadius", &calcGeometricalRadiusWrapper1, python::arg("cntnr"));
	python::def("calcGeometricalDiameter", &calcGeometricalDiameterWrapper1, python::arg("cntnr"));
	python::def("hasCoordinates", &hasCoordinatesWrapper2, (python::arg("cntnr"), python::arg("dim")));
	python::def("get2DCoordinates", &get2DCoordinatesWrapper2, (python::arg("cntnr"),  python::arg("coords")));
	python::def("get3DCoordinates", &get3DCoordinatesWrapper2, (python::arg("cntnr"),  python::arg("coords")));
	python::def("set2DCoordinates", &Chem::set2DCoordinates, (python::arg("cntnr"), python::arg("coords")));
	python::def("set3DCoordinates", &Chem::set3DCoordinates, (python::arg("cntnr"), python::arg("coords")));
	python::def("setActiveConformation", &Chem::setActiveConformation, (python::arg("cntnr"), python::arg("conf_idx")));
	python::def("getConformationData", &getConformationDataWrapper3, (python::arg("cntnr"), python::arg("conf_idx"),python::arg("coords")));
	python::def("addConformationData", &Chem::addConformationData, (python::arg("cntnr"), python::arg("coords")));
	python::def("getNumConformations", &getNumConformationsWrapper1, python::arg("cntnr"));
}
