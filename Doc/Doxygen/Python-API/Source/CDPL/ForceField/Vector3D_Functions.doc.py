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
# \brief Calculates the distance \f$ r_{ij} \f$ between two atoms <em>i</em> and <em>j</em>.
# 
# \f$ r_{ij} = |\vec{v_{ij}}| \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
# 
# \param atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param atom2_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# 
# \return The calculated distance \f$ r_{ij} \f$.
# 
def calcDistance(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D) -> float: pass

##
# \brief Calculates the squared distance \f$ r_{ij}^2 \f$ between two atoms <em>i</em> and <em>j</em>.
# 
# \f$ r_{ij}^2 = |\vec{v_{ij}}|^2 \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
# 
# \param atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param atom2_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# 
# \return The calculated squared distance \f$ r_{ij}^2 \f$.
# 
def calcSquaredDistance(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \return 
#
def calcBondLengthsAndAngle(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D) -> tuple: pass

##
# \brief Calculates the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ \vartheta_{ijk} = \arccos(\frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|}) \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom <em>k</em>.
# \param r_ij The length of the bond between atom <em>i</em> and <em>j</em>.
# \param r_jk The length of the bond between atom <em>j</em> and <em>k</em>.
# 
# \return The calculated bond angle \f$ \vartheta_{ijk} \f$.
# 
def calcBondAngle(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, r_ij: float, r_jk: float) -> float: pass

##
# \brief Calculates the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ \vartheta_{ijk} = \arccos(\frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|}) \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom <em>k</em>.
# 
# \return The calculated bond angle \f$ \vartheta_{ijk} \f$.
# 
def calcBondAngle(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D) -> float: pass

##
# \brief Calculates the out-of-plane angle \f$ \chi_{ijk;l} \f$ between the bond <em>j-l</em> and the plane defined by the atoms <em>i-j-k</em>.
# 
# \f$ \chi_{ijk;l} = \frac{\pi}{2} - \arccos(\frac{\vec{n_{ijk}} \cdot \vec{v_{jl}}}{|\vec{n_{ijk}}| \: |\vec{v_{jl}}|}) \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{jl}} = \vec{p_l} - \vec{p_j} \f$<br>
#  \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
#  \f$ \vec{p_l} \f$ = coordinates of atom <em>l</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom <em>k</em>.
# \param oop_atom_pos The position \f$ \vec{p_l} \f$ of the out-of-plane atom <em>l</em>.
# \param r_jl The length of the bond between atom <em>j</em> and atom <em>l</em>.
# 
# \return The calculated out-of-plane angle \f$ \chi_{ijk;l} \f$.
# 
def calcOutOfPlaneAngle(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, oop_atom_pos: Math.Vector3D, r_jl: float) -> float: pass

##
# \brief Calculates the partial derivatives \f$ \frac{\partial r_{ij}}{\partial \vec{p_x}} \f$ of the distance \f$ r_{ij} \f$ between two atoms <em>i</em> and <em>j</em>.
# 
# \f$ \frac{\partial r_{ij}}{\partial \vec{p_i}} = \frac{-\vec{v_{ij}}}{r_{ij}} \f$<br>
#  \f$ \frac{\partial r_{ij}}{\partial \vec{p_j}} = \frac{\vec{v_{ij}}}{r_{ij}} \f$<br>
#  \f$ r_{ij} = |\vec{v_{ij}}| \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
# 
# \param atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param atom2_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# \param atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial r_{ij}}{\partial \vec{p_i}} \f$ at the given atom positions.
# \param atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial r_{ij}}{\partial \vec{p_j}} \f$ at the given atom positions.
# 
# \return The calculated distance \f$ r_{ij} \f$.
# 
def calcDistanceDerivatives(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, atom1_deriv: Math.Vector3D, atom2_deriv: Math.Vector3D) -> float: pass

##
# \brief Calculates the partial derivatives \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_x}} \f$ of the of the <em>cosine</em> of the angle \f$ \vartheta_{ijk} \f$ between the bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_i}} = \frac{\vec{v_{jk}}}{r_{ji} \: r_{jk}} - \frac{\vec{v_{ji}} \: (\vec{v_{ji}} \cdot \vec{v_{jk}})}{r_{ji}^3 \: r_{jk}} \f$<br>
#  \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_k}} = \frac{\vec{v_{ji}}}{r_{ji} \: r_{jk}} - \frac{\vec{v_{jk}} \: (\vec{v_{ji}} \cdot \vec{v_{jk}})}{r_{ji} \: r_{jk}^3} \f$<br>
#  \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_j}} = -(\frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_i}} + \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_k}}) \f$<br>
#  \f$ \cos(\vartheta_{ijk}) = \frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{r_{ij} \: r_{jk}} \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
#  \f$ r_{ji} = |\vec{v_{ji}}| \f$<br>
#  \f$ r_{jk} = |\vec{v_{jk}}| \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom <em>k</em>.
# \param term_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_i}} \f$ at the given atom positions.
# \param ctr_atom_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_j}} \f$ at the given atom positions.
# \param term_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\vartheta_{ijk})}{\partial \vec{p_k}} \f$ at the given atom positions.
# 
# \return The calculated cosine of the bond angle \f$ \vartheta_{ijk} \f$.
# 
def calcBondAngleCosDerivatives(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, term_atom1_deriv: Math.Vector3D, ctr_atom_deriv: Math.Vector3D, term_atom2_deriv: Math.Vector3D) -> float: pass

##
# \brief Calculates the partial derivatives \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_x}} \f$ of the <em>cosine</em> of the angle \f$ \omega_{ijk;l} \f$ between the bond <em>j-l</em> and the normal of the plane defined by the atoms <em>i-j-k</em>.
# 
# \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_i}} = \frac{\vec{v_{jk}} \times \vec{v_{jl}}}{|\vec{n_{ijk}}| \: r_{jl}} - \cos(\omega_{ijk;l}) \: \frac{M_1 \cdot \vec{n_{ijk}}}{|\vec{n_{ijk}}|^2} \f$<br>
#  \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_k}} = \frac{\vec{v_{jl}} \times \vec{v_{ji}}}{|\vec{n_{ijk}}| \: r_{jl}} - \cos(\omega_{ijk;l}) \: \frac{M_2 \cdot \vec{n_{ijk}}}{|\vec{n_{ijk}}|^2} \f$<br>
#  \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_l}} = \frac{-1}{|\vec{n_{ijk}}| \: r_{jl}} \: (\frac{\vec{v_{jl}} (\vec{n_{ijk}} \cdot \vec{v_{jl}})}{r_{jl}^2} + \vec{r_{kl}} \times \vec{v_{il}} + \vec{v_{jl}} \times \vec{v_{ji}} + \vec{v_{jk}} \times \vec{v_{jl}}) \f$<br>
#  \f$ \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_j}} = -(\frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_i}} + \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_k}} + \frac{\partial \cos(\omega_{ijk;l})}{\partial \vec{p_l}}) \f$<br>
#  \f$ \cos(\omega_{ijk;l}) = \frac{\vec{n_{ijk}} \cdot \vec{v_{jl}}}{|\vec{n_{ijk}}| \: r_{jl}} \f$<br>
# 
# where<br>
#  \f$ M_1 = \left| \begin{array}{ccc} 0 & -\vec{v_{jk}}.z & \vec{v_{jk}}.y \\ \vec{v_{jk}}.z & 0 & -\vec{v_{jk}}.x \\ -\vec{v_{jk}}.y & \vec{v_{jk}}.x & 0 \end{array} \right| \f$<br>
#  \f$ M_2 = \left| \begin{array}{ccc} 0 & \vec{v_{ji}}.z & -\vec{v_{ji}}.y \\ -\vec{v_{ji}}.z & 0 & \vec{v_{ji}}.x \\ \vec{v_{ji}}.y & -\vec{v_{ji}}.x & 0 \end{array} \right| \f$<br>
#  \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{jl}} = \vec{p_l} - \vec{p_j} \f$<br>
#  \f$ \vec{r_{kl}} = \vec{p_l} - \vec{p_k} \f$<br>
#  \f$ \vec{v_{il}} = \vec{p_l} - \vec{p_i} \f$<br>
#  \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
#  \f$ r_{jl} = |\vec{v_{jl}}| \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
#  \f$ \vec{p_l} \f$ = coordinates of atom <em>l</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom <em>k</em>.
# \param oop_atom_pos The position \f$ \vec{p_l} \f$ of the out-of-plane atom <em>l</em>.
# \param term_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_i}} \f$ at the given atom positions.
# \param ctr_atom_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_j}} \f$ at the given atom positions.
# \param term_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_k}} \f$ at the given atom positions.
# \param oop_atom_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\omega_{ijkl})}{\partial \vec{p_l}} \f$ at the given atom positions.
# 
# \return The calculated cosine of the angle \f$ \omega_{ijk;l} \f$.
# 
def calcOutOfPlaneAngleCosDerivatives(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, oop_atom_pos: Math.Vector3D, term_atom1_deriv: Math.Vector3D, ctr_atom_deriv: Math.Vector3D, term_atom2_deriv: Math.Vector3D, oop_atom_deriv: Math.Vector3D) -> float: pass

##
# \brief Calculates the partial derivatives \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_x}} \f$ of the <em>cosine</em> of the angle \f$ \Phi_{ijkl} \f$ between the planes defined by the atom triplets <em>i-j-k</em> and <em>j-k-l</em>.
# 
# \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_i}} = \vec{v_{jk}} \times \vec{a} \f$<br>
#  <br>
#  \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_j}} = \vec{r_{ki}} \times \vec{a} - \vec{v_{lk}} \times \vec{b} \f$<br>
#  \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_l}} = \vec{v_{jk}} \times \vec{b} \f$<br>
#  \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_k}} = -(\frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_i}} + \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_j}} + \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_l}}) \f$<br>
#  \f$ \cos(\Phi_{ijkl}) = \frac{\vec{n_{ijk}} \cdot \vec{n_{jkl}}}{|\vec{n_{ijk}}| \: |\vec{n_{jkl}}|} \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{lk}} = \vec{p_k} - \vec{p_l} \f$<br>
#  \f$ \vec{r_{ki}} = \vec{p_i} - \vec{p_k} \f$<br>
#  \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
#  \f$ \vec{n_{jkl}} = \vec{v_{jk}} \times \vec{v_{lk}} \f$<br>
#  \f$ \vec{a} = \frac{\frac{\vec{n_{jkl}}}{|\vec{n_{jkl}}|} - \cos(\Phi_{ijkl}) \: \frac{\vec{n_{ijk}}}{|\vec{n_{ijk}}|}}{|\vec{n_{ijk}}|} \f$<br>
#  \f$ \vec{b} = \frac{\frac{\vec{n_{ijk}}}{|\vec{n_{ijk}}|} - \cos(\Phi_{ijkl}) \: \frac{\vec{n_{jkl}}}{|\vec{n_{jkl}}|}}{|\vec{n_{jkl}}|} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
#  \f$ \vec{p_l} \f$ = coordinates of atom <em>l</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom1_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param ctr_atom2_pos The position \f$ \vec{p_k} \f$ of the central atom <em>k</em>.
# \param term_atom2_pos The position \f$ \vec{p_l} \f$ of the terminal atom <em>l</em>.
# \param term_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_i}} \f$ at the given atom positions.
# \param ctr_atom1_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_j}} \f$ at the given atom positions.
# \param ctr_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_k}} \f$ at the given atom positions.
# \param term_atom2_deriv Output variable for the calculated partial derivative \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_l}} \f$ at the given atom positions.
# 
# \return The calculated cosine of the dihedral angle \f$ \Phi_{ijkl} \f$.
# 
def calcDihedralAngleCosDerivatives(term_atom1_pos: Math.Vector3D, ctr_atom1_pos: Math.Vector3D, ctr_atom2_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, term_atom1_deriv: Math.Vector3D, ctr_atom1_deriv: Math.Vector3D, ctr_atom2_deriv: Math.Vector3D, term_atom2_deriv: Math.Vector3D) -> float: pass

##
# \brief 
# \param term_atom1_pos 
# \param ctr_atom_pos 
# \param term_atom2_pos 
# \return 
#
def calcBondLengthsAndAngleCos(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D) -> tuple: pass

##
# \brief Calculates the <em>cosine</em> of the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ \cos(\vartheta_{ijk}) = \frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|} \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom <em>k</em>.
# \param r_ij The length of the bond between atom <em>i</em> and <em>j</em>.
# \param r_jk The length of the bond between atom <em>j</em> and <em>k</em>.
# 
# \return The calculated cosine of the bond angle \f$ \vartheta_{ijk} \f$.
# 
def calcBondAngleCos(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, r_ij: float, r_jk: float) -> float: pass

##
# \brief Calculates the <em>cosine</em> of the bond angle \f$ \vartheta_{ijk} \f$ between the two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ \cos(\vartheta_{ijk}) = \frac{\vec{v_{ij}} \cdot \vec{v_{jk}}}{|\vec{v_{ij}}| \: |\vec{v_{jk}}|} \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ij}} = \vec{p_j} - \vec{p_i} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of the terminal atom <em>k</em>.
# 
# \return The calculated cosine of the bond angle \f$ \vartheta_{ijk} \f$.
# 
def calcBondAngleCos(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D) -> float: pass

##
# \brief Calculates the <em>cosine</em> of the dihedral angle \f$ \Phi_{ijkl} \f$ between the planes defined by the atom triplets <em>i-j-k</em> and <em>j-k-l</em>.
# 
# \f$ \cos(\Phi_{ijkl}) = \frac{\vec{n_{ijk}} \cdot \vec{n_{jkl}}}{|\vec{n_{ijk}}| \: |\vec{n_{jkl}}|} \f$<br>
# 
# where<br>
#  \f$ \vec{v_{ji}} = \vec{p_i} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{jk}} = \vec{p_k} - \vec{p_j} \f$<br>
#  \f$ \vec{v_{lk}} = \vec{p_k} - \vec{p_l} \f$<br>
#  \f$ \vec{n_{ijk}} = \vec{v_{ji}} \times \vec{v_{jk}} \f$<br>
#  \f$ \vec{n_{jkl}} = \vec{v_{jk}} \times \vec{v_{lk}} \f$<br>
# 
# \f$ \vec{p_i} \f$ = coordinates of atom <em>i</em>.<br>
#  \f$ \vec{p_j} \f$ = coordinates of atom <em>j</em>.<br>
#  \f$ \vec{p_k} \f$ = coordinates of atom <em>k</em>.<br>
#  \f$ \vec{p_l} \f$ = coordinates of atom <em>l</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom1_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param ctr_atom2_pos The position \f$ \vec{p_k} \f$ of the central atom <em>k</em>.
# \param term_atom2_pos The position \f$ \vec{p_l} \f$ of the terminal atom <em>l</em>.
# 
# \return The calculated cosine of the dihedral angle \f$ \Phi_{ijkl} \f$.
# 
def calcDihedralAngleCos(term_atom1_pos: Math.Vector3D, ctr_atom1_pos: Math.Vector3D, ctr_atom2_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D) -> float: pass

##
# \brief Calculates the electrostatic interaction energy gradient \f$ \nabla EQ_{ij} \f$ for the atom pair <em>i-j</em>.
# 
# Energy function:<br>
# 
# \f$ EQ_{ij} = S \: 332.0716 \: \frac{q_i \: q_j}{D \: (R_{ij} + \delta)^n} \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial EQ_{ij}}{\partial \vec{p_x}} = \frac{\partial EQ_{ij}}{\partial R_{ij}} \: \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$<br>
# 
# \f$ \frac{\partial EQ_{ij}}{\partial R_{ij}} = -S \: 332.0716 \: n \: \frac{q_i \: q_j}{D \: (R_{ij} + \delta)^{n + 1}} \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
# 
# where<br>
#  \f$ S \f$ = a scaling factor depending on the topological distance of <em>i-j</em>.<br>
#  \f$ q_i \f$ and \f$ q_j \f$ = partial atomic charges.<br>
#  \f$ D \f$ = dielectric constant.<br>
#  \f$ R_{ij} \f$ = interatomic distance (Å).<br>
#  \f$ \delta \f$ = electrostatic buffering constant (<em>0.05</em> Å).<br>
#  \f$ n \f$ = exponent (normally <em>1</em>, but can be <em>2</em> for distance-dependent dielectric constant).<br>
#  \f$ \vec{p_x} \f$ = coordinates of the involved atoms <em>i</em> and <em>j</em>.<br>
# 
# Note: 1-4 electrostatic interactions are scaled by <em>0.75</em> (thus, the electrostatic gradient term becomes \f$ EQ_{14} \: 0.75 \f$).
# 
# \param atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param atom2_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param atom1_chg The partial atom charge \f$ q_i \f$ of atom <em>i</em>.
# \param atom2_chg The partial atom charge \f$ q_j \f$ of atom <em>j</em>.
# \param scale_fact The scaling factor for \f$ S \f$ depending on the topological <em>i-j</em> distance.
# \param de_const The dielectric constant \f$ D \f$.
# \param dist_expo The exponent \f$ n \f$.
# 
# \return The calculated electrostatic interaction energy \f$ EQ_{ij} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable!
# 
def calcMMFF94ElectrostaticGradient(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, atom1_grad: Math.Vector3D, atom2_grad: Math.Vector3D, atom1_chg: float, atom2_chg: float, scale_fact: float, de_const: float, dist_expo: float) -> float: pass

##
# \brief Calculates the stretch-bend interaction energy gradient \f$ \nabla EBA_{ijk} \f$ for two bonds <em>i-j</em> and <em>j-k</em>.
# 
# Energy function:<br>
# 
# \f$ EBA_{ijk} = 2.51210 \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \: \Delta \vartheta_{ijk} \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial EBA_{ijk}}{\partial \vec{p_x}} = 2.5121 \: \Delta \vartheta_{ijk} \: (kba_{IJK} \: \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} + kba_{KJI} \: \frac{\partial \Delta r_{kj}}{\partial \vec{p_x}}) + 2.5121 \: \frac{\partial \Delta \vartheta_{ijk}}{\partial \vec{p_x}} \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \f$<br>
# 
# \f$ \frac{\partial \Delta \vartheta_{ijk}}{\partial \vec{p_x}} = \frac{\partial \Delta \vartheta_{ijk}}{\partial \vartheta_{ijk}} \: \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} \: \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$<br>
#  \f$ \frac{\partial \Delta \vartheta_{ijk}}{\partial \vartheta_{ijk}} = \frac{180}{\pi} \f$<br>
#  \f$ \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} = \frac{-1}{\sqrt{1 - \cos(\vartheta_{ijk})^2}} \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$ see calcBondAngleCosDerivatives() and for the calculation of \f$ \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
# 
# where<br>
#  \f$ kba_{IJK} \f$ = force constant in \f$ \frac{md}{rad} \f$ for <em>i-j</em> stretch coupled to <em>i-j-k</em> bend.<br>
#  \f$ kba_{KJI} \f$ = force constant in \f$ \frac{md}{rad} \f$ for <em>k-j</em> stretch coupled to <em>i-j-k</em> bend.<br>
#  \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em>.<br>
#  \f$ \Delta r_{kj} \f$ = \f$ r_{kj} - r_{KJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>k</em> and <em>j</em> of types <em>K</em> and <em>J</em>.<br>
#  \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} \: \frac{180}{\pi} - \vartheta_{IJK}^0 \f$, the difference between actual and reference <em>i-j-k</em> bond angles in degrees.<br>
#  \f$ \vec{p_x} \f$ = coordinates of the involved atoms <em>i</em>, <em>j</em> and <em>k</em>.<br>
# 
# Currently, stretch-bend interactions are omitted when the <em>i-j-k</em> interaction corresponds to a linear bond angle. <br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom <em>k</em>.
# \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param ctr_atom_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>k</em>.
# \param ijk_force_const The stretch-bend force constant \f$ kba_{IJK} \f$.
# \param kji_force_const The stretch-bend force constant \f$ kba_{KJI} \f$.
# \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
# \param ref_length1 The reference bond length \f$ r_{IJ}^0 \f$.
# \param ref_length2 The reference bond length \f$ r_{KJ}^0 \f$.
# 
# \return The calculated stretch-bend interaction energy \f$ EBA_{ijk} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable!
# 
def calcMMFF94StretchBendGradient(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, term_atom1_grad: Math.Vector3D, ctr_atom_grad: Math.Vector3D, term_atom2_grad: Math.Vector3D, ijk_force_const: float, kji_force_const: float, ref_angle: float, ref_length1: float, ref_length2: float) -> float: pass

##
# \brief Calculates the angle bending interaction energy gradient \f$ \nabla EA_{ijk} \f$ for two bonds <em>i-j</em> and <em>j-k</em>.
# 
# Energy function employed for the non-linear case:<br>
# 
# \f$ EA_{ijk} = 0.043844 \: \frac{ka_{IJK}}{2} \: \Delta \vartheta_{ijk}^2 \: (1 + cb \: \Delta \vartheta_{ijk}) \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial EA_{ijk}}{\partial \vec{p_x}} = \frac{\partial EA_{ijk}}{\partial \vartheta_{ijk}} \: \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} \: \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$<br>
# 
# \f$ \frac{\partial EA_{ijk}}{\partial \vartheta_{ijk}} = -ka_{IJK} \: (86.58992538 \: \vartheta_{ijk}^2 - 3.022558594 \: \vartheta_{ijk} \: \vartheta_{IJK}^0 - 143.9313616 \: \vartheta_{ijk} + 0.02637679965 \: \vartheta_{IJK}^{0^2} + 2.512076157 \: \vartheta_{IJK}^0) \f$<br>
#  <br>
#  \f$ \frac{\partial \vartheta_{ijk}}{\partial \cos(\vartheta_{ijk})} = \frac{-1}{\sqrt{1 - \cos(\vartheta_{ijk})^2}} \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$ see calcBondAngleCosDerivatives().
# 
# For linear or near-linear bond angles such as those which occur in alkynes, nitriles, isonitriles, azides, and diazo compounds, the energy function form used in DREIDING and UFF is employed:
# 
# \f$ EA_{ijk} = 143.9325 \: ka_{IJK} \:(1 + \cos(\vartheta_{ijk})) \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial EA_{ijk}}{\partial \vec{p_x}} = 143.9325 \: ka_{IJK} \: \frac{\partial \cos(\vartheta_{ijk})}{\vec{p_x}} \f$<br>
# 
# where<br>
#  \f$ ka_{IJK} \f$ = angle bending force constant in \f$ \frac{md Ang}{rad^2} \f$ for the angle between atoms <em>i</em>, <em>j</em> and <em>k</em> of atom types <em>I</em>, <em>J</em> and <em>K</em>.<br>
#  \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and reference <em>i-j-k</em> bond angles in degrees.<br>
#  \f$ cb \f$ = \f$ -0.007 \: deg^{-1} \f$, the "cubic-bend" constant.<br>
#  \f$ \vec{p_x} \f$ = coordinates of the involved atoms <em>i</em>, <em>j</em> and <em>k</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom <em>k</em>.
# \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param ctr_atom_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>k</em>.
# \param linear If <tt>True</tt>, the bond angle is linear.
# \param force_const The angle bending force constant \f$ ka_{IJK} \f$.
# \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
# 
# \return The calculated angle bending interaction energy \f$ EA_{ijk} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable!
# 
def calcMMFF94AngleBendingGradient(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, term_atom1_grad: Math.Vector3D, ctr_atom_grad: Math.Vector3D, term_atom2_grad: Math.Vector3D, linear: bool, force_const: float, ref_angle: float) -> float: pass

##
# \brief Calculates the out-of-plane bending interaction energy gradient \f$ \nabla EOOP_{ijk;l} \f$ for the bond <em>j-l</em> and the plane <em>i-j-k</em>.
# 
# Energy function:<br>
# 
# \f$ EOOP_{ijk;l} = 0.043844 \: \frac{koop_{IJK \colon L}}{2} \: (\chi_{ijk;l} \: \frac{180}{\pi})^2 \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial EOOP_{ijk;l}}{\partial \vec{p_x}} = \frac{\partial EOOP_{ijk;l}}{\partial \chi_{ijk;l}} \: \frac{\partial \chi_{ijk;l}}{\partial \cos(\alpha_{ijk;l})} \: \frac{\partial \cos(\alpha_{ijk;l})}{\partial \vec{p_x}} \f$<br>
# 
# \f$ \frac{\partial EOOP_{ijk;l}}{\partial \chi_{ijk;l}} = 0.043844 \: (\frac{180}{\pi})^2 \: \chi_{ijk;l} \: koop_{IJK \colon L} \f$<br>
#  \f$ \chi_{ijk;l} = \frac{\pi}{2} - \alpha_{ijk;l} \f$<br>
#  \f$ \frac{\partial \chi_{ijk;l}}{\partial \cos(\alpha_{ijk;l})} = \frac{-1}{\sqrt{1 - \cos(\alpha_{ijk;l})^2}} \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial \cos(\alpha_{ijk;l})}{\partial \vec{p_x}} \f$ see calcOutOfPlaneAngleCosDerivatives().
# 
# where<br>
#  \f$ koop_{IJK \colon L} \f$ = out-of-plane bending force constant in \f$ \frac{md Ang}{rad^2} \f$.<br>
#  \f$ \chi_{ijk;l} \f$ = angle in radians between the bond <em>j-l</em> and the plane <em>i-j-k</em>, where <em>j</em> is the central atom.<br>
#  \f$ \vec{p_x} \f$ = coordinates of the involved atoms <em>i</em>, <em>j</em>, <em>k</em> and <em>l</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param ctr_atom_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param term_atom2_pos The position \f$ \vec{p_k} \f$ of atom <em>k</em>.
# \param oop_atom_pos The position \f$ \vec{p_l} \f$ of the out-of-plane atom <em>l</em>.
# \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param ctr_atom_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>k</em>.
# \param oop_atom_grad The output variable storing the accumulated energy gradient contributions for atom <em>l</em>.
# \param force_const The out-of-plane bending force constant \f$ koop_{IJK \colon L} \f$.
# 
# \return The calculated out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable!
# 
def calcMMFF94OutOfPlaneBendingGradient(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, oop_atom_pos: Math.Vector3D, term_atom1_grad: Math.Vector3D, ctr_atom_grad: Math.Vector3D, term_atom2_grad: Math.Vector3D, oop_atom_grad: Math.Vector3D, force_const: float) -> float: pass

##
# \brief Calculates the bond stretching interaction energy gradient \f$ \nabla EB_{ij} \f$ for the bond <em>i-j</em>.
# 
# Energy function:<br>
# 
# \f$ EB_{ij} = 143.9325 \: \frac{kb_{IJ}}{2} \: \Delta r_{ij}^2 \times (1 + cs \: \Delta r_{ij} + \frac{7}{12} \: cs^2 \: \Delta r_{ij}^2) \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial EB_{ij}}{\partial \vec{p_x}} = \frac{\partial EB_{ij}}{\partial \Delta r_{ij}} \: \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$<br>
# 
# \f$ \frac{\partial EB_{ij}}{\partial \Delta r_{ij}} = (167.92125 \: \Delta r_{ij}^3 \: cs^2 + 215.89875 \: \Delta r_{ij}^2 \: cs + 143.9325 \: \Delta r_{ij}) \: kb_{IJ} \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
# 
# where<br>
#  \f$ kb_{IJ} \f$ = the bond stretching force constant in \f$ \frac{md}{Ang} \f$ for bonded atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em>.<br>
#  \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em>.<br>
#  \f$ cs \f$ = \f$ -2 \: Ang^{-1} \f$, the "cubic stretch" constant.<br>
#  \f$ \vec{p_x} \f$ = coordinates of the involved atoms <em>i</em> and <em>j</em>.<br>
# 
# Note: throughout this description, the indices <em>i</em>, <em>j</em>, <em>k</em>, ... represent atoms; <em>I</em>, <em>J</em>, <em>K</em>, ... denote the corresponding numerical MMFF atom types (or, occasionally, the atomic species).
# 
# \param atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param atom2_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param force_const The bond stretching force constant \f$ kb_{IJ} \f$.
# \param ref_length The reference bond length \f$ r_{IJ}^0 \f$.
# 
# \return The calculated bond stretching interaction energy \f$ EB_{ij} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable!
# 
def calcMMFF94BondStretchingGradient(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, atom1_grad: Math.Vector3D, atom2_grad: Math.Vector3D, force_const: float, ref_length: float) -> float: pass

##
# \brief Calculates the elastic potential energy gradient \f$ \nabla E_{ij} \f$ for a pair of atoms <em>i-j</em>.
# 
# Energy function:<br>
# 
# \f$ E_{ij} = k_{ij} \: \Delta r_{ij}^2 \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial E_{ij}}{\partial \vec{p_x}} = \frac{\partial E_{ij}}{\partial \Delta r_{ij}} \: \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$<br>
# 
# \f$ \frac{\partial E_{ij}}{\partial \Delta r_{ij}} = 2 \: \Delta r_{ij} \: k_{ij} \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial \Delta r_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
# 
# where<br>
#  \f$ k_{ij} \f$ = the force constant of the elastic potential.<br>
#  \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{ij}^0 \f$, the difference between actual and reference distance of the atoms <em>i</em> and <em>j</em>.<br>
#  \f$ \vec{p_x} \f$ = coordinates of the atoms <em>i</em> and <em>j</em>.<br>
# 
# \param atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param atom2_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param force_const The force constant \f$ k_{ij} \f$.
# \param ref_length The reference distance \f$ r_{ij}^0 \f$.
# 
# \return The calculated elastic potential energy \f$ E_{ij} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable! 
# 
# \since 1.1
# 
def calcElasticPotentialGradient(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, atom1_grad: Math.Vector3D, atom2_grad: Math.Vector3D, force_const: float, ref_length: float) -> float: pass

##
# \brief Calculates the torsion interaction energy gradient \f$ \nabla ET_{ijkl} \f$ for the central bond <em>j-k</em> and the connected bonds <em>i-j</em> and <em>k-l</em>.
# 
# Energy function:<br>
# 
# \f$ ET_{ijkl} = 0.5 \: (V_1 \: (1 + \cos(\Phi_{ijkl})) + V_2 \: (1 - \cos(2 \: \Phi_{ijkl})) + V_3 \: (1 + \cos(3 \: \Phi_{ijkl}))) \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial ET_{ijkl}}{\partial \vec{p_x}} = \frac{\partial ET_{ijkl}}{\partial \Phi_{ijkl}} \: \frac{\partial \Phi_{ijkl}}{\partial \cos(\Phi_{ijkl})} \: \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_x}} \f$<br>
# 
# \f$ \frac{\partial ET_{ijkl}}{\partial \Phi_{ijkl}} = V_2 \: \sin(2 \: \Phi_{ijkl}) - 0.5 \: V_1 \: \sin(\Phi_{ijkl}) - 1.5 \: V_3 \: \sin(3 \: \Phi_{ijkl}) \f$<br>
#  \f$ \frac{\partial \Phi_{ijkl}}{\partial \cos(\Phi_{ijkl})} = \frac{-1}{\sqrt{1 - \cos(\Phi_{ijkl})^2}} \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial \cos(\Phi_{ijkl})}{\partial \vec{p_x}} \f$ see calcDihedralAngleCosDerivatives().
# 
# where<br>
#  \f$ \Phi_{ijkl} \f$ is the <em>i-j-k-l</em> dihedral angle. The constants \f$ V_1 \f$, \f$ V_2 \f$ and \f$ V_3 \f$ depend on the atom types <em>I</em>, <em>J</em>, <em>K</em> and <em>L</em> for atoms <em>i</em>, <em>j</em>, <em>k</em> and <em>l</em>, where <em>i-j</em>, <em>j-k</em> and <em>k-l</em> are bonded pairs and <em>i</em> is not equal to <em>l</em>.<br>
#  <br>
#  \f$ \vec{p_x} \f$ = coordinates of the involved atoms <em>i</em>, <em>j</em>, <em>k</em> and <em>l</em>.<br>
# 
# \param term_atom1_pos The position \f$ \vec{p_i} \f$ of the terminal atom <em>i</em>.
# \param ctr_atom1_pos The position \f$ \vec{p_j} \f$ of the central atom <em>j</em>.
# \param ctr_atom2_pos The position \f$ \vec{p_k} \f$ of the central atom <em>k</em>.
# \param term_atom2_pos The position \f$ \vec{p_l} \f$ of the terminal atom <em>l</em>.
# \param term_atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param ctr_atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param ctr_atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>k</em>.
# \param term_atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>l</em>.
# \param tor_param1 The torsion parameter \f$ V_1 \f$.
# \param tor_param2 The torsion parameter \f$ V_2 \f$.
# \param tor_param3 The torsion parameter \f$ V_3 \f$.
# 
# \return The calculated torsion interaction energy \f$ ET_{ijkl} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable!
# 
def calcMMFF94TorsionGradient(term_atom1_pos: Math.Vector3D, ctr_atom1_pos: Math.Vector3D, ctr_atom2_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, term_atom1_grad: Math.Vector3D, ctr_atom1_grad: Math.Vector3D, ctr_atom2_grad: Math.Vector3D, term_atom2_grad: Math.Vector3D, tor_param1: float, tor_param2: float, tor_param3: float) -> float: pass

##
# \brief Calculates the van der Waals interaction energy gradient \f$ \nabla E_{vdW_{ij}} \f$ for the atom pair <em>i-j</em>.
# 
# Energy function:<br>
#  \f$ E_{vdW_{ij}} = \varepsilon_{IJ} \: (\frac{1.07 \: R_{IJ}^*}{(R_{ij} + 0.07 \: R_{IJ}^*)})^7 \: (\frac{1.12 \: R_{IJ}^{*^7}}{(R_{ij}^7 + 0.12 \: R_{IJ}^{*^7})} - 2) \;\;\;\; (1) \f$
# 
# The partial derivatives with respect to the atom coordinates \f$ \vec{p_x} \f$ are calculated by:<br>
# 
# \f$ \frac{\partial E_{vdW_{ij}}}{\partial \vec{p_x}} = \frac{\partial E_{vdW_{ij}}}{\partial R_{ij}} \: \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$<br>
# 
# \f$ \frac{\partial E_{vdW_{ij}}}{\partial R_{ij}} = \frac{-R_{IJ}^{*^7} \: \varepsilon_{IJ}}{(R_{ij} + 0.07 \: R_{IJ}^*)^8 \: (R_{ij}^7 + 0.12 \: R_{IJ}^{*^7})^2} \: (-22.48094067 \: R_{ij}^{14} + 19.78322779 \: R_{ij}^7 \: R_{IJ}^{*^7} + 0.8812528743 \: R_{ij}^6 \: R_{IJ}^{*^8} + 1.186993667 \: R_{IJ}^{*^{14}}) \f$<br>
# 
# for the calculation of the partial derivatives \f$ \frac{\partial R_{ij}}{\partial \vec{p_x}} \f$ see calcDistanceDerivatives().
# 
# where<br>
#  \f$ R_{ij} \f$ = the interatomic distance.<br>
#  \f$ R_{II}^* = A_I \: \alpha_I^{PEXP} \;\;\;\; (2) \f$<br>
#  \f$ R_{IJ}^* = 0.5 \: (R_{II}^* + R_{JJ}^*) \: (1 + AFACT(1 - \exp(-BFACT \: \gamma_{IJ}^2))) \;\;\;\; (3) \f$<br>
#  \f$ \gamma_{IJ} = \frac{(R_{II}^* - R_{JJ}^*)}{(R_{II}^* + R_{JJ}^*)} \;\;\;\; (4) \f$ <br>
#  \f$ \varepsilon_{IJ} = \frac{181.16 \: G_I \: GJ \: \alpha_I \: \alpha_J}{((\alpha_I / N_I)^{1/2} + (\alpha_J / N_J)^{1/2})} \: \frac{1}{R_{IJ}^{*6}} \;\;\;\; (5) \f$<br>
#  \f$ \vec{p_x} \f$ = coordinates of the involved atoms <em>i</em> and <em>j</em>.<br>
# 
# MMFF employs a "Buffered 14-7" form (eq 1) together with an expression which relates the minimum-gradient separation \f$ R_{II}^* \f$ to the atomic polarizability \f$ \alpha_I \f$ (eq 2), a specially formulated combination rule (eqs 3, 4), and a Slater-Kirkwood expression for the well depth \f$ \varepsilon_{IJ} \f$ (eq 5): The first non-comment line in the parameter file "MMFFVDW.PAR" contains five floating point numbers which define the variables <em>PEXP</em>, <em>AFACT</em>, <em>BFACT</em>, <em>DARAD</em>, and <em>DAEPS</em>, respectively. <em>PEXP</em> (currently <em>0.25</em>), <em>AFACT</em> (currently <em>0.2</em>) and <em>BFACT</em> (currently <em>12.0</em>) are used in the equations shown above; <em>DARAD</em> and <em>DAEPS</em> are used as follows:
# 
# When either <em>i</em> or <em>j</em> is a hydrogen-bond donor, MMFF uses the simple arithmetic mean \f$ 0.5 \: (R_{II}^* + R_{JJ}^*) \f$ instead of eq 3 to obtain \f$ R_{IJ}^* \f$. If the <em>i-j</em> interaction is a donor-acceptor interaction, MMFF also scales \f$ R_{IJ}^* \f$ as given by eq 3 by <em>DARAD</em> (currently <em>0.8</em>) and \f$ \varepsilon_{IJ} \f$ as given by eq 5 by <em>DAEPS</em> (currently <em>0.5</em>).
# 
# \param atom1_pos The position \f$ \vec{p_i} \f$ of atom <em>i</em>.
# \param atom2_pos The position \f$ \vec{p_j} \f$ of atom <em>j</em>.
# \param atom1_grad The output variable storing the accumulated energy gradient contributions for atom <em>i</em>.
# \param atom2_grad The output variable storing the accumulated energy gradient contributions for atom <em>j</em>.
# \param e_IJ The precalculated value \f$ \varepsilon_{IJ} \f$.
# \param r_IJ The precalculated value \f$ R_{IJ}^* \f$.
# \param r_IJ_7 The precalculated value \f$ R_{IJ}^{*^7} \f$.
# 
# \return The calculated van der Waals interaction energy \f$ E_{vdW_{ij}} \f$. 
# 
# \note The calculated partial energy derivative (see above) for an atom gets <em>added</em> to the corresponding output variable!
# 
def calcMMFF94VanDerWaalsGradient(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, atom1_grad: Math.Vector3D, atom2_grad: Math.Vector3D, e_IJ: float, r_IJ: float, r_IJ_7: float) -> float: pass

##
# \brief Calculates the electrostatic interaction energy \f$ EQ_{ij} \f$ for the atom pair <em>i-j</em>.
# 
# \f$ EQ_{ij} = S \: 332.0716 \: \frac{q_i \: q_j}{D \: (R_{ij} + \delta)^n} \f$
# 
# where<br>
#  \f$ S \f$ = a scaling factor depending on the topological distance of <em>i-j</em>.<br>
#  \f$ q_i \f$ and \f$ q_j \f$ = Partial atomic charges.<br>
#  \f$ D \f$ = Dielectric constant.<br>
#  \f$ R_{ij} \f$ = Interatomic distance (Å) (see calcDistance()).<br>
#  \f$ \delta \f$ = Electrostatic buffering constant (<em>0.05</em> Å).<br>
#  \f$ n \f$ = Exponent (normally <em>1</em>, but can be <em>2</em> for distance-dependent dielectric constant).<br>
# 
# Note: 1-4 electrostatic interactions are scaled by <em>0.75</em> (thus, the electrostatic energy term becomes \f$ EQ_{14} \: 0.75 \f$).
# 
# \param atom1_pos The position of atom <em>i</em>.
# \param atom2_pos The position of atom <em>j</em>.
# \param atom1_chg The partial atom charge \f$ q_i \f$ of atom <em>i</em>.
# \param atom2_chg The partial atom charge \f$ q_j \f$ of atom <em>j</em>.
# \param scale_fact The scaling factor for \f$ S \f$ depending on the topological <em>i-j</em> distance.
# \param de_const The dielectric constant \f$ D \f$.
# \param dist_expo The exponent \f$ n \f$.
# 
# \return The calculated electrostatic interaction energy \f$ EQ_{ij} \f$.
# 
def calcMMFF94ElectrostaticEnergy(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, atom1_chg: float, atom2_chg: float, scale_fact: float, de_const: float, dist_expo: float) -> float: pass

##
# \brief Calculates the stretch-bend interaction energy \f$ EBA_{ijk} \f$ for two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ EBA_{ijk} = 2.51210 \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \: \Delta \vartheta_{ijk} \f$
# 
# where<br>
#  \f$ kba_{IJK} \f$ = force constant in \f$ \frac{md}{rad} \f$ for <em>i-j</em> stretch coupled to <em>i-j-k</em> bend.<br>
#  \f$ kba_{KJI} \f$ = force constant in \f$ \frac{md}{rad} \f$ for <em>k-j</em> stretch coupled to <em>i-j-k</em> bend.<br>
#  \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em>.<br>
#  \f$ \Delta r_{kj} \f$ = \f$ r_{kj} - r_{KJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>k</em> and <em>j</em> of types <em>K</em> and <em>J</em>.<br>
#  \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and reference <em>i-j-k</em> bond angles in degrees.<br>
# 
# For the calculation of \f$ r_{ij} \f$, \f$ r_{kj} \f$, and \f$ \vartheta_{ijk} \f$ see calcBondLengthsAndAngle().
# 
# Currently, stretch-bend interactions are omitted when the <em>i-j-k</em> interaction corresponds to a linear bond angle. <br>
# 
# \param term_atom1_pos The position of atom <em>i</em>.
# \param ctr_atom_pos The position of the central atom <em>j</em>.
# \param term_atom2_pos The position of atom <em>k</em>.
# \param ijk_force_const The stretch-bend force constant \f$ kba_{IJK} \f$.
# \param kji_force_const The stretch-bend force constant \f$ kba_{KJI} \f$.
# \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
# \param ref_length1 The reference bond length \f$ r_{IJ}^0 \f$.
# \param ref_length2 The reference bond length \f$ r_{KJ}^0 \f$.
# 
# \return The calculated stretch-bend interaction energy \f$ EBA_{ijk} \f$.
# 
def calcMMFF94StretchBendEnergy(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, ijk_force_const: float, kji_force_const: float, ref_angle: float, ref_length1: float, ref_length2: float) -> float: pass

##
# \brief Calculates the stretch-bend interaction energy \f$ EBA_{ijk} \f$ for two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ EBA_{ijk} = 2.51210 \: (kba_{IJK} \: \Delta r_{ij} + kba_{KJI} \: \Delta r_{kj}) \: \Delta \vartheta_{ijk} \f$
# 
# where<br>
#  \f$ kba_{IJK} \f$ = force constant in \f$ \frac{md}{rad} \f$ for <em>i-j</em> stretch coupled to <em>i-j-k</em> bend.<br>
#  \f$ kba_{KJI} \f$ = force constant in \f$ \frac{md}{rad} \f$ for <em>k-j</em> stretch coupled to <em>i-j-k</em> bend.<br>
#  \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em>.<br>
#  \f$ \Delta r_{kj} \f$ = \f$ r_{kj} - r_{KJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>k</em> and <em>j</em> of types <em>K</em> and <em>J</em>.<br>
#  \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and reference <em>i-j-k</em> bond angles in degrees.<br>
# 
# For the calculation of \f$ r_{ij} \f$, \f$ r_{kj} \f$, and \f$ \vartheta_{ijk} \f$ see calcBondLengthsAndAngle().
# 
# Currently, stretch-bend interactions are omitted when the <em>i-j-k</em> interaction corresponds to a linear bond angle. <br>
# 
# \param term_atom1_pos The position of atom <em>i</em>.
# \param ctr_atom_pos The position of the central atom <em>j</em>.
# \param term_atom2_pos The position of atom <em>k</em>.
# \param r_ij The length of the bond between atom <em>i</em> and <em>j</em>.
# \param r_jk The length of the bond between atom <em>j</em> and <em>k</em>.
# \param ijk_force_const The stretch-bend force constant \f$ kba_{IJK} \f$.
# \param kji_force_const The stretch-bend force constant \f$ kba_{KJI} \f$.
# \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
# \param ref_length1 The reference bond length \f$ r_{IJ}^0 \f$.
# \param ref_length2 The reference bond length \f$ r_{KJ}^0 \f$.
# 
# \return The calculated stretch-bend interaction energy \f$ EBA_{ijk} \f$.
# 
def calcMMFF94StretchBendEnergy(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, r_ij: float, r_jk: float, ijk_force_const: float, kji_force_const: float, ref_angle: float, ref_length1: float, ref_length2: float) -> float: pass

##
# \brief Calculates the angle bending interaction energy \f$ EA_{ijk} \f$ for two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ EA_{ijk} = 0.043844 \: \frac{ka_{IJK}}{2} \: \Delta \vartheta_{ijk}^2 \: (1 + cb \: \Delta \vartheta_{ijk}) \f$
# 
# where<br>
#  \f$ ka_{IJK} \f$ = angle bending force constant in \f$ \frac{md Ang}{rad^2} \f$ for the angle between atoms <em>i</em>, <em>j</em> and <em>k</em> of atom types <em>I</em>, <em>J</em> and <em>K</em>.<br>
#  \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and reference <em>i-j-k</em> bond angles in degrees (see calcBondAngle()).<br>
#  \f$ cb \f$ = \f$ -0.007 \: deg^{-1} \f$, the "cubic-bend" constant.<br>
# 
# For linear or near-linear bond angles such as those which occur in alkynes, nitriles, isonitriles, azides, and diazo compounds, the form used in DREIDING and UFF is employed:
# 
# \f$ EA_{ijk} = 143.9325 \: ka_{IJK} \:(1 + \cos(\vartheta_{ijk})) \f$
# 
# where \f$ ka_{IJK} \f$ and \f$ \vartheta_{ijk} \f$ are defined as above.
# 
# \param term_atom1_pos The position of atom <em>i</em>.
# \param ctr_atom_pos The position of the central atom <em>j</em>.
# \param term_atom2_pos The position of atom <em>k</em>.
# \param linear If <tt>True</tt>, the bond angle is linear.
# \param force_const The angle bending force constant \f$ ka_{IJK} \f$.
# \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
# 
# \return The calculated angle bending interaction energy \f$ EA_{ijk} \f$.
# 
def calcMMFF94AngleBendingEnergy(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, linear: bool, force_const: float, ref_angle: float) -> float: pass

##
# \brief Calculates the angle bending interaction energy \f$ EA_{ijk} \f$ for two bonds <em>i-j</em> and <em>j-k</em>.
# 
# \f$ EA_{ijk} = 0.043844 \: \frac{ka_{IJK}}{2} \: \Delta \vartheta_{ijk}^2 \: (1 + cb \: \Delta \vartheta_{ijk}) \f$
# 
# where<br>
#  \f$ ka_{IJK} \f$ = angle bending force constant in \f$ \frac{md Ang}{rad^2} \f$ for the angle between atoms <em>i</em>, <em>j</em> and <em>k</em> of atom types <em>I</em>, <em>J</em> and <em>K</em>.<br>
#  \f$ \Delta \vartheta_{ijk} \f$ = \f$ \vartheta_{ijk} - \vartheta_{IJK}^0 \f$, the difference between actual and reference <em>i-j-k</em> bond angles in degrees (see calcBondAngle()).<br>
#  \f$ cb \f$ = \f$ -0.007 \: deg^{-1} \f$, the "cubic-bend" constant.<br>
# 
# For linear or near-linear bond angles such as those which occur in alkynes, nitriles, isonitriles, azides, and diazo compounds, the form used in DREIDING and UFF is employed:
# 
# \f$ EA_{ijk} = 143.9325 \: ka_{IJK} \:(1 + \cos(\vartheta_{ijk})) \f$
# 
# where \f$ ka_{IJK} \f$ and \f$ \vartheta_{ijk} \f$ are defined as above.
# 
# \param term_atom1_pos The position of atom <em>i</em>.
# \param ctr_atom_pos The position of the central atom <em>j</em>.
# \param term_atom2_pos The position of atom <em>k</em>.
# \param r_ij The length of the bond between atom <em>i</em> and <em>j</em>.
# \param r_jk The length of the bond between atom <em>j</em> and <em>k</em>.
# \param linear If <tt>True</tt>, the bond angle is linear.
# \param force_const The angle bending force constant \f$ ka_{IJK} \f$.
# \param ref_angle The reference bond angle \f$ \vartheta_{IJK}^0 \f$.
# 
# \return The calculated angle bending interaction energy \f$ EA_{ijk} \f$.
# 
def calcMMFF94AngleBendingEnergy(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, r_ij: float, r_jk: float, linear: bool, force_const: float, ref_angle: float) -> float: pass

##
# \brief Calculates the out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$ for the bond <em>j-l</em> and the plane <em>i-j-k</em>.
# 
# \f$ EOOP_{ijk;l} = 0.043844 \: \frac{koop_{IJK \colon L}}{2} \: \chi_{ijk;l}^2 \f$
# 
# where<br>
#  \f$ koop_{IJK \colon L} \f$ = out-of-plane bending force constant in \f$ \frac{md Ang}{rad^2} \f$.<br>
#  \f$ \chi_{ijk;l} \f$ = angle in degrees between the bond <em>j-l</em> and the plane <em>i-j-k</em>, where <em>j</em> is the central atom (see calcOutOfPlaneAngle()).<br>
# 
# \param term_atom1_pos The position of atom <em>i</em>.
# \param ctr_atom_pos The position of the central atom <em>j</em>.
# \param term_atom2_pos The position of atom <em>k</em>.
# \param oop_atom_pos The position of the out-of-plane atom <em>l</em>.
# \param force_const The out-of-plane bending force constant \f$ koop_{IJK \colon L} \f$.
# 
# \return The calculated out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$.
# 
def calcMMFF94OutOfPlaneBendingEnergy(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, oop_atom_pos: Math.Vector3D, force_const: float) -> float: pass

##
# \brief Calculates the out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$ for the bond <em>j-l</em> and the plane <em>i-j-k</em>.
# 
# \f$ EOOP_{ijk;l} = 0.043844 \: \frac{koop_{IJK \colon L}}{2} \: \chi_{ijk;l}^2 \f$
# 
# where<br>
#  \f$ koop_{IJK \colon L} \f$ = out-of-plane bending force constant in \f$ \frac{md Ang}{rad^2} \f$.<br>
#  \f$ \chi_{ijk;l} \f$ = angle in degrees between the bond <em>j-l</em> and the plane <em>i-j-k</em>, where <em>j</em> is the central atom (see calcOutOfPlaneAngle()).<br>
# 
# \param term_atom1_pos The position of atom <em>i</em>.
# \param ctr_atom_pos The position of the central atom <em>j</em>.
# \param term_atom2_pos The position of atom <em>k</em>.
# \param oop_atom_pos The position of the out-of-plane atom <em>l</em>.
# \param r_jl The length of the bond between atom <em>j</em> and atom <em>l</em>.
# \param force_const The out-of-plane bending force constant \f$ koop_{IJK \colon L} \f$.
# 
# \return The calculated out-of-plane bending interaction energy \f$ EOOP_{ijk;l} \f$.
# 
def calcMMFF94OutOfPlaneBendingEnergy(term_atom1_pos: Math.Vector3D, ctr_atom_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, oop_atom_pos: Math.Vector3D, r_jl: float, force_const: float) -> float: pass

##
# \brief Calculates the bond stretching interaction energy \f$ EB_{ij} \f$ for the bond <em>i-j</em>.
# 
# \f$ EB_{ij} = 143.9325 \: \frac{kb_{IJ}}{2} \: \Delta r_{ij}^2 \times (1 + cs \: \Delta r_{ij} + \frac{7}{12} \: cs^2 \: \Delta r_{ij}^2) \f$
# 
# where<br>
#  \f$ kb_{IJ} \f$ = the bond stretching force constant in \f$ \frac{md}{Ang} \f$ for bonded atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em>.<br>
#  \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{IJ}^0 \f$, the difference in angstroms between actual and reference bond lengths between bonded atoms <em>i</em> and <em>j</em> of types <em>I</em> and <em>J</em> (see calcDistance()).<br>
#  \f$ cs \f$ = \f$ -2 \: Ang^{-1} \f$, the "cubic stretch" constant.<br>
# 
# Note: throughout this description, the indices <em>i</em>, <em>j</em>, <em>k</em>, ... represent atoms; <em>I</em>, <em>J</em>, <em>K</em>, ... denote the corresponding numerical MMFF atom types (or, occasionally, the atomic species).
# 
# \param atom1_pos The position of atom <em>i</em>.
# \param atom2_pos The position of atom <em>j</em>.
# \param force_const The bond stretching force constant \f$ kb_{IJ} \f$.
# \param ref_length The reference bond length \f$ r_{IJ}^0 \f$.
# 
# \return The calculated bond stretching interaction energy \f$ EB_{ij} \f$.
# 
def calcMMFF94BondStretchingEnergy(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, force_const: float, ref_length: float) -> float: pass

##
# \brief Calculates the energy \f$ E_{ij} \f$ of an elastic potential applied on a pair of atoms <em>i-j</em>.
# 
# \f$ E_{ij} = k_{ij} \: \Delta r_{ij}^2 \f$
# 
# where<br>
#  \f$ k_{ij} \f$ = the force constant of the elastic potential.<br>
#  \f$ \Delta r_{ij} \f$ = \f$ r_{ij} - r_{ij}^0 \f$, the difference between actual and reference distance of the atoms <em>i</em> and <em>j</em>.<br>
# 
# \param atom1_pos The position of atom <em>i</em>.
# \param atom2_pos The position of atom <em>j</em>.
# \param force_const The force constant \f$ k_{ij} \f$.
# \param ref_length The reference distance \f$ r_{ij}^0 \f$.
# 
# \return The calculated elastic potential energy \f$ E_{ij} \f$. 
# 
# \since 1.1
# 
def calcElasticPotentialEnergy(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, force_const: float, ref_length: float) -> float: pass

##
# \brief Calculates the torsion interaction energy \f$ ET_{ijkl} \f$ for the central bond <em>j-k</em> and the connected bonds <em>i-j</em> and <em>k-l</em>.
# 
# \f$ ET_{ijkl} = 0.5 \: (V_1 \: (1 + \cos(\Phi_{ijkl})) + V_2 \: (1 - \cos(2 \: \Phi_{ijkl})) + V_3 \: (1 + \cos(3 \: \Phi_{ijkl}))) \f$
# 
# where \f$ \Phi_{ijkl} \f$ is the <em>i-j-k-l</em> dihedral angle. The constants \f$ V_1 \f$, \f$ V_2 \f$ and \f$ V_3 \f$ depend on the atom types <em>I</em>, <em>J</em>, <em>K</em> and <em>L</em> for atoms <em>i</em>, <em>j</em>, <em>k</em> and <em>l</em>, where <em>i-j</em>, <em>j-k</em> and <em>k-l</em> are bonded pairs and <em>i</em> is not equal to <em>l</em>. <br>
# 
# For the calculation of \f$ \cos(\Phi_{ijkl}) \f$ see calcDihedralAngleCos().
# 
# \param term_atom1_pos The position of the terminal atom <em>i</em>.
# \param ctr_atom1_pos The position of the central atom <em>j</em>.
# \param ctr_atom2_pos The position of the central atom <em>k</em>.
# \param term_atom2_pos The position of the terminal atom <em>l</em>.
# \param tor_param1 The torsion parameter \f$ V_1 \f$.
# \param tor_param2 The torsion parameter \f$ V_2 \f$.
# \param tor_param3 The torsion parameter \f$ V_3 \f$.
# 
# \return The calculated torsion interaction energy \f$ ET_{ijkl} \f$.
# 
def calcMMFF94TorsionEnergy(term_atom1_pos: Math.Vector3D, ctr_atom1_pos: Math.Vector3D, ctr_atom2_pos: Math.Vector3D, term_atom2_pos: Math.Vector3D, tor_param1: float, tor_param2: float, tor_param3: float) -> float: pass

##
# \brief Calculates the van der Waals interaction energy \f$ E_{vdW_{ij}} \f$ for the atom pair <em>i-j</em>.
# 
# \f$ E_{vdW_{ij}} = \varepsilon_{IJ} \: (\frac{1.07 \: R_{IJ}^*}{(R_{ij} + 0.07 \: R_{IJ}^*)})^7 \: (\frac{1.12 \: R_{IJ}^{*^7}}{(R_{ij}^7 + 0.12 \: R_{IJ}^{*^7})} - 2) \;\;\;\; (1) \f$
# 
# where<br>
#  \f$ R_{ij} \f$ = the interatomic distance (see calcDistance()).<br>
#  \f$ R_{II}^* = A_I \: \alpha_I^{PEXP} \;\;\;\; (2) \f$<br>
#  \f$ R_{IJ}^* = 0.5 \: (R_{II}^* + R_{JJ}^*) \: (1 + AFACT(1 - \exp(-BFACT \: \gamma_{IJ}^2))) \;\;\;\; (3) \f$<br>
#  \f$ \gamma_{IJ} = \frac{(R_{II}^* - R_{JJ}^*)}{(R_{II}^* + R_{JJ}^*)} \;\;\;\; (4) \f$ <br>
#  \f$ \varepsilon_{IJ} = \frac{181.16 \: G_I \: GJ \: \alpha_I \: \alpha_J}{((\alpha_I / N_I)^{1/2} + (\alpha_J / N_J)^{1/2})} \: \frac{1}{R_{IJ}^{*^6}} \;\;\;\; (5) \f$<br>
# 
# MMFF employs a "Buffered 14-7" form (eq 1) together with an expression which relates the minimum-energy separation \f$ R_{II}^* \f$ to the atomic polarizability \f$ \alpha_I \f$ (eq 2), a specially formulated combination rule (eqs 3, 4), and a Slater-Kirkwood expression for the well depth \f$ \varepsilon_{IJ} \f$ (eq 5): The first non-comment line in the parameter file "MMFFVDW.PAR" contains five floating point numbers which define the variables <em>PEXP</em>, <em>AFACT</em>, <em>BFACT</em>, <em>DARAD</em>, and <em>DAEPS</em>, respectively. <em>PEXP</em> (currently <em>0.25</em>), <em>AFACT</em> (currently <em>0.2</em>) and <em>BFACT</em> (currently <em>12.0</em>) are used in the equations shown above; <em>DARAD</em> and <em>DAEPS</em> are used as follows:
# 
# When either <em>i</em> or <em>j</em> is a hydrogen-bond donor, MMFF uses the simple arithmetic mean \f$ 0.5 \: (R_{II}^* + R_{JJ}^*) \f$ instead of eq 3 to obtain \f$ R_{IJ}^* \f$. If the <em>i-j</em> interaction is a donor-acceptor interaction, MMFF also scales \f$ R_{IJ}^* \f$ as given by eq 3 by <em>DARAD</em> (currently <em>0.8</em>) and \f$ \varepsilon_{IJ} \f$ as given by eq 5 by <em>DAEPS</em> (currently <em>0.5</em>).
# 
# \param atom1_pos The position of atom <em>i</em>.
# \param atom2_pos The position of atom <em>j</em>.
# \param e_IJ The precalculated value \f$ \varepsilon_{IJ} \f$.
# \param r_IJ The precalculated value \f$ R_{IJ}^* \f$.
# \param r_IJ_7 The precalculated value \f$ R_{IJ}^{*^7} \f$.
# 
# \return The calculated van der Waals interaction energy \f$ E_{vdW_{ij}} \f$.
# 
def calcMMFF94VanDerWaalsEnergy(atom1_pos: Math.Vector3D, atom2_pos: Math.Vector3D, e_IJ: float, r_IJ: float, r_IJ_7: float) -> float: pass
