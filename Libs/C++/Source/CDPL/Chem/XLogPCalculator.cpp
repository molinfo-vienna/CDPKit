/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * XLogPCalculator.cpp 
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


#include "StaticInit.hpp"

#include <numeric>
#include <vector>

#include <boost/thread.hpp>

#include "CDPL/Chem/XLogPCalculator.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Math/VectorIterator.hpp"


using namespace CDPL;


namespace
{

	const std::size_t LOGP_OFFSET_INDEX           = 0;
	const std::size_t HYDROPHOBIC_C_INDEX         = 91;
	const std::size_t INTERNAL_H_BOND_INDEX       = 92;
	const std::size_t HALOGEN_13_PAIR_INDEX       = 93;
	const std::size_t AROMATIC_N_14_PAIR_INDEX    = 94;
	const std::size_t ORTHO_SP3_O_PAIR_INDEX      = 95;
	const std::size_t PARA_DONOR_PAIR_INDEX       = 96;
	const std::size_t SP2_O_15_PAIR_INDEX         = 97;
	const std::size_t ALPHA_AMINO_ACID_INDEX      = 98;
	const std::size_t SALICYLIC_ACID_INDEX        = 99;
	const std::size_t P_AMINO_SULFONIC_ACID_INDEX = 100;

	const std::string INTERNAL_H_BOND_SMARTS1      = "[N,O;!H0]-[R]~[R]-,=[O]";
	const std::string INTERNAL_H_BOND_SMARTS2      = "[N,O;!H0]-[R]~*~[!R]-,=[O]";
	const std::string INTERNAL_H_BOND_SMARTS3      = "[N,O;!H0]-[!R]~*~[R]-,=[O]";
	const std::string HALOGEN_13_PAIR_SMARTS       = "[F,Cl,I,Br]-*-[F,Cl,I,Br]";
	const std::string AROMATIC_N_14_PAIR_SMARTS    = "n1:a:a:n:a:a1";
	const std::string ORTHO_SP3_O_PAIR_SMARTS      = "[*;!R]-[O;H0;!R]-c:c-[O;H0;!R]-[*;!R]"; 
	const std::string PARA_DONOR_PAIR_SMARTS       = "c1(-[#7,#8;!H0]):a:a:c(-[#7,#8;!H0]):a:a:1";
	const std::string SP2_O_15_PAIR_SMARTS         = "O=[C;!R]-[*;!R]-[C;!R]=O";
	const std::string ALPHA_AMINO_ACID_SMARTS      = "[CX4](-[NH2])-C(=O)-[OH1]";
	const std::string SALICYLIC_ACID_SMARTS        = "c1:c(-C(=O)-O):c(-[OH1]):c:c:c:1";
	const std::string P_AMINO_SULFONIC_ACID_SMARTS = "S(=O)(=O)-c1:c:c:c:c:c:1-N";

	Chem::Molecule::SharedPointer internalHBondQuery1;
	Chem::Molecule::SharedPointer internalHBondQuery2;
	Chem::Molecule::SharedPointer internalHBondQuery3;
	Chem::Molecule::SharedPointer halogen13PairQuery;
	Chem::Molecule::SharedPointer aromaticN14PairQuery;
	Chem::Molecule::SharedPointer orthoSP3OPairQuery;
	Chem::Molecule::SharedPointer paraDonorPairQuery;
	Chem::Molecule::SharedPointer sp2O15PairQuery;
	Chem::Molecule::SharedPointer alphaAminoAcidQuery;
	Chem::Molecule::SharedPointer salicylicAcid;
	Chem::Molecule::SharedPointer pAminoSulfonicAcidQuery;

	typedef std::vector<Chem::MolecularGraph::SharedPointer> PatternTable;

	PatternTable atomTypePatterns;

	boost::once_flag initSSSPatternsFlag = BOOST_ONCE_INIT;

	void initSSSPatterns()
	{
		internalHBondQuery1 = Chem::parseSMARTS(INTERNAL_H_BOND_SMARTS1);
		internalHBondQuery2 = Chem::parseSMARTS(INTERNAL_H_BOND_SMARTS2);
		internalHBondQuery3 = Chem::parseSMARTS(INTERNAL_H_BOND_SMARTS3);
		halogen13PairQuery = Chem::parseSMARTS(HALOGEN_13_PAIR_SMARTS);
		aromaticN14PairQuery = Chem::parseSMARTS(AROMATIC_N_14_PAIR_SMARTS);
		orthoSP3OPairQuery = Chem::parseSMARTS(ORTHO_SP3_O_PAIR_SMARTS);
		paraDonorPairQuery = Chem::parseSMARTS(PARA_DONOR_PAIR_SMARTS);
		sp2O15PairQuery = Chem::parseSMARTS(SP2_O_15_PAIR_SMARTS);
		alphaAminoAcidQuery = Chem::parseSMARTS(ALPHA_AMINO_ACID_SMARTS);
		salicylicAcid = Chem::parseSMARTS(SALICYLIC_ACID_SMARTS);
		pAminoSulfonicAcidQuery = Chem::parseSMARTS(P_AMINO_SULFONIC_ACID_SMARTS);

		atomTypePatterns.push_back(Chem::parseSMARTS("[CH3:1][!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH3:2][!#1;!#7;!#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH3:3][#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:4]([!#1;!#7;!#8;!u;!a])[!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:5]([!#1;!#7;!#8;u,a])[!#1;!#7;!#8;!u;!a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:6]([!#1;!#7;!#8;u,a])[!#1;!#7;!#8;u,a]")); // (π=2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:7]([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:7]([!#1;!#7;!#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:8]([#7,#8;!u;!a])[#7,#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:8]([!#1;!#7;!#8;u,a])[#7,#8;!u;!a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:8]([!#1;!#7;!#8;!u;!a])[#7,#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:9]([#7,#8;u,a])[#7,#8;u,a]")); // (π=2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH2:9]([!#1;!#7;!#8;u,a])[#7,#8;u,a]")); // (π=2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:10]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])[!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:11]([!#1;!#7;!#8;u,a])([!#1;!#7;!#8;!u;!a])[!#1;!#7;!#8;!u;!a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:12]([!#1;!#7;!#8;u,a])([!#1;!#7;!#8;u,a])[!#1;!#7;!#8]")); // (π≥2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:13]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:13]([!#1;!#7;!#8;!u;!a])([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:13]([#7,#8;!u;!a])([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:14]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])[#7,#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:14]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;u,a])[#7,#8;!u;!a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:14]([!#1;!#7;!#8;u,a])([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:14]([!#1;!#7;!#8;!u;!a])([#7,#8;!u;!a])[#7,#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:14]([#7,#8;!u;!a])([#7,#8;!u;!a])[#7,#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:15]([!#1;!#7;!#8;u,a])([!#1;!#7;!#8;u,a])[#7,#8]")); // (π≥2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:15]([!#1;!#7;!#8;u,a])([!#1;!#7;!#8])[#7,#8;u,a]")); // (π≥2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:15]([!#1;!#7;!#8])([#7,#8;u,a])[#7,#8;u,a]")); // (π≥2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:15]([!#1;!#7;!#8;u,a])([#7,#8;u,a])[#7,#8]")); // (π≥2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[CH:15]([#7,#8;u,a])([#7,#8;u,a])[#7,#8]")); // (π≥2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:16]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])[!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:17]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])[!#1;!#7;!#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:18]([!#1;!#7;!#8])([!#1;!#7;!#8])([!#1;!#7;!#8;u,a])[!#1;!#7;!#8;u,a]")); // (π≥2)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:19]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:19]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:19]([!#1;!#7;!#8;!u;!a])([#7,#8;!u;!a])([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:19]([#7,#8;!u;!a])([#7,#8;!u;!a])([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:20]([!#1;!#7;!#8])([!#1;!#7;!#8])([!#1;!#7;!#8])[#7,#8;u,a]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:20]([!#1;!#7;!#8])([!#1;!#7;!#8])([!#1;!#7;!#8;u,a])[#7,#8]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:20]([!#1;!#7;!#8])([!#1;!#7;!#8])([#7,#8])[#7,#8;u,a]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:20]([!#1;!#7;!#8])([!#1;!#7;!#8;u,a])([#7,#8])[#7,#8]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:20]([!#1;!#7;!#8])([#7,#8])([#7,#8])[#7,#8;u,a]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:20]([!#1;!#7;!#8;u,a])([#7,#8])([#7,#8])[#7,#8]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[C:20]([#7,#8])([#7,#8])([#7,#8])[#7,#8;u,a]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[CH2:21]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[CH:22][!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[CH:23][!#1;!#7;!#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[CH:24][#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[CH:25][#7,#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:26]([!#1;!#7;!#8;!u;!a])[!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:27]([!#1;!#7;!#8])[!#1;!#7;!#8;u,a]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:28]([!#1;!#7;!#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:29]([!#1;!#7;!#8;u,a])[#7,#8]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:29]([!#1;!#7;!#8])[#7,#8;u,a]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:30]([#7,#8;!u;!a])[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:31]([#7,#8;u,a])[#7,#8]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("c:[cH:32]:c")); // arom
		atomTypePatterns.push_back(Chem::parseSMARTS("*:[cH:33]:n"));
		atomTypePatterns.push_back(Chem::parseSMARTS("c:[c:34](~[!#1;!#7;!#8]):c"));
		atomTypePatterns.push_back(Chem::parseSMARTS("c:[c:35](~[#7,#8]):c"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*:[c:36](~[!#1;!#7;!#8]):n"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*:[c:37](~[#7,#8]):n"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8]#[CH:38]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*#[C:39]*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[C:40]=*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;!u;!a][NH2:41]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;u,a][NH2:42]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[#7,#8][NH2:43]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;!u;!a][NH:44][!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;u,a][NH:45][!#1;!#7;!#8]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;R;u,a][NH;R:46][!#1;!#7;!#8;R;u,a]")); // (ring)c
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[NH:47]-[#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[NH;R:48]-[#7,#8]")); // (ring)
		atomTypePatterns.push_back(Chem::parseSMARTS("[N:49]([!#1;!#7;!#8;!u;!a])([!#1;!#7;!#8;!u;!a])[!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[N:50]([!#1;!#7;!#8])([!#1;!#7;!#8])[!#1;!#7;!#8;u,a]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[N;R:51]([!#1;!#7;!#8])([!#1;!#7;!#8])[!#1;!#7;!#8]")); // (ring)
		atomTypePatterns.push_back(Chem::parseSMARTS("[N:52]([!#1;!#7;!#8])([!#1;!#7;!#8])[#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[N:52]([!#1;!#7;!#8])([#7,#8])[#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[N:52]([#7,#8])([#7,#8])[#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[N;R:53]([!#1;!#7;!#8])([!#1;!#7;!#8])[#7,#8]")); // (ring)
		atomTypePatterns.push_back(Chem::parseSMARTS("[N;R:53]([!#1;!#7;!#8])([#7,#8])[#7,#8]")); // (ring)
		atomTypePatterns.push_back(Chem::parseSMARTS("[N;R:53]([#7,#8])([#7,#8])[#7,#8]")); // (ring)
		atomTypePatterns.push_back(Chem::parseSMARTS("O=C([*,#1])-[NH2:54]"));  // amide
		atomTypePatterns.push_back(Chem::parseSMARTS("O=C([*,#1])-[NH:55][!#1;!#7;!#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("O=C([*,#1])-[NH:56][#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("O=C([*,#1])-[N:57]([!#1;!#7;!#8])[!#1;!#7;!#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("O=C(-[*,#1])-[N:58]([!#1;!#7;!#8])[#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("C=[N:59]-[!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("C=[N:60]-[!#1;!#7;!#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("C=[N:61]-[#7,#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("C=[N:62]-[#7,#8;u,a]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("N=[N:63]-[!#1;!#7;!#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("N=[N:64]-[#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[N:65]=O"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[N:66](=O)O"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*:[n;r6:67]:*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-C#[N:68]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;!u;!a]-[OH:69]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;u,a]-[OH:70]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[#7,#8]-[OH:71]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;!u;!a]-[O:72]-[!#1;!#7;!#8;!u;!a]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8;u,a]-[O:73]-[!#1;!#7;!#8]")); // (π>0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[!#1;!#7;!#8]-[O:74]-[#7,#8]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[O:75]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[SH:76]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[S:77]-*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*=[S:78]"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[S:79](=O)-*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("*-[S:80](=O)(=O)-*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("O=[P:81](-*)(-*)-*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("S=[P:82](-*)(-*)-*"));
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;!u;!a]-[F:83]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;u,a]-[F:84]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;!u;!a]-[Cl:85]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;u,a]-[Cl:86]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;!u;!a]-[Br:87]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;u,a]-[Br:88]")); // (π=1)
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;!u;!a]-[I:89]")); // (π=0)
		atomTypePatterns.push_back(Chem::parseSMARTS("[*;u,a]-[I:90]")); // (π=1)
	}

	const double REGRESSION_COEFFS[] = {
	    0.137510724896,
		0.50247901934,
		0.211887964842,
		-0.0485590557979,
		0.339841940879,
		0.0112326039648,
		-0.134686341152,
		-0.102511201454,
		-0.225532991148,
		-0.784789451695,
		0.134437675015,
		-0.187707955441,
		-0.436710837842,
		-0.138146103865,
		-0.0625866525676,
		-0.535469884673,
		-0.215035748663,
		-0.516633255611,
		-0.254077542765,
		-0.242380202792,
		-0.546710814968,
		0.352955379854,
		0.439628753048,
		0.131139323445,
		0.00338546139024,
		-0.235410050647,
		-0.0501318027234,
		0.0280340541,
		0.0198873504162,
		0.0307722109136,
		0.153511312505,
		-0.261705231262,
		0.318986713068,
		-0.0351919322658,
		0.313193103478,
		-0.0277230781657,
		0.0217648313099,
		0.409912868457,
		0.139078627226,
		0.327915105334,
		2.30142242574,
		-0.595923013795,
		-0.517533628108,
		-0.740331326025,
		-0.215382726764,
		-0.0942782453386,
		0.25089460539,
		0.530882779306,
		1.43755283029e-15,
		0.370574728567,
		0.550398402697,
		0.138251573481,
		-0.821806485874,
		-0.763276243532,
		-0.753373679583,
		-0.254537132819,
		-0.352576565822,
		-0.0529495298562,
		-0.081240917974,
		-0.0946376639222,
		-0.461394586119,
		1.00576102608,
		0.0888075684303,
		0.471933438143,
		-1.15026046069,
		0.802584504652,
		0.5987915776,
		-0.27042274493,
		-0.513520401177,
		-0.591257865271,
		-0.0711214558842,
		-0.762391343202,
		0.0420906997366,
		0.249101482818,
		0.499786687899,
		-0.372385120812,
		0.32816347768,
		0.262775286932,
		-0.361411316955,
		-1.25265319278,
		-0.258045795453,
		-0.737304444685,
		1.05984642097,
		0.292889829057,
		0.187298909247,
		0.470238123807,
		0.626429798946,
		0.772164989871,
		0.792288864121,
		0.955188203082,
		1.08037149888,
		0.206644430773,
		0.108104710151,
		0.193434817501,
		0.570641084099,
		-0.131685512999,
		-0.38976907697,
		0.424609609518,
		-2.39055523804,
		0.786266642436,
		-0.0793728371136
	};
}


const std::size_t Chem::XLogPCalculator::FEATURE_VECTOR_SIZE;


Chem::XLogPCalculator::XLogPCalculator(): featureVector(FEATURE_VECTOR_SIZE), logP(0.0) {}

Chem::XLogPCalculator::XLogPCalculator(const MolecularGraph& molgraph): featureVector(FEATURE_VECTOR_SIZE)
{
	calculate(molgraph);
}

double Chem::XLogPCalculator::calculate(const MolecularGraph& molgraph)
{
	init(molgraph);
	calcLogP(molgraph);

	return logP;
}

double Chem::XLogPCalculator::getResult() const
{
	return logP;
}

const Math::DVector& Chem::XLogPCalculator::getFeatureVector() const
{
	return featureVector;
}

void Chem::XLogPCalculator::init(const MolecularGraph& molgraph)
{
	featureVector.clear();
	featureVector[LOGP_OFFSET_INDEX] = 1;

	if (corrSubstructHistoGen.getNumPatterns() == 0) {
		boost::call_once(&initSSSPatterns, initSSSPatternsFlag);

		corrSubstructHistoGen.addPattern(internalHBondQuery1, INTERNAL_H_BOND_INDEX);
		corrSubstructHistoGen.addPattern(internalHBondQuery2, INTERNAL_H_BOND_INDEX);
		corrSubstructHistoGen.addPattern(internalHBondQuery3, INTERNAL_H_BOND_INDEX);
		corrSubstructHistoGen.addPattern(halogen13PairQuery, HALOGEN_13_PAIR_INDEX);
		corrSubstructHistoGen.addPattern(aromaticN14PairQuery, AROMATIC_N_14_PAIR_INDEX);
		corrSubstructHistoGen.addPattern(orthoSP3OPairQuery, ORTHO_SP3_O_PAIR_INDEX);
		corrSubstructHistoGen.addPattern(paraDonorPairQuery, PARA_DONOR_PAIR_INDEX);
		corrSubstructHistoGen.addPattern(sp2O15PairQuery, SP2_O_15_PAIR_INDEX);
		corrSubstructHistoGen.addPattern(alphaAminoAcidQuery, ALPHA_AMINO_ACID_INDEX, 0, false);
		corrSubstructHistoGen.addPattern(salicylicAcid, SALICYLIC_ACID_INDEX, 0, false);
		corrSubstructHistoGen.addPattern(pAminoSulfonicAcidQuery, P_AMINO_SULFONIC_ACID_INDEX, 0, false);

		for (PatternTable::const_iterator p_it = atomTypePatterns.begin(), p_end = atomTypePatterns.end(); p_it != p_end; ++p_it)
			atomTyper.addPattern(*p_it);
	}
}

void Chem::XLogPCalculator::countHydrophicCarbons(const MolecularGraph& molgraph)
{
	const Math::ULMatrix& dist_mtx = *getTopologicalDistanceMatrix(molgraph);
	
	for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++) {
		const Atom& atom = molgraph.getAtom(i);

		if (getType(atom) != AtomType::C || getAromaticityFlag(atom))
			continue;

		switch (getHybridizationState(atom)) {

			case HybridizationState::SP2:
				if (getRingFlag(atom))
					continue;
					
			case HybridizationState::SP3:
				break;

			default:
				continue;
		}

		bool hydrophobic = true;

		for (std::size_t j = 0; j < num_atoms && hydrophobic; j++) {
			if (i == j)
				continue;

			switch (getType(molgraph.getAtom(j))) {

				case AtomType::C:
				case AtomType::H:
					continue;

				default:
					if (dist_mtx(i, j) < 4)
						hydrophobic = false;
					continue;
			}
		}

		if (hydrophobic)
			featureVector[HYDROPHOBIC_C_INDEX]++;
	}
}

void Chem::XLogPCalculator::calcLogP(const MolecularGraph& molgraph)
{
	corrSubstructHistoGen.generate(molgraph, featureVector);
	atomTyper.execute(molgraph);

	for (std::size_t i = 0, num_atoms = molgraph.getNumAtoms(); i < num_atoms; i++)
		if (atomTyper.hasAtomLabel(i))
			featureVector[atomTyper.getAtomLabel(i)]++;

	countHydrophicCarbons(molgraph);

	logP = std::inner_product(Math::vectorBegin(featureVector), Math::vectorEnd(featureVector), REGRESSION_COEFFS, 0.0);
}
