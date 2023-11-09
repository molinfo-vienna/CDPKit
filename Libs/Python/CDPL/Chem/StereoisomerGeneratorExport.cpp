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
        .def("enumerateAtomCenters", &Chem::StereoisomerGenerator::enumerateAtomCenters,
             (python::arg("self"), python::arg("enumerate")))
        .def("atomCentersEnumerated", &Chem::StereoisomerGenerator::atomCentersEnumerated,
             python::arg("self"))
        .def("enumerateBondCenters", &Chem::StereoisomerGenerator::enumerateBondCenters,
             (python::arg("self"), python::arg("enumerate")))
        .def("bondCentersEnumerated", &Chem::StereoisomerGenerator::bondCentersEnumerated,
             python::arg("self"))
        .def("enumerateSpecifiedCenters", &Chem::StereoisomerGenerator::enumerateSpecifiedCenters,
             (python::arg("self"), python::arg("enumerate")))
        .def("specifiedCentersEnumerated", &Chem::StereoisomerGenerator::specifiedCentersEnumerated,
             python::arg("self"))
        .def("enumerateSymmetricCenters", &Chem::StereoisomerGenerator::enumerateSymmetricCenters,
             (python::arg("self"), python::arg("enumerate")))
        .def("symmetricCentersEnumerated", &Chem::StereoisomerGenerator::symmetricCentersEnumerated,
             python::arg("self"))
        .def("excludeBridgeheadAtoms", &Chem::StereoisomerGenerator::excludeBridgeheadAtoms,
             (python::arg("self"), python::arg("exclude")))
        .def("bridgeheadAtomsExcluded", &Chem::StereoisomerGenerator::bridgeheadAtomsExcluded,
             python::arg("self"))
        .def("excludeNitrogens", &Chem::StereoisomerGenerator::excludeNitrogens,
             (python::arg("self"), python::arg("exclude")))
        .def("nitrogensExcluded", &Chem::StereoisomerGenerator::nitrogensExcluded,
             python::arg("self"))
        .def("excludeRingBonds", &Chem::StereoisomerGenerator::excludeRingBonds,
             (python::arg("self"), python::arg("exclude")))
        .def("ringBondsExcluded", &Chem::StereoisomerGenerator::ringBondsExcluded,
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
        .add_property("enumAtomCenters", &Chem::StereoisomerGenerator::atomCentersEnumerated,
             &Chem::StereoisomerGenerator::enumerateAtomCenters)
        .add_property("enumBondCenters", &Chem::StereoisomerGenerator::bondCentersEnumerated,
             &Chem::StereoisomerGenerator::enumerateBondCenters)
        .add_property("enumSpecifiedCenters", &Chem::StereoisomerGenerator::specifiedCentersEnumerated,
             &Chem::StereoisomerGenerator::enumerateSpecifiedCenters)
        .add_property("enumSymmetricCenters", &Chem::StereoisomerGenerator::symmetricCentersEnumerated,
             &Chem::StereoisomerGenerator::enumerateSymmetricCenters)
        .add_property("exclBridgeheadAtoms", &Chem::StereoisomerGenerator::bridgeheadAtomsExcluded,
             &Chem::StereoisomerGenerator::excludeBridgeheadAtoms)
        .add_property("exclNitrogens", &Chem::StereoisomerGenerator::nitrogensExcluded,
             &Chem::StereoisomerGenerator::excludeNitrogens)
        .add_property("exclRingBonds", &Chem::StereoisomerGenerator::ringBondsExcluded,
             &Chem::StereoisomerGenerator::excludeRingBonds)
        .add_property("minRingSize", &Chem::StereoisomerGenerator::getMinRingSize,
             &Chem::StereoisomerGenerator::setMinRingSize)
        .add_property("atomDescriptors", python::make_function(&Chem::StereoisomerGenerator::getAtomDescriptors,
                                                               python::return_internal_reference<>()))
        .add_property("bondDescriptors", python::make_function(&Chem::StereoisomerGenerator::getBondDescriptors,
                                                               python::return_internal_reference<>()));
}
