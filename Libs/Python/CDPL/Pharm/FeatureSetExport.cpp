/* 
 * FragmentExport.cpp 
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

#include "CDPL/Pharm/FeatureSet.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "FeatureContainerVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

    bool addFeature(CDPL::Pharm::FeatureSet& ftr_set, CDPL::Pharm::Feature& ftr)
    {
        return ftr_set.addFeature(ftr);
    }

    bool removeFeature(CDPL::Pharm::FeatureSet& ftr_set, CDPL::Pharm::Feature& ftr)
    {
        return ftr_set.removeFeature(ftr);
    }
}


void CDPLPythonPharm::exportFeatureSet()
{
    using namespace boost;
    using namespace CDPL;

    void (Pharm::FeatureSet::*removeFeatureFunc)(std::size_t) = &Pharm::FeatureSet::removeFeature;

    Pharm::FeatureSet& (Pharm::FeatureSet::*copyFtrContainerFunc)(const Pharm::FeatureContainer&) = &Pharm::FeatureSet::operator=;
    Pharm::FeatureSet& (Pharm::FeatureSet::*copyFtrSetFunc)(const Pharm::FeatureSet&) = &Pharm::FeatureSet::operator=;

    python::scope scope = python::class_<Pharm::FeatureSet, Pharm::FeatureSet::SharedPointer, 
                                         python::bases<Pharm::FeatureContainer> >("FeatureSet", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Pharm::FeatureSet&>((python::arg("self"), python::arg("ftr_set")))
             [python::with_custodian_and_ward<1, 2>()])
        .def(python::init<const Pharm::FeatureContainer&>((python::arg("self"), python::arg("cntnr")))
             [python::with_custodian_and_ward<1, 2>()])
        .def("assign", copyFtrSetFunc, (python::arg("self"), python::arg("ftr_set")),
             python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("assign", copyFtrContainerFunc, (python::arg("self"), python::arg("cntnr")),
             python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("addFeature", &addFeature, (python::arg("self"), python::arg("ftr")),
             python::with_custodian_and_ward<1, 2>())
        .def("removeFeature", removeFeatureFunc, (python::arg("self"), python::arg("idx")))
        .def("removeFeature", &removeFeature, (python::arg("self"), python::arg("ftr")))
        .def("clear", &Pharm::FeatureSet::clear, python::arg("self"))
        .def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
        .def(FeatureContainerSpecialFunctionsVisitor(false))
        .def("__iadd__", &Pharm::FeatureSet::operator+=, (python::arg("self"), python::arg("cntnr")), 
             python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("__isub__", &Pharm::FeatureSet::operator-=, (python::arg("self"), python::arg("cntnr")), 
             python::return_self<>());
}

