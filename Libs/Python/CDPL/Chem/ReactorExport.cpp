/* 
 * ReactorExport.cpp 
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

#include "CDPL/Chem/Reactor.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportReactor()
{
	using namespace boost;
	using namespace CDPL;

	Chem::Reactor::ReactionSite& (Chem::Reactor::*getReactionSiteFunc)(std::size_t) = &Chem::Reactor::getReactionSite;

	python::class_<Chem::Reactor, boost::noncopyable>("Reactor", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::Reaction&>((python::arg("self"), python::arg("rxn_pattern")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::Reactor>())	
		.def("setReactionPattern", &Chem::Reactor::setReactionPattern, (python::arg("self"), python::arg("rxn_pattern")),
			 python::with_custodian_and_ward<1, 2>())
		.def("findReactionSites", &Chem::Reactor::findReactionSites, (python::arg("self"), python::arg("rxn_target")),
			 python::with_custodian_and_ward<1, 2>())
		.def("getNumReactionSites", &Chem::Reactor::getNumReactionSites, python::arg("self"))
		.def("getReactionSite", getReactionSiteFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("performReaction", &Chem::Reactor::performReaction, (python::arg("self"), python::arg("rxn_site")));
}
