/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

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

#include <algorithm>
#include <functional>
#include <locale>

#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL; 


const std::string& Base::DataFormat::getDescription() const
{
	return description;
}

void Base::DataFormat::setDescription(const std::string& descr)
{
	description = descr;
}

const std::string& Base::DataFormat::getName() const
{
	return name;
}

void Base::DataFormat::setName(const std::string& name)
{
	this->name = name;
}

const std::string& Base::DataFormat::getMimeType() const
{
	return mimeType;
}

void Base::DataFormat::setMimeType(const std::string& mime_type)
{
	mimeType = mime_type;
}

std::size_t Base::DataFormat::getNumFileExtensions() const
{
	return fileExtensions.size();
}

Base::DataFormat::ConstFileExtensionIterator Base::DataFormat::getFileExtensionsBegin() const
{
	return fileExtensions.begin();
}

Base::DataFormat::ConstFileExtensionIterator Base::DataFormat::getFileExtensionsEnd() const
{
	return fileExtensions.end();
}

Base::DataFormat::FileExtensionIterator Base::DataFormat::getFileExtensionsBegin() 
{
	return fileExtensions.begin();
}

Base::DataFormat::FileExtensionIterator Base::DataFormat::getFileExtensionsEnd() 
{
	return fileExtensions.end();
}

Base::DataFormat& Base::DataFormat::addFileExtension(const std::string& file_ext)
{
	fileExtensions.push_back(file_ext);

	return *this;
}

const std::string& Base::DataFormat::getFileExtension(std::size_t idx) const
{
	if (idx >= fileExtensions.size())
		throw IndexError("DataFormat: file extension index out of bounds");

	return fileExtensions[idx];
}

void Base::DataFormat::setFileExtension(std::size_t idx, const std::string& file_ext)
{
	if (idx >= fileExtensions.size())
		throw IndexError("DataFormat: file extension index out of bounds");

	fileExtensions[idx] = file_ext;
}

void Base::DataFormat::removeFileExtension(std::size_t idx)
{
	if (idx >= fileExtensions.size())
		throw IndexError("DataFormat: file extension index out of bounds");

	fileExtensions.erase(fileExtensions.begin() + idx);
}

Base::DataFormat::FileExtensionIterator Base::DataFormat::removeFileExtension(const FileExtensionIterator& it)
{
	if (it < fileExtensions.begin() || it >= fileExtensions.end())
		throw RangeError("DataFormat: extension iterator out of valid range");

	return fileExtensions.erase(it);
}

void Base::DataFormat::clearFileExtensions()
{
	fileExtensions.clear();
}

bool Base::DataFormat::isMultiRecordFormat() const
{
	return multiRecordFormat;
}

void Base::DataFormat::setMultiRecordFormat(bool multi)
{
	multiRecordFormat = multi;
}

bool Base::DataFormat::matchesName(const std::string& query_name) const
{
	using namespace std::placeholders;
	
	if (name.length() != query_name.length())
		return false;

	const std::locale& locale = std::locale::classic();
	char (*tolower)(char, const std::locale&) = &std::tolower;

	return std::equal(name.begin(), name.end(), query_name.begin(),
					  std::bind(std::equal_to<char>(), 
								std::bind(tolower, _1, std::ref(locale)),
								std::bind(tolower, _2, std::ref(locale))));
}

bool Base::DataFormat::matchesMimeType(const std::string& query_type) const
{
	using namespace std::placeholders;
	
	if (mimeType.length() != query_type.length())
		return false;

	const std::locale& locale = std::locale::classic();
	char (*tolower)(char, const std::locale&) = &std::tolower;

	return std::equal(mimeType.begin(), mimeType.end(), query_type.begin(),
					  std::bind(std::equal_to<char>(), 
								std::bind(tolower, _1, std::ref(locale)),
								std::bind(tolower, _2, std::ref(locale))));
}

bool Base::DataFormat::matchesFileExtension(const std::string& query_ext) const
{
	using namespace std::placeholders;
	
	ConstFileExtensionIterator ext_list_end = fileExtensions.end();

	const std::locale& locale = std::locale::classic();
	char (*tolower)(char, const std::locale&) = &std::tolower;

	for (ConstFileExtensionIterator it = fileExtensions.begin(); it != ext_list_end; ++it) {
		const std::string& file_ext = *it;

		if (file_ext.length() != query_ext.length())
			continue;

		if (std::equal(file_ext.begin(), file_ext.end(), query_ext.begin(),
					   std::bind(std::equal_to<char>(), std::bind(tolower, _1, std::ref(locale)), std::bind(tolower, _2, std::ref(locale)))))
			return true;
	}

	return false;
}

bool Base::DataFormat::operator==(const DataFormat& fmt) const
{
	return (matchesMimeType(fmt.mimeType) && matchesName(fmt.name));
}

bool Base::DataFormat::operator!=(const DataFormat& fmt) const
{
	return !operator==(fmt);
}
