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
# \brief Provides constants for the specification of the chemical element or generic type of an atom.
# 
# For constants with a name equal to the symbol of a chemical element, the value of the constant corresponds to the atomic number of the respective element. Atom types with a value higher than AtomType.MAX_ATOMIC_NO are generic atom types that represent a set of chemical elements.
# 
class AtomType(Boost.Python.instance):

    ##
    # \brief Specifies an atom with an unknown or undefined atom type.
    # 
    UNKNOWN = 0

    ##
    # \brief Marks the end of the supported chemical elements.
    # 
    MAX_ATOMIC_NO = 113

    ##
    # \brief Marks the end of all supported atom types.
    # 
    MAX_TYPE = 124

    ##
    # \brief Specifies an R-group.
    # 
    R = 124

    ##
    # \brief A generic type that covers any element except hydrogen.
    # 
    A = 114

    ##
    # \brief A generic type that covers any element.
    # 
    AH = 115

    ##
    # \brief A generic type that covers any element (equivalent to AtomType.AH).
    # 
    ANY = 122

    ##
    # \brief A generic type for heteroatoms (N, O, S or P).
    # 
    HET = 123

    ##
    # \brief Specifies <em>Actinium</em>.
    # 
    Ac = 89

    ##
    # \brief Specifies <em>Silver</em>.
    # 
    Ag = 47

    ##
    # \brief Specifies <em>Aluminium</em>.
    # 
    Al = 13

    ##
    # \brief Specifies <em>Americium</em>.
    # 
    Am = 95

    ##
    # \brief Specifies <em>Argon</em>.
    # 
    Ar = 18

    ##
    # \brief Specifies <em>Arsenic</em>.
    # 
    As = 33

    ##
    # \brief Specifies <em>Astatine</em>.
    # 
    At = 85

    ##
    # \brief Specifies <em>Gold</em>.
    # 
    Au = 79

    ##
    # \brief Specifies <em>Boron</em>.
    # 
    B = 5

    ##
    # \brief Specifies <em>Barium</em>.
    # 
    Ba = 56

    ##
    # \brief Specifies <em>Beryllium</em>.
    # 
    Be = 4

    ##
    # \brief Specifies <em>Bohrium</em>.
    # 
    Bh = 107

    ##
    # \brief Specifies <em>Bismuth</em>.
    # 
    Bi = 83

    ##
    # \brief Specifies <em>Berkelium</em>.
    # 
    Bk = 97

    ##
    # \brief Specifies <em>Bromine</em>.
    # 
    Br = 35

    ##
    # \brief Specifies <em>Carbon</em>.
    # 
    C = 6

    ##
    # \brief Specifies <em>Calcium</em>.
    # 
    Ca = 20

    ##
    # \brief Specifies <em>Cadmium</em>.
    # 
    Cd = 48

    ##
    # \brief Specifies <em>Cerium</em>.
    # 
    Ce = 58

    ##
    # \brief Specifies <em>Californium</em>.
    # 
    Cf = 98

    ##
    # \brief Specifies <em>Chlorine</em>.
    # 
    Cl = 17

    ##
    # \brief Specifies <em>Curium</em>.
    # 
    Cm = 96

    ##
    # \brief Specifies <em>Copernicium</em>.
    # 
    Cn = 112

    ##
    # \brief Specifies <em>Cobalt</em>.
    # 
    Co = 27

    ##
    # \brief Specifies <em>Chromium</em>.
    # 
    Cr = 24

    ##
    # \brief Specifies <em>Caesium</em>.
    # 
    Cs = 55

    ##
    # \brief Specifies <em>Copper</em>.
    # 
    Cu = 29

    ##
    # \brief Specifies <em>Hydrogen (Deuterium)</em>.
    # 
    D = 1

    ##
    # \brief Specifies <em>Dubnium</em>.
    # 
    Db = 105

    ##
    # \brief Specifies <em>Darmstadtium</em>.
    # 
    Ds = 110

    ##
    # \brief Specifies <em>Dysprosium</em>.
    # 
    Dy = 66

    ##
    # \brief Specifies <em>Erbium</em>.
    # 
    Er = 68

    ##
    # \brief Specifies <em>Einsteinium</em>.
    # 
    Es = 99

    ##
    # \brief Specifies <em>Europium</em>.
    # 
    Eu = 63

    ##
    # \brief Specifies <em>Fluorine</em>.
    # 
    F = 9

    ##
    # \brief Specifies <em>Iron</em>.
    # 
    Fe = 26

    ##
    # \brief Specifies <em>Fermium</em>.
    # 
    Fm = 100

    ##
    # \brief Specifies <em>Francium</em>.
    # 
    Fr = 87

    ##
    # \brief Specifies <em>Gallium</em>.
    # 
    Ga = 31

    ##
    # \brief Specifies <em>Gadolinium</em>.
    # 
    Gd = 64

    ##
    # \brief Specifies <em>Germanium</em>.
    # 
    Ge = 32

    ##
    # \brief Specifies <em>Hydrogen</em>.
    # 
    H = 1

    ##
    # \brief Specifies <em>Helium</em>.
    # 
    He = 2

    ##
    # \brief Specifies <em>Hafnium</em>.
    # 
    Hf = 72

    ##
    # \brief Specifies <em>Mercury</em>.
    # 
    Hg = 80

    ##
    # \brief Specifies <em>Holmium</em>.
    # 
    Ho = 67

    ##
    # \brief Specifies <em>Hassium</em>.
    # 
    Hs = 108

    ##
    # \brief Specifies <em>Iodine</em>.
    # 
    I = 53

    ##
    # \brief Specifies <em>Indium</em>.
    # 
    In = 49

    ##
    # \brief Specifies <em>Iridium</em>.
    # 
    Ir = 77

    ##
    # \brief Specifies <em>Potassium</em>.
    # 
    K = 19

    ##
    # \brief Specifies <em>Krypton</em>.
    # 
    Kr = 36

    ##
    # \brief Specifies <em>Lanthanum</em>.
    # 
    La = 57

    ##
    # \brief Specifies <em>Lithium</em>.
    # 
    Li = 3

    ##
    # \brief Specifies <em>Lawrencium</em>.
    # 
    Lr = 103

    ##
    # \brief Specifies <em>Lutetium</em>.
    # 
    Lu = 71

    ##
    # \brief A generic type that covers any element that is a metal.
    # 
    M = 118

    ##
    # \brief A generic type that covers hydrogen and any element that is a metal.
    # 
    MH = 119

    ##
    # \brief Specifies <em>Mendelevium</em>.
    # 
    Md = 101

    ##
    # \brief Specifies <em>Magnesium</em>.
    # 
    Mg = 12

    ##
    # \brief Specifies <em>Manganese</em>.
    # 
    Mn = 25

    ##
    # \brief Specifies <em>Molybdenum</em>.
    # 
    Mo = 42

    ##
    # \brief Specifies <em>Meitnerium</em>.
    # 
    Mt = 109

    ##
    # \brief Specifies <em>Nitrogen</em>.
    # 
    N = 7

    ##
    # \brief Specifies <em>Sodium</em>.
    # 
    Na = 11

    ##
    # \brief Specifies <em>Niobium</em>.
    # 
    Nb = 41

    ##
    # \brief Specifies <em>Neodymium</em>.
    # 
    Nd = 60

    ##
    # \brief Specifies <em>Neon</em>.
    # 
    Ne = 10

    ##
    # \brief Specifies <em>Nihonium</em>.
    # 
    Nh = 113

    ##
    # \brief Specifies <em>Nickel</em>.
    # 
    Ni = 28

    ##
    # \brief Specifies <em>Nobelium</em>.
    # 
    No = 102

    ##
    # \brief Specifies <em>Neptunium</em>.
    # 
    Np = 93

    ##
    # \brief Specifies <em>Oxygen</em>.
    # 
    O = 8

    ##
    # \brief Specifies <em>Osmium</em>.
    # 
    Os = 76

    ##
    # \brief Specifies <em>Phosphorus</em>.
    # 
    P = 15

    ##
    # \brief Specifies <em>Protactinium</em>.
    # 
    Pa = 91

    ##
    # \brief Specifies <em>Lead</em>.
    # 
    Pb = 82

    ##
    # \brief Specifies <em>Palladium</em>.
    # 
    Pd = 46

    ##
    # \brief Specifies <em>Promethium</em>.
    # 
    Pm = 61

    ##
    # \brief Specifies <em>Polonium</em>.
    # 
    Po = 84

    ##
    # \brief Specifies <em>Praseodymium</em>.
    # 
    Pr = 59

    ##
    # \brief Specifies <em>Platinum</em>.
    # 
    Pt = 78

    ##
    # \brief Specifies <em>Plutonium</em>.
    # 
    Pu = 94

    ##
    # \brief A generic type that covers any element except hydrogen and carbon.
    # 
    Q = 116

    ##
    # \brief A generic type that covers any element except carbon.
    # 
    QH = 117

    ##
    # \brief Specifies <em>Radium</em>.
    # 
    Ra = 88

    ##
    # \brief Specifies <em>Rubidium</em>.
    # 
    Rb = 37

    ##
    # \brief Specifies <em>Rhenium</em>.
    # 
    Re = 75

    ##
    # \brief Specifies <em>Rutherfordium</em>.
    # 
    Rf = 104

    ##
    # \brief Specifies <em>Roentgenium</em>.
    # 
    Rg = 111

    ##
    # \brief Specifies <em>Rhodium</em>.
    # 
    Rh = 45

    ##
    # \brief Specifies <em>Radon</em>.
    # 
    Rn = 86

    ##
    # \brief Specifies <em>Ruthenium</em>.
    # 
    Ru = 44

    ##
    # \brief Specifies <em>Sulfur</em>.
    # 
    S = 16

    ##
    # \brief Specifies <em>Antimony</em>.
    # 
    Sb = 51

    ##
    # \brief Specifies <em>Scandium</em>.
    # 
    Sc = 21

    ##
    # \brief Specifies <em>Selenium</em>.
    # 
    Se = 34

    ##
    # \brief Specifies <em>Seaborgium</em>.
    # 
    Sg = 106

    ##
    # \brief Specifies <em>Silicon</em>.
    # 
    Si = 14

    ##
    # \brief Specifies <em>Samarium</em>.
    # 
    Sm = 62

    ##
    # \brief Specifies <em>Tin</em>.
    # 
    Sn = 50

    ##
    # \brief Specifies <em>Strontium</em>.
    # 
    Sr = 38

    ##
    # \brief Specifies <em>Hydrogen (Tritium)</em>.
    # 
    T = 1

    ##
    # \brief Specifies <em>Tantalum</em>.
    # 
    Ta = 73

    ##
    # \brief Specifies <em>Terbium</em>.
    # 
    Tb = 65

    ##
    # \brief Specifies <em>Technetium</em>.
    # 
    Tc = 43

    ##
    # \brief Specifies <em>Tellurium</em>.
    # 
    Te = 52

    ##
    # \brief Specifies <em>Thorium</em>.
    # 
    Th = 90

    ##
    # \brief Specifies <em>Titanium</em>.
    # 
    Ti = 22

    ##
    # \brief Specifies <em>Thallium</em>.
    # 
    Tl = 81

    ##
    # \brief Specifies <em>Thulium</em>.
    # 
    Tm = 69

    ##
    # \brief Specifies <em>Uranium</em>.
    # 
    U = 92

    ##
    # \brief Specifies <em>Vanadium</em>.
    # 
    V = 23

    ##
    # \brief Specifies <em>Tungsten</em>.
    # 
    W = 74

    ##
    # \brief A generic type that covers any element that is a halogen.
    # 
    X = 120

    ##
    # \brief A generic type that covers hydrogen and any element that is a halogen.
    # 
    XH = 121

    ##
    # \brief Specifies <em>Xenon</em>.
    # 
    Xe = 54

    ##
    # \brief Specifies <em>Yttrium</em>.
    # 
    Y = 39

    ##
    # \brief Specifies <em>Ytterbium</em>.
    # 
    Yb = 70

    ##
    # \brief Specifies <em>Zinc</em>.
    # 
    Zn = 30

    ##
    # \brief Specifies <em>Zirconium</em>.
    # 
    Zr = 40
