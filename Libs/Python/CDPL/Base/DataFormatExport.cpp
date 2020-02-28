/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DataFormatExport.cpp 
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


#include <memory>

#include <boost/python.hpp>
#include <boost/python/ssize_t.hpp>

#include "CDPL/Base/DataFormat.hpp"

#include "CopyAssOp.hpp"
#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	struct FileExtensionSequence
	{

		FileExtensionSequence(CDPL::Base::DataFormat& data_format): dataFormat(data_format) {}

		std::size_t getNumExtensions() const {
			return dataFormat.getNumFileExtensions();
		}

		void setExtension(std::size_t idx, const std::string& file_ext) {
			dataFormat.setFileExtension(idx, file_ext);
		}
	
		bool containsExtension(const std::string& file_ext) {
			return dataFormat.matchesFileExtension(file_ext);
		}

		const std::string& getExtension(std::size_t idx) const {
			return dataFormat.getFileExtension(idx);
		}
	
		void removeExtension(std::size_t idx) {
			dataFormat.removeFileExtension(idx);
		}
	
		CDPL::Base::DataFormat& dataFormat;
	};

	class DataFormatWrapper : public CDPL::Base::DataFormat, public boost::python::wrapper<CDPL::Base::DataFormat>
	{

	public:
		DataFormatWrapper(): CDPL::Base::DataFormat() {}

		DataFormatWrapper(const CDPL::Base::DataFormat& fmt): CDPL::Base::DataFormat(fmt) {}

		DataFormatWrapper(const std::string& name, const std::string& descr, 
						  const std::string& mime_type, bool multi_rec): 
			CDPL::Base::DataFormat(name, descr, mime_type, static_cast<const std::string*>(0), 
								   static_cast<const std::string*>(0), multi_rec) {} 

		DataFormatWrapper(const std::string& name, const std::string& descr, const std::string& mime_type, 
						  PyObject* iterable, bool multi_rec):
			CDPL::Base::DataFormat(name, descr, mime_type, 
								   static_cast<const std::string*>(0),
								   static_cast<const std::string*>(0), 
								   multi_rec)
		{
			using namespace boost;

			PyObject *iter = PyObject_GetIter(iterable);

			if (!iter) {
				PyErr_SetString(PyExc_TypeError, "DataFormat: iterable object expected as 4th argument");

				python::throw_error_already_set();
			}

			python::handle<> iter_handle(iter);
			PyObject *item;

			while ((item = PyIter_Next(iter)))
				addFileExtension(python::extract<std::string>(python::object(python::handle<>(item))));
		} 
	};

	FileExtensionSequence getFileExtensions(CDPL::Base::DataFormat& fmt)
	{
		return FileExtensionSequence(fmt);
	}
}


void CDPLPythonBase::exportDataFormat()
{
	using namespace boost;
	using namespace CDPL;

	void (Base::DataFormat::*removeFileExtensionFunc)(std::size_t) = &Base::DataFormat::removeFileExtension;

    python::scope scope = python::class_<DataFormatWrapper>("DataFormat", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Base::DataFormat&>((python::arg("self"), python::arg("fmt"))))
		.def(python::init<const std::string&, const std::string&, const std::string&, bool>((
							 python::arg("self"), python::arg("name"), python::arg("descr"),
							 python::arg("mime_type"), python::arg("multi_rec"))))
		.def(python::init<const std::string&, const std::string&, const std::string&, PyObject*, bool>((
							 python::arg("self"), python::arg("name"), python::arg("description"),
							 python::arg("mime_type"), python::arg("file_extensions"),
							 python::arg("multi_rec"))))
		.def("getNumFileExtensions", &Base::DataFormat::getNumFileExtensions, python::arg("self"))
		.def("getFileExtension", &Base::DataFormat::getFileExtension, (python::arg("self"), python::arg("idx")),
			 python::return_value_policy<python::copy_const_reference>())
		.def("addFileExtension", &Base::DataFormat::addFileExtension, (python::arg("self"), python::arg("file_ext")),
			 python::return_self<>())
		.def("setFileExtension", &Base::DataFormat::setFileExtension, (python::arg("self"), python::arg("idx"),
			 python::arg("file_ext")))
		.def("clearFileExtensions", &Base::DataFormat::clearFileExtensions, python::arg("self"))
		.def("removeFileExtension", removeFileExtensionFunc, (python::arg("self"), python::arg("idx")))
		.def("matchesName", &Base::DataFormat::matchesName, (python::arg("self"), python::arg("name")))
		.def("matchesMimeType", &Base::DataFormat::matchesMimeType, (python::arg("self"), python::arg("mime_type")))
		.def("matchesFileExtension", &Base::DataFormat::matchesFileExtension, (python::arg("self"), python::arg("file_ext")))
		.def("getDescription", &Base::DataFormat::getDescription, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("setDescription", &Base::DataFormat::setDescription, (python::arg("self"), python::arg("descr")))
		.def("getName", &Base::DataFormat::getName, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setName", &Base::DataFormat::setName, (python::arg("self"), python::arg("name")))
		.def("getMimeType", &Base::DataFormat::getMimeType, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setMimeType", &Base::DataFormat::setMimeType, (python::arg("self"), python::arg("mime_type")))
		.def("isMultiRecordFormat", &Base::DataFormat::isMultiRecordFormat, python::arg("self"))
		.def("setMultiRecordFormat", &Base::DataFormat::setMultiRecordFormat, (python::arg("self"), python::arg("multi_rec")))
		.def("getFileExtensions", &getFileExtensions, python::arg("self"))
		.def("assign", copyAssOp(&Base::DataFormat::operator=), (python::arg("self"), python::arg("fmt")), python::return_self<>())
		.def(ObjectIdentityCheckVisitor<Base::DataFormat>())
		.add_property("numFileExtensions", &Base::DataFormat::getNumFileExtensions)
        .add_property("description", 
					  python::make_function(&Base::DataFormat::getDescription, 
											python::return_value_policy<python::copy_const_reference>()),
					  &Base::DataFormat::setDescription)    
		.add_property("name", 
					  python::make_function(&Base::DataFormat::getName, 
											python::return_value_policy<python::copy_const_reference>()),
					  &Base::DataFormat::setName)    
		.add_property("mimeType", 
					  python::make_function(&Base::DataFormat::getMimeType, 
											python::return_value_policy<python::copy_const_reference>()),
					  &Base::DataFormat::setMimeType)    
		.add_property("multiRecordFormat", &Base::DataFormat::isMultiRecordFormat, 
					  &Base::DataFormat::setMultiRecordFormat)    
		.add_property("fileExtensions", &getFileExtensions)
		.def("__ne__", &Base::DataFormat::operator!=, (python::arg("self"), python::arg("fmt")))    
        .def("__eq__", &Base::DataFormat::operator==, (python::arg("self"), python::arg("fmt")));

	python::class_<FileExtensionSequence>("FileExtensionSequence", python::no_init)
		.def("__len__", &FileExtensionSequence::getNumExtensions, python::arg("self"))
		.def("__getitem__", &FileExtensionSequence::getExtension, (python::arg("self"), python::arg("idx")), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("__delitem__", &FileExtensionSequence::removeExtension, (python::arg("self"), python::arg("idx")))
		.def("__setitem__", &FileExtensionSequence::setExtension, (python::arg("self"), python::arg("idx"), python::arg("file_ext")))
		.def("__contains__", &FileExtensionSequence::containsExtension, (python::arg("self"), python::arg("file_ext")));
}
