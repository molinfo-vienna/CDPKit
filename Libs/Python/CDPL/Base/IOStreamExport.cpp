/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * IOStreamExport.cpp 
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


#include <string>
#include <fstream>
#include <sstream>
#include <cstddef>

#include <boost/python.hpp>
#include <boost/python/ssize_t.hpp>

#include "CDPL/Base/Exceptions.hpp"

#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	template <typename IOStreamImpl>
	class IOStream : public IOStreamImpl
	{

	public:
		IOStream(const char* file_name, const std::string& mode_str, std::ios_base::openmode mode):        // constructor for std::fstream 
			IOStreamImpl(file_name, mode), closed(false), softSpace(false), 
			openModeString(mode_str), openModeFlags(mode) {}

		IOStream(const std::string& init_str, const std::string& mode_str, std::ios_base::openmode mode):  // constructor for std::stringstream 
			IOStreamImpl(init_str, mode), closed(false), softSpace(false),
			openModeString(mode_str), openModeFlags(mode) {}

		IOStream& getIterator() {
			return *this;
		}

		const std::string& nextLine() {
			checkIfClosed();
			checkIfReadOpAllowed();

			IOStreamImpl::clear();
			IOStreamImpl::tellg();

			getLine();

			if (data.empty()) {
				PyErr_SetString(PyExc_StopIteration, "");

				boost::python::throw_error_already_set();
			}

			return data;
		}

		const std::string& readLine(long max_count = -1) {
			checkIfClosed();
			checkIfReadOpAllowed();

			IOStreamImpl::clear();
			IOStreamImpl::tellg();

			if (max_count < 0) 
				return getLine();

			data.clear();

			char c;

			for (long i = 0; i < max_count && IOStreamImpl::get(c); i++) {
				data.push_back(c);

				if (c == '\n')
					break;
			}

			checkIfInBadState();

			return data;
		}

		boost::python::list readLines(long max_count = -1) {
			checkIfClosed();
			checkIfReadOpAllowed();

			boost::python::list lines;

			IOStreamImpl::clear();
			IOStreamImpl::tellg();

			if (max_count < 0) 
				for ( ; !getLine().empty(); lines.append(data));
			else
				for (long count = 0; count < max_count && !getLine().empty(); lines.append(data), count += data.size());

			return lines;
		}

		const std::string& readChars(long max_count = -1) {
			checkIfClosed();
			checkIfReadOpAllowed();

			data.clear();

			IOStreamImpl::clear();
			IOStreamImpl::tellg();

			char c;

			if (max_count < 0)
				for ( ; IOStreamImpl::get(c); data.push_back(c));
			else
				for (long i = 0; i < max_count && IOStreamImpl::get(c); data.push_back(c), i++);

			checkIfInBadState();

			return data;
		}

		void writeChars(PyObject* str) {
			using namespace boost;

			checkIfClosed();
			checkIfWriteOpAllowed();

			char* buf;
			python::ssize_t length;

			if (PyString_AsStringAndSize(str, &buf, &length) != 0) {
				PyErr_SetString(PyExc_TypeError, "IOStream: write() argument must be a string");

				python::throw_error_already_set();
			}

			IOStreamImpl::clear();
			IOStreamImpl::tellp();

			IOStreamImpl::write(buf, length);

			checkIfInGoodState();
		}

		void writeLines(PyObject* iterable) {
			using namespace boost;

			checkIfClosed();
			checkIfWriteOpAllowed();

			PyObject *iter = PyObject_GetIter(iterable);

			if (!iter) {
				PyErr_SetString(PyExc_TypeError, "IOStream: writelines() requires an iterable argument");

				boost::python::throw_error_already_set();
			}

			python::handle<> iter_handle(python::borrowed(iter)); Py_DECREF(iter);

			PyObject *item;

			IOStreamImpl::clear();
			IOStreamImpl::tellp();

			while ((item = PyIter_Next(iter))) {
				python::handle<> item_handle(python::borrowed(item)); Py_DECREF(item);

				char* buf;
				python::ssize_t length;

				if (PyString_AsStringAndSize(item, &buf, &length) != 0) {
					PyErr_SetString(PyExc_TypeError, "IOStream: argument to writelines() must be a sequence of strings");

					boost::python::throw_error_already_set();
				}

				IOStreamImpl::write(buf, length);

				checkIfInGoodState();
			}
		}

		void flushStream() {
			checkIfClosed();

			IOStreamImpl::flush();

			checkIfInBadState();
		}

		void closeStream() {
			closed = true;
		}

		bool isClosed() const {
			return closed;
		}

		const std::string& getOpenModeString() const {
			return openModeString;
		}

		std::ios_base::openmode getOpenModeFlags() const {
			return openModeFlags;
		}

		bool getSoftSpace() const {
			return softSpace;
		}

		void setSoftSpace(bool value) {
			softSpace = value;
		}

		std::size_t tellReadPos() {
			checkIfClosed();

			IOStreamImpl::clear();

			typename IOStreamImpl::pos_type pos = IOStreamImpl::tellg();

			if (pos == typename IOStreamImpl::pos_type(-1))
				throw CDPL::Base::IOError("IOStream: could not get file position");
				
			return std::size_t(pos);
		}

		std::size_t tellWritePos() {
			checkIfClosed();

			IOStreamImpl::clear();

			typename IOStreamImpl::pos_type pos = IOStreamImpl::tellp();

			if (pos == typename IOStreamImpl::pos_type(-1))
				throw CDPL::Base::IOError("IOStream: could not get file position");
				
			return std::size_t(pos);
		}

		void seekReadPos(typename IOStreamImpl::off_type offs, unsigned int whence = 0) {
			checkIfClosed();
	
			IOStreamImpl::clear();

			IOStreamImpl::seekg(offs, getSeekDir(whence));

			checkIfInGoodState();
		}

		void seekWritePos(typename IOStreamImpl::off_type offs, unsigned int whence = 0) {
			checkIfClosed();
	
			IOStreamImpl::clear();

			IOStreamImpl::seekp(offs, getSeekDir(whence));

			checkIfInGoodState();
		}

	protected:
		void checkIfClosed() const {
			if (!closed)
				return;
 
			throw CDPL::Base::ValueError("IOStream: operation on closed stream");
		}
 
		void checkIfWriteOpAllowed() const {
			if (openModeFlags & std::ios_base::out)
				return;

			throw CDPL::Base::IOError("IOStream: write operation not allowed");
		}
 
		void checkIfReadOpAllowed() const {
			if (openModeFlags & std::ios_base::in)
				return;

			throw CDPL::Base::IOError("IOStream: read operation not allowed");
		}
 
		void checkIfInBadState() const {
			if (!IOStreamImpl::bad())
				return;

			throw CDPL::Base::IOError("IOStream: stream in bad state");
		}

		void checkIfInGoodState() const {
			if (IOStreamImpl::good())
				return;

			throw CDPL::Base::IOError("IOStream: I/O operation failed");
		}

		static std::ios_base::openmode parseOpenModeFlags(const std::string& mode_str) {

			if (mode_str.find("r+b") == 0 || mode_str.find("rb+") == 0 || mode_str.find("br+") == 0) 
				return (std::ios_base::in | std::ios_base::out | std::ios_base::binary);

			if (mode_str.find("w+b") == 0 || mode_str.find("wb+") == 0 || mode_str.find("bw+") == 0) 
				return (std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
		
			if (mode_str.find("a+b") == 0 || mode_str.find("ab+") == 0 ||  mode_str.find("ba+") == 0) 
				return (std::ios_base::in | std::ios_base::out | std::ios_base::app | std::ios_base::binary);

			if (mode_str.find("rb") == 0 || mode_str.find("br") == 0) 
				return (std::ios_base::in | std::ios_base::binary);

			if (mode_str.find("wb") == 0 || mode_str.find("bw") == 0) 
				return (std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);
		
			if (mode_str.find("ab") == 0 || mode_str.find("ba") == 0) 
				return (std::ios_base::out | std::ios_base::app | std::ios_base::binary);

			if (mode_str.find("r+") == 0) 
				return (std::ios_base::in | std::ios_base::out);

			if (mode_str.find("w+") == 0) 
				return (std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
		
			if (mode_str.find("a+") == 0) 
				return (std::ios_base::in | std::ios_base::out | std::ios_base::app);

			if (mode_str.find("r") == 0) 
				return (std::ios_base::in);

			if (mode_str.find("w") == 0) 
				return (std::ios_base::out | std::ios_base::trunc);
		
			if (mode_str.find("a") == 0) 
				return (std::ios_base::out | std::ios_base::app);

			throw CDPL::Base::IOError("IOStream: invalid open mode " + mode_str);

			return std::ios_base::openmode(); // never reached, only to suppress compiler warnings
		} 

	private:
		static std::ios_base::seekdir getSeekDir(unsigned int whence) {
			if (whence > 2)
				throw CDPL::Base::IOError("IOStream: invalid argument");

			return (whence == 1 ? std::ios_base::cur : whence == 2 ? std::ios_base::end : std::ios_base::beg);
		}

		const std::string& getLine() {
			data.clear();

			std::getline(*this, data);

			checkIfInBadState();

			if (IOStreamImpl::good())
				data.push_back('\n');

			return data;
		}

		bool                    closed;
		bool                    softSpace;
		std::string             openModeString;
		std::ios_base::openmode openModeFlags;
		std::string             data;
	};

	class FileIOStream : public IOStream<std::fstream>, public boost::python::wrapper<IOStream<std::fstream> >
	{

	public:
		FileIOStream(const char* file_name, const std::string& mode_str): 
			IOStream<std::fstream>(file_name, mode_str, parseOpenModeFlags(mode_str)), fileName(file_name) {

			if (good())
				return;

			throw CDPL::Base::IOError("FileIOStream: could not open file");
		}

		FileIOStream(const char* file_name, std::ios_base::openmode mode): 
			IOStream<std::fstream>(file_name, "", mode), fileName(file_name) {
			
			if (good())
				return;

			throw CDPL::Base::IOError("FileIOStream: could not open file");
		}

		void closeFile() {
			close();
			closeStream();
		}

		const std::string& getFileName() const {
			return fileName;
		}
/*
		bool isATTY() const {
			checkIfClosed();

			int fd = ::open(fileName.c_str(), O_RDONLY);

			if (fd < 0)
				throw CDPL::Base::IOError("FileIOStream: could not open file");

			bool is_a_tty = isatty(fd);

			::close(fd);

			return is_a_tty;
		}

		void truncate(long new_length = -1) {
			std::size_t saved_fpos = tellWritePos();

			checkIfWriteOpAllowed();

			close();

			::truncate(fileName.c_str(), new_length < 0 ? ::off_t(saved_fpos) : ::off_t(new_length));

			open(fileName.c_str(), getOpenModeFlags());
			seekg(saved_fpos);

			checkIfInGoodState();
		}
*/
	private:
		std::string fileName;
	};

	class StringIOStream : public IOStream<std::stringstream>, public boost::python::wrapper<IOStream<std::stringstream> >
	{

	public:
		StringIOStream(const std::string& init_str, const std::string& mode_str): 
			IOStream<std::stringstream>(init_str, mode_str, parseOpenModeFlags(mode_str)) {}

		StringIOStream(const std::string& init_str, std::ios_base::openmode mode): 
			IOStream<std::stringstream>(init_str, "", mode) {}

		bool isATTY() const {
			checkIfClosed();

			return false;
		}

		void truncate(long new_length = -1) {
			std::size_t saved_fpos = tellWritePos();

			checkIfWriteOpAllowed();

			std::string value = str();

			value.resize(new_length < 0 ? std::string::size_type(saved_fpos) : std::string::size_type(new_length));

			str(value);

			checkIfInGoodState();
		}

		std::string getValue() const {
			checkIfClosed();

			return str();
		}

		void setValue(const std::string& value) {
			checkIfClosed();

			str(value);
		}
	};
}


void CDPLPythonBase::exportIOStreams()
{
	using namespace boost;

	python::class_<std::istream, boost::noncopyable>("IStream", python::no_init);
	python::class_<std::ostream, boost::noncopyable>("OStream", python::no_init);

	python::class_<std::iostream, python::bases<std::istream, std::ostream>, boost::noncopyable>("IOStream", python::no_init)
		.def(ObjectIdentityCheckVisitor<std::iostream>())
		.def_readonly("IN", std::ios_base::in)
		.def_readonly("OUT", std::ios_base::out)
		.def_readonly("TRUNC", std::ios_base::trunc)
		.def_readonly("APP", std::ios_base::app)
		.def_readonly("ATE", std::ios_base::ate)
		.def_readonly("BIN", std::ios_base::binary);

	python::class_<FileIOStream, python::bases<std::iostream>, boost::noncopyable>("FileIOStream", python::no_init)
		.def(python::init<const char*, const std::string&>((python::arg("self"), python::arg("file_name"), python::arg("mode") = "r")))
		.def(python::init<const char*, std::ios_base::openmode>((python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in)))
		.def("flush", &FileIOStream::flushStream, python::arg("self"))
		.def("close", &FileIOStream::closeFile, python::arg("self"))
		.def("readline", &FileIOStream::readLine, (python::arg("self"), python::arg("size") = -1), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("readlines", &FileIOStream::readLines, (python::arg("self"), python::arg("size") = -1))
		.def("xreadlines", &FileIOStream::getIterator, python::arg("self"), python::return_self<>())
		.def("read", &FileIOStream::readChars, (python::arg("self"), python::arg("size") = -1), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("write", &FileIOStream::writeChars, (python::arg("self"), python::arg("string")))
		.def("writelines", &FileIOStream::writeLines, (python::arg("self"), python::arg("iterable")))
//		.def("isatty", &FileIOStream::isATTY, python::arg("self"))
//		.def("truncate", &FileIOStream::truncate, (python::arg("self"), python::arg("length") = -1))
		.def("tell", &FileIOStream::tellReadPos, python::arg("self"))
		.def("tellr", &FileIOStream::tellReadPos, python::arg("self"))
		.def("tellw", &FileIOStream::tellWritePos, python::arg("self"))
		.def("seek", &FileIOStream::seekReadPos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
		.def("seekr", &FileIOStream::seekReadPos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
		.def("seekw", &FileIOStream::seekWritePos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
		.def("next", &FileIOStream::nextLine, python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.add_property("softspace", &FileIOStream::getSoftSpace, &FileIOStream::setSoftSpace)
		.add_property("closed", &FileIOStream::isClosed)
		.add_property("name", python::make_function(&FileIOStream::getFileName, 
													python::return_value_policy<python::copy_const_reference>()))
		.add_property("mode", python::make_function(&FileIOStream::getOpenModeString, 
													python::return_value_policy<python::copy_const_reference>()))
		.add_property("modeFlags", &FileIOStream::getOpenModeFlags)
		.def("__iter__", &FileIOStream::getIterator, python::arg("self"), python::return_self<>());

	python::class_<StringIOStream, python::bases<std::iostream>, boost::noncopyable>("StringIOStream", python::no_init)
		.def(python::init<const std::string&, const std::string&>((python::arg("self"), python::arg("string") = "", python::arg("mode") = "r+")))
		.def(python::init<const std::string&, std::ios_base::openmode>((python::arg("self"), python::arg("string") = "", python::arg("mode") = std::ios_base::in | std::ios_base::out)))
		.def("flush", &StringIOStream::flushStream, python::arg("self"))
		.def("close", &StringIOStream::closeStream, python::arg("self"))
		.def("readline", &StringIOStream::readLine, (python::arg("self"), python::arg("size") = -1), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("readlines", &StringIOStream::readLines, (python::arg("self"), python::arg("size") = -1))
		.def("xreadlines", &StringIOStream::getIterator, python::arg("self"), python::return_self<>())
		.def("read", &StringIOStream::readChars, (python::arg("self"), python::arg("size") = -1), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("write", &StringIOStream::writeChars, (python::arg("self"), python::arg("string")))
		.def("writelines", &StringIOStream::writeLines, (python::arg("self"), python::arg("iterable")))
		.def("isatty", &StringIOStream::isATTY, python::arg("self"))
		.def("truncate", &StringIOStream::truncate, (python::arg("self"), python::arg("length") = -1))
		.def("getvalue", &StringIOStream::getValue, python::arg("self"))
		.def("setvalue", &StringIOStream::setValue, (python::arg("self"), python::arg("value")))
		.def("tellr", &StringIOStream::tellReadPos, python::arg("self"))
		.def("tellw", &StringIOStream::tellWritePos, python::arg("self"))
		.def("seekr", &StringIOStream::seekReadPos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
		.def("seekw", &StringIOStream::seekWritePos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
		.def("next", &StringIOStream::nextLine, python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.add_property("value", &StringIOStream::getValue, &StringIOStream::setValue)
		.add_property("softspace", &StringIOStream::getSoftSpace, &StringIOStream::setSoftSpace)
		.add_property("closed", &StringIOStream::isClosed)
		.add_property("mode", python::make_function(&StringIOStream::getOpenModeString, 
													python::return_value_policy<python::copy_const_reference>()))
		.add_property("modeFlags", &StringIOStream::getOpenModeFlags)
		.def("__iter__", &StringIOStream::getIterator, python::arg("self"), python::return_self<>());
}
