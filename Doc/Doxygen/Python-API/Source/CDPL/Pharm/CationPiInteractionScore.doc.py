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
# \brief Pharm.FeatureInteractionScore implementation that scores an aromatic/cationic feature pair by combining per-component scores for cation-to-ring-center distance and cation-displacement to ring-plane-normal angle.
# 
class CationPiInteractionScore(FeatureInteractionScore):

    ##
    # \brief Default minimum cation-to-aromatic-center distance in &Aring;ngstrom.
    # 
    DEF_MIN_DISTANCE = 3.5

    ##
    # \brief Default maximum cation-to-aromatic-center distance in &Aring;ngstrom.
    # 
    DEF_MAX_DISTANCE = 5.5

    ##
    # \brief Default maximum angle between cation displacement and aromatic-ring plane normal in degrees.
    # 
    DEF_MAX_ANGLE = 30.0

    ##
    # \brief Initializes a copy of the \c %CationPiInteractionScore instance \a score.
    # \param score The \c %CationPiInteractionScore instance to copy.
    # 
    def __init__(score: CationPiInteractionScore) -> None: pass

    ##
    # \brief Constructs a <tt>CationPiInteractionScore</tt> functor with the specified constraints.
    # 
    # \param aro_cat <tt>True</tt> if the first feature argument represents the aromatic- and the second one the cationic-feature, and <tt>False</tt> otherwise.
    # \param min_dist The minimum allowed distance between the cationic- and aromatic-feature centers.
    # \param max_dist The maximum allowed distance between the cationic- and aromatic-feature centers.
    # \param max_ang The maximum allowed angle between the cationic- and aromatic-feature plane normal.
    # 
    def __init__(aro_cat: bool, min_dist: float = 3.5, max_dist: float = 5.5, max_ang: float = 30.0) -> None: pass

    ##
    # \brief Specifies the function that maps the cation-aromatic distance to its score contribution.
    # 
    # \param func The distance-scoring function.
    # 
    def setDistanceScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief Specifies the function that maps the cation-displacement angle to its score contribution.
    # 
    # \param func The angle-scoring function.
    # 
    def setAngleScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief Returns the currently configured minimum cation-aromatic distance.
    # 
    # \return The minimum distance.
    # 
    def getMinDistance() -> float: pass

    ##
    # \brief Returns the currently configured maximum cation-aromatic distance.
    # 
    # \return The maximum distance.
    # 
    def getMaxDistance() -> float: pass

    ##
    # \brief Returns the currently configured maximum angle between cation displacement and aromatic-plane normal.
    # 
    # \return The maximum angle in degrees.
    # 
    def getMaxAngle() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %CationPiInteractionScore instance \a constr.
    # \param constr The \c %CationPiInteractionScore instance to copy.
    # \return \a self
    # 
    def assign(constr: CationPiInteractionScore) -> CationPiInteractionScore: pass

    minDistance = property(getMinDistance)

    maxDistance = property(getMaxDistance)

    maxAngle = property(getMaxAngle)
