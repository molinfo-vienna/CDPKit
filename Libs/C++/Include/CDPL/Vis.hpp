/* 
 * Vis.hpp 
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

/**
 * \file
 * \brief A convenience header including everything that is defined in namespace CDPL::Vis.
 */

#ifndef CDPL_VIS_HPP
#define CDPL_VIS_HPP

#include "CDPL/Config.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/ControlParameterDefault.hpp"
#include "CDPL/Vis/AtomProperty.hpp"
#include "CDPL/Vis/BondProperty.hpp"
#include "CDPL/Vis/MolecularGraphProperty.hpp"
#include "CDPL/Vis/ReactionProperty.hpp"
#include "CDPL/Vis/AtomPropertyDefault.hpp"
#include "CDPL/Vis/BondPropertyDefault.hpp"
#include "CDPL/Vis/MolecularGraphPropertyDefault.hpp"
#include "CDPL/Vis/ReactionPropertyDefault.hpp"
#include "CDPL/Vis/DataFormat.hpp"
#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/AtomFunctions.hpp"
#include "CDPL/Vis/BondFunctions.hpp"
#include "CDPL/Vis/MolecularGraphFunctions.hpp"
#include "CDPL/Vis/ReactionFunctions.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/LayoutStyle.hpp"
#include "CDPL/Vis/LayoutDirection.hpp"
#include "CDPL/Vis/ArrowStyle.hpp"
#include "CDPL/Vis/SizeSpecification.hpp"
#include "CDPL/Vis/FontMetrics.hpp"
#include "CDPL/Vis/View2D.hpp"
#include "CDPL/Vis/Renderer2D.hpp"
#include "CDPL/Vis/StructureView2D.hpp"
#include "CDPL/Vis/ReactionView2D.hpp"
#include "CDPL/Vis/Color.hpp"
#include "CDPL/Vis/Pen.hpp"
#include "CDPL/Vis/Brush.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"
#include "CDPL/Vis/Line2D.hpp"
#include "CDPL/Vis/PointArray2D.hpp"
#include "CDPL/Vis/ColorTable.hpp"
#include "CDPL/Vis/AtomColorTable.hpp"
#include "CDPL/Vis/GraphicsPrimitive2D.hpp"
#include "CDPL/Vis/LinePrimitive2D.hpp"
#include "CDPL/Vis/PolygonPrimitive2D.hpp"
#include "CDPL/Vis/PolylinePrimitive2D.hpp"
#include "CDPL/Vis/LineSegmentListPrimitive2D.hpp"
#include "CDPL/Vis/PointListPrimitive2D.hpp"
#include "CDPL/Vis/EllipsePrimitive2D.hpp"
#include "CDPL/Vis/TextLabelPrimitive2D.hpp"

#ifdef HAVE_QT

#include "CDPL/Vis/QtRenderer2D.hpp"
#include "CDPL/Vis/QtFontMetrics.hpp"
#include "CDPL/Vis/QtObjectFactory.hpp"

#endif // HAVE_QT

#ifdef HAVE_CAIRO

#include "CDPL/Vis/CairoRenderer2D.hpp"
#include "CDPL/Vis/CairoFontMetrics.hpp"
#include "CDPL/Vis/ImageWriter.hpp"
#include "CDPL/Vis/CairoPointer.hpp"

#ifdef HAVE_CAIRO_PNG_SUPPORT

#include "CDPL/Vis/PNGMolecularGraphWriter.hpp"
#include "CDPL/Vis/PNGReactionWriter.hpp"
#include "CDPL/Vis/PNGMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/PNGReactionOutputHandler.hpp"

#endif // HAVE_CAIRO_PNG_SUPPORT

#ifdef HAVE_CAIRO_PDF_SUPPORT

#include "CDPL/Vis/PDFMolecularGraphWriter.hpp"
#include "CDPL/Vis/PDFReactionWriter.hpp"
#include "CDPL/Vis/PDFMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/PDFReactionOutputHandler.hpp"

#endif // HAVE_CAIRO_PDF_SUPPORT

#ifdef HAVE_CAIRO_PS_SUPPORT

#include "CDPL/Vis/PSMolecularGraphWriter.hpp"
#include "CDPL/Vis/PSReactionWriter.hpp"
#include "CDPL/Vis/PSMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/PSReactionOutputHandler.hpp"

#endif // HAVE_CAIRO_PS_SUPPORT

#ifdef HAVE_CAIRO_SVG_SUPPORT

#include "CDPL/Vis/SVGMolecularGraphWriter.hpp"
#include "CDPL/Vis/SVGReactionWriter.hpp"
#include "CDPL/Vis/SVGMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/SVGReactionOutputHandler.hpp"

#endif // HAVE_CAIRO_SVG_SUPPORT
#endif // HAVE_CAIRO
#endif // CDPL_VIS_HPP
