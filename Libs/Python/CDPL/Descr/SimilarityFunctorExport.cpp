/* 
 * SimilarityFunctorExport.cpp 
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
#include <boost/python/def_visitor.hpp>

#include "CDPL/Descr/SimilarityFunctors.hpp"
#include "CDPL/Math/Vector.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename FuncType>
    struct DefCtorVisitor : public boost::python::def_visitor<DefCtorVisitor<FuncType> >
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;

            cl.def(python::init<>(python::arg("self")));
        }
    };

    template <typename FuncType>
    struct DefMemberVisitor : public boost::python::def_visitor<DefMemberVisitor<FuncType> >
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;

            cl
                .def(python::init<const FuncType&>((python::arg("self"), python::arg("func"))))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<FuncType>())
                .def("assign", CDPLPythonBase::copyAssOp<FuncType>(),
                     (python::arg("self"), python::arg("func")), python::return_self<>());
        }
    };

    template <typename FuncType, typename ResType = double>
    struct BSArgCallOpVisitor : public boost::python::def_visitor<BSArgCallOpVisitor<FuncType, ResType> >
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;
            using namespace CDPL;
            
            cl.def("__call__", static_cast<ResType (FuncType::*)(const Util::BitSet&, const Util::BitSet&) const>(&FuncType::operator()),
                   (python::arg("self"), python::arg("bs1"), python::arg("bs2")));
        }
    };

    template <typename FuncType>
    struct VecArgCallOpVisitor : public boost::python::def_visitor<VecArgCallOpVisitor<FuncType> >
    {

        friend class boost::python::def_visitor_access;

        template <typename ClassType>
        void visit(ClassType& cl) const
        {
            using namespace boost;
            using namespace CDPL;
            
            cl
                .def("__call__", static_cast<double (FuncType::*)(const Math::FVector&, const Math::FVector&) const>(&FuncType::operator()),
                        (python::arg("self"), python::arg("v1"), python::arg("v2")))
                .def("__call__", static_cast<double (FuncType::*)(const Math::DVector&, const Math::DVector&) const>(&FuncType::operator()),
                     (python::arg("self"), python::arg("v1"), python::arg("v2")))
                .def("__call__", static_cast<double (FuncType::*)(const Math::LVector&, const Math::LVector&) const>(&FuncType::operator()),
                     (python::arg("self"), python::arg("v1"), python::arg("v2")))
                .def("__call__", static_cast<double (FuncType::*)(const Math::ULVector&, const Math::ULVector&) const>(&FuncType::operator()),
                     (python::arg("self"), python::arg("v1"), python::arg("v2")));
        }
    };
}


void CDPLPythonDescr::exportSimilarityFunctors()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Descr::TanimotoSimilarity>("TanimotoSimilarity", python::no_init)
        .def(DefCtorVisitor<Descr::TanimotoSimilarity>())
        .def(DefMemberVisitor<Descr::TanimotoSimilarity>())
        .def(BSArgCallOpVisitor<Descr::TanimotoSimilarity>())
        .def(VecArgCallOpVisitor<Descr::TanimotoSimilarity>());

    python::class_<Descr::CosineSimilarity>("CosineSimilarity", python::no_init)
        .def(DefCtorVisitor<Descr::CosineSimilarity>())
        .def(DefMemberVisitor<Descr::CosineSimilarity>())
        .def(BSArgCallOpVisitor<Descr::CosineSimilarity>())
        .def(VecArgCallOpVisitor<Descr::CosineSimilarity>());

    python::class_<Descr::EuclideanSimilarity>("EuclideanSimilarity", python::no_init)
        .def(DefCtorVisitor<Descr::EuclideanSimilarity>())
        .def(DefMemberVisitor<Descr::EuclideanSimilarity>())
        .def(BSArgCallOpVisitor<Descr::EuclideanSimilarity>());

    python::class_<Descr::ManhattanSimilarity>("ManhattanSimilarity", python::no_init)
        .def(DefCtorVisitor<Descr::ManhattanSimilarity>())
        .def(DefMemberVisitor<Descr::ManhattanSimilarity>())
        .def(BSArgCallOpVisitor<Descr::ManhattanSimilarity>());

    python::class_<Descr::DiceSimilarity>("DiceSimilarity", python::no_init)
        .def(DefCtorVisitor<Descr::DiceSimilarity>())
        .def(DefMemberVisitor<Descr::DiceSimilarity>())
        .def(BSArgCallOpVisitor<Descr::DiceSimilarity>());

    python::class_<Descr::TverskySimilarity>("TverskySimilarity", python::no_init)
        .def(python::init<double, double>((python::arg("self"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05)))
        .def(DefMemberVisitor<Descr::TverskySimilarity>())
        .def(BSArgCallOpVisitor<Descr::TverskySimilarity>());

    python::class_<Descr::HammingDistance>("HammingDistance", python::no_init)
        .def(DefCtorVisitor<Descr::HammingDistance>())
        .def(DefMemberVisitor<Descr::HammingDistance>())
        .def(BSArgCallOpVisitor<Descr::HammingDistance, std::size_t>());

    python::class_<Descr::ManhattanDistance>("ManhattanDistance", python::no_init)
        .def(DefCtorVisitor<Descr::ManhattanDistance>())
        .def(DefMemberVisitor<Descr::ManhattanDistance>())
        .def(VecArgCallOpVisitor<Descr::ManhattanDistance>());

    python::class_<Descr::EuclideanDistance>("EuclideanDistance", python::no_init)
        .def(DefCtorVisitor<Descr::EuclideanDistance>())
        .def(DefMemberVisitor<Descr::EuclideanDistance>())
        .def(BSArgCallOpVisitor<Descr::DiceSimilarity>())
        .def(VecArgCallOpVisitor<Descr::EuclideanDistance>());
}
