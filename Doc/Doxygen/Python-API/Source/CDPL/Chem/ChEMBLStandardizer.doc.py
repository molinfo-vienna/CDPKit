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
# \brief Implementation of the ChEMBL structure preprocessing pipeline.
# 
# \see [\ref CSCP]
# 
class ChEMBLStandardizer(Boost.Python.instance):

    ##
    # \brief Bitwise-OR-combined flags reporting which standardization steps modified the input molecule.
    # 
    class ChangeFlags(Boost.Python.enum):

        ##
        # \brief No changes were applied.
        # 
        NONE = 0

        ##
        # \brief The molecule matched a ChEMBL exclusion criterion and was not processed further.
        # 
        EXCLUDED = 1

        ##
        # \brief Removable explicit hydrogen atoms were removed.
        # 
        EXPLICIT_HYDROGENS_REMOVED = 2

        ##
        # \brief Atoms/bonds with unknown stereo descriptors were standardized.
        # 
        UNKNOWN_STEREO_STANDARDIZED = 4

        ##
        # \brief Aromatic bonds were kekulized to alternating single/double bonds.
        # 
        BONDS_KEKULIZED = 8

        ##
        # \brief Functional-group structure normalizations were applied.
        # 
        STRUCTURE_NORMALIZED = 16

        ##
        # \brief Atom formal charges were removed where possible.
        # 
        CHARGES_REMOVED = 32

        ##
        # \brief Defined stereo at tartrate-like substructures was cleared.
        # 
        TARTRATE_STEREO_CLEARED = 64

        ##
        # \brief 2D bond-angle artefacts were corrected.
        # 
        STRUCTURE_2D_CORRECTED = 128

        ##
        # \brief Atom isotope information was cleared.
        # 
        ISOTOPE_INFO_CLEARED = 256

        ##
        # \brief Salt components were removed (parent extraction only).
        # 
        SALT_COMPONENTS_REMOVED = 512

        ##
        # \brief Common solvent components were removed (parent extraction only).
        # 
        SOLVENT_COMPONENTS_REMOVED = 1024

        ##
        # \brief Duplicate disconnected components were collapsed (parent extraction only).
        # 
        DUPLICATE_COMPONENTS_REMOVED = 2048

    ##
    # \brief Constructs the <tt>ChEMBLStandardizer</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>ChEMBLStandardizer</tt> instance <em>standardizer</em>.
    # 
    # \param standardizer The <tt>ChEMBLStandardizer</tt> to copy.
    # 
    def __init__(standardizer: ChEMBLStandardizer) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ChEMBLStandardizer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ChEMBLStandardizer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the state of this standardizer by a copy of the state of <em>standardizer</em>.
    # 
    # \param standardizer The source <tt>ChEMBLStandardizer</tt>.
    # 
    # \return \a self
    # 
    def assign(standardizer: ChEMBLStandardizer) -> ChEMBLStandardizer: pass

    ##
    # \brief Standardizes <em>mol</em> in place.
    # 
    # \param mol The molecule to standardize (modified in place).
    # \param proc_excld If <tt>True</tt>, ChEMBL exclusion criteria are ignored and the molecule is processed regardless.
    # 
    # \return A bitwise-OR combination of ChangeFlags reporting which standardization steps modified the molecule.
    # 
    def standardize(mol: Molecule, proc_excld: bool = False) -> ChangeFlags: pass

    ##
    # \brief 
    # \param mol 
    # \param std_mol 
    # \param proc_excluded 
    # \return 
    #
    def standardize(mol: MolecularGraph, std_mol: Molecule, proc_excluded: bool = False) -> ChangeFlags: pass

    ##
    # \brief Extracts the parent compound of <em>mol</em> in place (removing salt/solvent components).
    # 
    # \param mol The molecule from which to extract the parent (modified in place).
    # \param neutralize If <tt>True</tt>, charges of the extracted parent are subsequently neutralized.
    # \param check_exclusion If <tt>True</tt>, ChEMBL exclusion criteria are checked before processing.
    # 
    # \return A bitwise-OR combination of ChangeFlags reporting which steps modified the molecule.
    # 
    def getParent(mol: Molecule, neutralize: bool = True, check_exclusion: bool = True) -> ChangeFlags: pass

    ##
    # \brief 
    # \param mol 
    # \param parent_mol 
    # \param neutralize 
    # \param check_exclusion 
    # \return 
    #
    def getParent(mol: MolecularGraph, parent_mol: Molecule, neutralize: bool = True, check_exclusion: bool = True) -> ChangeFlags: pass

    objectID = property(getObjectID)
