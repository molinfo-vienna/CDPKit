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
# \brief FeaturePositionMatchFunctor.
# 
class FeaturePositionMatchFunctor(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FeaturePositionMatchFunctor instance with a copy of the state of the \e %FeaturePositionMatchFunctor instance \a func.
    # \param func The \e %FeaturePositionMatchFunctor instance to copy.
    # 
    def __init__(func: FeaturePositionMatchFunctor) -> None: pass

    ##
    # \brief Initializes the \e %FeaturePositionMatchFunctor instance.
    # \param query_mode 
    # 
    def __init__(query_mode: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %FeaturePositionMatchFunctor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeaturePositionMatchFunctor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeaturePositionMatchFunctor instance \a func.
    # \param func The \e %FeaturePositionMatchFunctor instance to copy.
    # \return \a self
    # 
    def assign(func: FeaturePositionMatchFunctor) -> FeaturePositionMatchFunctor: pass

    ##
    # \brief Checks if the distance between <em>ftr1</em> and <em>ftr2</em> is below the allowed maximum and calculates a score reflecting their proximity.
    # 
    # If in 'query mode', the tolerance of <em>ftr1</em> specifies the allowed maximum distance. Otherwise, the maximum tolerance of the features takes effect.
    # 
    # \param ftr1 The first feature.
    # \param ftr2 The second feature.
    # 
    # \return A score from <em>0</em> (=outside effective tolerance) and <em>1</em> (exact position match) that specifies the proximity of the features. 
    # 
    # \see Pharm.getPosition(const Feature&), Pharm.getTolerance(const Feature&)
    # 
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    ##
    # \brief Checks if the distance between <em>ftr1</em> and <em>ftr2</em> is below the allowed maximum and calculates a score reflecting their proximity.
    # 
    # If in 'query mode', the tolerance of <em>ftr1</em> specifies the allowed maximum distance. Otherwise, the maximum tolerance of the features takes effect.
    # 
    # \param ftr1 The first feature.
    # \param ftr2 The second feature.
    # \param xform The transformation to apply to the position of the second feature.
    # 
    # \return A score from <em>0</em> (=outside effective tolerance) and <em>1</em> (exact position match) that specifies the proximity of the features. 
    # 
    # \see Pharm.getPosition(const Feature&), Pharm.getTolerance(const Feature&)
    # 
    def __call__(ftr1: Feature, ftr2: Feature, xform: Math.Matrix4D) -> bool: pass

    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    # \brief 
    #
    qryMode = property(getQryMode)
