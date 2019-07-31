/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SystematicConformerGeneratorImpl.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::SystematicConformerGeneratorImpl.
 */

#ifndef CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATORIMPL_HPP
#define CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATORIMPL_HPP

#include <vector>
#include <utility>

#include <boost/timer/timer.hpp>
#include <boost/tuple/tuple.hpp>

#include "CDPL/ConfGen/SystematicConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentConformerGenerator.hpp"
#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "FragmentTreeNode.hpp"


namespace CDPL 
{

    namespace ConfGen 
    {
	
		class SystematicConformerGeneratorImpl 
		{

		public:
			typedef SystematicConformerGenerator::Settings Settings;
			typedef SystematicConformerGenerator::Status Status;

			SystematicConformerGeneratorImpl();

			~SystematicConformerGeneratorImpl();

			void applySettings(const Settings& settings);

			const Settings& getSettings() const;

			Status generate(const Chem::MolecularGraph& molgraph);

		private:
			class Vec3DArrayDeallocator
			{

			public:
				Vec3DArrayDeallocator(SystematicConformerGeneratorImpl* owner, Math::Vector3DArray* array_ptr): 
					owner(owner), arrayPtr(array_ptr) {}

				~Vec3DArrayDeallocator() {
					if (arrayPtr)
						owner->freeVector3DArray(arrayPtr);
				}

				void release() {
					arrayPtr = 0;
				}

			private:
				SystematicConformerGeneratorImpl* owner;
				Math::Vector3DArray*              arrayPtr;
			};

			SystematicConformerGeneratorImpl(const SystematicConformerGeneratorImpl&);

			SystematicConformerGeneratorImpl& operator=(const SystematicConformerGeneratorImpl&);

			void freeVector3DArrays();
		
			void buildTree(const Chem::MolecularGraph& molgraph);

			void getBuildFragmentNodes(FragmentTreeNode& node);
			void clearFragmentConformers(FragmentTreeNode& node) const;

			bool setBuildFragmentCoordinates();

			bool setExistingCoordinates(FragmentTreeNode& node);
			bool setFragmentLibraryCoordinates(FragmentTreeNode& node);
			bool generateFragmentCoordinates(FragmentTreeNode& node);

			void distChainBuildFragmentCoordinates(FragmentTreeNode& node, const Math::Vector3DArray& coords, 
												   bool fix_stereo);

			void fixAtomAndBondConfigurations(FragmentTreeNode& node) const;

			void setupAromRingSubstituentBondLengthList(FragmentTreeNode& node);
			void fixAromRingSubstituentBondLengths(Math::Vector3DArray& coords) const;

			void generateChainBuildFragmentSubtrees();

			void getLibraryFragmentConformation(const Chem::MolecularGraph& lib_frag, 
												std::size_t conf_idx, Math::Vector3DArray& coords) const;

			void buildAtomIndexMaps(FragmentTreeNode& node) const;
			void buildFragmentLibraryEntryAtomIndexMap(const FragmentTreeNode& node);

			void getFragmentLinkBonds(const Chem::MolecularGraph& molgraph);
			void getRotatableBonds(const Chem::MolecularGraph& molgraph);

			void generateMMFF94ParameterData(const Chem::MolecularGraph& molgraph, unsigned int ff_type, 
											 ForceField::MMFF94InteractionData& ia_data);

			void setupMMFF94TreeNodeParameterData();
			void distMMFF94ParameterData(FragmentTreeNode& node);
			void extractMMFF94ParameterData(FragmentTreeNode& node);

			Math::Vector3DArray* allocVector3DArray();
			void freeVector3DArray(Math::Vector3DArray* vec_array);

			bool timeoutExceeded() const;

			typedef FragmentTreeNode::BondList BondList;
			typedef FragmentTreeNode::AtomIndexMap AtomIndexMap;
			typedef std::vector<FragmentTreeNode*> NodeList;
			typedef std::vector<Math::Vector3DArray::SharedPointer> AllocVector3DArrayList;
			typedef std::vector<Math::Vector3DArray*> Vector3DArrayList;
			typedef std::pair<std::size_t, std::size_t> IndexPair;
			typedef std::vector<IndexPair> IndexPairList;
			typedef boost::tuple<std::size_t, std::size_t, double> BondLengthDescriptor;
			typedef std::vector<BondLengthDescriptor> BondLengthDescriptorList;

			Settings                                        settings;
			FragmentTreeNode                                fragTree;
			BondList                                        bondList;
			NodeList                                        buildFragNodes; 
			FragmentLibraryEntry                            fragLibEntry;
			FragmentConformerGenerator                      fragConfGen;
			IndexPairList                                   fragLibEntryAtomIdxMap;
			BondLengthDescriptorList                        aromRingSubstBondLens;
			boost::timer::cpu_timer                         timer;
			ForceField::MMFF94InteractionParameterizer      mmff94Parameterizer;
			ForceField::MMFF94InteractionData               tmpMMFF94ParamData;
			ForceField::MMFF94InteractionData               fragBuildMMFF94ParamData;
			Chem::SmallestSetOfSmallestRings::SharedPointer fragSSSR;
			AllocVector3DArrayList                          allocCoordArrays;
			Vector3DArrayList                               freeCoordArrays;
		};
    }
}

#endif // CDPL_CONFGEN_SYSTEMATICCONFORMERGENERATORIMPL_HPP
