/* 
 * MLRModelExport.cpp 
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

#include "CDPL/Math/MLRModel.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "VectorExpression.hpp"
#include "ClassExports.hpp"


namespace
{

    template <typename T>
    struct MLRModelExport
    {

        typedef CDPL::Math::MLRModel<T> ModelType;
        typedef typename CDPL::Math::MLRModel<T>::SizeType SizeType;
        typedef typename CDPL::Math::MLRModel<T>::ValueType ValueType;
        typedef typename CDPL::Math::MLRModel<T>::VectorType VectorType;
        typedef typename CDPL::Math::MLRModel<T>::MatrixType MatrixType;

        MLRModelExport(const char* name) {
            using namespace boost;

            const MatrixType& (ModelType::*getXMatrixFunc)() const = &ModelType::getXMatrix;
            const VectorType& (ModelType::*getYValuesFunc)() const = &ModelType::getYValues;

            python::class_<ModelType >(name, python::no_init)
                .def(python::init<>(python::arg("self")))
                .def(python::init<const ModelType&>((python::arg("self"), python::arg("model"))))
                .def(CDPLPythonBase::ObjectIdentityCheckVisitor<ModelType >())
                .def("assign", CDPLPythonBase::copyAssOp(&ModelType::operator=), (python::arg("self"), python::arg("model")),
                     python::return_self<>())
                .def("resizeDataSet", &ModelType::resizeDataSet, 
                     (python::arg("self"), python::arg("num_points"), python::arg("num_vars")))
                .def("clearDataSet", &ModelType::clearDataSet, python::arg("self"))
                .def("setXYData", &setXYData<float>, 
                     (python::arg("self"), python::arg("i"), python::arg("x_vars"), python::arg("y")))
                .def("setXYData", &setXYData<double>, 
                     (python::arg("self"), python::arg("i"), python::arg("x_vars"), python::arg("y")))
                .def("setXYData", &setXYData<long>, 
                     (python::arg("self"), python::arg("i"), python::arg("x_vars"), python::arg("y")))
                .def("setXYData", &setXYData<unsigned long>, 
                     (python::arg("self"), python::arg("i"), python::arg("x_vars"), python::arg("y")))
                .def("addXYData", &addXYData<float>, 
                     (python::arg("self"), python::arg("x_vars"), python::arg("y")))
                .def("addXYData", &addXYData<double>, 
                     (python::arg("self"), python::arg("x_vars"), python::arg("y")))
                .def("addXYData", &addXYData<long>, 
                     (python::arg("self"), python::arg("x_vars"), python::arg("y")))
                .def("addXYData", &addXYData<unsigned long>, 
                     (python::arg("self"), python::arg("x_vars"), python::arg("y")))
                .def("getXMatrix", getXMatrixFunc, python::arg("self"), 
                     python::return_internal_reference<>())
                .def("getYValues", getYValuesFunc, python::arg("self"), 
                     python::return_internal_reference<>())
                .def("buildModel", &ModelType::buildModel, python::arg("self"))
                .def("calcStatistics", &ModelType::calcStatistics, python::arg("self"))
                .def("calcYValue", &calcYValue<float>, (python::arg("self"), python::arg("x_vars")))
                .def("calcYValue", &calcYValue<double>, (python::arg("self"), python::arg("x_vars")))
                .def("calcYValue", &calcYValue<long>, (python::arg("self"), python::arg("x_vars")))
                .def("calcYValue", &calcYValue<unsigned long>, (python::arg("self"), python::arg("x_vars")))
                .def("getCoefficients", &ModelType::getCoefficients, python::arg("self"),
                     python::return_internal_reference<>())
                .def("getChiSquare", &ModelType::getChiSquare, python::arg("self"))
                .def("getGoodnessOfFit", &ModelType::getGoodnessOfFit, python::arg("self"))
                .def("getCorrelationCoefficient", &ModelType::getCorrelationCoefficient, python::arg("self"))
                .def("getStandardDeviation", &ModelType::getStandardDeviation, python::arg("self"))
                .def("__call__", &calcYValue<float>, (python::arg("self"), python::arg("x_vars")))
                .def("__call__", &calcYValue<double>, (python::arg("self"), python::arg("x_vars")))
                .def("__call__", &calcYValue<long>, (python::arg("self"), python::arg("x_vars")))
                .def("__call__", &calcYValue<unsigned long>, (python::arg("self"), python::arg("x_vars")))
                .add_property("xMatrix", python::make_function(getXMatrixFunc, python::return_internal_reference<>()))
                .add_property("yValues", python::make_function(getYValuesFunc, python::return_internal_reference<>()))
                .add_property("coefficients", python::make_function(&ModelType::getCoefficients,
                                                                    python::return_internal_reference<>()))
                .add_property("chiSquare", &ModelType::getChiSquare)
                .add_property("goodnessOfFit", &ModelType::getGoodnessOfFit)
                .add_property("correlationCoefficient", &ModelType::getCorrelationCoefficient)
                .add_property("standardDeviation", &ModelType::getStandardDeviation);
        }

        template <typename T1>
        static void setXYData(ModelType& model, SizeType i, 
                              const typename CDPLPythonMath::ConstVectorExpression<T1>::SharedPointer& x,
                              ValueType y) {

            model.setXYData(i, *x, y);
        }

        template <typename T1>
        static void addXYData(ModelType& model, 
                              const typename CDPLPythonMath::ConstVectorExpression<T1>::SharedPointer& x,
                              ValueType y) {

            model.addXYData(*x, y);
        }
    
        template <typename T1>
        static ValueType calcYValue(ModelType& model,
                                    const typename CDPLPythonMath::ConstVectorExpression<T1>::SharedPointer& x) {

            return model.calcYValue(*x);
        }
    };
}


void CDPLPythonMath::exportMLRModelTypes()
{
    MLRModelExport<float>("FMLRModel");
    MLRModelExport<double>("DMLRModel");
}
