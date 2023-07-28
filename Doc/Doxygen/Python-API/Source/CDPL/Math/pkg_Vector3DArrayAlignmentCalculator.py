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
class Vector3DArrayAlignmentCalculator(Boost.Python.instance):

    ##
    # \brief Initializes the \e %Vector3DArrayAlignmentCalculator instance.
    # \param self The \e %Vector3DArrayAlignmentCalculator instance to initialize.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %Vector3DArrayAlignmentCalculator instance.
    # \param self The \e %Vector3DArrayAlignmentCalculator instance to initialize.
    # \param algo 
    # 
    def __init__(algo: Vector3DArrayAlignmentCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # \param self The \e %Vector3DArrayAlignmentCalculator instance this method is called upon.
    # 
    # Different Python \e %Vector3DArrayAlignmentCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \e %Vector3DArrayAlignmentCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief 
    # \param algo 
    # \return 
    #
    def assign(algo: Vector3DArrayAlignmentCalculator) -> Vector3DArrayAlignmentCalculator: pass

    ##
    # \brief 
    # \return 
    #
    def getTransform() -> DMatrix: pass

    ##
    # \brief 
    # \param points 
    # \param ref_points 
    # \param do_center 
    # \param max_svd_iter 
    # \return 
    #
    def calculate(points: Vector3DArray, ref_points: Vector3DArray, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    ##
    # \brief 
    # \param points 
    # \param ref_points 
    # \param weights 
    # \param do_center 
    # \param max_svd_iter 
    # \return 
    #
    def calculate(points: Vector3DArray, ref_points: Vector3DArray, weights: ConstFVectorExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    ##
    # \brief 
    # \param points 
    # \param ref_points 
    # \param weights 
    # \param do_center 
    # \param max_svd_iter 
    # \return 
    #
    def calculate(points: Vector3DArray, ref_points: Vector3DArray, weights: ConstDVectorExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    objectID = property(getObjectID)

    transform = property(getTransform)
