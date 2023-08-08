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
# \brief FeaturePairDistanceMatchFunctor.
# 
class FeaturePairDistanceMatchFunctor(Boost.Python.instance):

    ##
    # \brief Initializes a copy of the \e %FeaturePairDistanceMatchFunctor instance \a func.
    # \param func The \e %FeaturePairDistanceMatchFunctor instance to copy.
    # 
    def __init__(func: FeaturePairDistanceMatchFunctor) -> None: pass

    ##
    # \brief Constructs the <tt>FeaturePairDistanceMatchFunctor</tt> instance.
    # 
    # \param query_mode If <tt>True</tt>, the second pair feature distance must fall in the distance +/- tolerances of the first pair for the compatibility check to succeed. If <tt>False</tt>, it is sufficient that any one of the pairs matches the distance range of the other.
    # 
    def __init__(query_mode: bool) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \e %FeaturePairDistanceMatchFunctor instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %FeaturePairDistanceMatchFunctor instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \return 
    #
    def queryMode() -> bool: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %FeaturePairDistanceMatchFunctor instance \a func.
    # \param func The \e %FeaturePairDistanceMatchFunctor instance to copy.
    # \return \a self
    # 
    def assign(func: FeaturePairDistanceMatchFunctor) -> FeaturePairDistanceMatchFunctor: pass

    ##
    # \brief Checks if the feature pairs (<em>p1_ftr1</em>, <em>p1_ftr2</em>) and (<em>p2_ftr1</em>, <em>p2_ftr2</em>) are matching in terms of their feature distance.
    # 
    # \param p1_ftr1 The first feature of the first pair.
    # \param p1_ftr2 The second feature of the first pair.
    # \param p2_ftr1 The first feature of the second pair.
    # \param p2_ftr2 The second feature of the second pair.
    # 
    # \return <tt>True</tt> if the feature pair distance are compatible, and <tt>False</tt> otherwise. 
    # 
    # \see FeaturePairDistanceMatchFunctor()
    # 
    def __call__(p1_ftr1: Feature, p1_ftr2: Feature, p2_ftr1: Feature, p2_ftr2: Feature) -> bool: pass

    objectID = property(getObjectID)

    qryMode = property(queryMode)
