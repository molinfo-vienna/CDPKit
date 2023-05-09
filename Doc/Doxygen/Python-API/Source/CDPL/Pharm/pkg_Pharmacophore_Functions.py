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
# \param pharm 
# \param iactions 
# \param append 
#
def buildInteractionPharmacophore(pharm: Pharmacophore, iactions: FeatureMapping, append: bool = False) -> None: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param coords_func 
# \param vdw_scaling_fact 
# \return 
#
def removeExclusionVolumesWithClashes(pharm: Pharmacophore, cntnr: CDPL.Chem.AtomContainer, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, vdw_scaling_fact: float = 1.0) -> bool: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param coords_func 
# \param vdw_scaling_fact 
# \return 
#
def resizeExclusionVolumesWithClashes(pharm: Pharmacophore, cntnr: CDPL.Chem.AtomContainer, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, vdw_scaling_fact: float = 1.0) -> bool: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param coords_func 
# \param tol 
# \param min_dist 
# \param rel_dist 
# \param append 
#
def createExclusionVolumes(pharm: Pharmacophore, cntnr: CDPL.Chem.AtomContainer, coords_func: CDPL.Chem.Atom3DCoordinatesFunction, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass

##
# \brief 
# \param pharm 
# \param cntnr 
# \param tol 
# \param min_dist 
# \param rel_dist 
# \param append 
#
def createExclusionVolumes(pharm: Pharmacophore, cntnr: FeatureContainer, tol: float = 0.0, min_dist: float = 0.0, rel_dist: bool = True, append: bool = True) -> None: pass
