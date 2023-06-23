/* 
 * Utilities.cpp 
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


#include <sstream>
#include <iomanip>

#include <boost/test/auto_unit_test.hpp>
#include <boost/tokenizer.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Vis/View2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/ControlParameter.hpp"

#include "Utilities.hpp"

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

# include <cairo.h>

# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/CairoRenderer2D.hpp"
# include "CDPL/Vis/CairoFontMetrics.hpp"


using namespace CDPL;


void Vis::dumpImage(View2D& view, const std::string& prefix, std::size_t& img_id, const std::string& msg)
{
	CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1000, 500));
	
	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoRenderer2D renderer(ctxt_ptr);

	view.render(renderer);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	renderer.setBrush(Brush());
	
	Base::Any vp_var = view.getParameter(ControlParameter::VIEWPORT);

	if (!vp_var.isEmpty()) {
		const Rectangle2D& vp = vp_var.getData<Rectangle2D>();

		if (vp.isDefined()) {
			renderer.setPen(Pen(Color::BLUE, 1.0, Pen::DASH_DOT_LINE));
			renderer.drawRectangle(vp.getMin()(0), vp.getMin()(1), vp.getWidth(), vp.getHeight());
		}
	}

	Rectangle2D brect;

	view.getModelBounds(brect);

	if (brect.isDefined()) {
		renderer.setPen(Pen(Color::GREEN, 1.0, Pen::DASH_LINE));
		renderer.drawRectangle(brect.getMin()(0), brect.getMin()(1), brect.getWidth(), brect.getHeight());
	}

	renderer.setFont(Font("", 9.0));
	renderer.setPen(Color::RED);

	double y = 20.0;

	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

	Tokenizer line_tokenizer(msg, boost::char_separator<char>("\n"));

	for (Tokenizer::iterator it = line_tokenizer.begin(); it != line_tokenizer.end(); ++it, y += 10.0)
		renderer.drawText(10.0, y, *it);

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);
	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

	std::ostringstream oss;

	oss << prefix << std::setfill('0') << std::setw(3) << img_id++ << ".png";

	BOOST_CHECK(oss);
	BOOST_CHECK(cairo_surface_write_to_png(surf_ptr.get(), oss.str().c_str()) == CAIRO_STATUS_SUCCESS);
}

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO


using namespace CDPL;


void Vis::initMolecule(Chem::Molecule& mol)
{
	using namespace Chem;

	perceiveComponents(mol, false);
	perceiveComponentGroups(mol, false);
	perceiveSSSR(mol, false);
	setRingFlags(mol, false);
	calcTopologicalDistanceMatrix(mol, false);

	calcImplicitHydrogenCounts(mol, false);
	perceiveHybridizationStates(mol, false);

	setAromaticityFlags(mol, false);

	calcAtomStereoDescriptors(mol, false);
	calcBondStereoDescriptors(mol, false);

	buildMatchExpressionStrings(mol, false);
}

void Vis::initReaction(Chem::Reaction& rxn)
{
	for (Chem::Reaction::ComponentIterator it = rxn.getComponentsBegin(), end = rxn.getComponentsEnd(); it != end; ++it)
		initMolecule(*it);
}
