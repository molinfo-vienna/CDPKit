/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataIOBase.cpp 
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

#include <functional>
#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Base/DataIOBase.hpp"


using namespace CDPL;


std::size_t Base::DataIOBase::registerIOCallback(const IOCallbackFunction& cb)
{
	std::size_t id = 0;
	std::size_t num_callbacks = callbacks.size();

	for ( ; id < num_callbacks && std::find_if(callbacks.begin(), callbacks.end(),
											   boost::bind(std::equal_to<std::size_t>(),
														   boost::bind(&CallbackListEntry::first, _1),
														   id)) != callbacks.end(); id++);
	callbacks.push_back(CallbackListEntry(id, cb));

	return id;
}

void Base::DataIOBase::unregisterIOCallback(std::size_t id)
{
	callbacks.erase(std::remove_if(callbacks.begin(), callbacks.end(), boost::bind(std::equal_to<std::size_t>(),
																				   boost::bind(&CallbackListEntry::first, _1),
																				   id)),
					callbacks.end());
}

void Base::DataIOBase::invokeIOCallbacks() const
{
	std::for_each(callbacks.begin(), callbacks.end(), boost::bind(&IOCallbackFunction::operator(),
																  boost::bind(&CallbackListEntry::second, _1), 
																  boost::ref(*this)));
}

Base::DataIOBase& Base::DataIOBase::operator=(const DataIOBase& io_base)
{
	if (&io_base == this)
		return *this;

	ControlParameterContainer::operator=(io_base);

	return *this;
}
