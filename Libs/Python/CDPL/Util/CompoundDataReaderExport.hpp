/* 
 * CompoundDataReaderExport.hpp 
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


#ifndef CDPL_PYTHON_UTIL_COMPOUNDDATAREADEREXPORT_HPP
#define CDPL_PYTHON_UTIL_COMPOUNDDATAREADEREXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Util/CompoundDataReader.hpp"


namespace CDPLPythonUtil
{

    template <typename T>
    struct CompoundDataReaderExport
    {

		CompoundDataReaderExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			typedef Util::CompoundDataReader<T> ReaderType;

			python::class_<ReaderType, typename Util::CompoundDataReader<T>::SharedPointer,
						   python::bases<Base::DataReader<T> >, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const ReaderType&>((python::arg("self"), python::arg("reader"))))
				.def("assign", &ReaderType::operator=, (python::arg("self"), python::arg("reader")),
					 python::return_self<>())
				.def("getNumReaders", &ReaderType::getNumReaders, python::arg("self"))
				.def("addReader", &ReaderType::addReader, (python::arg("self"), python::arg("reader")))
				.def("removeReader", &ReaderType::removeReader, (python::arg("self"), python::arg("idx")))
				.def("clear", &ReaderType::clear, python::arg("self"))
				.def("getReader", &ReaderType::getReader, (python::arg("self"), python::arg("idx")),
					 python::return_value_policy<python::copy_const_reference>())
				.add_property("numReaders", &ReaderType::getNumReaders);
		}
    };
}

#endif // CDPL_PYTHON_UTIL_COMPOUNDDATAREADEREXPORT_HPP
