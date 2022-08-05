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
class FeaturePositionMatchFunctor(Boost.Python.instance):

    ##
    # \brief Initializes the \e %FeaturePositionMatchFunctor instance.
    # \param func 
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
    # \return The assignment target \a self.
    #
    def assign(func: FeaturePositionMatchFunctor) -> FeaturePositionMatchFunctor: pass

    ##
    # \brief 
    # \param ftr1 
    # \param ftr2 
    # \return 
    #
    def __call__(ftr1: Feature, ftr2: Feature) -> bool: pass

    ##
    # \brief 
    # \param ftr1 
    # \param ftr2 
    # \param xform 
    # \return 
    #
    def __call__(ftr1: Feature, ftr2: Feature, xform: CDPL.Math.Matrix4D) -> bool: pass

    ##
    # \brief 
    #
    objectID = property(getObjectID)

    ##
    # \brief FIXME!
    #
    qryMode = property(getQryMode)
