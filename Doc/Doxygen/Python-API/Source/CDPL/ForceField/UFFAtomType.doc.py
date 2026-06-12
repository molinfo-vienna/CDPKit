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
# \brief Provides constants for the specification of numeric <em>Universal Force Field (UFF)</em> atom types.
# 
# \see [\ref UFF]
# 
class UFFAtomType(Boost.Python.instance):

    ##
    # \brief Atom with no matching UFF type.
    # 
    NONE = 0

    ##
    # \brief 
    #
    H   = 1

    ##
    # \brief Hydrogen (bridging boron atoms).
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
    # \brief Beryllium.
    # 
    Be_3_2 = 5

    ##
    # \brief Boron (sp3).
    # 
    B_3 = 6

    ##
    # \brief Boron (sp2).
    # 
    B_2 = 7

    ##
    # \brief Carbon (sp3).
    # 
    C_3 = 8

    ##
    # \brief Carbon (aromatic/resonant).
    # 
    C_R = 9

    ##
    # \brief Carbon (sp2).
    # 
    C_2 = 10

    ##
    # \brief Carbon (sp).
    # 
    C_1 = 11

    ##
    # \brief Nitrogen (sp3).
    # 
    N_3 = 12

    ##
    # \brief Nitrogen (aromatic/resonant).
    # 
    N_R = 13

    ##
    # \brief Nitrogen (sp2).
    # 
    N_2 = 14

    ##
    # \brief Nitrogen (sp).
    # 
    N_1 = 15

    ##
    # \brief Oxygen (sp3).
    # 
    O_3 = 16

    ##
    # \brief Oxygen (sp3, in zeolite framework).
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
    # \brief Oxygen (sp).
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
    # \brief Magnesium.
    # 
    Mg_3_2 = 24

    ##
    # \brief Aluminum.
    # 
    Al_3 = 25

    ##
    # \brief Silicon.
    # 
    Si_3 = 26

    ##
    # \brief Phosphorus (sp3, trivalent).
    # 
    P_3_3 = 27

    ##
    # \brief Phosphorus (sp3, pentavalent).
    # 
    P_3_5 = 28

    ##
    # \brief Phosphorus (sp3, in organometallic complexes).
    # 
    P_3_q = 29

    ##
    # \brief Sulfur (sp3, bivalent).
    # 
    S_3_2 = 30

    ##
    # \brief Sulfur (sp3, tetravalent).
    # 
    S_3_4 = 31

    ##
    # \brief Sulfur (sp3, hexavalent).
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
    # \brief Calcium.
    # 
    Ca_6_2 = 38

    ##
    # \brief Scandium.
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
    # \brief Vanadium.
    # 
    V_3_5 = 42

    ##
    # \brief Chromium.
    # 
    Cr_6_3 = 43

    ##
    # \brief Manganese.
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
    # \brief Cobalt.
    # 
    Co_6_3 = 47

    ##
    # \brief Nickel.
    # 
    Ni_4_2 = 48

    ##
    # \brief Copper.
    # 
    Cu_3_1 = 49

    ##
    # \brief Zinc.
    # 
    Zn_3_2 = 50

    ##
    # \brief Gallium.
    # 
    Ga_3_3 = 51

    ##
    # \brief Germanium.
    # 
    Ge_3 = 52

    ##
    # \brief Arsenic.
    # 
    As_3_3 = 53

    ##
    # \brief Selenium.
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
    # \brief Strontium.
    # 
    Sr_6_2 = 58

    ##
    # \brief Yttrium.
    # 
    Y_3_3 = 59

    ##
    # \brief Zirconium.
    # 
    Zr_3_4 = 60

    ##
    # \brief Niobium.
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
    # \brief Technetium.
    # 
    Tc_6_5 = 64

    ##
    # \brief Ruthenium.
    # 
    Ru_6_2 = 65

    ##
    # \brief Rhodium.
    # 
    Rh_6_3 = 66

    ##
    # \brief Palladium.
    # 
    Pd_4_2 = 67

    ##
    # \brief Silver.
    # 
    Ag_1_1 = 68

    ##
    # \brief Cadmium.
    # 
    Cd_3_2 = 69

    ##
    # \brief Indium.
    # 
    In_3_3 = 70

    ##
    # \brief Tin.
    # 
    Sn_3 = 71

    ##
    # \brief Antimony.
    # 
    Sb_3_3 = 72

    ##
    # \brief Tellurium.
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
    # \brief Barium.
    # 
    Ba_6_2 = 77

    ##
    # \brief Lanthanum.
    # 
    La_3_3 = 78

    ##
    # \brief Cerium.
    # 
    Ce_6_3 = 79

    ##
    # \brief Praseodymium.
    # 
    Pr_6_3 = 80

    ##
    # \brief Neodymium.
    # 
    Nd_6_3 = 81

    ##
    # \brief Promethium.
    # 
    Pm_6_3 = 82

    ##
    # \brief Samarium.
    # 
    Sm_6_3 = 83

    ##
    # \brief Europium.
    # 
    Eu_6_3 = 84

    ##
    # \brief Gadolinium.
    # 
    Gd_6_3 = 85

    ##
    # \brief Terbium.
    # 
    Tb_6_3 = 86

    ##
    # \brief Dysprosium.
    # 
    Dy_6_3 = 87

    ##
    # \brief Holmium.
    # 
    Ho_6_3 = 88

    ##
    # \brief Erbium.
    # 
    Er_6_3 = 89

    ##
    # \brief Thulium.
    # 
    Tm_6_3 = 90

    ##
    # \brief Ytterbium.
    # 
    Yb_6_3 = 91

    ##
    # \brief Lutetium.
    # 
    Lu_6_3 = 92

    ##
    # \brief Hafnium.
    # 
    Hf_3_4 = 93

    ##
    # \brief Tantalum.
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
    # \brief Osmium.
    # 
    Os_6_6 = 100

    ##
    # \brief Iridium.
    # 
    Ir_6_3 = 101

    ##
    # \brief Platinum.
    # 
    Pt_4_2 = 102

    ##
    # \brief Gold.
    # 
    Au_4_3 = 103

    ##
    # \brief Mercury.
    # 
    Hg_1_2 = 104

    ##
    # \brief Thallium.
    # 
    Tl_3_3 = 105

    ##
    # \brief Lead.
    # 
    Pb_3 = 106

    ##
    # \brief Bismuth.
    # 
    Bi_3_3 = 107

    ##
    # \brief Polonium.
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
    # \brief Radium.
    # 
    Ra_6_2 = 112

    ##
    # \brief Actinium.
    # 
    Ac_6_3 = 113

    ##
    # \brief Thorium.
    # 
    Th_6_4 = 114

    ##
    # \brief Protactinium.
    # 
    Pa_6_4 = 115

    ##
    # \brief Uranium.
    # 
    U_6_4 = 116

    ##
    # \brief Neptunium.
    # 
    Np_6_4 = 117

    ##
    # \brief Plutonium.
    # 
    Pu_6_4 = 118

    ##
    # \brief Americium.
    # 
    Am_6_4 = 119

    ##
    # \brief Curium.
    # 
    Cm_6_3 = 120

    ##
    # \brief Berkelium.
    # 
    Bk_6_3 = 121

    ##
    # \brief Californium.
    # 
    Cf_6_3 = 122

    ##
    # \brief Einsteinium.
    # 
    Es_6_3 = 123

    ##
    # \brief Fermium.
    # 
    Fm_6_3 = 124

    ##
    # \brief Mendelevium.
    # 
    Md_6_3 = 125

    ##
    # \brief Nobelium.
    # 
    No_6_3 = 126

    ##
    # \brief Lawrencium.
    # 
    Lr_6_3 = 127

    ##
    # \brief The highest UFF atom type value.
    # 
    MAX_TYPE = 127
