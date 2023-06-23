/* 
 * UtilityFunctions.cpp 
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


#include "StaticInit.hpp"

#include <unordered_map>

#include "CDPL/Pharm/UtilityFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"


using namespace CDPL; 


namespace
{

    typedef std::unordered_map<unsigned int, std::string> FeatureTypeToStringMap;

    FeatureTypeToStringMap featureTypeToStringMap;
    const std::string      EMPTY_STRING;
	
    struct Init {

	Init() {
	    using namespace Pharm;

	    featureTypeToStringMap.emplace(FeatureType::UNKNOWN, "UNK");
	    featureTypeToStringMap.emplace(FeatureType::HYDROPHOBIC, "H");
	    featureTypeToStringMap.emplace(FeatureType::AROMATIC, "AR");
	    featureTypeToStringMap.emplace(FeatureType::NEGATIVE_IONIZABLE, "NI");
	    featureTypeToStringMap.emplace(FeatureType::POSITIVE_IONIZABLE, "PI");
	    featureTypeToStringMap.emplace(FeatureType::H_BOND_DONOR, "HBD");
	    featureTypeToStringMap.emplace(FeatureType::H_BOND_ACCEPTOR, "HBA");
	    featureTypeToStringMap.emplace(FeatureType::HALOGEN_BOND_DONOR, "XBD");
	    featureTypeToStringMap.emplace(FeatureType::HALOGEN_BOND_ACCEPTOR, "XBA");
	    featureTypeToStringMap.emplace(FeatureType::EXCLUSION_VOLUME, "XV");
	}

    } init;
}


const std::string& Pharm::getFeatureTypeString(unsigned int ftr_type)
{
    FeatureTypeToStringMap::const_iterator it = featureTypeToStringMap.find(ftr_type);

    if (it != featureTypeToStringMap.end())
	return it->second;

    return EMPTY_STRING;
}
