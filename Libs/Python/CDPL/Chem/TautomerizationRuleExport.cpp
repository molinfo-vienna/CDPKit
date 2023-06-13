/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TautomerizationRuleExport.cpp 
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

#include "CDPL/Chem/TautomerizationRule.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    struct TautomerizationRuleWrapper : CDPL::Chem::TautomerizationRule, boost::python::wrapper<CDPL::Chem::TautomerizationRule> 
    {

		typedef std::shared_ptr<TautomerizationRuleWrapper> SharedPointer;

		unsigned int getID() const {
			return this->get_override("getID")();
		}

		bool setup(CDPL::Chem::MolecularGraph& parent_molgraph) {	
			return this->get_override("setup")(boost::ref(parent_molgraph));
		}      

		bool generate(CDPL::Chem::Molecule& tautomer) {	
			return this->get_override("generate")(boost::ref(tautomer));
		}      

		CDPL::Chem::TautomerizationRule::SharedPointer clone() const {	
			return this->get_override("clone")();
		}      
    };
}


void CDPLPythonChem::exportTautomerizationRule()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<TautomerizationRuleWrapper, TautomerizationRuleWrapper::SharedPointer, boost::noncopyable>("TautomerizationRule", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::TautomerizationRule>())	
		.def("getID", python::pure_virtual(&Chem::TautomerizationRule::getID), 
			 python::arg("self"))
		.def("setup", python::pure_virtual(&Chem::TautomerizationRule::setup),
			 (python::arg("self"), python::arg("parent_molgraph")))
		.def("generate", python::pure_virtual(&Chem::TautomerizationRule::generate),
			 (python::arg("self"), python::arg("tautomer")))
		.def("clone", python::pure_virtual(&Chem::TautomerizationRule::clone),
			 python::arg("self"));

    python::register_ptr_to_python<Chem::TautomerizationRule::SharedPointer>();
}
