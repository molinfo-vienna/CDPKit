/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CFLFragmentLibraryEntryWriter.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>

#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"

#include "CFLFragmentLibraryEntryWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool ConfGen::CFLFragmentLibraryEntryWriter::write(std::ostream& os, const FragmentLibraryEntry& entry)
{
	entryBuffer.setIOPointer(CDF::HEADER_SIZE);
	entryBuffer.putInt(entry.getHashCode(), false);
	entryBuffer.putInt(boost::numeric_cast<CDF::SizeType>(entry.getNumConformers()), false);
	
	putString(entry.getSMILES(), entryBuffer);

	for (FragmentLibraryEntry::ConstConformerIterator it = entry.getConformersBegin(), end = entry.getConformersEnd(); it != end; ++it) {
		const ConformerData& conf_data = *it;
		std::size_t num_coords = conf_data.getSize();

		entryBuffer.putInt(boost::numeric_cast<CDF::SizeType>(num_coords), false);
		entryBuffer.putFloat(float(conf_data.getEnergy()));

		for (std::size_t i = 0; i < num_coords; i++)
			for (std::size_t j = 0; j < 3; j++)
				entryBuffer.putFloat(float(conf_data[i][j]));
	}

	entryBuffer.resize(entryBuffer.getIOPointer());
	entryBuffer.setIOPointer(0);

	CDF::Header cdf_header;

	cdf_header.recordDataLength = boost::numeric_cast<Base::uint64>(entryBuffer.getSize() - CDF::HEADER_SIZE);
	cdf_header.recordTypeID = CDF::FRAGLIB_DATA_RECORD_ID;
	cdf_header.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

	putHeader(cdf_header, entryBuffer);

	entryBuffer.writeBuffer(os);

	return os.good();
}
