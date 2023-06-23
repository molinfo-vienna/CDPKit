/* 
 * MMFF94GradientFunctionExport.cpp 
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

#include "CDPL/ForceField/MMFF94GradientFunctions.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionData.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionData.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionData.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionData.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "FunctionExports.hpp"


namespace
{

    double calcMMFF94BondStretchingGradient1(const CDPL::ForceField::MMFF94BondStretchingInteractionData& ia_data, const CDPL::Math::Vector3DArray& coords, 
                                             CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94BondStretchingGradient<double>(ia_data.getElementsBegin(), ia_data.getElementsEnd(), coords, grad);
    }

    double calcMMFF94BondStretchingGradient2(const CDPL::ForceField::MMFF94BondStretchingInteraction& iaction, const CDPL::Math::Vector3DArray& coords, 
                                             CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94BondStretchingGradient<double>(iaction, coords, grad);
    }

    double calcMMFF94BondStretchingGradient3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, 
                                             CDPL::Math::Vector3D& atom1_grad, CDPL::Math::Vector3D& atom2_grad, 
                                             double force_const, double ref_length)
    {
        return CDPL::ForceField::calcMMFF94BondStretchingGradient(atom1_pos, atom2_pos, atom1_grad, atom2_grad, force_const, ref_length);
    }

    double calcMMFF94AngleBendingGradient1(const CDPL::ForceField::MMFF94AngleBendingInteractionData& ia_data, const CDPL::Math::Vector3DArray& coords, 
                                           CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94AngleBendingGradient<double>(ia_data.getElementsBegin(), ia_data.getElementsEnd(), coords, grad);
    }

    double calcMMFF94AngleBendingGradient2(const CDPL::ForceField::MMFF94AngleBendingInteraction& iaction, const CDPL::Math::Vector3DArray& coords, 
                                           CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94AngleBendingGradient<double>(iaction, coords, grad);
    }

    double calcMMFF94AngleBendingGradient3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                           const CDPL::Math::Vector3D& term_atom2_pos, CDPL::Math::Vector3D& term_atom1_grad,
                                           CDPL::Math::Vector3D& ctr_atom_grad, CDPL::Math::Vector3D& term_atom2_grad, 
                                           bool linear, double force_const, double ref_angle)
    {
        return CDPL::ForceField::calcMMFF94AngleBendingGradient(term_atom1_pos, ctr_atom_pos, term_atom2_pos, 
                                                                term_atom1_grad, ctr_atom_grad, term_atom2_grad, 
                                                                linear, force_const, ref_angle);
    }

    double calcMMFF94StretchBendGradient1(const CDPL::ForceField::MMFF94StretchBendInteractionData& ia_data, const CDPL::Math::Vector3DArray& coords, 
                                          CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94StretchBendGradient<double>(ia_data.getElementsBegin(), ia_data.getElementsEnd(), coords, grad);
    }

    double calcMMFF94StretchBendGradient2(const CDPL::ForceField::MMFF94StretchBendInteraction& iaction, const CDPL::Math::Vector3DArray& coords, 
                                          CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94StretchBendGradient<double>(iaction, coords, grad);
    }

    double calcMMFF94StretchBendGradient3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                          const CDPL::Math::Vector3D& term_atom2_pos, CDPL::Math::Vector3D& term_atom1_grad,
                                          CDPL::Math::Vector3D& ctr_atom_grad, CDPL::Math::Vector3D& term_atom2_grad,
                                          double ijk_force_const, double kji_force_const, double ref_angle, double ref_length1, double ref_length2)
    {
        return CDPL::ForceField::calcMMFF94StretchBendGradient(term_atom1_pos, ctr_atom_pos, term_atom2_pos, 
                                                               term_atom1_grad, ctr_atom_grad, term_atom2_grad,
                                                               ijk_force_const, kji_force_const,
                                                               ref_angle, ref_length1, ref_length2);
    }

    double calcMMFF94OutOfPlaneBendingGradient1(const CDPL::ForceField::MMFF94OutOfPlaneBendingInteractionData& ia_data, const CDPL::Math::Vector3DArray& coords, 
                                                CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94OutOfPlaneBendingGradient<double>(ia_data.getElementsBegin(), ia_data.getElementsEnd(), coords, grad);
    }

    double calcMMFF94OutOfPlaneBendingGradient2(const CDPL::ForceField::MMFF94OutOfPlaneBendingInteraction& iaction, const CDPL::Math::Vector3DArray& coords, 
                                                CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94OutOfPlaneBendingGradient<double>(iaction, coords, grad);
    }

    double calcMMFF94OutOfPlaneBendingGradient3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                                const CDPL::Math::Vector3D& term_atom2_pos, const CDPL::Math::Vector3D& oop_atom_pos, 
                                                CDPL::Math::Vector3D& term_atom1_grad, CDPL::Math::Vector3D& ctr_atom_grad, 
                                                CDPL::Math::Vector3D& term_atom2_grad, CDPL::Math::Vector3D& oop_atom_grad, 
                                                double force_const)
    {
        return CDPL::ForceField::calcMMFF94OutOfPlaneBendingGradient(term_atom1_pos, ctr_atom_pos, term_atom2_pos, oop_atom_pos, 
                                                                     term_atom1_grad, ctr_atom_grad, term_atom2_grad, oop_atom_grad, 
                                                                     force_const);
    }

    double calcMMFF94TorsionGradient1(const CDPL::ForceField::MMFF94TorsionInteractionData& ia_data, const CDPL::Math::Vector3DArray& coords, 
                                      CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94TorsionGradient<double>(ia_data.getElementsBegin(), ia_data.getElementsEnd(), coords, grad);
    }

    double calcMMFF94TorsionGradient2(const CDPL::ForceField::MMFF94TorsionInteraction& iaction, const CDPL::Math::Vector3DArray& coords, 
                                      CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94TorsionGradient<double>(iaction, coords, grad);
    }

    double calcMMFF94TorsionGradient3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom1_pos, 
                                      const CDPL::Math::Vector3D& ctr_atom2_pos, const CDPL::Math::Vector3D& term_atom2_pos, 
                                      CDPL::Math::Vector3D& term_atom1_grad, CDPL::Math::Vector3D& ctr_atom1_grad, 
                                      CDPL::Math::Vector3D& ctr_atom2_grad, CDPL::Math::Vector3D& term_atom2_grad, 
                                      double tor_param1, double tor_param2, double tor_param3)
    {
        return CDPL::ForceField::calcMMFF94TorsionGradient(term_atom1_pos, ctr_atom1_pos, ctr_atom2_pos, term_atom2_pos, 
                                                           term_atom1_grad, ctr_atom1_grad, ctr_atom2_grad, term_atom2_grad, 
                                                           tor_param1, tor_param2, tor_param3);
    }

    double calcMMFF94ElectrostaticGradient1(const CDPL::ForceField::MMFF94ElectrostaticInteractionData& ia_data, const CDPL::Math::Vector3DArray& coords, 
                                            CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94ElectrostaticGradient<double>(ia_data.getElementsBegin(), ia_data.getElementsEnd(), coords, grad);
    }

    double calcMMFF94ElectrostaticGradient2(const CDPL::ForceField::MMFF94ElectrostaticInteraction& iaction, const CDPL::Math::Vector3DArray& coords, 
                                            CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94ElectrostaticGradient<double>(iaction, coords, grad);
    }

    double calcMMFF94ElectrostaticGradient3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, 
                                            CDPL::Math::Vector3D& atom1_grad, CDPL::Math::Vector3D& atom2_grad, double atom1_chg,
                                            double atom2_chg, double scale_fact, double de_const, double dist_expo)
    {
        return CDPL::ForceField::calcMMFF94ElectrostaticGradient(atom1_pos, atom2_pos, atom1_grad, atom2_grad, atom1_chg, atom2_chg, scale_fact, 
                                                                 de_const, dist_expo);
    }

    double calcMMFF94VanDerWaalsGradient1(const CDPL::ForceField::MMFF94VanDerWaalsInteractionData& ia_data, const CDPL::Math::Vector3DArray& coords, 
                                          CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94VanDerWaalsGradient<double>(ia_data.getElementsBegin(), ia_data.getElementsEnd(), coords, grad);
    }

    double calcMMFF94VanDerWaalsGradient2(const CDPL::ForceField::MMFF94VanDerWaalsInteraction& iaction, const CDPL::Math::Vector3DArray& coords, 
                                          CDPL::Math::Vector3DArray& grad)
    {
        return CDPL::ForceField::calcMMFF94VanDerWaalsGradient<double>(iaction, coords, grad);
    }

    double calcMMFF94VanDerWaalsGradient3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, 
                                          CDPL::Math::Vector3D& atom1_grad, CDPL::Math::Vector3D& atom2_grad, double e_IJ,
                                          double r_IJ, double r_IJ_7)
    {
        return CDPL::ForceField::calcMMFF94VanDerWaalsGradient(atom1_pos, atom2_pos, atom1_grad, atom2_grad, e_IJ, r_IJ, r_IJ_7);
    }
}


void CDPLPythonForceField::exportMMFF94GradientFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("calcMMFF94BondStretchingGradient", &calcMMFF94BondStretchingGradient1,
                (python::arg("ia_data"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94BondStretchingGradient", &calcMMFF94BondStretchingGradient2,
                (python::arg("iaction"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94BondStretchingGradient", &calcMMFF94BondStretchingGradient3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"),
                 python::arg("atom1_grad"), python::arg("atom2_grad"),
                 python::arg("force_const"), python::arg("ref_length")));

    python::def("calcMMFF94AngleBendingGradient", &calcMMFF94AngleBendingGradient1,
                (python::arg("ia_data"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94AngleBendingGradient", &calcMMFF94AngleBendingGradient2,
                (python::arg("iaction"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94AngleBendingGradient", &calcMMFF94AngleBendingGradient3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("term_atom1_grad"), python::arg("ctr_atom_grad"), python::arg("term_atom2_grad"), 
                 python::arg("linear"), python::arg("force_const"), python::arg("ref_angle")));

    python::def("calcMMFF94StretchBendGradient", &calcMMFF94StretchBendGradient1,
                (python::arg("ia_data"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94StretchBendGradient", &calcMMFF94StretchBendGradient2,
                (python::arg("iaction"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94StretchBendGradient", &calcMMFF94StretchBendGradient3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("term_atom1_grad"), python::arg("ctr_atom_grad"), python::arg("term_atom2_grad"), 
                 python::arg("ijk_force_const"), python::arg("kji_force_const"), python::arg("ref_angle"),
                 python::arg("ref_length1"),  python::arg("ref_length2")));

    python::def("calcMMFF94OutOfPlaneBendingGradient", &calcMMFF94OutOfPlaneBendingGradient1,
                (python::arg("ia_data"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94OutOfPlaneBendingGradient", &calcMMFF94OutOfPlaneBendingGradient2,
                (python::arg("iaction"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94OutOfPlaneBendingGradient", &calcMMFF94OutOfPlaneBendingGradient3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"),
                 python::arg("oop_atom_pos"), python::arg("term_atom1_grad"), python::arg("ctr_atom_grad"),
                 python::arg("term_atom2_grad"), python::arg("oop_atom_grad"), python::arg("force_const")));

    python::def("calcMMFF94TorsionGradient", &calcMMFF94TorsionGradient1,
                (python::arg("ia_data"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94TorsionGradient", &calcMMFF94TorsionGradient2,
                (python::arg("iaction"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94TorsionGradient", &calcMMFF94TorsionGradient3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom1_pos"), python::arg("ctr_atom2_pos"), 
                 python::arg("term_atom2_pos"), python::arg("term_atom1_grad"), python::arg("ctr_atom1_grad"), 
                 python::arg("ctr_atom2_grad"), python::arg("term_atom2_grad"), python::arg("tor_param1"), 
                 python::arg("tor_param2"), python::arg("tor_param3")));

    python::def("calcMMFF94ElectrostaticGradient", &calcMMFF94ElectrostaticGradient1,
                (python::arg("ia_data"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94ElectrostaticGradient", &calcMMFF94ElectrostaticGradient2,
                (python::arg("iaction"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94ElectrostaticGradient", &calcMMFF94ElectrostaticGradient3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"),
                 python::arg("atom1_grad"), python::arg("atom2_grad"), python::arg("atom1_chg"), 
                 python::arg("atom2_chg"), python::arg("scale_fact"), python::arg("de_const"),
                 python::arg("dist_expo")));

    python::def("calcMMFF94VanDerWaalsGradient", &calcMMFF94VanDerWaalsGradient1,
                (python::arg("ia_data"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94VanDerWaalsGradient", &calcMMFF94VanDerWaalsGradient2,
                (python::arg("iaction"), python::arg("coords"), python::arg("grad")));
    python::def("calcMMFF94VanDerWaalsGradient", &calcMMFF94VanDerWaalsGradient3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"),
                 python::arg("atom1_grad"), python::arg("atom2_grad"), python::arg("e_IJ"), 
                 python::arg("r_IJ"), python::arg("r_IJ_7")));
}
