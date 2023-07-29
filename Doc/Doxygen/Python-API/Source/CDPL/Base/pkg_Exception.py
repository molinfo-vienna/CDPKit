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
# \brief The root of the <em>CDPL</em> exception hierarchy.
# 
class Exception(builtins.Exception):

    ##
    # \brief Constructs an <tt>Exception</tt> object with the error message set to <em>msg</em>.
    # 
    # \param msg A message describing the cause of the exception and/or the location where the error occurred.
    # 
    def __init__(msg: str = '') -> None: pass

    ##
    # \brief Returns the message describing the cause of the exception and/or the location where the error occurred.
    # 
    # \return The message describing the cause of the exception and/or the location where the error occurred.
    # 
    def what() -> str: pass

    ##
    # \brief Returns a string representation of the \e %Exception instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass
