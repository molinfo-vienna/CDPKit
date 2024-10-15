/* 
 * MMCIFDataWriter.hpp 
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


#ifndef CDPL_BIOMOL_MMCIFDATAWRITER_HPP
#define CDPL_BIOMOL_MMCIFDATAWRITER_HPP

#include <iosfwd>
#include <unordered_set>
#include <set>
#include <map>
#include <vector>
#include <utility>

#include <boost/ptr_container/ptr_vector.hpp>

#include "CDPL/Biomol/MMCIFData.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Biomol/MMCIFDataProcessingFunction.hpp"
#include "CDPL/Internal/StringUtilities.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }
    
    namespace Biomol
    {

        class MMCIFDataWriter
        {

          public:
            MMCIFDataWriter(const Base::DataIOBase& io_base);

            bool writeMolecularGraph(std::ostream& os, const Chem::MolecularGraph& molgraph);

          private:
            typedef std::unordered_set<const std::string*,
                                       Internal::StringPtrHashFunc,
                                       Internal::StringPtrCmpFunc>  AtomIDSet;
            struct Entity;
            struct ChemComp;
            
            void init(std::ostream& os);

            bool outputMacromolData(const Chem::MolecularGraph& molgraph);
            void outputEntryData();
            void outputEntityData();
            void outputEntityPolyData();
            void outputEntityPolySeqData();
            void outputStructConnData(const Chem::MolecularGraph& molgraph);
            void outputAtomTypeData();
            void outputAtomSiteData(const Chem::MolecularGraph& molgraph);
            void outputMacromolCompData();
            void outputMacromolCompAtomData();
            void outputMacromolCompBondData();
            
            bool prepAtomSiteData(const Chem::MolecularGraph& molgraph);
            void prepMacromolCompData();
            void prepStructConnData(const Chem::MolecularGraph& molgraph);
            void prepEntityData(const Chem::MolecularGraph& molgraph);

            void getEntityAtoms(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t model_no,
                                const std::string& chain_id);

            bool genEntityPolySeqStrings(const Entity& entity, std::string& olc_seq, std::string& can_olc_seq);

            const std::string& getPolymerEntityType(const Entity& entity);
            
            void outputChemCompData(const Chem::MolecularGraph& molgraph);
            void outputChemCompAtomData(const Chem::MolecularGraph& molgraph, const std::string& comp_id);
            void outputChemCompBondData(const Chem::MolecularGraph& molgraph, const std::string& comp_id);

            bool hasMissingLeavingAtomNbrs(const Chem::Atom& atom, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph);
            
            const ResidueDictionary& getResidueDictionary() const;

            ChemComp& getChemCompData(const std::string* comp_id);
            
            std::string getChemCompId(const Chem::MolecularGraph& molgraph);
            
            void setDataBlockId(const Chem::MolecularGraph& molgraph);

            const std::string& createUniqueAtomID(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                  const AtomIDSet& id_set, std::string& id) const;

            struct Entity
            {
             
                struct StringPtrLessCmpFunc
                {

                    bool operator()(const std::string* str1, const std::string* str2) const;
                };

                typedef std::pair<const std::string*, long>                ResidueID;
                typedef std::vector<ResidueID>                             ResidueIDList;
                typedef std::set<const std::string*, StringPtrLessCmpFunc> ChainIDSet;

                std::size_t        index;
                std::string        id;
                std::size_t        modelNo{0};
                std::size_t        count{1};
                double             weight{0.0};
                const std::string* type{nullptr};
                const std::string* srcMethod{nullptr};
                const std::string* descr{nullptr};
                ResidueIDList      resSequence;
                ChainIDSet         chains;
            };

            struct ChemComp
            {
                
                struct Atom
                {

                    Atom(const std::string* id, const std::string* alt_id, const std::string* sym,
                         unsigned int config, bool arom, std::size_t num_lvg_nbrs):
                        id(id), altId(alt_id), symbol(sym), config(config), aromatic(arom),
                        numLvgNbrs(num_lvg_nbrs)
                    {}

                    const std::string* id;
                    const std::string* altId;
                    const std::string* symbol;
                    unsigned int       config;
                    bool               aromatic;
                    std::size_t        numLvgNbrs;
                };
                
                struct Bond
                {

                    Bond(const std::string* atom1_id, const std::string* atom2_id, std::size_t order,
                         unsigned int config, bool arom):
                        atom1Id(atom1_id), atom2Id(atom2_id), order(order), config(config), aromatic(arom)
                    {}

                    const std::string* atom1Id;
                    const std::string* atom2Id;
                    std::size_t        order;
                    unsigned int       config;
                    int                aromatic;
                };
                
                typedef std::pair<const std::string*, const std::string*> BondID;

                struct BondIDHashFunc
                {

                    std::size_t operator()(const BondID& bond_id) const;
                };

                struct BondIDCmpFunc
                {

                    bool operator()(const BondID& bond_id1, const BondID& bond_id2) const;
                };
                
                typedef std::unordered_set<BondID,
                                           BondIDHashFunc, BondIDCmpFunc> BondIDSet;
                typedef std::vector<Atom>                                 AtomList;
                typedef std::vector<Bond>                                 BondList;
                typedef std::unique_ptr<ChemComp>                         Pointer;

                AtomList           atoms;
                AtomIDSet          linkAtomIds;
                AtomIDSet          leavingAtomIds;
                BondList           bonds;
                BondIDSet          bondIds;
                bool               unknown{true};
                bool               isStdRes{false};
                const std::string* name{nullptr};
                const std::string* parent{nullptr};
                const std::string* oneLetterCode{nullptr};
                unsigned int       type{0};
                std::string        formula;
                double             weight{-1.0};
            };

            struct CIStringPtrLessCmpFunc
            {

                bool operator()(const std::string* str1, const std::string* str2) const;
            };
            
            typedef boost::ptr_vector<Entity>                           EntityList;
            typedef std::map<const std::string*, ChemComp::Pointer,
                             CIStringPtrLessCmpFunc>                    ChemCompDictionary;
            typedef ResidueDictionary::SharedPointer                    ResDictPointer;
            typedef std::unordered_set<const Chem::Bond*>               BondSet;
            typedef std::set<std::string>                               StringSet;
            typedef std::vector<const Chem::Atom*>                      AtomList;
            typedef std::vector<std::size_t>                            UIntArray;
            
            const Base::DataIOBase&     ioBase;
            ResDictPointer              resDictionary;
            MMCIFDataProcessingFunction dataPostprocFunc;
            bool                        strictErrorChecking;
            MMCIFData                   mmCIFData;
            std::size_t                 numOutDataBlocks;
            bool                        outputAsChemComp;
            AtomList                    atomSites;
            ChemCompDictionary          chemCompDict;
            EntityList                  entities;
            AtomList                    entityAtoms;
            Entity::ResidueIDList       entityResSequence;
            UIntArray                   atomEntityIndices;
            UIntArray                   uniqueAtomResIds;
            BondSet                     disulfBonds;
            BondSet                     nonStdBonds;
            StringSet                   seenAtomTypes;
            AtomIDSet                   chemCompAtomIds[2];
            std::string                 tmpString;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATAWRITER_HPP
