/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BasicPharmacophoreTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <string>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Chem/BasicPharmacophore.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/LookupKey.hpp"


namespace
{

	void checkFeatureIndices(const CDPL::Chem::BasicPharmacophore& pharm)
	{
		for (std::size_t i = 0; i < pharm.getNumFeatures(); i++)
			BOOST_CHECK(pharm.getFeatureIndex(pharm.getFeature(i)) == i);
	}
}


BOOST_AUTO_TEST_CASE(BasicPharmacophoreTest)
{
	using namespace CDPL;
	using namespace Chem;
	using namespace Base;

	LookupKey prop_key1 = LookupKey::create("key1"); 
	LookupKey prop_key2 = LookupKey::create("key2"); 

//-----	

	BasicPharmacophore pharm1;

	BOOST_CHECK(pharm1.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm1.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm1.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	Pharmacophore::SharedPointer pharm1_clone_ptr = pharm1.clone();
	BasicPharmacophore& pharm1_clone = static_cast<BasicPharmacophore&>(*pharm1_clone_ptr);

	BOOST_CHECK(&pharm1 != pharm1_clone_ptr.get());

	BOOST_CHECK(pharm1_clone.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1_clone).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm1_clone).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1_clone).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm1_clone).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1_clone).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1_clone).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1_clone).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1_clone).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm1_clone.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm1_clone.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm1_clone.removeFeature(pharm1_clone.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm1_clone.removeFeature(pharm1_clone.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm1_clone.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicPharmacophoreFeature& pharm1_feature1 = pharm1.addFeature();

	pharm1_feature1.setProperty(prop_key2, std::string("C"));

	BOOST_CHECK(pharm1.getNumFeatures() == 1);

	checkFeatureIndices(pharm1);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1 == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1 == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature1);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature1);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature1);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature1);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK(pharm1.containsFeature(pharm1_feature1));

//-----	

	BasicPharmacophoreFeature& pharm1_feature2 = pharm1.addFeature();
	pharm1_feature2.setProperty(prop_key2, std::string("H"));

	BasicPharmacophoreFeature& pharm1_feature3 = (pharm1.addFeature() = pharm1_feature2);

	BasicPharmacophoreFeature& pharm1_feature4 = pharm1.addFeature();
	pharm1_feature4.setProperty(prop_key2, std::string("O"));

	BasicPharmacophoreFeature& pharm1_feature5 = (pharm1.addFeature() = pharm1_feature3);

	BOOST_CHECK(pharm1.getNumFeatures() == 5);

	checkFeatureIndices(pharm1);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature1);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature1);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature2);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature3);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature3);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3) == &pharm1_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3) == &pharm1_feature4);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 4) == &pharm1_feature5);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 4) == &pharm1_feature5);


	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature1);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature1);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature3);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature3);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(3) == &pharm1_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(3) == &pharm1_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(4) == &pharm1_feature5);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(4) == &pharm1_feature5);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm1.containsFeature(pharm1_feature1));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature2));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature4));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature5));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature3));

//-----	

	BOOST_CHECK(pharm1.getNumFeatures() == 5);

	checkFeatureIndices(pharm1);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature1);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature1);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature2);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature3);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature3);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3) == &pharm1_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3) == &pharm1_feature4);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 4) == &pharm1_feature5);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 4) == &pharm1_feature5);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature1);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature1);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature3);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature3);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(3) == &pharm1_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(3) == &pharm1_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(4) == &pharm1_feature5);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(4) == &pharm1_feature5);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(5), IndexError);


	BOOST_CHECK_THROW(pharm1.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 5), RangeError);


	BOOST_CHECK(pharm1.containsFeature(pharm1_feature1));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature2));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature4));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature5));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature3));

//-----	

	pharm1.setProperty(prop_key1, std::string("BasicPharmacophore 1"));

	BOOST_CHECK(pharm1.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

	pharm1_clone_ptr = pharm1.clone();
	BasicPharmacophore& pharm1_clone2 = static_cast<BasicPharmacophore&>(*pharm1_clone_ptr);

	BOOST_CHECK(&pharm1 != pharm1_clone_ptr.get());

	BOOST_CHECK(pharm1_clone2.getNumFeatures() == 5);

	checkFeatureIndices(pharm1_clone2);

	BOOST_CHECK_THROW(pharm1_clone2.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm1_clone2).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() == &pharm1_clone2.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() == &pharm1_clone2.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 1) == &pharm1_clone2.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 1) == &pharm1_clone2.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 2) == &pharm1_clone2.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 2) == &pharm1_clone2.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 3) == &pharm1_clone2.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 3) == &pharm1_clone2.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 4) == &pharm1_clone2.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1_clone2).getFeaturesBegin() + 4) == &pharm1_clone2.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1_clone2).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1_clone2).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm1_clone2.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm1_clone2.removeFeature(pharm1_clone2.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm1_clone2.containsFeature(pharm1_clone2.getFeature(0)));

	BOOST_CHECK(!pharm1_clone2.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm1_clone2.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm1_clone2.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm1_clone2.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm1_clone2.containsFeature(pharm1_feature5));
	
	BOOST_CHECK(pharm1_clone2.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm1_clone2.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm1_clone2.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm1_clone2.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm1_clone2.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm1_clone2.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

	BOOST_CHECK(pharm1_feature1.getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm1_feature2.getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm1_feature3.getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm1_feature4.getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm1_feature5.getProperty<std::string>(prop_key2) == "H");

//-----	

	BasicPharmacophore pharm2(pharm1);

	BOOST_CHECK(pharm2.getNumFeatures() == 5);

	checkFeatureIndices(pharm2);

	BOOST_CHECK_THROW(pharm2.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm2).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm2).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4) == &pharm2.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4) == &pharm2.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm2).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm2).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm2.containsFeature(pharm2.getFeature(0)));

	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature5));
	
	BOOST_CHECK(pharm2.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm2.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm2.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm2.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm2.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm2.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	BasicPharmacophore pharm3;

	BOOST_CHECK(&(pharm3 = pharm1) == &pharm3);

	BOOST_CHECK(pharm3.getNumFeatures() == 5);

	checkFeatureIndices(pharm3);

	BOOST_CHECK_THROW(pharm3.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm3).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm3).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() == &pharm3.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() == &pharm3.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 1) == &pharm3.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 1) == &pharm3.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 2) == &pharm3.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 2) == &pharm3.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 3) == &pharm3.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 3) == &pharm3.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 4) == &pharm3.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 4) == &pharm3.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm3).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm3).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(pharm3.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm3.containsFeature(pharm3.getFeature(0)));

	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature5));
	
	BOOST_CHECK(pharm3.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm3.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm3.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm3.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm3.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm3.getNumProperties() == 1);

	BOOST_CHECK(pharm3.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	pharm3.clear();

	BOOST_CHECK(pharm3.getNumFeatures() == 0);
	BOOST_CHECK(pharm3.getNumProperties() == 0);

	pharm3.copy(pharm1);

	BOOST_CHECK(pharm3.getNumFeatures() == 5);

	checkFeatureIndices(pharm3);

	BOOST_CHECK_THROW(pharm3.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm3).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm3).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() == &pharm3.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() == &pharm3.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 1) == &pharm3.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 1) == &pharm3.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 2) == &pharm3.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 2) == &pharm3.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 3) == &pharm3.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 3) == &pharm3.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() + 4) == &pharm3.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() + 4) == &pharm3.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm3).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm3).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(pharm3.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm3.containsFeature(pharm3.getFeature(0)));

	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm3.containsFeature(pharm1_feature5));
	BOOST_CHECK(pharm3.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm3.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm3.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm3.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm3.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm3.getNumProperties() == 1);

	BOOST_CHECK(pharm3.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	BasicPharmacophore pharm4;

	BOOST_CHECK(&(pharm4 += pharm1) == &pharm4);
	
	BOOST_CHECK(pharm4.getNumFeatures() == 5);

	checkFeatureIndices(pharm4);

	BOOST_CHECK_THROW(pharm4.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm4).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm4).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm4).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm4).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(pharm4.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm4.containsFeature(pharm4.getFeature(0)));

	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature5));
	BOOST_CHECK(pharm4.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm4.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm4.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm4.getNumProperties() == 0);

	BOOST_CHECK_THROW(pharm4.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	
	
	pharm4.clear();

	BOOST_CHECK(pharm4.getNumFeatures() == 0);
	BOOST_CHECK(pharm4.getNumProperties() == 0);

	pharm4.append(pharm1);
	
	BOOST_CHECK(pharm4.getNumFeatures() == 5);

	checkFeatureIndices(pharm4);

	BOOST_CHECK_THROW(pharm4.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm4).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm4).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm4).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm4).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(pharm4.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm4.containsFeature(pharm4.getFeature(0)));

	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature5));

	BOOST_CHECK(pharm4.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm4.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm4.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm4.getNumProperties() == 0);

	BOOST_CHECK_THROW(pharm4.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	pharm4.setProperty(prop_key1, std::string("BasicPharmacophore 4"));

	pharm4.append(BasicPharmacophore());

	BOOST_CHECK(pharm4.getNumFeatures() == 5);

	checkFeatureIndices(pharm4);

	BOOST_CHECK(pharm4.getProperty<std::string>(prop_key1) == "BasicPharmacophore 4");

//-----	

	BasicPharmacophore pharm5;

	BOOST_CHECK(pharm5.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm5).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm5).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm5.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm5.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	pharm5.append(pharm1);

	BOOST_CHECK(pharm5.getNumFeatures() == 5);

	checkFeatureIndices(pharm5);

	BOOST_CHECK_THROW(pharm5.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm5).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm5).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm5.containsFeature(pharm5.getFeature(0)));

	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature5));
	
	BOOST_CHECK(pharm5.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm5.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm5.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm5.getNumProperties() == 0);

	BOOST_CHECK_THROW(pharm5.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicPharmacophore pharm6;

	BOOST_CHECK(&(pharm6 = BasicPharmacophore()) == &pharm6);

	BOOST_CHECK(pharm6.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm6).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm6).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm6).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm6).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm6).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm6).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm6).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm6).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm6.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm6.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm6.removeFeature(pharm6.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm6.removeFeature(pharm6.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm6.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BasicPharmacophore pharm7;

	BOOST_CHECK(&(pharm7 += BasicPharmacophore()) == &pharm7);

	BOOST_CHECK(pharm7.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm7).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm7).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm7).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm7).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm7).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm7).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm7).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm7).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm7.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm7.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm7.removeFeature(pharm7.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm7.removeFeature(pharm7.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm7.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BOOST_CHECK(&(pharm2 += BasicPharmacophore()) == &pharm2);

	BOOST_CHECK(pharm2.getNumFeatures() == 5);

	checkFeatureIndices(pharm2);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm2).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm2).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4) == &pharm2.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4) == &pharm2.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm2).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm2).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm2.containsFeature(pharm2.getFeature(0)));

	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm2.containsFeature(pharm1_feature5));
	
	BOOST_CHECK(pharm2.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm2.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm2.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm2.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm2.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm2.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	BOOST_CHECK(&(pharm3 = BasicPharmacophore()) == &pharm3);

	BOOST_CHECK(pharm3.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm3).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm3).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm3).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm3).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm3).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm3).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm3.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(pharm3.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm3.removeFeature(pharm3.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm3.getProperty<std::string>(prop_key1), ItemNotFound);

	BOOST_CHECK(pharm3.getNumProperties() == 0);

//-----	

	BOOST_CHECK(&(pharm3 += pharm3) == &pharm3);

	BOOST_CHECK(pharm3.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm3).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm3).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm3).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm3).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm3).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm3).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm3).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm3).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm3.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm3.removeFeature(pharm3.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm3.removeFeature(pharm3.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm3.getProperty<std::string>(prop_key1), ItemNotFound);

//-----	

	BOOST_CHECK(&(pharm4 += pharm4) == &pharm4);
		
	checkFeatureIndices(pharm4);

	BOOST_CHECK_THROW(pharm4.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(pharm4.getNumFeatures() == 10);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 10 == const_cast<const BasicPharmacophore&>(pharm4).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 10 == const_cast<BasicPharmacophore&>(pharm4).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm4).getFeature(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm4).getFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(pharm4.getFeaturesBegin() + 10), RangeError);

	BOOST_CHECK(pharm4.containsFeature(pharm4.getFeature(0)));

	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature1));

	BOOST_CHECK(pharm4.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm4.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm4.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm4.getProperty<std::string>(prop_key1) == "BasicPharmacophore 4");

//-----	

	pharm4.copy(BasicPharmacophore());

	BOOST_CHECK(pharm4.getNumFeatures() == 0);
	BOOST_CHECK(pharm4.getNumProperties() == 0);
	
	pharm4.copy(pharm1);

	checkFeatureIndices(pharm4);

	BOOST_CHECK(pharm4.getNumFeatures() == 5);
	BOOST_CHECK(pharm4.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

	pharm4.setProperty(prop_key1, std::string("BasicPharmacophore 4"));
	pharm4.append(pharm4);

	checkFeatureIndices(pharm4);

	BOOST_CHECK_THROW(pharm4.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(pharm4.getNumFeatures() == 10);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 10 == const_cast<const BasicPharmacophore&>(pharm4).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 10 == const_cast<BasicPharmacophore&>(pharm4).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() == &pharm4.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 1) == &pharm4.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 2) == &pharm4.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 3) == &pharm4.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm4).getFeaturesBegin() + 4) == &pharm4.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm4).getFeature(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm4).getFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm4.removeFeature(pharm4.getFeaturesBegin() + 10), RangeError);

	BOOST_CHECK(pharm4.containsFeature(pharm4.getFeature(0)));

	BOOST_CHECK(!pharm4.containsFeature(pharm1_feature1));
	
	BOOST_CHECK(pharm4.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm4.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm4.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm4.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm4.getProperty<std::string>(prop_key1) == "BasicPharmacophore 4");

//-----	

	pharm4.copy(pharm1);

	checkFeatureIndices(pharm4);

	BOOST_CHECK(pharm4.getNumFeatures() == 5);
	BOOST_CHECK(pharm4.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

	pharm4.setProperty(prop_key1, std::string("BasicPharmacophore 4"));

//-----	

	BOOST_CHECK(&(pharm5 = pharm1) == &pharm5);

	pharm5.setProperty(prop_key1, std::string("BasicPharmacophore 5"));

	BOOST_CHECK(&(pharm5 += pharm2) == &pharm5);

	BOOST_CHECK(pharm5.getNumFeatures() == 10);

	checkFeatureIndices(pharm5);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 10 == const_cast<const BasicPharmacophore&>(pharm5).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 10 == const_cast<BasicPharmacophore&>(pharm5).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin() + 10), RangeError);

	BOOST_CHECK(pharm5.containsFeature(pharm5.getFeature(0)));

	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature1));

	BOOST_CHECK(pharm5.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm5.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm5.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm5.getProperty<std::string>(prop_key1) == "BasicPharmacophore 5");

//-----	

	BOOST_CHECK(&(pharm5 = pharm5) == &pharm5);

	BOOST_CHECK(pharm5.getNumFeatures() == 10);

	checkFeatureIndices(pharm5);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 10 == const_cast<const BasicPharmacophore&>(pharm5).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 10 == const_cast<BasicPharmacophore&>(pharm5).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(10), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(10), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin() + 10), RangeError);

	BOOST_CHECK(pharm5.containsFeature(pharm5.getFeature(0)));

	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature1));
	
	BOOST_CHECK(pharm5.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm5.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm5.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm5.getProperty<std::string>(prop_key1) == "BasicPharmacophore 5");

//-----	

	BOOST_CHECK(&(pharm5 = pharm2) == &pharm5);

	BOOST_CHECK(pharm5.getNumFeatures() == 5);

	checkFeatureIndices(pharm5);

	BOOST_CHECK_THROW(pharm5.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm5).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm5).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm5.containsFeature(pharm5.getFeature(0)));

	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature5));
	
	BOOST_CHECK(pharm5.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm5.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm5.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm5.getNumProperties() == 1);

	BOOST_CHECK(pharm5.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	pharm5.copy(pharm5);

	BOOST_CHECK(pharm5.getNumFeatures() == 5);

	checkFeatureIndices(pharm5);

	BOOST_CHECK_THROW(pharm5.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm5).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm5).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() == &pharm5.getFeature(0));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 1) == &pharm5.getFeature(1));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 2) == &pharm5.getFeature(2));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 3) == &pharm5.getFeature(3));

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() + 4) == &pharm5.getFeature(4));

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin() + 5), RangeError);

	BOOST_CHECK(pharm5.containsFeature(pharm5.getFeature(0)));

	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature1));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature2));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature3));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm5.containsFeature(pharm1_feature5));

	BOOST_CHECK(pharm5.getFeature(0).getProperty<std::string>(prop_key2) == "C");
	BOOST_CHECK(pharm5.getFeature(1).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(2).getProperty<std::string>(prop_key2) == "H");
	BOOST_CHECK(pharm5.getFeature(3).getProperty<std::string>(prop_key2) == "O");
	BOOST_CHECK(pharm5.getFeature(4).getProperty<std::string>(prop_key2) == "H");

	BOOST_CHECK(pharm5.getNumProperties() == 1);

	BOOST_CHECK(pharm5.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	pharm5.clear();

	BOOST_CHECK(pharm5.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm5).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm5).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm5).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm5).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm5).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm5).getFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm5.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm5.removeFeature(pharm5.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK_THROW(pharm5.getProperty<std::string>(prop_key1), ItemNotFound);

	BOOST_CHECK(pharm5.getNumProperties() == 0);

//-----	

	pharm1.removeFeature(0);

	BOOST_CHECK(pharm1.getNumFeatures() == 4);

	checkFeatureIndices(pharm1);

	BOOST_CHECK_THROW(pharm1.getFeatureIndex(pharm4.getFeature(0)), ItemNotFound);
	BOOST_CHECK_THROW(pharm1.getFeatureIndex(pharm1_feature1), ItemNotFound);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 4 == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 4 == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature2);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature3);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature3);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature4);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3) == &pharm1_feature5);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3) == &pharm1_feature5);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature3);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature3);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(3) == &pharm1_feature5);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(3) == &pharm1_feature5);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(4), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(4), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 4), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesEnd()), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesEnd() + 1), RangeError);

	BOOST_CHECK(!pharm1.containsFeature(pharm1_feature1));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature2));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature4));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature5));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature3));


//-----	

	pharm1.removeFeature(1);

	BOOST_CHECK(pharm1.getNumFeatures() == 3);

	checkFeatureIndices(pharm1);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3 == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 3 == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature2);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature4);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature5);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2) == &pharm1_feature5);


	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature5);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(2) == &pharm1_feature5);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(3), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(3), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(3), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 3), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesEnd()), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesEnd() + 1), RangeError);

	BOOST_CHECK(!pharm1.containsFeature(pharm1_feature1));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature2));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature4));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature5));
	BOOST_CHECK(!pharm1.containsFeature(pharm1_feature3));

//-----	

	pharm1.removeFeature(2);

	BOOST_CHECK(pharm1.getNumFeatures() == 2);

	checkFeatureIndices(pharm1);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2 == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 2 == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature2);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == &pharm1_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() + 1) == &pharm1_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(0) == &pharm1_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm1).getFeature(1) == &pharm1_feature4);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(2), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(2), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(3), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 2), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesEnd()), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesEnd() + 1), RangeError);

	BOOST_CHECK(!pharm1.containsFeature(pharm1_feature1));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature2));
	BOOST_CHECK(pharm1.containsFeature(pharm1_feature4));
	BOOST_CHECK(!pharm1.containsFeature(pharm1_feature5));
	BOOST_CHECK(!pharm1.containsFeature(pharm1_feature3));
	
	BOOST_CHECK(pharm1.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----

	BasicPharmacophoreFeature& pharm2_feature1 = pharm2.getFeature(0);
	BasicPharmacophoreFeature& pharm2_feature2 = pharm2.getFeature(1);
	BasicPharmacophoreFeature& pharm2_feature3 = pharm2.getFeature(2);
	BasicPharmacophoreFeature& pharm2_feature4 = pharm2.getFeature(3);
	BasicPharmacophoreFeature& pharm2_feature5 = pharm2.getFeature(4);

	BOOST_CHECK(pharm2.getNumFeatures() == 5);

	checkFeatureIndices(pharm2);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 5 == const_cast<const BasicPharmacophore&>(pharm2).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 5 == const_cast<BasicPharmacophore&>(pharm2).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature1);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature1);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature2);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2_feature3);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2_feature3);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2_feature4);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4) == &pharm2_feature5);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4) == &pharm2_feature5);


	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature1);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature1);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(2) == &pharm2_feature3);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(2) == &pharm2_feature3);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(3) == &pharm2_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(3) == &pharm2_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(4) == &pharm2_feature5);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(4) == &pharm2_feature5);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm2).getFeature(5), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm2).getFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(5), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesBegin() + 5), RangeError);
	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesEnd()), RangeError);

	BOOST_CHECK(pharm2.containsFeature(pharm2_feature1));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature2));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature4));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature5));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature3));

//-----

	BasicPharmacophore::FeatureIterator f_it = pharm2.removeFeature(pharm2.getFeaturesBegin());

	BOOST_CHECK(f_it == pharm2.getFeaturesBegin());

	BOOST_CHECK(pharm2.getNumFeatures() == 4);

	checkFeatureIndices(pharm2);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4 == const_cast<const BasicPharmacophore&>(pharm2).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 4 == const_cast<BasicPharmacophore&>(pharm2).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature2);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature3);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature3);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2_feature4);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2_feature5);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3) == &pharm2_feature5);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature3);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature3);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(2) == &pharm2_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(2) == &pharm2_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(3) == &pharm2_feature5);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(3) == &pharm2_feature5);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm2).getFeature(4), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm2).getFeature(4), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(4), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesBegin() + 4), RangeError);
	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesEnd()), RangeError);
	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesEnd() + 1), RangeError);

	BOOST_CHECK(!pharm2.containsFeature(pharm2_feature1));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature2));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature4));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature5));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature3));
	
//-----	

	f_it = pharm2.removeFeature(++pharm2.getFeaturesBegin());

	BOOST_CHECK(f_it == ++pharm2.getFeaturesBegin());

	BOOST_CHECK(pharm2.getNumFeatures() == 3);

	checkFeatureIndices(pharm2);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3 == const_cast<const BasicPharmacophore&>(pharm2).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 3 == const_cast<BasicPharmacophore&>(pharm2).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature2);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature4);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2_feature5);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2) == &pharm2_feature5);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(2) == &pharm2_feature5);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(2) == &pharm2_feature5);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm2).getFeature(3), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm2).getFeature(3), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(3), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesBegin() + 3), RangeError);
	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesEnd()), RangeError);
	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesEnd() + 1), RangeError);

	BOOST_CHECK(!pharm2.containsFeature(pharm2_feature1));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature2));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature4));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature5));
	BOOST_CHECK(!pharm2.containsFeature(pharm2_feature3));
	
//-----	

	f_it = pharm2.removeFeature(--pharm2.getFeaturesEnd());

	BOOST_CHECK(f_it == pharm2.getFeaturesEnd());

	BOOST_CHECK(pharm2.getNumFeatures() == 2);

	checkFeatureIndices(pharm2);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2 == const_cast<const BasicPharmacophore&>(pharm2).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 2 == const_cast<BasicPharmacophore&>(pharm2).getFeaturesEnd());

	BOOST_CHECK(&*const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature2);
	BOOST_CHECK(&*const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() == &pharm2_feature2);

	BOOST_CHECK(&*(const_cast<const BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature4);
	BOOST_CHECK(&*(const_cast<BasicPharmacophore&>(pharm2).getFeaturesBegin() + 1) == &pharm2_feature4);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature2);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(0) == &pharm2_feature2);

	BOOST_CHECK(&const_cast<const BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature4);
	BOOST_CHECK(&const_cast<BasicPharmacophore&>(pharm2).getFeature(1) == &pharm2_feature4);

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm2).getFeature(2), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm2).getFeature(2), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(3), IndexError);

	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesBegin() + 2), RangeError);
	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesEnd()), RangeError);
	BOOST_CHECK_THROW(pharm2.removeFeature(pharm2.getFeaturesEnd() + 1), RangeError);

	BOOST_CHECK(!pharm2.containsFeature(pharm2_feature1));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature2));
	BOOST_CHECK(pharm2.containsFeature(pharm2_feature4));
	BOOST_CHECK(!pharm2.containsFeature(pharm2_feature5));
	BOOST_CHECK(!pharm2.containsFeature(pharm2_feature3));

	BOOST_CHECK(pharm2.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	pharm1.removeFeature(0);
	
	f_it = pharm1.removeFeature(pharm1.getFeaturesBegin());

	BOOST_CHECK(f_it == pharm1.getFeaturesBegin());

	BOOST_CHECK(pharm1.getNumFeatures() == 0);

	BOOST_CHECK(const_cast<const BasicPharmacophore&>(pharm1).getFeaturesBegin() == const_cast<const BasicPharmacophore&>(pharm1).getFeaturesEnd());
	BOOST_CHECK(const_cast<BasicPharmacophore&>(pharm1).getFeaturesBegin() == const_cast<BasicPharmacophore&>(pharm1).getFeaturesEnd());

	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(0), IndexError);
	BOOST_CHECK_THROW(const_cast<const BasicPharmacophore&>(pharm1).getFeature(1), IndexError);
	BOOST_CHECK_THROW(const_cast<BasicPharmacophore&>(pharm1).getFeature(1), IndexError);


	BOOST_CHECK_THROW(pharm1.removeFeature(0), IndexError);
	BOOST_CHECK_THROW(pharm1.removeFeature(1), IndexError);

	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin()), RangeError);
	BOOST_CHECK_THROW(pharm1.removeFeature(pharm1.getFeaturesBegin() + 1), RangeError);

	BOOST_CHECK(pharm1.getProperty<std::string>(prop_key1) == "BasicPharmacophore 1");

//-----	

	BOOST_CHECK(pharm1.addFeature().getNumProperties() == 0);
	BOOST_CHECK(pharm1.addFeature().getNumProperties() == 0);
	BOOST_CHECK(pharm1.addFeature().getNumProperties() == 0);
	BOOST_CHECK(pharm1.addFeature().getNumProperties() == 0);
	BOOST_CHECK(pharm1.addFeature().getNumProperties() == 0);

	BOOST_CHECK(pharm1.getNumFeatures() == 5);

	checkFeatureIndices(pharm1);

//-----	

	pharm1.clear();

	BOOST_CHECK(pharm1.getNumFeatures() == 0);

	pharm1.addFeature();
	pharm1.addFeature();
	pharm1.addFeature();
	pharm1.addFeature();

	BOOST_CHECK(pharm1.getNumFeatures() == 4);

	checkFeatureIndices(pharm1);

	BOOST_CHECK(pharm1.getFeaturesEnd() - pharm1.getFeaturesBegin() == 4);

	BOOST_CHECK(pharm1.getNumFeatures() == 4);

	checkFeatureIndices(pharm1);

	f_it = pharm1.removeFeature(pharm1.getFeaturesBegin());

	BOOST_CHECK(f_it == pharm1.getFeaturesBegin());

	f_it = pharm1.removeFeature(pharm1.getFeaturesBegin() + 1);

	BOOST_CHECK(f_it == pharm1.getFeaturesBegin() + 1);

	f_it = pharm1.removeFeature(--pharm1.getFeaturesEnd());

	BOOST_CHECK(f_it == pharm1.getFeaturesEnd());

	f_it = pharm1.removeFeature(pharm1.getFeaturesBegin());

	BOOST_CHECK(f_it == pharm1.getFeaturesEnd());

	BOOST_CHECK(pharm1.getNumFeatures() == 0);

//-----	

	pharm1.addFeature();
	pharm1.addFeature();
	pharm1.addFeature();
	pharm1.addFeature();

	checkFeatureIndices(pharm1);
}
