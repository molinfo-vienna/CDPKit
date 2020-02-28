/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataIOManagerExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_DATAIOMANAGEREXPORT_HPP
#define CDPL_PYTHON_BASE_DATAIOMANAGEREXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Base/DataIOManager.hpp"


namespace CDPLPythonBase
{

	template <typename T>
	struct DataIOManagerExport
	{

		struct InputHandlerSequence {};
		struct OutputHandlerSequence {};

		DataIOManagerExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			typedef Base::DataIOManager<T> ManagerType;

			python::scope scope = python::class_<Base::DataIOManager<T>, boost::noncopyable>(name, python::no_init)
				.def("registerInputHandler", &ManagerType::registerInputHandler, python::arg("handler"))
				.staticmethod("registerInputHandler")
				.def("getInputHandler", &ManagerType::getInputHandler, python::arg("idx"),
					 python::return_value_policy<python::copy_const_reference>())
				.staticmethod("getInputHandler")
				.def("getInputHandlerByFormat", &ManagerType::getInputHandlerByFormat, python::arg("fmt"))
				.staticmethod("getInputHandlerByFormat")
				.def("getInputHandlerByName", &ManagerType::getInputHandlerByName, python::arg("name"))
				.staticmethod("getInputHandlerByName")
				.def("getInputHandlerByFileExtension", &ManagerType::getInputHandlerByFileExtension, python::arg("file_ext"))
				.staticmethod("getInputHandlerByFileExtension")
				.def("getInputHandlerByMimeType", &ManagerType::getInputHandlerByMimeType, python::arg("mime_type"))
				.staticmethod("getInputHandlerByMimeType")
				.def("unregisterInputHandler", static_cast<bool (*)(const Base::DataFormat&)>(&ManagerType::unregisterInputHandler), 
					 python::arg("fmt"))
				.def("unregisterInputHandler", static_cast<void (*)(std::size_t)>(&ManagerType::unregisterInputHandler), 
					 python::arg("idx"))
				.def("unregisterInputHandler", static_cast<bool (*)(const typename ManagerType::InputHandlerPointer&)>(&ManagerType::unregisterInputHandler), 
					 python::arg("handler"))
				.staticmethod("unregisterInputHandler")
				.def("getNumInputHandlers", &ManagerType::getNumInputHandlers)
				.staticmethod("getNumInputHandlers")
				.def("getInputHandlers", &createInputHandlerSequence)
				.staticmethod("getInputHandlers")
				.add_static_property("inputHandlers", &createInputHandlerSequence)
				.add_static_property("numInputHandlers", &ManagerType::getNumInputHandlers)
				
				.def("registerOutputHandler", &ManagerType::registerOutputHandler, python::arg("handler"))
				.staticmethod("registerOutputHandler")
				.def("getOutputHandler", &ManagerType::getOutputHandler, python::arg("idx"), 
					 python::return_value_policy<python::copy_const_reference>())
				.staticmethod("getOutputHandler")
				.def("getOutputHandlerByFormat", &ManagerType::getOutputHandlerByFormat, python::arg("fmt"))
				.staticmethod("getOutputHandlerByFormat")
				.def("getOutputHandlerByName", &ManagerType::getOutputHandlerByName, python::arg("name"))
				.staticmethod("getOutputHandlerByName")
				.def("getOutputHandlerByFileExtension", &ManagerType::getOutputHandlerByFileExtension, python::arg("file_ext"))
				.staticmethod("getOutputHandlerByFileExtension")
				.def("getOutputHandlerByMimeType", &ManagerType::getOutputHandlerByMimeType, python::arg("mime_type"))
				.staticmethod("getOutputHandlerByMimeType")
				.def("unregisterOutputHandler", static_cast<bool (*)(const Base::DataFormat&)>(&ManagerType::unregisterOutputHandler), 
					 python::arg("fmt"))
				.def("unregisterOutputHandler", static_cast<void (*)(std::size_t)>(&ManagerType::unregisterOutputHandler), 
					 python::arg("idx"))
				.def("unregisterOutputHandler", static_cast<bool (*)(const typename ManagerType::OutputHandlerPointer&)>(&ManagerType::unregisterOutputHandler), 
					 python::arg("handler"))
				.staticmethod("unregisterOutputHandler")
				.def("getNumOutputHandlers", &ManagerType::getNumOutputHandlers)
				.staticmethod("getNumOutputHandlers")
				.def("getOutputHandlers", &createOutputHandlerSequence)
				.staticmethod("getOutputHandlers")
				.add_static_property("outputHandlers", &createOutputHandlerSequence)
				.add_static_property("numOutputHandlers", &ManagerType::getNumOutputHandlers);

			python::class_<InputHandlerSequence>("InputHandlerSequence", python::no_init)
				.def("__getitem__", &ManagerType::getInputHandler, python::arg("idx"), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("__getitem__", &ManagerType::getInputHandlerByFormat, python::arg("fmt"))
				.def("__getitem__", &ManagerType::getInputHandlerByName, python::arg("name"))
				.staticmethod("__getitem__")
				.def("__delitem__", static_cast<void (*)(std::size_t)>(&ManagerType::unregisterInputHandler), 
					 python::arg("idx"))
				.def("__delitem__", static_cast<bool (*)(const Base::DataFormat&)>(&ManagerType::unregisterInputHandler),
					 python::arg("fmt"))
				.def("__delitem__", static_cast<bool (*)(const typename ManagerType::InputHandlerPointer&)>(&ManagerType::unregisterInputHandler),
					 python::arg("handler"))
				.staticmethod("__delitem__")
				.def("__len__", &ManagerType::getNumInputHandlers) 
				.staticmethod("__len__");

			python::class_<OutputHandlerSequence>("OutputHandlerSequence", python::no_init)
				.def("__getitem__", &ManagerType::getOutputHandler, python::arg("idx"), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("__getitem__", &ManagerType::getOutputHandlerByFormat, python::arg("fmt"))
				.def("__getitem__", &ManagerType::getOutputHandlerByName, python::arg("name"))
				.staticmethod("__getitem__")
				.def("__delitem__", static_cast<void (*)(std::size_t)>(&ManagerType::unregisterOutputHandler),
					 python::arg("idx"))
				.def("__delitem__", static_cast<bool (*)(const Base::DataFormat&)>(&ManagerType::unregisterOutputHandler),
					 python::arg("fmt"))
				.def("__delitem__", static_cast<bool (*)(const typename ManagerType::OutputHandlerPointer&)>(&ManagerType::unregisterOutputHandler)
					 , python::arg("handler"))
				.staticmethod("__delitem__")
				.def("__len__", &ManagerType::getNumOutputHandlers) 
				.staticmethod("__len__");
		}

		static InputHandlerSequence createInputHandlerSequence() {
			return InputHandlerSequence();
		}

		static OutputHandlerSequence createOutputHandlerSequence() {
			return OutputHandlerSequence();
		}
	};
}

#endif // CDPL_PYTHON_BASE_DATAIOMANAGEREXPORT_HPP
