/* 
 * GRAILDataSetGeneratorExport.cpp 
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

#include "CDPL/GRAIL/GRAILDataSetGenerator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    CDPL::Grid::DRegularGrid::SharedPointer
    calcAtomDensityGrid(CDPL::GRAIL::GRAILDataSetGenerator& gen, CDPL::Chem::AtomContainer& atoms,
                        const CDPL::Chem::Atom3DCoordinatesFunction& coords_func,
                        const std::string& grid_name)
    {
        return gen.calcAtomDensityGrid(atoms, coords_func, grid_name);
    }
}


void CDPLPythonGRAIL::exportGRAILDataSetGenerator()
{
    using namespace boost;
    using namespace CDPL;
  
    python::class_<GRAIL::GRAILDataSetGenerator, GRAIL::GRAILDataSetGenerator::SharedPointer,
                   boost::noncopyable>("GRAILDataSetGenerator", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const GRAIL::GRAILDataSetGenerator&>((python::arg("self"), python::arg("gen"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<GRAIL::GRAILDataSetGenerator>())
        .def("assign", CDPLPythonBase::copyAssOp(&GRAIL::GRAILDataSetGenerator::operator=), 
             (python::arg("self"), python::arg("gen")), python::return_self<>())
        .def("setScoringFunction", &GRAIL::GRAILDataSetGenerator::setScoringFunction, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type"), python::arg("func")))
        .def("removeScoringFunction", &GRAIL::GRAILDataSetGenerator::removeScoringFunction, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")))
        .def("getScoringFunction", &GRAIL::GRAILDataSetGenerator::getScoringFunction, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")),
             python::return_internal_reference<>())
        .def("setGridName", &GRAIL::GRAILDataSetGenerator::setGridName, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type"), python::arg("name")))
        .def("removeGridName", &GRAIL::GRAILDataSetGenerator::removeGridName, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")))
        .def("getGridName", &GRAIL::GRAILDataSetGenerator::getGridName, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")),
             python::return_value_policy<python::copy_const_reference>())
        .def("enableInteraction", &GRAIL::GRAILDataSetGenerator::enableInteraction, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type"), python::arg("enable")))
        .def("isInteractionEnabled", &GRAIL::GRAILDataSetGenerator::isInteractionEnabled, 
             (python::arg("self"), python::arg("ftr_type"), python::arg("tgt_ftr_type")))
        .def("clearEnabledInteractions", &GRAIL::GRAILDataSetGenerator::isInteractionEnabled, python::arg("self"))
        .def("setScoreCombinationFunction", &GRAIL::GRAILDataSetGenerator::setScoreCombinationFunction,
             (python::arg("self"), python::arg("func")))
        .def("getScoreCombinationFunction", &GRAIL::GRAILDataSetGenerator::getScoreCombinationFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("normalizeScores", &GRAIL::GRAILDataSetGenerator::normalizeScores, (python::arg("self"), python::arg("normalize")))
        .def("scoresNormalized", &GRAIL::GRAILDataSetGenerator::scoresNormalized, python::arg("self"))
        .def("diminishScoresByAtomDensity", &GRAIL::GRAILDataSetGenerator::diminishScoresByAtomDensity,
             (python::arg("self"), python::arg("diminish")))
        .def("scoresDiminishedByAtomDensity", &GRAIL::GRAILDataSetGenerator::scoresDiminishedByAtomDensity, python::arg("self"))
        .def("storeEnvironmentAtomDensityGrid", &GRAIL::GRAILDataSetGenerator::storeEnvironmentAtomDensityGrid,
             (python::arg("self"), python::arg("store")))
        .def("environmentAtomDensityGridStored", &GRAIL::GRAILDataSetGenerator::environmentAtomDensityGridStored, python::arg("self"))
        .def("setEnvironmentAtomDensityGridName", &GRAIL::GRAILDataSetGenerator::setEnvironmentAtomDensityGridName,
             (python::arg("self"), python::arg("")))
        .def("getEnvironmentAtomDensityGridName", &GRAIL::GRAILDataSetGenerator::getEnvironmentAtomDensityGridName, python::arg("self"),
             python::return_value_policy<python::copy_const_reference>())
        .def("getGridStepSize", &GRAIL::GRAILDataSetGenerator::getGridStepSize, python::arg("self"))
        .def("setGridStepSize", &GRAIL::GRAILDataSetGenerator::setGridStepSize, (python::arg("self"), python::arg("size")))
        .def("getGridXSize", &GRAIL::GRAILDataSetGenerator::getGridXSize, python::arg("self"))
        .def("setGridXSize", &GRAIL::GRAILDataSetGenerator::setGridXSize, (python::arg("self"), python::arg("size")))
        .def("getGridYSize", &GRAIL::GRAILDataSetGenerator::getGridYSize, python::arg("self"))
        .def("setGridYSize", &GRAIL::GRAILDataSetGenerator::setGridYSize, (python::arg("self"), python::arg("size")))
        .def("getGridZSize", &GRAIL::GRAILDataSetGenerator::getGridZSize, python::arg("self"))
        .def("setGridZSize", &GRAIL::GRAILDataSetGenerator::setGridZSize, (python::arg("self"), python::arg("size")))
        .def("getGridTransform", &GRAIL::GRAILDataSetGenerator::getGridTransform, python::arg("self"),
             python::return_internal_reference<>())
        .def("setGridTransform", &GRAIL::GRAILDataSetGenerator::setGridTransform<Math::Matrix4D>, 
             (python::arg("self"), python::arg("xform")))
        .def("setGridParamsForBoundingBox", &GRAIL::GRAILDataSetGenerator::setGridParamsForBoundingBox,
             (python::arg("self"), python::arg("bbox_min"), python::arg("bbox_max"),
              python::arg("step_size") = GRAIL::GRAILDataSetGenerator::DEF_GRID_STEP_SIZE))
        .def("getPharmacophoreGenerator", static_cast<Pharm::DefaultPharmacophoreGenerator& (GRAIL::GRAILDataSetGenerator::*)()>
             (&GRAIL::GRAILDataSetGenerator::getPharmacophoreGenerator), python::arg("self"),
             python::return_internal_reference<>())
        .def("setPharmacophoreProcessingFunction", &GRAIL::GRAILDataSetGenerator::setPharmacophoreProcessingFunction,
             (python::arg("self"), python::arg("func")))
        .def("getPharmacophoreProcessingFunction", &GRAIL::GRAILDataSetGenerator::getPharmacophoreProcessingFunction,
             python::arg("self"), python::return_internal_reference<>())
        .def("calcInteractionGrids", &GRAIL::GRAILDataSetGenerator::calcInteractionGrids,
             (python::arg("self"), python::arg("tgt_env"), python::arg("coords_func"), python::arg("grid_set"), python::arg("append") = false))
        .def("calcAtomDensityGrid", &calcAtomDensityGrid,
             (python::arg("self"), python::arg("atoms"), python::arg("coords_func"), python::arg("grid_name")))
        .def_readonly("DEF_GRID_STEP_SIZE", GRAIL::GRAILDataSetGenerator::DEF_GRID_STEP_SIZE)
        .add_property("normalizedScores", &GRAIL::GRAILDataSetGenerator::scoresNormalized,
                      &GRAIL::GRAILDataSetGenerator::normalizeScores)
        .add_property("scoreCombinationFunction",
                      python::make_function(&GRAIL::GRAILDataSetGenerator::getScoreCombinationFunction, python::return_internal_reference<>()),
                      &GRAIL::GRAILDataSetGenerator::setScoreCombinationFunction)
        .add_property("pharmProcessingFunction",
                      python::make_function(&GRAIL::GRAILDataSetGenerator::getPharmacophoreProcessingFunction, python::return_internal_reference<>()),
                      &GRAIL::GRAILDataSetGenerator::setPharmacophoreProcessingFunction)
        .add_property("gridStepSize", &GRAIL::GRAILDataSetGenerator::getGridStepSize, &GRAIL::GRAILDataSetGenerator::setGridStepSize)
        .add_property("gridXSize", &GRAIL::GRAILDataSetGenerator::getGridXSize, &GRAIL::GRAILDataSetGenerator::setGridXSize)
        .add_property("gridYSize", &GRAIL::GRAILDataSetGenerator::getGridYSize, &GRAIL::GRAILDataSetGenerator::setGridYSize)
        .add_property("gridZSize", &GRAIL::GRAILDataSetGenerator::getGridZSize, &GRAIL::GRAILDataSetGenerator::setGridZSize)
        .add_property("gridTransform", 
                      python::make_function(&GRAIL::GRAILDataSetGenerator::getGridTransform, python::return_internal_reference<>()),
                      &GRAIL::GRAILDataSetGenerator::setGridTransform<Math::Matrix4D>)
        .add_property("pharmGenerator", 
                      python::make_function(static_cast<Pharm::DefaultPharmacophoreGenerator& (GRAIL::GRAILDataSetGenerator::*)()>
                                            (&GRAIL::GRAILDataSetGenerator::getPharmacophoreGenerator),
                                            python::return_internal_reference<>()))
        .add_property("dimScoresByAtomDensity", &GRAIL::GRAILDataSetGenerator::scoresDiminishedByAtomDensity,
                      &GRAIL::GRAILDataSetGenerator::diminishScoresByAtomDensity)
        .add_property("storeEnvAtomDensityGrid", &GRAIL::GRAILDataSetGenerator::environmentAtomDensityGridStored,
                      &GRAIL::GRAILDataSetGenerator::storeEnvironmentAtomDensityGrid)
        .add_property("envAtomDensityGridName",
                      python::make_function(&GRAIL::GRAILDataSetGenerator::getEnvironmentAtomDensityGridName,
                                            python::return_value_policy<python::copy_const_reference>()),
                      &GRAIL::GRAILDataSetGenerator::setEnvironmentAtomDensityGridName);
}
