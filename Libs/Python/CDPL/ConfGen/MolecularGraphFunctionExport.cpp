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

#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Chem/CommonConnectedSubstructureSearch.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"

#include "FunctionExports.hpp"


void CDPLPythonConfGen::exportMolecularGraphFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("createFragmentLinkBondMask", &ConfGen::createFragmentLinkBondMask, 
                (python::arg("molgraph"), python::arg("bond_mask"), python::arg("reset") = true));
    python::def("createRotatableBondMask", 
                static_cast<std::size_t (*)(const Chem::MolecularGraph&, Util::BitSet&, bool, bool)>(&ConfGen::createRotatableBondMask), 
                (python::arg("molgraph"), python::arg("bond_mask"), python::arg("het_h_rotors"), python::arg("reset") = true));
    python::def("createRotatableBondMask", 
                static_cast<std::size_t (*)(const Chem::MolecularGraph&, const Util::BitSet&, Util::BitSet&, bool, bool)>(&ConfGen::createRotatableBondMask), 
                (python::arg("molgraph"), python::arg("excl_bond_mask"), python::arg("bond_mask"), python::arg("het_h_rotors"), 
                 python::arg("reset") = true));
    python::def("getRotatableBondCount", &ConfGen::getRotatableBondCount, (python::arg("molgraph"), python::arg("het_h_rotors")));
    python::def("perceiveFragmentType", &ConfGen::perceiveFragmentType, python::arg("molgraph"));
    python::def("parameterizeMMFF94Interactions", &ConfGen::parameterizeMMFF94Interactions, 
                (python::arg("molgraph"), python::arg("parameterizer"), python::arg("param_data"), python::arg("ff_type"), 
                 python::arg("strict"), python::arg("estat_de_const"), python::arg("estat_dist_expo")));
    python::def("setupFixedSubstructureData", static_cast<std::size_t (*)(const Chem::SubstructureSearch&, std::size_t,
                                                                          Chem::MolecularGraph&, Chem::Fragment&,
                                                                          Math::Vector3DArray*)>(&ConfGen::setupFixedSubstructureData),
                (python::arg("sub_search"), python::arg("max_num_matches"), python::arg("molgraph"), python::arg("fixed_substr"),
                 python::arg("fixed_substr_coords") = 0));
    python::def("setupFixedSubstructureData", static_cast<std::size_t (*)(const Chem::CommonConnectedSubstructureSearch&, std::size_t,
                                                                          Chem::MolecularGraph&, Chem::Fragment&,
                                                                          Math::Vector3DArray*)>(&ConfGen::setupFixedSubstructureData),
                (python::arg("sub_search"), python::arg("max_num_matches"), python::arg("molgraph"), python::arg("fixed_substr"),
                 python::arg("fixed_substr_coords") = 0));
}
