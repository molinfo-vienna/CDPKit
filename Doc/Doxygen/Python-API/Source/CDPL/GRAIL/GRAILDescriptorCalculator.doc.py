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
        # \brief HVY_ATOM_COUNT.
        #
        HVY_ATOM_COUNT = 8

        ##
        # \brief ROT_BOND_COUNT.
        #
        ROT_BOND_COUNT = 9

        ##
        # \brief TOTAL_HYD.
        #
        TOTAL_HYD = 10

        ##
        # \brief LOGP.
        #
        LOGP = 11

        ##
        # \brief TPSA.
        #
        TPSA = 12

        ##
        # \brief ENV_HBA_OCC_SUM.
        #
        ENV_HBA_OCC_SUM = 13

        ##
        # \brief ENV_HBA_OCC_MAX.
        #
        ENV_HBA_OCC_MAX = 14

        ##
        # \brief ENV_HBD_OCC_SUM.
        #
        ENV_HBD_OCC_SUM = 15

        ##
        # \brief ENV_HBD_OCC_MAX.
        #
        ENV_HBD_OCC_MAX = 16

        ##
        # \brief PI_AR_SCORE_SUM.
        #
        PI_AR_SCORE_SUM = 17

        ##
        # \brief PI_AR_SCORE_MAX.
        #
        PI_AR_SCORE_MAX = 18

        ##
        # \brief AR_PI_SCORE_SUM.
        #
        AR_PI_SCORE_SUM = 19

        ##
        # \brief AR_PI_SCORE_MAX.
        #
        AR_PI_SCORE_MAX = 20

        ##
        # \brief H_H_SCORE_SUM.
        #
        H_H_SCORE_SUM = 21

        ##
        # \brief H_H_SCORE_MAX.
        #
        H_H_SCORE_MAX = 22

        ##
        # \brief AR_AR_SCORE_SUM.
        #
        AR_AR_SCORE_SUM = 23

        ##
        # \brief AR_AR_SCORE_MAX.
        #
        AR_AR_SCORE_MAX = 24

        ##
        # \brief HBD_HBA_SCORE_SUM.
        #
        HBD_HBA_SCORE_SUM = 25

        ##
        # \brief HBD_HBA_SCORE_MAX.
        #
        HBD_HBA_SCORE_MAX = 26

        ##
        # \brief HBA_HBD_SCORE_SUM.
        #
        HBA_HBD_SCORE_SUM = 27

        ##
        # \brief HBA_HBD_SCORE_MAX.
        #
        HBA_HBD_SCORE_MAX = 28

        ##
        # \brief XBD_XBA_SCORE_SUM.
        #
        XBD_XBA_SCORE_SUM = 29

        ##
        # \brief XBD_XBA_SCORE_MAX.
        #
        XBD_XBA_SCORE_MAX = 30

        ##
        # \brief ES_ENERGY.
        #
        ES_ENERGY = 31

        ##
        # \brief ES_ENERGY_SQRD_DIST.
        #
        ES_ENERGY_SQRD_DIST = 32

        ##
        # \brief VDW_ENERGY_ATT.
        #
        VDW_ENERGY_ATT = 33

        ##
        # \brief VDW_ENERGY_REP.
        #
        VDW_ENERGY_REP = 34

    ##
    # \brief 
    #
    TOTAL_DESCRIPTOR_SIZE = 35

    ##
    # \brief 
    #
    LIGAND_DESCRIPTOR_SIZE = 13

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
