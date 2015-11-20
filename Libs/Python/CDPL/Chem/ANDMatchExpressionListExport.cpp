/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ANDMatchExpressionListExport.cpp 
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

#include "CDPL/Chem/ANDMatchExpressionList.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Reaction.hpp"

#include "ClassExports.hpp"


namespace
{

	template <typename ObjType1, typename ObjType2 = void>
	struct ANDMatchExprListExport
	{

		ANDMatchExprListExport(const char* name) {
			using namespace boost;
			using namespace CDPL;

			python::class_<Chem::ANDMatchExpressionList<ObjType1, ObjType2>, 
				typename Chem::ANDMatchExpressionList<ObjType1, ObjType2>::SharedPointer, 
				python::bases<Chem::MatchExpressionList<ObjType1, ObjType2> > >(name, python::no_init)
				.def(python::init<>(python::arg("self")))
				.def(python::init<const Chem::ANDMatchExpressionList<ObjType1, ObjType2>&>((python::arg("self"), python::arg("expr")))
					 [python::with_custodian_and_ward<1, 2>()])
				.def("assign", &Chem::ANDMatchExpressionList<ObjType1, ObjType2>::operator=, (python::arg("self"), python::arg("expr")),
					 python::return_self<python::with_custodian_and_ward<1, 2> >());
		}
	};
}


void CDPLPythonChem::exportANDMatchExpressionLists()
{
	using namespace boost;
	using namespace CDPL;

	ANDMatchExprListExport<Chem::Atom, Chem::MolecularGraph>("ANDAtomMatchExpressionList");
	ANDMatchExprListExport<Chem::Bond, Chem::MolecularGraph>("ANDBondMatchExpressionList");
	ANDMatchExprListExport<Chem::MolecularGraph>("ANDMolecularGraphMatchExpressionList");
	ANDMatchExprListExport<Chem::Reaction>("ANDReactionMatchExpressionList");
}
