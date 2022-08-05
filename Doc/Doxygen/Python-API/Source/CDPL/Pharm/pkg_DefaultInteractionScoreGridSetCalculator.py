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
class DefaultInteractionScoreGridSetCalculator(InteractionScoreGridSetCalculator):

    ##
    # \brief Initializes the \e %DefaultInteractionScoreGridSetCalculator instance.
    #
    def __init__() -> None: pass

    ##
    # \brief Initializes the \e %DefaultInteractionScoreGridSetCalculator instance.
    # \param step_size 
    # \param x_size 
    # \param y_size 
    # \param z_size 
    #
    def __init__(step_size: float, x_size: int, y_size: int, z_size: int) -> None: pass

    ##
    # \brief Initializes the \e %DefaultInteractionScoreGridSetCalculator instance.
    # \param x_step_size 
    # \param y_step_size 
    # \param z_step_size 
    # \param x_size 
    # \param y_size 
    # \param z_size 
    #
    def __init__(x_step_size: float, y_step_size: float, z_step_size: float, x_size: int, y_size: int, z_size: int) -> None: pass

    ##
    # \brief Initializes the \e %DefaultInteractionScoreGridSetCalculator instance.
    # \param calculator 
    #
    def __init__(calculator: DefaultInteractionScoreGridSetCalculator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DefaultInteractionScoreGridSetCalculator instance \a calculator.
    # \param calculator The \e %DefaultInteractionScoreGridSetCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(calculator: DefaultInteractionScoreGridSetCalculator) -> DefaultInteractionScoreGridSetCalculator: pass

    ##
    # \brief 
    # \return 
    #
    def getXStepSize() -> float: pass

    ##
    # \brief 
    # \param size 
    #
    def setXStepSize(size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getYStepSize() -> float: pass

    ##
    # \brief 
    # \param size 
    #
    def setYStepSize(size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getZStepSize() -> float: pass

    ##
    # \brief 
    # \param size 
    #
    def setZStepSize(size: float) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGridXSize() -> int: pass

    ##
    # \brief 
    # \param size 
    #
    def setGridXSize(size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGridYSize() -> int: pass

    ##
    # \brief 
    # \param size 
    #
    def setGridYSize(size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getGridZSize() -> int: pass

    ##
    # \brief 
    # \param size 
    #
    def setGridZSize(size: int) -> None: pass

    ##
    # \brief 
    # \return 
    #
    def getCoordinatesTransform() -> CDPL.Math.Matrix4D: pass

    ##
    # \brief 
    # \param xform 
    #
    def setCoordinatesTransform(xform: CDPL.Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param features 
    # \param grid_set 
    #
    def calculate(features: FeatureContainer, grid_set: CDPL.Grid.DRegularGridSet) -> None: pass

    ##
    # \brief 
    #
    xStepSize = property(getXStepSize, setXStepSize)

    ##
    # \brief 
    #
    yStepSize = property(getYStepSize, setYStepSize)

    ##
    # \brief 
    #
    zStepSize = property(getZStepSize, setZStepSize)

    ##
    # \brief 
    #
    gridXSize = property(getGridXSize, setGridXSize)

    ##
    # \brief 
    #
    gridYSize = property(getGridYSize, setGridYSize)

    ##
    # \brief 
    #
    gridZSize = property(getGridZSize, setGridZSize)

    ##
    # \brief 
    #
    coordinatesTransform = property(getCoordinatesTransform, setCoordinatesTransform)
