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
class PDBData(Boost.Python.instance):

    ##
    # \brief 
    #
    class RecordType(Boost.Python.enum):

        ##
        # \brief HEADER.
        #
        HEADER = 0

        ##
        # \brief OBSLTE.
        #
        OBSLTE = 1

        ##
        # \brief TITLE.
        #
        TITLE = 2

        ##
        # \brief SPLIT.
        #
        SPLIT = 3

        ##
        # \brief CAVEAT.
        #
        CAVEAT = 4

        ##
        # \brief COMPND.
        #
        COMPND = 5

        ##
        # \brief SOURCE.
        #
        SOURCE = 6

        ##
        # \brief KEYWDS.
        #
        KEYWDS = 7

        ##
        # \brief EXPDTA.
        #
        EXPDTA = 8

        ##
        # \brief AUTHOR.
        #
        AUTHOR = 9

        ##
        # \brief REVDAT.
        #
        REVDAT = 10

        ##
        # \brief SPRSDE.
        #
        SPRSDE = 11

        ##
        # \brief JRNL.
        #
        JRNL = 12

        ##
        # \brief REMARK.
        #
        REMARK = 13

        ##
        # \brief DBREF.
        #
        DBREF = 14

        ##
        # \brief DBREF1.
        #
        DBREF1 = 15

        ##
        # \brief DBREF2.
        #
        DBREF2 = 16

        ##
        # \brief SEQADV.
        #
        SEQADV = 17

        ##
        # \brief SEQRES.
        #
        SEQRES = 18

        ##
        # \brief MODRES.
        #
        MODRES = 19

        ##
        # \brief HET.
        #
        HET = 20

        ##
        # \brief FORMUL.
        #
        FORMUL = 21

        ##
        # \brief HETNAM.
        #
        HETNAM = 22

        ##
        # \brief HETSYN.
        #
        HETSYN = 23

        ##
        # \brief HELIX.
        #
        HELIX = 24

        ##
        # \brief SHEET.
        #
        SHEET = 25

        ##
        # \brief TURN.
        #
        TURN = 26

        ##
        # \brief SSBOND.
        #
        SSBOND = 27

        ##
        # \brief LINK.
        #
        LINK = 28

        ##
        # \brief CISPEP.
        #
        CISPEP = 29

        ##
        # \brief SITE.
        #
        SITE = 30

        ##
        # \brief CRYST1.
        #
        CRYST1 = 31

        ##
        # \brief MTRIX1.
        #
        MTRIX1 = 32

        ##
        # \brief MTRIX2.
        #
        MTRIX2 = 33

        ##
        # \brief MTRIX3.
        #
        MTRIX3 = 34

        ##
        # \brief ORIGX1.
        #
        ORIGX1 = 35

        ##
        # \brief ORIGX2.
        #
        ORIGX2 = 36

        ##
        # \brief ORIGX3.
        #
        ORIGX3 = 37

        ##
        # \brief SCALE1.
        #
        SCALE1 = 38

        ##
        # \brief SCALE2.
        #
        SCALE2 = 39

        ##
        # \brief SCALE3.
        #
        SCALE3 = 40

        ##
        # \brief STRUCTURE_ID.
        #
        STRUCTURE_ID = 41

        ##
        # \brief DEPOSITION_DATE.
        #
        DEPOSITION_DATE = 42

        ##
        # \brief RESOLUTION.
        #
        RESOLUTION = 43

    ##
    # \brief Initializes the \e %PDBData instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %PDBData instance.
    # \param other 
    #
    def __init__(other: PDBData) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %PDBData instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %PDBData instances \e a and \e b reference different C++ objects. 
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
    def getNumRecords() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %PDBData instance \a data.
    # \param data The \e %PDBData instance to copy.
    # \return \a self
    #
    def assign(data: PDBData) -> PDBData: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    def containsRecord(type: RecordType) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    def getData(type: RecordType) -> str: pass

    ##
    # \brief 
    # \param type 
    # \return 
    #
    def removeRecord(type: RecordType) -> bool: pass

    ##
    # \brief 
    # \param type 
    # \param data 
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

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numRecords = property(getNumRecords)

    ##
    # \brief 
    #
    recordTypes = property(getRecordTypes)

    ##
    # \brief 
    #
    recordData = property(getRecordData)

    ##
    # \brief 
    #
    records = property(getRecords)
