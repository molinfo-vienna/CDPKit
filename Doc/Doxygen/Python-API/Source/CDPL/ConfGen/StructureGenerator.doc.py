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
# \brief High-level driver for the generation of a single low-energy 3D structure from a molecular graph.
# 
# Internally delegates to the same pipeline as ConfGen.ConformerGenerator but stops after the first acceptable conformer has been produced.
# 
class StructureGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>StructureGenerator</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %StructureGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %StructureGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the current generator settings (mutable).
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> StructureGeneratorSettings: pass

    ##
    # \brief Removes all configured fragment libraries.
    # 
    def clearFragmentLibraries() -> None: pass

    ##
    # \brief Adds <em>lib</em> to the list of fragment libraries consulted during fragment-based 3D structure generation.
    # 
    # \param lib The fragment library to add.
    # 
    def addFragmentLibrary(lib: FragmentLibrary) -> None: pass

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
    # \brief Sets the callback invoked when the configured timeout is reached.
    # 
    # \param func The timeout callback.
    # 
    def setTimeoutCallback(func: CallbackFunction) -> None: pass

    ##
    # \brief Returns the currently configured timeout callback.
    # 
    # \return A reference to the timeout callback.
    # 
    def getTimeoutCallback() -> CallbackFunction: pass

    ##
    # \brief Sets the callback receiving log messages emitted by the generator.
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
    # \brief Generates a single 3D structure for <em>molgraph</em>.
    # 
    # \param molgraph The input molecular graph.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the generation.
    # 
    def generate(molgraph: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Generates a single 3D structure for <em>molgraph</em> while keeping the substructure <em>fixed_substr</em> at its current 3D coordinates.
    # 
    # \param molgraph The input molecular graph.
    # \param fixed_substr The substructure that must retain its current 3D coordinates.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the generation. 
    # 
    # \since 1.1
    # 
    def generate(molgraph: Chem.MolecularGraph, fixed_substr: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Generates a single 3D structure for <em>molgraph</em> while keeping the substructure <em>fixed_substr</em> at the supplied 3D coordinates <em>fixed_substr_coords</em>.
    # 
    # \param molgraph The input molecular graph.
    # \param fixed_substr The substructure that must retain the supplied 3D coordinates.
    # \param fixed_substr_coords The 3D coordinates assigned to <em>fixed_substr</em>.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the generation. 
    # 
    # \since 1.1
    # 
    def generate(molgraph: Chem.MolecularGraph, fixed_substr: Chem.MolecularGraph, fixed_substr_coords: Math.Vector3DArray) -> int: pass

    ##
    # \brief Transfers the generated 3D coordinates onto the atoms of <em>molgraph</em> (via Chem.set3DCoordinates).
    # 
    # \param molgraph The molecular graph receiving the 3D coordinates.
    # 
    def setCoordinates(molgraph: Chem.MolecularGraph) -> None: pass

    ##
    # \brief Returns the conformer data produced by the most recent generate() call.
    # 
    # \return A reference to the conformer data.
    # 
    def getCoordinates() -> ConformerData: pass

    objectID = property(getObjectID)

    settings = property(getSettings)

    coordinates = property(getCoordinates)

    abortCallback = property(getAbortCallback, setAbortCallback)

    timeoutCallback = property(getTimeoutCallback, setTimeoutCallback)

    logMessageCallback = property(getLogMessageCallback, setLogMessageCallback)
