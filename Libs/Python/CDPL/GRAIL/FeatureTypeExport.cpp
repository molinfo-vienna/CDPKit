/* 
 * FeatureTypeExport.cpp 
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

#include "CDPL/GRAIL/FeatureType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct FeatureType {};
}


void CDPLPythonGRAIL::exportFeatureTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<FeatureType, boost::noncopyable>("FeatureType", python::no_init)
		.def_readonly("UNKNOWN", &GRAIL::FeatureType::UNKNOWN)
		.def_readonly("HYDROPHOBIC", &GRAIL::FeatureType::HYDROPHOBIC)
		.def_readonly("AROMATIC", &GRAIL::FeatureType::AROMATIC)
		.def_readonly("NEGATIVE_IONIZABLE", &GRAIL::FeatureType::NEGATIVE_IONIZABLE)
		.def_readonly("POSITIVE_IONIZABLE", &GRAIL::FeatureType::POSITIVE_IONIZABLE)
		.def_readonly("H_BOND_DONOR", &GRAIL::FeatureType::H_BOND_DONOR)
		.def_readonly("H_BOND_ACCEPTOR", &GRAIL::FeatureType::H_BOND_ACCEPTOR)
		.def_readonly("HALOGEN_BOND_DONOR", &GRAIL::FeatureType::HALOGEN_BOND_DONOR)
		.def_readonly("HALOGEN_BOND_ACCEPTOR", &GRAIL::FeatureType::HALOGEN_BOND_ACCEPTOR)
		.def_readonly("EXCLUSION_VOLUME", &GRAIL::FeatureType::EXCLUSION_VOLUME)
		.def_readonly("MAX_TYPE", &GRAIL::FeatureType::MAX_TYPE)
		.def_readonly("H_BOND_DONOR_N", &GRAIL::FeatureType::H_BOND_DONOR_N)
	    .def_readonly("H_BOND_DONOR_N3", &GRAIL::FeatureType::H_BOND_DONOR_N3)
	    .def_readonly("H_BOND_DONOR_N2", &GRAIL::FeatureType::H_BOND_DONOR_N2)
	    .def_readonly("H_BOND_DONOR_Nar", &GRAIL::FeatureType::H_BOND_DONOR_Nar)
	    .def_readonly("H_BOND_DONOR_Nam", &GRAIL::FeatureType::H_BOND_DONOR_Nam)
	    .def_readonly("H_BOND_DONOR_Npl3", &GRAIL::FeatureType::H_BOND_DONOR_Npl3)
	    .def_readonly("H_BOND_DONOR_N4", &GRAIL::FeatureType::H_BOND_DONOR_N4)
	    .def_readonly("H_BOND_DONOR_O", &GRAIL::FeatureType::H_BOND_DONOR_O)
	    .def_readonly("H_BOND_DONOR_O3", &GRAIL::FeatureType::H_BOND_DONOR_O3)
	    .def_readonly("H_BOND_DONOR_S", &GRAIL::FeatureType::H_BOND_DONOR_S)
	    .def_readonly("H_BOND_DONOR_S3", &GRAIL::FeatureType::H_BOND_DONOR_S3)
	    .def_readonly("H_BOND_ACCEPTOR_N", &GRAIL::FeatureType::H_BOND_ACCEPTOR_N)
	    .def_readonly("H_BOND_ACCEPTOR_N3", &GRAIL::FeatureType::H_BOND_ACCEPTOR_N3)
	    .def_readonly("H_BOND_ACCEPTOR_N2", &GRAIL::FeatureType::H_BOND_ACCEPTOR_N2)
	    .def_readonly("H_BOND_ACCEPTOR_N1", &GRAIL::FeatureType::H_BOND_ACCEPTOR_N1)
	    .def_readonly("H_BOND_ACCEPTOR_Nar", &GRAIL::FeatureType::H_BOND_ACCEPTOR_Nar)
	    .def_readonly("H_BOND_ACCEPTOR_Npl3", &GRAIL::FeatureType::H_BOND_ACCEPTOR_Npl3)
	    .def_readonly("H_BOND_ACCEPTOR_O", &GRAIL::FeatureType::H_BOND_ACCEPTOR_O)
	    .def_readonly("H_BOND_ACCEPTOR_O3", &GRAIL::FeatureType::H_BOND_ACCEPTOR_O3)
	    .def_readonly("H_BOND_ACCEPTOR_O2", &GRAIL::FeatureType::H_BOND_ACCEPTOR_O2)
	    .def_readonly("H_BOND_ACCEPTOR_Oco2", &GRAIL::FeatureType::H_BOND_ACCEPTOR_Oco2)
	    .def_readonly("H_BOND_ACCEPTOR_S", &GRAIL::FeatureType::H_BOND_ACCEPTOR_S)
	    .def_readonly("H_BOND_ACCEPTOR_S3", &GRAIL::FeatureType::H_BOND_ACCEPTOR_S3)
	    .def_readonly("H_BOND_ACCEPTOR_S2", &GRAIL::FeatureType::H_BOND_ACCEPTOR_S2)
		.def_readonly("MAX_EXT_TYPE", &GRAIL::FeatureType::MAX_EXT_TYPE);
}
