/* 
 * FeatureGeneratorExport.cpp 
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

#include "CDPL/Pharm/FeatureGenerator.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct FeatureGeneratorWrapper : CDPL::Pharm::FeatureGenerator, boost::python::wrapper<CDPL::Pharm::FeatureGenerator> 
    {

        typedef std::shared_ptr<FeatureGeneratorWrapper> SharedPointer;

        void generate(const CDPL::Chem::MolecularGraph& molgraph, CDPL::Pharm::Pharmacophore& pharm) {    
            this->get_override("generate")(boost::ref(molgraph), boost::ref(pharm));
        }      

        CDPL::Pharm::FeatureGenerator::SharedPointer clone() const {    
            return this->get_override("clone")();
        }      
    };
}


void CDPLPythonPharm::exportFeatureGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<FeatureGeneratorWrapper, FeatureGeneratorWrapper::SharedPointer, boost::noncopyable>("FeatureGenerator", python::no_init)
        .def(python::init<>(python::arg("self")))
        //.def(python::init<const Pharm::FeatureGenerator&>((python::arg("self"), python::arg("gen"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureGenerator>())
        //.def("assign", &Pharm::FeatureGenerator::operator=, (python::arg("self"), python::arg("gen")))
        .def("setAtom3DCoordinatesFunction", &Pharm::FeatureGenerator::setAtom3DCoordinatesFunction,
             (python::arg("self"), python::arg("func")))
        .def("getAtom3DCoordinatesFunction", &Pharm::FeatureGenerator::getAtom3DCoordinatesFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("generate", python::pure_virtual(&Pharm::FeatureGenerator::generate),
             (python::arg("self"), python::arg("molgraph"), python::arg("pharm")))
        .def("clone", python::pure_virtual(&Pharm::FeatureGenerator::clone),
             python::arg("self"))
        .add_property("atomCoordsFunction",
                      python::make_function(&Pharm::FeatureGenerator::getAtom3DCoordinatesFunction, python::return_internal_reference<>()),
                      &Pharm::FeatureGenerator::setAtom3DCoordinatesFunction);

    python::register_ptr_to_python<Pharm::FeatureGenerator::SharedPointer>();
}
