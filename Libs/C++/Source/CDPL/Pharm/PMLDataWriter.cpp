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
    ioBase(io_base), wrtHeader(true), strictErrorChecking(true)
{}

bool Pharm::PMLDataWriter::writeFeatureContainer(std::ostream& os, const FeatureContainer& cntnr)
{
    init(os);

    if (wrtHeader) {
        writeHeader(os);

        wrtHeader = false;
        alignElemID = 0;
        featureID = 1;
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
    if (wrtHeader)
        return;

    writeFooter(os);
    wrtHeader = true;
}

void Pharm::PMLDataWriter::writeHeader(std::ostream& os) const
{
    os << PML::HEADER << '\n';
}

void Pharm::PMLDataWriter::writeFooter(std::ostream& os) const
{
    os << PML::FOOTER << '\n';
}

void Pharm::PMLDataWriter::startAlignmentElement(std::ostream& os, const FeatureContainer& cntnr)
{
    using namespace Internal;
    
    writeStartTag(os, PML::Element::ALIGNMENT_ELEM, false, 2);

    writeAttribute(os, PML::Attribute::NAME, getName(cntnr), false);
    writeAttribute(os, PML::Attribute::ID, PML::Element::ALIGNMENT_ELEM + std::to_string(alignElemID++), false);
    writeAttribute(os, PML::Attribute::FLAG_CODE, PML::DEFAULT_FLAG_CODE, true);
}

void Pharm::PMLDataWriter::endAlignmentElement(std::ostream& os) const
{
    Internal::writeEndTag(os, PML::Element::ALIGNMENT_ELEM, 2);
}

void Pharm::PMLDataWriter::startPharmacophore(std::ostream& os, const FeatureContainer& cntnr) const
{
    using namespace Internal;
    
    writeStartTag(os, PML::Element::PHARMACOPHORE, false, 3);

    writeAttribute(os, PML::Attribute::NAME, getName(cntnr), false);
    writeAttribute(os, PML::Attribute::ID, PML::Element::PHARMACOPHORE + '0', false);
    writeAttribute(os, PML::Attribute::PHARM_TYPE, PML::PHARM_TYPE_LIGAND_SCOUT, true);
}

void Pharm::PMLDataWriter::endPharmacophore(std::ostream& os) const
{
    Internal::writeEndTag(os, PML::Element::PHARMACOPHORE, 3);
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
    
    writeAttribute(os, PML::Attribute::NAME, name, false);
    writeAttribute(os, PML::Attribute::FEATURE_ID, featureID++, false);
    writeAttribute(os, PML::Attribute::OPTIONAL, getOptionalFlag(ftr), false);
    writeAttribute(os, PML::Attribute::DISABLED, getDisabledFlag(ftr), false);
    writeAttribute(os, PML::Attribute::WEIGHT, getWeight(ftr), false);
    writeAttribute(os, PML::Attribute::ID, "feature" + std::to_string(id), close);
}

void Pharm::PMLDataWriter::writeXVolume(std::ostream& os, const Feature& ftr, std::size_t id)
{
    using namespace Internal;
    
    writeStartTag(os, PML::Element::VOLUME_FEATURE, false, 4);
    
    writeAttribute(os, PML::Attribute::TYPE, PML::VOLUME_TYPE_EXCLUSION, false);
    writeAttribute(os, PML::Attribute::FEATURE_ID, featureID++, false);
    writeAttribute(os, PML::Attribute::OPTIONAL, getOptionalFlag(ftr), false);
    writeAttribute(os, PML::Attribute::DISABLED, getDisabledFlag(ftr), false);
    writeAttribute(os, PML::Attribute::WEIGHT, getWeight(ftr), false);
    writeAttribute(os, PML::Attribute::ID, "feature" + std::to_string(id), true);

    writePositionAndTolerance(os, PML::Element::FEATURE_POSITION, get3DCoordinates(ftr), getTolerance(ftr));

    writeEndTag(os, PML::Element::VOLUME_FEATURE, 4);
}

void Pharm::PMLDataWriter::writePointFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id)
{
    using namespace Internal;
    
    writeStartTag(os, PML::Element::POINT_FEATURE, false, 4);

    writeDefaultFeatureAttributes(os, ftr, name, id, true);

    writePositionAndTolerance(os, PML::Element::FEATURE_POSITION, get3DCoordinates(ftr), getTolerance(ftr));

    writeEndTag(os, PML::Element::POINT_FEATURE, 4);
}

void Pharm::PMLDataWriter::writeVectorFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id, bool points_to_lig)
{
    using namespace Internal;
    
    writeStartTag(os, PML::Element::VECTOR_FEATURE, false, 4);

    writeDefaultFeatureAttributes(os, ftr, name, id, false);
    writeAttribute(os, PML::Attribute::HAS_SYN_PROJECTED_POINT, false, false);
    writeAttribute(os, PML::Attribute::POINTS_TO_LIGAND, points_to_lig, true);

    if (points_to_lig) {
        writePositionAndTolerance(os, PML::Element::FEATURE_TARGET, get3DCoordinates(ftr), getTolerance(ftr));
        writePositionAndTolerance(os, PML::Element::FEATURE_ORIGIN, get3DCoordinates(ftr) - (getOrientation(ftr) * getLength(ftr)), 
                                  getTolerance(ftr) * VECTOR_FEATURE_TARGET_TOL_FACTOR);

    } else {
        writePositionAndTolerance(os, PML::Element::FEATURE_ORIGIN, get3DCoordinates(ftr), getTolerance(ftr));
        writePositionAndTolerance(os, PML::Element::FEATURE_TARGET, get3DCoordinates(ftr) + (getOrientation(ftr) * getLength(ftr)), 
                                  getTolerance(ftr) * VECTOR_FEATURE_TARGET_TOL_FACTOR);
    }

    writeEndTag(os, PML::Element::VECTOR_FEATURE, 4);
}

void Pharm::PMLDataWriter::writePlaneFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id)
{
    using namespace Internal;
    
    writeStartTag(os, PML::Element::PLANE_FEATURE, false, 4);

    writeDefaultFeatureAttributes(os, ftr, name, id, true);

    writePositionAndTolerance(os, PML::Element::FEATURE_POSITION, get3DCoordinates(ftr), getTolerance(ftr));
    writePositionAndTolerance(os, PML::Element::FEATURE_NORMAL, getOrientation(ftr), getTolerance(ftr) * PLANE_FEATURE_SECOND_TOL_FACTOR);

    writeEndTag(os, PML::Element::PLANE_FEATURE, 4);
}

template <typename VE>
void Pharm::PMLDataWriter::writePositionAndTolerance(std::ostream& os, const std::string& tag, const VE& pos, double tol) const
{
    using namespace Internal;
    
    writeStartTag(os, tag, false, 5);

    writeAttribute(os, PML::Attribute::COORDS_X, pos[0], false);
    writeAttribute(os, PML::Attribute::COORDS_Y, pos[1], false);
    writeAttribute(os, PML::Attribute::COORDS_Z, pos[2], false);
    writeAttribute(os, PML::Attribute::TOLERANCE, tol, true, true);
}
