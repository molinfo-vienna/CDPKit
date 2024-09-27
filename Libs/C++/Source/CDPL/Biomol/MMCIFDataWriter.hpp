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
#include <unordered_map>
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
                                       Internal::StringPtrCmpFunc>  AtomIdSet;
            struct ChemComp;
            
            void init(std::ostream& os);

            bool outputMacromoleculeData(const Chem::MolecularGraph& molgraph);
            void outputEntryData();
            void outputEntityData();
            void outputAtomSiteData(const Chem::MolecularGraph& molgraph);
            void outputMacromoleculeCompData();
            void outputMacromoleculeCompAtomData();
            void outputMacromoleculeCompBondData();
            
            bool prepAtomSiteData(const Chem::MolecularGraph& molgraph);
            void prepEntityData(const Chem::MolecularGraph& molgraph);
            void prepMacromoleculeCompData(const Chem::MolecularGraph& molgraph);
            
            void getEntityAtoms(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, std::size_t model_no);
            
            void outputChemCompData(const Chem::MolecularGraph& molgraph);
            void outputChemCompAtomData(const Chem::MolecularGraph& molgraph, const std::string& comp_id);
            void outputChemCompBondData(const Chem::MolecularGraph& molgraph, const std::string& comp_id);

            const ResidueDictionary& getResidueDictionary() const;

            ChemComp& getChemCompData(const std::string& comp_id);
            
            std::string getChemCompId(const Chem::MolecularGraph& molgraph);
            
            void setDataBlockId(const Chem::MolecularGraph& molgraph);

            const std::string& createUniqueAtomId(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                  const AtomIdSet& id_set, std::string& id) const;

            typedef std::vector<const std::string*> StringPtrList;

            struct Entity
            {

                std::size_t   id{0};
                std::size_t   modelNo{0};
                std::size_t   count{1};
                double        weight{0.0};
                std::string   type;
                std::string   srcMethod;
                std::string   descr;
                StringPtrList resSequence;
            };

            struct ChemComp
            {
                
                struct Atom
                {

                    Atom(const std::string* id, unsigned int type, unsigned int config, int aromatic):
                        id(id), type(type), config(config), aromatic(aromatic)
                    {}

                    const std::string* id;
                    unsigned int       type;
                    unsigned int       config;
                    int                aromatic;
                };
                
                struct Bond
                {

                    Bond(const std::string* atom_1_id, const std::string* atom_2_id, std::size_t order,
                         unsigned int config, int aromatic):
                        atom1Id(atom_1_id), atom2Id(atom_2_id), order(order), config(config), aromatic(aromatic)
                    {}

                    const std::string* atom1Id;
                    const std::string* atom2Id;
                    std::size_t        order;
                    unsigned int       config;
                    int                aromatic;
                };

                void addAtom(const Chem::Atom& atom);
                void addBond(const Chem::Bond& bond);
                
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
                                           BondIDHashFunc, BondIDCmpFunc> BondIdSet;
                typedef std::vector<Atom>                                 AtomList;
                typedef std::vector<Bond>                                 BondList;
                typedef std::unique_ptr<ChemComp>                         Pointer;
                
                AtomList    atoms;
                AtomIdSet   atomIds;
                BondList    bonds;
                BondIdSet   bondIds;
            };

            typedef boost::ptr_vector<Entity>                           EntityList;
            typedef std::unordered_map<std::string, ChemComp::Pointer,
                                       Internal::CIStringHashFunc,
                                       Internal::CIStringCmpFunc>       ChemCompDictionary;
            typedef ResidueDictionary::SharedPointer                    ResDictPointer;
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
            StringPtrList               entityResSequence;
            UIntArray                   atomEntityIds;
            AtomIdSet                   chemCompAtomIds[2];
            std::string                 tmpString;
        };
    } // namespace Biomol
} // namespace CDPL

#endif // CDPL_BIOMOL_MMCIFDATAWRITER_HPP
