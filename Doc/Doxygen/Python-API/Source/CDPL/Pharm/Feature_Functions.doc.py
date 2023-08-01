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
# \param feature 
#
def clearTolerance(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasTolerance(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getTolerance(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
# \param tol 
#
def setTolerance(feature: Feature, tol: float) -> None: pass

##
# \brief 
# \param feature 
#
def clearType(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasType(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getType(feature: Feature) -> int: pass

##
# \brief 
# \param feature 
# \param type 
#
def setType(feature: Feature, type: int) -> None: pass

##
# \brief 
# \param feature 
#
def clearSubstructure(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasSubstructure(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getSubstructure(feature: Feature) -> Chem.Fragment: pass

##
# \brief 
# \param feature 
# \param substruct 
#
def setSubstructure(feature: Feature, substruct: Chem.Fragment) -> None: pass

##
# \brief 
# \param feature 
#
def clearDisabledFlag(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasDisabledFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getDisabledFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \param flag 
#
def setDisabledFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief 
# \param feature 
#
def clearOptionalFlag(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasOptionalFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getOptionalFlag(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \param flag 
#
def setOptionalFlag(feature: Feature, flag: bool) -> None: pass

##
# \brief 
# \param feature 
#
def clearLength(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasLength(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getLength(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
# \param length 
#
def setLength(feature: Feature, length: float) -> None: pass

##
# \brief 
# \param feature 
#
def clearOrientation(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasOrientation(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getOrientation(feature: Feature) -> Math.Vector3D: pass

##
# \brief 
# \param feature 
# \param orient 
#
def setOrientation(feature: Feature, orient: Math.Vector3D) -> None: pass

##
# \brief 
# \param feature 
#
def clearWeight(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasWeight(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getWeight(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
# \param weight 
#
def setWeight(feature: Feature, weight: float) -> None: pass

##
# \brief 
# \param feature 
#
def clearGeometry(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasGeometry(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getGeometry(feature: Feature) -> int: pass

##
# \brief 
# \param feature 
# \param geom 
#
def setGeometry(feature: Feature, geom: int) -> None: pass

##
# \brief 
# \param feature 
#
def clearHydrophobicity(feature: Feature) -> None: pass

##
# \brief 
# \param feature 
# \return 
#
def hasHydrophobicity(feature: Feature) -> bool: pass

##
# \brief 
# \param feature 
# \return 
#
def getHydrophobicity(feature: Feature) -> float: pass

##
# \brief 
# \param feature 
# \param hyd 
#
def setHydrophobicity(feature: Feature, hyd: float) -> None: pass
