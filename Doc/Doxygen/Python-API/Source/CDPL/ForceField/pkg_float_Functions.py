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
# \param r_ij The interatomic distance \f$ R_{ij} \f$ of atom <em>i</em> and atom <em>j</em>.
# \param atom1_chg The partial atom charge \f$ q_i \f$ of atom <em>i</em>.
# \param atom2_chg The partial atom charge \f$ q_j \f$ of atom <em>j</em>.
# \param scale_fact The scaling factor for \f$ S \f$ depending on the topological <em>i-j</em> distance.
# \param de_const The dielectric constant \f$ D \f$.
# \param dist_expo The exponent \f$ n \f$.
# 
# \return The calculated electrostatic interaction energy \f$ EQ_{ij} \f$.
# 
def calcMMFF94ElectrostaticEnergy(r_ij: float, atom1_chg: float, atom2_chg: float, scale_fact: float, de_const: float, dist_expo: float) -> float: pass

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
# \param r_ij The length of the bond between atom <em>i</em> and <em>j</em>.
# \param force_const The bond stretching force constant \f$ kb_{IJ} \f$.
# \param ref_length The reference bond length \f$ r_{IJ}^0 \f$.
# 
# \return The calculated bond stretching interaction energy \f$ EB_{ij} \f$.
# 
def calcMMFF94BondStretchingEnergy(r_ij: float, force_const: float, ref_length: float) -> float: pass

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
# \param r_ij The interatomic distance \f$ R_{ij} \f$ of atom <em>i</em> and atom <em>j</em>.
# \param e_IJ The precalculated value \f$ \varepsilon_{IJ} \f$.
# \param r_IJ The precalculated value \f$ R_{IJ}^* \f$.
# \param r_IJ_7 The precalculated value \f$ R_{IJ}^{*^7} \f$.
# 
# \return The calculated van der Waals interaction energy \f$ E_{vdW_{ij}} \f$.
# 
def calcMMFF94VanDerWaalsEnergy(r_ij: float, e_IJ: float, r_IJ: float, r_IJ_7: float) -> float: pass
