/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ConfigInfoExport.cpp 
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

#include "Exports.hpp"


void CDPLPython::exportConfigInfo()
{
	using namespace boost;

	python::scope module;

#ifdef HAVE_QT
    module.attr("HAVE_QT") = true;
#else
    module.attr("HAVE_QT") = false;
#endif

#ifdef HAVE_CAIRO
	module.attr("HAVE_CAIRO") = true;
#else
	module.attr("HAVE_CAIRO") = true;
#endif

#ifdef HAVE_CAIRO_PNG_SUPPORT
	module.attr("HAVE_CAIRO_PNG_SUPPORT") = true;
#else
	module.attr("HAVE_CAIRO_PNG_SUPPORT") = false;
#endif

#ifdef HAVE_CAIRO_PDF_SUPPORT
	module.attr("HAVE_CAIRO_PDF_SUPPORT") = true;
#else
	module.attr("HAVE_CAIRO_PDF_SUPPORT") = false;
#endif

#ifdef HAVE_CAIRO_PS_SUPPORT
	module.attr("HAVE_CAIRO_PS_SUPPORT") = true;
#else
	module.attr("HAVE_CAIRO_PS_SUPPORT") = false;
#endif

#ifdef HAVE_CAIRO_SVG_SUPPORT
	module.attr("HAVE_CAIRO_SVG_SUPPORT") = true;
#else
	module.attr("HAVE_CAIRO_SVG_SUPPORT") = false;
#endif

#ifdef HAVE_SQLITE3
    module.attr("HAVE_SQLITE3") = true;
#else
    module.attr("HAVE_SQLITE3") = false;
#endif

#ifdef HAVE_BOOST_FILESYSTEM
    module.attr("HAVE_BOOST_FILESYSTEM") = true;
#else
    module.attr("HAVE_BOOST_FILESYSTEM") = false;
#endif

#ifdef HAVE_BOOST_IOSTREAMS
    module.attr("HAVE_BOOST_IOSTREAMS") = true;
#else
    module.attr("HAVE_BOOST_IOSTREAMS") = false;
#endif

#ifdef HAVE_NUMPY
    module.attr("HAVE_NUMPY") = true;
#else
    module.attr("HAVE_NUMPY") = false;
#endif

}
