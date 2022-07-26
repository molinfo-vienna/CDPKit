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
        # \param self The \e %Entry instance to initialize.
        #
        def __init__(self: object) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param entry 
        #
        def __init__(self: object, entry: Entry) -> None: pass

        ##
        # \brief Initializes the \e %Entry instance.
        # \param self The \e %Entry instance to initialize.
        # \param code 
        # \param rep_code 
        # \param rep_by_code 
        # \param obsolete 
        # \param name 
        # \param type 
        # \param struc_ret_func 
        #
        def __init__(self: object, code: str, rep_code: str, rep_by_code: str, obsolete: bool, name: str, type: int, struc_ret_func: MolecularGraphPointerStringFunctor) -> None: pass

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
        def getObjectID(self: Entry) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Entry instance \a entry.
        # \param self The \e %Entry instance this method is called upon.
        # \param entry The \e %Entry instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: Entry, entry: Entry) -> Entry: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getCode(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getReplacedCode(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getReplacedByCode(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getType(self: Entry) -> int: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getName(self: Entry) -> str: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def isObsolete(self: Entry) -> bool: pass

        ##
        # \brief 
        # \param self The \e %Entry instance this method is called upon.
        # \return 
        #
        def getStructure(self: Entry) -> CDPL.Chem.MolecularGraph: pass

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
    # \param self The \e %ResidueDictionary instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %ResidueDictionary instance.
    # \param self The \e %ResidueDictionary instance to initialize.
    # \param dict 
    #
    def __init__(self: object, dict: ResidueDictionary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %ResidueDictionary instance this method is called upon.
    #
    # Different Python \e %ResidueDictionary instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ResidueDictionary instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: ResidueDictionary) -> int: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    # \param entry 
    #
    def addEntry(self: ResidueDictionary, entry: Entry) -> None: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    # \param code 
    # \return 
    #
    def containsEntry(self: ResidueDictionary, code: str) -> bool: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    # \param code 
    #
    def removeEntry(self: ResidueDictionary, code: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    # \param code 
    # \return 
    #
    def getEntry(self: ResidueDictionary, code: str) -> Entry: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    #
    def clear(self: ResidueDictionary) -> None: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    # \return 
    #
    def getNumEntries(self: ResidueDictionary) -> int: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    # \return 
    #
    def getEntries(self: ResidueDictionary) -> list: pass

    ##
    # \brief 
    # \param self The \e %ResidueDictionary instance this method is called upon.
    #
    def loadDefaults(self: ResidueDictionary) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ResidueDictionary instance \a dict.
    # \param self The \e %ResidueDictionary instance this method is called upon.
    # \param dict The \e %ResidueDictionary instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: ResidueDictionary, dict: ResidueDictionary) -> ResidueDictionary: pass

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
