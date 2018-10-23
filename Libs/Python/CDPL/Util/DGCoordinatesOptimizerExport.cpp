/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DGCoordinatesOptimizerExport.cpp 
 *
 * This file is part of the Utilical Data Processing Toolkit
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

#include "CDPL/Util/DGCoordinatesOptimizer.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Vector.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{
	
	template <typename OptimizerType>
	struct VolumeConstraintList {

		VolumeConstraintList(OptimizerType& gen): optimizer(gen) {}
		
		std::size_t getSize() const {
			return optimizer.getNumVolumeConstraints();
		}

		typename OptimizerType::VolumeConstraint& getConstraint(std::size_t idx) const {
			return optimizer.getVolumeConstraint(idx);
		}

		void removeConstraint(std::size_t idx) {
			optimizer.removeVolumeConstraint(idx);
		}

		OptimizerType& optimizer;
	};

	template <typename OptimizerType>
	VolumeConstraintList<OptimizerType> createVolumeConstraintList(OptimizerType& gen) 
	{
		return VolumeConstraintList<OptimizerType>(gen);
	}

	template <typename OptimizerType>
	struct DistanceConstraintList {

		DistanceConstraintList(OptimizerType& gen): optimizer(gen) {}
		
		std::size_t getSize() const {
			return optimizer.getNumDistanceConstraints();
		}

		typename OptimizerType::DistanceConstraint& getConstraint(std::size_t idx) const {
			return optimizer.getDistanceConstraint(idx);
		}

		void removeConstraint(std::size_t idx) {
			optimizer.removeDistanceConstraint(idx);
		}

		OptimizerType& optimizer;
	};

	template <typename OptimizerType>
	DistanceConstraintList<OptimizerType> createDistanceConstraintList(OptimizerType& gen) 
	{
		return DistanceConstraintList<OptimizerType>(gen);
	}

	template <typename OptimizerType>
	class DGCoordinatesOptimizerVisitor : 
		public boost::python::def_visitor<DGCoordinatesOptimizerVisitor<OptimizerType> >
	{
		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace CDPL;
			using namespace boost;

			typedef typename OptimizerType::DistanceConstraint DistanceConstraint;
			typedef typename OptimizerType::ValueType ValueType;
			typedef DistanceConstraintList<OptimizerType> DistanceConstraintList;
		
			python::scope scope = cl;

			python::class_<DistanceConstraintList>("DistanceConstraintList", python::no_init)
				.def("__len__", &DistanceConstraintList::getSize, python::arg("self"))
				.def("__getitem__", &DistanceConstraintList::getConstraint, (python::arg("self"), python::arg("idx")), 
					 python::return_internal_reference<1>())
				.def("__delitem__", &DistanceConstraintList::removeConstraint, (python::arg("self"), python::arg("idx")));

			python::class_<DistanceConstraint>("DistanceConstraint", python::no_init)
				.def(python::init<std::size_t, std::size_t, const ValueType&, const ValueType&>(
						 (python::arg("self"), python::arg("pt1_idx"), python::arg("pt2_idx"), python::arg("lb"), python::arg("ub"))))
				.def(python::init<const DistanceConstraint&>((python::arg("self"), python::arg("constr"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<DistanceConstraint>())
				.def("assign", CDPLPythonBase::copyAssOp(&DistanceConstraint::operator=), 
					 (python::arg("self"), python::arg("constr")), python::return_self<>())
				.def("getPoint1Index", &DistanceConstraint::getPoint1Index, python::arg("self"))
				.def("getPoint2Index", &DistanceConstraint::getPoint2Index, python::arg("self"))
				.def("getLowerBound", &DistanceConstraint::getLowerBound, python::arg("self"),
					 python::return_value_policy<python::copy_const_reference>())
				.def("getUpperBound", &DistanceConstraint::getUpperBound, python::arg("self"),
					 python::return_value_policy<python::copy_const_reference>())
				.add_property("point1Index", &DistanceConstraint::getPoint1Index)
				.add_property("point2Index", &DistanceConstraint::getPoint2Index)
				.add_property("lowerBound", python::make_function(&DistanceConstraint::getLowerBound, 
																  python::return_value_policy<python::copy_const_reference>()))
				.add_property("upperBound", python::make_function(&DistanceConstraint::getUpperBound, 
																  python::return_value_policy<python::copy_const_reference>()));

			cl
				.def(python::init<>(python::arg("self")))
				.def(python::init<const OptimizerType&>((python::arg("self"), python::arg("gen"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<OptimizerType>())
				.def("assign", CDPLPythonBase::copyAssOp(&OptimizerType::operator=), 
					 (python::arg("self"), python::arg("gen")), python::return_self<>())
				.def("clearDistanceConstraints", &OptimizerType::clearDistanceConstraints, python::arg("self"))
				.def("getNumDistanceConstraints", &OptimizerType::getNumDistanceConstraints, python::arg("self"))
				.def("getDistanceConstraint", 
					 static_cast<DistanceConstraint& (OptimizerType::*)(std::size_t)>(&OptimizerType::getDistanceConstraint),
					 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
				.def("addDistanceConstraint", &OptimizerType::addDistanceConstraint, 
					 (python::arg("self"), python::arg("pt1_idx"), python::arg("pt2_idx"), python::arg("lb"), python::arg("ub")))
				.def("removeDistanceConstraint", 
					 static_cast<void (OptimizerType::*)(std::size_t)>(&OptimizerType::removeDistanceConstraint),
					 (python::arg("self"), python::arg("idx")))
				.def("setNumCycles", &OptimizerType::setNumCycles, (python::arg("self"), python::arg("num_cycles")))
				.def("getNumCycles", &OptimizerType::getNumCycles, python::arg("self"))
				.def("setCycleStepCountFactor", &OptimizerType::setCycleStepCountFactor, (python::arg("self"), python::arg("fact")))
				.def("getCycleStepCountFactor", &OptimizerType::getCycleStepCountFactor, python::arg("self"))
				.def("setStartLearningRate", &OptimizerType::setStartLearningRate, (python::arg("self"), python::arg("rate")))
				.def("getStartLearningRate", &OptimizerType::getStartLearningRate, python::arg("self"), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("setLearningRateDecrement", &OptimizerType::setLearningRateDecrement, (python::arg("self"), python::arg("decr")))
				.def("getLearningRateDecrement", &OptimizerType::getLearningRateDecrement, python::arg("self"), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("setRandomSeed", &OptimizerType::setRandomSeed, (python::arg("self"), python::arg("seed")))
				.def("optimize", 
					 &OptimizerType::template optimize<Math::VectorArray<Math::CVector<ValueType, OptimizerType::COORDS_DIM> > >, 
					 (python::arg("self"), python::arg("num_points"), python::arg("coords")))
				.def("getDistanceError", 
					 &OptimizerType::template getDistanceError<Math::VectorArray<Math::CVector<ValueType, OptimizerType::COORDS_DIM> > >, 
					 (python::arg("self"), python::arg("coords")))
				.def_readonly("COORDS_DIM", OptimizerType::COORDS_DIM)
				.def_readonly("DEF_NUM_CYCLES", OptimizerType::DEF_NUM_CYCLES)
				.def_readonly("DEF_CYCLE_STEP_COUNT_FACTOR", OptimizerType::DEF_CYCLE_STEP_COUNT_FACTOR)
				.def_readonly("DEF_START_LEARNING_RATE", OptimizerType::DEF_START_LEARNING_RATE)
				.def_readonly("DEF_LEARNING_RATE_DECREMENT", OptimizerType::DEF_LEARNING_RATE_DECREMENT)
				.add_property("numCycles", &OptimizerType::getNumCycles, &OptimizerType::setNumCycles)
				.add_property("cycleStepCountFactor", &OptimizerType::getCycleStepCountFactor, &OptimizerType::setCycleStepCountFactor)
				.add_property("startLearningRate", python::make_function(&OptimizerType::getStartLearningRate, 
																		 python::return_value_policy<python::copy_const_reference>()),
							  &OptimizerType::setStartLearningRate)
				.add_property("learningRateDecrement", python::make_function(&OptimizerType::getLearningRateDecrement, 
																			 python::return_value_policy<python::copy_const_reference>()),
							  &OptimizerType::setLearningRateDecrement)
				.add_property("numDistanceConstraints", &OptimizerType::getNumDistanceConstraints)
				.add_property("distanceConstraints", python::make_function(&createDistanceConstraintList<OptimizerType>,
																		   python::with_custodian_and_ward_postcall<0, 1>()));
		}
	};
}


void CDPLPythonUtil::exportDGCoordinatesOptimizer()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<Util::DGCoordinatesOptimizer<2, double> >("DG2DCoordinatesOptimizer", python::no_init)
		.def(DGCoordinatesOptimizerVisitor<Util::DGCoordinatesOptimizer<2, double> >());

// 3D specialization

	typedef Util::DGCoordinatesOptimizer<3, double> OptimizerType;
	typedef OptimizerType::VolumeConstraint VolumeConstraint;
	typedef OptimizerType::ValueType ValueType;
	typedef VolumeConstraintList<OptimizerType> VolumeConstraintList;

	python::class_<OptimizerType> cl("DG3DCoordinatesOptimizer", python::no_init);

	python::scope scope = cl;

	python::class_<VolumeConstraintList>("VolumeConstraintList", python::no_init)
		.def("__len__", &VolumeConstraintList::getSize, python::arg("self"))
		.def("__getitem__", &VolumeConstraintList::getConstraint, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__delitem__", &VolumeConstraintList::removeConstraint, (python::arg("self"), python::arg("idx")));

	python::class_<VolumeConstraint>("VolumeConstraint", python::no_init)
		.def(python::init<std::size_t, std::size_t, std::size_t, std::size_t, const ValueType&, const ValueType&>(
				 (python::arg("self"), python::arg("pt1_idx"), python::arg("pt2_idx"),
				  python::arg("pt3_idx"), python::arg("pt4_idx"), python::arg("lb"), python::arg("ub"))))
		.def(python::init<const VolumeConstraint&>((python::arg("self"), python::arg("constr"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<VolumeConstraint>())
		.def("assign", CDPLPythonBase::copyAssOp(&VolumeConstraint::operator=), 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.def("getPoint1Index", &VolumeConstraint::getPoint1Index, python::arg("self"))
		.def("getPoint2Index", &VolumeConstraint::getPoint2Index, python::arg("self"))
		.def("getPoint3Index", &VolumeConstraint::getPoint3Index, python::arg("self"))
		.def("getPoint4Index", &VolumeConstraint::getPoint4Index, python::arg("self"))
		.def("getLowerBound", &VolumeConstraint::getLowerBound, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getUpperBound", &VolumeConstraint::getUpperBound, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.add_property("point1Index", &VolumeConstraint::getPoint1Index)
		.add_property("point2Index", &VolumeConstraint::getPoint2Index)
		.add_property("point3Index", &VolumeConstraint::getPoint3Index)
		.add_property("point4Index", &VolumeConstraint::getPoint4Index)
		.add_property("lowerBound", python::make_function(&VolumeConstraint::getLowerBound, 
														  python::return_value_policy<python::copy_const_reference>()))
		.add_property("upperBound", python::make_function(&VolumeConstraint::getUpperBound, 
														  python::return_value_policy<python::copy_const_reference>()));
	cl
		.def(DGCoordinatesOptimizerVisitor<OptimizerType>())
		.def("clearVolumeConstraints", &OptimizerType::clearVolumeConstraints, python::arg("self"))
		.def("getNumVolumeConstraints", &OptimizerType::getNumVolumeConstraints, python::arg("self"))
		.def("getVolumeConstraint", 
			 static_cast<VolumeConstraint& (OptimizerType::*)(std::size_t)>(&OptimizerType::getVolumeConstraint),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("addVolumeConstraint", &OptimizerType::addVolumeConstraint, 
			 (python::arg("self"), python::arg("pt1_idx"), python::arg("pt2_idx"), python::arg("pt3_idx"), 
			  python::arg("pt4_idx"), python::arg("lb"), python::arg("ub")))
		.def("removeVolumeConstraint", 
			 static_cast<void (OptimizerType::*)(std::size_t)>(&OptimizerType::removeVolumeConstraint),
			 (python::arg("self"), python::arg("idx")))
		.def("getVolumeError", 
					 &OptimizerType::getVolumeError<Math::VectorArray<Math::CVector<ValueType, OptimizerType::COORDS_DIM> > >, 
					 (python::arg("self"), python::arg("coords")))
		.add_property("numVolumeConstraints", &OptimizerType::getNumVolumeConstraints)
		.add_property("volumeConstraints", python::make_function(&createVolumeConstraintList<OptimizerType>,
																 python::with_custodian_and_ward_postcall<0, 1>()));
}
