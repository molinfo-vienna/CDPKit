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
# \brief Constraint functor that accepts a pair of features whose 3D-position distance lies within a configured [min, max] interval.
# 
class FeatureDistanceConstraint(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \c %FeatureDistanceConstraint instance \a constr.
    # \param constr The \c %FeatureDistanceConstraint instance to copy.
    # 
    def __init__(constr: FeatureDistanceConstraint) -> None: pass

    ##
    # \brief Constructs a <tt>FeatureDistanceConstraint</tt> functor with a minimum feature distance of <em>min_dist</em> and maximum distance of <em>max_dist</em>.
    # 
    # \param min_dist The minimum feature pair distance.
    # \param max_dist The maximum feature pair distance.
    # 
    def __init__(min_dist: float, max_dist: float) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %FeatureDistanceConstraint instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %FeatureDistanceConstraint instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Returns the currently configured minimum feature pair distance.
    # 
    # \return The minimum distance.
    # 
    def getMinDistance() -> float: pass

    ##
    # \brief Returns the currently configured maximum feature pair distance.
    # 
    # \return The maximum distance.
    # 
    def getMaxDistance() -> float: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %FeatureDistanceConstraint instance \a constr.
    # \param constr The \c %FeatureDistanceConstraint instance to copy.
    # \return \a self
    # 
    def assign(constr: FeatureDistanceConstraint) -> FeatureDistanceConstraint: pass

    ##
    # \brief Tests whether the 3D-position distance between <em>ftr1</em> and <em>ftr2</em> lies within the configured [min, max] interval.
    # 
    # \param ftr1 The first feature.
    # \param ftr2 The second feature.
    # 
    # \return <tt>True</tt> if the constraint is satisfied, and <tt>False</tt> otherwise.
    # 
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    objectID = property(getObjectID)

    minDistance = property(getMinDistance)

    maxDistance = property(getMaxDistance)
