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
# \brief Driver for populating a ConfGen.FragmentLibrary with conformers of canonicalized molecular fragments.
# 
# For each input fragment the generator constructs the corresponding ConfGen.CanonicalFragment, computes its hash code and SMILES string, generates a representative conformer ensemble using ConfGen.FragmentConformerGenerator and stores the result as a new FragmentLibraryEntry in the associated FragmentLibrary. Already-present entries (identified by hash code) are skipped.
# 
class FragmentLibraryGenerator(Boost.Python.instance):

    ##
    # \brief Constructs the <tt>FragmentLibraryGenerator</tt> instance without an associated fragment library.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>FragmentLibraryGenerator</tt> instance and associates it with <em>lib</em>.
    # 
    # \param lib The fragment library to populate.
    # 
    def __init__(lib: FragmentLibrary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FragmentLibraryGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FragmentLibraryGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Sets the fragment library to populate.
    # 
    # \param lib The new fragment library.
    # 
    def setFragmentLibrary(lib: FragmentLibrary) -> None: pass

    ##
    # \brief Returns the currently associated fragment library.
    # 
    # \return A reference to the fragment library smart reference.
    # 
    def getFragmentLibrary() -> FragmentLibrary: pass

    ##
    # \brief Sets the callback invoked periodically to allow conformer generation to be aborted.
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
    # \brief Sets the callback invoked periodically to check whether the configured generation timeout has elapsed.
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
    # \brief Sets the callback that receives log messages produced during fragment processing.
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
    # \brief 
    # \param arg1 
    # \param frag 
    # \return 
    #
    def process(self: MolecularGraph, frag: Chem.MolecularGraph) -> int: pass

    ##
    # \brief Returns the number of conformers generated during the last process() call.
    # 
    # \return The number of generated conformers.
    # 
    def getNumGeneratedConformers() -> int: pass

    ##
    # \brief Returns the hash code of the library entry created during the last process() call.
    # 
    # \return The hash code of the library entry.
    # 
    def getLibraryEntryHashCode() -> int: pass

    ##
    # \brief Returns a reference to the fragment conformer-generation settings.
    # 
    # \return A reference to the settings.
    # 
    def getSettings() -> FragmentConformerGeneratorSettings: pass

    objectID = property(getObjectID)

    settings = property(getSettings)

    abortCallback = property(getAbortCallback, setAbortCallback)

    timeoutCallback = property(getTimeoutCallback, setTimeoutCallback)

    fragmentLibrary = property(getFragmentLibrary, setFragmentLibrary)

    numGeneratedConformers = property(getNumGeneratedConformers)

    libraryEntryHashCode = property(getLibraryEntryHashCode)

    logMessageCallback = property(getLogMessageCallback, setLogMessageCallback)
