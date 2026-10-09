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
# \brief Output stream that transparently writes bzip2-compressed data.
# 
class BZip2OStream(Base.OStream):

    ##
    # \brief Contructs the \c BZip2OStream instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs the \c BZip2OStream instance.
    # \param os 
    # 
    def __init__(os: Base.OStream) -> None: pass

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

    def open(os: Base.OStream) -> None: pass

    ##
    # \brief FIXME!
    #
    closed = property(getClosed)

    ##
    # \brief FIXME!
    #
    softspace = property(getSoftspace, setSoftspace)

    ##
    # \brief FIXME!
    #
    mode = property(getMode)

    ##
    # \brief FIXME!
    #
    modeFlags = property(getModeFlags)
