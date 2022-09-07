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

			class StructureData
		    {

				friend class ResonanceStructureGenerator;

			  public:
				const Util::LArray& getAtomCharges() const;

				const Util::STArray& getBondOrders() const;

			  private:
				Util::LArray  atomCharges;
				Util::STArray bondOrders;
			};

			/**
			 * \brief Constructs the \c %ResonanceStructureGenerator instance.
			 */
			ResonanceStructureGenerator();

			ResonanceStructureGenerator(const ResonanceStructureGenerator& gen);

			virtual ~ResonanceStructureGenerator() {}

			ResonanceStructureGenerator& operator=(const ResonanceStructureGenerator& gen);
			
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

				double getElectronegativity() const;

				bool checkValenceState(const StructureData& res_struct, long val_diff, long charge_diff) const;

				bool getVisitedFlag() const;

				void setVisitedFlag();

			  private:
				typedef std::vector<std::size_t> IndexArray;

				bool         canShiftElecs;
				std::size_t  index;
				unsigned int atomType;
				long         valElecCount;
				std::size_t  unprdElecCount;
				std::size_t  implHCount;
				double       enegativity;
				IndexArray   bondIndices;
				IndexArray   atomIndices;
				bool         visited;
			};
			
			typedef std::vector<AtomData> AtomDataArray;
			typedef std::vector<BondData> BondDataList;

			void init(const MolecularGraph& molgraph);

			void createInputResStructData();

			void extractResBonds();
			void extractResBonds(AtomData& atom_data);

			void genStartResStructs();
			void genOutputResStructs();

			void modifyResStruct(StructureData& res_struct, const BondData& res_bond,
								 long bond_order_diff, long atom1_chg_diff, long atom2_chg_diff) const;

			StructureDataCache    resStructDataCache;
			const MolecularGraph* molGraph;
			AtomDataArray         atomData;
			BondDataList          resBonds;
			StructureData         inputResStruct;
			StructureDataList     startResStructs;
			StructureDataList     outputResStructs;
			Util::BitSet          tmpBitMask;
		};
    }
}

#endif // CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP
