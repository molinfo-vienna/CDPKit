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
    # \brief Atom with no matching <em>Sybyl</em> atom type.
    # 
    UNKNOWN = 0

    ##
    # \brief Specifies sp3 carbon.
    # 
    C_3 = 1

    ##
    # \brief Specifies sp2 carbon.
    # 
    C_2 = 2

    ##
    # \brief Specifies sp carbon.
    # 
    C_1 = 3

    ##
    # \brief Specifies an aromatic carbon.
    # 
    C_ar = 4

    ##
    # \brief Specifies a carbocation (C+), used only in a guanidinium group.
    # 
    C_cat = 5

    ##
    # \brief Specifies sp3 nitrogen.
    # 
    N_3 = 6

    ##
    # \brief Specifies sp2 nitrogen.
    # 
    N_2 = 7

    ##
    # \brief Specifies sp nitrogen.
    # 
    N_1 = 8

    ##
    # \brief Specifies an aromatic nitrogen.
    # 
    N_ar = 9

    ##
    # \brief Specifies nitrogen in amides.
    # 
    N_am = 10

    ##
    # \brief Specifies a trigonal planar nitrogen.
    # 
    N_pl3 = 11

    ##
    # \brief Specifies a positively charged sp3 nitrogen.
    # 
    N_4 = 12

    ##
    # \brief Specifies sp3 oxygen.
    # 
    O_3 = 13

    ##
    # \brief Specifies sp2 oxygen.
    # 
    O_2 = 14

    ##
    # \brief Specifies oxygen in carboxylate and phosphate groups.
    # 
    O_co2 = 15

    ##
    # \brief Specifies oxygen in the <em>Single Point Charge (SPC)</em> water model.
    # 
    O_spc = 16

    ##
    # \brief Specifies oxygen in the <em>Transferable Intermolecular Potential (TIP3P)</em> water model.
    # 
    O_t3p = 17

    ##
    # \brief Specifies sp3 sulfur.
    # 
    S_3 = 18

    ##
    # \brief Specifies sp2 sulfur.
    # 
    S_2 = 19

    ##
    # \brief Specifies sulfur in sulfoxides.
    # 
    S_O = 20

    ##
    # \brief Specifies sulfur in sulfones.
    # 
    S_O2 = 21

    ##
    # \brief Specifies sp3 phosphorous.
    # 
    P_3 = 22

    ##
    # \brief Specifies fluorine.
    # 
    F = 23

    ##
    # \brief Specifies hydrogen.
    # 
    H = 24

    ##
    # \brief Specifies hydrogen in the <em>Single Point Charge (SPC)</em> water model.
    # 
    H_spc = 25

    ##
    # \brief Specifies hydrogen in the <em>Transferable intermolecular Potential (TIP3P)</em> water model.
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
    # \brief Specifies a dummy carbon.
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
    # \brief Specifies lithium.
    # 
    Li = 34

    ##
    # \brief Specifies sodium.
    # 
    Na = 35

    ##
    # \brief Specifies magnesium.
    # 
    Mg = 36

    ##
    # \brief Specifies aluminum.
    # 
    Al = 37

    ##
    # \brief Specifies silicon.
    # 
    Si = 38

    ##
    # \brief Specifies potassium.
    # 
    K = 39

    ##
    # \brief Specifies calcium.
    # 
    Ca = 40

    ##
    # \brief Specifies chromium (tetrahedral).
    # 
    Cr_th = 41

    ##
    # \brief Specifies chromium (octahedral).
    # 
    Cr_oh = 42

    ##
    # \brief Specifies manganese.
    # 
    Mn = 43

    ##
    # \brief 
    #
    e = 44

    ##
    # \brief Specifies cobalt (octahedral).
    # 
    Co_oh = 45

    ##
    # \brief Specifies copper.
    # 
    Cu = 46

    ##
    # \brief Specifies chlorine.
    # 
    Cl = 47

    ##
    # \brief Specifies bromine.
    # 
    Br = 48

    ##
    # \brief Specifies iodine.
    # 
    I = 49

    ##
    # \brief Specifies zinc.
    # 
    Zn = 50

    ##
    # \brief Specifies selenium.
    # 
    Se = 51

    ##
    # \brief Specifies molybdenum.
    # 
    Mo = 52

    ##
    # \brief Specifies tin.
    # 
    Sn = 53

    ##
    # \brief Marks the end of all supported atom types.
    # 
    MAX_TYPE = 55
