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
class DataFormat(Boost.Python.instance):

    ##
    # \brief 
    #
    class FileExtensionSequence(Boost.Python.instance):

        ##
        # \brief 
        # \param self The \e %FileExtensionSequence instance this method is called upon.
        # \return 
        #
        def __len__(self: FileExtensionSequence) -> int: pass

        ##
        # \brief 
        # \param self The \e %FileExtensionSequence instance this method is called upon.
        # \param idx 
        # \return 
        #
        def __getitem__(self: FileExtensionSequence, idx: int) -> str: pass

        ##
        # \brief 
        # \param self The \e %FileExtensionSequence instance this method is called upon.
        # \param idx 
        #
        def __delitem__(self: FileExtensionSequence, idx: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %FileExtensionSequence instance this method is called upon.
        # \param idx 
        # \param file_ext 
        #
        def __setitem__(self: FileExtensionSequence, idx: int, file_ext: str) -> None: pass

        ##
        # \brief Returns the result of the membership test operation <tt>file_ext in self</tt>.
        # \param self The \e %FileExtensionSequence instance this method is called upon.
        # \param file_ext The value to test for membership.
        # \return The result of the membership test operation.
        #
        def __contains__(self: FileExtensionSequence, file_ext: str) -> bool: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    # \param self The \e %DataFormat instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    # \param self The \e %DataFormat instance to initialize.
    # \param fmt 
    #
    def __init__(self: object, fmt: DataFormat) -> None: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    # \param self The \e %DataFormat instance to initialize.
    # \param name 
    # \param descr 
    # \param mime_type 
    # \param multi_rec 
    #
    def __init__(self: object, name: str, descr: str, mime_type: str, multi_rec: bool) -> None: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    # \param self The \e %DataFormat instance to initialize.
    # \param name 
    # \param descr 
    # \param mime_type 
    # \param file_exts 
    # \param multi_rec 
    #
    def __init__(self: object, name: str, descr: str, mime_type: str, file_exts: object, multi_rec: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \return 
    #
    def getNumFileExtensions(self: DataFormat) -> int: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getFileExtension(self: DataFormat, idx: int) -> str: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param file_ext 
    # \return 
    #
    def addFileExtension(self: DataFormat, file_ext: str) -> DataFormat: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param idx 
    # \param file_ext 
    #
    def setFileExtension(self: DataFormat, idx: int, file_ext: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    #
    def clearFileExtensions(self: DataFormat) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param idx 
    #
    def removeFileExtension(self: DataFormat, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param name 
    # \return 
    #
    def matchesName(self: DataFormat, name: str) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param mime_type 
    # \return 
    #
    def matchesMimeType(self: DataFormat, mime_type: str) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param file_ext 
    # \return 
    #
    def matchesFileExtension(self: DataFormat, file_ext: str) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \return 
    #
    def getDescription(self: DataFormat) -> str: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param descr 
    #
    def setDescription(self: DataFormat, descr: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \return 
    #
    def getName(self: DataFormat) -> str: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param name 
    #
    def setName(self: DataFormat, name: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \return 
    #
    def getMimeType(self: DataFormat) -> str: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param mime_type 
    #
    def setMimeType(self: DataFormat, mime_type: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \return 
    #
    def isMultiRecordFormat(self: DataFormat) -> bool: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \param multi_rec 
    #
    def setMultiRecordFormat(self: DataFormat, multi_rec: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %DataFormat instance this method is called upon.
    # \return 
    #
    def getFileExtensions(self: DataFormat) -> FileExtensionSequence: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DataFormat instance \a fmt.
    # \param self The \e %DataFormat instance this method is called upon.
    # \param fmt The \e %DataFormat instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DataFormat, fmt: DataFormat) -> DataFormat: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %DataFormat instance this method is called upon.
    #
    # Different Python \e %DataFormat instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DataFormat instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: DataFormat) -> int: pass

    ##
    # \brief Returns a string representation of the \e %DataFormat instance.
    # \param self The \e %DataFormat instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: DataFormat) -> str: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != fmt</tt>.
    # \param self The \e %DataFormat instance this method is called upon.
    # \param fmt The \e %DataFormat instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: DataFormat, fmt: DataFormat) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == fmt</tt>.
    # \param self The \e %DataFormat instance this method is called upon.
    # \param fmt The \e %DataFormat instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: DataFormat, fmt: DataFormat) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    numFileExtensions = property(getNumFileExtensions)

    ##
    # \brief 
    #
    description = property(getDescription, setDescription)

    ##
    # \brief 
    #
    name = property(getName, setName)

    ##
    # \brief 
    #
    mimeType = property(getMimeType, setMimeType)

    ##
    # \brief FIXME!
    #
    multiRecordFormat = property(getMultiRecordFormat, setMultiRecordFormat)

    ##
    # \brief 
    #
    fileExtensions = property(getFileExtensions)
