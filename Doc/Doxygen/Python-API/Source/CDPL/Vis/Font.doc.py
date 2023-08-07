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
# \brief Specifies a font for drawing text.
# 
# On creation of a <tt>Font</tt> object one can specify various attributes the font should have. The attributes set in the constructor can also be set later, e.g. setFamily() and setSize(). The remaining attributes must be set after construction, e.g. setBold(), setItalic(), setUnderlined(), setOverlined(), setStrikedOut() and setFixedPitch(). The corresponding getter methods like getFamily() and getSize() return the values that were set, even though the values used may differ. Renderer2D implementations generally will use the font with the specified attributes, or if no exactly matching font exists, they will take the closest matching available font.
# 
class Font(Boost.Python.instance):

    ##
    # \brief Constructs a font object with an unspecified family name and a font size of <em>12.0</em>.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %Font instance \a font.
    # \param font The \e %Font instance to copy.
    # 
    def __init__(font: Font) -> None: pass

    ##
    # \brief Constructs a font object with the specified font family name and font size.
    # 
    # If <em>size</em> is negative, the font size is set to zero.
    # 
    # \param family The font family name.
    # \param size The font size.
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
    # \brief Sets the font family name.
    # 
    # \param family The font family name.
    # 
    def setFamily(family: str) -> None: pass

    ##
    # \brief Returns the font family name.
    # 
    # \return The font family name.
    # 
    def getFamily() -> str: pass

    ##
    # \brief Sets the font size.
    # 
    # If <em>size</em> is negative, the font size is set to zero.
    # 
    # \param size The font size.
    # 
    def setSize(size: float) -> None: pass

    ##
    # \brief Returns the font size.
    # 
    # \return The font size.
    # 
    def getSize() -> float: pass

    ##
    # \brief Sets or clears the flag specifying whether text should be rendered bold.
    # 
    # \param flag <tt>True</tt> if text should be rendered bold, and <tt>False</tt> otherwise.
    # 
    def setBold(flag: bool) -> None: pass

    ##
    # \brief Returns the flag specifying whether text is rendered bold.
    # 
    # \return <tt>True</tt> if text is rendered bold, and <tt>False</tt> otherwise.
    # 
    def isBold() -> bool: pass

    ##
    # \brief Sets or clears the flag specifying whether text should be rendered italicized.
    # 
    # \param flag <tt>True</tt> if text should be rendered italicized, and <tt>False</tt> otherwise.
    # 
    def setItalic(flag: bool) -> None: pass

    ##
    # \brief Returns the flag specifying whether text is rendered italicized.
    # 
    # \return <tt>True</tt> if text is rendered italicized, and <tt>False</tt> otherwise.
    # 
    def isItalic() -> bool: pass

    ##
    # \brief Sets or clears the flag specifying whether text should be rendered underlined.
    # 
    # \param flag <tt>True</tt> if text should be rendered underlined, and <tt>False</tt> otherwise.
    # 
    def setUnderlined(flag: bool) -> None: pass

    ##
    # \brief Returns the flag specifying whether text is rendered underlined.
    # 
    # \return <tt>True</tt> if text is rendered underlined, and <tt>False</tt> otherwise.
    # 
    def isUnderlined() -> bool: pass

    ##
    # \brief Sets or clears the flag specifying whether text should be rendered overlined.
    # 
    # \param flag <tt>True</tt> if text should be rendered overlined, and <tt>False</tt> otherwise.
    # 
    def setOverlined(flag: bool) -> None: pass

    ##
    # \brief Returns the flag specifying whether text is rendered overlined.
    # 
    # \return <tt>True</tt> if text is rendered overlined, and <tt>False</tt> otherwise.
    # 
    def isOverlined() -> bool: pass

    ##
    # \brief Sets or clears the flag specifying whether text should be rendered striked-out.
    # 
    # \param flag <tt>True</tt> if text should be rendered striked-out, and <tt>False</tt> otherwise.
    # 
    def setStrikedOut(flag: bool) -> None: pass

    ##
    # \brief Returns the flag specifying whether text is rendered striked-out.
    # 
    # \return <tt>True</tt> if text is rendered striked-out, and <tt>False</tt> otherwise.
    # 
    def isStrikedOut() -> bool: pass

    ##
    # \brief Sets or clears the fixed pitch flag.
    # 
    # \param flag <tt>True</tt> if the font has a fixed pitch, and <tt>False</tt> otherwise.
    # 
    def setFixedPitch(flag: bool) -> None: pass

    ##
    # \brief Returns the fixed pitch flag.
    # 
    # \return <tt>True</tt> if the font has a fixed pitch, and <tt>False</tt> otherwise.
    # 
    def hasFixedPitch() -> bool: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param font The other <tt>Font</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if all font attributes compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(font: Font) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == font)</tt>.
    # 
    # \param font The other <tt>Font</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if one of the font attributes compares non-equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(font: Font) -> bool: pass

    ##
    # \brief Returns a string representation of the \e %Font instance.
    # \return The generated string representation.
    # 
    def __str__() -> str: pass

    objectID = property(getObjectID)

    family = property(getFamily, setFamily)

    size = property(getSize, setSize)

    bold = property(isBold, setBold)

    italic = property(isItalic, setItalic)

    underlined = property(isUnderlined, setUnderlined)

    overlined = property(isOverlined, setOverlined)

    strikedOut = property(isStrikedOut, setStrikedOut)

    fixedPitch = property(hasFixedPitch, setFixedPitch)
