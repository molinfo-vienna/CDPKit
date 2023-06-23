/* 
 * LookupKey.hpp 
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
 * \brief Definition of the class CDPL::Base::LookupKey.
 */

#ifndef CDPL_BASE_VALUEKEY_HPP
#define CDPL_BASE_VALUEKEY_HPP

#include <cstddef>
#include <string>

#include "CDPL/Base/APIPrefix.hpp"


namespace CDPL 
{

    namespace Base
    {

        /**
         * \brief An unique lookup key for control-parameter and property values.
         *
         * \c %LookupKey has a private default constructor and a public copy constructor. The creation of
         * not copy constructed new instances is only possible by the method create(const std::string& name).
         * \c %LookupKey instances created by this method are guaranteed to be unique (given that the internal instance counter of type
         * \c std::size_t does not overflow), i.e. the created instance is <em>not a copy</em> of an existing key and does not compare equal
         * to any instance created before or afterwards.         
         */
        class CDPL_BASE_API LookupKey 
        {

        public:
            /**
             * \brief A functor class implementing the generation of hash codes for \c %LookupKey instances.
             */
            struct HashFunc
            {

                /**
                 * \brief Returns the hash code of the \c %LookupKey instance \a key.
                 * \param key The \c %LookupKey instance.
                 * \return The hash code of \a key.
                 */
                std::size_t operator()(const LookupKey& key) const;
            };

            /**
             * \brief Used to denote an invalid, unused or unspecified key.
             */
            CDPL_BASE_API static const LookupKey NONE;

            /**
             * \brief Creates a new unique \c %LookupKey instance and registers it under the specified name.
             *
             * \c %LookupKey instances created by this method are guaranteed to be unique (given that the internal
             * instance counter of type \c std::size_t does not overflow), i.e. the instance is <em>not a copy</em> of an
             * existing key and does not compare equal to any instance created before or afterwards.
             *
             * \param name The name of the \c %LookupKey instance.
             * \return A new unique \c %LookupKey instance.
             */
            static LookupKey create(const std::string& name);

            /**
             * \brief Sets the name of the \c %LookupKey instance.
             * \param name The new name of the \c %LookupKey instance.
             */
            void setName(const std::string& name) const;

            /**
             * \brief Returns the name of the \c %LookupKey instance.
             * \return The name of the \c %LookupKey instance.
             * \throw Base::ItemNotFound if the requested name could not be found.
             */
            const std::string& getName() const;

            /**
             * \brief Returns the unique numeric identifier associated with the \c %LookupKey instance.
             * \return The unique numeric identifier of the \c %LookupKey instance.
             */
            std::size_t getID() const;

            /**
             * \brief Less than comparison operator.
             * \param key The other \c %LookupKey instance to be compared with.
             * \return \c true if the numeric identifier of this instance is smaller than the identifier of \a key,
             *         and \c false otherwise.
             */ 
            bool operator<(const LookupKey& key) const;

            /**
             * \brief Equality comparison operator.
             * \param key The other \c %LookupKey instance to be compared with.
             * \return \c true if the numeric identifiers of the keys are equal, and \c false otherwise.
             */
            bool operator==(const LookupKey& key) const;

            /**
             * \brief Inequality comparison operator.
             * \param key The other \c %LookupKey instance to be compared with.
             * \return \c true if the numeric identifiers of the keys are not equal, and \c false otherwise.
             */
            bool operator!=(const LookupKey& key) const;

        private:
            LookupKey(std::size_t id): numericID(id) {}

            std::size_t numericID;
        };
    }
}


// Implementation

inline std::size_t CDPL::Base::LookupKey::getID() const
{
    return numericID;
}

inline bool CDPL::Base::LookupKey::operator<(const LookupKey& key) const
{
    return (numericID < key.numericID);
}

inline bool CDPL::Base::LookupKey::operator==(const LookupKey& key) const
{
    return (numericID == key.numericID);
}

inline bool CDPL::Base::LookupKey::operator!=(const LookupKey& key) const
{
    return (numericID != key.numericID);
}


inline std::size_t CDPL::Base::LookupKey::HashFunc::operator()(const LookupKey& key) const 
{
    return key.numericID;
}

#endif // CDPL_BASE_VALUEKEY_HPP
