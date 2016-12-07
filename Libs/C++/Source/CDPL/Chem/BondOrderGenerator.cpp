/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondOrderGenerator.cpp 
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

#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <sstream>
#include <cmath>
#include <cassert>
#include <limits>

#include <boost/bind.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

#include "CDPL/Chem/BondOrderGenerator.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/AtomBondMapping.hpp"
#include "CDPL/Chem/MatchExpression.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Math/Vector.hpp"


using namespace CDPL;


namespace
{

	Util::STArray CHALCOGENIDE_VAL_STATES_BCGE4;

    std::string FUNC_GROUP_PATTERN_STRINGS[] = { 
	    "N-C(-*)=O",
	    "*:N-C(-*)=O",

		"O-C(-*)=O",
		"*-O-C(-*)=O",

		"O-[Se](-*)=O",
		"*-O-[Se](-*)=O",
		"S-C(-*)=O",
		"*:S-C(-*)=O",
		"S-C(-*)=S",
		"*:S-C(-*)=S",

		"N-C(-*)=S",
		"*:N-C(-*)=S",

		"*:N-C(-N)=N",
		"N-C(-N)=N-*",
		"N-C(-*)=N",
	
		"*-S(=O)(=O)-*",
		"*-P(-*)(-*)=O",
		"*-N=N=N",
		"*-N(-O)=O"
	};
	
	typedef std::vector<Chem::Molecule::SharedPointer> MoleculeTable;

	MoleculeTable FUNC_GROUP_PATTERN_MOLS;

	void initFunctionalGroupPatterns() 
	{
		static bool initialized = false;

		if (initialized)
			return;

		initialized = true;

		for (std::size_t i = 0; i < sizeof(FUNC_GROUP_PATTERN_STRINGS) / sizeof(std::string); i++) {
			using namespace Chem;

			std::istringstream iss(FUNC_GROUP_PATTERN_STRINGS[i]);
			SMILESMoleculeReader smi_reader(iss);
			Molecule::SharedPointer mol_ptr(new BasicMolecule());

			if (smi_reader.read(*mol_ptr)) 
				FUNC_GROUP_PATTERN_MOLS.push_back(mol_ptr);
		}

		CHALCOGENIDE_VAL_STATES_BCGE4.addElement(6);
	}

	void genMappedBondMask(const Chem::AtomBondMapping& mapping, Util::BitSet& mask, const Chem::MolecularGraph& molgraph)
	{
		using namespace Chem;

		const BondMapping& bnd_mapping = mapping.getBondMapping();

		mask.reset();

		for (BondMapping::ConstEntryIterator it = bnd_mapping.getEntriesBegin(), end = bnd_mapping.getEntriesEnd(); it != end; ++it)
			mask.set(molgraph.getBondIndex(*it->second));
	}

 	struct True 
	{

		bool operator()(const Chem::Bond&) const {
			return true;
		}
	};

	struct BondAtomTypeCmpFunc : public std::binary_function<const Chem::Bond*, const Chem::Bond*, bool>
	{

		BondAtomTypeCmpFunc(std::size_t atom_idx): atomIdx(atom_idx) {}

		bool operator()(const Chem::Bond* bond1, const Chem::Bond* bond2) const {
			using namespace Chem;
			
			return ((getType(bond1->getAtom(atomIdx)) == AtomType::C) && 
					!(getType(bond2->getAtom(atomIdx)) == AtomType::C));
		}

		const std::size_t atomIdx;
	};
}


class Chem::BondOrderGenerator::AtomMatchExpression : public Chem::MatchExpression<Atom, MolecularGraph>
{

public:
	bool operator()(const Atom& qry_atom, const MolecularGraph& qry_molgraph, const Atom& tgt_atom, 
					const MolecularGraph& tgt_molgraph, const Base::Variant&) const {

		unsigned int qry_atom_type = getType(qry_atom); 

		if (qry_atom_type != AtomType::ANY) {
			assert(qry_atom_type != AtomType::UNKNOWN && qry_atom_type <= AtomType::MAX_ATOMIC_NO);

			if (qry_atom_type != getType(tgt_atom))
				return false;

			if (getHeavyBondCount(qry_atom, qry_molgraph) == 1 && getHeavyBondCount(tgt_atom, tgt_molgraph) != 1)
				return false;
		}   

		return true;
	}
};


class Chem::BondOrderGenerator::BondMatchExpression : public Chem::MatchExpression<Bond, MolecularGraph>
{

public:
	BondMatchExpression(const BondOrderGenerator& gen, const Util::STArray& ordrs): generator(gen), orders(ordrs) {}

	bool operator()(const Bond& qry_bond, const MolecularGraph&, const Bond& tgt_bond, 
					const MolecularGraph& tgt_molgraph, const Base::Variant&) const {

		if (hasAromaticityFlag(qry_bond)) 
			return true;

		std::size_t qry_order = getOrder(qry_bond);
		std::size_t tgt_bond_idx = tgt_molgraph.getBondIndex(tgt_bond);

		if (generator.defOrderMask.test(tgt_bond_idx) && orders[tgt_bond_idx] != qry_order)
			return false;

		if (qry_order > 1) {
			const Atom& tgt_atom1 = tgt_bond.getBegin();

			if (getType(tgt_atom1) < AtomType::Ne) {
				switch (generator.atomGeometries[tgt_molgraph.getAtomIndex(tgt_atom1)]) {

					case LINEAR:
					case TRIG_PLANAR:
					case TERMINAL:
						break;

					default:
						return false;
				}
			}

			const Atom& tgt_atom2 = tgt_bond.getEnd();

			if (getType(tgt_atom2) < AtomType::Ne) {
				switch (generator.atomGeometries[tgt_molgraph.getAtomIndex(tgt_atom2)]) {

					case LINEAR:
					case TRIG_PLANAR:
					case TERMINAL:
						break;

					default:
						return false;
				}
			}
		}

		return true;
	}

private:
	const BondOrderGenerator& generator;
	const Util::STArray&      orders;
};


Chem::BondOrderGenerator::BondOrderGenerator(): undefOnly(true) {}

Chem::BondOrderGenerator::BondOrderGenerator(const MolecularGraph& molgraph, Util::STArray& orders, bool undef_only): undefOnly(undef_only) 
{
	generate(molgraph, orders);
}

void Chem::BondOrderGenerator::undefinedOnly(bool undef_only) 
{
	undefOnly = undef_only;
}

bool Chem::BondOrderGenerator::undefinedOnly() const
{
	return undefOnly;
}

void Chem::BondOrderGenerator::generate(const MolecularGraph& molgraph, Util::STArray& orders)
{
	init(molgraph, orders);

	if (undefBonds.empty())
		return;

	calcFreeAtomValences(orders);
	perceiveAtomGeometries(orders);
	assignBondOrders(orders);
}

void Chem::BondOrderGenerator::init(const MolecularGraph& molgraph, Util::STArray& orders)
{
	std::size_t num_bonds = molgraph.getNumBonds();

	molGraph = &molgraph;
	
	orders.assign(num_bonds, 0);
	
	defOrderMask.resize(num_bonds);
	defOrderMask.set();

	conjRingBondMask.resize(num_bonds);
	conjRingBondMask.reset();

	bondMappingMask1.resize(num_bonds);
	bondMappingMask2.resize(num_bonds);

	undefBonds.clear();

	for (std::size_t i = 0; i < num_bonds; i++) {
		const Bond& bond = molgraph.getBond(i);

		if (!molgraph.containsAtom(bond.getBegin()) || !molgraph.containsAtom(bond.getEnd()))
			continue;

		if (undefOnly && hasOrder(bond)) {
			orders[i] = getOrder(bond);

		} else {
			//orders[i] = 1; // UNCOMMENT ME
			defOrderMask.reset(i);
			undefBonds.push_back(&bond);
		}
	}

	std::size_t num_atoms = molGraph->getNumAtoms();

	freeAtomValences.clear();
	freeAtomValences.reserve(num_atoms);

	atomGeometries.clear();
	atomGeometries.reserve(num_atoms);

	multibondAtomMask.resize(num_atoms);
	multibondAtomMask.reset();

    if (!substructSearch)
		substructSearch.reset(new SubstructureSearch());

	if (!funcGroupPatterns.empty())
		return;

	initFunctionalGroupPatterns();

	MatchExpression<Atom, MolecularGraph>::SharedPointer atom_expr(new AtomMatchExpression());
	MatchExpression<Bond, MolecularGraph>::SharedPointer bond_expr(new BondMatchExpression(*this, orders));

	std::size_t num_patterns = FUNC_GROUP_PATTERN_MOLS.size();

	for (std::size_t i = 0; i < num_patterns; i++) {
		Molecule::SharedPointer ptn_copy = FUNC_GROUP_PATTERN_MOLS[i]->clone();

		std::for_each(ptn_copy->getAtomsBegin(), ptn_copy->getAtomsEnd(), 
					  boost::bind(static_cast<void (*)(Atom&, const MatchExpression<Atom,
													   MolecularGraph>::SharedPointer&)>(&setMatchExpression), 
								  _1, atom_expr));

		std::for_each(ptn_copy->getBondsBegin(), ptn_copy->getBondsEnd(), 
					  boost::bind(static_cast<void (*)(Bond&, const MatchExpression<Bond,
													   MolecularGraph>::SharedPointer&)>(&setMatchExpression), 
								  _1, bond_expr));

		buildMatchExpressions(*ptn_copy, false);

		funcGroupPatterns.push_back(ptn_copy);
	}
}

void Chem::BondOrderGenerator::calcFreeAtomValences(Util::STArray& orders)
{
	for (MolecularGraph::ConstAtomIterator it = molGraph->getAtomsBegin(), end = molGraph->getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		long valence = 0;
		long num_undef_nbr_bonds = 0;
		
		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
			const Bond& bond = *b_it;

			if (!molGraph->containsBond(bond) || !molGraph->containsAtom(*a_it))
				continue;

			std::size_t bond_idx = molGraph->getBondIndex(bond);

			if (!defOrderMask.test(bond_idx))
				num_undef_nbr_bonds++;
			else
				valence += orders[bond_idx];
		}

		if (num_undef_nbr_bonds == 0) {
			freeAtomValences.push_back(0);
			continue;
		}
	
		if (hasImplicitHydrogenCount(atom))
			valence += getImplicitHydrogenCount(atom);

		unsigned int atom_type = getType(atom);
		long charge = getFormalCharge(atom);

		if (atom_type == AtomType::C)
			charge = std::min(charge, -charge);

		const Util::STArray* valence_states;

		if (AtomDictionary::getIUPACGroup(atom_type) == 16 && atom_type > AtomType::O && getExplicitBondCount(atom, *molGraph) >= 4)
		 	valence_states = &CHALCOGENIDE_VAL_STATES_BCGE4;			
		else
			valence_states = &AtomDictionary::getValenceStates(atom_type);		

		bool def_nbr_bonds = false;

		for (std::size_t j = 0; true; j++) {
			if (j == valence_states->getSize()) {
				def_nbr_bonds = true;
				break;
			}

			long free_valence = valence_states->getElement(j) + charge - valence;

			if (free_valence > num_undef_nbr_bonds) {
				freeAtomValences.push_back(std::size_t(free_valence));
				break;
			}

			if (free_valence == num_undef_nbr_bonds) {
				def_nbr_bonds = true;
				break;
			}
		}

		if (def_nbr_bonds) {
			assignNbrBondOrders(atom, orders);
			freeAtomValences.push_back(0);
		}
	}
}

void Chem::BondOrderGenerator::perceiveAtomGeometries(Util::STArray& orders)
{
	std::transform(molGraph->getAtomsBegin(), molGraph->getAtomsEnd(), 
				   std::back_inserter(atomGeometries),
				   boost::bind(&BondOrderGenerator::perceiveInitialGeometry, this, _1));

	FragmentList::SharedPointer sssr = getSSSR(*molGraph);

	std::for_each(sssr->getElementsBegin(), sssr->getElementsEnd(), 
				  boost::bind(&BondOrderGenerator::fixRingAtomGeometries, this, _1));

	std::for_each(molGraph->getAtomsBegin(), molGraph->getAtomsEnd(), 
				  boost::bind(&BondOrderGenerator::postprocessGeometry, this, _1, boost::ref(orders)));
}

void Chem::BondOrderGenerator::assignBondOrders(Util::STArray& orders)
{
	assignTetrahedralAtomBondOrders(orders);
	assignFunctionalGroupBondOrders(orders);
	assignConjRingBondOrders(orders);
	assignRemainingBondOrders(orders);
}

void Chem::BondOrderGenerator::assignTetrahedralAtomBondOrders(Util::STArray& orders)
{
	for (BondList::const_iterator it = undefBonds.begin(), end = undefBonds.end(); it != end; ++it) {
		const Bond* bond = *it;
		std::size_t bond_idx = molGraph->getBondIndex(*bond);

		if (defOrderMask.test(bond_idx))
			continue;

		const Atom& atom1 = bond->getBegin();
		const Atom& atom2 = bond->getEnd();
		
		std::size_t atom1_idx = molGraph->getAtomIndex(atom1);
		std::size_t atom2_idx = molGraph->getAtomIndex(atom2);
	
		if ((atomGeometries[atom1_idx] == TETRAHEDRAL && getType(atom1) < AtomType::Ne && getExplicitBondCount(atom1, *molGraph) > 2) ||
			(atomGeometries[atom2_idx] == TETRAHEDRAL && getType(atom2) < AtomType::Ne && getExplicitBondCount(atom2, *molGraph) > 2)) {

			defOrderMask.set(bond_idx);
			orders[bond_idx] = 1; // REMOVE ME
			
			assert(freeAtomValences[atom1_idx] > 0);
			freeAtomValences[atom1_idx]--;

			assert(freeAtomValences[atom2_idx] > 0);
			freeAtomValences[atom2_idx]--;
		}
	}
}

void Chem::BondOrderGenerator::assignFunctionalGroupBondOrders(Util::STArray& orders)
{
	for (MolecularGraphPtrList::const_iterator ptn_it = funcGroupPatterns.begin(), ptn_end = funcGroupPatterns.end(); 
		 ptn_it != ptn_end; ++ptn_it) {

		const MolecularGraph& pattern = *ptn_it->get();

		substructSearch->setQuery(pattern);
		
		if (!substructSearch->findMappings(*molGraph))
			continue;

		std::size_t num_mappings = substructSearch->getNumMappings();

		procMappingMask.resize(num_mappings);
		procMappingMask.reset();

		for (std::size_t i = 0; i < num_mappings; i++) {
			if (procMappingMask.test(i))
				continue;

			const AtomBondMapping& mapping = substructSearch->getMapping(i);
			const BondMapping& bond_mapping = mapping.getBondMapping();
			bool has_undef_bonds = false;

			for (BondMapping::ConstEntryIterator it = bond_mapping.getEntriesBegin(), end = bond_mapping.getEntriesEnd(); it != end; ++it) {
				const Bond& mpd_bond = *it->second;
				std::size_t mpd_bond_idx = molGraph->getBondIndex(mpd_bond);

				if (!defOrderMask.test(mpd_bond_idx))
					has_undef_bonds = true;
			}
	
			procMappingMask.set(i);

			if (has_undef_bonds) {
				funcGroupMappings.clear();
				funcGroupMappings.push_back(std::make_pair(0.0, &mapping));
			}

			genMappedBondMask(mapping, bondMappingMask1, *molGraph);
			
			for (std::size_t j = i + 1; j < num_mappings; j++) {
				const AtomBondMapping& next_mapping = substructSearch->getMapping(j);

				genMappedBondMask(next_mapping, bondMappingMask2, *molGraph);

				if (bondMappingMask1 == bondMappingMask2) {
					if (has_undef_bonds)
						funcGroupMappings.push_back(std::make_pair(0.0, &next_mapping));
				
					procMappingMask.set(j);
				}
			}

			if (!has_undef_bonds)
				continue;

			if (funcGroupMappings.size() > 1) {
				for (ABMappingList::iterator m_it = funcGroupMappings.begin(), m_end = funcGroupMappings.end(); m_it != m_end; ++m_it) {
					double score = calcMappingScore(*m_it->second);
					m_it->first = score;
				}

				std::sort(funcGroupMappings.begin(), funcGroupMappings.end(), 
						  boost::bind(std::greater<double>(), 
									  boost::bind(&ABMappingList::value_type::first, _1), 
									  boost::bind(&ABMappingList::value_type::first, _2)));
			}

			for (ABMappingList::const_iterator m_it = funcGroupMappings.begin(), m_end = funcGroupMappings.end(); m_it != m_end; ++m_it) {
				const BondMapping& curr_bond_mapping = m_it->second->getBondMapping();
				bool success = true;

				fragBondList.clear();

				for (BondMapping::ConstEntryIterator it = curr_bond_mapping.getEntriesBegin(), end = curr_bond_mapping.getEntriesEnd(); it != end; ++it) {
					const Bond& ptn_bond = *it->first;

					if (hasAromaticityFlag(ptn_bond))
						continue;

					const Bond& mpd_bond = *it->second;
					std::size_t mpd_bond_idx = molGraph->getBondIndex(mpd_bond);
		
					if (!defOrderMask.test(mpd_bond_idx)) {
						std::size_t order = getOrder(ptn_bond);
				
						const Atom& mpd_atom1 = mpd_bond.getBegin();
						const Atom& mpd_atom2 = mpd_bond.getEnd();

						std::size_t mpd_atom1_idx = molGraph->getAtomIndex(mpd_atom1);
						std::size_t mpd_atom2_idx = molGraph->getAtomIndex(mpd_atom2);

						assert(freeAtomValences[mpd_atom1_idx] >= 0);
						assert(freeAtomValences[mpd_atom2_idx] >= 0);

						if (freeAtomValences[mpd_atom1_idx] >= order && freeAtomValences[mpd_atom2_idx] >= order) {
							defOrderMask.set(mpd_bond_idx);
							orders[mpd_bond_idx] = order;

							freeAtomValences[mpd_atom1_idx] -= order;
							freeAtomValences[mpd_atom2_idx] -= order;

							fragBondList.push_back(&mpd_bond);

						} else {
							for (BondList::const_iterator b_it = fragBondList.begin(), b_end = fragBondList.end(); b_it != b_end; ++b_it) {
								const Bond* bond = *b_it;
								std::size_t bond_idx = molGraph->getBondIndex(*bond);

								defOrderMask.reset(bond_idx);

								const Atom& atom1 = bond->getBegin();
								const Atom& atom2 = bond->getEnd();

								std::size_t atom1_idx = molGraph->getAtomIndex(atom1);
								std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

								freeAtomValences[atom1_idx] += orders[bond_idx];
								freeAtomValences[atom2_idx] += orders[bond_idx];

								orders[bond_idx] = 0; // REMOVE ME
							}

							success = false;
							break;
						}
					}
				}

				if (success)
					break;
			}
		}
	}
}

double Chem::BondOrderGenerator::calcMappingScore(const AtomBondMapping& mapping) const
{
	double score = 0.0;
 	const BondMapping& bond_mapping = mapping.getBondMapping();

	for (BondMapping::ConstEntryIterator it = bond_mapping.getEntriesBegin(), end = bond_mapping.getEntriesEnd(); it != end; ++it) {
		const Bond& bond = *it->first;
		const Bond& mpd_bond = *it->second;

		std::size_t order = getOrder(bond);

		if (order > 1 && getRingFlag(mpd_bond))
			score += 1.0;

		const Atom& atom1 = mpd_bond.getBegin();
		const Atom& atom2 = mpd_bond.getEnd();

		double bond_length = length(get3DCoordinates(atom1) - get3DCoordinates(atom2));
		double cov_rad_bond_length = AtomDictionary::getCovalentRadius(getType(atom1), order) + AtomDictionary::getCovalentRadius(getType(atom2), order);
		double bond_length_diff = std::abs(bond_length - cov_rad_bond_length);

		score -= bond_length_diff;
	}

	return score;
}

void Chem::BondOrderGenerator::assignConjRingBondOrders(Util::STArray& orders)
{
	markConjRingBonds(orders);

	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> BondGraph; 
	typedef boost::property_map<BondGraph, boost::vertex_index_t>::type AtomIndexMap;
	typedef boost::graph_traits<BondGraph>::vertex_descriptor VertexDescriptor;
	typedef std::vector<VertexDescriptor> VertexList;

 	std::size_t num_verts = atomGeometries.size();

	BondGraph bond_graph(num_verts);
	VertexList max_match(num_verts);
	BondList undef_bonds;

	for (BondList::const_iterator it = undefBonds.begin(), end = undefBonds.end(); it != end; ++it) {
		const Bond* bond = *it;
		std::size_t bond_idx = molGraph->getBondIndex(*bond);

		if (defOrderMask.test(bond_idx))
			continue;

		fragBondList.clear();

		getUndefBondFragment(bond->getBegin(), false, 
							 boost::bind(&BondOrderGenerator::isConjRingBond, this, _1));

		if (fragBondList.empty())
			continue;

		bond_graph.clear();

		BondList::iterator undef_bonds_beg = fragBondList.begin();
		BondList::iterator undef_bonds_end = fragBondList.end();

		for (BondList::iterator it = undef_bonds_beg; it != undef_bonds_end; ++it) {
			const Bond* bond = *it;
			const Atom& atom1 = bond->getBegin();
			const Atom& atom2 = bond->getEnd();

			std::size_t atom1_idx = molGraph->getAtomIndex(atom1);
			std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

			orders[molGraph->getBondIndex(*bond)] = 1; // REMOVE ME

			assert(freeAtomValences[atom1_idx] > 0);
			freeAtomValences[atom1_idx]--;
				
			assert(freeAtomValences[atom2_idx] > 0);
			freeAtomValences[atom2_idx]--;

			boost::add_edge(atom1_idx, atom2_idx, bond_graph);
		}

		std::sort(undef_bonds_beg, undef_bonds_end, BondAtomTypeCmpFunc(1));
		std::stable_sort(undef_bonds_beg, undef_bonds_end, BondAtomTypeCmpFunc(0));

		max_match.assign(num_verts, boost::graph_traits<BondGraph>::null_vertex());

		for (BondList::iterator it = undef_bonds_beg; it != undef_bonds_end; ++it) {
			const Bond* bond = *it;
			VertexDescriptor u = boost::vertex(molGraph->getAtomIndex(bond->getBegin()), bond_graph);
			VertexDescriptor v = boost::vertex(molGraph->getAtomIndex(bond->getEnd()), bond_graph);

			if (boost::get(&max_match[0], u) == get(&max_match[0], v)) {
				put(&max_match[0], u, v);
				put(&max_match[0], v, u);
			}
		}    
		
		boost::edmonds_augmenting_path_finder<BondGraph, boost::graph_traits<BondGraph>::vertex_descriptor*, AtomIndexMap> 
			augmentor(bond_graph, &max_match[0], boost::get(boost::vertex_index, bond_graph));

		bool not_maximum_yet = true;

		while(not_maximum_yet)
			not_maximum_yet = augmentor.augment_matching();

		augmentor.get_current_matching(&max_match[0]);
		
		AtomIndexMap atom_index_map = boost::get(boost::vertex_index, bond_graph);

		boost::graph_traits<BondGraph>::vertex_iterator vi, vi_end;

		for (boost::tie(vi, vi_end) = boost::vertices(bond_graph); vi != vi_end; ++vi) {
			if (max_match[*vi] != boost::graph_traits<BondGraph>::null_vertex() && *vi < max_match[*vi]) {
				std::size_t atom1_idx = atom_index_map[*vi];
				std::size_t atom2_idx = atom_index_map[max_match[*vi]];

				const Atom& atom1 = molGraph->getAtom(atom1_idx);
				const Atom& atom2 = molGraph->getAtom(atom2_idx);

				std::size_t bond_idx = molGraph->getBondIndex(atom1.getBondToAtom(atom2));

				bondMappingMask1.set(bond_idx);
				
				orders[bond_idx] = 2;

				assert(freeAtomValences[atom1_idx] > 0);
				freeAtomValences[atom1_idx]--;
				
				assert(freeAtomValences[atom2_idx] > 0);
				freeAtomValences[atom2_idx]--;
			}
		}
	}
}

void Chem::BondOrderGenerator::assignRemainingBondOrders(Util::STArray& orders)
{
	for (BondList::const_iterator it = undefBonds.begin(), end = undefBonds.end(); it != end; ++it) {
		const Bond* bond = *it;
		std::size_t bond_idx = molGraph->getBondIndex(*bond);

		if (defOrderMask.test(bond_idx))
			continue;

		const Atom& atom1 = bond->getBegin();
		const Atom& atom2 = bond->getEnd();
			
		std::size_t atom1_idx = molGraph->getAtomIndex(atom1);
		std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

		if (atomGeometries[atom1_idx] != TRIG_PLANAR || atomGeometries[atom2_idx] != TRIG_PLANAR)
			continue;

		getNeighborAtoms(atom1, nbrAtomList1, &atom2);
		getNeighborAtoms(atom2, nbrAtomList2, &atom1);

		std::size_t count = 0;
		double avg_tor_angle = 0.0;

		const Math::Vector3D& atom1_pos = get3DCoordinates(atom1);
		const Math::Vector3D& atom2_pos = get3DCoordinates(atom2);

		for (AtomList::const_iterator it1 = nbrAtomList1.begin(), end1 = nbrAtomList1.end(); it1 != end1; ++it1) {
			const Atom* wing_atom1 = *it1;
			const Math::Vector3D& wing_atom1_pos = get3DCoordinates(*wing_atom1);

			for (AtomList::const_iterator it2 = nbrAtomList2.begin(), end2 = nbrAtomList2.end(); it2 != end2; ++it2) {
				const Atom* wing_atom2 = *it2;
				const Math::Vector3D& wing_atom2_pos = get3DCoordinates(*wing_atom2);

				double angle = calcDihedralAngle(wing_atom1_pos, atom1_pos, atom2_pos, wing_atom2_pos);

				if (angle > M_PI * 0.5)
					angle = M_PI - angle;

				avg_tor_angle += angle;
				count++;
			}
		}

		if (count == 0)
			continue;

		avg_tor_angle = avg_tor_angle * 180.0 / (count * M_PI);

		if (avg_tor_angle >= 30) {
			defOrderMask.set(bond_idx);
			orders[bond_idx] = 1;  // REMOVE ME
			
			assert(freeAtomValences[atom1_idx] > 0);
			freeAtomValences[atom1_idx]--;

			assert(freeAtomValences[atom2_idx] > 0);
			freeAtomValences[atom2_idx]--;
		}
	}

	workingBondOrders.assign(orders.getElementsBegin(), orders.getElementsEnd());

	for (BondList::const_iterator it = undefBonds.begin(), end = undefBonds.end(); it != end; ++it) {
		const Bond* bond = *it;
		std::size_t bond_idx = molGraph->getBondIndex(*bond);

		if (defOrderMask.test(bond_idx))
			continue;

		fragBondList.clear();
		fragAtomList.clear();

		getUndefBondFragment(bond->getBegin(), true, True());
	
		bestOrderAssmentScore = -std::numeric_limits<double>::max();
		currOrderAssmentScore = 0;

		fragBondOrders.resize(fragBondList.size());

		assignFragBondOrders(0, orders);

		// fix order of certain terminal double bonds

		for (BondList::const_iterator it1 = fragBondList.begin(), end1 = fragBondList.end(); it1 != end1; ++it1) {
			const Bond* bond = *it1;
			std::size_t& order = orders[molGraph->getBondIndex(*bond)];

			if (order != 2)
				continue;

			const Atom* atom1 = &bond->getBegin();
			const Atom* atom2 = &bond->getEnd();

			std::size_t atom1_idx = molGraph->getAtomIndex(*atom1);
			std::size_t atom2_idx = molGraph->getAtomIndex(*atom2);

			Geometry atom1_geom = atomGeometries[atom1_idx];
			Geometry atom2_geom = atomGeometries[atom2_idx];

			if (atom2_geom == TRIG_PLANAR && atom1_geom == TERMINAL) {
				std::swap(atom1_idx, atom2_idx);
				std::swap(atom1, atom2);

			} else if (atom1_geom != TRIG_PLANAR || atom2_geom != TERMINAL)
				continue;

			if (getExplicitBondCount(*atom1, *molGraph) > 2)
				continue;

			double bond_length = length(get3DCoordinates(*atom1) - get3DCoordinates(*atom2));

			unsigned int atom1_type = getType(*atom1);
			unsigned int atom2_type = getType(*atom2);

			std::size_t best_order = 0;
			double min_bl_diff = std::numeric_limits<double>::max();
			
			for (std::size_t i = 1; i <= 3; i++) {
				double cov_rad_atom1 = AtomDictionary::getCovalentRadius(atom1_type, i);
				
				if (cov_rad_atom1 <= 0.0)
					continue;

				double cov_rad_atom2 = AtomDictionary::getCovalentRadius(atom2_type, i);
				
				if (cov_rad_atom2 <= 0.0)
					continue;

				double bl_diff = std::abs(bond_length - cov_rad_atom1 - cov_rad_atom2);

				if (bl_diff <= min_bl_diff) {
					best_order = i;
					min_bl_diff = bl_diff;
				}
			}

			if (best_order != 2)
				order = 1;
		}
	}
}

void Chem::BondOrderGenerator::assignFragBondOrders(std::size_t depth, Util::STArray& orders)
{
	std::size_t frag_size = fragBondList.size();

	if (depth >= frag_size) {
		currOrderAssmentScore += calcHybridizationMatchScore();

		if (currOrderAssmentScore <= bestOrderAssmentScore)
			return;

		for (std::size_t i = 0; i < frag_size; i++)
			orders[molGraph->getBondIndex(*fragBondList[i])] = fragBondOrders[i]; 
		
		bestOrderAssmentScore = currOrderAssmentScore;
		return;
	}

	const Bond* bond = fragBondList[depth];
	const Atom& atom1 = bond->getBegin();
	const Atom& atom2 = bond->getEnd();
		
	std::size_t atom1_idx = molGraph->getAtomIndex(atom1);
	std::size_t atom2_idx = molGraph->getAtomIndex(atom2);
	
	std::size_t& free_val_atom1 = freeAtomValences[atom1_idx];
	std::size_t& free_val_atom2 = freeAtomValences[atom2_idx];

	if (free_val_atom1 == 0 || free_val_atom2 == 0)
		return;

	std::size_t max_atom1_order = free_val_atom1;
	Geometry atom1_geom = atomGeometries[atom1_idx];
	bool atom1_mb_flag = multibondAtomMask.test(atom1_idx);

	unsigned int atom1_type = getType(atom1);
	unsigned int atom2_type = getType(atom2);

	switch (atom1_geom) {

		case LINEAR:
			max_atom1_order = std::min(std::size_t(3), free_val_atom1);
			break;

		case TRIG_PLANAR:
			if (atom1_mb_flag) {
				max_atom1_order = 1;
				break;
			}

		case TETRAHEDRAL:
			max_atom1_order = std::min(std::size_t(2), free_val_atom1);
	
		default:
			break;
	}

	std::size_t max_atom2_order = free_val_atom2;
	Geometry atom2_geom = atomGeometries[atom2_idx];
	bool atom2_mb_flag = multibondAtomMask.test(atom2_idx);

	switch (atom2_geom) {

		case LINEAR:
			max_atom2_order = std::min(std::size_t(3), free_val_atom2);
			break;

		case TRIG_PLANAR:
			if (atom2_mb_flag) {
				max_atom2_order = 1;
				break;
			}

		case TETRAHEDRAL:
			max_atom2_order = std::min(std::size_t(2), free_val_atom2);
	
		default:
			break;
	}

	double elneg_score = std::abs(AtomDictionary::getAllredRochowElectronegativity(atom1_type) - 
								  AtomDictionary::getAllredRochowElectronegativity(atom2_type)) * 0.5;
	std::size_t max_order = std::min(max_atom1_order, max_atom2_order);

	double saved_score = currOrderAssmentScore;
	std::size_t saved_free_val_atom1 = free_val_atom1;
	std::size_t saved_free_val_atom2 = free_val_atom2;

	double bond_length = length(get3DCoordinates(atom1) - get3DCoordinates(atom2));
	bool ring_bond = getRingFlag(*bond);

	for (std::size_t order = 1; order <= max_order; order++) {
		double score_contrib = 1.0;
		double cov_rad_bond_length = AtomDictionary::getCovalentRadius(atom1_type, order) + 
			AtomDictionary::getCovalentRadius(atom2_type, order);
		double bond_length_dev = std::abs(bond_length - cov_rad_bond_length);

		score_contrib -= bond_length_dev;

		if (order > 1) {
			multibondAtomMask.set(atom1_idx);
			multibondAtomMask.set(atom2_idx);

			if (ring_bond)
			  	score_contrib += 0.5;

			score_contrib += elneg_score;
		}
	
		currOrderAssmentScore = saved_score + score_contrib;
		free_val_atom1 = saved_free_val_atom1 - order;
		free_val_atom2 = saved_free_val_atom2 - order;

		fragBondOrders[depth] = order;

		assignFragBondOrders(depth + 1, orders);
	}

	currOrderAssmentScore = saved_score;
	free_val_atom1 = saved_free_val_atom1;
	free_val_atom2 = saved_free_val_atom2;

	multibondAtomMask.set(atom1_idx, atom1_mb_flag);
	multibondAtomMask.set(atom2_idx, atom2_mb_flag);
}

double Chem::BondOrderGenerator::calcHybridizationMatchScore() 
{
	std::size_t frag_size = fragBondList.size();

	for (std::size_t i = 0; i < frag_size; i++)
		workingBondOrders[molGraph->getBondIndex(*fragBondList[i])] = fragBondOrders[i]; 
	
	double score = 0.0;

	for (AtomList::const_iterator it = fragAtomList.begin(), end = fragAtomList.end(); it != end; ++it) {
		const Atom& atom = *(*it);
		std::size_t atom_idx = molGraph->getAtomIndex(atom);

		switch (atomGeometries[atom_idx]) {

			case LINEAR:
				if (countBondsWithOrder(atom, 2, workingBondOrders) == 2 ||
					(countBondsWithOrder(atom, 1, workingBondOrders) == 1 && countBondsWithOrder(atom, 3, workingBondOrders) == 1))
					break;
				continue;

			case TRIG_PLANAR:
				if (getType(atom) != AtomType::C)
					continue;

				if (countBondsWithOrder(atom, 2, workingBondOrders) == 1)
					break;
				continue;

			case TETRAHEDRAL:
				if (getType(atom) != AtomType::C)
					continue;

				if (countBondsWithOrder(atom, 2, workingBondOrders) == 0)
					break;

			default:
				continue;
		}

		score += 1.0;
	}

	return score;
}

void Chem::BondOrderGenerator::markConjRingBonds(Util::STArray& orders) 
{
	FragmentList::SharedPointer sssr = getSSSR(*molGraph);

	for (FragmentList::ConstElementIterator it = sssr->getElementsBegin(), end = sssr->getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;
		std::size_t size = ring.getNumAtoms();

		if (size != 5 && size != 6)
			continue;

		bool skip = false;

		for (std::size_t i = 0; i < size && !skip; i++) {
			const Atom& atom = ring.getAtom(i);
			const Bond& bond = ring.getBond(i);

			std::size_t atom_idx = molGraph->getAtomIndex(atom);

			if (atomGeometries[atom_idx] != TRIG_PLANAR) {
				skip = true;
				break;
			}

			switch (getType(atom)) {

				case AtomType::C: {
					std::size_t bond_idx = molGraph->getBondIndex(bond);
					std::size_t prev_bond_idx = molGraph->getBondIndex(ring.getBond((i + size - 1) % size));

					if (defOrderMask.test(bond_idx) && orders[bond_idx] == 1 && 
						defOrderMask.test(prev_bond_idx) && orders[prev_bond_idx] == 1) {
						skip = true;
					}

					continue;		
				}

				case AtomType::N:
				case AtomType::O:
				case AtomType::S:
				case AtomType::Se:
					continue;

				default:
					skip = true;
					continue;		
			}
		}

		if (skip)
			continue;

		for (Fragment::ConstBondIterator it = ring.getBondsBegin(), end = ring.getBondsEnd(); it != end; ++it)
			conjRingBondMask.set(molGraph->getBondIndex(*it), true);
	}
}

void Chem::BondOrderGenerator::assignNbrBondOrders(const Atom& atom, Util::STArray& orders)
{
	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	std::size_t atom_idx = molGraph->getAtomIndex(atom);

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsBond(bond) || !molGraph->containsAtom(nbr_atom))
			continue;

		std::size_t bond_idx = molGraph->getBondIndex(bond);

		if (defOrderMask.test(bond_idx))
			continue;

		std::size_t nbr_atom_idx = molGraph->getAtomIndex(nbr_atom);

		defOrderMask.set(bond_idx);
		orders[bond_idx] = 1;

		if (nbr_atom_idx < atom_idx)
			freeAtomValences[nbr_atom_idx]--;
	}
}

void Chem::BondOrderGenerator::postprocessGeometry(const Atom& atom, Util::STArray& orders)
{
	std::size_t atom_idx = molGraph->getAtomIndex(atom);
	Geometry& geom = atomGeometries[atom_idx];

	if (geom != LINEAR && geom != TRIG_PLANAR)
		return;

	unsigned int atom_type = getType(atom);

	bool maybe_arom_het_atom = (atom_type == AtomType::N || atom_type == AtomType::O ||
								atom_type == AtomType::S || atom_type == AtomType::Se) && getRingFlag(atom);

	std::size_t free_val = freeAtomValences[atom_idx];

	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsBond(bond) || !molGraph->containsAtom(nbr_atom))
			continue;

		std::size_t bond_idx = molGraph->getBondIndex(bond);
		std::size_t nbr_atom_idx = molGraph->getAtomIndex(nbr_atom);

		switch (atomGeometries[nbr_atom_idx]) {

			case TERMINAL:
			case LINEAR:
			case TRIG_PLANAR:
				if (maybe_arom_het_atom)
					return;

				if (defOrderMask.test(bond_idx)) {
					if (orders[bond_idx] >= 2)
						return;

					continue;
				} 

				if (free_val >=2 && freeAtomValences[nbr_atom_idx] >= 2)
					return;

			default:
				continue;
		}
	}

	geom = (geom == TRIG_PLANAR ? TETRAHEDRAL : TRIG_PLANAR);
}

void Chem::BondOrderGenerator::fixRingAtomGeometries(const Fragment& ring)
{
	std::size_t rsize = ring.getNumAtoms();

	if (rsize != 5 && rsize != 6)
		return;

	double avg_tor_angle = calcAvgTorsionAngle(ring);

	if ((rsize == 5 && avg_tor_angle < 7.5) || (rsize == 6 && avg_tor_angle < 12.0)) {
		for (Fragment::ConstAtomIterator it = ring.getAtomsBegin(), end = ring.getAtomsEnd(); it != end; ++it) {
			const Atom& atom = *it;

			if (getExplicitBondCount(atom, *molGraph) == 2)
				atomGeometries[molGraph->getAtomIndex(atom)] = TRIG_PLANAR;
		}
	} 
}

Chem::BondOrderGenerator::Geometry Chem::BondOrderGenerator::perceiveInitialGeometry(const Atom& atom)
{
	getNeighborAtoms(atom, nbrAtomList1, 0);

	switch (nbrAtomList1.size()) {

		case 1:
			return TERMINAL;

		case 2: {
			double avg_angle = calcAvgBondAngle(atom, nbrAtomList1);			

			if (avg_angle > 155.0)
				return LINEAR;

			if (avg_angle > 115.0)
				return TRIG_PLANAR;

			return TETRAHEDRAL;
		}

		case 3: {
			double avg_angle = calcAvgBondAngle(atom, nbrAtomList1);			

			if (avg_angle > 115.0)
				return TRIG_PLANAR;

			return TETRAHEDRAL;
		}

		case 4: {
			double avg_angle = calcAvgBondAngle(atom, nbrAtomList1);			

			if (avg_angle <= 115.0)
				return TETRAHEDRAL;
		}
		
		default:
			return UNDEF;
	}
}

void Chem::BondOrderGenerator::getNeighborAtoms(const Atom& atom, AtomList& atom_list, const Atom* exclude_atom) const
{
	atom_list.clear();

	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsBond(bond) || !molGraph->containsAtom(nbr_atom))
			continue;

		if (exclude_atom != 0 && &nbr_atom == exclude_atom)
			continue;

		atom_list.push_back(&nbr_atom);
	}
}

std::size_t Chem::BondOrderGenerator::countBondsWithOrder(const Atom& atom, std::size_t order, const UIntTable& order_table) const 
{
	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	std::size_t count = 0;

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Bond& bond = *b_it;
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsBond(bond) || !molGraph->containsAtom(nbr_atom))
			continue;

		std::size_t bond_idx = molGraph->getBondIndex(bond);

		if (!defOrderMask.test(bond_idx))
			continue;

		if (order_table[bond_idx] == order)
			count++;
	}

	return count;
}

template <typename Pred>
void Chem::BondOrderGenerator::getUndefBondFragment(const Atom& atom, bool add_atoms, const Pred& bond_pred)
{
	if (add_atoms)
		fragAtomList.push_back(&atom);

	Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
	Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

	for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
		const Atom& nbr_atom = *a_it;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		const Bond& bond = *b_it;

		if (!molGraph->containsBond(bond))
			continue;

		std::size_t bond_idx = molGraph->getBondIndex(bond);

		if (defOrderMask.test(bond_idx))
			continue;

		if (!bond_pred(bond))
			continue;

		defOrderMask.set(bond_idx);

		fragBondList.push_back(&bond);

		getUndefBondFragment(nbr_atom, add_atoms, bond_pred);
	}
}

double Chem::BondOrderGenerator::calcAvgBondAngle(const Atom& atom, const AtomList& nbr_atoms) const
{
	Math::Vector3D nbr_atom1_vec, nbr_atom2_vec;
	double angle_sum = 0.0;
	std::size_t count = 0;

	const Math::Vector3D& atom_pos = get3DCoordinates(atom);

	for (AtomList::const_iterator it1 = nbr_atoms.begin(), end = nbr_atoms.end(); it1 != end; ) {
		const Math::Vector3D& nbr_atom1_pos = get3DCoordinates(*(*it1));

		nbr_atom1_vec = nbr_atom1_pos;
		nbr_atom1_vec -= atom_pos;
		
		double nbr_atom1_vec_len = length(nbr_atom1_vec);

		for (AtomList::const_iterator it2 = ++it1; it2 != end; ++it2) {
			const Math::Vector3D& nbr_atom2_pos = get3DCoordinates(*(*it2));

			nbr_atom2_vec = nbr_atom2_pos;
			nbr_atom2_vec -= atom_pos;

			angle_sum += std::acos(innerProd(nbr_atom1_vec, nbr_atom2_vec) / (nbr_atom1_vec_len * length(nbr_atom2_vec)));
			count++;
		}
	}

	return (angle_sum * 180.0 / (M_PI * count));
}

double Chem::BondOrderGenerator::calcDihedralAngle(const Atom& atom1, const Atom& atom2, const Atom& atom3, const Atom& atom4) const
{
	const Math::Vector3D& atom1_pos = get3DCoordinates(atom1);
	const Math::Vector3D& atom2_pos = get3DCoordinates(atom2);
	const Math::Vector3D& atom3_pos = get3DCoordinates(atom3);
	const Math::Vector3D& atom4_pos = get3DCoordinates(atom4);

	return calcDihedralAngle(atom1_pos, atom2_pos, atom3_pos, atom4_pos); 
}

double Chem::BondOrderGenerator::calcDihedralAngle(const Math::Vector3D& atom1_pos, const Math::Vector3D& atom2_pos, 
												   const Math::Vector3D& atom3_pos, const Math::Vector3D& atom4_pos) const
{
	Math::Vector3D vec_21(atom2_pos);
	
	vec_21 -= atom1_pos;

	Math::Vector3D vec_32(atom3_pos);

	vec_32 -= atom2_pos;

	Math::Vector3D vec_43(atom4_pos);

	vec_43 -= atom3_pos;

	Math::Vector3D pl_vec1 = crossProd(vec_21, vec_32);
	Math::Vector3D pl_vec2 = crossProd(vec_32, vec_43);

	return std::acos(innerProd(pl_vec1, pl_vec2) / (length(pl_vec1) * length(pl_vec2)));
}

double Chem::BondOrderGenerator::calcAvgTorsionAngle(const Fragment& ring) const
{
	double angle_sum = 0.0;
	std::size_t rsize = ring.getNumAtoms();

	for (std::size_t i = 0; i < rsize; i++)
		angle_sum += calcDihedralAngle(ring.getAtom(i), ring.getAtom((i + 1) % rsize), 
									   ring.getAtom((i + 2) % rsize), ring.getAtom((i + 3) % rsize));
	
	return (angle_sum * 180.0 / (rsize * M_PI));
}

bool Chem::BondOrderGenerator::isConjRingBond(const Bond& bond) const
{
	return conjRingBondMask.test(molGraph->getBondIndex(bond));
}
