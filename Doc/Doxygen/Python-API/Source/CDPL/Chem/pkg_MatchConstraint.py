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
class MatchConstraint(Boost.Python.instance):

    ##
    # \brief 
    #
    class Relation(Boost.Python.enum):

        ##
        # \brief ANY.
        #
        ANY = 0

        ##
        # \brief LESS.
        #
        LESS = 1

        ##
        # \brief EQUAL.
        #
        EQUAL = 2

        ##
        # \brief GREATER.
        #
        GREATER = 3

        ##
        # \brief LESS_OR_EQUAL.
        #
        LESS_OR_EQUAL = 4

        ##
        # \brief GREATER_OR_EQUAL.
        #
        GREATER_OR_EQUAL = 5

        ##
        # \brief NOT_EQUAL.
        #
        NOT_EQUAL = 6

    ##
    # \brief Initializes the \e %MatchConstraint instance.
    # \param constr 
    #
    def __init__(constr: MatchConstraint) -> None: pass

    ##
    # \brief Initializes the \e %MatchConstraint instance.
    # \param id 
    # \param rel 
    #
    def __init__(id: int, rel: Relation) -> None: pass

    ##
    # \brief Initializes the \e %MatchConstraint instance.
    # \param id 
    # \param rel 
    # \param val 
    #
    def __init__(id: int, rel: Relation, val: CDPL.Base.Any) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MatchConstraint instance \a constr.
    # \param constr The \e %MatchConstraint instance to copy.
    # \return \a self
    #
    def assign(constr: MatchConstraint) -> MatchConstraint: pass

    ##
    # \brief 
    # \return 
    #
    def getID() -> int: pass

    ##
    # \brief 
    # \param id 
    #
    def setID(id: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getRelation() -> Relation: pass

    ##
    # \brief 
    # \param rel 
    #
    def setRelation(rel: Relation) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getValue() -> CDPL.Base.Any: pass

    ##
    # \brief 
    # \param val 
    #
    def setValue(val: CDPL.Base.Any) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def hasValue() -> bool: pass

    ##
    # \brief 
    #
    ID = property(getID, setID)

    ##
    # \brief FIXME!
    #
    rel = property(getRel, setRel)

    ##
    # \brief FIXME!
    #
    val = property(getVal, setVal)
