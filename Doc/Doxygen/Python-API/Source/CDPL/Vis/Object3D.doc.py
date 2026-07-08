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
# \brief Hierarchical 3D scene object that owns a list of nested sub-objects and inherits its property bag from Base.PropertyContainer.
# 
# Concrete 3D representations (e.g. those produced by Vis.FeatureContainerObject3DFactory) are typically assembled as trees of nested <tt>Object3D</tt> instances annotated with rendering-relevant properties.
# 
# \since 1.3
# 
class Object3D(Base.PropertyContainer):

    ##
    # \brief Default constructor.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs a copy of the <tt>Object3D</tt> instance <em>obj</em>.
    # 
    # \param obj The <tt>Object3D</tt> instance to copy.
    # 
    def __init__(obj: Object3D) -> None: pass

    ##
    # \brief Replaces the current state of \a arg1 with a copy of the state of the \c %Object3D instance \a self.
    # \param self The \c %Object3D instance to copy.
    # \return \a arg1
    # 
    def assign(self: Object3D) -> Object3D: pass

    ##
    # \brief Removes all sub-objects and clears all properties of this object.
    # 
    def clear() -> None: pass

    ##
    # \brief Removes the sub-object at index <em>idx</em>.
    # 
    # \param idx The zero-based index of the sub-object to remove.
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumSubObjects()).
    # 
    def removeSubObject(idx: int) -> None: pass

    ##
    # \brief Returns a reference to the sub-object at index <em>idx</em>.
    # 
    # \param idx The zero-based sub-object index.
    # 
    # \return A reference to the sub-object. 
    # 
    # \throw Base.IndexError if <em>idx</em> is not in the range [0, getNumSubObjects()).
    # 
    def getSubObject(idx: int) -> Object3D: pass

    ##
    # \brief Returns the number of sub-objects directly owned by this object.
    # 
    # \return The sub-object count.
    # 
    def getNumSubObjects() -> int: pass

    ##
    # \brief Creates a new empty sub-object and appends it to the sub-object list.
    # 
    # \return A reference to the newly created sub-object.
    # 
    def addSubObject() -> Object3D: pass

    ##
    # \brief 
    # \param obj 
    # \return 
    #
    def addSubObject(obj: Object3D) -> Object3D: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    ##
    # \brief 
    # \param idx 
    # \return 
    #
    def __getitem__(idx: int) -> Object3D: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param key 
    # \param value 
    #
    def __setitem__(key: Base.LookupKey, value: Base.Any) -> None: pass

    ##
    # \brief 
    # \param key 
    # \return 
    #
    def __delitem__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param idx 
    #
    def __delitem__(idx: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def __len__() -> int: pass

    numSubObjects = property(getNumSubObjects)
