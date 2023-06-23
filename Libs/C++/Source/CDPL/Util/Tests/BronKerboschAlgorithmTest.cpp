/* 
 * BronKerboschAlgorithmTest.cpp 
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Util/BronKerboschAlgorithm.hpp"


namespace
{
    void createAdjMatrix(std::size_t dim, CDPL::Util::BitSetArray& adj_mtx)
    {
        adj_mtx.clear();
        
        for (std::size_t i = 0; i < dim; i++) 
            adj_mtx.addElement(CDPL::Util::BitSet(dim, false));
    }

    void createClique(std::size_t from, std::size_t to, CDPL::Util::BitSetArray& adj_mtx)
    {
        for (std::size_t i = from; i < to; i++) 
            for (std::size_t j = from; j < to; j++)
                if (i != j)
                    adj_mtx[i].set(j);
    }

    void connect(std::size_t i, std::size_t j, CDPL::Util::BitSetArray& adj_mtx)
    {
        adj_mtx[i].set(j);
        adj_mtx[j].set(i);
    }
}


BOOST_AUTO_TEST_CASE(BronKerboschAlgorithmTest)
{
    using namespace CDPL;
    using namespace Util;

    BitSetArray adj_mtx;
    BitSet clique;

    createAdjMatrix(100, adj_mtx);

    createClique(0, 10, adj_mtx);
    createClique(11, 15, adj_mtx);
    createClique(14, 17, adj_mtx);
    createClique(15, 50, adj_mtx);
    createClique(49, 52, adj_mtx);
    createClique(51, 95, adj_mtx);
    createClique(90, 99, adj_mtx);
    createClique(95, 100, adj_mtx);

    BronKerboschAlgorithm bka1;

    bka1.init(adj_mtx);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 10);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 1);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 4);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 3);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 35);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 3);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 44);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 9);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 5);

    BOOST_CHECK(bka1.nextClique(clique) == false);
    BOOST_CHECK(bka1.nextClique(clique) == false);

//-------------

    createAdjMatrix(6, adj_mtx);
    
    connect(0, 1, adj_mtx);
    connect(1, 4, adj_mtx);
    connect(4, 0, adj_mtx);
    connect(4, 3, adj_mtx);
    connect(1, 2, adj_mtx);
    connect(2, 3, adj_mtx);
    connect(3, 5, adj_mtx);

    bka1.init(adj_mtx);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 3);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka1.nextClique(clique) == false);
    BOOST_CHECK(bka1.nextClique(clique) == false);

//-------------

    bka1.init(adj_mtx);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BronKerboschAlgorithm bka2(bka1);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 3);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);


    BOOST_CHECK(bka2.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 3);

    BOOST_CHECK(bka2.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);


    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka1.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka1.nextClique(clique) == false);
    BOOST_CHECK(bka1.nextClique(clique) == false);


    BOOST_CHECK(bka2.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka2.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka2.nextClique(clique) == false);
    BOOST_CHECK(bka2.nextClique(clique) == false);

    BOOST_CHECK(bka1.nextClique(clique) == false);

//-------------

    BronKerboschAlgorithm bka3(adj_mtx);

    BOOST_CHECK(bka3.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BronKerboschAlgorithm bka4;
    bka4 = bka3;

    BOOST_CHECK(bka4.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 3);

    BOOST_CHECK(bka4.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);


    BOOST_CHECK(bka3.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 3);

    BOOST_CHECK(bka3.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka3.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);


    BOOST_CHECK(bka4.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka4.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka4.nextClique(clique) == false);
    BOOST_CHECK(bka4.nextClique(clique) == false);


    BOOST_CHECK(bka3.nextClique(clique));
    BOOST_CHECK_EQUAL(clique.count(), 2);

    BOOST_CHECK(bka3.nextClique(clique) == false);
    BOOST_CHECK(bka3.nextClique(clique) == false);
}

