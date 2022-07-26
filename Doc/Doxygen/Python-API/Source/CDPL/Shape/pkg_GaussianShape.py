#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
# \brief 
#
class GaussianShape(CDPL.Base.PropertyContainer):

    ##
    # \brief 
    #
    class Element(Boost.Python.instance):

        ##
        # \brief Initializes the \e %Element instance.
        # \param self The \e %Element instance to initialize.
        # \param elem 
        #
        def __init__(self: object, elem: Element) -> None: pass

        ##
        # \brief Initializes the \e %Element instance.
        # \param arg1 The \e %Element instance to initialize.
        # \param pos 
        # \param radius 
        # \param color 
        # \param hardness 
        #
        def __init__(arg1: object, pos: CDPL.Math.Vector3D, radius: float, color: int = 0, hardness: float = 2.7) -> None: pass

        ##
        # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
        # \param self The \e %Element instance this method is called upon.
        #
        # Different Python \e %Element instances may reference the same underlying C++ class instance. The commonly used Python expression
        # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Element instances \e a and \e b reference different C++ objects. 
        # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
        # <tt>a.getObjectID() != b.getObjectID()</tt>.
        #
        # \return The numeric ID of the internally referenced C++ class instance.
        #
        def getObjectID(self: Element) -> int: pass

        ##
        # \brief Replaces the current state of \a self with a copy of the state of the \e %Element instance \a elem.
        # \param self The \e %Element instance this method is called upon.
        # \param elem The \e %Element instance to copy.
        # \return The assignment target \a self.
        #
        def assign(self: Element, elem: Element) -> Element: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \param pos 
        #
        def setPosition(self: Element, pos: CDPL.Math.Vector3D) -> None: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \return 
        #
        def getPosition(self: Element) -> CDPL.Math.Vector3D: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \param radius 
        #
        def setRadius(self: Element, radius: float) -> None: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \return 
        #
        def getRadius(self: Element) -> float: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \param color 
        #
        def setColor(self: Element, color: int) -> None: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \return 
        #
        def getColor(self: Element) -> int: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \param hardness 
        #
        def setHardness(self: Element, hardness: float) -> None: pass

        ##
        # \brief 
        # \param self The \e %Element instance this method is called upon.
        # \return 
        #
        def getHardness(self: Element) -> float: pass

        ##
        # \brief 
        #
        objectID = property(getObjectID)

        ##
        # \brief 
        #
        radius = property(getRadius, setRadius)

        ##
        # \brief 
        #
        color = property(getColor, setColor)

        ##
        # \brief 
        #
        hardness = property(getHardness, setHardness)

        ##
        # \brief 
        #
        position = property(getPosition, setPosition)

    ##
    # \brief Initializes the \e %GaussianShape instance.
    # \param self The \e %GaussianShape instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %GaussianShape instance.
    # \param self The \e %GaussianShape instance to initialize.
    # \param shape 
    #
    def __init__(self: object, shape: GaussianShape) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %GaussianShape instance \a shape.
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param shape The \e %GaussianShape instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: GaussianShape, shape: GaussianShape) -> GaussianShape: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key 
    # \param value 
    #
    def setProperty(self: GaussianShape, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key 
    # \return 
    #
    def removeProperty(self: GaussianShape, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key 
    # \param throw_ 
    # \return 
    #
    def getProperty(self: GaussianShape, key: CDPL.Base.LookupKey, throw_: bool = False) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key 
    # \return 
    #
    def isPropertySet(self: GaussianShape, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    #
    def clearProperties(self: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param cntnr 
    #
    def addProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param cntnr 
    #
    def copyProperties(self: PropertyContainer, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param cntnr 
    #
    def swap(self: GaussianShape, cntnr: CDPL.Base.PropertyContainer) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    #
    def clear(self: GaussianShape) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \return 
    #
    def getNumElements(self: GaussianShape) -> int: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param pos 
    # \param radius 
    # \param color 
    # \param hardness 
    #
    def addElement(self: GaussianShape, pos: CDPL.Math.Vector3D, radius: float, color: int = 0, hardness: float = 2.7) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param elem 
    #
    def addElement(self: GaussianShape, elem: Element) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param idx 
    #
    def removeElement(self: GaussianShape, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param idx 
    # \return 
    #
    def getElement(self: GaussianShape, idx: int) -> Element: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key 
    # \return 
    #
    def __getitem__(self: PropertyContainer, key: CDPL.Base.LookupKey) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param idx 
    # \return 
    #
    def __getitem__(self: GaussianShape, idx: int) -> Element: pass

    ##
    # \brief Returns the result of the membership test operation <tt>key in self</tt>.
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key The value to test for membership.
    # \return The result of the membership test operation.
    #
    def __contains__(self: GaussianShape, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key 
    # \param value 
    #
    def __setitem__(self: GaussianShape, key: CDPL.Base.LookupKey, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param key 
    # \return 
    #
    def __delitem__(self: GaussianShape, key: CDPL.Base.LookupKey) -> bool: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \param idx 
    #
    def __delitem__(self: GaussianShape, idx: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %GaussianShape instance this method is called upon.
    # \return 
    #
    def __len__(self: GaussianShape) -> int: pass
