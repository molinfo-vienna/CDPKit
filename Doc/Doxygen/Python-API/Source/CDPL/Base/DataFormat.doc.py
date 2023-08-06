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
# \brief Provides meta-information about a particular data storage format.
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
    # \brief Default constructor.
    # 
    # All string attributes are initialized to an empty string, and the multi record format flag is set to <tt>False</tt>.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DataFormat instance with a copy of the state of the \e %DataFormat instance \a fmt.
    # \param fmt The \e %DataFormat instance to copy.
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
    # \brief Returns the number of registered file extensions.
    # 
    # \return The number of registered file extensions.
    # 
    def getNumFileExtensions() -> int: pass

    ##
    # \brief Returns the file extension list entry at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the requested file extension list entry.
    # 
    # \return The file extension list entry at index <em>idx</em>. 
    # 
    # \throw Base.IndexError if <em>idx</em> is out of bounds.
    # 
    def getFileExtension(idx: int) -> str: pass

    ##
    # \brief Adds <em>file_ext</em> to the current list of file extensions.
    # 
    # \param file_ext The file extension to add.
    # 
    def addFileExtension(file_ext: str) -> DataFormat: pass

    ##
    # \brief Sets the file extension list entry at index <em>idx</em> to <em>file_ext</em>.
    # 
    # \param idx The zero-based index of the file extension list entry to set.
    # \param file_ext The new file extension list entry.
    # 
    # \throw Base.IndexError if <em>idx</em> is out of bounds.
    # 
    def setFileExtension(idx: int, file_ext: str) -> None: pass

    ##
    # \brief Clears the file extension list.
    # 
    def clearFileExtensions() -> None: pass

    ##
    # \brief Removes the file extension list entry at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the file extension list entry to remove.
    # 
    # \throw Base.IndexError if <em>idx</em> is out of bounds.
    # 
    def removeFileExtension(idx: int) -> None: pass

    ##
    # \brief Tells whether the name of this data format matches the name specified by <em>name</em>.
    # 
    # \param name The name to match.
    # 
    # \return <tt>True</tt> if the name of the data format matches the argument, and <tt>False</tt> otherwise. 
    # 
    # \note The name matching is case-insensitive.
    # 
    def matchesName(name: str) -> bool: pass

    ##
    # \brief Tells whether the mime-type of this data format matches the mime-type specified by <em>mime_type</em>.
    # 
    # \param mime_type The mime-type to match.
    # 
    # \return <tt>True</tt> if the mime-type of the data format matches the argument, and <tt>False</tt> otherwise. 
    # 
    # \note The mime-type matching is case-insensitive.
    # 
    def matchesMimeType(mime_type: str) -> bool: pass

    ##
    # \brief Tells whether <em>file_ext</em> is contained in the list of file extensions.
    # 
    # \param file_ext The file extension to search for.
    # 
    # \return <tt>True</tt> if <em>file_ext</em> is contained in the list of file extensions, and <tt>False</tt> otherwise. 
    # 
    # \note The file extension matching is case-insensitive.
    # 
    def matchesFileExtension(file_ext: str) -> bool: pass

    ##
    # \brief Returns the description of the data format.
    # 
    # \return The data format description.
    # 
    def getDescription() -> str: pass

    ##
    # \brief Sets the description of the data format.
    # 
    # \param descr The data format description.
    # 
    def setDescription(descr: str) -> None: pass

    ##
    # \brief Returns the short-name of the data format.
    # 
    # \return The short-name of the data format.
    # 
    def getName() -> str: pass

    ##
    # \brief Sets the short-name of the data format.
    # 
    # \param name The short-name of the data format.
    # 
    def setName(name: str) -> None: pass

    ##
    # \brief Returns the mime-type of the data format.
    # 
    # \return The mime-type of the data format.
    # 
    def getMimeType() -> str: pass

    ##
    # \brief Sets the mime-type of the data format.
    # 
    # \param mime_type The mime-type of the data format.
    # 
    def setMimeType(mime_type: str) -> None: pass

    ##
    # \brief Tells whether or not the data format supports the storage of multiple data records.
    # 
    # \return <tt>True</tt> if the data format supports the storage of multiple data records, and <tt>False</tt> otherwise.
    # 
    def isMultiRecordFormat() -> bool: pass

    ##
    # \brief Specifies whether or not the data format supports the storage of multiple data records.
    # 
    # \param multi_rec <tt>True</tt> if the data format supports the storage of multiple data records, and <tt>False</tt> otherwise.
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
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == fmt)</tt>.
    # 
    # \param fmt The other <tt>DataFormat</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the names and/or mime-types compare non-equal (case-insensitive!), and <tt>False</tt> otherwise. 
    # 
    # \see __eq__()
    # 
    def __ne__(fmt: DataFormat) -> bool: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param fmt The other <tt>DataFormat</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the names and mime-types compare equal (case-insensitive!), and <tt>False</tt> otherwise.
    # 
    def __eq__(fmt: DataFormat) -> bool: pass

    objectID = property(getObjectID)

    numFileExtensions = property(getNumFileExtensions)

    description = property(getDescription, setDescription)

    name = property(getName, setName)

    mimeType = property(getMimeType, setMimeType)

    ##
    # \brief FIXME!
    #
    multiRecordFormat = property(getMultiRecordFormat, setMultiRecordFormat)

    fileExtensions = property(getFileExtensions)
