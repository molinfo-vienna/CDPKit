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
        # \brief ENV_HBA_N_OCC.
        #
        ENV_HBA_N_OCC = 28

        ##
        # \brief ENV_HBA_O_OCC.
        #
        ENV_HBA_O_OCC = 29

        ##
        # \brief ENV_HBA_S_OCC.
        #
        ENV_HBA_S_OCC = 30

        ##
        # \brief ENV_HBD_N_OCC.
        #
        ENV_HBD_N_OCC = 31

        ##
        # \brief ENV_HBD_O_OCC.
        #
        ENV_HBD_O_OCC = 32

        ##
        # \brief ENV_HBD_S_OCC.
        #
        ENV_HBD_S_OCC = 33

        ##
        # \brief PI_AR_SCORE.
        #
        PI_AR_SCORE = 34

        ##
        # \brief AR_PI_SCORE.
        #
        AR_PI_SCORE = 35

        ##
        # \brief H_H_SCORE.
        #
        H_H_SCORE = 36

        ##
        # \brief AR_AR_SCORE.
        #
        AR_AR_SCORE = 37

        ##
        # \brief HBD_HBA_N_SCORE.
        #
        HBD_HBA_N_SCORE = 38

        ##
        # \brief HBD_HBA_O_SCORE.
        #
        HBD_HBA_O_SCORE = 39

        ##
        # \brief HBD_HBA_S_SCORE.
        #
        HBD_HBA_S_SCORE = 40

        ##
        # \brief HBD_N3_HBA_N_SCORE.
        #
        HBD_N3_HBA_N_SCORE = 41

        ##
        # \brief HBD_N3_HBA_O_SCORE.
        #
        HBD_N3_HBA_O_SCORE = 42

        ##
        # \brief HBD_N3_HBA_S_SCORE.
        #
        HBD_N3_HBA_S_SCORE = 43

        ##
        # \brief HBD_N2_HBA_N_SCORE.
        #
        HBD_N2_HBA_N_SCORE = 44

        ##
        # \brief HBD_N2_HBA_O_SCORE.
        #
        HBD_N2_HBA_O_SCORE = 45

        ##
        # \brief HBD_N2_HBA_S_SCORE.
        #
        HBD_N2_HBA_S_SCORE = 46

        ##
        # \brief HBD_Nar_HBA_N_SCORE.
        #
        HBD_Nar_HBA_N_SCORE = 47

        ##
        # \brief HBD_Nar_HBA_O_SCORE.
        #
        HBD_Nar_HBA_O_SCORE = 48

        ##
        # \brief HBD_Nar_HBA_S_SCORE.
        #
        HBD_Nar_HBA_S_SCORE = 49

        ##
        # \brief HBD_Nam_HBA_N_SCORE.
        #
        HBD_Nam_HBA_N_SCORE = 50

        ##
        # \brief HBD_Nam_HBA_O_SCORE.
        #
        HBD_Nam_HBA_O_SCORE = 51

        ##
        # \brief HBD_Nam_HBA_S_SCORE.
        #
        HBD_Nam_HBA_S_SCORE = 52

        ##
        # \brief HBD_Npl3_HBA_N_SCORE.
        #
        HBD_Npl3_HBA_N_SCORE = 53

        ##
        # \brief HBD_Npl3_HBA_O_SCORE.
        #
        HBD_Npl3_HBA_O_SCORE = 54

        ##
        # \brief HBD_Npl3_HBA_S_SCORE.
        #
        HBD_Npl3_HBA_S_SCORE = 55

        ##
        # \brief HBD_N4_HBA_N_SCORE.
        #
        HBD_N4_HBA_N_SCORE = 56

        ##
        # \brief HBD_N4_HBA_O_SCORE.
        #
        HBD_N4_HBA_O_SCORE = 57

        ##
        # \brief HBD_N4_HBA_S_SCORE.
        #
        HBD_N4_HBA_S_SCORE = 58

        ##
        # \brief HBD_O3_HBA_N_SCORE.
        #
        HBD_O3_HBA_N_SCORE = 59

        ##
        # \brief HBD_O3_HBA_O_SCORE.
        #
        HBD_O3_HBA_O_SCORE = 60

        ##
        # \brief HBD_O3_HBA_S_SCORE.
        #
        HBD_O3_HBA_S_SCORE = 61

        ##
        # \brief HBD_S3_HBA_N_SCORE.
        #
        HBD_S3_HBA_N_SCORE = 62

        ##
        # \brief HBD_S3_HBA_O_SCORE.
        #
        HBD_S3_HBA_O_SCORE = 63

        ##
        # \brief HBD_S3_HBA_S_SCORE.
        #
        HBD_S3_HBA_S_SCORE = 64

        ##
        # \brief HBA_HBD_N_SCORE.
        #
        HBA_HBD_N_SCORE = 65

        ##
        # \brief HBA_HBD_O_SCORE.
        #
        HBA_HBD_O_SCORE = 66

        ##
        # \brief HBA_HBD_S_SCORE.
        #
        HBA_HBD_S_SCORE = 67

        ##
        # \brief HBA_N3_HBD_N_SCORE.
        #
        HBA_N3_HBD_N_SCORE = 68

        ##
        # \brief HBA_N3_HBD_O_SCORE.
        #
        HBA_N3_HBD_O_SCORE = 69

        ##
        # \brief HBA_N3_HBD_S_SCORE.
        #
        HBA_N3_HBD_S_SCORE = 70

        ##
        # \brief HBA_N2_HBD_N_SCORE.
        #
        HBA_N2_HBD_N_SCORE = 71

        ##
        # \brief HBA_N2_HBD_O_SCORE.
        #
        HBA_N2_HBD_O_SCORE = 72

        ##
        # \brief HBA_N2_HBD_S_SCORE.
        #
        HBA_N2_HBD_S_SCORE = 73

        ##
        # \brief HBA_N1_HBD_N_SCORE.
        #
        HBA_N1_HBD_N_SCORE = 74

        ##
        # \brief HBA_N1_HBD_O_SCORE.
        #
        HBA_N1_HBD_O_SCORE = 75

        ##
        # \brief HBA_N1_HBD_S_SCORE.
        #
        HBA_N1_HBD_S_SCORE = 76

        ##
        # \brief HBA_Nar_HBD_N_SCORE.
        #
        HBA_Nar_HBD_N_SCORE = 77

        ##
        # \brief HBA_Nar_HBD_O_SCORE.
        #
        HBA_Nar_HBD_O_SCORE = 78

        ##
        # \brief HBA_Nar_HBD_S_SCORE.
        #
        HBA_Nar_HBD_S_SCORE = 79

        ##
        # \brief HBA_Npl3_HBD_N_SCORE.
        #
        HBA_Npl3_HBD_N_SCORE = 80

        ##
        # \brief HBA_Npl3_HBD_O_SCORE.
        #
        HBA_Npl3_HBD_O_SCORE = 81

        ##
        # \brief HBA_Npl3_HBD_S_SCORE.
        #
        HBA_Npl3_HBD_S_SCORE = 82

        ##
        # \brief HBA_O3_HBD_N_SCORE.
        #
        HBA_O3_HBD_N_SCORE = 83

        ##
        # \brief HBA_O3_HBD_O_SCORE.
        #
        HBA_O3_HBD_O_SCORE = 84

        ##
        # \brief HBA_O3_HBD_S_SCORE.
        #
        HBA_O3_HBD_S_SCORE = 85

        ##
        # \brief HBA_O2_HBD_N_SCORE.
        #
        HBA_O2_HBD_N_SCORE = 86

        ##
        # \brief HBA_O2_HBD_O_SCORE.
        #
        HBA_O2_HBD_O_SCORE = 87

        ##
        # \brief HBA_O2_HBD_S_SCORE.
        #
        HBA_O2_HBD_S_SCORE = 88

        ##
        # \brief HBA_Oco2_HBD_N_SCORE.
        #
        HBA_Oco2_HBD_N_SCORE = 89

        ##
        # \brief HBA_Oco2_HBD_O_SCORE.
        #
        HBA_Oco2_HBD_O_SCORE = 90

        ##
        # \brief HBA_Oco2_HBD_S_SCORE.
        #
        HBA_Oco2_HBD_S_SCORE = 91

        ##
        # \brief HBA_S3_HBD_N_SCORE.
        #
        HBA_S3_HBD_N_SCORE = 92

        ##
        # \brief HBA_S3_HBD_O_SCORE.
        #
        HBA_S3_HBD_O_SCORE = 93

        ##
        # \brief HBA_S3_HBD_S_SCORE.
        #
        HBA_S3_HBD_S_SCORE = 94

        ##
        # \brief HBA_S2_HBD_N_SCORE.
        #
        HBA_S2_HBD_N_SCORE = 95

        ##
        # \brief HBA_S2_HBD_O_SCORE.
        #
        HBA_S2_HBD_O_SCORE = 96

        ##
        # \brief HBA_S2_HBD_S_SCORE.
        #
        HBA_S2_HBD_S_SCORE = 97

        ##
        # \brief XBD_XBA_SCORE.
        #
        XBD_XBA_SCORE = 98

        ##
        # \brief ES_ENERGY.
        #
        ES_ENERGY = 99

        ##
        # \brief VDW_ENERGY.
        #
        VDW_ENERGY = 100

    ##
    # \brief 
    #
    TOTAL_DESCRIPTOR_SIZE = 101

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
