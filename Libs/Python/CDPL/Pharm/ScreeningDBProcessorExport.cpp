/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningDBProcessorExport.cpp 
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

#include "CDPL/Pharm/ScreeningDBProcessor.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportScreeningDBProcessor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::ScreeningDBProcessor, Pharm::ScreeningDBProcessor::SharedPointer, boost::noncopyable> 
		cl("ScreeningDBProcessor", python::no_init);

	python::scope scope = cl;
  
	python::enum_<Pharm::ScreeningDBProcessor::HitReportMode>("HitReportMode")
		.value("FIRST_MATCHING_CONF", Pharm::ScreeningDBProcessor::FIRST_MATCHING_CONF)
		.value("BEST_MATCHING_CONF", Pharm::ScreeningDBProcessor::BEST_MATCHING_CONF)
		.value("ALL_MATCHING_CONFS", Pharm::ScreeningDBProcessor::ALL_MATCHING_CONFS)
		.export_values();

	python::class_<Pharm::ScreeningDBProcessor::SearchHit/*, boost::noncopyable*/>("SearchHit", python::no_init)
		.def(python::init<const Pharm::ScreeningDBProcessor&, const Pharm::Pharmacophore&, const Pharm::Pharmacophore&, const Chem::Molecule&, 
			 const Math::Matrix4D&, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("db_proc"), python::arg("qry_pharm"), python::arg("hit_pharm"), python::arg("mol"), 
				  python::arg("xform"), python::arg("pharm_idx"), python::arg("mol_idx"), python::arg("conf_idx")))
			 [python::with_custodian_and_ward<1, 2, python::with_custodian_and_ward<1, 3, python::with_custodian_and_ward<1, 4, 
			  python::with_custodian_and_ward<1, 5, python::with_custodian_and_ward<1, 5> > > > >()])
		.def(python::init<const Pharm::ScreeningDBProcessor::SearchHit&>((python::arg("self"), python::arg("hit")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::ScreeningDBProcessor::SearchHit>())	
		.def("assign", &Pharm::ScreeningDBProcessor::SearchHit::operator=, (python::arg("self"), python::arg("hit")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("getDBProcessor", &Pharm::ScreeningDBProcessor::SearchHit::getDBProcessor, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getQueryPharmacophore", &Pharm::ScreeningDBProcessor::SearchHit::getQueryPharmacophore, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitPharmacophore", &Pharm::ScreeningDBProcessor::SearchHit::getHitPharmacophore, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitMolecule", &Pharm::ScreeningDBProcessor::SearchHit::getHitMolecule, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitAlignmentTransform", &Pharm::ScreeningDBProcessor::SearchHit::getHitAlignmentTransform, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitPharmacophoreIndex", &Pharm::ScreeningDBProcessor::SearchHit::getHitPharmacophoreIndex, python::arg("self"))
		.def("getHitMoleculeIndex", &Pharm::ScreeningDBProcessor::SearchHit::getHitMoleculeIndex, python::arg("self"))
		.def("getHitConformationIndex", &Pharm::ScreeningDBProcessor::SearchHit::getHitConformationIndex, python::arg("self"))
		.add_property("dbProcessor", 
					  python::make_function(&Pharm::ScreeningDBProcessor::SearchHit::getDBProcessor,
											python::return_internal_reference<>()))
		.add_property("queryPharmacophore", 
					  python::make_function(&Pharm::ScreeningDBProcessor::SearchHit::getQueryPharmacophore,
											python::return_internal_reference<>()))
		.add_property("hitPharmacophore", 
					  python::make_function(&Pharm::ScreeningDBProcessor::SearchHit::getHitPharmacophore,
											python::return_internal_reference<>()))
		.add_property("hitMolecule", 
					  python::make_function(&Pharm::ScreeningDBProcessor::SearchHit::getHitMolecule,
											python::return_internal_reference<>()))
		.add_property("hitAlignmentTransform", 
					  python::make_function(&Pharm::ScreeningDBProcessor::SearchHit::getHitAlignmentTransform,
											python::return_internal_reference<>()))
		.add_property("hitPharmacophoreIndex", &Pharm::ScreeningDBProcessor::SearchHit::getHitPharmacophoreIndex)
		.add_property("hitMoleculeIndex", &Pharm::ScreeningDBProcessor::SearchHit::getHitMoleculeIndex)
		.add_property("hitConformationIndex", &Pharm::ScreeningDBProcessor::SearchHit::getHitConformationIndex);

	cl
		.def(python::init<Pharm::ScreeningDBAccessor&>((python::arg("self"), python::arg("db_acc")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::ScreeningDBProcessor>())	
		.def("setDBAccessor", &Pharm::ScreeningDBProcessor::setDBAccessor, 
			 (python::arg("self"), python::arg("db_acc")), python::with_custodian_and_ward<1, 2>())
		.def("getDBAccessor", &Pharm::ScreeningDBProcessor::getDBAccessor, python::arg("self"),
			 python::return_internal_reference<>())
		.def("setHitReportMode", &Pharm::ScreeningDBProcessor::setHitReportMode, 
			 (python::arg("self"), python::arg("mode")))
		.def("getHitReportMode", &Pharm::ScreeningDBProcessor::getHitReportMode, python::arg("self"))
		.def("setMaxNumOmittedFeatures", &Pharm::ScreeningDBProcessor::setMaxNumOmittedFeatures, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumOmittedFeatures", &Pharm::ScreeningDBProcessor::getMaxNumOmittedFeatures, python::arg("self"))
		.def("checkXVolumeClashes", &Pharm::ScreeningDBProcessor::checkXVolumeClashes, 
			 (python::arg("self"), python::arg("check")))
		.def("xVolumeClashesChecked", &Pharm::ScreeningDBProcessor::xVolumeClashesChecked,
			 python::arg("self"))
		.def("seekBestAlignments", &Pharm::ScreeningDBProcessor::seekBestAlignments, 
			 (python::arg("self"), python::arg("seek_best")))
		.def("bestAlignmentsSeeked", &Pharm::ScreeningDBProcessor::bestAlignmentsSeeked, 
			 python::arg("self"))
		.def("setHitCallbackFunction", &Pharm::ScreeningDBProcessor::setHitCallbackFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getHitCallbackFunction", &Pharm::ScreeningDBProcessor::getHitCallbackFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setProgressCallbackFunction", &Pharm::ScreeningDBProcessor::setProgressCallbackFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getProgressCallbackFunction", &Pharm::ScreeningDBProcessor::getProgressCallbackFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setScoringFunction", &Pharm::ScreeningDBProcessor::setScoringFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getScoringFunction", &Pharm::ScreeningDBProcessor::getScoringFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("searchDB", &Pharm::ScreeningDBProcessor::searchDB, 
			 (python::arg("self"), python::arg("pharm"), python::arg("mol_start_idx") = 0, python::arg("mol_end_idx") = 0))
		.add_property("dbAcccessor", python::make_function(&Pharm::ScreeningDBProcessor::getDBAccessor,
														   python::return_internal_reference<>()),
					  python::make_function(&Pharm::ScreeningDBProcessor::setDBAccessor, 
											python::with_custodian_and_ward<1, 2>()))
		.add_property("hitCallbackFunction", python::make_function(&Pharm::ScreeningDBProcessor::getHitCallbackFunction,
																   python::return_internal_reference<>()),
					  &Pharm::ScreeningDBProcessor::setHitCallbackFunction)
		.add_property("progressCallbackFunction", python::make_function(&Pharm::ScreeningDBProcessor::getProgressCallbackFunction,
																		python::return_internal_reference<>()),
					  &Pharm::ScreeningDBProcessor::setProgressCallbackFunction)
		.add_property("scoringFunction", python::make_function(&Pharm::ScreeningDBProcessor::getScoringFunction,
															   python::return_internal_reference<>()),
					  &Pharm::ScreeningDBProcessor::setScoringFunction)
		.add_property("hitReportMode", &Pharm::ScreeningDBProcessor::getHitReportMode,
					  &Pharm::ScreeningDBProcessor::setHitReportMode)
		.add_property("maxNumOmittedFeatures", &Pharm::ScreeningDBProcessor::getMaxNumOmittedFeatures,
					  &Pharm::ScreeningDBProcessor::setMaxNumOmittedFeatures)
		.add_property("checkXVolumes", &Pharm::ScreeningDBProcessor::xVolumeClashesChecked,
					  &Pharm::ScreeningDBProcessor::checkXVolumeClashes)
		.add_property("bestAlignments", &Pharm::ScreeningDBProcessor::bestAlignmentsSeeked,
					  &Pharm::ScreeningDBProcessor::seekBestAlignments);
}
