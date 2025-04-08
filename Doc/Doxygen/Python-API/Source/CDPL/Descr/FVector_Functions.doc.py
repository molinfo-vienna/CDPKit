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
# \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Euclidean Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \[ D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|} \]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcEuclideanDistance(v1: Math.FVector, v2: Math.FVector) -> float: pass

##
# \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \[ D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1 \]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcManhattanDistance(v1: Math.FVector, v2: Math.FVector) -> float: pass

##
# \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Cosine Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \[ S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}{\left \| \vec{v}_2 \right \|}} \]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcCosineSimilarity(v1: Math.FVector, v2: Math.FVector) -> float: pass

##
# \brief Calculates the <em>Tanimoto Similarity</em> [\ref CITB] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Tanimoto Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \[ S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}^2 + {\left \| \vec{v}_2 \right \|}^2 - \vec{v}_1 \cdot \vec{v}_2} \]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcTanimotoSimilarity(v1: Math.FVector, v2: Math.FVector) -> float: pass
