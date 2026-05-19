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
# \brief Provides constants used to specify the structural class of H-bond acceptor atoms.
# 
class HBondAcceptorAtomType(Boost.Python.instance):

    ##
    # \brief Specifies that the H-bond acceptor type of the atom is undefined.
    # 
    UNDEF = 0

    ##
    # \brief Specifies that the atom is not a H-bond acceptor.
    # 
    NONE = 1

    ##
    # \brief Water oxygen acceptor.
    # 
    O_H2O = 2

    ##
    # \brief Urea oxygen acceptor.
    # 
    O_UREA = 3

    ##
    # \brief Barbituric-acid oxygen acceptor.
    # 
    O_BARBITURIC_ACID = 4

    ##
    # \brief Uric-acid oxygen acceptor.
    # 
    O_URIC_ACID = 5

    ##
    # \brief Ether oxygen acceptor.
    # 
    O_ETHER = 6

    ##
    # \brief Amide oxygen acceptor.
    # 
    O_AMIDE = 7

    ##
    # \brief N-oxide oxygen acceptor.
    # 
    O_N_OXIDE = 8

    ##
    # \brief Carboxylic-acid oxygen acceptor.
    # 
    O_ACID = 9

    ##
    # \brief Ester oxygen acceptor.
    # 
    O_ESTER = 10

    ##
    # \brief Sulfoxide oxygen acceptor.
    # 
    O_SULFOXIDE = 11

    ##
    # \brief Nitro-group oxygen acceptor.
    # 
    O_NITRO = 12

    ##
    # \brief Selenium-oxide oxygen acceptor.
    # 
    O_SELEN_OXIDE = 13

    ##
    # \brief Aldehyde oxygen acceptor.
    # 
    O_ALDEHYD = 14

    ##
    # \brief Ketone oxygen acceptor.
    # 
    O_KETONE = 15

    ##
    # \brief Alcohol oxygen acceptor.
    # 
    O_ALCOHOL = 16

    ##
    # \brief Ammonia nitrogen acceptor.
    # 
    N_NH3 = 17

    ##
    # \brief Diamine nitrogen acceptor.
    # 
    N_DIAMINE = 18

    ##
    # \brief Mono-/di-nitro-aniline nitrogen acceptor.
    # 
    N_MONO_DI_NITRO_ANILINE = 19

    ##
    # \brief Tri-nitro-aniline nitrogen acceptor.
    # 
    N_TRI_NITRO_ANILINE = 20

    ##
    # \brief Halogeno-aniline nitrogen acceptor.
    # 
    N_HALOGENO_ANILINE = 21

    ##
    # \brief Aniline nitrogen acceptor.
    # 
    N_ANILINE = 22

    ##
    # \brief Nitrile nitrogen acceptor.
    # 
    N_NITRILE = 23

    ##
    # \brief Azole (five-membered aromatic) nitrogen acceptor.
    # 
    N_AZOLE = 24

    ##
    # \brief Aliphatic amine nitrogen acceptor.
    # 
    N_AMINE = 25

    ##
    # \brief Amidine nitrogen acceptor.
    # 
    N_AMIDINE = 26

    ##
    # \brief Imine nitrogen acceptor.
    # 
    N_IMINE = 30

    ##
    # \brief Azo (N=N) nitrogen acceptor.
    # 
    N_AZO = 27

    ##
    # \brief Azine (six-membered aromatic N) nitrogen acceptor.
    # 
    N_AZINE = 28

    ##
    # \brief Diazine (six-membered aromatic with two N) nitrogen acceptor.
    # 
    N_DIAZINE = 29

    ##
    # \brief Sulfide sulfur acceptor.
    # 
    S_SULFIDE = 31

    ##
    # \brief Thiourea sulfur acceptor.
    # 
    S_THIOUREA = 32

    ##
    # \brief Mono-/di-phosphine phosphorus acceptor.
    # 
    P_MONO_DI_PHOSPHINE = 33

    ##
    # \brief Tri-phosphine phosphorus acceptor.
    # 
    P_TRI_PHOSPHINE = 34

    ##
    # \brief Highest H-bond acceptor type constant defined in this namespace.
    # 
    MAX_TYPE = 34
