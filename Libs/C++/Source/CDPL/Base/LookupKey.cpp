/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * LookupKey.cpp 
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

#include <unordered_map>
#include <atomic>
#include <mutex>

#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Base
	{

		void initLookupKey() {}
	}
}


namespace
{

	typedef std::unordered_map<std::size_t, std::string> KeyNameMap;

	KeyNameMap& getNameMap()
	{
		static KeyNameMap map;

		return map;
	}
}


using namespace CDPL; 


const Base::LookupKey Base::LookupKey::NONE = Base::LookupKey::create("NONE"); 


Base::LookupKey Base::LookupKey::create(const std::string& name)
{
	static std::atomic<std::size_t> next_id(0);

	LookupKey key(next_id.fetch_add(1, std::memory_order_relaxed));

	key.setName(name);

	return key;
}

void Base::LookupKey::setName(const std::string& name) const
{
	static std::mutex mutex;

	std::lock_guard<std::mutex> lock(mutex);

	getNameMap()[numericID] = name;
}

const std::string& Base::LookupKey::getName() const
{
	KeyNameMap& name_map = getNameMap();

	KeyNameMap::const_iterator it = name_map.find(numericID);

	if (it != name_map.end())
		return it->second;

	throw ItemNotFound("LookupKey: name of key not found");
}

