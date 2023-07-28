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
class SpatialAtomAlignment(Boost.Python.instance):

    ##
    # \brief Initializes the \e %SpatialAtomAlignment instance.
    # \param self The \e %SpatialAtomAlignment instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %SpatialAtomAlignment instance.
    # \param self The \e %SpatialAtomAlignment instance to initialize.
    # \param alignment 
    # 
    def __init__(alignment: SpatialAtomAlignment) -> None: pass

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
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param func 
    #
    def setEntityMatchFunction(func: CDPL.ForceField.InteractionFilterFunction2) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEntityMatchFunction() -> CDPL.ForceField.InteractionFilterFunction2: pass

    ##
    # \brief 
    # \param func 
    #
    def setEntityPairMatchFunction(func: CDPL.ForceField.InteractionFilterFunction4) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEntityPairMatchFunction() -> CDPL.ForceField.InteractionFilterFunction4: pass

    ##
    # \brief 
    # \param func 
    #
    def setTopAlignmentConstraintFunction(func: BoolSTPairArrayFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getTopAlignmentConstraintFunction() -> BoolSTPairArrayFunctor: pass

    ##
    # \brief 
    # \param func 
    #
    def setEntity3DCoordinatesFunction(func: Atom3DCoordinatesFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEntity3DCoordinatesFunction() -> Atom3DCoordinatesFunction: pass

    ##
    # \brief 
    # \param func 
    #
    def setEntityWeightFunction(func: CDPL.ForceField.MMFF94AtomChargeFunction) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getEntityWeightFunction() -> CDPL.ForceField.MMFF94AtomChargeFunction: pass

    ##
    # \brief 
    # \param exhaustive 
    #
    def performExhaustiveSearch(exhaustive: bool) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def exhaustiveSearchPerformed() -> bool: pass

    ##
    # \brief 
    # \param entity 
    # \param first_set 
    #
    def addEntity(entity: Atom, first_set: bool) -> None: pass

    ##
    # \brief 
    # \param first_set 
    #
    def clearEntities(first_set: bool) -> None: pass

    ##
    # \brief 
    # \param first_set 
    # \return 
    #
    def getNumEntities(first_set: bool) -> int: pass

    ##
    # \brief 
    # \param first_set 
    # \return 
    #
    def getEntities(first_set: bool) -> object: pass

    ##
    # \brief 
    # \param idx 
    # \param first_set 
    # \return 
    #
    def getEntity(idx: int, first_set: bool) -> Atom: pass

    ##
    # \brief 
    # \param min_size 
    #
    def setMinTopologicalMappingSize(min_size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinTopologicalMappingSize() -> int: pass

    ##
    # \brief 
    # \param reset 
    #
    def reset() -> None: pass

    ##
    # \brief 
    # \return 
    #
    def nextAlignment() -> bool: pass

    ##
    # \brief 
    # \return 
    #
    def getTransform() -> CDPL.Math.Matrix4D: pass

    ##
    # \brief 
    # \param alignment 
    # \return 
    #
    def assign(alignment: SpatialAtomAlignment) -> SpatialAtomAlignment: pass

    ##
    # \brief 
    # \return 
    #
    def getTopologicalMapping() -> CDPL.Util.STPairArray: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    topMapping = property(getTopMapping)

    minTopologicalMappingSize = property(getMinTopologicalMappingSize, setMinTopologicalMappingSize)

    ##
    # \brief FIXME!
    # \brief 
    #
    exhaustiveSearch = property(getExhaustiveSearch, setExhaustiveSearch)

    transform = property(getTransform)

    entityMatchFunction = property(getEntityMatchFunction, setEntityMatchFunction)

    entityPairMatchFunction = property(getEntityPairMatchFunction, setEntityPairMatchFunction)

    topAlignmentConstraintFunction = property(getTopAlignmentConstraintFunction, setTopAlignmentConstraintFunction)

    entity3DCoordinatesFunction = property(getEntity3DCoordinatesFunction, setEntity3DCoordinatesFunction)

    entityWeightFunction = property(getEntityWeightFunction, setEntityWeightFunction)
