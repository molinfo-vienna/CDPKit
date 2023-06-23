/* 
 * BasicFeatureTest.cpp 
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

#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/LookupKey.hpp"


BOOST_AUTO_TEST_CASE(BasicFeatureTest)
{
    using namespace CDPL;
    using namespace Pharm;
    using namespace Base;

    BasicPharmacophore pharm;

    pharm.addFeature();
    pharm.addFeature();

    //-----

    for (std::size_t i = 0; i < pharm.getNumFeatures(); i++)
        BOOST_CHECK(pharm.getFeature(i).getIndex() == i);

    BOOST_CHECK(&const_cast<const BasicFeature&>(pharm.getFeature(0)).getPharmacophore() == &pharm);
    BOOST_CHECK(&const_cast<BasicFeature&>(pharm.getFeature(0)).getPharmacophore() == &pharm);

    //-----

    BOOST_CHECK(&const_cast<const BasicFeature&>(pharm.getFeature(1)).getPharmacophore() == &pharm);
    BOOST_CHECK(&const_cast<BasicFeature&>(pharm.getFeature(1)).getPharmacophore() == &pharm);

    //-----

    LookupKey prop_key1 = LookupKey::create("key1"); 
    LookupKey prop_key2 = LookupKey::create("key2"); 

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 0);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 0);

    BOOST_CHECK(&(pharm.getFeature(1) = pharm.getFeature(1)) == &pharm.getFeature(1));

    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 0);

    pharm.getFeature(1).setProperty(prop_key2, std::string("value2"));
    
    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 0);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 1);

    BOOST_CHECK_THROW(pharm.getFeature(0).getProperty<std::string>(prop_key2), ItemNotFound);
    BOOST_CHECK(pharm.getFeature(1).getProperty<std::string>(prop_key2) == "value2");

    BOOST_CHECK(&(pharm.getFeature(1) = pharm.getFeature(1)) == &pharm.getFeature(1));

    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 1);

    BOOST_CHECK(pharm.getFeature(1).getProperty<std::string>(prop_key2) == "value2");

    BOOST_CHECK(&(pharm.getFeature(0) = pharm.getFeature(1)) == &pharm.getFeature(0));

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 1);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 1);

    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key2) == "value2");
    BOOST_CHECK(pharm.getFeature(1).getProperty<std::string>(prop_key2) == "value2");

    pharm.getFeature(0).setProperty(prop_key2, std::string("value1"));

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 1);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 1);

    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key2) == "value1");
    BOOST_CHECK(pharm.getFeature(1).getProperty<std::string>(prop_key2) == "value2");

    BOOST_CHECK(&(pharm.getFeature(0) = pharm.getFeature(1)) == &pharm.getFeature(0));

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 1);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 1);

    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key2) == "value2");
    BOOST_CHECK(pharm.getFeature(1).getProperty<std::string>(prop_key2) == "value2");

    pharm.getFeature(0).setProperty(prop_key1, std::string("value1"));

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 2);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 1);

    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key1) == "value1");
    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key2) == "value2");
    BOOST_CHECK(pharm.getFeature(1).getProperty<std::string>(prop_key2) == "value2");

    BOOST_CHECK(&(pharm.getFeature(0) = pharm.getFeature(0)) == &pharm.getFeature(0));

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 2);

    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key1) == "value1");
    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key2) == "value2");

    BOOST_CHECK(&(pharm.getFeature(0) = pharm.getFeature(1)) == &pharm.getFeature(0));

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 1);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 1);

    BOOST_CHECK_THROW(pharm.getFeature(0).getProperty<std::string>(prop_key1), ItemNotFound);
    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key2) == "value2");
    BOOST_CHECK(pharm.getFeature(1).getProperty<std::string>(prop_key2) == "value2");

    pharm.getFeature(1).clearProperties();

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 1);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 0);

    BOOST_CHECK(pharm.getFeature(0).getProperty<std::string>(prop_key2) == "value2");
    BOOST_CHECK_THROW(pharm.getFeature(1).getProperty<std::string>(prop_key2), ItemNotFound);

    BOOST_CHECK(&(pharm.getFeature(0) = pharm.getFeature(1)) == &pharm.getFeature(0));

    BOOST_CHECK(pharm.getFeature(0).getNumProperties() == 0);
    BOOST_CHECK(pharm.getFeature(1).getNumProperties() == 0);

    BOOST_CHECK_THROW(pharm.getFeature(0).getProperty<std::string>(prop_key2), ItemNotFound);
    BOOST_CHECK_THROW(pharm.getFeature(1).getProperty<std::string>(prop_key2), ItemNotFound);
}
