/* 
 * CairoPointer.cpp 
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

#include <cairo.h>

#include "CDPL/Vis/CairoPointer.hpp"


using namespace CDPL;


cairo_t* Vis::CairoPointerTraits<cairo_t>::reference(cairo_t* p) throw()
{
    if (p)
        return cairo_reference(p);

    return 0;
}

void Vis::CairoPointerTraits<cairo_t>::destroy(cairo_t* p) throw()
{
    if (p)
        cairo_destroy(p);
}


cairo_surface_t* Vis::CairoPointerTraits<cairo_surface_t>::reference(cairo_surface_t* p) throw()
{
    if (p)
        return cairo_surface_reference(p);

    return 0;
}

void Vis::CairoPointerTraits<cairo_surface_t>::destroy(cairo_surface_t* p) throw()
{
    if (p)
        cairo_surface_destroy(p);
}


cairo_pattern_t* Vis::CairoPointerTraits<cairo_pattern_t>::reference(cairo_pattern_t* p) throw()
{
    if (p)
        return cairo_pattern_reference(p);

    return 0;
}

void Vis::CairoPointerTraits<cairo_pattern_t>::destroy(cairo_pattern_t* p) throw()
{
    if (p)
        cairo_pattern_destroy(p);
}
