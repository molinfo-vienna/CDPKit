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
#include <cstddef>

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


void Pharm::PSDFeatureContainerByteBufferWriter::writeFeatureContainer(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf)
{
    try {
        outputHeaderAndName(cntnr, bbuf);
        outputFeatures(cntnr, bbuf);

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDFeatureContainerByteBufferWriter: writing pharmacophore data failed: ") + e.what());
    }
}

void Pharm::PSDFeatureContainerByteBufferWriter::outputHeaderAndName(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf) const
{
    using namespace PSDPharmacophoreDataFormat;

    // header
    bbuf.resize(0);
    bbuf.setIOPointer(0);
    bbuf.putInt(FORMAT_ID, false);

    // name
    std::uint32_t name_len = 0; 
    std::uint8_t name_len_sto_size = 0;
    
    if (hasName(cntnr)) {
        auto& name = getName(cntnr);

        name_len = boost::numeric_cast<std::uint32_t>(name.size());
        bbuf.setIOPointer(2);
        
        name_len_sto_size = bbuf.putInt(name_len, true);

        bbuf.putBytes(name.data(), name_len);
        bbuf.setIOPointer(1);
    }

    bbuf.putInt(std::uint8_t(CURR_VERSION + (name_len_sto_size << NAME_LENGTH_BYTE_COUNT_SHIFT)), false);
}

void Pharm::PSDFeatureContainerByteBufferWriter::outputFeatures(const FeatureContainer& cntnr, Internal::ByteBuffer& bbuf)
{
    using namespace PSDPharmacophoreDataFormat;
    namespace Feature = PSDPharmacophoreDataFormat::Feature;
    
    std::uint32_t ftr_cnt = boost::numeric_cast<std::uint32_t>(cntnr.getNumFeatures());

    if (ftr_cnt == 0)
        return;

    double pos_trans_vec[3] = { 0.0 };
    double pos_scaling_fact = 1.0;
    std::uint8_t trans_flags = 0;
    
    coordinates.clear();

    for (auto& ftr : cntnr)
        if (has3DCoordinates(ftr))
            coordinates.addElement(get3DCoordinates(ftr));

    calcCoordsTransform(coordinates, pos_trans_vec, pos_scaling_fact, Feature::POSITION_PRECISION);
    
    auto saved_io_ptr = bbuf.getSize();
    
    bbuf.setIOPointer(saved_io_ptr + 1);

    std::uint8_t ftr_cnt_stor_size = bbuf.putInt(ftr_cnt, true);

    if (pos_trans_vec[0] != 0.0) {
        trans_flags |= FEATURE_X_POS_TRANSLATION_FLAG;
        bbuf.putFloat(float(pos_trans_vec[0]));
    }
    
    if (pos_trans_vec[1] != 0.0) {
        trans_flags |= FEATURE_Y_POS_TRANSLATION_FLAG;
        bbuf.putFloat(float(pos_trans_vec[1]));
    }
    
    if (pos_trans_vec[2] != 0.0) {
        trans_flags |= FEATURE_Z_POS_TRANSLATION_FLAG;
        bbuf.putFloat(float(pos_trans_vec[2]));
    }
    
    if (pos_scaling_fact != 1.0) {
        trans_flags |= FEATURE_POS_SCALING_FACTOR_FLAG;
        bbuf.putFloat(float(pos_scaling_fact));
    }
    
    bbuf.setIOPointer(saved_io_ptr);
    bbuf.putInt(std::uint8_t(ftr_cnt_stor_size + trans_flags), false);
    bbuf.setIOPointer(bbuf.getSize());

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

        bbuf.putInt(prop_flags, false);

        if ((prop_flags & Feature::TYPE_FLAG) || (prop_flags & Feature::GEOMETRY_FLAG)) {
            std::uint8_t type_and_geo = 0;

            if (prop_flags & Feature::TYPE_FLAG)
                type_and_geo = getType(ftr);

            if (prop_flags & Feature::GEOMETRY_FLAG)
                type_and_geo |= (getGeometry(ftr) << Feature::GEOMETRY_SHIFT);

            bbuf.putInt(type_and_geo, false);
        }

        if (prop_flags & Feature::POSITION_FLAG) {
            auto& pos = Chem::get3DCoordinates(ftr);

            for (std::size_t i = 0; i < 3; i++)
                bbuf.putInt(floatingToInt16FixedPoint(pos_trans_vec[i] + pos(i) * pos_scaling_fact, Feature::POSITION_PRECISION), false);
        }

        if (prop_flags & Feature::ORIENTATION_FLAG) {
            auto& orient = getOrientation(ftr);

            for (std::size_t i = 0; i < 3; i++)
                bbuf.putInt(floatingToInt16FixedPoint(orient(i), Feature::ORIENTATION_PRECISION), false);
        }

        if (prop_flags & Feature::TOLERANCE_FLAG)
            bbuf.putInt(floatingToInt16FixedPoint(getTolerance(ftr), Feature::TOLERANCE_PRECISION), false);

        if (prop_flags & Feature::LENGTH_FLAG)
            bbuf.putInt(floatingToInt16FixedPoint(getLength(ftr), Feature::LENGTH_PRECISION), false);

        if (prop_flags & Feature::WEIGHT_FLAG)
            bbuf.putInt(floatingToInt16FixedPoint(getWeight(ftr), Feature::WEIGHT_PRECISION), false);

        if (prop_flags & Feature::HYDROPHOBICITY_FLAG)
            bbuf.putInt(floatingToInt16FixedPoint(getHydrophobicity(ftr), Feature::HYDROPHOBICITY_PRECISION), false);
    }
}
