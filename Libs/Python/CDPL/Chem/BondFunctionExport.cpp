/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondFunctionExport.cpp 
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

#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


#define MAKE_BOND_FUNC_WRAPPERS(TYPE, FUNC_SUFFIX)                 \
TYPE get##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond)             \
{                                                                  \
	return get##FUNC_SUFFIX(bond);                                 \
}                                                                  \
                                                                   \
bool has##FUNC_SUFFIX##Wrapper(CDPL::Chem::Bond& bond)             \
{                                                                  \
	return has##FUNC_SUFFIX(bond);                                 \
}

#define EXPORT_BOND_FUNCS(FUNC_SUFFIX, ARG_NAME)                                                             \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("bond"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME))); 

#define EXPORT_BOND_FUNCS_COPY_REF(FUNC_SUFFIX, ARG_NAME)                                                    \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_value_policy<python::copy_const_reference>());                                    \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("bond"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME))); 

#define EXPORT_BOND_FUNCS_COPY_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                 \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_value_policy<python::copy_const_reference,                                        \
			python::with_custodian_and_ward_postcall<0, 1> >());                                             \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("bond"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME)),       \
			python::with_custodian_and_ward<1, 2>());                                                            

#define EXPORT_BOND_FUNCS_INT_REF_CW(FUNC_SUFFIX, ARG_NAME)                                                  \
python::def("get"#FUNC_SUFFIX, &get##FUNC_SUFFIX##Wrapper, python::arg("bond"),                              \
            python::return_internal_reference<1>());                                                         \
python::def("has"#FUNC_SUFFIX, &has##FUNC_SUFFIX##Wrapper, python::arg("bond"));                             \
python::def("clear"#FUNC_SUFFIX, &Chem::clear##FUNC_SUFFIX, python::arg("bond"));                            \
python::def("set"#FUNC_SUFFIX, &Chem::set##FUNC_SUFFIX, (python::arg("bond"), python::arg(#ARG_NAME)),       \
			python::with_custodian_and_ward<1, 2>());  


namespace
{

	typedef CDPL::Chem::MatchExpression<CDPL::Chem::Bond, CDPL::Chem::MolecularGraph>::SharedPointer MatchExpressionPtr;
	typedef const MatchExpressionPtr& MatchExpressionPtrRef;

	MAKE_BOND_FUNC_WRAPPERS(const std::string&, MatchExpressionString)
	MAKE_BOND_FUNC_WRAPPERS(std::size_t, Order)
	MAKE_BOND_FUNC_WRAPPERS(bool, AromaticityFlag)
	MAKE_BOND_FUNC_WRAPPERS(bool, RingFlag)
	MAKE_BOND_FUNC_WRAPPERS(unsigned int, CIPConfiguration)
	MAKE_BOND_FUNC_WRAPPERS(unsigned int, SybylType)
	MAKE_BOND_FUNC_WRAPPERS(bool, StereoCenterFlag)
	MAKE_BOND_FUNC_WRAPPERS(const CDPL::Chem::StereoDescriptor&, StereoDescriptor)
	MAKE_BOND_FUNC_WRAPPERS(MatchExpressionPtrRef, MatchExpression)
	MAKE_BOND_FUNC_WRAPPERS(unsigned int, ReactionCenterStatus)
	MAKE_BOND_FUNC_WRAPPERS(unsigned int, Direction)
	MAKE_BOND_FUNC_WRAPPERS(unsigned int, 2DStereoFlag)

	MAKE_FUNCTION_WRAPPER1(const CDPL::Chem::MatchConstraintList::SharedPointer&, getMatchConstraints, CDPL::Chem::Bond&)
	MAKE_FUNCTION_WRAPPER1(bool, hasMatchConstraints, CDPL::Chem::Bond&)
	MAKE_FUNCTION_WRAPPER1(bool, isHydrogenBond, CDPL::Chem::Bond&)

	MAKE_FUNCTION_WRAPPER2(bool, isInRing, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getSizeOfSmallestContainingFragment, CDPL::Chem::Bond&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getSizeOfLargestContainingFragment, CDPL::Chem::Bond&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getNumContainingFragments, CDPL::Chem::Bond&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER2(MatchExpressionPtr, buildMatchExpression, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(unsigned int, calcCIPConfiguration, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(std::size_t, getNumContainingSSSRRings, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);
	MAKE_FUNCTION_WRAPPER2(unsigned int, perceiveSybylType, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&);

	MAKE_FUNCTION_WRAPPER3(void, getContainingFragments, CDPL::Chem::Bond&, CDPL::Chem::FragmentList&, CDPL::Chem::FragmentList&);
	MAKE_FUNCTION_WRAPPER3(double, calcPolarizability, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, double);
	MAKE_FUNCTION_WRAPPER3(bool, isInRingOfSize, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, std::size_t);
	MAKE_FUNCTION_WRAPPER3(bool, isInFragmentOfSize, CDPL::Chem::Bond&, CDPL::Chem::FragmentList&, std::size_t);
	MAKE_FUNCTION_WRAPPER3(unsigned int, calcCIPConfiguration, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, const CDPL::Chem::AtomPriorityFunction&);

	MAKE_FUNCTION_WRAPPER4(bool, isStereoCenter, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, std::size_t, bool);
	MAKE_FUNCTION_WRAPPER4(unsigned int, calcBondConfiguration, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, const CDPL::Chem::StereoDescriptor&, const CDPL::Math::Vector3DArray&);
	MAKE_FUNCTION_WRAPPER4(bool, isRotatable, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, bool, bool);

	MAKE_FUNCTION_WRAPPER5(CDPL::Chem::StereoDescriptor, calcStereoDescriptor, CDPL::Chem::Bond&, CDPL::Chem::MolecularGraph&, std::size_t, std::size_t, bool);

	std::string buildMatchExpressionStringWrapper(CDPL::Chem::Bond& bond, CDPL::Chem::MolecularGraph& molgraph)
	{
		std::string str;

		buildMatchExpressionString(bond, molgraph, str);
		return str;
	}
}


void CDPLPythonChem::exportBondFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("isHydrogenBond", &isHydrogenBondWrapper1, python::arg("bond"));

	python::def("getSizeOfSmallestContainingFragment", &getSizeOfSmallestContainingFragmentWrapper2,
				(python::arg("bond"), python::arg("frag_list")));
	python::def("getSizeOfLargestContainingFragment", &getSizeOfLargestContainingFragmentWrapper2,
				(python::arg("bond"), python::arg("frag_list")));
	python::def("getNumContainingFragments", &getNumContainingFragmentsWrapper2,
				(python::arg("bond"), python::arg("frag_list")));
	python::def("buildMatchExpression", &buildMatchExpressionWrapper2, 
				(python::arg("bond"), python::arg("molgraph")),
				python::with_custodian_and_ward_postcall<0, 1>());
	python::def("isInRing", &isInRingWrapper2, (python::arg("bond"), python::arg("molgraph")));

	python::def("calcCIPConfiguration", &calcCIPConfigurationWrapper2, 
				(python::arg("bond"), python::arg("molgraph")));
	python::def("getNumContainingSSSRRings", &getNumContainingSSSRRingsWrapper2, 
				(python::arg("bond"), python::arg("molgraph")));
	python::def("perceiveSybylType", &perceiveSybylTypeWrapper2,
				(python::arg("bond"), python::arg("molgraph")));

	python::def("calcCIPConfiguration", &calcCIPConfigurationWrapper3, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("cip_pri_func")));
	python::def("getContainingFragments", &getContainingFragmentsWrapper3,
				(python::arg("bond"), python::arg("frag_list"), python::arg("cont_frag_list")),
				python::with_custodian_and_ward<3, 2>());
	python::def("calcPolarizability", &calcPolarizabilityWrapper3, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("damping") = 0.75));
	python::def("isInRingOfSize", &isInRingOfSizeWrapper3,
				(python::arg("bond"), python::arg("molgraph"), python::arg("size")));
	python::def("isInFragmentOfSize", &isInFragmentOfSizeWrapper3, 
				(python::arg("bond"), python::arg("frag_list"), python::arg("size")));

	python::def("isStereoCenter", &isStereoCenterWrapper4, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("min_ring_size") = 8, python::arg("check_cip_sym") = true));
	python::def("calcBondConfiguration", &calcBondConfigurationWrapper4,
				(python::arg("bond"), python::arg("molgraph"), python::arg("descr"), python::arg("coords")));
	python::def("isRotatable", &isRotatableWrapper4, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("inc_h_rotors"), python::arg("inc_amide_bonds")));

	python::def("calcStereoDescriptor", &calcStereoDescriptorWrapper5, 
				(python::arg("bond"), python::arg("molgraph"), python::arg("dim") = 1, 
				 python::arg("min_ring_size") = 8, python::arg("check_order") = true));

	python::def("buildMatchExpressionString", &buildMatchExpressionStringWrapper,
				(python::arg("bond"), python::arg("molgraph")));

	python::def("getMatchConstraints", &getMatchConstraintsWrapper1, python::arg("bond"),
				python::return_value_policy<python::copy_const_reference, python::with_custodian_and_ward_postcall<0, 1> >());
	python::def("hasMatchConstraints", &hasMatchConstraintsWrapper1, python::arg("bond"));
	python::def("setMatchConstraints", &Chem::setMatchConstraints, 
				(python::arg("bond"), python::arg("constr")));
	python::def("clearMatchConstraints", &Chem::clearMatchConstraints, python::arg("bond"));

	EXPORT_BOND_FUNCS_COPY_REF(MatchExpressionString, expr_str)
	EXPORT_BOND_FUNCS(Order, order)
	EXPORT_BOND_FUNCS(AromaticityFlag, aromatic)
	EXPORT_BOND_FUNCS(RingFlag, in_ring)
	EXPORT_BOND_FUNCS(CIPConfiguration, config)
	EXPORT_BOND_FUNCS(SybylType, type)
	EXPORT_BOND_FUNCS(StereoCenterFlag, is_center)
	EXPORT_BOND_FUNCS(Direction, dir)
    EXPORT_BOND_FUNCS_INT_REF_CW(StereoDescriptor, descr)
    EXPORT_BOND_FUNCS_COPY_REF_CW(MatchExpression, expr)
	EXPORT_BOND_FUNCS(ReactionCenterStatus, status)
	EXPORT_BOND_FUNCS(2DStereoFlag, flag)
}
