/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataInputHandlerExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_DATAINPUTHANDLEREXPORT_HPP
#define CDPL_PYTHON_BASE_DATAINPUTHANDLEREXPORT_HPP

#include <boost/python.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Base/DataInputHandler.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/DataReader.hpp"

#include "ObjectIdentityCheckVisitor.hpp"


namespace CDPLPythonBase
{

	template <typename T>
	struct DataInputHandlerWrapper : 
		CDPL::Base::DataInputHandler<T>, boost::python::wrapper<CDPL::Base::DataInputHandler<T> >
	{

		typedef typename CDPL::Base::DataInputHandler<T>::ReaderType ReaderType;
		typedef boost::shared_ptr<DataInputHandlerWrapper> SharedPointer;

		const CDPL::Base::DataFormat& getDataFormat() const {
			return this->get_override("getDataFormat")();
		}

		typename ReaderType::SharedPointer createReader(std::istream& is) const {
			return this->get_override("createReader")(boost::ref(is));
		}

		typename ReaderType::SharedPointer createReader(const std::string& file_name, std::ios_base::openmode mode) const {
			return this->get_override("createReader")(file_name, mode);
		}
	};

	template <typename T>
	struct DataInputHandlerExport
	{

		DataInputHandlerExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			typedef Base::DataInputHandler<T> HandlerType;

			typename HandlerType::ReaderType::SharedPointer (HandlerType::*createReaderFunc1)(std::istream&) const;
			typename HandlerType::ReaderType::SharedPointer (HandlerType::*createReaderFunc2)(const std::string&, std::ios_base::openmode) const;

			python::class_<DataInputHandlerWrapper<T>, typename DataInputHandlerWrapper<T>::SharedPointer, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(ObjectIdentityCheckVisitor<HandlerType>())
				.def("getDataFormat", python::pure_virtual(&HandlerType::getDataFormat), 
					 python::arg("self"), python::return_internal_reference<1>())
				.def("createReader", python::pure_virtual(createReaderFunc1), 
					 (python::arg("self"), python::arg("is")), python::with_custodian_and_ward_postcall<0, 2>())
				.def("createReader", python::pure_virtual(createReaderFunc2), 
					 (python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in | std::ios_base::binary));

			python::register_ptr_to_python<typename Base::DataInputHandler<T>::SharedPointer>();
		}
	};
}

#endif // CDPL_PYTHON_BASE_DATAINPUTHANDLEREXPORT_HPP
