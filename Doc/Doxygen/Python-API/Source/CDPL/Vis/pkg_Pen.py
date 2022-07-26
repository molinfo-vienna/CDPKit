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
class Pen(Boost.Python.instance):

    ##
    # \brief 
    #
    class LineStyle(Boost.Python.enum):

        ##
        # \brief NO_LINE.
        #
        NO_LINE = 0

        ##
        # \brief SOLID_LINE.
        #
        SOLID_LINE = 1

        ##
        # \brief DASH_LINE.
        #
        DASH_LINE = 2

        ##
        # \brief DOT_LINE.
        #
        DOT_LINE = 3

        ##
        # \brief DASH_DOT_LINE.
        #
        DASH_DOT_LINE = 4

        ##
        # \brief DASH_DOT_DOT_LINE.
        #
        DASH_DOT_DOT_LINE = 5

    ##
    # \brief 
    #
    class CapStyle(Boost.Python.enum):

        ##
        # \brief FLAT_CAP.
        #
        FLAT_CAP = 0

        ##
        # \brief SQUARE_CAP.
        #
        SQUARE_CAP = 1

        ##
        # \brief ROUND_CAP.
        #
        ROUND_CAP = 2

    ##
    # \brief 
    #
    class JoinStyle(Boost.Python.enum):

        ##
        # \brief MITER_JOIN.
        #
        MITER_JOIN = 0

        ##
        # \brief BEVEL_JOIN.
        #
        BEVEL_JOIN = 1

        ##
        # \brief ROUND_JOIN.
        #
        ROUND_JOIN = 2

    ##
    # \brief Initializes the \e %Pen instance.
    # \param self The \e %Pen instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %Pen instance.
    # \param self The \e %Pen instance to initialize.
    # \param pen 
    #
    def __init__(self: object, pen: Pen) -> None: pass

    ##
    # \brief Initializes the \e %Pen instance.
    # \param self The \e %Pen instance to initialize.
    # \param line_style 
    #
    def __init__(self: object, line_style: LineStyle) -> None: pass

    ##
    # \brief Initializes the \e %Pen instance.
    # \param self The \e %Pen instance to initialize.
    # \param color 
    # \param width 
    # \param line_style 
    # \param cap_style 
    # \param join_style 
    #
    def __init__(self: object, color: Color, width: float = 1.0, line_style: LineStyle = CDPL.Vis.LineStyle.SOLID_LINE, cap_style: CapStyle = CDPL.Vis.CapStyle.ROUND_CAP, join_style: JoinStyle = CDPL.Vis.JoinStyle.ROUND_JOIN) -> None: pass

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
    def getObjectID(self: Pen) -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Pen instance \a pen.
    # \param self The \e %Pen instance this method is called upon.
    # \param pen The \e %Pen instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: Pen, pen: Pen) -> Pen: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \return 
    #
    def getCapStyle(self: Pen) -> CapStyle: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \param cap_style 
    #
    def setCapStyle(self: Pen, cap_style: CapStyle) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \return 
    #
    def getColor(self: Pen) -> Color: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \param color 
    #
    def setColor(self: Pen, color: Color) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \return 
    #
    def getJoinStyle(self: Pen) -> JoinStyle: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \param join_style 
    #
    def setJoinStyle(self: Pen, join_style: JoinStyle) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \return 
    #
    def getLineStyle(self: Pen) -> LineStyle: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \param line_style 
    #
    def setLineStyle(self: Pen, line_style: LineStyle) -> None: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \return 
    #
    def getWidth(self: Pen) -> float: pass

    ##
    # \brief 
    # \param self The \e %Pen instance this method is called upon.
    # \param width 
    #
    def setWidth(self: Pen, width: float) -> None: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == pen</tt>.
    # \param self The \e %Pen instance this method is called upon.
    # \param pen The \e %Pen instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __eq__(self: Pen, pen: Pen) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != pen</tt>.
    # \param self The \e %Pen instance this method is called upon.
    # \param pen The \e %Pen instance to be compared with.
    # \return The result of the comparison operation.
    #
    def __ne__(self: Pen, pen: Pen) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    capStyle = property(getCapStyle, setCapStyle)

    ##
    # \brief 
    #
    lineStyle = property(getLineStyle, setLineStyle)

    ##
    # \brief 
    #
    joinStyle = property(getJoinStyle, setJoinStyle)

    ##
    # \brief 
    #
    color = property(getColor, setColor)

    ##
    # \brief 
    #
    width = property(getWidth, setWidth)
