/* 
 * DataFormatTest.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include <boost/test/auto_unit_test.hpp>

#include "CDPL/Vis/DataFormat.hpp"
#include "CDPL/Base/DataFormat.hpp"


BOOST_AUTO_TEST_CASE(DataFormatTest)
{
	using namespace CDPL;
	using namespace Vis;

	BOOST_CHECK(DataFormat::PNG.getName() == "PNG");
	BOOST_CHECK(DataFormat::PNG.getDescription() == "Portable Network Graphics");
	BOOST_CHECK(DataFormat::PNG.getMimeType() == "image/png");
	BOOST_CHECK(DataFormat::PNG.isMultiRecordFormat() == false);

	BOOST_CHECK(DataFormat::PNG.matchesName("png"));
	BOOST_CHECK(DataFormat::PNG.matchesMimeType("image/png"));
	BOOST_CHECK(DataFormat::PNG.matchesFileExtension("png"));

//-----

	BOOST_CHECK(DataFormat::PDF.getName() == "PDF");
	BOOST_CHECK(DataFormat::PDF.getDescription() == "Adobe Portable Document Format");
	BOOST_CHECK(DataFormat::PDF.getMimeType() == "application/pdf");
	BOOST_CHECK(DataFormat::PDF.isMultiRecordFormat() == false);

	BOOST_CHECK(DataFormat::PDF.matchesName("pdf"));
	BOOST_CHECK(DataFormat::PDF.matchesMimeType("application/pdf"));
	BOOST_CHECK(DataFormat::PDF.matchesFileExtension("pdf"));

//-----

	BOOST_CHECK(DataFormat::SVG.getName() == "SVG");
	BOOST_CHECK(DataFormat::SVG.getDescription() == "Scalable Vector Graphics");
	BOOST_CHECK(DataFormat::SVG.getMimeType() == "image/svg+xml");
	BOOST_CHECK(DataFormat::SVG.isMultiRecordFormat() == false);

	BOOST_CHECK(DataFormat::SVG.matchesName("svg"));
	BOOST_CHECK(DataFormat::SVG.matchesMimeType("image/svg+xml"));
	BOOST_CHECK(DataFormat::SVG.matchesFileExtension("svg"));

//-----

	BOOST_CHECK(DataFormat::PS.getName() == "PS");
	BOOST_CHECK(DataFormat::PS.getDescription() == "Adobe PostScript");
	BOOST_CHECK(DataFormat::PS.getMimeType() == "application/postscript");
	BOOST_CHECK(DataFormat::PS.isMultiRecordFormat() == false);

	BOOST_CHECK(DataFormat::PS.matchesName("ps"));
	BOOST_CHECK(DataFormat::PS.matchesMimeType("application/postscript"));
	BOOST_CHECK(DataFormat::PS.matchesFileExtension("ps"));
	BOOST_CHECK(DataFormat::PS.matchesFileExtension("eps"));
}

