/* 
 * RDFReactionWriterExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Chem/RDFReactionWriter.hpp"
#include "CDPL/Chem/RDFGZReactionWriter.hpp"
#include "CDPL/Chem/RDFBZ2ReactionWriter.hpp"
#include "CDPL/Util/FileDataWriter.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportRDFReactionWriter()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::RDFReactionWriter, python::bases<Base::DataWriter<Chem::Reaction> >,
        boost::noncopyable>("RDFReactionWriter", python::no_init)
        .def(python::init<std::ostream&>((python::arg("self"), python::arg("os")))
             [python::with_custodian_and_ward<1, 2>()]);

    python::class_<Util::FileDataWriter<Chem::RDFReactionWriter>, python::bases<Base::DataWriter<Chem::Reaction> >, 
        boost::noncopyable>("FileRDFReactionWriter", python::no_init)
        .def(python::init<const std::string&, std::ios_base::openmode>(
                 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
                  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

    python::class_<Chem::RDFGZReactionWriter, python::bases<Base::DataWriter<Chem::Reaction> >, 
        boost::noncopyable>("RDFGZReactionWriter", python::no_init)
        .def(python::init<std::iostream&>((python::arg("self"), python::arg("ios")))
             [python::with_custodian_and_ward<1, 2>()]);

    python::class_<Util::FileDataWriter<Chem::RDFGZReactionWriter>, python::bases<Base::DataWriter<Chem::Reaction> >, 
        boost::noncopyable>("FileRDFGZReactionWriter", python::no_init)
        .def(python::init<const std::string&, std::ios_base::openmode>(
                 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
                  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));

    python::class_<Chem::RDFBZ2ReactionWriter, python::bases<Base::DataWriter<Chem::Reaction> >, 
        boost::noncopyable>("RDFBZ2ReactionWriter", python::no_init)
        .def(python::init<std::iostream&>((python::arg("self"), python::arg("ios")))
             [python::with_custodian_and_ward<1, 2>()]);

    python::class_<Util::FileDataWriter<Chem::RDFBZ2ReactionWriter>, python::bases<Base::DataWriter<Chem::Reaction> >, 
        boost::noncopyable>("FileRDFBZ2ReactionWriter", python::no_init)
        .def(python::init<const std::string&, std::ios_base::openmode>(
                 (python::arg("self"), python::arg("file_name"), python::arg("mode") = 
                  std::ios_base::in | std::ios_base::out | std::ios_base::trunc | std::ios_base::binary)));
}
