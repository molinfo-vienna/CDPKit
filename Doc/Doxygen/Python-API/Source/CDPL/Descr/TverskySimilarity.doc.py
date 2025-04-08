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
# \brief Functor class for calculating the <em>Tversky Similarity</em> [\ref GSIM] of bitsets.
# 
# \since 1.2.3
# 
class TverskySimilarity(Boost.Python.instance):

    ##
    # \brief Constructor.
    # 
    # \param alpha Weights the contribution of the first bitset.
    # \param beta Weights the contribution of the second bitset.
    # 
    def __init__(alpha: float = 0.95, beta: float = 0.05) -> None: pass

    ##
    # \brief Initializes a copy of the \e %TverskySimilarity instance \a func.
    # \param func The \e %TverskySimilarity instance to copy.
    # 
    def __init__(func: TverskySimilarity) -> None: pass

    ##
    # \brief Returns the numeric identifier (ID) of the wrapped C++ class instance.
    # 
    # Different Python \c %TverskySimilarity instances may reference the same underlying C++ class instance. The commonly used Python expression
    # <tt>a is not b</tt> thus cannot tell reliably whether the two \c %TverskySimilarity instances \e a and \e b reference different C++ objects. 
    # The numeric identifier returned by this method allows to correctly implement such an identity test via the simple expression
    # <tt>a.getObjectID() != b.getObjectID()</tt>.
    # 
    # \return The numeric ID of the internally referenced C++ class instance.
    # 
    def getObjectID() -> int: pass

    ##
    # \brief Replaces the current state of \a self with a copy of the state of the \c %TverskySimilarity instance \a func.
    # \param func The \c %TverskySimilarity instance to copy.
    # \return \a self
    # 
    def assign(func: TverskySimilarity) -> TverskySimilarity: pass

    ##
    # \brief Calculates the <em>Tversky Similarity</em> [\ref GSIM] of the bitsets <em>bs1</em> and <em>bs2</em>.
    # 
    # The <em>Tversky Similarity</em> \f$ S_{ab} \f$ is calculated by:
    # 
    # \[ S_{ab} = \frac{N_{ab}}{\alpha * N_a + \beta * N_b + N_{ab}} \]
    # 
    # where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of bits that are only set in the first bitset and \f$ N_b \f$ is the number of bits that are only set in the second bitset. \f$ \alpha \f$ and \f$ \beta \f$ are bitset contribution weighting factors.
    # 
    # The <em>Tversky</em> measure is asymmetric. Setting the parameters \f$ \alpha = \beta = 1.0 \f$ makes it identical to the <em>Tanimoto</em> measure.
    # 
    # If the specified bitsets <em>bs1</em> and <em>bs2</em> are of different size, missing bits at the end of the smaller bitset are assumed to be zero.
    # 
    # \param bs1 The first bitset.
    # \param bs2 The second bitset.
    # 
    # \return The calculated similarity measure. 
    # 
    # \see TverskySimilarity.TverskySimilarity()
    # 
    def __call__(bs1: Util.BitSet, bs2: Util.BitSet) -> float: pass

    objectID = property(getObjectID)
