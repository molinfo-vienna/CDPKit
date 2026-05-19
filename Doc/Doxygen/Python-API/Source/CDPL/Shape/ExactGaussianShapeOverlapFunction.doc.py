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
# \brief Shape.GaussianShapeOverlapFunction implementation that evaluates the overlap analytically using the full Gaussian-product expansion (no approximations).
# 
# The exact evaluation is more accurate but typically slower than Shape.FastGaussianShapeOverlapFunction.
# 
class ExactGaussianShapeOverlapFunction(GaussianShapeOverlapFunction):

    ##
    # \brief Constructs the <tt>ExactGaussianShapeOverlapFunction</tt> instance without associated shape functions.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>ExactGaussianShapeOverlapFunction</tt> instance with the given reference and aligned shape functions.
    # 
    # \param ref_shape_func The reference shape function.
    # \param ovl_shape_func The aligned shape function.
    # 
    def __init__(ref_shape_func: GaussianShapeFunction, ovl_shape_func: GaussianShapeFunction) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>ExactGaussianShapeOverlapFunction</tt> instance <em>func</em>.
    # 
    # \param func The <tt>ExactGaussianShapeOverlapFunction</tt> to copy.
    # 
    def __init__(func: ExactGaussianShapeOverlapFunction) -> None: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param func The other <tt>ExactGaussianShapeOverlapFunction</tt> instance.
    # 
    # \return \a self
    # 
    def assign(func: ExactGaussianShapeOverlapFunction) -> ExactGaussianShapeOverlapFunction: pass
