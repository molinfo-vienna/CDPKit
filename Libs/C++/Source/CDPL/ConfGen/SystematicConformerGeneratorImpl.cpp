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
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/ConfGen/UtilityFunctions.hpp"
#include "CDPL/ConfGen/FragmentType.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Bond.hpp"
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
		"  <rule pattern=\"[*,#1:1]~[^3:2]-[^3X4H3:3]-[#1:4]\">"
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

	const double MAX_PLANAR_ATOM_GEOM_OOP_ANGLE  = 10.0 / 180.0 * M_PI;
	const double MIN_LINEAR_ATOM_GEOM_BOND_ANGLE = 175.0 / 180.0 * M_PI;
}


ConfGen::SystematicConformerGeneratorImpl::SystematicConformerGeneratorImpl()
{
	using namespace Chem;

	fragConfGen.reuseExistingCoordinates(false);

	torsionRuleMatcher.reportUniqueMappingsOnly(true);
	torsionRuleMatcher.stopAtFirstMatchingRule(true);

	symMappingSearch.includeIdentityMapping(true);
	symMappingSearch.setAtomPropertyFlags(AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::AROMATICITY |
										  AtomPropertyFlag::EXPLICIT_BOND_COUNT | AtomPropertyFlag::HYBRIDIZATION_STATE);
	symMappingSearch.setBondPropertyFlags(BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY |
										  BondPropertyFlag::AROMATICITY);
	symMappingSearch.setFoundMappingCallback(
		boost::bind(&ConfGen::SystematicConformerGeneratorImpl::processSymmetryMapping, this, _1, _2));
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
	init(molgraph);

	buildTree(molgraph);
	setupRootAtomIndexLists(fragTree);
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
	setupTorsions(fragTree);

	if (timeoutExceeded())
		return Status::TIMEOUT_EXCEEDED;

	getSymmetryMappings();

	if (timeoutExceeded())
		return Status::TIMEOUT_EXCEEDED;

	return Status::SUCCESS;
}

void ConfGen::SystematicConformerGeneratorImpl::init(const Chem::MolecularGraph& molgraph)
{
	timer.start();	
	extAtomConnectivities.clear();
	freeCoordArrays.clear();
	freeIndexArrays.clear();

	symMappingHAtomMask.resize(molgraph.getNumAtoms());
	symMappingHAtomMask.reset();
	
	if (settings.nitrogensEnumerated()) {
		enumNitrogenMask.resize(molgraph.getNumAtoms());
		enumNitrogenMask.reset();
	}

	std::for_each(allocCoordArrays.begin(), allocCoordArrays.end(), 
				  boost::bind(&SystematicConformerGeneratorImpl::freeVector3DArray, this, 
							  boost::bind<Math::Vector3DArray*>(&Math::Vector3DArray::SharedPointer::get, _1)));

	std::for_each(allocIndexArrays.begin(), allocIndexArrays.end(), 
				  boost::bind(&SystematicConformerGeneratorImpl::freeIndexArray, this, 
							  boost::bind<IndexArray*>(&IndexArrayPtr::get, _1)));

	buildAtomTypeMask(molgraph, hAtomMask, Chem::AtomType::H, true);
}

void ConfGen::SystematicConformerGeneratorImpl::buildTree(const Chem::MolecularGraph& molgraph)
{
	buildFragNodes.clear();

	getFragmentLinkBonds(molgraph);

	fragTree.splitRecursive(molgraph, splitBondList); // build tree according to build fragment link bonds

	getBuildFragmentNodes(fragTree);

	genChainBuildFragmentSubtrees();
}

void ConfGen::SystematicConformerGeneratorImpl::setupRootAtomIndexLists(FragmentTreeNode& node) const
{
	IndexArray& idx_list = node.getRootAtomIndices();
	
	idx_list.clear();

	std::transform(node.getFragment().getAtomsBegin(), node.getFragment().getAtomsEnd(), std::back_inserter(idx_list),
				   boost::bind(&Chem::MolecularGraph::getAtomIndex, &fragTree.getFragment(), _1));

	if (!node.hasChildren())
		return;

	setupRootAtomIndexLists(*node.getLeftChild());
	setupRootAtomIndexLists(*node.getRightChild());
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

	AtomList& nbr_atoms1 = node.getSplitBondAtom1Neighbors();

	nbr_atoms1.clear();

	if (getConnectedAtoms(*bond_atoms[0], frag, std::back_inserter(nbr_atoms1), bond_atoms[1]) == 0) // sanity_check
		return;

	AtomList& nbr_atoms2 = node.getSplitBondAtom2Neighbors();

	nbr_atoms2.clear();

	if (getConnectedAtoms(*bond_atoms[1], frag, std::back_inserter(nbr_atoms2), bond_atoms[0]) == 0) // sanity_check
		return;

	const Bond& bond = *node.getSplitBond();
	std::size_t order = getOrder(bond);

	if (order == 2 && isStereoCenter(bond, frag, false, 0)) {
		// torsion setup for stereo double bonds

		const StereoDescriptor& descr = getStereoDescriptor(bond);
		const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();
		bool descr_valid = true;

		if ((descr.getConfiguration() == BondConfiguration::CIS || descr.getConfiguration() == BondConfiguration::TRANS) && descr.isValid(bond)) {
			for (std::size_t i = 0; i < 4; i++) {
				if (!frag.containsAtom(*ref_atoms[i])) {
					descr_valid = false;
					break;
				}
			}

		} else
			descr_valid = false;
		
		if (descr_valid) {
			// choose angle that results in desired configuration

			if (ref_atoms[1] == bond_atoms[0])
				node.setTorsionReferenceAtoms(ref_atoms[0], ref_atoms[3]);
			else
				node.setTorsionReferenceAtoms(ref_atoms[3], ref_atoms[0]);

			node.getTorsionAngles().push_back(descr.getConfiguration() == BondConfiguration::CIS ? 0.0 : 180.0);

		} else {
			// choose trans configuration of bulkiest substituents
	
			node.setTorsionReferenceAtoms(getBulkiestSubstituent(node.getSplitBondAtom1Neighbors()),
										  getBulkiestSubstituent(node.getSplitBondAtom2Neighbors()));
			node.getTorsionAngles().push_back(180.0);
		}

	} else {
		// find matching rules for all other bonds

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

			if (!node.getTorsionAngles().empty()) {
				const Atom* const* match_atoms = match->getAtoms();
				
				if (match_atoms[1] == bond_atoms[0])
					node.setTorsionReferenceAtoms(match_atoms[0], match_atoms[3]);
				else
					node.setTorsionReferenceAtoms(match_atoms[3], match_atoms[0]);
			}
		}
		
		if (node.getTorsionAngles().empty()) {
			std::size_t rot_sym_order = std::max(getRotationalSymmetryOrder(*bond_atoms[0], *bond_atoms[1], nbr_atoms1, node),
												 getRotationalSymmetryOrder(*bond_atoms[1], *bond_atoms[0], nbr_atoms2, node));
			// fallback: rotation in 30° steps

			for (std::size_t i = 0, num_angles = 12 / rot_sym_order; i < num_angles; i++)
				node.getTorsionAngles().push_back(i * 30.0);

			node.setTorsionReferenceAtoms(getBulkiestSubstituent(node.getSplitBondAtom1Neighbors()),
										  getBulkiestSubstituent(node.getSplitBondAtom2Neighbors()));

			if (order != 1)
				node.setKeepAllConformersFlag(false);

		} else if (node.getTorsionAngles().size() > 1) {
			std::size_t rot_sym_order = std::max(getRotationalSymmetryOrder(*bond_atoms[0], *bond_atoms[1], nbr_atoms1, node),
												 getRotationalSymmetryOrder(*bond_atoms[1], *bond_atoms[0], nbr_atoms2, node));

			if (rot_sym_order > 1) {
				// reduce number of torsion angles due to rotational symmetry

				double ident_rot_ang = 360.0 / rot_sym_order; 

				for (FragmentTreeNode::TorsionAngleArray::iterator it = node.getTorsionAngles().begin(), end = node.getTorsionAngles().end(); it != end; ++it) {
					double& tor_ang = *it;

					tor_ang = std::fmod(tor_ang, ident_rot_ang);
				}

				std::sort(node.getTorsionAngles().begin(), node.getTorsionAngles().end());
		
				node.getTorsionAngles().erase(std::unique(node.getTorsionAngles().begin(), node.getTorsionAngles().end()), node.getTorsionAngles().end());
			}
		}
	}

	if (order == 1 && node.getTorsionAngles().size() > 1 && settings.heteroAtomHydrogensEnumerated()) {
		const MolecularGraph& root_frag = fragTree.getFragment();
			
		if (getType(*bond_atoms[0]) != AtomType::C && getHeavyBondCount(*bond_atoms[0], root_frag) == 1) {
			for (AtomList::const_iterator it = nbr_atoms1.begin(), end = nbr_atoms1.end(); it != end; ++it) 
					symMappingHAtomMask.set(root_frag.getAtomIndex(**it));
		}

		if (getType(*bond_atoms[1]) != AtomType::C && getHeavyBondCount(*bond_atoms[1], root_frag) == 1) {
			for (AtomList::const_iterator it = nbr_atoms2.begin(), end = nbr_atoms2.end(); it != end; ++it) 
				symMappingHAtomMask.set(root_frag.getAtomIndex(**it));
		}
	}

	// check if bond and reference atoms are in an invalid linear arrangement

	if ((node.getTorsionReferenceAtoms()[0] ? hasLinearGeometry(*bond_atoms[0], *bond_atoms[1], *node.getTorsionReferenceAtoms()[0], *node.getLeftChild()) : false) ||
		(node.getTorsionReferenceAtoms()[1] ? hasLinearGeometry(*bond_atoms[1], *bond_atoms[0], *node.getTorsionReferenceAtoms()[1], *node.getRightChild()) : false))
		node.setTorsionReferenceAtoms(0, 0);
}

void ConfGen::SystematicConformerGeneratorImpl::getSymmetryMappings()
{
	buildSymmetryMappingSearchMolGraph();
	setupSymmetryMappingValidationData();

	symMappings.clear();
	symMappingSearch.findMappings(symMappingSearchMolGraph);

	std::cerr << "Found " << symMappings.size() << " symmetry mappings....\n";
}

void ConfGen::SystematicConformerGeneratorImpl::buildSymmetryMappingSearchMolGraph()
{
	using namespace Chem;

	symMappingSearchMolGraph.clear();
	symMappingAtomIndices.clear();

	const MolecularGraph& root_frag = fragTree.getFragment();

	hAtomMask ^= symMappingHAtomMask;

	for (std::size_t i = 0, num_atoms = root_frag.getNumAtoms(); i < num_atoms; i++) {
		if (!hAtomMask.test(i)) {
			symMappingSearchMolGraph.addAtom(root_frag.getAtom(i));
			symMappingAtomIndices.push_back(i);
		}
	}

	for (MolecularGraph::ConstBondIterator it = root_frag.getBondsBegin(), end = root_frag.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (symMappingSearchMolGraph.containsAtom(bond.getBegin()) && symMappingSearchMolGraph.containsAtom(bond.getEnd()))
			symMappingSearchMolGraph.addBond(bond);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::setupSymmetryMappingValidationData()
{
	using namespace Chem;

	symMappingAtomStereoDescrs.clear();

	const MolecularGraph& root_frag = fragTree.getFragment();
	bool nitrogens_enum = settings.nitrogensEnumerated();
	std::size_t i = 0;

	for (Fragment::ConstAtomIterator it = symMappingSearchMolGraph.getAtomsBegin(), end = symMappingSearchMolGraph.getAtomsEnd(); it != end; ++it, i++) {
		const Atom& atom = *it;

		if (nitrogens_enum && enumNitrogenMask.test(symMappingAtomIndices[i]))
			continue;

		if (getRingFlag(atom))
			continue;

		if (getHybridizationState(atom) != HybridizationState::SP3)
			continue;

		tmpAtomList.clear();

		std::size_t nbr_cnt = getConnectedAtoms(atom, symMappingSearchMolGraph, std::back_inserter(tmpAtomList));

		if (nbr_cnt < 3 || nbr_cnt > 4)
			continue;

		const FragmentTreeNode* coords_node = getLeafNodeWithCoordinates(atom, tmpAtomList, fragTree);

		if (!coords_node)
			continue;

		const Math::Vector3DArray& coords = *coords_node->getConformers().front().first;

		std::size_t atom_idx = symMappingAtomIndices[i];
		std::size_t nbr_atom1_idx = root_frag.getAtomIndex(*tmpAtomList[0]);
		std::size_t nbr_atom2_idx = root_frag.getAtomIndex(*tmpAtomList[1]);
		std::size_t nbr_atom3_idx = root_frag.getAtomIndex(*tmpAtomList[2]);

		const Math::Vector3D& nbr_atom1_coords = coords[nbr_atom1_idx];
		const Math::Vector3D& nbr_atom2_coords = coords[nbr_atom2_idx];
		const Math::Vector3D& nbr_atom3_coords = coords[nbr_atom3_idx];
		const Math::Vector3D& atom_coords = coords[atom_idx];

		double oop_angle = ForceField::calcOutOfPlaneAngle<double>(nbr_atom1_coords, atom_coords, nbr_atom2_coords, nbr_atom3_coords);

		if (std::abs(oop_angle) <= MAX_PLANAR_ATOM_GEOM_OOP_ANGLE)
			continue;
		
		double vol = innerProd(crossProd(atom_coords - nbr_atom2_coords, atom_coords - nbr_atom1_coords), 
							   atom_coords - nbr_atom3_coords); 
		unsigned int config = (vol > 0.0 ? AtomConfiguration::S : vol < 0.0 ? AtomConfiguration::R : AtomConfiguration::NONE);

		if (config == AtomConfiguration::NONE)
			continue;

		symMappingAtomStereoDescrs.insert(AtomStereoDescriptorMap::value_type(&atom, StereoDescriptor(config, *tmpAtomList[0], *tmpAtomList[1], *tmpAtomList[2])));
	}

	std::cerr << "Got " << symMappingAtomStereoDescrs.size() << " symmetry mapping check atom stereo descriptors....\n";
}

bool ConfGen::SystematicConformerGeneratorImpl::processSymmetryMapping(const Chem::MolecularGraph& molgraph, const Chem::AtomBondMapping& mapping)
{
	if (!checkSymmetryMapping(mapping))
		return false;

	symMappings.push_back(createAtomIndexMapping(mapping));
	return false;
}

bool ConfGen::SystematicConformerGeneratorImpl::checkSymmetryMapping(const Chem::AtomBondMapping& mapping) const
{
	// TODO
	return true;
}

ConfGen::SystematicConformerGeneratorImpl::IndexArray* ConfGen::SystematicConformerGeneratorImpl::createAtomIndexMapping(const Chem::AtomBondMapping& mapping)
{
	using namespace Chem;

	IndexArray* idx_mapping = allocIndexArray();
	const AtomMapping& atom_mapping = mapping.getAtomMapping();
	const MolecularGraph& root_frag = fragTree.getFragment();

	idx_mapping->clear();

	for (Fragment::ConstAtomIterator it = symMappingSearchMolGraph.getAtomsBegin(), end = symMappingSearchMolGraph.getAtomsEnd(); it != end; ++it) {
		const Atom* mpd_atom = atom_mapping[&*it];

		assert(mpd_atom);

		idx_mapping->push_back(root_frag.getAtomIndex(*mpd_atom));
	}

	return idx_mapping;
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

		if (!splitBondList.empty())
			node->splitRecursive(frag, splitBondList);
	}
}

bool ConfGen::SystematicConformerGeneratorImpl::setExistingCoordinates(FragmentTreeNode& node)
{
	using namespace Chem;

	try {
		Math::Vector3DArray* coords = allocVector3DArray();
		Vec3DArrayDeallocator dealloc_guard(this, coords);

		const MolecularGraph& frag = node.getFragment();
		const IndexArray& root_atom_inds = node.getRootAtomIndices();

		for (std::size_t i = 0, num_atoms = frag.getNumAtoms(); i < num_atoms; i++) {
			const Atom& atom = frag.getAtom(i);

			(*coords)[root_atom_inds[i]] = get3DCoordinates(atom);
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

	const IndexArray& root_atom_inds = node.getRootAtomIndices();
	const FragmentLibraryEntry::AtomMapping& entry_atom_map = fragLibEntry.getAtomMapping();

	fragLibEntryAtomIdxMap.clear();

	for (std::size_t i = 0, num_atoms = node.getFragment().getNumAtoms(); i < num_atoms; i++)
		fragLibEntryAtomIdxMap.push_back(IndexPair(fragLibEntry.getAtomIndex(*entry_atom_map[i]), root_atom_inds[i]));
}

void ConfGen::SystematicConformerGeneratorImpl::distChainBuildFragmentCoordinates(FragmentTreeNode& node, const Math::Vector3DArray& coords, 
																				  bool fix_configs, bool opt_db_configs)
{
	if (node.hasChildren()) {
		distChainBuildFragmentCoordinates(*node.getLeftChild(), coords, fix_configs, opt_db_configs);
		distChainBuildFragmentCoordinates(*node.getRightChild(), coords, fix_configs, opt_db_configs);
		return;
	}

	const IndexArray& root_atom_inds = node.getRootAtomIndices();

	Math::Vector3DArray* node_coords = allocVector3DArray();
	Vec3DArrayDeallocator dealloc_guard(this, node_coords);

	for (IndexArray::const_iterator idx_it = root_atom_inds.begin(), idx_end = root_atom_inds.end(); idx_it != idx_end; ++idx_it) {
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

	assert(node.getNumConformers() > 0);

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

	assert(node.getNumConformers() > 0);

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
	
		const Atom* subst1_atom = getBulkiestDoubleBondSubstituent(atom1, atom2, frag);

		if (!subst1_atom)
			return;

		const Atom* subst2_atom = getBulkiestDoubleBondSubstituent(atom2, atom1, frag);

		if (!subst2_atom)
			return;

		checkAndCorrectDoubleBondConfiguration(node, bond, 
											   StereoDescriptor(BondConfiguration::TRANS, 
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

	const IndexArray& root_atom_inds = node.getRootAtomIndices();

	// mirror fragment coordinates in xy-plane

	for (IndexArray::const_iterator it = root_atom_inds.begin(), end = root_atom_inds.end(); it != end; ++it)
		coords[*it][2] *= -1.0;
}

void ConfGen::SystematicConformerGeneratorImpl::checkAndCorrectDoubleBondConfiguration(FragmentTreeNode& node, const Chem::Bond& bond, 
																					   const Chem::StereoDescriptor& descr)
{
	using namespace Chem;

	Math::Vector3DArray& coords = *node.getConformers().front().first;

	if (calcBondConfiguration(bond, fragTree.getFragment(), descr, coords) == descr.getConfiguration())
		return;

	// rotate substituents on ref. atom 2 180° around bond axis

	const MolecularGraph& root_frag = fragTree.getFragment();
	const Chem::Atom* const* ref_atoms = descr.getReferenceAtoms();

	std::size_t bond_atom1_idx = root_frag.getAtomIndex(*ref_atoms[1]);
	std::size_t bond_atom2_idx = root_frag.getAtomIndex(*ref_atoms[2]);

	const Math::Vector3D& bond_atom1_pos = coords[bond_atom1_idx];
	const Math::Vector3D& bond_atom2_pos = coords[bond_atom2_idx];

	Math::Vector3D bond_vec(bond_atom2_pos - bond_atom1_pos);
	double bond_len = length(bond_vec);

	if (bond_len == 0.0) // sanity check
		return;

	Math::DQuaternion rot_quat(0, bond_vec[0] / bond_len, bond_vec[1] / bond_len, bond_vec[2] / bond_len);

	tmpAtomList.clear();

	getConnectedAtoms(*ref_atoms[2], node.getFragment(), std::back_inserter(tmpAtomList), ref_atoms[1]);

	for (AtomList::const_iterator it = tmpAtomList.begin(), end = tmpAtomList.end(); it != end; ++it) {
		assert(getExplicitBondCount(**it, node.getFragment()) == 1);

		Math::Vector3D& atom_pos = coords[root_frag.getAtomIndex(**it)];

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

	assert(node.getNumConformers() > 0);

	const MolecularGraph& frag = node.getFragment();
	const IndexArray& root_atom_inds = node.getRootAtomIndices();
	Math::Vector3DArray& coords = *node.getConformers().front().first;
	std::size_t i = 0;

	if (!ring_sys) {
		for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it, i++) {
			const Atom& atom = *it;

			if (!isInvertibleNitrogen(atom, frag, coords))
				continue;

			Math::Vector3DArray* inv_n_coords = allocVector3DArray();
			Vec3DArrayDeallocator dealloc_guard(this, inv_n_coords);

			// copy and mirror fragment coordinates in xy-plane

			for (IndexArray::const_iterator ai_it = root_atom_inds.begin(), ai_end = root_atom_inds.end(); ai_it != ai_end; ++ai_it) {
				std::size_t atom_idx = *ai_it;
				const Math::Vector3D& orig_atom_pos = coords[atom_idx];
				Math::Vector3D& new_atom_pos = (*inv_n_coords)[atom_idx];

				new_atom_pos[0] = orig_atom_pos[0];
				new_atom_pos[1] = orig_atom_pos[1];
				new_atom_pos[2] = -orig_atom_pos[2];
			}

			enumNitrogenMask.set(root_atom_inds[i]);

			node.addConformer(inv_n_coords);
			dealloc_guard.release();
			return;
		}

		return;
	}

	for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it, i++) {
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

		enumNitrogenMask.set(root_atom_inds[i]);

		assert(subst_nbr && ring_nbr2);
		assert(getExplicitBondCount(*subst_nbr, frag) == 1);

		const MolecularGraph& root_frag = fragTree.getFragment();

		std::size_t ctr_atom_idx = root_frag.getAtomIndex(atom);
		std::size_t ring_nbr1_idx = root_frag.getAtomIndex(*ring_nbr1);
		std::size_t ring_nbr2_idx = root_frag.getAtomIndex(*ring_nbr2);
		std::size_t subst_nbr_idx = root_frag.getAtomIndex(*subst_nbr);

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

			for (IndexArray::const_iterator ai_it = root_atom_inds.begin(), ai_end = root_atom_inds.end(); ai_it != ai_end; ++ai_it) {
				std::size_t curr_atom_idx = *ai_it;

				if (curr_atom_idx != subst_nbr_idx) {
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

	splitBondList.clear();

	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (isFragmentLinkBond(bond, molgraph))
			splitBondList.push_back(&bond);
	}
}

void ConfGen::SystematicConformerGeneratorImpl::getRotatableBonds(const Chem::MolecularGraph& frag)
{
	using namespace Chem;

	splitBondList.clear();	

	for (MolecularGraph::ConstBondIterator it = frag.getBondsBegin(), end = frag.getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
	
		if (isRotatable(bond, frag, true, false, true)) 
			splitBondList.push_back(&bond);
	}
}

const Chem::Atom* ConfGen::SystematicConformerGeneratorImpl::getBulkiestDoubleBondSubstituent(const Chem::Atom& atom, const Chem::Atom& db_nbr_atom, 
																							  const Chem::MolecularGraph& frag)
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

		if (&nbr_atom == &db_nbr_atom)
			continue;

		if (!frag.containsAtom(nbr_atom) || !frag.containsBond(*b_it))
			continue;

		if (++bond_cnt > 2)
			return 0;

		std::size_t nbr_ec = extAtomConnectivities[fragTree.getFragment().getAtomIndex(nbr_atom)];

		if (!bkst_subst || nbr_ec > bkst_subst_ec) {
			bkst_subst = &nbr_atom;
			bkst_subst_ec = nbr_ec;

		} else if (bkst_subst_ec == nbr_ec)
			return 0;
	}

	return bkst_subst;
}

const Chem::Atom* ConfGen::SystematicConformerGeneratorImpl::getBulkiestSubstituent(const AtomList& subst_atoms)
{
	using namespace Chem;

	calcExtendedAtomConnectivities();

	const Atom* max_ec_atom = 0;
	std::size_t max_atom_ec = 0;

	for (AtomList::const_iterator it = subst_atoms.begin(), end = subst_atoms.end(); it != end; ++it) {
		const Atom* atom = *it;
		std::size_t atom_ec = extAtomConnectivities[fragTree.getFragment().getAtomIndex(*atom)];

		if (!max_ec_atom || atom_ec > max_atom_ec) {
			max_ec_atom = atom;
			max_atom_ec = atom_ec;
		}
	}

	return max_ec_atom;
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

void ConfGen::SystematicConformerGeneratorImpl::calcExtendedAtomConnectivities()
{
	using namespace Chem;

	if (!extAtomConnectivities.empty())
		return;

	const MolecularGraph& root_frag = fragTree.getFragment();
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
																	 const Math::Vector3DArray& coords)
{
	using namespace Chem;

	if (getType(atom) != AtomType::N)
		return false;

	std::size_t h_bond_count = 0;
	std::size_t ring_bond_count = 0;
	std::size_t nbr_atom_indices[3];
	std::size_t h_nbr_idx = 0;
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

		std::size_t nbr_atom_idx = root_frag.getAtomIndex(nbr_atom);

		if (hAtomMask.test(nbr_atom_idx)) {
			if (++h_bond_count > 1)
				return false;

			h_nbr_idx = nbr_atom_idx;
		}

		nbr_atom_indices[i++] = nbr_atom_idx;
	}

	if (i != 3)
		return false;

	double oop_angle = ForceField::calcOutOfPlaneAngle<double>(coords[nbr_atom_indices[0]], coords[root_frag.getAtomIndex(atom)],
															   coords[nbr_atom_indices[1]], coords[nbr_atom_indices[2]]);

	if (std::abs(oop_angle) <= MAX_PLANAR_ATOM_GEOM_OOP_ANGLE)
		return false;

	if 	(h_bond_count > 0) 
		symMappingHAtomMask.set(h_nbr_idx);

	const StereoDescriptor& descr = getStereoDescriptor(atom);

	if (descr.isValid(atom) && (descr.getConfiguration() == AtomConfiguration::R || descr.getConfiguration() == AtomConfiguration::S))
		return false;

	return true;
}

bool ConfGen::SystematicConformerGeneratorImpl::hasLinearGeometry(const Chem::Atom& atom, const Chem::Atom& nbr_atom1,  
																  const Chem::Atom& nbr_atom2, const FragmentTreeNode& node) 
{
	using namespace Chem;

	tmpAtomList.clear();
	tmpAtomList.push_back(&nbr_atom1);
	tmpAtomList.push_back(&nbr_atom2);

	const FragmentTreeNode* coords_node = getLeafNodeWithCoordinates(atom, tmpAtomList, node);

	if (!coords_node)
		return false;

	const MolecularGraph& root_frag = fragTree.getFragment();

	std::size_t atom_idx = root_frag.getAtomIndex(atom);
	std::size_t nbr_atom1_idx = root_frag.getAtomIndex(nbr_atom1);
	std::size_t nbr_atom2_idx = root_frag.getAtomIndex(nbr_atom2);

	const Math::Vector3DArray& coords = *coords_node->getConformers().front().first;

	double bond_angle = ForceField::calcBondAngle<double>(coords[nbr_atom1_idx], coords[atom_idx], coords[nbr_atom2_idx]);

	return (bond_angle >= MIN_LINEAR_ATOM_GEOM_BOND_ANGLE);
}

bool ConfGen::SystematicConformerGeneratorImpl::hasPlanarGeometry(const Chem::Atom& atom, const Chem::Atom& nbr_atom1,  
																  const Chem::Atom& nbr_atom2, const Chem::Atom& nbr_atom3, 
																  const FragmentTreeNode& node)
{
	using namespace Chem;

	tmpAtomList.clear();
	tmpAtomList.push_back(&nbr_atom1);
	tmpAtomList.push_back(&nbr_atom2);
	tmpAtomList.push_back(&nbr_atom3);

	const FragmentTreeNode* coords_node = getLeafNodeWithCoordinates(atom, tmpAtomList, node);

	if (!coords_node)
		return false;

	const MolecularGraph& root_frag = fragTree.getFragment();

	std::size_t atom_idx = root_frag.getAtomIndex(atom);
	std::size_t nbr_atom1_idx = root_frag.getAtomIndex(nbr_atom1);
	std::size_t nbr_atom2_idx = root_frag.getAtomIndex(nbr_atom2);
	std::size_t nbr_atom3_idx = root_frag.getAtomIndex(nbr_atom3);

	const Math::Vector3DArray& coords = *coords_node->getConformers().front().first;

	double oop_angle = ForceField::calcOutOfPlaneAngle<double>(coords[nbr_atom1_idx], coords[atom_idx],
															   coords[nbr_atom2_idx], coords[nbr_atom3_idx]);

	return (std::abs(oop_angle) <= MAX_PLANAR_ATOM_GEOM_OOP_ANGLE);
}

const ConfGen::FragmentTreeNode* ConfGen::SystematicConformerGeneratorImpl::getLeafNodeWithCoordinates(const Chem::Atom& atom, const AtomList& nbr_atoms,
																									   const FragmentTreeNode& node) const
{
	using namespace Chem;

	const MolecularGraph& frag = node.getFragment();

	if (!frag.containsAtom(atom))
		return 0;

	if (node.hasChildren()) {
		if (const FragmentTreeNode* found_node = getLeafNodeWithCoordinates(atom, nbr_atoms, *node.getLeftChild()))
			return found_node;

		return getLeafNodeWithCoordinates(atom, nbr_atoms, *node.getRightChild());
	}

	if (node.getConformers().empty())
		return 0;

	for (AtomList::const_iterator it = nbr_atoms.begin(), end = nbr_atoms.end(); it != end; ++it)
		if (!frag.containsAtom(**it))
			return 0;
		
	return &node;
}

std::size_t ConfGen::SystematicConformerGeneratorImpl::getRotationalSymmetryOrder(const Chem::Atom& atom, const Chem::Atom& bond_nbr, 
																				  const AtomList& nbr_atoms, const FragmentTreeNode& node)
{
	using namespace Chem;

	unsigned int nbr_atom_type = 0;
	std::size_t nbr_bond_order = 0;
	bool first = true;

	const MolecularGraph& root_frag = fragTree.getFragment();

	for (AtomList::const_iterator it = nbr_atoms.begin(), end = nbr_atoms.end(); it != end; ++it) {
		const Atom& nbr_atom = **it;
	
		if (getExplicitBondCount(nbr_atom, root_frag) != 1)
			return 1;

		if (first) {
			nbr_atom_type = getType(nbr_atom);
			nbr_bond_order = getOrder(atom.getBondToAtom(nbr_atom));
			first = false;
			continue;
		}

		if (getType(nbr_atom) != nbr_atom_type)
			return 1;

		if (getOrder(atom.getBondToAtom(nbr_atom)) != nbr_bond_order)
			return 1;
	}

	switch (getHybridizationState(atom)) {

		case HybridizationState::SP2:
			if (nbr_atoms.size() != 2)
				return 1;

			return 2;

		case HybridizationState::SP3:
			if (nbr_atoms.size() == 3)
				return 3;
 
			if (nbr_atoms.size() == 2 && getType(atom) == AtomType::N) {
				if (hasPlanarGeometry(atom, bond_nbr, *nbr_atoms[0], *nbr_atoms[1], node))
					return 2;				
			}

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

ConfGen::SystematicConformerGeneratorImpl::IndexArray* ConfGen::SystematicConformerGeneratorImpl::allocIndexArray()
{
	if (!freeIndexArrays.empty()) {
		IndexArray* idx_array = freeIndexArrays.back();

		freeIndexArrays.pop_back();

		return idx_array;
	}

	IndexArrayPtr idx_array(new IndexArray());

	allocIndexArrays.push_back(idx_array);

	return idx_array.get();
}

void ConfGen::SystematicConformerGeneratorImpl::freeIndexArray(IndexArray* idx_array)
{
	freeIndexArrays.push_back(idx_array);
}
