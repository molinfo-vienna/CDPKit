/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResonanceStructureGenerator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::ResonanceStructureGenerator.
 */

#ifndef CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP
#define CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP

#include <vector>
#include <cstddef>
#include <unordered_set>

#include <boost/shared_ptr.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Base/IntegerTypes.hpp"
#include "CDPL/Util/Array.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectPool.hpp"


namespace CDPL 
{

    namespace Chem
    {

		class MolecularGraph;
		class Atom;
		
		/**
		 * \brief ResonanceStructureGenerator.
		 */
		class CDPL_CHEM_API ResonanceStructureGenerator 
		{

		  public:
			class StructureData;

		  private:
			typedef Util::ObjectPool<StructureData> StructureDataCache;
			typedef StructureDataCache::SharedObjectPointer StructureDataPtr;
			typedef std::vector<StructureDataPtr> StructureDataList;

		  public:
			typedef boost::shared_ptr<ResonanceStructureGenerator> SharedPointer;
			typedef boost::indirect_iterator<StructureDataList::const_iterator, const StructureData> ConstStructureDataIterator;

			class CDPL_CHEM_API StructureData
		    {

				friend class ResonanceStructureGenerator;

			  public:
				const Util::LArray& getAtomCharges() const;

				const Util::STArray& getBondOrders() const;

			  private:
				Util::LArray  atomCharges;
				Util::STArray bondOrders;
				std::size_t   numCharges;
			};

			/**
			 * \brief Constructs the \c %ResonanceStructureGenerator instance.
			 */
			ResonanceStructureGenerator();

			ResonanceStructureGenerator(const ResonanceStructureGenerator& gen);

			virtual ~ResonanceStructureGenerator() {}

			ResonanceStructureGenerator& operator=(const ResonanceStructureGenerator& gen);

			Util::BitSet& getOctetRuleCheckAtomTypes();

			const Util::BitSet& getOctetRuleCheckAtomTypes() const;
			
			void minimizeOctetRuleViolations(bool minimize);

			bool octetRuleViolationsMinimized() const;

			void minimizeSP1GeometryViolations(bool minimize);

			bool sp1GeometryViolationsMinimized() const;

			void minimizeCarbonBond12Charges(bool minimize);

			bool carbonBond12ChargesMinimized() const;

			void setChargeCountWindow(std::size_t win_size);

			std::size_t getChargeCountWindow() const;

			void setMaxNumGeneratedStructures(std::size_t max_num);

			std::size_t getMaxNumGeneratedStructures() const;
			
			/**
			 * \brief Generates all unique resonanceStructures of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the resonanceStructures.
			 */
			void generate(const MolecularGraph& molgraph);

			std::size_t getNumStructures() const;

			const StructureData& getStructureData(std::size_t idx) const;

			ConstStructureDataIterator getStructureDataBegin() const;

			ConstStructureDataIterator getStructureDataEnd() const;

		  private:			
			struct BondData
		    {

				std::size_t atom1Index;
				std::size_t atom2Index;
				std::size_t bondIndex;
			};
			
			class AtomData
		    {
				
			  public:
				long init(const Atom& atom, const MolecularGraph& molgraph, std::size_t idx);

				bool canShiftElectrons() const;

				std::size_t getNumBonds() const;

				std::size_t getBondIndex(std::size_t list_idx) const;

				std::size_t getAtomIndex(std::size_t list_idx) const;

				std::size_t getIndex() const;

				unsigned int getType() const;
				
				double getElectronegativity() const;

				bool isSP1Hybridized(const StructureData& res_struct) const;
				
				bool checkValenceState(const StructureData& res_struct, long val_diff, long charge_diff) const;

				bool octetRuleFulfilled(const StructureData& res_struct) const;
				
				std::size_t countRepChargePairs(const Util::LArray& charges) const;

				bool getVisitedFlag() const;

				void setVisitedFlag();

				bool getInSmallRingFlag() const;

				void setInSmallRingFlag();
				
			  private:
				typedef std::vector<std::size_t> IndexArray;

				bool         canShiftElecs;
				std::size_t  index;
				unsigned int type;
				long         valElecCount;
				std::size_t  unprdElecCount;
				std::size_t  implHCount;
				double       enegativity;
				IndexArray   bondIndices;
				IndexArray   atomIndices;
				bool         inSmallRing;
				bool         visited;
			};

			struct StructureDataPtrHashFunc
		    {

				std::size_t operator()(const StructureDataPtr& rs_ptr) const;
			};

			struct StructureDataPtrCmpFunc
		    {

				bool operator()(const StructureDataPtr& rs_ptr1, const StructureDataPtr& rs_ptr2) const {
					return (rs_ptr1->getBondOrders() == rs_ptr2->getBondOrders() &&
							rs_ptr1->getAtomCharges() == rs_ptr2->getAtomCharges());
				}
			};
			
			typedef std::vector<AtomData> AtomDataArray;
			typedef std::vector<const AtomData*> AtomDataPtrArray;
			typedef std::vector<BondData> BondDataList;
			typedef std::unordered_set<StructureDataPtr, StructureDataPtrHashFunc, StructureDataPtrCmpFunc> StructureDataSet;
			
			void init(const MolecularGraph& molgraph);

			void createInputResStructData();

			void extractResBonds();
			void extractResBonds(AtomData& atom_data);

			void genStartResStructs();
			void genStartResStructs(std::size_t depth, std::size_t num_rep_chg_pairs);

			std::size_t countRepChargePairs() const;
			
			void genOutputResStructs();
			void genOutputResStructs(StructureData& res_struct, std::size_t depth, std::size_t con_idx,
									 std::size_t num_charges);

			void postprocOutputResStructs();

			void minimzeResStructProperty(std::size_t (ResonanceStructureGenerator::* prop_func)(const StructureData&) const);
				
			std::size_t countOctetRuleViolations(const StructureData& res_struct) const;
			std::size_t countSP1GeometryViolations(const StructureData& res_struct) const;
			std::size_t count12ChargedCBonds(const StructureData& res_struct) const;
			
			void modifyResStruct(StructureData& res_struct, std::size_t bond_idx, std::size_t atom1_idx, std::size_t atom2_idx,
								 long bond_order_diff, long atom1_chg_diff, long atom2_chg_diff) const;
			
			StructureDataPtr copyResStructPtr(const StructureDataPtr& res_struct_ptr);
			StructureDataPtr copyResStruct(const StructureData& res_struct);
			
			StructureDataCache    resStructDataCache;
			bool                  minOctRuleViolations;
			bool                  minSP1GeomViolations;
			bool                  minCBond12Charges;
			std::size_t           chargeCountWin;
			Util::BitSet          octRuleCheckAtomTypes;
			std::size_t           maxNumGenStructs;
			const MolecularGraph* molGraph;
			AtomDataArray         atomData;
			AtomDataPtrArray      resAtoms;
			BondDataList          resBonds;
			StructureData         inputResStruct;
			StructureDataList     startResStructs;
			StructureDataSet      workingResStructs;
			StructureDataList     outputResStructs;
			StructureDataList     tmpOutputResStructs;
			Util::LArray          chargeDiffPtn;
			Util::BitSet          visBondMask;
			std::size_t           minNumRepChargePairs;
			std::size_t           minNumCharges;
		};
    }
}

#endif // CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP
