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
# \brief Sets the value of the GRAIL.AttributedGridProperty.FEATURE_TYPE property of <em>grid</em>.
# 
# \param grid The grid whose feature type to set.
# \param type The new feature type value.
# 
def setFeatureType(grid: Grid.AttributedGrid, type: int) -> None: pass

##
# \brief Tells whether <em>grid</em> carries an explicit GRAIL.AttributedGridProperty.FEATURE_TYPE property.
# 
# \param grid The grid to query.
# 
# \return <tt>True</tt> if the property is set on the grid, and <tt>False</tt> otherwise.
# 
def hasFeatureType(grid: Grid.AttributedGrid) -> bool: pass

##
# \brief Returns the value of the GRAIL.AttributedGridProperty.FEATURE_TYPE property of <em>grid</em>.
# 
# \param grid The grid whose feature type is requested.
# 
# \return The feature type value.
# 
def getFeatureType(grid: Grid.AttributedGrid) -> int: pass

##
# \brief Removes the GRAIL.AttributedGridProperty.FEATURE_TYPE property from <em>grid</em>.
# 
# \param grid The grid to clear the property from.
# 
def clearFeatureType(grid: Grid.AttributedGrid) -> None: pass

##
# \brief Sets the value of the GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property of <em>grid</em>.
# 
# \param grid The grid whose target feature type to set.
# \param type The new target feature type value.
# 
def setTargetFeatureType(grid: Grid.AttributedGrid, type: int) -> None: pass

##
# \brief Tells whether <em>grid</em> carries an explicit GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property.
# 
# \param grid The grid to query.
# 
# \return <tt>True</tt> if the property is set on the grid, and <tt>False</tt> otherwise.
# 
def hasTargetFeatureType(grid: Grid.AttributedGrid) -> bool: pass

##
# \brief Returns the value of the GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property of <em>grid</em>.
# 
# \param grid The grid whose target feature type is requested.
# 
# \return The target feature type value.
# 
def getTargetFeatureType(grid: Grid.AttributedGrid) -> int: pass

##
# \brief Removes the GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property from <em>grid</em>.
# 
# \param grid The grid to clear the property from.
# 
def clearTargetFeatureType(grid: Grid.AttributedGrid) -> None: pass

##
# \brief 
# \param feature 
# \param ligand 
# \return 
#
def perceiveExtendedType(feature: Pharm.Feature, ligand: bool) -> int: pass

##
# \brief Prepares a molecule for GRAIL descriptor calculation.
# 
# Performs the pre-processing steps (e.g. ring perception, atom typing, hydrogen handling) required by GRAIL.GRAILDescriptorCalculator on the molecular structure.
# 
# \param mol The molecule to prepare. The molecule is modified in place.
# \param std_prot_state If <tt>True</tt>, the standard protonation state of the molecule is assigned prior to the GRAIL-specific pre-processing.
# 
def prepareForGRAILDescriptorCalculation(mol: Chem.Molecule, std_prot_state: bool = False) -> None: pass
