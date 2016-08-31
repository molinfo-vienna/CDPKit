/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataWriter.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"

#include "CDFDataWriter.hpp"


using namespace CDPL;


bool Pharm::CDFDataWriter::writePharmacophore(std::ostream& os, const Pharmacophore& pharm)
{
	init();

	outputPharmHeader(pharm);
	outputFeatures(pharm);
	outputPharmProperties(pharm);

	return writeRecordData(os);
}

void Pharm::CDFDataWriter::init()
{
	strictErrorChecking(getStrictErrorCheckingParameter(ioBase)); 
	singlePrecisionFloats(getCDFWriteSinglePrecisionFloatsParameter(ioBase));

	dataBuffer.setIOPointer(0);
}

void Pharm::CDFDataWriter::outputPharmHeader(const Pharmacophore& pharm)
{
	cdfHeader.recordTypeID = CDF::PHARMACOPHORE_RECORD_ID;
	cdfHeader.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

	dataBuffer.putInt(boost::numeric_cast<CDF::SizeType>(pharm.getNumFeatures()), false);
}

void Pharm::CDFDataWriter::outputFeatures(const Pharmacophore& pharm)
{
	for (Pharmacophore::ConstFeatureIterator it = pharm.getFeaturesBegin(), end = pharm.getFeaturesEnd(); 
		 it != end; ++it) {

		const Feature& feature = *it;

		dataBuffer.putInt(CDF::PROP_LIST_END, false);
	}
}

void Pharm::CDFDataWriter::outputPharmProperties(const Pharmacophore& pharm)
{
	dataBuffer.putInt(CDF::PROP_LIST_END, false);
}

bool Pharm::CDFDataWriter::writeRecordData(std::ostream& os)
{
	dataBuffer.resize(dataBuffer.getIOPointer());

	cdfHeader.recordDataLength = boost::numeric_cast<CDF::SizeType>(dataBuffer.getSize());

	if (!writeHeader(os, cdfHeader))
		return false;

	dataBuffer.writeBuffer(os);

	return os.good();
}
