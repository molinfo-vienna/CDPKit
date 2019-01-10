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

#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Util/BitSet.hpp"

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
	MAKE_FUNCTION_WRAPPER1(std::size_t, getMaxAtomMappingID, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getMaxComponentGroupID, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(long, calcFormalCharge, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(double, calcExplicitMass, CDPL::Chem::AtomContainer&)
	MAKE_FUNCTION_WRAPPER1(std::size_t, getNumConformations, CDPL::Chem::AtomContainer&)

	MAKE_FUNCTION_WRAPPER2(void, calcExplicitMassComposition, CDPL::Chem::AtomContainer&, CDPL::Chem::MassComposition&)
	MAKE_FUNCTION_WRAPPER2(bool, hasCoordinates, CDPL::Chem::AtomContainer&, std::size_t);

	MAKE_FUNCTION_WRAPPER3(void, get3DCoordinates, CDPL::Chem::AtomContainer&, CDPL::Math::Vector3DArray&, bool);
	MAKE_FUNCTION_WRAPPER3(void, get2DCoordinates, CDPL::Chem::AtomContainer&, CDPL::Math::Vector2DArray&, bool);
	MAKE_FUNCTION_WRAPPER3(void, buildExplicitElementHistogram, CDPL::Chem::AtomContainer&, CDPL::Chem::ElementHistogram&, bool);

	MAKE_FUNCTION_WRAPPER4(std::size_t, buildAtomTypeMask, CDPL::Chem::AtomContainer&, CDPL::Util::BitSet&, unsigned int, bool);
	MAKE_FUNCTION_WRAPPER4(void, getConformation, CDPL::Chem::AtomContainer&, std::size_t, CDPL::Math::Vector3DArray&, bool);
	MAKE_FUNCTION_WRAPPER4(void, get3DCoordinates, CDPL::Chem::AtomContainer&, CDPL::Math::Vector3DArray&, const CDPL::Chem::Atom3DCoordinatesFunction&, bool);
	MAKE_FUNCTION_WRAPPER4(void, copyAtomsIf, CDPL::Chem::AtomContainer&, CDPL::Chem::Molecule&, const CDPL::Chem::AtomPredicate&, bool);
	MAKE_FUNCTION_WRAPPER4(void, copyAtomsIf, CDPL::Chem::AtomContainer&, CDPL::Chem::Fragment&, const CDPL::Chem::AtomPredicate&, bool);
	MAKE_FUNCTION_WRAPPER4(void, copyAtomsIfNot, CDPL::Chem::AtomContainer&, CDPL::Chem::Molecule&, const CDPL::Chem::AtomPredicate&, bool);
	MAKE_FUNCTION_WRAPPER4(void, copyAtomsIfNot, CDPL::Chem::AtomContainer&, CDPL::Chem::Fragment&, const CDPL::Chem::AtomPredicate&, bool);
	MAKE_FUNCTION_WRAPPER4(bool, insideBoundingBox, CDPL::Chem::AtomContainer&, const CDPL::Math::Vector3D&, const CDPL::Math::Vector3D&, const CDPL::Chem::Atom3DCoordinatesFunction&);
	MAKE_FUNCTION_WRAPPER4(bool, intersectsBoundingBox, CDPL::Chem::AtomContainer&, const CDPL::Math::Vector3D&, const CDPL::Math::Vector3D&, const CDPL::Chem::Atom3DCoordinatesFunction&);

	MAKE_FUNCTION_WRAPPER5(void, calcBoundingBox, CDPL::Chem::AtomContainer&, CDPL::Math::Vector3D&, CDPL::Math::Vector3D&, const CDPL::Chem::Atom3DCoordinatesFunction&, bool);


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
	python::def("getMaxAtomMappingID", &getMaxAtomMappingIDWrapper1, python::arg("cntnr"));
	python::def("calcFormalCharge", &calcFormalChargeWrapper1, python::arg("cntnr"));
	python::def("calcExplicitMass", &calcExplicitMassWrapper1, python::arg("cntnr"));
	python::def("calcExplicitMassComposition", &calcExplicitMassCompositionWrapper2, (python::arg("cntnr"), python::arg("mass_comp")));
	python::def("buildExplicitMassCompositionString", &buildExplicitMassCompositionStringWrapper, python::arg("cntnr"));
	python::def("buildExplicitMolecularFormula", &buildExplicitMolecularFormulaWrapper, python::arg("cntnr"));
	python::def("buildExplicitElementHistogram", &buildExplicitElementHistogramWrapper3, (python::arg("cntnr"), python::arg("hist"), python::arg("append") = false));
	python::def("hasCoordinates", &hasCoordinatesWrapper2, (python::arg("cntnr"), python::arg("dim")));
	python::def("get2DCoordinates", &get2DCoordinatesWrapper3, (python::arg("cntnr"), python::arg("coords"), python::arg("append") = false));
	python::def("set2DCoordinates", &Chem::set2DCoordinates, (python::arg("cntnr"), python::arg("coords")));
	python::def("transform2DCoordinates", &Chem::transform2DCoordinates, (python::arg("cntnr"), python::arg("mtx")));
	python::def("get3DCoordinates", &get3DCoordinatesWrapper3, (python::arg("cntnr"), python::arg("coords"), python::arg("append") = false));
	python::def("get3DCoordinates", &get3DCoordinatesWrapper4, (python::arg("cntnr"), python::arg("coords"), python::arg("coords_func"), python::arg("append") = false));
	python::def("set3DCoordinates", &Chem::set3DCoordinates, (python::arg("cntnr"), python::arg("coords")));
	python::def("transform3DCoordinates", &Chem::transform3DCoordinates, (python::arg("cntnr"), python::arg("mtx")));
	python::def("applyConformation", &Chem::applyConformation, (python::arg("cntnr"), python::arg("conf_idx")));
	python::def("getConformation", &getConformationWrapper4, (python::arg("cntnr"), python::arg("conf_idx"),python::arg("coords"), python::arg("append") = false));
	python::def("addConformation", &Chem::addConformation, (python::arg("cntnr"), python::arg("coords")));
	python::def("transformConformation", &Chem::transformConformation, (python::arg("cntnr"), python::arg("conf_idx"), python::arg("mtx")));
	python::def("transformConformations", &Chem::transformConformations, (python::arg("cntnr"), python::arg("mtx")));
	python::def("getNumConformations", &getNumConformationsWrapper1, python::arg("cntnr"));
	python::def("buildAtomTypeMask",  &buildAtomTypeMaskWrapper4, 
				(python::arg("cntnr"), python::arg("mask"), python::arg("type"), python::arg("reset") = true));
	python::def("copyAtomsIf", static_cast<void (*)(CDPL::Chem::AtomContainer&, CDPL::Chem::Molecule&, const CDPL::Chem::AtomPredicate&, bool)>(&copyAtomsIfWrapper4),
				(python::arg("cntnr"), python::arg("mol"), python::arg("pred"), python::arg("append") = false));
	python::def("copyAtomsIf", static_cast<void (*)(CDPL::Chem::AtomContainer&, CDPL::Chem::Fragment&, const CDPL::Chem::AtomPredicate&, bool)>(&copyAtomsIfWrapper4),
				(python::arg("cntnr"), python::arg("frag"), python::arg("pred"), python::arg("append") = false));
	python::def("copyAtomsIfNot", static_cast<void (*)(CDPL::Chem::AtomContainer&, CDPL::Chem::Molecule&, const CDPL::Chem::AtomPredicate&, bool)>(&copyAtomsIfNotWrapper4),
				(python::arg("cntnr"), python::arg("mol"), python::arg("pred"), python::arg("append") = false));
	python::def("copyAtomsIfNot", static_cast<void (*)(CDPL::Chem::AtomContainer&, CDPL::Chem::Fragment&, const CDPL::Chem::AtomPredicate&, bool)>(&copyAtomsIfNotWrapper4),
				(python::arg("cntnr"), python::arg("frag"), python::arg("pred"), python::arg("append") = false));

	python::def("calcBoundingBox", &calcBoundingBoxWrapper5, (python::arg("cntnr"), python::arg("min"), python::arg("max"), 
															  python::arg("coords_func"), (python::arg("reset") = true)));
	python::def("insideBoundingBox", &insideBoundingBoxWrapper4, (python::arg("cntnr"), python::arg("min"), python::arg("max"), 
																  python::arg("coords_func")));
	python::def("intersectsBoundingBox", &intersectsBoundingBoxWrapper4, (python::arg("cntnr"), python::arg("min"), 
																		  python::arg("max"), python::arg("coords_func")));
}
