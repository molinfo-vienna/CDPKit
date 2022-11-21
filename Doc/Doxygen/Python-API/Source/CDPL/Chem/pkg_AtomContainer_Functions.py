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
# \param cntnr 
# \return 
#
def getMaxAtomMappingID(cntnr: AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getMaxComponentGroupID(cntnr: AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \param ctr 
# \return 
#
def calcCentroid(cntnr: AtomContainer, coords_func: Atom3DCoordinatesFunction, ctr: CDPL.Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param mol 
# \param pred 
# \param append 
#
def copyAtomsIf(cntnr: AtomContainer, mol: Molecule, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param frag 
# \param pred 
# \param append 
#
def copyAtomsIf(cntnr: AtomContainer, frag: Fragment, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param mask 
# \param type 
# \param reset 
# \return 
#
def buildAtomTypeMask(cntnr: AtomContainer, mask: CDPL.Util.BitSet, type: int, reset: bool = True) -> int: pass

##
# \brief 
# \param cntnr 
# \param coords 
#
def addConformation(cntnr: AtomContainer, coords: CDPL.Math.Vector3DArray) -> None: pass

##
# \brief 
# \param cntnr 
# \param conf_idx 
# \param mtx 
#
def transformConformation(cntnr: AtomContainer, conf_idx: int, mtx: CDPL.Math.Matrix4D) -> None: pass

##
# \brief 
# \param cntnr 
# \param conf_idx 
# \param coords 
# \param append 
#
def getConformation(cntnr: AtomContainer, conf_idx: int, coords: CDPL.Math.Vector3DArray, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param conf_idx 
#
def applyConformation(cntnr: AtomContainer, conf_idx: int) -> None: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transform2DCoordinates(cntnr: AtomContainer, mtx: CDPL.Math.Matrix3D) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
# \param append 
#
def get2DCoordinates(cntnr: AtomContainer, coords: CDPL.Math.Vector2DArray, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
#
def set2DCoordinates(cntnr: AtomContainer, coords: CDPL.Math.Vector2DArray) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords 
# \param coords_func 
# \param append 
#
def get3DCoordinates(cntnr: AtomContainer, coords: CDPL.Math.Vector3DArray, coords_func: Atom3DCoordinatesFunction, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param dim 
# \return 
#
def hasCoordinates(cntnr: AtomContainer, dim: int) -> bool: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transformConformations(cntnr: AtomContainer, mtx: CDPL.Math.Matrix4D) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getNumConformations(cntnr: AtomContainer) -> int: pass

##
# \brief 
# \param cntnr 
#
def clearConformations(cntnr: AtomContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \param ctr 
# \return 
#
def calcCenterOfMass(cntnr: AtomContainer, coords_func: Atom3DCoordinatesFunction, ctr: CDPL.Math.Vector3D) -> bool: pass

##
# \brief 
# \param cntnr 
# \param mol 
# \param pred 
# \param append 
#
def copyAtomsIfNot(cntnr: AtomContainer, mol: Molecule, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param frag 
# \param pred 
# \param append 
#
def copyAtomsIfNot(cntnr: AtomContainer, frag: Fragment, pred: AtomPredicate, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param coords_func 
# \param reset 
#
def calcBoundingBox(cntnr: AtomContainer, min: CDPL.Math.Vector3D, max: CDPL.Math.Vector3D, coords_func: Atom3DCoordinatesFunction, reset: bool = True) -> None: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param coords_func 
# \return 
#
def insideBoundingBox(cntnr: AtomContainer, min: CDPL.Math.Vector3D, max: CDPL.Math.Vector3D, coords_func: Atom3DCoordinatesFunction) -> bool: pass

##
# \brief 
# \param cntnr 
# \param min 
# \param max 
# \param coords_func 
# \return 
#
def intersectsBoundingBox(cntnr: AtomContainer, min: CDPL.Math.Vector3D, max: CDPL.Math.Vector3D, coords_func: Atom3DCoordinatesFunction) -> bool: pass
