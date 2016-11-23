/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureContainerVisitor.hpp 
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


#ifndef CDPL_PYTHON_PHARM_FEATURECONTAINERVISITOR_HPP
#define CDPL_PYTHON_PHARM_FEATURECONTAINERVISITOR_HPP

#include <boost/python.hpp>
#include <boost/python/def_visitor.hpp>


#define FEATURECONTAINER_IMPL()											\
    std::size_t getNumFeatures() const {                                \
		return this->get_override("getNumFeatures")();                  \
    }																	\
																		\
    const CDPL::Pharm::Feature& getFeature(std::size_t idx) const {		\
		return this->get_override("getFeature")(idx);                   \
    }																	\
																		\
    bool containsFeature(const CDPL::Pharm::Feature& ftr) const {		\
		return this->get_override("containsFeature")(boost::ref(ftr));	\
    }																	\
																		\
    std::size_t getFeatureIndex(const CDPL::Pharm::Feature& ftr) const {\
		return this->get_override("getFeatureIndex")(boost::ref(ftr));	\
    }																	\
																		\
    CDPL::Pharm::Feature& getFeature(std::size_t idx)  {				\
		return this->get_override("getFeature")(idx);                   \
    }																	\
																		\
    std::size_t getNumEntities() const {								\
		if (boost::python::override f = this->get_override("getNumEntities")) \
            return f();													\
																		\
		return CDPL::Pharm::FeatureContainer::getNumEntities();			\
    }																	\
																		\
    std::size_t getNumEntitiesDef() const {								\
		return CDPL::Pharm::FeatureContainer::getNumEntities();			\
    }																	\
																		\
    const CDPL::Chem::Entity3D& getEntity(std::size_t idx) const {		\
		if (boost::python::override f = this->get_override("getEntity"))\
            return f(idx);												\
																		\
		return CDPL::Pharm::FeatureContainer::getEntity(idx);			\
    }																	\
																		\
    CDPL::Chem::Entity3D& getEntity(std::size_t idx) {					\
		if (boost::python::override f = this->get_override("getEntity")) \
            return f(idx);												\
																		\
		return CDPL::Pharm::FeatureContainer::getEntity(idx);			\
    }																	\
																		\
    CDPL::Chem::Entity3D& getEntityDef(std::size_t idx) {				\
		return CDPL::Pharm::FeatureContainer::getEntity(idx);			\
    }


namespace CDPLPythonPharm
{

    class FeatureContainerVisitorBase
    {

    protected:
		static bool containsFeature(CDPL::Pharm::FeatureContainer& cntnr, CDPL::Pharm::Feature& ftr) {
			return cntnr.containsFeature(ftr);
		}
    };

    template <typename Wrapper>
    class FeatureContainerVirtualFunctionsVisitor : private FeatureContainerVisitorBase, 
													public boost::python::def_visitor<FeatureContainerVirtualFunctionsVisitor<Wrapper> >
    {

		friend class boost::python::def_visitor_access;

		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			cl	
				.def("getFeature", python::pure_virtual(static_cast<Pharm::Feature& (Pharm::FeatureContainer::*)(std::size_t)>(&Pharm::FeatureContainer::getFeature)), 
					 (python::arg("self"), python::arg("idx")), python::return_internal_reference<1>())
				.def("containsFeature", python::pure_virtual(&this->containsFeature), (python::arg("self"), python::arg("ftr")))
				.def("getFeatureIndex", python::pure_virtual(&getFeatureIndex), (python::arg("self"), python::arg("ftr")))
				.def("getNumFeatures", python::pure_virtual(&Pharm::FeatureContainer::getNumFeatures), python::arg("self"))
				.def("getEntity", static_cast<Chem::Entity3D& (Pharm::FeatureContainer::*)(std::size_t)>(&Pharm::FeatureContainer::getEntity), 
					 &Wrapper::getEntityDef, (python::arg("self"), python::arg("idx")),
					 python::return_internal_reference<1>())
				.def("getNumEntities", &Pharm::FeatureContainer::getNumEntities, &Wrapper::getNumEntitiesDef, python::arg("self"));
		}

		static std::size_t getFeatureIndex(CDPL::Pharm::FeatureContainer& cntnr, CDPL::Pharm::Feature& ftr) {
			return cntnr.getFeatureIndex(ftr);
		}
    };

    class FeatureContainerSpecialFunctionsVisitor : private FeatureContainerVisitorBase, 
													public boost::python::def_visitor<FeatureContainerSpecialFunctionsVisitor>
    {

		friend class boost::python::def_visitor_access;

    public:
		FeatureContainerSpecialFunctionsVisitor(bool contains_only): containsOnly(contains_only) {}

    private:
		template <typename ClassType>
		void visit(ClassType& cl) const {
			using namespace boost;
			using namespace CDPL;

			cl.def("__contains__", &this->containsFeature, (python::arg("self"), python::arg("ftr")));

			if (containsOnly)
				return;

			cl
				.def("__getitem__", static_cast<Pharm::Feature& (Pharm::FeatureContainer::*)(std::size_t)>(&Pharm::FeatureContainer::getFeature),
					 (python::arg("self"), python::arg("idx")),
					 python::return_internal_reference<1>())
				.def("__len__", &Pharm::FeatureContainer::getNumFeatures, python::arg("self"));
		}

		bool containsOnly;
    };
}

#endif // CDPL_PYTHON_PHARM_FEATURECONTAINERVISITOR_HPP
