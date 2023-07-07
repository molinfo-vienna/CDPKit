/* 
 * BasicReactionExport.cpp 
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


#include <sstream>

#include <boost/python.hpp>

#include "CDPL/Chem/BasicReaction.hpp"
#include "CDPL/Chem/CDFReactionWriter.hpp"
#include "CDPL/Chem/CDFReactionReader.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "ClassExports.hpp"


namespace
{

    struct BasicReactionPickleSuite : boost::python::pickle_suite
    {

        static boost::python::tuple
        getstate(boost::python::object obj)
        {
            using namespace boost;
            using namespace CDPL;

            std::ostringstream os(std::ios_base::binary | std::ios_base::out);

            if (!Chem::CDFReactionWriter(os).write(python::extract<const Chem::BasicReaction&>(obj)))
                throw Base::IOError("BasicReactionPickleSuite: writing CDF data record failed");
            
            return python::make_tuple(obj.attr("__dict__"), os.str());
        }

        static void
        setstate(boost::python::object obj, boost::python::tuple state)
        {
            using namespace boost;
            using namespace CDPL;

            python::extract<python::dict>(obj.attr("__dict__"))().update(state[0]);

            std::istringstream is(python::extract<std::string>(state[1]), std::ios_base::binary | std::ios_base::in);
            
            if (!Chem::CDFReactionReader(is).read(python::extract<Chem::BasicReaction&>(obj)))
                throw Base::IOError("BasicReactionPickleSuite: reading CDF data record failed");
        }

        static bool getstate_manages_dict() { return true; }
    };
} // namespace


void CDPLPythonChem::exportBasicReaction()
{
    using namespace boost;
    using namespace CDPL;

    Chem::BasicMolecule& (Chem::BasicReaction::*addComponentFunc)(unsigned int) = &Chem::BasicReaction::addComponent;
    Chem::BasicMolecule& (Chem::BasicReaction::*addComponentCopyFunc)(unsigned int, const Chem::Molecule&) = &Chem::BasicReaction::addComponent;

    void (Chem::BasicReaction::*copyBasicRxnFunc)(const Chem::BasicReaction&) = &Chem::BasicReaction::copy;
    void (Chem::BasicReaction::*copyRxnFunc)(const Chem::Reaction&) = &Chem::BasicReaction::copy;

    Chem::BasicReaction& (Chem::BasicReaction::*assignBasicRxnFunc)(const Chem::BasicReaction&) = &Chem::BasicReaction::operator=;
    Chem::Reaction& (Chem::Reaction::*assignRxnFunc)(const Chem::Reaction&) = &Chem::Reaction::operator=;

    python::class_<Chem::BasicReaction, Chem::BasicReaction::SharedPointer,
                   python::bases<Chem::Reaction> >("BasicReaction", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::BasicReaction&>((python::arg("self"), python::arg("mol"))))
        .def(python::init<const Chem::Reaction&>((python::arg("self"), python::arg("mol"))))
        .def_pickle(BasicReactionPickleSuite())
        .def("addComponent", addComponentFunc, (python::arg("self"), python::arg("role")),
             python::return_internal_reference<1>())
        .def("addComponent", addComponentCopyFunc, (python::arg("self"), python::arg("role"), python::arg("mol")),
             python::return_internal_reference<1>())
        .def("copy", copyBasicRxnFunc, (python::arg("self"), python::arg("rxn")))
        .def("copy", copyRxnFunc, (python::arg("self"), python::arg("rxn")))
        .def("assign", assignBasicRxnFunc, (python::arg("self"), python::arg("rxn")),
             python::return_self<>())
        .def("assign", assignRxnFunc, (python::arg("self"), python::arg("rxn")),
             python::return_self<>());
}
