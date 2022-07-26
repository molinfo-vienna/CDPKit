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
class StructureGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %StructureGenerator instance.
    # \param self The \e %StructureGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %StructureGenerator instance this method is called upon.
    #
    # Different Python \e %StructureGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %StructureGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: StructureGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \return 
    #
    def getSettings(self: StructureGenerator) -> StructureGeneratorSettings: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    #
    def clearFragmentLibraries(self: StructureGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \param lib 
    #
    def addFragmentLibrary(self: StructureGenerator, lib: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    #
    def clearTorsionLibraries(self: StructureGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \param lib 
    #
    def addTorsionLibrary(self: StructureGenerator, lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \param func 
    #
    def setAbortCallback(self: StructureGenerator, func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \return 
    #
    def getAbortCallback(self: StructureGenerator) -> CallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \param func 
    #
    def setTimeoutCallback(self: StructureGenerator, func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \return 
    #
    def getTimeoutCallback(self: StructureGenerator) -> CallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def generate(self: StructureGenerator, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \param molgraph 
    #
    def setCoordinates(self: StructureGenerator, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %StructureGenerator instance this method is called upon.
    # \return 
    #
    def getCoordinates(self: StructureGenerator) -> ConformerData: pass

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
    coordinates = property(getCoordinates)

    ##
    # \brief 
    #
    abortCallback = property(getAbortCallback, setAbortCallback)

    ##
    # \brief 
    #
    timeoutCallback = property(getTimeoutCallback, setTimeoutCallback)

    ##
    # \brief FIXME!
    #
    logMessageCallback = property(getLogMessageCallback, setLogMessageCallback)
