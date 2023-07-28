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
class MMFF94SymbolicToNumericAtomTypeMap(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param sym_type 
        # \param num_type 
        # 
        def __init__(sym_type: str, num_type: int) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %Entry instance this method is called upon.
        # 
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        objectID = property(getObjectID)

        ##
        # \brief FIXME!
        # \brief 
        #
        symbolicType = property(getSymbolicType)

        ##
        # \brief FIXME!
        # \brief 
        #
        numericType = property(getNumericType)

    ##
    # \brief Initializes the \e %MMFF94SymbolicToNumericAtomTypeMap instance.
    # \param self The \e %MMFF94SymbolicToNumericAtomTypeMap instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94SymbolicToNumericAtomTypeMap instance.
    # \param self The \e %MMFF94SymbolicToNumericAtomTypeMap instance to initialize.
    # \param map 
    # 
    def __init__(map: MMFF94SymbolicToNumericAtomTypeMap) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %MMFF94SymbolicToNumericAtomTypeMap instance this method is called upon.
    # 
    # Different Python \e %MMFF94SymbolicToNumericAtomTypeMap instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94SymbolicToNumericAtomTypeMap instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param sym_type 
    # \param num_type 
    #
    def addEntry(sym_type: str, num_type: int) -> None: pass

    ##
    # \brief 
    # \param sym_type 
    # \return 
    #
    def removeEntry(sym_type: str) -> bool: pass

    ##
    # \brief 
    # \param sym_type 
    # \return 
    #
    def getEntry(sym_type: str) -> int: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief 
    # \param is 
    #
    def load(is: CDPL.Base.IStream) -> None: pass

    ##
    # \brief 
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94SymbolicToNumericAtomTypeMap instance \a map.
    # \param self The \e %MMFF94SymbolicToNumericAtomTypeMap instance this method is called upon.
    # \param map The \e %MMFF94SymbolicToNumericAtomTypeMap instance to copy.
    # \return \a self
    # 
    def assign(map: MMFF94SymbolicToNumericAtomTypeMap) -> MMFF94SymbolicToNumericAtomTypeMap: pass

    ##
    # \brief 
    # \param map 
    #
    @staticmethod
    def set(map: MMFF94SymbolicToNumericAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94SymbolicToNumericAtomTypeMap: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
