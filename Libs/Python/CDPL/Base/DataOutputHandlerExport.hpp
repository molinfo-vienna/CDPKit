/* 
 * DataOutputHandlerExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_DATAOUTPUTHANDLEREXPORT_HPP
#define CDPL_PYTHON_BASE_DATAOUTPUTHANDLEREXPORT_HPP

#include <memory>

#include <boost/python.hpp>

#include "CDPL/Base/DataOutputHandler.hpp"
#include "CDPL/Base/DataFormat.hpp"
#include "CDPL/Base/DataWriter.hpp"

#include "ObjectIdentityCheckVisitor.hpp"


namespace CDPLPythonBase
{

	template <typename T>
	struct DataOutputHandlerWrapper : 
		CDPL::Base::DataOutputHandler<T>, boost::python::wrapper<CDPL::Base::DataOutputHandler<T> >
	{

		typedef typename CDPL::Base::DataOutputHandler<T>::WriterType WriterType;
		typedef std::shared_ptr<DataOutputHandlerWrapper> SharedPointer;

		const CDPL::Base::DataFormat& getDataFormat() const {
			return this->get_override("getDataFormat")();
		}

		typename WriterType::SharedPointer createWriter(std::iostream& ios) const {
			return this->get_override("createWriter")(boost::ref(ios));
		}

		typename WriterType::SharedPointer createWriter(const std::string& file_name, std::ios_base::openmode mode) const {
			return this->get_override("createWriter")(file_name, mode);
		}
	};

	template <typename T>
	struct DataOutputHandlerExport
	{

		DataOutputHandlerExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			typedef Base::DataOutputHandler<T> HandlerType;

			typename HandlerType::WriterType::SharedPointer (HandlerType::*createWriterFunc1)(std::iostream&) const = &HandlerType::createWriter;
			typename HandlerType::WriterType::SharedPointer (HandlerType::*createWriterFunc2)(const std::string&, std::ios_base::openmode) const = &HandlerType::createWriter;

            python::class_<DataOutputHandlerWrapper<T>, typename DataOutputHandlerWrapper<T>::SharedPointer, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(ObjectIdentityCheckVisitor<HandlerType>())
				.def("getDataFormat", python::pure_virtual(&HandlerType::getDataFormat),
					 python::arg("self"), python::return_internal_reference<1>())
				.def("createWriter", python::pure_virtual(createWriterFunc1), 
					 (python::arg("self"), python::arg("is")), python::with_custodian_and_ward_postcall<0, 2>())
				.def("createWriter", python::pure_virtual(createWriterFunc2), 
					 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
					  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary));

			python::register_ptr_to_python<typename Base::DataOutputHandler<T>::SharedPointer>();
		}
	};
}

#endif // CDPL_PYTHON_BASE_DATAOUTPUTHANDLEREXPORT_HPP
