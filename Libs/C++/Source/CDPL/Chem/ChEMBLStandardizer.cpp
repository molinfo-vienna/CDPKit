/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ChEMBLStandardizer.cpp 
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

 
#include "StaticInit.hpp"

#include <cstring>
#include <algorithm>
#include <utility>
#include <cmath>
#include <mutex>

#include <boost/bind.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "CDPL/Chem/ChEMBLStandardizer.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/FragmentFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"


using namespace CDPL;


namespace
{

	const char* CHEMBL_SALT_STRUCTURE_LIBRARY =                 
    #include "ChEMBL-Salts.smi.str" 
	;

	const char* CHEMBL_SOLVENT_STRUCTURE_LIBRARY =                 
    #include "ChEMBL-Solvents.smi.str" 
	;

	std::once_flag initSaltAndSolventDataFlag;
	
	typedef std::pair<std::uint64_t, std::uint64_t> StructureID;
	typedef std::unordered_set<StructureID, boost::hash<StructureID> > StructureIDSet;

	StructureIDSet chemblSaltStructureIDs;
	StructureIDSet chemblSolventStructureIDs;

	inline StructureID genStructureID(Chem::MolecularGraph& molgraph, Chem::HashCodeCalculator& hash_calc)
	{
		return StructureID(hash_calc.calculate(molgraph), (molgraph.getNumAtoms() << 32) + molgraph.getNumBonds());
	}

	void initSaltAndSolventData()

	{
		using namespace Chem;

		boost::iostreams::stream<boost::iostreams::array_source> salts_is(CHEMBL_SALT_STRUCTURE_LIBRARY, std::strlen(CHEMBL_SALT_STRUCTURE_LIBRARY));
		boost::iostreams::stream<boost::iostreams::array_source> solvents_is(CHEMBL_SOLVENT_STRUCTURE_LIBRARY, std::strlen(CHEMBL_SOLVENT_STRUCTURE_LIBRARY));

		HashCodeCalculator hash_calc;

		hash_calc.includeGlobalStereoFeatures(false);
		hash_calc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hash_calc, AtomPropertyFlag::TYPE | AtomPropertyFlag::AROMATICITY));
		hash_calc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | BondPropertyFlag::AROMATICITY));

		BasicMolecule mol;

		for (std::size_t i = 0; i < 2; i++) {
			SMILESMoleculeReader smi_reader(i == 0 ? salts_is : solvents_is);

			setSMILESRecordFormatParameter(smi_reader, "NS");

			while (smi_reader.read(mol)) {
				calcImplicitHydrogenCounts(mol, makeHydrogenDeplete(mol));
				perceiveHybridizationStates(mol, false);
				perceiveSSSR(mol, false);
				setRingFlags(mol, false);
				setAromaticityFlags(mol, false);

				(i == 0 ? chemblSaltStructureIDs : chemblSolventStructureIDs).insert(genStructureID(mol, hash_calc));
			}
		}
	}

	struct SubstructureTransform
	{

		const char* patternSMARTS;
		long        atomCharges[3 * 2 + 1];
		long        bondOrders[3 * 3 + 1];
	};

	const SubstructureTransform STRUCT_NORM_TRANSFORMS[] = {
	    { "[Li,Na,K;+0:1]-[O+0:2]", { 2, 1, 1, 2, -1 }, { 1, 1, 2, 0 } },                 // ([*+1:1].[O-:2])           Alkaline oxide to ions
		{ "[N;X3:1](=[O:2])=[O:3]", { 3, 1, 1, 2, -1, 3, 0 }, { 2, 1, 2, 1, 1, 3, 2} },   // [*+1:1]([*-1:2])=[*:3]     Nitro to N+(O-)=O
		{ "[*:1]-[N;X2:2]#[N;X1:3]", { 1, 2, 1 }, { 0 } },                                // [*:1]-[*+1:2]#[*:3]        Diazonium N
		{ "[N;X4;v4;+0:1]", { 1, 1, 1}, { 0 } },                                          // [*+1:1]                    Quaternary N
		{ "[*:1]=[O;X2;v3;+0:2]-[#6:3]", { 1, 2, 1 }, { 0 } },                            // [*:1]=[*+1:2]-[*:3]        Trivalent O	
		{ "[!O:1][S+0;D3:2](=[O:3])[!O:4]", { 2, 2, 1, 3, -1 }, { 1, 2, 3, 1 } },         // [*:1][S+1:2]([O-:3])[*:4]  Sulfoxide to -S+(O-)
		{ "[!O:1][SH1+1;D3:2](=[O:3])[!O:4]", {2, 2, 1, 3, -1 }, { 2, 2, 3, 1 } },        // [*:1][S+1:2]([O-:3])[*:4]  Sulfoxide to -S+(O-) 2
		{ "[O:1]=[S;D2;+0:2]-[#6:3]", { 1, 2, 1 }, { 0 } },                               // [*:1]=[*+1:2]-[*:3]        Trivalent S
		{ "[C:1]([OH1;D1:2])=;!@[NH1:3]", { 0 }, { 2, 1, 2, 2, 1, 3, 1 } },               // [C:1](=[OH0:2])-[NH2:3]    Bad amide tautomer1	
		{ "[C:1]([OH1;D1:2])=;!@[NH0:3]", { 0 }, { 2, 1, 2, 2, 1, 3, 1 } },               // [C:1](=[OH0:2])-[NH1:3]    Bad amide tautomer2
		{ "[F,Cl,Br,I;X0;+0:1]", { 1, 1, -1 }, { 0 } },                                   // [*-1:1]                    Halogen with no neighbors
		{ "[C,N;-;D2,D3:1]-[N+2;D3:2]-[O-;D1:3]", {2, 1, 0, 2, 1 }, { 1, 1, 2, 2 } },     // [*-0:1]=[*+1:2]-[*-:3]     Odd pyridine/pyridazine oxide structure
		{ "[*:1][N-:2][N+:3]#[N:4]", {2, 2, 0, 4, -1 }, { 2, 2, 3, 2, 3, 4, 2 } },        // [*:1][N+0:2]=[N+:3]=[N-:4] Odd azide 1
		{ "[*:1][N:2]=[N+0:3]=[N:4]", {3, 2, 0, 3, 1, 4, -1 }, { 0 } }                    // [*:1][N+0:2]=[N+:3]=[N-:4] Odd azide 2
	};

	Chem::Molecule::SharedPointer STRUCT_NORM_TRANSFORM_PATTERNS[sizeof(STRUCT_NORM_TRANSFORMS) / sizeof(SubstructureTransform)];
	
	std::once_flag initStructNormTransformPatternsFlag;
	
	void initStructNormTransformPatterns()
	{
		for (std::size_t i = 0; i < sizeof(STRUCT_NORM_TRANSFORMS) / sizeof(SubstructureTransform); i++)
			STRUCT_NORM_TRANSFORM_PATTERNS[i] = Chem::parseSMARTS(STRUCT_NORM_TRANSFORMS[i].patternSMARTS);
	}
	
	Chem::Molecule::SharedPointer TARTRATE_PATTERN;

	std::once_flag initTartratePatternFlag;

	void initTartratePattern()
	{
		TARTRATE_PATTERN = Chem::parseSMARTS("[O;v1,v2H1]C(=O)[Cv4H1:1]([O;v1,v2H1])[Cv4H1:2]([O;v1,v2H1])C(=O)[O;v1,v2H1]");
	}
	
	const unsigned int EXCLUDE_ATOM_TYPES[] = {
		Chem::AtomType::Sc, Chem::AtomType::Ti, Chem::AtomType::V, Chem::AtomType::Cr,
		Chem::AtomType::Mn, Chem::AtomType::Fe, Chem::AtomType::Co, Chem::AtomType::Ni,
		Chem::AtomType::Cu, Chem::AtomType::Ga, Chem::AtomType::Y, Chem::AtomType::Zr,
		Chem::AtomType::Nb, Chem::AtomType::Mo, Chem::AtomType::Tc, Chem::AtomType::Ru,
		Chem::AtomType::Rh, Chem::AtomType::Pd, Chem::AtomType::Cd, Chem::AtomType::In,
		Chem::AtomType::Sn, Chem::AtomType::La, Chem::AtomType::Hf, Chem::AtomType::Ta,
		Chem::AtomType::W, Chem::AtomType::Re, Chem::AtomType::Os, Chem::AtomType::Ir,
		Chem::AtomType::Pt, Chem::AtomType::Au, Chem::AtomType::Hg, Chem::AtomType::Tl,
		Chem::AtomType::Pb, Chem::AtomType::Bi, Chem::AtomType::Po, Chem::AtomType::Ac,
		Chem::AtomType::Ce, Chem::AtomType::Pr, Chem::AtomType::Nd, Chem::AtomType::Pm,
		Chem::AtomType::Sm, Chem::AtomType::Eu, Chem::AtomType::Gd, Chem::AtomType::Tb,
		Chem::AtomType::Dy, Chem::AtomType::Ho, Chem::AtomType::Er, Chem::AtomType::Tm,
		Chem::AtomType::Yb, Chem::AtomType::Lu, Chem::AtomType::Th, Chem::AtomType::Pa,
		Chem::AtomType::U, Chem::AtomType::Np, Chem::AtomType::Pu, Chem::AtomType::Am,
		Chem::AtomType::Cm, Chem::AtomType::Bk, Chem::AtomType::Cf, Chem::AtomType::Es,
		Chem::AtomType::Fm, Chem::AtomType::Md, Chem::AtomType::No, Chem::AtomType::Lr,
		Chem::AtomType::Ge, Chem::AtomType::Sb, Chem::AtomType::UNKNOWN
	};

	Util::BitSet excludeAtomTypeMask;

	struct Init
	{

		Init() {
			excludeAtomTypeMask.resize(Chem::AtomType::MAX_ATOMIC_NO + 1);
				
			for (std::size_t i = 0; i < sizeof(EXCLUDE_ATOM_TYPES) / sizeof(unsigned int); i++)
				excludeAtomTypeMask.set(EXCLUDE_ATOM_TYPES[i]);
		}
		
	} init;
}


Chem::ChEMBLStandardizer::ChEMBLStandardizer()
{
	substructSearch.uniqueMappingsOnly(true);

	hashCodeCalc.includeGlobalStereoFeatures(false);
	hashCodeCalc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | BondPropertyFlag::AROMATICITY));
}

Chem::ChEMBLStandardizer::ChEMBLStandardizer(const ChEMBLStandardizer& standardizer)
{
	substructSearch.uniqueMappingsOnly(true);

	hashCodeCalc.includeGlobalStereoFeatures(false);
	hashCodeCalc.setBondHashSeedFunction(HashCodeCalculator::DefBondHashSeedFunctor(BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY | BondPropertyFlag::AROMATICITY));
}

Chem::ChEMBLStandardizer::ChangeFlags Chem::ChEMBLStandardizer::standardize(Molecule& mol, bool proc_excluded)
{
	ChangeFlags changes = NONE;

	if (mol.getNumAtoms() == 0)
		return NONE;

	if (checkExclusionCriterions(mol)) {
		if (!proc_excluded)
			return EXCLUDED;

		changes = EXCLUDED;
	}

	if (standardizeUnknownStereochemistry(mol))
		changes = ChangeFlags(changes | UNKNOWN_STEREO_STANDARDIZED);

	if (kekulizeBonds(mol))
		changes = ChangeFlags(changes | BONDS_KEKULIZED);

	if (removeExplicitHydrogens(mol))
		changes = ChangeFlags(changes | EXPLICIT_HYDROGENS_REMOVED);

	if (normalizeStructure(mol))
		changes = ChangeFlags(changes | STRUCTURE_NORMALIZED);

	if (removeCharges(mol))
		changes = ChangeFlags(changes | CHARGES_REMOVED);

	if (removeTartrateStereochemistry(mol))
		changes = ChangeFlags(changes | TARTRATE_STEREO_CLEARED);

	if (cleanup2DStructure(mol))
		changes = ChangeFlags(changes | STRUCTURE_2D_CORRECTED);

	clearMatchConstraints(mol);
	
	return changes;
}

Chem::ChEMBLStandardizer::ChangeFlags Chem::ChEMBLStandardizer::standardize(const Molecule& mol, Molecule& std_mol, bool proc_excluded)
{
	copyMolecule(mol, std_mol);
	
	return standardize(std_mol, proc_excluded);
}

Chem::ChEMBLStandardizer::ChangeFlags Chem::ChEMBLStandardizer::getParent(Molecule& mol, bool neutralize, bool check_exclusion)
{
	if (mol.getNumAtoms() == 0)
		return NONE;

	ChangeFlags changes = NONE;
	
	for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;

		if (getIsotope(atom) > 0) {
			setIsotope(atom, 0);

			changes = ChangeFlags(changes | ISOTOPE_INFO_CLEARED);
		}
	}   

	if (removeExplicitHydrogens(mol))
		changes = ChangeFlags(changes | EXPLICIT_HYDROGENS_REMOVED);

	FragmentList::SharedPointer mol_comps = perceiveComponents(mol, false);

	if (mol_comps->getSize() == 1) {
		if (check_exclusion && checkExclusionCriterions(mol))
			changes = ChangeFlags(changes | EXCLUDED);

		if (neutralize && removeCharges(mol))
			changes = ChangeFlags(changes | CHARGES_REMOVED);

		return changes;
	}

	perceiveSSSR(mol, false);
	perceiveHybridizationStates(mol, false);
	setRingFlags(mol, false);
	setAromaticityFlags(mol, false);

	std::call_once(initSaltAndSolventDataFlag, &initSaltAndSolventData);
		
	hashCodeCalc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hashCodeCalc, AtomPropertyFlag::TYPE | AtomPropertyFlag::AROMATICITY));
	molCompList1.clear();

	for (FragmentList::ConstElementIterator it = mol_comps->getElementsBegin(), end = mol_comps->getElementsEnd(); it != end; ++it) {
		const Fragment& orig_comp = *it;

		tmpFragment = orig_comp;

		makeHydrogenDeplete(tmpFragment);

		StructureID struct_id = genStructureID(tmpFragment, hashCodeCalc);

		if (chemblSolventStructureIDs.find(struct_id) != chemblSolventStructureIDs.end())
			continue;

		molCompList1.push_back(MoleculeComponent(&orig_comp, struct_id));
	}

	if (molCompList1.empty()) {
		if (check_exclusion && checkExclusionCriterions(mol))
			changes = ChangeFlags(changes | EXCLUDED);

		if (neutralize && removeCharges(mol))
			changes = ChangeFlags(changes | CHARGES_REMOVED);

		return changes;
	}

	if (mol_comps->getSize() > molCompList1.size())
		changes = ChangeFlags(changes | SOLVENT_COMPONENTS_REMOVED);

	molCompList2.clear();

	for (MoleculeComponentList::const_iterator it = molCompList1.begin(), end = molCompList1.end(); it != end; ++it) {
		const MoleculeComponent& comp = *it;

		if (chemblSaltStructureIDs.find(comp.second) != chemblSaltStructureIDs.end())
			continue;

		molCompList2.push_back(comp);
	}

	if (molCompList2.empty())  // go back to state after solvent stripping
		molCompList2 = molCompList1;  

	bool salts_stripped = (molCompList1.size() > molCompList2.size());
	
	hashCodeCalc.setAtomHashSeedFunction(HashCodeCalculator::DefAtomHashSeedFunctor(hashCodeCalc, AtomPropertyFlag::TYPE | AtomPropertyFlag::AROMATICITY | AtomPropertyFlag::FORMAL_CHARGE));
	uniqueMolComps.clear();

	for (MoleculeComponentList::const_iterator it = molCompList2.begin(), end = molCompList2.end(); it != end; ++it) {
		const MoleculeComponent& comp = *it;

		tmpMolecule = *comp.first;

		if (neutralize && removeCharges(tmpMolecule)) {
			perceiveSSSR(tmpMolecule, true);
			perceiveHybridizationStates(tmpMolecule, false);
			setAromaticityFlags(tmpMolecule, false);
		}

		makeHydrogenDeplete(tmpMolecule);

		uniqueMolComps.insert(genStructureID(tmpMolecule, hashCodeCalc));
	}

	bool dups_removed = false;
			
	if (uniqueMolComps.size() == 1 && molCompList2.size() > 1) {
		molCompList2.resize(1);
		dups_removed = true;
	}
	
	bool excluded = false;
	
	if (check_exclusion) {
		std::size_t boron_count = 0;

		for (MoleculeComponentList::const_iterator it = molCompList2.begin(), end = molCompList2.end(); it != end; ++it) {
			const MoleculeComponent& comp = *it;

			if (checkExclusionCriterions(*comp.first, boron_count)) {
				excluded = true;
				break;
			}
		}
	}
	
	if (excluded) { // go back to state after solvent stripping
		molCompList2 = molCompList1;
		salts_stripped = false;
		dups_removed = false;
	}
	
	if (molCompList2.size() != mol_comps->getSize()) {
		bool clear_sssr = false;

		for (FragmentList::ElementIterator it1 = mol_comps->getElementsBegin(); it1 != mol_comps->getElementsEnd(); ) {
			const Fragment& comp = *it1;
			bool keep_comp = false;
			
			for (MoleculeComponentList::const_iterator it2 = molCompList2.begin(), end2 = molCompList2.end(); it2 != end2; ++it2) {
				if (&comp == it2->first) {
					keep_comp = true;
					break;
				}
			}

			if (keep_comp) {
				++it1;
				continue;
			}

			for (Fragment::ConstAtomIterator a_it = comp.getAtomsBegin(), a_end = comp.getAtomsEnd(); a_it != a_end; ++a_it) {
				const Atom& atom = *a_it;

				if (getRingFlag(atom))
					clear_sssr = true;

				mol.removeAtom(mol.getAtomIndex(atom));
			}
			
			it1 = mol_comps->removeElement(it1);
		}

		if (clear_sssr)
			clearSSSR(mol);
	}
	
	if (excluded)
		changes = ChangeFlags(changes | EXCLUDED);

	if (salts_stripped)
		changes = ChangeFlags(changes | SALT_COMPONENTS_REMOVED);

	if (dups_removed)
		changes = ChangeFlags(changes | DUPLICATE_COMPONENTS_REMOVED);

	if (neutralize && removeCharges(mol))
		changes = ChangeFlags(changes | CHARGES_REMOVED);
	
	return changes;
}

Chem::ChEMBLStandardizer::ChangeFlags Chem::ChEMBLStandardizer::getParent(const Molecule& mol, Molecule& parent_mol, bool neutralize, bool check_exclusion)
{
	copyMolecule(mol, parent_mol);
	
	return getParent(parent_mol, neutralize, check_exclusion);
}

Chem::ChEMBLStandardizer& Chem::ChEMBLStandardizer::operator=(const ChEMBLStandardizer& standardizer)
{
	return *this;
}
	
void Chem::ChEMBLStandardizer::copyMolecule(const Molecule& mol, Molecule& mol_copy) const
{
	mol_copy.copy(mol);
//	mol_copy.clearProperties();

	copyAtomStereoDescriptors(mol, mol_copy);
	copyBondStereoDescriptors(mol, mol_copy);

	if (hasSSSR(mol))
		copySSSR(mol, mol_copy);

	clearComponents(mol_copy);
}

bool Chem::ChEMBLStandardizer::checkExclusionCriterions(const Molecule& mol) const
{
	std::size_t boron_count = 0;
	
	return checkExclusionCriterions(mol, boron_count);
}

bool Chem::ChEMBLStandardizer::checkExclusionCriterions(const MolecularGraph& molgraph, std::size_t& boron_count) const
{
	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		unsigned int atom_type = getType(*it);

		if (atom_type > AtomType::MAX_ATOMIC_NO)
			return true;

		if (excludeAtomTypeMask.test(atom_type))
			return true;

		if (atom_type == AtomType::B && boron_count++ == 7)
			return true;
	}

	return false;
}

bool Chem::ChEMBLStandardizer::standardizeUnknownStereochemistry(Molecule& mol) const
{
	bool changes = false;
	
	for (Molecule::BondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) {
		Bond& bond = *it;

		if (getOrder(bond) != 1)
			continue;
		
		unsigned int stereo_flag = get2DStereoFlag(bond);

		if (stereo_flag != BondStereoFlag::EITHER && stereo_flag != BondStereoFlag::REVERSE_EITHER)
			continue;

		for (std::size_t i = 0; i < 2; i++) {
			Atom& atom = (i == 0 ? bond.getBegin() : bond.getEnd());

			clearStereoDescriptor(atom);

			for (Atom::BondIterator nb_it = atom.getBondsBegin(), nb_end = atom.getBondsEnd(); nb_it != nb_end; ++nb_it) {
				Bond& nbr_bond = *nb_it;

				clearStereoDescriptor(nbr_bond);

				if (getOrder(nbr_bond) == 2 && Internal::getBondCount(nbr_bond.getNeighbor(atom), mol, 2) > 1)
					set2DStereoFlag(nbr_bond, BondStereoFlag::EITHER);
				else
					clear2DStereoFlag(nbr_bond);
			}
		}
		
		changes = true;
	}

	FragmentList::SharedPointer sssr = perceiveSSSR(mol, false);

	for (FragmentList::ElementIterator it = sssr->getElementsBegin(), end = sssr->getElementsEnd(); it != end; ++it) {
		Fragment& ring = *it;

		if (ring.getNumBonds() > 8)
			continue;

		for (Fragment::BondIterator b_it = ring.getBondsBegin(), b_end = ring.getBondsEnd(); b_it != b_end; ++b_it) {
			Bond& bond = *b_it;
			unsigned int stereo_flag = get2DStereoFlag(bond);
		
			if (stereo_flag != BondStereoFlag::EITHER && stereo_flag != BondStereoFlag::REVERSE_EITHER)
				continue;
		
			if (getOrder(bond) == 2) {
				clear2DStereoFlag(bond);
				changes = true;
			}
		}
	}
	
	return changes;
}

bool Chem::ChEMBLStandardizer::kekulizeBonds(Molecule& mol)
{
	bool changes = false;

	kekuleStructureCalc.calculate(mol, kekulizedBondOrders);

	for (std::size_t i = 0, num_bonds = mol.getNumBonds(); i < num_bonds; i++) {
		Bond& bond = mol.getBond(i);

		if (getOrder(bond) == kekulizedBondOrders[i])
			continue;

		setOrder(bond, kekulizedBondOrders[i]);
		changes = true;
	}

	if (!changes)
		return false;

	std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), static_cast<void (*)(Atom&)>(&clearHybridizationState));
	std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), static_cast<void (*)(Atom&)>(&clearAromaticityFlag));
	std::for_each(mol.getBondsBegin(), mol.getBondsEnd(), static_cast<void (*)(Bond&)>(&clearAromaticityFlag));
		
	return true;
}

bool Chem::ChEMBLStandardizer::removeExplicitHydrogens(Molecule& mol) const
{
	calcImplicitHydrogenCounts(mol, false);
	setRingFlags(mol, false);
	perceiveHybridizationStates(mol, false);
	setAromaticityFlags(mol, false);
	calcAtomStereoDescriptors(mol, false);
	
	bool changes = false;

	for (std::size_t i = mol.getNumAtoms(); i > 0; i--) {
		std::size_t atom_idx = i - 1;
		Atom& atom = mol.getAtom(atom_idx);
		
		if (isRemovableHydrogen(atom)) {
			Atom& con_atom = atom.getAtom(0);
			
			mol.removeAtom(atom_idx);

			setImplicitHydrogenCount(con_atom, getImplicitHydrogenCount(con_atom) + 1);
			
			changes = true;
		}
	}

	if (changes)
		clearComponents(mol);
	
	return changes;
}

bool Chem::ChEMBLStandardizer::isRemovableHydrogen(const Atom& atom) const
{
	return chargeStandardizer.isRemovableHydrogen(atom);
}

bool Chem::ChEMBLStandardizer::normalizeStructure(Molecule& mol)
{
	std::call_once(initStructNormTransformPatternsFlag, &initStructNormTransformPatterns);
	
	bool changes = false;
	bool clr_comps = false;
	bool clr_arom = false;
	bool clr_sssr = false;

	for (std::size_t i = 0; i < sizeof(STRUCT_NORM_TRANSFORMS) / sizeof(SubstructureTransform); i++) {
		const Molecule& ptn_mol = *STRUCT_NORM_TRANSFORM_PATTERNS[i];
		
		substructSearch.setQuery(ptn_mol);

		if (!substructSearch.findMappings(mol))
			continue;

		bool recalc_ring_flags = false;
		const long* bond_orders = STRUCT_NORM_TRANSFORMS[i].bondOrders;
					
		for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(), end = substructSearch.getMappingsEnd(); it != end; ++it) {
			const AtomMapping& atom_mpg = it->getAtomMapping();

			for (std::size_t j = 1, orders_end = std::size_t(bond_orders[0] * 3 + 1); j < orders_end; j += 3) {
				const Atom* bond_atom1 = atom_mpg[getAtomWithMappingID(ptn_mol, bond_orders[j])];

				if (!bond_atom1)
					continue;

				const Atom* bond_atom2 = atom_mpg[getAtomWithMappingID(ptn_mol, bond_orders[j + 1])];

				if (!bond_atom2)
					continue;

				Bond* bond = const_cast<Bond*>(bond_atom1->findBondToAtom(*bond_atom2));

				if (!bond)
					continue;

				std::size_t order = bond_orders[j + 2];
				bool is_ring_bond = getRingFlag(*bond);
				
				if (order == 0) {
					mol.removeBond(mol.getBondIndex(*bond));

					if (is_ring_bond) {
						recalc_ring_flags = true;
						clr_sssr = true;
						clr_arom = true;

					} else
						clr_comps = true;
					
				} else {
					if (is_ring_bond || getRingFlag(*bond_atom1) || getRingFlag(*bond_atom2))
						clr_arom = true;

					if (getOrder(*bond) == 2 && order == 1) {
						clear2DStereoFlag(*bond);
						clearStereoDescriptor(*bond);
					}
					
					setOrder(*bond, order);
				}
				
				changes = true;
			}

			const long* atom_charges = STRUCT_NORM_TRANSFORMS[i].atomCharges;

			for (std::size_t j = 1, charges_end = std::size_t(atom_charges[0] * 2 + 1); j < charges_end; j += 2) {
				const Atom* atom = atom_mpg[getAtomWithMappingID(ptn_mol, atom_charges[j])];

				if (!atom)
					continue;
			
				setFormalCharge(const_cast<Atom&>(*atom), atom_charges[j + 1]);

				if (getRingFlag(*atom))
					clr_arom = true;
				
				changes = true;
			}

			for (AtomMapping::ConstEntryIterator a_it = atom_mpg.getEntriesBegin(), a_end = atom_mpg.getEntriesEnd(); a_it != a_end; ++a_it) {
				const Atom* atom = a_it->second;

				if (!atom || !getAtomMappingID(*atom))
					continue;
				
				setImplicitHydrogenCount(const_cast<Atom&>(*atom), calcImplicitHydrogenCount(*atom, mol));
			}
		}

		if (recalc_ring_flags)
			setRingFlags(mol, true);
	}

	if (!changes)
		return false;

	if (clr_comps)
		clearComponents(mol);

	if (clr_sssr) 
		clearSSSR(mol);

	if (clr_arom) {
		std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), static_cast<void (*)(Atom&)>(&clearAromaticityFlag));
		std::for_each(mol.getBondsBegin(), mol.getBondsEnd(), static_cast<void (*)(Bond&)>(&clearAromaticityFlag));
	}

	std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), &clearHybridizationState);
			
	return true;
}

const Chem::Atom* Chem::ChEMBLStandardizer::getAtomWithMappingID(const Molecule& ptn, std::size_t id) const
{
	for (Molecule::ConstAtomIterator it = ptn.getAtomsBegin(), end = ptn.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (getAtomMappingID(atom) == id)
			return &atom;
	}

	return 0;
}

bool Chem::ChEMBLStandardizer::removeCharges(Molecule& mol)
{
	return chargeStandardizer.standardize(mol, ProtonationStateStandardizer::MAX_CHARGE_COMPENSATION);
}

bool Chem::ChEMBLStandardizer::removeTartrateStereochemistry(Molecule& mol)
{
	std::call_once(initTartratePatternFlag, &initTartratePattern);

	perceiveHybridizationStates(mol, false);
	setAromaticityFlags(mol, false);
	
	substructSearch.setQuery(*TARTRATE_PATTERN);

	if (!substructSearch.findMappings(mol))
		return false;

	bool changes = false;
					
	for (SubstructureSearch::ConstMappingIterator it = substructSearch.getMappingsBegin(), end = substructSearch.getMappingsEnd(); it != end; ++it) {
		const AtomMapping& atom_mpg = it->getAtomMapping();

		for (std::size_t i = 1; i <= 2; i++) {
			Atom* atom = const_cast<Atom*>(atom_mpg[getAtomWithMappingID(*TARTRATE_PATTERN, i)]);

			if (!atom || !hasStereoDescriptor(*atom))
				continue;

			const StereoDescriptor& sto_descr = getStereoDescriptor(*atom);

			if (!sto_descr.isValid(*atom) ||
				(sto_descr.getConfiguration() != AtomConfiguration::R && sto_descr.getConfiguration() != AtomConfiguration::S))
				continue;
			
			clearStereoDescriptor(*atom);
			changes = true;
		}
	}

	return changes;
}
	
bool Chem::ChEMBLStandardizer::cleanup2DStructure(Molecule& mol)
{
	const double MAX_LINEARITY_DEV = 0.017;
	
	if (!hasCoordinates(mol, 2))
		return false;

	bool changes = false;

	atom2DCoords.clear();

	for (Molecule::ConstBondIterator it = mol.getBondsBegin(), end = mol.getBondsEnd(); it != end; ++it) { // check and correct triple bonds
		const Bond& bond = *it;

		if (getOrder(bond) != 3)
			continue;

		if (getRingFlag(bond))
			continue;
		
		for (std::size_t i = 0; i < 2; i++) {
			const Atom& ctr_atom = bond.getAtom(i);
			
			if (ctr_atom.getNumBonds() != 2)
				continue;

			double lin_dev = calc2DBondAngle(mol, ctr_atom, ctr_atom.getAtom(0), ctr_atom.getAtom(1)) - M_PI;

			if (std::abs(lin_dev) <= MAX_LINEARITY_DEV)
				continue;
			
			rotateSubstituent(mol, ctr_atom, ctr_atom.getAtom(1), -lin_dev);
			changes = true;
		}
	}

	for (Molecule::ConstAtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) { // check and correct allene-like structures
		const Atom& atom = *it;

		if (getType(atom) != AtomType::C)
			continue;

		if (getRingFlag(atom))
			continue;

		if (atom.getNumBonds() != 2)
			continue;

		if (Internal::getExplicitBondCount(atom, mol, 2) != 2)
			continue;

		double lin_dev = calc2DBondAngle(mol, atom, atom.getAtom(0), atom.getAtom(1)) - M_PI;

		if (std::abs(lin_dev) <= MAX_LINEARITY_DEV)
			continue;
			
		rotateSubstituent(mol, atom, atom.getAtom(1), -lin_dev);
		changes = true;
	}
	
	if (changes)
		set2DCoordinates(mol, atom2DCoords);
		
	return changes;
}

double Chem::ChEMBLStandardizer::calc2DBondAngle(const Molecule& mol, const Atom& ctr_atom, const Atom& nbr_atom1, const Atom& nbr_atom2)
{
	if (atom2DCoords.isEmpty())
		get2DCoordinates(mol, atom2DCoords);

	std::size_t ctr_atom_idx = ctr_atom.getIndex();

	Math::Vector2D bond1_vec(atom2DCoords[nbr_atom1.getIndex()] - atom2DCoords[ctr_atom_idx]);
	double bond1_len = length(bond1_vec);

	if (bond1_len <= 1E-6)
		return M_PI;

	Math::Vector2D bond2_vec(atom2DCoords[nbr_atom2.getIndex()] - atom2DCoords[ctr_atom_idx]);
	double bond2_len = length(bond2_vec);

	if (bond2_len <= 1E-6)
		return M_PI;

	bond1_vec /= bond1_len;
	bond2_vec /= bond2_len;

	double ang_cos = bond1_vec(0) * bond2_vec(0) + bond1_vec(1) * bond2_vec(1);
	double ang_sin = bond1_vec(0) * bond2_vec(1) - bond1_vec(1) * bond2_vec(0);
	double ang = std::atan2(ang_sin, ang_cos);

	if (ang >= 0)
		return ang;

	return (2 * M_PI + ang);
}

void Chem::ChEMBLStandardizer::rotateSubstituent(const Molecule& mol, const Atom& ctr_atom, const Atom& subst_atom, double rot_ang)
{
	markedAtomSet.resize(mol.getNumAtoms());
	markedAtomSet.reset();
	markedAtomSet.set(ctr_atom.getIndex());

	markReachableAtoms(subst_atom, mol, markedAtomSet, false);

	double rot_ang_cos = std::cos(rot_ang);
	double rot_ang_sin = std::sin(rot_ang);
	const Math::Vector2D& ctr_atom_pos = atom2DCoords[ctr_atom.getIndex()];
	
	for (Util::BitSet::size_type atom_idx = markedAtomSet.find_first(); atom_idx != Util::BitSet::npos; atom_idx = markedAtomSet.find_next(atom_idx)) {
		Math::Vector2D& atom_pos = atom2DCoords[atom_idx];
		double x_transl = atom_pos(0) - ctr_atom_pos(0);
		double y_transl = atom_pos(1) - ctr_atom_pos(1);

		atom_pos(0) = x_transl * rot_ang_cos - y_transl * rot_ang_sin + ctr_atom_pos(0);
		atom_pos(1) = x_transl * rot_ang_sin + y_transl * rot_ang_cos + ctr_atom_pos(1);
	}
}

void Chem::ChEMBLStandardizer::clearMatchConstraints(Molecule& mol) const
{
	std::for_each(mol.getAtomsBegin(), mol.getAtomsEnd(), static_cast<void (*)(Atom&)>(&Chem::clearMatchConstraints));
	std::for_each(mol.getBondsBegin(), mol.getBondsEnd(), static_cast<void (*)(Bond&)>(&Chem::clearMatchConstraints));
}
