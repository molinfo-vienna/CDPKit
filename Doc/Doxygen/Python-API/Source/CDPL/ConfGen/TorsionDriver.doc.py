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
# \brief 
#
class TorsionDriver(Boost.Python.instance):

    ##
    # \brief Initializes the \e %TorsionDriver instance.
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
    # \brief 
    # \return 
    #
    def getSettings() -> TorsionDriverSettings: pass

    ##
    # \brief 
    #
    def clearTorsionLibraries() -> None: pass

    ##
    # \brief 
    # \param lib 
    #
    def addTorsionLibrary(lib: TorsionLibrary) -> None: pass

    ##
    # \brief 
    # \param molgraph 
    # \return 
    #
    def setup(molgraph: Chem.MolecularGraph) -> int: pass

    ##
    # \brief 
    # \param molgraph 
    # \param bond_mask 
    # \return 
    #
    def setup(molgraph: Chem.MolecularGraph, bond_mask: Util.BitSet) -> int: pass

    ##
    # \brief 
    #
    def clearInputCoordinates() -> None: pass

    ##
    # \brief 
    # \param frag_idx 
    #
    def clearInputCoordinates(frag_idx: int) -> None: pass

    ##
    # \brief 
    # \param coords 
    #
    def addInputCoordinates(coords: Math.Vector3DArray) -> None: pass

    ##
    # \brief 
    # \param coords 
    # \param frag_idx 
    #
    def addInputCoordinates(coords: Math.Vector3DArray, frag_idx: int) -> None: pass

    ##
    # \brief 
    # \param conf_data 
    # \param frag_idx 
    #
    def addInputCoordinates(conf_data: ConformerData, frag_idx: int) -> None: pass

    ##
    # \brief 
    # \param func 
    #
    def setAbortCallback(func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getAbortCallback() -> CallbackFunction: pass

    ##
    # \brief 
    # \param func 
    #
    def setTimeoutCallback(func: CallbackFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTimeoutCallback() -> CallbackFunction: pass

    ##
    # \brief 
    # \param func 
    #
    def setLogMessageCallback(func: LogMessageCallbackFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getLogMessageCallback() -> LogMessageCallbackFunction: pass

    ##
    # \brief 
    # \return 
    #
    def generateConformers() -> int: pass

    ##
    # \brief 
    # \return 
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
