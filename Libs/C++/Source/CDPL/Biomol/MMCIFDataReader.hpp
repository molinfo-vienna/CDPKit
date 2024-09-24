/* 
 * MMCIFDataReader.hpp 
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


#ifndef CDPL_BIOMOL_MMCIFDATAREADER_HPP
#define CDPL_BIOMOL_MMCIFDATAREADER_HPP

#include <istream>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>

#include "CDPL/Biomol/MMCIFData.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Internal/StringUtilities.hpp"


namespace CDPL
{

    namespace Base
    {

        class DataIOBase;
    }

    namespace Chem
    {

        class Molecule;
    }

    namespace Biomol
    {

        class MMCIFDataReader
        {

          public:
            MMCIFDataReader(const Base::DataIOBase& io_base);
            
            bool hasMoreData(std::istream& is);
            bool skipMolecule(std::istream& is);
            bool readMolecule(std::istream& is, Chem::Molecule& mol);

          private:
            enum Token : int;

            struct ChemComp;
            
            void init(std::istream&);
            void init(std::istream&, Chem::Molecule& mol);
            
            void readMacromolecule(const MMCIFData& data, Chem::Molecule& mol);

            void initChemCompDict(const MMCIFData& data);
            void procChemCompAtoms(const MMCIFData& data);
            void procChemCompBonds(const MMCIFData& data);

            void readAtomSites(const MMCIFData& data, Chem::Molecule& mol);
            void postprocAtomSites(Chem::Molecule& mol);
            void createNonStdInterResidueBonds(const MMCIFData& data, Chem::Molecule& mol) const;
            void applyDictionaryBondOrders(Chem::Molecule& mol);
            void setMacromoleculeName(const MMCIFData& data, Chem::Molecule& mol) const;

            Chem::Atom* getAtom(const MMCIFData& data, Chem::Molecule& mol,
                                const std::string* auth_asym_id, const std::string* auth_atom_id,
                                const std::string* auth_comp_id, const std::string* auth_seq_id,
                                const std::string* label_asym_id, const std::string* label_atom_id,
                                const std::string* label_comp_id, const std::string* label_seq_id,
                                const std::string* ins_code) const;
            
            const ResidueDictionary& getResidueDictionary() const;
            
            void getMissingChemCompLinkAtomsFromResDictStructs();
            void setupChemCompDataFromResDictStruct(ChemComp& chem_comp, const std::string& comp_id);
            
            ChemComp& getOrAddChemCompData(const std::string& comp_id);
            ChemComp& getChemCompData(const std::string& comp_id);
            
            void readChemComps(const MMCIFData& data, Chem::Molecule& mol);
            void readChemCompAtoms(const MMCIFData& data, Chem::Molecule& mol);
            bool readChemCompBonds(const MMCIFData& data, Chem::Molecule& mol);
            void postprocReadChemComps(const MMCIFData& data, Chem::Molecule& mol) const;

            void perceiveBondOrders(Chem::Molecule& mol);
            void calcAtomCharges(Chem::Molecule& mol);
            
            MMCIFData::SharedPointer parseInput(std::istream& is);

            void parseLoopSection(std::istream& is, MMCIFData& data);

            bool extractCategoryandItemNames(std::string& cat_name, std::string& item_name, bool strict) const;
  
            Token nextToken(std::istream& is);

            void putbackToken(std::istream& is) const;

            typedef std::pair<const std::string*, const std::string*> ChemCompAtomID;

            struct ChemCompAtomIDHash
            {

                std::size_t operator()(const ChemCompAtomID& atom_id) const;
            };

            struct ChemCompAtomIDCmpFunc
            {

                bool operator()(const ChemCompAtomID& atom_id1, const ChemCompAtomID& atom_id2) const;
            };

            struct ChemComp
            {
                
                struct Atom
                {

                    Atom(const std::string* id, const std::string* alt_id, long form_charge, unsigned int type, bool leaving_flag):
                        id(id), altId(alt_id), formCharge(form_charge), type(type), leavingFlag(leaving_flag)
                    {}

                    const std::string* id;
                    const std::string* altId;
                    long               formCharge;
                    unsigned int       type;
                    bool               leavingFlag;
                };
                
                struct Bond
                {

                    Bond(std::size_t atom_1_idx, std::size_t atom_2_idx, std::size_t order):
                        atom1Idx(atom_1_idx), atom2Idx(atom_2_idx), order(order)
                    {}

                    std::size_t atom1Idx;
                    std::size_t atom2Idx;
                    std::size_t order;
                };

                ChemComp& clear();
              
                bool hasAtom(const std::string& id) const;

                std::size_t getBondOrder(const std::string& atom_1_id, const std::string& atom_2_id) const;

                operator bool() const;

                typedef std::vector<Atom>     AtomList;
                typedef std::vector<Bond>     BondList;
                typedef std::set<std::size_t> LinkAtomSet;

                AtomList    atoms;
                BondList    bonds;
                LinkAtomSet linkAtoms;
            };

            typedef std::unordered_map<ChemCompAtomID, std::size_t,
                                       ChemCompAtomIDHash,
                                       ChemCompAtomIDCmpFunc>           ChemCompAtomLookupMap;
            typedef std::vector<ChemComp>                               ChemCompList;
            typedef std::unordered_map<std::string, std::size_t,
                                       Internal::CIStringHashFunc,
                                       Internal::CIStringCmpFunc>       ChemCompDictionary;
            typedef std::vector<Chem::Atom*>                            AtomList;
            typedef std::pair<Chem::Atom*, std::size_t>                 AtomIndexPair;
            typedef std::vector<AtomIndexPair>                          AtomIndexPairList;
            typedef std::unordered_map<const std::string*, Chem::Atom*,
                                       Internal::StringPtrHashFunc,
                                       Internal::StringPtrCmpFunc>      NameToAtomMap;
            typedef std::unordered_map<std::string, std::size_t>        BondOrderCache;
            typedef ResidueDictionary::SharedPointer                    ResDictPointer;

            const Base::DataIOBase& ioBase;
            std::istream::pos_type  lastStreamPos;
            std::string             tokenValue;
            bool                    strictErrorChecking;
            ResDictPointer          resDictionary;
            bool                    applyDictAtomBonding;
            bool                    applyDictBondOrders;
            bool                    applyDictAtomCharges;
            bool                    applyDictAtomTypes;
            bool                    calcCharges;
            bool                    perceiveOrders;
            bool                    combInterferingResCoords;
            ChemCompAtomLookupMap   chemCompAtomLookupMap;
            ChemCompList            chemCompList;
            ChemCompDictionary      chemCompDict;
            std::size_t             chemCompCount;
            std::size_t             startAtomCount;
            std::size_t             startBondCount;
            AtomIndexPairList       atomSites;
            NameToAtomMap           currResidueAtoms;
            AtomList                currResidueLinkAtoms;
            AtomList                prevResidueLinkAtoms;
            BondOrderCache          bondOrderCache;
            Chem::Fragment          readMolGraph;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATAREADER_HPP
