/* 
 * ColorTableExport.cpp 
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


#include <sstream>

#include <boost/python.hpp>

#include "CDPL/Vis/ColorTable.hpp"

#include "Util/MapVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	std::string toString(const CDPL::Vis::ColorTable& tab)
	{
		std::ostringstream oss;

		oss << "CDPL.Vis.ColorTable(";
		
		if (tab.isEmpty())
			oss << ')';

		else  {
			bool first_entry = true;

			for (CDPL::Vis::ColorTable::ConstEntryIterator it = tab.getEntriesBegin(), end = tab.getEntriesEnd(); it != end; ++it) {
				if (!first_entry)
					oss << ", ";
				else
					oss << '{';
			
				oss << it->first << ": (" << it->second.getRed() << ", " << it->second.getGreen() << ", " << it->second.getBlue() << ", " << it->second.getAlpha() << ')'; 
				first_entry = false;
			}

			oss << "})";
		}
		
		return oss.str();
	}
}


void CDPLPythonVis::exportColorTable()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<Vis::ColorTable, Vis::ColorTable::SharedPointer>("ColorTable", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Vis::ColorTable&>((python::arg("self"), python::arg("table"))))
		.def(CDPLPythonUtil::MapVisitor<Vis::ColorTable, 
			 python::return_internal_reference<>, python::default_call_policies, python::default_call_policies,
			 python::return_internal_reference<1, python::with_custodian_and_ward_postcall<0, 3> >, true>())	
		.def("__str__", &toString, python::arg("self"))
		.def("__eq__", &Vis::ColorTable::operator==, (python::arg("self"), python::arg("table")))
		.def("__ne__", &Vis::ColorTable::operator!=, (python::arg("self"), python::arg("table")));
}
