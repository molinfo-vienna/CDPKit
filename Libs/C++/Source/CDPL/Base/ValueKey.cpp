/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ValueKey.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/unordered_map.hpp>

#include "CDPL/Base/ValueKey.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Base
	{

		void initValueKey() {}
	}
}


namespace
{

	typedef boost::unordered_map<std::size_t, std::string> KeyNameMap;

	KeyNameMap& getNameMap()
	{
		static KeyNameMap name_map;

		return name_map;
	}
}


using namespace CDPL; 


const Base::ValueKey Base::ValueKey::NONE = Base::ValueKey::create("NONE"); 

Base::ValueKey Base::ValueKey::create(const std::string& name)
{
	static std::size_t next_id = 0;

	ValueKey key(next_id++);

	key.setName(name);

	return key;
}

void Base::ValueKey::setName(const std::string& name) const
{
	KeyNameMap& names = getNameMap();

	names[numericID] = name;
}

const std::string& Base::ValueKey::getName() const
{
	KeyNameMap& names = getNameMap();

	KeyNameMap::const_iterator it = names.find(numericID);

	if (it != names.end())
		return it->second;

	throw ItemNotFound("ValueKey: name of key not found");
}

