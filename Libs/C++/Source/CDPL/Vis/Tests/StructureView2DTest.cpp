/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * StructureView2DTest.cpp 
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
#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/AtomColorTable.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/AtomProperty.hpp"
#include "CDPL/Vis/AtomFunctions.hpp"
#include "CDPL/Vis/BondProperty.hpp"
#include "CDPL/Vis/MolecularGraphProperty.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MatchConstraintList.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomProperty.hpp"
#include "CDPL/Chem/BondProperty.hpp"
#include "CDPL/Chem/ReactionCenterStatus.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/JMEMoleculeReader.hpp"

#include "Utilities.hpp"

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

# include <cairo.h>

# include "CDPL/Vis/CairoPointer.hpp"
# include "CDPL/Vis/CairoRenderer2D.hpp"
# include "CDPL/Vis/CairoFontMetrics.hpp"

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO


BOOST_AUTO_TEST_CASE(StructureView2DTest)
{
	using namespace CDPL;
	using namespace Vis;
	using namespace Chem;

	StructureView2D view;

	BOOST_CHECK(!view.getStructure());
	BOOST_CHECK(!view.getFontMetrics());

#ifdef HAVE_CAIRO 
# ifdef HAVE_CAIRO_PNG_SUPPORT

	std::size_t img_id = 1;
	CairoPointer<cairo_surface_t> surf_ptr(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1));

	BOOST_CHECK(cairo_surface_status(surf_ptr.get()) == CAIRO_STATUS_SUCCESS);

	CairoPointer<cairo_t> ctxt_ptr(cairo_create(surf_ptr.get()));

	BOOST_CHECK(cairo_status(ctxt_ptr.get()) == CAIRO_STATUS_SUCCESS);

//----

	view.setParameter(ControlParameter::BACKGROUND_COLOR, Color::WHITE);

	dumpImage(view, "StructureView2DTest_", img_id, "Structure = 0; FontMetrics = 0; ControlParameter::BACKGROUND_COLOR set");

//----

	BasicMolecule mol;

	view.setStructure(&mol);

	BOOST_CHECK(view.getStructure() == &mol);
	BOOST_CHECK(!view.getFontMetrics());

	dumpImage(view, "StructureView2DTest_", img_id, "Structure != 0; Atom Count = 0");

//----

	std::ifstream is(std::string(std::string(std::getenv("CDPKIT_TEST_DATA_DIR")) + "/TestMolData.jme").c_str());

	BOOST_CHECK(is);
	BOOST_CHECK(JMEMoleculeReader(is).read(mol));

	initMolecule(mol);

	view.setStructure(&mol);

	BOOST_CHECK(view.getStructure() == &mol);
	BOOST_CHECK(!view.getFontMetrics());

	dumpImage(view, "StructureView2DTest_", img_id, "Atom Count > 0");

//----

	CairoFontMetrics font_metrics(ctxt_ptr);

	view.setFontMetrics(&font_metrics);

	BOOST_CHECK(view.getFontMetrics() == &font_metrics);
	BOOST_CHECK(view.getStructure() == &mol);

	dumpImage(view, "StructureView2DTest_", img_id, "FontMetrics != 0");

//----

	view.setParameter(ControlParameter::BOND_LENGTH, SizeSpecification(0.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LENGTH = 0.0");

//----

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::NONE);
	view.setParameter(ControlParameter::VIEWPORT, Rectangle2D(50.0, 50.0, 450.0, 450.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::VIEWPORT = (50.0, 50.0, 450.0, 450.0); ControlParameter::SIZE_ADJUSTMENT = NONE");

//----

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::NONE);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = NONE");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::TOP);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::V_CENTER);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::BOTTOM);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT | Alignment::TOP);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT | TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT | Alignment::V_CENTER);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT | V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::LEFT | Alignment::BOTTOM);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = LEFT | BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER | Alignment::TOP);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER | TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER | Alignment::V_CENTER);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER | V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::H_CENTER | Alignment::BOTTOM);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = H_CENTER | BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT | Alignment::TOP);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT | TOP");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT | Alignment::V_CENTER);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT | V_CENTER");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::RIGHT | Alignment::BOTTOM);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = RIGHT | BOTTOM");

	view.setParameter(ControlParameter::ALIGNMENT, Alignment::CENTER);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ALIGNMENT = CENTER");

//----

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::BEST_FIT);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SIZE_ADJUSTMENT = BEST_FIT");

	view.setParameter(ControlParameter::VIEWPORT, Rectangle2D(200.0, 200.0, 300.0, 300.0));
	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::NONE);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::VIEWPORT = (200.0, 200.0, 300.0, 300.0); ControlParameter::SIZE_ADJUSTMENT = NONE");

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::IF_REQUIRED);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SIZE_ADJUSTMENT = IF_REQUIRED");

//----

	view.setParameter(ControlParameter::VIEWPORT, Rectangle2D(50.0, 50.0, 450.0, 450.0));
	view.setParameter(ControlParameter::BOND_LENGTH, SizeSpecification(50.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::VIEWPORT = (50.0, 50.0, 450.0, 450.0); ControlParameter::BOND_LENGTH = 50.0");

	view.setParameter(ControlParameter::SIZE_ADJUSTMENT, SizeAdjustment::BEST_FIT);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SIZE_ADJUSTMENT = BEST_FIT");

//----

	view.removeParameter(ControlParameter::BACKGROUND_COLOR);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BACKGROUND_COLOR = removed");

//----

	view.setParameter(ControlParameter::ATOM_COLOR, Color::BLUE);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_COLOR = BLUE");

	setColor(mol.getAtom(6), Color::GREEN);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(6) Vis::AtomProperty::COLOR = GREEN");

	mol.setProperty(MolecularGraphProperty::ATOM_COLOR, Color(0.3, 0.3, 0.3));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::ATOM_COLOR = (0.3, 0.3, 0.3)");

	ColorTable::SharedPointer color_tab_ptr(new ColorTable(AtomColorTable::ELEMENT_COLORS_2D));

	mol.removeProperty(MolecularGraphProperty::ATOM_COLOR);

	view.setParameter(ControlParameter::ATOM_COLOR_TABLE, color_tab_ptr);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::ATOM_COLOR removed; ControlParameter::ATOM_COLOR_TABLE = set");

	view.removeParameter(ControlParameter::ATOM_COLOR_TABLE);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::ATOM_COLOR removed; ControlParameter::ATOM_COLOR_TABLE = removed");

	view.setParameter(ControlParameter::ATOM_COLOR_TABLE, color_tab_ptr);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::ATOM_COLOR removed; ControlParameter::ATOM_COLOR_TABLE = set");

//----

	view.setParameter(ControlParameter::BOND_COLOR, Color::YELLOW);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_COLOR = YELLOW");

	mol.getBond(0).setProperty(Vis::BondProperty::COLOR, Color::MAGENTA);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(0) BondProperty::COLOR = MAGENTA");

	mol.setProperty(MolecularGraphProperty::BOND_COLOR, Color(0.0, 0.0, 0.3));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::BOND_COLOR = (0.0, 0.0, 0.3)");

//----

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(0.2, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (0.2, true)");

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(0.2, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (0.2, true, true)");

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(0.2, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (0.2, true, true, true)");

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(0.2, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (0.2, true, false, true)");

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(2.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (2.0)");

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(2.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (2.0, false, true)");

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(2.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (2.0, false, true, true)");

	view.setParameter(ControlParameter::BOND_LINE_WIDTH, SizeSpecification(2.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_WIDTH = (2.0, false, false, true)");

	mol.getBond(1).setProperty(Vis::BondProperty::LINE_WIDTH, SizeSpecification(6.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(1) BondProperty::LINE_WIDTH = (6.0)");

	mol.setProperty(MolecularGraphProperty::BOND_LINE_WIDTH, SizeSpecification(2.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::BOND_LINE_WIDTH = (2.0)");

//----

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(0.3, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (0.3, true)");

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(0.3, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (0.3, true, true)");

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(0.3, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (0.3, true, true, true)");

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(0.3, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (0.3, true, false, true)");

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(5.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (5.0)");

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(5.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (5.0, false, true)");

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(5.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (5.0, false, true, true)");

	view.setParameter(ControlParameter::BOND_LINE_SPACING, SizeSpecification(5.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LINE_SPACING = (5.0, false, false, true)");

	mol.getBond(1).setProperty(Vis::BondProperty::LINE_SPACING, SizeSpecification(10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(1) BondProperty::LINE_SPACING = (10.0)");

	mol.setProperty(MolecularGraphProperty::BOND_LINE_SPACING, SizeSpecification(5.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::BOND_LINE_SPACING = 5.0");

//----

	mol.getBond(3).setProperty(Chem::BondProperty::STEREO_2D_FLAG, BondStereoFlag::EITHER);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(3) BondProperty::STEREO_2D_FLAG = EITHER");

	mol.getBond(0).setProperty(Chem::BondProperty::STEREO_2D_FLAG, BondStereoFlag::REVERSE_EITHER);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(0) BondProperty::STEREO_2D_FLAG = REVERSE_EITHER");

	mol.getBond(4).setProperty(Chem::BondProperty::ORDER, std::size_t(0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(4) BondProperty::ORDER = 0");

//----

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(0.4, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (0.4, true)");

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(0.4, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (0.4, true, true)");

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(0.4, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (0.4, true, true, true)");

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(0.4, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (0.4, true, false, true)");

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(0.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (4.0)");

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(4.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (4.0, false, true)");

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(4.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (4.0, false, true, true)");

	view.setParameter(ControlParameter::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(4.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_WEDGE_WIDTH = (4.0, false, false, true)");

	mol.getBond(18).setProperty(Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(20.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(18) BondProperty::STEREO_BOND_WEDGE_WIDTH = (20.0)");

	mol.setProperty(MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH, SizeSpecification(8.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH = (8.0)");

//----

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(0.2, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (0.3, true)");

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(0.2, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (0.2, true, true)");

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(0.2, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (0.2, true, true, true)");

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(0.2, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (0.2, true, false, true)");

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(4.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (4.0)");

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(4.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (4.0, false, true)");

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(4.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (4.0, false, true, true)");

	view.setParameter(ControlParameter::STEREO_BOND_HASH_SPACING, SizeSpecification(4.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::STEREO_BOND_HASH_SPACING = (4.0, false, false, true)");

	mol.getBond(18).setProperty(Vis::BondProperty::STEREO_BOND_HASH_SPACING, SizeSpecification(10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(18) BondProperty::STEREO_BOND_HASH_SPACING = (10.0)");

	mol.setProperty(MolecularGraphProperty::STEREO_BOND_HASH_SPACING, SizeSpecification(5.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::STEREO_BOND_HASH_SPACING = (5.0)");

//----

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (0.3, true)");

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (0.3, true, true)");

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (0.3, true, true, true)");

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (0.3, true, false, true)");

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(5.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (5.0)");

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(5.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (5.0, false, true)");

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(5.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (5.0, false, true, true)");

	view.setParameter(ControlParameter::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(5.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::DOUBLE_BOND_TRIM_LENGTH = (5.0, false, false, true)");

	mol.getBond(1).setProperty(Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(-10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(1) BondProperty::DOUBLE_BOND_TRIM_LENGTH = (-10.0)");

	mol.setProperty(MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH, SizeSpecification(5.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH = (5.0)");

//----

	mol.getBond(1).setProperty(Chem::BondProperty::ORDER, std::size_t(3));
	mol.getBond(4).setProperty(Chem::BondProperty::ORDER, std::size_t(3));

	view.setStructure(&mol);

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true));

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(1) BondProperty::ORDER = 3; Bond(4) BondProperty::ORDER = 3; ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (0.3, true)");

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (0.3, true, true)");

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (0.3, true, true, true)");

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(0.3, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (0.3, true, false, true)");

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(5.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (5.0)");

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(5.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (5.0, false, true)");

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(5.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (5.0, false, true, true)");

	view.setParameter(ControlParameter::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(5.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::TRIPLE_BOND_TRIM_LENGTH = (5.0, false, false, true)");

	mol.getBond(1).setProperty(Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(-10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(1) BondProperty::TRIPLE_BOND_TRIM_LENGTH = (-10.0)");

	mol.setProperty(MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH, SizeSpecification(5.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH = (5.0)");

//----

	mol.getBond(2).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::BOND_MADE);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(2) BondProperty::REACTION_CENTER_STATUS = BOND_MADE");

	mol.getBond(3).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::BOND_BROKEN);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(3) BondProperty::REACTION_CENTER_STATUS = BOND_BROKEN");

	mol.getBond(4).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::BOND_ORDER_CHANGE);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(4) BondProperty::REACTION_CENTER_STATUS = BOND_ORDER_CHANGE");

	mol.getBond(5).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::NO_CENTER);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(5) BondProperty::REACTION_CENTER_STATUS = NO_CENTER");

	mol.getBond(6).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::IS_CENTER);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(6) BondProperty::REACTION_CENTER_STATUS = IS_CENTER");

	mol.getBond(7).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::IS_CENTER | ReactionCenterStatus::BOND_MADE);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(7) BondProperty::REACTION_CENTER_STATUS = IS_CENTER | BOND_MADE");

	mol.getBond(8).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::IS_CENTER | 
							   ReactionCenterStatus::BOND_MADE | 
							   ReactionCenterStatus::BOND_BROKEN);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(8) BondProperty::REACTION_CENTER_STATUS = IS_CENTER | BOND_MADE | BOND_BROKEN");

	mol.getBond(9).setProperty(Chem::BondProperty::REACTION_CENTER_STATUS, ReactionCenterStatus::IS_CENTER | 
							   ReactionCenterStatus::BOND_MADE | 
							   ReactionCenterStatus::BOND_BROKEN |
							   ReactionCenterStatus::BOND_ORDER_CHANGE);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(9) BondProperty::REACTION_CENTER_STATUS =\nIS_CENTER | BOND_MADE | BOND_BROKEN | BOND_ORDER_CHANGE");

//----

	MatchConstraintList::SharedPointer constr_ptr(new MatchConstraintList());

	constr_ptr->addElement(BondMatchConstraint::ORDER,
						   MatchConstraint::EQUAL,
						   BondMatchConstraint::SINGLE | BondMatchConstraint::DOUBLE | BondMatchConstraint::TRIPLE);

	mol.getBond(6).setProperty(Chem::BondProperty::MATCH_CONSTRAINTS, constr_ptr);
	mol.getBond(15).setProperty(Chem::BondProperty::MATCH_CONSTRAINTS, constr_ptr);

	buildMatchExpressionStrings(mol, true);

	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(6)/Bond(15) BondProperty::LOCAL_MATCH_CONSTRAINTS:\nORDER = SINGLE | DOUBLE | TRIPLE");

//----

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(0.9, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (0.9, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(0.9, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (0.9, true, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(0.9, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (0.9, true, true, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(0.9, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (0.9, true, false, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(40.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (40.0)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(40.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (40.0, false, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(40.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (40.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_LENGTH, SizeSpecification(40.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_LENGTH = (40.0, false, false, true)");

	mol.getBond(7).setProperty(Vis::BondProperty::REACTION_CENTER_LINE_LENGTH, SizeSpecification(10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(7) BondProperty::REACTION_CENTER_LINE_LENGTH = (10.0)");

	mol.setProperty(MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH, SizeSpecification(30.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH = (30.0)");

//----

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(0.2, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (0.3, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(0.2, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (0.2, true, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(0.2, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (0.2, true, true, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(0.2, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (0.2, true, false, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(4.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (4.0)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(4.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (4.0, false, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(4.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (4.0, false, true, true)");

	view.setParameter(ControlParameter::REACTION_CENTER_LINE_SPACING, SizeSpecification(4.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::REACTION_CENTER_LINE_SPACING = (4.0, false, false, true)");

	mol.getBond(7).setProperty(Vis::BondProperty::REACTION_CENTER_LINE_SPACING, SizeSpecification(10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(7) BondProperty::REACTION_CENTER_LINE_SPACING = (10.0)");

	mol.setProperty(MolecularGraphProperty::REACTION_CENTER_LINE_SPACING, SizeSpecification(5.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::REACTION_CENTER_LINE_SPACING = (5.0)");

//----

	Font bnd_font;

	bnd_font.setFamily("Serif");

	view.setParameter(ControlParameter::BOND_LABEL_FONT, bnd_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_FONT = (Serif)");

	bnd_font.setFamily("Helvetica");
	bnd_font.setItalic(true);

	view.setParameter(ControlParameter::BOND_LABEL_FONT, bnd_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_FONT = (Helvetica, italic)");

	bnd_font.setFamily("Courier");
	bnd_font.setBold(true);

	view.setParameter(ControlParameter::BOND_LABEL_FONT, bnd_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_FONT = (Courier, bold, italic)");

	bnd_font.setFamily("");
	bnd_font.setItalic(false);

	mol.getBond(6).setProperty(Vis::BondProperty::LABEL_FONT, bnd_font);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(6) BondProperty::LABEL_FONT = (Default, bold, italic)");

	bnd_font.setFamily("Times");
	bnd_font.setItalic(false);

	mol.setProperty(MolecularGraphProperty::BOND_LABEL_FONT, bnd_font);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::BOND_LABEL_FONT = (Times, bold)");

//----

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(0.5, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (0.5, true)");

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(0.5, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (0.5, true, true)");

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(0.5, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (0.5, true, true, true)");

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(0.5, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (0.5, true, false, true)");

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(12.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (12.0)");

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(12.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (12.0, false, true)");

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(12.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (12.0, false, true, true)");

	view.setParameter(ControlParameter::BOND_LABEL_SIZE, SizeSpecification(12.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_SIZE = (12.0, false, false, true)");

	mol.getBond(5).setProperty(Vis::BondProperty::LABEL_SIZE, SizeSpecification(20.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(5) BondProperty::LABEL_SIZE = (20.0)");

	mol.setProperty(MolecularGraphProperty::BOND_LABEL_SIZE, SizeSpecification(12.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::BOND_LABEL_SIZE = (12.0)");

//----

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(0.1, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (0.1, true)");

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(0.1, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (0.1, true, true)");

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(0.1, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (0.1, true, true, true)");

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(0.1, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (0.1, true, false, true)");

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(4.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (4.0)");

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(4.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (4.0, false, true)");

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(4.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (4.0, false, true, true)");

	view.setParameter(ControlParameter::BOND_LABEL_MARGIN, SizeSpecification(4.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::BOND_LABEL_MARGIN = (4.0, false, false, true)");

	mol.getBond(5).setProperty(Vis::BondProperty::LABEL_MARGIN, SizeSpecification(-10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Bond(5) BondProperty::LABEL_MARGIN = (-10.0)");

	mol.setProperty(MolecularGraphProperty::BOND_LABEL_MARGIN, SizeSpecification(1.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::BOND_LABEL_MARGIN = (1.0)");

//----

	mol.getAtom(6).setProperty(Chem::AtomProperty::ISOTOPE, std::size_t(100));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(6) AtomProperty::ISOTOPE = 100");

//----

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 0");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(1));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 1");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(2));
	mol.getAtom(12).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(2));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13)/Atom(12) AtomProperty::UNPAIRED_ELECTRON_COUNT = 2");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(3));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 3");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(4));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 4");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(5));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 5");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(6));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 6");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(7));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 7");

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(8));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 8");

//----

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(0.1, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (0.1, true)");

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(0.1, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (0.1, true, true)");

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(0.1, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (0.1, true, true, true)");

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(0.1, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (0.1, true, false, true)");

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(4.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (4.0)");

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(4.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (4.0, false, true)");

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(4.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (4.0, false, true, true)");

	view.setParameter(ControlParameter::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(4.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::RADICAL_ELECTRON_DOT_SIZE = (4.0, false, false, true)");

	mol.getAtom(13).setProperty(Vis::AtomProperty::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::RADICAL_ELECTRON_DOT_SIZE = (10.0)");

	mol.setProperty(MolecularGraphProperty::RADICAL_ELECTRON_DOT_SIZE, SizeSpecification(3.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::RADICAL_ELECTRON_DOT_SIZE = (3.0)");

//----

	mol.getAtom(13).setProperty(Chem::AtomProperty::UNPAIRED_ELECTRON_COUNT, std::size_t(9));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(13) AtomProperty::UNPAIRED_ELECTRON_COUNT = 9");

//----

	view.setParameter(ControlParameter::SHOW_CARBONS, true);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_CARBONS = true");

//----

	view.setParameter(ControlParameter::SHOW_HYDROGEN_COUNTS, true);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_HYDROGEN_COUNTS = true");

//----

	view.setParameter(ControlParameter::SHOW_CARBONS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_CARBONS = false");

//----

	Font atm_font;

	atm_font.setFamily("Serif");

	view.setParameter(ControlParameter::ATOM_LABEL_FONT, atm_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_FONT = (Serif)");

	atm_font.setFamily("Helvetica");
	atm_font.setItalic(true);

	view.setParameter(ControlParameter::ATOM_LABEL_FONT, atm_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_FONT = (Helvetica, italic)");

	atm_font.setFamily("Courier");
	atm_font.setBold(true);

	view.setParameter(ControlParameter::ATOM_LABEL_FONT, atm_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_FONT = (Courier, bold, italic)");

	atm_font.setFamily("");
	atm_font.setItalic(false);

	mol.getAtom(6).setProperty(Vis::AtomProperty::LABEL_FONT, atm_font);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(6) AtomProperty::LABEL_FONT = (Default, bold, italic)");

	atm_font.setFamily("Times");
	atm_font.setItalic(false);

	mol.setProperty(MolecularGraphProperty::ATOM_LABEL_FONT, atm_font);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::ATOM_LABEL_FONT = (Times, bold)");

//----

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(0.5, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (0.5, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(0.5, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (0.5, true, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(0.5, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (0.5, true, true, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(0.5, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (0.5, true, false, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(12.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (12.0)");

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(12.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (12.0, false, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(12.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (12.0, false, true, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_SIZE, SizeSpecification(12.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_SIZE = (12.0, false, false, true)");

	mol.getAtom(6).setProperty(Vis::AtomProperty::LABEL_SIZE, SizeSpecification(20.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(6) AtomProperty::LABEL_SIZE = (20.0)");

	mol.setProperty(MolecularGraphProperty::ATOM_LABEL_SIZE, SizeSpecification(12.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::ATOM_LABEL_SIZE = (12.0)");

//----

	Font sec_atm_font;

	sec_atm_font.setFamily("Serif");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_FONT, sec_atm_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_FONT = (Serif)");

	sec_atm_font.setFamily("Helvetica");
	sec_atm_font.setItalic(true);

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_FONT, sec_atm_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_FONT = (Helvetica, italic)");

	sec_atm_font.setFamily("Courier");
	sec_atm_font.setBold(true);

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_FONT, sec_atm_font);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_FONT = (Courier, bold, italic)");

	sec_atm_font.setFamily("");
	sec_atm_font.setItalic(false);

	mol.getAtom(6).setProperty(Vis::AtomProperty::SECONDARY_LABEL_FONT, sec_atm_font);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(6) AtomProperty::SECONDARY_LABEL_FONT = (Default, bold, italic)");

	sec_atm_font.setFamily("Times");
	sec_atm_font.setItalic(false);

	mol.setProperty(MolecularGraphProperty::SECONDARY_ATOM_LABEL_FONT, sec_atm_font);
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::SECONDARY_ATOM_LABEL_FONT = (Times, bold)");

//----

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(0.5, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (0.5, true)");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(0.5, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (0.5, true, true)");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(0.5, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (0.5, true, true, true)");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(0.5, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (0.5, true, false, true)");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(12.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (12.0)");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(12.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (12.0, false, true)");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(12.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (12.0, false, true, true)");

	view.setParameter(ControlParameter::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(12.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SECONDARY_ATOM_LABEL_SIZE = (12.0, false, false, true)");

	mol.getAtom(6).setProperty(Vis::AtomProperty::SECONDARY_LABEL_SIZE, SizeSpecification(20.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(6) AtomProperty::SECONDARY_LABEL_SIZE = (20.0)");

	mol.setProperty(MolecularGraphProperty::SECONDARY_ATOM_LABEL_SIZE, SizeSpecification(12.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::SECONDARY_ATOM_LABEL_SIZE = (12.0)");

//----

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(0.1, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (0.1, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(0.1, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (0.1, true, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(0.1, true, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (0.1, true, true, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(0.1, true, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (0.1, true, false, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(4.0));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (4.0)");

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(4.0, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (4.0, false, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(4.0, false, true, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (4.0, false, true, true)");

	view.setParameter(ControlParameter::ATOM_LABEL_MARGIN, SizeSpecification(4.0, false, false, true));

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::ATOM_LABEL_MARGIN = (4.0, false, false, true)");

	mol.getAtom(6).setProperty(Vis::AtomProperty::LABEL_MARGIN, SizeSpecification(-10.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "Atom(6) BondProperty::LABEL_MARGIN = (-10.0)");

	mol.setProperty(MolecularGraphProperty::ATOM_LABEL_MARGIN, SizeSpecification(1.0));
	view.setStructure(&mol);

	dumpImage(view, "StructureView2DTest_", img_id, "MolecularGraphProperty::ATOM_LABEL_MARGIN = (1.0)");

//----

	view.setParameter(ControlParameter::USE_CALCULATED_ATOM_COORDINATES, true);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::USE_CALCULATED_ATOM_COORDINATES = true");

//----

	view.setParameter(ControlParameter::SHOW_HYDROGEN_COUNTS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_HYDROGEN_COUNTS = false");

//----

	view.setParameter(ControlParameter::SHOW_CHARGES, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_CHARGES = false");

//----

	view.setParameter(ControlParameter::SHOW_ISOTOPES, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_ISOTOPES = false");

//----

	view.setParameter(ControlParameter::SHOW_EXPLICIT_HYDROGENS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_EXPLICIT_HYDROGENS = false");

//----

	view.setParameter(ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS = false");

//----

	view.setParameter(ControlParameter::SHOW_ATOM_QUERY_INFOS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_ATOM_QUERY_INFOS = false");

//----

	view.setParameter(ControlParameter::SHOW_ATOM_REACTION_INFOS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_ATOM_REACTION_INFOS = false");

//----

	view.setParameter(ControlParameter::SHOW_RADICAL_ELECTRONS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_RADICAL_ELECTRONS = false");

//----

	view.setParameter(ControlParameter::SHOW_BOND_REACTION_INFOS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_BOND_REACTION_INFOS = false");

//----

	view.setParameter(ControlParameter::SHOW_STEREO_BONDS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_STEREO_BONDS = false");

//----

	view.setParameter(ControlParameter::SHOW_BOND_QUERY_INFOS, false);

	dumpImage(view, "StructureView2DTest_", img_id, "ControlParameter::SHOW_BOND_QUERY_INFOS = false");

# endif // HAVE_CAIRO_PNG_SUPPORT
#endif // HAVE_CAIRO

}

