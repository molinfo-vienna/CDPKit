/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataReaderExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_DATAREADEREXPORT_HPP
#define CDPL_PYTHON_BASE_DATAREADEREXPORT_HPP

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Base/DataReader.hpp"


namespace CDPLPythonBase
{

	template <typename T>
	struct DataReaderWrapper : CDPL::Base::DataReader<T>, boost::python::wrapper<CDPL::Base::DataReader<T> >
	{

		typedef boost::shared_ptr<DataReaderWrapper<T> > SharedPointer;

		CDPL::Base::DataReader<T>& read(T& obj, bool overwrite) {
			this->get_override("read")(boost::ref(obj), overwrite);

			return *this;
		}

		CDPL::Base::DataReader<T>& read(std::size_t idx, T& obj, bool overwrite) {
			this->get_override("read")(idx, boost::ref(obj), overwrite);

			return *this;		
		}

		CDPL::Base::DataReader<T>& skip() {
			this->get_override("skip")();

			return *this;
		}

		bool hasMoreData() {
			return this->get_override("hasMoreData")();
		}

		std::size_t getRecordIndex() const {
			return this->get_override("getRecordIndex")();
		}

		void setRecordIndex(std::size_t idx) {
			this->get_override("getRecordIndex")(idx);
		}

		std::size_t getNumRecords() {
			return this->get_override("getNumRecords")();
		}
		
		operator const void*() const {
			if (boost::python::override f = this->get_override("__nonzero__"))
				return (f() ? static_cast<const void*>(this) : static_cast<const void*>(0));

			if (this->get_override("__bool__")())
				return this;

			return 0;
		}

		bool operator!() const {
			if (boost::python::override f = this->get_override("__nonzero__"))
				return !f();

			return !this->get_override("__bool__")();
		}

		void close() {
			if (boost::python::override f = this->get_override("close")) {
				f();                                                      
				return;                                                   
			}                                                             
                              
			CDPL::Base::DataReader<T>::close();
		}

		void closeDef() {
			CDPL::Base::DataReader<T>::close();
		}
	};

	template <typename T>
	struct DataReaderExport
	{

		DataReaderExport(const char* name, const char* obj_arg_name) {
			using namespace boost;
			using namespace CDPL;

			typedef Base::DataReader<T> ReaderType;

			ReaderType& (ReaderType::*readFunc1)(T&, bool) = &ReaderType::read;
			ReaderType& (ReaderType::*readFunc2)(std::size_t, T&, bool) = &ReaderType::read;

			python::class_<DataReaderWrapper<T>, typename DataReaderWrapper<T>::SharedPointer,
				python::bases<Base::DataIOBase>, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def("read", python::pure_virtual(readFunc1), (python::arg("self"), python::arg(obj_arg_name), python::arg("overwrite") = true), 
					 python::return_self<>())
				.def("read", python::pure_virtual(readFunc2), (python::arg("self"), python::arg("idx"), python::arg(obj_arg_name), python::arg("overwrite") = true), 
					 python::return_self<>())
				.def("skip", python::pure_virtual(&ReaderType::skip), python::arg("self"), python::return_self<>())
				.def("hasMoreData", python::pure_virtual(&ReaderType::hasMoreData), python::arg("self"))
				.def("getRecordIndex", python::pure_virtual(&ReaderType::getRecordIndex), python::arg("self"))
				.def("setRecordIndex", python::pure_virtual(&ReaderType::setRecordIndex), (python::arg("self"), python::arg("idx")))
				.def("getNumRecords", python::pure_virtual(&ReaderType::getNumRecords), python::arg("self"))
				.def("close", &ReaderType::close, &DataReaderWrapper<T>::closeDef, python::arg("self"))
				.def("__nonzero__", python::pure_virtual(&nonZero), python::arg("self"))
				.def("__bool__", python::pure_virtual(&nonZero), python::arg("self"))
				.add_property("numRecords", &ReaderType::getNumRecords);

			python::register_ptr_to_python<typename Base::DataReader<T>::SharedPointer>();
		}

		static bool nonZero(CDPL::Base::DataReader<T>& reader) {
			return reader.operator const void*();
		}
	};
}

#endif // CDPL_PYTHON_BASE_DATAREADEREXPORT_HPP
