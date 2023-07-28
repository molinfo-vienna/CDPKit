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
# \brief A common interface for data-structures that support a random access to stored Chem.Entity3D instances.
# 
# Implementations have to guarantee that a given Chem.Entity3D object is stored only once and its index is unique amongst all contained Chem.Entity3D instances. Otherwise algorithms that rely on this behaviour may not work correctly!
# 
class Entity3DContainer(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Entity3DContainer instance.
    # \param self The \e %Entity3DContainer instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Returns a reference to the entity at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the Chem.Entity3D instance to return.
    # 
    # \return A reference to the entity at the specified index. 
    # 
    # \throw Base.IndexError if the number of entities is zero or <em>idx</em> is not in the range [0, getNumEntities() - 1].
    # 
    def getEntity(idx: int) -> Entity3D: pass

    ##
    # \brief Returns the number of stored Chem.Entity3D objects.
    # 
    # \return The number of stored Chem.Entity3D objects.
    # 
    def getNumEntities() -> int: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Entity3DContainer instance this method is called upon.
    # 
    # Different Python \e %Entity3DContainer instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Entity3DContainer instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Entity3D: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    objectID = property(getObjectID)

    numEntities = property(getNumEntities)
