/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CFLFragmentLibraryEntryReader.cpp 
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

#include <cstddef>

#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"

#include "CFLFragmentLibraryEntryReader.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


ConfGen::CFLFragmentLibraryEntryReader::CFLFragmentLibraryEntryReader()
{
	strictErrorChecking(true);
}

bool ConfGen::CFLFragmentLibraryEntryReader::hasMoreData(std::istream& is)
{
	CDF::Header header;

	return skipToRecord(is, header, CDF::FRAGLIB_DATA_RECORD_ID, true, entryBuffer);
}

bool ConfGen::CFLFragmentLibraryEntryReader::skip(std::istream& is)
{
	return skipNextRecord(is, CDF::FRAGLIB_DATA_RECORD_ID, entryBuffer);
}

bool ConfGen::CFLFragmentLibraryEntryReader::read(std::istream& is, FragmentLibraryEntry& entry)
{
    CDF::Header header;

    if (!skipToRecord(is, header, CDF::FRAGLIB_DATA_RECORD_ID, false, entryBuffer))
		return false;

    readData(is, header.recordDataLength, entryBuffer);

	Base::uint64 hash_code;
	CDF::SizeType num_confs;
	std::string smiles;

    entryBuffer.setIOPointer(0);
    entryBuffer.getInt(hash_code);
    entryBuffer.getInt(num_confs);

	getString(smiles, entryBuffer);

	entry.setHashCode(hash_code);
	entry.setSMILES(smiles);
	entry.clearConformers();

	for (CDF::SizeType i = 0; i < num_confs; i++) {
		ConformerData::SharedPointer conf_data(new ConformerData());
		CDF::SizeType num_coords;
		float tmp;

		entryBuffer.getInt(num_coords);
		entryBuffer.getFloat(tmp);

		conf_data->resize(num_coords);
		conf_data->setEnergy(tmp);

		for (CDF::SizeType j = 0; j < num_coords; j++) {
			for (std::size_t k = 0; k < 3; k++) {
				entryBuffer.getFloat(tmp);
                (*conf_data)[j][k] = tmp;
			}
		}

		entry.addConformer(conf_data);
	}

    return true;
}
