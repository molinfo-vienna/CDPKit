/* 
 * CDFRegularGridSetDataWriter.cpp 
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
#include <cstdint>

#include <boost/numeric/conversion/cast.hpp>

#include "CDFRegularGridSetDataWriter.hpp"
#include "CDFFormatData.hpp"


using namespace CDPL;


bool Grid::CDFRegularGridSetDataWriter::writeGridSet(std::ostream& os, const DRegularGridSet& grid_set)
{
    writeGridSet(grid_set, dataBuffer);

    return writeRecordData(os);
}

void Grid::CDFRegularGridSetDataWriter::writeGridSet(const DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf)
{
    init();

    bbuf.setIOPointer(0);

    appendGridSet(grid_set, bbuf);

    bbuf.resize(bbuf.getIOPointer());
}

void Grid::CDFRegularGridSetDataWriter::appendGridSet(const DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf)
{
    std::size_t init_pos = bbuf.getIOPointer();

    bbuf.setIOPointer(init_pos + CDF::HEADER_SIZE);

    outputGridSetData(grid_set, bbuf);

    std::size_t saved_pos = bbuf.getIOPointer();

    bbuf.setIOPointer(init_pos);

    outputGridSetHeader(grid_set, bbuf, saved_pos - init_pos - CDF::HEADER_SIZE);

    bbuf.setIOPointer(saved_pos);

    for (DRegularGridSet::ConstElementIterator it = grid_set.getElementsBegin(), end = grid_set.getElementsEnd(); it != end; ++it) 
        appendGrid(*it, bbuf);
}

void Grid::CDFRegularGridSetDataWriter::outputGridSetData(const DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf) const
{
    bbuf.putInt(boost::numeric_cast<CDF::SizeType>(grid_set.getSize()), false);
}

void Grid::CDFRegularGridSetDataWriter::outputGridSetHeader(const DRegularGridSet& grid_set, Internal::ByteBuffer& bbuf, std::size_t rec_size) const
{
    CDF::Header cdf_header;

    cdf_header.recordDataLength = boost::numeric_cast<std::uint64_t>(rec_size);
    cdf_header.recordTypeID = CDF::DREGULAR_GRID_SET_RECORD_ID;
    cdf_header.recordFormatVersion = CDF::CURR_FORMAT_VERSION;

    putHeader(cdf_header, bbuf);
}

bool Grid::CDFRegularGridSetDataWriter::writeRecordData(std::ostream& os) const
{
    dataBuffer.writeBuffer(os);

    return os.good();
}
