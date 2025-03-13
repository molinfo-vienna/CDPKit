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
# \brief Functor class for calculating <em>Cosine Similarities</em> [\ref WCOS] of bitsets and vectors.
# 
class CosineSimilarity(Boost.Python.instance):

    ##
    # \brief Initializes the \e %CosineSimilarity instance.
    # 
    def __init__() -> None: pass

    ##
    # \brief Initializes a copy of the \e %CosineSimilarity instance \a func.
    # \param func The \e %CosineSimilarity instance to copy.
    # 
    def __init__(func: CosineSimilarity) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %CosineSimilarity instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %CosineSimilarity instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %CosineSimilarity instance \a func.
    # \param func The \c %CosineSimilarity instance to copy.
    # \return \a self
    # 
    def assign(func: CosineSimilarity) -> CosineSimilarity: pass

    ##
    # \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the bitsets <em>bs1</em> and <em>bs2</em>.
    # 
    # The <em>Cosine Similarity</em> \f$ S_{ab} \f$ is calculated by:
    # 
    # \[ S_{ab} = \frac{N_{ab}}{\sqrt{N_a * N_b}} \]
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
    def __call__(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

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
    def __call__(v1: Math.FVector, v2: Math.FVector) -> float: pass

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
    def __call__(v1: Math.DVector, v2: Math.DVector) -> float: pass

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
    def __call__(v1: Math.LVector, v2: Math.LVector) -> float: pass

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
    def __call__(v1: Math.ULVector, v2: Math.ULVector) -> float: pass

    objectID = property(getObjectID)
