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
# \brief Specifies how to draw lines and outlines of shapes.
# 
# A pen has a line style, width, color, cap style and join style attribute. The line style specifies how a line will look like (solid, dashed, ...). The default line style is Pen.SOLID_LINE. Setting the line style to Pen.NO_LINE tells the renderer not to draw lines or outlines. The pen color defines the color of lines and text. The default line color is Color.BLACK. The cap style specifies how the end points of lines are drawn and the join style defines how the joins between two or more connected have to be drawn. The default cap style is Pen.ROUND_CAP and the default join style is Pen.ROUND_JOIN.
# 
class Pen(Boost.Python.instance):

    ##
    # \brief Defines constants for supported line styles.
    # 
    class LineStyle(Boost.Python.enum):

        ##
        # \brief Tells the renderer not to draw lines or shape outlines.
        # 
        NO_LINE = 0

        ##
        # \brief Specifies a solid line without gaps.
        # 
        SOLID_LINE = 1

        ##
        # \brief Specifies a dashed line.
        # 
        DASH_LINE = 2

        ##
        # \brief Specifies a dotted line.
        # 
        DOT_LINE = 3

        ##
        # \brief Specifies a line with alternating dots and dashes.
        # 
        DASH_DOT_LINE = 4

        ##
        # \brief Specifies a line with dashes that are followed by two dots.
        # 
        DASH_DOT_DOT_LINE = 5

    ##
    # \brief Defines constants for supported line cap styles.
    # 
    class CapStyle(Boost.Python.enum):

        ##
        # \brief Specifies a squared line end that does not cover the end point of the line.
        # 
        FLAT_CAP = 0

        ##
        # \brief Specifies a squared line end that covers the end point and extends beyond it with half the line width.
        # 
        SQUARE_CAP = 1

        ##
        # \brief Specifies a rounded line end.
        # 
        ROUND_CAP = 2

    ##
    # \brief Defines constants for supported line join styles.
    # 
    class JoinStyle(Boost.Python.enum):

        ##
        # \brief Specifies a join style where the outer edges of the lines are extended to meet at an angle, and this area is filled.
        # 
        MITER_JOIN = 0

        ##
        # \brief Specifies a join style where the triangular notch between the two lines is filled.
        # 
        BEVEL_JOIN = 1

        ##
        # \brief Specifies a join style where the circular arc between the two lines is filled.
        # 
        ROUND_JOIN = 2

    ##
    # \brief Constructs a pen with line style Pen.SOLID_LINE, line width <em>1.0</em>, cap style Pen.ROUND_CAP, join style Pen.ROUND_JOIN and color Color.BLACK.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Pen instance.
    # \param self The \e %Pen instance to initialize.
    # \param pen 
    # 
    def __init__(pen: Pen) -> None: pass

    ##
    # \brief Constructs a pen with the specified line style, line width <em>1.0</em>, cap style Pen.ROUND_CAP, join style Pen.ROUND_JOIN and color Color.BLACK.
    # 
    # \param line_style The line style.
    # 
    def __init__(line_style: LineStyle) -> None: pass

    ##
    # \brief Constructs a pen with the specified color, line width, line style, cap style and join style.
    # 
    # If <em>width</em> is negative, the line width is set to zero.
    # 
    # \param color The pen color.
    # \param width The line width.
    # \param line_style The line style.
    # \param cap_style The line cap style.
    # \param join_style The line join style.
    # 
    def __init__(color: Color, width: float = 1.0, line_style: LineStyle = CDPL.Vis.LineStyle.SOLID_LINE, cap_style: CapStyle = CDPL.Vis.CapStyle.ROUND_CAP, join_style: JoinStyle = CDPL.Vis.JoinStyle.ROUND_JOIN) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Pen instance this method is called upon.
    # 
    # Different Python \e %Pen instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Pen instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Pen instance \a pen.
    # \param self The \e %Pen instance this method is called upon.
    # \param pen The \e %Pen instance to copy.
    # \return \a self
    # 
    def assign(pen: Pen) -> Pen: pass

    ##
    # \brief Returns the line cap style.
    # 
    # \return The line cap style.
    # 
    def getCapStyle() -> CapStyle: pass

    ##
    # \brief Sets the line cap style to <em>cap_style</em>.
    # 
    # \param cap_style The line cap style.
    # 
    def setCapStyle(cap_style: CapStyle) -> None: pass

    ##
    # \brief Returns the color of the pen.
    # 
    # \return The color of the pen.
    # 
    def getColor() -> Color: pass

    ##
    # \brief Sets the pen's color to the specified value.
    # 
    # \param color The color of the pen.
    # 
    def setColor(color: Color) -> None: pass

    ##
    # \brief Returns the line join style.
    # 
    # \return The line join style.
    # 
    def getJoinStyle() -> JoinStyle: pass

    ##
    # \brief Sets the line join style to <em>join_style</em>.
    # 
    # \param join_style The line join style.
    # 
    def setJoinStyle(join_style: JoinStyle) -> None: pass

    ##
    # \brief Returns the line style.
    # 
    # \return The line style.
    # 
    def getLineStyle() -> LineStyle: pass

    ##
    # \brief Sets the line style to <em>line_style</em>.
    # 
    # \param line_style The line style.
    # 
    def setLineStyle(line_style: LineStyle) -> None: pass

    ##
    # \brief Returns the line width.
    # 
    # \return The line width.
    # 
    def getWidth() -> float: pass

    ##
    # \brief Sets the line width to the specified value.
    # 
    # If <em>width</em> is negative, the line width is set to zero.
    # 
    # \param width The line width.
    # 
    def setWidth(width: float) -> None: pass

    ##
    # \brief Equality comparison operator.
    # 
    # \param pen The other <tt>Pen</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if all pen attributes compare equal, and <tt>False</tt> otherwise.
    # 
    def __eq__(pen: Pen) -> bool: pass

    ##
    # \brief Inequality comparison operator.
    # 
    # The result is equivalent to <tt>!(self == pen)</tt>.
    # 
    # \param pen The other <tt>Pen</tt> object to be compared with.
    # 
    # \return <tt>True</tt> if the pen attributes compare non-equal, and <tt>False</tt> otherwise.
    # 
    def __ne__(pen: Pen) -> bool: pass

    objectID = property(getObjectID)

    capStyle = property(getCapStyle, setCapStyle)

    lineStyle = property(getLineStyle, setLineStyle)

    joinStyle = property(getJoinStyle, setJoinStyle)

    color = property(getColor, setColor)

    width = property(getWidth, setWidth)
