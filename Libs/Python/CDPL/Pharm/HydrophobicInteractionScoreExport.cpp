/* 
 * HydrophobicInteractionScoreExport.cpp 
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

#include "CDPL/Pharm/HydrophobicInteractionScore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportHydrophobicInteractionScore()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::HydrophobicInteractionScore, Pharm::HydrophobicInteractionScore::SharedPointer,
                   python::bases<Pharm::FeatureDistanceScore>, boost::noncopyable>("HydrophobicInteractionScore", python::no_init)
        .def(python::init<const Pharm::HydrophobicInteractionScore&>((python::arg("self"), python::arg("score"))))
        .def(python::init<double, double>((python::arg("self"), 
                                           python::arg("min_dist") = Pharm::HydrophobicInteractionScore::DEF_MIN_DISTANCE,
                                           python::arg("max_dist") = Pharm::HydrophobicInteractionScore::DEF_MAX_DISTANCE)))
        .def_readonly("DEF_MIN_DISTANCE", Pharm::HydrophobicInteractionScore::DEF_MIN_DISTANCE)
        .def_readonly("DEF_MAX_DISTANCE", Pharm::HydrophobicInteractionScore::DEF_MAX_DISTANCE);
}
