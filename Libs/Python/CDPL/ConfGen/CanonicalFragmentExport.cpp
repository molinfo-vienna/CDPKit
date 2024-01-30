/* 
 * CanonicalFragmentExport.cpp 
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

#include "CDPL/ConfGen/CanonicalFragment.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct AtomMapping
    {

        AtomMapping(const CDPL::ConfGen::CanonicalFragment& frag): frag(frag) {}

        std::size_t getNumAtoms() const {
            return frag.getAtomMapping().size();
        }

        const CDPL::Chem::Atom& getAtom(std::size_t idx) const {
            if (idx >= frag.getAtomMapping().size())
                throw CDPL::Base::IndexError("CanonicalFragment.AtomMapping: index out of bounds");

            return *frag.getAtomMapping()[idx];
        }

        const CDPL::ConfGen::CanonicalFragment& frag;
    };

    AtomMapping getAtomMapping(CDPL::ConfGen::CanonicalFragment& frag)
    {
        return AtomMapping(frag);
    }

    struct AtomMappingExport
    {

        AtomMappingExport(const char* name) {
            using namespace boost;

            python::class_<AtomMapping>(name, python::no_init)
                .def("__len__", &AtomMapping::getNumAtoms, python::arg("self"))
                .def("__getitem__", &AtomMapping::getAtom, (python::arg("self"), python::arg("idx")), 
                     python::return_internal_reference<1>());
        }
    };
}


void CDPLPythonConfGen::exportCanonicalFragment()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ConfGen::CanonicalFragment, ConfGen::CanonicalFragment::SharedPointer, 
                   python::bases<Chem::MolecularGraph>, boost::noncopyable> cl("CanonicalFragment", python::no_init);

    python::scope scope = cl;
  
    python::class_<AtomMapping>("AtomMapping", python::no_init)
        .def("__len__", &AtomMapping::getNumAtoms, python::arg("self"))
        .def("__getitem__", &AtomMapping::getAtom, (python::arg("self"), python::arg("idx")), 
             python::return_internal_reference<1>());

    cl
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Chem::MolecularGraph&, const Chem::MolecularGraph&>(
            (python::arg("self"), python::arg("molgraph"), python::arg("parent"))))
        .def(python::init<const ConfGen::CanonicalFragment&>((python::arg("self"), python::arg("frag"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::CanonicalFragment>())
        .def("assign", &ConfGen::CanonicalFragment::operator=, (python::arg("self"), python::arg("frag")),
             python::return_self<>())
        .def("create", &ConfGen::CanonicalFragment::create,
             (python::arg("self"), python::arg("molgraph"), python::arg("parent"),
              python::arg("modify") = true, python::arg("strip_aro_subst") = true))
        .def("getHashCode", &ConfGen::CanonicalFragment::getHashCode, python::arg("self"))
        .def("clear", &ConfGen::CanonicalFragment::clear, python::arg("self"))
        .def("getAtomMapping", &getAtomMapping, python::arg("self"), python::with_custodian_and_ward_postcall<0, 1>())
        .add_property("hashCode", &ConfGen::CanonicalFragment::getHashCode)
        .add_property("atomMapping", python::make_function(&getAtomMapping,
                                                           python::with_custodian_and_ward_postcall<0, 1>()));
}
