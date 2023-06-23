/* 
 * DataFormat.cpp 
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

#include "CDPL/Config.hpp"
#include "CDPL/Base/DataIOManager.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Vis/DataFormat.hpp"
#include "CDPL/Vis/PNGMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/PNGReactionOutputHandler.hpp"
#include "CDPL/Vis/PDFMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/PDFReactionOutputHandler.hpp"
#include "CDPL/Vis/PSMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/PSReactionOutputHandler.hpp"
#include "CDPL/Vis/SVGMolecularGraphOutputHandler.hpp"
#include "CDPL/Vis/SVGReactionOutputHandler.hpp"


namespace
{

    const char* pngFileExtensions[] = { "png" };
    const char* pdfFileExtensions[] = { "pdf" };
    const char* psFileExtensions[]  = { "ps", "eps" };
    const char* svgFileExtensions[] = { "svg" };
}


using namespace CDPL;

        
const Base::DataFormat Vis::DataFormat::PNG("PNG", "Portable Network Graphics", "image/png", 
                                            pngFileExtensions, pngFileExtensions + 1, false);
const Base::DataFormat Vis::DataFormat::PDF("PDF", "Adobe Portable Document Format", "application/pdf", 
                                            pdfFileExtensions, pdfFileExtensions + 1, false);
const Base::DataFormat Vis::DataFormat::PS("PS", "Adobe PostScript", "application/postscript", 
                                           psFileExtensions, psFileExtensions + 2, false);
const Base::DataFormat Vis::DataFormat::SVG("SVG", "Scalable Vector Graphics", "image/svg+xml", 
                                            svgFileExtensions, svgFileExtensions + 1, false);

namespace CDPL
{

    namespace Vis
    {

        void initDataFormats() {}
    }
}


namespace
{

    struct Init 
    {

        Init() {
            using namespace Base;
            using namespace Chem;
            using namespace Vis;

#ifdef HAVE_CAIRO_PNG_SUPPORT

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new PNGMolecularGraphOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new PNGReactionOutputHandler()));

#endif // HAVE_CAIRO_PNG_SUPPORT

#ifdef HAVE_CAIRO_PDF_SUPPORT

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new PDFMolecularGraphOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new PDFReactionOutputHandler()));

#endif // HAVE_CAIRO_PDF_SUPPORT

#ifdef HAVE_CAIRO_PS_SUPPORT

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new PSMolecularGraphOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new PSReactionOutputHandler()));

#endif // HAVE_CAIRO_PS_SUPPORT

#ifdef HAVE_CAIRO_SVG_SUPPORT

            DataIOManager<MolecularGraph>::registerOutputHandler(DataIOManager<MolecularGraph>::OutputHandlerPointer(new SVGMolecularGraphOutputHandler()));
            DataIOManager<Reaction>::registerOutputHandler(DataIOManager<Reaction>::OutputHandlerPointer(new SVGReactionOutputHandler()));

#endif // HAVE_CAIRO_SVG_SUPPORT

        }

    } init;
}
