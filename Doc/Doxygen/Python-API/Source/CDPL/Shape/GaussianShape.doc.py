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
# \brief A data type for the descripton of arbitrary shapes composed of spheres approximated by gaussian functions.
# 
class GaussianShape(Base.PropertyContainer):

    ##
    # \brief A single sphere of the Gaussian shape, characterized by a position, radius, hardness and color.
    # 
    class Element(Boost.Python.instance):

        ##
        # \brief Initializes a copy of the \c %Element instance \a elem.
        # \param elem The \c %Element instance to copy.
        # 
        def __init__(elem: Element) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \c %Element instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %Element instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \c %Element instance \a elem.
        # \param elem The \c %Element instance to copy.
        # \return \a self
        # 
        def assign(elem: Element) -> Element: pass

        ##
        # \brief Sets the position of the sphere center.
        # 
        # \param pos The sphere center position.
        # 
        def setPosition(pos: Math.Vector3D) -> None: pass

        ##
        # \brief Returns the position of the sphere center.
        # 
        # \return The sphere center position.
        # 
        def getPosition() -> Math.Vector3D: pass

        ##
        # \brief Sets the sphere radius.
        # 
        # \param radius The sphere radius.
        # 
        def setRadius(radius: float) -> None: pass

        ##
        # \brief Returns the sphere radius.
        # 
        # \return The sphere radius.
        # 
        def getRadius() -> float: pass

        ##
        # \brief Sets the color attribute of the sphere.
        # 
        # \param color The color attribute.
        # 
        def setColor(color: int) -> None: pass

        ##
        # \brief Returns the color attribute of the sphere.
        # 
        # \return The color attribute.
        # 
        def getColor() -> int: pass

        ##
        # \brief Sets the hardness of the Gaussian.
        # 
        # \param hardness The Gaussian hardness.
        # 
        def setHardness(hardness: float) -> None: pass

        ##
        # \brief Returns the hardness of the Gaussian.
        # 
        # \return The Gaussian hardness.
        # 
        def getHardness() -> float: pass

        objectID = property(getObjectID)

        radius = property(getRadius, setRadius)

        color = property(getColor, setColor)

        hardness = property(getHardness, setHardness)

        position = property(getPosition, setPosition)

    ##
    # \brief Initializes the \c %GaussianShape instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \c %GaussianShape instance \a shape.
    # \param shape The \c %GaussianShape instance to copy.
    # 
    def __init__(shape: GaussianShape) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %GaussianShape instance \a shape.
    # \param shape The \c %GaussianShape instance to copy.
    # \return \a self
    # 
    def assign(shape: GaussianShape) -> GaussianShape: pass

    ##
    # \brief Removes all elements from the shape.
    # 
    def clear() -> None: pass

    ##
    # \brief Returns the number of elements in the shape.
    # 
    # \return The number of elements.
    # 
    def getNumElements() -> int: pass

    ##
    # \brief Adds a new element to the shape.
    # 
    # \param pos The position of the new element's sphere center.
    # \param radius The sphere radius.
    # \param color The color attribute.
    # \param hardness The hardness of the Gaussian.
    # 
    def addElement(pos: Math.Vector3D, radius: float, color: int = 0, hardness: float = 2.7) -> None: pass

    ##
    # \brief Adds the given element to the shape.
    # 
    # \param elem The element to add.
    # 
    def addElement(elem: Element) -> None: pass

    ##
    # \brief Removes the element at index <em>idx</em>.
    # 
    # \param idx The index of the element to remove.
    # 
    # \throw Base.IndexError if the number of elements is zero or <em>idx</em> is not in the range [0, getNumElements() - 1].
    # 
    def removeElement(idx: int) -> None: pass

    ##
    # \brief Returns a reference to the element at index <em>idx</em>.
    # 
    # \param idx The index of the element.
    # 
    # \return A reference to the element. 
    # 
    # \throw Base.IndexError if the number of elements is zero or <em>idx</em> is not in the range [0, getNumElements() - 1].
    # 
    def getElement(idx: int) -> Element: pass

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
    def __getitem__(idx: int) -> Element: pass

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
