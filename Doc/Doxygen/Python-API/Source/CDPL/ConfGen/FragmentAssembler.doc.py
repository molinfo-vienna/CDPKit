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
# \brief Driver for the fragment-based generation of 3D starting conformers.
# 
# The assembler decomposes a molecular graph into chain and ring fragments, looks up pre-built conformers from a ConfGen.FragmentLibrary for each fragment (generating them on the fly when no library entry is available) and reassembles them into full 3D structures. The conformers produced this way are intended to serve as <em>starting conformers</em> for subsequent torsion driving — they are not (in general) a final conformer ensemble.
# 
# \see ConfGen.TorsionDriver, ConfGen.ConformerGenerator
# 
class FragmentAssembler(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>FragmentAssembler</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentAssembler instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentAssembler instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the current assembler settings (mutable).
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> FragmentAssemblerSettings: pass

    ##
    # \brief Removes all configured fragment libraries.
    # 
    def clearFragmentLibraries() -> None: pass

    ##
    # \brief Adds <em>lib</em> to the list of fragment libraries consulted during assembly.
    # 
    # \param lib The fragment library to add.
    # 
    def addFragmentLibrary(lib: FragmentLibrary) -> None: pass

    ##
    # \brief Sets the callback invoked periodically to allow the processing to be aborted by the user.
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
    # \brief Sets the callback receiving log messages emitted by the assembler.
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
    # \brief Assembles 3D conformer(s) for <em>molgraph</em> from fragment building blocks.
    # 
    # \param molgraph The input molecular graph.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the assembly.
    # 
    def assemble(molgraph: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Assembles 3D conformer(s) for <em>molgraph</em> while keeping the substructure <em>fixed_substr</em> at the supplied 3D coordinates.
    # 
    # \param molgraph The input molecular graph.
    # \param fixed_substr The substructure that must retain the supplied 3D coordinates.
    # \param fixed_substr_coords The 3D coordinates assigned to <em>fixed_substr</em>.
    # 
    # \return A ConfGen.ReturnCode value reporting the outcome of the assembly. 
    # 
    # \since 1.1
    # 
    def assemble(molgraph: Chem.MolecularGraph, fixed_substr: Chem.MolecularGraph, fixed_substr_coords: Math.Vector3DArray) -> int: pass

    ##
    # \brief Returns the number of assembled conformers.
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
