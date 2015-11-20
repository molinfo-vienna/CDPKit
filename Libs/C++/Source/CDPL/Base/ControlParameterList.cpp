/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterList.cpp 
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

#include <algorithm>
#include <functional>

#include <boost/bind.hpp>

#include "CDPL/Base/ControlParameterList.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


namespace
{

	const Base::Variant NIL;
}


Base::ControlParameterList::~ControlParameterList()
{
	if (parent)
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());

	ChildList tmp_children;
	tmp_children.swap(children);

	std::for_each(tmp_children.begin(), tmp_children.end(),
				  boost::bind(&ControlParameterList::setParent, _1, static_cast<ControlParameterList*>(0)));
}

std::size_t Base::ControlParameterList::getSize() const
{
	return parameters.size();
}

void Base::ControlParameterList::setParameter(const ValueKey& key, const Variant& val)
{
	if (val.isEmpty()) {
		removeParameter(key);
		return;
	}

	parameters[key] = val;
	parameterChanged(key, val);
}

bool Base::ControlParameterList::removeParameter(const ValueKey& key)
{
	ParameterMap::iterator it = parameters.find(key);

	if (it == parameters.end())
		return false;

	parameters.erase(it);
	parameterRemoved(key);

	return true;
}

void Base::ControlParameterList::clear()
{
	ParameterMap::iterator params_end = parameters.end();

	for (ParameterMap::iterator it = parameters.begin(); it != params_end; ) {
		ValueKey key = it->first;

		parameters.erase(it++);
		parameterRemoved(key);
	}
}

const Base::Variant& Base::ControlParameterList::getParameter(const ValueKey& key, bool throw_ex, bool local) const
{
	ConstParameterIterator it = parameters.find(key);
	
	if (it != parameters.end())
		return it->second;

	if (local || !parent) {
		if (throw_ex)
			throw ItemNotFound("ControlParameterList: parameter " 
							   + key.getName() + " not found");
		return NIL;
	}

	return parent->getParameter(key, throw_ex);
}

bool Base::ControlParameterList::isParameterSet(const ValueKey& key, bool local) const
{
	if (parameters.find(key) != parameters.end()) 
		return true;

	if (local)
		return false;

	if (parent)
		return parent->isParameterSet(key, local);

	return false;
}

Base::ControlParameterList::ConstParameterIterator Base::ControlParameterList::getParametersBegin() const
{
	return parameters.begin();
}

Base::ControlParameterList::ConstParameterIterator Base::ControlParameterList::getParametersEnd() const
{
	return parameters.end();
}

void Base::ControlParameterList::setParent(const ControlParameterList* new_parent)
{
	if (new_parent == this)
		return;

	if (parent == new_parent)
		return;

	if (new_parent)
		new_parent->children.push_back(this);

	if (parent)
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());

	parent = new_parent;

	parentChanged();
}

const Base::ControlParameterList* Base::ControlParameterList::getParent() const
{
	return parent;
}

std::size_t Base::ControlParameterList::registerParameterChangedCallback(const ParameterChangedCallbackFunction& cb)
{
	std::size_t id = 0;
	std::size_t num_callbacks = paramChangedCallbacks.size();

	for ( ; id < num_callbacks && std::find_if(paramChangedCallbacks.begin(), paramChangedCallbacks.end(),
											   boost::bind(std::equal_to<std::size_t>(),
														   boost::bind(&ParamChangedCallbackListEntry::first, _1),
														   id)) != paramChangedCallbacks.end(); id++);

	paramChangedCallbacks.push_back(ParamChangedCallbackListEntry(id, cb));

	return id;
}

void Base::ControlParameterList::unregisterParameterChangedCallback(std::size_t id)
{
	paramChangedCallbacks.erase(std::remove_if(paramChangedCallbacks.begin(), paramChangedCallbacks.end(), 
											   boost::bind(std::equal_to<std::size_t>(),
														   boost::bind(&ParamChangedCallbackListEntry::first, _1),
														   id)),
								paramChangedCallbacks.end());
}

std::size_t Base::ControlParameterList::registerParameterRemovedCallback(const ParameterRemovedCallbackFunction& cb)
{
	std::size_t id = 0;
	std::size_t num_callbacks = paramRemovedCallbacks.size();

	for ( ; id < num_callbacks && std::find_if(paramRemovedCallbacks.begin(), paramRemovedCallbacks.end(),
											   boost::bind(std::equal_to<std::size_t>(),
														   boost::bind(&ParamRemovedCallbackListEntry::first, _1),
														   id)) != paramRemovedCallbacks.end(); id++);

	paramRemovedCallbacks.push_back(ParamRemovedCallbackListEntry(id, cb));

	return id;
}

void Base::ControlParameterList::unregisterParameterRemovedCallback(std::size_t id)
{
	paramRemovedCallbacks.erase(std::remove_if(paramRemovedCallbacks.begin(), paramRemovedCallbacks.end(), 
											   boost::bind(std::equal_to<std::size_t>(),
														   boost::bind(&ParamRemovedCallbackListEntry::first, _1),
														   id)),
								paramRemovedCallbacks.end());
}

std::size_t Base::ControlParameterList::registerParentChangedCallback(const ParentChangedCallbackFunction& cb)
{
	std::size_t id = 0;
	std::size_t num_callbacks = parentChangedCallbacks.size();

	for ( ; id < num_callbacks && std::find_if(parentChangedCallbacks.begin(), parentChangedCallbacks.end(),
											   boost::bind(std::equal_to<std::size_t>(),
														   boost::bind(&ParentChangedCallbackListEntry::first, _1),
														   id)) != parentChangedCallbacks.end(); id++);

	parentChangedCallbacks.push_back(ParentChangedCallbackListEntry(id, cb));

	return id;
}

void Base::ControlParameterList::unregisterParentChangedCallback(std::size_t id)
{
	parentChangedCallbacks.erase(std::remove_if(parentChangedCallbacks.begin(), parentChangedCallbacks.end(), 
												boost::bind(std::equal_to<std::size_t>(),
															boost::bind(&ParentChangedCallbackListEntry::first, _1),
															id)),
								 parentChangedCallbacks.end());
}

Base::ControlParameterList& Base::ControlParameterList::operator=(const ControlParameterList& cpl)
{
	clear();

	ConstParameterIterator cpl_params_end = cpl.parameters.end();

	for (ConstParameterIterator it = cpl.parameters.begin(); it != cpl_params_end; ++it) {
		const ParameterEntry& item = *it;

		setParameter(item.first, item.second);
	}

	return *this;
}

void Base::ControlParameterList::parameterRemoved(const ValueKey& key) const
{
	std::for_each(paramRemovedCallbacks.begin(), paramRemovedCallbacks.end(), 
				  boost::bind(&ParameterRemovedCallbackFunction::operator(),
							  boost::bind(&ParamRemovedCallbackListEntry::second, _1),
							  boost::ref(key))); 

	std::for_each(children.begin(), children.end(),
				  boost::bind(&ControlParameterList::parentParameterRemoved, _1, boost::ref(key)));
}

void Base::ControlParameterList::parameterChanged(const ValueKey& key, const Variant& val) const
{
	std::for_each(paramChangedCallbacks.begin(), paramChangedCallbacks.end(), 
				  boost::bind(&ParameterChangedCallbackFunction::operator(),
							  boost::bind(&ParamChangedCallbackListEntry::second, _1),
							  boost::ref(key), boost::ref(val))); 

	std::for_each(children.begin(), children.end(),
				  boost::bind(&ControlParameterList::parentParameterChanged, _1, boost::ref(key), boost::ref(val)));
}

void Base::ControlParameterList::parentParameterRemoved(const ValueKey& key) const
{
	ConstParameterIterator it = parameters.find(key);
	
	if (it != parameters.end())
		return;

	parameterRemoved(key);
}

void Base::ControlParameterList::parentParameterChanged(const ValueKey& key, const Variant& val) const
{
	ConstParameterIterator it = parameters.find(key);
	
	if (it != parameters.end())
		return;

	parameterChanged(key, val);
}

void Base::ControlParameterList::parentChanged() const
{
	std::for_each(parentChangedCallbacks.begin(), parentChangedCallbacks.end(), 
				  boost::bind(&ParentChangedCallbackFunction::operator(),
							  boost::bind(&ParentChangedCallbackListEntry::second, _1))); 

	std::for_each(children.begin(), children.end(),
				  boost::bind(&ControlParameterList::parentChanged, _1));
}
