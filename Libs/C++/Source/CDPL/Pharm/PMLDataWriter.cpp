/* 
 * PMLDataWriter.cpp 
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

#include <ostream>
#include <iomanip>
#include <map>

#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "PMLDataWriter.hpp"
#include "PMLFormatData.hpp"


using namespace CDPL;


namespace
{

    constexpr double PLANE_FEATURE_SECOND_TOL_FACTOR  = 0.5;
    constexpr double VECTOR_FEATURE_TARGET_TOL_FACTOR = 1.5;
    const std::string NOT_FOUND;

    const std::string FEATURE_ID_PREFIX = "feature";
    const std::string PHARMACOPHORE_ID  = Pharm::PML::Element::PHARMACOPHORE + '0';

    typedef std::map<unsigned int, std::string> FeatureTypeToNameMap;

    FeatureTypeToNameMap ls4FeatureNames{
      { Pharm::FeatureType::HYDROPHOBIC, Pharm::PML::FeatureName::HYDROPHOBIC },
      { Pharm::FeatureType::AROMATIC, Pharm::PML::FeatureName::AROMATIC },
      { Pharm::FeatureType::NEGATIVE_IONIZABLE, Pharm::PML::FeatureName::NEG_IONIZABLE },
      { Pharm::FeatureType::POSITIVE_IONIZABLE, Pharm::PML::FeatureName::POS_IONIZABLE },
      { Pharm::FeatureType::H_BOND_DONOR, Pharm::PML::FeatureName::H_BOND_DONOR },
      { Pharm::FeatureType::H_BOND_ACCEPTOR, Pharm::PML::FeatureName::H_BOND_ACCEPTOR },
      { Pharm::FeatureType::HALOGEN_BOND_DONOR, Pharm::PML::FeatureName::X_BOND_DONOR },
      { Pharm::FeatureType::HALOGEN_BOND_ACCEPTOR, Pharm::PML::FeatureName::X_BOND_ACCEPTOR }
    };

    const std::string& getLS4FeatureName(unsigned int type)
    {
        FeatureTypeToNameMap::const_iterator it = ls4FeatureNames.find(type);

        if (it == ls4FeatureNames.end())
            return NOT_FOUND;

        return it->second;
    }
}


Pharm::PMLDataWriter::PMLDataWriter(const Base::DataIOBase& io_base): 
    ioBase(io_base), startDoc(true)
{}

bool Pharm::PMLDataWriter::writeFeatureContainer(std::ostream& os, const FeatureContainer& cntnr)
{
    init(os);

    if (startDoc) {
        startDocument(os);

        startDoc = false;
        alignElemId = 0;
        featureId = 1;
    }

    startAlignmentElement(os, cntnr);
    startPharmacophore(os, cntnr);
    writeFeatures(os, cntnr);
    endPharmacophore(os);
    endAlignmentElement(os);

    return os.good(); 
}

void Pharm::PMLDataWriter::init(std::ostream& os)
{
    os << std::fixed << std::boolalpha;

    strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
}

void Pharm::PMLDataWriter::close(std::ostream& os)
{
    if (startDoc)
        return;

    endDocument(os);
    startDoc = true;
}

void Pharm::PMLDataWriter::startDocument(std::ostream& os) const
{
    os << PML::DOC_PROLOG << '\n';
}

void Pharm::PMLDataWriter::endDocument(std::ostream& os) const
{
    os << PML::DOC_EPILOG << '\n';
}

void Pharm::PMLDataWriter::startAlignmentElement(std::ostream& os, const FeatureContainer& cntnr)
{
    using namespace Internal;
    
    beginXMLStartTag(os, PML::Element::ALIGNMENT_ELEM, 2);

    writeXMLAttribute(os, PML::Attribute::NAME, escapeXMLData(getName(cntnr), tmpString, true));
    writeXMLAttribute(os, PML::Attribute::ID, PML::Element::ALIGNMENT_ELEM + std::to_string(alignElemId++));
    writeXMLAttribute(os, PML::Attribute::FLAG_CODE, PML::DEFAULT_FLAG_CODE);

    endXMLStartTag(os);
}

void Pharm::PMLDataWriter::endAlignmentElement(std::ostream& os) const
{
    Internal::writeXMLEndTag(os, PML::Element::ALIGNMENT_ELEM, 2);
}

void Pharm::PMLDataWriter::startPharmacophore(std::ostream& os, const FeatureContainer& cntnr)
{
    using namespace Internal;
    
    beginXMLStartTag(os, PML::Element::PHARMACOPHORE, 3);

    writeXMLAttribute(os, PML::Attribute::NAME, escapeXMLData(getName(cntnr), tmpString, true));
    writeXMLAttribute(os, PML::Attribute::ID, PHARMACOPHORE_ID);
    writeXMLAttribute(os, PML::Attribute::PHARM_TYPE, PML::PHARM_TYPE_LIGAND_SCOUT);

    endXMLStartTag(os);
}

void Pharm::PMLDataWriter::endPharmacophore(std::ostream& os) const
{
    Internal::writeXMLEndTag(os, PML::Element::PHARMACOPHORE, 3);
}

void Pharm::PMLDataWriter::writeFeatures(std::ostream& os, const FeatureContainer& cntnr)
{
    std::size_t id = 0;

    for (FeatureContainer::ConstFeatureIterator it = cntnr.getFeaturesBegin(), end = cntnr.getFeaturesEnd(); it != end; ++it) {
        const Feature& ftr = *it;
        unsigned int ftr_type = getType(ftr);

        if (ftr_type == FeatureType::EXCLUSION_VOLUME) {
            writeXVolume(os, ftr, id++);
            continue;
        }

        const std::string& ls4_name = getLS4FeatureName(ftr_type);

        if (ls4_name.empty()) {
            if (strictErrorChecking)
                throw Base::IOError("PMLDataWriter: output feature type not supported by LigandScout");

            continue;
        }

        switch (getGeometry(ftr)) {

            case FeatureGeometry::SPHERE:
                writePointFeature(os, ftr, ls4_name, id++);
                continue;

            case FeatureGeometry::VECTOR:
                writeVectorFeature(os, ftr, ls4_name, id++,
                                   ftr_type == FeatureType::H_BOND_ACCEPTOR ||
                                   ftr_type == FeatureType::HALOGEN_BOND_ACCEPTOR);
                continue;

            case FeatureGeometry::PLANE:
                writePlaneFeature(os, ftr, ls4_name, id++);
                continue;
    
            default:
                if (strictErrorChecking)
                    throw Base::IOError("PMLDataWriter: output feature geometry not supported by LigandScout");
        }
    } 
}

void Pharm::PMLDataWriter::writeDefaultFeatureAttributes(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id, bool close)
{
    using namespace Internal;
    
    writeXMLAttribute(os, PML::Attribute::NAME, name);
    writeXMLAttribute(os, PML::Attribute::FEATURE_ID, featureId++);
    writeXMLAttribute(os, PML::Attribute::OPTIONAL, getOptionalFlag(ftr));
    writeXMLAttribute(os, PML::Attribute::DISABLED, getDisabledFlag(ftr));
    writeXMLAttribute(os, PML::Attribute::WEIGHT, getWeight(ftr));
    writeXMLAttribute(os, PML::Attribute::ID, FEATURE_ID_PREFIX + std::to_string(id));

    if (close)
        endXMLStartTag(os);
}

void Pharm::PMLDataWriter::writeXVolume(std::ostream& os, const Feature& ftr, std::size_t id)
{
    using namespace Internal;
    
    beginXMLStartTag(os, PML::Element::VOLUME_FEATURE, 4);
    
    writeXMLAttribute(os, PML::Attribute::TYPE, PML::VOLUME_TYPE_EXCLUSION);
    writeXMLAttribute(os, PML::Attribute::FEATURE_ID, featureId++);
    writeXMLAttribute(os, PML::Attribute::OPTIONAL, getOptionalFlag(ftr));
    writeXMLAttribute(os, PML::Attribute::DISABLED, getDisabledFlag(ftr));
    writeXMLAttribute(os, PML::Attribute::WEIGHT, getWeight(ftr));
    writeXMLAttribute(os, PML::Attribute::ID, FEATURE_ID_PREFIX + std::to_string(id));

    endXMLStartTag(os);

    writePositionAndTolerance(os, PML::Element::FEATURE_POSITION, get3DCoordinates(ftr), getTolerance(ftr));

    writeXMLEndTag(os, PML::Element::VOLUME_FEATURE, 4);
}

void Pharm::PMLDataWriter::writePointFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id)
{
    using namespace Internal;
    
    beginXMLStartTag(os, PML::Element::POINT_FEATURE, 4);

    writeDefaultFeatureAttributes(os, ftr, name, id, true);

    writePositionAndTolerance(os, PML::Element::FEATURE_POSITION, get3DCoordinates(ftr), getTolerance(ftr));

    writeXMLEndTag(os, PML::Element::POINT_FEATURE, 4);
}

void Pharm::PMLDataWriter::writeVectorFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id, bool points_to_lig)
{
    using namespace Internal;
    
    beginXMLStartTag(os, PML::Element::VECTOR_FEATURE, 4);

    writeDefaultFeatureAttributes(os, ftr, name, id, false);
    writeXMLAttribute(os, PML::Attribute::HAS_SYN_PROJECTED_POINT, false);
    writeXMLAttribute(os, PML::Attribute::POINTS_TO_LIGAND, points_to_lig);

    endXMLStartTag(os);

    if (points_to_lig) {
        writePositionAndTolerance(os, PML::Element::FEATURE_TARGET, get3DCoordinates(ftr), getTolerance(ftr));
        writePositionAndTolerance(os, PML::Element::FEATURE_ORIGIN, get3DCoordinates(ftr) - (getOrientation(ftr) * getLength(ftr)), 
                                  getTolerance(ftr) * VECTOR_FEATURE_TARGET_TOL_FACTOR);

    } else {
        writePositionAndTolerance(os, PML::Element::FEATURE_ORIGIN, get3DCoordinates(ftr), getTolerance(ftr));
        writePositionAndTolerance(os, PML::Element::FEATURE_TARGET, get3DCoordinates(ftr) + (getOrientation(ftr) * getLength(ftr)), 
                                  getTolerance(ftr) * VECTOR_FEATURE_TARGET_TOL_FACTOR);
    }

    writeXMLEndTag(os, PML::Element::VECTOR_FEATURE, 4);
}

void Pharm::PMLDataWriter::writePlaneFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id)
{
    using namespace Internal;
    
    beginXMLStartTag(os, PML::Element::PLANE_FEATURE, 4);

    writeDefaultFeatureAttributes(os, ftr, name, id, true);

    writePositionAndTolerance(os, PML::Element::FEATURE_POSITION, get3DCoordinates(ftr), getTolerance(ftr));
    writePositionAndTolerance(os, PML::Element::FEATURE_NORMAL, getOrientation(ftr), getTolerance(ftr) * PLANE_FEATURE_SECOND_TOL_FACTOR);

    writeXMLEndTag(os, PML::Element::PLANE_FEATURE, 4);
}

template <typename VE>
void Pharm::PMLDataWriter::writePositionAndTolerance(std::ostream& os, const std::string& tag, const VE& pos, double tol) const
{
    using namespace Internal;
    
    beginXMLStartTag(os, tag, 5);

    writeXMLAttribute(os, PML::Attribute::COORDS_X, pos[0]);
    writeXMLAttribute(os, PML::Attribute::COORDS_Y, pos[1]);
    writeXMLAttribute(os, PML::Attribute::COORDS_Z, pos[2]);
    writeXMLAttribute(os, PML::Attribute::TOLERANCE, tol);

    endXMLStartTag(os, true);
}
