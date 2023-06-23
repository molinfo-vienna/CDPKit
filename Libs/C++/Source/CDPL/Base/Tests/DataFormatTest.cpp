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

#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/Exceptions.hpp"


BOOST_AUTO_TEST_CASE(DataFormatTest)
{
	using namespace CDPL;
	using namespace Base;

	const char* file_extensions[] = { "png", "xng" };

	DataFormat df1("PNG", "Portable Network Graphics", "image/png", file_extensions, file_extensions + 2, true);

	BOOST_CHECK(df1.getName() == "PNG");
	BOOST_CHECK(df1.getDescription() == "Portable Network Graphics");
	BOOST_CHECK(df1.getMimeType() == "image/png");
	BOOST_CHECK(df1.isMultiRecordFormat() == true);

	BOOST_CHECK(df1.getNumFileExtensions() == 2);

	BOOST_CHECK(const_cast<const DataFormat&>(df1).getFileExtensionsEnd() - 2 == const_cast<const DataFormat&>(df1).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df1).getFileExtensionsEnd() - 2 == const_cast<DataFormat&>(df1).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df1).getFileExtensionsEnd() - const_cast<const DataFormat&>(df1).getFileExtensionsBegin() == 2);
	BOOST_CHECK(const_cast<DataFormat&>(df1).getFileExtensionsEnd() - const_cast<DataFormat&>(df1).getFileExtensionsBegin() == 2);

	BOOST_CHECK(df1.getFileExtension(0) == "png");
	BOOST_CHECK(df1.getFileExtension(1) == "xng");

	BOOST_CHECK_THROW(df1.getFileExtension(2), IndexError);
	BOOST_CHECK_THROW(df1.getFileExtension(3), IndexError);

	BOOST_CHECK(df1.matchesName("png"));
	BOOST_CHECK(df1.matchesName("PNG"));
	BOOST_CHECK(df1.matchesName("pNg"));
	BOOST_CHECK(!df1.matchesName("pngc"));
	BOOST_CHECK(!df1.matchesName(" png"));
	BOOST_CHECK(!df1.matchesName("png "));
	BOOST_CHECK(!df1.matchesName(""));

	BOOST_CHECK(df1.matchesMimeType("image/png"));
	BOOST_CHECK(df1.matchesMimeType("IMAGE/PNG"));
	BOOST_CHECK(df1.matchesMimeType("ImAGe/pnG"));
	BOOST_CHECK(!df1.matchesMimeType("inage/png"));
	BOOST_CHECK(!df1.matchesMimeType(" image/png"));
	BOOST_CHECK(!df1.matchesMimeType("image/png "));
	BOOST_CHECK(!df1.matchesMimeType("imge/png"));
	BOOST_CHECK(!df1.matchesMimeType(""));

	BOOST_CHECK(df1.matchesFileExtension("png"));
	BOOST_CHECK(df1.matchesFileExtension("PNG"));
	BOOST_CHECK(df1.matchesFileExtension("pNg"));
	BOOST_CHECK(!df1.matchesFileExtension(" png"));
	BOOST_CHECK(!df1.matchesFileExtension("png "));
	BOOST_CHECK(!df1.matchesFileExtension("pn g"));
	BOOST_CHECK(!df1.matchesFileExtension("pnxg"));
	BOOST_CHECK(!df1.matchesFileExtension("pag"));
	BOOST_CHECK(!df1.matchesFileExtension("pg"));
	BOOST_CHECK(!df1.matchesFileExtension(""));

	BOOST_CHECK(df1.matchesFileExtension("xng"));
	BOOST_CHECK(df1.matchesFileExtension("XNG"));
	BOOST_CHECK(df1.matchesFileExtension("xnG"));
	BOOST_CHECK(!df1.matchesFileExtension(" xng"));
	BOOST_CHECK(!df1.matchesFileExtension("xng "));
	BOOST_CHECK(!df1.matchesFileExtension("xn g"));
	BOOST_CHECK(!df1.matchesFileExtension("xnxg"));
	BOOST_CHECK(!df1.matchesFileExtension("xag"));
	BOOST_CHECK(!df1.matchesFileExtension("xn"));

//-----

	DataFormat df2;

	BOOST_CHECK(df2.getName() == "");
	BOOST_CHECK(df2.getDescription() == "");
	BOOST_CHECK(df2.getMimeType() == "");
	BOOST_CHECK(df2.isMultiRecordFormat() == false);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK_THROW(df2.getFileExtension(0), IndexError);
	BOOST_CHECK_THROW(df2.getFileExtension(1), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

//-----

	df2.setName("Name");

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "");
	BOOST_CHECK(df2.getMimeType() == "");
	BOOST_CHECK(df2.isMultiRecordFormat() == false);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK_THROW(df2.getFileExtension(0), IndexError);
	BOOST_CHECK_THROW(df2.getFileExtension(1), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

//-----

	df2.setDescription("Description");

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "");
	BOOST_CHECK(df2.isMultiRecordFormat() == false);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK_THROW(df2.getFileExtension(0), IndexError);
	BOOST_CHECK_THROW(df2.getFileExtension(1), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

//-----

	df2.setMimeType("mime/type");

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == false);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK_THROW(df2.getFileExtension(0), IndexError);
	BOOST_CHECK_THROW(df2.getFileExtension(1), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

//-----

	df2.setMultiRecordFormat(true);

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK_THROW(df2.getFileExtension(0), IndexError);
	BOOST_CHECK_THROW(df2.getFileExtension(1), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

	BOOST_CHECK(!df2.matchesFileExtension(""));

//-----

	df2.addFileExtension("ext1");

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 1);

	BOOST_CHECK(df2.getFileExtension(0) == "ext1");

	BOOST_CHECK_THROW(df2.getFileExtension(1), IndexError);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1 == df2.getFileExtensionsEnd());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 1);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 1);

	BOOST_CHECK(df2.matchesFileExtension("ext1"));
	BOOST_CHECK(!df2.matchesFileExtension("ext2"));
	BOOST_CHECK(!df2.matchesFileExtension(""));

//-----

	df2.addFileExtension("ext2");

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 2);

	BOOST_CHECK(df2.getFileExtension(0) == "ext1");
	BOOST_CHECK(df2.getFileExtension(1) == "ext2");

	BOOST_CHECK_THROW(df2.getFileExtension(2), IndexError);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2 == df2.getFileExtensionsEnd());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 2);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 2);

	BOOST_CHECK(df2.matchesFileExtension("ext1"));
	BOOST_CHECK(df2.matchesFileExtension("ext2"));
	BOOST_CHECK(!df2.matchesFileExtension(""));

//-----

	df2.addFileExtension("");

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 3);

	BOOST_CHECK(df2.getFileExtension(0) == "ext1");
	BOOST_CHECK(df2.getFileExtension(1) == "ext2");
	BOOST_CHECK(df2.getFileExtension(2) == "");

	BOOST_CHECK_THROW(df2.getFileExtension(3), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 3);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2) == "");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2) == "");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(df2.matchesFileExtension("ext1"));
	BOOST_CHECK(df2.matchesFileExtension("ext2"));
	BOOST_CHECK(df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	df2.setFileExtension(2, "ext3");

	BOOST_CHECK_THROW(df2.setFileExtension(3, "ext4"), IndexError);

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 3);

	BOOST_CHECK(df2.getFileExtension(0) == "ext1");
	BOOST_CHECK(df2.getFileExtension(1) == "ext2");
	BOOST_CHECK(df2.getFileExtension(2) == "ext3");

	BOOST_CHECK_THROW(df2.getFileExtension(4), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 3);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2) == "ext3");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2) == "ext3");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(df2.matchesFileExtension("ext1"));
	BOOST_CHECK(df2.matchesFileExtension("ext2"));
	BOOST_CHECK(df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	df2.setFileExtension(2, "ext");

	BOOST_CHECK_THROW(df2.setFileExtension(3, "ext4"), IndexError);

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 3);

	BOOST_CHECK(df2.getFileExtension(0) == "ext1");
	BOOST_CHECK(df2.getFileExtension(1) == "ext2");
	BOOST_CHECK(df2.getFileExtension(2) == "ext");

	BOOST_CHECK_THROW(df2.getFileExtension(4), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 3);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2) == "ext");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2) == "ext");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(df2.matchesFileExtension("ext1"));
	BOOST_CHECK(df2.matchesFileExtension("ext2"));
	BOOST_CHECK(df2.matchesFileExtension("ext"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	*(df2.getFileExtensionsBegin() + 2) = "ext3";

	BOOST_CHECK_THROW(df2.setFileExtension(3, "ext4"), IndexError);

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 3);

	BOOST_CHECK(df2.getFileExtension(0) == "ext1");
	BOOST_CHECK(df2.getFileExtension(1) == "ext2");
	BOOST_CHECK(df2.getFileExtension(2) == "ext3");

	BOOST_CHECK_THROW(df2.getFileExtension(4), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 3);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 3);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2) == "ext3");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext2");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2) == "ext3");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 3 == df2.getFileExtensionsEnd());

	BOOST_CHECK(df2.matchesFileExtension("ext1"));
	BOOST_CHECK(df2.matchesFileExtension("ext2"));
	BOOST_CHECK(df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension("ext"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	df2.removeFileExtension(1);

	BOOST_CHECK_THROW(df2.removeFileExtension(3), IndexError);

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 2);

	BOOST_CHECK(df2.getFileExtension(0) == "ext1");
	BOOST_CHECK(df2.getFileExtension(1) == "ext3");

	BOOST_CHECK_THROW(df2.getFileExtension(2), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 2);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 2);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext3");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 2 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext1");
	BOOST_CHECK(*(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1) == "ext3");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 2 == df2.getFileExtensionsEnd());

	BOOST_CHECK(df2.matchesFileExtension("ext1"));
	BOOST_CHECK(!df2.matchesFileExtension("ext2"));
	BOOST_CHECK(df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	DataFormat::FileExtensionIterator it = df2.removeFileExtension(df2.getFileExtensionsBegin());

	BOOST_CHECK(it == df2.getFileExtensionsBegin());

	BOOST_CHECK_THROW(df2.removeFileExtension(df2.getFileExtensionsEnd()), RangeError);

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 1);

	BOOST_CHECK(df2.getFileExtension(0) == "ext3");

	BOOST_CHECK_THROW(df2.getFileExtension(1), IndexError);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 1);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 1);

	BOOST_CHECK(*const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == "ext3");
	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsBegin() + 1 == df2.getFileExtensionsEnd());

	BOOST_CHECK(*const_cast<DataFormat&>(df2).getFileExtensionsBegin() == "ext3");
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsBegin() + 1 == df2.getFileExtensionsEnd());

	BOOST_CHECK(!df2.matchesFileExtension("ext1"));
	BOOST_CHECK(!df2.matchesFileExtension("ext2"));
	BOOST_CHECK(df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	df2.clearFileExtensions();

	BOOST_CHECK(df2.getName() == "Name");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

	BOOST_CHECK(!df2.matchesFileExtension("ext1"));
	BOOST_CHECK(!df2.matchesFileExtension("ext2"));
	BOOST_CHECK(!df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

	BOOST_CHECK_THROW(df2.removeFileExtension(0), IndexError);
	BOOST_CHECK_THROW(df2.removeFileExtension(df2.getFileExtensionsBegin()), RangeError);

	BOOST_CHECK_THROW(df2.setFileExtension(0, ""), IndexError);

	BOOST_CHECK_THROW(df2.getFileExtension(0), IndexError);

//-----

	df2.setName("");

	BOOST_CHECK(df2.getName() == "");
	BOOST_CHECK(df2.getDescription() == "Description");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

	BOOST_CHECK(!df2.matchesFileExtension("ext1"));
	BOOST_CHECK(!df2.matchesFileExtension("ext2"));
	BOOST_CHECK(!df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	df2.setDescription("");

	BOOST_CHECK(df2.getName() == "");
	BOOST_CHECK(df2.getDescription() == "");
	BOOST_CHECK(df2.getMimeType() == "mime/type");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

	BOOST_CHECK(!df2.matchesFileExtension("ext1"));
	BOOST_CHECK(!df2.matchesFileExtension("ext2"));
	BOOST_CHECK(!df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	df2.setMimeType("");

	BOOST_CHECK(df2.getName() == "");
	BOOST_CHECK(df2.getDescription() == "");
	BOOST_CHECK(df2.getMimeType() == "");
	BOOST_CHECK(df2.isMultiRecordFormat() == true);

	BOOST_CHECK(df2.getNumFileExtensions() == 0);

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() == const_cast<const DataFormat&>(df2).getFileExtensionsBegin());
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() == const_cast<DataFormat&>(df2).getFileExtensionsBegin());

	BOOST_CHECK(const_cast<const DataFormat&>(df2).getFileExtensionsEnd() - const_cast<const DataFormat&>(df2).getFileExtensionsBegin() == 0);
	BOOST_CHECK(const_cast<DataFormat&>(df2).getFileExtensionsEnd() - const_cast<DataFormat&>(df2).getFileExtensionsBegin() == 0);

	BOOST_CHECK(!df2.matchesFileExtension("ext1"));
	BOOST_CHECK(!df2.matchesFileExtension("ext2"));
	BOOST_CHECK(!df2.matchesFileExtension("ext3"));
	BOOST_CHECK(!df2.matchesFileExtension(""));
	BOOST_CHECK(!df2.matchesFileExtension(" "));

//-----

	BOOST_CHECK(!(df1 == df2));
	BOOST_CHECK(df1 != df2);

	df2.setName(df1.getName());

	BOOST_CHECK(!(df1 == df2));
	BOOST_CHECK(df1 != df2);

	df2.setMimeType(df1.getMimeType());

	BOOST_CHECK(df1 == df2);
	BOOST_CHECK(!(df1 != df2));

//-----

	df1.clearFileExtensions();

	BOOST_CHECK(df1.getNumFileExtensions() == 0);

	df1.addFileExtension("a");
	df1.addFileExtension("ab");
	df1.addFileExtension("abc");
	df1.addFileExtension("abcd");

	BOOST_CHECK(df1.getNumFileExtensions() == 4);

	BOOST_CHECK(const_cast<const DataFormat&>(df1).getFileExtensionsEnd() - 
				const_cast<const DataFormat&>(df1).getFileExtensionsBegin() == 4);
	BOOST_CHECK(const_cast<DataFormat&>(df1).getFileExtensionsEnd() - 
				const_cast<DataFormat&>(df1).getFileExtensionsBegin() == 4);

	it = df1.removeFileExtension(df1.getFileExtensionsBegin());

	BOOST_CHECK(it == df1.getFileExtensionsBegin());

	it = df1.removeFileExtension(df1.getFileExtensionsBegin() + 1);

	BOOST_CHECK(it == df1.getFileExtensionsBegin() + 1);

	it = df1.removeFileExtension(--df1.getFileExtensionsEnd());

	BOOST_CHECK(it == df1.getFileExtensionsEnd());

	it = df1.removeFileExtension(df1.getFileExtensionsBegin());

	BOOST_CHECK(it == df1.getFileExtensionsEnd());
}

