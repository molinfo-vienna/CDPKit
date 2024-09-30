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
      { Pharm::FeatureType::HYDROPHOBIC, Pharm::PML::HYDROPHOBIC_FEATURE_NAME },
      { Pharm::FeatureType::AROMATIC, Pharm::PML::AROMATIC_FEATURE_NAME },
      { Pharm::FeatureType::NEGATIVE_IONIZABLE, Pharm::PML::NEG_IONIZABLE_FEATURE_NAME },
      { Pharm::FeatureType::POSITIVE_IONIZABLE, Pharm::PML::POS_IONIZABLE_FEATURE_NAME },
      { Pharm::FeatureType::H_BOND_DONOR, Pharm::PML::H_BOND_DONOR_FEATURE_NAME },
      { Pharm::FeatureType::H_BOND_ACCEPTOR, Pharm::PML::H_BOND_ACCEPTOR_FEATURE_NAME },
      { Pharm::FeatureType::HALOGEN_BOND_DONOR, Pharm::PML::X_BOND_DONOR_FEATURE_NAME },
      { Pharm::FeatureType::HALOGEN_BOND_ACCEPTOR, Pharm::PML::X_BOND_ACCEPTOR_FEATURE_NAME }
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
    ioBase(io_base), writeHeader(true), strictErrorChecking(true)
{}

bool Pharm::PMLDataWriter::writeFeatureContainer(std::ostream& os, const FeatureContainer& cntnr)
{
    init(os);

    if (writeHeader) {
        writeElemContainerHeader(os);

        writeHeader = false;
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
    if (writeHeader)
        return;

    writeElemContainerFooter(os);
    writeHeader = true;
}

void Pharm::PMLDataWriter::writeElemContainerHeader(std::ostream& os) const
{
    os << PML::ELEM_CONTAINER_HEADER << '\n';
}

void Pharm::PMLDataWriter::writeElemContainerFooter(std::ostream& os) const
{
    os << PML::ELEM_CONTAINER_FOOTER << '\n';
}

void Pharm::PMLDataWriter::startAlignmentElement(std::ostream& os, const FeatureContainer& cntnr)
{
    writeStartTag(os, PML::ALIGNMENT_ELEM_TAG, false);

    writeAttribute(os, PML::NAME_ATTRIBUTE, getName(cntnr), false);
    writeAttribute(os, PML::ID_ATTRIBUTE, PML::ALIGNMENT_ELEM_TAG + std::to_string(alignElemID++), false);
    writeAttribute(os, PML::FLAG_CODE_ATTRIBUTE, PML::DEFAULT_FLAG_CODE, true);
}

void Pharm::PMLDataWriter::endAlignmentElement(std::ostream& os) const
{
    writeEndTag(os, PML::ALIGNMENT_ELEM_TAG);
}

void Pharm::PMLDataWriter::startPharmacophore(std::ostream& os, const FeatureContainer& cntnr) const
{
    writeStartTag(os, PML::PHARMACOPHORE_TAG, false);

    writeAttribute(os, PML::NAME_ATTRIBUTE, getName(cntnr), false);
    writeAttribute(os, PML::ID_ATTRIBUTE, PML::PHARMACOPHORE_TAG + '0', false);
    writeAttribute(os, PML::PHARM_TYPE_ATTRIBUTE, PML::PHARM_TYPE_LIGAND_SCOUT, true);
}

void Pharm::PMLDataWriter::endPharmacophore(std::ostream& os) const
{
    writeEndTag(os, PML::PHARMACOPHORE_TAG);
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
    writeAttribute(os, PML::NAME_ATTRIBUTE, name, false);
    writeAttribute(os, PML::FEATURE_ID_ATTRIBUTE, featureID++, false);
    writeAttribute(os, PML::OPTIONAL_ATTRIBUTE, getOptionalFlag(ftr), false);
    writeAttribute(os, PML::DISABLED_ATTRIBUTE, getDisabledFlag(ftr), false);
    writeAttribute(os, PML::WEIGHT_ATTRIBUTE, getWeight(ftr), false);
    writeAttribute(os, PML::ID_ATTRIBUTE, "feature" + std::to_string(id), close);
}

void Pharm::PMLDataWriter::writeXVolume(std::ostream& os, const Feature& ftr, std::size_t id)
{
    writeStartTag(os, PML::VOLUME_FEATURE_TAG, false);
    
    writeAttribute(os, PML::TYPE_ATTRIBUTE, PML::VOLUME_TYPE_EXCLUSION, false);
    writeAttribute(os, PML::FEATURE_ID_ATTRIBUTE, featureID++, false);
    writeAttribute(os, PML::OPTIONAL_ATTRIBUTE, getOptionalFlag(ftr), false);
    writeAttribute(os, PML::DISABLED_ATTRIBUTE, getDisabledFlag(ftr), false);
    writeAttribute(os, PML::WEIGHT_ATTRIBUTE, getWeight(ftr), false);
    writeAttribute(os, PML::ID_ATTRIBUTE, "feature" + std::to_string(id), true);

    writePositionAndTolerance(os, PML::FEATURE_POSITION_TAG, get3DCoordinates(ftr), getTolerance(ftr));

    writeEndTag(os, PML::VOLUME_FEATURE_TAG);
}

void Pharm::PMLDataWriter::writePointFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id)
{
    writeStartTag(os, PML::POINT_FEATURE_TAG, false);

    writeDefaultFeatureAttributes(os, ftr, name, id, true);

    writePositionAndTolerance(os, PML::FEATURE_POSITION_TAG, get3DCoordinates(ftr), getTolerance(ftr));

    writeEndTag(os, PML::POINT_FEATURE_TAG);
}

void Pharm::PMLDataWriter::writeVectorFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id, bool points_to_lig)
{
    writeStartTag(os, PML::VECTOR_FEATURE_TAG, false);

    writeDefaultFeatureAttributes(os, ftr, name, id, false);
    writeAttribute(os, PML::PROJECTED_POINT_ATTRIBUTE, false, false);
    writeAttribute(os, PML::POINTS_TO_LIGAND_ATTRIBUTE, points_to_lig, true);

    if (points_to_lig) {
        writePositionAndTolerance(os, PML::FEATURE_TARGET_TAG, get3DCoordinates(ftr), getTolerance(ftr));
        writePositionAndTolerance(os, PML::FEATURE_ORIGIN_TAG, get3DCoordinates(ftr) - (getOrientation(ftr) * getLength(ftr)), 
                                  getTolerance(ftr) * VECTOR_FEATURE_TARGET_TOL_FACTOR);

    } else {
        writePositionAndTolerance(os, PML::FEATURE_ORIGIN_TAG, get3DCoordinates(ftr), getTolerance(ftr));
        writePositionAndTolerance(os, PML::FEATURE_TARGET_TAG, get3DCoordinates(ftr) + (getOrientation(ftr) * getLength(ftr)), 
                                  getTolerance(ftr) * VECTOR_FEATURE_TARGET_TOL_FACTOR);
    }

    writeEndTag(os, PML::VECTOR_FEATURE_TAG);
}

void Pharm::PMLDataWriter::writePlaneFeature(std::ostream& os, const Feature& ftr, const std::string& name, std::size_t id)
{
    writeStartTag(os, PML::PLANE_FEATURE_TAG, false);

    writeDefaultFeatureAttributes(os, ftr, name, id, true);

    writePositionAndTolerance(os, PML::FEATURE_POSITION_TAG, get3DCoordinates(ftr), getTolerance(ftr));
    writePositionAndTolerance(os, PML::FEATURE_NORMAL_TAG, getOrientation(ftr), getTolerance(ftr) * PLANE_FEATURE_SECOND_TOL_FACTOR);

    writeEndTag(os, PML::PLANE_FEATURE_TAG);
}

template <typename VE>
void Pharm::PMLDataWriter::writePositionAndTolerance(std::ostream& os, const std::string& tag, const VE& pos, double tol) const
{
    writeStartTag(os, tag, false);

    writeAttribute(os, PML::COORDS_X_ATTRIBUTE, pos[0], false);
    writeAttribute(os, PML::COORDS_Y_ATTRIBUTE, pos[1], false);
    writeAttribute(os, PML::COORDS_Z_ATTRIBUTE, pos[2], false);
    writeAttribute(os, PML::TOLERANCE_ATTRIBUTE, tol, true, true);
}

void Pharm::PMLDataWriter::writeStartTag(std::ostream& os, const std::string& tag, bool close) const
{
    os << '<' << tag;

    if (close)
        os << ">\n";
}

void Pharm::PMLDataWriter::writeEndTag(std::ostream& os, const std::string& tag) const
{
    os << "</" << tag << ">\n";
}

template <typename T>
void Pharm::PMLDataWriter::writeAttribute(std::ostream& os, const std::string& name, const T& value, bool close, bool empty) const
{
    os << ' ' << name << "=\"" << value << "\"";

    if (close) 
        os << (empty ? " />\n" : ">\n");
}
