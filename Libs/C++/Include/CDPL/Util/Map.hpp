/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Map.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
 * \brief Definition of the class CDPL::Util::Map.
 */

#ifndef CDPL_UTIL_MAP_HPP
#define CDPL_UTIL_MAP_HPP

#include <map>
#include <functional>
#include <utility>
#include <string>
#include <cstddef>

#include <boost/shared_ptr.hpp>

#include "CDPL/Base/Exceptions.hpp"


namespace CDPL
{

	namespace Util
	{

		/**
		 * \addtogroup CDPL_UTIL_CONTAINERS
		 * @{
		 */

		template <typename ValueType, bool Allow = true> 
		struct MapDefaultValue
		{

			static const ValueType& get() {
				return defValue;
			} 

			static const ValueType defValue;
		};

		template <typename ValueType, bool Allow> 
		const ValueType MapDefaultValue<ValueType, Allow>::defValue = ValueType();

		template <typename ValueType> 
		struct MapDefaultValue<ValueType, false>
		{

			static const ValueType& get() {
				throw Base::OperationFailed("Map: default value not supported");
			} 
		};

		/**
		 * \brief A unique sorted associative container that maps keys to values.
		 *
		 * Since \c %Map is a sorted associative container, it uses an ordering relation on its keys.
		 * Two keys are considered to be equivalent if neither one is less than the other. \c %Map
		 * guarantees that the complexity for most operations is never worse than logarithmic, and
		 * the entries are always sorted in ascending order by key. It is also an unique associative
		 * container, meaning that no two entries have the same key. \c %Map has the important property
		 * that inserting a new entry does not invalidate iterators that point to existing
		 * entries. Erasing an entry also does not invalidate any iterators, except, of course,
		 * for iterators that actually point to the entry that is being erased.
		 *
		 * \tparam Key The type of the map's keys.
		 * \tparam Value The type of the mapped values.
		 * \tparam AllowDefValues Whether to return a default value or to throw an exception if a key/value
		 *                        entry is not present in the map.
		 * \param KeyCompFunc The type of a functor class used to establish the strictly weak ordering on the map's keys.
		 *                    The functor has to return \c true if the first argument is less than the second one,
		 *                    and \c false otherwise. 
		 */
		template <typename Key, typename Value, bool AllowDefValues = false, 
				  typename KeyCompFunc = std::less<Key> >
		class Map
		{

			typedef std::map<Key, Value, KeyCompFunc> StorageType;

		public:
			/**
			 * \brief A reference-counted smart pointer [\ref BSHPTR] for dynamically allocated \c %Map instances.
			 */
			typedef boost::shared_ptr<Map> SharedPointer;
 
			/**
			 * \brief The type of the map's keys.
			 */
			typedef Key KeyType;

			/**
			 * \brief The type of the mapped values.
			 */
			typedef Value ValueType;

			/**
			 * \brief The type of the key/value pairs stored in the map.
			 *
			 * The member \c Entry::first is the \c const key object of type \a Key and the
			 * member \c Entry::second is the associated value object of type \a Value.
			 */
			typedef typename StorageType::value_type Entry;

			/**
			 * \brief A constant iterator used to iterate over the entries of the map.
			 */
			typedef typename StorageType::const_iterator ConstEntryIterator;

			/**
			 * \brief A constant iterator used to iterate backwards over the entries of the map.
			 */
			typedef typename StorageType::const_reverse_iterator ConstReverseEntryIterator;

			/**
			 * \brief A mutable iterator used to iterate over the entries of the map.
			 */
			typedef typename StorageType::iterator EntryIterator;
		
			/**
			 * \brief A mutable iterator used to iterate backwards over the entries of the map.
			 */
			typedef typename StorageType::reverse_iterator ReverseEntryIterator;

			/**
			 * \brief Creates an empty map.
			 */
			Map(): data() {}

			/**
			 * \brief Creates an empty map and uses \a func as key compare function.
			 * \param func The key compare function to use.
			 */
			Map(const KeyCompFunc& func): data(func) {}
			
			/**
			 * \brief Creates and initializes the map with copies of the key value pairs in the range <em>[first, last)</em>. 
			 * \param first The start of the range.
			 * \param last The end of the range.
			 */
			template <typename InputIter>
			Map(const InputIter& first, const InputIter& last): data(first, last) {}

			/**
			 * \brief Creates and initializes the map with copies of the key value pairs in the range <em>[first, last)</em> 
			 *        and uses \a func as key compare function. 
			 * \param first The start of the range.
			 * \param last The end of the range.
			 * \param func The key compare function to use.
			 */
			template <typename InputIter>
			Map(const InputIter& first, const InputIter& last, const KeyCompFunc& func): data(first, last, func) {}
			
			/**
			 * \brief Virtual destructor.
			 */
			virtual ~Map() {}

			/**
			 * \brief Returns the size (number of entries) of the map.
			 * \return The size of the map.
			 */
			std::size_t getSize() const;

			/**
			 * \brief Tells whether the map is empty (<tt>getSize() == 0</tt>).
			 * \return \c true if the map is empty, and \c false otherwise.
			 */
			bool isEmpty() const;
			
			/**
			 * \brief Erases all entries.
			 */
			void clear();

			/**
			 * \brief Swaps the contents with \a map.
			 * \param map The other map with which the contents will be exchanged.
			 */
			void swap(Map& map);

			/**
			 * \brief Returns the key compare function used by the map.
			 * \return The key compare function.
			 */
			KeyCompFunc getKeyCompareFunction() const;

			/**
			 * \brief Returns a mutable iterator pointing to the entry specified by \a key.
			 *
			 * If the map does not contain an entry with the specified key, an iterator pointing
			 * one past the last entry of the map (<tt>== getEntriesEnd()</tt>) is returned.
			 *
			 * \param key The key specifying the entry.
			 * \return A mutable iterator pointing the entry specified by the key or
			 *         getEntriesEnd(), if the map contains no such entry.
			 */
			EntryIterator getEntry(const Key& key);

			/**
			 * \brief Returns a constant iterator pointing to the entry specified by \a key.
			 *
			 * If the map does not contain an entry with the specified key, an iterator pointing
			 * one past the last entry of the map (<tt>== getEntriesEnd()</tt>) is returned.
			 *
			 * \param key The key specifying the entry.
			 * \return A constant iterator pointing the entry specified by the key or
			 *         getEntriesEnd(), if the map contains no such entry.
			 */
			ConstEntryIterator getEntry(const Key& key) const;

			/**
			 * \brief Tells whether the map contains an entry with the specified key.
			 * \param key The key specifying the entry.
			 * \return \c true if the map contains the specified entry, and \c false otherwise.
			 */
			bool containsEntry(const Key& key) const;

			/**
			 * \brief Returns a non-\c const reference to the value associated with the specified key.
			 *
			 * If the map contains an entry with the specified key, a reference to the associated value is
			 * returned. If the map does not contain the entry and default values are enabled 
			 * (that is, the template parameter \a AllowDefValues is \c true), a new map entry
			 * is created which associates \a key with the default constructed value object.
			 * Otherwise, Base::ItemNotFound is thrown to indicate the error.
			 *
			 * \param key The key associated with the requested value.
			 * \return A non-\c const reference to the requested value.
			 * \throw Base::ItemNotFound if \a AllowDefValues is \c false and the map does not
			 *        contain an entry with the specified key.
			 */
			Value& getValue(const Key& key);

			/**
			 * \brief Returns a non-\c const reference to the value associated with the specified key,
			 *        or the value given by the second argument if the specified entry does
			 *        not exist.
			 *
			 * If the map contains an entry with the specified key, a reference to the associated value is
			 * returned. If the map does not contain the entry, the second argument \a def_value
			 * is returned.
			 *
			 * \param key The key associated with the requested value.
			 * \param def_value The value which is returned if the specified entry does
			 *                  not exist.
			 * \return A non-\c const reference to the requested or default value.
			 */
			Value& getValue(const Key& key, Value& def_value);

			/**
			 * \brief Returns a \c const reference to the value associated with the specified key.
			 *
			 * If the map contains the specified entry, a reference to the associated value is
			 * returned. If the map does not contain the entry and default values are enabled 
			 * (that is, the template parameter \a AllowDefValues is \c true), a \c const
			 * reference to a default constructed value object is returned. Otherwise, 
			 * Base::ItemNotFound is thrown to indicate the error.
			 *
			 * \param key The key associated with the requested value.
			 * \return A \c const reference to the requested value.
			 * \throw Base::ItemNotFound if \a AllowDefValues is \c false and the map does not
			 *        contain an entry with the specified key.
			 */
			const Value& getValue(const Key& key) const;
			
			/**
			 * \brief Returns a \c const reference to the value associated with the specified key,
			 *        or the value given by the second argument if the specified entry does
			 *        not exist.
			 *
			 * If the map contains an entry with the specified key, a reference to the associated value is
			 * returned. If the map does not contain the entry, the second argument \a def_value
			 * is returned.
			 *
			 * \param key The key associated with the requested value.
			 * \param def_value The value which is returned if the specified entry does
			 *                  not exist.
			 * \return A \c const reference to the requested or default value.
			 */	
			const Value& getValue(const Key& key, const Value& def_value) const;

			/**
			 * \brief Returns a non-\c const reference to the value associated with the specified key.
			 *
			 * The method is equivalent to getValue(const Key&).
			 *
			 * \param key The key associated with the requested value.
			 * \return A non-\c const reference to the requested value.
			 * \throw Base::ItemNotFound if \a AllowDefValues is \c false and the map does not
			 *        contain an entry with the specified key.
			 * \see getValue(const Key&)
			 */
			Value& operator[](const Key& key);

			/**
			 * \brief Returns a \c const reference to the value associated with the specified key.
			 *
			 * The method is equivalent to getValue(const Key&) const.
			 *
			 * \param key The key associated with the requested value.
			 * \return A \c const reference to the requested value.
			 * \throw Base::ItemNotFound if \a AllowDefValues is \c false and the map does not
			 *        contain an entry with the specified key.
			 * \see getValue(const Key&) const
			 */
			const Value& operator[](const Key& key) const;

			/**
			 * \brief Removes the entry pointed to by the iterator \a it from the map.
			 * \param it The iterator pointing to the entry to remove.
			 */
			void removeEntry(const EntryIterator& it);

			/**
			 * \brief Removes the entry specified by \a key from the map.
			 * \param key The key specifying the entry to remove.
			 */
			bool removeEntry(const Key& key);

			/**
			 * \brief Removes all entries pointed to by the iterators in the range <em>[first, last)</em> from the map.
			 * \param first The start of the range.
			 * \param last The end of the range.
			 */
			void removeEntries(const EntryIterator& first, const EntryIterator& last);

			/**
			 * \brief Tries to insert the key/value pair \a item into the map.
			 *
			 * Inserts \a item if and only if the map does not already contain an entry whose key is
			 * the same as the key of \a item. The return value is a pair \c P. \c P.first is an iterator
			 * pointing to the entry whose key is the same as the key of \a item. \c P.second is a boolean
			 * value which is \c true if \a item was actually inserted, and \c false if the
			 * map already contained an entry with the same key as \a item.
			 *
			 * \param item The key/value pair to insert.
			 * \return A std::pair consisting of an iterator pointing to an entry whose key is the
			 *         same as the key of \a item and a boolean value which is \c true if the insertion
			 *         of \a item was successful (an entry with the specified key did not already exist), and
			 *         \c false otherwise.
			 */
			std::pair<EntryIterator, bool> insertEntry(const Entry& item);

			/**
			 * \brief Tries to insert a new entry with specified key and value into the map.
			 *
			 * Inserts a new entry if and only if the map does not already contain an entry whose key is
			 * the same as the specified key. The return value is a pair \c P. \c P.first is an iterator
			 * pointing to the entry whose key is the same as the specified key. \c P.second is a boolean
			 * value which is \c true if \a item was actually inserted, and \c false
			 * if the map already contained an entry with the specified key.
			 *
			 * \param key The key of the entry to insert.
			 * \param value The value associated with \a key.
			 * \return A std::pair consisting of an iterator pointing to an entry whose key is the
			 *         same as \a key and a boolean value, which is \c true if the insertion
			 *         of \a item was successful (an entry with the specified key did not already exist), and
			 *         \c false otherwise.
			 */
			std::pair<EntryIterator, bool> insertEntry(const Key& key, const Value& value);

			/**
			 * \brief Tries to insert the key/value pair \a item into the map and uses the iterator \a it as
			 *        a hint for the insertion location.
			 *
			 * Inserts \a item if and only if the map does not already contain an entry whose key is
			 * the same as the key of \a item. The argument \a it is a hint and points to the location
			 * where the insertion position search will begin. The return value is a dereferenceable
			 * iterator that points to the entry with a key that is equivalent to that of \a item. 
			 *
			 * \param it An iterator pointing to a location where the insertion position search will begin.
			 * \param item The key/value pair to insert.
			 * \return An iterator that points to the entry with a key that is equivalent to that of \a item.
			 */
			EntryIterator insertEntry(const EntryIterator& it, const Entry& item);

			/**
			 * \brief Tries to insert a new entry with the specified key and value into the map
			 *        and uses the iterator \a it as a hint for the insertion location.
			 *
			 * Inserts a new entry if and only if the map does not already contain an entry whose key is
			 * the same as the specified key. The argument \a it is a hint and points to the location where the insertion
			 * position search will begin. The return value is a dereferenceable iterator that points to
			 * the entry with a key that is equivalent to the specified key. 
			 *
			 * \param it An iterator pointing to a location where the insertion position search will begin.
			 * \param key The key of the entry to insert.
			 * \param value The value associated with \a key
			 * \return An iterator that points to the entry with a key that is equivalent to the specified key.
			 */
			EntryIterator insertEntry(const EntryIterator& it, const Key& key, const Value& value);

			/**
			 * \brief Inserts a new entry or updates the value of an existing entry with the key and value
			 *        given by \a item.
			 *
			 * If the map does not already contain an entry whose key is the same as the key of \a item
			 * then a new entry will be created. Otherwise, the value of the existing entry is updated 
			 * with the value of \a item. The return value is a dereferenceable iterator that points to
			 * the newly inserted or updated entry whose key is equivalent to that of \a item. 
			 *
			 * \param item The key/value pair.
			 * \return An iterator that points to the newly inserted or updated entry.
			 */
			EntryIterator setEntry(const Entry& item);

			/**
			 * \brief Inserts a new entry or updates the value of an existing entry with the specified key and
			 *        value.
			 *
			 * If the map does not already contain an entry whose key is the same as \a key
			 * then a new entry will be created. Otherwise, the value of the existing entry is updated 
			 * with \a value. The return value is a dereferenceable iterator that points to
			 * the newly inserted or updated entry whose key is equivalent to the specified key. 
			 *
			 * \param key The key of the entry to insert or update.
			 * \param value The value to be associated with \a key.
			 * \return An iterator that points to the newly inserted or updated entry.
			 */
			EntryIterator setEntry(const Key& key, const Value& value);

			/**
			 * \brief Tries to insert the key/value pairs in the range <em>[first, last)</em>.
			 *
			 * This is equivalent to calling insertEntry(const Entry&) for each key/value pair \a i that
			 * is pointed to by an iterator in the range <em>[first, last)</em>. A key/value pair is inserted
			 * if and only if the map does not already contain an entry with an equivalent key.
			 *
			 * \param first The start of the range.
			 * \param last The end of the range.
			 */
			template <typename InputIter>
			void insertEntries(const InputIter& first, const InputIter& last);

			/**
			 * \brief Inserts new entries or updates the value of existing entries using the key/value pairs 
			 *        in the range <em>[first, last)</em>.
			 *
			 * This is equivalent to calling setEntry(const Entry&) for each key/value pair \a i that is pointed to
			 * by an iterator in the range <em>[first, last)</em>.
			 *
			 * \param first The start of the range.
			 * \param last The end of the range.
			 */
			template <typename InputIter>
			void setEntries(const InputIter& first, const InputIter& last);

			/**
			 * \brief Returns a mutable iterator pointing to the first entry whose key is not less than the specified key.
			 * \return A mutable iterator pointing to the first entry whose key is not less than the specified key.
			 */
			EntryIterator getLowerBound(const Key& key);

			/**
			 * \brief Returns a constant iterator pointing to the first entry whose key is not less than the specified key.
			 * \return A constant iterator pointing to the first entry whose key is not less than the specified key.
			 */
			ConstEntryIterator getLowerBound(const Key& key) const;

			/**
			 * \brief Returns a mutable iterator pointing to the first entry whose key is greater than the specified key.
			 * \return A mutable iterator pointing to the first entry whose key is greater than the specified key.
			 */
			EntryIterator getUpperBound(const Key& key);

			/**
			 * \brief Returns a constant iterator pointing to the first entry whose key is greater than the specified key.
			 * \return A constant iterator pointing to the first entry whose key is greater than the specified key.
			 */
			ConstEntryIterator getUpperBound(const Key& key) const;

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the map.
			 * \return A constant iterator pointing to the beginning of the map.
			 */
			ConstEntryIterator getEntriesBegin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the map.
			 * \return A mutable iterator pointing to the beginning of the map.
			 */
			EntryIterator getEntriesBegin();

			/**
			 * \brief Returns a constant iterator pointing to the end of the map.
			 * \return A constant iterator pointing to the end of the map.
			 */
			ConstEntryIterator getEntriesEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the map.
			 * \return A mutable iterator pointing to the end of the map.
			 */
			EntryIterator getEntriesEnd();

			/**
			 * \brief Returns a constant iterator pointing to the beginning of the reversed map.
			 * \return A constant iterator pointing to the beginning of the reversed map.
			 */
			ConstReverseEntryIterator getEntriesReverseBegin() const;

			/**
			 * \brief Returns a mutable iterator pointing to the beginning of the reversed map.
			 * \return A mutable iterator pointing to the beginning of the reversed map.
			 */
			ReverseEntryIterator getEntriesReverseBegin();

			/**
			 * \brief Returns a constant iterator pointing to the end of the reversed map.
			 * \return A constant iterator pointing to the end of the reversed map.
			 */
			ConstReverseEntryIterator getEntriesReverseEnd() const;

			/**
			 * \brief Returns a mutable iterator pointing to the end of the reversed map.
			 * \return A mutable iterator pointing to the end of the reversed map.
			 */
			ReverseEntryIterator getEntriesReverseEnd();

			/**
			 * \brief Equality comparison operator.
			 *
			 * This is an equivalence relation. It is linear in the size of the
			 * map. Two maps are considered equivalent if their sizes are equal,
			 * and if the corresponding entries compare equal.
			 *
			 * \param map The other map to be compared with.
			 * \return \c true if the sizes and entries of the arrays are 
			 *         equal, and \c false otherwise.
			 * \note \a KeyType and \a ValueType must be equality comparable.
			 */
			bool operator==(const Map& map) const;

			/**
			 * \brief Inequality comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this == map)</tt>.
			 *
			 * \param map The map to be compared with.
			 * \return \c true if the sizes or entries of the maps are 
			 *         non-equal, and \c false otherwise.
			 * \see operator==()
			 */			
			bool operator!=(const Map& map) const;

			/**
			 * \brief Less or equal comparison operator.
			 *
			 * The result is equivalent to <tt>!(map < *this)</tt>.
			 *
			 * \param map The other map to be compared with.
			 * \return \c true if this map is lexicographically less
			 *         than or equal to \a map, and \c false otherwise.
			 * \see operator<()
			 */
			bool operator<=(const Map& map) const;

			/**
			 * \brief Greater or equal comparison operator.
			 *
			 * The result is equivalent to <tt>!(*this < map)</tt>.
			 *
			 * \param map The other map to be compared with.
			 * \return \c true if this map is lexicographically greater
			 *         than or equal to \a map, and \c false otherwise.
			 * \see operator<()
			 */
			bool operator>=(const Map& map) const;

			/**
			 * \brief Less than comparison operator.
			 *
			 * The result is \c true if the entries of the array are lexicographically less
			 * than the entries in \a map, and \c false otherwise.
			 *
			 * \param map The other map to be compared with.
			 * \return \c true if this map is lexicographically less than \a map, and 
			 *         \c false otherwise.
			 * \note \a KeyType and \a ValueType must be less than comparable.
			 */
			bool operator<(const Map& map) const;

			/**
			 * \brief Greater than comparison operator.
			 *
			 * The result is equivalent to <tt>(map < *this)</tt>.
			 *
			 * \param map The other map to be compared with.
			 * \return \c true if this map is lexicographically greater than \a map, and 
			 *         \c false otherwise.
			 * \see operator<()
			 */			
			bool operator>(const Map& map) const;

		protected:
			/**
			 * \brief Returns the name of the (derived) Map class.
			 *
			 * Overriding this method provides an easy way to customize exception
			 * messages with the name of a derived class. 
			 *
			 * Consider the class \c MyMap which inherits publicly from \c Map<int, int> and overrides getClassName():
			 * \code
			 * class MyMap : public CDPL::Util::Map<int, int>
			 * {
			 *
			 *    .....
			 *
			 * private:
			 *    const char* getClassName() const {
			 *       return "MyMap";
			 *    }
			 * };
			 * \endcode
			 *
			 * If, for example, the requested value for a particular key is not found, the error message
			 * of the thrown Base::ItemNotFound exception will now start with "MyMap: ...." instead of
			 * the default "Map: ....". 

			 * \return The name of the class as a C-string.
			 * \see Array::getClassName
			 */
			virtual const char* getClassName() const;

		private:
			const Value& getDefaultValue() const;

			StorageType data;
		};

		/**
		 * @}
		 */
	}
}


// Implementation

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
std::size_t CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getSize() const
{
	return data.size();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::isEmpty() const
{
	return data.empty();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
void CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::clear()
{
	data.clear();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
void CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::swap(Map& map)
{
	data.swap(map.data);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
KeyCompFunc CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getKeyCompareFunction() const
{
	return data.key_comp();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntry(const Key& key)
{
	return data.find(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ConstEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntry(const Key& key) const
{
	return data.find(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::containsEntry(const Key& key) const
{
	return (data.find(key) != data.end());
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
Value& CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getValue(const Key& key)
{
	EntryIterator lb = data.lower_bound(key);

	if (lb == data.end() || data.key_comp()(key, (*lb).first)) {
		if (!AllowDefValues)
			throw Base::ItemNotFound(std::string(getClassName()) + ": key not found");
        
		return (*data.insert(lb, Entry(key, getDefaultValue()))).second;
	}

	return (*lb).second;
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
Value& CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getValue(const Key& key, Value& def_value)
{
	EntryIterator it = data.find(key);

	if (it == data.end())
		return def_value;

	return (*it).second;
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
const Value& CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getValue(const Key& key) const
{
	ConstEntryIterator it = data.find(key);

	if (it == data.end()) {
		if (!AllowDefValues)
			throw Base::ItemNotFound(std::string(getClassName()) + ": key not found");

		return getDefaultValue();
	}

	return (*it).second;
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
const Value& CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getValue(const Key& key,
																					   const Value& def_value) const
{
	ConstEntryIterator it = data.find(key);

	if (it == data.end())
		return def_value;

	return (*it).second;
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
Value& CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator[](const Key& key)
{
	return getValue(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
const Value& CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator[](const Key& key) const
{
	return getValue(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
void CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::removeEntry(const EntryIterator& it)
{
	data.erase(it);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::removeEntry(const Key& key)
{
	return (data.erase(key) > 0);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
void CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::removeEntries(const EntryIterator& first, 
																					const EntryIterator& last)
{
	data.erase(first, last);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
std::pair<typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator, bool> 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::insertEntry(const Entry& item)
{
	return data.insert(item);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
std::pair<typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator, bool> 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::insertEntry(const Key& key, const Value& value)
{
	return data.insert(Entry(key, value));
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::insertEntry(const EntryIterator& it, const Entry& item)
{
	return data.insert(it, item);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::insertEntry(const EntryIterator& it, const Key& key, 
																	  const Value& value)
{
	return data.insert(it, Entry(key, value));
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::setEntry(const Entry& item)
{
	EntryIterator lb = data.lower_bound(item.first);

	if (lb == data.end() || data.key_comp()(item.first, (*lb).first))
		return data.insert(lb, item);

	(*lb).second = item.second;
	return lb;
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::setEntry(const Key& key, const Value& value)
{
	return setEntry(Entry(key, value));
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
template <typename InputIter>
void CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::insertEntries(const InputIter& first, const InputIter& last)
{
	data.insert(first, last);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
template <typename InputIter>
void CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::setEntries(const InputIter& first, const InputIter& last)
{
	for (InputIter it = first; it != last; ++it)
		setEntry(*it);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getLowerBound(const Key& key)
{
	return data.lower_bound(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ConstEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getLowerBound(const Key& key) const
{
	return data.lower_bound(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getUpperBound(const Key& key)
{
	return data.upper_bound(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ConstEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getUpperBound(const Key& key) const
{
	return data.upper_bound(key);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ConstEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesBegin() const
{
	return data.begin();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesBegin()
{
	return data.begin();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>		
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ConstEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesEnd() const
{
	return data.end();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::EntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesEnd()
{
	return data.end();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ConstReverseEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesReverseBegin() const
{
	return data.rbegin();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ReverseEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesReverseBegin()
{
	return data.rbegin();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ConstReverseEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesReverseEnd() const
{
	return data.rend();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
typename CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::ReverseEntryIterator 
CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getEntriesReverseEnd()
{
	return data.rend();
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator==(const Map& map) const
{
	return (data == map.data);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator!=(const Map& map) const
{
	return (data != map.data);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator<=(const Map& map) const
{
	return (data <= map.data);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator>=(const Map& map) const
{
	return (data >= map.data);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator<(const Map& map) const
{
	return (data < map.data);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
bool CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::operator>(const Map& map) const
{
	return (data > map.data);
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
const char* CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getClassName() const
{
	return "Map";
}

template <typename Key, typename Value, bool AllowDefValues, typename KeyCompFunc>
const Value& CDPL::Util::Map<Key, Value, AllowDefValues, KeyCompFunc>::getDefaultValue() const
{
	return MapDefaultValue<Value, AllowDefValues>::get();
}

#endif // CDPL_UTIL_MAP_HPP
