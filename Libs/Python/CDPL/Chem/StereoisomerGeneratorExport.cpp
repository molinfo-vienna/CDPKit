/* 
 * StereoisomerGeneratorExport.cpp 
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

#include "CDPL/Chem/StereoisomerGenerator.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Util/ArrayVisitor.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    const CDPL::Chem::StereoDescriptor& getItem(const CDPL::Chem::StereoisomerGenerator::StereoDescriptorArray& array, std::size_t idx)
    {
        CHECK_ARRAY_INDEX(array, idx, false);
        
        return array.getElement(idx);
    }
}


void CDPLPythonChem::exportStereoisomerGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::StereoisomerGenerator, Chem::StereoisomerGenerator::SharedPointer,
                   boost::noncopyable> cl("StereoisomerGenerator", python::no_init);

    python::scope scope = cl;

    typename Chem::StereoDescriptor& (Chem::StereoisomerGenerator::StereoDescriptorArray::*getElementFunc)(std::size_t) =
        &Chem::StereoisomerGenerator::StereoDescriptorArray::getElement;
  
    python::class_<Chem::StereoisomerGenerator::StereoDescriptorArray,
                   boost::noncopyable>("StereoDescriptorArray", python::no_init)
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::StereoisomerGenerator::StereoDescriptorArray>())
        .def("getSize", &Chem::StereoisomerGenerator::StereoDescriptorArray::getSize, python::arg("self"))
        .def("isEmpty", &Chem::StereoisomerGenerator::StereoDescriptorArray::isEmpty, python::arg("self"))
        .def("getElement", getElementFunc, (python::arg("self"), python::arg("idx")),
             python::return_internal_reference<>())
        .def("__getitem__", &getItem, (python::arg("self"), python::arg("idx")),
             python::return_internal_reference<>())
        .def("__len__", &Chem::StereoisomerGenerator::StereoDescriptorArray::getSize, python::arg("self"))
        .add_property("size", &Chem::StereoisomerGenerator::StereoDescriptorArray::getSize);

    cl
        .def(python::init<>(python::arg("self")))
        .def(python::init<Chem::StereoisomerGenerator>((python::arg("self"), python::arg("gen"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::StereoisomerGenerator>())
        .def("assign", CDPLPythonBase::copyAssOp<Chem::StereoisomerGenerator>(),
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("setAtomPredicate", &Chem::StereoisomerGenerator::setAtomPredicate,
             (python::arg("self"), python::arg("pred")))
        .def("getAtomPredicate", &Chem::StereoisomerGenerator::getAtomPredicate,
             python::arg("self"), python::return_internal_reference<>())
        .def("setBondPredicate", &Chem::StereoisomerGenerator::setBondPredicate,
             (python::arg("self"), python::arg("pred")))
        .def("getBondPredicate", &Chem::StereoisomerGenerator::getBondPredicate,
             python::arg("self"), python::return_internal_reference<>())
        .def("enumerateAtomConfig", &Chem::StereoisomerGenerator::enumerateAtomConfig,
             (python::arg("self"), python::arg("enumerate")))
        .def("atomConfigEnumerated", &Chem::StereoisomerGenerator::atomConfigEnumerated,
             python::arg("self"))
        .def("enumerateBondConfig", &Chem::StereoisomerGenerator::enumerateBondConfig,
             (python::arg("self"), python::arg("enumerate")))
        .def("bondConfigEnumerated", &Chem::StereoisomerGenerator::bondConfigEnumerated,
             python::arg("self"))
        .def("includeSpecifiedCenters", &Chem::StereoisomerGenerator::includeSpecifiedCenters,
             (python::arg("self"), python::arg("include")))
        .def("specifiedCentersIncluded", &Chem::StereoisomerGenerator::specifiedCentersIncluded,
             python::arg("self"))
        .def("includeSymmetricCenters", &Chem::StereoisomerGenerator::includeSymmetricCenters,
             (python::arg("self"), python::arg("include")))
        .def("symmetricCentersIncluded", &Chem::StereoisomerGenerator::symmetricCentersIncluded,
             python::arg("self"))
        .def("includeBridgeheadAtoms", &Chem::StereoisomerGenerator::includeBridgeheadAtoms,
             (python::arg("self"), python::arg("include")))
        .def("bridgeheadAtomsIncluded", &Chem::StereoisomerGenerator::bridgeheadAtomsIncluded,
             python::arg("self"))
        .def("includeNitrogens", &Chem::StereoisomerGenerator::includeNitrogens,
             (python::arg("self"), python::arg("include")))
        .def("nitrogensIncluded", &Chem::StereoisomerGenerator::nitrogensIncluded,
             python::arg("self"))
        .def("includeRingBonds", &Chem::StereoisomerGenerator::includeRingBonds,
             (python::arg("self"), python::arg("include")))
        .def("ringBondsIncluded", &Chem::StereoisomerGenerator::ringBondsIncluded,
             python::arg("self"))
        .def("setMinRingSize", &Chem::StereoisomerGenerator::setMinRingSize,
             (python::arg("self"), python::arg("min_size")))
        .def("getMinRingSize", &Chem::StereoisomerGenerator::getMinRingSize,
             python::arg("self"))
        .def("setup", &Chem::StereoisomerGenerator::setup,
             (python::arg("self"), python::arg("molgraph")))
        .def("generate", &Chem::StereoisomerGenerator::generate, python::arg("self"))
        .def("getAtomDescriptors", &Chem::StereoisomerGenerator::getAtomDescriptors, python::arg("self"),
             python::return_internal_reference<>())
        .def("getBondDescriptors", &Chem::StereoisomerGenerator::getBondDescriptors, python::arg("self"),
             python::return_internal_reference<>())
        .add_property("atomPredicate", python::make_function(&Chem::StereoisomerGenerator::getAtomPredicate,
                                                             python::return_internal_reference<>()),
                      &Chem::StereoisomerGenerator::setAtomPredicate)
        .add_property("bondPredicate", python::make_function(&Chem::StereoisomerGenerator::getBondPredicate,
                                                             python::return_internal_reference<>()),
                      &Chem::StereoisomerGenerator::setBondPredicate)
        .add_property("enumAtomConfig", &Chem::StereoisomerGenerator::atomConfigEnumerated,
             &Chem::StereoisomerGenerator::enumerateAtomConfig)
        .add_property("enumBondConfig", &Chem::StereoisomerGenerator::bondConfigEnumerated,
             &Chem::StereoisomerGenerator::enumerateBondConfig)
        .add_property("incSpecifiedCenters", &Chem::StereoisomerGenerator::specifiedCentersIncluded,
             &Chem::StereoisomerGenerator::includeSpecifiedCenters)
        .add_property("incSymmetricCenters", &Chem::StereoisomerGenerator::symmetricCentersIncluded,
             &Chem::StereoisomerGenerator::includeSymmetricCenters)
        .add_property("incBridgeheadAtoms", &Chem::StereoisomerGenerator::bridgeheadAtomsIncluded,
             &Chem::StereoisomerGenerator::includeBridgeheadAtoms)
        .add_property("incNitrogens", &Chem::StereoisomerGenerator::nitrogensIncluded,
             &Chem::StereoisomerGenerator::includeNitrogens)
        .add_property("incRingBonds", &Chem::StereoisomerGenerator::ringBondsIncluded,
             &Chem::StereoisomerGenerator::includeRingBonds)
        .add_property("minRingSize", &Chem::StereoisomerGenerator::getMinRingSize,
             &Chem::StereoisomerGenerator::setMinRingSize)
        .add_property("atomDescriptors", python::make_function(&Chem::StereoisomerGenerator::getAtomDescriptors,
                                                               python::return_internal_reference<>()))
        .add_property("bondDescriptors", python::make_function(&Chem::StereoisomerGenerator::getBondDescriptors,
                                                               python::return_internal_reference<>()));
}
