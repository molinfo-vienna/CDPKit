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
# \brief Pharm.FeatureInteractionScore implementation that scores a halogen-bond donor/acceptor feature pair by combining per-component scores for halogen-acceptor distance, acceptor-halogen-bound-atom angle and acceptor direction angle.
# 
class XBondingInteractionScore(FeatureInteractionScore):

    ##
    # \brief Default minimum halogen-acceptor distance in &Aring;ngstrom.
    # 
    DEF_MIN_AX_DISTANCE = 1.6

    ##
    # \brief Default maximum halogen-acceptor distance in &Aring;ngstrom.
    # 
    DEF_MAX_AX_DISTANCE = 4.0

    ##
    # \brief Default minimum acceptor-halogen-bound-atom angle in degrees.
    # 
    DEF_MIN_AXB_ANGLE = 150.0

    ##
    # \brief Default maximum deviation from the acceptor's preferred X-bonding direction in degrees.
    # 
    DEF_MAX_ACC_ANGLE = 35.0

    ##
    # \brief Initializes a copy of the \c %XBondingInteractionScore instance \a score.
    # \param score The \c %XBondingInteractionScore instance to copy.
    # 
    def __init__(score: XBondingInteractionScore) -> None: pass

    ##
    # \brief Constructs a <tt>XBondingInteractionScore</tt> functor with the specified scores.
    # 
    # \param don_acc <tt>True</tt> if the first feature argument represents the donor- and the second one the acceptor-feature, and <tt>False</tt> otherwise.
    # \param min_ax_dist The minimum allowed distance between the halogen-atom and the acceptor-feature.
    # \param max_ax_dist The maximum allowed distance between the halogen-atom and the acceptor-feature.
    # \param min_axb_ang The minimum allowed angle between the vectors halogen->acceptor snd halogen->bound atom.
    # \param max_acc_ang The maximum allowed angle deviation from the acceptor's preferred X-bonding direction.
    # 
    def __init__(don_acc: bool, min_ax_dist: float = 1.6, max_ax_dist: float = 4.0, min_axb_ang: float = 150.0, max_acc_ang: float = 35.0) -> None: pass

    ##
    # \brief Specifies the function that maps the halogen-acceptor distance to its score contribution.
    # 
    # \param func The distance-scoring function.
    # 
    def setDistanceScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief Specifies the function that maps the acceptor-direction angle to its score contribution.
    # 
    # \param func The acceptor-angle scoring function.
    # 
    def setAcceptorAngleScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief Specifies the function that maps the acceptor-halogen-bound-atom angle to its score contribution.
    # 
    # \param func The AXB-angle scoring function.
    # 
    def setAXBAngleScoringFunction(func: DoubleDoubleFunctor) -> None: pass

    ##
    # \brief Returns the currently configured minimum halogen-acceptor distance.
    # 
    # \return The minimum AX distance.
    # 
    def getMinAXDistance() -> float: pass

    ##
    # \brief Returns the currently configured maximum halogen-acceptor distance.
    # 
    # \return The maximum AX distance.
    # 
    def getMaxAXDistance() -> float: pass

    ##
    # \brief Returns the currently configured minimum acceptor-halogen-bound-atom angle.
    # 
    # \return The minimum AXB angle in degrees.
    # 
    def getMinAXBAngle() -> float: pass

    ##
    # \brief Returns the currently configured maximum deviation from the acceptor's preferred X-bonding direction.
    # 
    # \return The maximum acceptor angle in degrees.
    # 
    def getMaxAcceptorAngle() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %XBondingInteractionScore instance \a constr.
    # \param constr The \c %XBondingInteractionScore instance to copy.
    # \return \a self
    # 
    def assign(constr: XBondingInteractionScore) -> XBondingInteractionScore: pass

    minAXDistance = property(getMinAXDistance)

    maxAXDistance = property(getMaxAXDistance)

    minAXBAngle = property(getMinAXBAngle)

    maxAcceptorAngle = property(getMaxAcceptorAngle)
