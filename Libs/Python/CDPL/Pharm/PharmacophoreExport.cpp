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

#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Chem/Entity3DContainerVisitor.hpp"
#include "Base/PropertyContainerVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct PharmacophoreWrapper : CDPL::Pharm::Pharmacophore, boost::python::wrapper<CDPL::Pharm::Pharmacophore> 
	{

		typedef boost::shared_ptr<PharmacophoreWrapper> SharedPointer;

		PROPERTYCONTAINER_IMPL(PharmacophoreWrapper) 

		void clear() {
			this->get_override("clear")();
		}

		CDPL::Pharm::Feature& addFeature() {
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
		
		const CDPL::Pharm::Feature& getFeature(std::size_t idx) const {         
			return this->get_override("getFeature")(idx);                   
		}                                                                
                                                                                          
		CDPL::Pharm::Feature& getFeature(std::size_t idx)  {                    
			return this->get_override("getFeature")(idx);                   
		}
                                         
		bool containsFeature(const CDPL::Pharm::Feature& feature) const {          
			return this->get_override("containsFeature")(boost::ref(feature)); 
		}                                                                
                                                                     
		std::size_t getFeatureIndex(const CDPL::Pharm::Feature& feature) const {   
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

	bool containsFeature(CDPL::Pharm::Pharmacophore& pharm, CDPL::Pharm::Feature& feature) {
		return pharm.containsFeature(feature);
	}

	std::size_t getFeatureIndex(CDPL::Pharm::Pharmacophore& pharm, CDPL::Pharm::Feature& feature) {
		return pharm.getFeatureIndex(feature);
	}
}


void CDPLPythonPharm::exportPharmacophore()
{
	using namespace boost;
	using namespace CDPL;

	void (Pharm::Pharmacophore::*removeFeatureFunc)(std::size_t) = &Pharm::Pharmacophore::removeFeature;
	Pharm::Feature& (Pharm::Pharmacophore::*getFeatureFunc)(std::size_t) = &Pharm::Pharmacophore::getFeature;

	python::scope scope = python::class_<PharmacophoreWrapper, PharmacophoreWrapper::SharedPointer, 
										 python::bases<Chem::Entity3DContainer, Base::PropertyContainer>,
										 boost::noncopyable>("Pharmacophore", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def("clear",  python::pure_virtual(&Pharm::Pharmacophore::clear), python::arg("self"))
		.def("addFeature",  python::pure_virtual(&Pharm::Pharmacophore::addFeature), python::arg("self"),
			 python::return_internal_reference<1>())
		.def("removeFeature", python::pure_virtual(removeFeatureFunc), (python::arg("self"), python::arg("idx")))
		.def("copy", python::pure_virtual(&Pharm::Pharmacophore::copy), (python::arg("self"), python::arg("pharm")))
		.def("append", python::pure_virtual(&Pharm::Pharmacophore::append), (python::arg("self"), python::arg("pharm")))
		.def("clone", python::pure_virtual(&Pharm::Pharmacophore::clone), python::arg("self"))
		.def("assign", &Pharm::Pharmacophore::operator=, (python::arg("self"), python::arg("pharm")), 
			 python::return_self<>())
		.def("getFeature", python::pure_virtual(getFeatureFunc), (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("containsFeature", python::pure_virtual(&containsFeature), (python::arg("self"), python::arg("feature")))
		.def("getFeatureIndex", python::pure_virtual(&getFeatureIndex), (python::arg("self"), python::arg("feature")))
		.def("getNumFeatures", python::pure_virtual(&Pharm::Pharmacophore::getNumFeatures), python::arg("self"))
		.def("getEntity", static_cast<Chem::Entity3D& (Pharm::Pharmacophore::*)(std::size_t)>(&Pharm::Pharmacophore::getEntity), 
			 &PharmacophoreWrapper::getEntityDef, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<1>())
		.def("getNumEntities", &Pharm::Pharmacophore::getNumEntities, &PharmacophoreWrapper::getNumEntitiesDef, python::arg("self"))
		.def("__iadd__", &Pharm::Pharmacophore::operator+=, (python::arg("self"), python::arg("pharm")), 
			 python::return_self<>())
		.def("__len__", &Pharm::Pharmacophore::getNumFeatures, python::arg("self"))
		.def("__getitem__", getFeatureFunc, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__contains__", &containsFeature, (python::arg("self"), python::arg("feature")))
		.def("__delitem__", removeFeatureFunc, (python::arg("self"), python::arg("idx")))
		.def(CDPLPythonBase::PropertyContainerVirtualFunctionsVisitor<PharmacophoreWrapper>())
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor(true))
		.add_property("numFeatures", &Pharm::Pharmacophore::getNumFeatures);

	python::register_ptr_to_python<Pharm::Pharmacophore::SharedPointer>();
}
