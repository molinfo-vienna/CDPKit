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
# \brief Data structure for the storage of preprocessed <em>Brookhaven Protein Data Bank (PDB)</em> data.
# 
# \see [\ref PDB]
# 
class PDBData(Boost.Python.instance):

    ##
    # \brief Specifies the type of a stored <em>PDB</em> data record.
    # 
    class RecordType(Boost.Python.enum):

        ##
        # \brief <tt>HEADER</tt> record (structure classification, deposition date, <em>PDB</em> ID).
        # 
        HEADER = 0

        ##
        # \brief <tt>OBSLTE</tt> record (PDB IDs that have replaced this entry).
        # 
        OBSLTE = 1

        ##
        # \brief <tt>TITLE</tt> record (title of the entry).
        # 
        TITLE = 2

        ##
        # \brief <tt>SPLIT</tt> record (list of entries that together form the complete structure).
        # 
        SPLIT = 3

        ##
        # \brief <tt>CAVEAT</tt> record (warns of errors and unresolved issues of the entry).
        # 
        CAVEAT = 4

        ##
        # \brief <tt>COMPND</tt> record (description of the macromolecular contents).
        # 
        COMPND = 5

        ##
        # \brief <tt>SOURCE</tt> record (specifies the biological and/or chemical source of each biological molecule).
        # 
        SOURCE = 6

        ##
        # \brief <tt>KEYWDS</tt> record (a set of terms relevant to the entry).
        # 
        KEYWDS = 7

        ##
        # \brief <tt>EXPDTA</tt> record (information about the experiment).
        # 
        EXPDTA = 8

        ##
        # \brief <tt>AUTHOR</tt> record (contains the names of the people responsible for the contents of the entry).
        # 
        AUTHOR = 9

        ##
        # \brief <tt>REVDAT</tt> record (revision history of the entry).
        # 
        REVDAT = 10

        ##
        # \brief <tt>SPRSDE</tt> record (PDB IDs that this entry supersedes).
        # 
        SPRSDE = 11

        ##
        # \brief <tt>JRNL</tt> record (literature citation associated with the entry).
        # 
        JRNL = 12

        ##
        # \brief <tt>REMARK</tt> record (experimental details, annotations, comments, and information not included in other records).
        # 
        REMARK = 13

        ##
        # \brief <tt>DBREF</tt> record (cross-reference links between <em>PDB</em> sequences and a corresponding database sequence).
        # 
        DBREF = 14

        ##
        # \brief <tt>DBREF1</tt> record (first part of a two-line database cross-reference).
        # 
        DBREF1 = 15

        ##
        # \brief <tt>DBREF2</tt> record (second part of a two-line database cross-reference).
        # 
        DBREF2 = 16

        ##
        # \brief <tt>SEQADV</tt> record (differences between sequence information in the <tt>SEQRES</tt> record and the sequence database entry given in <tt>DBREF</tt>).
        # 
        SEQADV = 17

        ##
        # \brief <tt>SEQRES</tt> record (residue sequence of biopolymer chains).
        # 
        SEQRES = 18

        ##
        # \brief <tt>MODRES</tt> record (descriptions of modifications to protein and nucleic acid residues).
        # 
        MODRES = 19

        ##
        # \brief <tt>HET</tt> record (describes non-standard residues for which coordinates are supplied).
        # 
        HET = 20

        ##
        # \brief <tt>FORMUL</tt> record (chemical formula of non-standard residues).
        # 
        FORMUL = 21

        ##
        # \brief <tt>HETNAM</tt> record (chemical names of non-standard residues).
        # 
        HETNAM = 22

        ##
        # \brief <tt>HETSYN</tt> record (synonyms for non-standard residues).
        # 
        HETSYN = 23

        ##
        # \brief <tt>HELIX</tt> record (helix secondary structure annotations).
        # 
        HELIX = 24

        ##
        # \brief <tt>SHEET</tt> record (sheet secondary structure annotations).
        # 
        SHEET = 25

        ##
        # \brief <tt>TURN</tt> record (locations of short loop turns that connect standard secondary structure segments).
        # 
        TURN = 26

        ##
        # \brief <tt>SSBOND</tt> record (identifies disulfide bonds in protein and polypeptide structures).
        # 
        SSBOND = 27

        ##
        # \brief <tt>LINK</tt> record (bonds between residues that are not implied by the primary structure).
        # 
        LINK = 28

        ##
        # \brief <tt>CISPEP</tt> record (specifies prolines and other peptides found to be in the cis conformation).
        # 
        CISPEP = 29

        ##
        # \brief <tt>SITE</tt> record (specifies residues of an active or binding site).
        # 
        SITE = 30

        ##
        # \brief <tt>CRYST1</tt> record (unit cell parameters, space group, and Z value).
        # 
        CRYST1 = 31

        ##
        # \brief <tt>MTRIX1</tt> record (first row of a non-crystallographic symmetry transformation matrix).
        # 
        MTRIX1 = 32

        ##
        # \brief <tt>MTRIX2</tt> record (second row of a non-crystallographic symmetry transformation matrix).
        # 
        MTRIX2 = 33

        ##
        # \brief <tt>MTRIX3</tt> record (third row of a non-crystallographic symmetry transformation matrix).
        # 
        MTRIX3 = 34

        ##
        # \brief <tt>ORIGX1</tt> record (first row of the orthogonal to submitted coordinates transformation).
        # 
        ORIGX1 = 35

        ##
        # \brief <tt>ORIGX2</tt> record (second row of the orthogonal to submitted coordinates transformation).
        # 
        ORIGX2 = 36

        ##
        # \brief <tt>ORIGX3</tt> record (third row of the orthogonal to submitted coordinates transformation).
        # 
        ORIGX3 = 37

        ##
        # \brief <tt>SCALE1</tt> record (first row of the orthogonal to fractional coordinates transformation).
        # 
        SCALE1 = 38

        ##
        # \brief <tt>SCALE2</tt> record (second row of the orthogonal to fractional coordinates transformation).
        # 
        SCALE2 = 39

        ##
        # \brief <tt>SCALE3</tt> record (third row of the orthogonal to fractional coordinates transformation).
        # 
        SCALE3 = 40

        ##
        # \brief The 4 character <em>PDB</em> identifier extracted from the <tt>HEADER</tt> record.
        # 
        STRUCTURE_ID = 41

        ##
        # \brief The deposition date extracted from the <tt>HEADER</tt> record.
        # 
        DEPOSITION_DATE = 42

        ##
        # \brief The experimental resolution extracted from <tt>REMARK</tt> records.
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
    # \return <tt>True</tt> if a record of the given type has been found, and <tt>False</tt> otherwise.
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
    # \brief Stores a record built from <em>type</em> and <em>data</em> (any pre-existing record of the same type is replaced).
    # 
    # \param type The record type.
    # \param data The record data string.
    # 
    # \return An iterator pointing to the stored record.
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
