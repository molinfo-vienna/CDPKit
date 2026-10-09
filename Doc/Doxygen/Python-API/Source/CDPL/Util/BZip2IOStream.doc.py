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
# \brief Bidirectional stream that transparently (de)compresses bzip2 data.
# 
class BZip2IOStream(Base.IOStream):

    ##
    # \brief Contructs the \c BZip2IOStream instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs the \c BZip2IOStream instance.
    # \param ios 
    # 
    def __init__(ios: Base.IOStream) -> None: pass

    ##
    # \brief Reads one entire line.
    # 
    # A trailing newline character is kept in the string (but may be absent when a file ends with an incomplete line).
    # If the \a size argument is present and non-negative, it is a maximum byte count (including the trailing newline)
    # and an incomplete line may be returned. When \a size is not \e 0, an empty string is returned only if EOF is
    # encountered immediately.
    # 
    # \param size If present and non-negative, specifies the maximum number of bytes to read (including the trailing newline).
    # \return A string holding the read line.
    # 
    def readline(size: int = -1) -> str: pass

    ##
    # \brief Reads lines until EOF and returns a list containing the lines thus read.
    # 
    # If the optional \a size argument is present and non-negative, instead of reading up to EOF, whole lines totalling approximately \a size bytes
    # are read. 
    # 
    # \param size If present and non-negative, specifies the maximum number of bytes to read.
    # \return A list containing the read lines.
    # 
    def readlines(size: int = -1) -> list: pass

    ##
    # \brief Returns the stream instance.
    # \return \a self.
    # 
    def xreadlines() -> BZip2IOStream: pass

    ##
    # \brief Reads at most \a size bytes.
    # 
    # If the size argument is negative or omitted, all data until EOF is reached are read. The bytes are returned as a string object.
    # An empty string is returned when EOF is encountered immediately.
    # 
    # \param size If present and non-negative, specifies the maximum number of bytes to read.
    # \return A string containing the read data.
    # 
    def read(size: int = -1) -> str: pass

    ##
    # \brief Returns the current read position.
    # \return The current read position.
    # 
    def tell() -> int: pass

    ##
    # \brief Returns the current read position.
    # \return The current read position.
    # 
    def tellr() -> int: pass

    ##
    # \brief Sets the current read position.
    # 
    # The whence argument is optional and defaults to \e 0 (absolute positioning).
    # Other supported values are \e 1 to seek relative to the current position and \e 2 for seeking relative to the end of input.
    # 
    # \param offs The offset to use for the seek operation.
    # \param whence Value specifying how to calculate the final read position.
    # 
    def seek(offs: int, whence: int = 0) -> None: pass

    ##
    # \brief Sets the current read position.
    # 
    # The whence argument is optional and defaults to \e 0 (absolute positioning).
    # Other supported values are \e 1 to seek relative to the current position and \e 2 for seeking relative to the end of input.
    # 
    # \param offs The offset to use for the seek operation.
    # \param whence Value specifying how to calculate the final read position.
    # 
    def seekr(offs: int, whence: int = 0) -> None: pass

    ##
    # \brief Reads and returns the next line.
    # 
    # A stream object is its own iterator, for example <tt>iter(s)</tt> returns \a s.
    # When a stream is used as an iterator, typically in a for loop (for example, <tt>for line in s: print line.strip()</tt>),
    # the next() method is called repeatedly. This method returns the next input line, or raises \c StopIteration when EOF is hit
    # when the stream is open for reading (when the stream has been opened for writing only then Base.IOError is raised).
    # 
    # \return A string holding the read line.
    # 
    def next() -> str: pass

    ##
    # \brief Tells whether the stream has been closed.
    # \see close()
    # 
    def isClosed() -> bool: pass

    ##
    # \brief Returns the open mode string that was provided as argument to the constructor.
    # \return The open mode string (e.g. 'r+') that was provided as argument to the constructor.
    # 
    def getOpenModeString() -> str: pass

    ##
    # \brief Returns the open mode flags that were provided as argument to the constructor.
    # \return The open mode flags that were provided as argument to the constructor (see Stream.OpenMode).
    # 
    def getOpenModeFlags() -> OpenMode: pass

    ##
    # \brief Flushes the internal buffer.
    # 
    def flush() -> None: pass

    ##
    # \brief Outputs the specified string.
    # \param string The string to output.
    # \note Due to buffering, the string may not actually show up in the file until the flush() or close() method is called.
    # 
    def write(string: object) -> None: pass

    ##
    # \brief Outputs the specified sequence of strings.
    # \param iterable The string sequence to output (can be any iterable object producing strings, typically a list of strings).
    # 
    def writelines(iterable: object) -> None: pass

    ##
    # \brief Returns the current write position.
    # \return The current write position.
    # 
    def tellw() -> int: pass

    ##
    # \brief Sets the current write position.
    # 
    # The whence argument is optional and defaults to \e 0 (absolute positioning).
    # Other supported values are \e 1 to seek relative to the current position and \e 2 for seeking relative to the end of input.
    # 
    # \param offs The offset to use for the seek operation.
    # \param whence Value specifying how to calculate the final write position.
    # 
    def seekw(offs: int, whence: int = 0) -> None: pass

    ##
    # \brief Returns a boolean that indicates whether a space character needs to be printed before another value when using the print statement.
    # \return \c True if a space character needs to be printed before another value when using the print statement, and \c False otherwise.
    # 
    def getSoftSpace() -> bool: pass

    ##
    # \brief Sets a boolean that indicates whether a space character needs to be printed before another value when using the print statement.
    # \param value \c True if a space character shall be printed before another value when using the print statement, and \c False otherwise.
    # 
    def setSoftSpace(value: bool) -> None: pass

    ##
    # \brief Closes the stream.
    # 
    # A closed stream cannot be read from or written to anymore. %Any operation which requires the stream to be open will raise a
    # Base.ValueError after the stream has been closed. Calling close() more than once is allowed.
    # 
    def close() -> None: pass

    def open(ios: Base.IOStream) -> None: pass

    ##
    # \brief Returns the stream instance.
    # \return \a self.
    # 
    def __iter__() -> BZip2IOStream: pass

    ##
    # \brief FIXME!
    #
    closed = property(getClosed)

    ##
    # \brief FIXME!
    #
    mode = property(getMode)

    ##
    # \brief FIXME!
    #
    modeFlags = property(getModeFlags)

    ##
    # \brief FIXME!
    #
    softspace = property(getSoftspace, setSoftspace)
