/* 
 * CDFDataWriter.hpp 
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


#ifndef CDPL_GRID_CDFDATAWRITER_HPP
#define CDPL_GRID_CDFDATAWRITER_HPP

#include <vector>
#include <functional>

#include "CDPL/Grid/APIPrefix.hpp"

#include "CDPL/Internal/CDFDataWriterBase.hpp"
#include "CDPL/Internal/ByteBuffer.hpp"


namespace CDPL
{

    namespace Grid
    {

        class AttributedGrid;

        class CDPL_GRID_API CDFDataWriter : public Internal::CDFDataWriterBase
        {

          public:
            typedef std::function<unsigned int(const CDFDataWriter&, const AttributedGrid&, Internal::ByteBuffer&)> PropertyHandler;

            static void registerExternalPropertyHandler(const PropertyHandler& handler);

          protected:
            void outputProperties(const AttributedGrid& grid, Internal::ByteBuffer& bbuf);

          private:
            void outputExternalProperties(const AttributedGrid& grid, Internal::ByteBuffer& bbuf);
            void outputExternalProperties(const PropertyHandler& handler, const AttributedGrid& grid, Internal::ByteBuffer& bbuf);

            typedef std::vector<PropertyHandler> PropertyHandlerList;

            static PropertyHandlerList extPropertyHandlers;
            Internal::ByteBuffer       extDataBuffer;
        };
    } // namespace Grid
} // namespace CDPL

#endif // CDPL_GRID_CDFDATAWRITER_HPP
