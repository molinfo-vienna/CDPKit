/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Controllable.cpp 
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

#include "CDPL/Base/Controllable.hpp"


using namespace CDPL;


std::size_t Base::Controllable::getNumParameters() const
{
	return controlParams.getSize();
}

void Base::Controllable::setParameter(const ValueKey& key, const Variant& v)
{
	controlParams.setParameter(key, v);
}

void Base::Controllable::setParameters(const ControlParameterList& cp_list)
{
	controlParams = cp_list;
}

bool Base::Controllable::removeParameter(const ValueKey& key)
{
	return controlParams.removeParameter(key);
}

void Base::Controllable::clearParameters()
{
	controlParams.clear();
}

const Base::Variant& Base::Controllable::getParameter(const ValueKey& key, bool throw_ex, bool local) const
{
	return controlParams.getParameter(key, throw_ex, local);
}

bool Base::Controllable::isParameterSet(const ValueKey& key, bool local) const
{
	return controlParams.isParameterSet(key, local);
}

Base::Controllable::ConstParameterIterator Base::Controllable::getParametersBegin() const
{
	return controlParams.getParametersBegin();
}

Base::Controllable::ConstParameterIterator Base::Controllable::getParametersEnd() const
{
	return controlParams.getParametersEnd();
}

void Base::Controllable::setParent(const ControlParameterList* parent)
{
	controlParams.setParent(parent);
}

void Base::Controllable::setParent(const Controllable& parent)
{
	controlParams.setParent(&parent.controlParams);
}

const Base::ControlParameterList* Base::Controllable::getParent() const
{
	return controlParams.getParent();
}

std::size_t Base::Controllable::registerParameterChangedCallback(const ParameterChangedCallbackFunction& cb)
{
	return controlParams.registerParameterChangedCallback(cb);
}

void Base::Controllable::unregisterParameterChangedCallback(std::size_t id)
{
	controlParams.unregisterParameterChangedCallback(id);
}

std::size_t Base::Controllable::registerParameterRemovedCallback(const ParameterRemovedCallbackFunction& cb)
{
	return controlParams.registerParameterRemovedCallback(cb);
}

void Base::Controllable::unregisterParameterRemovedCallback(std::size_t id)
{
	controlParams.unregisterParameterRemovedCallback(id);
}

std::size_t Base::Controllable::registerParentChangedCallback(const ParentChangedCallbackFunction& cb)
{
	return controlParams.registerParentChangedCallback(cb);
}

void Base::Controllable::unregisterParentChangedCallback(std::size_t id)
{
	controlParams.unregisterParentChangedCallback(id);
}

Base::ControlParameterList& Base::Controllable::getParameters()
{
	return controlParams;
}

const Base::ControlParameterList& Base::Controllable::getParameters() const
{
	return controlParams;
}

Base::Controllable& Base::Controllable::operator=(const Controllable& controllable)
{
	if (this == &controllable)
		return *this;

	controlParams = controllable.controlParams;

	return *this;
}
