/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PDBDataExport.cpp 
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


#include <algorithm>

#include <boost/python.hpp>
#include <boost/bind.hpp>

#include "CDPL/Chem/PDBData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	boost::python::object getRecordTypes(const CDPL::Chem::PDBData& pdb_data) {
		using namespace boost;
			
		python::list types;
			
		std::for_each(pdb_data.getRecordsBegin(), pdb_data.getRecordsEnd(),
					  boost::bind(&python::list::append<typename CDPL::Chem::PDBData::RecordType>, boost::ref(types),
								  boost::bind(&CDPL::Chem::PDBData::Record::first, _1)));

		return types;
	}

	boost::python::object getRecordData(CDPL::Chem::PDBData& pdb_data) {
		using namespace boost;
			
		python::list values;

		std::for_each(pdb_data.getRecordsBegin(), pdb_data.getRecordsEnd(),
					  boost::bind(&python::list::append<typename std::string>, boost::ref(values),
								  boost::bind(&CDPL::Chem::PDBData::Record::second, _1)));

		return values;
	}

	boost::python::object getRecords(CDPL::Chem::PDBData& pdb_data)
	{
		using namespace boost;

		python::list records;

		CDPL::Chem::PDBData::RecordIterator records_end = pdb_data.getRecordsEnd();
			
		for (CDPL::Chem::PDBData::RecordIterator it = pdb_data.getRecordsBegin(); it != records_end; ++it)  
			records.append(python::make_tuple(it->first, it->second));

		return records;
	}

	void setRecord(CDPL::Chem::PDBData& pdb_data, const CDPL::Chem::PDBData::RecordType& type, const std::string& data) 
	{
		pdb_data.setRecord(type, data);
	}
}


void CDPLPythonChem::exportPDBData()
{
	using namespace boost;
	using namespace CDPL;

	bool (Chem::PDBData::*removeRecordFunc)(const Chem::PDBData::RecordType&) = &Chem::PDBData::removeRecord;
	const std::string& (Chem::PDBData::*getDataFunc)(const Chem::PDBData::RecordType&) const = &Chem::PDBData::getData;
 
	python::class_<Chem::PDBData, Chem::PDBData::SharedPointer> pdb_data_class("PDBData", python::no_init);
	python::scope scope = pdb_data_class;

	python::enum_<Chem::PDBData::RecordType>("RecordType")
	    .value("HEADER", Chem::PDBData::HEADER)
	    .value("OBSLTE", Chem::PDBData::OBSLTE)
	    .value("TITLE", Chem::PDBData::TITLE)
	    .value("SPLIT", Chem::PDBData::SPLIT)
	    .value("CAVEAT", Chem::PDBData::CAVEAT)
	    .value("COMPND", Chem::PDBData::COMPND)
	    .value("SOURCE", Chem::PDBData::SOURCE)
	    .value("KEYWDS", Chem::PDBData::KEYWDS)
	    .value("EXPDTA", Chem::PDBData::EXPDTA)
	    .value("AUTHOR", Chem::PDBData::AUTHOR)
	    .value("REVDAT", Chem::PDBData::REVDAT)
	    .value("SPRSDE", Chem::PDBData::SPRSDE)
	    .value("JRNL", Chem::PDBData::JRNL)
	    .value("REMARK", Chem::PDBData::REMARK)
	    .value("DBREF", Chem::PDBData::DBREF)
	    .value("DBREF1", Chem::PDBData::DBREF1)
	    .value("DBREF2", Chem::PDBData::DBREF2)
	    .value("SEQADV", Chem::PDBData::SEQADV)
	    .value("SEQRES", Chem::PDBData::SEQRES)
	    .value("MODRES", Chem::PDBData::MODRES)
	    .value("HET", Chem::PDBData::HET)
	    .value("FORMUL", Chem::PDBData::FORMUL)
	    .value("HETNAM", Chem::PDBData::HETNAM)
	    .value("HETSYM", Chem::PDBData::HETSYM)
	    .value("HELIX", Chem::PDBData::HELIX)
	    .value("SHEET", Chem::PDBData::SHEET)
	    .value("TURN", Chem::PDBData::TURN)
	    .value("SSBOND", Chem::PDBData::SSBOND)
	    .value("LINK", Chem::PDBData::LINK)
	    .value("SITE", Chem::PDBData::SITE)
	    .value("CRYST1", Chem::PDBData::CRYST1)
	    .value("MTRIX1", Chem::PDBData::MTRIX1)
	    .value("MTRIX2", Chem::PDBData::MTRIX2)
	    .value("MTRIX3", Chem::PDBData::MTRIX3)
	    .value("ORIGX1", Chem::PDBData::ORIGX1)
	    .value("ORIGX2", Chem::PDBData::ORIGX2)
	    .value("ORIGX3", Chem::PDBData::ORIGX3)
	    .value("SCALE1", Chem::PDBData::SCALE1)
	    .value("SCALE2", Chem::PDBData::SCALE2)
	    .value("SCALE3", Chem::PDBData::SCALE3)
	    .export_values();
	
	pdb_data_class
		.def(python::init<>(python::arg("self")))    
		.def(python::init<const Chem::PDBData&>((python::arg("self"), python::arg("other"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::PDBData>())
		.def("getNumRecords", &Chem::PDBData::getNumRecords, python::arg("self"))
		.def("isEmpty", &Chem::PDBData::isEmpty, python::arg("self"))
		.def("clear", &Chem::PDBData::clear, python::arg("self"))
		.def("assign", &Chem::PDBData::operator=, (python::arg("self"), python::arg("data")), 
			 python::return_self<>())
		.def("containsRecord", &Chem::PDBData::containsRecord, (python::arg("self"), python::arg("type")))
		.def("getData", getDataFunc, (python::arg("self"), python::arg("type")), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("removeRecord", removeRecordFunc, (python::arg("self"), python::arg("type")))
		.def("setRecord", &setRecord, (python::arg("self"), python::arg("type"), python::arg("data")))
		.def("getRecordTypes", &getRecordTypes, python::arg("self"))
		.def("getRecordData", &getRecordData, python::arg("self"))
		.def("getRecords", &getRecords, python::arg("self"))
		.def("__len__", &Chem::PDBData::getNumRecords, python::arg("self"))
		.def("__getitem__", getDataFunc, (python::arg("self"), python::arg("type")), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("__setitem__", &setRecord, (python::arg("self"), python::arg("type"), python::arg("data")))
		.def("__delitem__", removeRecordFunc, (python::arg("self"), python::arg("type")))
		.def("__contains__", &Chem::PDBData::containsRecord, (python::arg("self"), python::arg("type")))
		.add_property("numRecords", &Chem::PDBData::getNumRecords)
		.add_property("recordTypes", &getRecordTypes)
		.add_property("recordData", &getRecordData)
		.add_property("records", &getRecords);
}
