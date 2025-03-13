/* 
 * BulkSimilarityCalculatorExport.cpp 
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

#include "CDPL/Descr/BulkSimilarityCalculator.hpp"
#include "CDPL/Math/Vector.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    template <typename DT>
    struct BulkSimilarityCalculatorExport
    {

        typedef CDPL::Descr::BulkSimilarityCalculator<DT> CalculatorType;

        BulkSimilarityCalculatorExport(const char* name)
        {
            using namespace boost;
        
            python::class_<CalculatorType, typename CalculatorType::SharedPointer>(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const CalculatorType&>
                     ((python::arg("self"), python::arg("calc"))))
                .def(python::init<const typename CalculatorType::SimilarityFunction&>
                     ((python::arg("self"), python::arg("sim_func"))))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<CalculatorType>())
                .def("assign", CDPLPythonBase::copyAssOp<CalculatorType>(),
                     (python::arg("self"), python::arg("calc")), python::return_self<>())
                .def("setSimilarityFunction",
                     &CalculatorType::template setSimilarityFunction<const typename CalculatorType::SimilarityFunction&>,
                     (python::arg("self"), python::arg("func")))
                .def("getSimilarityFunction", &CalculatorType::getSimilarityFunction,
                     python::arg("self"), python::return_internal_reference<>())
                .def("clear", &CalculatorType::clear, python::arg("self"))
                .def("getNumDescriptors", &CalculatorType::getNumDescriptors, python::arg("self"))
                .def("addDescriptor", static_cast<void (CalculatorType::*)(const typename CalculatorType::DescriptorPointer&)>
                     (&CalculatorType::addDescriptor), (python::arg("self"), python::arg("descr")))
                .def("containsDescriptor", &CalculatorType::containsDescriptor,
                     (python::arg("self"), python::arg("descr")))
                .def("getDescriptor", &CalculatorType::getDescriptor,
                     (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
                .def("removeDescriptor", static_cast<void (CalculatorType::*)(std::size_t)>(&CalculatorType::removeDescriptor),
                     (python::arg("self"), python::arg("idx")))
                .def("calculate", &CalculatorType::calculate,
                     (python::arg("self"), python::arg("descr"), python::arg("sort") = false, python::arg("sort_desc") = true))
                .def("getResult", &getResult, (python::arg("self"), python::arg("idx")))
                .def("getSimilarity", &CalculatorType::getSimilarity,
                     (python::arg("self"), python::arg("idx")),
                     python::return_value_policy<python::copy_const_reference>())
                .def("getDescriptorIndex", &CalculatorType::getDescriptorIndex,
                     (python::arg("self"), python::arg("idx")))
                .def("__getitem__", &getResult, (python::arg("self"), python::arg("idx")))
                .def("__contains__", &CalculatorType::containsDescriptor,
                     (python::arg("self"), python::arg("descr")))
                .add_property("numDescriptors", &CalculatorType::getNumDescriptors)
                .add_property("similarityFunc",
                               python::make_function(&CalculatorType::getSimilarityFunction, 
                                                     python::return_internal_reference<>()),
                              &CalculatorType::template setSimilarityFunction<const typename CalculatorType::SimilarityFunction&>);
        }

        static boost::python::tuple getResult(const CalculatorType& calc, std::size_t idx)
        {
            auto& res = calc.getResult(idx);

            return boost::python::make_tuple(res.first, res.second);
        }
    };
}


void CDPLPythonDescr::exportBulkSimilarityCalculator()
{
    using namespace boost;
    using namespace CDPL;

    BulkSimilarityCalculatorExport<Util::BitSet>("BitSetBulkSimilarityCalculator");
    BulkSimilarityCalculatorExport<Math::FVector>("FVectorBulkSimilarityCalculator");
    BulkSimilarityCalculatorExport<Math::DVector>("DVectorBulkSimilarityCalculator");
    BulkSimilarityCalculatorExport<Math::ULVector>("ULVectorBulkSimilarityCalculator");
    BulkSimilarityCalculatorExport<Math::LVector>("LVectorBulkSimilarityCalculator");
}
