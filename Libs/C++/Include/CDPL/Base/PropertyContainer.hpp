/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PropertyContainer.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Base::PropertyContainer.
 */

#ifndef CDPL_BASE_PROPERTYCONTAINER_HPP
#define CDPL_BASE_PROPERTYCONTAINER_HPP

#include <utility>
#include <unordered_map>

#include "CDPL/Base/APIPrefix.hpp"
#include "CDPL/Base/LookupKey.hpp"
#include "CDPL/Base/Any.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace CDPL 
{
	
	namespace Base
	{

		/**
		 * \brief A class providing methods for the storage and lookup of object properties.
		 *
		 * The purpose of \c %PropertyContainer is to provide a common facility for the storage and lookup of
		 * dynamic object properties to subclasses and their clients.
		 *
		 * \c %PropertyContainer stores the properties in a map that associates unique property keys of type
		 * Base::LookupKey with corresponding property values of type Base::Any. Iterators pointing to
		 * the beginning and end of the property key/value pairs (see PropertyContainer::PropertyEntry) can be
		 * retrieved by the methods getPropertiesBegin() and getPropertiesEnd(), respectively. The
		 * number of currently stored property value entries is accessible via the method getNumProperties(). 
		 *
		 * For the explicit assignment of property values the method setProperty() is provided which
		 * expects the key of the property as its first and the value to assign as the second argument.
		 * Whether the value of a particular property has been set can be tested by the method
		 * isPropertySet(). 
		 * For the erasure of property values the methods removeProperty() and clearProperties() are provided.
		 * The first method clears the value of a single property while the latter method removes all assigned
		 * property values.
		 *
		 * To access the value of a property, two types of getProperty() methods are available that both 
		 * expect the key of the property as the first argument. The templated versions return the stored property
		 * value (or the specified default if not available) as a reference to an object of the specified template
		 * argument type. The non-template method returns the requested property value indirectly as a reference to the
		 * Base::Any instance storing the actual value. If the requested property value does not exist, an additional
		 * argument decides whether to throw an exception or to return an empty Base::Any instance.
		 */
		class CDPL_BASE_API PropertyContainer
		{

			typedef std::unordered_map<LookupKey, Any, LookupKey::HashFunc> PropertyMap;

		public:
			/**	
			 * \brief A Base::LookupKey / Base::Any pair that stores the property value for a given property key.
			 */
			typedef PropertyMap::value_type PropertyEntry;

			/**
			 * \brief A constant iterator used to iterate over the property entries.
			 */
			typedef PropertyMap::const_iterator ConstPropertyIterator;
	
			/**
			 * \brief Returns the number of property entries.
			 * \return The number of property entries.
			 */
			std::size_t getNumProperties() const;
		
			/**
			 * \brief Sets the value of the property specified by \a key to \a val.
			 *
			 * If \a val is of type Base::Any and empty, i.e. the method Base::Any::isEmpty() returns \c true, and a property
			 * entry for \a key exists, the entry gets erased (equivalent to removeProperty() with \a key as argument).
			 *
			 * \param key The key of the property value to assign or remove.
			 * \param val The value of the property.
			 */
			 template <typename T>
			 void setProperty(const LookupKey& key, T&& val);

			/**
			 * \brief Returns the value of the property specified by \a key as a \c const reference to an object of type \a T.
			 *
			 * If an entry for the specified property exists, the stored value will be returned. Otherwise a Base::ItemNotFound exception
			 * will be thrown.
			 *
			 * \param key The key of the property value to return.
			 * \return The stored value of the property as a \c const reference to an object of type \a T.
			 * \throw Base::ItemNotFound if an entry for the requested property value does not exist, and  
			 *        Base::BadCast if the stored property value cannot be casted to the target type \a T.
			 */
			template <typename T>
			const T& getProperty(const LookupKey& key) const;
	
			/**
			 * \brief Returns the value of the property specified by \a key as a \c const reference
			 *        to an object of type \a T, or the default value \a def_val if a stored value does not exist.
			 *
			 * If a value has been assigned to the specified property, the stored value will be returned.
			 * Otherwise the default value specified by \a def_val gets returned.
			 *
			 * \param key The key of the property for which to return the stored (or specified default) value.
			 * \param def_val The default value that shall be returned if an entry for the specified property
			 *                  does not exist.
			 * \return The stored property value or the default specified by \a def_val.
			 * \throw Base::BadCast if the stored property value cannot be casted to the target type \a T.
			 */
			template <typename T>
			const T& getPropertyOrDefault(const LookupKey& key, const T& def_val) const;

			/**
			 * \brief Returns the value of the property specified by \a key.
			 *
			 * If an entry for the specified property exists, the stored value will be returned. Otherwise an empty Base::Any
			 * object gets returned if \a _throw is \c false, and a Base::ItemNotFound exception will be thrown if \a _throw is \c true.
			 *
			 * \param key The key of the property value to return.
			 * \param throw_ Specifies whether to throw a Base::ItemNotFound exception or to return an empty Base::Any object
			 *               if the requested property value does not exist.
			 * \return The stored property value or and empty Base::Any object.
			 * \throw Base::ItemNotFound if an entry for the requested property value does not exist and \a throw_ is \c true.
			 */
			inline const Any& getProperty(const LookupKey& key, bool throw_ = false) const;

			/**
			 * \brief Tells whether or not a value has been assigned to the property specified by \a key.
			 * \param key The key of the property.
			 * \return \c true if a value has been assigned to the specified property, and \c false otherwise.
			 */
			inline bool isPropertySet(const LookupKey& key) const;

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the property entries.
			 * \return A constant iterator pointing to the beginning of the property entries.
			 */
			ConstPropertyIterator getPropertiesBegin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the property entries.
			 * \return A constant iterator pointing to the end of the property entries.
			 */
			ConstPropertyIterator getPropertiesEnd() const;

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the property entries.
			 * \return A constant iterator pointing to the beginning of the property entries.
			 */
			ConstPropertyIterator begin() const;

			/**
			 * \brief Returns a constant iterator pointing to the end of the property entries.
			 * \return A constant iterator pointing to the end of the property entries.
			 */
			ConstPropertyIterator end() const;

			/**
			 * \brief Clears the value of the property specified by \a key.
			 * \param key The key of the property value to erase.
			 * \return \c true if an entry for \a key could be found and was erased, and \c false otherwise.
			 */
			bool removeProperty(const LookupKey& key);

			/**
			 * \brief Clears all property values.
			 */
			void clearProperties();

			/**
			 * \brief Adds the property value entries in the \c %PropertyContainer instance \a cntnr.
			 *
			 * Any property values which have no corresponding assigned value in \a cntnr are left unchanged. Otherwise the value
			 * of the local property gets overwritten by the value stored in \a cntnr. 
			 *
			 * \param cntnr The \c %PropertyContainer instance containing the property value entries to add.
			 */
			void addProperties(const PropertyContainer& cntnr);

			/**
			 * \brief Replaces the current set of properties by a copy of the entries in \a cntnr.
			 * \param cntnr The \c %PropertyContainer instance containing the property value entries to add.
			 */
			void copyProperties(const PropertyContainer& cntnr);

			/**
			 * \brief Exchanges the properties of this container with the properties of the container \a cntnr.
			 * \param cntnr The container to exchange the properties with.
			 */
			void swap(PropertyContainer& cntnr);

		protected:
			/**
			 * \brief Constructs an empty \c %PropertyContainer instance.
			 */
			PropertyContainer() {}

			/**
			 * \brief Constructs a copy of the \c %PropertyContainer instance \a cntnr.
			 * \param cntnr The \c %PropertyContainer instance to copy.
			 */
			PropertyContainer(const PropertyContainer& cntnr);

			/**
			 * \brief Virtual destructor.
			 */
			virtual ~PropertyContainer();

			/**
			 * \brief Assignment operator.
			 *
			 * Internally calls copyProperties() to perform the actual work.
			 *
			 * \param cntnr The \c %PropertyContainer instance to copy.
			 * \return A reference to itself.
			 */
			PropertyContainer& operator=(const PropertyContainer& cntnr);
		  
		private:
			inline bool isEmptyAny(const Any& val) const;

			template <typename T>
			bool isEmptyAny(const T& val) const;

			PropertyMap properties;
		};
	}
}


// Implementation of template members

template <typename T> 
const T& CDPL::Base::PropertyContainer::getProperty(const LookupKey& key) const
{
	return getProperty(key, true).template getData<T>();
}

template <typename T> 
const T& CDPL::Base::PropertyContainer::getPropertyOrDefault(const LookupKey& key, const T& def_val) const
{
	const Any& val = getProperty(key, false);

	return (val.isEmpty() ? def_val : val.template getData<T>());
}

const CDPL::Base::Any& CDPL::Base::PropertyContainer::getProperty(const LookupKey& key, bool throw_ex) const
{
	static const Any NOT_FOUND;
	
	ConstPropertyIterator it = properties.find(key);
	
	if (it != properties.end())
		return it->second;

	if (throw_ex)
		throw ItemNotFound("PropertyContainer: property " + key.getName() + " not found");
	
	return NOT_FOUND;
}

template <typename T>
void CDPL::Base::PropertyContainer::setProperty(const LookupKey& key, T&& val)
{
	if (isEmptyAny(val)) {
		properties.erase(key);
		return;
	}
	
	properties[key] = std::forward<T>(val);
}

bool CDPL::Base::PropertyContainer::isPropertySet(const LookupKey& key) const
{
	return (properties.find(key) != properties.end());
}

bool CDPL::Base::PropertyContainer::isEmptyAny(const Any& val) const
{
	return val.isEmpty();
}

template <typename T>
bool CDPL::Base::PropertyContainer::isEmptyAny(const T&) const
{
	return false;
}

#endif // CDPL_BASE_PROPERTYCONTAINER_HPP
