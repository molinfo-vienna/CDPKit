/* 
 * PDBDataExport.cpp 
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


#include <algorithm>
#include <utility>
#include <functional>

#include <boost/python.hpp>

#include "CDPL/Biomol/PDBData.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    boost::python::object getRecordTypes(const CDPL::Biomol::PDBData& pdb_data) {
        using namespace boost;
            
        python::list types;
            
        std::for_each(pdb_data.getRecordsBegin(), pdb_data.getRecordsEnd(),
                      std::bind(&python::list::append<CDPL::Biomol::PDBData::RecordType>, std::ref(types),
                                std::bind(&CDPL::Biomol::PDBData::Record::first, std::placeholders::_1)));

        return std::move(types);
    }

    boost::python::object getRecordData(CDPL::Biomol::PDBData& pdb_data) {
        using namespace boost;
            
        python::list values;

        std::for_each(pdb_data.getRecordsBegin(), pdb_data.getRecordsEnd(),
                      std::bind(&python::list::append<std::string>, std::ref(values),
                                std::bind(&CDPL::Biomol::PDBData::Record::second, std::placeholders::_1)));

        return std::move(values);
    }

    boost::python::object getRecords(CDPL::Biomol::PDBData& pdb_data)
    {
        using namespace boost;

        python::list records;

        CDPL::Biomol::PDBData::RecordIterator records_end = pdb_data.getRecordsEnd();
            
        for (CDPL::Biomol::PDBData::RecordIterator it = pdb_data.getRecordsBegin(); it != records_end; ++it)  
            records.append(python::make_tuple(it->first, it->second));

        return std::move(records);
    }

    void setRecord(CDPL::Biomol::PDBData& pdb_data, const CDPL::Biomol::PDBData::RecordType& type, const std::string& data) 
    {
        pdb_data.setRecord(type, data);
    }
}


void CDPLPythonBiomol::exportPDBData()
{
    using namespace boost;
    using namespace CDPL;

    bool (Biomol::PDBData::*removeRecordFunc)(const Biomol::PDBData::RecordType&) = &Biomol::PDBData::removeRecord;
    const std::string& (Biomol::PDBData::*getDataFunc)(const Biomol::PDBData::RecordType&) const = &Biomol::PDBData::getData;
 
    python::class_<Biomol::PDBData, Biomol::PDBData::SharedPointer> pdb_data_class("PDBData", python::no_init);
    python::scope scope = pdb_data_class;

    python::enum_<Biomol::PDBData::RecordType>("RecordType")
        .value("HEADER", Biomol::PDBData::HEADER)
        .value("OBSLTE", Biomol::PDBData::OBSLTE)
        .value("TITLE", Biomol::PDBData::TITLE)
        .value("SPLIT", Biomol::PDBData::SPLIT)
        .value("CAVEAT", Biomol::PDBData::CAVEAT)
        .value("COMPND", Biomol::PDBData::COMPND)
        .value("SOURCE", Biomol::PDBData::SOURCE)
        .value("KEYWDS", Biomol::PDBData::KEYWDS)
        .value("EXPDTA", Biomol::PDBData::EXPDTA)
        .value("AUTHOR", Biomol::PDBData::AUTHOR)
        .value("REVDAT", Biomol::PDBData::REVDAT)
        .value("SPRSDE", Biomol::PDBData::SPRSDE)
        .value("JRNL", Biomol::PDBData::JRNL)
        .value("REMARK", Biomol::PDBData::REMARK)
        .value("DBREF", Biomol::PDBData::DBREF)
        .value("DBREF1", Biomol::PDBData::DBREF1)
        .value("DBREF2", Biomol::PDBData::DBREF2)
        .value("SEQADV", Biomol::PDBData::SEQADV)
        .value("SEQRES", Biomol::PDBData::SEQRES)
        .value("MODRES", Biomol::PDBData::MODRES)
        .value("HET", Biomol::PDBData::HET)
        .value("FORMUL", Biomol::PDBData::FORMUL)
        .value("HETNAM", Biomol::PDBData::HETNAM)
        .value("HETSYN", Biomol::PDBData::HETSYN)
        .value("HELIX", Biomol::PDBData::HELIX)
        .value("SHEET", Biomol::PDBData::SHEET)
        .value("TURN", Biomol::PDBData::TURN)
        .value("SSBOND", Biomol::PDBData::SSBOND)
        .value("LINK", Biomol::PDBData::LINK)
        .value("CISPEP", Biomol::PDBData::CISPEP)
        .value("SITE", Biomol::PDBData::SITE)
        .value("CRYST1", Biomol::PDBData::CRYST1)
        .value("MTRIX1", Biomol::PDBData::MTRIX1)
        .value("MTRIX2", Biomol::PDBData::MTRIX2)
        .value("MTRIX3", Biomol::PDBData::MTRIX3)
        .value("ORIGX1", Biomol::PDBData::ORIGX1)
        .value("ORIGX2", Biomol::PDBData::ORIGX2)
        .value("ORIGX3", Biomol::PDBData::ORIGX3)
        .value("SCALE1", Biomol::PDBData::SCALE1)
        .value("SCALE2", Biomol::PDBData::SCALE2)
        .value("SCALE3", Biomol::PDBData::SCALE3)
        .value("STRUCTURE_ID", Biomol::PDBData::STRUCTURE_ID)
        .value("DEPOSITION_DATE", Biomol::PDBData::DEPOSITION_DATE)
        .value("RESOLUTION", Biomol::PDBData::RESOLUTION)
        .export_values();
    
    pdb_data_class
        .def(python::init<>(python::arg("self")))    
        .def(python::init<const Biomol::PDBData&>((python::arg("self"), python::arg("other"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Biomol::PDBData>())
        .def("getNumRecords", &Biomol::PDBData::getNumRecords, python::arg("self"))
        .def("isEmpty", &Biomol::PDBData::isEmpty, python::arg("self"))
        .def("clear", &Biomol::PDBData::clear, python::arg("self"))
        .def("assign", &Biomol::PDBData::operator=, (python::arg("self"), python::arg("data")), 
             python::return_self<>())
        .def("containsRecord", &Biomol::PDBData::containsRecord, (python::arg("self"), python::arg("type")))
        .def("getData", getDataFunc, (python::arg("self"), python::arg("type")), 
             python::return_value_policy<python::copy_const_reference>())
        .def("removeRecord", removeRecordFunc, (python::arg("self"), python::arg("type")))
        .def("setRecord", &setRecord, (python::arg("self"), python::arg("type"), python::arg("data")))
        .def("getRecordTypes", &getRecordTypes, python::arg("self"))
        .def("getRecordData", &getRecordData, python::arg("self"))
        .def("getRecords", &getRecords, python::arg("self"))
        .def("__len__", &Biomol::PDBData::getNumRecords, python::arg("self"))
        .def("__getitem__", getDataFunc, (python::arg("self"), python::arg("type")), 
             python::return_value_policy<python::copy_const_reference>())
        .def("__setitem__", &setRecord, (python::arg("self"), python::arg("type"), python::arg("data")))
        .def("__delitem__", removeRecordFunc, (python::arg("self"), python::arg("type")))
        .def("__contains__", &Biomol::PDBData::containsRecord, (python::arg("self"), python::arg("type")))
        .add_property("numRecords", &Biomol::PDBData::getNumRecords)
        .add_property("recordTypes", &getRecordTypes)
        .add_property("recordData", &getRecordData)
        .add_property("records", &getRecords);
}
