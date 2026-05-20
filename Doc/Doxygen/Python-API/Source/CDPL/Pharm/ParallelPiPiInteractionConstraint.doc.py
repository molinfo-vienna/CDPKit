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
# \brief Constraint functor that tests whether an aromatic feature pair satisfies the geometric criteria for a parallel (sandwich/displaced) &pi;-&pi; interaction (vertical/horizontal center separations plus ring-normal angle).
# 
class ParallelPiPiInteractionConstraint(Boost.Python.instance):

    ##
    # \brief Default minimum out-of-plane (vertical) ring-center separation in &Aring;ngstrom.
    # 
    DEF_MIN_V_DISTANCE = 3.0

    ##
    # \brief Default maximum out-of-plane (vertical) ring-center separation in &Aring;ngstrom.
    # 
    DEF_MAX_V_DISTANCE = 5.5

    ##
    # \brief Default maximum in-plane (horizontal) ring-center displacement in &Aring;ngstrom.
    # 
    DEF_MAX_H_DISTANCE = 2.8

    ##
    # \brief Default maximum angle deviation from 0&deg; of the two ring-plane normals in degrees.
    # 
    DEF_MAX_ANGLE = 30.0

    ##
    # \brief Initializes a copy of the \c %ParallelPiPiInteractionConstraint instance \a constr.
    # \param constr The \c %ParallelPiPiInteractionConstraint instance to copy.
    # 
    def __init__(constr: ParallelPiPiInteractionConstraint) -> None: pass

    ##
    # \brief Constructs a <tt>ParallelPiPiInteractionConstraint</tt> functor with the specified constraints.
    # 
    # \param min_v_dist The minimum allowed distance of the two feature-positions orthogonal to the ring-planes.
    # \param max_v_dist The maximum allowed distance of the two feature-positions orthogonal to the ring-planes.
    # \param max_h_dist The maximum allowed distance of the feature-position along the their ring-planes.
    # \param max_ang The maximum allowed angle deviation from 0° of the two ring-plane orientation vectors.
    # 
    def __init__(min_v_dist: float = 3.0, max_v_dist: float = 5.5, max_h_dist: float = 2.8, max_ang: float = 30.0) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %ParallelPiPiInteractionConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %ParallelPiPiInteractionConstraint instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the currently configured minimum out-of-plane ring-center separation.
    # 
    # \return The minimum vertical distance.
    # 
    def getMinVDistance() -> float: pass

    ##
    # \brief Returns the currently configured maximum out-of-plane ring-center separation.
    # 
    # \return The maximum vertical distance.
    # 
    def getMaxVDistance() -> float: pass

    ##
    # \brief Returns the currently configured maximum in-plane ring-center displacement.
    # 
    # \return The maximum horizontal distance.
    # 
    def getMaxHDistance() -> float: pass

    ##
    # \brief Returns the currently configured maximum deviation from a 0&deg; angle between the two ring-plane normals.
    # 
    # \return The maximum angle deviation in degrees.
    # 
    def getMaxAngle() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %ParallelPiPiInteractionConstraint instance \a constr.
    # \param constr The \c %ParallelPiPiInteractionConstraint instance to copy.
    # \return \a self
    # 
    def assign(constr: ParallelPiPiInteractionConstraint) -> ParallelPiPiInteractionConstraint: pass

    ##
    # \brief Tests whether <em>ftr1</em> and <em>ftr2</em> satisfy the geometric parallel &pi;-&pi; criteria.
    # 
    # \param ftr1 The first aromatic feature.
    # \param ftr2 The second aromatic feature.
    # 
    # \return <tt>True</tt> if the constraint is satisfied, and <tt>False</tt> otherwise.
    # 
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    objectID = property(getObjectID)

    minVDistance = property(getMinVDistance)

    maxVDistance = property(getMaxVDistance)

    maxHDistance = property(getMaxHDistance)

    maxAngle = property(getMaxAngle)
