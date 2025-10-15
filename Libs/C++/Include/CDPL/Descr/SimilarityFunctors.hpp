/* 
 * SimilarityFunctors.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/**
 * \file
 * \brief Definition of functor classes for the calculation of various similarity and distance measures.
 */

#ifndef CDPL_DESCR_SIMILARITYFUNCTORS_HPP
#define CDPL_DESCR_SIMILARITYFUNCTORS_HPP

#include "CDPL/Descr/SimilarityFunctions.hpp"


namespace CDPL
{

    namespace Descr
    {

        /**
         * \brief Functor class for calculating <em>Tanimoto Similarities</em> [\ref CITB] of bitsets and vectors.
         * \since 1.2.3
         */
        class TanimotoSimilarity
        {

          public:
            /**
             * \brief Calculates the <em>Tanimoto Similarity</em> of the bitsets \a bs1 and \a bs2.
             *
             * The <em>Tanimoto Similarity</em> \f$ S_{ab} \f$ is calculated by:
             *
             * \f[ 
             *    S_{ab} = \frac{N_{ab}}{N_a + N_b - N_{ab}} 
             * \f] 
             *
             * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
             * bits that are set in the first bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset.
             * 
             * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
             * to be zero.
             *
             * \param bs1 The first bitset.
             * \param bs2 The second bitset.
             * \return The calculated similarity measure.
             */
            double operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
            {
                return calcTanimotoSimilarity(bs1, bs2);
            }

            /**
             * \brief Calculates the <em>Tanimoto Similarity</em> of the vectors \a v1 and \a v2.
             *
             * The <em>Tanimoto Similarity</em> \f$ S_{12} \f$ is calculated by:
             *
             * \f[ 
             *    S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}^2 + {\left \| \vec{v}_2 \right \|}^2 - \vec{v}_1 \cdot \vec{v}_2} 
             * \f] 
             * 
             * \param v1 The first vector.
             * \param v2 The second vector.
             * \return The calculated similarity measure.
             */
            template <typename V>
            double operator()(const V& v1, const V& v2) const
            {
                return calcTanimotoSimilarity(v1, v2);
            }
        };

        /**
         * \brief Functor class for calculating <em>Cosine Similarities</em> [\ref WCOS] of bitsets and vectors.
         * \since 1.2.3
         */
        class CosineSimilarity
        {

          public:
            /**
             * \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the bitsets \a bs1 and \a bs2.
             *
             * The <em>Cosine Similarity</em> \f$ S_{ab} \f$ is calculated by:
             *
             * \f[ 
             *    S_{ab} = \frac{N_{ab}}{\sqrt{N_a * N_b}} 
             * \f] 
             *
             * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
             * bits that are set in the first bitset and \f$ N_b \f$ is the number of bits that are set in the second bitset.
             * 
             * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
             * to be zero.
             *
             * \param bs1 The first bitset.
             * \param bs2 The second bitset.
             * \return The calculated similarity measure.
             */
            double operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
            {
                return calcCosineSimilarity(bs1, bs2);
            }

            /**
             * \brief Calculates the <em>Cosine Similarity</em> [\ref WCOS] of the vectors \a v1 and \a v2.
             *
             * The <em>Cosine Similarity</em>\f$ S_{12} \f$ is calculated by:
             *
             * \f[ 
             *    S_{12} = \frac{\vec{v}_1 \cdot \vec{v}_2}{{\left \| \vec{v}_1 \right \|}{\left \| \vec{v}_2 \right \|}} 
             * \f] 
             * 
             * \param v1 The first vector.
             * \param v2 The second vector.
             * \return The calculated similarity measure.
             */
            template <typename V>
            double operator()(const V& v1, const V& v2) const
            {
                return calcCosineSimilarity(v1, v2);
            }
        };

        /**
         * \brief Functor class for calculating the <em>Euclidean Similarity</em> [\ref GSIM] of bitsets.
         * \since 1.2.3
         */
        class EuclideanSimilarity
        {

          public:
            /**
             * \brief Calculates the <em>Euclidean Similarity</em> [\ref GSIM] of the bitsets \a bs1 and \a bs2.
             *
             * The <em>Euclidean Similarity</em> \f$ S_{ab} \f$ is calculated by:
             *
             * \f[ 
             *    S_{ab} = 1 - \sqrt{\frac{N_{ab} + N_{!ab}}{N_a + N_b + N_{ab} + N_{!ab}}}
             * \f] 
             *
             * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
             * bits that are set only in the first bitset, \f$ N_b \f$ is the number of bits that are set only in the second bitset and
             * \f$ N_{!ab} \f$ is the number of bits that are not set in both bitsets.
             * 
             * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
             * to be zero.
             *
             * \param bs1 The first bitset.
             * \param bs2 The second bitset.
             * \return The calculated similarity measure.
             */
            double operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
            {
                return calcEuclideanSimilarity(bs1, bs2);
            }
        };

        /**
         * \brief Functor class for calculating the <em>Manhattan Similarity</em> [\ref GSIM] of bitsets.
         * \since 1.2.3
         */
        class ManhattanSimilarity
        {

          public:
              /**
               * \brief Calculates the <em>Manhattan Similarity</em> [\ref GSIM] of the bitsets \a bs1 and \a bs2.
               *
               * The <em>Manhattan Similarity</em> \f$ S_{ab} \f$ is calculated by:
               *
               * \f[ 
               *    S_{ab} = 1 - \frac{N_a + N_b}{N_a + N_b + N_{ab} + N_{!ab}}
               * \f] 
               *
               * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
               * bits that are set only in the first bitset, \f$ N_b \f$ is the number of bits that are set only in the second bitset and
               * \f$ N_{!ab} \f$ is the number of bits that are not set in both bitsets.
               * 
               * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
               * to be zero.
               *
               * \param bs1 The first bitset.
               * \param bs2 The second bitset.
               * \return The calculated similarity measure.
               */
            double operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
            {
                return calcManhattanSimilarity(bs1, bs2);
            }
        };

        /**
         * \brief Functor class for calculating the <em>Dice Similarity</em> [\ref GSIM] of bitsets.
         * \since 1.2.3
         */
        class DiceSimilarity
        {

          public:
            /**
             * \brief Calculates the <em>Dice Similarity</em> [\ref GSIM] of the bitsets \a bs1 and \a bs2.
             *
             * The <em>Dice Similarity</em> \f$ S_{ab} \f$ is calculated by:
             *
             * \f[ 
             *    S_{ab} = \frac{2 * N_{ab}}{N_a + N_b + 2 * N_{ab}} 
             * \f] 
             *
             * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
             * bits that are only set in the first bitset and \f$ N_b \f$ is the number of bits that are only set in the second bitset.
             * 
             * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
             * to be zero.
             *
             * \param bs1 The first bitset.
             * \param bs2 The second bitset.
             * \return The calculated similarity measure.
             */
             double operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
             {
                return calcDiceSimilarity(bs1, bs2);
            }
        };

        /**
         * \brief Functor class for calculating the <em>Tversky Similarity</em> [\ref GSIM] of bitsets.
         * \since 1.2.3
         */
        class TverskySimilarity
        {

          public:
            /** 
             * \brief Constructor.
             * \param alpha Weights the contribution of the first bitset.
             * \param beta Weights the contribution of the second bitset.
             */
            TverskySimilarity(double alpha = 0.95, double beta = 0.05):
                alpha(alpha), beta(beta) {}

            /**
             * \brief Calculates the <em>Tversky Similarity</em> [\ref GSIM] of the bitsets \a bs1 and \a bs2.
             *
             * The <em>Tversky Similarity</em> \f$ S_{ab} \f$ is calculated by:
             *
             * \f[ 
             *    S_{ab} = \frac{N_{ab}}{\alpha * N_a + \beta * N_b + N_{ab}} 
             * \f] 
             *
             * where \f$ N_{ab} \f$ is the number of bits that are set in both bitsets, \f$ N_a \f$ is the number of
             * bits that are only set in the first bitset and \f$ N_b \f$ is the number of bits that are only set in the second bitset.
             * \f$ \alpha \f$ and \f$ \beta \f$ are bitset contribution weighting factors. 
             *
             * The <em>Tversky</em> measure is asymmetric. Setting the parameters \f$ \alpha = \beta = 1.0 \f$ makes it identical to the <em>Tanimoto</em> measure.
             *
             * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
             * to be zero.
             *
             * \param bs1 The first bitset.
             * \param bs2 The second bitset.
             * \return The calculated similarity measure.
             * \see TverskySimilarity::TverskySimilarity()
             */
            double operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
            {
                return calcTverskySimilarity(bs1, bs2, alpha, beta);
            }

          private:
            double alpha;
            double beta;
        };

        /**
         * \brief Functor class for calculating the <em>Hamming Distance</em> [\ref WHAM, \ref CITB] between bitsets.
         * \since 1.2.3
         */
        class HammingDistance
        {

          public:
            /**
             * \brief Calculates the <em>Hamming Distance</em> [\ref WHAM, \ref CITB] between the bitsets \a bs1 and \a bs2.
             *
             * The <em>Hamming Distance</em> \f$ D_{ab} \f$ is calculated by:
             *
             * \f[ 
             *    D_{ab} = N_a + N_b
             * \f] 
             *
             * where \f$ N_a \f$ is the number of bits that are set in the first bitset but not in the second bitset
             * and \f$ N_b \f$ is the number of bits that are set in the second bitset but not in the first one.
             * 
             * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
             * to be zero.
             *
             * \param bs1 The first bitset.
             * \param bs2 The second bitset.
             * \return The calculated distance.
             */
            std::size_t operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
            {
                return calcHammingDistance(bs1, bs2);
            }
        };

        /**
         * \brief Functor class for calculating the <em>Manhattan Distance</em> [\ref MADI] between bitsets and vectors.
         * \since 1.2.3
         */
        class ManhattanDistance
        {

          public:
            /**
             * \brief Calculates the <em>Manhattan Distance</em> [\ref MADI] between the vectors \a v1 and \a v2.
             *
             * The <em>Manhattan Distance</em>\f$ D_{12} \f$ is calculated by:
             *
             * \f[ 
             *    D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}_1
             * \f] 
             * 
             * \param v1 The first vector.
             * \param v2 The second vector.
             * \return The calculated distance measure.
             */
            template <typename V>
            double operator()(const V& v1, const V& v2) const
            {
                return calcManhattanDistance(v1, v2);
            }
        };

        /**
         * \brief Functor class for calculating the <em>Euclidean Distance</em> [\ref CITB] between bitsets and vectors.
         * \since 1.2.3
         */
        class EuclideanDistance
        {

          public:
            /**
             * \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the bitsets \a bs1 and \a bs2.
             *
             * The <em>Euclidean Distance</em> \f$ D_{ab} \f$ is calculated by:
             *
             * \f[ 
             *    D_{ab} = \sqrt{N_a + N_b}
             * \f] 
             *
             * where \f$ N_a \f$ is the number of bits that are set in the first bitset but not in the second bitset
             * and \f$ N_b \f$ is the number of bits that are set in the second bitset but not in the first one.
             * 
             * If the specified bitsets \a bs1 and \a bs2 are of different size, missing bits at the end of the smaller bitset are assumed
             * to be zero.
             *
             * \param bs1 The first bitset.
             * \param bs2 The second bitset.
             * \return The calculated distance.
             */
            double operator()(const Util::BitSet& bs1, const Util::BitSet& bs2) const
            {
                return calcEuclideanDistance(bs1, bs2);
            }

            /**
             * \brief Calculates the <em>Euclidean Distance</em> [\ref CITB] between the vectors \a v1 and \a v2.
             *
             * The <em>Euclidean Distance</em>\f$ D_{12} \f$ is calculated by:
             *
             * \f[ 
             *    D_{12} = {\left \| \vec{v}_1 - \vec{v}_2 \right \|}
             * \f] 
             * 
             * \param v1 The first vector.
             * \param v2 The second vector.
             * \return The calculated distance measure.
             */
            template <typename V>
            double operator()(const V& v1, const V& v2) const
            {
                return calcEuclideanDistance(v1, v2);
            }
        };
        
    } // namespace Descr
} // namespace CDPL

#endif // CDPL_DESCR_SIMILARITYFUNCTORS_HPP
