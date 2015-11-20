/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Controllable.hpp 
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
 * \brief Definition of the class CDPL::Base::Controllable.
 */

#ifndef CDPL_BASE_CONTROLLABLE_HPP
#define CDPL_BASE_CONTROLLABLE_HPP

#include <cstddef>

#include "CDPL/Base/APIPrefix.hpp"
#include "CDPL/Base/ControlParameterList.hpp"


namespace CDPL 
{

	namespace Base
	{
	
		/**
		 * \addtogroup CDPL_BASE_CONTROL_PARAMETERS
		 * @{
		 */
		
		/**
		 * \brief A common base for arbitrary classes that allow a configuration of their runtime behaviour via control-parameters.
		 *
		 * The purpose of \c %Controllable is to provide methods for setting and querying control-parameter values that
		 * control some aspect of a class's runtime behaviour. \c %Controllable is designed to be used as a public base
		 * class and has a protected constructor, copy constructor and destructor.
		 * 
		 * Control-parameter values are stored in a Base::ControlParameterList instance that is accessible via the method
		 * getParameters(). \c %Controllable mimics the Base::ControlParameterList interface by providing equally named
		 * (the only exception is getNumParameters()) methods that forward any calls to the corresponding method of the
		 * contained Base::ControlParameterList instance. Please refer to the Base::ControlParameterList documentation
		 * for further information about the provided methods.
		 */
		class CDPL_BASE_API Controllable
		{

		public:
			/**
			 * \brief A Base::ValueKey / Base::Variant pair used to store the control-parameter
			 *        values and associated keys.
			 * \see Base::ControlParameterList::ParameterEntry
			 */
			typedef ControlParameterList::ParameterEntry ParameterEntry;

			/**
			 * \brief A constant iterator used to iterate over the control-parameter entries.
			 * \see Base::ControlParameterList::ConstParameterIterator
			 */
			typedef ControlParameterList::ConstParameterIterator ConstParameterIterator; 

			/**
			 * \brief A functor class that wraps callback target functions which get invoked when the value of a
			 *        control-parameter has changed.
			 * \see Base::ControlParameterList::ParameterChangedCallbackFunction
			 */
			typedef ControlParameterList::ParameterChangedCallbackFunction ParameterChangedCallbackFunction;

			/**
			 * \brief A functor class that wraps callback target functions which get invoked when a control-parameter entry
			 *        has been removed.
			 * \see Base::ControlParameterList::ParameterRemovedCallbackFunction
			 */
			typedef ControlParameterList::ParameterRemovedCallbackFunction ParameterRemovedCallbackFunction;

			/**
			 * \brief A functor class that wraps callback target functions which get invoked when the 
			 *        parent has been changed or was detached.
			 * \see Base::ControlParameterList::ParentChangedCallbackFunction
			 */
			typedef ControlParameterList::ParentChangedCallbackFunction ParentChangedCallbackFunction;

			/**
			 * \brief Returns the number of control-parameter entries.
			 * \return The number of control-parameter entries.
			 * \see Base::ControlParameterList::getSize()
			 */
			std::size_t getNumParameters() const;

			/**
			 * \brief Replaces all control-parameter entries by a copy of the entries in \a cpl.
			 *
			 * The operation is equivalent to first erasing all entries by calling clearParameters() and then calling
			 * setParameter() for each key/value entry in \a cpl.
			 * 
			 * \param cpl The control-parameter list containing the entries to copy.
			 */
			void setParameters(const ControlParameterList& cpl);

			/**
			 * \brief Sets the value of the control-parameter specified by \a key to \a value.
			 *
			 * If \a value is empty, i.e. the method Base::Variant::isEmpty() returns \c true, and a control-parameter
			 * entry for \a key exists, the entry gets erased (equivalent to removeParameter() with \a key as argument).
			 * Otherwise the control-parameter is assigned the specified value and any callback functions registered by
			 * registerParameterChangedCallback() will be invoked with \a key and \a value provided as arguments.
			 * Callbacks of affected direct and indirect children which do not have an entry for the specified control-parameter also
			 * get invoked.    
			 *
			 * \param key The key of the control-parameter value to assign.
			 * \param value The value of the control-parameter.
			 * \see Base::ControlParameterList::setParameter()
			 */
			void setParameter(const ValueKey& key, const Variant& value);

			/**
			 * \brief Returns the value of the control-parameter specified by \a key.
			 *
			 * If an entry for the specified control-parameter exists, the stored value will be returned.
			 * If an entry for the control-parameter does not exist, the result depends on the arguments \a throw_ and \a local:
			 *
			 * If a parent has been set and the argument \a local is \c false, the request is forwarded to the parent
			 * (which may also forward the request). Otherwise an empty Base::Variant object is returned if \a _throw is \c false,
			 * and a Base::ItemNotFound exception will be thrown if \a _throw is \c true.
			 *
			 * \param key The key of the control-parameter value to return.
			 * \param throw_ Specifies whether or not to throw a Base::ItemNotFound exception if an entry
			 *               for the control-parameter does not exist.
			 * \param local Specifies whether or not the request shall be forwarded to the parent if a local entry 
			 *              for the control-parameter does not exist.
			 * \return The stored control-parameter value or an empty Base::Variant object.
			 * \throw Base::ItemNotFound if an entry for the requested control-parameter value does not exist and \a _throw
			 *        is \c true.
			 * \see Base::ControlParameterList::getParameter(const ValueKey&, bool = false, bool = false)
			 */
			const Variant& getParameter(const ValueKey& key, bool throw_ = false, bool local = false) const;

			/**
			 * \brief Returns the value of the control-parameter specified by \a key as a \c const reference
			 *        to an object of type \a T.
			 *
			 * If an entry for the specified control-parameter exists, the stored value will be returned.
			 * If an entry for the control-parameter does not exist, a parent has been set and the argument \a local
			 * is \c false, the call is forwarded to the parent (which may also forward the request). Otherwise a
			 * Base::ItemNotFound exception will be thrown.
			 *
			 * \param key The key of the control-parameter value to return.
			 * \param local Specifies whether or not the request shall be forwarded to the parent if a local entry 
			 *              for the control-parameter does not exist.
			 * \return The stored control-parameter value as a \c const reference to an object of type \a T.
			 * \throw Base::ItemNotFound if an entry for the requested control-parameter value does not exist, and 
			 *        Base::BadCast if the stored control-parameter value cannot be casted to the target type \a T.
			 * \see Base::ControlParameterList::getParameter(const ValueKey&, bool = false)
			 */
			template <typename T>
			const T& getParameter(const ValueKey& key, bool local = false) const;

			/**
			 * \brief Returns the value of the control-parameter specified by \a key as a \c const reference
			 *        to an object of type \a T, or the default value \a def_value if a stored value does not exist.
			 *
			 * If an entry for the specified control-parameter exists, the stored value will be returned.
			 * If an entry for the control-parameter does not exist, a parent has been set and the argument \a local
			 * is \c false, the call is forwarded to the parent (which may also forward the request). Otherwise the default
			 * value specified by \a def_value is returned.
			 *
			 * \param key The key of the control-parameter for which to return the stored (or specified default) value.
			 * \param def_value The default value that shall be returned if an entry for the specified control-parameter
			 *                  does not exist.
			 * \param local Specifies whether or not the request shall be forwarded to the parent if a local entry 
			 *              for the control-parameter does not exist.
			 * \return The stored control-parameter value or the default specified by \a def_value.
			 * \throw Base::BadCast if the stored control-parameter value cannot be casted to the target type \a T.
			 * \see Base::ControlParameterList::getParameterOrDefault()
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
			 * \see Base::ControlParameterList::removeParameter()
			 */
			bool removeParameter(const ValueKey& key);

			/**
			 * \brief Erases all control-parameter entries.
			 *
			 * For each entry, any callback functions registered by registerParameterRemovedCallback() will be
			 * invoked with the key of the removed control-parameter entry as an argument. Callbacks of affected
			 * direct and indirect children which do not have an entry for the erased control-parameter also get invoked.    
			 *
			 * \see Base::ControlParameterList::clear()
			 */
			void clearParameters();

			/**
			 * \brief Tells whether or not a value has been assigned to the control-parameter specified by \a key.
			 *
			 * If the an entry for the specified control-parameter does not exist, a parent list has been set
			 * and the argument \a local is \c false, the call is forwarded to the parent (which may also forward
			 * the call). Otherwise the result of the local search is returned.
			 *
			 * \param key The key of the control-parameter.
			 * \param local Specifies whether or not the query shall be forwarded to the parent if a local entry 
			 *              for the control-parameter does not exist.
			 * \return \c true if an entry for the specified control-parameter could be found, and \c false otherwise.
			 * \see Base::ControlParameterList::isParameterSet()
			 */
			bool isParameterSet(const ValueKey& key, bool local = false) const;

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the control-parameter entries.
			 * \return A constant iterator pointing to the beginning of the control-parameter entries.
			 * \see Base::ControlParameterList::getParametersBegin()
			 */
			ConstParameterIterator getParametersBegin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the control-parameter entries.
			 * \return A constant iterator pointing to the end of the control-parameter entries.
			 * \see Base::ControlParameterList::getParametersEnd()
			 */
			ConstParameterIterator getParametersEnd() const;

			/**
			 * \brief Sets or removes the parent control-parameter list used to resolve requests for missing entries.
			 *
			 * A control-parameter list that has been set as a parent gets used whenever a request for a control-parameter
			 * value cannot be satisfied locally. That is, if a key/value entry for a given control-parameter
			 * does not exist, the request is simply forwarded to the parent list (which may also forward the request).
			 *
			 * Any callback functions registered by registerParentChangedCallback() will be invoked after the new parent list has
			 * been set (or the old list was detached by providing a \e null pointer). Callbacks of any direct and indirect
			 * children also get invoked.
			 * 
			 * \param cpl A pointer to the parent control-parameter list or \e null. If the pointer is \e null,
			 *            the currently set parent list (if any) gets detached. 
			 * \see Base::ControlParameterList::setParent()
			 */
			void setParent(const ControlParameterList* cpl);

			/**
			 * \brief Uses the control-parameter list provided by the \c %Controllable instance \a c to resolve requests for
			 *        missing entries.
			 * \param controllable The \c %Controllable instance that shall be used to resolve requests for missing entries.
			 * \see setParent(const ControlParameterList*)
			 */
			void setParent(const Controllable& controllable);

			/**
			 * \brief Returns a pointer to the parent control-parameter list.
			 * \return A pointer to the parent control-parameter list, or \e null if no parent list has been set.
			 * \see Base::ControlParameterList::setParent()
			 */
			const ControlParameterList* getParent() const;

			/**
			 * \brief Registers a callback target function that gets invoked when the value of a
			 *        control-parameter has changed. 
			 * \param func A Controllable::ParameterChangedCallbackFunction object wrapping the target function.
			 * \return An identifier for the registered callback.
			 * \see Base::ControlParameterList::registerParameterChangedCallback()
			 */
			std::size_t registerParameterChangedCallback(const ParameterChangedCallbackFunction& func);

			/**
			 * \brief Unregisters the callback specified by \a id.
			 *
			 * If a registered callback with the identifier \a id does not exist, the method has no effect.
			 *
			 * \param id The identifier of the callback to unregister.
			 * \see Base::ControlParameterList::unregisterParameterChangedCallback()
			 */
			void unregisterParameterChangedCallback(std::size_t id);

			/**
			 * \brief Registers a callback target function that gets invoked when a control-parameter entry
			 *        has been removed. 
			 * \param func A Controllable::ParameterRemovedCallbackFunction object wrapping the target function.
			 * \return An identifier for the registered callback.
			 * \see Base::ControlParameterList::registerParameterRemovedCallback()
			 */
			std::size_t registerParameterRemovedCallback(const ParameterRemovedCallbackFunction& func);

			/**
			 * \brief Unregisters the callback specified by \a id.
			 *
			 * If a registered callback with the identifier \a id does not exist, the method has no effect.
			 *
			 * \param id The identifier of the callback to unregister.
			 * \see Base::ControlParameterList::unregisterParameterRemovedCallback()
			 */
			void unregisterParameterRemovedCallback(std::size_t id);

			/**
			 * \brief Registers a callback target function that gets invoked when the parent 
			 *        list has been changed or was detached.
			 * \param func A Controllable::ParentChangedCallbackFunction object wrapping the target function.
			 * \return An identifier for the registered callback.
			 * \see Base::ControlParameterList::registerParentChangedCallback()
			 */
			std::size_t registerParentChangedCallback(const ParentChangedCallbackFunction& func);

			/**
			 * \brief Unregisters the callback specified by \a id.
			 *
			 * If a registered callback with the identifier \a id does not exist, the method has no effect.
			 *
			 * \param id The identifier of the callback to unregister.
			 * \see Base::ControlParameterList::unregisterParentChangedCallback()
			 */
			void unregisterParentChangedCallback(std::size_t id);

			/**
			 * \brief Returns a non-\c const reference to the internal control-parameter list.
			 * \return A non-\c const reference to the internal control-parameter list.
			 */
			ControlParameterList& getParameters();

			/**
			 * \brief Returns a \c const reference to the internal control-parameter list.
			 * \return A \c const reference to the internal control-parameter list.
			 */
			const ControlParameterList& getParameters() const;

		protected:
			/**
			 * \brief Constructs an empty \c %Controllable instance.
			 */
			Controllable() {}

			/**
			 * \brief Constructs a copy of the specified \c %Controllable instance.
			 * \param controllable The \c %Controllable instance to copy.
			 * \note Only the control-parameter entries of \a controllable are copied. Entries in the parent of
			 *       \a controllable (if set) will be ignored (see setParent()).
			 * \see Base::ControlParameterList::ControlParameterList(const ControlParameterList&)
			 */
			Controllable(const Controllable& controllable): controlParams(controllable.controlParams) {}

			/**
			 * \brief Virtual destructor.
			 *
			 * The parent pointer of any children will be set to \e null before the instance gets
			 * destroyed (see setParent()).  
			 *
			 * \see Base::ControlParameterList::~ControlParameterList()
			 */
			virtual ~Controllable() {}
	
			/**
			 * \brief Assignment operator.
			 * \param controllable The \c %Controllable instance to copy.
			 * \return A reference to itself.
			 * \note Only the control-parameter entries of \a controllable are copied. Entries in the parent of
			 *       \a controllable (if set) will be ignored (see setParent()).
			 * \see Base::ControlParameterList::operator=(const ControlParameterList&)
			 */
			Controllable& operator=(const Controllable& controllable);

		private:
			ControlParameterList controlParams;
		};
	
		/**
		 * @}
		 */
	}
}


// Implementation of template members

template <typename T> 
inline const T& CDPL::Base::Controllable::getParameter(const ValueKey& key, bool local) const
{
	return controlParams.template getParameter<T>(key, local);
}

template <typename T> 
inline const T& CDPL::Base::Controllable::getParameterOrDefault(const ValueKey& key, const T& def, bool local) const
{
	return controlParams.template getParameterOrDefault<T>(key, def, local);
}

#endif // CDPL_BASE_CONTROLLABLE_HPP
