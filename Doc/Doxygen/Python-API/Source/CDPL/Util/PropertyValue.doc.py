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
# \brief An unary functor that retrieves the value of a given property from the Base.PropertyContainer instance provided as argument.
# 
class PropertyValue(builtins.object):

    ##
    # \brief Constructs a <tt>PropertyValue</tt> instance for the property specified by <em>key</em>.
    # 
    # \param key The key of the property.
    # 
    def __init__(key: PropertyKey) -> None: pass

    ##
    # \brief Retrievs the value of the property specified in the constructor from the Base.PropertyContainer instance <em>cntnr</em>.
    # 
    # \param cntnr The Base.PropertyContainer instance storing the property value.
    # 
    # \return The value of the property.
    # 
    def __call__(cntnr: Base.PropertyContainer) -> object: pass
