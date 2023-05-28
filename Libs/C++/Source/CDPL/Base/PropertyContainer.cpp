/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PropertyContainer.cpp 
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

#include "CDPL/Base/PropertyContainer.hpp"
 

using namespace CDPL;


Base::PropertyContainer::PropertyContainer(const PropertyContainer& cntnr): properties(cntnr.properties) {}

Base::PropertyContainer::~PropertyContainer() {}

std::size_t Base::PropertyContainer::getNumProperties() const
{
	return properties.size();
}

Base::PropertyContainer::ConstPropertyIterator Base::PropertyContainer::getPropertiesBegin() const
{
	return properties.begin();
}

Base::PropertyContainer::ConstPropertyIterator Base::PropertyContainer::getPropertiesEnd() const
{
	return properties.end();
}

bool Base::PropertyContainer::removeProperty(const LookupKey& key)
{
	return (properties.erase(key) > 0);
}

void Base::PropertyContainer::clearProperties()
{
	properties.clear();
}

void Base::PropertyContainer::addProperties(const PropertyContainer& cntnr)
{
	if (this == &cntnr)
		return;

	PropertyMap::const_iterator cntnr_props_end = cntnr.properties.end();

	for (PropertyMap::const_iterator it = cntnr.properties.begin(); it != cntnr_props_end; ++it) {
		const Variant& val = it->second;
		const LookupKey& key = it->first;

		properties[key] = val;
	}
}

void Base::PropertyContainer::copyProperties(const PropertyContainer& cntnr)
{
	if (this == &cntnr)
		return;

	properties = cntnr.properties;
}

void Base::PropertyContainer::swap(PropertyContainer& cntnr)
{
	properties.swap(cntnr.properties);
}

Base::PropertyContainer& Base::PropertyContainer::operator=(const PropertyContainer& cntnr)
{
	if (this == &cntnr)
		return *this;

	copyProperties(cntnr);

	return *this;
}
