/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BFGSMinimizerExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Math/BFGSMinimizer.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	template <typename T, typename A>
	struct BFGSMinimizerExport
	{

		typedef T FuncValueType;
		typedef A ArrayType;
		typedef CDPL::Math::BFGSMinimizer<ArrayType, FuncValueType> MinimizerType;

		BFGSMinimizerExport(const char* name) {
			using namespace boost;
		
			python::class_<MinimizerType> cl(name, python::no_init);
			python::scope scope = cl;

			python::enum_<typename MinimizerType::Status>("Status")
				.value("SUCCESS", MinimizerType::SUCCESS)
				.value("NO_PROGRESS", MinimizerType::NO_PROGRESS)
				.value("ITER_LIMIT_REACHED", MinimizerType::ITER_LIMIT_REACHED)
				.value("GNORM_REACHED", MinimizerType::GNORM_REACHED)
				.value("DELTAF_REACHED", MinimizerType::DELTAF_REACHED)
				.export_values();
			
			cl
				.def(python::init<const typename MinimizerType::ObjectiveFunction&, const typename MinimizerType::GradientFunction&>(
						 (python::arg("self"), python::arg("func"), python::arg("grad_func"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<MinimizerType>())
				.def("getGradientNorm", &MinimizerType::getGradientNorm, python::arg("self"))
				.def("getFunctionDelta", &MinimizerType::getFunctionDelta, python::arg("self"))
				.def("getFunctionValue", &MinimizerType::getFunctionValue, python::arg("self"))
				.def("getNumIterations", &MinimizerType::getNumIterations, python::arg("self"))
				.def("getStatus", &MinimizerType::getStatus, python::arg("self"))
				.def("minimize", &minimize, 
					 (python::arg("self"), python::arg("x"), python::arg("g"), python::arg("max_iter"), 
					  python::arg("g_norm"), python::arg("delta_f"), python::arg("do_setup") = true))
				.def("setup", &MinimizerType::setup, 
					 (python::arg("self"), python::arg("x"), python::arg("g"), python::arg("step_size") = 0.001, 
					  python::arg("tol") = 0.15))
				.def("iterate", &iterate, (python::arg("self"), python::arg("f"), python::arg("x"), python::arg("g")))
				.add_property("gradientNorm", &MinimizerType::getGradientNorm)
				.add_property("functionDelta", &MinimizerType::getFunctionDelta)
				.add_property("functionValue", &MinimizerType::getFunctionValue)
				.add_property("numIterations", &MinimizerType::getNumIterations)
				.add_property("status", &MinimizerType::getStatus);
		}

		static typename MinimizerType::Status minimize(MinimizerType& minimizer, ArrayType& x, ArrayType& g, 
													   std::size_t max_iter, const FuncValueType& g_norm, 
													   const FuncValueType& delta_f, bool call_setup) {
	
			return minimizer.minimize(x, g, max_iter, g_norm, delta_f, call_setup);
		}

		static boost::python::tuple iterate(MinimizerType& minimizer, const FuncValueType& f, ArrayType& x, 
											ArrayType& g) {
			FuncValueType tmp_f = f;

			typename MinimizerType::Status status = minimizer.iterate(tmp_f, x, g);

			return boost::python::make_tuple(status, tmp_f);
		}
	};
}


void CDPLPythonMath::exportBFGSMinimizerTypes()
{
	using namespace CDPL;

	BFGSMinimizerExport<float, Math::FVector>("FVectorBFGSMinimizer");
	BFGSMinimizerExport<double, Math::DVector>("DVectorBFGSMinimizer");

	BFGSMinimizerExport<float, Math::Vector2FArray>("Vector2FArrayBFGSMinimizer");
	BFGSMinimizerExport<float, Math::Vector3FArray>("Vector3FArrayBFGSMinimizer");

	BFGSMinimizerExport<double, Math::Vector2DArray>("Vector2DArrayBFGSMinimizer");
	BFGSMinimizerExport<double, Math::Vector3DArray>("Vector3DArrayBFGSMinimizer");
}
