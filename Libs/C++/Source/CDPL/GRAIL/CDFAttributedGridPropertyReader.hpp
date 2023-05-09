/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFAttributedGridPropertyReader.hpp 
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


#ifndef CDPL_GRAIL_CDFATTRIBUTEDGRIDPROPERTYREADER_HPP
#define CDPL_GRAIL_CDFATTRIBUTEDGRIDPROPERTYREADER_HPP

namespace CDPL 
{

    namespace Internal
    {

		class ByteBuffer;
    }

    namespace Grid
    {

		class CDFDataReader;
		class AttributedGrid;
    }
	
    namespace GRAIL
    {

		class CDFAttributedGridPropertyReader
		{

		  public:
			static void registerExternalPropertyHandlers();

		  private:
			static bool readProperties(unsigned int handler_id, const Grid::CDFDataReader& reader, 
									   Grid::AttributedGrid& grid, Internal::ByteBuffer& data);
		};
    }
}

#endif // CDPL_GRAIL_CDFATTRIBUTEDGRIDPROPERTYREADER_HPP
