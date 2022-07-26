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
class Font(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Font instance.
    # \param self The \e %Font instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Font instance.
    # \param self The \e %Font instance to initialize.
    # \param font 
    #
    def __init__(self: object, font: Font) -> None: pass

    ##
    # \brief Initializes the \e %Font instance.
    # \param self The \e %Font instance to initialize.
    # \param family 
    # \param size 
    #
    def __init__(self: object, family: str, size: float = 12.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Font instance this method is called upon.
    #
    # Different Python \e %Font instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Font instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: Font) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Font instance \a font.
    # \param self The \e %Font instance this method is called upon.
    # \param font The \e %Font instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Font, font: Font) -> Font: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param family 
    #
    def setFamily(self: Font, family: str) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def getFamily(self: Font) -> str: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param size 
    #
    def setSize(self: Font, size: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def getSize(self: Font) -> float: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param flag 
    #
    def setBold(self: Font, flag: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def isBold(self: Font) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param flag 
    #
    def setItalic(self: Font, flag: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def isItalic(self: Font) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param flag 
    #
    def setUnderlined(self: Font, flag: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def isUnderlined(self: Font) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param flag 
    #
    def setOverlined(self: Font, flag: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def isOverlined(self: Font) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param flag 
    #
    def setStrikedOut(self: Font, flag: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def isStrikedOut(self: Font) -> bool: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \param flag 
    #
    def setFixedPitch(self: Font, flag: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %Font instance this method is called upon.
    # \return 
    #
    def hasFixedPitch(self: Font) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == font</tt>.
    # \param self The \e %Font instance this method is called upon.
    # \param font The \e %Font instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Font, font: Font) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != font</tt>.
    # \param self The \e %Font instance this method is called upon.
    # \param font The \e %Font instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Font, font: Font) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Font instance.
    # \param self The \e %Font instance this method is called upon.
    # \return The generated string representation.
    #
    def __str__(self: Font) -> str: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    family = property(getFamily, setFamily)

    ##
    # \brief 
    #
    size = property(getSize, setSize)

    ##
    # \brief FIXME!
    #
    bold = property(getBold, setBold)

    ##
    # \brief FIXME!
    #
    italic = property(getItalic, setItalic)

    ##
    # \brief FIXME!
    #
    underlined = property(getUnderlined, setUnderlined)

    ##
    # \brief FIXME!
    #
    overlined = property(getOverlined, setOverlined)

    ##
    # \brief FIXME!
    #
    strikedOut = property(getStrikedOut, setStrikedOut)

    ##
    # \brief FIXME!
    #
    fixedPitch = property(getFixedPitch, setFixedPitch)
