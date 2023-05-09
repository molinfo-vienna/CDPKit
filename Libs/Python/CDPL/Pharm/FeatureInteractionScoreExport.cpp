/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureInteractionScoreExport.cpp 
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
#include <boost/shared_ptr.hpp>

#include "CDPL/Pharm/FeatureInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct FeatureInteractionScoreWrapper : CDPL::Pharm::FeatureInteractionScore, boost::python::wrapper<CDPL::Pharm::FeatureInteractionScore> 
	{
	
		typedef boost::shared_ptr<FeatureInteractionScoreWrapper> SharedPointer;

		double operator()(const CDPL::Pharm::Feature& ftr1, const CDPL::Pharm::Feature& ftr2) const {
			return this->get_override("__call__")(boost::ref(ftr1), boost::ref(ftr2));
		}

		double operator()(const CDPL::Math::Vector3D& ftr1_pos, const CDPL::Pharm::Feature& ftr2) const {
			return this->get_override("__call__")(boost::ref(ftr1_pos), boost::ref(ftr2));
		}
	};

	double callOperator1(CDPL::Pharm::FeatureInteractionScore& score, CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
	{
		return score(ftr1, ftr2);
	}

	double callOperator2(CDPL::Pharm::FeatureInteractionScore& score, const CDPL::Math::Vector3D& ftr1_pos, CDPL::Pharm::Feature& ftr2)
	{
		return score(ftr1_pos, ftr2);
	}
}


void CDPLPythonPharm::exportFeatureInteractionScore()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<FeatureInteractionScoreWrapper, FeatureInteractionScoreWrapper::SharedPointer,
										 boost::noncopyable>("FeatureInteractionScore", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureInteractionScore>())
		.def("__call__", python::pure_virtual(&callOperator1), python::arg("self"), python::arg("ftr1"), python::arg("ftr2"))
		.def("__call__", python::pure_virtual(&callOperator2), python::arg("self"), python::arg("ftr1_pos"), python::arg("ftr2"));

	python::register_ptr_to_python<Pharm::FeatureInteractionScore::SharedPointer>();
}
