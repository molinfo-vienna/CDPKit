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
# \brief MatchConstraint.
# 
class MatchConstraint(Boost.Python.instance):

    ##
    # \brief Defines constants for the specification of relational constraints on the values of query/target attribute pairs.
    # 
    class Relation(Boost.Python.enum):

        ##
        # \brief Specifies that the relation between the query and target attribute value is not constrained.
        # 
        ANY = 0

        ##
        # \brief Specifies that the value of the query attribute must be less than the corresponding value of the target attribute to fulfill the constraint.
        # 
        LESS = 1

        ##
        # \brief Specifies that the value of the query attribute must be equal to the corresponding value of the target attribute to fulfill the constraint.
        # 
        EQUAL = 2

        ##
        # \brief Specifies that the value of the query attribute must be greater than the corresponding value of the target attribute to fulfill the constraint.
        # 
        GREATER = 3

        ##
        # \brief Specifies that the value of the query attribute must be less than or equal to the corresponding value of the target attribute to fulfill the constraint.
        # 
        LESS_OR_EQUAL = 4

        ##
        # \brief Specifies that the value of the query attribute must be greater than or equal to the corresponding value of the target attribute to fulfill the constraint.
        # 
        GREATER_OR_EQUAL = 5

        ##
        # \brief Specifies that the value of the query attribute must not be equal to the corresponding value of the target attribute to fulfill the constraint.
        # 
        NOT_EQUAL = 6

    ##
    # \brief Initializes a copy of the \e %MatchConstraint instance \a constr.
    # \param constr The \e %MatchConstraint instance to copy.
    # 
    def __init__(constr: MatchConstraint) -> None: pass

    ##
    # \brief Initializes the \e %MatchConstraint instance.
    # \param id 
    # \param rel 
    # 
    def __init__(id: int, rel: Relation) -> None: pass

    ##
    # \brief Constructs a <tt>MatchConstraint</tt> object with the given identifier, relational constraint on the values of matching query/target attribute pairs and value of the query attribute.
    # 
    # \param id The identifier of the match constraint.
    # \param rel The relational constraint on the values of matching query/target attribute pairs.
    # \param val The value of the query attribute.
    # 
    def __init__(id: int, rel: Relation, val: Base.Any) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %MatchConstraint instance \a constr.
    # \param constr The \e %MatchConstraint instance to copy.
    # \return \a self
    # 
    def assign(constr: MatchConstraint) -> MatchConstraint: pass

    ##
    # \brief Returns the identifier of the match constraint.
    # 
    # \return The identifier of the match constraint.
    # 
    def getID() -> int: pass

    ##
    # \brief Sets the match constraint identifier to <em>id</em>.
    # 
    # \param id The identifier of the match constraint.
    # 
    def setID(id: int) -> None: pass

    ##
    # \brief Returns the relational constraint that must be fulfilled by the values of matching query/target attribute pairs.
    # 
    # \return The relational constraint on the values of matching query/target attribute pairs.
    # 
    def getRelation() -> Relation: pass

    ##
    # \brief Sets the relational constraint that must be fulfilled by the values of matching query/target attribute pairs.
    # 
    # \param rel The relational constraint on the values of matching query/target attribute pairs.
    # 
    def setRelation(rel: Relation) -> None: pass

    ##
    # \brief Returns a reference to the value of the query attribute of type <em>T</em>.
    # 
    # \return A reference to the value of the stored query attribute. 
    # 
    # \throw Base.BadCast if the stored <tt>Any</tt> instance is empty, or the stored value is not of the specified type <em>T</em>.
    # 
    def getValue() -> Base.Any: pass

    ##
    # \brief Sets the value of the query attribute.
    # 
    # \param val The value of the query attribute.
    # 
    def setValue(val: Base.Any) -> None: pass

    ##
    # \brief Tells wether a query attribute value has been set.
    # 
    # \return <tt>True</tt> if the value of the query attribute has been set, <tt>False</tt> otherwise.
    # 
    def hasValue() -> bool: pass

    id = property(getID, setID)

    relation = property(getRelation, setRelation)

    value = property(getValue, setValue)
