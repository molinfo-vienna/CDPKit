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
# \brief Data structure for the storage of data records found in PDB formatted data [\ref PDB].
# 
class PDBData(Boost.Python.instance):

    ##
    # \brief Identifies the type of PDB data record.
    # 
    class RecordType(Boost.Python.enum):

        ##
        # \brief PDB <tt>HEADER</tt> record (structure classification, deposition date, PDB ID).
        # 
        HEADER = 0

        ##
        # \brief PDB <tt>OBSLTE</tt> record (PDB IDs that have replaced this entry).
        # 
        OBSLTE = 1

        ##
        # \brief PDB <tt>TITLE</tt> record (title of the entry).
        # 
        TITLE = 2

        ##
        # \brief PDB <tt>SPLIT</tt> record (list of entries that together form the complete structure).
        # 
        SPLIT = 3

        ##
        # \brief PDB <tt>CAVEAT</tt> record (caveats about the structure).
        # 
        CAVEAT = 4

        ##
        # \brief PDB <tt>COMPND</tt> record (description of macromolecular contents).
        # 
        COMPND = 5

        ##
        # \brief PDB <tt>SOURCE</tt> record (source organism information).
        # 
        SOURCE = 6

        ##
        # \brief PDB <tt>KEYWDS</tt> record (keywords describing the entry).
        # 
        KEYWDS = 7

        ##
        # \brief PDB <tt>EXPDTA</tt> record (experimental technique).
        # 
        EXPDTA = 8

        ##
        # \brief PDB <tt>AUTHOR</tt> record (authors of the entry).
        # 
        AUTHOR = 9

        ##
        # \brief PDB <tt>REVDAT</tt> record (revision history of the entry).
        # 
        REVDAT = 10

        ##
        # \brief PDB <tt>SPRSDE</tt> record (PDB IDs that this entry supersedes).
        # 
        SPRSDE = 11

        ##
        # \brief PDB <tt>JRNL</tt> record (literature citation associated with the entry).
        # 
        JRNL = 12

        ##
        # \brief PDB <tt>REMARK</tt> record (free-text annotations).
        # 
        REMARK = 13

        ##
        # \brief PDB <tt>DBREF</tt> record (cross-references to external sequence databases).
        # 
        DBREF = 14

        ##
        # \brief PDB <tt>DBREF1</tt> record (first part of a two-line database cross-reference).
        # 
        DBREF1 = 15

        ##
        # \brief PDB <tt>DBREF2</tt> record (second part of a two-line database cross-reference).
        # 
        DBREF2 = 16

        ##
        # \brief PDB <tt>SEQADV</tt> record (sequence differences relative to the reference database).
        # 
        SEQADV = 17

        ##
        # \brief PDB <tt>SEQRES</tt> record (residue sequence of biopolymer chains).
        # 
        SEQRES = 18

        ##
        # \brief PDB <tt>MODRES</tt> record (modified residues).
        # 
        MODRES = 19

        ##
        # \brief PDB <tt>HET</tt> record (non-standard residue identification).
        # 
        HET = 20

        ##
        # \brief PDB <tt>FORMUL</tt> record (chemical formula of non-standard residues).
        # 
        FORMUL = 21

        ##
        # \brief PDB <tt>HETNAM</tt> record (chemical name of non-standard residues).
        # 
        HETNAM = 22

        ##
        # \brief PDB <tt>HETSYN</tt> record (synonyms for non-standard residues).
        # 
        HETSYN = 23

        ##
        # \brief PDB <tt>HELIX</tt> record (helix secondary-structure annotations).
        # 
        HELIX = 24

        ##
        # \brief PDB <tt>SHEET</tt> record (sheet secondary-structure annotations).
        # 
        SHEET = 25

        ##
        # \brief PDB <tt>TURN</tt> record (turn secondary-structure annotations).
        # 
        TURN = 26

        ##
        # \brief PDB <tt>SSBOND</tt> record (disulfide bond annotations).
        # 
        SSBOND = 27

        ##
        # \brief PDB <tt>LINK</tt> record (covalent links between non-standard residues).
        # 
        LINK = 28

        ##
        # \brief PDB <tt>CISPEP</tt> record (cis peptide bond annotations).
        # 
        CISPEP = 29

        ##
        # \brief PDB <tt>SITE</tt> record (groups of residues describing an active or binding site).
        # 
        SITE = 30

        ##
        # \brief PDB <tt>CRYST1</tt> record (unit cell parameters and space group).
        # 
        CRYST1 = 31

        ##
        # \brief PDB <tt>MTRIX1</tt> record (first row of a non-crystallographic-symmetry transformation matrix).
        # 
        MTRIX1 = 32

        ##
        # \brief PDB <tt>MTRIX2</tt> record (second row of a non-crystallographic-symmetry transformation matrix).
        # 
        MTRIX2 = 33

        ##
        # \brief PDB <tt>MTRIX3</tt> record (third row of a non-crystallographic-symmetry transformation matrix).
        # 
        MTRIX3 = 34

        ##
        # \brief PDB <tt>ORIGX1</tt> record (first row of the orthogonal-to-submitted-coordinates transformation).
        # 
        ORIGX1 = 35

        ##
        # \brief PDB <tt>ORIGX2</tt> record (second row of the orthogonal-to-submitted-coordinates transformation).
        # 
        ORIGX2 = 36

        ##
        # \brief PDB <tt>ORIGX3</tt> record (third row of the orthogonal-to-submitted-coordinates transformation).
        # 
        ORIGX3 = 37

        ##
        # \brief PDB <tt>SCALE1</tt> record (first row of the orthogonal-to-fractional-coordinates transformation).
        # 
        SCALE1 = 38

        ##
        # \brief PDB <tt>SCALE2</tt> record (second row of the orthogonal-to-fractional-coordinates transformation).
        # 
        SCALE2 = 39

        ##
        # \brief PDB <tt>SCALE3</tt> record (third row of the orthogonal-to-fractional-coordinates transformation).
        # 
        SCALE3 = 40

        ##
        # \brief Derived: the 4-character PDB identifier extracted from the <tt>HEADER</tt> record.
        # 
        STRUCTURE_ID = 41

        ##
        # \brief Derived: the deposition date extracted from the <tt>HEADER</tt> record.
        # 
        DEPOSITION_DATE = 42

        ##
        # \brief Derived: the experimental resolution extracted from <tt>REMARK</tt> records.
        # 
        RESOLUTION = 43

    ##
    # \brief Constructs an empty <tt>PDBData</tt> instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %PDBData instance \a data.
    # \param data The \c %PDBData instance to copy.
    # 
    def __init__(data: PDBData) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %PDBData instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %PDBData instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the number of stored records.
    # 
    # \return The number of records.
    # 
    def getNumRecords() -> int: pass

    ##
    # \brief Tells whether no records are stored.
    # 
    # \return <tt>True</tt> if no records are stored, and <tt>False</tt> otherwise.
    # 
    def isEmpty() -> bool: pass

    ##
    # \brief Removes all stored records.
    # 
    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %PDBData instance \a data.
    # \param data The \c %PDBData instance to copy.
    # \return \a self
    # 
    def assign(data: PDBData) -> PDBData: pass

    ##
    # \brief Tells whether a record of the given type is stored.
    # 
    # \param type The queried record type.
    # 
    # \return <tt>True</tt> if a record of the given type is stored, and <tt>False</tt> otherwise.
    # 
    def containsRecord(type: RecordType) -> bool: pass

    ##
    # \brief Returns the data string associated with the given record type.
    # 
    # \param type The record type whose data is requested.
    # 
    # \return A reference to the data string. 
    # 
    # \throw Base.ItemNotFound if no record of the given type is stored.
    # 
    def getData(type: RecordType) -> str: pass

    ##
    # \brief Removes the record of the given type.
    # 
    # \param type The type of the record to remove.
    # 
    # \return <tt>True</tt> if the record was removed, and <tt>False</tt> if no matching record existed.
    # 
    def removeRecord(type: RecordType) -> bool: pass

    ##
    # \brief Stores a record built from <em>type</em> and <em>data</em>. Any pre-existing record of the same type is replaced.
    # 
    # \param type The record type.
    # \param data The record data string.
    # 
    # \return An iterator referencing the stored record.
    # 
    def setRecord(type: RecordType, data: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRecordTypes() -> object: pass

    ##
    # \brief 
    # \return 
    #
    def getRecordData() -> object: pass

    ##
    # \brief 
    # \return 
    #
    def getRecords() -> object: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    def __getitem__(type: RecordType) -> str: pass

    ##
    # \brief 
    # \param type 
    # \param data 
    #
    def __setitem__(type: RecordType, data: str) -> None: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    def __delitem__(type: RecordType) -> bool: pass

    ##
    # \brief Returns the result of the membership test operation <tt>type in self</tt>.
    # \param type The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(type: RecordType) -> bool: pass

    objectID = property(getObjectID)

    numRecords = property(getNumRecords)

    recordTypes = property(getRecordTypes)

    recordData = property(getRecordData)

    records = property(getRecords)
