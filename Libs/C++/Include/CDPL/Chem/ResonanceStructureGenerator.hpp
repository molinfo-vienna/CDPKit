/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResonanceStructureGenerator.hpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include <boost/function.hpp>
#include <boost/unordered_set.hpp>
#include <boost/shared_ptr.hpp>

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
			typedef boost::shared_ptr<ResonanceStructureGenerator> SharedPointer;

			typedef Util::LArray AtomChargeArray;
			typedef Util::STArray BondOrderArray;
			typedef boost::function2<bool, const AtomChargeArray&, const BondOrderArray&> CallbackFunction;

			/**
			 * \brief Constructs the \c %ResonanceStructureGenerator instance.
			 */
			ResonanceStructureGenerator();

			ResonanceStructureGenerator(const ResonanceStructureGenerator& gen);

			virtual ~ResonanceStructureGenerator() {}

			ResonanceStructureGenerator& operator=(const ResonanceStructureGenerator& gen);

			void setCallbackFunction(const CallbackFunction& func);

			const CallbackFunction& getCallbackFunction() const;
			
			/**
			 * \brief Generates all unique resonanceStructures of the molecular graph \a molgraph.
			 * \param molgraph The molecular graph for which to generate the resonanceStructures.
			 */
			void generate(const MolecularGraph& molgraph);

		  private:			
			struct ResStructData
		    {

				AtomChargeArray atomCharges;
				BondOrderArray  bondOrders;
			};

			struct ResBond
		    {

				std::size_t atom1Index;
				std::size_t atom2Index;
				std::size_t bondIndex;
			};

			class AtomData
		    {
				
			  public:
				long init(const Atom& atom, const MolecularGraph& molgraph, std::size_t atom_idx);

				bool canShiftElectrons() const;

				std::size_t getNumBonds() const;

				std::size_t getBondIndex(std::size_t list_idx) const;

				double getElectronegativity() const;

				bool checkValenceState(const ResStructData& res_struct, long val_diff, long charge_diff) const;
				
			  private:
				typedef std::vector<std::size_t> IndexArray;

				bool         canShiftElecs;
				std::size_t  atomIndex;
				unsigned int atomType;
				long         valElecCount;
				std::size_t  unprdElecCount;
				std::size_t  implHCount;
				double       enegativity;
				IndexArray   bondIndices;
			};
			
			typedef Util::ObjectPool<ResStructData> ResStructDataCache;
			typedef ResStructDataCache::SharedObjectPointer ResStructDataPtr;
			typedef boost::unordered_set<Base::uint64> HashCodeSet;
			typedef std::vector<ResStructDataPtr> ResStructList;
			typedef std::vector<AtomData> AtomDataArray;
			typedef std::vector<ResBond> ResBondList;

			bool init(const MolecularGraph& molgraph);
			bool genStartResStruct();

			bool shiftCharges(const ResStructData& res_struct);
			bool genNewResStruct(const ResStructData& res_struct, ResStructDataPtr& new_res_struct_ptr, const ResBond& res_bond,
								 long bond_order_diff, long atom1_chg_diff, long atom2_chg_diff);
			
			bool addNewResStruct(const ResStructDataPtr& res_struct_ptr);

			Base::uint64 calcResStructHashCode(const ResStructData& res_struct) const;

			bool outputResStruct(const ResStructData& res_struct) const;
			bool validateOutputResStruct(const ResStructData& res_struct) const;

			void restoreState(const ResStructData& src_res_struct, ResStructData& tgt_res_struct, const ResBond& res_bond) const;

			void allocResStructData(const ResStructData& src_res_struct, ResStructDataPtr& alloc_res_struct_ptr);

			ResStructDataCache    resStructDataCache;
			const MolecularGraph* molGraph;
			CallbackFunction      callbackFunc;
			AtomDataArray         atomData;
			ResBondList           resBonds;
			HashCodeSet           resStructHashCodes;
			ResStructList         currGeneration;
			ResStructList         nextGeneration;
			Util::BitSet          tmpBitMask;
		};
    }
}

#endif // CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP
