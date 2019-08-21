/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGeneratorImpl.cpp 
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
#include <cmath>

#include <boost/bind.hpp>

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/ForceField/InteractionType.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/Math/Quaternion.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "SystematicConformerGeneratorImpl.hpp"
#include "TorsionLibraryDataReader.hpp"


using namespace CDPL;


namespace
{

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionData2(const InteractionData& src_ia_data, InteractionData& frag_ia_data, InteractionData& non_frag_ia_data, 
											   const Chem::MolecularGraph& src_molgraph, const Chem::MolecularGraph& frag)
	{
		for (typename InteractionData::ConstElementIterator it = src_ia_data.getElementsBegin(), end = src_ia_data.getElementsEnd(); it != end; ++it) {
			const typename InteractionData::ElementType& params = *it;

			if (frag.containsAtom(src_molgraph.getAtom(params.getAtom1Index())) && 
				frag.containsAtom(src_molgraph.getAtom(params.getAtom2Index())))

				frag_ia_data.addElement(params);
			else
				non_frag_ia_data.addElement(params);
		}
	}

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionData3(const InteractionData& src_ia_data, InteractionData& frag_ia_data, InteractionData& non_frag_ia_data, 
											   const Chem::MolecularGraph& src_molgraph, const Chem::MolecularGraph& frag)
	{
		for (typename InteractionData::ConstElementIterator it = src_ia_data.getElementsBegin(), end = src_ia_data.getElementsEnd(); it != end; ++it) {
			const typename InteractionData::ElementType& params = *it;

			if (frag.containsAtom(src_molgraph.getAtom(params.getAtom1Index())) &&
				frag.containsAtom(src_molgraph.getAtom(params.getAtom2Index())) && 
				frag.containsAtom(src_molgraph.getAtom(params.getAtom3Index())))

				frag_ia_data.addElement(params);
			else
				non_frag_ia_data.addElement(params);
		}
	}

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionData4(const InteractionData& src_ia_data, InteractionData& frag_ia_data, InteractionData& non_frag_ia_data, 
											   const Chem::MolecularGraph& src_molgraph, const Chem::MolecularGraph& frag)
	{
		for (typename InteractionData::ConstElementIterator it = src_ia_data.getElementsBegin(), end = src_ia_data.getElementsEnd(); it != end; ++it) {
			const typename InteractionData::ElementType& params = *it;

			if (frag.containsAtom(src_molgraph.getAtom(params.getAtom1Index())) &&
				frag.containsAtom(src_molgraph.getAtom(params.getAtom2Index())) && 
				frag.containsAtom(src_molgraph.getAtom(params.getAtom3Index())) &&
				frag.containsAtom(src_molgraph.getAtom(params.getAtom4Index())))

				frag_ia_data.addElement(params);
			else
				non_frag_ia_data.addElement(params);
		}
	}

	class UniqueValueCountPred : public std::unary_function<std::size_t, bool>
	{

	public:
		UniqueValueCountPred(): first(true) {}

		bool operator()(std::size_t value) {
			if (first || value != currValue) {
				currValue = value;
				first = false;
				return true;
			}

			return false;
		}
		 
	private:
		bool        first;
		std::size_t currValue;
	};

	const double MAX_PLANAR_ATOM_GEOM_OOP_ANGLE  = 10.0 / 180.0 * M_PI;
	const double MIN_LINEAR_ATOM_GEOM_BOND_ANGLE = 170.0 / 180.0 * M_PI;

	const char* GENERIC_TORSION_RULES = 
		"<library name=\"GenericRules\">"
		" <category name=\"GG\" atomType1=\"*\" atomType2=\"*\">"
		"  <rule pattern=\"[*:1][CH2:2]-[a:3][a:4]\">"
        "   <torsions>"
        "     <angle value=\"0\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"180\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"90\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-90\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"45\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-45\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"135\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-135\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		"  <rule pattern=\"[*:1]~[C^3H0:2]-[C^3H0,C^3H1:3]~[*:4]\">"
        "   <torsions>"
        "     <angle value=\"30\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-30\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"150\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-150\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"0\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"180\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"90\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-90\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"120\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-120\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		"  <rule pattern=\"[*,#1:1]~[^3X4:2]-[^3X4H3:3]-[#1:4]\">"
        "   <torsions>"
        "     <angle value=\"60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		"  <rule pattern=\"[*,#1:1]~[^3X4:2]-[^3X2H1:3]-[#1:4]\">"
        "   <torsions>"
        "     <angle value=\"180\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		"  <rule pattern=\"[*,#1:1]~[*:2]-[X2:3]#[X1,X2&H1:4]\">"
        "   <torsions>"
        "     <angle value=\"0\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		"  <rule pattern=\"[*:1]~[^3H2:2]-[^3H2:3]~[*:4]\">"
        "   <torsions>"
        "     <angle value=\"180\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		"  <rule pattern=\"[*,#1:1]~[^3:2]-[^3:3]~[*,#1:4]\">"
        "   <torsions>"
        "     <angle value=\"40\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-40\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
		"     <angle value=\"60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
		"     <angle value=\"80\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-80\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-160\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"160\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"180\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		"  <rule pattern=\"[*,#1:1]~[*:2]-[*:3]~[*,#1:4]\">"
        "   <torsions>"
        "     <angle value=\"0\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
		"     <angle value=\"30\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-30\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
		"     <angle value=\"60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-60\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
		"     <angle value=\"90\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-90\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"120\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-120\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"   
        "     <angle value=\"150\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"-150\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "     <angle value=\"180\" tolerance1=\"0\" tolerance2=\"0\" score=\"0\"/>"
        "   </torsions>"
        "  </rule>"
		" </category>"
		"</library>";

	ConfGen::TorsionLibrary::SharedPointer genericTorLib(new ConfGen::TorsionLibrary());

	struct Init
    {

		Init() {
			ConfGen::TorsionLibraryDataReader().read(GENERIC_TORSION_RULES, *genericTorLib);
		}

    } init;
}


ConfGen::SystematicConformerGeneratorImpl::SystematicConformerGeneratorImpl()
{
	fragConfGen.reuseExistingCoordinates(false);

	torsionRuleMatcher.reportUniqueMappingsOnly(true);
	torsionRuleMatcher.stopAtFirstMatchingRule(true);
}

ConfGen::SystematicConformerGeneratorImpl::~SystematicConformerGeneratorImpl() {}

void ConfGen::SystematicConformerGeneratorImpl::applySettings(const Settings& settings)
{
	this->settings = settings;
}

const ConfGen::SystematicConformerGeneratorImpl::Settings& 
ConfGen::SystematicConformerGeneratorImpl::getSettings() const
{
	return settings;
}

ConfGen::SystematicConformerGeneratorImpl::Status 
ConfGen::SystematicConformerGeneratorImpl::generate(const Chem::MolecularGraph& molgraph)
{
	init();
	buildTree(molgraph);
	buildAtomIndexMaps(fragTree);
	genConfSearchMMFF94InteractionData();
	distFragmentMMFF94InteractionData(fragTree);
	clearNodeConformers(fragTree);

	if (timeoutExceeded())
		return Status::TIMEOUT_EXCEEDED;
	
	if (!setupBuildFragmentConformers()) {
		if (timeoutExceeded())
			return Status::TIMEOUT_EXCEEDED;

		return Status::ERROR;
	}

	calcLeafNodeConformerEnergies(fragTree);
	genTerminalAtomMask(molgraph);
	setupTorsions(fragTree);

	return Status::SUCCESS;
}

void ConfGen::SystematicConformerGeneratorImpl::init()
{
	timer.start();	
	extAtomConnectivities.clear();
	freeCoordArrays.clear();

	std::for_each(allocCoordArrays.begin(), allocCoordArrays.end(), 
				  boost::bind(&SystematicConformerGeneratorImpl::freeVector3DArray, this, 
							  boost::bind<Math::Vector3DArray*>(&Math::Vector3DArray::SharedPointer::get, _1)));
}

void ConfGen::SystematicConformerGeneratorImpl::buildTree(const Chem::MolecularGraph& molgraph)
{
	buildFragNodes.clear();

	getFragmentLinkBonds(molgraph);

	fragTree.splitRecursive(molgraph, bondList); // build tree according to build fragment link bonds

	getBuildFragmentNodes(fragTree);

	genChainBuildFragmentSubtrees();

/*
	std::cerr << "digraph FragmentTree" << std::endl;
	std::cerr << '{' << std::endl;

	fragTree.printTree(std::cerr);

	std::cerr << '}' << std::endl;
*/
}

void ConfGen::SystematicConformerGeneratorImpl::buildAtomIndexMaps(FragmentTreeNode& node) const
{
	FragmentTreeNode::AtomIndexMap& idx_map = node.getAtomIndexMap();
	
	idx_map.clear();

	std::transform(node.getFragment().getAtomsBegin(), node.getFragment().getAtomsEnd(), std::back_inserter(idx_map),
				   boost::bind(&Chem::MolecularGraph::getAtomIndex, &fragTree.getFragment(), _1));

	if (!node.hasChildren())
		return;

	buildAtomIndexMaps(*node.getLeftChild());
	buildAtomIndexMaps(*node.getRightChild());
}

void ConfGen::SystematicConformerGeneratorImpl::genConfSearchMMFF94InteractionData()
{
	genMMFF94InteractionData(fragTree.getFragment(), settings.getSearchForceFieldType(), fragTree.getMMFF94InteractionData());
}

void ConfGen::SystematicConformerGeneratorImpl::clearNodeConformers(FragmentTreeNode& node) const
{
	node.getConformers().clear();

	if (!node.hasChildren())
		return;

	clearNodeConformers(*node.getLeftChild());
	clearNodeConformers(*node.getRightChild());
}

bool ConfGen::SystematicConformerGeneratorImpl::setupBuildFragmentConformers()
{
	for (NodeList::const_iterator it = buildFragNodes.begin(), end = buildFragNodes.end(); it != end; ++it) {
		FragmentTreeNode* node = *it;

		if (settings.existingCoordinatesReused() && 
			(!settings.ringsEnumerated() || node->getFragmentType() != FragmentType::FLEXIBLE_RING_SYSTEM) && 
			setExistingCoordinates(*node))
			continue;
		
		fragLibEntry.create(node->getFragment());
		buildFragmentLibraryEntryAtomIndexMap(*node);

		if (setFragmentLibraryConformers(*node))
			continue;

		if (!genFragmentConformers(*node))
			return false;
	}

	return true;
}

void ConfGen::SystematicConformerGeneratorImpl::calcLeafNodeConformerEnergies(FragmentTreeNode& node)
{
	if (node.hasChildren()) {
		calcLeafNodeConformerEnergies(*node.getLeftChild());
		calcLeafNodeConformerEnergies(*node.getRightChild());
		return;
	}

	mmff94EnergyCalc.setup(node.getMMFF94InteractionData());

	for (FragmentTreeNode::ConformerIterator it = node.getConformers().begin(), end = node.getConformers().end(); it != end; ++it) 
		it->second = mmff94EnergyCalc(*it->first);

	if (node.getNumConformers() > 1)
		std::sort(node.getConformers().begin(), node.getConformers().end(), 
				  boost::bind(std::less<double>(),
							  boost::bind(&FragmentTreeNode::ConfData::second, _1),
							  boost::bind(&FragmentTreeNode::ConfData::second, _2)));
}

void ConfGen::SystematicConformerGeneratorImpl::genTerminalAtomMask(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	termAtomMask.resize(molgraph.getNumAtoms());
	termAtomMask.reset();

	std::size_t i = 0;

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it, i++)
		if (getExplicitBondCount(*it, molgraph) == 1)
			termAtomMask.set(i);
}

void ConfGen::SystematicConformerGeneratorImpl::setupTorsions(FragmentTreeNode& node)
{
	using namespace Chem;

	if (!node.hasChildren())
		return;

	setupTorsions(*node.getLeftChild());
	setupTorsions(*node.getRightChild());

	node.getTorsionAngles().clear();
	node.setTorsionReferenceAtoms(0, 0);
	node.setKeepAllConformersFlag(true);

	const Atom* const* bond_atoms = node.getSplitBondAtoms();
	const MolecularGraph& frag = node.getFragment();

	std::size_t bond_count1 = getExplicitBondCount(*bond_atoms[0], frag);

	if (bond_count1 < 2) // sanity_check
		return;

	std::size_t bond_count2 = getExplicitBondCount(*bond_atoms[1], frag);

	if (bond_count2 < 2) // sanity_check
		return;

	bool lin_atom_flag1 = (bond_count1 == 2 && hasLinearGeometry(*bond_atoms[0], *node.getLeftChild()));
	bool lin_atom_flag2 = (bond_count2 == 2 && hasLinearGeometry(*bond_atoms[1], *node.getRightChild()));

	const Bond& bond = *node.getSplitBond();
	std::size_t order = getOrder(bond);

	if (order == 1 && (!lin_atom_flag1 || !lin_atom_flag2)) {
		const TorsionRuleMatch* match = getMatchingTorsionRule(bond);

		if (match) {
			for (TorsionRule::ConstAngleEntryIterator it = match->getRule().getAnglesBegin(), end = match->getRule().getAnglesEnd(); it != end; ++it) {
				double tor_ang = it->getAngle();

				// normalize angle to range [0, 360)

				if (tor_ang < 0.0)
					tor_ang = std::fmod(tor_ang, 360.0) + 360.0;
				else 
					tor_ang = std::fmod(tor_ang, 360.0);

				node.getTorsionAngles().push_back(tor_ang);
			}

			if (!node.getTorsionAngles().empty() && !lin_atom_flag1 && !lin_atom_flag2) {
				const Atom* const* match_atoms = match->getAtoms();
				
				if (match_atoms[1] == bond_atoms[0])
					node.setTorsionReferenceAtoms(match_atoms[0], match_atoms[3]);
				else
					node.setTorsionReferenceAtoms(match_atoms[3], match_atoms[0]);
			}
		}

	} else if (order == 2 && bond_count1 <= 3 && bond_count2 <= 3 && !lin_atom_flag1 && !lin_atom_flag2) {
		const StereoDescriptor& descr = getStereoDescriptor(bond);

		if ((descr.getConfiguration() == BondConfiguration::CIS || descr.getConfiguration() == BondConfiguration::TRANS) && descr.isValid(bond)) {
			const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();
			bool descr_valid = true;
	
			for (std::size_t i = 0; i < 4; i++) {
				if (!frag.containsAtom(*ref_atoms[i])) {
					descr_valid = false;
					break;
				}
			}

			if (descr_valid) {
				if (ref_atoms[1] == bond_atoms[0])
					node.setTorsionReferenceAtoms(ref_atoms[0], ref_atoms[3]);
				else
					node.setTorsionReferenceAtoms(ref_atoms[3], ref_atoms[0]);

				// choose angle that results in desired configuration

				node.getTorsionAngles().push_back(descr.getConfiguration() == BondConfiguration::CIS ? 0.0 : 180.0);
				return;
			}
		}
		
		// choose trans configuration of bulkiest substituents
	
		node.setTorsionReferenceAtoms(getBulkiestSubstituent(*bond_atoms[0], *bond_atoms[1], frag, false),
									  getBulkiestSubstituent(*bond_atoms[1], *bond_atoms[0], frag, false));
		node.getTorsionAngles().push_back(180.0);
		return;
	}

	std::size_t rot_sym_order = std::max(lin_atom_flag1 ? std::size_t(1) : getRotationalSymmetryOrder(*bond_atoms[0], bond, node),
										 lin_atom_flag2 ? std::size_t(1) : getRotationalSymmetryOrder(*bond_atoms[1], bond, node));

	if (node.getTorsionAngles().empty()) {
		// fallback: rotation in 30° steps

		for (std::size_t i = 0, num_angles = 12 / rot_sym_order; i < num_angles; i++)
			node.getTorsionAngles().push_back(i * 30.0);

		if (!lin_atom_flag1 && !lin_atom_flag2)
			node.setTorsionReferenceAtoms(getBulkiestSubstituent(*bond_atoms[0], *bond_atoms[1], frag, false),
										  getBulkiestSubstituent(*bond_atoms[1], *bond_atoms[0], frag, false));
		
	} else if (rot_sym_order > 1) {
		// reduce number of torsion angles due to rotational symmetry

		double ident_rot_ang = 360.0 / rot_sym_order; 

		for (FragmentTreeNode::TorsionAngleArray::iterator it = node.getTorsionAngles().begin(), end = node.getTorsionAngles().end(); it != end; ++it) {
			double& tor_ang = *it;

			tor_ang = std::fmod(tor_ang, ident_rot_ang);
		}

		std::sort(node.getTorsionAngles().begin(), node.getTorsionAngles().end());
		
		node.getTorsionAngles().erase(std::unique(node.getTorsionAngles().begin(), node.getTorsionAngles().end()), node.getTorsionAngles().end());
	}

	bool is_h_rotor = (getHeavyBondCount(*bond_atoms[0], frag) == 1 || getHeavyBondCount(*bond_atoms[1], frag) == 1);

	if (is_h_rotor && (!settings.hydrogenRotorsEnabled() || !isHeteroAtomHydrogenRotor(bond, frag)))
		node.setKeepAllConformersFlag(false);
}

const ConfGen::TorsionRuleMatch* ConfGen::SystematicConformerGeneratorImpl::getMatchingTorsionRule(const Chem::Bond& bond)
{
	torsionRuleMatcher.setTorsionLibrary(settings.getTorsionLibrary());

	if (torsionRuleMatcher.findMatches(bond, fragTree.getFragment(), false)) 
		return &torsionRuleMatcher.getMatch(0); 

	torsionRuleMatcher.setTorsionLibrary(genericTorLib);

	if (torsionRuleMatcher.findMatches(bond, fragTree.getFragment(), false)) 
		return &torsionRuleMatcher.getMatch(0); 

	return 0;
}

void ConfGen::SystematicConformerGeneratorImpl::getBuildFragmentNodes(FragmentTreeNode& node)
{
	if (!node.hasChildren()) {
		buildFragNodes.push_back(&node);
		return;
	}

	getBuildFragmentNodes(*node.getLeftChild());
	getBuildFragmentNodes(*node.getRightChild());
}

void ConfGen::SystematicConformerGeneratorImpl::genChainBuildFragmentSubtrees()
{
	using namespace Chem;

	for (NodeList::const_iterator it = buildFragNodes.begin(), end = buildFragNodes.end(); it != end; ++it) {
		FragmentTreeNode* node = *it;
		const MolecularGraph& frag = node->getFragment();
		unsigned int frag_type = perceiveFragmentType(frag);

		node->setFragmentType(frag_type);

		if (frag_type != FragmentType::CHAIN)
			continue;

		getRotatableBonds(frag);

		if (!bondList.empty())
			node->splitRecursive(frag, bondList);
	}
}

bool ConfGen::SystematicConformerGeneratorImpl::setExistingCoordinates(FragmentTreeNode& node)
{
	using namespace Chem;

	try {
		Math::Vector3DArray* coords = allocVector3DArray();
		Vec3DArrayDeallocator dealloc_guard(this, coords);

		const MolecularGraph& frag = node.getFragment();
		const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();

		for (std::size_t i = 0, num_atoms = frag.getNumAtoms(); i < num_atoms; i++) {
			const Atom& atom = frag.getAtom(i);

			(*coords)[atom_idx_map[i]] = get3DCoordinates(atom);
		}

		if (node.getFragmentType() == FragmentType::CHAIN && node.hasChildren())
			distChainBuildFragmentCoordinates(node, *coords, false, false);

		else {
			node.addConformer(coords);
			dealloc_guard.release();

			enumNitrogens(node, node.getFragmentType() != FragmentType::CHAIN);
		}

		return true;

	} catch (const Base::ItemNotFound& e) {}

	return false;
}

bool ConfGen::SystematicConformerGeneratorImpl::setFragmentLibraryConformers(FragmentTreeNode& node)
{
	using namespace Chem;

	if (!settings.getFragmentLibrary())
		return false;

	const MolecularGraph::SharedPointer& entry_ptr = settings.getFragmentLibrary()->getEntry(fragLibEntry.getHashCode());

	if (!entry_ptr)
		return false;

	if (entry_ptr->getNumAtoms() != fragLibEntry.getNumAtoms())  // sanity check
		return false;

	std::size_t num_confs = getNumConformations(*entry_ptr);

	if (num_confs == 0)
		return false;

	switch (node.getFragmentType()) {

		case FragmentType::CHAIN: {
			Math::Vector3DArray* coords = allocVector3DArray();
			Vec3DArrayDeallocator dealloc_guard(this, coords);

			getLibraryFragmentConformation(*entry_ptr, 0, *coords);

			if (node.hasChildren())
				distChainBuildFragmentCoordinates(node, *coords, true, false);

			else {
				node.addConformer(coords);
				dealloc_guard.release();

				fixAtomConfigurations(node);
				fixBondConfigurations(node, false);
				enumNitrogens(node, false);
			}

			return true;
		}

		case FragmentType::RIGID_RING_SYSTEM:
		case FragmentType::FLEXIBLE_RING_SYSTEM: {
			setupAromRingSubstituentBondLengthList(node);

			for (std::size_t  i = 0; i < num_confs; i++) {
				Math::Vector3DArray* coords = allocVector3DArray();
				Vec3DArrayDeallocator dealloc_guard(this, coords);

				getLibraryFragmentConformation(*entry_ptr, i, *coords);
				fixAromRingSubstituentBondLengths(*coords);

				node.addConformer(coords);
				dealloc_guard.release();
			}

			enumNitrogens(node, true);
			return true;
		}
	}

	return false;
}

bool ConfGen::SystematicConformerGeneratorImpl::genFragmentConformers(FragmentTreeNode& node)
{
	std::size_t frag_build_to = settings.getMaxFragmentBuildTime();

	if (settings.getTimeout() > 0) {
		std::size_t elapsed_time = timer.elapsed().wall / 1000000;

		if (elapsed_time >= settings.getTimeout())
			return false;

		if (frag_build_to > 0)
			frag_build_to = std::min(frag_build_to, settings.getTimeout() - elapsed_time);
		else
			frag_build_to = settings.getTimeout() - elapsed_time;
	}

	fragConfGen.setTimeout(frag_build_to);

	if (!fragSSSR)
		fragSSSR.reset(new Chem::SmallestSetOfSmallestRings());

	fragSSSR->perceive(fragLibEntry);
	setSSSR(fragLibEntry, fragSSSR);

	genMMFF94InteractionData(fragLibEntry, settings.getBuildForceFieldType(), fragBuildMMFF94Data);

	fragConfGen.generate(fragLibEntry, fragBuildMMFF94Data, node.getFragmentType());

	std::size_t num_confs = fragConfGen.getNumConformers();

	if (num_confs == 0) 
		return false;

	if (node.getFragmentType() == FragmentType::CHAIN) {
		Math::Vector3DArray* coords = allocVector3DArray();
		Vec3DArrayDeallocator dealloc_guard(this, coords);
		const Math::Vector3DArray& gen_coords = fragConfGen.getCoordinates(0);

		for (IndexPairList::const_iterator it = fragLibEntryAtomIdxMap.begin(), end = fragLibEntryAtomIdxMap.end(); it != end; ++it) {
			const IndexPair& idx_mapping = *it;

			(*coords)[idx_mapping.second].assign(gen_coords[idx_mapping.first]);
		}

		if (node.hasChildren())
			distChainBuildFragmentCoordinates(node, *coords, false, true);

		else {
			node.addConformer(coords);
			dealloc_guard.release();

			fixBondConfigurations(node, true);
			enumNitrogens(node, false);
		}

		return true;
	}

	setupAromRingSubstituentBondLengthList(node);

	for (std::size_t i = 0; i < num_confs; i++) {
		Math::Vector3DArray* coords = allocVector3DArray();
		Vec3DArrayDeallocator dealloc_guard(this, coords);
		const Math::Vector3DArray& gen_coords = fragConfGen.getCoordinates(i);

		for (IndexPairList::const_iterator it = fragLibEntryAtomIdxMap.begin(), end = fragLibEntryAtomIdxMap.end(); it != end; ++it) {
			const IndexPair& idx_mapping = *it;

			(*coords)[idx_mapping.second].assign(gen_coords[idx_mapping.first]);
		}

		fixAromRingSubstituentBondLengths(*coords);

		node.addConformer(coords);
		dealloc_guard.release();
	}

	enumNitrogens(node, true);
	return true;
}

void ConfGen::SystematicConformerGeneratorImpl::buildFragmentLibraryEntryAtomIndexMap(const FragmentTreeNode& node)
{
	using namespace Chem;

	const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();
	const FragmentLibraryEntry::AtomMapping& entry_atom_map = fragLibEntry.getAtomMapping();

	fragLibEntryAtomIdxMap.clear();

	for (std::size_t i = 0, num_atoms = node.getFragment().getNumAtoms(); i < num_atoms; i++)
		fragLibEntryAtomIdxMap.push_back(IndexPair(fragLibEntry.getAtomIndex(*entry_atom_map[i]), atom_idx_map[i]));
}

void ConfGen::SystematicConformerGeneratorImpl::distChainBuildFragmentCoordinates(FragmentTreeNode& node, const Math::Vector3DArray& coords, 
																				  bool fix_configs, bool opt_db_configs)
{
	if (node.hasChildren()) {
		distChainBuildFragmentCoordinates(*node.getLeftChild(), coords, fix_configs, opt_db_configs);
		distChainBuildFragmentCoordinates(*node.getRightChild(), coords, fix_configs, opt_db_configs);
		return;
	}

	const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();

	Math::Vector3DArray* node_coords = allocVector3DArray();
	Vec3DArrayDeallocator dealloc_guard(this, node_coords);

	for (AtomIndexMap::const_iterator idx_it = atom_idx_map.begin(), idx_end = atom_idx_map.end(); idx_it != idx_end; ++idx_it) {
		std::size_t atom_idx = *idx_it;

		(*node_coords)[atom_idx] = coords[atom_idx];
	}
		
	node.addConformer(node_coords);
	dealloc_guard.release();

	if (fix_configs) {
		fixAtomConfigurations(node);
		fixBondConfigurations(node, false);

	} else if (opt_db_configs)
		fixBondConfigurations(node, true);

	enumNitrogens(node, false);
}

void ConfGen::SystematicConformerGeneratorImpl::getLibraryFragmentConformation(const Chem::MolecularGraph& lib_frag, 
																			   std::size_t conf_idx, Math::Vector3DArray& coords) const
{
	for (IndexPairList::const_iterator it = fragLibEntryAtomIdxMap.begin(), end = fragLibEntryAtomIdxMap.end(); it != end; ++it) {
		const IndexPair& idx_mapping = *it;

		coords[idx_mapping.second].assign((*get3DCoordinatesArray(lib_frag.getAtom(idx_mapping.first)))[conf_idx]);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::setupAromRingSubstituentBondLengthList(FragmentTreeNode& node)
{
	using namespace Chem;
	using namespace ForceField;

	const MolecularGraph& frag = node.getFragment();
	const MolecularGraph& root_frag = fragTree.getFragment();
	const MMFF94BondStretchingInteractionData& bs_params = node.getMMFF94InteractionData().getBondStretchingInteractions();

	aromRingSubstBondLens.clear();

	for (MolecularGraph::ConstBondIterator it = frag.getBondsBegin(), end = frag.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (getRingFlag(bond))
			continue;

		const Atom* atom1 = &bond.getBegin();
		const Atom* atom2 = &bond.getEnd();

		if (getAromaticityFlag(*atom2) && getType(*atom1) != AtomType::H && getAromaticBondCount(*atom2, frag) == 2 && getExplicitBondCount(*atom1, frag) == 1) {
			std::swap(atom1, atom2);

		} else if (!(getAromaticityFlag(*atom1) && getType(*atom2) != AtomType::H && getAromaticBondCount(*atom1, frag) == 2 && getExplicitBondCount(*atom2, frag) == 1))
			continue;

		std::size_t atom1_idx = root_frag.getAtomIndex(*atom1);
		std::size_t atom2_idx = root_frag.getAtomIndex(*atom2);

		for (MMFF94BondStretchingInteractionData::ConstElementIterator bs_ia_it = bs_params.getElementsBegin(), 
				 bs_ia_end = bs_params.getElementsEnd(); bs_ia_it != bs_ia_end; ++bs_ia_it) {

			const MMFF94BondStretchingInteraction& bs_ia = *bs_ia_it;

			if ((bs_ia.getAtom1Index() == atom1_idx && bs_ia.getAtom2Index() == atom2_idx) ||
				(bs_ia.getAtom1Index() == atom2_idx && bs_ia.getAtom2Index() == atom1_idx)) {

				aromRingSubstBondLens.push_back(boost::make_tuple(atom1_idx, atom2_idx, bs_ia.getReferenceLength()));
				break;
			}
		}
	}
}

void ConfGen::SystematicConformerGeneratorImpl::fixAromRingSubstituentBondLengths(Math::Vector3DArray& coords) const
{
	if (aromRingSubstBondLens.empty())
		return;

	for (BondLengthDescriptorList::const_iterator it = aromRingSubstBondLens.begin(), end = aromRingSubstBondLens.end(); it != end; ++it) {
		const BondLengthDescriptor& descr = *it;

		std::size_t atom1_idx = descr.get<0>();
		std::size_t atom2_idx = descr.get<1>();

		coords[atom2_idx].minusAssign(coords[atom1_idx]);
		coords[atom2_idx] *= descr.get<2>() / length(coords[atom2_idx]);
		coords[atom2_idx].plusAssign(coords[atom1_idx]);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::fixAtomConfigurations(FragmentTreeNode& node) const
{
	using namespace Chem;

	if (node.getNumConformers() == 0) // should not happen
		return;

	const MolecularGraph& frag = node.getFragment();

	for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (!isStereoCenter(atom, frag, false))
			continue;

		const StereoDescriptor& descr = getStereoDescriptor(atom);

		if (descr.getConfiguration() != AtomConfiguration::R && descr.getConfiguration() != AtomConfiguration::S)
			return;

		if (!descr.isValid(atom))
			return;

		std::size_t num_ref_atoms = descr.getNumReferenceAtoms();
		const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();

		for (std::size_t i = 0; i < num_ref_atoms; i++) 
			if (!frag.containsAtom(*ref_atoms[i])) 
				return;

		checkAndCorrectAtomConfiguration(node, atom, descr);
		return;
	}
}

void ConfGen::SystematicConformerGeneratorImpl::fixBondConfigurations(FragmentTreeNode& node, bool opt_only)
{
	using namespace Chem;

	if (node.getNumConformers() == 0) // should not happen
		return;

	const MolecularGraph& frag = node.getFragment();

	for (MolecularGraph::ConstBondIterator it = frag.getBondsBegin(), end = frag.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (!isStereoCenter(bond, frag, false, 0))
			continue;

		const StereoDescriptor& descr = getStereoDescriptor(bond);

		if ((descr.getConfiguration() == BondConfiguration::CIS || descr.getConfiguration() == BondConfiguration::TRANS) && descr.isValid(bond)) {
			const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();
			bool descr_valid = true;
	
			for (std::size_t i = 0; i < 4; i++) {
				if (!frag.containsAtom(*ref_atoms[i])) {
					descr_valid = false;
					break;
				}
			}

			if (descr_valid) {
				if (!opt_only)
					checkAndCorrectDoubleBondConfiguration(node, bond, descr);
				return;
			}
		} 

		// choose trans config of bulkiest substituents

		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();
	
		const Atom* subst1_atom = getBulkiestSubstituent(atom1, atom2, frag, true);

		if (!subst1_atom)
			return;

		const Atom* subst2_atom = getBulkiestSubstituent(atom2, atom1, frag, true);

		if (!subst2_atom)
			return;

		checkAndCorrectDoubleBondConfiguration(node, bond, StereoDescriptor(BondConfiguration::TRANS, 
																			*subst1_atom, atom1, atom2, *subst2_atom));
		return;
	}
}

void ConfGen::SystematicConformerGeneratorImpl::checkAndCorrectAtomConfiguration(FragmentTreeNode& node, const Chem::Atom& atom, 
																				 const Chem::StereoDescriptor& descr) const
{
	using namespace Chem;

	Math::Vector3DArray& coords = *node.getConformers().front().first;

	if (calcAtomConfiguration(atom, fragTree.getFragment(), descr, coords) == descr.getConfiguration())
		return;

	const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();

	// mirror fragment coordinates in xy-plane

	for (AtomIndexMap::const_iterator ai_it = atom_idx_map.begin(), ai_end = atom_idx_map.end(); ai_it != ai_end; ++ai_it)
		coords[*ai_it][2] *= -1.0;
}

void ConfGen::SystematicConformerGeneratorImpl::checkAndCorrectDoubleBondConfiguration(FragmentTreeNode& node, const Chem::Bond& bond, 
																					   const Chem::StereoDescriptor& descr)
{
	using namespace Chem;

	Math::Vector3DArray& coords = *node.getConformers().front().first;

	if (calcBondConfiguration(bond, fragTree.getFragment(), descr, coords) == descr.getConfiguration())
		return;

	// rotate substituents on ref. atom 2 180° around bond axis

	const MolecularGraph& frag = node.getFragment();
	const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();		
	const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();

	std::size_t bond_atom1_idx = frag.getAtomIndex(*ref_atoms[1]);
	std::size_t bond_atom2_idx = frag.getAtomIndex(*ref_atoms[2]);

	const Math::Vector3D& bond_atom1_pos = coords[atom_idx_map[bond_atom1_idx]];
	const Math::Vector3D& bond_atom2_pos = coords[atom_idx_map[bond_atom2_idx]];

	double dx = bond_atom2_pos[0] - bond_atom1_pos[0];
	double dy = bond_atom2_pos[1] - bond_atom1_pos[1];
	double dz = bond_atom2_pos[2] - bond_atom1_pos[2];
	double bond_len = std::sqrt(dx * dx + dy * dy + dz * dz);

	Math::DQuaternion rot_quat(0, dx / bond_len, dy / bond_len, dz / bond_len);

	reachableAtomMask.resize(frag.getNumAtoms());
	reachableAtomMask.reset();
	reachableAtomMask.set(bond_atom1_idx);
	reachableAtomMask.set(bond_atom2_idx);

	markReachableAtoms(*ref_atoms[2], frag, reachableAtomMask, false);

	reachableAtomMask.reset(bond_atom1_idx);
	reachableAtomMask.reset(bond_atom2_idx);

	for (Util::BitSet::size_type i = reachableAtomMask.find_first(); i != Util::BitSet::npos; i = reachableAtomMask.find_next(i)) {
		Math::Vector3D& atom_pos = coords[atom_idx_map[i]];

		atom_pos.minusAssign(bond_atom1_pos);
		atom_pos = rotate(rot_quat, atom_pos);
		atom_pos.plusAssign(bond_atom1_pos);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::enumNitrogens(FragmentTreeNode& node, bool ring_sys)
{
	using namespace Chem;

	if (!settings.nitrogensEnumerated())
		return;

	if (node.getNumConformers() == 0) // should not happen
		return;

	const MolecularGraph& frag = node.getFragment();
	const AtomIndexMap& atom_idx_map = node.getAtomIndexMap();
	Math::Vector3DArray& coords = *node.getConformers().front().first;

	if (!ring_sys) {
		for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it) {
			const Atom& atom = *it;

			if (!isInvertibleNitrogen(atom, frag, coords))
				continue;

			Math::Vector3DArray* inv_n_coords = allocVector3DArray();
			Vec3DArrayDeallocator dealloc_guard(this, inv_n_coords);

			// copy and mirror fragment coordinates in xy-plane

			for (AtomIndexMap::const_iterator ai_it = atom_idx_map.begin(), ai_end = atom_idx_map.end(); ai_it != ai_end; ++ai_it) {
				std::size_t atom_idx = *ai_it;
				Math::Vector3D::ConstPointer orig_atom_pos = coords[atom_idx].getData();
				Math::Vector3D::Pointer new_atom_pos = (*inv_n_coords)[atom_idx].getData();

				new_atom_pos[0] = orig_atom_pos[0];
				new_atom_pos[1] = orig_atom_pos[1];
				new_atom_pos[2] = -orig_atom_pos[2];
			}

			node.addConformer(inv_n_coords);
			dealloc_guard.release();
			return;
		}

		return;
	}

	std::size_t num_atoms = frag.getNumAtoms();

	for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;

		if (!isInvertibleNitrogen(atom, frag, coords))
			continue;

		const Atom* ring_nbr1 = 0;
		const Atom* ring_nbr2 = 0;
		const Atom* subst_nbr = 0;

		Atom::ConstBondIterator b_it = atom.getBondsBegin();

		for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
			const Atom& nbr_atom = *a_it;
			const Bond& bond = *b_it;

			if (!frag.containsAtom(nbr_atom) || !frag.containsBond(bond))
				continue;

			if (getRingFlag(bond)) {
				if (!ring_nbr1)
					ring_nbr1 = &nbr_atom;
				else
					ring_nbr2 = &nbr_atom;

			} else 
				subst_nbr = &nbr_atom;
		}

		if (!subst_nbr || !ring_nbr2) // should not happend
			continue;

		std::size_t ctr_atom_idx = frag.getAtomIndex(atom);
		std::size_t ring_nbr1_idx = frag.getAtomIndex(*ring_nbr1);
		std::size_t ring_nbr2_idx = frag.getAtomIndex(*ring_nbr2);
		std::size_t subst_nbr_idx = frag.getAtomIndex(*subst_nbr);

		reachableAtomMask.resize(num_atoms);
		reachableAtomMask.reset();
		reachableAtomMask.set(ctr_atom_idx);
		reachableAtomMask.set(subst_nbr_idx);

		markReachableAtoms(*subst_nbr, frag, reachableAtomMask, false);

		reachableAtomMask.reset(ctr_atom_idx);

		ctr_atom_idx = atom_idx_map[ctr_atom_idx];
		ring_nbr1_idx = atom_idx_map[ring_nbr1_idx];
		ring_nbr2_idx = atom_idx_map[ring_nbr2_idx];

		Math::Vector3D ring_nbr1_vec;
		Math::Vector3D ring_nbr2_vec;
		Math::Vector3D subst_atom_vec;
		Math::Vector3D plane_normal;

		for (std::size_t i = 0, num_confs = node.getNumConformers(); i < num_confs; i++) {
			const Math::Vector3DArray& conf = *node.getConformers()[i].first;
			Math::Vector3DArray* inv_n_conf = allocVector3DArray();
			Vec3DArrayDeallocator dealloc_guard(this, inv_n_conf);

			const Math::Vector3D& ctr_atom_pos = conf[ctr_atom_idx];

			ring_nbr1_vec.assign(conf[ring_nbr1_idx] - ctr_atom_pos);
			ring_nbr2_vec.assign(conf[ring_nbr2_idx] - ctr_atom_pos);
			plane_normal.assign(crossProd(ring_nbr1_vec, ring_nbr2_vec));

			double plane_normal_len = length(plane_normal);

			if (plane_normal_len == 0.0) // sanity check
				continue;

			plane_normal /= plane_normal_len;

			for (std::size_t j = 0; j < num_atoms; j++) {
				std::size_t curr_atom_idx = atom_idx_map[j];

				if (!reachableAtomMask.test(j)) {
					(*inv_n_conf)[curr_atom_idx].assign(conf[curr_atom_idx]);
					continue;
				}

				const Math::Vector3D& subst_atom_pos = conf[curr_atom_idx];

				subst_atom_vec.assign(subst_atom_pos - ctr_atom_pos);

				double plane_dist = innerProd(plane_normal, subst_atom_vec);
				Math::Vector3D& inv_n_subst_atom_pos = (*inv_n_conf)[curr_atom_idx];

				inv_n_subst_atom_pos[0] = subst_atom_pos[0] - 2.0 * plane_dist * plane_normal[0];
				inv_n_subst_atom_pos[1] = subst_atom_pos[1] - 2.0 * plane_dist * plane_normal[1];
				inv_n_subst_atom_pos[2] = subst_atom_pos[2] - 2.0 * plane_dist * plane_normal[2];
			}

			node.addConformer(inv_n_conf);
			dealloc_guard.release();
		}
	}
}

void ConfGen::SystematicConformerGeneratorImpl::getFragmentLinkBonds(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	bondList.clear();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (isFragmentLinkBond(bond, molgraph))
			bondList.push_back(&bond);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::getRotatableBonds(const Chem::MolecularGraph& frag)
{
	using namespace Chem;

	bondList.clear();	

	for (MolecularGraph::ConstBondIterator it = frag.getBondsBegin(), end = frag.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
	
		if (isRotatable(bond, frag, true, false, true)) 
			bondList.push_back(&bond);
	}
}

const Chem::Atom* ConfGen::SystematicConformerGeneratorImpl::getBulkiestSubstituent(const Chem::Atom& atom, const Chem::Atom& excl_atom, 
																					const Chem::MolecularGraph& frag, bool strict)
{
	using namespace Chem;

	calcExtendedAtomConnectivities();

	Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	const Atom* bkst_subst = 0;
	std::size_t bkst_subst_ec = 0;
	std::size_t bond_cnt = 0;

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (&nbr_atom == &excl_atom)
			continue;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(*b_it))
			continue;

		if (++bond_cnt > 2 && strict)
			return 0;

		std::size_t nbr_ec = extAtomConnectivities[fragTree.getFragment().getAtomIndex(nbr_atom)];

		if (!bkst_subst || nbr_ec > bkst_subst_ec) {
			bkst_subst = &nbr_atom;
			bkst_subst_ec = nbr_ec;

		} else if (strict && (bkst_subst_ec == nbr_ec))
			return 0;
	}

	return bkst_subst;
}

void ConfGen::SystematicConformerGeneratorImpl::calcExtendedAtomConnectivities()
{
	using namespace Chem;

	if (!extAtomConnectivities.empty())
		return;

	const MolecularGraph& root_frag = fragTree.getFragment();

	buildAtomTypeMask(root_frag, hAtomMask, AtomType::H, true);

	std::size_t num_atoms = root_frag.getNumAtoms();
	std::size_t last_num_classes = 0;

	extAtomConnectivities.assign(num_atoms, 1);

	while (true) {
		tmpExtAtomConnectivities.assign(num_atoms, 0);

		for (MolecularGraph::ConstBondIterator it = root_frag.getBondsBegin(), end = root_frag.getBondsEnd(); it != end; ++it) {
			const Bond& bond = *it;
			std::size_t atom1_idx = root_frag.getAtomIndex(bond.getBegin());

			if (hAtomMask.test(atom1_idx))
				continue;

			std::size_t atom2_idx = root_frag.getAtomIndex(bond.getEnd());
	
			if (hAtomMask.test(atom2_idx))
				continue;

			tmpExtAtomConnectivities[atom1_idx] += extAtomConnectivities[atom2_idx];
			tmpExtAtomConnectivities[atom2_idx] += extAtomConnectivities[atom1_idx];
		}

		extAtomConnectivities = tmpExtAtomConnectivities;

		std::sort(tmpExtAtomConnectivities.begin(), tmpExtAtomConnectivities.end());

		std::size_t num_classes = std::count_if(tmpExtAtomConnectivities.begin(), tmpExtAtomConnectivities.end(), UniqueValueCountPred());

		if (num_classes <= last_num_classes) 
			break;

		last_num_classes = num_classes;
	}
}

bool ConfGen::SystematicConformerGeneratorImpl::isInvertibleNitrogen(const Chem::Atom& atom, const Chem::MolecularGraph& frag, 
																	 const Math::Vector3DArray& coords) const
{
	using namespace Chem;

	if (getType(atom) != AtomType::N)
		return false;

	const StereoDescriptor& descr = getStereoDescriptor(atom);

	if (descr.isValid(atom) && (descr.getConfiguration() == AtomConfiguration::R || descr.getConfiguration() == AtomConfiguration::S))
		return false;

	std::size_t h_bond_count = 0;
	std::size_t ring_bond_count = 0;
	std::size_t nbr_atom_indices[3];
	std::size_t i = 0;

	const MolecularGraph& root_frag = fragTree.getFragment();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(bond))
			continue;

		if (i == 3)
			return false;

		if (getOrder(bond) != 1)
			return false;

		if (getRingFlag(bond) && (++ring_bond_count > 2))
			return false;

		if (getType(nbr_atom) == AtomType::H && (++h_bond_count > 1))
			return false;
	
		nbr_atom_indices[i++] = root_frag.getAtomIndex(nbr_atom);
	}

	if (i != 3)
		return false;

	double oop_angle = ForceField::calcOutOfPlaneAngle<double>(coords[nbr_atom_indices[0]], coords[root_frag.getAtomIndex(atom)],
															   coords[nbr_atom_indices[1]], coords[nbr_atom_indices[2]]);

	return (std::abs(oop_angle) > MAX_PLANAR_ATOM_GEOM_OOP_ANGLE);
}

bool ConfGen::SystematicConformerGeneratorImpl::hasLinearGeometry(const Chem::Atom& atom, const FragmentTreeNode& node) const
{
	using namespace Chem;

	const FragmentTreeNode* coords_node = getLeafNodeWithCoordinates(atom, node);

	if (!coords_node)
		return false;

	const MolecularGraph& frag = coords_node->getFragment();

	const Atom* nbr_atom1 = 0;
	const Atom* nbr_atom2 = 0;

	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(bond))
			continue;

		if (!nbr_atom1)
			nbr_atom1 = &nbr_atom;

		else {
			if (nbr_atom2)
				return false;

			nbr_atom2 = &nbr_atom;
		}
	}

	if (!nbr_atom2)
		return false;

	const MolecularGraph& root_frag = fragTree.getFragment();

	std::size_t ctr_atom_idx = root_frag.getAtomIndex(atom);
	std::size_t nbr_atom1_idx = root_frag.getAtomIndex(*nbr_atom1);
	std::size_t nbr_atom2_idx = root_frag.getAtomIndex(*nbr_atom2);

	const Math::Vector3DArray& coords = *coords_node->getConformers().front().first;

	double bond_angle = ForceField::calcBondAngle<double>(coords[nbr_atom1_idx], coords[ctr_atom_idx], coords[nbr_atom2_idx]);

	return (bond_angle >= MIN_LINEAR_ATOM_GEOM_BOND_ANGLE);
}

bool ConfGen::SystematicConformerGeneratorImpl::isPlanarNitrogen(const Chem::Atom& atom, const FragmentTreeNode& node) const
{
	using namespace Chem;

	if (getType(atom) != AtomType::N)
		return false;

	const FragmentTreeNode* coords_node = getLeafNodeWithCoordinates(atom, node);

	if (!coords_node)
		return false;

	const MolecularGraph& frag = coords_node->getFragment();

	std::size_t nbr_atom_indices[3];
	std::size_t i = 0;

	const MolecularGraph& root_frag = fragTree.getFragment();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(bond))
			continue;

		if (i == 3)
			return false;

		nbr_atom_indices[i++] = root_frag.getAtomIndex(nbr_atom);
	}

	if (i != 3)
		return false;

	const Math::Vector3DArray& coords = *coords_node->getConformers().front().first;

	double oop_angle = ForceField::calcOutOfPlaneAngle<double>(coords[nbr_atom_indices[0]], coords[root_frag.getAtomIndex(atom)],
															   coords[nbr_atom_indices[1]], coords[nbr_atom_indices[2]]);

	return (std::abs(oop_angle) <= MAX_PLANAR_ATOM_GEOM_OOP_ANGLE);
}

const ConfGen::FragmentTreeNode* ConfGen::SystematicConformerGeneratorImpl::getLeafNodeWithCoordinates(const Chem::Atom& atom, 
																									   const FragmentTreeNode& node) const
{
	if (!node.getFragment().containsAtom(atom))
		return 0;

	if (node.hasChildren()) {
		if (const FragmentTreeNode* found_node = getLeafNodeWithCoordinates(atom, *node.getLeftChild()))
			return found_node;

		return getLeafNodeWithCoordinates(atom, *node.getRightChild());
	}

	if (node.getConformers().empty())
		return 0;

	if (getExplicitBondCount(atom, node.getFragment()) <= 1)
		return 0;
		
	return &node;
}

std::size_t ConfGen::SystematicConformerGeneratorImpl::getRotationalSymmetryOrder(const Chem::Atom& atom, const Chem::Bond& bond,
																				  const FragmentTreeNode& node) const
{
	using namespace Chem;

	std::size_t nbr_cnt = 0;
	unsigned int nbr_atom_type = 0;
	bool first = true;

	const MolecularGraph& root_frag = fragTree.getFragment();
	const MolecularGraph& frag = node.getFragment();
	Atom::ConstBondIterator b_it = atom.getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& nbr_bond = *b_it;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(nbr_bond))
			continue;

		nbr_cnt++;

		if (&bond == &nbr_bond)
			continue;

		if (!termAtomMask.test(root_frag.getAtomIndex(nbr_atom)))
			return 1;

		if (first) {
			nbr_atom_type = getType(nbr_atom);
			first = false;
			continue;
		}

		if (getType(nbr_atom) != nbr_atom_type)
			return 1;
	}

	switch (getHybridizationState(atom)) {

		case HybridizationState::SP2:
			if (nbr_cnt != 3)
				return 1;

			return 2;

		case HybridizationState::SP3:
			if (nbr_cnt == 4)
				return 3;
 
			if (nbr_cnt == 3 && isPlanarNitrogen(atom, node))
				return 2;				

		default:
			return 1;
	}
	
	return 1;
}

void ConfGen::SystematicConformerGeneratorImpl::genMMFF94InteractionData(const Chem::MolecularGraph& molgraph, unsigned int ff_type, 
																		 ForceField::MMFF94InteractionData& ia_data)
{
	using namespace ForceField;

 	unsigned int ia_types = ForceField::InteractionType::ALL;

	switch (ff_type) {

		case ForceFieldType::MMFF94S:
			mmff94Parameterizer.setStaticParameterDefaults();
			break;

		case ForceFieldType::MMFF94:
			mmff94Parameterizer.setDynamicParameterDefaults();
			break;

		case ForceFieldType::MMFF94S_NO_ESTAT:
			ia_types ^= InteractionType::ELECTROSTATIC;
			mmff94Parameterizer.setStaticParameterDefaults();
			break;

		case ForceFieldType::MMFF94_NO_ESTAT:
			ia_types ^= InteractionType::ELECTROSTATIC;
			mmff94Parameterizer.setDynamicParameterDefaults();
			break;

		default:
			throw Base::ValueError("SystematicConformerGeneratorImpl: invalid forcefield type");
	}

	mmff94Parameterizer.performStrictAtomTyping(settings.strictAtomTypingPerformed());
	mmff94Parameterizer.parameterize(molgraph, ia_data, ia_types);
}

void ConfGen::SystematicConformerGeneratorImpl::distFragmentMMFF94InteractionData(FragmentTreeNode& node)
{
	if (node.hasChildren()) {
		distFragmentMMFF94InteractionData(*node.getLeftChild());
		distFragmentMMFF94InteractionData(*node.getRightChild());
	}

	if (&node != &fragTree)
		extractFragmentMMFF94InteractionData(node);
}

void ConfGen::SystematicConformerGeneratorImpl::extractFragmentMMFF94InteractionData(FragmentTreeNode& node)
{
	using namespace Chem;
	using namespace ForceField;

	const MolecularGraph& root_frag = fragTree.getFragment();
	const MolecularGraph& node_frag = node.getFragment();

	MMFF94InteractionData& root_ia_data = fragTree.getMMFF94InteractionData();
	MMFF94InteractionData& node_ia_data = node.getMMFF94InteractionData();

	node_ia_data.clear();
	tmpMMFF94Data.clear();

	extractFragmentMMFF94InteractionData2(root_ia_data.getBondStretchingInteractions(), node_ia_data.getBondStretchingInteractions(), 
										  tmpMMFF94Data.getBondStretchingInteractions(), root_frag, node_frag);
	extractFragmentMMFF94InteractionData2(root_ia_data.getElectrostaticInteractions(), node_ia_data.getElectrostaticInteractions(), 
										  tmpMMFF94Data.getElectrostaticInteractions(), root_frag, node_frag);
	extractFragmentMMFF94InteractionData2(root_ia_data.getVanDerWaalsInteractions(), node_ia_data.getVanDerWaalsInteractions(), 
										  tmpMMFF94Data.getVanDerWaalsInteractions(), root_frag, node_frag);
	extractFragmentMMFF94InteractionData3(root_ia_data.getAngleBendingInteractions(), node_ia_data.getAngleBendingInteractions(), 
										  tmpMMFF94Data.getAngleBendingInteractions(), root_frag, node_frag);
	extractFragmentMMFF94InteractionData3(root_ia_data.getStretchBendInteractions(), node_ia_data.getStretchBendInteractions(), 
										  tmpMMFF94Data.getStretchBendInteractions(), root_frag, node_frag);
	extractFragmentMMFF94InteractionData4(root_ia_data.getOutOfPlaneBendingInteractions(), node_ia_data.getOutOfPlaneBendingInteractions(), 
										  tmpMMFF94Data.getOutOfPlaneBendingInteractions(), root_frag, node_frag);
	extractFragmentMMFF94InteractionData4(root_ia_data.getTorsionInteractions(), node_ia_data.getTorsionInteractions(), 
										  tmpMMFF94Data.getTorsionInteractions(), root_frag, node_frag);

	root_ia_data.swap(tmpMMFF94Data);
}

bool ConfGen::SystematicConformerGeneratorImpl::timeoutExceeded() const
{
	if (settings.getTimeout() == 0)
		return false;

	return (timer.elapsed().wall > (boost::timer::nanosecond_type(settings.getTimeout()) * 1000000));
}

Math::Vector3DArray* ConfGen::SystematicConformerGeneratorImpl::allocVector3DArray()
{
	if (!freeCoordArrays.empty()) {
		Math::Vector3DArray* vec_array = freeCoordArrays.back();

		vec_array->resize(fragTree.getFragment().getNumAtoms());
		freeCoordArrays.pop_back();

		return vec_array;
	}

	Math::Vector3DArray::SharedPointer vec_array(new Math::Vector3DArray());

	vec_array->resize(fragTree.getFragment().getNumAtoms());
	allocCoordArrays.push_back(vec_array);

	return vec_array.get();
}

void ConfGen::SystematicConformerGeneratorImpl::freeVector3DArray(Math::Vector3DArray* vec_array)
{
	freeCoordArrays.push_back(vec_array);
}
