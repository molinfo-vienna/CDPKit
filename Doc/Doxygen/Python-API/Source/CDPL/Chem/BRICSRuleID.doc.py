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
# \brief Provides constants for the identification of BRICS fragmentation rules.
# 
# \see [\ref BRICS]
# 
class BRICSRuleID(Boost.Python.instance):

    ##
    # \brief No rule applies.
    # 
    NONE = 0

    ##
    # \brief Rule cleaving the bond between atom-class L1 and L2 (C-C between sp3 carbons).
    # 
    L1_L2 = 1

    ##
    # \brief Rule cleaving the bond between atom-class L1 and L3 (sp3 C - N).
    # 
    L1_L3 = 2

    ##
    # \brief Rule cleaving the bond between atom-class L1 and L10.
    # 
    L1_L10 = 3

    ##
    # \brief Rule cleaving the bond between atom-class L2 and L12.
    # 
    L2_L12 = 4

    ##
    # \brief Rule cleaving the bond between atom-class L2 and L14.
    # 
    L2_L14 = 5

    ##
    # \brief Rule cleaving the bond between atom-class L2 and L16.
    # 
    L2_L16 = 6

    ##
    # \brief Rule cleaving the bond between atom-class L3 and L4.
    # 
    L3_L4 = 7

    ##
    # \brief Rule cleaving the bond between atom-class L3 and L13.
    # 
    L3_L13 = 8

    ##
    # \brief Rule cleaving the bond between atom-class L3 and L14.
    # 
    L3_L14 = 9

    ##
    # \brief Rule cleaving the bond between atom-class L3 and L15.
    # 
    L3_L15 = 10

    ##
    # \brief Rule cleaving the bond between atom-class L3 and L16.
    # 
    L3_L16 = 11

    ##
    # \brief Rule cleaving the bond between atom-class L4 and L5.
    # 
    L4_L5 = 12

    ##
    # \brief Rule cleaving the bond between atom-class L4 and L11.
    # 
    L4_L11 = 13

    ##
    # \brief Rule cleaving the bond between atom-class L5 and L13.
    # 
    L5_L13 = 14

    ##
    # \brief Rule cleaving the bond between atom-class L5 and L15.
    # 
    L5_L15 = 15

    ##
    # \brief Rule cleaving the bond between atom-class L6 and L13.
    # 
    L6_L13 = 16

    ##
    # \brief Rule cleaving the bond between atom-class L6 and L14.
    # 
    L6_L14 = 17

    ##
    # \brief Rule cleaving the bond between atom-class L6 and L15.
    # 
    L6_L15 = 18

    ##
    # \brief Rule cleaving the bond between atom-class L6 and L16.
    # 
    L6_L16 = 19

    ##
    # \brief Rule cleaving the bond between two atoms of atom-class L7.
    # 
    L7_L7 = 20

    ##
    # \brief Rule cleaving the bond between atom-class L8 and L9.
    # 
    L8_L9 = 21

    ##
    # \brief Rule cleaving the bond between atom-class L8 and L10.
    # 
    L8_L10 = 22

    ##
    # \brief Rule cleaving the bond between atom-class L8 and L13.
    # 
    L8_L13 = 23

    ##
    # \brief Rule cleaving the bond between atom-class L8 and L14.
    # 
    L8_L14 = 24

    ##
    # \brief Rule cleaving the bond between atom-class L8 and L15.
    # 
    L8_L15 = 25

    ##
    # \brief Rule cleaving the bond between atom-class L8 and L16.
    # 
    L8_L16 = 26

    ##
    # \brief Rule cleaving the bond between atom-class L9 and L15.
    # 
    L9_L15 = 27

    ##
    # \brief Rule cleaving the bond between atom-class L9 and L16.
    # 
    L9_L16 = 28

    ##
    # \brief Rule cleaving the bond between atom-class L10 and L13.
    # 
    L10_L13 = 29

    ##
    # \brief Rule cleaving the bond between atom-class L10 and L14.
    # 
    L10_L14 = 30

    ##
    # \brief Rule cleaving the bond between atom-class L10 and L15.
    # 
    L10_L15 = 31

    ##
    # \brief Rule cleaving the bond between atom-class L10 and L16.
    # 
    L10_L16 = 32

    ##
    # \brief Rule cleaving the bond between atom-class L11 and L13.
    # 
    L11_L13 = 33

    ##
    # \brief Rule cleaving the bond between atom-class L11 and L14.
    # 
    L11_L14 = 34

    ##
    # \brief Rule cleaving the bond between atom-class L11 and L15.
    # 
    L11_L15 = 35

    ##
    # \brief Rule cleaving the bond between atom-class L11 and L16.
    # 
    L11_L16 = 36

    ##
    # \brief Rule cleaving the bond between atom-class L13 and L14.
    # 
    L13_L14 = 37

    ##
    # \brief Rule cleaving the bond between atom-class L13 and L15.
    # 
    L13_L15 = 38

    ##
    # \brief Rule cleaving the bond between atom-class L13 and L16.
    # 
    L13_L16 = 39

    ##
    # \brief Rule cleaving the bond between atom-class L14 and L15.
    # 
    L14_L15 = 40

    ##
    # \brief Rule cleaving the bond between atom-class L14 and L16.
    # 
    L14_L16 = 41

    ##
    # \brief Rule cleaving the bond between atom-class L15 and L16.
    # 
    L15_L16 = 42
