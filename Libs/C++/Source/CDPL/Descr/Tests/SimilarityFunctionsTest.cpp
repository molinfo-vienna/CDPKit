/* 
 * SimilarityFunctionsTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <cmath>

#include <boost/lexical_cast.hpp>
#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Descr/SimilarityFunctions.hpp"
#include "CDPL/Util/BitSet.hpp"


BOOST_AUTO_TEST_CASE(SimilarityFunctionsTest)
{
    using namespace CDPL;
    using namespace Descr;
    using namespace Util;
    
    BitSet bs1 = boost::lexical_cast<BitSet>("1001000011101010111010110100110");
    BitSet bs2 = boost::lexical_cast<BitSet>("000000111011110100110111101111100010");

    BOOST_CHECK(std::isnan(calcTanimotoSimilarity(BitSet(), BitSet())));
    BOOST_CHECK(std::isnan(calcTanimotoSimilarity(boost::lexical_cast<BitSet>("00000"), boost::lexical_cast<BitSet>("00000"))));

    BOOST_CHECK(std::isnan(calcTanimotoSimilarity(BitSet(), boost::lexical_cast<BitSet>("00000"))));
    BOOST_CHECK(std::isnan(calcTanimotoSimilarity(boost::lexical_cast<BitSet>("00000"), BitSet())));

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs1, BitSet()), 0.0);
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(BitSet(), bs1), 0.0);

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs2, BitSet()), 0.0);
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(BitSet(), bs2), 0.0);

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs1, boost::lexical_cast<BitSet>("00000")), 0.0);
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(boost::lexical_cast<BitSet>("00000"), bs1), 0.0);

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs2, boost::lexical_cast<BitSet>("00000")), 0.0);
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(boost::lexical_cast<BitSet>("00000"), bs2), 0.0);

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs1, bs2), 11.0 / (16 + 20 - 11));
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs2, bs1), 11.0 / (16 + 20 - 11));

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs1, bs1), 1.0);
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs2, bs2), 1.0);

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(BitSet(bs1), bs1), 1.0);
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs2, BitSet(bs2)), 1.0);

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(bs1, BitSet(bs1)), 1.0);
    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(BitSet(bs2), bs2), 1.0);

//-----

    BOOST_CHECK_EQUAL(calcHammingDistance(BitSet(), BitSet()), 0);
    BOOST_CHECK_EQUAL(calcHammingDistance(boost::lexical_cast<BitSet>("00000"), boost::lexical_cast<BitSet>("00000")), 0);

    BOOST_CHECK_EQUAL(calcHammingDistance(BitSet(), boost::lexical_cast<BitSet>("00000")), 0);
    BOOST_CHECK_EQUAL(calcHammingDistance(boost::lexical_cast<BitSet>("00000"), BitSet()), 0);

    BOOST_CHECK_EQUAL(calcHammingDistance(BitSet(), boost::lexical_cast<BitSet>("111111")), 6);
    BOOST_CHECK_EQUAL(calcHammingDistance(boost::lexical_cast<BitSet>("111111"), BitSet()), 6);

    BOOST_CHECK_EQUAL(calcHammingDistance(bs1, BitSet()), 16);
    BOOST_CHECK_EQUAL(calcHammingDistance(BitSet(), bs1), 16);

    BOOST_CHECK_EQUAL(calcHammingDistance(bs2, BitSet()), 20);
    BOOST_CHECK_EQUAL(calcHammingDistance(BitSet(), bs2), 20);

    BOOST_CHECK_EQUAL(calcHammingDistance(bs1, boost::lexical_cast<BitSet>("00000")), 16);
    BOOST_CHECK_EQUAL(calcHammingDistance(boost::lexical_cast<BitSet>("00000"), bs1), 16);

    BOOST_CHECK_EQUAL(calcHammingDistance(bs2, boost::lexical_cast<BitSet>("00000")), 20);
    BOOST_CHECK_EQUAL(calcHammingDistance(boost::lexical_cast<BitSet>("00000"), bs2), 20);

    BOOST_CHECK_EQUAL(calcHammingDistance(bs1, bs2), 14);
    BOOST_CHECK_EQUAL(calcHammingDistance(bs2, bs1), 14);

    BOOST_CHECK_EQUAL(calcHammingDistance(bs1, bs1), 0);
    BOOST_CHECK_EQUAL(calcHammingDistance(bs2, bs2), 0);

    BOOST_CHECK_EQUAL(calcHammingDistance(BitSet(bs1), bs1), 0);
    BOOST_CHECK_EQUAL(calcHammingDistance(bs2, BitSet(bs2)), 0);

    BOOST_CHECK_EQUAL(calcHammingDistance(bs1, BitSet(bs1)), 0);
    BOOST_CHECK_EQUAL(calcHammingDistance(BitSet(bs2), bs2), 0);

//-----

    BOOST_CHECK_EQUAL(calcEuclideanDistance(BitSet(), BitSet()), 0.0);
    BOOST_CHECK_EQUAL(calcEuclideanDistance(boost::lexical_cast<BitSet>("00000"), boost::lexical_cast<BitSet>("00000")), 0.0);

    BOOST_CHECK_EQUAL(calcEuclideanDistance(BitSet(), boost::lexical_cast<BitSet>("00000")), 0.0);
    BOOST_CHECK_EQUAL(calcEuclideanDistance(boost::lexical_cast<BitSet>("00000"), BitSet()), 0.0);

    BOOST_CHECK_EQUAL(calcEuclideanDistance(BitSet(), boost::lexical_cast<BitSet>("111111")), std::sqrt(6.0));
    BOOST_CHECK_EQUAL(calcEuclideanDistance(boost::lexical_cast<BitSet>("111111"), BitSet()), std::sqrt(6.0));

    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs1, BitSet()), 4.0);
    BOOST_CHECK_EQUAL(calcEuclideanDistance(BitSet(), bs1), 4.0);

    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs2, BitSet()), std::sqrt(20.0));
    BOOST_CHECK_EQUAL(calcEuclideanDistance(BitSet(), bs2), std::sqrt(20.0));

    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs1, boost::lexical_cast<BitSet>("00000")), 4.0);
    BOOST_CHECK_EQUAL(calcEuclideanDistance(boost::lexical_cast<BitSet>("00000"), bs1), 4.0);

    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs2, boost::lexical_cast<BitSet>("00000")), std::sqrt(20.0));
    BOOST_CHECK_EQUAL(calcEuclideanDistance(boost::lexical_cast<BitSet>("00000"), bs2), std::sqrt(20.0));

    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs1, bs2), std::sqrt(14.0));
    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs2, bs1), std::sqrt(14.0));

    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs1, bs1), 0.0);
    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs2, bs2), 0.0);

    BOOST_CHECK_EQUAL(calcEuclideanDistance(BitSet(bs1), bs1), 0.0);
    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs2, BitSet(bs2)), 0.0);

    BOOST_CHECK_EQUAL(calcEuclideanDistance(bs1, BitSet(bs1)), 0.0);
    BOOST_CHECK_EQUAL(calcEuclideanDistance(BitSet(bs2), bs2), 0.0);

//-----

    BOOST_CHECK_CLOSE(calcCosineSimilarity(boost::lexical_cast<BitSet>("10111000"), boost::lexical_cast<BitSet>("11011010")), 0.67, 0.3);

//-----

    BOOST_CHECK_CLOSE(calcDiceSimilarity(boost::lexical_cast<BitSet>("10111000"), boost::lexical_cast<BitSet>("11011010")), 0.666, 0.11);

//-----

    BOOST_CHECK_CLOSE(calcEuclideanSimilarity(boost::lexical_cast<BitSet>("10111000"), boost::lexical_cast<BitSet>("11011010")), 0.791, 0.1);

//-----

    BOOST_CHECK_EQUAL(calcManhattanSimilarity(boost::lexical_cast<BitSet>("10111000"), boost::lexical_cast<BitSet>("11011010")), 1.0 - 0.375);

//-----

    BOOST_CHECK_EQUAL(calcTanimotoSimilarity(boost::lexical_cast<BitSet>("10111000"), boost::lexical_cast<BitSet>("11011010")), 0.5);

//-----

    BOOST_CHECK_EQUAL(calcTverskySimilarity(boost::lexical_cast<BitSet>("10111000"), boost::lexical_cast<BitSet>("11011010"), 1.0, 1.0), 0.5);

}
