/* 
 * IOStreamExport.cpp 
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


#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/python.hpp>

#include "CDPL/Base/Exceptions.hpp"

#include "IOStream.hpp"
#include "ObjectIdentityCheckVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

    class FileIOStream : public CDPLPythonBase::IOStream<std::fstream>, 
                         public boost::python::wrapper<CDPLPythonBase::IOStream<std::fstream> >
    {

    public:
        FileIOStream(const char* file_name, const std::string& mode_str): 
            std::fstream(file_name, parseOpenModeFlags(mode_str)), 
            CDPLPythonBase::IOStream<std::fstream>(mode_str, parseOpenModeFlags(mode_str)), fileName(file_name) {

            if (good())
                return;

            throw CDPL::Base::IOError("FileIOStream: could not open file");
        }

        FileIOStream(const char* file_name, std::ios_base::openmode mode): 
            std::fstream(file_name, mode), 
            CDPLPythonBase::IOStream<std::fstream>("", mode), fileName(file_name) {
            
            if (good())
                return;

            throw CDPL::Base::IOError("FileIOStream: could not open file");
        }

        void close() {
            std::fstream::close();

            if (!good())
                throw CDPL::Base::IOError("FileIOStream: could not close file");

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

    class StringIOStream : public CDPLPythonBase::IOStream<std::stringstream>, 
                           public boost::python::wrapper<CDPLPythonBase::IOStream<std::stringstream> >
    {

    public:
        StringIOStream(const std::string& init_str, const std::string& mode_str): 
            std::stringstream(init_str, parseOpenModeFlags(mode_str)), 
            CDPLPythonBase::IOStream<std::stringstream>(mode_str, parseOpenModeFlags(mode_str)) {}

        StringIOStream(const std::string& init_str, std::ios_base::openmode mode): 
            std::stringstream(init_str, mode), IOStream<std::stringstream>("", mode) {}

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

    python::class_<std::istream, boost::noncopyable>("IStream", python::no_init)
        .def(ObjectIdentityCheckVisitor<std::istream>())
        .def_readonly("STD_IN", &std::cin);

    python::class_<std::ostream, boost::noncopyable>("OStream", python::no_init)
        .def(ObjectIdentityCheckVisitor<std::ostream>())
        .def_readonly("STD_OUT", &std::cout)
        .def_readonly("STD_ERR", &std::cerr);

    {
        python::scope scope = python::class_<std::iostream, python::bases<std::istream, std::ostream>, boost::noncopyable>("IOStream", python::no_init);

        python::enum_<std::ios_base::openmode>("OpenMode")
            .value("IN", std::ios_base::in)
            .value("OUT", std::ios_base::out)
            .value("TRUNC", std::ios_base::trunc)
            .value("APP", std::ios_base::app)
            .value("ATE", std::ios_base::ate)
            .value("BIN", std::ios_base::binary)
            .export_values();
    }

    python::class_<FileIOStream, python::bases<std::iostream>, boost::noncopyable>("FileIOStream", python::no_init)
        .def(python::init<const char*, const std::string&>((python::arg("self"), python::arg("file_name"), python::arg("mode") = "r")))
        .def(python::init<const char*, std::ios_base::openmode>((python::arg("self"), python::arg("file_name"), python::arg("mode") = std::ios_base::in)))
        .def(IStreamVisitor<FileIOStream>())
        .def(OStreamVisitor<FileIOStream>())
        .def("close", &FileIOStream::close, python::arg("self"))
        .add_property("name", python::make_function(&FileIOStream::getFileName, 
                                                    python::return_value_policy<python::copy_const_reference>()));

    python::class_<StringIOStream, python::bases<std::iostream>, boost::noncopyable>("StringIOStream", python::no_init)
        .def(python::init<const std::string&, const std::string&>((python::arg("self"), python::arg("string") = "", python::arg("mode") = "r+")))
        .def(python::init<const std::string&, std::ios_base::openmode>((python::arg("self"), python::arg("string") = "", python::arg("mode") = std::ios_base::in | std::ios_base::out)))
        .def(IStreamVisitor<StringIOStream>())
        .def(OStreamVisitor<StringIOStream>())
        .def("isatty", &StringIOStream::isATTY, python::arg("self"))
        .def("truncate", &StringIOStream::truncate, (python::arg("self"), python::arg("length") = -1))
        .def("getvalue", &StringIOStream::getValue, python::arg("self"))
        .def("setvalue", &StringIOStream::setValue, (python::arg("self"), python::arg("value")))
        //.def("close", &StringIOStream::closeStream, python::arg("self"))
        .add_property("value", &StringIOStream::getValue, &StringIOStream::setValue);
}
