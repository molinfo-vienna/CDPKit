/* 
 * BondContainerFunctionExport.cpp 
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

#include "CDPL/MolProp/BondContainerFunctions.hpp"
#include "CDPL/Chem/BondContainer.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


namespace
{

    MAKE_FUNCTION_WRAPPER1(std::size_t, getExplicitBondCount, CDPL::Chem::BondContainer&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getExplicitHydrogenBondCount, CDPL::Chem::BondContainer&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getExplicitChainBondCount, CDPL::Chem::BondContainer&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getRingBondCount, CDPL::Chem::BondContainer&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getAromaticBondCount, CDPL::Chem::BondContainer&);
    MAKE_FUNCTION_WRAPPER1(std::size_t, getHeavyBondCount, CDPL::Chem::BondContainer&);

    MAKE_FUNCTION_WRAPPER3(std::size_t, getExplicitBondCount, CDPL::Chem::BondContainer&, std::size_t, bool);
}


void CDPLPythonMolProp::exportBondContainerFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("getExplicitBondCount", &getExplicitBondCountWrapper1, python::arg("cntnr"));
    python::def("getExplicitBondCount", &getExplicitBondCountWrapper3, (python::arg("cntnr"), python::arg("order"), python::arg("inc_aro") = true));
    python::def("getExplicitHydrogenBondCount", &getExplicitHydrogenBondCountWrapper1, python::arg("cntnr"));
    python::def("getExplicitChainBondCount", &getExplicitChainBondCountWrapper1, python::arg("cntnr"));
    python::def("getRingBondCount", &getRingBondCountWrapper1, python::arg("cntnr"));
    python::def("getAromaticBondCount", &getAromaticBondCountWrapper1, python::arg("cntnr"));
    python::def("getHeavyBondCount", &getHeavyBondCountWrapper1, python::arg("cntnr"));
}
