/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDFMolecularGraphWriter.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/PDFMolecularGraphWriter.hpp"
#include "CDPL/Vis/CairoPointer.hpp"

#include "StreamWriteFunc.hpp"


using namespace CDPL;


Vis::PDFMolecularGraphWriter::PDFMolecularGraphWriter(std::ostream& os): 
	ImageWriter(static_cast<const DataIOBase&>(*this)), output(os), state(os.good()) {}

Base::DataWriter<Chem::MolecularGraph>& Vis::PDFMolecularGraphWriter::write(const Chem::MolecularGraph& molgraph)
{
	state = false;

	CairoPointer<cairo_surface_t> surf(renderMolGraphImage(molgraph));

	state = surf.get();

	invokeIOCallbacks();

	return *this;
}

Vis::PDFMolecularGraphWriter::operator const void*() const
{
	return (state ? this : 0);
}

bool Vis::PDFMolecularGraphWriter::operator!() const
{
	return !state;
}

cairo_surface_t* Vis::PDFMolecularGraphWriter::createCairoSurface(double w, double h) const
{
	return cairo_pdf_surface_create_for_stream(&streamWriteFunc, &output, w, h);
}

cairo_surface_t* Vis::PDFMolecularGraphWriter::createCairoSurface() const
{
	return cairo_pdf_surface_create_for_stream(&streamWriteFunc, 0, 0.0, 0.0);
}
