/* 
 * ImageWriter.cpp 
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

#include "CDPL/Vis/ImageWriter.hpp"
#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/ReactionView2D.hpp"
#include "CDPL/Vis/CairoFontMetrics.hpp"
#include "CDPL/Vis/CairoRenderer2D.hpp"
#include "CDPL/Vis/CairoPointer.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"


using namespace CDPL;


Vis::ImageWriter::ImageWriter(const Base::DataIOBase& io_base): ioBase(io_base) {}

Vis::ImageWriter::~ImageWriter() {}

cairo_surface_t* Vis::ImageWriter::renderMolGraphImage(const Chem::MolecularGraph& molgraph)
{
	if (!structureView.get()) {
		structureView.reset(new StructureView2D());

		structureView->setParent(&ioBase);
	}

	structureView->setStructure(&molgraph);

	return renderImage(*structureView);
}

cairo_surface_t* Vis::ImageWriter::renderReactionImage(const Chem::Reaction& rxn)
{
	if (!reactionView.get()) {
		reactionView.reset(new ReactionView2D());

		reactionView->setParent(&ioBase);
	}

	reactionView->setReaction(&rxn);

	return renderImage(*reactionView);
}

cairo_surface_t* Vis::ImageWriter::renderImage(View2D& view) const
{
	CairoPointer<cairo_surface_t> fm_surf(createCairoSurface());
	CairoPointer<cairo_t> fm_ctxt(cairo_create(fm_surf.get()));

	if (cairo_surface_status(fm_surf.get()) != CAIRO_STATUS_SUCCESS 
		|| cairo_status(fm_ctxt.get()) != CAIRO_STATUS_SUCCESS) 
		return 0;

	CairoFontMetrics font_metrics(fm_ctxt);

	view.setFontMetrics(&font_metrics);

	Rectangle2D brect;

	getImageBounds(view, brect);

	if (cairo_status(fm_ctxt.get()) != CAIRO_STATUS_SUCCESS 
		|| cairo_surface_status(fm_surf.get()) != CAIRO_STATUS_SUCCESS) 
		return 0;

	CairoPointer<cairo_surface_t> render_surf(createCairoSurface(brect.getWidth(), brect.getHeight()));
	CairoPointer<cairo_t> render_ctxt(cairo_create(render_surf.get()));

	if (cairo_status(render_ctxt.get()) != CAIRO_STATUS_SUCCESS 
		|| cairo_surface_status(render_surf.get()) != CAIRO_STATUS_SUCCESS) 
		return 0;

	CairoRenderer2D renderer(render_ctxt);  
	Math::Matrix3D transform = Math::IdentityMatrix<double>(3, 3);

	transform(0, 2) = -brect.getMin()(0);
	transform(1, 2) = -brect.getMin()(1);

	renderer.transform(transform);

	view.render(renderer);

	if (cairo_status(render_ctxt.get()) != CAIRO_STATUS_SUCCESS 
		|| cairo_status(fm_ctxt.get()) != CAIRO_STATUS_SUCCESS 
		|| cairo_surface_status(render_surf.get()) != CAIRO_STATUS_SUCCESS 
		|| cairo_surface_status(fm_surf.get()) != CAIRO_STATUS_SUCCESS) 
		return 0;

	cairo_show_page(render_ctxt.get());

	return render_surf.release();
}

void Vis::ImageWriter::getImageBounds(View2D& view, Rectangle2D& brect) const
{
	brect = getViewportParameter(ioBase);

	if (!brect.isDefined()) {
		view.getModelBounds(brect);

		if (!brect.isDefined())
			brect.setBounds(0.0, 0.0, 1.0, 1.0);
	}
}
