/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ReactionView2DTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <string>
#include <cstddef>
#include <fstream>

#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Config.hpp"
#include "CDPL/Vis/ReactionView2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/ArrowStyle.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Vis/LayoutStyle.hpp"
#include "CDPL/Vis/LayoutDirection.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/AtomProperty.hpp"
#include "CDPL/Vis/MolecularGraphProperty.hpp"
#include "CDPL/Vis/ReactionProperty.hpp"
#include "CDPL/Chem/BasicReaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/JMEReactionReader.hpp"

#include "Utilities.hpp"

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

# include <cairo.h>

# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/CairoRenderer2D.hpp"
# include "CDPL/Vis/CairoFontMetrics.hpp"

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO


BOOST_AUTO_TEST_CASE(ReactionView2DTest)
{
	using namespace CDPL;
	using namespace Vis;
	using namespace Chem;

	std::size_t img_id = 1;
	ReactionView2D view;

	BOOST_CHECK(!view.getReaction());
	BOOST_CHECK(!view.getFontMetrics());

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

	CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1));

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

//----

	view.setParameter(ControlParameter::BACKGROUND_COLOR, Color::WHITE);

	dumpImage(view, "ReactionView2DTest_", img_id, "Reaction = 0; FontMetrics = 0; ControlParameter::BACKGROUND_COLOR set");

//----

	BasicReaction rxn;

	view.setReaction(&rxn);

	BOOST_CHECK(view.getReaction() == &rxn);
	BOOST_CHECK(!view.getFontMetrics());

	dumpImage(view, "ReactionView2DTest_", img_id, "Reaction != 0; Component Count = 0");

//----

	rxn.addComponent(ReactionRole::REACTANT);
	rxn.addComponent(ReactionRole::REACTANT);

	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "Reactant Count == 2");

//----

	rxn.addComponent(ReactionRole::AGENT);
	rxn.addComponent(ReactionRole::AGENT);
	rxn.addComponent(ReactionRole::AGENT);

	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "Agent Count == 3");

//----

	rxn.addComponent(ReactionRole::PRODUCT);
	rxn.addComponent(ReactionRole::PRODUCT);
	rxn.addComponent(ReactionRole::PRODUCT);

	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "Product Count == 3");

//----

	rxn.clear();

	std::ifstream is(std::string(std::string(std::getenv("CDPTK_DATA_DIR")) + "/TestRxnData.jme").c_str());

	BOOST_CHECK(is);
	BOOST_CHECK(JMEReactionReader(is).read(rxn));

	initReaction(rxn);

	view.setReaction(&rxn);

	BOOST_CHECK(view.getReaction() == &rxn);
	BOOST_CHECK(!view.getFontMetrics());

	dumpImage(view, "ReactionView2DTest_", img_id, "New Reaction Data");

//----

	CairoFontMetrics font_metrics(ctxt_ptr);

	view.setFontMetrics(&font_metrics);

	BOOST_CHECK(view.getFontMetrics() == &font_metrics);
	BOOST_CHECK(view.getReaction() == &rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "FontMetrics != 0");

//----

	view.setParameter(ControlParameter::BOND_LENGTH, SizeSpecification(0.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::BOND_LENGTH = 0.0");

//----

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::NONE);
	view.setParameter(ControlParameter::VIEWPORT, Rectangle2D(50.0, 50.0, 950.0, 450.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::VIEWPORT = (50.0, 50.0, 950.0, 450.0); ControlParameter::SIZE_ADJUSTMENT = NONE");

//----

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::NONE);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = NONE");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::TOP);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::V_CENTER);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::BOTTOM);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT | Alignment::TOP);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT | TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT | Alignment::V_CENTER);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT | V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT | Alignment::BOTTOM);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT | BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER | Alignment::TOP);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER | TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER | Alignment::V_CENTER);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER | V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER | Alignment::BOTTOM);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER | BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT | Alignment::TOP);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT | TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT | Alignment::V_CENTER);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT | V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT | Alignment::BOTTOM);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT | BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::CENTER);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::ALIGNMENT = CENTER");

//----

	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION, LayoutDirection::HORIZONTAL);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_COMPONENT_LAYOUT = NONE; ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION = HORIZONTAL");

	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_COMPONENT_LAYOUT = LINEAR; ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION = HORIZONTAL");

	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_COMPONENT_LAYOUT = PACKED; ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION = HORIZONTAL");

	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION, LayoutDirection::VERTICAL);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_COMPONENT_LAYOUT = NONE; ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION = VERTICAL");

	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_COMPONENT_LAYOUT = LINEAR; ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION = VERTICAL");

	view.setParameter(ControlParameter::REACTION_COMPONENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_COMPONENT_LAYOUT = PACKED; ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION = VERTICAL");

	rxn.setProperty(ReactionProperty::COMPONENT_LAYOUT, LayoutStyle::LINEAR);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::COMPONENT_LAYOUT = LINEAR");

	rxn.setProperty(ReactionProperty::COMPONENT_LAYOUT_DIRECTION, LayoutDirection::HORIZONTAL);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::COMPONENT_LAYOUT_DIRECTION = HORIZONTAL");

//----

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::HORIZONTAL);
	view.setParameter(ControlParameter::REACTION_AGENT_ALIGNMENT, Alignment::NONE);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = NONE");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = NONE");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = NONE");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::VERTICAL);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = NONE");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = NONE");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = NONE");

//++

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::HORIZONTAL);
	view.setParameter(ControlParameter::REACTION_AGENT_ALIGNMENT, Alignment::TOP);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = TOP");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = TOP");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = TOP");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::VERTICAL);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = TOP");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = TOP");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = TOP");

//++

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::HORIZONTAL);
	view.setParameter(ControlParameter::REACTION_AGENT_ALIGNMENT, Alignment::V_CENTER);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = V_CENTER");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = V_CENTER");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = V_CENTER");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::VERTICAL);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = V_CENTER");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = V_CENTER");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = V_CENTER");

//++

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::HORIZONTAL);
	view.setParameter(ControlParameter::REACTION_AGENT_ALIGNMENT, Alignment::BOTTOM);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = BOTTOM");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = BOTTOM");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = HORIZONTAL; ControlParameter::REACTION_AGENT_ALIGNMENT = BOTTOM");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::NONE);
	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION, LayoutDirection::VERTICAL);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = NONE; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = BOTTOM");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::LINEAR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = LINEAR; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = BOTTOM");

	view.setParameter(ControlParameter::REACTION_AGENT_LAYOUT, LayoutStyle::PACKED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_AGENT_LAYOUT = PACKED; ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION = VERTICAL; ControlParameter::REACTION_AGENT_ALIGNMENT = BOTTOM");

//++

	rxn.setProperty(ReactionProperty::AGENT_LAYOUT, LayoutStyle::LINEAR);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::AGENT_LAYOUT = LINEAR");

	rxn.setProperty(ReactionProperty::AGENT_LAYOUT_DIRECTION, LayoutDirection::HORIZONTAL);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::AGENT_LAYOUT_DIRECTION = HORIZONTAL");

	rxn.setProperty(ReactionProperty::AGENT_ALIGNMENT, Alignment::V_CENTER);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::AGENT_ALIGNMENT = V_CENTER");

//----

	view.setParameter(ControlParameter::SHOW_REACTION_REACTANTS, false);
	view.setParameter(ControlParameter::SHOW_REACTION_AGENTS, false);
	view.setParameter(ControlParameter::SHOW_REACTION_PRODUCTS, false);

	dumpImage(view, "ReactionView2DTest_", img_id, "REACTION_COMPONENT_VISIBILITY = NONE");

	view.setParameter(ControlParameter::SHOW_REACTION_REACTANTS, true);

	dumpImage(view, "ReactionView2DTest_", img_id, "REACTION_COMPONENT_VISIBILITY = REACTANT");

	view.setParameter(ControlParameter::SHOW_REACTION_REACTANTS, false);
	view.setParameter(ControlParameter::SHOW_REACTION_AGENTS, true);

	dumpImage(view, "ReactionView2DTest_", img_id, "REACTION_COMPONENT_VISIBILITY = AGENT");

	view.setParameter(ControlParameter::SHOW_REACTION_AGENTS, false);
	view.setParameter(ControlParameter::SHOW_REACTION_PRODUCTS, true);

	dumpImage(view, "ReactionView2DTest_", img_id, "REACTION_COMPONENT_VISIBILITY = PRODUCT");

	view.setParameter(ControlParameter::SHOW_REACTION_REACTANTS, true);
	view.setParameter(ControlParameter::SHOW_REACTION_AGENTS, true);
	view.setParameter(ControlParameter::SHOW_REACTION_PRODUCTS, false);

	dumpImage(view, "ReactionView2DTest_", img_id, "REACTION_COMPONENT_VISIBILITY = REACTANT | AGENT");

	view.setParameter(ControlParameter::SHOW_REACTION_AGENTS, false);
	view.setParameter(ControlParameter::SHOW_REACTION_PRODUCTS, true);

	dumpImage(view, "ReactionView2DTest_", img_id, "REACTION_COMPONENT_VISIBILITY = REACTANT | PRODUCT");
	
	view.setParameter(ControlParameter::SHOW_REACTION_REACTANTS, false);
	view.setParameter(ControlParameter::SHOW_REACTION_AGENTS, true);

	dumpImage(view, "ReactionView2DTest_", img_id, "REACTION_COMPONENT_VISIBILITY = AGENT | PRODUCT");

	rxn.setProperty(ReactionProperty::SHOW_REACTANTS, true);
	rxn.setProperty(ReactionProperty::SHOW_AGENTS, true);
	rxn.setProperty(ReactionProperty::SHOW_PRODUCTS, true);
	
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::COMPONENT_VISIBILITY = REACTANT | AGENT | PRODUCT");

//----

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::BEST_FIT);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::SIZE_ADJUSTMENT = BEST_FIT");

	view.setParameter(ControlParameter::VIEWPORT, Rectangle2D(300.0, 200.0, 700.0, 300.0));
	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::NONE);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::VIEWPORT = (300.0, 200.0, 700.0, 300.0); ControlParameter::SIZE_ADJUSTMENT = NONE");

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::IF_REQUIRED);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::SIZE_ADJUSTMENT = IF_REQUIRED");

//----

	view.setParameter(ControlParameter::VIEWPORT, Rectangle2D(50.0, 50.0, 950.0, 450.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::VIEWPORT = (50.0, 50.0, 950.0, 450.0)");

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::BEST_FIT);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::SIZE_ADJUSTMENT = BEST_FIT");

//----

	view.removeParameter(ControlParameter::BACKGROUND_COLOR);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::BACKGROUND_COLOR = removed");

//----

	rxn.getComponent(0, ReactionRole::REACTANT).getAtom(16).setProperty(AtomProperty::COLOR, Color::GREEN);
	rxn.getComponent(0, ReactionRole::REACTANT).setProperty(MolecularGraphProperty::ATOM_COLOR, Color::RED);

	view.setParameter(ControlParameter::ATOM_COLOR, Color::DARK_BLUE);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "Reactant(0).Atom(16) AtomProperty::COLOR = GREEN; Reactant(0) MolecularGraphProperty::ATOM_COLOR = RED; ControlParameter::ATOM_COLOR = DARK_BLUE");

//----

	view.setParameter(ControlParameter::REACTION_ARROW_COLOR, Color::YELLOW);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_COLOR = YELLOW");

	rxn.setProperty(ReactionProperty::ARROW_COLOR, Color(0.0, 0.0, 0.3));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::ARROW_COLOR = (0.0, 0.0, 0.3)");

//----

	view.setParameter(ControlParameter::REACTION_ARROW_STYLE, ArrowStyle::NONE);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_STYLE = NONE");

	view.setParameter(ControlParameter::REACTION_ARROW_STYLE, ArrowStyle::REACTION_SOLID);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_STYLE = REACTION_SOLID");

	view.setParameter(ControlParameter::REACTION_ARROW_STYLE, ArrowStyle::REACTION_HOLLOW);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_STYLE = REACTION_HOLLOW");

	rxn.setProperty(ReactionProperty::ARROW_STYLE, ArrowStyle::REACTION_HOLLOW);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::ARROW_STYLE = REACTION_HOLLOW");

//----

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(0.5, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (0.5, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(0.5, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (0.5, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(0.5, true, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (0.5, true, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(0.5, true, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (0.5, true, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(57.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (57.0)");

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(57.0, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (57.0, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(57.0, false, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (57.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LENGTH, SizeSpecification(57.0, false, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LENGTH = (57.0, false, false, true)");

	rxn.setProperty(ReactionProperty::ARROW_LENGTH, SizeSpecification(100.0));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::ARROW_LENGTH = (100.0)");

//----

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(0.2, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (0.2, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(0.2, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (0.2, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(0.2, true, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (0.2, true, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(0.2, true, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (0.2, true, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(20.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (20.0)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(20.0, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (20.0, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(20.0, false, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (20.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_LENGTH, SizeSpecification(20.0, false, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_LENGTH = (20.0, false, false, true)");

	rxn.setProperty(ReactionProperty::ARROW_HEAD_LENGTH, SizeSpecification(30.0));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::ARROW_HEAD_LENGTH = (30.0)");

//----

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(0.2, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (0.2, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(0.2, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (0.2, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(0.2, true, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (0.2, true, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(0.2, true, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (0.2, true, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(20.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (20.0)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(20.0, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (20.0, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(20.0, false, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (20.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_HEAD_WIDTH, SizeSpecification(20.0, false, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_HEAD_WIDTH = (20.0, false, false, true)");

	rxn.setProperty(ReactionProperty::ARROW_HEAD_WIDTH, SizeSpecification(30.0));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::ARROW_HEAD_WIDTH = (30.0)");

//----

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(0.1, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (0.1, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(0.1, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (0.1, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(0.1, true, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (0.1, true, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(0.1, true, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (0.1, true, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(10.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (10.0)");

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(10.0, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (10.0, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(10.0, false, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (10.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_SHAFT_WIDTH, SizeSpecification(10.0, false, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_SHAFT_WIDTH = (10.0, false, false, true)");

	rxn.setProperty(ReactionProperty::ARROW_SHAFT_WIDTH, SizeSpecification(15.0));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::ARROW_SHAFT_WIDTH = (15.0)");

//----

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(0.5, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (0.5, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(0.5, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (0.5, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(0.5, true, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (0.5, true, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(0.5, true, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (0.5, true, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(3.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (3.0)");

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(3.0, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (3.0, false, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(3.0, false, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (3.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_ARROW_LINE_WIDTH, SizeSpecification(3.0, false, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_ARROW_LINE_WIDTH = (3.0, false, false, true)");

	rxn.setProperty(ReactionProperty::ARROW_LINE_WIDTH, SizeSpecification(1.0));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::ARROW_LINE_WIDTH = (1.0)");

//----

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_COLOR, Color::GREEN);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_COLOR = GREEN");

	rxn.setProperty(ReactionProperty::PLUS_SIGN_COLOR, Color::DARK_RED);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::PLUS_SIGN_COLOR = DARK_RED");

//----

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(0.5, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (0.5, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(0.5, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (0.5, true, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(0.5, true, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (0.5, true, true, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(0.5, true, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (0.5, true, false, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(5.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (5.0)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(5.0, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (5.0, false, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(5.0, false, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (5.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH, SizeSpecification(5.0, false, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_LINE_WIDTH = (5.0, false, false, true)");

	rxn.setProperty(ReactionProperty::PLUS_SIGN_LINE_WIDTH, SizeSpecification(2.0));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::PLUS_SIGN_LINE_WIDTH = (2.0)");

//----

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(0.5, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (0.5, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(0.5, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (0.5, true, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(0.5, true, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (0.5, true, true, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(0.5, true, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (0.5, true, false, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(15.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (15.0)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(15.0, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (15.0, false, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(15.0, false, true, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (15.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_PLUS_SIGN_SIZE, SizeSpecification(15.0, false, false, true));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::REACTION_PLUS_SIGN_SIZE = (15.0, false, false, true)");

	rxn.setProperty(ReactionProperty::PLUS_SIGN_SIZE, SizeSpecification(10.0));
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::PLUS_SIGN_SIZE = (10.0)");

//----

	view.setParameter(ControlParameter::USE_CALCULATED_ATOM_COORDINATES, true);
	view.setParameter(ControlParameter::BOND_LENGTH, SizeSpecification(25.0));

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::USE_CALCULATED_ATOM_COORDINATES = true; ControlParameter::BOND_LENGTH = (25.0)");

//----

	view.setParameter(ControlParameter::SHOW_REACTION_PLUS_SIGNS, false);

	dumpImage(view, "ReactionView2DTest_", img_id, "ControlParameter::SHOW_REACTION_PLUS_SIGNS = false");

	rxn.setProperty(ReactionProperty::SHOW_PLUS_SIGNS, true);
	view.setReaction(&rxn);

	dumpImage(view, "ReactionView2DTest_", img_id, "ReactionProperty::SHOW_PLUS_SIGNS = true");

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO

}
