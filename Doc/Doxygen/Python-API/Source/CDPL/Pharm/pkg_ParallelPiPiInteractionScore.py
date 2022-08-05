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
class ParallelPiPiInteractionScore(Boost.Python.instance):

    ##
    # \brief 
    #
    DEF_MIN_V_DISTANCE = 3.0

    ##
    # \brief 
    #
    DEF_MAX_V_DISTANCE = 5.5

    ##
    # \brief 
    #
    DEF_MAX_H_DISTANCE = 2.8

    ##
    # \brief 
    #
    DEF_ANGLE_TOLERANCE = 20.0

    ##
    # \brief Initializes the \e %ParallelPiPiInteractionScore instance.
    # \param score 
    #
    def __init__(score: ParallelPiPiInteractionScore) -> None: pass

    ##
    # \brief Initializes the \e %ParallelPiPiInteractionScore instance.
    # \param min_v_dist 
    # \param max_v_dist 
    # \param max_h_dist 
    # \param ang_tol 
    #
    def __init__(min_v_dist: float = 3.0, max_v_dist: float = 5.5, max_h_dist: float = 2.8, ang_tol: float = 20.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    #
    # Different Python \e %ParallelPiPiInteractionScore instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %ParallelPiPiInteractionScore instances \e a and \e b reference different C++ objects. 
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
    def setNormalizationFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getMinVDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxVDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getMaxHDistance() -> float: pass

    ##
    # \brief 
    # \return 
    #
    def getAngleTolerance() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %ParallelPiPiInteractionScore instance \a constr.
    # \param constr The \e %ParallelPiPiInteractionScore instance to copy.
    # \return The assignment target \a self.
    #
    def assign(constr: ParallelPiPiInteractionScore) -> ParallelPiPiInteractionScore: pass

    ##
    # \brief 
    # \param ftr1 
    # \param ftr2 
    # \return 
    #
    def __call__(ftr1: Feature, ftr2: Feature) -> float: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief 
    #
    minVDistance = property(getMinVDistance)

    ##
    # \brief 
    #
    maxVDistance = property(getMaxVDistance)

    ##
    # \brief 
    #
    maxHDistance = property(getMaxHDistance)

    ##
    # \brief 
    #
    angleTolerance = property(getAngleTolerance)
