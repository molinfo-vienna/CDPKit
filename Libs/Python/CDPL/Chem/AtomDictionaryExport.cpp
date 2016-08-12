/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomDictionaryExport.cpp 
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
#include <boost/python/stl_iterator.hpp>

#include "CDPL/Chem/AtomDictionary.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	CDPL::Chem::AtomDictionary::Entry* makeEntry(unsigned int atom_type, std::size_t iso, const std::string& sym,
												 const std::string& name, std::size_t most_abdt_iso, double avg_weight,
												 std::size_t iupac_grp, bool metal, bool non_metal, boost::python::object val_states,
												 double vdw_rad, boost::python::object cov_radii, double ar_eneg, boost::python::object iso_masses)
	{
		using namespace boost;
		using namespace CDPL;
		using namespace Chem;

		double cov_rad_array[] = { 0, 0, 0 };
		AtomDictionary::Entry::IsotopeMassMap iso_mass_map;
		CDPL::Util::STArray val_state_array;

		if (val_states.ptr() != Py_None) {
			if (python::extract<const CDPL::Util::STArray&>(val_states).check())
				val_state_array = python::extract<const CDPL::Util::STArray&>(val_states);

			else 
				val_state_array.assign(python::stl_input_iterator<std::size_t>(val_states), 
									   python::stl_input_iterator<std::size_t>());
		}

		if (cov_radii.ptr() != Py_None) {
			for (int i = 0; i < len(cov_radii) && i < 3; i++)
				cov_rad_array[i] = python::extract<double>(cov_radii[i]);
		}

		if (iso_masses.ptr() != Py_None) {
			python::dict masses = python::extract<python::dict>(iso_masses);
			python::list items = masses.items();

			for (python::stl_input_iterator<python::tuple> it = python::stl_input_iterator<python::tuple>(items), 
					 end = python::stl_input_iterator<python::tuple>(); it != end; ++it) {

				python::tuple item = *it;

				iso_mass_map.insertEntry(python::extract<std::size_t>(item[0]), python::extract<double>(item[1]));
			}
		}

		return new AtomDictionary::Entry(atom_type, iso, sym, name, most_abdt_iso, avg_weight, iupac_grp, metal, non_metal, val_state_array,
										 vdw_rad, cov_rad_array, ar_eneg, iso_mass_map);
	}

	boost::python::dict getIsotopeMasses(const CDPL::Chem::AtomDictionary::Entry& entry)
	{
		using namespace CDPL;
		using namespace Chem;

		boost::python::dict iso_masses;

		for (AtomDictionary::Entry::IsotopeMassMap::ConstEntryIterator it = entry.getIsotopeMasses().getEntriesBegin(), end = entry.getIsotopeMasses().getEntriesEnd();
			 it != end; ++it)
			iso_masses[it->first] = it->second;

		return iso_masses;
	}

	boost::python::list getEntries(const CDPL::Chem::AtomDictionary& dict)
	{
		using namespace CDPL;
		using namespace Chem;

		boost::python::list entries;

		for (AtomDictionary::ConstEntryIterator it = dict.getEntriesBegin(), end = dict.getEntriesEnd(); it != end; ++it)
			entries.append(boost::ref(*it));

		return entries;
	}

	void setDictionary(boost::python::object dict_obj)
	{	
		using namespace boost;
		using namespace CDPL;

		static python::handle<> dict_handle;

		if (dict_obj.ptr() == Py_None) {
			Chem::AtomDictionary::set(0);
			dict_handle = python::handle<>();
			return;
		}

		Chem::AtomDictionary::set(python::extract<const CDPL::Chem::AtomDictionary*>(dict_obj));
		dict_handle = python::handle<>(python::borrowed(dict_obj.ptr()));
	}
}


void CDPLPythonChem::exportAtomDictionary()
{
    using namespace boost;
    using namespace CDPL;

	python::scope scope = python::class_<Chem::AtomDictionary, Chem::AtomDictionary::SharedPointer>("AtomDictionary", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::AtomDictionary&>((python::arg("self"), python::arg("dict"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::AtomDictionary>())	
		.def("addEntry", &Chem::AtomDictionary::addEntry, (python::arg("self"), python::arg("entry"))) 
		.def("containsEntry", &Chem::AtomDictionary::containsEntry, (python::arg("self"), python::arg("type"), python::arg("isotope"))) 
		.def("removeEntry", &Chem::AtomDictionary::removeEntry, (python::arg("self"), python::arg("type"), python::arg("isotope"))) 
		.def("getEntry", &Chem::AtomDictionary::getEntry, (python::arg("self"), python::arg("type"), python::arg("isotope")),
			 python::return_internal_reference<>()) 
		.def("clear", &Chem::AtomDictionary::clear, python::arg("self")) 
		.def("getNumEntries", &Chem::AtomDictionary::getNumEntries, python::arg("self")) 
		.def("getEntries", &getEntries, python::arg("self")) 
		.def("loadDefaultEntries", &Chem::AtomDictionary::loadDefaultEntries, python::arg("self")) 
		.def("assign", &Chem::AtomDictionary::operator=, (python::arg("self"), python::arg("dict")), python::return_self<>())
		.add_property("numEntries", &Chem::AtomDictionary::getNumEntries)
		.add_property("entries", &getEntries)
		.def("set", &setDictionary, python::arg("dict"))
		.staticmethod("set")
		.def("get", &Chem::AtomDictionary::get, python::return_value_policy<python::reference_existing_object>())
		.staticmethod("get")
		.def("getSymbol", &Chem::AtomDictionary::getSymbol, (python::arg("type"), python::arg("isotope") = 0),
			 python::return_value_policy<python::copy_const_reference>())
		.staticmethod("getSymbol")
		.def("getName", &Chem::AtomDictionary::getName, (python::arg("type"), python::arg("isotope") = 0),
			 python::return_value_policy<python::copy_const_reference>())
		.staticmethod("getName")
		.def("getType", &Chem::AtomDictionary::getType, python::arg("symbol"))
		.staticmethod("getType")
		.def("getMostAbundantIsotope", &Chem::AtomDictionary::getMostAbundantIsotope, python::arg("type"))
		.staticmethod("getMostAbundantIsotope")
		.def("getIUPACGroup", &Chem::AtomDictionary::getIUPACGroup, python::arg("type"))
		.staticmethod("getIUPACGroup")
		.def("getNumValenceElectrons", &Chem::AtomDictionary::getNumValenceElectrons, python::arg("type"))
		.staticmethod("getNumValenceElectrons")
		.def("getAtomicWeight", &Chem::AtomDictionary::getAtomicWeight, (python::arg("type"), python::arg("isotope") = 0))
		.staticmethod("getAtomicWeight")
		.def("getVdWRadius", &Chem::AtomDictionary::getVdWRadius, python::arg("type"))
		.staticmethod("getVdWRadius")
		.def("getCovalentRadius", &Chem::AtomDictionary::getCovalentRadius, (python::arg("type"), python::arg("order") = 1))
		.staticmethod("getCovalentRadius")
		.def("getAllredRochowElectronegativity", &Chem::AtomDictionary::getAllredRochowElectronegativity, python::arg("type"))
		.staticmethod("getAllredRochowElectronegativity")
		.def("getValenceStates", &Chem::AtomDictionary::getValenceStates, python::arg("type"),
			 python::return_value_policy<python::reference_existing_object>())
		.staticmethod("getValenceStates")
		.def("isChemicalElement", &Chem::AtomDictionary::isChemicalElement, python::arg("type"))
		.staticmethod("isChemicalElement")
		.def("isMainGroupElement", &Chem::AtomDictionary::isMainGroupElement, python::arg("type"))
		.staticmethod("isMainGroupElement")
		.def("isTransitionMetal", &Chem::AtomDictionary::isTransitionMetal, python::arg("type"))
		.staticmethod("isTransitionMetal")
		.def("isMetal", &Chem::AtomDictionary::isMetal, python::arg("type"))
		.staticmethod("isMetal")
		.def("isSemiMetal", &Chem::AtomDictionary::isSemiMetal, python::arg("type"))
		.staticmethod("isSemiMetal")
		.def("isNonMetal", &Chem::AtomDictionary::isNonMetal, python::arg("type"))
		.staticmethod("isNonMetal")
		.def("isHalogen", &Chem::AtomDictionary::isHalogen, python::arg("type"))
		.staticmethod("isHalogen")
		.def("isNobleGas", &Chem::AtomDictionary::isNobleGas, python::arg("type"))
		.staticmethod("isNobleGas");

	python::class_<Chem::AtomDictionary::Entry>("Entry", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Chem::AtomDictionary::Entry&>((python::arg("self"), python::arg("entry"))))
		.def("__init__", python::make_constructor(&makeEntry, python::default_call_policies(),
												  (python::arg("atom_type"), python::arg("iso"), python::arg("sym"),
												   python::arg("name"), python::arg("most_abdt_iso"), python::arg("avg_weight"),
												   python::arg("iupac_grp"), python::arg("metal"), python::arg("non_metal"), python::arg("val_states"),
												   python::arg("vdw_rad"), python::arg("cov_radii"), python::arg("ar_eneg"), python::arg("iso_masses"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::AtomDictionary::Entry>())	
		.def("assign", &Chem::AtomDictionary::Entry::operator=, (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getType", &Chem::AtomDictionary::Entry::getType, python::arg("self"))
		.def("getIsotope", &Chem::AtomDictionary::Entry::getIsotope, python::arg("self"))
		.def("getName", &Chem::AtomDictionary::Entry::getName, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getSymbol", &Chem::AtomDictionary::Entry::getSymbol, python::arg("self"),
			 python::return_value_policy<python::copy_const_reference>())
		.def("getMostAbundantIsotope", &Chem::AtomDictionary::Entry::getMostAbundantIsotope, python::arg("self"))
		.def("getAverageWeight", &Chem::AtomDictionary::Entry::getAverageWeight, python::arg("self"))
		.def("getIUPACGroup", &Chem::AtomDictionary::Entry::getIUPACGroup, python::arg("self"))
		.def("isMetal", &Chem::AtomDictionary::Entry::isMetal, python::arg("self"))
		.def("isNonMetal", &Chem::AtomDictionary::Entry::isNonMetal, python::arg("self"))
		.def("getValenceStates", &Chem::AtomDictionary::Entry::getValenceStates, python::arg("self"),
			 python::return_internal_reference<>())
		.def("getVdWRadius", &Chem::AtomDictionary::Entry::getVdWRadius, python::arg("self"))
		.def("getCovalentRadius", &Chem::AtomDictionary::Entry::getCovalentRadius, (python::arg("self"), python::arg("order")))
		.def("getAllredRochowElectronegativity", &Chem::AtomDictionary::Entry::getAllredRochowElectronegativity, python::arg("self"))
		.def("getIsotopeMasses", &getIsotopeMasses, python::arg("self"))
		.add_property("type", &Chem::AtomDictionary::Entry::getType)
		.add_property("isotope", &Chem::AtomDictionary::Entry::getIsotope)
		.add_property("name", python::make_function(&Chem::AtomDictionary::Entry::getName,
													python::return_value_policy<python::copy_const_reference>()))
		.add_property("symbol", python::make_function(&Chem::AtomDictionary::Entry::getSymbol,
													  python::return_value_policy<python::copy_const_reference>()))
		.add_property("mostAbundantIsotope", &Chem::AtomDictionary::Entry::getMostAbundantIsotope)
		.add_property("averageWeight", &Chem::AtomDictionary::Entry::getAverageWeight)
		.add_property("IUPACGroup", &Chem::AtomDictionary::Entry::getIUPACGroup)
		.add_property("metal", &Chem::AtomDictionary::Entry::isMetal)
		.add_property("nonMetal", &Chem::AtomDictionary::Entry::isNonMetal)
		.add_property("valenceStates", python::make_function(&Chem::AtomDictionary::Entry::getValenceStates,
															 python::return_internal_reference<>()))
		.add_property("VdWRadius", &Chem::AtomDictionary::Entry::getVdWRadius)
		.add_property("AllredRochowElectronegativity", &Chem::AtomDictionary::Entry::getAllredRochowElectronegativity)
		.add_property("isotopeMasses", &getIsotopeMasses);
}
