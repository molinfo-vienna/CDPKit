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
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance to initialize.
    #
    def __init__(self: object) -> None: pass

    ##
    # \brief Initializes the \e %DefaultInteractionScoreGridSetCalculator instance.
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance to initialize.
    # \param step_size 
    # \param x_size 
    # \param y_size 
    # \param z_size 
    #
    def __init__(self: object, step_size: float, x_size: int, y_size: int, z_size: int) -> None: pass

    ##
    # \brief Initializes the \e %DefaultInteractionScoreGridSetCalculator instance.
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance to initialize.
    # \param x_step_size 
    # \param y_step_size 
    # \param z_step_size 
    # \param x_size 
    # \param y_size 
    # \param z_size 
    #
    def __init__(self: object, x_step_size: float, y_step_size: float, z_step_size: float, x_size: int, y_size: int, z_size: int) -> None: pass

    ##
    # \brief Initializes the \e %DefaultInteractionScoreGridSetCalculator instance.
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance to initialize.
    # \param calculator 
    #
    def __init__(self: object, calculator: DefaultInteractionScoreGridSetCalculator) -> None: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \e %DefaultInteractionScoreGridSetCalculator instance \a calculator.
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param calculator The \e %DefaultInteractionScoreGridSetCalculator instance to copy.
    # \return The assignment target \a self.
    #
    def assign(self: DefaultInteractionScoreGridSetCalculator, calculator: DefaultInteractionScoreGridSetCalculator) -> DefaultInteractionScoreGridSetCalculator: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \return 
    #
    def getXStepSize(self: DefaultInteractionScoreGridSetCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param size 
    #
    def setXStepSize(self: DefaultInteractionScoreGridSetCalculator, size: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \return 
    #
    def getYStepSize(self: DefaultInteractionScoreGridSetCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param size 
    #
    def setYStepSize(self: DefaultInteractionScoreGridSetCalculator, size: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \return 
    #
    def getZStepSize(self: DefaultInteractionScoreGridSetCalculator) -> float: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param size 
    #
    def setZStepSize(self: DefaultInteractionScoreGridSetCalculator, size: float) -> None: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \return 
    #
    def getGridXSize(self: DefaultInteractionScoreGridSetCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param size 
    #
    def setGridXSize(self: DefaultInteractionScoreGridSetCalculator, size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \return 
    #
    def getGridYSize(self: DefaultInteractionScoreGridSetCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param size 
    #
    def setGridYSize(self: DefaultInteractionScoreGridSetCalculator, size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \return 
    #
    def getGridZSize(self: DefaultInteractionScoreGridSetCalculator) -> int: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param size 
    #
    def setGridZSize(self: DefaultInteractionScoreGridSetCalculator, size: int) -> None: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \return 
    #
    def getCoordinatesTransform(self: DefaultInteractionScoreGridSetCalculator) -> CDPL.Math.Matrix4D: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param xform 
    #
    def setCoordinatesTransform(self: DefaultInteractionScoreGridSetCalculator, xform: CDPL.Math.Matrix4D) -> None: pass

    ##
    # \brief 
    # \param self The \e %DefaultInteractionScoreGridSetCalculator instance this method is called upon.
    # \param features 
    # \param grid_set 
    #
    def calculate(self: DefaultInteractionScoreGridSetCalculator, features: FeatureContainer, grid_set: CDPL.Grid.DRegularGridSet) -> None: pass

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
