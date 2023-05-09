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
# \param ctr 
# \return 
#
def calcCentroid(cntnr: Entity3DContainer, ctr: CDPL.Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transform3DCoordinates(cntnr: Entity3DContainer, mtx: CDPL.Math.Matrix4D) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
# \param append 
#
def get3DCoordinates(cntnr: Entity3DContainer, coords: CDPL.Math.Vector3DArray, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
#
def set3DCoordinates(cntnr: Entity3DContainer, coords: CDPL.Math.Vector3DArray) -> None: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def calcGeometricalDistanceMatrix(cntnr: Entity3DContainer, mtx: CDPL.Math.DMatrix) -> None: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param reset 
#
def calcBoundingBox(cntnr: Entity3DContainer, min: CDPL.Math.Vector3D, max: CDPL.Math.Vector3D, reset: bool = True) -> None: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \return 
#
def insideBoundingBox(cntnr: Entity3DContainer, min: CDPL.Math.Vector3D, max: CDPL.Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \return 
#
def intersectsBoundingBox(cntnr: Entity3DContainer, min: CDPL.Math.Vector3D, max: CDPL.Math.Vector3D) -> bool: pass
