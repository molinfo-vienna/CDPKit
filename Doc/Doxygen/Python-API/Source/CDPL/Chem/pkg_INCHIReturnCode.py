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
# \brief Provides constants that are used to describe the status of an <em>InChI</em> [\ref INCHI] output or input operation.
# 
# The defined constants correspond to the return values of the <em>InChI C-API</em> functions (see [\ref INCHI]) that were used for the creation or decoding of <em>InChI</em> strings and keys.
# 
class INCHIReturnCode(Boost.Python.instance):

    ##
    # \brief Not used by the <em>InChI</em> C-library.
    # 
    SKIP = -2

    ##
    # \brief Specifies that no structural data were provided for the <em>InChI</em> generation (e.g. empty structure).
    # 
    EOF_ = -1

    ##
    # \brief Specifies that the operation was successful and no warnings have been issued.
    # 
    OKAY = 0

    ##
    # \brief Specifies that the operation was successful but warnings have been issued.
    # 
    WARNING = 1

    ##
    # \brief Specifies that the operation was not successful and no <em>InChI</em> has been created.
    # 
    ERROR = 2

    ##
    # \brief Specifies that the operation was not successful because some severe error occurred during processing (typically a memory allocation failure).
    # 
    FATAL = 3

    ##
    # \brief Specifies that the operation was not successful because of an unknown program error.
    # 
    UNKNOWN = 4

    ##
    # \brief Specifies that a previous call to the <em>InChI</em> generation function has not yet returned (should never happen).
    # 
    BUSY = 5
