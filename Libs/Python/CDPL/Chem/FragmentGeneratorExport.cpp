/* 
 * FragmentGeneratorExport.cpp 
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

#include "CDPL/Chem/FragmentGenerator.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonChem::exportFragmentGenerator()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::FragmentGenerator, Chem::FragmentGenerator::SharedPointer,
                   boost::noncopyable> cl("FragmentGenerator", python::no_init);

    python::scope scope = cl;

    python::class_<Chem::FragmentGenerator::FragmentationRule, boost::noncopyable>("FragmentationRuler", python::no_init)
        .def(python::init<Chem::FragmentGenerator::FragmentationRule>((python::arg("self"), python::arg("rule"))))
        .def(python::init<const Chem::MolecularGraph::SharedPointer&, unsigned int>(
                 (python::arg("self"), python::arg("match_ptn"), python::arg("id"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::FragmentGenerator::FragmentationRule>())
        .def("assign", CDPLPythonBase::copyAssOp(&Chem::FragmentGenerator::FragmentationRule::operator=), 
             (python::arg("self"), python::arg("rule")), python::return_self<>())
        .def("getMatchPattern", &Chem::FragmentGenerator::FragmentationRule::getMatchPattern,
             python::arg("self"), python::return_value_policy<python::copy_const_reference>())
        .def("setMatchPattern", &Chem::FragmentGenerator::FragmentationRule::setMatchPattern,
             (python::arg("self"), python::arg("ptn")))
        .def("getID", &Chem::FragmentGenerator::FragmentationRule::getID,
             python::arg("self"))
        .def("setID", &Chem::FragmentGenerator::FragmentationRule::setID,
             (python::arg("self"), python::arg("id")))
        .add_property("matchPattern", 
                      python::make_function(&Chem::FragmentGenerator::FragmentationRule::getMatchPattern,
                                            python::return_value_policy<python::copy_const_reference>()),
                      &Chem::FragmentGenerator::FragmentationRule::setMatchPattern)
        .add_property("id", &Chem::FragmentGenerator::FragmentationRule::getID, 
                      &Chem::FragmentGenerator::FragmentationRule::setID);

    python::class_<Chem::FragmentGenerator::ExcludePattern, boost::noncopyable>("ExcludePattern", python::no_init)
        .def(python::init<Chem::FragmentGenerator::ExcludePattern>((python::arg("self"), python::arg("excl_ptn"))))
        .def(python::init<const Chem::MolecularGraph::SharedPointer&, unsigned int>(
                 (python::arg("self"), python::arg("match_ptn"), python::arg("rule_id"))))
        .def(python::init<const Chem::MolecularGraph::SharedPointer&>(
                 (python::arg("self"), python::arg("match_ptn"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::FragmentGenerator::ExcludePattern>())
        .def("assign", CDPLPythonBase::copyAssOp(&Chem::FragmentGenerator::ExcludePattern::operator=), 
             (python::arg("self"), python::arg("excl_ptn")), python::return_self<>())
        .def("getMatchPattern", &Chem::FragmentGenerator::ExcludePattern::getMatchPattern,
             python::arg("self"), python::return_value_policy<python::copy_const_reference>())
        .def("setMatchPattern", &Chem::FragmentGenerator::ExcludePattern::setMatchPattern,
             (python::arg("self"), python::arg("ptn")))
        .def("getRuleID", &Chem::FragmentGenerator::ExcludePattern::getRuleID,
             python::arg("self"))
        .def("setRuleID", &Chem::FragmentGenerator::ExcludePattern::setRuleID,
             (python::arg("self"), python::arg("id")))
        .def("isGeneric", &Chem::FragmentGenerator::ExcludePattern::isGeneric,
             python::arg("self"))
        .def("setGeneric", &Chem::FragmentGenerator::ExcludePattern::setGeneric,
             (python::arg("self"), python::arg("generic")))
        .add_property("matchPattern", 
                      python::make_function(&Chem::FragmentGenerator::ExcludePattern::getMatchPattern,
                                            python::return_value_policy<python::copy_const_reference>()),
                      &Chem::FragmentGenerator::ExcludePattern::setMatchPattern)
        .add_property("ruleID", &Chem::FragmentGenerator::ExcludePattern::getRuleID, 
                      &Chem::FragmentGenerator::ExcludePattern::setRuleID)
        .add_property("generic", &Chem::FragmentGenerator::ExcludePattern::isGeneric, 
                      &Chem::FragmentGenerator::ExcludePattern::setGeneric);

    python::class_<Chem::FragmentGenerator::FragmentLink, boost::noncopyable>("FragmentLink", python::no_init)
        .def(python::init<Chem::FragmentGenerator::FragmentLink>((python::arg("self"), python::arg("link")))[python::with_custodian_and_ward<1, 2>()])
        .def(python::init<std::size_t, std::size_t, Chem::Bond&, unsigned int, unsigned int, unsigned int>(
                 (python::arg("self"), python::arg("frag1_idx"), python::arg("frag2_idx"), python::arg("bond"), 
                  python::arg("rule_id"), python::arg("atom1_label"), python::arg("atom2_label")))
             [python::with_custodian_and_ward<1, 4>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::FragmentGenerator::FragmentLink>())
        .def("assign", CDPLPythonBase::copyAssOp(&Chem::FragmentGenerator::FragmentLink::operator=), 
             (python::arg("self"), python::arg("link")), python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("getFragment1Index", &Chem::FragmentGenerator::FragmentLink::getFragment1Index,
             python::arg("self"))
        .def("getFragment2Index", &Chem::FragmentGenerator::FragmentLink::getFragment2Index,
             python::arg("self"))
        .def("getBond", &Chem::FragmentGenerator::FragmentLink::getBond,
             python::arg("self"), python::return_internal_reference<>())
        .def("getRuleID", &Chem::FragmentGenerator::FragmentLink::getRuleID,
             python::arg("self"))
        .def("getAtom1Label", &Chem::FragmentGenerator::FragmentLink::getAtom1Label,
             python::arg("self"))
        .def("getAtom2Label", &Chem::FragmentGenerator::FragmentLink::getAtom2Label,
             python::arg("self"))
        .add_property("fragment1Index", &Chem::FragmentGenerator::FragmentLink::getFragment1Index)
        .add_property("fragment2Index", &Chem::FragmentGenerator::FragmentLink::getFragment2Index)
        .add_property("bond", python::make_function(&Chem::FragmentGenerator::FragmentLink::getBond,
                                                    python::return_internal_reference<>()))
        .add_property("ruleID", &Chem::FragmentGenerator::FragmentLink::getRuleID)
        .add_property("atom1Label", &Chem::FragmentGenerator::FragmentLink::getAtom1Label)
        .add_property("atom2Label", &Chem::FragmentGenerator::FragmentLink::getAtom2Label);
    
    cl
        .def(python::init<>(python::arg("self")))
        .def(python::init<Chem::FragmentGenerator>((python::arg("self"), python::arg("gen")))[python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::FragmentGenerator>())
        .def("assign", &Chem::FragmentGenerator::operator=, 
             (python::arg("self"), python::arg("gen")), python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("addFragmentationRule",
             static_cast<void (Chem::FragmentGenerator::*)(const Chem::MolecularGraph::SharedPointer&, unsigned int)>
             (&Chem::FragmentGenerator::addFragmentationRule), 
             (python::arg("self"), python::arg("match_ptn"), python::arg("rule_id")))
        .def("addFragmentationRule",
             static_cast<void (Chem::FragmentGenerator::*)(const Chem::FragmentGenerator::FragmentationRule&)>
             (&Chem::FragmentGenerator::addFragmentationRule), 
             (python::arg("self"), python::arg("rule")))
        .def("removeFragmentationRule", &Chem::FragmentGenerator::removeFragmentationRule, 
             (python::arg("self"), python::arg("idx")))
        .def("getFragmentationRule",
             static_cast<Chem::FragmentGenerator::FragmentationRule& (Chem::FragmentGenerator::*)(std::size_t)>
             (&Chem::FragmentGenerator::getFragmentationRule), 
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
        .def("clearFragmentationRules", &Chem::FragmentGenerator::clearFragmentationRules, 
             python::arg("self"))
        .def("getNumFragmentationRules", &Chem::FragmentGenerator::getNumFragmentationRules, 
             python::arg("self"))
        .def("addExcludePattern",
             static_cast<void (Chem::FragmentGenerator::*)(const Chem::MolecularGraph::SharedPointer&, unsigned int)>
             (&Chem::FragmentGenerator::addExcludePattern), 
             (python::arg("self"), python::arg("match_ptn"), python::arg("rule_id")))
        .def("addExcludePattern",
             static_cast<void (Chem::FragmentGenerator::*)(const Chem::MolecularGraph::SharedPointer&)>
             (&Chem::FragmentGenerator::addExcludePattern), 
             (python::arg("self"), python::arg("match_ptn")))
        .def("addExcludePattern",
             static_cast<void (Chem::FragmentGenerator::*)(const Chem::FragmentGenerator::ExcludePattern&)>
             (&Chem::FragmentGenerator::addExcludePattern), 
             (python::arg("self"), python::arg("excl_ptn")))
        .def("removeExcludePattern", &Chem::FragmentGenerator::removeExcludePattern, 
             (python::arg("self"), python::arg("idx")))
        .def("getExcludePattern",
             static_cast<Chem::FragmentGenerator::ExcludePattern& (Chem::FragmentGenerator::*)(std::size_t)>
             (&Chem::FragmentGenerator::getExcludePattern), 
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
        .def("clearExcludePatterns", &Chem::FragmentGenerator::clearExcludePatterns, 
             python::arg("self"))
        .def("getNumExcludePatterns", &Chem::FragmentGenerator::getNumExcludePatterns, 
             python::arg("self"))
        .def("setFragmentFilterFunction", &Chem::FragmentGenerator::setFragmentFilterFunction, 
             (python::arg("self"), python::arg("func")))
        .def("getFragmentFilterFunction", &Chem::FragmentGenerator::getFragmentFilterFunction, 
             python::arg("self"), python::return_internal_reference<>())
        .def("generate", &Chem::FragmentGenerator::generate, 
             (python::arg("self"), python::arg("molgraph"), python::arg("frag_list"), python::arg("append") = false))
        .def("getFragmentLink", &Chem::FragmentGenerator::getFragmentLink, 
             (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
        .def("getNumFragmentLinks", &Chem::FragmentGenerator::getNumFragmentLinks, 
             python::arg("self"))
        .def("includeSplitBonds",
             static_cast<bool (Chem::FragmentGenerator::*)() const>(&Chem::FragmentGenerator::includeSplitBonds), 
             python::arg("self"))
        .def("includeSplitBonds",
             static_cast<void (Chem::FragmentGenerator::*)(bool)>(&Chem::FragmentGenerator::includeSplitBonds), 
             (python::arg("self"), python::arg("include")))
        .add_property("fragmentFilterFunction",
                      python::make_function(&Chem::FragmentGenerator::getFragmentFilterFunction,
                                            python::return_internal_reference<>()),
                      &Chem::FragmentGenerator::setFragmentFilterFunction)
        .add_property("incSplitBonds",
                      static_cast<bool (Chem::FragmentGenerator::*)() const>(&Chem::FragmentGenerator::includeSplitBonds),
                      static_cast<void (Chem::FragmentGenerator::*)(bool)>(&Chem::FragmentGenerator::includeSplitBonds))
        .add_property("numFragmentationRules", &Chem::FragmentGenerator::getNumFragmentationRules)
        .add_property("numExcludePatterns", &Chem::FragmentGenerator::getNumExcludePatterns)
        .add_property("numFragmentLinks", &Chem::FragmentGenerator::getNumFragmentLinks);
}
