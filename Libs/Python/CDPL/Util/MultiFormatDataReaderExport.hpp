/* 
 * MultiFormatDataReaderExport.hpp 
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


#ifndef CDPL_PYTHON_UTIL_MULTIFORMATDATAREADEREXPORT_HPP
#define CDPL_PYTHON_UTIL_MULTIFORMATDATAREADEREXPORT_HPP

#include <boost/python.hpp>

#include "CDPL/Util/MultiFormatDataReader.hpp"


namespace CDPLPythonUtil
{

    template <typename T>
    struct MultiFormatDataReaderExport
    {

        MultiFormatDataReaderExport(const char* name)
        {
            using namespace boost;
            using namespace CDPL;

            typedef Util::MultiFormatDataReader<T> ReaderType;

            python::class_<ReaderType, typename Util::MultiFormatDataReader<T>::SharedPointer,
                           python::bases<Base::DataReader<T> >, boost::noncopyable>(name, python::no_init)
                .def(python::init<const std::string&, std::ios_base::openmode>(
                    (python::arg("self"), python::arg("file_name"),
                     python::arg("mode") = std::ios_base::in | std::ios_base::binary)))
                .def(python::init<const std::string&, const std::string&, std::ios_base::openmode>(
                    (python::arg("self"), python::arg("file_name"), python::arg("fmt"),
                     python::arg("mode") = std::ios_base::in | std::ios_base::binary)))
                .def(python::init<const std::string&, const Base::DataFormat&, std::ios_base::openmode>(
                    (python::arg("self"), python::arg("file_name"), python::arg("fmt"),
                     python::arg("mode") = std::ios_base::in | std::ios_base::binary)))
                .def(python::init<std::istream&, const std::string&>(
                    (python::arg("self"), python::arg("is"), python::arg("fmt"))))
                .def(python::init<std::istream&, const Base::DataFormat&>(
                    (python::arg("self"), python::arg("is"), python::arg("fmt"))))
                .def("getDataFormat", &ReaderType::getDataFormat, python::arg("self"),
                     python::return_internal_reference<>())
                .add_property("dataFormat",
                              python::make_function(&ReaderType::getDataFormat,
                                                    python::return_internal_reference<>()));
        }
    };
} // namespace CDPLPythonUtil

#endif // CDPL_PYTHON_UTIL_MULTIFORMATDATAREADEREXPORT_HPP
