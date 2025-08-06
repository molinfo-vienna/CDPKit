/* 
 * ClassExports.hpp 
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


#ifndef CDPL_PYTHON_VIS_CLASSEXPORTS_HPP
#define CDPL_PYTHON_VIS_CLASSEXPORTS_HPP

#include "CDPL/Config.hpp"


namespace CDPLPythonVis
{

    void exportSizeSpecification();
    void exportColor();
    void exportPen();
    void exportBrush();
    void exportFont();
    void exportFontMetrics();
    void exportLine2D();
    void exportRectangle2D();
    void exportPointArray2D();
    void exportPath2D();
    void exportPath2DConverter();
    void exportColorTable();

    void exportGraphicsPrimitive2D();
    void exportView2D();
    void exportRenderer2D();
    void exportStructureView2D();
    void exportReactionView2D();
    void exportStructureGridView2D();
    void exportLinePrimitive2D();
    void exportPolygonPrimitive2D();
    void exportPolylinePrimitive2D();
    void exportLineSegmentListPrimitive2D();
    void exportPointListPrimitive2D();
    void exportTextLabelPrimitive2D();
    void exportTextBlockPrimitive2D();
    void exportEllipsePrimitive2D();
    void exportPathPrimitive2D();
    void exportClipPathPrimitive2D();

    void exportObject3D();
    void exportShape3D();
    void exportTriangleMesh3D();
    void exportBuiltinTriangleMeshes();
    void exportShape3DVisitor();
    void exportFeatureContainerObject3DFactory();
    
#ifdef HAVE_CAIRO_PNG_SUPPORT

    void exportPNGMolecularGraphWriter();
    void exportPNGReactionWriter();
    void exportPNGMolecularGraphOutputHandler();
    void exportPNGReactionOutputHandler();

#endif // HAVE_CAIRO_PNG_SUPPORT

#ifdef HAVE_CAIRO_PDF_SUPPORT

    void exportPDFMolecularGraphWriter();
    void exportPDFReactionWriter();
    void exportPDFMolecularGraphOutputHandler();
    void exportPDFReactionOutputHandler();

#endif // HAVE_CAIRO_PDF_SUPPORT

#ifdef HAVE_CAIRO_PS_SUPPORT

    void exportPSMolecularGraphWriter();
    void exportPSReactionWriter();
    void exportPSMolecularGraphOutputHandler();
    void exportPSReactionOutputHandler();

#endif // HAVE_CAIRO_PS_SUPPORT

#ifdef HAVE_CAIRO_SVG_SUPPORT

    void exportSVGMolecularGraphWriter();
    void exportSVGReactionWriter();
    void exportSVGMolecularGraphOutputHandler();
    void exportSVGReactionOutputHandler();

#endif // HAVE_CAIRO_SVG_SUPPORT

} // namespace CDPLPythonVis

#endif // CDPL_PYTHON_VIS_CLASSEXPORTS_HPP
