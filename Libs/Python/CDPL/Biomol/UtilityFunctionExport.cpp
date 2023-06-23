/* 
 * UtilityFunctionExport.cpp 
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


#include <boost/python.hpp>
#include <boost/python/ssize_t.hpp>

#include "CDPL/Biomol/UtilityFunctions.hpp"

#include "FunctionExports.hpp"


namespace
{

	boost::python::ssize_t findResidueAtomWrapper(PyObject* cont, boost::python::ssize_t idx, const std::string& res_code, const std::string& chain_id, 
									   long res_seq_no, char ins_code, std::size_t model_no, const std::string& atom_name, long serial_no) 
    {
		using namespace boost;

		python::ssize_t size = PySequence_Length(cont);

		if (size < 0)
			return size;

		for (python::ssize_t i = idx; i < size; i++) {
			PyObject* item = PySequence_GetItem(cont, i);

			if (!item)
				continue;

			python::extract<const CDPL::Chem::Atom&> extract(item);

			if (!extract.check())
				continue;

			const CDPL::Chem::Atom& atom = extract();

			if (CDPL::Biomol::matchesResidueInfo(atom,
												 (res_code.empty() ? 0 : res_code.c_str()), (chain_id.empty() ? 0 : chain_id.c_str()), res_seq_no, ins_code, model_no,
												 (atom_name.empty() ? 0 : atom_name.c_str()), serial_no))
				return i;
		}

		return size;
    }

    boost::python::ssize_t findResidueWrapper(PyObject* cont, boost::python::ssize_t idx, const std::string& res_code, const std::string& chain_id, 
											  long res_seq_no, char ins_code, std::size_t model_no, const std::string& atom_name, long serial_no) 
    {
		using namespace boost;

		python::ssize_t size = PySequence_Length(cont);

		if (size < 0)
			return size;

		for (python::ssize_t i = idx; i < size; i++) {
			PyObject* item = PySequence_GetItem(cont, i);

			if (!item)
				continue;

			python::extract<const CDPL::Chem::MolecularGraph&> extract(item);

			if (!extract.check())
				continue;

			const CDPL::Chem::MolecularGraph& molgraph = extract();

			if (CDPL::Biomol::matchesResidueInfo(molgraph, (res_code.empty() ? 0 : res_code.c_str()), (chain_id.empty() ? 0 : chain_id.c_str()), res_seq_no, ins_code, model_no)) {
				if (atom_name.empty() && serial_no == 0)
					return i;

				if (CDPL::Biomol::findResidueAtom(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), (res_code.empty() ? 0 : res_code.c_str()), 
												  (chain_id.empty() ? 0 : chain_id.c_str()), res_seq_no, ins_code, model_no,
												  (atom_name.empty() ? 0 : atom_name.c_str()), serial_no) != molgraph.getAtomsEnd())
					return i;
			}
		}

		return size;
    }
}


void CDPLPythonBiomol::exportUtilityFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("findResidueAtom", &findResidueAtomWrapper, 
				(python::arg("cntnr"), python::arg("idx"),  python::arg("res_code") = "", python::arg("chain_id") = "", 
				 python::arg("res_seq_no") = Biomol::IGNORE_SEQUENCE_NO, python::arg("ins_code") = char(0), python::arg("model_no") = 0, 
				 python::arg("atom_name") = "", python::arg("serial_no") = Biomol::IGNORE_SERIAL_NO));
    python::def("findResidue", &findResidueWrapper, 
				(python::arg("cntnr"), python::arg("idx"),  python::arg("res_code") = "", python::arg("chain_id") = "", 
				 python::arg("res_seq_no") = Biomol::IGNORE_SEQUENCE_NO, python::arg("ins_code") = char(0), python::arg("model_no") = 0, 
				 python::arg("atom_name") = "", python::arg("serial_no") = Biomol::IGNORE_SERIAL_NO));
}
