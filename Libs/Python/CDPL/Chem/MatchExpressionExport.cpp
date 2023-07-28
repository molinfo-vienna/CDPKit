/* 
 * MatchExpressionExport.cpp 
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


#include <memory>

#include <boost/python.hpp>

#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Reaction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename ObjType1, typename ObjType2>
    struct MatchExpressionWrapper : 
        CDPL::Chem::MatchExpression<ObjType1, ObjType2>, boost::python::wrapper<CDPL::Chem::MatchExpression<ObjType1, ObjType2> >
    {

        typedef std::shared_ptr<MatchExpressionWrapper> SharedPointer;

        bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, 
                        const ObjType1& target_obj1, const ObjType2& target_obj2, 
                        const CDPL::Base::Any& aux_data) const {

            boost::python::override override = this->get_override("matches");
             
            if (override)
                return override(boost::ref(query_obj1), boost::ref(query_obj2), boost::ref(target_obj1), boost::ref(target_obj2), aux_data);

            return CDPL::Chem::MatchExpression<ObjType1, ObjType2>::operator()(query_obj1, query_obj2, target_obj1, target_obj2, aux_data);
        }

        static bool matches(const typename CDPL::Chem::MatchExpression<ObjType1, ObjType2>& expr, 
                            ObjType1& query_obj1, ObjType2& query_obj2, 
                            ObjType1& target_obj1, ObjType2& target_obj2, 
                            const CDPL::Base::Any& aux_data) {

            return expr(query_obj1, query_obj2, target_obj1, target_obj2, aux_data);
        }

        bool operator()(const ObjType1& query_obj1, const ObjType2& query_obj2, 
                        const ObjType1& target_obj1, const ObjType2& target_obj2, 
                        const CDPL::Chem::AtomBondMapping& mapping, const CDPL::Base::Any& aux_data) const {

            boost::python::override override = this->get_override("mappingMatches");
             
            if (override)
                return override(boost::ref(query_obj1), boost::ref(query_obj2), boost::ref(target_obj1), boost::ref(target_obj2),
                                boost::ref(mapping), aux_data);

            return this->CDPL::Chem::MatchExpression<ObjType1, ObjType2>::operator()(query_obj1, query_obj2, target_obj1, target_obj2, mapping, aux_data);
        }

        static bool mappingMatches(const CDPL::Chem::MatchExpression<ObjType1, ObjType2>& expr, 
                                   ObjType1& query_obj1, ObjType2& query_obj2, 
                                   ObjType1& target_obj1, ObjType2& target_obj2, 
                                   const CDPL::Chem::AtomBondMapping& mapping, const CDPL::Base::Any& aux_data)
        {
            return expr(query_obj1, query_obj2, target_obj1, target_obj2, mapping, aux_data);
        }

        bool requiresAtomBondMapping() const {
            boost::python::override override = this->get_override("requiresAtomBondMapping");
             
            if (override)
                return override();

            return this->CDPL::Chem::MatchExpression<ObjType1, ObjType2>::requiresAtomBondMapping();
        }
    };


    template <typename ObjType>
    struct MatchExpressionWrapper<ObjType, void> : 
        CDPL::Chem::MatchExpression<ObjType, void>, boost::python::wrapper<CDPL::Chem::MatchExpression<ObjType, void> >
    {

        typedef std::shared_ptr<MatchExpressionWrapper> SharedPointer;

        bool operator()(const ObjType& query_obj, const ObjType& target_obj, const CDPL::Base::Any& aux_data) const {
            boost::python::override override = this->get_override("matches");
             
            if (override)
                return override(boost::ref(query_obj), boost::ref(target_obj), aux_data);

            return this->CDPL::Chem::MatchExpression<ObjType, void>::operator()(query_obj, target_obj, aux_data);
        }


        static bool matches(const CDPL::Chem::MatchExpression<ObjType, void>& expr, 
                            ObjType& query_obj, ObjType& target_obj, const CDPL::Base::Any& aux_data) {
    
            return expr(query_obj, target_obj, aux_data);
        }

        bool operator()(const ObjType& query_obj, const ObjType& target_obj, 
                        const CDPL::Chem::AtomBondMapping& mapping, const CDPL::Base::Any& aux_data) const {

            boost::python::override override = this->get_override("mappingMatches");
             
            if (override)
                return override(boost::ref(query_obj), boost::ref(target_obj), boost::ref(mapping), aux_data);

            return this->CDPL::Chem::MatchExpression<ObjType, void>::operator()(query_obj, target_obj, mapping, aux_data);
        }

        static bool mappingMatches(const CDPL::Chem::MatchExpression<ObjType, void>& expr, 
                                   ObjType& query_obj, ObjType& target_obj,
                                   const CDPL::Chem::AtomBondMapping& mapping, const CDPL::Base::Any& aux_data) {

            return expr(query_obj, target_obj, mapping, aux_data);
        }

        bool requiresAtomBondMapping() const {
            boost::python::override override = this->get_override("requiresAtomBondMapping");
             
            if (override)
                return override();

            return this->CDPL::Chem::MatchExpression<ObjType, void>::requiresAtomBondMapping();
        }
    };


    template <typename ObjType1, typename ObjType2>
    struct MatchExpressionExport
    {

        MatchExpressionExport(const char* name, const char* query_arg1_name, const char* query_arg2_name, 
                              const char* target_arg1_name, const char* target_arg2_name) {
            using namespace boost;
            using namespace CDPL;

            python::class_<MatchExpressionWrapper<ObjType1, ObjType2>, typename MatchExpressionWrapper<ObjType1, ObjType2>::SharedPointer, 
                boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::MatchExpression<ObjType1, ObjType2> >())    
                .def("__call__", &MatchExpressionWrapper<ObjType1, ObjType2>::matches,
                     (python::arg("self"), python::arg(query_arg1_name), 
                      python::arg(query_arg2_name), python::arg(target_arg1_name), 
                      python::arg(target_arg2_name), python::arg("aux_data")))
                .def("__call__", &MatchExpressionWrapper<ObjType1, ObjType2>::mappingMatches,
                     (python::arg("self"), python::arg(query_arg1_name), 
                      python::arg(query_arg2_name), python::arg(target_arg1_name), 
                      python::arg(target_arg2_name), python::arg("mapping"),
                      python::arg("aux_data")))
                .def("requiresAtomBondMapping", 
                     &Chem::MatchExpression<ObjType1, ObjType2>::requiresAtomBondMapping, 
                     python::arg("self")); 

            python::register_ptr_to_python<typename Chem::MatchExpression<ObjType1>::SharedPointer>();
        }
    };


    template <typename ObjType>
    struct MatchExpressionExport<ObjType, void>
    {

        MatchExpressionExport(const char* name, const char* query_arg_name, const char* target_arg_name) {
            using namespace boost;
            using namespace CDPL;

            python::class_<MatchExpressionWrapper<ObjType, void>, 
                typename MatchExpressionWrapper<ObjType, void>::SharedPointer, 
                boost::noncopyable>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::MatchExpression<ObjType, void> >())    
                .def("__call__", &MatchExpressionWrapper<ObjType, void>::matches,
                     (python::arg("self"), python::arg(query_arg_name), 
                      python::arg(target_arg_name), python::arg("aux_data")))
                .def("__call__", &MatchExpressionWrapper<ObjType, void>::mappingMatches,
                     (python::arg("self"), python::arg(query_arg_name), 
                      python::arg(target_arg_name), python::arg("mapping"), 
                      python::arg("aux_data")))
                .def("requiresAtomBondMapping", &Chem::MatchExpression<ObjType, void>::requiresAtomBondMapping, 
                     python::arg("self")); 

            python::register_ptr_to_python<typename Chem::MatchExpression<ObjType>::SharedPointer>();
        }
    };
}


void CDPLPythonChem::exportMatchExpressions()
{
    using namespace CDPL;

    MatchExpressionExport<Chem::Atom, Chem::MolecularGraph>("AtomMatchExpression", "query_atom", "query_molgraph", 
                                                            "target_atom", "target_molgraph");
    MatchExpressionExport<Chem::Bond, Chem::MolecularGraph>("BondMatchExpression", "query_bond", "query_molgraph", 
                                                            "target_bond", "target_molgraph");
    MatchExpressionExport<Chem::MolecularGraph, void>("MolecularGraphMatchExpression", "query_molgraph", "target_molgraph");
    MatchExpressionExport<Chem::Reaction, void>("ReactionMatchExpression", "query_rxn", "target_rxn");
}
