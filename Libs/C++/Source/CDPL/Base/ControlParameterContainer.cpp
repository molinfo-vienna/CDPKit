/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterContainer.cpp 
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

#include "CDPL/Base/ControlParameterContainer.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Base::ControlParameterContainer::~ControlParameterContainer()
{
	if (parent)
		parent->children.erase(std::remove(parent->children.begin(), parent->children.end(), this), parent->children.end());

	ChildContainer tmp_children;
	tmp_children.swap(children);

	std::for_each(tmp_children.begin(), tmp_children.end(),
				  std::bind(&ControlParameterContainer::setParent, std::placeholders::_1,
							static_cast<ControlParameterContainer*>(0)));
}

std::size_t Base::ControlParameterContainer::getNumParameters() const
{
	return parameters.size();
}

bool Base::ControlParameterContainer::removeParameter(const LookupKey& key)
{
	ParameterMap::iterator it = parameters.find(key);

	if (it == parameters.end())
		return false;

	parameters.erase(it);
	parameterRemoved(key);

	return true;
}

void Base::ControlParameterContainer::clearParameters()
{
	ParameterMap::iterator params_end = parameters.end();

	for (ParameterMap::iterator it = parameters.begin(); it != params_end; ) {
		LookupKey key = it->first;

		parameters.erase(it++);
		parameterRemoved(key);
	}
}

const Base::Any& Base::ControlParameterContainer::getParameter(const LookupKey& key, bool throw_ex, bool local) const
{
	static const Base::Any NOT_FOUND;
	
	ConstParameterIterator it = parameters.find(key);
	
	if (it != parameters.end())
		return it->second;

	if (local || !parent) {
		if (throw_ex)
			throw ItemNotFound("ControlParameterContainer: parameter " + key.getName() + " not found");

		return NOT_FOUND;
	}

	return parent->getParameter(key, throw_ex);
}

bool Base::ControlParameterContainer::isParameterSet(const LookupKey& key, bool local) const
{
	if (parameters.find(key) != parameters.end()) 
		return true;

	if (local)
		return false;

	if (parent)
		return parent->isParameterSet(key, local);

	return false;
}

void Base::ControlParameterContainer::addParameters(const ControlParameterContainer& cntnr)
{
	if (this == &cntnr)
		return;

	ConstParameterIterator cntnr_params_end = cntnr.parameters.end();

	for (ConstParameterIterator it = cntnr.parameters.begin(); it != cntnr_params_end; ++it) {
		const ParameterEntry& item = *it;

		setParameter(item.first, item.second);
	}
}

void Base::ControlParameterContainer::copyParameters(const ControlParameterContainer& cntnr)
{
	if (this == &cntnr)
		return;

	clearParameters();

	ConstParameterIterator cntnr_params_end = cntnr.parameters.end();

	for (ConstParameterIterator it = cntnr.parameters.begin(); it != cntnr_params_end; ++it) {
		const ParameterEntry& item = *it;

		setParameter(item.first, item.second);
	}
}

Base::ControlParameterContainer::ConstParameterIterator Base::ControlParameterContainer::getParametersBegin() const
{
	return parameters.begin();
}

Base::ControlParameterContainer::ConstParameterIterator Base::ControlParameterContainer::getParametersEnd() const
{
	return parameters.end();
}

Base::ControlParameterContainer::ConstParameterIterator Base::ControlParameterContainer::begin() const
{
	return parameters.begin();
}

Base::ControlParameterContainer::ConstParameterIterator Base::ControlParameterContainer::end() const
{
	return parameters.end();
}

void Base::ControlParameterContainer::setParent(const ControlParameterContainer* new_parent)
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

const Base::ControlParameterContainer* Base::ControlParameterContainer::getParent() const
{
	return parent;
}

std::size_t Base::ControlParameterContainer::registerParameterChangedCallback(const ParameterChangedCallbackFunction& cb)
{
	std::size_t id = 0;
	std::size_t num_callbacks = paramChangedCallbacks.size();

	for ( ; id < num_callbacks && std::find_if(paramChangedCallbacks.begin(), paramChangedCallbacks.end(),
											   std::bind(std::equal_to<std::size_t>(),
														 std::bind(&ParamChangedCallbackContainerEntry::first, std::placeholders::_1),
														 id)) != paramChangedCallbacks.end(); id++);

	paramChangedCallbacks.push_back(ParamChangedCallbackContainerEntry(id, cb));

	return id;
}

void Base::ControlParameterContainer::unregisterParameterChangedCallback(std::size_t id)
{
	paramChangedCallbacks.erase(std::remove_if(paramChangedCallbacks.begin(), paramChangedCallbacks.end(), 
											   std::bind(std::equal_to<std::size_t>(),
														 std::bind(&ParamChangedCallbackContainerEntry::first, std::placeholders::_1),
														 id)),
								paramChangedCallbacks.end());
}

std::size_t Base::ControlParameterContainer::registerParameterRemovedCallback(const ParameterRemovedCallbackFunction& cb)
{
	std::size_t id = 0;
	std::size_t num_callbacks = paramRemovedCallbacks.size();

	for ( ; id < num_callbacks && std::find_if(paramRemovedCallbacks.begin(), paramRemovedCallbacks.end(),
											   std::bind(std::equal_to<std::size_t>(),
														 std::bind(&ParamRemovedCallbackContainerEntry::first, std::placeholders::_1),
														 id)) != paramRemovedCallbacks.end(); id++);

	paramRemovedCallbacks.push_back(ParamRemovedCallbackContainerEntry(id, cb));

	return id;
}

void Base::ControlParameterContainer::unregisterParameterRemovedCallback(std::size_t id)
{
	paramRemovedCallbacks.erase(std::remove_if(paramRemovedCallbacks.begin(), paramRemovedCallbacks.end(), 
											   std::bind(std::equal_to<std::size_t>(),
														 std::bind(&ParamRemovedCallbackContainerEntry::first, std::placeholders::_1),
														 id)),
								paramRemovedCallbacks.end());
}

std::size_t Base::ControlParameterContainer::registerParentChangedCallback(const ParentChangedCallbackFunction& cb)
{
	std::size_t id = 0;
	std::size_t num_callbacks = parentChangedCallbacks.size();

	for ( ; id < num_callbacks && std::find_if(parentChangedCallbacks.begin(), parentChangedCallbacks.end(),
											   std::bind(std::equal_to<std::size_t>(),
														 std::bind(&ParentChangedCallbackContainerEntry::first, std::placeholders::_1),
														 id)) != parentChangedCallbacks.end(); id++);

	parentChangedCallbacks.push_back(ParentChangedCallbackContainerEntry(id, cb));

	return id;
}

void Base::ControlParameterContainer::unregisterParentChangedCallback(std::size_t id)
{
	parentChangedCallbacks.erase(std::remove_if(parentChangedCallbacks.begin(), parentChangedCallbacks.end(), 
												std::bind(std::equal_to<std::size_t>(),
														  std::bind(&ParentChangedCallbackContainerEntry::first, std::placeholders::_1),
														  id)),
								 parentChangedCallbacks.end());
}

Base::ControlParameterContainer& Base::ControlParameterContainer::operator=(const ControlParameterContainer& cntnr)
{
	if (this == &cntnr)
		return *this;

	copyParameters(cntnr);

	return *this;
}

void Base::ControlParameterContainer::parameterRemoved(const LookupKey& key) const
{
	using namespace std::placeholders;
	
	std::for_each(paramRemovedCallbacks.begin(), paramRemovedCallbacks.end(), 
				  std::bind(&ParameterRemovedCallbackFunction::operator(),
							std::bind(&ParamRemovedCallbackContainerEntry::second, _1),
							std::ref(key))); 

	std::for_each(children.begin(), children.end(),
				  std::bind(&ControlParameterContainer::parentParameterRemoved, _1, std::ref(key)));
}

void Base::ControlParameterContainer::parameterChanged(const LookupKey& key, const Any& val) const
{
	using namespace std::placeholders;
		
	std::for_each(paramChangedCallbacks.begin(), paramChangedCallbacks.end(), 
				  std::bind(&ParameterChangedCallbackFunction::operator(),
							std::bind(&ParamChangedCallbackContainerEntry::second, _1),
							std::ref(key), std::ref(val))); 

	std::for_each(children.begin(), children.end(),
				  std::bind(&ControlParameterContainer::parentParameterChanged, _1, std::ref(key), std::ref(val)));
}

void Base::ControlParameterContainer::parentParameterRemoved(const LookupKey& key) const
{
	ConstParameterIterator it = parameters.find(key);
	
	if (it != parameters.end())
		return;

	parameterRemoved(key);
}

void Base::ControlParameterContainer::parentParameterChanged(const LookupKey& key, const Any& val) const
{
	ConstParameterIterator it = parameters.find(key);
	
	if (it != parameters.end())
		return;

	parameterChanged(key, val);
}

void Base::ControlParameterContainer::parentChanged() const
{
	using namespace std::placeholders;
	
	std::for_each(parentChangedCallbacks.begin(), parentChangedCallbacks.end(), 
				  std::bind(&ParentChangedCallbackFunction::operator(),
							std::bind(&ParentChangedCallbackContainerEntry::second, _1))); 

	std::for_each(children.begin(), children.end(),
				  std::bind(&ControlParameterContainer::parentChanged, _1));
}
