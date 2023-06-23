/* 
 * StreamWriteFunc.cpp 
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

#include <cairo.h>

#include "StreamWriteFunc.hpp"


using namespace CDPL;


cairo_status_t Vis::streamWriteFunc(void* closure, const unsigned char* data, unsigned int length)
{
    if (!closure)
        return CAIRO_STATUS_SUCCESS;

    try {
        std::ostream* os = static_cast<std::ostream*>(closure);

        if (!os->good())
            return CAIRO_STATUS_WRITE_ERROR;

        os->write(reinterpret_cast<const char*>(data), length);

        return (os->good() ? CAIRO_STATUS_SUCCESS : CAIRO_STATUS_WRITE_ERROR);

    } catch (...) {
        return CAIRO_STATUS_WRITE_ERROR;
    }
}


