/* 
 * MMFF94EnergyFunctionExport.cpp 
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

#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94StretchBendInteractionList.hpp"
#include "CDPL/ForceField/MMFF94OutOfPlaneBendingInteractionList.hpp"
#include "CDPL/ForceField/MMFF94TorsionInteractionList.hpp"
#include "CDPL/ForceField/MMFF94ElectrostaticInteractionList.hpp"
#include "CDPL/ForceField/MMFF94VanDerWaalsInteractionList.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "FunctionExports.hpp"


namespace
{

    double calcMMFF94BondStretchingEnergy1(const CDPL::ForceField::MMFF94BondStretchingInteractionList& ia_list, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94BondStretchingEnergy<double>(ia_list.getElementsBegin(), ia_list.getElementsEnd(), coords);
    }

    double calcMMFF94BondStretchingEnergy2(const CDPL::ForceField::MMFF94BondStretchingInteraction& iaction, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94BondStretchingEnergy<double>(iaction, coords);
    }

    double calcMMFF94BondStretchingEnergy3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, 
                                           double force_const, double ref_length)
    {
        return CDPL::ForceField::calcMMFF94BondStretchingEnergy<double>(atom1_pos, atom2_pos, force_const, ref_length);
    }

    double calcMMFF94BondStretchingEnergy4(double r_ij, double force_const, double ref_length)
    {
        return CDPL::ForceField::calcMMFF94BondStretchingEnergy<double>(r_ij, force_const, ref_length);
    }


    double calcMMFF94AngleBendingEnergy1(const CDPL::ForceField::MMFF94AngleBendingInteractionList& ia_list, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94AngleBendingEnergy<double>(ia_list.getElementsBegin(), ia_list.getElementsEnd(), coords);
    }

    double calcMMFF94AngleBendingEnergy2(const CDPL::ForceField::MMFF94AngleBendingInteraction& iaction, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94AngleBendingEnergy<double>(iaction, coords);
    }

    double calcMMFF94AngleBendingEnergy3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                         const CDPL::Math::Vector3D& term_atom2_pos, bool linear, double force_const, double ref_angle)
    {
        return CDPL::ForceField::calcMMFF94AngleBendingEnergy<double>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, linear, force_const, ref_angle);
    }

    double calcMMFF94AngleBendingEnergy4(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                         const CDPL::Math::Vector3D& term_atom2_pos, double r_ij, double r_jk, bool linear, double force_const, double ref_angle)
    {
        return CDPL::ForceField::calcMMFF94AngleBendingEnergy<double>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, r_ij, r_jk, linear, force_const, ref_angle);
    }


    double calcMMFF94StretchBendEnergy1(const CDPL::ForceField::MMFF94StretchBendInteractionList& ia_list, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94StretchBendEnergy<double>(ia_list.getElementsBegin(), ia_list.getElementsEnd(), coords);
    }

    double calcMMFF94StretchBendEnergy2(const CDPL::ForceField::MMFF94StretchBendInteraction& iaction, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94StretchBendEnergy<double>(iaction, coords);
    }

    double calcMMFF94StretchBendEnergy3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                        const CDPL::Math::Vector3D& term_atom2_pos, double ijk_force_const, double kji_force_const, 
                                        double ref_angle, double ref_length1, double ref_length2)
    {
        return CDPL::ForceField::calcMMFF94StretchBendEnergy<double>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, ijk_force_const, kji_force_const,
                                                                     ref_angle, ref_length1, ref_length2);
    }

    double calcMMFF94StretchBendEnergy4(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                        const CDPL::Math::Vector3D& term_atom2_pos, double r_ij, double r_jk, double ijk_force_const, double kji_force_const, 
                                        double ref_angle, double ref_length1, double ref_length2)
    {
        return CDPL::ForceField::calcMMFF94StretchBendEnergy<double>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, r_ij, r_jk, ijk_force_const, kji_force_const,
                                                                     ref_angle, ref_length1, ref_length2);
    }


    double calcMMFF94OutOfPlaneBendingEnergy1(const CDPL::ForceField::MMFF94OutOfPlaneBendingInteractionList& ia_list, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy<double>(ia_list.getElementsBegin(), ia_list.getElementsEnd(), coords);
    }

    double calcMMFF94OutOfPlaneBendingEnergy2(const CDPL::ForceField::MMFF94OutOfPlaneBendingInteraction& iaction, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy<double>(iaction, coords);
    }

    double calcMMFF94OutOfPlaneBendingEnergy3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                              const CDPL::Math::Vector3D& term_atom2_pos, const CDPL::Math::Vector3D& oop_atom_pos, 
                                              double force_const)
    {
        return CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy<double>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, oop_atom_pos, force_const);
    }

    double calcMMFF94OutOfPlaneBendingEnergy4(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom_pos, 
                                              const CDPL::Math::Vector3D& term_atom2_pos, const CDPL::Math::Vector3D& oop_atom_pos, 
                                              double r_jl, double force_const)
    {
        return CDPL::ForceField::calcMMFF94OutOfPlaneBendingEnergy<double>(term_atom1_pos, ctr_atom_pos, term_atom2_pos, oop_atom_pos, r_jl, force_const);
    }


    double calcMMFF94TorsionEnergy1(const CDPL::ForceField::MMFF94TorsionInteractionList& ia_list, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94TorsionEnergy<double>(ia_list.getElementsBegin(), ia_list.getElementsEnd(), coords);
    }

    double calcMMFF94TorsionEnergy2(const CDPL::ForceField::MMFF94TorsionInteraction& iaction, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94TorsionEnergy<double>(iaction, coords);
    }

    double calcMMFF94TorsionEnergy3(const CDPL::Math::Vector3D& term_atom1_pos, const CDPL::Math::Vector3D& ctr_atom1_pos, 
                                    const CDPL::Math::Vector3D& ctr_atom2_pos, const CDPL::Math::Vector3D& term_atom2_pos, 
                                    double tor_param1, double tor_param2, double tor_param3)
    {
        return CDPL::ForceField::calcMMFF94TorsionEnergy<double>(term_atom1_pos, ctr_atom1_pos, ctr_atom2_pos, term_atom2_pos, 
                                                                 tor_param1, tor_param2, tor_param3);
    }

    double calcMMFF94ElectrostaticEnergy1(const CDPL::ForceField::MMFF94ElectrostaticInteractionList& ia_list, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94ElectrostaticEnergy<double>(ia_list.getElementsBegin(), ia_list.getElementsEnd(), coords);
    }

    double calcMMFF94ElectrostaticEnergy2(const CDPL::ForceField::MMFF94ElectrostaticInteraction& iaction, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94ElectrostaticEnergy<double>(iaction, coords);
    }

    double calcMMFF94ElectrostaticEnergy3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, double atom1_chg,
                                          double atom2_chg, double scale_fact, double de_const, double dist_expo)
    {
        return CDPL::ForceField::calcMMFF94ElectrostaticEnergy<double>(atom1_pos, atom2_pos, atom1_chg, atom2_chg, scale_fact, de_const, dist_expo);
    }

    double calcMMFF94ElectrostaticEnergy4(double r_ij, double atom1_chg,
                                          double atom2_chg, double scale_fact, double de_const, double dist_expo)
    {
        return CDPL::ForceField::calcMMFF94ElectrostaticEnergy<double>(r_ij, atom1_chg, atom2_chg, scale_fact, de_const, dist_expo);
    }


    double calcMMFF94VanDerWaalsEnergy1(const CDPL::ForceField::MMFF94VanDerWaalsInteractionList& ia_list, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94VanDerWaalsEnergy<double>(ia_list.getElementsBegin(), ia_list.getElementsEnd(), coords);
    }

    double calcMMFF94VanDerWaalsEnergy2(const CDPL::ForceField::MMFF94VanDerWaalsInteraction& iaction, const CDPL::Math::Vector3DArray& coords)
    {
        return CDPL::ForceField::calcMMFF94VanDerWaalsEnergy<double>(iaction, coords);
    }

    double calcMMFF94VanDerWaalsEnergy3(const CDPL::Math::Vector3D& atom1_pos, const CDPL::Math::Vector3D& atom2_pos, double e_IJ,
                                        double r_IJ, double r_IJ_7)
    {
        return CDPL::ForceField::calcMMFF94VanDerWaalsEnergy<double>(atom1_pos, atom2_pos, e_IJ, r_IJ, r_IJ_7);
    }

    double calcMMFF94VanDerWaalsEnergy4(double r_ij, double e_IJ, double r_IJ, double r_IJ_7)
    {
        return CDPL::ForceField::calcMMFF94VanDerWaalsEnergy<double>(r_ij, e_IJ, r_IJ, r_IJ_7);
    }
}


void CDPLPythonForceField::exportMMFF94EnergyFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("calcMMFF94BondStretchingEnergy", &calcMMFF94BondStretchingEnergy1,
                (python::arg("ia_list"), python::arg("coords")));
    python::def("calcMMFF94BondStretchingEnergy", &calcMMFF94BondStretchingEnergy2,
                (python::arg("iaction"), python::arg("coords")));
    python::def("calcMMFF94BondStretchingEnergy", &calcMMFF94BondStretchingEnergy3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"), python::arg("force_const"), python::arg("ref_length")));
    python::def("calcMMFF94BondStretchingEnergy", &calcMMFF94BondStretchingEnergy4,
                (python::arg("r_ij"), python::arg("force_const"), python::arg("ref_length")));

    python::def("calcMMFF94AngleBendingEnergy", &calcMMFF94AngleBendingEnergy1,
                (python::arg("ia_list"), python::arg("coords")));
    python::def("calcMMFF94AngleBendingEnergy", &calcMMFF94AngleBendingEnergy2,
                (python::arg("iaction"), python::arg("coords")));
    python::def("calcMMFF94AngleBendingEnergy", &calcMMFF94AngleBendingEnergy3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("linear"), python::arg("force_const"), python::arg("ref_angle")));
    python::def("calcMMFF94AngleBendingEnergy", &calcMMFF94AngleBendingEnergy4,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("r_ij"), python::arg("r_jk"), python::arg("linear"), python::arg("force_const"),
                 python::arg("ref_angle")));

    python::def("calcMMFF94StretchBendEnergy", &calcMMFF94StretchBendEnergy1,
                (python::arg("ia_list"), python::arg("coords")));
    python::def("calcMMFF94StretchBendEnergy", &calcMMFF94StretchBendEnergy2,
                (python::arg("iaction"), python::arg("coords")));
    python::def("calcMMFF94StretchBendEnergy", &calcMMFF94StretchBendEnergy3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("ijk_force_const"), python::arg("kji_force_const"), python::arg("ref_angle"),
                 python::arg("ref_length1"),  python::arg("ref_length2")));
    python::def("calcMMFF94StretchBendEnergy", &calcMMFF94StretchBendEnergy4,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("r_ij"), python::arg("r_jk"), python::arg("ijk_force_const"), python::arg("kji_force_const"),
                 python::arg("ref_angle"), python::arg("ref_length1"),  python::arg("ref_length2")));

    python::def("calcMMFF94OutOfPlaneBendingEnergy", &calcMMFF94OutOfPlaneBendingEnergy1,
                (python::arg("ia_list"), python::arg("coords")));
    python::def("calcMMFF94OutOfPlaneBendingEnergy", &calcMMFF94OutOfPlaneBendingEnergy2,
                (python::arg("iaction"), python::arg("coords")));
    python::def("calcMMFF94OutOfPlaneBendingEnergy", &calcMMFF94OutOfPlaneBendingEnergy3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("oop_atom_pos"), python::arg("force_const")));
    python::def("calcMMFF94OutOfPlaneBendingEnergy", &calcMMFF94OutOfPlaneBendingEnergy4,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom_pos"), python::arg("term_atom2_pos"), 
                 python::arg("oop_atom_pos"), python::arg("r_jl"), python::arg("force_const")));

    python::def("calcMMFF94TorsionEnergy", &calcMMFF94TorsionEnergy1,
                (python::arg("ia_list"), python::arg("coords")));
    python::def("calcMMFF94TorsionEnergy", &calcMMFF94TorsionEnergy2,
                (python::arg("iaction"), python::arg("coords")));
    python::def("calcMMFF94TorsionEnergy", &calcMMFF94TorsionEnergy3,
                (python::arg("term_atom1_pos"), python::arg("ctr_atom1_pos"), python::arg("ctr_atom2_pos"), 
                 python::arg("term_atom2_pos"), python::arg("tor_param1"), python::arg("tor_param2"), 
                 python::arg("tor_param3")));

    python::def("calcMMFF94ElectrostaticEnergy", &calcMMFF94ElectrostaticEnergy1,
                (python::arg("ia_list"), python::arg("coords")));
    python::def("calcMMFF94ElectrostaticEnergy", &calcMMFF94ElectrostaticEnergy2,
                (python::arg("iaction"), python::arg("coords")));
    python::def("calcMMFF94ElectrostaticEnergy", &calcMMFF94ElectrostaticEnergy3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"), python::arg("atom1_chg"), 
                 python::arg("atom2_chg"), python::arg("scale_fact"), python::arg("de_const"),
                 python::arg("dist_expo")));
    python::def("calcMMFF94ElectrostaticEnergy", &calcMMFF94ElectrostaticEnergy4,
                (python::arg("r_ij"), python::arg("atom1_chg"), python::arg("atom2_chg"), 
                 python::arg("scale_fact"), python::arg("de_const"), python::arg("dist_expo")));

    python::def("calcMMFF94VanDerWaalsEnergy", &calcMMFF94VanDerWaalsEnergy1,
                (python::arg("ia_list"), python::arg("coords")));
    python::def("calcMMFF94VanDerWaalsEnergy", &calcMMFF94VanDerWaalsEnergy2,
                (python::arg("iaction"), python::arg("coords")));
    python::def("calcMMFF94VanDerWaalsEnergy", &calcMMFF94VanDerWaalsEnergy3,
                (python::arg("atom1_pos"), python::arg("atom2_pos"), python::arg("e_IJ"), 
                 python::arg("r_IJ"), python::arg("r_IJ_7")));
    python::def("calcMMFF94VanDerWaalsEnergy", &calcMMFF94VanDerWaalsEnergy4,
                (python::arg("r_ij"), python::arg("e_IJ"), python::arg("r_IJ"), python::arg("r_IJ_7")));
}
