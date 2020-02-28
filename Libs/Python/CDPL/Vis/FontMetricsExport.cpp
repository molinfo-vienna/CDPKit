/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FontMetricsExport.cpp 
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

#include "CDPL/Vis/FontMetrics.hpp"
#include "CDPL/Vis/Font.hpp"
#include "CDPL/Vis/Rectangle2D.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct FontMetricsWrapper : CDPL::Vis::FontMetrics, boost::python::wrapper<CDPL::Vis::FontMetrics>
	{

		void setFont(const CDPL::Vis::Font& font) {
			this->get_override("setFont")(boost::ref(font));
		}

		double getAscent() const {
			return this->get_override("getAscent")();
		} 

		double getDescent() const {
			return this->get_override("getDescent")();
		}
 
		double getHeight() const {
			return this->get_override("getHeight")();
		}

		double getLeading() const {
			return this->get_override("getLeading")();
		} 

		double getWidth(const std::string& str) const {
			return this->get_override("getWidth")(str);
		} 

		double getWidth(char ch) const {
			return getWidth(std::string(1, ch));
		} 

		void getBounds(const std::string& str, CDPL::Vis::Rectangle2D& bounds) const {
			this->get_override("getBounds")(str, boost::ref(bounds));
		} 

		void getBounds(char ch, CDPL::Vis::Rectangle2D& bounds) const {
			getBounds(std::string(1, ch), bounds);
		} 
	};
}


void CDPLPythonVis::exportFontMetrics()
{
	using namespace boost;
	using namespace CDPL;

	double (Vis::FontMetrics::*getWidthFunc)(const std::string&) const = &Vis::FontMetrics::getWidth;
	void (Vis::FontMetrics::*getBoundsFunc)(const std::string&, Vis::Rectangle2D&) const = &Vis::FontMetrics::getBounds;

	python::class_<FontMetricsWrapper, boost::noncopyable>("FontMetrics", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Vis::FontMetrics>())	
		.def("setFont", python::pure_virtual(&Vis::FontMetrics::setFont), 
			 (python::arg("self"), python::arg("font")))
		.def("getAscent", python::pure_virtual(&Vis::FontMetrics::getAscent), python::arg("self"))
		.def("getDescent", python::pure_virtual(&Vis::FontMetrics::getDescent), python::arg("self"))
		.def("getHeight", python::pure_virtual(&Vis::FontMetrics::getHeight), python::arg("self"))
		.def("getLeading", python::pure_virtual(&Vis::FontMetrics::getLeading), python::arg("self"))
		.def("getWidth", python::pure_virtual(getWidthFunc), (python::arg("self"), python::arg("string")))
		.def("getBounds", python::pure_virtual(getBoundsFunc), 
			 (python::arg("self"), python::arg("string"), python::arg("bounds")));
}
