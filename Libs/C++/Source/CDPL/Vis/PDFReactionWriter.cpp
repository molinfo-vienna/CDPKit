/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDFReactionWriter.cpp 
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
#include <cairo-pdf.h>

#include "CDPL/Vis/PDFReactionWriter.hpp"
#include "CDPL/Vis/CairoPointer.hpp"

#include "StreamWriteFunc.hpp"


using namespace CDPL;


Vis::PDFReactionWriter::PDFReactionWriter(std::ostream& os): 
	ImageWriter(static_cast<const DataIOBase&>(*this)), output(os), state(os.good()) {}

Base::DataWriter<Chem::Reaction>& Vis::PDFReactionWriter::write(const Chem::Reaction& rxn)
{
	state = false;

	CairoPointer<cairo_surface_t> surf(renderReactionImage(rxn));

	state = surf.get();

	invokeIOCallbacks(1.0);

	return *this;
}

Vis::PDFReactionWriter::operator const void*() const
{
	return (state ? this : 0);
}

bool Vis::PDFReactionWriter::operator!() const
{
	return !state;
}

cairo_surface_t* Vis::PDFReactionWriter::createCairoSurface(double w, double h) const
{
	return cairo_pdf_surface_create_for_stream(&streamWriteFunc, &output, w, h);
}

cairo_surface_t* Vis::PDFReactionWriter::createCairoSurface() const
{
	return cairo_pdf_surface_create_for_stream(&streamWriteFunc, 0, 0.0, 0.0);
}
