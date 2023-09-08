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
# \brief GRAILDescriptorCalculator.
# 
# \see [\ref GRAIL]
# 
class GRAILDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief 
    #
    class ElementIndex(Boost.Python.enum):

        ##
        # \brief PI_COUNT.
        #
        PI_COUNT = 0

        ##
        # \brief NI_COUNT.
        #
        NI_COUNT = 1

        ##
        # \brief AR_COUNT.
        #
        AR_COUNT = 2

        ##
        # \brief H_COUNT.
        #
        H_COUNT = 3

        ##
        # \brief HBD_COUNT.
        #
        HBD_COUNT = 4

        ##
        # \brief HBA_COUNT.
        #
        HBA_COUNT = 5

        ##
        # \brief XBD_COUNT.
        #
        XBD_COUNT = 6

        ##
        # \brief XBA_COUNT.
        #
        XBA_COUNT = 7

        ##
        # \brief HBD_N3_COUNT.
        #
        HBD_N3_COUNT = 8

        ##
        # \brief HBD_N2_COUNT.
        #
        HBD_N2_COUNT = 9

        ##
        # \brief HBD_Nar_COUNT.
        #
        HBD_Nar_COUNT = 10

        ##
        # \brief HBD_Nam_COUNT.
        #
        HBD_Nam_COUNT = 11

        ##
        # \brief HBD_Npl3_COUNT.
        #
        HBD_Npl3_COUNT = 12

        ##
        # \brief HBD_N4_COUNT.
        #
        HBD_N4_COUNT = 13

        ##
        # \brief HBD_O3_COUNT.
        #
        HBD_O3_COUNT = 14

        ##
        # \brief HBD_S3_COUNT.
        #
        HBD_S3_COUNT = 15

        ##
        # \brief HBA_N3_COUNT.
        #
        HBA_N3_COUNT = 16

        ##
        # \brief HBA_N2_COUNT.
        #
        HBA_N2_COUNT = 17

        ##
        # \brief HBA_N1_COUNT.
        #
        HBA_N1_COUNT = 18

        ##
        # \brief HBA_Nar_COUNT.
        #
        HBA_Nar_COUNT = 19

        ##
        # \brief HBA_Npl3_COUNT.
        #
        HBA_Npl3_COUNT = 20

        ##
        # \brief HBA_O3_COUNT.
        #
        HBA_O3_COUNT = 21

        ##
        # \brief HBA_O2_COUNT.
        #
        HBA_O2_COUNT = 22

        ##
        # \brief HBA_Oco2_COUNT.
        #
        HBA_Oco2_COUNT = 23

        ##
        # \brief HBA_S3_COUNT.
        #
        HBA_S3_COUNT = 24

        ##
        # \brief HBA_S2_COUNT.
        #
        HBA_S2_COUNT = 25

        ##
        # \brief HVY_ATOM_COUNT.
        #
        HVY_ATOM_COUNT = 26

        ##
        # \brief ROT_BOND_COUNT.
        #
        ROT_BOND_COUNT = 27

        ##
        # \brief TOTAL_HYD.
        #
        TOTAL_HYD = 28

        ##
        # \brief LOGP.
        #
        LOGP = 29

        ##
        # \brief TPSA.
        #
        TPSA = 30

        ##
        # \brief ENV_HBA_N_OCC_SUM.
        #
        ENV_HBA_N_OCC_SUM = 31

        ##
        # \brief ENV_HBA_N_OCC_MAX.
        #
        ENV_HBA_N_OCC_MAX = 32

        ##
        # \brief ENV_HBA_O_OCC_SUM.
        #
        ENV_HBA_O_OCC_SUM = 33

        ##
        # \brief ENV_HBA_O_OCC_MAX.
        #
        ENV_HBA_O_OCC_MAX = 34

        ##
        # \brief ENV_HBA_S_OCC_SUM.
        #
        ENV_HBA_S_OCC_SUM = 35

        ##
        # \brief ENV_HBA_S_OCC_MAX.
        #
        ENV_HBA_S_OCC_MAX = 36

        ##
        # \brief ENV_HBD_N_OCC_SUM.
        #
        ENV_HBD_N_OCC_SUM = 37

        ##
        # \brief ENV_HBD_N_OCC_MAX.
        #
        ENV_HBD_N_OCC_MAX = 38

        ##
        # \brief ENV_HBD_O_OCC_SUM.
        #
        ENV_HBD_O_OCC_SUM = 39

        ##
        # \brief ENV_HBD_O_OCC_MAX.
        #
        ENV_HBD_O_OCC_MAX = 40

        ##
        # \brief ENV_HBD_S_OCC_SUM.
        #
        ENV_HBD_S_OCC_SUM = 41

        ##
        # \brief ENV_HBD_S_OCC_MAX.
        #
        ENV_HBD_S_OCC_MAX = 42

        ##
        # \brief PI_AR_SCORE_SUM.
        #
        PI_AR_SCORE_SUM = 43

        ##
        # \brief PI_AR_SCORE_MAX.
        #
        PI_AR_SCORE_MAX = 44

        ##
        # \brief AR_PI_SCORE_SUM.
        #
        AR_PI_SCORE_SUM = 45

        ##
        # \brief AR_PI_SCORE_MAX.
        #
        AR_PI_SCORE_MAX = 46

        ##
        # \brief H_H_SCORE_SUM.
        #
        H_H_SCORE_SUM = 47

        ##
        # \brief H_H_SCORE_MAX.
        #
        H_H_SCORE_MAX = 48

        ##
        # \brief AR_AR_SCORE_SUM.
        #
        AR_AR_SCORE_SUM = 49

        ##
        # \brief AR_AR_SCORE_MAX.
        #
        AR_AR_SCORE_MAX = 50

        ##
        # \brief HBD_HBA_N_SCORE_SUM.
        #
        HBD_HBA_N_SCORE_SUM = 51

        ##
        # \brief HBD_HBA_N_SCORE_MAX.
        #
        HBD_HBA_N_SCORE_MAX = 52

        ##
        # \brief HBD_HBA_O_SCORE_SUM.
        #
        HBD_HBA_O_SCORE_SUM = 53

        ##
        # \brief HBD_HBA_O_SCORE_MAX.
        #
        HBD_HBA_O_SCORE_MAX = 54

        ##
        # \brief HBD_HBA_S_SCORE_SUM.
        #
        HBD_HBA_S_SCORE_SUM = 55

        ##
        # \brief HBD_HBA_S_SCORE_MAX.
        #
        HBD_HBA_S_SCORE_MAX = 56

        ##
        # \brief HBD_N3_HBA_N_SCORE_SUM.
        #
        HBD_N3_HBA_N_SCORE_SUM = 57

        ##
        # \brief HBD_N3_HBA_N_SCORE_MAX.
        #
        HBD_N3_HBA_N_SCORE_MAX = 58

        ##
        # \brief HBD_N3_HBA_O_SCORE_SUM.
        #
        HBD_N3_HBA_O_SCORE_SUM = 59

        ##
        # \brief HBD_N3_HBA_O_SCORE_MAX.
        #
        HBD_N3_HBA_O_SCORE_MAX = 60

        ##
        # \brief HBD_N3_HBA_S_SCORE_SUM.
        #
        HBD_N3_HBA_S_SCORE_SUM = 61

        ##
        # \brief HBD_N3_HBA_S_SCORE_MAX.
        #
        HBD_N3_HBA_S_SCORE_MAX = 62

        ##
        # \brief HBD_N2_HBA_N_SCORE_SUM.
        #
        HBD_N2_HBA_N_SCORE_SUM = 63

        ##
        # \brief HBD_N2_HBA_N_SCORE_MAX.
        #
        HBD_N2_HBA_N_SCORE_MAX = 64

        ##
        # \brief HBD_N2_HBA_O_SCORE_SUM.
        #
        HBD_N2_HBA_O_SCORE_SUM = 65

        ##
        # \brief HBD_N2_HBA_O_SCORE_MAX.
        #
        HBD_N2_HBA_O_SCORE_MAX = 66

        ##
        # \brief HBD_N2_HBA_S_SCORE_SUM.
        #
        HBD_N2_HBA_S_SCORE_SUM = 67

        ##
        # \brief HBD_N2_HBA_S_SCORE_MAX.
        #
        HBD_N2_HBA_S_SCORE_MAX = 68

        ##
        # \brief HBD_Nar_HBA_N_SCORE_SUM.
        #
        HBD_Nar_HBA_N_SCORE_SUM = 69

        ##
        # \brief HBD_Nar_HBA_N_SCORE_MAX.
        #
        HBD_Nar_HBA_N_SCORE_MAX = 70

        ##
        # \brief HBD_Nar_HBA_O_SCORE_SUM.
        #
        HBD_Nar_HBA_O_SCORE_SUM = 71

        ##
        # \brief HBD_Nar_HBA_O_SCORE_MAX.
        #
        HBD_Nar_HBA_O_SCORE_MAX = 72

        ##
        # \brief HBD_Nar_HBA_S_SCORE_SUM.
        #
        HBD_Nar_HBA_S_SCORE_SUM = 73

        ##
        # \brief HBD_Nar_HBA_S_SCORE_MAX.
        #
        HBD_Nar_HBA_S_SCORE_MAX = 74

        ##
        # \brief HBD_Nam_HBA_N_SCORE_SUM.
        #
        HBD_Nam_HBA_N_SCORE_SUM = 75

        ##
        # \brief HBD_Nam_HBA_N_SCORE_MAX.
        #
        HBD_Nam_HBA_N_SCORE_MAX = 76

        ##
        # \brief HBD_Nam_HBA_O_SCORE_SUM.
        #
        HBD_Nam_HBA_O_SCORE_SUM = 77

        ##
        # \brief HBD_Nam_HBA_O_SCORE_MAX.
        #
        HBD_Nam_HBA_O_SCORE_MAX = 78

        ##
        # \brief HBD_Nam_HBA_S_SCORE_SUM.
        #
        HBD_Nam_HBA_S_SCORE_SUM = 79

        ##
        # \brief HBD_Nam_HBA_S_SCORE_MAX.
        #
        HBD_Nam_HBA_S_SCORE_MAX = 80

        ##
        # \brief HBD_Npl3_HBA_N_SCORE_SUM.
        #
        HBD_Npl3_HBA_N_SCORE_SUM = 81

        ##
        # \brief HBD_Npl3_HBA_N_SCORE_MAX.
        #
        HBD_Npl3_HBA_N_SCORE_MAX = 82

        ##
        # \brief HBD_Npl3_HBA_O_SCORE_SUM.
        #
        HBD_Npl3_HBA_O_SCORE_SUM = 83

        ##
        # \brief HBD_Npl3_HBA_O_SCORE_MAX.
        #
        HBD_Npl3_HBA_O_SCORE_MAX = 84

        ##
        # \brief HBD_Npl3_HBA_S_SCORE_SUM.
        #
        HBD_Npl3_HBA_S_SCORE_SUM = 85

        ##
        # \brief HBD_Npl3_HBA_S_SCORE_MAX.
        #
        HBD_Npl3_HBA_S_SCORE_MAX = 86

        ##
        # \brief HBD_N4_HBA_N_SCORE_SUM.
        #
        HBD_N4_HBA_N_SCORE_SUM = 87

        ##
        # \brief HBD_N4_HBA_N_SCORE_MAX.
        #
        HBD_N4_HBA_N_SCORE_MAX = 88

        ##
        # \brief HBD_N4_HBA_O_SCORE_SUM.
        #
        HBD_N4_HBA_O_SCORE_SUM = 89

        ##
        # \brief HBD_N4_HBA_O_SCORE_MAX.
        #
        HBD_N4_HBA_O_SCORE_MAX = 90

        ##
        # \brief HBD_N4_HBA_S_SCORE_SUM.
        #
        HBD_N4_HBA_S_SCORE_SUM = 91

        ##
        # \brief HBD_N4_HBA_S_SCORE_MAX.
        #
        HBD_N4_HBA_S_SCORE_MAX = 92

        ##
        # \brief HBD_O3_HBA_N_SCORE_SUM.
        #
        HBD_O3_HBA_N_SCORE_SUM = 93

        ##
        # \brief HBD_O3_HBA_N_SCORE_MAX.
        #
        HBD_O3_HBA_N_SCORE_MAX = 94

        ##
        # \brief HBD_O3_HBA_O_SCORE_SUM.
        #
        HBD_O3_HBA_O_SCORE_SUM = 95

        ##
        # \brief HBD_O3_HBA_O_SCORE_MAX.
        #
        HBD_O3_HBA_O_SCORE_MAX = 96

        ##
        # \brief HBD_O3_HBA_S_SCORE_SUM.
        #
        HBD_O3_HBA_S_SCORE_SUM = 97

        ##
        # \brief HBD_O3_HBA_S_SCORE_MAX.
        #
        HBD_O3_HBA_S_SCORE_MAX = 98

        ##
        # \brief HBD_S3_HBA_N_SCORE_SUM.
        #
        HBD_S3_HBA_N_SCORE_SUM = 99

        ##
        # \brief HBD_S3_HBA_N_SCORE_MAX.
        #
        HBD_S3_HBA_N_SCORE_MAX = 100

        ##
        # \brief HBD_S3_HBA_O_SCORE_SUM.
        #
        HBD_S3_HBA_O_SCORE_SUM = 101

        ##
        # \brief HBD_S3_HBA_O_SCORE_MAX.
        #
        HBD_S3_HBA_O_SCORE_MAX = 102

        ##
        # \brief HBD_S3_HBA_S_SCORE_SUM.
        #
        HBD_S3_HBA_S_SCORE_SUM = 103

        ##
        # \brief HBD_S3_HBA_S_SCORE_MAX.
        #
        HBD_S3_HBA_S_SCORE_MAX = 104

        ##
        # \brief HBA_HBD_N_SCORE_SUM.
        #
        HBA_HBD_N_SCORE_SUM = 105

        ##
        # \brief HBA_HBD_N_SCORE_MAX.
        #
        HBA_HBD_N_SCORE_MAX = 106

        ##
        # \brief HBA_HBD_O_SCORE_SUM.
        #
        HBA_HBD_O_SCORE_SUM = 107

        ##
        # \brief HBA_HBD_O_SCORE_MAX.
        #
        HBA_HBD_O_SCORE_MAX = 108

        ##
        # \brief HBA_HBD_S_SCORE_SUM.
        #
        HBA_HBD_S_SCORE_SUM = 109

        ##
        # \brief HBA_HBD_S_SCORE_MAX.
        #
        HBA_HBD_S_SCORE_MAX = 110

        ##
        # \brief HBA_N3_HBD_N_SCORE_SUM.
        #
        HBA_N3_HBD_N_SCORE_SUM = 111

        ##
        # \brief HBA_N3_HBD_N_SCORE_MAX.
        #
        HBA_N3_HBD_N_SCORE_MAX = 112

        ##
        # \brief HBA_N3_HBD_O_SCORE_SUM.
        #
        HBA_N3_HBD_O_SCORE_SUM = 113

        ##
        # \brief HBA_N3_HBD_O_SCORE_MAX.
        #
        HBA_N3_HBD_O_SCORE_MAX = 114

        ##
        # \brief HBA_N3_HBD_S_SCORE_SUM.
        #
        HBA_N3_HBD_S_SCORE_SUM = 115

        ##
        # \brief HBA_N3_HBD_S_SCORE_MAX.
        #
        HBA_N3_HBD_S_SCORE_MAX = 116

        ##
        # \brief HBA_N2_HBD_N_SCORE_SUM.
        #
        HBA_N2_HBD_N_SCORE_SUM = 117

        ##
        # \brief HBA_N2_HBD_N_SCORE_MAX.
        #
        HBA_N2_HBD_N_SCORE_MAX = 118

        ##
        # \brief HBA_N2_HBD_O_SCORE_SUM.
        #
        HBA_N2_HBD_O_SCORE_SUM = 119

        ##
        # \brief HBA_N2_HBD_O_SCORE_MAX.
        #
        HBA_N2_HBD_O_SCORE_MAX = 120

        ##
        # \brief HBA_N2_HBD_S_SCORE_SUM.
        #
        HBA_N2_HBD_S_SCORE_SUM = 121

        ##
        # \brief HBA_N2_HBD_S_SCORE_MAX.
        #
        HBA_N2_HBD_S_SCORE_MAX = 122

        ##
        # \brief HBA_N1_HBD_N_SCORE_SUM.
        #
        HBA_N1_HBD_N_SCORE_SUM = 123

        ##
        # \brief HBA_N1_HBD_N_SCORE_MAX.
        #
        HBA_N1_HBD_N_SCORE_MAX = 124

        ##
        # \brief HBA_N1_HBD_O_SCORE_SUM.
        #
        HBA_N1_HBD_O_SCORE_SUM = 125

        ##
        # \brief HBA_N1_HBD_O_SCORE_MAX.
        #
        HBA_N1_HBD_O_SCORE_MAX = 126

        ##
        # \brief HBA_N1_HBD_S_SCORE_SUM.
        #
        HBA_N1_HBD_S_SCORE_SUM = 127

        ##
        # \brief HBA_N1_HBD_S_SCORE_MAX.
        #
        HBA_N1_HBD_S_SCORE_MAX = 128

        ##
        # \brief HBA_Nar_HBD_N_SCORE_SUM.
        #
        HBA_Nar_HBD_N_SCORE_SUM = 129

        ##
        # \brief HBA_Nar_HBD_N_SCORE_MAX.
        #
        HBA_Nar_HBD_N_SCORE_MAX = 130

        ##
        # \brief HBA_Nar_HBD_O_SCORE_SUM.
        #
        HBA_Nar_HBD_O_SCORE_SUM = 131

        ##
        # \brief HBA_Nar_HBD_O_SCORE_MAX.
        #
        HBA_Nar_HBD_O_SCORE_MAX = 132

        ##
        # \brief HBA_Nar_HBD_S_SCORE_SUM.
        #
        HBA_Nar_HBD_S_SCORE_SUM = 133

        ##
        # \brief HBA_Nar_HBD_S_SCORE_MAX.
        #
        HBA_Nar_HBD_S_SCORE_MAX = 134

        ##
        # \brief HBA_Npl3_HBD_N_SCORE_SUM.
        #
        HBA_Npl3_HBD_N_SCORE_SUM = 135

        ##
        # \brief HBA_Npl3_HBD_N_SCORE_MAX.
        #
        HBA_Npl3_HBD_N_SCORE_MAX = 136

        ##
        # \brief HBA_Npl3_HBD_O_SCORE_SUM.
        #
        HBA_Npl3_HBD_O_SCORE_SUM = 137

        ##
        # \brief HBA_Npl3_HBD_O_SCORE_MAX.
        #
        HBA_Npl3_HBD_O_SCORE_MAX = 138

        ##
        # \brief HBA_Npl3_HBD_S_SCORE_SUM.
        #
        HBA_Npl3_HBD_S_SCORE_SUM = 139

        ##
        # \brief HBA_Npl3_HBD_S_SCORE_MAX.
        #
        HBA_Npl3_HBD_S_SCORE_MAX = 140

        ##
        # \brief HBA_O3_HBD_N_SCORE_SUM.
        #
        HBA_O3_HBD_N_SCORE_SUM = 141

        ##
        # \brief HBA_O3_HBD_N_SCORE_MAX.
        #
        HBA_O3_HBD_N_SCORE_MAX = 142

        ##
        # \brief HBA_O3_HBD_O_SCORE_SUM.
        #
        HBA_O3_HBD_O_SCORE_SUM = 143

        ##
        # \brief HBA_O3_HBD_O_SCORE_MAX.
        #
        HBA_O3_HBD_O_SCORE_MAX = 144

        ##
        # \brief HBA_O3_HBD_S_SCORE_SUM.
        #
        HBA_O3_HBD_S_SCORE_SUM = 145

        ##
        # \brief HBA_O3_HBD_S_SCORE_MAX.
        #
        HBA_O3_HBD_S_SCORE_MAX = 146

        ##
        # \brief HBA_O2_HBD_N_SCORE_SUM.
        #
        HBA_O2_HBD_N_SCORE_SUM = 147

        ##
        # \brief HBA_O2_HBD_N_SCORE_MAX.
        #
        HBA_O2_HBD_N_SCORE_MAX = 148

        ##
        # \brief HBA_O2_HBD_O_SCORE_SUM.
        #
        HBA_O2_HBD_O_SCORE_SUM = 149

        ##
        # \brief HBA_O2_HBD_O_SCORE_MAX.
        #
        HBA_O2_HBD_O_SCORE_MAX = 150

        ##
        # \brief HBA_O2_HBD_S_SCORE_SUM.
        #
        HBA_O2_HBD_S_SCORE_SUM = 151

        ##
        # \brief HBA_O2_HBD_S_SCORE_MAX.
        #
        HBA_O2_HBD_S_SCORE_MAX = 152

        ##
        # \brief HBA_Oco2_HBD_N_SCORE_SUM.
        #
        HBA_Oco2_HBD_N_SCORE_SUM = 153

        ##
        # \brief HBA_Oco2_HBD_N_SCORE_MAX.
        #
        HBA_Oco2_HBD_N_SCORE_MAX = 154

        ##
        # \brief HBA_Oco2_HBD_O_SCORE_SUM.
        #
        HBA_Oco2_HBD_O_SCORE_SUM = 155

        ##
        # \brief HBA_Oco2_HBD_O_SCORE_MAX.
        #
        HBA_Oco2_HBD_O_SCORE_MAX = 156

        ##
        # \brief HBA_Oco2_HBD_S_SCORE_SUM.
        #
        HBA_Oco2_HBD_S_SCORE_SUM = 157

        ##
        # \brief HBA_Oco2_HBD_S_SCORE_MAX.
        #
        HBA_Oco2_HBD_S_SCORE_MAX = 158

        ##
        # \brief HBA_S3_HBD_N_SCORE_SUM.
        #
        HBA_S3_HBD_N_SCORE_SUM = 159

        ##
        # \brief HBA_S3_HBD_N_SCORE_MAX.
        #
        HBA_S3_HBD_N_SCORE_MAX = 160

        ##
        # \brief HBA_S3_HBD_O_SCORE_SUM.
        #
        HBA_S3_HBD_O_SCORE_SUM = 161

        ##
        # \brief HBA_S3_HBD_O_SCORE_MAX.
        #
        HBA_S3_HBD_O_SCORE_MAX = 162

        ##
        # \brief HBA_S3_HBD_S_SCORE_SUM.
        #
        HBA_S3_HBD_S_SCORE_SUM = 163

        ##
        # \brief HBA_S3_HBD_S_SCORE_MAX.
        #
        HBA_S3_HBD_S_SCORE_MAX = 164

        ##
        # \brief HBA_S2_HBD_N_SCORE_SUM.
        #
        HBA_S2_HBD_N_SCORE_SUM = 165

        ##
        # \brief HBA_S2_HBD_N_SCORE_MAX.
        #
        HBA_S2_HBD_N_SCORE_MAX = 166

        ##
        # \brief HBA_S2_HBD_O_SCORE_SUM.
        #
        HBA_S2_HBD_O_SCORE_SUM = 167

        ##
        # \brief HBA_S2_HBD_O_SCORE_MAX.
        #
        HBA_S2_HBD_O_SCORE_MAX = 168

        ##
        # \brief HBA_S2_HBD_S_SCORE_SUM.
        #
        HBA_S2_HBD_S_SCORE_SUM = 169

        ##
        # \brief HBA_S2_HBD_S_SCORE_MAX.
        #
        HBA_S2_HBD_S_SCORE_MAX = 170

        ##
        # \brief XBD_XBA_SCORE_SUM.
        #
        XBD_XBA_SCORE_SUM = 171

        ##
        # \brief XBD_XBA_SCORE_MAX.
        #
        XBD_XBA_SCORE_MAX = 172

        ##
        # \brief ES_ENERGY.
        #
        ES_ENERGY = 173

        ##
        # \brief ES_ENERGY_SQRD_DIST.
        #
        ES_ENERGY_SQRD_DIST = 174

        ##
        # \brief VDW_ENERGY_ATT.
        #
        VDW_ENERGY_ATT = 175

        ##
        # \brief VDW_ENERGY_REP.
        #
        VDW_ENERGY_REP = 176

    ##
    # \brief 
    #
    TOTAL_DESCRIPTOR_SIZE = 177

    ##
    # \brief 
    #
    LIGAND_DESCRIPTOR_SIZE = 31

    ##
    # \brief Initializes the \e %GRAILDescriptorCalculator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %GRAILDescriptorCalculator instance \a calc.
    # \param calc The \e %GRAILDescriptorCalculator instance to copy.
    # 
    def __init__(calc: GRAILDescriptorCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %GRAILDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %GRAILDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GRAILDescriptorCalculator instance \a calc.
    # \param calc The \e %GRAILDescriptorCalculator instance to copy.
    # \return \a self
    # 
    def assign(calc: GRAILDescriptorCalculator) -> GRAILDescriptorCalculator: pass

    ##
    # \brief 
    # \param tgt_env 
    # \param coords_func 
    # \param tgt_env_changed 
    #
    def initTargetData(tgt_env: Chem.MolecularGraph, coords_func: Chem.Atom3DCoordinatesFunction, tgt_env_changed: bool = True) -> None: pass

    ##
    # \brief 
    # \param ligand 
    #
    def initLigandData(ligand: Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param atom_coords 
    # \param descr 
    # \param update_lig_part 
    #
    def calculate(atom_coords: Math.Vector3DArray, descr: Math.DVector, update_lig_part: bool = True) -> None: pass

    objectID = property(getObjectID)
