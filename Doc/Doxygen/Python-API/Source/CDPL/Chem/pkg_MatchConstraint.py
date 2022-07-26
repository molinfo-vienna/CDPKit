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
    # \param self The \e %MatchConstraint instance to initialize.
    # \param constr 
    #
    def __init__(self: object, constr: MatchConstraint) -> None: pass

    ##
    # \brief Initializes the \e %MatchConstraint instance.
    # \param self The \e %MatchConstraint instance to initialize.
    # \param id 
    # \param relation 
    #
    def __init__(self: object, id: int, relation: Relation) -> None: pass

    ##
    # \brief Initializes the \e %MatchConstraint instance.
    # \param self The \e %MatchConstraint instance to initialize.
    # \param id 
    # \param relation 
    # \param value 
    #
    def __init__(self: object, id: int, relation: Relation, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MatchConstraint instance \a constr.
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \param constr The \e %MatchConstraint instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: MatchConstraint, constr: MatchConstraint) -> MatchConstraint: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \return 
    #
    def getID(self: MatchConstraint) -> int: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \param id 
    #
    def setID(self: MatchConstraint, id: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \return 
    #
    def getRelation(self: MatchConstraint) -> Relation: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \param relation 
    #
    def setRelation(self: MatchConstraint, relation: Relation) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \return 
    #
    def getValue(self: MatchConstraint) -> CDPL.Base.Variant: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \param value 
    #
    def setValue(self: MatchConstraint, value: CDPL.Base.Variant) -> None: pass

    ##
    # \brief 
    # \param self The \e %MatchConstraint instance this method is called upon.
    # \return 
    #
    def hasValue(self: MatchConstraint) -> bool: pass

    ##
    # \brief 
    #
    ID = property(getID, setID)

    ##
    # \brief 
    #
    relation = property(getRelation, setRelation)

    ##
    # \brief 
    #
    value = property(getValue, setValue)
