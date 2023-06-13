/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureContainerExport.cpp 
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

#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/PropertyContainerVisitor.hpp"

#include "FeatureContainerVisitor.hpp"
#include "ClassExports.hpp"


namespace
{

	struct FeatureContainerWrapper : CDPL::Pharm::FeatureContainer, boost::python::wrapper<CDPL::Pharm::FeatureContainer> 
	{
	
		typedef std::shared_ptr<FeatureContainerWrapper> SharedPointer;

		FEATURECONTAINER_IMPL()
	};
}


void CDPLPythonPharm::exportFeatureContainer()
{
	using namespace boost;
	using namespace CDPL;

	python::scope scope = python::class_<FeatureContainerWrapper, FeatureContainerWrapper::SharedPointer,
										 python::bases<Chem::Entity3DContainer, Base::PropertyContainer>,
										 boost::noncopyable>("FeatureContainer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(FeatureContainerVirtualFunctionsVisitor<FeatureContainerWrapper>())
		.def(FeatureContainerSpecialFunctionsVisitor(false))
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor())
		.add_property("numFeatures", &Pharm::FeatureContainer::getNumFeatures);

	python::register_ptr_to_python<Pharm::FeatureContainer::SharedPointer>();
}
