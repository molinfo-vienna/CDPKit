/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreExport.cpp 
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
#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/PharmacophoreFeature.hpp"

#include "Chem/Entity3DContainerVisitor.hpp"
#include "Base/PropertyContainerVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct PharmacophoreWrapper : CDPL::Chem::Pharmacophore, boost::python::wrapper<CDPL::Chem::Pharmacophore> 
	{

		typedef boost::shared_ptr<PharmacophoreWrapper> SharedPointer;

		PROPERTYCONTAINER_IMPL(PharmacophoreWrapper) 

		void clear() {
			this->get_override("clear")();
		}

		CDPL::Chem::PharmacophoreFeature& addFeature() {
			return this->get_override("addFeature")();
		}

		void removeFeature(std::size_t idx) {
			this->get_override("removeFeature")(idx);
		}

		void copy(const Pharmacophore& pharm) {
			this->get_override("copy")(boost::ref(pharm));
		}
	
		void append(const Pharmacophore& pharm) {
			this->get_override("append")(boost::ref(pharm));
		}

		Pharmacophore::SharedPointer clone() const {
			return this->get_override("clone")();
		}

		std::size_t getNumFeatures() const {                                
			return this->get_override("getNumFeatures")();                  
		}                                                                
		
		const CDPL::Chem::PharmacophoreFeature& getFeature(std::size_t idx) const {         
			return this->get_override("getFeature")(idx);                   
		}                                                                
                                                                                          
		CDPL::Chem::PharmacophoreFeature& getFeature(std::size_t idx)  {                    
			return this->get_override("getFeature")(idx);                   
		}
                                         
		bool containsFeature(const CDPL::Chem::PharmacophoreFeature& feature) const {          
			return this->get_override("containsFeature")(boost::ref(feature)); 
		}                                                                
                                                                     
		std::size_t getFeatureIndex(const CDPL::Chem::PharmacophoreFeature& feature) const {   
			return this->get_override("getFeatureIndex")(boost::ref(feature)); 
		}                

		std::size_t getNumEntities() const {                             
			if (boost::python::override f = this->get_override("getNumEntities")) 
				return f();                                                       
                                                                              
			return Pharmacophore::getNumEntities();                   
		}                                                                
                                                                     
		std::size_t getNumEntitiesDef() const {                          
			return Pharmacophore::getNumEntities();          
		}                                                                
                                                                     
		const CDPL::Chem::Entity3D& getEntity(std::size_t idx) const {   
			if (boost::python::override f = this->get_override("getEntity")) 
				return f(idx);                                               
                                                                         
			return Pharmacophore::getEntity(idx);                
		}                                                                
                                                                     
		CDPL::Chem::Entity3D& getEntity(std::size_t idx) {         
			if (boost::python::override f = this->get_override("getEntity")) 
				return f(idx);                                               
                                                                         
			return Pharmacophore::getEntity(idx);                
		}                                                                
                                                                     
		CDPL::Chem::Entity3D& getEntityDef(std::size_t idx) {      
			return Pharmacophore::getEntity(idx);            
		}                                              
	};

	bool containsFeature(CDPL::Chem::Pharmacophore& pharm, CDPL::Chem::PharmacophoreFeature& feature) {
		return pharm.containsFeature(feature);
	}

	std::size_t getFeatureIndex(CDPL::Chem::Pharmacophore& pharm, CDPL::Chem::PharmacophoreFeature& feature) {
		return pharm.getFeatureIndex(feature);
	}
}


void CDPLPythonChem::exportPharmacophore()
{
	using namespace boost;
	using namespace CDPL;

	void (Chem::Pharmacophore::*removeFeatureFunc)(std::size_t) = &Chem::Pharmacophore::removeFeature;
	Chem::PharmacophoreFeature& (Chem::Pharmacophore::*getFeatureFunc)(std::size_t) = &Chem::Pharmacophore::getFeature;

	python::scope scope = python::class_<PharmacophoreWrapper, PharmacophoreWrapper::SharedPointer, 
										 python::bases<Chem::Entity3DContainer, Base::PropertyContainer>,
										 boost::noncopyable>("Pharmacophore", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("clear",  python::pure_virtual(&Chem::Pharmacophore::clear), python::arg("self"))
		.def("addFeature",  python::pure_virtual(&Chem::Pharmacophore::addFeature), python::arg("self"),
			 python::return_internal_reference<1>())
		.def("removeFeature", python::pure_virtual(removeFeatureFunc), (python::arg("self"), python::arg("idx")))
		.def("copy", python::pure_virtual(&Chem::Pharmacophore::copy), (python::arg("self"), python::arg("pharm")))
		.def("append", python::pure_virtual(&Chem::Pharmacophore::append), (python::arg("self"), python::arg("pharm")))
		.def("clone", python::pure_virtual(&Chem::Pharmacophore::clone), python::arg("self"))
		.def("assign", &Chem::Pharmacophore::operator=, (python::arg("self"), python::arg("pharm")), 
			 python::return_self<>())
		.def("getFeature", python::pure_virtual(getFeatureFunc), (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("containsFeature", python::pure_virtual(&containsFeature), (python::arg("self"), python::arg("feature")))
		.def("getFeatureIndex", python::pure_virtual(&getFeatureIndex), (python::arg("self"), python::arg("feature")))
		.def("getNumFeatures", python::pure_virtual(&Chem::Pharmacophore::getNumFeatures), python::arg("self"))
		.def("getEntity", static_cast<Chem::Entity3D& (Chem::Pharmacophore::*)(std::size_t)>(&Chem::Pharmacophore::getEntity), 
			 &PharmacophoreWrapper::getEntityDef, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<1>())
		.def("getNumEntities", &Chem::Pharmacophore::getNumEntities, &PharmacophoreWrapper::getNumEntitiesDef, python::arg("self"))
		.def("__iadd__", &Chem::Pharmacophore::operator+=, (python::arg("self"), python::arg("pharm")), 
			 python::return_self<>())
		.def("__len__", &Chem::Pharmacophore::getNumFeatures, python::arg("self"))
		.def("__getitem__", getFeatureFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__contains__", &containsFeature, (python::arg("self"), python::arg("feature")))
		.def("__delitem__", removeFeatureFunc, (python::arg("self"), python::arg("idx")))
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<PharmacophoreWrapper>())
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor(true))
		.add_property("numFeatures", &Chem::Pharmacophore::getNumFeatures);

	python::register_ptr_to_python<Chem::Pharmacophore::SharedPointer>();
}
