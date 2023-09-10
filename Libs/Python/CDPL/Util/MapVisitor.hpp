/* 
 * MapVisitor.hpp 
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


#ifndef CDPL_PYTHON_UTIL_MAPVISITOR_HPP
#define CDPL_PYTHON_UTIL_MAPVISITOR_HPP

#include <algorithm>
#include <type_traits>

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"


namespace CDPLPythonUtil
{

    template <typename MapType>
    struct LValueGetter
    {

        static boost::reference_wrapper<typename MapType::ValueType> getValue(typename MapType::ValueType& value)
        {
            return boost::ref(value);
        }
    };

    template <typename MapType>
    struct RValueGetter
    {

        static typename MapType::ValueType getValue(typename MapType::ValueType& value)
        {
            return value;
        }
    };

    template <typename MapType>
    struct KeyLValueGetter
    {

        static boost::reference_wrapper<const typename MapType::KeyType> getValue(const typename MapType::KeyType& key)
        {
            return boost::ref(key);
        }
    };

    template <typename MapType>
    struct KeyRValueGetter
    {

        static const typename MapType::KeyType getValue(const typename MapType::KeyType& key)
        {
            return key;
        }
    };

    template <typename MapType, typename ValueReturnPolicy,
              typename EntryAdditionPolicy1, typename EntryAdditionPolicy2,
              typename GetValueOrDefaultPolicy, bool GetValueOrDefaultWithLValue, bool GetKeyWithLValue>
    class BasicMapVisitor : public boost::python::def_visitor<BasicMapVisitor<MapType, ValueReturnPolicy, EntryAdditionPolicy1,
                                                                              EntryAdditionPolicy2, GetValueOrDefaultPolicy, GetValueOrDefaultWithLValue, GetKeyWithLValue> >
    {

        friend class boost::python::def_visitor_access;

        struct ValueOrDefaultLValueGetter
        {

            static typename MapType::ValueType& getValue(MapType& map, const typename MapType::KeyType& key,
                                                         typename MapType::ValueType& def_value)
            {
                return map.getValue(key, def_value);
            }
        };

        struct ValueOrDefaultRValueGetter
        {

            static typename MapType::ValueType getValue(MapType& map, const typename MapType::KeyType& key,
                                                        typename MapType::ValueType def_value)
            {
                return map.getValue(key, def_value);
            }
        };

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;

            bool (MapType::*removeEntryFunc)(const typename MapType::KeyType&) = &MapType::removeEntry;

            typename MapType::ValueType& (MapType::*getValueFunc)(const typename MapType::KeyType&) = &MapType::getValue;

            typedef typename std::conditional<GetValueOrDefaultWithLValue,
                                              ValueOrDefaultLValueGetter,
                                              ValueOrDefaultRValueGetter>::type ValueOrDefaultGetter;

            cl
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<MapType>())
                .def("getSize", &MapType::getSize, python::arg("self"))
                .def("isEmpty", &MapType::isEmpty, python::arg("self"))
                .def("clear", &MapType::clear, python::arg("self"))
                .def("assign", CDPLPythonBase::copyAssOp<MapType>(&MapType::operator=), (python::arg("self"), python::arg("map")),
                     python::return_self<EntryAdditionPolicy1>())
                .def("getValue", getValueFunc, (python::arg("self"), python::arg("key")), ValueReturnPolicy())
                .def("getValue", &ValueOrDefaultGetter::getValue, (python::arg("self"), python::arg("key"), python::arg("def_value")),
                     GetValueOrDefaultPolicy())
                .def("removeEntry", removeEntryFunc, (python::arg("self"), python::arg("key")))
                .def("setEntry", &setEntry, (python::arg("self"), python::arg("key"), python::arg("value")),
                     EntryAdditionPolicy2())
                .def("getKeys", &getKeys, python::arg("self"))
                .def("getValues", &getValues, python::arg("self"))
                .def("getEntries", &getEntries, python::arg("self"))
                .def("__len__", &MapType::getSize, python::arg("self"))
                .def("__getitem__", getValueFunc, (python::arg("self"), python::arg("key")),
                     ValueReturnPolicy())
                .def("__setitem__", &setItem, (python::arg("self"), python::arg("key"), python::arg("value")),
                     EntryAdditionPolicy2())
                .def("__delitem__", removeEntryFunc, (python::arg("self"), python::arg("key")))
                .add_property("keys", &getKeys)
                .add_property("values", &getValues)
                .add_property("entries", &getEntries)
                .add_property("size", &MapType::getSize);
        }

        static void setEntry(MapType& map, const typename MapType::KeyType& key, const typename MapType::ValueType& value)
        {
            map.setEntry(key, value);
        }

        static void setItem(MapType& map, const typename MapType::KeyType& key, const typename MapType::ValueType& value)
        {
            map[key] = value;
        }

        static boost::python::object getKeys(MapType& map)
        {
            using namespace boost;

            python::list keys;

            typename MapType::EntryIterator entries_end = map.getEntriesEnd();

            for (typename MapType::EntryIterator it = map.getEntriesBegin(); it != entries_end; ++it)
                keys.append(std::conditional<GetKeyWithLValue, KeyLValueGetter<MapType>, KeyRValueGetter<MapType> >::type::getValue((*it).first));

            return std::move(keys);
        }

        static boost::python::object getValues(MapType& map)
        {
            using namespace boost;

            python::list values;

            typename MapType::EntryIterator entries_end = map.getEntriesEnd();

            for (typename MapType::EntryIterator it = map.getEntriesBegin(); it != entries_end; ++it)
                values.append(std::conditional<GetValueOrDefaultWithLValue, LValueGetter<MapType>,
                                               RValueGetter<MapType> >::type::getValue((*it).second));

            return std::move(values);
        }

        static boost::python::object getEntries(MapType& map)
        {
            using namespace boost;

            python::list entries;

            typename MapType::EntryIterator entries_end = map.getEntriesEnd();

            for (typename MapType::EntryIterator it = map.getEntriesBegin(); it != entries_end; ++it)
                entries.append(python::make_tuple(std::conditional<GetKeyWithLValue, KeyLValueGetter<MapType>, KeyRValueGetter<MapType> >::type::getValue((*it).first),
                                                  std::conditional<GetValueOrDefaultWithLValue,
                                                                   LValueGetter<MapType>, RValueGetter<MapType> >::type::getValue((*it).second)));
            return std::move(entries);
        }
    };

    template <typename MapType, typename ValueReturnPolicy,
              typename EntryAdditionPolicy1, typename EntryAdditionPolicy2,
              typename GetValueOrDefaultPolicy, bool GetValueOrDefaultWithLValue, bool GetKeyWithLValue = false>
    class MapVisitor : public boost::python::def_visitor<MapVisitor<MapType, ValueReturnPolicy, EntryAdditionPolicy1,
                                                                    EntryAdditionPolicy2, GetValueOrDefaultPolicy, GetValueOrDefaultWithLValue, GetKeyWithLValue> >
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;

            cl
                .def(BasicMapVisitor<MapType, ValueReturnPolicy, EntryAdditionPolicy1, EntryAdditionPolicy2,
                                     GetValueOrDefaultPolicy, GetValueOrDefaultWithLValue, GetKeyWithLValue>())
                .def("containsEntry", &MapType::containsEntry, (python::arg("self"), python::arg("key")))
                .def("insertEntry", &insertEntry, (python::arg("self"), python::arg("key"), python::arg("value")),
                     EntryAdditionPolicy2())
                .def("__contains__", &MapType::containsEntry, (python::arg("self"), python::arg("key")));
        }

        static bool insertEntry(MapType& map, const typename MapType::KeyType& key, const typename MapType::ValueType& value)
        {
            return map.insertEntry(key, value).second;
        }
    };

    template <typename MapType, typename ValueReturnPolicy,
              typename EntryAdditionPolicy1, typename EntryAdditionPolicy2,
              typename GetValueOrDefaultPolicy, bool GetValueOrDefaultWithLValue, bool GetKeyWithLValue = false>
    class MultiMapVisitor : public boost::python::def_visitor<MultiMapVisitor<MapType, ValueReturnPolicy, EntryAdditionPolicy1,
                                                                              EntryAdditionPolicy2, GetValueOrDefaultPolicy, GetValueOrDefaultWithLValue, GetKeyWithLValue> >
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;

            std::size_t (MapType::*removeEntriesFunc)(const typename MapType::KeyType&) = &MapType::removeEntries;

            cl
                .def(BasicMapVisitor<MapType, ValueReturnPolicy, EntryAdditionPolicy1, EntryAdditionPolicy2,
                                     GetValueOrDefaultPolicy, GetValueOrDefaultWithLValue, GetKeyWithLValue>())
                .def("getNumEntries", &MapType::getNumEntries, (python::arg("self"), python::arg("key")))
                .def("removeEntries", removeEntriesFunc, (python::arg("self"), python::arg("key")))
                .def("insertEntry", &insertEntry, (python::arg("self"), python::arg("key"), python::arg("value")),
                     EntryAdditionPolicy2())
                .def("getValues", &getValues, (python::arg("self"), python::arg("key")))
                .def("__contains__", &MapType::getNumEntries, (python::arg("self"), python::arg("key")));
        }

        static void insertEntry(MapType& map, const typename MapType::KeyType& key, const typename MapType::ValueType& value)
        {
            map.insertEntry(key, value);
        }

        static boost::python::object getValues(MapType& map, const typename MapType::KeyType& key)
        {
            using namespace boost;

            python::list values;

            typename MapType::EntryIteratorRange entry_range = map.getEntries(key);

            for (; entry_range.first != entry_range.second; ++entry_range.first)
                values.append(std::conditional<GetValueOrDefaultWithLValue, LValueGetter<MapType>,
                                               RValueGetter<MapType> >::type::getValue((*entry_range.first).second));

            return std::move(values);
        }
    };
} // namespace CDPLPythonUtil

#endif // CDPL_PYTHON_UTIL_MAPVISITOR_HPP
