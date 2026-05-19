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
# \brief Shape.GaussianShapeOverlapFunction implementation that uses two approximation techniques to trade some accuracy for a substantial speedup compared to Shape.ExactGaussianShapeOverlapFunction.
# 
# Two independent acceleration features can be enabled:
#  - <b>Proximity optimization</b> prunes Gaussian-product pair contributions based on a scaled van-der-Waals proximity test (see setRadiusScalingFactor()).
#  - <b>Fast exponential function</b> replaces the expensive <tt>std::exp</tt> call with a fast approximation that is accurate enough for screening-style overlap evaluation.
# 
class FastGaussianShapeOverlapFunction(GaussianShapeOverlapFunction):

    ##
    # \brief Default scaling factor applied to van der Waals radii for the proximity-check pruning.
    # 
    DEF_RADIUS_SCALING_FACTOR = 1.4

    ##
    # \brief Constructs the <tt>FastGaussianShapeOverlapFunction</tt> instance without associated shape functions.
    # 
    def __init__() -> None: pass

    ##
    # \brief Constructs the <tt>FastGaussianShapeOverlapFunction</tt> instance with the given reference and aligned shape functions.
    # 
    # \param ref_shape_func The reference shape function.
    # \param ovl_shape_func The aligned shape function.
    # 
    def __init__(ref_shape_func: GaussianShapeFunction, ovl_shape_func: GaussianShapeFunction) -> None: pass

    ##
    # \brief Constructs a copy of the <tt>FastGaussianShapeOverlapFunction</tt> instance <em>func</em>.
    # 
    # \param func The <tt>FastGaussianShapeOverlapFunction</tt> to copy.
    # 
    def __init__(func: FastGaussianShapeOverlapFunction) -> None: pass

    ##
    # \brief Copy assignment operator.
    # 
    # \param func The other <tt>FastGaussianShapeOverlapFunction</tt> instance.
    # 
    # \return \a self
    # 
    def assign(func: FastGaussianShapeOverlapFunction) -> FastGaussianShapeOverlapFunction: pass

    ##
    # \brief Enables or disables the proximity-check pruning of Gaussian-product pair contributions.
    # 
    # \param enable <tt>True</tt> to enable the proximity check, and <tt>False</tt> to disable it.
    # 
    def proximityOptimization(enable: bool) -> None: pass

    ##
    # \brief Tells whether the proximity-check pruning is enabled.
    # 
    # \return <tt>True</tt> if the proximity check is enabled, and <tt>False</tt> otherwise.
    # 
    def proximityOptimization() -> bool: pass

    ##
    # \brief Sets the scaling factor applied to van der Waals radii during the proximity check.
    # 
    # \param factor The new radius scaling factor.
    # 
    def setRadiusScalingFactor(factor: float) -> None: pass

    ##
    # \brief Returns the currently configured radius scaling factor.
    # 
    # \return The radius scaling factor.
    # 
    def getRadiusScalingFactor() -> float: pass

    ##
    # \brief Enables or disables the use of a fast approximation for the exponential function.
    # 
    # \param enable <tt>True</tt> to enable the fast-exponential approximation, and <tt>False</tt> to use the standard exponential.
    # 
    def fastExpFunction(enable: bool) -> None: pass

    ##
    # \brief Tells whether the fast-exponential approximation is enabled.
    # 
    # \return <tt>True</tt> if the fast-exponential approximation is enabled, and <tt>False</tt> otherwise.
    # 
    def fastExpFunction() -> bool: pass

    proximityOpt = property(proximityOptimization, proximityOptimization)

    radiusScalingFactor = property(getRadiusScalingFactor, setRadiusScalingFactor)

    fastExpFunc = property(fastExpFunction, fastExpFunction)
