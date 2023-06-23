/* 
 * MultiConfMoleculeInputProcessorExport.cpp 
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

#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct MultiConfMoleculeInputProcessorWrapper :
        CDPL::Chem::MultiConfMoleculeInputProcessor, boost::python::wrapper<CDPL::Chem::MultiConfMoleculeInputProcessor> 
    {
    
        typedef std::shared_ptr<MultiConfMoleculeInputProcessorWrapper> SharedPointer;

        bool init(CDPL::Chem::MolecularGraph& tgt_molgraph) const {
            return this->get_override("init")(boost::ref(tgt_molgraph));
        }

        bool isConformation(CDPL::Chem::MolecularGraph& tgt_molgraph, CDPL::Chem::MolecularGraph& conf_molgraph) const {
            return this->get_override("isConformation")(boost::ref(tgt_molgraph), boost::ref(conf_molgraph));
        }

        bool addConformation(CDPL::Chem::MolecularGraph& tgt_molgraph, CDPL::Chem::MolecularGraph& conf_molgraph) const {
            return this->get_override("addConformation")(boost::ref(tgt_molgraph), boost::ref(conf_molgraph));
        }
    };
}


void CDPLPythonChem::exportMultiConfMoleculeInputProcessor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<MultiConfMoleculeInputProcessorWrapper, MultiConfMoleculeInputProcessorWrapper::SharedPointer,
                   boost::noncopyable>("MultiConfMoleculeInputProcessor", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::MultiConfMoleculeInputProcessor>())
        .def("init", python::pure_virtual(&Chem::MultiConfMoleculeInputProcessor::init), 
             python::arg("tgt_molgraph"))
        .def("isConformation", python::pure_virtual(&Chem::MultiConfMoleculeInputProcessor::isConformation), 
             (python::arg("tgt_molgraph"), python::arg("conf_molgraph")))
        .def("addConformation", python::pure_virtual(&Chem::MultiConfMoleculeInputProcessor::addConformation), 
             (python::arg("tgt_molgraph"), python::arg("conf_molgraph")));

    python::register_ptr_to_python<Chem::MultiConfMoleculeInputProcessor::SharedPointer>();
}
