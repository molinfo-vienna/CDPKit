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
# \brief Sets the value of the GRAIL.AttributedGridProperty.FEATURE_TYPE property of the grid <em>grid</em> to <em>type</em>.
# 
# \param grid The grid for which to set the property value.
# \param type The new feature type value.
# 
def setFeatureType(grid: Grid.AttributedGrid, type: int) -> None: pass

##
# \brief Tells whether the GRAIL.AttributedGridProperty.FEATURE_TYPE property of the grid <em>grid</em> is set.
# 
# \param grid The grid for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasFeatureType(grid: Grid.AttributedGrid) -> bool: pass

##
# \brief Returns the value of the GRAIL.AttributedGridProperty.FEATURE_TYPE property of the grid <em>grid</em>.
# 
# \param grid The grid for which to return the property value.
# 
# \return The feature type value.
# 
def getFeatureType(grid: Grid.AttributedGrid) -> int: pass

##
# \brief Clears the value of the GRAIL.AttributedGridProperty.FEATURE_TYPE property of the grid <em>grid</em>.
# 
# \param grid The grid for which to clear the property value.
# 
def clearFeatureType(grid: Grid.AttributedGrid) -> None: pass

##
# \brief Sets the value of the GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property of the grid <em>grid</em> to <em>type</em>.
# 
# \param grid The grid for which to set the property value.
# \param type The new target feature type value.
# 
def setTargetFeatureType(grid: Grid.AttributedGrid, type: int) -> None: pass

##
# \brief Tells whether the GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property of the grid <em>grid</em> is set.
# 
# \param grid The grid for which to query the property value.
# 
# \return <tt>True</tt> if the property is set, and <tt>False</tt> otherwise.
# 
def hasTargetFeatureType(grid: Grid.AttributedGrid) -> bool: pass

##
# \brief Returns the value of the GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property of the grid <em>grid</em>.
# 
# \param grid The grid for which to return the property value.
# 
# \return The target feature type value.
# 
def getTargetFeatureType(grid: Grid.AttributedGrid) -> int: pass

##
# \brief Clears the value of the GRAIL.AttributedGridProperty.TARGET_FEATURE_TYPE property of the grid <em>grid</em>.
# 
# \param grid The grid for which to clear the property value.
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
# \brief Prepares the molecule <em>mol</em> for GRAIL descriptor calculation.
# 
# Performs all molecular structure preprocessing steps (e.g. ring perception, atom typing, hydrogen handling) required by the descriptor calculation procedure (implemented by GRAIL.GRAILDescriptorCalculator).
# 
# \param mol The molecule to prepare. The molecule is modified in place.
# \param std_prot_state If <tt>True</tt>, the standard protonation state of the molecule is assigned prior to the GRAIL-specific preprocessing.
# 
def prepareForGRAILDescriptorCalculation(mol: Chem.Molecule, std_prot_state: bool = False) -> None: pass
