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
    # \brief Replaces the current state with a copy of the state of the \c Object3D instance \a self.
    # \param self The \c Object3D instance to copy.
    # \return \a arg1.
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
    # \brief Returns the sub-object at index <em>idx</em>.
    # 
    # \param idx The zero-based sub-object index.
    # 
    # \return The sub-object. 
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
    # \return The newly created sub-object.
    # 
    def addSubObject() -> Object3D: pass

    def addSubObject(obj: Object3D) -> Object3D: pass

    ##
    # \brief Returns the value of the property specified by <em>key</em>.
    # 
    # If an entry for the specified property exists, the stored value will be returned. Otherwise a Base.ItemNotFound exception will be thrown.
    # 
    # \param key The key of the property value to return.
    # 
    # 
    # \return The stored property value. 
    # 
    # \throw Base.ItemNotFound if an entry for the requested property value does not exist.
    # 
    def __getitem__(key: Base.LookupKey) -> Base.Any: pass

    def __getitem__(idx: int) -> Object3D: pass

    ##
    # \brief Tells whether or not a value has been assigned to the property specified by <em>key</em>.
    # 
    # \param key The key of the property.
    # 
    # \return <tt>True</tt> if a value has been assigned to the specified property, and <tt>False</tt> otherwise.
    # 
    def __contains__(key: Base.LookupKey) -> bool: pass

    ##
    # \brief Sets the value of the property specified by <em>key</em> to <em>val</em>.
    # 
    # If <em>val</em> is of type Base.Any and empty, i.e. the method Base.Any.isEmpty() returns <tt>True</tt>, and a property entry for <em>key</em> exists, the entry gets erased (equivalent to removeProperty() with <em>key</em> as argument).
    # 
    # \param key The key of the property value to assign or remove.
    # \param val The value of the property.
    # 
    def __setitem__(key: Base.LookupKey, val: Base.Any) -> None: pass

    ##
    # \brief Removes the entry for the property specified by <em>key</em>.
    # 
    # \param key The key of the property entry to remove.
    # 
    # \return <tt>True</tt> if an entry for <em>key</em> could be found and was removed, and <tt>False</tt> otherwise.
    # 
    def __delitem__(key: Base.LookupKey) -> bool: pass

    def __delitem__(idx: int) -> None: pass

    def __len__() -> int: pass

    numSubObjects = property(getNumSubObjects)
