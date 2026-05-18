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
# \brief Calculation of GRAIL descriptors for protein-ligand complexes.
# 
# The descriptor is a vector of 35 elements that captures ligand-only properties (counts of pharmacophore features, heavy atoms, rotatable bonds, \f$ \log P \f$, \f$ TPSA \f$, etc.) and target-environment-specific scores (HBA/HBD occupancy sums and maxima, pi/aromatic/hydrophobic/halogen-bonding interaction scores, and electrostatic
#  - Van der Waals energy contributions). See ElementIndex for the layout.
# 
# \see [\ref GRADE]
# 
class GRAILDescriptorCalculator(Boost.Python.instance):

    ##
    # \brief Indices of the individual elements of the GRAIL descriptor vector.
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
        # \brief Heavy atom count (ligand).
        # 
        HVY_ATOM_COUNT = 8

        ##
        # \brief Rotatable bond count (ligand).
        # 
        ROT_BOND_COUNT = 9

        ##
        # \brief Total computed hydrophobicity (ligand).
        # 
        TOTAL_HYD = 10

        ##
        # \brief Computed \f$ \log P \f$ (ligand).
        # 
        LOGP = 11

        ##
        # \brief Computed topological polar surface area (ligand).
        # 
        TPSA = 12

        ##
        # \brief Sum of HBA occupancy scores against the target environment.
        # 
        ENV_HBA_OCC_SUM = 13

        ##
        # \brief Maximum HBA occupancy score against the target environment.
        # 
        ENV_HBA_OCC_MAX = 14

        ##
        # \brief Sum of HBD occupancy scores against the target environment.
        # 
        ENV_HBD_OCC_SUM = 15

        ##
        # \brief Maximum HBD occupancy score against the target environment.
        # 
        ENV_HBD_OCC_MAX = 16

        ##
        # \brief Sum of (ligand positive-ionizable &rarr; target aromatic) interaction scores.
        # 
        PI_AR_SCORE_SUM = 17

        ##
        # \brief Maximum (ligand positive-ionizable &rarr; target aromatic) interaction score.
        # 
        PI_AR_SCORE_MAX = 18

        ##
        # \brief Sum of (ligand aromatic &rarr; target positive-ionizable) interaction scores.
        # 
        AR_PI_SCORE_SUM = 19

        ##
        # \brief Maximum (ligand aromatic &rarr; target positive-ionizable) interaction score.
        # 
        AR_PI_SCORE_MAX = 20

        ##
        # \brief Sum of hydrophobic-hydrophobic interaction scores.
        # 
        H_H_SCORE_SUM = 21

        ##
        # \brief Maximum hydrophobic-hydrophobic interaction score.
        # 
        H_H_SCORE_MAX = 22

        ##
        # \brief Sum of aromatic-aromatic interaction scores.
        # 
        AR_AR_SCORE_SUM = 23

        ##
        # \brief Maximum aromatic-aromatic interaction score.
        # 
        AR_AR_SCORE_MAX = 24

        ##
        # \brief Sum of (ligand HBD &rarr; target HBA) interaction scores.
        # 
        HBD_HBA_SCORE_SUM = 25

        ##
        # \brief Maximum (ligand HBD &rarr; target HBA) interaction score.
        # 
        HBD_HBA_SCORE_MAX = 26

        ##
        # \brief Sum of (ligand HBA &rarr; target HBD) interaction scores.
        # 
        HBA_HBD_SCORE_SUM = 27

        ##
        # \brief Maximum (ligand HBA &rarr; target HBD) interaction score.
        # 
        HBA_HBD_SCORE_MAX = 28

        ##
        # \brief Sum of (ligand XBD &rarr; target XBA) interaction scores.
        # 
        XBD_XBA_SCORE_SUM = 29

        ##
        # \brief Maximum (ligand XBD &rarr; target XBA) interaction score.
        # 
        XBD_XBA_SCORE_MAX = 30

        ##
        # \brief Electrostatic interaction energy.
        # 
        ES_ENERGY = 31

        ##
        # \brief Electrostatic interaction energy with squared atom-pair distance dependency.
        # 
        ES_ENERGY_SQRD_DIST = 32

        ##
        # \brief Attractive part of the Van der Waals interaction energy.
        # 
        VDW_ENERGY_ATT = 33

        ##
        # \brief Repulsive part of the Van der Waals interaction energy.
        # 
        VDW_ENERGY_REP = 34

    ##
    # \brief Total number of elements in the calculated descriptor vector.
    # 
    TOTAL_DESCRIPTOR_SIZE = 35

    ##
    # \brief Number of ligand-only descriptor elements (the first <tt>LIGAND_DESCRIPTOR_SIZE</tt> entries of the vector).
    # 
    LIGAND_DESCRIPTOR_SIZE = 13

    ##
    # \brief Constructs the <tt>GRAILDescriptorCalculator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>GRAILDescriptorCalculator</tt> instance <em>calc</em>.
    # 
    # \param calc The <tt>GRAILDescriptorCalculator</tt> to copy.
    # 
    def __init__(calc: GRAILDescriptorCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GRAILDescriptorCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GRAILDescriptorCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param calc The other <tt>GRAILDescriptorCalculator</tt> instance.
    # 
    # \return \a self
    # 
    def assign(calc: GRAILDescriptorCalculator) -> GRAILDescriptorCalculator: pass

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
    # \brief Calculates the GRAIL descriptor for the current ligand pose.
    # 
    # The pose is supplied via per-atom 3D coordinates in <em>atom_coords</em> (same order as the atoms of the molecular graph passed to initLigandData()). The result is written to <em>descr</em>.
    # 
    # \param atom_coords The 3D coordinates of the ligand atoms.
    # \param descr The output descriptor vector (resized to TOTAL_DESCRIPTOR_SIZE).
    # \param update_lig_part If <tt>True</tt>, the ligand-only part of the descriptor is recomputed.
    # 
    def calculate(atom_coords: Math.Vector3DArray, descr: Math.DVector, update_lig_part: bool = True) -> None: pass

    objectID = property(getObjectID)
