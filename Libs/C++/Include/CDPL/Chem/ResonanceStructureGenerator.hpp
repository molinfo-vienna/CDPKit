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
 * \brief Definition of class CDPL::Chem::ResonanceStructureGenerator.
 */

#ifndef CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP
#define CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP

#include <vector>
#include <cstddef>
#include <unordered_set>
#include <memory>

#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
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
         * \brief Enumerates the resonance structures of a molecular graph by redistributing &pi;-electrons across the
         *        resonance-active bonds.
         *
         * For each generated resonance structure the per-atom formal charges and per-bond orders are reported as a
         * Chem::ResonanceStructureGenerator::StructureData record. Optional postprocessing minimizes octet-rule
         * violations, sp-hybridization-geometry violations, and 1,2-charge separations on adjacent carbon atoms.
         */
        class CDPL_CHEM_API ResonanceStructureGenerator
        {

          public:
            class StructureData;

          private:
            typedef Util::ObjectPool<StructureData>         StructureDataCache;
            typedef StructureDataCache::SharedObjectPointer StructureDataPtr;
            typedef std::vector<StructureDataPtr>           StructureDataList;

          public:
            /**
             * \brief A reference-counted smart pointer [\ref SHPTR] for dynamically allocated \c %ResonanceStructureGenerator instances.
             */
            typedef std::shared_ptr<ResonanceStructureGenerator>                                     SharedPointer;

            /**
             * \brief A constant iterator over the generated resonance-structure records.
             */
            typedef boost::indirect_iterator<StructureDataList::const_iterator, const StructureData> ConstStructureDataIterator;

            /**
             * \brief Holds the per-atom formal charges and per-bond orders that define a single resonance structure.
             */
            class CDPL_CHEM_API StructureData
            {

                friend class ResonanceStructureGenerator;

              public:
                /**
                 * \brief Returns the per-atom formal charges of this resonance structure.
                 * \return A \c const reference to the per-atom formal charge array.
                 */
                const Util::LArray& getAtomCharges() const;

                /**
                 * \brief Returns the bond orders of this resonance structure.
                 * \return A \c const reference to the bond order array.
                 */
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

            /**
             * \brief Constructs a copy of the \c %ResonanceStructureGenerator instance \a gen.
             * \param gen The \c %ResonanceStructureGenerator to copy.
             */
            ResonanceStructureGenerator(const ResonanceStructureGenerator& gen);

            /**
             * \brief Virtual destructor.
             */
            virtual ~ResonanceStructureGenerator() {}

            /**
             * \brief Replaces the state of this generator by a copy of the state of \a gen.
             * \param gen The source \c %ResonanceStructureGenerator.
             * \return A reference to itself.
             */
            ResonanceStructureGenerator& operator=(const ResonanceStructureGenerator& gen);

            /**
             * \brief Returns the bit mask of atom types subjected to the octet-rule check during minimization.
             * \return A reference to the bit mask (indexed by Chem::AtomType value).
             */
            Util::BitSet& getOctetRuleCheckAtomTypes();

            /**
             * \brief Returns the bit mask of atom types subjected to the octet-rule check during minimization.
             * \return A \c const reference to the bit mask (indexed by Chem::AtomType value).
             */
            const Util::BitSet& getOctetRuleCheckAtomTypes() const;

            /**
             * \brief Specifies whether resonance structures violating the octet rule shall be filtered out.
             * \param minimize If \c true, structures with octet-rule violations on the configured atom types are minimized.
             */
            void minimizeOctetRuleViolations(bool minimize);

            /**
             * \brief Tells whether octet-rule violations are minimized.
             * \return \c true if octet-rule violations are minimized, and \c false otherwise.
             */
            bool octetRuleViolationsMinimized() const;

            /**
             * \brief Specifies whether resonance structures with sp-hybridization-geometry violations shall be filtered out.
             * \param minimize If \c true, sp-hybridization-geometry violations are minimized.
             */
            void minimizeSP1GeometryViolations(bool minimize);

            /**
             * \brief Tells whether sp-hybridization-geometry violations are minimized.
             * \return \c true if sp-geometry violations are minimized, and \c false otherwise.
             */
            bool sp1GeometryViolationsMinimized() const;

            /**
             * \brief Specifies whether resonance structures with 1,2-charge separations on adjacent carbon atoms shall be filtered out.
             * \param minimize If \c true, 1,2-charged C&minus;C resonance forms are minimized.
             */
            void minimizeCarbonBond12Charges(bool minimize);

            /**
             * \brief Tells whether 1,2-charge separations on adjacent carbon atoms are minimized.
             * \return \c true if 1,2-charged C&minus;C resonance forms are minimized, and \c false otherwise.
             */
            bool carbonBond12ChargesMinimized() const;

            /**
             * \brief Sets the maximum allowed difference between the lowest and highest formal charge count of accepted resonance structures.
             * \param win_size The new charge-count window size.
             */
            void setChargeCountWindow(std::size_t win_size);

            /**
             * \brief Returns the configured charge-count window size.
             * \return The charge-count window size.
             */
            std::size_t getChargeCountWindow() const;

            /**
             * \brief Sets the upper limit on the number of resonance structures generated per molecule.
             * \param max_num The new output-structure limit.
             */
            void setMaxNumGeneratedStructures(std::size_t max_num);

            /**
             * \brief Returns the upper limit on the number of resonance structures generated per molecule.
             * \return The output-structure limit.
             */
            std::size_t getMaxNumGeneratedStructures() const;

            /**
             * \brief Generates all unique resonance structures of the molecular graph \a molgraph.
             * \param molgraph The molecular graph for which to generate the resonance structures.
             */
            void generate(const MolecularGraph& molgraph);

            /**
             * \brief Returns the number of generated resonance structures.
             * \return The resonance-structure count.
             */
            std::size_t getNumStructures() const;

            /**
             * \brief Returns the resonance-structure record at index \a idx.
             * \param idx The zero-based structure index.
             * \return A \c const reference to the resonance-structure record.
             * \throw Base::IndexError if \a idx is not in the range [0, getNumStructures()).
             */
            const StructureData& getStructureData(std::size_t idx) const;

            /**
             * \brief Returns a constant iterator pointing to the first generated resonance-structure record.
             * \return A constant iterator pointing to the first record.
             */
            ConstStructureDataIterator getStructureDataBegin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last generated resonance-structure record.
             * \return A constant iterator pointing one past the last record.
             */
            ConstStructureDataIterator getStructureDataEnd() const;

            /**
             * \brief Returns a constant iterator pointing to the first generated record (range-based for support).
             * \return A constant iterator pointing to the first record.
             */
            ConstStructureDataIterator begin() const;

            /**
             * \brief Returns a constant iterator pointing one past the last generated record (range-based for support).
             * \return A constant iterator pointing one past the last record.
             */
            ConstStructureDataIterator end() const;

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

                bool operator()(const StructureDataPtr& rs_ptr1, const StructureDataPtr& rs_ptr2) const
                {
                    return (rs_ptr1->getBondOrders() == rs_ptr2->getBondOrders() &&
                            rs_ptr1->getAtomCharges() == rs_ptr2->getAtomCharges());
                }
            };

            typedef std::vector<AtomData>                                                                   AtomDataArray;
            typedef std::vector<const AtomData*>                                                            AtomDataPtrArray;
            typedef std::vector<BondData>                                                                   BondDataList;
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

            void minimzeResStructProperty(std::size_t (ResonanceStructureGenerator::*prop_func)(const StructureData&) const);

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
    } // namespace Chem
} // namespace CDPL

#endif // CDPL_CHEM_RESONANCESTRUCTUREGENERATOR_HPP
