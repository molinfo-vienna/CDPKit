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
# \brief Greedy RMSD-based conformer-diversity filter.
# 
# For each candidate conformer the selector computes the minimum symmetry-equivalent RMSD against the set of already-selected conformers. A new conformer is accepted (added to the selected set) only if its minimum RMSD exceeds the configured threshold.
# 
class RMSDConformerSelector(Boost.Python.instance):

    ##
    # \brief Default maximum number of considered automorphism (symmetry) mappings per setup() call.
    # 
    DEF_MAX_NUM_SYMMETRY_MAPPINGS = 32768

    ##
    # \brief Constructs the <tt>RMSDConformerSelector</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %RMSDConformerSelector instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %RMSDConformerSelector instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the minimum RMSD that a candidate conformer must keep from every already-selected conformer to be accepted.
    # 
    # \param min_rmsd The new minimum RMSD.
    # 
    def setMinRMSD(min_rmsd: float) -> None: pass

    ##
    # \brief Returns the currently configured minimum RMSD threshold.
    # 
    # \return The minimum RMSD threshold.
    # 
    def getMinRMSD() -> float: pass

    ##
    # \brief Sets the callback invoked periodically to allow the selection to be aborted by the user.
    # 
    # \param func The abort-check callback.
    # 
    def setAbortCallback(func: CallbackFunction) -> None: pass

    ##
    # \brief Returns the currently configured abort-check callback.
    # 
    # \return A reference to the abort-check callback.
    # 
    def getAbortCallback() -> CallbackFunction: pass

    ##
    # \brief Returns the number of symmetry (automorphism) mappings enumerated during the last setup() call.
    # 
    # \return The symmetry-mapping count.
    # 
    def getNumSymmetryMappings() -> int: pass

    ##
    # \brief Sets the maximum number of symmetry mappings to enumerate per setup() call.
    # 
    # \param max_num The new maximum number of mappings.
    # 
    def setMaxNumSymmetryMappings(max_num: int) -> None: pass

    ##
    # \brief Returns the currently configured maximum number of symmetry mappings.
    # 
    # \return The maximum number of mappings.
    # 
    def getMaxNumSymmetryMappings() -> int: pass

    ##
    # \brief Sets up the selector for the subgraph of <em>molgraph</em> defined by <em>atom_mask</em> while restricting the enumerated automorphisms to those that preserve the chirality of atoms in <em>stable_config_atom_mask</em> with respect to the supplied 3D coordinates <em>coords</em>.
    # 
    # \param molgraph The parent molecular graph.
    # \param atom_mask The bit mask selecting atoms considered during RMSD computation.
    # \param stable_config_atom_mask The bit mask of atoms whose stereo-configuration must be preserved.
    # \param coords The 3D coordinates used to determine the stereo-configurations.
    # 
    def setup(molgraph: Chem.MolecularGraph, atom_mask: Util.BitSet, stable_config_atom_mask: Util.BitSet, coords: Math.Vector3DArray) -> None: pass

    ##
    # \brief Sets up the selector for the subgraph of <em>molgraph</em> defined by <em>atom_mask</em>.
    # 
    # \param molgraph The parent molecular graph.
    # \param atom_mask The bit mask selecting atoms considered during RMSD computation.
    # 
    def setup(molgraph: Chem.MolecularGraph, atom_mask: Util.BitSet) -> None: pass

    ##
    # \brief Tests whether <em>conf_coords</em> is sufficiently different from already-selected conformers and, if so, adds it to the selected set.
    # 
    # \param conf_coords The candidate conformer's 3D coordinates.
    # 
    # \return <tt>True</tt> if the conformer was selected, and <tt>False</tt> otherwise.
    # 
    def selected(conf_coords: Math.Vector3DArray) -> bool: pass

    objectID = property(getObjectID)

    abortCallback = property(getAbortCallback, setAbortCallback)

    numSymmetryMappings = property(getNumSymmetryMappings)

    maxNumSymmetryMappings = property(getMaxNumSymmetryMappings, setMaxNumSymmetryMappings)

    minRMSD = property(getMinRMSD, setMinRMSD)
