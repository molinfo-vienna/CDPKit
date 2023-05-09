#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
#

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \return 
#
def calcDistance(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \return 
#
def calcSquaredDistance(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \return 
#
def calcBondLengthsAndAngle(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D) -> tuple: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param r_ij 
# \param r_jk 
# \return 
#
def calcBondAngle(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, r_ij: float, r_jk: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \return 
#
def calcBondAngle(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param oop_atom_pos 
# \param r_jl 
# \return 
#
def calcOutOfPlaneAngle(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, oop_atom_pos: CDPL.Math.Vector3D, r_jl: float) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \param atom1_deriv 
# \param atom2_deriv 
# \return 
#
def calcDistanceDerivatives(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D, atom1_deriv: CDPL.Math.Vector3D, atom2_deriv: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param term_atom1_deriv 
# \param ctr_atom_deriv 
# \param term_atom2_deriv 
# \return 
#
def calcBondAngleCosDerivatives(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, term_atom1_deriv: CDPL.Math.Vector3D, ctr_atom_deriv: CDPL.Math.Vector3D, term_atom2_deriv: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param oop_atom_pos 
# \param term_atom1_deriv 
# \param ctr_atom_deriv 
# \param term_atom2_deriv 
# \param oop_atom_deriv 
# \return 
#
def calcOutOfPlaneAngleCosDerivatives(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, oop_atom_pos: CDPL.Math.Vector3D, term_atom1_deriv: CDPL.Math.Vector3D, ctr_atom_deriv: CDPL.Math.Vector3D, term_atom2_deriv: CDPL.Math.Vector3D, oop_atom_deriv: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom1_pos 
# \param ctr_atom2_pos 
# \param term_atom2_pos 
# \param term_atom1_deriv 
# \param ctr_atom1_deriv 
# \param ctr_atom2_deriv 
# \param term_atom2_deriv 
# \return 
#
def calcDihedralAngleCosDerivatives(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom1_pos: CDPL.Math.Vector3D, ctr_atom2_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, term_atom1_deriv: CDPL.Math.Vector3D, ctr_atom1_deriv: CDPL.Math.Vector3D, ctr_atom2_deriv: CDPL.Math.Vector3D, term_atom2_deriv: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \return 
#
def calcBondLengthsAndAngleCos(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D) -> tuple: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param r_ij 
# \param r_jk 
# \return 
#
def calcBondAngleCos(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, r_ij: float, r_jk: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \return 
#
def calcBondAngleCos(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom1_pos 
# \param ctr_atom2_pos 
# \param term_atom2_pos 
# \return 
#
def calcDihedralAngleCos(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom1_pos: CDPL.Math.Vector3D, ctr_atom2_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \param atom1_grad 
# \param atom2_grad 
# \param atom1_chg 
# \param atom2_chg 
# \param scale_fact 
# \param de_const 
# \param dist_expo 
# \return 
#
def calcMMFF94ElectrostaticGradient(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D, atom1_grad: CDPL.Math.Vector3D, atom2_grad: CDPL.Math.Vector3D, atom1_chg: float, atom2_chg: float, scale_fact: float, de_const: float, dist_expo: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param term_atom1_grad 
# \param ctr_atom_grad 
# \param term_atom2_grad 
# \param ijk_force_const 
# \param kji_force_const 
# \param ref_angle 
# \param ref_length1 
# \param ref_length2 
# \return 
#
def calcMMFF94StretchBendGradient(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, term_atom1_grad: CDPL.Math.Vector3D, ctr_atom_grad: CDPL.Math.Vector3D, term_atom2_grad: CDPL.Math.Vector3D, ijk_force_const: float, kji_force_const: float, ref_angle: float, ref_length1: float, ref_length2: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param term_atom1_grad 
# \param ctr_atom_grad 
# \param term_atom2_grad 
# \param linear 
# \param force_const 
# \param ref_angle 
# \return 
#
def calcMMFF94AngleBendingGradient(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, term_atom1_grad: CDPL.Math.Vector3D, ctr_atom_grad: CDPL.Math.Vector3D, term_atom2_grad: CDPL.Math.Vector3D, linear: bool, force_const: float, ref_angle: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param oop_atom_pos 
# \param term_atom1_grad 
# \param ctr_atom_grad 
# \param term_atom2_grad 
# \param oop_atom_grad 
# \param force_const 
# \return 
#
def calcMMFF94OutOfPlaneBendingGradient(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, oop_atom_pos: CDPL.Math.Vector3D, term_atom1_grad: CDPL.Math.Vector3D, ctr_atom_grad: CDPL.Math.Vector3D, term_atom2_grad: CDPL.Math.Vector3D, oop_atom_grad: CDPL.Math.Vector3D, force_const: float) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \param atom1_grad 
# \param atom2_grad 
# \param force_const 
# \param ref_length 
# \return 
#
def calcMMFF94BondStretchingGradient(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D, atom1_grad: CDPL.Math.Vector3D, atom2_grad: CDPL.Math.Vector3D, force_const: float, ref_length: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom1_pos 
# \param ctr_atom2_pos 
# \param term_atom2_pos 
# \param term_atom1_grad 
# \param ctr_atom1_grad 
# \param ctr_atom2_grad 
# \param term_atom2_grad 
# \param tor_param1 
# \param tor_param2 
# \param tor_param3 
# \return 
#
def calcMMFF94TorsionGradient(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom1_pos: CDPL.Math.Vector3D, ctr_atom2_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, term_atom1_grad: CDPL.Math.Vector3D, ctr_atom1_grad: CDPL.Math.Vector3D, ctr_atom2_grad: CDPL.Math.Vector3D, term_atom2_grad: CDPL.Math.Vector3D, tor_param1: float, tor_param2: float, tor_param3: float) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \param atom1_grad 
# \param atom2_grad 
# \param e_IJ 
# \param r_IJ 
# \param r_IJ_7 
# \return 
#
def calcMMFF94VanDerWaalsGradient(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D, atom1_grad: CDPL.Math.Vector3D, atom2_grad: CDPL.Math.Vector3D, e_IJ: float, r_IJ: float, r_IJ_7: float) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \param atom1_chg 
# \param atom2_chg 
# \param scale_fact 
# \param de_const 
# \param dist_expo 
# \return 
#
def calcMMFF94ElectrostaticEnergy(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D, atom1_chg: float, atom2_chg: float, scale_fact: float, de_const: float, dist_expo: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param ijk_force_const 
# \param kji_force_const 
# \param ref_angle 
# \param ref_length1 
# \param ref_length2 
# \return 
#
def calcMMFF94StretchBendEnergy(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, ijk_force_const: float, kji_force_const: float, ref_angle: float, ref_length1: float, ref_length2: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param r_ij 
# \param r_jk 
# \param ijk_force_const 
# \param kji_force_const 
# \param ref_angle 
# \param ref_length1 
# \param ref_length2 
# \return 
#
def calcMMFF94StretchBendEnergy(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, r_ij: float, r_jk: float, ijk_force_const: float, kji_force_const: float, ref_angle: float, ref_length1: float, ref_length2: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param linear 
# \param force_const 
# \param ref_angle 
# \return 
#
def calcMMFF94AngleBendingEnergy(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, linear: bool, force_const: float, ref_angle: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param r_ij 
# \param r_jk 
# \param linear 
# \param force_const 
# \param ref_angle 
# \return 
#
def calcMMFF94AngleBendingEnergy(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, r_ij: float, r_jk: float, linear: bool, force_const: float, ref_angle: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param oop_atom_pos 
# \param force_const 
# \return 
#
def calcMMFF94OutOfPlaneBendingEnergy(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, oop_atom_pos: CDPL.Math.Vector3D, force_const: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \param oop_atom_pos 
# \param r_jl 
# \param force_const 
# \return 
#
def calcMMFF94OutOfPlaneBendingEnergy(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, oop_atom_pos: CDPL.Math.Vector3D, r_jl: float, force_const: float) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \param force_const 
# \param ref_length 
# \return 
#
def calcMMFF94BondStretchingEnergy(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D, force_const: float, ref_length: float) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom1_pos 
# \param ctr_atom2_pos 
# \param term_atom2_pos 
# \param tor_param1 
# \param tor_param2 
# \param tor_param3 
# \return 
#
def calcMMFF94TorsionEnergy(term_atom1_pos: CDPL.Math.Vector3D, ctr_atom1_pos: CDPL.Math.Vector3D, ctr_atom2_pos: CDPL.Math.Vector3D, term_atom2_pos: CDPL.Math.Vector3D, tor_param1: float, tor_param2: float, tor_param3: float) -> float: pass

##
# \brief 
# \param atom1_pos 
# \param atom2_pos 
# \param e_IJ 
# \param r_IJ 
# \param r_IJ_7 
# \return 
#
def calcMMFF94VanDerWaalsEnergy(atom1_pos: CDPL.Math.Vector3D, atom2_pos: CDPL.Math.Vector3D, e_IJ: float, r_IJ: float, r_IJ_7: float) -> float: pass
