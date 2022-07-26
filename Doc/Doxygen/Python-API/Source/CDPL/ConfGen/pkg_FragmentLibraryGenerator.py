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
class FragmentLibraryGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FragmentLibraryGenerator instance.
    # \param self The \e %FragmentLibraryGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %FragmentLibraryGenerator instance.
    # \param self The \e %FragmentLibraryGenerator instance to initialize.
    # \param lib 
    #
    def __init__(self: object, lib: FragmentLibrary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    #
    # Different Python \e %FragmentLibraryGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FragmentLibraryGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: FragmentLibraryGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \param lib 
    #
    def setFragmentLibrary(self: FragmentLibraryGenerator, lib: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \return 
    #
    def getFragmentLibrary(self: FragmentLibraryGenerator) -> FragmentLibrary: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \param func 
    #
    def setAbortCallback(self: FragmentLibraryGenerator, func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \return 
    #
    def getAbortCallback(self: FragmentLibraryGenerator) -> CallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \param func 
    #
    def setTimeoutCallback(self: FragmentLibraryGenerator, func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \return 
    #
    def getTimeoutCallback(self: FragmentLibraryGenerator) -> CallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \param func 
    #
    def setLogMessageCallback(self: FragmentLibraryGenerator, func: LogMessageCallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \return 
    #
    def getLogMessageCallback(self: FragmentLibraryGenerator) -> LogMessageCallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \param arg1 
    # \param frag 
    # \return 
    #
    def process(arg1: FragmentLibraryGenerator, self: MolecularGraph, frag: CDPL.Chem.MolecularGraph) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \return 
    #
    def getNumGeneratedConformers(self: FragmentLibraryGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \return 
    #
    def getLibraryEntryHashCode(self: FragmentLibraryGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %FragmentLibraryGenerator instance this method is called upon.
    # \return 
    #
    def getSettings(self: FragmentLibraryGenerator) -> FragmentConformerGeneratorSettings: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    settings = property(getSettings)

    ##
    # \brief 
    #
    abortCallback = property(getAbortCallback, setAbortCallback)

    ##
    # \brief 
    #
    timeoutCallback = property(getTimeoutCallback, setTimeoutCallback)

    ##
    # \brief 
    #
    fragmentLibrary = property(getFragmentLibrary, setFragmentLibrary)

    ##
    # \brief 
    #
    numGeneratedConformers = property(getNumGeneratedConformers)

    ##
    # \brief 
    #
    libraryEntryHashCode = property(getLibraryEntryHashCode)

    ##
    # \brief 
    #
    logMessageCallback = property(getLogMessageCallback, setLogMessageCallback)
