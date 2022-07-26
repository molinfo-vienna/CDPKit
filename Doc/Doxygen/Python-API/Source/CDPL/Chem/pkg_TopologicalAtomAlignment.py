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
class TopologicalAtomAlignment(Boost.Python.instance):

    ##
    # \brief Initializes the \e %TopologicalAtomAlignment instance.
    # \param self The \e %TopologicalAtomAlignment instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %TopologicalAtomAlignment instance.
    # \param self The \e %TopologicalAtomAlignment instance to initialize.
    # \param alignment 
    #
    def __init__(self: object, alignment: TopologicalAtomAlignment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    #
    # Different Python \e %TopologicalAtomAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %TopologicalAtomAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: TopologicalAtomAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityMatchFunction(self: TopologicalAtomAlignment, func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \return 
    #
    def getEntityMatchFunction(self: TopologicalAtomAlignment) -> CDPL.ForceField.InteractionFilterFunction2: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityPairMatchFunction(self: TopologicalAtomAlignment, func: CDPL.ForceField.InteractionFilterFunction4) -> None: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \return 
    #
    def getEntityPairMatchFunction(self: TopologicalAtomAlignment) -> CDPL.ForceField.InteractionFilterFunction4: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param entity 
    # \param first_set 
    #
    def addEntity(self: TopologicalAtomAlignment, entity: Atom, first_set: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param first_set 
    #
    def clearEntities(self: TopologicalAtomAlignment, first_set: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param first_set 
    # \return 
    #
    def getNumEntities(self: TopologicalAtomAlignment, first_set: bool) -> int: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param first_set 
    # \return 
    #
    def getEntities(self: TopologicalAtomAlignment, first_set: bool) -> object: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param idx 
    # \param first_set 
    # \return 
    #
    def getEntity(self: TopologicalAtomAlignment, idx: int, first_set: bool) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    #
    def reset(self: TopologicalAtomAlignment) -> None: pass

    ##
    # \brief 
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param mapping 
    # \return 
    #
    def nextAlignment(self: TopologicalAtomAlignment, mapping: CDPL.Util.STPairArray) -> bool: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %TopologicalAtomAlignment instance \a alignment.
    # \param self The \e %TopologicalAtomAlignment instance this method is called upon.
    # \param alignment The \e %TopologicalAtomAlignment instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: TopologicalAtomAlignment, alignment: TopologicalAtomAlignment) -> TopologicalAtomAlignment: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    ##
    # \brief 
    #
    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)
