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
# \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Cosine Similarity</em> \f$ S_{ab} \f$ is calculated by:
# 
# \f[   S_{ab} = \frac{N_{ab}}{\sqrt{N_a * N_b}} 
# \f]
# 
# where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of bits that are set in the first bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# 
# \return The calculated similarity measure.
# 
def calcCosineSimilarity(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

##
# \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Cosine Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}{\left \| \vec{v}_2 \right \|}} 
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcCosineSimilarity(v1: Math.DVector, v2: Math.DVector) -> float: pass

##
# \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Cosine Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}{\left \| \vec{v}_2 \right \|}} 
# \f]
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
# \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Cosine Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}{\left \| \vec{v}_2 \right \|}} 
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcCosineSimilarity(v1: Math.LVector, v2: Math.LVector) -> float: pass

##
# \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Cosine Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}{\left \| \vec{v}_2 \right \|}} 
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcCosineSimilarity(v1: Math.ULVector, v2: Math.ULVector) -> float: pass

##
# \brief Calculates the <em>Dice Similarity</em> [\ref GSIM] of the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Dice Similarity</em> \f$ S_{ab} \f$ is calculated by:
# 
# \f[   S_{ab} = \frac{2 * N_{ab}}{N_a + N_b + 2 * N_{ab}} 
# \f]
# 
# where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of bits that are only set in the first bitset and \f$ N_b \f$ is the number of bits that are only set in the second bitset.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# 
# \return The calculated similarity measure.
# 
def calcDiceSimilarity(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

##
# \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Euclidean Distance</em> \f$ D_{ab} \f$ is calculated by:
# 
# \f[   D_{ab} = \sqrt{N_a + N_b}
# \f]
# 
# where \f$ N_a \f$ is the number of bits that are set in the first bitset but not in the second bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset but not in the first one.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# 
# \return The calculated distance.
# 
def calcEuclideanDistance(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

##
# \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Euclidean Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcEuclideanDistance(v1: Math.DVector, v2: Math.DVector) -> float: pass

##
# \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Euclidean Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}
# \f]
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
# \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Euclidean Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcEuclideanDistance(v1: Math.LVector, v2: Math.LVector) -> float: pass

##
# \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Euclidean Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcEuclideanDistance(v1: Math.ULVector, v2: Math.ULVector) -> float: pass

##
# \brief Calculates the <em>Euclidean Similarity</em> [\ref GSIM] of the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Euclidean Similarity</em> \f$ S_{ab} \f$ is calculated by:
# 
# \f[   S_{ab} = \sqrt{\frac{N_{ab} + N_{!ab}}{N_a + N_b + N_{ab} + N_{!ab}}}
# \f]
# 
# where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of bits that are set only in the first bitset, \f$ N_b \f$ is the number of bits that are set only in the second bitset and \f$ N_{!ab} \f$ is the number of bits that are not set in both bitsets.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# 
# \return The calculated similarity measure.
# 
def calcEuclideanSimilarity(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \return 
#
def calcGeometricalDiameter(cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction) -> float: pass

##
# \brief 
# \param cntnr 
# \return 
#
def calcGeometricalDiameter(cntnr: Chem.Entity3DContainer) -> float: pass

##
# \brief 
# \param cntnr 
# \param coords_func 
# \return 
#
def calcGeometricalRadius(cntnr: Chem.AtomContainer, coords_func: Chem.Atom3DCoordinatesFunction) -> float: pass

##
# \brief 
# \param cntnr 
# \return 
#
def calcGeometricalRadius(cntnr: Chem.Entity3DContainer) -> float: pass

##
# \brief Calculates the <em>Hamming Distance</em> [\ref WHAM, \ref CITB] between the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Hamming Distance</em> \f$ D_{ab} \f$ is calculated by:
# 
# \f[   D_{ab} = N_a + N_b
# \f]
# 
# where \f$ N_a \f$ is the number of bits that are set in the first bitset but not in the second bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset but not in the first one.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# 
# \return The calculated distance.
# 
def calcHammingDistance(bs1: Util.BitSet, bs2: Util.BitSet) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcKierShape1(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcKierShape2(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcKierShape3(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcManhattanDistance(v1: Math.DVector, v2: Math.DVector) -> float: pass

##
# \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1
# \f]
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
# \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcManhattanDistance(v1: Math.LVector, v2: Math.LVector) -> float: pass

##
# \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Manhattan Distance</em> \f$ D_{12} \f$ is calculated by:
# 
# \f[   D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated distance measure. 
# 
# \since 1.2.3
# 
def calcManhattanDistance(v1: Math.ULVector, v2: Math.ULVector) -> float: pass

##
# \brief Calculates the <em>Manhattan Similarity</em> [\ref GSIM] of the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Manhattan Similarity</em> \f$ S_{ab} \f$ is calculated by:
# 
# \f[   S_{ab} = 1 - \frac{N_a + N_b}{N_a + N_b + N_{ab} + N_{!ab}}
# \f]
# 
# where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of bits that are set only in the first bitset, \f$ N_b \f$ is the number of bits that are set only in the second bitset and \f$ N_{!ab} \f$ is the number of bits that are not set in both bitsets.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# 
# \return The calculated similarity measure.
# 
def calcManhattanSimilarity(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcMolecularComplexity(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcRandicIndex(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcRingComplexity(molgraph: Chem.MolecularGraph) -> float: pass

##
# \brief Calculates the <em>Tanimoto Similarity</em> [\ref CITB] of the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Tanimoto Similarity</em> \f$ S_{ab} \f$ is calculated by:
# 
# \f[   S_{ab} = \frac{N_{ab}}{N_a + N_b - N_{ab}} 
# \f]
# 
# where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of bits that are set in the first bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# 
# \return The calculated similarity measure.
# 
def calcTanimotoSimilarity(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

##
# \brief Calculates the <em>Tanimoto Similarity</em> [\ref CITB] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Tanimoto Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}^2 + {\left \| \vec{v}_2 \right \|}^2 - \vec{v}_1 \cdot \vec{v}_2} 
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcTanimotoSimilarity(v1: Math.DVector, v2: Math.DVector) -> float: pass

##
# \brief Calculates the <em>Tanimoto Similarity</em> [\ref CITB] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Tanimoto Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}^2 + {\left \| \vec{v}_2 \right \|}^2 - \vec{v}_1 \cdot \vec{v}_2} 
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcTanimotoSimilarity(v1: Math.FVector, v2: Math.FVector) -> float: pass

##
# \brief Calculates the <em>Tanimoto Similarity</em> [\ref CITB] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Tanimoto Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}^2 + {\left \| \vec{v}_2 \right \|}^2 - \vec{v}_1 \cdot \vec{v}_2} 
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcTanimotoSimilarity(v1: Math.LVector, v2: Math.LVector) -> float: pass

##
# \brief Calculates the <em>Tanimoto Similarity</em> [\ref CITB] of the vectors <em>v1</em> and <em>v2</em>.
# 
# The <em>Tanimoto Similarity</em> \f$ S_{12} \f$ is calculated by:
# 
# \f[   S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}^2 + {\left \| \vec{v}_2 \right \|}^2 - \vec{v}_1 \cdot \vec{v}_2} 
# \f]
# 
# \param v1 The first vector.
# \param v2 The second vector.
# 
# \return The calculated similarity measure. 
# 
# \since 1.2.3
# 
def calcTanimotoSimilarity(v1: Math.ULVector, v2: Math.ULVector) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcTopologicalDiameter(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcTopologicalRadius(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcTotalWalkCount(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief Calculates the <em>Tversky Similarity</em> [\ref GSIM] of the bitsets <em>bs1</em> and <em>bs2</em>.
# 
# The <em>Tversky Similarity</em> \f$ S_{ab} \f$ is calculated by:
# 
# \f[   S_{ab} = \frac{N_{ab}}{a * N_a + b * N_b + N_{ab}} 
# \f]
# 
# where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of bits that are only set in the first bitset and \f$ N_b \f$ is the number of bits that are only set in the second bitset. \f$ a \f$ and \f$ b \f$ are bitset contribution weighting factors.
# 
# The <em>Tversky</em> measure is asymmetric. Setting the parameters \f$ a = b = 1.0 \f$ makes it identical to the <em>Tanimoto</em> measure.
# 
# If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
# 
# \param bs1 The first bitset.
# \param bs2 The second bitset.
# \param a Weights the contribution of the first bitset.
# \param b Weights the contribution of the second bitset.
# 
# \return The calculated similarity measure.
# 
def calcTverskySimilarity(bs1: Util.BitSet, bs2: Util.BitSet, a: float, b: float) -> float: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcWienerIndex(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcZagrebIndex1(molgraph: Chem.MolecularGraph) -> int: pass

##
# \brief 
# \param molgraph 
# \return 
#
def calcZagrebIndex2(molgraph: Chem.MolecularGraph) -> int: pass
