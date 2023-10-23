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
class Path2D(Boost.Python.instance):

    ##
    # \brief 
    #
    class FillRule(Boost.Python.enum):

        ##
        # \brief EVEN_ODD.
        #
        EVEN_ODD = 0

        ##
        # \brief WINDING.
        #
        WINDING = 1

    ##
    # \brief Initializes the \e %Path2D instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %Path2D instance \a path.
    # \param path The \e %Path2D instance to copy.
    # 
    def __init__(path: Path2D) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %Path2D instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Path2D instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %Path2D instance \a path.
    # \param path The \e %Path2D instance to copy.
    # \return \a self
    # 
    def assign(path: Path2D) -> Path2D: pass

    ##
    # \brief 
    # \return 
    #
    def isEmpty() -> bool: pass

    ##
    # \brief 
    #
    def clear() -> None: pass

    ##
    # \brief 
    # \param rule 
    #
    def setFilleRule(rule: FillRule) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getFilleRule() -> FillRule: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def moveTo(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param pos 
    #
    def moveTo(pos: Math.Vector2D) -> None: pass

    ##
    # \brief 
    # \param cx 
    # \param cy 
    # \param rx 
    # \param ry 
    # \param start_ang 
    # \param sweep 
    #
    def arc(cx: float, cy: float, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief 
    # \param ctr 
    # \param rx 
    # \param ry 
    # \param start_ang 
    # \param sweep 
    #
    def arc(ctr: Math.Vector2D, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief 
    # \param cx 
    # \param cy 
    # \param rx 
    # \param ry 
    # \param start_ang 
    # \param sweep 
    #
    def arcTo(cx: float, cy: float, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief 
    # \param ctr 
    # \param rx 
    # \param ry 
    # \param start_ang 
    # \param sweep 
    #
    def arcTo(ctr: Math.Vector2D, rx: float, ry: float, start_ang: float, sweep: float) -> None: pass

    ##
    # \brief 
    # \param x 
    # \param y 
    #
    def lineTo(x: float, y: float) -> None: pass

    ##
    # \brief 
    # \param pos 
    #
    def lineTo(pos: Math.Vector2D) -> None: pass

    ##
    # \brief 
    #
    def closePath() -> None: pass

    ##
    # \brief 
    # \param conv 
    #
    def convert(conv: Path2DConverter) -> None: pass

    ##
    # \brief Performs the in-place addition operation <tt>self += path</tt>.
    # \param path Specifies the second addend.
    # \return The updated \e %Path2D instance \a self.
    # 
    def __iadd__(path: Path2D) -> Path2D: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self == path</tt>.
    # \param path The \e %Path2D instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __eq__(path: Path2D) -> bool: pass

    ##
    # \brief Returns the result of the comparison operation <tt>self != path</tt>.
    # \param path The \e %Path2D instance to be compared with.
    # \return The result of the comparison operation.
    # 
    def __ne__(path: Path2D) -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def __bool__() -> bool: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    empty = property(getEmpty)

    ##
    # \brief FIXME!
    #
    fillRule = property(getFillRule, setFillRule)
