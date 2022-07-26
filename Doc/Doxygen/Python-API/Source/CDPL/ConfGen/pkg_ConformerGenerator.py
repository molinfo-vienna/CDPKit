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
class ConformerGenerator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %ConformerGenerator instance.
    # \param self The \e %ConformerGenerator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ConformerGenerator instance this method is called upon.
    #
    # Different Python \e %ConformerGenerator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ConformerGenerator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ConformerGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param molgraph 
    # \return 
    #
    def generate(self: ConformerGenerator, molgraph: CDPL.Chem.MolecularGraph) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \return 
    #
    def getSettings(self: ConformerGenerator) -> ConformerGeneratorSettings: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    #
    def clearFragmentLibraries(self: ConformerGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param lib 
    #
    def addFragmentLibrary(self: ConformerGenerator, lib: FragmentLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    #
    def clearTorsionLibraries(self: ConformerGenerator) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param lib 
    #
    def addTorsionLibrary(self: ConformerGenerator, lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param func 
    #
    def setAbortCallback(self: ConformerGenerator, func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \return 
    #
    def getAbortCallback(self: ConformerGenerator) -> CallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param func 
    #
    def setTimeoutCallback(self: ConformerGenerator, func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \return 
    #
    def getTimeoutCallback(self: ConformerGenerator) -> CallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param func 
    #
    def setLogMessageCallback(self: ConformerGenerator, func: LogMessageCallbackFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \return 
    #
    def getLogMessageCallback(self: ConformerGenerator) -> LogMessageCallbackFunction: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param molgraph 
    #
    def setConformers(self: ConformerGenerator, molgraph: CDPL.Chem.MolecularGraph) -> None: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \return 
    #
    def getNumConformers(self: ConformerGenerator) -> int: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param conf_idx 
    # \return 
    #
    def getConformer(self: ConformerGenerator, conf_idx: int) -> ConformerData: pass

    ##
    # \brief 
    # \param self The \e %ConformerGenerator instance this method is called upon.
    # \param conf_idx 
    # \return 
    #
    def __getitem__(self: ConformerGenerator, conf_idx: int) -> ConformerData: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numConformers = property(getNumConformers)

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
    logMessageCallback = property(getLogMessageCallback, setLogMessageCallback)
