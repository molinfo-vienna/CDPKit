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
def clearName(cntnr: FeatureContainer) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def hasName(cntnr: FeatureContainer) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getName(cntnr: FeatureContainer) -> str: pass

##
# \brief 
# \param cntnr 
# \param name 
#
def setName(cntnr: FeatureContainer, name: str) -> None: pass

##
# \brief 
# \param cntnr 
# \param tgt_set 
# \param type 
# \param append 
# \return 
#
def removeFeaturesWithType(cntnr: FeatureContainer, tgt_set: FeatureSet, type: int, append: bool = False) -> bool: pass

##
# \brief 
# \param cntnr 
# \return 
#
def generateFeatureTypeHistogramString(cntnr: FeatureContainer) -> str: pass

##
# \brief 
# \param cntnr 
# \param hist 
# \param append 
#
def generateFeatureTypeHistogram(cntnr: FeatureContainer, hist: FeatureTypeHistogram, append: bool = False) -> None: pass

##
# \brief 
# \param ftr_cntnr 
# \param atom_cntnr 
# \param coords_func 
# \param xform 
# \param vdw_factor 
# \return 
#
def checkForExclusionVolumeClashes(ftr_cntnr: FeatureContainer, atom_cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction, xform: Math.Matrix4D, vdw_factor: float = 1.0) -> bool: pass

##
# \brief 
# \param cntnr 
# \param tgt_set 
# \param pos_tol 
# \param append 
# \return 
#
def removePositionalDuplicates(cntnr: FeatureContainer, tgt_set: FeatureSet, pos_tol: float = 0.0, append: bool = False) -> bool: pass

##
# \brief 
# \param cntnr 
# \param mtx 
#
def transform3DCoordinates(cntnr: FeatureContainer, mtx: Math.Matrix4D) -> None: pass

##
# \brief 
# \param cntnr 
# \param atoms 
# \param append 
#
def getFeatureAtoms(cntnr: FeatureContainer, atoms: Chem.Fragment, append: bool = False) -> None: pass

##
# \brief 
# \param cntnr 
# \param fix_geom 
#
def clearOrientations(cntnr: FeatureContainer, fix_geom: bool = True) -> None: pass

##
# \brief 
# \param cntnr 
# \return 
#
def getFeatureCount(cntnr: FeatureContainer) -> int: pass

##
# \brief 
# \param cntnr 
# \param type 
# \return 
#
def getFeatureCount(cntnr: FeatureContainer, type: int) -> int: pass
