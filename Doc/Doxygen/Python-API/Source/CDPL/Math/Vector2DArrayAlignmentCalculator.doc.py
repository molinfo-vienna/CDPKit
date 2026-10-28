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
# \brief Kabsch algorithm [\ref KABA] implementation that operates directly on vector array inputs.
# 
class Vector2DArrayAlignmentCalculator(Boost.Python.instance):

    ##
    # \brief Contructs the \c Vector2DArrayAlignmentCalculator instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c Vector2DArrayAlignmentCalculator instance \a algo.
    # \param algo The \c Vector2DArrayAlignmentCalculator instance to copy.
    # 
    def __init__(algo: Vector2DArrayAlignmentCalculator) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c Vector2DArrayAlignmentCalculator instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c Vector2DArrayAlignmentCalculator instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c Vector2DArrayAlignmentCalculator instance \a algo.
    # \param algo The \c Vector2DArrayAlignmentCalculator instance to copy.
    # \return \a self.
    # 
    def assign(algo: Vector2DArrayAlignmentCalculator) -> Vector2DArrayAlignmentCalculator: pass

    ##
    # \brief Returns the rigid-body transformation produced by the most recent successful calculate() call.
    # 
    # \return The homogeneous transformation matrix.
    # 
    def getTransform() -> DMatrix: pass

    ##
    # \brief Aligns <em>points</em> onto <em>ref_points</em> (with uniform weights) using the Kabsch algorithm.
    # 
    # \param points The vector array containing the points to align.
    # \param ref_points The vector array containing the reference points.
    # \param do_center If <tt>True</tt>, the point sets are centered before alignment.
    # \param max_svd_iter The maximum number of iterations for the internal SVD step (0 means unlimited).
    # 
    # \return <tt>True</tt> if the SVD step converged, and <tt>False</tt> otherwise.
    # 
    def calculate(points: Vector2DArray, ref_points: Vector2DArray, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    ##
    # \brief Aligns <em>points</em> onto <em>ref_points</em> (with per-point weights) using the Kabsch algorithm.
    # 
    # \param points The vector array containing the points to align.
    # \param ref_points The vector array containing the reference points.
    # \param weights The per-point weights.
    # \param do_center If <tt>True</tt>, the point sets are centered before alignment.
    # \param max_svd_iter The maximum number of iterations for the internal SVD step (0 means unlimited).
    # 
    # \return <tt>True</tt> if the SVD step converged, and <tt>False</tt> otherwise.
    # 
    def calculate(points: Vector2DArray, ref_points: Vector2DArray, weights: ConstFVectorExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    ##
    # \brief Aligns <em>points</em> onto <em>ref_points</em> (with per-point weights) using the Kabsch algorithm.
    # 
    # \param points The vector array containing the points to align.
    # \param ref_points The vector array containing the reference points.
    # \param weights The per-point weights.
    # \param do_center If <tt>True</tt>, the point sets are centered before alignment.
    # \param max_svd_iter The maximum number of iterations for the internal SVD step (0 means unlimited).
    # 
    # \return <tt>True</tt> if the SVD step converged, and <tt>False</tt> otherwise.
    # 
    def calculate(points: Vector2DArray, ref_points: Vector2DArray, weights: ConstDVectorExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    objectID = property(getObjectID)

    transform = property(getTransform)
