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
# \param grid 
# \param comment 
#
def setComment(grid: AttributedGrid, comment: str) -> None: pass

##
# \brief 
# \param grid 
# \return 
#
def hasComment(grid: AttributedGrid) -> bool: pass

##
# \brief 
# \param grid 
# \return 
#
def getComment(grid: AttributedGrid) -> str: pass

##
# \brief 
# \param grid 
#
def clearComment(grid: AttributedGrid) -> None: pass

##
# \brief 
# \param grid 
# \param name 
#
def setName(grid: AttributedGrid, name: str) -> None: pass

##
# \brief 
# \param grid 
# \return 
#
def hasName(grid: AttributedGrid) -> bool: pass

##
# \brief 
# \param grid 
# \return 
#
def getName(grid: AttributedGrid) -> str: pass

##
# \brief 
# \param grid 
#
def clearName(grid: AttributedGrid) -> None: pass

##
# \brief 
# \param cntnr 
# \param single_prec 
#
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param is_name 
#
def setCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer, is_name: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearCUBECommentIsNameParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param factor 
#
def setCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer, factor: float) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief 
# \param cntnr 
#
def clearCUBEInputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param factor 
#
def setCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer, factor: float) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> float: pass

##
# \brief 
# \param cntnr 
#
def clearCUBEOutputDistanceScalingFactorParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param strict 
#
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
#
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass
