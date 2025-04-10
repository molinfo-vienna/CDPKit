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
    # \brief 
    #
    class ChangeFlags(Boost.Python.enum):

        ##
        # \brief NONE.
        #
        NONE = 0

        ##
        # \brief EXCLUDED.
        #
        EXCLUDED = 1

        ##
        # \brief EXPLICIT_HYDROGENS_REMOVED.
        #
        EXPLICIT_HYDROGENS_REMOVED = 2

        ##
        # \brief UNKNOWN_STEREO_STANDARDIZED.
        #
        UNKNOWN_STEREO_STANDARDIZED = 4

        ##
        # \brief BONDS_KEKULIZED.
        #
        BONDS_KEKULIZED = 8

        ##
        # \brief STRUCTURE_NORMALIZED.
        #
        STRUCTURE_NORMALIZED = 16

        ##
        # \brief CHARGES_REMOVED.
        #
        CHARGES_REMOVED = 32

        ##
        # \brief TARTRATE_STEREO_CLEARED.
        #
        TARTRATE_STEREO_CLEARED = 64

        ##
        # \brief STRUCTURE_2D_CORRECTED.
        #
        STRUCTURE_2D_CORRECTED = 128

        ##
        # \brief ISOTOPE_INFO_CLEARED.
        #
        ISOTOPE_INFO_CLEARED = 256

        ##
        # \brief SALT_COMPONENTS_REMOVED.
        #
        SALT_COMPONENTS_REMOVED = 512

        ##
        # \brief SOLVENT_COMPONENTS_REMOVED.
        #
        SOLVENT_COMPONENTS_REMOVED = 1024

        ##
        # \brief DUPLICATE_COMPONENTS_REMOVED.
        #
        DUPLICATE_COMPONENTS_REMOVED = 2048

    ##
    # \brief Initializes the \e %ChEMBLStandardizer instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %ChEMBLStandardizer instance \a standardizer.
    # \param standardizer The \e %ChEMBLStandardizer instance to copy.
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
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ChEMBLStandardizer instance \a standardizer.
    # \param standardizer The \c %ChEMBLStandardizer instance to copy.
    # \return \a self
    # 
    def assign(standardizer: ChEMBLStandardizer) -> ChEMBLStandardizer: pass

    ##
    # \brief 
    # \param mol 
    # \param proc_excld 
    # \return 
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
    # \brief 
    # \param mol 
    # \param neutralize 
    # \param check_exclusion 
    # \return 
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
