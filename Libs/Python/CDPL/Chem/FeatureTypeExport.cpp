/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureTypeExport.cpp 
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

#include "CDPL/Chem/FeatureType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct FeatureType {};
}


void CDPLPythonChem::exportFeatureTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<FeatureType, boost::noncopyable>("FeatureType", python::no_init)
	.def_readonly("UNKNOWN", &Chem::FeatureType::UNKNOWN)
	.def_readonly("HYDROPHOBIC", &Chem::FeatureType::HYDROPHOBIC)
	.def_readonly("AROMATIC", &Chem::FeatureType::AROMATIC)
	.def_readonly("NEG_IONIZABLE", &Chem::FeatureType::NEG_IONIZABLE)
	.def_readonly("POS_IONIZABLE", &Chem::FeatureType::POS_IONIZABLE)
	.def_readonly("H_BOND_DONOR", &Chem::FeatureType::H_BOND_DONOR)
	.def_readonly("H_BOND_ACCEPTOR", &Chem::FeatureType::H_BOND_ACCEPTOR)
	.def_readonly("X_VOLUME", &Chem::FeatureType::X_VOLUME);
}
