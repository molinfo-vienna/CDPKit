/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ValueKey.hpp 
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
 * \brief Definition of the class CDPL::Base::ValueKey.
 */

#ifndef CDPL_BASE_VALUEKEY_HPP
#define CDPL_BASE_VALUEKEY_HPP

#include <cstddef>
#include <string>
#include <functional>

#include "CDPL/Base/APIPrefix.hpp"


namespace CDPL 
{

	namespace Base
	{

		/**
		 * \addtogroup CDPL_BASE_CONTROL_PARAMETERS_AND_PROPERTIES
		 * @{
		 */

		/**
		 * \brief An unique lookup key for control-parameter and property values.
		 *
		 * \c %ValueKey has a private default constructor and a public copy constructor. The creation of
		 * not copy constructed new instances is only possible by the method create(const std::string& name).
		 * \c %ValueKey instances created by this method are guaranteed to be unique (given that the internal instance counter of type
		 * \c std::size_t does not overflow), i.e. the created instance is <em>not a copy</em> of an existing key and does not compare equal
		 * to any instance created before or afterwards.		 
		 */
		class ValueKey 
		{

		public:
			/**
			 * \brief A functor class implementing the generation of hash codes for \c %ValueKey instances.
			 */
			struct HashFunc : public std::unary_function<const ValueKey&, std::size_t>
			{

				/**
				 * \brief Returns the hash code of the \c %ValueKey instance \a key.
				 * \param key The \c %ValueKey instance.
				 * \return The hash code of \a key.
				 */
				std::size_t operator()(const ValueKey& key) const;
			};

			/**
			 * \brief Used to denote an invalid, unused or unspecified key.
			 */
			CDPL_BASE_API static const ValueKey NONE;

			/**
			 * \brief Creates a new unique \c %ValueKey instance and registers it under the specified name.
			 *
			 * ValueKey instances created by this method are guaranteed to be unique (given that the internal
			 * instance counter of type \c std::size_t does not overflow), i.e. the instance is <em>not a copy</em> of an
			 * existing key and does not compare equal to any instance created before or afterwards.
			 *
			 * \param name The name of the \c %ValueKey instance.
			 * \return A new unique \c %ValueKey instance.
			 */
			static ValueKey create(const std::string& name);

			/**
			 * \brief Sets the name of the \c %ValueKey instance.
			 * \param name The new name of the \c %ValueKey instance.
			 */
			void setName(const std::string& name) const;

			/**
			 * \brief Returns the name of the \c %ValueKey instance.
			 * \return The name of the \c %ValueKey instance.
			 * \throw Base::ItemNotFound if the requested name could not be found.
			 */
			const std::string& getName() const;

			/**
			 * \brief Returns the unique numeric identifier associated with the \c %ValueKey instance.
			 * \return The unique numeric identifier of the \c %ValueKey instance.
			 */
			std::size_t getID() const;

			/**
			 * \brief Less than comparison operator.
			 * \param key The other \c %ValueKey instance to be compared with.
			 * \return \c true if the numeric identifier of this instance is smaller than the identifier of \a key,
			 *         and \c false otherwise.
			 */ 
			bool operator<(const ValueKey& key) const;

			/**
			 * \brief Equality comparison operator.
			 * \param key The other \c %ValueKey instance to be compared with.
			 * \return \c true if the numeric identifiers of the keys are equal, and \c false otherwise.
			 */
			bool operator==(const ValueKey& key) const;

			/**
			 * \brief Inequality comparison operator.
			 * \param key The other \c %ValueKey instance to be compared with.
			 * \return \c true if the numeric identifiers of the keys are not equal, and \c false otherwise.
			 */
			bool operator!=(const ValueKey& key) const;

		private:
			ValueKey(std::size_t id): numericID(id) {}

			std::size_t numericID;
		};
	
		/**
		 * @}
		 */
	}
}


// Implementation

inline std::size_t CDPL::Base::ValueKey::getID() const
{
	return numericID;
}

inline bool CDPL::Base::ValueKey::operator<(const ValueKey& key) const
{
	return (numericID < key.numericID);
}

inline bool CDPL::Base::ValueKey::operator==(const ValueKey& key) const
{
	return (numericID == key.numericID);
}

inline bool CDPL::Base::ValueKey::operator!=(const ValueKey& key) const
{
	return (numericID != key.numericID);
}

inline std::size_t CDPL::Base::ValueKey::HashFunc::operator()(const ValueKey& key) const 
{
	return key.numericID;
}

#endif // CDPL_BASE_VALUEKEY_HPP
