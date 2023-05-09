/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PNGReactionWriter.cpp 
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
#include <cmath>

#include <cairo.h>

#include "CDPL/Vis/PNGReactionWriter.hpp"
#include "CDPL/Vis/CairoPointer.hpp"

#include "StreamWriteFunc.hpp"


using namespace CDPL;


Vis::PNGReactionWriter::PNGReactionWriter(std::ostream& os): 
	ImageWriter(static_cast<const DataIOBase&>(*this)), output(os), state(os.good()) {}

Base::DataWriter<Chem::Reaction>& Vis::PNGReactionWriter::write(const Chem::Reaction& rxn)
{
	state = false;

	CairoPointer<cairo_surface_t> surf(renderReactionImage(rxn));

	if (surf.get()) { 
		cairo_surface_write_to_png_stream(surf.get(), &streamWriteFunc, &output);
	
		state = (cairo_surface_status(surf.get()) == CAIRO_STATUS_SUCCESS); 
	}

	invokeIOCallbacks(1.0);

	return *this;
}

Vis::PNGReactionWriter::operator const void*() const
{
	return (state ? this : 0);
}

bool Vis::PNGReactionWriter::operator!() const
{
	return !state;
}

cairo_surface_t* Vis::PNGReactionWriter::createCairoSurface(double w, double h) const
{
	return cairo_image_surface_create(CAIRO_FORMAT_ARGB32, int(std::ceil(w)), int(std::ceil(h)));
}

cairo_surface_t* Vis::PNGReactionWriter::createCairoSurface() const
{
	return cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 0, 0);
}
