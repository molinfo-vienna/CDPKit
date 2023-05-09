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
# \brief 
#
class Font(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Font instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Font instance.
    # \param font 
    #
    def __init__(font: Font) -> None: pass

    ##
    # \brief Initializes the \e %Font instance.
    # \param family 
    # \param size 
    #
    def __init__(family: str, size: float = 12.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %Font instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Font instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Font instance \a font.
    # \param font The \e %Font instance to copy.
    # \return \a self
    #
    def assign(font: Font) -> Font: pass

    ##
    # \brief 
    # \param family 
    #
    def setFamily(family: str) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFamily() -> str: pass

    ##
    # \brief 
    # \param size 
    #
    def setSize(size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getSize() -> float: pass

    ##
    # \brief 
    # \param flag 
    #
    def setBold(flag: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isBold() -> bool: pass

    ##
    # \brief 
    # \param flag 
    #
    def setItalic(flag: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isItalic() -> bool: pass

    ##
    # \brief 
    # \param flag 
    #
    def setUnderlined(flag: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isUnderlined() -> bool: pass

    ##
    # \brief 
    # \param flag 
    #
    def setOverlined(flag: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isOverlined() -> bool: pass

    ##
    # \brief 
    # \param flag 
    #
    def setStrikedOut(flag: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def isStrikedOut() -> bool: pass

    ##
    # \brief 
    # \param flag 
    #
    def setFixedPitch(flag: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def hasFixedPitch() -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == font</tt>.
    # \param font The \e %Font instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(font: Font) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != font</tt>.
    # \param font The \e %Font instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(font: Font) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Font instance.
    # \return The generated string representation.
    #
    def __str__() -> str: pass

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
