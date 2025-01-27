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

void Pharm::PSDPharmacophoreByteBufferReader::readPharmacophore(Internal::ByteBuffer& byte_buf, Pharmacophore& pharm)
{
    if (containsCDFData(byte_buf)) {
        if (!cdfReader)
            cdfReader.reset(new CDFDataReader(*this));

        cdfReader->readPharmacophore(pharm, byte_buf);
        return;
    }

    using namespace PSDPharmacophoreDataFormat;

    std::uint8_t tmp;

    byte_buf.setIOPointer(0);
    byte_buf.getInt(tmp);

    if (tmp != FORMAT_ID)
        throw Base::IOError("PSDPharmacophoreByteBufferReader: invalid pharmacophore data format");

    byte_buf.getInt(tmp);

    if ((tmp & VERSION_MASK) != CURR_VERSION)
        throw Base::IOError("PSDPharmacophoreByteBufferReader: invalid pharmacophore data format version");

    
} 
