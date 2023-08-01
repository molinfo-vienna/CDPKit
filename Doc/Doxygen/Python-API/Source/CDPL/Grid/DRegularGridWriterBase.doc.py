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
# \brief An interface for writing data objects of type Grid.DRegularGrid to an arbitrary data sink.
# 
# <tt>DRegularGridWriterBase</tt> is the common interface of classes which write objects of type Grid.DRegularGrid to some data sink (e.g. a file) that expects the data to be encoded in a particular storage format.
# 
# From the <tt>DRegularGridWriterBase</tt> interface point of view, the data sink is continuous output stream in which the data objects are written as data records. For the output of a given data object the method write() has to be called with the object passed as an argument.
# 
# If the write() operation fails, the writer instance is set into an error state that can be queried by the special methods __bool__() and __nonzero__(). Additionally, a <tt>DRegularGridWriterBase</tt> implementation may decide to throw an exception of type Base.IOError to report the error condition.
# 
class DRegularGridWriterBase(Base.DataIOBase):

    ##
    # \brief Initializes the \e %DRegularGridWriterBase instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Writes the DRegularGrid object <em>grid</em>.
    # 
    # \param grid The DRegularGrid object to write.
    # 
    # \return \a self 
    # 
    # \throw Base.IOError if an I/O error occurred.
    # 
    def write(grid: DRegularGrid) -> DRegularGridWriterBase: pass

    ##
    # \brief Writes format dependent data (if required) to mark the end of output.
    # 
    # \throw Base.IOError if an I/O error occurred.
    # 
    def close() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __nonzero__() -> bool: pass
