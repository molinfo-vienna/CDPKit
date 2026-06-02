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
# \brief Provides constants for the specification of <em>Universal Force Field (UFF)</em> atom types.
# 
# \see [\ref UFF]
# 
class UFFAtomType(Boost.Python.instance):

    ##
    # \brief Atom with no matching UFF atom type.
    # 
    NONE = 0

    ##
    # \brief 
    #
    H   = 1

    ##
    # \brief Hydrogen bridging between two boron atoms.
    # 
    H_b = 2

    ##
    # \brief Helium.
    # 
    He_4_4 = 3

    ##
    # \brief Lithium.
    # 
    Li = 4

    ##
    # \brief Beryllium (tetrahedral).
    # 
    Be_3_2 = 5

    ##
    # \brief Boron (sp3, tetrahedral).
    # 
    B_3 = 6

    ##
    # \brief Boron (sp2, trigonal-planar).
    # 
    B_2 = 7

    ##
    # \brief Carbon (sp3, tetrahedral).
    # 
    C_3 = 8

    ##
    # \brief Carbon (aromatic/resonant).
    # 
    C_R = 9

    ##
    # \brief Carbon (sp2, trigonal-planar).
    # 
    C_2 = 10

    ##
    # \brief Carbon (sp, linear).
    # 
    C_1 = 11

    ##
    # \brief Nitrogen (sp3, pyramidal).
    # 
    N_3 = 12

    ##
    # \brief Nitrogen (aromatic/resonant).
    # 
    N_R = 13

    ##
    # \brief Nitrogen (sp2, trigonal-planar).
    # 
    N_2 = 14

    ##
    # \brief Nitrogen (sp, linear).
    # 
    N_1 = 15

    ##
    # \brief Oxygen (sp3).
    # 
    O_3 = 16

    ##
    # \brief Oxygen in a zeolite framework.
    # 
    O_3_z = 17

    ##
    # \brief Oxygen (aromatic/resonant).
    # 
    O_R = 18

    ##
    # \brief Oxygen (sp2).
    # 
    O_2 = 19

    ##
    # \brief Oxygen (sp, linear, e.g. carbonyl in CO).
    # 
    O_1 = 20

    ##
    # \brief Fluorine.
    # 
    F = 21

    ##
    # \brief Neon.
    # 
    Ne_4_4 = 22

    ##
    # \brief Sodium.
    # 
    Na = 23

    ##
    # \brief Magnesium (tetrahedral).
    # 
    Mg_3_2 = 24

    ##
    # \brief Aluminum (tetrahedral).
    # 
    Al_3 = 25

    ##
    # \brief Silicon (tetrahedral).
    # 
    Si_3 = 26

    ##
    # \brief Phosphorus (sp3, three-coordinate).
    # 
    P_3_3 = 27

    ##
    # \brief Phosphorus (sp3, five-coordinate, e.g. phosphate).
    # 
    P_3_5 = 28

    ##
    # \brief Phosphorus in organometallic complexes.
    # 
    P_3_q = 29

    ##
    # \brief Sulfur (sp3, two-coordinate).
    # 
    S_3_2 = 30

    ##
    # \brief Sulfur (sp3, four-coordinate, e.g. sulfoxide).
    # 
    S_3_4 = 31

    ##
    # \brief Sulfur (sp3, six-coordinate, e.g. sulfone).
    # 
    S_3_6 = 32

    ##
    # \brief Sulfur (aromatic/resonant).
    # 
    S_R = 33

    ##
    # \brief Sulfur (sp2).
    # 
    S_2 = 34

    ##
    # \brief Chlorine.
    # 
    Cl = 35

    ##
    # \brief Argon.
    # 
    Ar_4_4 = 36

    ##
    # \brief Potassium.
    # 
    K = 37

    ##
    # \brief Calcium (octahedral).
    # 
    Ca_6_2 = 38

    ##
    # \brief Scandium (tetrahedral).
    # 
    Sc_3_3 = 39

    ##
    # \brief Titanium (tetrahedral).
    # 
    Ti_3_4 = 40

    ##
    # \brief Titanium (octahedral).
    # 
    Ti_6_4 = 41

    ##
    # \brief Vanadium (tetrahedral).
    # 
    V_3_5 = 42

    ##
    # \brief Chromium (octahedral).
    # 
    Cr_6_3 = 43

    ##
    # \brief Manganese (octahedral).
    # 
    Mn_6_2 = 44

    ##
    # \brief Iron (tetrahedral).
    # 
    Fe_3_2 = 45

    ##
    # \brief Iron (octahedral).
    # 
    Fe_6_2 = 46

    ##
    # \brief Cobalt (octahedral).
    # 
    Co_6_3 = 47

    ##
    # \brief Nickel (square-planar).
    # 
    Ni_4_2 = 48

    ##
    # \brief Copper (tetrahedral).
    # 
    Cu_3_1 = 49

    ##
    # \brief Zinc (tetrahedral).
    # 
    Zn_3_2 = 50

    ##
    # \brief Gallium (tetrahedral).
    # 
    Ga_3_3 = 51

    ##
    # \brief Germanium (tetrahedral).
    # 
    Ge_3 = 52

    ##
    # \brief Arsenic (tetrahedral).
    # 
    As_3_3 = 53

    ##
    # \brief Selenium (tetrahedral).
    # 
    Se_3_2 = 54

    ##
    # \brief Bromine.
    # 
    Br = 55

    ##
    # \brief Krypton.
    # 
    Kr_4_4 = 56

    ##
    # \brief Rubidium.
    # 
    Rb = 57

    ##
    # \brief Strontium (octahedral).
    # 
    Sr_6_2 = 58

    ##
    # \brief Yttrium (tetrahedral).
    # 
    Y_3_3 = 59

    ##
    # \brief Zirconium (tetrahedral).
    # 
    Zr_3_4 = 60

    ##
    # \brief Niobium (tetrahedral).
    # 
    Nb_3_5 = 61

    ##
    # \brief Molybdenum (octahedral).
    # 
    Mo_6_6 = 62

    ##
    # \brief Molybdenum (tetrahedral).
    # 
    Mo_3_6 = 63

    ##
    # \brief Technetium (octahedral).
    # 
    Tc_6_5 = 64

    ##
    # \brief Ruthenium (octahedral).
    # 
    Ru_6_2 = 65

    ##
    # \brief Rhodium (octahedral).
    # 
    Rh_6_3 = 66

    ##
    # \brief Palladium (square-planar).
    # 
    Pd_4_2 = 67

    ##
    # \brief Silver (linear).
    # 
    Ag_1_1 = 68

    ##
    # \brief Cadmium (tetrahedral).
    # 
    Cd_3_2 = 69

    ##
    # \brief Indium (tetrahedral).
    # 
    In_3_3 = 70

    ##
    # \brief Tin (tetrahedral).
    # 
    Sn_3 = 71

    ##
    # \brief Antimony (tetrahedral).
    # 
    Sb_3_3 = 72

    ##
    # \brief Tellurium (tetrahedral).
    # 
    Te_3_2 = 73

    ##
    # \brief Iodine.
    # 
    I = 74

    ##
    # \brief Xenon.
    # 
    Xe_4_4 = 75

    ##
    # \brief Caesium.
    # 
    Cs = 76

    ##
    # \brief Barium (octahedral).
    # 
    Ba_6_2 = 77

    ##
    # \brief Lanthanum (tetrahedral).
    # 
    La_3_3 = 78

    ##
    # \brief Cerium (octahedral).
    # 
    Ce_6_3 = 79

    ##
    # \brief Praseodymium (octahedral).
    # 
    Pr_6_3 = 80

    ##
    # \brief Neodymium (octahedral).
    # 
    Nd_6_3 = 81

    ##
    # \brief Promethium (octahedral).
    # 
    Pm_6_3 = 82

    ##
    # \brief Samarium (octahedral).
    # 
    Sm_6_3 = 83

    ##
    # \brief Europium (octahedral).
    # 
    Eu_6_3 = 84

    ##
    # \brief Gadolinium (octahedral).
    # 
    Gd_6_3 = 85

    ##
    # \brief Terbium (octahedral).
    # 
    Tb_6_3 = 86

    ##
    # \brief Dysprosium (octahedral).
    # 
    Dy_6_3 = 87

    ##
    # \brief Holmium (octahedral).
    # 
    Ho_6_3 = 88

    ##
    # \brief Erbium (octahedral).
    # 
    Er_6_3 = 89

    ##
    # \brief Thulium (octahedral).
    # 
    Tm_6_3 = 90

    ##
    # \brief Ytterbium (octahedral).
    # 
    Yb_6_3 = 91

    ##
    # \brief Lutetium (octahedral).
    # 
    Lu_6_3 = 92

    ##
    # \brief Hafnium (tetrahedral).
    # 
    Hf_3_4 = 93

    ##
    # \brief Tantalum (tetrahedral).
    # 
    Ta_3_5 = 94

    ##
    # \brief Tungsten (octahedral).
    # 
    W_6_6 = 95

    ##
    # \brief Tungsten (tetrahedral).
    # 
    W_3_4 = 96

    ##
    # \brief Tungsten (tetrahedral, higher oxidation state).
    # 
    W_3_6 = 97

    ##
    # \brief Rhenium (octahedral).
    # 
    Re_6_5 = 98

    ##
    # \brief Rhenium (tetrahedral).
    # 
    Re_3_7 = 99

    ##
    # \brief Osmium (octahedral).
    # 
    Os_6_6 = 100

    ##
    # \brief Iridium (octahedral).
    # 
    Ir_6_3 = 101

    ##
    # \brief Platinum (square-planar).
    # 
    Pt_4_2 = 102

    ##
    # \brief Gold (square-planar).
    # 
    Au_4_3 = 103

    ##
    # \brief Mercury (linear).
    # 
    Hg_1_2 = 104

    ##
    # \brief Thallium (tetrahedral).
    # 
    Tl_3_3 = 105

    ##
    # \brief Lead (tetrahedral).
    # 
    Pb_3 = 106

    ##
    # \brief Bismuth (tetrahedral).
    # 
    Bi_3_3 = 107

    ##
    # \brief Polonium (tetrahedral).
    # 
    Po_3_2 = 108

    ##
    # \brief Astatine.
    # 
    At = 109

    ##
    # \brief Radon.
    # 
    Rn_4_4 = 110

    ##
    # \brief Francium.
    # 
    Fr = 111

    ##
    # \brief Radium (octahedral).
    # 
    Ra_6_2 = 112

    ##
    # \brief Actinium (octahedral).
    # 
    Ac_6_3 = 113

    ##
    # \brief Thorium (octahedral).
    # 
    Th_6_4 = 114

    ##
    # \brief Protactinium (octahedral).
    # 
    Pa_6_4 = 115

    ##
    # \brief Uranium (octahedral).
    # 
    U_6_4 = 116

    ##
    # \brief Neptunium (octahedral).
    # 
    Np_6_4 = 117

    ##
    # \brief Plutonium (octahedral).
    # 
    Pu_6_4 = 118

    ##
    # \brief Americium (octahedral).
    # 
    Am_6_4 = 119

    ##
    # \brief Curium (octahedral).
    # 
    Cm_6_3 = 120

    ##
    # \brief Berkelium (octahedral).
    # 
    Bk_6_3 = 121

    ##
    # \brief Californium (octahedral).
    # 
    Cf_6_3 = 122

    ##
    # \brief Einsteinium (octahedral).
    # 
    Es_6_3 = 123

    ##
    # \brief Fermium (octahedral).
    # 
    Fm_6_3 = 124

    ##
    # \brief Mendelevium (octahedral).
    # 
    Md_6_3 = 125

    ##
    # \brief Nobelium (octahedral).
    # 
    No_6_3 = 126

    ##
    # \brief Lawrencium (octahedral).
    # 
    Lr_6_3 = 127

    ##
    # \brief Marks the end of all supported UFF atom types.
    # 
    MAX_TYPE = 127
