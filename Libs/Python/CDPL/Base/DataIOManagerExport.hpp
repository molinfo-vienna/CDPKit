/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataIOManagerExport.hpp 
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


#ifndef CDPL_PYTHON_BASE_DATAIOMANAGEREXPORT_HPP
#define CDPL_PYTHON_BASE_DATAIOMANAGEREXPORT_HPP

#include <map>

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
				.def("registerInputHandler", &registerInputHandler, python::arg("handler"))
				.staticmethod("registerInputHandler")
				.def("getInputHandler", &getInputHandlerByIndex, python::arg("idx"))
				.staticmethod("getInputHandler")
				.def("getInputHandlerByFormat", &getInputHandlerByFormat, python::arg("fmt"))
				.staticmethod("getInputHandlerByFormat")
				.def("getInputHandlerByName", &getInputHandlerByName, python::arg("name"))
				.staticmethod("getInputHandlerByName")
				.def("getInputHandlerByFileExtension", &getInputHandlerByFileExtension, python::arg("file_ext"))
				.staticmethod("getInputHandlerByFileExtension")
				.def("getInputHandlerByMimeType", &getInputHandlerByMimeType, python::arg("mime_type"))
				.staticmethod("getInputHandlerByMimeType")
				.def("unregisterInputHandler", &unregisterInputHandlerByFormat, python::arg("fmt"))
				.def("unregisterInputHandler", &unregisterInputHandlerByIndex, python::arg("idx"))
				.def("unregisterInputHandler", &unregisterInputHandler, python::arg("handler"))
				.staticmethod("unregisterInputHandler")
				.def("getNumInputHandlers", &ManagerType::getNumInputHandlers)
				.staticmethod("getNumInputHandlers")
				.def("getInputHandlers", &createInputHandlerSequence)
				.staticmethod("getInputHandlers")
				.add_static_property("inputHandlers", &createInputHandlerSequence)
				.add_static_property("numInputHandlers", &ManagerType::getNumInputHandlers)
				
				.def("registerOutputHandler", &registerOutputHandler, python::arg("handler"))
				.staticmethod("registerOutputHandler")
				.def("getOutputHandler", &getOutputHandlerByIndex, python::arg("idx"))
				.staticmethod("getOutputHandler")
				.def("getOutputHandlerByFormat", &getOutputHandlerByFormat, python::arg("fmt"))
				.staticmethod("getOutputHandlerByFormat")
				.def("getOutputHandlerByName", &getOutputHandlerByName, python::arg("name"))
				.staticmethod("getOutputHandlerByName")
				.def("getOutputHandlerByFileExtension", &getOutputHandlerByFileExtension, python::arg("file_ext"))
				.staticmethod("getOutputHandlerByFileExtension")
				.def("getOutputHandlerByMimeType", &getOutputHandlerByMimeType, python::arg("mime_type"))
				.staticmethod("getOutputHandlerByMimeType")
				.def("unregisterOutputHandler", &unregisterOutputHandlerByFormat, python::arg("fmt"))
				.def("unregisterOutputHandler", &unregisterOutputHandlerByIndex, python::arg("idx"))
				.def("unregisterOutputHandler", &unregisterOutputHandler, python::arg("handler"))
				.staticmethod("unregisterOutputHandler")
				.def("getNumOutputHandlers", &ManagerType::getNumOutputHandlers)
				.staticmethod("getNumOutputHandlers")
				.def("getOutputHandlers", &createOutputHandlerSequence)
				.staticmethod("getOutputHandlers")
				.add_static_property("outputHandlers", &createOutputHandlerSequence)
				.add_static_property("numOutputHandlers", &ManagerType::getNumOutputHandlers);

			python::class_<InputHandlerSequence>("InputHandlerSequence", python::no_init)
				.def("__getitem__", &getInputHandlerByIndex, python::arg("idx"))
				.def("__getitem__", &getInputHandlerByFormat, python::arg("fmt"))
				.def("__getitem__", &getInputHandlerByName, python::arg("name"))
				.staticmethod("__getitem__")
				.def("__delitem__", &unregisterInputHandlerByIndex, python::arg("idx"))
				.def("__delitem__", &unregisterInputHandlerByFormat, python::arg("fmt"))
				.def("__delitem__", &unregisterInputHandler, python::arg("handler"))
				.staticmethod("__delitem__")
				.def("__len__", &ManagerType::getNumInputHandlers) 
				.staticmethod("__len__");

			python::class_<OutputHandlerSequence>("OutputHandlerSequence", python::no_init)
				.def("__getitem__", &getOutputHandlerByIndex, python::arg("idx"))
				.def("__getitem__", &getOutputHandlerByFormat, python::arg("fmt"))
				.def("__getitem__", &getOutputHandlerByName, python::arg("name"))
				.staticmethod("__getitem__")
				.def("__delitem__", &unregisterOutputHandlerByIndex, python::arg("idx"))
				.def("__delitem__", &unregisterOutputHandlerByFormat, python::arg("fmt"))
				.def("__delitem__", &unregisterOutputHandler, python::arg("handler"))
				.staticmethod("__delitem__")
				.def("__len__", &ManagerType::getNumOutputHandlers) 
				.staticmethod("__len__");
		}

		typedef std::map<const void*, boost::python::handle<> > PythonInputHandlerRegistry;
		typedef std::map<const void*, boost::python::handle<> > PythonOutputHandlerRegistry;

		static PythonInputHandlerRegistry& getPythonInputHandlers() {
			static PythonInputHandlerRegistry handlers;

			return handlers;
		}

		static PythonOutputHandlerRegistry& getPythonOutputHandlers() {
			static PythonOutputHandlerRegistry handlers;

			return handlers;
		}

		static boost::python::object createInputHandlerObject(const CDPL::Base::DataInputHandler<T>* handler) {
			using namespace boost;

			PythonInputHandlerRegistry::const_iterator it = getPythonInputHandlers().find(handler);
			
			if (it != getPythonInputHandlers().end())
				return python::object(it->second);

			return python::object(python::ptr(handler));
		}

		static boost::python::object createOutputHandlerObject(const CDPL::Base::DataOutputHandler<T>* handler) {
			using namespace boost;

			PythonOutputHandlerRegistry::const_iterator it = getPythonOutputHandlers().find(handler);
			
			if (it != getPythonOutputHandlers().end())
				return python::object(it->second);

			return python::object(python::ptr(handler));
		}

		static void registerInputHandler(const boost::python::object& handler_obj) {
			using namespace boost;
			using namespace CDPL;

			const CDPL::Base::DataInputHandler<T>& handler = python::extract<const Base::DataInputHandler<T>&>(handler_obj)();

			getPythonInputHandlers()[&handler] = python::handle<>(python::borrowed(handler_obj.ptr()));

			Base::DataIOManager<T>::registerInputHandler(handler);
		}


		static void registerOutputHandler(const boost::python::object& handler_obj) {
			using namespace boost;
			using namespace CDPL;

			const CDPL::Base::DataOutputHandler<T>& handler = python::extract<const Base::DataOutputHandler<T>&>(handler_obj)();

			getPythonOutputHandlers()[&handler] = python::handle<>(python::borrowed(handler_obj.ptr()));

			Base::DataIOManager<T>::registerOutputHandler(handler);
		}

		static bool unregisterInputHandler(const CDPL::Base::DataInputHandler<T>& handler) {
			using namespace CDPL;

			if (Base::DataIOManager<T>::unregisterInputHandler(handler)) {
				getPythonInputHandlers().erase(&handler);

				return true;
			}

			return false;
		}

		static bool unregisterInputHandlerByFormat(const CDPL::Base::DataFormat& fmt) {
			using namespace CDPL;

			for (std::size_t i = 0; i < Base::DataIOManager<T>::getNumInputHandlers(); ) {
				const Base::DataInputHandler<T>& handler = Base::DataIOManager<T>::getInputHandler(i);

				if (handler.getDataFormat() != fmt) {
					i++; 
					continue;
				}
				
				Base::DataIOManager<T>::unregisterInputHandler(i);

				getPythonInputHandlers().erase(&handler);

				return true;
			}

			return false;
		}

		static void unregisterInputHandlerByIndex(std::size_t idx) {
			using namespace CDPL;

			const Base::DataInputHandler<T>& handler = Base::DataIOManager<T>::getInputHandler(idx);

			Base::DataIOManager<T>::unregisterInputHandler(idx);
			
			getPythonInputHandlers().erase(&handler);
		}

		static bool unregisterOutputHandler(const CDPL::Base::DataOutputHandler<T>& handler) {
			using namespace CDPL;

			if (Base::DataIOManager<T>::unregisterOutputHandler(handler)) {
				getPythonOutputHandlers().erase(&handler);

				return true;
			}

			return false;
		}

		static bool unregisterOutputHandlerByFormat(const CDPL::Base::DataFormat& fmt) {
			using namespace CDPL;
		
			for (std::size_t i = 0; i < Base::DataIOManager<T>::getNumOutputHandlers(); ) {
				const Base::DataOutputHandler<T>& handler = Base::DataIOManager<T>::getOutputHandler(i);

				if (handler.getDataFormat() != fmt) {
					i++; 
					continue;
				}

				Base::DataIOManager<T>::unregisterOutputHandler(i);

				getPythonOutputHandlers().erase(&handler);

				return true;
			}

			return false;
		}

		static void unregisterOutputHandlerByIndex(std::size_t idx) {
			using namespace CDPL;

			const Base::DataOutputHandler<T>& handler = Base::DataIOManager<T>::getOutputHandler(idx);

			Base::DataIOManager<T>::unregisterOutputHandler(idx);

			getPythonOutputHandlers().erase(&handler);
		}

		static boost::python::object getInputHandlerByIndex(std::size_t idx) {
			return createInputHandlerObject(&CDPL::Base::DataIOManager<T>::getInputHandler(idx));
		}

		static boost::python::object getOutputHandlerByIndex(std::size_t idx) {
			return createOutputHandlerObject(&CDPL::Base::DataIOManager<T>::getOutputHandler(idx));
		}

		static boost::python::object getInputHandlerByFormat(const CDPL::Base::DataFormat& fmt) {
			return createInputHandlerObject(CDPL::Base::DataIOManager<T>::getInputHandlerByFormat(fmt));
		}

		static boost::python::object getOutputHandlerByFormat(const CDPL::Base::DataFormat& fmt) {
			return createOutputHandlerObject(CDPL::Base::DataIOManager<T>::getOutputHandlerByFormat(fmt));
		}

		static boost::python::object getInputHandlerByName(const std::string& name) {
			return createInputHandlerObject(CDPL::Base::DataIOManager<T>::getInputHandlerByName(name));
		}

		static boost::python::object getOutputHandlerByName(const std::string& name) {
			return createOutputHandlerObject(CDPL::Base::DataIOManager<T>::getOutputHandlerByName(name));
		}

		static boost::python::object getInputHandlerByFileExtension(const std::string& file_ext) {
			return createInputHandlerObject(CDPL::Base::DataIOManager<T>::getInputHandlerByFileExtension(file_ext));
		}

		static boost::python::object getOutputHandlerByFileExtension(const std::string& file_ext) {
			return createOutputHandlerObject(CDPL::Base::DataIOManager<T>::getOutputHandlerByFileExtension(file_ext));
		}

		static boost::python::object getInputHandlerByMimeType(const std::string& mime_type) {
			return createInputHandlerObject(CDPL::Base::DataIOManager<T>::getInputHandlerByMimeType(mime_type));
		}

		static boost::python::object getOutputHandlerByMimeType(const std::string& mime_type) {
			return createOutputHandlerObject(CDPL::Base::DataIOManager<T>::getOutputHandlerByMimeType(mime_type));
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
