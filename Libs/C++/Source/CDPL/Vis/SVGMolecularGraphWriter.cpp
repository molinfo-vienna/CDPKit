/* 
 * SVGMolecularGraphWriter.cpp 
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
#include <cairo-svg.h>

#include "CDPL/Vis/SVGMolecularGraphWriter.hpp"
#include "CDPL/Vis/CairoPointer.hpp"

#include "StreamWriteFunc.hpp"


using namespace CDPL;


Vis::SVGMolecularGraphWriter::SVGMolecularGraphWriter(std::ostream& os): 
    ImageWriter(static_cast<const DataIOBase&>(*this)), output(os), state(os.good()) {}

Base::DataWriter<Chem::MolecularGraph>& Vis::SVGMolecularGraphWriter::write(const Chem::MolecularGraph& molgraph)
{
    state = false;

    CairoPointer<cairo_surface_t> surf(renderMolGraphImage(molgraph));

    state = surf.get();

    invokeIOCallbacks(1.0);

    return *this;
}

Vis::SVGMolecularGraphWriter::operator const void*() const
{
    return (state ? this : 0);
}

bool Vis::SVGMolecularGraphWriter::operator!() const
{
    return !state;
}

cairo_surface_t* Vis::SVGMolecularGraphWriter::createCairoSurface(double w, double h) const
{
    return cairo_svg_surface_create_for_stream(&streamWriteFunc, &output, w, h);
}

cairo_surface_t* Vis::SVGMolecularGraphWriter::createCairoSurface() const
{
    return cairo_svg_surface_create_for_stream(&streamWriteFunc, 0, 0.0, 0.0);
}
