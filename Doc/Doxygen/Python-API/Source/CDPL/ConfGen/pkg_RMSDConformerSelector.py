#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
class RMSDConformerSelector(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MAX_NUM_SYMMETRY_MAPPINGS = 32768

    ##
    # \brief Initializes the \e %RMSDConformerSelector instance.
    # \param self The \e %RMSDConformerSelector instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    #
    # Different Python \e %RMSDConformerSelector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %RMSDConformerSelector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: RMSDConformerSelector) -> int: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \param min_rmsd 
    #
    def setMinRMSD(self: RMSDConformerSelector, min_rmsd: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \return 
    #
    def getMinRMSD(self: RMSDConformerSelector) -> float: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \param func 
    #
    def setAbortCallback(self: RMSDConformerSelector, func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \return 
    #
    def getAbortCallback(self: RMSDConformerSelector) -> CallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \return 
    #
    def getNumSymmetryMappings(self: RMSDConformerSelector) -> int: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \param max_num 
    #
    def setMaxNumSymmetryMappings(self: RMSDConformerSelector, max_num: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \return 
    #
    def getMaxNumSymmetryMappings(self: RMSDConformerSelector) -> int: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \param molgraph 
    # \param atom_mask 
    # \param stable_config_atom_mask 
    # \param coords 
    #
    def setup(self: RMSDConformerSelector, molgraph: CDPL.Chem.MolecularGraph, atom_mask: CDPL.Util.BitSet, stable_config_atom_mask: CDPL.Util.BitSet, coords: CDPL.Math.Vector3DArray) -> None: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \param molgraph 
    # \param atom_mask 
    #
    def setup(self: RMSDConformerSelector, molgraph: CDPL.Chem.MolecularGraph, atom_mask: CDPL.Util.BitSet) -> None: pass

    ##
    # \brief 
    # \param self The \e %RMSDConformerSelector instance this method is called upon.
    # \param conf_coords 
    # \return 
    #
    def selected(self: RMSDConformerSelector, conf_coords: CDPL.Math.Vector3DArray) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    abortCallback = property(getAbortCallback, setAbortCallback)

    ##
    # \brief 
    #
    numSymmetryMappings = property(getNumSymmetryMappings)

    ##
    # \brief 
    #
    maxNumSymmetryMappings = property(getMaxNumSymmetryMappings, setMaxNumSymmetryMappings)

    ##
    # \brief 
    #
    minRMSD = property(getMinRMSD, setMinRMSD)
