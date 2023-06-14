/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CDFDataReader.hpp 
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


#ifndef CDPL_GRID_CDFDATAREADER_HPP
#define CDPL_GRID_CDFDATAREADER_HPP

#include <vector>
#include <functional>

#include "CDPL/Grid/APIPrefix.hpp"
#include "CDPL/Grid/CDFFormatData.hpp"

#include "CDPL/Internal/CDFDataReaderBase.hpp"


namespace CDPL 
{

    namespace Grid
    {

	class AttributedGrid;

	class CDPL_GRID_API CDFDataReader : public Internal::CDFDataReaderBase
	{

	  public:
	    typedef std::function<bool(unsigned int, const CDFDataReader&, AttributedGrid&, Internal::ByteBuffer&)> PropertyHandler;

	    static void registerExternalPropertyHandler(const PropertyHandler& handler);
	
	  protected:
	    void readProperties(AttributedGrid& grid, Internal::ByteBuffer& bbuf) const;

	  private:
	    void readExternalProperties(CDF::PropertySpec prop_spec, AttributedGrid& obj, Internal::ByteBuffer& data) const;
	    bool readExternalProperties(unsigned int handler_id, AttributedGrid& grid, Internal::ByteBuffer& bbuf) const;

	    typedef std::vector<PropertyHandler> PropertyHandlerList;

	    static PropertyHandlerList extPropertyHandlers;
	};
    }
}

#endif // CDPL_GRID_CDFDATAREADER_HPP
