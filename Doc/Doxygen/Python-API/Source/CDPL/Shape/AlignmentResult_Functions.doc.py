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
# \param res 
# \return 
#
def calcTanimotoComboScore(res: AlignmentResult) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \param beta 
# \return 
#
def calcTverskyComboScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief 
# \param res 
# \param beta 
# \return 
#
def calcAlignedTverskyComboScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \return 
#
def calcReferenceTverskyComboScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief 
# \param res 
# \return 
#
def calcShapeTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief 
# \param res 
# \return 
#
def calcTotalOverlapTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief 
# \param res 
# \return 
#
def calcColorTanimotoScore(res: AlignmentResult) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \param beta 
# \return 
#
def calcShapeTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief 
# \param res 
# \param beta 
# \return 
#
def calcAlignedShapeTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \return 
#
def calcReferenceShapeTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \param beta 
# \return 
#
def calcTotalOverlapTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief 
# \param res 
# \param beta 
# \return 
#
def calcAlignedTotalOverlapTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \return 
#
def calcReferenceTotalOverlapTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \param beta 
# \return 
#
def calcColorTverskyScore(res: AlignmentResult, alpha: float = 0.95, beta: float = 0.05) -> float: pass

##
# \brief 
# \param res 
# \param beta 
# \return 
#
def calcAlignedColorTverskyScore(res: AlignmentResult, beta: float = 0.95) -> float: pass

##
# \brief 
# \param res 
# \param alpha 
# \return 
#
def calcReferenceColorTverskyScore(res: AlignmentResult, alpha: float = 0.95) -> float: pass
