/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataWriterExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_DATAWRITEREXPORT_HPP
#define CDPL_PYTHON_BASE_DATAWRITEREXPORT_HPP

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Base/DataWriter.hpp"


namespace CDPLPythonBase
{

	template <typename T>
	struct DataWriterWrapper : CDPL::Base::DataWriter<T>, boost::python::wrapper<CDPL::Base::DataWriter<T> >
	{

		typedef boost::shared_ptr<DataWriterWrapper<T> > SharedPointer;

		CDPL::Base::DataWriter<T>& write(const T& obj) {
			this->get_override("write")(boost::ref(obj));

			return *this;
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
                              
			CDPL::Base::DataWriter<T>::close();
		}

		void closeDef() {
			CDPL::Base::DataWriter<T>::close();
		}
	};

	template <typename T>
	struct DataWriterExport
	{

		DataWriterExport(const char* name, const char* obj_arg_name) {
			using namespace boost;
			using namespace CDPL;

			typedef Base::DataWriter<T> WriterType;

			python::class_<DataWriterWrapper<T>, typename DataWriterWrapper<T>::SharedPointer,
				python::bases<Base::DataIOBase>, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def("write", python::pure_virtual(&WriterType::write), 
					 (python::arg("self"), python::arg(obj_arg_name)), python::return_self<>())
				.def("close", &WriterType::close, &DataWriterWrapper<T>::closeDef, python::arg("self"))
				.def("__bool__", python::pure_virtual(&nonZero), python::arg("self"))
				.def("__nonzero__", python::pure_virtual(&nonZero), python::arg("self"));

			python::register_ptr_to_python<typename Base::DataWriter<T>::SharedPointer>();
		}

		static bool nonZero(CDPL::Base::DataWriter<T>& writer) {
			return writer.operator const void*();
		}
	};
}

#endif // CDPL_PYTHON_BASE_DATAWRITEREXPORT_HPP
