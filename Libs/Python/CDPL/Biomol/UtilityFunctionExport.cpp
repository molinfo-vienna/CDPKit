/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctionExport.cpp 
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
#include <boost/python/ssize_t.hpp>

#include "CDPL/Biomol/UtilityFunctions.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


namespace
{

	MAKE_FUNCTION_WRAPPER1(bool, isPDBBackboneAtom, CDPL::Chem::Atom&);
	
	MAKE_FUNCTION_WRAPPER3(bool, areInSameResidue, CDPL::Chem::Atom&, CDPL::Chem::Atom&, unsigned int);

	MAKE_FUNCTION_WRAPPER6(void, extractResidueSubstructure, CDPL::Chem::Atom&, CDPL::Chem::MolecularGraph&, CDPL::Chem::Fragment&, bool, unsigned int, bool);

	MAKE_FUNCTION_WRAPPER6(void, extractResidueSubstructures, CDPL::Chem::AtomContainer&, CDPL::Chem::MolecularGraph&, CDPL::Chem::Fragment&, bool, unsigned int, bool);
	
	bool matchesResidueInfoWrapper1(CDPL::Chem::Atom& atom, const std::string& res_code, const std::string& chain_id, 
								   long res_seq_no, char ins_code, std::size_t model_no, const std::string& atom_name, long serial_no) 
	{
		return CDPL::Biomol::matchesResidueInfo(atom, (res_code.empty() ? 0 : res_code.c_str()), (chain_id.empty() ? 0 : chain_id.c_str()), 
												res_seq_no, ins_code, model_no, (atom_name.empty() ? 0 : atom_name.c_str()), serial_no);
 	}

	bool matchesResidueInfoWrapper2(CDPL::Chem::MolecularGraph& molgraph, const std::string& res_code, const std::string& chain_id, 
								   long res_seq_no, char ins_code, std::size_t model_no) 
	{
		return CDPL::Biomol::matchesResidueInfo(molgraph, (res_code.empty() ? 0 : res_code.c_str()), (chain_id.empty() ? 0 : chain_id.c_str()), 
												res_seq_no, ins_code, model_no);
 	}
	
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

	python::scope().attr("IGNORE_SEQUENCE_NO") = Biomol::IGNORE_SEQUENCE_NO;
	python::scope().attr("IGNORE_SERIAL_NO") = Biomol::IGNORE_SERIAL_NO;

	python::def("convertMOL2ToPDBResidueInfo", &Biomol::convertMOL2ToPDBResidueInfo, (python::arg("molgraph"), python::arg("override")));
	python::def("combineInterferingResidueCoordinates", &Biomol::combineInterferingResidueCoordinates, 
				(python::arg("mol"), python::arg("max_ctr_dist") = 1.0));
	python::def("setHydrogenResidueSequenceInfo", &Biomol::setHydrogenResidueSequenceInfo, 
				(python::arg("molgraph"), python::arg("overwrite"), python::arg("flags") = Biomol::AtomPropertyFlag::DEFAULT));
	
	python::def("extractEnvironmentResidues",
				static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&,
									 Chem::Fragment&, double, bool)>(&Biomol::extractEnvironmentResidues), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_residues"),
				 python::arg("max_dist"), python::arg("append") = false));
	python::def("extractEnvironmentResidues",
				static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&,
									 Chem::Fragment&, const Chem::Atom3DCoordinatesFunction&, double, bool)>(&Biomol::extractEnvironmentResidues), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_residues"),
				 python::arg("coords_func"), python::arg("max_dist"), python::arg("append") = false));
	python::def("extractProximalAtoms", static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&, Chem::Fragment&, 
															 double, bool, bool)>(&Biomol::extractProximalAtoms), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_atoms"),
				 python::arg("max_dist"), python::arg("inc_core_atoms") = false, python::arg("append") = false));
	python::def("extractProximalAtoms", static_cast<void (*)(const Chem::MolecularGraph&, const Chem::MolecularGraph&, Chem::Fragment&, 
															 const Chem::Atom3DCoordinatesFunction&, double, bool, bool)>(&Biomol::extractProximalAtoms), 
				(python::arg("core"), python::arg("macromol"), python::arg("env_atoms"),
				 python::arg("coords_func"), python::arg("max_dist"), python::arg("inc_core_atoms") = false, python::arg("append") = false));
	
	python::def("isPDBBackboneAtom", &isPDBBackboneAtomWrapper1, python::arg("atom"));
	python::def("areInSameResidue", &areInSameResidueWrapper3, 
				(python::arg("atom1"), python::arg("atom2"), python::arg("flags") = Biomol::AtomPropertyFlag::DEFAULT));
	python::def("extractResidueSubstructure", &extractResidueSubstructureWrapper6,
				(python::arg("atom"), python::arg("molgraph"), python::arg("res_substruct"), 
				 python::arg("cnctd_only") = false, python::arg("flags") = Biomol::AtomPropertyFlag::DEFAULT, python::arg("append") = false));
	python::def("extractResidueSubstructures", &extractResidueSubstructuresWrapper6,
				(python::arg("cntnr"), python::arg("molgraph"), python::arg("res_substructs"), 
				 python::arg("cnctd_only") = false, python::arg("flags") = Biomol::AtomPropertyFlag::DEFAULT,
				 python::arg("append") = false));
 	python::def("matchesResidueInfo", &matchesResidueInfoWrapper1, 
				(python::arg("atom"), python::arg("res_code") = "", python::arg("chain_id") = "", 
				 python::arg("res_seq_no") = Biomol::IGNORE_SEQUENCE_NO, python::arg("ins_code") = char(0), python::arg("model_no") = 0, 
				 python::arg("atom_name") = "", python::arg("serial_no") = Biomol::IGNORE_SERIAL_NO));
	python::def("matchesResidueInfo", &matchesResidueInfoWrapper2, 
				(python::arg("molgraph"), python::arg("res_code") = "", python::arg("chain_id") = "", 
				 python::arg("res_seq_no") = Biomol::IGNORE_SEQUENCE_NO, python::arg("ins_code") = char(0), python::arg("model_no") = 0));
    python::def("findResidueAtom", &findResidueAtomWrapper, 
				(python::arg("cntnr"), python::arg("idx"),  python::arg("res_code") = "", python::arg("chain_id") = "", 
				 python::arg("res_seq_no") = Biomol::IGNORE_SEQUENCE_NO, python::arg("ins_code") = char(0), python::arg("model_no") = 0, 
				 python::arg("atom_name") = "", python::arg("serial_no") = Biomol::IGNORE_SERIAL_NO));
    python::def("findResidue", &findResidueWrapper, 
				(python::arg("cntnr"), python::arg("idx"),  python::arg("res_code") = "", python::arg("chain_id") = "", 
				 python::arg("res_seq_no") = Biomol::IGNORE_SEQUENCE_NO, python::arg("ins_code") = char(0), python::arg("model_no") = 0, 
				 python::arg("atom_name") = "", python::arg("serial_no") = Biomol::IGNORE_SERIAL_NO));
}
