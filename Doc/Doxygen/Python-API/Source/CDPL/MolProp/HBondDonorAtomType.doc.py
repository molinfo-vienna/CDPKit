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
# \brief Provides constants used to specify the structural class of H-bond donor atoms.
# 
class HBondDonorAtomType(Boost.Python.instance):

    ##
    # \brief Specifies that the H-bond donor type of the atom is undefined.
    # 
    UNDEF = 0

    ##
    # \brief Specifies that the atom is not a H-bond donor.
    # 
    NONE = 1

    ##
    # \brief Iodine donor of hydrogen iodide.
    # 
    I_HI = 2

    ##
    # \brief Bromine donor of hydrogen bromide.
    # 
    BR_HBR = 3

    ##
    # \brief Chlorine donor of hydrogen chloride.
    # 
    CL_HCL = 4

    ##
    # \brief Sulfur donor of thiocyanic acid.
    # 
    S_HSCN = 5

    ##
    # \brief Fluorine donor of hydrogen fluoride.
    # 
    F_HF = 6

    ##
    # \brief Hydrogen donor of molecular hydrogen.
    # 
    H_H2 = 7

    ##
    # \brief Carbon donor of hydrogen cyanide.
    # 
    C_HCN = 8

    ##
    # \brief Carbon donor of terminal-alkyne hydrogen.
    # 
    C_ETHINE = 9

    ##
    # \brief Nitrogen donor of hydrazoic acid (HN3).
    # 
    N_HN3 = 10

    ##
    # \brief Nitrogen donor of ammonia.
    # 
    N_NH3 = 11

    ##
    # \brief Nitrogen donor of ammonium.
    # 
    N_NH4 = 12

    ##
    # \brief Aliphatic amine nitrogen donor.
    # 
    N_AMINE = 13

    ##
    # \brief Aliphatic aminium nitrogen donor.
    # 
    N_AMINIUM = 14

    ##
    # \brief Aniline nitrogen donor.
    # 
    N_ANILINE = 15

    ##
    # \brief Mono-/di-nitro-aniline nitrogen donor.
    # 
    N_MONO_DI_NITRO_ANILINE = 16

    ##
    # \brief Tri-nitro-aniline nitrogen donor.
    # 
    N_TRI_NITRO_ANILINE = 17

    ##
    # \brief Pyrrole-like aromatic nitrogen donor.
    # 
    N_PYRROLE = 18

    ##
    # \brief Amide nitrogen donor.
    # 
    N_AMIDE = 19

    ##
    # \brief Imine nitrogen donor.
    # 
    N_IMINE = 20

    ##
    # \brief Iminium nitrogen donor.
    # 
    N_IMINIUM = 21

    ##
    # \brief Sulfur donor of hydrogen sulfide.
    # 
    S_H2S = 22

    ##
    # \brief Sulfur donor of bisulfide.
    # 
    S_HS = 23

    ##
    # \brief Thiol sulfur donor.
    # 
    S_THIOL = 24

    ##
    # \brief Oxygen donor of phosphoric acid (H3PO4).
    # 
    O_H3PO4 = 25

    ##
    # \brief Oxygen donor of carbonic acid (H2CO3).
    # 
    O_H2CO3 = 26

    ##
    # \brief Oxygen donor of bicarbonate (HCO3-).
    # 
    O_HCO3 = 27

    ##
    # \brief Oxygen donor of hydrogen peroxide (H2O2).
    # 
    O_H2O2 = 28

    ##
    # \brief Oxygen donor of water.
    # 
    O_H2O = 29

    ##
    # \brief Oxygen donor of triflic acid (CF3SO3H).
    # 
    O_CF3SO3H = 30

    ##
    # \brief Oxygen donor of perchloric acid (HClO4).
    # 
    O_HCLO4 = 31

    ##
    # \brief Oxygen donor of sulfuric acid (H2SO4).
    # 
    O_H2SO4 = 32

    ##
    # \brief Oxygen donor of nitric acid (HNO3).
    # 
    O_HNO3 = 33

    ##
    # \brief Oxygen donor of hydrogen sulfate (HSO4-).
    # 
    O_HSO4 = 34

    ##
    # \brief Oxygen donor of nitrous acid (HNO2).
    # 
    O_HNO2 = 35

    ##
    # \brief Oxygen donor of hydroxylamine (NH2OH).
    # 
    O_NH2OH = 36

    ##
    # \brief Oxygen donor of dihydrogen phosphate (H2PO4-).
    # 
    O_H2PO4 = 37

    ##
    # \brief Oxygen donor of boric acid (H3BO3).
    # 
    O_H3BO3 = 38

    ##
    # \brief Oxygen donor of silicic acid (H4SiO4).
    # 
    O_H4SIO4 = 39

    ##
    # \brief Oxygen donor of hydrogen phosphate (HPO4(2-)).
    # 
    O_HPO4 = 40

    ##
    # \brief Oxygen donor of dihydrogen borate (H2BO3-).
    # 
    O_H2BO3 = 41

    ##
    # \brief Oxygen donor of hydroxide (HO-).
    # 
    O_HO = 42

    ##
    # \brief Sulfonic-acid oxygen donor.
    # 
    O_SULFONIC_ACID = 43

    ##
    # \brief Mono-/di-nitro-phenol oxygen donor.
    # 
    O_MONO_DI_NITRO_PHENOL = 44

    ##
    # \brief Halogeno-alcohol oxygen donor.
    # 
    O_HALOGENO_ALCOHOL = 45

    ##
    # \brief Alcohol oxygen donor.
    # 
    O_ALCOHOL = 46

    ##
    # \brief Tri-nitro-phenol oxygen donor.
    # 
    O_TRI_NITRO_PHENOL = 47

    ##
    # \brief Halogeno-phenol oxygen donor.
    # 
    O_HALOGENO_PHENOL = 48

    ##
    # \brief Phenol oxygen donor.
    # 
    O_PHENOL = 49

    ##
    # \brief Carboxylic-acid oxygen donor.
    # 
    O_CARBOXYLIC_ACID = 50

    ##
    # \brief Halogeno-carboxylic-acid oxygen donor.
    # 
    O_HALOGENO_CARBOXYCLIC_ACID = 51

    ##
    # \brief Enol oxygen donor.
    # 
    O_ENOL = 52

    ##
    # \brief Oxime oxygen donor.
    # 
    O_OXIME = 53

    ##
    # \brief Pentachloro-phenol oxygen donor.
    # 
    O_CL5_PHENOL = 54

    ##
    # \brief Highest H-bond donor type constant defined in this namespace.
    # 
    MAX_TYPE = 54
