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
# \brief Driver for the systematic enumeration of conformers obtained by rotating around rotatable bonds of a molecular graph, using preferred torsion angles taken from configured ConfGen.TorsionLibrary instances.
# 
class TorsionDriver(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>TorsionDriver</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TorsionDriver instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TorsionDriver instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the current driver settings (mutable).
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> TorsionDriverSettings: pass

    ##
    # \brief Removes all configured torsion libraries.
    # 
    def clearTorsionLibraries() -> None: pass

    ##
    # \brief Adds <em>lib</em> to the list of torsion libraries consulted during torsion driving.
    # 
    # \param lib The torsion library to add.
    # 
    def addTorsionLibrary(lib: TorsionLibrary) -> None: pass

    ##
    # \brief Sets up the driver for <em>molgraph</em> with the default rotatable-bond perception.
    # 
    # \param molgraph The input molecular graph.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the setup.
    # 
    def setup(molgraph: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Sets up the driver for <em>molgraph</em> using only the bonds whose corresponding bit is set in <em>bond_mask</em> as rotatable.
    # 
    # \param molgraph The input molecular graph.
    # \param bond_mask The bit mask of rotatable bonds (one bit per bond of <em>molgraph</em>).
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the setup.
    # 
    def setup(molgraph: Chem.MolecularGraph, bond_mask: Util.BitSet) -> int: pass

    ##
    # \brief Removes all stored input coordinates.
    # 
    def clearInputCoordinates() -> None: pass

    ##
    # \brief Removes all input coordinates of the fragment at index <em>frag_idx</em>.
    # 
    # \param frag_idx The zero-based fragment index.
    # 
    def clearInputCoordinates(frag_idx: int) -> None: pass

    ##
    # \brief Adds <em>coords</em> as a new starting conformation that the driver will torsion-drive.
    # 
    # \param coords The input 3D coordinates.
    # 
    def addInputCoordinates(coords: Math.Vector3DArray) -> None: pass

    ##
    # \brief Adds <em>coords</em> as a new starting conformation restricted to the fragment at index <em>frag_idx</em>.
    # 
    # \param coords The input 3D coordinates of the fragment.
    # \param frag_idx The zero-based fragment index.
    # 
    def addInputCoordinates(coords: Math.Vector3DArray, frag_idx: int) -> None: pass

    ##
    # \brief Adds the conformer data shared reference <em>conf_data</em> as a new starting conformation restricted to the fragment at index <em>frag_idx</em>.
    # 
    # \param conf_data The input conformer data.
    # \param frag_idx The zero-based fragment index.
    # 
    def addInputCoordinates(conf_data: ConformerData, frag_idx: int) -> None: pass

    ##
    # \brief Sets the callback invoked periodically to allow the generation to be aborted by the user.
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
    # \brief Sets the callback invoked periodically to check whether the configured timeout has elapsed.
    # 
    # \param func The timeout-check callback.
    # 
    def setTimeoutCallback(func: CallbackFunction) -> None: pass

    ##
    # \brief Returns the currently configured timeout-check callback.
    # 
    # \return A reference to the timeout-check callback.
    # 
    def getTimeoutCallback() -> CallbackFunction: pass

    ##
    # \brief Sets the callback receiving log messages emitted by the driver.
    # 
    # \param func The log-message callback.
    # 
    def setLogMessageCallback(func: LogMessageCallbackFunction) -> None: pass

    ##
    # \brief Returns the currently configured log-message callback.
    # 
    # \return A reference to the log-message callback.
    # 
    def getLogMessageCallback() -> LogMessageCallbackFunction: pass

    ##
    # \brief Runs the torsion-driving conformer enumeration.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the generation.
    # 
    def generateConformers() -> int: pass

    ##
    # \brief Returns the number of generated conformers.
    # 
    # \return The conformer count.
    # 
    def getNumConformers() -> int: pass

    ##
    # \brief 
    # \param conf_idx 
    # \return 
    #
    def getConformer(conf_idx: int) -> ConformerData: pass

    ##
    # \brief 
    # \param conf_idx 
    # \return 
    #
    def __getitem__(conf_idx: int) -> ConformerData: pass

    objectID = property(getObjectID)

    numConformers = property(getNumConformers)

    settings = property(getSettings)

    abortCallback = property(getAbortCallback, setAbortCallback)

    timeoutCallback = property(getTimeoutCallback, setTimeoutCallback)

    logMessageCallback = property(getLogMessageCallback, setLogMessageCallback)
