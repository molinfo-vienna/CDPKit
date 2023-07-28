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
# \brief Provides constants for the specification of the <em>Tripos Sybyl</em> atom type.
# 
class SybylAtomType(Boost.Python.instance):

    ##
    # \brief Atom with no matching Sybyl atom type.
    # 
    UNKNOWN = 0

    ##
    # \brief Specifies sp3 <em>Carbon</em>.
    # 
    C_3 = 1

    ##
    # \brief Specifies sp2 <em>Carbon</em>.
    # 
    C_2 = 2

    ##
    # \brief Specifies sp <em>Carbon</em>.
    # 
    C_1 = 3

    ##
    # \brief Specifies an aromatic <em>Carbon</em>.
    # 
    C_ar = 4

    ##
    # \brief Specifies a <em>Carbocation</em> (C+), used only in a guanidinium group.
    # 
    C_cat = 5

    ##
    # \brief Specifies sp3 <em>Nitrogen</em>.
    # 
    N_3 = 6

    ##
    # \brief Specifies sp2 <em>Nitrogen</em>.
    # 
    N_2 = 7

    ##
    # \brief Specifies sp <em>Nitrogen</em>.
    # 
    N_1 = 8

    ##
    # \brief Specifies an aromatic <em>Nitrogen</em>.
    # 
    N_ar = 9

    ##
    # \brief Specifies <em>Nitrogen</em> in amides.
    # 
    N_am = 10

    ##
    # \brief Specifies a trigonal planar <em>Nitrogen</em>.
    # 
    N_pl3 = 11

    ##
    # \brief Specifies a positively charged sp3 <em>Nitrogen</em>.
    # 
    N_4 = 12

    ##
    # \brief Specifies sp3 <em>Oxygen</em>.
    # 
    O_3 = 13

    ##
    # \brief Specifies sp2 <em>Oxygen</em>.
    # 
    O_2 = 14

    ##
    # \brief Specifies <em>Oxygen</em> in carboxylate and phosphate groups.
    # 
    O_co2 = 15

    ##
    # \brief Specifies <em>Oxygen</em> in the <em>Single Point Charge (SPC)</em> water model.
    # 
    O_spc = 16

    ##
    # \brief Specifies <em>Oxygen</em> in the <em>Transferable Intermolecular Potential (TIP3P)</em> water model.
    # 
    O_t3p = 17

    ##
    # \brief Specifies sp3 <em>Sulfur</em>.
    # 
    S_3 = 18

    ##
    # \brief Specifies sp2 <em>Sulfur</em>.
    # 
    S_2 = 19

    ##
    # \brief Specifies <em>Sulfur</em> in sulfoxides.
    # 
    S_O = 20

    ##
    # \brief Specifies <em>Sulfur</em> in sulfones.
    # 
    S_O2 = 21

    ##
    # \brief Specifies sp3 <em>Phosphorous</em>.
    # 
    P_3 = 22

    ##
    # \brief Specifies <em>Fluorine</em>.
    # 
    F = 23

    ##
    # \brief Specifies <em>Hydrogen</em>.
    # 
    H = 24

    ##
    # \brief Specifies <em>Hydrogen</em> in the <em>Single Point Charge (SPC)</em> water model.
    # 
    H_spc = 25

    ##
    # \brief Specifies <em>Hydrogen</em> in the <em>Transferable intermolecular Potential (TIP3P)</em> water model.
    # 
    H_t3p = 26

    ##
    # \brief Specifies a lone pair.
    # 
    LP = 27

    ##
    # \brief Specifies a dummy atom.
    # 
    Du = 28

    ##
    # \brief Specifies a dummy <em>Carbon</em>.
    # 
    Du_C = 29

    ##
    # \brief Specifies any atom.
    # 
    Any = 30

    ##
    # \brief Specifies any halogen.
    # 
    Hal = 31

    ##
    # \brief Specifies a heteroatom (N, O, S or P).
    # 
    Het = 32

    ##
    # \brief Specifies any heavy atom (non-Hydrogen).
    # 
    Hev = 33

    ##
    # \brief Specifies <em>Lithium</em>.
    # 
    Li = 34

    ##
    # \brief Specifies <em>Sodium</em>.
    # 
    Na = 35

    ##
    # \brief Specifies <em>Magnesium</em>.
    # 
    Mg = 36

    ##
    # \brief Specifies <em>Aluminum</em>.
    # 
    Al = 37

    ##
    # \brief Specifies <em>Silicon</em>.
    # 
    Si = 38

    ##
    # \brief Specifies <em>Potassium</em>.
    # 
    K = 39

    ##
    # \brief Specifies <em>Calcium</em>.
    # 
    Ca = 40

    ##
    # \brief Specifies <em>Chromium</em> (tetrahedral).
    # 
    Cr_th = 41

    ##
    # \brief Specifies <em>Chromium</em> (octahedral).
    # 
    Cr_oh = 42

    ##
    # \brief Specifies <em>Manganese</em>.
    # 
    Mn = 43

    ##
    # \brief 
    #
    e = 44

    ##
    # \brief Specifies <em>Cobalt</em> (octahedral).
    # 
    Co_oh = 45

    ##
    # \brief Specifies <em>Copper</em>.
    # 
    Cu = 46

    ##
    # \brief Specifies <em>Chlorine</em>.
    # 
    Cl = 47

    ##
    # \brief Specifies <em>Bromine</em>.
    # 
    Br = 48

    ##
    # \brief Specifies <em>Iodine</em>.
    # 
    I = 49

    ##
    # \brief Specifies <em>Zinc</em>.
    # 
    Zn = 50

    ##
    # \brief Specifies <em>Selenium</em>.
    # 
    Se = 51

    ##
    # \brief Specifies <em>Molybdenum</em>.
    # 
    Mo = 52

    ##
    # \brief Specifies <em>Tin</em>.
    # 
    Sn = 53

    ##
    # \brief Marks the end of all supported atom types.
    # 
    MAX_TYPE = 55
