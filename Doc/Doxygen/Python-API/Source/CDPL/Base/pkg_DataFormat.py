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
class DataFormat(Boost.Python.instance):

    ##
    # \brief 
    #
    class FileExtensionSequence(Boost.Python.instance):

        ##
        # \brief 
        # \return 
        #
        def __len__() -> int: pass

        ##
        # \brief 
        # \param idx 
        # \return 
        #
        def __getitem__(idx: int) -> str: pass

        ##
        # \brief 
        # \param idx 
        #
        def __delitem__(idx: int) -> None: pass

        ##
        # \brief 
        # \param idx 
        # \param file_ext 
        #
        def __setitem__(idx: int, file_ext: str) -> None: pass

        ##
        # \brief Returns the result of the membership test operation <tt>file_ext in self</tt>.
        # \param file_ext The value to test for membership.
        # \return The result of the membership test operation.
        #
        def __contains__(file_ext: str) -> bool: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    # \param fmt 
    #
    def __init__(fmt: DataFormat) -> None: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    # \param name 
    # \param descr 
    # \param mime_type 
    # \param multi_rec 
    #
    def __init__(name: str, descr: str, mime_type: str, multi_rec: bool) -> None: pass

    ##
    # \brief Initializes the \e %DataFormat instance.
    # \param name 
    # \param descr 
    # \param mime_type 
    # \param file_exts 
    # \param multi_rec 
    #
    def __init__(name: str, descr: str, mime_type: str, file_exts: object, multi_rec: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumFileExtensions() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def getFileExtension(idx: int) -> str: pass

    ##
    # \brief 
    # \param file_ext 
    # \return 
    #
    def addFileExtension(file_ext: str) -> DataFormat: pass

    ##
    # \brief 
    # \param idx 
    # \param file_ext 
    #
    def setFileExtension(idx: int, file_ext: str) -> None: pass

    ##
    # \brief 
    #
    def clearFileExtensions() -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeFileExtension(idx: int) -> None: pass

    ##
    # \brief 
    # \param name 
    # \return 
    #
    def matchesName(name: str) -> bool: pass

    ##
    # \brief 
    # \param mime_type 
    # \return 
    #
    def matchesMimeType(mime_type: str) -> bool: pass

    ##
    # \brief 
    # \param file_ext 
    # \return 
    #
    def matchesFileExtension(file_ext: str) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getDescription() -> str: pass

    ##
    # \brief 
    # \param descr 
    #
    def setDescription(descr: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getName() -> str: pass

    ##
    # \brief 
    # \param name 
    #
    def setName(name: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMimeType() -> str: pass

    ##
    # \brief 
    # \param mime_type 
    #
    def setMimeType(mime_type: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isMultiRecordFormat() -> bool: pass

    ##
    # \brief 
    # \param multi_rec 
    #
    def setMultiRecordFormat(multi_rec: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFileExtensions() -> FileExtensionSequence: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DataFormat instance \a fmt.
    # \param fmt The \e %DataFormat instance to copy.
    # \return \a self
    #
    def assign(fmt: DataFormat) -> DataFormat: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %DataFormat instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %DataFormat instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Returns a string representation of the \e %DataFormat instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != fmt</tt>.
    # \param fmt The \e %DataFormat instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(fmt: DataFormat) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == fmt</tt>.
    # \param fmt The \e %DataFormat instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(fmt: DataFormat) -> bool: pass

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
