/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningProcessorExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportScreeningProcessor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::ScreeningProcessor, Pharm::ScreeningProcessor::SharedPointer, boost::noncopyable> 
		cl("ScreeningProcessor", python::no_init);

	python::scope scope = cl;
  
	python::enum_<Pharm::ScreeningProcessor::HitReportMode>("HitReportMode")
		.value("FIRST_MATCHING_CONF", Pharm::ScreeningProcessor::FIRST_MATCHING_CONF)
		.value("BEST_MATCHING_CONF", Pharm::ScreeningProcessor::BEST_MATCHING_CONF)
		.value("ALL_MATCHING_CONFS", Pharm::ScreeningProcessor::ALL_MATCHING_CONFS)
		.export_values();

	python::class_<Pharm::ScreeningProcessor::SearchHit/*, boost::noncopyable*/>("SearchHit", python::no_init)
		.def(python::init<const Pharm::ScreeningProcessor&, const Pharm::FeatureContainer&, const Pharm::FeatureContainer&, const Chem::Molecule&, 
			 const Math::Matrix4D&, std::size_t, std::size_t, std::size_t>(
				 (python::arg("self"), python::arg("hit_prov"), python::arg("qry_pharm"), python::arg("hit_pharm"), python::arg("mol"), 
				  python::arg("xform"), python::arg("pharm_idx"), python::arg("mol_idx"), python::arg("conf_idx")))
			 [python::with_custodian_and_ward<1, 2, python::with_custodian_and_ward<1, 3, python::with_custodian_and_ward<1, 4, 
			  python::with_custodian_and_ward<1, 5, python::with_custodian_and_ward<1, 5> > > > >()])
		.def(python::init<const Pharm::ScreeningProcessor::SearchHit&>((python::arg("self"), python::arg("hit")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::ScreeningProcessor::SearchHit>())	
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::ScreeningProcessor::SearchHit::operator=),
			 (python::arg("self"), python::arg("hit")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("getHitProvider", &Pharm::ScreeningProcessor::SearchHit::getHitProvider, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getQueryPharmacophore", &Pharm::ScreeningProcessor::SearchHit::getQueryPharmacophore, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitPharmacophore", &Pharm::ScreeningProcessor::SearchHit::getHitPharmacophore, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitMolecule", &Pharm::ScreeningProcessor::SearchHit::getHitMolecule, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitAlignmentTransform", &Pharm::ScreeningProcessor::SearchHit::getHitAlignmentTransform, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getHitPharmacophoreIndex", &Pharm::ScreeningProcessor::SearchHit::getHitPharmacophoreIndex, python::arg("self"))
		.def("getHitMoleculeIndex", &Pharm::ScreeningProcessor::SearchHit::getHitMoleculeIndex, python::arg("self"))
		.def("getHitConformationIndex", &Pharm::ScreeningProcessor::SearchHit::getHitConformationIndex, python::arg("self"))
		.add_property("hitProvider", 
					  python::make_function(&Pharm::ScreeningProcessor::SearchHit::getHitProvider,
											python::return_internal_reference<>()))
		.add_property("queryPharmacophore", 
					  python::make_function(&Pharm::ScreeningProcessor::SearchHit::getQueryPharmacophore,
											python::return_internal_reference<>()))
		.add_property("hitPharmacophore", 
					  python::make_function(&Pharm::ScreeningProcessor::SearchHit::getHitPharmacophore,
											python::return_internal_reference<>()))
		.add_property("hitMolecule", 
					  python::make_function(&Pharm::ScreeningProcessor::SearchHit::getHitMolecule,
											python::return_internal_reference<>()))
		.add_property("hitAlignmentTransform", 
					  python::make_function(&Pharm::ScreeningProcessor::SearchHit::getHitAlignmentTransform,
											python::return_internal_reference<>()))
		.add_property("hitPharmacophoreIndex", &Pharm::ScreeningProcessor::SearchHit::getHitPharmacophoreIndex)
		.add_property("hitMoleculeIndex", &Pharm::ScreeningProcessor::SearchHit::getHitMoleculeIndex)
		.add_property("hitConformationIndex", &Pharm::ScreeningProcessor::SearchHit::getHitConformationIndex);

	cl
		.def(python::init<Pharm::ScreeningDBAccessor&>((python::arg("self"), python::arg("db_acc")))
			 [python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::ScreeningProcessor>())	
		.def("setDBAccessor", &Pharm::ScreeningProcessor::setDBAccessor, 
			 (python::arg("self"), python::arg("db_acc")), python::with_custodian_and_ward<1, 2>())
		.def("getDBAccessor", &Pharm::ScreeningProcessor::getDBAccessor, python::arg("self"),
			 python::return_internal_reference<>())
		.def("setHitReportMode", &Pharm::ScreeningProcessor::setHitReportMode, 
			 (python::arg("self"), python::arg("mode")))
		.def("getHitReportMode", &Pharm::ScreeningProcessor::getHitReportMode, python::arg("self"))
		.def("setMaxNumOmittedFeatures", &Pharm::ScreeningProcessor::setMaxNumOmittedFeatures, 
			 (python::arg("self"), python::arg("max_num")))
		.def("getMaxNumOmittedFeatures", &Pharm::ScreeningProcessor::getMaxNumOmittedFeatures, python::arg("self"))
		.def("checkXVolumeClashes", &Pharm::ScreeningProcessor::checkXVolumeClashes, 
			 (python::arg("self"), python::arg("check")))
		.def("xVolumeClashesChecked", &Pharm::ScreeningProcessor::xVolumeClashesChecked,
			 python::arg("self"))
		.def("seekBestAlignments", &Pharm::ScreeningProcessor::seekBestAlignments, 
			 (python::arg("self"), python::arg("seek_best")))
		.def("bestAlignmentsSeeked", &Pharm::ScreeningProcessor::bestAlignmentsSeeked, 
			 python::arg("self"))
		.def("setHitCallback", &Pharm::ScreeningProcessor::setHitCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getHitCallback", &Pharm::ScreeningProcessor::getHitCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setProgressCallback", &Pharm::ScreeningProcessor::setProgressCallback, 
			 (python::arg("self"), python::arg("func")))
		.def("getProgressCallback", &Pharm::ScreeningProcessor::getProgressCallback, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("setScoringFunction", &Pharm::ScreeningProcessor::setScoringFunction, 
			 (python::arg("self"), python::arg("func")))
		.def("getScoringFunction", &Pharm::ScreeningProcessor::getScoringFunction, 
			 python::arg("self"), python::return_internal_reference<>())
		.def("searchDB", &Pharm::ScreeningProcessor::searchDB, 
			 (python::arg("self"), python::arg("query"), python::arg("mol_start_idx") = 0, python::arg("mol_end_idx") = 0))
		.add_property("dbAcccessor", python::make_function(&Pharm::ScreeningProcessor::getDBAccessor,
														   python::return_internal_reference<>()),
					  python::make_function(&Pharm::ScreeningProcessor::setDBAccessor, 
											python::with_custodian_and_ward<1, 2>()))
		.add_property("hitCallback", python::make_function(&Pharm::ScreeningProcessor::getHitCallback,
																   python::return_internal_reference<>()),
					  &Pharm::ScreeningProcessor::setHitCallback)
		.add_property("progressCallback", python::make_function(&Pharm::ScreeningProcessor::getProgressCallback,
																		python::return_internal_reference<>()),
					  &Pharm::ScreeningProcessor::setProgressCallback)
		.add_property("scoringFunction", python::make_function(&Pharm::ScreeningProcessor::getScoringFunction,
															   python::return_internal_reference<>()),
					  &Pharm::ScreeningProcessor::setScoringFunction)
		.add_property("hitReportMode", &Pharm::ScreeningProcessor::getHitReportMode,
					  &Pharm::ScreeningProcessor::setHitReportMode)
		.add_property("maxNumOmittedFeatures", &Pharm::ScreeningProcessor::getMaxNumOmittedFeatures,
					  &Pharm::ScreeningProcessor::setMaxNumOmittedFeatures)
		.add_property("checkXVolumes", &Pharm::ScreeningProcessor::xVolumeClashesChecked,
					  &Pharm::ScreeningProcessor::checkXVolumeClashes)
		.add_property("bestAlignments", &Pharm::ScreeningProcessor::bestAlignmentsSeeked,
					  &Pharm::ScreeningProcessor::seekBestAlignments);
}
