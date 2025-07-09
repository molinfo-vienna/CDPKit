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
# \brief The abstract base class of all 3D graphics primitives.
# 
# Graphics primitives are simple (atomic) geometrical objects which can be used as building blocks for larger and more complex 3D objects (e.g. the 3D representation of a molecular structure).
# 
class GraphicsPrimitive3D(Boost.Python.instance):

    ##
    # \brief Initializes the \e %GraphicsPrimitive3D instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %GraphicsPrimitive3D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %GraphicsPrimitive3D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Creates a dynamically allocated copy of the graphics primitive.
    # 
    # \return The copy of the graphics primitive.
    # 
    def clone() -> GraphicsPrimitive3D: pass

    ##
    # \brief GraphicsPrimitive3DVisitor implementation accept method [\ref VPTN].
    # 
    def accept(visitor: object) -> None: pass

    objectID = property(getObjectID)
