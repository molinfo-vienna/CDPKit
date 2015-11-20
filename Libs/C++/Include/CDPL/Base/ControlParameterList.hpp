/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ControlParameterList.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Base::ControlParameterList.
 */

#ifndef CDPL_BASE_CONTROLPARAMETERLIST_HPP
#define CDPL_BASE_CONTROLPARAMETERLIST_HPP

#include <vector>
#include <utility>
#include <cstddef>

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/unordered_map.hpp>

#include "CDPL/Base/APIPrefix.hpp"
#include "CDPL/Base/ValueKey.hpp"
#include "CDPL/Base/Variant.hpp"


namespace CDPL 
{
	
	namespace Base
	{
		
		/**
		 * \addtogroup CDPL_BASE_CONTROL_PARAMETERS
		 * @{
		 */

		/**
		 * \brief A data structure for the storage and lookup of control-parameter values.
		 *
		 * For the explicit assignment of control-parameter values the method setParameter() is provided which
		 * expects the key of the control-parameter as its first and the value to assign as the second argument.
		 * The availability of a value for a particular control-parameter can be tested by the method isParameterSet().
		 * For the retrieval of control-parameter values the getParameter() family of overloaded methods
		 * is provided which expect the key of the control-parameter as an argument. The method getParameterOrDefault() 
		 * additionally allows to specify a default value that gets returned if an entry for the requested control-parameter
		 * value does not exist. \c %ControlParameterList guarantees that the complexity of these operations is never worse
		 * than logarithmic. 
		 *
		 * Control-parameter values are stored in an associative map as Base::ValueKey / Base::Variant pairs of type
		 * ControlParameterList::ParameterEntry. The current number of entries can be queried with the method getSize(). Iterators
		 * pointing to the beginning and end of the list are obtained via the methods getEntriesBegin() and getEntriesEnd(),
		 * respectively.
		 *
		 * \c %ControlParameterList allows for an arrangement of instances in a tree-like hierarchy where each non-root instance
		 * has exactly one parent and zero or more children. In such hierarchies, a child list forwards requests for control-parameter
		 * values to their parents if they do not contain a local entry for a given control-parameter.
		 * The parent list is set and detached by the method setParent(). A \c %ControlParameterList instance automatically keeps
		 * track of any links from and to other instances in the hierarchy and detaches any parent or child lists on object destruction.
		 *
		 * For the notification of client code about any changes that affect control-parameter values, the
		 * \c %ControlParameterList interface provides three methods for the registration of callback functions: 
		 *  - registerParameterChangedCallback() \n
		 *   registers callback target functions that get invoked when the value of a
		 * 	 control-parameter has changed 
		 *  - registerParameterRemovedCallback() \n
		 *   registers callback target functions that get invoked when a control-parameter entry
		 *   has been removed 
		 *  - and registerParentChangedCallback() \n
		 *   is used to register callback target functions that get invoked when the parent 
		 *   list has been changed or was detached
		 *
		 * Each of these methods returns a numeric identifier for the registered callback function.
		 * For callback unregistration purposes the methods unregisterParameterChangedCallback(), unregisterParameterRemovedCallback()
		 * and unregisterParentChangedCallback() are provided. These methods require the previously obtained numeric identifier of the
		 * callback to be passed as an argument. 
		 */
		class CDPL_BASE_API ControlParameterList
		{

			typedef boost::unordered_map<ValueKey, Variant, ValueKey::HashFunc> ParameterMap;

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %ControlParameterList instances.
			 */
			typedef boost::shared_ptr<ControlParameterList> SharedPointer;

			/**
			 * \brief A Base::ValueKey / Base::Variant pair used to store the control-parameter
			 *        values and associated keys.
			 */
			typedef ParameterMap::value_type ParameterEntry;

			/**
			 * \brief A constant iterator used to iterate over the control-parameter entries.
			 */
			typedef ParameterMap::const_iterator ConstParameterIterator; 
		
			/**
			 * \brief A functor class that wraps callback target functions which get invoked when the value of a
			 *        control-parameter has changed.
			 *
			 * \c %ParameterChangedCallbackFunction allows to wrap any function pointer or function object compatible with
			 * a return type of \c void and two arguments of type <tt>const Base::ValueKey&</tt> and <tt>Base::Variant</tt>.
			 * For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function2<void, const ValueKey&, const Variant&> ParameterChangedCallbackFunction;

			/**
			 * \brief A functor class that wraps callback target functions which get invoked when a control-parameter entry
			 *        has been removed.
			 *
			 * \c %ParameterRemovedCallbackFunction allows to wrap any function pointer or function object compatible with a
			 * return type of \c void and an argument of type <tt>const Base::ValueKey&</tt>. For details refer to
			 * the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 */
			typedef boost::function1<void, const ValueKey&> ParameterRemovedCallbackFunction;

			/**
			 * \brief A functor class that wraps callback target functions which get invoked when the parent 
			 *        list has been changed or was detached.
			 *
			 * \c %ParentChangedCallbackFunction allows to wrap any function pointer or function object compatible with a return type
			 * of \c void and no arguments. For details refer to the <em>Boost.Function</em> documentation [\ref BFUN]. 
			 *
			 * \see setParent()
			 */
			typedef boost::function0<void> ParentChangedCallbackFunction;

			/**
			 * \brief Constructs an empty \c %ControlParameterList instance.
			 */
			ControlParameterList(): parent(0) {}

			/**
			 * \brief Constructs a copy of the \c %ControlParameterList instance \a cpl.
			 * \param cpl The \c %ControlParameterList instance to copy.
			 * \note Only the control-parameter entries of \a cpl are copied. Entries in the parent list
			 *       of \a cpl (if set) will be ignored (see setParent()).
			 */
			ControlParameterList(const ControlParameterList& cpl): parameters(cpl.parameters), parent(0) {}

			/**
			 * \brief Destructor.
			 *
			 * The parent pointer of any children will be set to \e null before the instance gets
			 * destroyed (see setParent()).  
			 */
			~ControlParameterList();

			/**
			 * \brief Returns the number of list entries.
			 * \return The number of list entries.
			 */
			std::size_t getSize() const;

			/**
			 * \brief Sets the value of the control-parameter specified by \a key to \a value.
			 *
			 * If \a value is empty, i.e. the method Base::Variant::isEmpty() returns \c true, and a control-parameter
			 * entry for \a key exists, the entry gets erased (equivalent to removeParameter() with \a key as argument).
			 * Otherwise the control-parameter is assigned the specified value and any callback functions registered by
			 * registerParameterChangedCallback() will be invoked with \a key and \a value provided as arguments.
			 * Callbacks of affected direct and indirect children which do not have an entry for the specified control-parameter also get
			 * invoked.    
			 *
			 * \param key The key of the control-parameter value to assign.
			 * \param value The value of the control-parameter.
			 */
			void setParameter(const ValueKey& key, const Variant& value);

			/**
			 * \brief Returns the value of the control-parameter specified by \a key.
			 *
			 * If the list contains an entry for the specified control-parameter, the stored value will be returned.
			 * If an entry for the control-parameter does not exist, the results depends on the arguments
			 * \a throw_ and \a local:
			 *
			 * If a parent list has been set and the argument \a local is \c false, the request is forwarded to the parent
			 * (which may also forward the request). Otherwise an empty Base::Variant object is returned if \a _throw is \c false,
			 * and a Base::ItemNotFound exception will be thrown if \a _throw is \c true.
			 *
			 * \param key The key of the control-parameter value to return.
			 * \param throw_ Specifies whether or not to throw a Base::ItemNotFound exception if an entry
			 *               for the control-parameter does not exist.
			 * \param local Specifies whether or not the request shall be forwarded to the parent list if a local entry 
			 *              for the control-parameter does not exist.
			 * \return The stored control-parameter value or an empty Base::Variant object.
			 * \throw Base::ItemNotFound if an entry for the requested control-parameter value does not exist and \a _throw
			 *        is \c true.
			 */
			const Variant& getParameter(const ValueKey& key, bool throw_ = false, bool local = false) const;

			/**
			 * \brief Returns the value of the control-parameter specified by \a key as a \c const reference
			 *        to an object of type \a T.
			 *
			 * If the list contains an entry for the specified control-parameter, the stored value will be returned.
			 * If an entry for the control-parameter does not exist, a parent list has been set and the argument \a local
			 * is \c false, the call is forwarded to the parent (which may also forward the request). Otherwise a
			 * Base::ItemNotFound exception will be thrown.
			 *
			 * \param key The key of the control-parameter value to return.
			 * \param local Specifies whether or not the request shall be forwarded to the parent list if a local entry 
			 *              for the control-parameter does not exist.
			 * \return The stored control-parameter value as a \c const reference to an object of type \a T.
			 * \throw Base::ItemNotFound if an entry for the requested control-parameter value does not exist, and 
			 *        Base::BadCast if the stored control-parameter value cannot be casted to the target type \a T.
			 */
			template <typename T>
			const T& getParameter(const ValueKey& key, bool local = false) const;

			/**
			 * \brief Returns the value of the control-parameter specified by \a key as a \c const reference
			 *        to an object of type \a T, or the default value \a def_value if a stored value does not exist.
			 *
			 * If the list contains an entry for the specified control-parameter, the stored value will be returned.
			 * If an entry for the control-parameter does not exist, a parent list has been set and the argument \a local
			 * is \c false, the call is forwarded to the parent (which may also forward the request). Otherwise the default
			 * value specified by \a def_value is returned.
			 *
			 * \param key The key of the control-parameter for which to return the stored (or specified default) value.
			 * \param def_value The default value that shall be returned if an entry for the specified control-parameter
			 *                  does not exist.
			 * \param local Specifies whether or not the request shall be forwarded to the parent list if a local entry 
			 *              for the control-parameter does not exist.
			 * \return The stored control-parameter value or the default specified by \a def_value.
			 * \throw Base::BadCast if the stored control-parameter value cannot be casted to the target type \a T.
			 */
			template <typename T>
			const T& getParameterOrDefault(const ValueKey& key, const T& def_value, bool local = false) const;

			/**
			 * \brief Removes the entry for the control-parameter specified by \a key.
			 *
			 * If an entry for the control-parameter specified by \a key exists, the entry is removed and any callback
			 * functions registered by registerParameterRemovedCallback() will be invoked with \a key provided as an
			 * argument. Callbacks of affected direct and indirect children which do not have an entry for the specified
			 * control-parameter also get invoked.   
			 * 
			 * \param key The key of the control-parameter entry to remove.
			 * \return \c true if an entry for \a key could be found and was removed, and \c false otherwise.
			 */
			bool removeParameter(const ValueKey& key);

			/**
			 * \brief Erases all list entries.
			 *
			 * For each list entry, any callback functions registered by registerParameterRemovedCallback() will be
			 * invoked with the key of the removed control-parameter entry as an argument. Callbacks of affected direct and
			 * indirect children which do not have an entry for the erased control-parameter also get invoked.    
			 */
			void clear();

			/**
			 * \brief Tells whether or not a value has been assigned to the control-parameter specified by \a key.
			 *
			 * If the list does not contain an entry for the specified control-parameter, a parent list has been set
			 * and the argument \a local is \c false, the call is forwarded to the parent (which may also forward
			 * the call). Otherwise the result of the local search is returned.
			 *
			 * \param key The key of the control-parameter.
			 * \param local Specifies whether or not the query shall be forwarded to the parent list if a local entry 
			 *              for the control-parameter does not exist.
			 * \return \c true if an entry for the specified control-parameter could be found, and \c false otherwise.
			 */
			bool isParameterSet(const ValueKey& key, bool local = false) const;

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the entries.
			 * \return A constant iterator pointing to the beginning of the entries.
			 */
			ConstParameterIterator getParametersBegin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the entries.
			 * \return A constant iterator pointing to the end of the entries.
			 */
			ConstParameterIterator getParametersEnd() const;

			/**
			 * \brief Sets or removes the parent control-parameter list used to resolve requests for missing entries.
			 *
			 * A control-parameter list that has been set as a parent gets used whenever a request for a control-parameter
			 * value cannot be satisfied locally by the list itself. That is, if a key/value entry for a given control-parameter
			 * does not exist, the request is simply forwarded to the parent list (which may also forward the request).
			 *
			 * Any callback functions registered by registerParentChangedCallback() will be invoked after the new parent list has
			 * been set (or the old list was detached by providing a \e null pointer). Callbacks of any direct and indirect
			 * children also get invoked.
			 * 
			 * \param cpl A pointer to the parent control-parameter list or \e null. If the pointer is \e null,
			 *            the currently set parent list (if any) gets detached. 
			 */
			void setParent(const ControlParameterList* cpl);

			/**
			 * \brief Returns a pointer to the parent control-parameter list.
			 * \return A pointer to the parent control-parameter list, or \e null if no parent list has been set.
			 * \see setParent()
			 */
			const ControlParameterList* getParent() const;

			/**
			 * \brief Registers a callback target function that gets invoked when the value of a
			 *        control-parameter has changed. 
			 * \param func A ControlParameterList::ParameterChangedCallbackFunction object wrapping the target function.
			 * \return An identifier for the registered callback.
			 */
			std::size_t registerParameterChangedCallback(const ParameterChangedCallbackFunction& func);

			/**
			 * \brief Unregisters the callback specified by \a id.
			 *
			 * If a registered callback with the identifier \a id does not exist, the method has no effect.
			 *
			 * \param id The identifier of the callback to unregister.
			 */
			void unregisterParameterChangedCallback(std::size_t id);
	
			/**
			 * \brief Registers a callback target function that gets invoked when a control-parameter entry
			 *        has been removed. 
			 * \param func A ControlParameterList::ParameterRemovedCallbackFunction object wrapping the target function.
			 * \return An identifier for the registered callback.
			 */
			std::size_t registerParameterRemovedCallback(const ParameterRemovedCallbackFunction& func);

			/**
			 * \brief Unregisters the callback specified by \a id.
			 *
			 * If a registered callback with the identifier \a id does not exist, the method has no effect.
			 *
			 * \param id The identifier of the callback to unregister.
			 */
			void unregisterParameterRemovedCallback(std::size_t id);

			/**
			 * \brief Registers a callback target function that gets invoked when the parent 
			 *        list has been changed or was detached.
			 * \param func A ControlParameterList::ParentChangedCallbackFunction object wrapping the target function.
			 * \return An identifier for the registered callback.
			 */
			std::size_t registerParentChangedCallback(const ParentChangedCallbackFunction& func);

			/**
			 * \brief Unregisters the callback specified by \a id.
			 *
			 * If a registered callback with the identifier \a id does not exist, the method has no effect.
			 *
			 * \param id The identifier of the callback to unregister.
			 */
			void unregisterParentChangedCallback(std::size_t id);

			/**
			 * \brief Assignment operator.
			 *
			 * The assignment is equivalent to first erasing all entries by calling clear() and then calling
			 * setParameter() for each key/value entry in \a cpl.
			 * 
			 * \param cpl The \c %ControlParameterList instance to copy.
			 * \return A reference to itself.
			 * \note Only the entries in \a cpl are copied. Entries in a parent list of \a cpl are
			 *       ignored (see setParent()).
			 */
			ControlParameterList& operator=(const ControlParameterList& cpl);

		private:
			void parameterRemoved(const ValueKey&) const;
			void parameterChanged(const ValueKey&, const Variant&) const;

			void parentParameterRemoved(const ValueKey&) const;
			void parentParameterChanged(const ValueKey&, const Variant&) const;

			void parentChanged() const;

			typedef std::vector<ControlParameterList*> ChildList;
			typedef std::pair<std::size_t, ParameterChangedCallbackFunction> ParamChangedCallbackListEntry;
			typedef std::vector<ParamChangedCallbackListEntry> ParamChangedCallbackList;
			typedef std::pair<std::size_t, ParameterRemovedCallbackFunction> ParamRemovedCallbackListEntry;
			typedef std::vector<ParamRemovedCallbackListEntry> ParamRemovedCallbackList;
			typedef std::pair<std::size_t, ParentChangedCallbackFunction> ParentChangedCallbackListEntry;
			typedef std::vector<ParentChangedCallbackListEntry> ParentChangedCallbackList;

			ParameterMap                parameters;
			const ControlParameterList* parent;
			mutable ChildList           children;
			ParamChangedCallbackList    paramChangedCallbacks;
			ParamRemovedCallbackList    paramRemovedCallbacks;
			ParentChangedCallbackList   parentChangedCallbacks;
		};
	
		/**
		 * @}
		 */
	}
}


// Implementation of template members

template <typename T> 
inline const T& CDPL::Base::ControlParameterList::getParameter(const ValueKey& key, bool local) const
{
	return getParameter(key, true, local).template getData<T>();
}

template <typename T> 
inline const T& CDPL::Base::ControlParameterList::getParameterOrDefault(const ValueKey& key, const T& def, bool local) const
{
	const Variant& val = getParameter(key, false, local);

	return (val.isEmpty() ? def : val.template getData<T>());
}

#endif // CDPL_BASE_CONTROLPARAMETERLIST_HPP
