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
# \brief Sets the value of the Grid.AttributedGridProperty.COMMENT property of the attributed grid <em>grid</em> to <em>comment</em>.
# 
# \param grid The attributed grid for which to set the property value.
# \param comment The new comment.
# 
# \since 1.4
# 
def setComment(grid: AttributedGrid, comment: str) -> None: pass

##
# \brief Tells whether the Grid.AttributedGridProperty.COMMENT property of the attributed grid <em>grid</em> is set.
# 
# \param grid The attributed grid for which to query the property value.
# 
# \return <tt>True</tt> if the comment property is set, and <tt>False</tt> otherwise. 
# 
# \since 1.4
# 
def hasComment(grid: AttributedGrid) -> bool: pass

##
# \brief Returns the value of the Grid.AttributedGridProperty.COMMENT property of the attributed grid <em>grid</em>.
# 
# \param grid The attributed grid for which to return the property value.
# 
# \return A reference to the comment. 
# 
# \since 1.4
# 
def getComment(grid: AttributedGrid) -> str: pass

##
# \brief Clears the value of the Grid.AttributedGridProperty.COMMENT property of the attributed grid <em>grid</em>.
# 
# \param grid The attributed grid for which to clear the property value.
# 
# \since 1.4
# 
def clearComment(grid: AttributedGrid) -> None: pass

##
# \brief Sets the value of the Grid.AttributedGridProperty.NAME property of the attributed grid <em>grid</em> to <em>name</em>.
# 
# \param grid The attributed grid for which to set the property value.
# \param name The new name.
# 
def setName(grid: AttributedGrid, name: str) -> None: pass

##
# \brief Tells whether the Grid.AttributedGridProperty.NAME property of the attributed grid <em>grid</em> is set.
# 
# \param grid The attributed grid for which to query the property value.
# 
# \return <tt>True</tt> if the name property is set, and <tt>False</tt> otherwise.
# 
def hasName(grid: AttributedGrid) -> bool: pass

##
# \brief Returns the value of the Grid.AttributedGridProperty.NAME property of the attributed grid <em>grid</em>.
# 
# \param grid The attributed grid for which to return the property value.
# 
# \return A reference to the name.
# 
def getName(grid: AttributedGrid) -> str: pass

##
# \brief Clears the value of the Grid.AttributedGridProperty.NAME property of the attributed grid <em>grid</em>.
# 
# \param grid The attributed grid for which to clear the property value.
# 
def clearName(grid: AttributedGrid) -> None: pass

##
# \brief Sets the value of the Grid.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> to <em>single_prec</em>.
# 
# \param cntnr The control-parameter container.
# \param single_prec <tt>True</tt> to write single-precision floats, and <tt>False</tt> to write double-precision floats.
# 
# \since 1.2
# 
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass

##
# \brief Tells whether the Grid.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def hasCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Grid.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if <em>CDF</em> output uses single-precision floats, and <tt>False</tt> otherwise. 
# 
# \since 1.2
# 
def getCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Grid.ControlParameter.CDF_OUTPUT_SINGLE_PRECISION_FLOATS parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.2
# 
def clearCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Grid.ControlParameter.CUBE_COMMENT_IS_NAME parameter of <em>cntnr</em> to <em>is_name</em>.
# 
# \param cntnr The control-parameter container.
# \param is_name <tt>True</tt> to interpret the <em>Gaussian CUBE</em> comment line as the grid name, and <tt>False</tt> to treat it as a regular comment.
# 
# \since 1.4
# 
def setCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer, is_name: bool) -> None: pass

##
# \brief Tells whether the Grid.ControlParameter.CUBE_COMMENT_IS_NAME parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.4
# 
def hasCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Grid.ControlParameter.CUBE_COMMENT_IS_NAME parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the <em>Gaussian CUBE</em> comment line is interpreted as the grid name, and <tt>False</tt> otherwise. 
# 
# \since 1.4
# 
def getCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Grid.ControlParameter.CUBE_COMMENT_IS_NAME parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.4
# 
def clearCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Grid.ControlParameter.CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter of <em>cntnr</em> to <em>factor</em>.
# 
# \param cntnr The control-parameter container.
# \param factor The new input distance scaling.
# 
# \since 1.4
# 
def setCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer, factor: float) -> None: pass

##
# \brief Tells whether the Grid.ControlParameter.CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.4
# 
def hasCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Grid.ControlParameter.CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The input distance scaling factor. 
# 
# \since 1.4
# 
def getCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief Removes the Grid.ControlParameter.CUBE_INPUT_DISTANCE_SCALING_FACTOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.4
# 
def clearCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Grid.ControlParameter.CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter of <em>cntnr</em> to <em>factor</em>.
# 
# \param cntnr The control-parameter container.
# \param factor The new output distance scaling factor.
# 
# \since 1.4
# 
def setCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer, factor: float) -> None: pass

##
# \brief Tells whether the Grid.ControlParameter.CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise. 
# 
# \since 1.4
# 
def hasCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Grid.ControlParameter.CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return The output distance scaling factor. 
# 
# \since 1.4
# 
def getCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief Removes the Grid.ControlParameter.CUBE_OUTPUT_DISTANCE_SCALING_FACTOR parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \since 1.4
# 
def clearCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief Sets the value of the Grid.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> to <em>strict</em>.
# 
# \param cntnr The control-parameter container.
# \param strict <tt>True</tt> to enable strict error checking, and <tt>False</tt> to disable it.
# 
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief Tells whether the Grid.ControlParameter.STRICT_ERROR_CHECKING parameter of <em>cntnr</em> is set.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if the parameter is set, and <tt>False</tt> otherwise.
# 
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Returns the value of the Grid.ControlParameter.STRICT_ERROR_CHECKING parameter stored in <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
# \return <tt>True</tt> if strict error checking is enabled, and <tt>False</tt> otherwise.
# 
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief Removes the Grid.ControlParameter.STRICT_ERROR_CHECKING parameter from <em>cntnr</em>.
# 
# \param cntnr The control-parameter container.
# 
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass
