/* 
 * PSDFeatureContainerByteBufferWriter.cpp 
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

#include <cstdint>

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "PSDFeatureContainerByteBufferWriter.hpp"
#include "PSDPharmacophoreDataFormat.hpp"
#include "PSDDataIOUtilities.hpp"


using namespace CDPL;


Pharm::PSDFeatureContainerByteBufferWriter::PSDFeatureContainerByteBufferWriter()
{}

Pharm::PSDFeatureContainerByteBufferWriter::~PSDFeatureContainerByteBufferWriter()
{}

void Pharm::PSDFeatureContainerByteBufferWriter::writeFeatureContainer(const FeatureContainer& cntnr, Internal::ByteBuffer& byte_buf)
{
    try {
        doWriteFeatureContainer(cntnr, byte_buf);

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDFeatureContainerByteBufferWriter: writing pharmacophore data failed: ") + e.what());
    }
}

void Pharm::PSDFeatureContainerByteBufferWriter::doWriteFeatureContainer(const FeatureContainer& cntnr, Internal::ByteBuffer& byte_buf)
{
    using namespace PSDPharmacophoreDataFormat;

    byte_buf.resize(0);
    byte_buf.setIOPointer(0);
    byte_buf.putInt(FORMAT_ID, false);

    std::uint32_t name_len = 0; 
    std::uint8_t name_len_sto_size = 0;
    
    if (hasName(cntnr)) {
        auto& name = getName(cntnr);

        if (!name.empty()) {
            name_len = boost::numeric_cast<std::uint32_t>(name.size());
            byte_buf.setIOPointer(2);

            name_len_sto_size = byte_buf.putInt(name_len, true);

            byte_buf.putBytes(name.c_str(), name_len);
            byte_buf.setIOPointer(1);
        }
    }

    byte_buf.putInt(std::uint8_t(CURR_VERSION + (name_len_sto_size << NAME_LENGTH_BYTE_COUNT_SHIFT)), false);
    
    std::uint32_t ftr_cnt = boost::numeric_cast<std::uint32_t>(cntnr.getNumFeatures());

    if (ftr_cnt == 0)
        return;

    double pos_trans_vec[3] = { 0.0 };
    double pos_scaling_fact = 1.0;
    std::uint8_t trans_flags = 0;
    
    ftrPosCoords.clear();

    for (auto& ftr : cntnr) {
        if (!has3DCoordinates(ftr))
            continue;

        auto& coords = get3DCoordinates(ftr);

        for (int i = 0; i < 3; i++) 
            ftrPosCoords.push_back(coords(i));
    }

    calcCoordsTransform(ftrPosCoords, pos_trans_vec, pos_scaling_fact, Feature::POSITION_PRECISION);
    
    auto saved_io_ptr = byte_buf.getSize();
    
    byte_buf.setIOPointer(saved_io_ptr + 1);

    std::uint8_t ftr_cnt_stor_size = byte_buf.putInt(ftr_cnt, true);

    if (pos_trans_vec[0] != 0.0) {
        trans_flags |= FEATURE_X_POS_TRANSLATION_FLAG;
        byte_buf.putFloat(float(pos_trans_vec[0]));
    }
    
    if (pos_trans_vec[1] != 0.0) {
        trans_flags |= FEATURE_Y_POS_TRANSLATION_FLAG;
        byte_buf.putFloat(float(pos_trans_vec[1]));
    }
    
    if (pos_trans_vec[2] != 0.0) {
        trans_flags |= FEATURE_Z_POS_TRANSLATION_FLAG;
        byte_buf.putFloat(float(pos_trans_vec[2]));
    }
    
    if (pos_scaling_fact != 1.0) {
        trans_flags |= FEATURE_POS_SCALING_FACTOR_FLAG;
        byte_buf.putFloat(float(pos_scaling_fact));
    }
    
    byte_buf.setIOPointer(saved_io_ptr);
    byte_buf.putInt(std::uint8_t(ftr_cnt_stor_size + trans_flags), false);
    byte_buf.setIOPointer(byte_buf.getSize());

    for (auto& ftr : cntnr) {
        std::uint8_t prop_flags = 0;

        if (hasType(ftr))
            prop_flags |= Feature::TYPE_FLAG;

        if (hasGeometry(ftr))
            prop_flags |= Feature::GEOMETRY_FLAG;

        if (Chem::has3DCoordinates(ftr))
            prop_flags |= Feature::POSITION_FLAG;

        if (hasOrientation(ftr))
            prop_flags |= Feature::ORIENTATION_FLAG;

        if (hasTolerance(ftr))
            prop_flags |= Feature::TOLERANCE_FLAG;

        if (hasLength(ftr))
            prop_flags |= Feature::LENGTH_FLAG;

        if (hasWeight(ftr))
            prop_flags |= Feature::WEIGHT_FLAG;

        if (hasHydrophobicity(ftr))
            prop_flags |= Feature::HYDROPHOBICITY_FLAG;

        byte_buf.putInt(prop_flags, false);

        if ((prop_flags & Feature::TYPE_FLAG) || (prop_flags & Feature::GEOMETRY_FLAG)) {
            std::uint8_t type_and_geo = 0;

            if (prop_flags & Feature::TYPE_FLAG)
                type_and_geo = getType(ftr);

            if (prop_flags & Feature::GEOMETRY_FLAG)
                type_and_geo |= (getGeometry(ftr) << Feature::GEOMETRY_SHIFT);

            byte_buf.putInt(type_and_geo, false);
        }

        if (prop_flags & Feature::POSITION_FLAG) {
            auto& pos = Chem::get3DCoordinates(ftr);

            for (int i = 0; i < 3; i++)
                byte_buf.putInt(floatingToInt16FixedPoint(pos_trans_vec[i] + pos(i) * pos_scaling_fact, Feature::POSITION_PRECISION), false);
        }

        if (prop_flags & Feature::ORIENTATION_FLAG) {
            auto& orient = getOrientation(ftr);

            for (int i = 0; i < 3; i++)
                byte_buf.putInt(floatingToInt16FixedPoint(orient(i), Feature::ORIENTATION_PRECISION), false);
        }

        if (prop_flags & Feature::TOLERANCE_FLAG)
            byte_buf.putInt(floatingToInt16FixedPoint(getTolerance(ftr), Feature::TOLERANCE_PRECISION), false);

        if (prop_flags & Feature::LENGTH_FLAG)
            byte_buf.putInt(floatingToInt16FixedPoint(getLength(ftr), Feature::LENGTH_PRECISION), false);

        if (prop_flags & Feature::WEIGHT_FLAG)
            byte_buf.putInt(floatingToInt16FixedPoint(getWeight(ftr), Feature::WEIGHT_PRECISION), false);

        if (prop_flags & Feature::HYDROPHOBICITY_FLAG)
            byte_buf.putInt(floatingToInt16FixedPoint(getHydrophobicity(ftr), Feature::HYDROPHOBICITY_PRECISION), false);
    }
} 
