/* 
 * PMLDataReader.cpp 
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

#include <boost/algorithm/string.hpp>

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "PMLDataReader.hpp"
#include "PMLFormatData.hpp"


using namespace CDPL;


namespace
{

    const std::string PHARMACOPHORE_START = '<' + Pharm::PML::Element::PHARMACOPHORE;
    const std::string PHARMACOPHORE_END   = "</" + Pharm::PML::Element::PHARMACOPHORE + '>';
    const std::string FALSE               = "false";
    const std::string ZERO                = "0";

    typedef std::unordered_map<std::string, unsigned int> FeatureNameToTypeMap;

    FeatureNameToTypeMap ls4FeatureTypes{
      { Pharm::PML::FeatureName::HYDROPHOBIC, Pharm::FeatureType::HYDROPHOBIC},
      { Pharm::PML::FeatureName::AROMATIC, Pharm::FeatureType::AROMATIC },
      { Pharm::PML::FeatureName::NEG_IONIZABLE, Pharm::FeatureType::NEGATIVE_IONIZABLE },
      { Pharm::PML::FeatureName::POS_IONIZABLE, Pharm::FeatureType::POSITIVE_IONIZABLE },
      { Pharm::PML::FeatureName::H_BOND_DONOR, Pharm::FeatureType::H_BOND_DONOR },
      { Pharm::PML::FeatureName::H_BOND_ACCEPTOR, Pharm::FeatureType::H_BOND_ACCEPTOR },
      { Pharm::PML::FeatureName::X_BOND_DONOR, Pharm::FeatureType::HALOGEN_BOND_DONOR },
      { Pharm::PML::FeatureName::X_BOND_ACCEPTOR, Pharm::FeatureType::HALOGEN_BOND_ACCEPTOR }
    };

    unsigned int getFeatureTypeFromLS4Name(const std::string& name)
    {
        FeatureNameToTypeMap::const_iterator it = ls4FeatureTypes.find(name);

        if (it == ls4FeatureTypes.end())
            return Pharm::FeatureType::UNKNOWN;

        return it->second;
    }

    bool getBoolValue(const char* value)
    {
        std::string val_lc = value;
        boost::algorithm::to_lower(val_lc);

        if (FALSE == val_lc || ZERO == val_lc)
            return false;

        return true;
    }
}


Pharm::PMLDataReader::PMLDataReader(const Base::DataIOBase& io_base): 
    ioBase(io_base), strictErrorChecking(true) 
{}

bool Pharm::PMLDataReader::hasMoreData(std::istream& is)
{
    return Internal::skipToString(is, PHARMACOPHORE_START, "PMLDataReader", false);
}

bool Pharm::PMLDataReader::readPharmacophore(std::istream& is, Pharmacophore& pharm)
{
    using namespace Internal;
    
    init();

    if (!skipToString(is, PHARMACOPHORE_START, "PMLDataReader", false))
        return false;

    pharmData.clear();

    if (!readToString(is, PHARMACOPHORE_END, pharmData, "PMLDataReader", true)) {
        if (strictErrorChecking)
            throw Base::IOError("PMLDataReader: error while reading pharmacophore, no closing pharmacophore tag found");

        return false;
    }

    pharmDocument.parse<0>(&pharmData[0]);
    
    const XMLNode* pharm_node = pharmDocument.first_node(PML::Element::PHARMACOPHORE.c_str());

    if (!pharm_node)
        throw Base::IOError("PMLDataReader: error while reading pharmacophore, pharmacophore node not accessible");

    getPharmacophoreProperties(pharm_node, pharm);
    extractFeatures(pharm_node, pharm);

    return true;
}

bool Pharm::PMLDataReader::skipPharmacophore(std::istream& is)
{
    using namespace Internal;
    
    init();

    if (!skipToString(is, PHARMACOPHORE_START, "PMLDataReader", false))
        throw Base::IOError("PMLDataReader: unexpected end of input");

    if (!skipToString(is, PHARMACOPHORE_END, "PMLDataReader", true)) {
        if (strictErrorChecking)
            throw Base::IOError("PMLDataReader: error while skipping input pharmacophore, no closing pharmacophore tag found");

        return false;
    }

    return true;
}

void Pharm::PMLDataReader::init()
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
}

void Pharm::PMLDataReader::getPharmacophoreProperties(const XMLNode* pharm_node, Pharmacophore& pharm) const
{
    if (const XMLAttribute* attr = pharm_node->first_attribute(PML::Attribute::NAME.c_str()))
        setName(pharm, attr->value());
}

void Pharm::PMLDataReader::extractFeatures(const XMLNode* pharm_node, Pharmacophore& pharm) const
{
    for (const XMLNode* node = pharm_node->first_node(); node; node = node->next_sibling()) {
        const char* node_name = node->name();

        if (std::strcmp(node_name, PML::Element::POINT_FEATURE.c_str()) == 0)
            addPointFeature(node, pharm);

        else if (std::strcmp(node_name, PML::Element::PLANE_FEATURE.c_str()) == 0)
            addPlaneFeature(node, pharm);

        else if (std::strcmp(node_name, PML::Element::VECTOR_FEATURE.c_str()) == 0)
            addVectorFeature(node, pharm);

        else if (std::strcmp(node_name, PML::Element::VOLUME_FEATURE.c_str()) == 0)
            addVolumeFeature(node, pharm);
    }
}

void Pharm::PMLDataReader::addPointFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const
{
    Feature* ftr = createFeature(ftr_node, pharm);

    if (!ftr)
        return;
    
    setGeometry(*ftr, FeatureGeometry::SPHERE);

    Math::Vector3D pos;

    if (getPosition(ftr_node, PML::Element::FEATURE_POSITION, pos))
        set3DCoordinates(*ftr, pos);

    double tol = 1.0;
        
    if (getTolerance(ftr_node, PML::Element::FEATURE_POSITION, tol))
        setTolerance(*ftr, tol);
}

void Pharm::PMLDataReader::addPlaneFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const
{
    Feature* ftr = createFeature(ftr_node, pharm);

    if (!ftr)
        return;
    
    setGeometry(*ftr, FeatureGeometry::PLANE);

    Math::Vector3D vec;

    if (getPosition(ftr_node, PML::Element::FEATURE_POSITION, vec))
        set3DCoordinates(*ftr, vec);

    if (getPosition(ftr_node, PML::Element::FEATURE_NORMAL, vec))
        setOrientation(*ftr, vec);

    double tol = 1.0;
        
    if (getTolerance(ftr_node, PML::Element::FEATURE_POSITION, tol))
        setTolerance(*ftr, tol);
}

void Pharm::PMLDataReader::addVectorFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const
{
    Feature* ftr = createFeature(ftr_node, pharm);

    if (!ftr)
        return;
    
    setGeometry(*ftr, FeatureGeometry::VECTOR);

    const XMLAttribute* attr = ftr_node->first_attribute(PML::Attribute::POINTS_TO_LIGAND.c_str());
    bool points_to_lig = false;

    if (attr)
        points_to_lig = getBoolValue(attr->value());

    Math::Vector3D org_pos;
    bool have_org_pos = getPosition(ftr_node, PML::Element::FEATURE_ORIGIN, org_pos);

    Math::Vector3D tgt_pos;
    bool have_tgt_pos = getPosition(ftr_node, PML::Element::FEATURE_TARGET, tgt_pos);

    if (have_tgt_pos && have_org_pos) {
        Math::Vector3D orient = tgt_pos - org_pos;
        double len = length(orient);

        orient /= len;

        setLength(*ftr, len);
        setOrientation(*ftr, orient);
    }

    if (points_to_lig) {
        double tol = 1.0;

        if (getTolerance(ftr_node, PML::Element::FEATURE_TARGET, tol))
            setTolerance(*ftr, tol);

        if (have_tgt_pos)
            set3DCoordinates(*ftr, tgt_pos);

    } else {
        double tol = 1.0;

        if (getTolerance(ftr_node, PML::Element::FEATURE_ORIGIN, tol))
            setTolerance(*ftr, tol);

        if (have_org_pos)
            set3DCoordinates(*ftr, org_pos);
    }
}

void Pharm::PMLDataReader::addVolumeFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const
{
    const XMLAttribute* attr = ftr_node->first_attribute(PML::Attribute::TYPE.c_str());

    if (!attr)
        return;

    if (std::strcmp(attr->value(), PML::VOLUME_TYPE_EXCLUSION.c_str()) != 0)
        return;

    Feature& ftr = pharm.addFeature();

    setType(ftr, FeatureType::EXCLUSION_VOLUME);
    setGeometry(ftr, FeatureGeometry::SPHERE);
    
    getDefaultFeatureProperties(ftr_node, ftr);

    Math::Vector3D pos;

    if (getPosition(ftr_node, PML::Element::FEATURE_POSITION, pos))
        set3DCoordinates(ftr, pos);

    double tol = 1.0;
        
    if (getTolerance(ftr_node, PML::Element::FEATURE_POSITION, tol))
        setTolerance(ftr, tol);
}

Pharm::Feature* Pharm::PMLDataReader::createFeature(const XMLNode* ftr_node, Pharmacophore& pharm) const
{
    const XMLAttribute* attr = ftr_node->first_attribute(PML::Attribute::NAME.c_str());

    if (!attr)
        return 0;

    unsigned int type = getFeatureTypeFromLS4Name(attr->value());

    if (type == FeatureType::UNKNOWN)
        return 0;

    Feature& ftr = pharm.addFeature();

    setType(ftr, type);
    getDefaultFeatureProperties(ftr_node, ftr);

    return &ftr;
}

void Pharm::PMLDataReader::getDefaultFeatureProperties(const XMLNode* ftr_node, Feature& ftr) const
{
    const XMLAttribute* attr = ftr_node->first_attribute(PML::Attribute::OPTIONAL.c_str());

    if (attr)
        setOptionalFlag(ftr, getBoolValue(attr->value()));

    attr = ftr_node->first_attribute(PML::Attribute::DISABLED.c_str());

    if (attr)
        setDisabledFlag(ftr, getBoolValue(attr->value()));
}

bool Pharm::PMLDataReader::getPosition(const XMLNode* ftr_node, const std::string& tag, Math::Vector3D& vec) const 
{
    using namespace Internal;

    const XMLNode* vec_node = ftr_node->first_node(tag.c_str());

    if (!vec_node)
        return false;

    const XMLAttribute* attr = vec_node->first_attribute(PML::Attribute::COORDS_X.c_str());

    if (attr)
        vec[0] = parseNumber<double>(attr->value(), attr->value() + attr->value_size(), 
                                     "PMLDataReader: error while parsing vector x-ccordinate");

    attr = vec_node->first_attribute(PML::Attribute::COORDS_Y.c_str());

    if (attr)
        vec[1] = parseNumber<double>(attr->value(), attr->value() + attr->value_size(), 
                                     "PMLDataReader: error while parsing vector y-ccordinate");

    attr = vec_node->first_attribute(PML::Attribute::COORDS_Z.c_str());

    if (attr)
        vec[2] = parseNumber<double>(attr->value(), attr->value() + attr->value_size(), 
                                     "PMLDataReader: error while parsing vector z-ccordinate");
    return true;
}

bool Pharm::PMLDataReader::getTolerance(const XMLNode* ftr_node, const std::string& tag, double& tol) const 
{
    const XMLNode* vec_node = ftr_node->first_node(tag.c_str());

    if (!vec_node)
        return false;

    const XMLAttribute* attr = vec_node->first_attribute(PML::Attribute::TOLERANCE.c_str());

    if (!attr)
        return false;

    tol = Internal::parseNumber<double>(attr->value(), attr->value() + attr->value_size(), 
                                        "PMLDataReader: error while parsing feature tolerance");
    return true;
}
