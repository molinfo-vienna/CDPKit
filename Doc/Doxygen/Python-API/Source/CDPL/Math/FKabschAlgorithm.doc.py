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
# \brief Implementation of the Kabsch algorithm [\ref KABA].
# 
# Finds the least Root Mean Square Distance between two sets of \f$ N \f$ points in \f$ D \f$ dimensions and the rigid transformation (i.e. translation and rotation) to employ in order to bring one set that close to the other.
# 
# Note that the points are paired, i.e. it is known which point in one set should be compared to a given point in the other set. It is possible to give weights to the points. Those weights are determined a priori and do not depend on the distances.
# 
# The convention is used that points are column vectors of the input matrices.
# 
class FKabschAlgorithm(Boost.Python.instance):

    ##
    # \brief Contructs the \c FKabschAlgorithm instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Contructs a copy of the \c FKabschAlgorithm instance \a algo.
    # \param algo The \c FKabschAlgorithm instance to copy.
    # 
    def __init__(algo: FKabschAlgorithm) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c FKabschAlgorithm instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c FKabschAlgorithm instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state with a copy of the state of the \c FKabschAlgorithm instance \a algo.
    # \param algo The \c FKabschAlgorithm instance to copy.
    # \return \a self
    # 
    def assign(algo: FKabschAlgorithm) -> FKabschAlgorithm: pass

    ##
    # \brief Returns the rigid-body transformation produced by the most recent successful align() call.
    # 
    # \return The \f$ (D+1) \times (D+1) \f$ transformation matrix (homogeneous form).
    # 
    def getTransform() -> FMatrix: pass

    ##
    # \brief Computes the rigid body transformation that aligns a set of \f$ N \f$ \f$ D \f$-dimensional points <em>points</em> with a corresponding set of reference points <em>ref_points</em> at a minimum RMSD.
    # 
    # \param points A <em>D&times;N</em>-matrix storing the points to align as column vectors.
    # \param ref_points A <em>D&times;N</em>-matrix storing the reference points as column vectors.
    # \param do_center <tt>True</tt> if centering of the data points needs to be performed, and <tt>False</tt> if not.
    # \param max_svd_iter The maximum number of iterations to perform in the SV-decomposition, or <em>0</em> if no limit.
    # 
    # \return <tt>True</tt> if convergence in the internal SV-decomposition has been reached in <em>max_svd_iter</em> iterations, and <tt>False</tt> otherwise. 
    # 
    # \pre <tt>points().getSize1() == ref_points().getSize1()</tt> 
    # 
    # \pre <tt>points().getSize2() == ref_points().getSize2()</tt> 
    # 
    # \throw Base.SizeError if preconditions got violated.
    # 
    def align(points: ConstFMatrixExpression, ref_points: ConstFMatrixExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    ##
    # \brief Computes the rigid body transformation that aligns a set of \f$ N \f$ \f$ D \f$-dimensional points <em>points</em> with a corresponding set of reference points <em>ref_points</em> at a minimum RMSD.
    # 
    # \param points A <em>D&times;N</em>-matrix storing the points to align as column vectors.
    # \param ref_points A <em>D&times;N</em>-matrix storing the reference points as column vectors.
    # \param do_center <tt>True</tt> if centering of the data points needs to be performed, and <tt>False</tt> if not.
    # \param max_svd_iter The maximum number of iterations to perform in the SV-decomposition, or <em>0</em> if no limit.
    # 
    # \return <tt>True</tt> if convergence in the internal SV-decomposition has been reached in <em>max_svd_iter</em> iterations, and <tt>False</tt> otherwise. 
    # 
    # \pre <tt>points().getSize1() == ref_points().getSize1()</tt> 
    # 
    # \pre <tt>points().getSize2() == ref_points().getSize2()</tt> 
    # 
    # \throw Base.SizeError if preconditions got violated.
    # 
    def align(points: ConstDMatrixExpression, ref_points: ConstDMatrixExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    ##
    # \brief Computes the rigid body transformation that aligns a set of \f$ N \f$ \f$ D \f$-dimensional points <em>points</em> with a corresponding set of reference points <em>ref_points</em> at a minimum RMSD.
    # 
    # \param points A <em>D&times;N</em>-matrix storing the points to align as column vectors.
    # \param ref_points A <em>D&times;N</em>-matrix storing the reference points as column vectors.
    # \param weights A \f$ N \f$-dimensional vector storing the non-negative weights that are assigned to the points.
    # \param do_center <tt>True</tt> if centering of the data points needs to be performed, and <tt>False</tt> if not.
    # \param max_svd_iter The maximum number of iterations to perform in the SV-decomposition, or <em>0</em> if no limit.
    # 
    # \return <tt>True</tt> if convergence in the internal SV-decomposition has been reached in <em>max_svd_iter</em> iterations, and <tt>False</tt> otherwise. 
    # 
    # \pre <tt>points().getSize1() == ref_points().getSize1()</tt> 
    # 
    # \pre <tt>points().getSize2() == ref_points().getSize2()</tt> 
    # 
    # \pre <tt>weights().getSize() == points().getSize2()</tt> 
    # 
    # \pre <tt>weights()(i) >= 0 && sum(weights) > 0</tt> 
    # 
    # \throw Base.SizeError or Base.ValueError if preconditions got violated.
    # 
    def align(points: ConstFMatrixExpression, ref_points: ConstFMatrixExpression, weights: ConstFVectorExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    ##
    # \brief Computes the rigid body transformation that aligns a set of \f$ N \f$ \f$ D \f$-dimensional points <em>points</em> with a corresponding set of reference points <em>ref_points</em> at a minimum RMSD.
    # 
    # \param points A <em>D&times;N</em>-matrix storing the points to align as column vectors.
    # \param ref_points A <em>D&times;N</em>-matrix storing the reference points as column vectors.
    # \param weights A \f$ N \f$-dimensional vector storing the non-negative weights that are assigned to the points.
    # \param do_center <tt>True</tt> if centering of the data points needs to be performed, and <tt>False</tt> if not.
    # \param max_svd_iter The maximum number of iterations to perform in the SV-decomposition, or <em>0</em> if no limit.
    # 
    # \return <tt>True</tt> if convergence in the internal SV-decomposition has been reached in <em>max_svd_iter</em> iterations, and <tt>False</tt> otherwise. 
    # 
    # \pre <tt>points().getSize1() == ref_points().getSize1()</tt> 
    # 
    # \pre <tt>points().getSize2() == ref_points().getSize2()</tt> 
    # 
    # \pre <tt>weights().getSize() == points().getSize2()</tt> 
    # 
    # \pre <tt>weights()(i) >= 0 && sum(weights) > 0</tt> 
    # 
    # \throw Base.SizeError or Base.ValueError if preconditions got violated.
    # 
    def align(points: ConstDMatrixExpression, ref_points: ConstDMatrixExpression, weights: ConstDVectorExpression, do_center: bool = True, max_svd_iter: int = 0) -> bool: pass

    objectID = property(getObjectID)

    transform = property(getTransform)
