/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Module.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Config.hpp"

#include "ClassExports.hpp"
#include "NamespaceExports.hpp"
#include "FunctionExports.hpp"
#include "ConverterRegistration.hpp"


BOOST_PYTHON_MODULE(_vis)
{
	using namespace CDPLPythonVis;

	exportSizeSpecification();
	exportColor();
	exportPen();
	exportBrush();
	exportFont();
	exportFontMetrics();
	exportLine2D();
	exportRectangle2D();
	exportPointArray2D();
	exportColorTable();
	exportGraphicsPrimitive2D();
	exportView2D();
	exportRenderer2D();
	exportStructureView2D();
	exportReactionView2D();
	exportLinePrimitive2D();
	exportPolygonPrimitive2D();
	exportPolylinePrimitive2D();
	exportLineSegmentListPrimitive2D();
	exportPointListPrimitive2D();
	exportTextLabelPrimitive2D();
	exportEllipsePrimitive2D();

#ifdef HAVE_CAIRO_PNG_SUPPORT

	exportPNGMolecularGraphWriter();
	exportPNGReactionWriter();
	exportPNGMolecularGraphOutputHandler();
	exportPNGReactionOutputHandler();

#endif // HAVE_CAIRO_PNG_SUPPORT

#ifdef HAVE_CAIRO_PDF_SUPPORT

	exportPDFMolecularGraphWriter();
	exportPDFReactionWriter();
	exportPDFMolecularGraphOutputHandler();
	exportPDFReactionOutputHandler();

#endif // HAVE_CAIRO_PDF_SUPPORT

#ifdef HAVE_CAIRO_PS_SUPPORT

	exportPSMolecularGraphWriter();
	exportPSReactionWriter();
	exportPSMolecularGraphOutputHandler();
	exportPSReactionOutputHandler();

#endif // HAVE_CAIRO_PS_SUPPORT

#ifdef HAVE_CAIRO_SVG_SUPPORT

	exportSVGMolecularGraphWriter();
	exportSVGReactionWriter();
	exportSVGMolecularGraphOutputHandler();
	exportSVGReactionOutputHandler();

#endif // HAVE_CAIRO_SVG_SUPPORT

	exportMolecularGraphFunctions();
	exportAtomFunctions();
	exportBondFunctions();
	exportReactionFunctions();
	exportControlParameterFunctions();

	exportMolecularGraphProperties();
	exportAtomProperties();
	exportBondProperties();
	exportReactionProperties();
	exportMolecularGraphPropertyDefaults();
	exportAtomPropertyDefaults();
	exportBondPropertyDefaults();
	exportReactionPropertyDefaults();

	exportControlParameters();
	exportControlParameterDefaults();

	exportDataFormats();
	exportAtomColorTables();

	exportAlignments();
	exportArrowStyles();
	exportLayoutDirections();
	exportLayoutStyles();
	exportSizeAdjustments();

	registerToPythonConverters();
	registerFromPythonConverters();
}
