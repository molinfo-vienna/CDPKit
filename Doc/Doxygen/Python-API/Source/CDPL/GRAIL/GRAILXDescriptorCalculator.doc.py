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
# \brief Calculation of the extended GRAIL-X descriptor for protein-ligand complexes.
# 
# <tt>GRAILXDescriptorCalculator</tt> is the SYBYL-atom-type-aware variant of GRAIL.GRAILDescriptorCalculator. The resulting 177-element descriptor refines the generic hydrogen-bond donor/acceptor terms by also resolving the chemical environment (N3, N2, Nar, Nam, Npl3, N4, O3, O2, Oco2, S3, S2) of the participating heavy atom. The full element layout is given by ElementIndex.
# 
# \see [\ref GRADE]
# 
class GRAILXDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief Indices of the individual elements of the extended GRAIL-X descriptor vector.
    # 
    # The layout consists of six sections (in this order):
    #  - Feature/atom/bond counts of the ligand (positions [0, 8) and [26, 31)).
    #  - HBD / HBA counts of the ligand resolved by heavy atom SYBYL type (positions [8, 26)).
    #  - Target-environment H-bond occupancy SUM/MAX values resolved by ligand-feature heavy atom element ([31, 43)).
    #  - Generic interaction scores SUM/MAX (PI-AR, AR-PI, H-H, AR-AR) ([43, 51)).
    #  - Hydrogen-bond interaction SUM/MAX scores between ligand HBD/HBA subtype and target HBA/HBD by heavy atom element ([51, 171)).
    #  - Halogen-bond and energy terms ([171, 177)).
    # 
    class ElementIndex(Boost.Python.enum):

        ##
        # \brief Positive-ionizable feature count (ligand).
        # 
        PI_COUNT = 0

        ##
        # \brief Negative-ionizable feature count (ligand).
        # 
        NI_COUNT = 1

        ##
        # \brief Aromatic feature count (ligand).
        # 
        AR_COUNT = 2

        ##
        # \brief Hydrophobic feature count (ligand).
        # 
        H_COUNT = 3

        ##
        # \brief Hydrogen-bond donor feature count (ligand).
        # 
        HBD_COUNT = 4

        ##
        # \brief Hydrogen-bond acceptor feature count (ligand).
        # 
        HBA_COUNT = 5

        ##
        # \brief Halogen-bond donor feature count (ligand).
        # 
        XBD_COUNT = 6

        ##
        # \brief Halogen-bond acceptor feature count (ligand).
        # 
        XBA_COUNT = 7

        ##
        # \brief Ligand HBD feature count with N3 heavy atom.
        # 
        HBD_N3_COUNT = 8

        ##
        # \brief Ligand HBD feature count with N2 heavy atom.
        # 
        HBD_N2_COUNT = 9

        ##
        # \brief Ligand HBD feature count with Nar heavy atom.
        # 
        HBD_Nar_COUNT = 10

        ##
        # \brief Ligand HBD feature count with Nam heavy atom.
        # 
        HBD_Nam_COUNT = 11

        ##
        # \brief Ligand HBD feature count with Npl3 heavy atom.
        # 
        HBD_Npl3_COUNT = 12

        ##
        # \brief Ligand HBD feature count with N4 heavy atom.
        # 
        HBD_N4_COUNT = 13

        ##
        # \brief Ligand HBD feature count with O3 heavy atom.
        # 
        HBD_O3_COUNT = 14

        ##
        # \brief Ligand HBD feature count with S3 heavy atom.
        # 
        HBD_S3_COUNT = 15

        ##
        # \brief Ligand HBA feature count with N3 heavy atom.
        # 
        HBA_N3_COUNT = 16

        ##
        # \brief Ligand HBA feature count with N2 heavy atom.
        # 
        HBA_N2_COUNT = 17

        ##
        # \brief Ligand HBA feature count with N1 heavy atom.
        # 
        HBA_N1_COUNT = 18

        ##
        # \brief Ligand HBA feature count with Nar heavy atom.
        # 
        HBA_Nar_COUNT = 19

        ##
        # \brief Ligand HBA feature count with Npl3 heavy atom.
        # 
        HBA_Npl3_COUNT = 20

        ##
        # \brief Ligand HBA feature count with O3 heavy atom.
        # 
        HBA_O3_COUNT = 21

        ##
        # \brief Ligand HBA feature count with O2 heavy atom.
        # 
        HBA_O2_COUNT = 22

        ##
        # \brief Ligand HBA feature count with Oco2 heavy atom.
        # 
        HBA_Oco2_COUNT = 23

        ##
        # \brief Ligand HBA feature count with S3 heavy atom.
        # 
        HBA_S3_COUNT = 24

        ##
        # \brief Ligand HBA feature count with S2 heavy atom.
        # 
        HBA_S2_COUNT = 25

        ##
        # \brief Heavy atom count (ligand).
        # 
        HVY_ATOM_COUNT = 26

        ##
        # \brief Rotatable bond count (ligand).
        # 
        ROT_BOND_COUNT = 27

        ##
        # \brief Total computed hydrophobicity (ligand).
        # 
        TOTAL_HYD = 28

        ##
        # \brief Computed \f$ \log P \f$ (ligand).
        # 
        LOGP = 29

        ##
        # \brief Computed topological polar surface area (ligand).
        # 
        TPSA = 30

        ##
        # \brief Sum of environment HBA occupancy scores against ligand HBD-N atoms.
        # 
        ENV_HBA_N_OCC_SUM = 31

        ##
        # \brief Maximum environment HBA occupancy score against ligand HBD-N atoms.
        # 
        ENV_HBA_N_OCC_MAX = 32

        ##
        # \brief Sum of environment HBA occupancy scores against ligand HBD-O atoms.
        # 
        ENV_HBA_O_OCC_SUM = 33

        ##
        # \brief Maximum environment HBA occupancy score against ligand HBD-O atoms.
        # 
        ENV_HBA_O_OCC_MAX = 34

        ##
        # \brief Sum of environment HBA occupancy scores against ligand HBD-S atoms.
        # 
        ENV_HBA_S_OCC_SUM = 35

        ##
        # \brief Maximum environment HBA occupancy score against ligand HBD-S atoms.
        # 
        ENV_HBA_S_OCC_MAX = 36

        ##
        # \brief Sum of environment HBD occupancy scores against ligand HBA-N atoms.
        # 
        ENV_HBD_N_OCC_SUM = 37

        ##
        # \brief Maximum environment HBD occupancy score against ligand HBA-N atoms.
        # 
        ENV_HBD_N_OCC_MAX = 38

        ##
        # \brief Sum of environment HBD occupancy scores against ligand HBA-O atoms.
        # 
        ENV_HBD_O_OCC_SUM = 39

        ##
        # \brief Maximum environment HBD occupancy score against ligand HBA-O atoms.
        # 
        ENV_HBD_O_OCC_MAX = 40

        ##
        # \brief Sum of environment HBD occupancy scores against ligand HBA-S atoms.
        # 
        ENV_HBD_S_OCC_SUM = 41

        ##
        # \brief Maximum environment HBD occupancy score against ligand HBA-S atoms.
        # 
        ENV_HBD_S_OCC_MAX = 42

        ##
        # \brief Sum of (ligand positive-ionizable &rarr; target aromatic) interaction scores.
        # 
        PI_AR_SCORE_SUM = 43

        ##
        # \brief Maximum (ligand positive-ionizable &rarr; target aromatic) interaction score.
        # 
        PI_AR_SCORE_MAX = 44

        ##
        # \brief Sum of (ligand aromatic &rarr; target positive-ionizable) interaction scores.
        # 
        AR_PI_SCORE_SUM = 45

        ##
        # \brief Maximum (ligand aromatic &rarr; target positive-ionizable) interaction score.
        # 
        AR_PI_SCORE_MAX = 46

        ##
        # \brief Sum of hydrophobic-hydrophobic interaction scores.
        # 
        H_H_SCORE_SUM = 47

        ##
        # \brief Maximum hydrophobic-hydrophobic interaction score.
        # 
        H_H_SCORE_MAX = 48

        ##
        # \brief Sum of aromatic-aromatic interaction scores.
        # 
        AR_AR_SCORE_SUM = 49

        ##
        # \brief Maximum aromatic-aromatic interaction score.
        # 
        AR_AR_SCORE_MAX = 50

        ##
        # \brief Sum of (any ligand HBD &rarr; target HBA-N) interaction scores.
        # 
        HBD_HBA_N_SCORE_SUM = 51

        ##
        # \brief Maximum (any ligand HBD &rarr; target HBA-N) interaction score.
        # 
        HBD_HBA_N_SCORE_MAX = 52

        ##
        # \brief Sum of (any ligand HBD &rarr; target HBA-O) interaction scores.
        # 
        HBD_HBA_O_SCORE_SUM = 53

        ##
        # \brief Maximum (any ligand HBD &rarr; target HBA-O) interaction score.
        # 
        HBD_HBA_O_SCORE_MAX = 54

        ##
        # \brief Sum of (any ligand HBD &rarr; target HBA-S) interaction scores.
        # 
        HBD_HBA_S_SCORE_SUM = 55

        ##
        # \brief Maximum (any ligand HBD &rarr; target HBA-S) interaction score.
        # 
        HBD_HBA_S_SCORE_MAX = 56

        ##
        # \brief Sum of (ligand HBD-N3 &rarr; target HBA-N) interaction scores.
        # 
        HBD_N3_HBA_N_SCORE_SUM = 57

        ##
        # \brief Maximum (ligand HBD-N3 &rarr; target HBA-N) interaction score.
        # 
        HBD_N3_HBA_N_SCORE_MAX = 58

        ##
        # \brief Sum of (ligand HBD-N3 &rarr; target HBA-O) interaction scores.
        # 
        HBD_N3_HBA_O_SCORE_SUM = 59

        ##
        # \brief Maximum (ligand HBD-N3 &rarr; target HBA-O) interaction score.
        # 
        HBD_N3_HBA_O_SCORE_MAX = 60

        ##
        # \brief Sum of (ligand HBD-N3 &rarr; target HBA-S) interaction scores.
        # 
        HBD_N3_HBA_S_SCORE_SUM = 61

        ##
        # \brief Maximum (ligand HBD-N3 &rarr; target HBA-S) interaction score.
        # 
        HBD_N3_HBA_S_SCORE_MAX = 62

        ##
        # \brief Sum of (ligand HBD-N2 &rarr; target HBA-N) interaction scores.
        # 
        HBD_N2_HBA_N_SCORE_SUM = 63

        ##
        # \brief Maximum (ligand HBD-N2 &rarr; target HBA-N) interaction score.
        # 
        HBD_N2_HBA_N_SCORE_MAX = 64

        ##
        # \brief Sum of (ligand HBD-N2 &rarr; target HBA-O) interaction scores.
        # 
        HBD_N2_HBA_O_SCORE_SUM = 65

        ##
        # \brief Maximum (ligand HBD-N2 &rarr; target HBA-O) interaction score.
        # 
        HBD_N2_HBA_O_SCORE_MAX = 66

        ##
        # \brief Sum of (ligand HBD-N2 &rarr; target HBA-S) interaction scores.
        # 
        HBD_N2_HBA_S_SCORE_SUM = 67

        ##
        # \brief Maximum (ligand HBD-N2 &rarr; target HBA-S) interaction score.
        # 
        HBD_N2_HBA_S_SCORE_MAX = 68

        ##
        # \brief Sum of (ligand HBD-Nar &rarr; target HBA-N) interaction scores.
        # 
        HBD_Nar_HBA_N_SCORE_SUM = 69

        ##
        # \brief Maximum (ligand HBD-Nar &rarr; target HBA-N) interaction score.
        # 
        HBD_Nar_HBA_N_SCORE_MAX = 70

        ##
        # \brief Sum of (ligand HBD-Nar &rarr; target HBA-O) interaction scores.
        # 
        HBD_Nar_HBA_O_SCORE_SUM = 71

        ##
        # \brief Maximum (ligand HBD-Nar &rarr; target HBA-O) interaction score.
        # 
        HBD_Nar_HBA_O_SCORE_MAX = 72

        ##
        # \brief Sum of (ligand HBD-Nar &rarr; target HBA-S) interaction scores.
        # 
        HBD_Nar_HBA_S_SCORE_SUM = 73

        ##
        # \brief Maximum (ligand HBD-Nar &rarr; target HBA-S) interaction score.
        # 
        HBD_Nar_HBA_S_SCORE_MAX = 74

        ##
        # \brief Sum of (ligand HBD-Nam &rarr; target HBA-N) interaction scores.
        # 
        HBD_Nam_HBA_N_SCORE_SUM = 75

        ##
        # \brief Maximum (ligand HBD-Nam &rarr; target HBA-N) interaction score.
        # 
        HBD_Nam_HBA_N_SCORE_MAX = 76

        ##
        # \brief Sum of (ligand HBD-Nam &rarr; target HBA-O) interaction scores.
        # 
        HBD_Nam_HBA_O_SCORE_SUM = 77

        ##
        # \brief Maximum (ligand HBD-Nam &rarr; target HBA-O) interaction score.
        # 
        HBD_Nam_HBA_O_SCORE_MAX = 78

        ##
        # \brief Sum of (ligand HBD-Nam &rarr; target HBA-S) interaction scores.
        # 
        HBD_Nam_HBA_S_SCORE_SUM = 79

        ##
        # \brief Maximum (ligand HBD-Nam &rarr; target HBA-S) interaction score.
        # 
        HBD_Nam_HBA_S_SCORE_MAX = 80

        ##
        # \brief Sum of (ligand HBD-Npl3 &rarr; target HBA-N) interaction scores.
        # 
        HBD_Npl3_HBA_N_SCORE_SUM = 81

        ##
        # \brief Maximum (ligand HBD-Npl3 &rarr; target HBA-N) interaction score.
        # 
        HBD_Npl3_HBA_N_SCORE_MAX = 82

        ##
        # \brief Sum of (ligand HBD-Npl3 &rarr; target HBA-O) interaction scores.
        # 
        HBD_Npl3_HBA_O_SCORE_SUM = 83

        ##
        # \brief Maximum (ligand HBD-Npl3 &rarr; target HBA-O) interaction score.
        # 
        HBD_Npl3_HBA_O_SCORE_MAX = 84

        ##
        # \brief Sum of (ligand HBD-Npl3 &rarr; target HBA-S) interaction scores.
        # 
        HBD_Npl3_HBA_S_SCORE_SUM = 85

        ##
        # \brief Maximum (ligand HBD-Npl3 &rarr; target HBA-S) interaction score.
        # 
        HBD_Npl3_HBA_S_SCORE_MAX = 86

        ##
        # \brief Sum of (ligand HBD-N4 &rarr; target HBA-N) interaction scores.
        # 
        HBD_N4_HBA_N_SCORE_SUM = 87

        ##
        # \brief Maximum (ligand HBD-N4 &rarr; target HBA-N) interaction score.
        # 
        HBD_N4_HBA_N_SCORE_MAX = 88

        ##
        # \brief Sum of (ligand HBD-N4 &rarr; target HBA-O) interaction scores.
        # 
        HBD_N4_HBA_O_SCORE_SUM = 89

        ##
        # \brief Maximum (ligand HBD-N4 &rarr; target HBA-O) interaction score.
        # 
        HBD_N4_HBA_O_SCORE_MAX = 90

        ##
        # \brief Sum of (ligand HBD-N4 &rarr; target HBA-S) interaction scores.
        # 
        HBD_N4_HBA_S_SCORE_SUM = 91

        ##
        # \brief Maximum (ligand HBD-N4 &rarr; target HBA-S) interaction score.
        # 
        HBD_N4_HBA_S_SCORE_MAX = 92

        ##
        # \brief Sum of (ligand HBD-O3 &rarr; target HBA-N) interaction scores.
        # 
        HBD_O3_HBA_N_SCORE_SUM = 93

        ##
        # \brief Maximum (ligand HBD-O3 &rarr; target HBA-N) interaction score.
        # 
        HBD_O3_HBA_N_SCORE_MAX = 94

        ##
        # \brief Sum of (ligand HBD-O3 &rarr; target HBA-O) interaction scores.
        # 
        HBD_O3_HBA_O_SCORE_SUM = 95

        ##
        # \brief Maximum (ligand HBD-O3 &rarr; target HBA-O) interaction score.
        # 
        HBD_O3_HBA_O_SCORE_MAX = 96

        ##
        # \brief Sum of (ligand HBD-O3 &rarr; target HBA-S) interaction scores.
        # 
        HBD_O3_HBA_S_SCORE_SUM = 97

        ##
        # \brief Maximum (ligand HBD-O3 &rarr; target HBA-S) interaction score.
        # 
        HBD_O3_HBA_S_SCORE_MAX = 98

        ##
        # \brief Sum of (ligand HBD-S3 &rarr; target HBA-N) interaction scores.
        # 
        HBD_S3_HBA_N_SCORE_SUM = 99

        ##
        # \brief Maximum (ligand HBD-S3 &rarr; target HBA-N) interaction score.
        # 
        HBD_S3_HBA_N_SCORE_MAX = 100

        ##
        # \brief Sum of (ligand HBD-S3 &rarr; target HBA-O) interaction scores.
        # 
        HBD_S3_HBA_O_SCORE_SUM = 101

        ##
        # \brief Maximum (ligand HBD-S3 &rarr; target HBA-O) interaction score.
        # 
        HBD_S3_HBA_O_SCORE_MAX = 102

        ##
        # \brief Sum of (ligand HBD-S3 &rarr; target HBA-S) interaction scores.
        # 
        HBD_S3_HBA_S_SCORE_SUM = 103

        ##
        # \brief Maximum (ligand HBD-S3 &rarr; target HBA-S) interaction score.
        # 
        HBD_S3_HBA_S_SCORE_MAX = 104

        ##
        # \brief Sum of (any ligand HBA &rarr; target HBD-N) interaction scores.
        # 
        HBA_HBD_N_SCORE_SUM = 105

        ##
        # \brief Maximum (any ligand HBA &rarr; target HBD-N) interaction score.
        # 
        HBA_HBD_N_SCORE_MAX = 106

        ##
        # \brief Sum of (any ligand HBA &rarr; target HBD-O) interaction scores.
        # 
        HBA_HBD_O_SCORE_SUM = 107

        ##
        # \brief Maximum (any ligand HBA &rarr; target HBD-O) interaction score.
        # 
        HBA_HBD_O_SCORE_MAX = 108

        ##
        # \brief Sum of (any ligand HBA &rarr; target HBD-S) interaction scores.
        # 
        HBA_HBD_S_SCORE_SUM = 109

        ##
        # \brief Maximum (any ligand HBA &rarr; target HBD-S) interaction score.
        # 
        HBA_HBD_S_SCORE_MAX = 110

        ##
        # \brief Sum of (ligand HBA-N3 &rarr; target HBD-N) interaction scores.
        # 
        HBA_N3_HBD_N_SCORE_SUM = 111

        ##
        # \brief Maximum (ligand HBA-N3 &rarr; target HBD-N) interaction score.
        # 
        HBA_N3_HBD_N_SCORE_MAX = 112

        ##
        # \brief Sum of (ligand HBA-N3 &rarr; target HBD-O) interaction scores.
        # 
        HBA_N3_HBD_O_SCORE_SUM = 113

        ##
        # \brief Maximum (ligand HBA-N3 &rarr; target HBD-O) interaction score.
        # 
        HBA_N3_HBD_O_SCORE_MAX = 114

        ##
        # \brief Sum of (ligand HBA-N3 &rarr; target HBD-S) interaction scores.
        # 
        HBA_N3_HBD_S_SCORE_SUM = 115

        ##
        # \brief Maximum (ligand HBA-N3 &rarr; target HBD-S) interaction score.
        # 
        HBA_N3_HBD_S_SCORE_MAX = 116

        ##
        # \brief Sum of (ligand HBA-N2 &rarr; target HBD-N) interaction scores.
        # 
        HBA_N2_HBD_N_SCORE_SUM = 117

        ##
        # \brief Maximum (ligand HBA-N2 &rarr; target HBD-N) interaction score.
        # 
        HBA_N2_HBD_N_SCORE_MAX = 118

        ##
        # \brief Sum of (ligand HBA-N2 &rarr; target HBD-O) interaction scores.
        # 
        HBA_N2_HBD_O_SCORE_SUM = 119

        ##
        # \brief Maximum (ligand HBA-N2 &rarr; target HBD-O) interaction score.
        # 
        HBA_N2_HBD_O_SCORE_MAX = 120

        ##
        # \brief Sum of (ligand HBA-N2 &rarr; target HBD-S) interaction scores.
        # 
        HBA_N2_HBD_S_SCORE_SUM = 121

        ##
        # \brief Maximum (ligand HBA-N2 &rarr; target HBD-S) interaction score.
        # 
        HBA_N2_HBD_S_SCORE_MAX = 122

        ##
        # \brief Sum of (ligand HBA-N1 &rarr; target HBD-N) interaction scores.
        # 
        HBA_N1_HBD_N_SCORE_SUM = 123

        ##
        # \brief Maximum (ligand HBA-N1 &rarr; target HBD-N) interaction score.
        # 
        HBA_N1_HBD_N_SCORE_MAX = 124

        ##
        # \brief Sum of (ligand HBA-N1 &rarr; target HBD-O) interaction scores.
        # 
        HBA_N1_HBD_O_SCORE_SUM = 125

        ##
        # \brief Maximum (ligand HBA-N1 &rarr; target HBD-O) interaction score.
        # 
        HBA_N1_HBD_O_SCORE_MAX = 126

        ##
        # \brief Sum of (ligand HBA-N1 &rarr; target HBD-S) interaction scores.
        # 
        HBA_N1_HBD_S_SCORE_SUM = 127

        ##
        # \brief Maximum (ligand HBA-N1 &rarr; target HBD-S) interaction score.
        # 
        HBA_N1_HBD_S_SCORE_MAX = 128

        ##
        # \brief Sum of (ligand HBA-Nar &rarr; target HBD-N) interaction scores.
        # 
        HBA_Nar_HBD_N_SCORE_SUM = 129

        ##
        # \brief Maximum (ligand HBA-Nar &rarr; target HBD-N) interaction score.
        # 
        HBA_Nar_HBD_N_SCORE_MAX = 130

        ##
        # \brief Sum of (ligand HBA-Nar &rarr; target HBD-O) interaction scores.
        # 
        HBA_Nar_HBD_O_SCORE_SUM = 131

        ##
        # \brief Maximum (ligand HBA-Nar &rarr; target HBD-O) interaction score.
        # 
        HBA_Nar_HBD_O_SCORE_MAX = 132

        ##
        # \brief Sum of (ligand HBA-Nar &rarr; target HBD-S) interaction scores.
        # 
        HBA_Nar_HBD_S_SCORE_SUM = 133

        ##
        # \brief Maximum (ligand HBA-Nar &rarr; target HBD-S) interaction score.
        # 
        HBA_Nar_HBD_S_SCORE_MAX = 134

        ##
        # \brief Sum of (ligand HBA-Npl3 &rarr; target HBD-N) interaction scores.
        # 
        HBA_Npl3_HBD_N_SCORE_SUM = 135

        ##
        # \brief Maximum (ligand HBA-Npl3 &rarr; target HBD-N) interaction score.
        # 
        HBA_Npl3_HBD_N_SCORE_MAX = 136

        ##
        # \brief Sum of (ligand HBA-Npl3 &rarr; target HBD-O) interaction scores.
        # 
        HBA_Npl3_HBD_O_SCORE_SUM = 137

        ##
        # \brief Maximum (ligand HBA-Npl3 &rarr; target HBD-O) interaction score.
        # 
        HBA_Npl3_HBD_O_SCORE_MAX = 138

        ##
        # \brief Sum of (ligand HBA-Npl3 &rarr; target HBD-S) interaction scores.
        # 
        HBA_Npl3_HBD_S_SCORE_SUM = 139

        ##
        # \brief Maximum (ligand HBA-Npl3 &rarr; target HBD-S) interaction score.
        # 
        HBA_Npl3_HBD_S_SCORE_MAX = 140

        ##
        # \brief Sum of (ligand HBA-O3 &rarr; target HBD-N) interaction scores.
        # 
        HBA_O3_HBD_N_SCORE_SUM = 141

        ##
        # \brief Maximum (ligand HBA-O3 &rarr; target HBD-N) interaction score.
        # 
        HBA_O3_HBD_N_SCORE_MAX = 142

        ##
        # \brief Sum of (ligand HBA-O3 &rarr; target HBD-O) interaction scores.
        # 
        HBA_O3_HBD_O_SCORE_SUM = 143

        ##
        # \brief Maximum (ligand HBA-O3 &rarr; target HBD-O) interaction score.
        # 
        HBA_O3_HBD_O_SCORE_MAX = 144

        ##
        # \brief Sum of (ligand HBA-O3 &rarr; target HBD-S) interaction scores.
        # 
        HBA_O3_HBD_S_SCORE_SUM = 145

        ##
        # \brief Maximum (ligand HBA-O3 &rarr; target HBD-S) interaction score.
        # 
        HBA_O3_HBD_S_SCORE_MAX = 146

        ##
        # \brief Sum of (ligand HBA-O2 &rarr; target HBD-N) interaction scores.
        # 
        HBA_O2_HBD_N_SCORE_SUM = 147

        ##
        # \brief Maximum (ligand HBA-O2 &rarr; target HBD-N) interaction score.
        # 
        HBA_O2_HBD_N_SCORE_MAX = 148

        ##
        # \brief Sum of (ligand HBA-O2 &rarr; target HBD-O) interaction scores.
        # 
        HBA_O2_HBD_O_SCORE_SUM = 149

        ##
        # \brief Maximum (ligand HBA-O2 &rarr; target HBD-O) interaction score.
        # 
        HBA_O2_HBD_O_SCORE_MAX = 150

        ##
        # \brief Sum of (ligand HBA-O2 &rarr; target HBD-S) interaction scores.
        # 
        HBA_O2_HBD_S_SCORE_SUM = 151

        ##
        # \brief Maximum (ligand HBA-O2 &rarr; target HBD-S) interaction score.
        # 
        HBA_O2_HBD_S_SCORE_MAX = 152

        ##
        # \brief Sum of (ligand HBA-Oco2 &rarr; target HBD-N) interaction scores.
        # 
        HBA_Oco2_HBD_N_SCORE_SUM = 153

        ##
        # \brief Maximum (ligand HBA-Oco2 &rarr; target HBD-N) interaction score.
        # 
        HBA_Oco2_HBD_N_SCORE_MAX = 154

        ##
        # \brief Sum of (ligand HBA-Oco2 &rarr; target HBD-O) interaction scores.
        # 
        HBA_Oco2_HBD_O_SCORE_SUM = 155

        ##
        # \brief Maximum (ligand HBA-Oco2 &rarr; target HBD-O) interaction score.
        # 
        HBA_Oco2_HBD_O_SCORE_MAX = 156

        ##
        # \brief Sum of (ligand HBA-Oco2 &rarr; target HBD-S) interaction scores.
        # 
        HBA_Oco2_HBD_S_SCORE_SUM = 157

        ##
        # \brief Maximum (ligand HBA-Oco2 &rarr; target HBD-S) interaction score.
        # 
        HBA_Oco2_HBD_S_SCORE_MAX = 158

        ##
        # \brief Sum of (ligand HBA-S3 &rarr; target HBD-N) interaction scores.
        # 
        HBA_S3_HBD_N_SCORE_SUM = 159

        ##
        # \brief Maximum (ligand HBA-S3 &rarr; target HBD-N) interaction score.
        # 
        HBA_S3_HBD_N_SCORE_MAX = 160

        ##
        # \brief Sum of (ligand HBA-S3 &rarr; target HBD-O) interaction scores.
        # 
        HBA_S3_HBD_O_SCORE_SUM = 161

        ##
        # \brief Maximum (ligand HBA-S3 &rarr; target HBD-O) interaction score.
        # 
        HBA_S3_HBD_O_SCORE_MAX = 162

        ##
        # \brief Sum of (ligand HBA-S3 &rarr; target HBD-S) interaction scores.
        # 
        HBA_S3_HBD_S_SCORE_SUM = 163

        ##
        # \brief Maximum (ligand HBA-S3 &rarr; target HBD-S) interaction score.
        # 
        HBA_S3_HBD_S_SCORE_MAX = 164

        ##
        # \brief Sum of (ligand HBA-S2 &rarr; target HBD-N) interaction scores.
        # 
        HBA_S2_HBD_N_SCORE_SUM = 165

        ##
        # \brief Maximum (ligand HBA-S2 &rarr; target HBD-N) interaction score.
        # 
        HBA_S2_HBD_N_SCORE_MAX = 166

        ##
        # \brief Sum of (ligand HBA-S2 &rarr; target HBD-O) interaction scores.
        # 
        HBA_S2_HBD_O_SCORE_SUM = 167

        ##
        # \brief Maximum (ligand HBA-S2 &rarr; target HBD-O) interaction score.
        # 
        HBA_S2_HBD_O_SCORE_MAX = 168

        ##
        # \brief Sum of (ligand HBA-S2 &rarr; target HBD-S) interaction scores.
        # 
        HBA_S2_HBD_S_SCORE_SUM = 169

        ##
        # \brief Maximum (ligand HBA-S2 &rarr; target HBD-S) interaction score.
        # 
        HBA_S2_HBD_S_SCORE_MAX = 170

        ##
        # \brief Sum of (ligand XBD &rarr; target XBA) interaction scores.
        # 
        XBD_XBA_SCORE_SUM = 171

        ##
        # \brief Maximum (ligand XBD &rarr; target XBA) interaction score.
        # 
        XBD_XBA_SCORE_MAX = 172

        ##
        # \brief Electrostatic interaction energy.
        # 
        ES_ENERGY = 173

        ##
        # \brief Electrostatic interaction energy with squared atom-pair distance dependency.
        # 
        ES_ENERGY_SQRD_DIST = 174

        ##
        # \brief Attractive part of the Van der Waals interaction energy.
        # 
        VDW_ENERGY_ATT = 175

        ##
        # \brief Repulsive part of the Van der Waals interaction energy.
        # 
        VDW_ENERGY_REP = 176

    ##
    # \brief Total number of elements in the calculated descriptor vector.
    # 
    TOTAL_DESCRIPTOR_SIZE = 177

    ##
    # \brief Number of ligand-only descriptor elements (the first <tt>LIGAND_DESCRIPTOR_SIZE</tt> entries of the vector).
    # 
    LIGAND_DESCRIPTOR_SIZE = 31

    ##
    # \brief Constructs the <tt>GRAILXDescriptorCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>GRAILXDescriptorCalculator</tt> instance <em>calc</em>.
    # 
    # \param calc The <tt>GRAILXDescriptorCalculator</tt> to copy.
    # 
    def __init__(calc: GRAILXDescriptorCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GRAILXDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GRAILXDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param calc The other <tt>GRAILXDescriptorCalculator</tt> instance.
    # 
    # \return \a self
    # 
    def assign(calc: GRAILXDescriptorCalculator) -> GRAILXDescriptorCalculator: pass

    ##
    # \brief Initializes the calculator with target-environment data for subsequent descriptor calculations.
    # 
    # \param tgt_env The target environment (e.g. binding-site residues).
    # \param coords_func The function used to retrieve atom 3D-coordinates from <em>tgt_env</em>.
    # \param tgt_env_changed If <tt>True</tt>, the target environment is reinitialized even if the same target was supplied previously.
    # 
    def initTargetData(tgt_env: Chem.MolecularGraph, coords_func: Chem.Atom3DCoordinatesFunction, tgt_env_changed: bool = True) -> None: pass

    ##
    # \brief Initializes the calculator with the molecular graph of the ligand.
    # 
    # \param ligand The ligand molecular graph.
    # 
    def initLigandData(ligand: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Calculates the extended GRAIL-X descriptor for the current ligand pose.
    # 
    # The pose is supplied via per-atom 3D coordinates in <em>atom_coords</em> (same order as the atoms of the molecular graph passed to initLigandData()). The result is written to <em>descr</em>.
    # 
    # \param atom_coords The 3D coordinates of the ligand atoms.
    # \param descr The output descriptor vector (resized to TOTAL_DESCRIPTOR_SIZE).
    # \param update_lig_part If <tt>True</tt>, the ligand-only part of the descriptor is recomputed.
    # 
    def calculate(atom_coords: Math.Vector3DArray, descr: Math.DVector, update_lig_part: bool = True) -> None: pass

    objectID = property(getObjectID)
