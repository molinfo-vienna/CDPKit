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
    # \brief 
    #
    class Element(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Element instance with a copy of the state of the \e %Element instance \a elem.
        # \param elem The \e %Element instance to copy.
        # 
        def __init__(elem: Element) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # 
        # Different Python \e %Element instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Element instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        # 
        # \return The numeric ID of the internally referenced C++ class instance.
        # 
        def getObjectID() -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Element instance \a elem.
        # \param elem The \e %Element instance to copy.
        # \return \a self
        # 
        def assign(elem: Element) -> Element: pass

        ##
        # \brief 
        # \param pos 
        #
        def setPosition(pos: Math.Vector3D) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getPosition() -> Math.Vector3D: pass

        ##
        # \brief 
        # \param radius 
        #
        def setRadius(radius: float) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getRadius() -> float: pass

        ##
        # \brief 
        # \param color 
        #
        def setColor(color: int) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getColor() -> int: pass

        ##
        # \brief 
        # \param hardness 
        #
        def setHardness(hardness: float) -> None: pass

        ##
        # \brief 
        # \return 
        #
        def getHardness() -> float: pass

        objectID = property(getObjectID)

        radius = property(getRadius, setRadius)

        color = property(getColor, setColor)

        hardness = property(getHardness, setHardness)

        position = property(getPosition, setPosition)

    ##
    # \brief Initializes the \e %GaussianShape instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %GaussianShape instance with a copy of the state of the \e %GaussianShape instance \a shape.
    # \param shape The \e %GaussianShape instance to copy.
    # 
    def __init__(shape: GaussianShape) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShape instance \a shape.
    # \param shape The \e %GaussianShape instance to copy.
    # \return \a self
    # 
    def assign(shape: GaussianShape) -> GaussianShape: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getNumElements() -> int: pass

    ##
    # \brief 
    # \param pos 
    # \param radius 
    # \param color 
    # \param hardness 
    #
    def addElement(pos: Math.Vector3D, radius: float, color: int = 0, hardness: float = 2.7) -> None: pass

    ##
    # \brief 
    # \param elem 
    #
    def addElement(elem: Element) -> None: pass

    ##
    # \brief 
    # \param idx 
    #
    def removeElement(idx: int) -> None: pass

    ##
    # \brief 
    # \param idx 
    # \return 
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
