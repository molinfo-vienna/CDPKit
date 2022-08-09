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
class ResidueDictionary(Boost.Python.instance):

    ##
    # \brief 
    #
    class Entry(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Entry instance.
        #
        def __init__() -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param entry 
        #
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param code 
        # \param rep_code 
        # \param rep_by_code 
        # \param obsolete 
        # \param name 
        # \param type 
        # \param struc_ret_func 
        #
        def __init__(code: str, rep_code: str, rep_by_code: str, obsolete: bool, name: str, type: int, struc_ret_func: MolecularGraphPointerStringFunctor) -> None: pass

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
        # \return The assignment target \a self.
        #
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \return 
        #
        def getCode() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getReplacedCode() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getReplacedByCode() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def getType() -> int: pass

        ##
        # \brief 
        # \return 
        #
        def getName() -> str: pass

        ##
        # \brief 
        # \return 
        #
        def isObsolete() -> bool: pass

        ##
        # \brief 
        # \return 
        #
        def getStructure() -> CDPL.Chem.MolecularGraph: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        code = property(getCode)

        ##
        # \brief 
        #
        replacedCode = property(getReplacedCode)

        ##
        # \brief 
        #
        replacedByCode = property(getReplacedByCode)

        ##
        # \brief FIXME!
        #
        obsolete = property(getObsolete)

        ##
        # \brief 
        #
        name = property(getName)

        ##
        # \brief 
        #
        type = property(getType)

        ##
        # \brief 
        #
        structure = property(getStructure)

    ##
    # \brief Initializes the \e %ResidueDictionary instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %ResidueDictionary instance.
    # \param dict 
    #
    def __init__(dict: ResidueDictionary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ResidueDictionary instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ResidueDictionary instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param entry 
    #
    def addEntry(entry: Entry) -> None: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    def containsEntry(code: str) -> bool: pass

    ##
    # \brief 
    # \param code 
    #
    def removeEntry(code: str) -> None: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    def getEntry(code: str) -> Entry: pass

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
    #
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ResidueDictionary instance \a dict.
    # \param dict The \e %ResidueDictionary instance to copy.
    # \return The assignment target \a self.
    #
    def assign(dict: ResidueDictionary) -> ResidueDictionary: pass

    ##
    # \brief 
    # \param dict 
    #
    @staticmethod
    def set(dict: ResidueDictionary) -> None: pass

    ##
    # \brief 
    # \param  
    # \return 
    #
    @staticmethod
    def get(: ) -> ResidueDictionary: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    @staticmethod
    def getReplacedCode(code: str) -> str: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    @staticmethod
    def getReplacedByCode(code: str) -> str: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    @staticmethod
    def isObsolete(code: str) -> bool: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    @staticmethod
    def getName(code: str) -> str: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    @staticmethod
    def isStdResidue(code: str) -> bool: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    @staticmethod
    def getType(code: str) -> int: pass

    ##
    # \brief 
    # \param code 
    # \return 
    #
    @staticmethod
    def getStructure(code: str) -> CDPL.Chem.MolecularGraph: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numEntries = property(getNumEntries)

    ##
    # \brief 
    #
    entries = property(getEntries)