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
# \brief 
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
        # \brief TOTAL_HYD.
        #
        TOTAL_HYD = 26

        ##
        # \brief LOGP.
        #
        LOGP = 27

        ##
        # \brief ENV_HBA_N_OCC_SUM.
        #
        ENV_HBA_N_OCC_SUM = 28

        ##
        # \brief ENV_HBA_N_OCC_MAX.
        #
        ENV_HBA_N_OCC_MAX = 29

        ##
        # \brief ENV_HBA_O_OCC_SUM.
        #
        ENV_HBA_O_OCC_SUM = 30

        ##
        # \brief ENV_HBA_O_OCC_MAX.
        #
        ENV_HBA_O_OCC_MAX = 31

        ##
        # \brief ENV_HBA_S_OCC_SUM.
        #
        ENV_HBA_S_OCC_SUM = 32

        ##
        # \brief ENV_HBA_S_OCC_MAX.
        #
        ENV_HBA_S_OCC_MAX = 33

        ##
        # \brief ENV_HBD_N_OCC_SUM.
        #
        ENV_HBD_N_OCC_SUM = 34

        ##
        # \brief ENV_HBD_N_OCC_MAX.
        #
        ENV_HBD_N_OCC_MAX = 35

        ##
        # \brief ENV_HBD_O_OCC_SUM.
        #
        ENV_HBD_O_OCC_SUM = 36

        ##
        # \brief ENV_HBD_O_OCC_MAX.
        #
        ENV_HBD_O_OCC_MAX = 37

        ##
        # \brief ENV_HBD_S_OCC_SUM.
        #
        ENV_HBD_S_OCC_SUM = 38

        ##
        # \brief ENV_HBD_S_OCC_MAX.
        #
        ENV_HBD_S_OCC_MAX = 39

        ##
        # \brief PI_AR_SCORE_SUM.
        #
        PI_AR_SCORE_SUM = 40

        ##
        # \brief PI_AR_SCORE_MAX.
        #
        PI_AR_SCORE_MAX = 41

        ##
        # \brief AR_PI_SCORE_SUM.
        #
        AR_PI_SCORE_SUM = 42

        ##
        # \brief AR_PI_SCORE_MAX.
        #
        AR_PI_SCORE_MAX = 43

        ##
        # \brief H_H_SCORE_SUM.
        #
        H_H_SCORE_SUM = 44

        ##
        # \brief H_H_SCORE_MAX.
        #
        H_H_SCORE_MAX = 45

        ##
        # \brief AR_AR_SCORE_SUM.
        #
        AR_AR_SCORE_SUM = 46

        ##
        # \brief AR_AR_SCORE_MAX.
        #
        AR_AR_SCORE_MAX = 47

        ##
        # \brief HBD_HBA_N_SCORE_SUM.
        #
        HBD_HBA_N_SCORE_SUM = 48

        ##
        # \brief HBD_HBA_N_SCORE_MAX.
        #
        HBD_HBA_N_SCORE_MAX = 49

        ##
        # \brief HBD_HBA_O_SCORE_SUM.
        #
        HBD_HBA_O_SCORE_SUM = 50

        ##
        # \brief HBD_HBA_O_SCORE_MAX.
        #
        HBD_HBA_O_SCORE_MAX = 51

        ##
        # \brief HBD_HBA_S_SCORE_SUM.
        #
        HBD_HBA_S_SCORE_SUM = 52

        ##
        # \brief HBD_HBA_S_SCORE_MAX.
        #
        HBD_HBA_S_SCORE_MAX = 53

        ##
        # \brief HBD_N3_HBA_N_SCORE_SUM.
        #
        HBD_N3_HBA_N_SCORE_SUM = 54

        ##
        # \brief HBD_N3_HBA_N_SCORE_MAX.
        #
        HBD_N3_HBA_N_SCORE_MAX = 55

        ##
        # \brief HBD_N3_HBA_O_SCORE_SUM.
        #
        HBD_N3_HBA_O_SCORE_SUM = 56

        ##
        # \brief HBD_N3_HBA_O_SCORE_MAX.
        #
        HBD_N3_HBA_O_SCORE_MAX = 57

        ##
        # \brief HBD_N3_HBA_S_SCORE_SUM.
        #
        HBD_N3_HBA_S_SCORE_SUM = 58

        ##
        # \brief HBD_N3_HBA_S_SCORE_MAX.
        #
        HBD_N3_HBA_S_SCORE_MAX = 59

        ##
        # \brief HBD_N2_HBA_N_SCORE_SUM.
        #
        HBD_N2_HBA_N_SCORE_SUM = 60

        ##
        # \brief HBD_N2_HBA_N_SCORE_MAX.
        #
        HBD_N2_HBA_N_SCORE_MAX = 61

        ##
        # \brief HBD_N2_HBA_O_SCORE_SUM.
        #
        HBD_N2_HBA_O_SCORE_SUM = 62

        ##
        # \brief HBD_N2_HBA_O_SCORE_MAX.
        #
        HBD_N2_HBA_O_SCORE_MAX = 63

        ##
        # \brief HBD_N2_HBA_S_SCORE_SUM.
        #
        HBD_N2_HBA_S_SCORE_SUM = 64

        ##
        # \brief HBD_N2_HBA_S_SCORE_MAX.
        #
        HBD_N2_HBA_S_SCORE_MAX = 65

        ##
        # \brief HBD_Nar_HBA_N_SCORE_SUM.
        #
        HBD_Nar_HBA_N_SCORE_SUM = 66

        ##
        # \brief HBD_Nar_HBA_N_SCORE_MAX.
        #
        HBD_Nar_HBA_N_SCORE_MAX = 67

        ##
        # \brief HBD_Nar_HBA_O_SCORE_SUM.
        #
        HBD_Nar_HBA_O_SCORE_SUM = 68

        ##
        # \brief HBD_Nar_HBA_O_SCORE_MAX.
        #
        HBD_Nar_HBA_O_SCORE_MAX = 69

        ##
        # \brief HBD_Nar_HBA_S_SCORE_SUM.
        #
        HBD_Nar_HBA_S_SCORE_SUM = 70

        ##
        # \brief HBD_Nar_HBA_S_SCORE_MAX.
        #
        HBD_Nar_HBA_S_SCORE_MAX = 71

        ##
        # \brief HBD_Nam_HBA_N_SCORE_SUM.
        #
        HBD_Nam_HBA_N_SCORE_SUM = 72

        ##
        # \brief HBD_Nam_HBA_N_SCORE_MAX.
        #
        HBD_Nam_HBA_N_SCORE_MAX = 73

        ##
        # \brief HBD_Nam_HBA_O_SCORE_SUM.
        #
        HBD_Nam_HBA_O_SCORE_SUM = 74

        ##
        # \brief HBD_Nam_HBA_O_SCORE_MAX.
        #
        HBD_Nam_HBA_O_SCORE_MAX = 75

        ##
        # \brief HBD_Nam_HBA_S_SCORE_SUM.
        #
        HBD_Nam_HBA_S_SCORE_SUM = 76

        ##
        # \brief HBD_Nam_HBA_S_SCORE_MAX.
        #
        HBD_Nam_HBA_S_SCORE_MAX = 77

        ##
        # \brief HBD_Npl3_HBA_N_SCORE_SUM.
        #
        HBD_Npl3_HBA_N_SCORE_SUM = 78

        ##
        # \brief HBD_Npl3_HBA_N_SCORE_MAX.
        #
        HBD_Npl3_HBA_N_SCORE_MAX = 79

        ##
        # \brief HBD_Npl3_HBA_O_SCORE_SUM.
        #
        HBD_Npl3_HBA_O_SCORE_SUM = 80

        ##
        # \brief HBD_Npl3_HBA_O_SCORE_MAX.
        #
        HBD_Npl3_HBA_O_SCORE_MAX = 81

        ##
        # \brief HBD_Npl3_HBA_S_SCORE_SUM.
        #
        HBD_Npl3_HBA_S_SCORE_SUM = 82

        ##
        # \brief HBD_Npl3_HBA_S_SCORE_MAX.
        #
        HBD_Npl3_HBA_S_SCORE_MAX = 83

        ##
        # \brief HBD_N4_HBA_N_SCORE_SUM.
        #
        HBD_N4_HBA_N_SCORE_SUM = 84

        ##
        # \brief HBD_N4_HBA_N_SCORE_MAX.
        #
        HBD_N4_HBA_N_SCORE_MAX = 85

        ##
        # \brief HBD_N4_HBA_O_SCORE_SUM.
        #
        HBD_N4_HBA_O_SCORE_SUM = 86

        ##
        # \brief HBD_N4_HBA_O_SCORE_MAX.
        #
        HBD_N4_HBA_O_SCORE_MAX = 87

        ##
        # \brief HBD_N4_HBA_S_SCORE_SUM.
        #
        HBD_N4_HBA_S_SCORE_SUM = 88

        ##
        # \brief HBD_N4_HBA_S_SCORE_MAX.
        #
        HBD_N4_HBA_S_SCORE_MAX = 89

        ##
        # \brief HBD_O3_HBA_N_SCORE_SUM.
        #
        HBD_O3_HBA_N_SCORE_SUM = 90

        ##
        # \brief HBD_O3_HBA_N_SCORE_MAX.
        #
        HBD_O3_HBA_N_SCORE_MAX = 91

        ##
        # \brief HBD_O3_HBA_O_SCORE_SUM.
        #
        HBD_O3_HBA_O_SCORE_SUM = 92

        ##
        # \brief HBD_O3_HBA_O_SCORE_MAX.
        #
        HBD_O3_HBA_O_SCORE_MAX = 93

        ##
        # \brief HBD_O3_HBA_S_SCORE_SUM.
        #
        HBD_O3_HBA_S_SCORE_SUM = 94

        ##
        # \brief HBD_O3_HBA_S_SCORE_MAX.
        #
        HBD_O3_HBA_S_SCORE_MAX = 95

        ##
        # \brief HBD_S3_HBA_N_SCORE_SUM.
        #
        HBD_S3_HBA_N_SCORE_SUM = 96

        ##
        # \brief HBD_S3_HBA_N_SCORE_MAX.
        #
        HBD_S3_HBA_N_SCORE_MAX = 97

        ##
        # \brief HBD_S3_HBA_O_SCORE_SUM.
        #
        HBD_S3_HBA_O_SCORE_SUM = 98

        ##
        # \brief HBD_S3_HBA_O_SCORE_MAX.
        #
        HBD_S3_HBA_O_SCORE_MAX = 99

        ##
        # \brief HBD_S3_HBA_S_SCORE_SUM.
        #
        HBD_S3_HBA_S_SCORE_SUM = 100

        ##
        # \brief HBD_S3_HBA_S_SCORE_MAX.
        #
        HBD_S3_HBA_S_SCORE_MAX = 101

        ##
        # \brief HBA_HBD_N_SCORE_SUM.
        #
        HBA_HBD_N_SCORE_SUM = 102

        ##
        # \brief HBA_HBD_N_SCORE_MAX.
        #
        HBA_HBD_N_SCORE_MAX = 103

        ##
        # \brief HBA_HBD_O_SCORE_SUM.
        #
        HBA_HBD_O_SCORE_SUM = 104

        ##
        # \brief HBA_HBD_O_SCORE_MAX.
        #
        HBA_HBD_O_SCORE_MAX = 105

        ##
        # \brief HBA_HBD_S_SCORE_SUM.
        #
        HBA_HBD_S_SCORE_SUM = 106

        ##
        # \brief HBA_HBD_S_SCORE_MAX.
        #
        HBA_HBD_S_SCORE_MAX = 107

        ##
        # \brief HBA_N3_HBD_N_SCORE_SUM.
        #
        HBA_N3_HBD_N_SCORE_SUM = 108

        ##
        # \brief HBA_N3_HBD_N_SCORE_MAX.
        #
        HBA_N3_HBD_N_SCORE_MAX = 109

        ##
        # \brief HBA_N3_HBD_O_SCORE_SUM.
        #
        HBA_N3_HBD_O_SCORE_SUM = 110

        ##
        # \brief HBA_N3_HBD_O_SCORE_MAX.
        #
        HBA_N3_HBD_O_SCORE_MAX = 111

        ##
        # \brief HBA_N3_HBD_S_SCORE_SUM.
        #
        HBA_N3_HBD_S_SCORE_SUM = 112

        ##
        # \brief HBA_N3_HBD_S_SCORE_MAX.
        #
        HBA_N3_HBD_S_SCORE_MAX = 113

        ##
        # \brief HBA_N2_HBD_N_SCORE_SUM.
        #
        HBA_N2_HBD_N_SCORE_SUM = 114

        ##
        # \brief HBA_N2_HBD_N_SCORE_MAX.
        #
        HBA_N2_HBD_N_SCORE_MAX = 115

        ##
        # \brief HBA_N2_HBD_O_SCORE_SUM.
        #
        HBA_N2_HBD_O_SCORE_SUM = 116

        ##
        # \brief HBA_N2_HBD_O_SCORE_MAX.
        #
        HBA_N2_HBD_O_SCORE_MAX = 117

        ##
        # \brief HBA_N2_HBD_S_SCORE_SUM.
        #
        HBA_N2_HBD_S_SCORE_SUM = 118

        ##
        # \brief HBA_N2_HBD_S_SCORE_MAX.
        #
        HBA_N2_HBD_S_SCORE_MAX = 119

        ##
        # \brief HBA_N1_HBD_N_SCORE_SUM.
        #
        HBA_N1_HBD_N_SCORE_SUM = 120

        ##
        # \brief HBA_N1_HBD_N_SCORE_MAX.
        #
        HBA_N1_HBD_N_SCORE_MAX = 121

        ##
        # \brief HBA_N1_HBD_O_SCORE_SUM.
        #
        HBA_N1_HBD_O_SCORE_SUM = 122

        ##
        # \brief HBA_N1_HBD_O_SCORE_MAX.
        #
        HBA_N1_HBD_O_SCORE_MAX = 123

        ##
        # \brief HBA_N1_HBD_S_SCORE_SUM.
        #
        HBA_N1_HBD_S_SCORE_SUM = 124

        ##
        # \brief HBA_N1_HBD_S_SCORE_MAX.
        #
        HBA_N1_HBD_S_SCORE_MAX = 125

        ##
        # \brief HBA_Nar_HBD_N_SCORE_SUM.
        #
        HBA_Nar_HBD_N_SCORE_SUM = 126

        ##
        # \brief HBA_Nar_HBD_N_SCORE_MAX.
        #
        HBA_Nar_HBD_N_SCORE_MAX = 127

        ##
        # \brief HBA_Nar_HBD_O_SCORE_SUM.
        #
        HBA_Nar_HBD_O_SCORE_SUM = 128

        ##
        # \brief HBA_Nar_HBD_O_SCORE_MAX.
        #
        HBA_Nar_HBD_O_SCORE_MAX = 129

        ##
        # \brief HBA_Nar_HBD_S_SCORE_SUM.
        #
        HBA_Nar_HBD_S_SCORE_SUM = 130

        ##
        # \brief HBA_Nar_HBD_S_SCORE_MAX.
        #
        HBA_Nar_HBD_S_SCORE_MAX = 131

        ##
        # \brief HBA_Npl3_HBD_N_SCORE_SUM.
        #
        HBA_Npl3_HBD_N_SCORE_SUM = 132

        ##
        # \brief HBA_Npl3_HBD_N_SCORE_MAX.
        #
        HBA_Npl3_HBD_N_SCORE_MAX = 133

        ##
        # \brief HBA_Npl3_HBD_O_SCORE_SUM.
        #
        HBA_Npl3_HBD_O_SCORE_SUM = 134

        ##
        # \brief HBA_Npl3_HBD_O_SCORE_MAX.
        #
        HBA_Npl3_HBD_O_SCORE_MAX = 135

        ##
        # \brief HBA_Npl3_HBD_S_SCORE_SUM.
        #
        HBA_Npl3_HBD_S_SCORE_SUM = 136

        ##
        # \brief HBA_Npl3_HBD_S_SCORE_MAX.
        #
        HBA_Npl3_HBD_S_SCORE_MAX = 137

        ##
        # \brief HBA_O3_HBD_N_SCORE_SUM.
        #
        HBA_O3_HBD_N_SCORE_SUM = 138

        ##
        # \brief HBA_O3_HBD_N_SCORE_MAX.
        #
        HBA_O3_HBD_N_SCORE_MAX = 139

        ##
        # \brief HBA_O3_HBD_O_SCORE_SUM.
        #
        HBA_O3_HBD_O_SCORE_SUM = 140

        ##
        # \brief HBA_O3_HBD_O_SCORE_MAX.
        #
        HBA_O3_HBD_O_SCORE_MAX = 141

        ##
        # \brief HBA_O3_HBD_S_SCORE_SUM.
        #
        HBA_O3_HBD_S_SCORE_SUM = 142

        ##
        # \brief HBA_O3_HBD_S_SCORE_MAX.
        #
        HBA_O3_HBD_S_SCORE_MAX = 143

        ##
        # \brief HBA_O2_HBD_N_SCORE_SUM.
        #
        HBA_O2_HBD_N_SCORE_SUM = 144

        ##
        # \brief HBA_O2_HBD_N_SCORE_MAX.
        #
        HBA_O2_HBD_N_SCORE_MAX = 145

        ##
        # \brief HBA_O2_HBD_O_SCORE_SUM.
        #
        HBA_O2_HBD_O_SCORE_SUM = 146

        ##
        # \brief HBA_O2_HBD_O_SCORE_MAX.
        #
        HBA_O2_HBD_O_SCORE_MAX = 147

        ##
        # \brief HBA_O2_HBD_S_SCORE_SUM.
        #
        HBA_O2_HBD_S_SCORE_SUM = 148

        ##
        # \brief HBA_O2_HBD_S_SCORE_MAX.
        #
        HBA_O2_HBD_S_SCORE_MAX = 149

        ##
        # \brief HBA_Oco2_HBD_N_SCORE_SUM.
        #
        HBA_Oco2_HBD_N_SCORE_SUM = 150

        ##
        # \brief HBA_Oco2_HBD_N_SCORE_MAX.
        #
        HBA_Oco2_HBD_N_SCORE_MAX = 151

        ##
        # \brief HBA_Oco2_HBD_O_SCORE_SUM.
        #
        HBA_Oco2_HBD_O_SCORE_SUM = 152

        ##
        # \brief HBA_Oco2_HBD_O_SCORE_MAX.
        #
        HBA_Oco2_HBD_O_SCORE_MAX = 153

        ##
        # \brief HBA_Oco2_HBD_S_SCORE_SUM.
        #
        HBA_Oco2_HBD_S_SCORE_SUM = 154

        ##
        # \brief HBA_Oco2_HBD_S_SCORE_MAX.
        #
        HBA_Oco2_HBD_S_SCORE_MAX = 155

        ##
        # \brief HBA_S3_HBD_N_SCORE_SUM.
        #
        HBA_S3_HBD_N_SCORE_SUM = 156

        ##
        # \brief HBA_S3_HBD_N_SCORE_MAX.
        #
        HBA_S3_HBD_N_SCORE_MAX = 157

        ##
        # \brief HBA_S3_HBD_O_SCORE_SUM.
        #
        HBA_S3_HBD_O_SCORE_SUM = 158

        ##
        # \brief HBA_S3_HBD_O_SCORE_MAX.
        #
        HBA_S3_HBD_O_SCORE_MAX = 159

        ##
        # \brief HBA_S3_HBD_S_SCORE_SUM.
        #
        HBA_S3_HBD_S_SCORE_SUM = 160

        ##
        # \brief HBA_S3_HBD_S_SCORE_MAX.
        #
        HBA_S3_HBD_S_SCORE_MAX = 161

        ##
        # \brief HBA_S2_HBD_N_SCORE_SUM.
        #
        HBA_S2_HBD_N_SCORE_SUM = 162

        ##
        # \brief HBA_S2_HBD_N_SCORE_MAX.
        #
        HBA_S2_HBD_N_SCORE_MAX = 163

        ##
        # \brief HBA_S2_HBD_O_SCORE_SUM.
        #
        HBA_S2_HBD_O_SCORE_SUM = 164

        ##
        # \brief HBA_S2_HBD_O_SCORE_MAX.
        #
        HBA_S2_HBD_O_SCORE_MAX = 165

        ##
        # \brief HBA_S2_HBD_S_SCORE_SUM.
        #
        HBA_S2_HBD_S_SCORE_SUM = 166

        ##
        # \brief HBA_S2_HBD_S_SCORE_MAX.
        #
        HBA_S2_HBD_S_SCORE_MAX = 167

        ##
        # \brief XBD_XBA_SCORE_SUM.
        #
        XBD_XBA_SCORE_SUM = 168

        ##
        # \brief XBD_XBA_SCORE_MAX.
        #
        XBD_XBA_SCORE_MAX = 169

        ##
        # \brief ES_ENERGY.
        #
        ES_ENERGY = 170

        ##
        # \brief ES_ENERGY_SQRD_DIST.
        #
        ES_ENERGY_SQRD_DIST = 171

        ##
        # \brief VDW_ENERGY.
        #
        VDW_ENERGY = 172

    ##
    # \brief 
    #
    TOTAL_DESCRIPTOR_SIZE = 173

    ##
    # \brief 
    #
    LIGAND_DESCRIPTOR_SIZE = 28

    ##
    # \brief Initializes the \e %GRAILDescriptorCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GRAILDescriptorCalculator instance.
    # \param calc 
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
    def initTargetData(tgt_env: CDPL.Chem.MolecularGraph, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, tgt_env_changed: bool = True) -> None: pass

    ##
    # \brief 
    # \param ligand 
    #
    def initLigandData(ligand: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param atom_coords 
    # \param descr 
    # \param update_lig_part 
    #
    def calculate(atom_coords: CDPL.Math.Vector3DArray, descr: CDPL.Math.DVector, update_lig_part: bool = True) -> None: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)
