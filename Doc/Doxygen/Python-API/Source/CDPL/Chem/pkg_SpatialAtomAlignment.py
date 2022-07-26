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
class SpatialAtomAlignment(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SpatialAtomAlignment instance.
    # \param self The \e %SpatialAtomAlignment instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %SpatialAtomAlignment instance.
    # \param self The \e %SpatialAtomAlignment instance to initialize.
    # \param alignment 
    #
    def __init__(self: object, alignment: SpatialAtomAlignment) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    #
    # Different Python \e %SpatialAtomAlignment instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %SpatialAtomAlignment instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    #
    # \return The numeric ID of the internally referenced C++ class instance.
    #
    def getObjectID(self: SpatialAtomAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityMatchFunction(self: SpatialAtomAlignment, func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getEntityMatchFunction(self: SpatialAtomAlignment) -> CDPL.ForceField.InteractionFilterFunction2: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityPairMatchFunction(self: SpatialAtomAlignment, func: CDPL.ForceField.InteractionFilterFunction4) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getEntityPairMatchFunction(self: SpatialAtomAlignment) -> CDPL.ForceField.InteractionFilterFunction4: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param func 
    #
    def setTopAlignmentConstraintFunction(self: SpatialAtomAlignment, func: BoolSTPairArrayFunctor) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getTopAlignmentConstraintFunction(self: SpatialAtomAlignment) -> BoolSTPairArrayFunctor: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param func 
    #
    def setEntity3DCoordinatesFunction(self: SpatialAtomAlignment, func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getEntity3DCoordinatesFunction(self: SpatialAtomAlignment) -> Atom3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param func 
    #
    def setEntityWeightFunction(self: SpatialAtomAlignment, func: CDPL.ForceField.MMFF94AtomChargeFunction) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getEntityWeightFunction(self: SpatialAtomAlignment) -> CDPL.ForceField.MMFF94AtomChargeFunction: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param entity 
    # \param first_set 
    #
    def addEntity(self: SpatialAtomAlignment, entity: Atom, first_set: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param first_set 
    #
    def clearEntities(self: SpatialAtomAlignment, first_set: bool) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param first_set 
    # \return 
    #
    def getNumEntities(self: SpatialAtomAlignment, first_set: bool) -> int: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param first_set 
    # \return 
    #
    def getEntities(self: SpatialAtomAlignment, first_set: bool) -> object: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param idx 
    # \param first_set 
    # \return 
    #
    def getEntity(self: SpatialAtomAlignment, idx: int, first_set: bool) -> Atom: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param min_size 
    #
    def setMinTopologicalMappingSize(self: SpatialAtomAlignment, min_size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getMinTopologicalMappingSize(self: SpatialAtomAlignment) -> int: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param reset 
    #
    def reset(reset: SpatialAtomAlignment) -> None: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def nextAlignment(self: SpatialAtomAlignment) -> bool: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getTransform(self: SpatialAtomAlignment) -> CDPL.Math.Matrix4D: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %SpatialAtomAlignment instance \a alignment.
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \param alignment The \e %SpatialAtomAlignment instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: SpatialAtomAlignment, alignment: SpatialAtomAlignment) -> SpatialAtomAlignment: pass

    ##
    # \brief 
    # \param self The \e %SpatialAtomAlignment instance this method is called upon.
    # \return 
    #
    def getTopologicalMapping(self: SpatialAtomAlignment) -> CDPL.Util.STPairArray: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    topMapping = property(getTopMapping)

    ##
    # \brief 
    #
    minTopologicalMappingSize = property(getMinTopologicalMappingSize, setMinTopologicalMappingSize)

    ##
    # \brief 
    #
    transform = property(getTransform)

    ##
    # \brief 
    #
    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    ##
    # \brief 
    #
    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)

    ##
    # \brief 
    #
    topAlignmentConstraintFunction = property(getTopAlignmentConstraintFunction, setTopAlignmentConstraintFunction)

    ##
    # \brief 
    #
    entity3DCoordinatesFunction = property(getEntity3DCoordinatesFunction, setEntity3DCoordinatesFunction)

    ##
    # \brief 
    #
    entityWeightFunction = property(getEntityWeightFunction, setEntityWeightFunction)
