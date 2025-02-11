/* 
 * PSDPharmacophoreByteBufferReader.cpp 
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

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"

#include "CDFDataReader.hpp"
#include "PSDPharmacophoreByteBufferReader.hpp"
#include "PSDPharmacophoreDataFormat.hpp"
#include "PSDDataIOUtilities.hpp"


using namespace CDPL;


Pharm::PSDPharmacophoreByteBufferReader::PSDPharmacophoreByteBufferReader()
{
    setStrictErrorCheckingParameter(*this, true);
}

Pharm::PSDPharmacophoreByteBufferReader::~PSDPharmacophoreByteBufferReader()
{}

void Pharm::PSDPharmacophoreByteBufferReader::readPharmacophore(Internal::ByteBuffer& bbuf, Pharmacophore& pharm)
{
    try {
        if (containsCDFData(bbuf)) {
            if (!cdfReader)
                cdfReader.reset(new CDFDataReader(*this));

            if (!cdfReader->readPharmacophore(pharm, bbuf))
                throw PSDIOError("PSDPharmacophoreByteBufferReader: reading pharmacophore data failed");

            return;
        }

        readHeaderAndName(bbuf, pharm);

        if (bbuf.getIOPointer() == bbuf.getSize())
            return;

        readFeatures(bbuf, pharm);

    } catch (const PSDIOError& e) {
        throw e;

    } catch (const std::exception& e) {
        throw Base::IOError(std::string("PSDPharmacophoreByteBufferReader: reading pharmacophore data failed: ") + e.what());
    }
}

void Pharm::PSDPharmacophoreByteBufferReader::readHeaderAndName(Internal::ByteBuffer& bbuf, Pharmacophore& pharm)
{
    using namespace PSDPharmacophoreDataFormat;
    
    std::uint8_t tmp = 0;

    // header
    bbuf.setIOPointer(0);
    bbuf.getInt(tmp);
    
    if (tmp != FORMAT_ID)
        throw PSDIOError("PSDPharmacophoreByteBufferReader: invalid pharmacophore data format");

    bbuf.getInt(tmp);

    if ((tmp & VERSION_MASK) != CURR_VERSION) // so far there is only one version
        throw PSDIOError("PSDPharmacophoreByteBufferReader: invalid pharmacophore data format version");

    // name
    if (tmp & NAME_LENGTH_BYTE_COUNT_MASK) {
        std::uint32_t name_len = 0;

        bbuf.getInt(name_len, (tmp & NAME_LENGTH_BYTE_COUNT_MASK) >> NAME_LENGTH_BYTE_COUNT_SHIFT);

        pharmName.resize(name_len);

        bbuf.getBytes(pharmName.data(), name_len);

        setName(pharm, pharmName);
    }
}

void Pharm::PSDPharmacophoreByteBufferReader::readFeatures(Internal::ByteBuffer& bbuf, Pharmacophore& pharm) const
{
    using namespace PSDPharmacophoreDataFormat;
    namespace Feature = PSDPharmacophoreDataFormat::Feature;
    
    std::uint8_t tmp;
    std::uint32_t ftr_count = 0;

    bbuf.getInt(tmp);
    bbuf.getInt(ftr_count, tmp & FEATURE_COUNT_BYTE_COUNT_MASK);
    
    float pos_trans_vec[3] = { 0.0f };
    float pos_scaling_fact = 1.0f;

    if (tmp & FEATURE_X_POS_TRANSLATION_FLAG)
        bbuf.getFloat(pos_trans_vec[0]);

    if (tmp & FEATURE_Y_POS_TRANSLATION_FLAG)
        bbuf.getFloat(pos_trans_vec[1]);
    
    if (tmp & FEATURE_Z_POS_TRANSLATION_FLAG)
        bbuf.getFloat(pos_trans_vec[2]);

    if (tmp & FEATURE_POS_SCALING_FACTOR_FLAG)
        bbuf.getFloat(pos_scaling_fact);

    for (std::size_t i = 0; i < ftr_count; i++) {
        auto& ftr = pharm.addFeature();
        std::uint8_t prop_flags = 0;

        bbuf.getInt(prop_flags);
     
        if ((prop_flags & Feature::TYPE_FLAG) || (prop_flags & Feature::GEOMETRY_FLAG)) {
            std::uint8_t type_and_geo = 0;

            bbuf.getInt(type_and_geo);
         
            if (prop_flags & Feature::TYPE_FLAG)
                setType(ftr, type_and_geo & Feature::TYPE_MASK);

            if (prop_flags & Feature::GEOMETRY_FLAG)
                setGeometry(ftr, (type_and_geo & Feature::GEOMETRY_MASK) >> Feature::GEOMETRY_SHIFT);
        }

        std::int16_t i16_val = 0;
        
        if (prop_flags & Feature::POSITION_FLAG) {
            Math::Vector3D pos;

            for (std::size_t j = 0; j < 3; j++) {
                bbuf.getInt(i16_val);

                pos(j) = (int16FixedToFloatingPoint<double>(i16_val, Feature::POSITION_PRECISION) - pos_trans_vec[j]) / pos_scaling_fact;
            }

            set3DCoordinates(ftr, pos);
        }
       
        if (prop_flags & Feature::ORIENTATION_FLAG) {
            Math::Vector3D orient;

            for (std::size_t j = 0; j < 3; j++) {
                bbuf.getInt(i16_val);

                orient(j) = int16FixedToFloatingPoint<double>(i16_val, Feature::ORIENTATION_PRECISION);
            }

            setOrientation(ftr, orient);
        }

        if (prop_flags & Feature::TOLERANCE_FLAG) {
            bbuf.getInt(i16_val);

            setTolerance(ftr, int16FixedToFloatingPoint<double>(i16_val, Feature::TOLERANCE_PRECISION));
        }
        
        if (prop_flags & Feature::LENGTH_FLAG) {
            bbuf.getInt(i16_val);

            setLength(ftr, int16FixedToFloatingPoint<double>(i16_val, Feature::LENGTH_PRECISION));
        }
        
        if (prop_flags & Feature::WEIGHT_FLAG) {
            bbuf.getInt(i16_val);

            setWeight(ftr, int16FixedToFloatingPoint<double>(i16_val, Feature::WEIGHT_PRECISION));
        }
        
        if (prop_flags & Feature::HYDROPHOBICITY_FLAG) {
            bbuf.getInt(i16_val);

            setHydrophobicity(ftr, int16FixedToFloatingPoint<double>(i16_val, Feature::HYDROPHOBICITY_PRECISION));
        }
    }
}
