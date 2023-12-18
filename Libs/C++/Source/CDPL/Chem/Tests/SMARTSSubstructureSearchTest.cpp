/* 
 * SMARTSSubstructureSearchTest.cpp 
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

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"


BOOST_AUTO_TEST_CASE(SMARTSSubstructureSearchTest)
{
    using namespace CDPL;
    using namespace Chem;
    
    SubstructureSearch sub_srch;
    BasicMolecule qry_mol, tgt_mol;

// -- Bond geometry matching tests --
        
    BOOST_CHECK(parseSMILES("C(/O)(\\F)=C(C)\\N", tgt_mol));
    
    initSubstructureSearchTarget(tgt_mol, false);

    // --
    
    BOOST_CHECK(parseSMARTS("F/C=C(N)/C", qry_mol));

    sub_srch.setQuery(qry_mol);

    BOOST_CHECK(sub_srch.findMappings(tgt_mol));
    BOOST_CHECK(sub_srch.getNumMappings() == 1);

    // --
    
    BOOST_CHECK(parseSMARTS("F\\C=C(N)/C", qry_mol));
    
    sub_srch.setQuery(qry_mol);

    BOOST_CHECK(!sub_srch.findMappings(tgt_mol));
    BOOST_CHECK(sub_srch.getNumMappings() == 0);

    // --
    
    BOOST_CHECK(parseSMARTS("F\\C=C(\\N)C", qry_mol));
    
    sub_srch.setQuery(qry_mol);

    BOOST_CHECK(!sub_srch.findMappings(tgt_mol));
    BOOST_CHECK(sub_srch.getNumMappings() == 0);

    // --
    
    BOOST_CHECK(parseSMARTS("*\\C=C(\\*)C", qry_mol));
    
    sub_srch.setQuery(qry_mol);

    BOOST_CHECK(sub_srch.findMappings(tgt_mol));
    BOOST_CHECK(sub_srch.getNumMappings() == 1);

    // --
    
    BOOST_CHECK(parseSMARTS("C(/O)=C/C", qry_mol));
    
    sub_srch.setQuery(qry_mol);

    BOOST_CHECK(sub_srch.findMappings(tgt_mol));
    BOOST_CHECK(sub_srch.getNumMappings() == 1);

    // --
    
    BOOST_CHECK(parseSMARTS("*\\C=C/*", qry_mol));
    
    sub_srch.setQuery(qry_mol);

    BOOST_CHECK(sub_srch.findMappings(tgt_mol));
    BOOST_CHECK(sub_srch.getNumMappings() == 4);

}
