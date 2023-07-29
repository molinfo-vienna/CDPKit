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
# \brief An interface for reading data objects of type Grid.DRegularGrid from an arbitrary data source.
# 
# <tt>DRegularGridReaderBase</tt> is the common interface of classes which read objects of type Grid.DRegularGrid from some data source (e.g. a file) that provides the data encoded in a particular storage format.
# 
# From the <tt>DRegularGridReaderBase</tt> interface point of view, the data source is organized as an array of logical data records. Each record is addressed by a zero-based sequential record index and contains the data for exactly <em>one</em> data object. The total number of available data records (which is equal to the maximum record index plus <em>1</em>) can be queried by the method getNumRecords().
# 
# Similar to low-level file I/O, data records may either be read in a sequential or in a random access manner. For sequential access the method read(grid: DRegularGrid) is provided which will read the data record at the 'current' record index (similar to a file reference). The current record index is accessible by the method getRecordIndex() and can be modified using the method setRecordIndex() (similar to a seek operation).
# 
# For reading data records in a random access manner, the method read(std::size_t idx, grid: DRegularGrid) is available. In contrast to the former read() method, this method expects the index of the record to read as the first argument.
# 
# If a read() (or skip()) operation was successful, the current record index is updated to point to the record immediately following the just read (or skipped) data record. If an operation fails, the reader instance is set into an error state that can be queried by the special methods __bool__() and __nonzero__(). Additionally, a <tt>DRegularGridReaderBase</tt> implementation may decide to throw an exception of type Base.IOError to report the error condition.
# 
class DRegularGridReaderBase(Base.DataIOBase):

    ##
    # \brief Initializes the \e %DRegularGridReaderBase instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Reads the data record at the current record index and stores the read data in <em>grid</em>.
    # 
    # If the read operation was successful, the record index is incremented by <em>1</em>.
    # 
    # \param grid The DRegularGrid object storing the read data.
    # \param overwrite Specifies whether any existing data in <em>grid</em> shall be replaced by the newly read data or if the read data should be appended (if supported by the reader and data type).
    # 
    # \return \a self 
    # 
    # \throw Base.IOError if an I/O error occurred.
    # 
    def read(grid: DRegularGrid, overwrite: bool = True) -> DRegularGridReaderBase: pass

    ##
    # \brief Reads the data record at index <em>idx</em> and stores the read data in <em>grid</em>.
    # 
    # If the read operation was successful, the record index is set to <em>idx + 1</em>.
    # 
    # \param idx The zero-based index of the data record to read.
    # \param grid The DRegularGrid object storing the read data.
    # \param overwrite Specifies whether any existing data in <em>grid</em> shall be replaced by the newly read data or if the read data should be appended (if supported by the reader and data type).
    # 
    # \return \a self 
    # 
    # \throw Base.IndexError if <em>idx</em> is greater or equal to the number of records. Base.IOError if an I/O error occurred.
    # 
    def read(idx: int, grid: DRegularGrid, overwrite: bool = True) -> DRegularGridReaderBase: pass

    ##
    # \brief Skips the data record at the current record index.
    # 
    # If the operation was successful, the record index is incremented by <em>1</em>.
    # 
    # \return \a self 
    # 
    # \throw Base.IOError if an I/O error occurred.
    # 
    def skip() -> DRegularGridReaderBase: pass

    ##
    # \brief Tells if there are any data records left to read.
    # 
    # \return <tt>True</tt> if there are data records left to read, and <tt>False</tt> otherwise. 
    # 
    # \throw Base.IOError if an I/O error occurred.
    # 
    def hasMoreData() -> bool: pass

    ##
    # \brief Returns the index of the current data record.
    # 
    # \return The zero-based index of the current data record.
    # 
    def getRecordIndex() -> int: pass

    ##
    # \brief Sets the index of the current data record to <em>idx</em>.
    # 
    # \param idx The zero-based index of the data record.
    # 
    # \throw Base.IndexError if <em>idx</em> is greater or equal to the number of available data records. Base.IOError if an I/O error occurred.
    # 
    def setRecordIndex(idx: int) -> None: pass

    ##
    # \brief Returns the total number of available data records.
    # 
    # \return The total number of available data records. 
    # 
    # \throw Base.IOError if an I/O error occurred.
    # 
    def getNumRecords() -> int: pass

    ##
    # \brief Performs a reader specific shutdown operation (if required).
    # 
    # \throw Base.IOError if an I/O error occurred.
    # 
    def close() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __nonzero__() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    numRecords = property(getNumRecords)
