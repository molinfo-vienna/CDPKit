/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataOutputHandlerExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_DATAOUTPUTHANDLEREXPORT_HPP
#define CDPL_PYTHON_BASE_DATAOUTPUTHANDLEREXPORT_HPP

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

		const CDPL::Base::DataFormat& getDataFormat() const {
			return this->get_override("getDataFormat")();
		}

		typename CDPL::Base::DataWriter<T>::SharedPointer createWriter(std::ostream& os) const {
			return this->get_override("createWriter")(boost::ref(os));
		}
	};

	template <typename T>
	struct DataOutputHandlerExport
	{

		DataOutputHandlerExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			typedef Base::DataOutputHandler<T> HandlerType;

			python::class_<DataOutputHandlerWrapper<T>, boost::noncopyable>(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(ObjectIdentityCheckVisitor<HandlerType>())
				.def("getDataFormat", python::pure_virtual(&HandlerType::getDataFormat),
					 python::arg("self"), python::return_internal_reference<1>())
				.def("createWriter", python::pure_virtual(&HandlerType::createWriter), 
					 (python::arg("self"), python::arg("os")), python::with_custodian_and_ward_postcall<0, 2>());
		}
	};
}

#endif // CDPL_PYTHON_BASE_DATAOUTPUTHANDLEREXPORT_HPP
