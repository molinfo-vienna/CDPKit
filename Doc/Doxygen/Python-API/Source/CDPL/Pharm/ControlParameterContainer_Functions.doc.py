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
# \param cntnr 
#
def clearPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPSDCreationModeParameter(cntnr: Base.ControlParameterContainer) -> Mode: pass

##
# \brief 
# \param cntnr 
# \param mode 
#
def setPSDCreationModeParameter(cntnr: Base.ControlParameterContainer, mode: Mode) -> None: pass

##
# \brief 
# \param cntnr 
#
def clearStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer) -> None: pass

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
# \param strict 
#
def setStrictErrorCheckingParameter(cntnr: Base.ControlParameterContainer, strict: bool) -> None: pass

##
# \brief 
# \param cntnr 
#
def clearPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \param allow 
#
def setPSDAllowDuplicatesParameter(cntnr: Base.ControlParameterContainer, allow: bool) -> None: pass

##
# \brief 
# \param cntnr 
#
def clearCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer) -> None: pass

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
# \param single_prec 
#
def setCDFOutputSinglePrecisionFloatsParameter(cntnr: Base.ControlParameterContainer, single_prec: bool) -> None: pass
