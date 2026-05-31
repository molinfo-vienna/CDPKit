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
# \brief A global dictionary for the lookup of meta-data associated with the residues in biological macromolecules.
# 
class ResidueDictionary(Boost.Python.instance):

    ##
    # \brief A single residue dictionary entry.
    # 
    class Entry(Boost.Python.instance):

        ##
        # \brief Constructs an empty (default-initialized) <tt>Entry</tt> instance.
        # 
        def __init__() -> None: pass

        ##
        # \brief Initializes a copy of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # 
        def __init__(entry: Entry) -> None: pass

        ##
        # \brief Constructs and initializes an <tt>Entry</tt> instance with the given data.
        # 
        # \param code The three-letter code (TLC) of the residue.
        # \param rep_code The TLC of the residue this entry replaces (or an empty string if it does not replace any other residue).
        # \param rep_by_code The TLC of the residue that replaces this one (or an empty string if it has not been replaced).
        # \param parent_code The TLC of the parent residue (or an empty string if there is no parent).
        # \param one_letter_code The one-letter residue code (or an empty string if not defined).
        # \param obsolete <tt>True</tt> if the residue type is obsolete, and <tt>False</tt> otherwise.
        # \param name The full residue name.
        # \param type The residue type (see Biomol.ResidueType).
        # \param struc_ret_func The function used to retrieve the residue structure on demand.
        # 
        def __init__(code: str, rep_code: str, rep_by_code: str, parent_code: str, one_letter_code: str, obsolete: bool, name: str, type: int, struc_ret_func: MolecularGraphPointerStringFunctor) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Entry instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Entry instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Entry instance \a entry.
        # \param entry The \c %Entry instance to copy.
        # \return \a self
        # 
        def assign(entry: Entry) -> Entry: pass

        ##
        # \brief Returns the three-letter code (TLC) of the residue.
        # 
        # \return A reference to the three-letter residue code.
        # 
        def getCode() -> str: pass

        ##
        # \brief Returns the TLC of the residue this entry replaces.
        # 
        # \return A reference to the replaced-residue code (or an empty string if this entry does not replace any other residue).
        # 
        def getReplacedCode() -> str: pass

        ##
        # \brief Returns the TLC of the residue that replaces this one.
        # 
        # \return A reference to the replacing-residue code (or an empty string if this entry has not been replaced).
        # 
        def getReplacedByCode() -> str: pass

        ##
        # \brief Returns the TLC of the parent residue.
        # 
        # \return A reference to the parent-residue code (or an empty string if there is no parent). 
        # 
        # \since 1.2
        # 
        def getParentCode() -> str: pass

        ##
        # \brief Returns the one-letter residue code.
        # 
        # \return A reference to the one-letter residue code (or an empty string if not defined). 
        # 
        # \since 1.2
        # 
        def getOneLetterCode() -> str: pass

        ##
        # \brief Returns the residue type (see Biomol.ResidueType).
        # 
        # \return The residue type identifier.
        # 
        def getType() -> int: pass

        ##
        # \brief Returns the full residue name.
        # 
        # \return A reference to the residue name.
        # 
        def getName() -> str: pass

        ##
        # \brief Tells whether the residue type described by this entry is obsolete.
        # 
        # \return <tt>True</tt> if the residue type is obsolete, and <tt>False</tt> otherwise.
        # 
        def isObsolete() -> bool: pass

        ##
        # \brief Retrieves the residue structure via the configured structure-retrieval function.
        # 
        # \return A shared reference to the residue structure (or an empty reference if no structure could be retrieved).
        # 
        def getStructure() -> Chem.MolecularGraph: pass

        objectID = property(getObjectID)

        code = property(getCode)

        replacedCode = property(getReplacedCode)

        replacedByCode = property(getReplacedByCode)

        parentCode = property(getParentCode)

        oneLetterCode = property(getOneLetterCode)

        obsolete = property(isObsolete)

        name = property(getName)

        type = property(getType)

        structure = property(getStructure)

    ##
    # \brief Initializes the \c %ResidueDictionary instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %ResidueDictionary instance \a dict.
    # \param dict The \c %ResidueDictionary instance to copy.
    # 
    def __init__(dict: ResidueDictionary) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ResidueDictionary instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ResidueDictionary instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Adds (or overwrites) the dictionary entry <em>entry</em> by moving its data.
    # 
    # \param entry The entry to add.
    # 
    # \since 1.2
    # 
    def addEntry(entry: Entry) -> None: pass

    ##
    # \brief Tells whether the dictionary contains an entry for the residue with three-letter code <em>code</em>.
    # 
    # \param code The residue three-letter code.
    # 
    # \return <tt>True</tt> if a matching entry exists, and <tt>False</tt> otherwise.
    # 
    def containsEntry(code: str) -> bool: pass

    ##
    # \brief Removes the dictionary entry for the residue with three-letter code <em>code</em>.
    # 
    # \param code The residue three-letter code.
    # 
    def removeEntry(code: str) -> None: pass

    ##
    # \brief Returns the dictionary entry for the residue with three-letter code <em>code</em>.
    # 
    # \param code The residue three-letter code.
    # 
    # \return A reference to the matching entry (or to an empty default-constructed entry if no matching entry exists).
    # 
    def getEntry(code: str) -> Entry: pass

    ##
    # \brief Removes all entries from the dictionary.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of entries in the dictionary.
    # 
    # \return The entry count.
    # 
    def getNumEntries() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def getEntries() -> list: pass

    ##
    # \brief Loads the built-in default residue dictionary entries.
    # 
    def loadDefaults() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ResidueDictionary instance \a dict.
    # \param dict The \c %ResidueDictionary instance to copy.
    # \return \a self
    # 
    def assign(dict: ResidueDictionary) -> ResidueDictionary: pass

    ##
    # \brief Replaces the process-wide default dictionary by <em>dict</em>.
    # 
    # \param dict The new default dictionary (a <tt>nullptr</tt> resets to the built-in default).
    # 
    @staticmethod
    def set(dict: ResidueDictionary) -> None: pass

    ##
    # \brief Returns the process-wide default dictionary (lazily initialized on first call).
    # 
    # \return A reference to the default-dictionary shared reference.
    # 
    @staticmethod
    def get(: ) -> ResidueDictionary: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def getReplacedCode(code: str) -> str: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def getReplacedByCode(code: str) -> str: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def getParentCode(code: str) -> str: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def getOneLetterCode(code: str) -> str: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def isObsolete(code: str) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def getName(code: str) -> str: pass

    ##
    # \brief Tells whether the residue with three-letter code <em>code</em> is a standard biopolymer residue (amino acid or nucleotide).
    # 
    # \param code The residue three-letter code.
    # 
    # \return <tt>True</tt> if the residue is a standard biopolymer residue, and <tt>False</tt> otherwise.
    # 
    @staticmethod
    def isStdResidue(code: str) -> bool: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def getType(code: str) -> int: pass

    ##
    # \brief 
    # \param arg1 
    # \param code 
    # \return 
    #
    def getStructure(code: str) -> Chem.MolecularGraph: pass

    objectID = property(getObjectID)

    numEntries = property(getNumEntries)

    entries = property(getEntries)
