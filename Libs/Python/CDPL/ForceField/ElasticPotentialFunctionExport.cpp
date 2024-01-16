/* 
 * ElasticPotentialFunctionExport.cpp 
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

#include "CDPL/ForceField/ElasticPotentialFunctions.hpp"
#include "CDPL/ForceField/ElasticPotentialData.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "FunctionExports.hpp"


namespace
{

    double calcElasticPotentialEnergy1(const CDPL::ForceField::ElasticPotentialData& data, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcElasticPotentialEnergy<double>(data.getElementsBegin(), data.getElementsEnd(), coords);
    }

    double calcElasticPotentialEnergy2(const CDPL::ForceField::ElasticPotential& pot, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcElasticPotentialEnergy<double>(pot, coords);
    }

    double calcElasticPotentialEnergy3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, 
                                           double force_const, double ref_length)
    {
        return CDPL::ForceField::calcElasticPotentialEnergy<double>(atom1_pos, atom2_pos, force_const, ref_length);
    }
    
    double calcElasticPotentialGradient1(const CDPL::ForceField::ElasticPotentialData& data, const CDPL::Math::Vector3DArray& coords, 
                                             CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcElasticPotentialGradient<double>(data.getElementsBegin(), data.getElementsEnd(), coords, grad);
    }

    double calcElasticPotentialGradient2(const CDPL::ForceField::ElasticPotential& pot, const CDPL::Math::Vector3DArray& coords, 
                                             CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcElasticPotentialGradient<double>(pot, coords, grad);
    }

    double calcElasticPotentialGradient3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, 
                                             CDPL::Math::Vector3D& atom1_grad, CDPL::Math::Vector3D& atom2_grad, 
                                             double force_const, double ref_length)
    {
        return CDPL::ForceField::calcElasticPotentialGradient(atom1_pos, atom2_pos, atom1_grad, atom2_grad, force_const, ref_length);
    }
}


void CDPLPythonForceField::exportElasticPotentialFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("calcElasticPotentialEnergy", &calcElasticPotentialEnergy1,
                (python::arg("data"), python::arg("coords")));
    python::def("calcElasticPotentialEnergy", &calcElasticPotentialEnergy2,
                (python::arg("pot"), python::arg("coords")));
    python::def("calcElasticPotentialEnergy", &calcElasticPotentialEnergy3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"), python::arg("force_const"), python::arg("ref_length")));
    python::def("calcElasticPotentialGradient", &calcElasticPotentialGradient1,
                (python::arg("data"), python::arg("coords"), python::arg("grad")));
    python::def("calcElasticPotentialGradient", &calcElasticPotentialGradient2,
                (python::arg("pot"), python::arg("coords"), python::arg("grad")));
    python::def("calcElasticPotentialGradient", &calcElasticPotentialGradient3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"),
                 python::arg("atom1_grad"), python::arg("atom2_grad"),
                 python::arg("force_const"), python::arg("ref_length")));
}
