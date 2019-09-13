/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DGCoordinatesGeneratorExport.cpp 
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

#include "CDPL/Util/DGCoordinatesGenerator.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Math/Vector.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{
	
	template <typename GeneratorType>
	struct VolumeConstraintList {

		VolumeConstraintList(GeneratorType& gen): generator(gen) {}
		
		std::size_t getSize() const {
			return generator.getNumVolumeConstraints();
		}

		typename GeneratorType::VolumeConstraint& getConstraint(std::size_t idx) const {
			return generator.getVolumeConstraint(idx);
		}

		void removeConstraint(std::size_t idx) {
			generator.removeVolumeConstraint(idx);
		}

		GeneratorType& generator;
	};

	template <typename GeneratorType>
	VolumeConstraintList<GeneratorType> createVolumeConstraintList(GeneratorType& gen) 
	{
		return VolumeConstraintList<GeneratorType>(gen);
	}

	template <typename GeneratorType>
	struct DistanceConstraintList {

		DistanceConstraintList(GeneratorType& gen): generator(gen) {}
		
		std::size_t getSize() const {
			return generator.getNumDistanceConstraints();
		}

		typename GeneratorType::DistanceConstraint& getConstraint(std::size_t idx) const {
			return generator.getDistanceConstraint(idx);
		}

		void removeConstraint(std::size_t idx) {
			generator.removeDistanceConstraint(idx);
		}

		GeneratorType& generator;
	};

	template <typename GeneratorType>
	DistanceConstraintList<GeneratorType> createDistanceConstraintList(GeneratorType& gen) 
	{
		return DistanceConstraintList<GeneratorType>(gen);
	}

	template <typename GeneratorType>
	class DGCoordinatesGeneratorVisitor : 
		public boost::python::def_visitor<DGCoordinatesGeneratorVisitor<GeneratorType> >
	{
		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace CDPL;
			using namespace boost;

			typedef typename GeneratorType::DistanceConstraint DistanceConstraint;
			typedef typename GeneratorType::ValueType ValueType;
			typedef DistanceConstraintList<GeneratorType> DistanceConstraintList;
		
			python::scope scope = cl;

			python::class_<DistanceConstraintList>("DistanceConstraintList", python::no_init)
				.def("__len__", &DistanceConstraintList::getSize, python::arg("self"))
				.def("__getitem__", &DistanceConstraintList::getConstraint, (python::arg("self"), python::arg("idx")), 
					 python::return_internal_reference<1>())
				.def("__delitem__", &DistanceConstraintList::removeConstraint, (python::arg("self"), python::arg("idx")));

			python::class_<DistanceConstraint>("DistanceConstraint", python::no_init)
				.def(python::init<std::size_t, std::size_t, const ValueType&, const ValueType&>(
						 (python::arg("self"), python::arg("pt1_idx"), python::arg("pt2_idx"), python::arg("lb"),
						  python::arg("ub"))))
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
				.def(python::init<const GeneratorType&>((python::arg("self"), python::arg("gen"))))
				.def(CDPLPythonBase::ObjectIdentityCheckVisitor<GeneratorType>())
				.def("assign", CDPLPythonBase::copyAssOp(&GeneratorType::operator=), 
					 (python::arg("self"), python::arg("gen")), python::return_self<>())
				.def("clearDistanceConstraints", &GeneratorType::clearDistanceConstraints, python::arg("self"))
				.def("getNumDistanceConstraints", &GeneratorType::getNumDistanceConstraints, python::arg("self"))
				.def("getDistanceConstraint", 
					 static_cast<DistanceConstraint& (GeneratorType::*)(std::size_t)>(&GeneratorType::getDistanceConstraint),
					 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
				.def("addDistanceConstraint", &GeneratorType::addDistanceConstraint, 
					 (python::arg("self"), python::arg("pt1_idx"), python::arg("pt2_idx"), python::arg("lb"), 
					  python::arg("ub")))
				.def("removeDistanceConstraint", 
					 static_cast<void (GeneratorType::*)(std::size_t)>(&GeneratorType::removeDistanceConstraint),
					 (python::arg("self"), python::arg("idx")))
				.def("setNumCycles", &GeneratorType::setNumCycles, (python::arg("self"), python::arg("num_cycles")))
				.def("getNumCycles", &GeneratorType::getNumCycles, python::arg("self"))
				.def("setCycleStepCountFactor", &GeneratorType::setCycleStepCountFactor, (python::arg("self"), python::arg("fact")))
				.def("getCycleStepCountFactor", &GeneratorType::getCycleStepCountFactor, python::arg("self"))
				.def("setStartLearningRate", &GeneratorType::setStartLearningRate, (python::arg("self"), python::arg("rate")))
				.def("getStartLearningRate", &GeneratorType::getStartLearningRate, python::arg("self"), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("setLearningRateDecrement", &GeneratorType::setLearningRateDecrement, (python::arg("self"), python::arg("decr")))
				.def("getLearningRateDecrement", &GeneratorType::getLearningRateDecrement, python::arg("self"), 
					 python::return_value_policy<python::copy_const_reference>())
				.def("setRandomSeed", &GeneratorType::setRandomSeed, (python::arg("self"), python::arg("seed")))
				.def("generate", 
					 &GeneratorType::template generate<Math::VectorArray<Math::CVector<ValueType, GeneratorType::COORDS_DIM> > >, 
					 (python::arg("self"), python::arg("num_points"), python::arg("coords")))
				.def("getDistanceError", 
					 &GeneratorType::template getDistanceError<Math::VectorArray<Math::CVector<ValueType, GeneratorType::COORDS_DIM> > >, 
					 (python::arg("self"), python::arg("coords")))
				.def_readonly("COORDS_DIM", GeneratorType::COORDS_DIM)
				.def_readonly("DEF_NUM_CYCLES", GeneratorType::DEF_NUM_CYCLES)
				.def_readonly("DEF_CYCLE_STEP_COUNT_FACTOR", GeneratorType::DEF_CYCLE_STEP_COUNT_FACTOR)
				.def_readonly("DEF_START_LEARNING_RATE", GeneratorType::DEF_START_LEARNING_RATE)
				.def_readonly("DEF_LEARNING_RATE_DECREMENT", GeneratorType::DEF_LEARNING_RATE_DECREMENT)
				.add_property("numCycles", &GeneratorType::getNumCycles, &GeneratorType::setNumCycles)
				.add_property("cycleStepCountFactor", &GeneratorType::getCycleStepCountFactor, &GeneratorType::setCycleStepCountFactor)
				.add_property("startLearningRate", python::make_function(&GeneratorType::getStartLearningRate, 
																		 python::return_value_policy<python::copy_const_reference>()),
							  &GeneratorType::setStartLearningRate)
				.add_property("learningRateDecrement", python::make_function(&GeneratorType::getLearningRateDecrement, 
																			 python::return_value_policy<python::copy_const_reference>()),
							  &GeneratorType::setLearningRateDecrement)
				.add_property("numDistanceConstraints", &GeneratorType::getNumDistanceConstraints)
				.add_property("distanceConstraints", python::make_function(&createDistanceConstraintList<GeneratorType>,
																		   python::with_custodian_and_ward_postcall<0, 1>()));
		}
	};
}


void CDPLPythonUtil::exportDGCoordinatesGenerator()
{
    using namespace boost;
    using namespace CDPL;

	python::class_<Util::DGCoordinatesGenerator<2, double> >("DG2DCoordinatesGenerator", python::no_init)
		.def(DGCoordinatesGeneratorVisitor<Util::DGCoordinatesGenerator<2, double> >());

// 3D specialization

	typedef Util::DGCoordinatesGenerator<3, double> GeneratorType;
	typedef GeneratorType::VolumeConstraint VolumeConstraint;
	typedef GeneratorType::ValueType ValueType;
	typedef VolumeConstraintList<GeneratorType> VolumeConstraintList;

	python::class_<GeneratorType> cl("DG3DCoordinatesGenerator", python::no_init);

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
		.def(DGCoordinatesGeneratorVisitor<GeneratorType>())
		.def("clearVolumeConstraints", &GeneratorType::clearVolumeConstraints, python::arg("self"))
		.def("getNumVolumeConstraints", &GeneratorType::getNumVolumeConstraints, python::arg("self"))
		.def("getVolumeConstraint", 
			 static_cast<VolumeConstraint& (GeneratorType::*)(std::size_t)>(&GeneratorType::getVolumeConstraint),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("addVolumeConstraint", &GeneratorType::addVolumeConstraint, 
			 (python::arg("self"), python::arg("pt1_idx"), python::arg("pt2_idx"), python::arg("pt3_idx"), 
			  python::arg("pt4_idx"), python::arg("lb"), python::arg("ub")))
		.def("removeVolumeConstraint", 
			 static_cast<void (GeneratorType::*)(std::size_t)>(&GeneratorType::removeVolumeConstraint),
			 (python::arg("self"), python::arg("idx")))
		.def("getVolumeError", 
					 &GeneratorType::getVolumeError<Math::VectorArray<Math::CVector<ValueType, GeneratorType::COORDS_DIM> > >, 
					 (python::arg("self"), python::arg("coords")))
		.add_property("numVolumeConstraints", &GeneratorType::getNumVolumeConstraints)
		.add_property("volumeConstraints", python::make_function(&createVolumeConstraintList<GeneratorType>,
																 python::with_custodian_and_ward_postcall<0, 1>()));
}
