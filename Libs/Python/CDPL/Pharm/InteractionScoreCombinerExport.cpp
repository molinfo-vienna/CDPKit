/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionScoreCombinerExport.cpp 
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

#include "CDPL/Pharm/InteractionScoreCombiner.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Pharm::InteractionScoreCombiner& comb, 
					  CDPL::Math::Vector3D& ftr1_pos, CDPL::Pharm::Feature& ftr2)
    {
		return comb(ftr1_pos, ftr2);
    }
}


void CDPLPythonPharm::exportInteractionScoreCombiner()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::InteractionScoreCombiner, 
				   boost::noncopyable>("InteractionScoreCombiner", python::no_init)
		.def(python::init<const Pharm::InteractionScoreCombiner&>(
				 (python::arg("self"), python::arg("comb"))))
		.def(python::init<const Pharm::InteractionScoreCombiner::ScoringFunction&, 
			 const Pharm::InteractionScoreCombiner::ScoringFunction&, const Pharm::InteractionScoreCombiner::CombinationFunction&>(
				 (python::arg("self"), python::arg("func1"), python::arg("func2"), python::arg("comb_func"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::InteractionScoreCombiner>())
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::InteractionScoreCombiner::operator=), 
			 (python::arg("self"), python::arg("con")), python::return_self<>())
		.def("__call__", &callOperator, 
			 (python::arg("self"), python::arg("ftr1_pos"), python::arg("ftr2")));
}
