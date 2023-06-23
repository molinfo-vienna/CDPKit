/* 
 * IOStream.hpp 
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


#ifndef CDPL_PYTHON_BASE_IOSTREAM_HPP
#define CDPL_PYTHON_BASE_IOSTREAM_HPP

#include <string>
#include <cstddef>

#include <boost/python.hpp>
#include <boost/python/ssize_t.hpp>

#include "CDPL/Base/Exceptions.hpp"



namespace CDPLPythonBase
{

	template <typename IOStreamImpl>
	class IOStream : virtual public IOStreamImpl
	{

	public:
		IOStream(const std::string& mode_str, std::ios_base::openmode mode):
			closed(false), softSpace(false), openModeString(mode_str), openModeFlags(mode) {}

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

			if (PyBytes_AsStringAndSize(str, &buf, &length) != 0) {
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

				if (PyBytes_AsStringAndSize(item, &buf, &length) != 0) {
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

			checkIfInGoodState();

			return std::size_t(pos);
		}

		std::size_t tellWritePos() {
			checkIfClosed();

			IOStreamImpl::clear();

			typename IOStreamImpl::pos_type pos = IOStreamImpl::tellp();

			if (pos == typename IOStreamImpl::pos_type(-1))
				throw CDPL::Base::IOError("IOStream: could not get file position");

			checkIfInGoodState();

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
		void closeStream() {
			closed = true;
		}

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

	template <typename StreamType>
	class IStreamVisitor : public boost::python::def_visitor<IStreamVisitor<StreamType> >
	{

		friend class boost::python::def_visitor_access;

	private:
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl	
				.def("readline", &StreamType::readLine, (python::arg("self"), python::arg("size") = -1), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("readlines", &StreamType::readLines, (python::arg("self"), python::arg("size") = -1))
				.def("xreadlines", &StreamType::getIterator, python::arg("self"), python::return_self<>())
				.def("read", &StreamType::readChars, (python::arg("self"), python::arg("size") = -1), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("tell", &StreamType::tellReadPos, python::arg("self"))
				.def("tellr", &StreamType::tellReadPos, python::arg("self"))
				.def("seek", &StreamType::seekReadPos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
				.def("seekr", &StreamType::seekReadPos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
				.def("next", &StreamType::nextLine, python::arg("self"), python::return_value_policy<python::copy_const_reference>())
				.add_property("closed", &StreamType::isClosed)
				.add_property("mode", python::make_function(&StreamType::getOpenModeString, 
															python::return_value_policy<python::copy_const_reference>()))
				.add_property("modeFlags", &StreamType::getOpenModeFlags)
				.def("__iter__", &StreamType::getIterator, python::arg("self"), python::return_self<>());
		}
	};

	template <typename StreamType>
	class OStreamVisitor : public boost::python::def_visitor<OStreamVisitor<StreamType> >
	{

		friend class boost::python::def_visitor_access;

	private:
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;

			cl	
				.def("flush", &StreamType::flushStream, python::arg("self"))
			
				.def("write", &StreamType::writeChars, (python::arg("self"), python::arg("string")))
				.def("writelines", &StreamType::writeLines, (python::arg("self"), python::arg("iterable")))
			
				.def("tellw", &StreamType::tellWritePos, python::arg("self"))
			
				.def("seekw", &StreamType::seekWritePos, (python::arg("self"), python::arg("offs"), python::arg("whence") = 0))
				.add_property("closed", &StreamType::isClosed)
				.add_property("softspace", &StreamType::getSoftSpace, &StreamType::setSoftSpace)
				.add_property("mode", python::make_function(&StreamType::getOpenModeString, 
															python::return_value_policy<python::copy_const_reference>()))
				.add_property("modeFlags", &StreamType::getOpenModeFlags);
			
		}
	};
}

#endif // CDPL_PYTHON_BASE_IOSTREAM_HPP
