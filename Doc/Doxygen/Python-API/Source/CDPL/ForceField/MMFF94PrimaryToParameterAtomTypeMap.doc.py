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
class MMFF94PrimaryToParameterAtomTypeMap(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief 
        #
        NUM_TYPES = 4

        ##
        # \brief Initializes the \e %Entry instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param atom_type 
        # \param param_types 
        # 
        def __init__(atom_type: int, param_types: object) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param entry The \e %Entry instance to copy.
        # \return \a self
        # 
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getAtomType() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getParameterAtomTypes() -> object: pass

        ##
        # \brief 
        # \return 
        #
        def __nonzero__() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def __bool__() -> bool: pass

        objectID = property(getObjectID)

        atomType = property(getAtomType)

        ##
        # \brief FIXME!
        # \brief 
        #
        paramAtomTypes = property(getParamAtomTypes)

    ##
    # \brief Initializes the \e %MMFF94PrimaryToParameterAtomTypeMap instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %MMFF94PrimaryToParameterAtomTypeMap instance with a copy of the state of the \e %MMFF94PrimaryToParameterAtomTypeMap instance \a map.
    # \param map The \e %MMFF94PrimaryToParameterAtomTypeMap instance to copy.
    # 
    def __init__(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %MMFF94PrimaryToParameterAtomTypeMap instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %MMFF94PrimaryToParameterAtomTypeMap instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param atom_type 
    # \param param_types 
    #
    def addEntry(atom_type: int, param_types: object) -> None: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def removeEntry(atom_type: int) -> bool: pass

    ##
    # \brief 
    # \param atom_type 
    # \return 
    #
    def getEntry(atom_type: int) -> Entry: pass

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
    def load(is: Base.IStream) -> None: pass

    ##
    # \brief 
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MMFF94PrimaryToParameterAtomTypeMap instance \a map.
    # \param map The \e %MMFF94PrimaryToParameterAtomTypeMap instance to copy.
    # \return \a self
    # 
    def assign(map: MMFF94PrimaryToParameterAtomTypeMap) -> MMFF94PrimaryToParameterAtomTypeMap: pass

    ##
    # \brief 
    # \param map 
    #
    @staticmethod
    def set(map: MMFF94PrimaryToParameterAtomTypeMap) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> MMFF94PrimaryToParameterAtomTypeMap: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
