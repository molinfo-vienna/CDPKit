/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFFragmentLibraryDataWriter.cpp 
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

#include "CDPL/Chem/ControlParameterFunctions.hpp"

#include "CDFFragmentLibraryDataWriter.hpp"
#include "CDFMoleculeDataFunctions.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


ConfGen::CDFFragmentLibraryDataWriter::CDFFragmentLibraryDataWriter(): molWriter(ctrlParams) 
{
	Chem::setStrictErrorCheckingParameter(ctrlParams, true); 
	Chem::setCDFWriteSinglePrecisionFloatsParameter(ctrlParams, true);
}

bool ConfGen::CDFFragmentLibraryDataWriter::write(std::ostream& os, const FragmentLibrary::Entry& entry)
{
	const Internal::ByteBuffer* mol_buf = &molDataBuffer;

	if (hasCDFMoleculeData(*entry.second)) 
		mol_buf = getCDFMoleculeData(*entry.second).get();
	else
		molWriter.writeMolGraph(*entry.second, molDataBuffer);

	entryInfoBuffer.setIOPointer(CDF::HEADER_SIZE);
	entryInfoBuffer.putInt(entry.first, false);
	entryInfoBuffer.putInt(boost::numeric_cast<Base::uint64>(mol_buf->getSize()), false);

	entryInfoBuffer.resize(entryInfoBuffer.getIOPointer());
	entryInfoBuffer.setIOPointer(0);

	CDF::Header cdf_header;

	cdf_header.recordDataLength = boost::numeric_cast<Base::uint64>(entryInfoBuffer.getSize() - CDF::HEADER_SIZE);
	cdf_header.recordTypeID = CDF::FRAGLIB_DATA_RECORD_ID;
	cdf_header.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

	putHeader(cdf_header, entryInfoBuffer);

	entryInfoBuffer.writeBuffer(os);
	mol_buf->writeBuffer(os);

	return os.good();
}
