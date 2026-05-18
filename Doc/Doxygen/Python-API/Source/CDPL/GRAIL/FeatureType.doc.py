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
# \brief Provides constants for the specification of GRAIL-specific extended pharmacophore feature types that refine H-bond donor and acceptor categories by the chemical environment (atom element + SYBYL-like type) of the participating heavy atom.
# 
# Re-exports all constants from namespace Pharm.FeatureType and adds extended donor/acceptor subtypes used by the GRAIL descriptor calculation.
# 
# \since 1.1
# 
class FeatureType(Boost.Python.instance):

    ##
    # \brief 
    #
    UNKNOWN = 0

    ##
    # \brief 
    #
    HYDROPHOBIC = 1

    ##
    # \brief 
    #
    AROMATIC = 2

    ##
    # \brief 
    #
    NEGATIVE_IONIZABLE = 3

    ##
    # \brief 
    #
    POSITIVE_IONIZABLE = 4

    ##
    # \brief 
    #
    H_BOND_DONOR = 5

    ##
    # \brief 
    #
    H_BOND_ACCEPTOR = 6

    ##
    # \brief 
    #
    HALOGEN_BOND_DONOR = 7

    ##
    # \brief 
    #
    HALOGEN_BOND_ACCEPTOR = 8

    ##
    # \brief 
    #
    EXCLUSION_VOLUME = 9

    ##
    # \brief 
    #
    MAX_TYPE = 9

    ##
    # \brief H-bond donor with a generic nitrogen heavy atom.
    # 
    H_BOND_DONOR_N = 10

    ##
    # \brief H-bond donor with an sp3 (<em>N.3</em>) nitrogen heavy atom.
    # 
    H_BOND_DONOR_N3 = 11

    ##
    # \brief H-bond donor with an sp2 (<em>N.2</em>) nitrogen heavy atom.
    # 
    H_BOND_DONOR_N2 = 12

    ##
    # \brief H-bond donor with an aromatic (<em>N.ar</em>) nitrogen heavy atom.
    # 
    H_BOND_DONOR_Nar = 13

    ##
    # \brief H-bond donor with an amide (<em>N.am</em>) nitrogen heavy atom.
    # 
    H_BOND_DONOR_Nam = 14

    ##
    # \brief H-bond donor with a trigonal-planar (<em>N.pl3</em>) nitrogen heavy atom.
    # 
    H_BOND_DONOR_Npl3 = 15

    ##
    # \brief H-bond donor with a quaternary (<em>N.4</em>) nitrogen heavy atom.
    # 
    H_BOND_DONOR_N4 = 16

    ##
    # \brief H-bond donor with a generic oxygen heavy atom.
    # 
    H_BOND_DONOR_O = 17

    ##
    # \brief H-bond donor with an sp3 (<em>O.3</em>) oxygen heavy atom.
    # 
    H_BOND_DONOR_O3 = 18

    ##
    # \brief H-bond donor with a generic sulfur heavy atom.
    # 
    H_BOND_DONOR_S = 19

    ##
    # \brief H-bond donor with an sp3 (<em>S.3</em>) sulfur heavy atom.
    # 
    H_BOND_DONOR_S3 = 20

    ##
    # \brief H-bond acceptor with a generic nitrogen heavy atom.
    # 
    H_BOND_ACCEPTOR_N = 21

    ##
    # \brief H-bond acceptor with an sp3 (<em>N.3</em>) nitrogen heavy atom.
    # 
    H_BOND_ACCEPTOR_N3 = 22

    ##
    # \brief H-bond acceptor with an sp2 (<em>N.2</em>) nitrogen heavy atom.
    # 
    H_BOND_ACCEPTOR_N2 = 23

    ##
    # \brief H-bond acceptor with an sp (<em>N.1</em>) nitrogen heavy atom.
    # 
    H_BOND_ACCEPTOR_N1 = 24

    ##
    # \brief H-bond acceptor with an aromatic (<em>N.ar</em>) nitrogen heavy atom.
    # 
    H_BOND_ACCEPTOR_Nar = 25

    ##
    # \brief H-bond acceptor with a trigonal-planar (<em>N.pl3</em>) nitrogen heavy atom.
    # 
    H_BOND_ACCEPTOR_Npl3 = 26

    ##
    # \brief H-bond acceptor with a generic oxygen heavy atom.
    # 
    H_BOND_ACCEPTOR_O = 27

    ##
    # \brief H-bond acceptor with an sp3 (<em>O.3</em>) oxygen heavy atom.
    # 
    H_BOND_ACCEPTOR_O3 = 28

    ##
    # \brief H-bond acceptor with an sp2 (<em>O.2</em>) oxygen heavy atom.
    # 
    H_BOND_ACCEPTOR_O2 = 29

    ##
    # \brief H-bond acceptor with a carboxylate (<em>O.co2</em>) oxygen heavy atom.
    # 
    H_BOND_ACCEPTOR_Oco2 = 30

    ##
    # \brief H-bond acceptor with a generic sulfur heavy atom.
    # 
    H_BOND_ACCEPTOR_S = 31

    ##
    # \brief H-bond acceptor with an sp3 (<em>S.3</em>) sulfur heavy atom.
    # 
    H_BOND_ACCEPTOR_S3 = 32

    ##
    # \brief H-bond acceptor with an sp2 (<em>S.2</em>) sulfur heavy atom.
    # 
    H_BOND_ACCEPTOR_S2 = 33

    ##
    # \brief Highest extended feature type constant defined in this namespace.
    # 
    MAX_EXT_TYPE = 33
