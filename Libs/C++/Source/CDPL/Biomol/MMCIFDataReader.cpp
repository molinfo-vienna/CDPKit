/* 
 * MMCIFDataReader.cpp 
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


#include "StaticInit.hpp"

#include <locale>
#include <cassert>
#include <stdexcept>
#include <algorithm>

#include <boost/functional/hash.hpp>

#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/MoleculeFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ComponentSet.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "MMCIFDataReader.hpp"
#include "MMCIFFormatData.hpp"


using namespace CDPL;


namespace
{

    inline std::string getFQItemName(const Biomol::MMCIFData::Category* cat, const Biomol::MMCIFData::Item* item)
    {
        return ('_' + cat->getName() + '.' + item->getName());
    }
    
    void throwFormatError(const Biomol::MMCIFData::Category* cat, const Biomol::MMCIFData::Item* item, std::size_t row_idx)
    {
        if (item->getNumValues() == 1)
            throw Base::IOError("MMCIFDataReader: " + getFQItemName(cat, item) + ": invalid value format");
        else
            throw Base::IOError("MMCIFDataReader: " + getFQItemName(cat, item) +
                                ": invalid value format at data row " + std::to_string(row_idx));
    }

    void throwRangeError(const Biomol::MMCIFData::Category* cat, const Biomol::MMCIFData::Item* item, std::size_t row_idx)
    {
        if (item->getNumValues() == 1)
            throw Base::IOError("MMCIFDataReader: " + getFQItemName(cat, item) + ": value out of range");
        else
            throw Base::IOError("MMCIFDataReader: " + getFQItemName(cat, item) +
                                ": value at data row " + std::to_string(row_idx) + " out of range");
    }

    inline void convert(const std::string& val_str, double& value, std::size_t& end_pos)
    {
        value = std::stod(val_str, &end_pos);
    }

    inline void convert(const std::string& val_str, std::size_t& value, std::size_t& end_pos)
    {
        value = std::stoul(val_str, &end_pos);
    }

    inline void convert(const std::string& val_str, long& value, std::size_t& end_pos)
    {
        value = std::stol(val_str, &end_pos);
    }

    inline void convert(const std::string& val_str, bool& value, std::size_t& end_pos)
    {
        using namespace Biomol;
        
        if (Internal::isEqualCI(val_str, MMCIF::TRUE_FLAG)) {
            value = true;
            end_pos = MMCIF::TRUE_FLAG.length();
            
        } else if (Internal::isEqualCI(val_str, MMCIF::FALSE_FLAG)) {
            value = false;
            end_pos = MMCIF::FALSE_FLAG.length();

        } else
            end_pos = std::string::npos;
    }

    inline bool valUndefOrMissing(const std::string& val_str)
    {
        using namespace Biomol;

        return (val_str == MMCIF::UNDEFINED_DATA_VALUE || val_str == MMCIF::MISSING_DATA_VALUE);
    }

    inline const std::string* getValue(const Biomol::MMCIFData::Item* item, std::size_t row_idx)
    {
        if (!item)
            return nullptr;

        auto& val = item->getValue(row_idx);

        if (valUndefOrMissing(val))
            return nullptr;

        return &val;
    }

    inline bool valuesMatch(const std::string* query_val, const Biomol::MMCIFData::Item* item, std::size_t row_idx)
    {
        if (!query_val)
            return true;
        
        if (!item)
            return false;
     
        return (*query_val == item->getValue(row_idx));
    }
    
    template <typename T>
    bool getValue(const Biomol::MMCIFData::Category* cat, const Biomol::MMCIFData::Item* item, std::size_t row_idx, T& value)
    {
        using namespace Biomol;

        if (!item)
            return false;
        
        auto& val_str = item->getValue(row_idx);

        if (valUndefOrMissing(val_str))
            return false;
        
        try {
            std::size_t end_pos;

            convert(val_str, value, end_pos);

            if (end_pos != val_str.length())
                throwFormatError(cat, item, row_idx);
            
        } catch (const std::invalid_argument& e) {
            throwFormatError(cat, item, row_idx);

        } catch (const std::out_of_range & e) {
            throwRangeError(cat, item, row_idx);
        }

        return true;
    }

    const Biomol::MMCIFData::Item* select(const Biomol::MMCIFData::Item* item1, const Biomol::MMCIFData::Item* item2)
    {
        if (!item1)
            return item2;

        if (!item2)
            return item1;

        std::size_t num_undef1 = 0;
        std::size_t num_undef2 = 0;

        for (std::size_t i = 0, num_values = item1->getNumValues(); i < num_values; i++) {
            if (valUndefOrMissing(item1->getValue(i)))
                num_undef1++;

            if (valUndefOrMissing(item2->getValue(i)))
                num_undef2++;
        }

        if (num_undef1 <= num_undef2)
            return item1;

        return item2;
    }
    
    constexpr double MIN_BOND_LENGTH       = 0.4;
    constexpr double BOND_LENGTH_TOLERANCE = 0.4;
}


enum Biomol::MMCIFDataReader::Token : int
{
    EOI = 0,
    PLAIN_STRING,
    QUOTED_STRING,
    TEXT_FIELD
};


Biomol::MMCIFDataReader::ChemComp& Biomol::MMCIFDataReader::ChemComp::clear()
{
    atoms.clear();
    bonds.clear();
    linkAtoms.clear();

    return *this;
}

bool Biomol::MMCIFDataReader::ChemComp::hasAtom(const std::string& id) const
{
    for (auto& atom : atoms) {
        if (atom.id && (*atom.id == id))
            return true;

        if (atom.altId && (*atom.altId == id))
            return true;
    }

    return false;
}

std::size_t Biomol::MMCIFDataReader::ChemComp::getBondOrder(const std::string& atom_1_id, const std::string& atom_2_id) const
{
    for (auto& bond : bonds) {
        auto& bond_beg = atoms[bond.atom1Idx];
        auto& bond_end = atoms[bond.atom2Idx];

        auto bond_beg_atom_1_match = (bond_beg.id && (*bond_beg.id == atom_1_id)) || (bond_beg.altId && (*bond_beg.altId == atom_1_id));
        auto bond_end_atom_2_match = (bond_end.id && (*bond_end.id == atom_2_id)) || (bond_end.altId && (*bond_end.altId == atom_2_id));

        if (bond_beg_atom_1_match && bond_end_atom_2_match)
            return bond.order;

        auto bond_end_atom_1_match = (bond_end.id && (*bond_end.id == atom_1_id)) || (bond_end.altId && (*bond_end.altId == atom_1_id));
        auto bond_beg_atom_2_match = (bond_beg.id && (*bond_beg.id == atom_2_id)) || (bond_beg.altId && (*bond_beg.altId == atom_2_id));

        if (bond_end_atom_1_match && bond_beg_atom_2_match)
            return bond.order;
    }

    return 0;
}

Biomol::MMCIFDataReader::ChemComp::operator bool() const
{
    return !atoms.empty();
}


std::size_t Biomol::MMCIFDataReader::ChemCompAtomIDHash::operator()(const ChemCompAtomID& atom_id) const
{
    std::size_t h = 0;

    if (atom_id.first)
        boost::hash_combine(h, *atom_id.first);

    boost::hash_combine(h, *atom_id.second);

    return h;
}


bool Biomol::MMCIFDataReader::ChemCompAtomIDCmpFunc::operator()(const ChemCompAtomID& atom_id1, const ChemCompAtomID& atom_id2) const
{
    return (*atom_id1.first == *atom_id2.first && *atom_id1.second == *atom_id2.second);
}


std::size_t Biomol::MMCIFDataReader::StringPtrHash::operator()(const std::string* str_ptr) const
{
    if (!str_ptr)
        return 0;

    return std::hash<std::string>{}(*str_ptr);
}


bool Biomol::MMCIFDataReader::StringPtrCmpFunc::operator()(const std::string* str_ptr1, const std::string* str_ptr2) const
{
    if (!str_ptr1)
        return !str_ptr2;

    if (!str_ptr2)
        return false;

    return (*str_ptr1 == *str_ptr2);
}


bool Biomol::MMCIFDataReader::hasMoreData(std::istream& is)
{
    init(is);

    while (auto token = nextToken(is)) {
        if (token == PLAIN_STRING && Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX)) {
            putbackToken(is);
            return true;
        }            
    }
  
    return false;
}

bool Biomol::MMCIFDataReader::skipMolecule(std::istream& is)
{
    init(is);
    
    while (auto token = nextToken(is)) {
        if (token == PLAIN_STRING && Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX))
            return true;
    }
    
    return false;
}

bool Biomol::MMCIFDataReader::readMolecule(std::istream& is, Chem::Molecule& mol)
{
    init(is, mol);

    auto data = parseInput(is);

    if (!data)
        return false;

    if (data->findCategory(MMCIF::AtomSite::NAME))
        readMacromolecule(*data, mol);
    else if (data->findCategory(MMCIF::ChemComp::NAME))
        readChemComps(*data, mol);
        
    setMMCIFData(mol, data);

    if (startAtomCount == 0 && !hasName(mol))
        setName(mol, data->getID());
    
    return true;
}

void Biomol::MMCIFDataReader::init(std::istream& is)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);

    is.imbue(std::locale::classic());
}

void Biomol::MMCIFDataReader::init(std::istream& is, Chem::Molecule& mol)
{
    init(is);

    resDictionary            = getResidueDictionaryParameter(ioBase);
    applyDictAtomBonding     = getMMCIFApplyDictAtomBondingParameter(ioBase);
    applyDictBondOrders      = getMMCIFApplyDictBondOrdersParameter(ioBase);
    applyDictAtomCharges     = getApplyDictFormalChargesParameter(ioBase);
    applyDictAtomTypes       = getApplyDictAtomTypesParameter(ioBase);
    calcCharges              = getCalcMissingFormalChargesParameter(ioBase);
    perceiveOrders           = getPerceiveMissingBondOrdersParameter(ioBase);
    combInterferingResCoords = getCombineInterferingResidueCoordinatesParameter(ioBase);

    startAtomCount = mol.getNumAtoms();
    startBondCount = mol.getNumBonds();
}

void Biomol::MMCIFDataReader::readMacromolecule(const MMCIFData& data, Chem::Molecule& mol)
{
    initChemCompDict(data);
    readAtomSites(data, mol);
    postprocAtomSites(mol);
    createNonStdInterResidueBonds(data, mol);

    if (combInterferingResCoords)
        combineInterferingResidueCoordinates(mol);

    applyDictionaryBondOrders(mol);
    perceiveBondOrders(mol);
    calcAtomCharges(mol);
    setMacromoleculeName(data, mol);
}

void Biomol::MMCIFDataReader::initChemCompDict(const MMCIFData& data)
{
    procChemCompAtoms(data);
    procChemCompBonds(data);
    getMissingChemCompLinkAtomsFromResDictStructs();
}

void Biomol::MMCIFDataReader::procChemCompAtoms(const MMCIFData& data)
{
    using namespace MMCIF;

    chemCompAtomLookupMap.clear();
    chemCompDict.clear();

    chemCompCount = 0;
    
    auto comp_atoms = data.findCategory(ChemCompAtom::NAME);

    if (!comp_atoms)
        return;

    auto num_atoms = comp_atoms->getNumValueRows();

    if (num_atoms == 0)
        return;

    auto comp_ids = comp_atoms->findItem(ChemCompAtom::Item::COMP_ID);
    auto ids = comp_atoms->findItem(ChemCompAtom::Item::ATOM_ID);
    auto alt_ids = comp_atoms->findItem(ChemCompAtom::Item::ALT_ATOM_ID);
    auto type_syms = comp_atoms->findItem(ChemCompAtom::Item::TYPE_SYMBOL);
    auto leaving_flags = comp_atoms->findItem(ChemCompAtom::Item::PDBX_LEAVING_ATOM_FLAG);
    auto form_charges = comp_atoms->findItem(ChemCompAtom::Item::CHARGE);
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        auto* comp_id = getValue(comp_ids, i);
        
        if (!comp_id)
            continue;

        auto* id = getValue(ids, i);

        if (!id)
            continue;

        auto& comp = getOrAddChemCompData(*comp_id);
        auto* alt_id = getValue(alt_ids, i);
        auto atom_type = Chem::AtomType::UNKNOWN;
        
        if (auto* type_sym = getValue(type_syms, i)) {
            atom_type = Chem::AtomDictionary::getType(*type_sym);

            if (strictErrorChecking && atom_type == Chem::AtomType::UNKNOWN)
                throw Base::IOError("MMCIFDataReader: " + getFQItemName(comp_atoms, type_syms) +
                                    ": unknown atom type symbol '" + *type_sym +
                                    (num_atoms > 1 ? "' at data row " + std::to_string(i) : std::string("'")));
        }

        long form_charge = 0;
        bool leaving_flag = false;
        
        getValue(comp_atoms, form_charges, i, form_charge);
        getValue(comp_atoms, leaving_flags, i, leaving_flag);

        chemCompAtomLookupMap.emplace(ChemCompAtomID{comp_id, id}, comp.atoms.size());

        comp.atoms.emplace_back(id, alt_id, form_charge, atom_type, leaving_flag);
    }
}

void Biomol::MMCIFDataReader::procChemCompBonds(const MMCIFData& data)
{
    using namespace MMCIF;
    
    auto comp_bonds = data.findCategory(ChemCompBond::NAME);

    if (!comp_bonds)
        return;

    auto num_bonds = comp_bonds->getNumValueRows();

    if (num_bonds == 0)
        return;

    auto comp_ids = comp_bonds->findItem(ChemCompBond::Item::COMP_ID);
    auto atom_ids_1 = comp_bonds->findItem(ChemCompBond::Item::ATOM_ID_1);
    auto atom_ids_2 = comp_bonds->findItem(ChemCompBond::Item::ATOM_ID_2);
    auto orders = comp_bonds->findItem(ChemCompBond::Item::ORDER);
    
    for (std::size_t i = 0; i < num_bonds; i++) {
        auto* comp_id = getValue(comp_ids, i);

        if (!comp_id)
            continue;

        auto it = chemCompDict.find(*comp_id);

        if (it == chemCompDict.end())
            continue;
        
        auto* atom_id_1 = getValue(atom_ids_1, i);

        if (!atom_id_1)
            continue;

        auto* atom_id_2 = getValue(atom_ids_2, i);

        if (!atom_id_2)
            continue;

        auto it1 = chemCompAtomLookupMap.find({comp_id, atom_id_1});

        if (it1 == chemCompAtomLookupMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find atom with id '" + *atom_id_1 + "' specified in _" + comp_bonds->getName() +
                                    (num_bonds > 1 ? " data at row " + std::to_string(i) : std::string(" data")));

            continue;
        }

        auto it2 = chemCompAtomLookupMap.find({comp_id, atom_id_2});

        if (it2 == chemCompAtomLookupMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find atom with id '" + *atom_id_2 + "' specified in _" + comp_bonds->getName() +
                                    (num_bonds > 1 ? " data at row " + std::to_string(i) : std::string(" data")));

            continue;
        }

        std::size_t order = 0;

        if (auto* order_str = getValue(orders, i)) {
            if (Internal::isEqualCI(*order_str, ChemCompBond::Order::SINGLE))
                order = 1;

            else if (Internal::isEqualCI(*order_str, ChemCompBond::Order::DOUBLE))
                order = 2;

            else if (Internal::isEqualCI(*order_str, ChemCompBond::Order::TRIPLE))
                order = 3;

            else if (strictErrorChecking &&
                     !Internal::isEqualCI(*order_str, ChemCompBond::Order::AROMATIC) &&
                     !Internal::isEqualCI(*order_str, ChemCompBond::Order::DELOCALIZED) &&
                     !Internal::isEqualCI(*order_str, ChemCompBond::Order::PI) &&
                     !Internal::isEqualCI(*order_str, ChemCompBond::Order::POLYMERIC) &&
                     !Internal::isEqualCI(*order_str, ChemCompBond::Order::QUADRUPLE))

                throw Base::IOError("MMCIFDataReader: " + getFQItemName(comp_bonds, orders) +
                                    ": invalid bond order specification '" + *order_str +
                                    (num_bonds > 1 ? "' at data row " + std::to_string(i) : std::string("'")));
        } else
            order = 1;

        auto& comp = chemCompList[it->second];
        auto atom_1_idx = it1->second;
        auto atom_2_idx = it2->second;
                          
        comp.bonds.emplace_back(atom_1_idx, atom_2_idx, order);

        if (comp.atoms[atom_1_idx].leavingFlag ^ comp.atoms[atom_2_idx].leavingFlag)
            comp.linkAtoms.insert(comp.atoms[atom_1_idx].leavingFlag ? atom_2_idx : atom_1_idx);
    }
}

void Biomol::MMCIFDataReader::readAtomSites(const MMCIFData& data, Chem::Molecule& mol)
{
    using namespace MMCIF;

    atomSiteSequence.clear();
    
    auto atom_sites = data.findCategory(AtomSite::NAME);

    if (!atom_sites)
        return;

    auto num_atoms = atom_sites->getNumValueRows();

    if (num_atoms == 0)
        return;

    auto pdb_groups = atom_sites->findItem(AtomSite::Item::GROUP_PDB);
    auto serial_nos = atom_sites->findItem(AtomSite::Item::ID);
    auto type_syms = atom_sites->findItem(AtomSite::Item::TYPE_SYMBOL);
    auto atom_alt_ids = atom_sites->findItem(AtomSite::Item::LABEL_ALT_ID);
    auto atom_ids = select(atom_sites->findItem(AtomSite::Item::AUTH_ATOM_ID), atom_sites->findItem(AtomSite::Item::LABEL_ATOM_ID));
    auto comp_ids = select(atom_sites->findItem(AtomSite::Item::AUTH_COMP_ID), atom_sites->findItem(AtomSite::Item::LABEL_COMP_ID));
    auto res_seq_nos = select(atom_sites->findItem(AtomSite::Item::AUTH_SEQ_ID), atom_sites->findItem(AtomSite::Item::LABEL_SEQ_ID));
    auto chain_ids = select(atom_sites->findItem(AtomSite::Item::AUTH_ASYM_ID), atom_sites->findItem(AtomSite::Item::LABEL_ASYM_ID));
    auto ins_codes = atom_sites->findItem(AtomSite::Item::PDBX_PDB_INS_CODE);
    auto coords_x = atom_sites->findItem(AtomSite::Item::COORDS_X);
    auto coords_y = atom_sites->findItem(AtomSite::Item::COORDS_Y);
    auto coords_z = atom_sites->findItem(AtomSite::Item::COORDS_Z);
    auto occupancies = atom_sites->findItem(AtomSite::Item::OCCUPANCY);
    auto b_factors = atom_sites->findItem(AtomSite::Item::B_ISO_OR_EQUIV);
    auto form_charges = atom_sites->findItem(AtomSite::Item::PDBX_FORMAL_CHARGE);
    auto model_nos = atom_sites->findItem(AtomSite::Item::PDBX_PDB_MODEL_NUM);

    Math::Vector3D coords;
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        auto& atom = mol.addAtom();

        atomSiteSequence.emplace_back(&atom, i);
        
        auto comp_id = getValue(comp_ids, i);

        if (comp_id)
            setResidueCode(atom, *comp_id);
        
        if (auto pdb_group = getValue(pdb_groups, i)) {
            if (Internal::isEqualCI(*pdb_group, AtomSite::PDBGroup::ATOM))
                setHeteroAtomFlag(atom, false);

            else if (Internal::isEqualCI(*pdb_group, AtomSite::PDBGroup::HET_ATOM))
                setHeteroAtomFlag(atom, true);

            else if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: " + getFQItemName(atom_sites, pdb_groups) +
                                    ": invalid PDB atom group specification '" + *pdb_group +
                                    (num_atoms > 1 ? "' at data row " + std::to_string(i) : std::string("'")));
            else
                setHeteroAtomFlag(atom, comp_id ? !ResidueDictionary::isStdResidue(*comp_id) : true);

        } else
            setHeteroAtomFlag(atom, comp_id ? !ResidueDictionary::isStdResidue(*comp_id) : true);

        if (auto atom_id = getValue(atom_ids, i))
            setResidueAtomName(atom, *atom_id);

        if (auto atom_id = getValue(atom_alt_ids, i))
            setResidueAltAtomName(atom, *atom_id);
       
        long serial_no = 0;

        if (getValue(atom_sites, serial_nos, i, serial_no))
            setSerialNumber(atom, serial_no);

        long res_seq_no = 0;

        if (getValue(atom_sites, res_seq_nos, i, res_seq_no))
            setResidueSequenceNumber(atom, res_seq_no);

        if (auto chain_id = getValue(chain_ids, i))
            setChainID(atom, *chain_id);

        if (auto ins_code = getValue(ins_codes, i)) {
            if (ins_code->length() == 1)
                setResidueInsertionCode(atom, (*ins_code)[0]);

            else if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: " + getFQItemName(atom_sites, type_syms) +
                                    ": invalid residue insertion code" +
                                    (num_atoms > 1 ? "' at data row " + std::to_string(i) : std::string("'")));
        }
        
        if (auto* type_sym = getValue(type_syms, i)) {
            auto atom_type = Chem::AtomDictionary::getType(*type_sym);

            if (atom_type == Chem::AtomType::UNKNOWN) {
                if (strictErrorChecking)
                    throw Base::IOError("MMCIFDataReader: " + getFQItemName(atom_sites, type_syms) +
                                        ": unknown atom type symbol '" + *type_sym +
                                        (num_atoms > 1 ? "' at data row " + std::to_string(i) : std::string("'")));

                setSymbol(atom, *type_sym);
                
            } else
                setSymbol(atom, Chem::AtomDictionary::getSymbol(atom_type));

            setType(atom, atom_type);
        }
        
        long form_charge = 0;
        
        if (getValue(atom_sites, form_charges, i, form_charge))
            setFormalCharge(atom, form_charge);
        
        if (getValue(atom_sites, coords_x, i, coords[0]) &&
            getValue(atom_sites, coords_y, i, coords[1]) &&
            getValue(atom_sites, coords_z, i, coords[2]))

            set3DCoordinates(atom, coords);

        std::size_t model_no = 0;

        if (getValue(atom_sites, model_nos, i, model_no))
            setModelNumber(atom, model_no);

        double occup = 0.0;

        if (getValue(atom_sites, occupancies, i, occup))
            setOccupancy(atom, occup);

        double b_fact = 0.0;

        if (getValue(atom_sites, b_factors, i, b_fact))
            setBFactor(atom, b_fact);
    }
}

void Biomol::MMCIFDataReader::postprocAtomSites(Chem::Molecule& mol)
{
    using namespace Chem;

    if (atomSiteSequence.empty())
        return;

    prevResidueLinkAtoms.clear();

    for (auto as_it = atomSiteSequence.begin(), as_end = atomSiteSequence.end(); as_it != as_end; ) {
        auto first_atom = as_it->first;
        auto res_id = getResidueSequenceNumber(*first_atom) * (1 << (sizeof(char) * 8)) + getResidueInsertionCode(*first_atom);
        auto& res_code = getResidueCode(*first_atom);
        auto& chain_id = getChainID(*first_atom);

        currResidueAtoms.clear();
        currResidueLinkAtoms.clear();

        auto res_as_start_it = as_it;

        for (++as_it; as_it != as_end; ++as_it) {
            auto next_atom = as_it->first;

            auto& next_chain_id = getChainID(*next_atom);

            if (next_chain_id != chain_id)
                break;

            auto& next_res_code = getResidueCode(*next_atom);

            if (next_res_code != res_code)
                break;

            auto next_res_id = getResidueSequenceNumber(*next_atom) * (1 << (sizeof(char) * 8)) + getResidueInsertionCode(*next_atom);

            if (next_res_id != res_id)
                break;
        }

        std::sort(res_as_start_it, as_it, [](const AtomIndexPair& atom1, const AtomIndexPair& atom2) {
                                              auto& res_atom_name1 = getResidueAtomName(*atom1.first);
                                              auto& res_atom_name2 = getResidueAtomName(*atom2.first);

                                              if (res_atom_name1 == res_atom_name2)
                                                  return ((hasAltLocationID(*atom1.first) ? getAltLocationID(*atom1.first) : ' ') <
                                                          (hasAltLocationID(*atom2.first) ? getAltLocationID(*atom2.first) : ' '));
    
                                              return (res_atom_name1 < res_atom_name2);
                                          });

        for (auto res_as_it = res_as_start_it; res_as_it != as_it; ) {
            auto atom = res_as_it->first;
            auto& atom_name = getResidueAtomName(*atom);
            auto alt_loc_id = (hasAltLocationID(*atom) ? getAltLocationID(*atom) : ' ');
            Math::Vector3DArray::SharedPointer coords;
            
            currResidueAtoms[&atom_name] = atom;

            for (++res_as_it; res_as_it != as_it; ++res_as_it) {
                auto next_atom = res_as_it->first;
                auto& next_atom_name = getResidueAtomName(*next_atom);

                if (next_atom_name != atom_name)
                    break;

                if ((hasAltLocationID(*next_atom) ? getAltLocationID(*next_atom) : ' ') == alt_loc_id)
                    break;

                if (!coords) {
                    coords.reset(new Math::Vector3DArray());
                    coords->addElement(get3DCoordinates(*atom));                    
                }

                coords->addElement(get3DCoordinates(*next_atom));

                mol.removeAtom(next_atom->getIndex());
            }

            if (coords)
                set3DCoordinatesArray(*atom, coords);
        }

        auto& chem_comp = getChemCompData(res_code);

        if (applyDictAtomTypes || applyDictAtomCharges) {
            for (auto& atom : chem_comp.atoms) {
                auto res_atom = currResidueAtoms[atom.id];

                if (!res_atom)
                    res_atom = currResidueAtoms[atom.altId];

                if (!res_atom)
                    continue;

                if (applyDictAtomTypes && (!hasType(*res_atom) || getType(*res_atom) == AtomType::UNKNOWN)) // fix unknown/missing element
                    setType(*res_atom, atom.type);

                if (applyDictAtomCharges && !hasFormalCharge(*res_atom)) // fix missing form. charge
                    setFormalCharge(*res_atom, atom.formCharge);
            }
        }

        if (applyDictAtomBonding) {
            for (auto& bond : chem_comp.bonds) {
                auto res_atom1 = currResidueAtoms[chem_comp.atoms[bond.atom1Idx].id];

                if (!res_atom1)
                    res_atom1 = currResidueAtoms[chem_comp.atoms[bond.atom1Idx].altId];

                if (!res_atom1)
                    continue;

                auto res_atom2 = currResidueAtoms[chem_comp.atoms[bond.atom2Idx].id];

                if (!res_atom2)
                    res_atom2 = currResidueAtoms[chem_comp.atoms[bond.atom2Idx].altId];

                if (!res_atom2)
                    continue;

                auto& res_bond = mol.addBond(mol.getAtomIndex(*res_atom1), mol.getAtomIndex(*res_atom2));

                if (applyDictBondOrders)
                    setOrder(res_bond, bond.order);
            }
        }

        // create potentially missing intra-residue bonds
        for (auto a_it1 = res_as_start_it; a_it1 != as_it; ) {
            auto atom1 = a_it1->first;
            
            if (!mol.containsAtom(*atom1)) {
                ++a_it1;
                continue;
            }

            auto& atom1_name = getResidueAtomName(*atom1);
            auto has_tmplt_bonds1 = (applyDictAtomBonding && chem_comp.hasAtom(atom1_name));
            auto atom1_is_h = (getType(*atom1) == AtomType::H);
            auto& atom1_pos = get3DCoordinates(*atom1);
            auto cov_rad1 = MolProp::getCovalentRadius(*atom1, 1);
                
            for (auto a_it2 = ++a_it1; a_it2 != as_it; ++a_it2) {
                auto atom2 = a_it2->first;
            
                if (!mol.containsAtom(*atom2))
                    continue;

                if (atom1_is_h && (getType(*atom2) == AtomType::H)) // do not connect hydrogens!
                    continue;
                
                auto has_tmplt_bonds2 = (applyDictAtomBonding && chem_comp.hasAtom(getResidueAtomName(*atom2)));

                if (has_tmplt_bonds1 && has_tmplt_bonds2) // atom pair already processed before
                    continue;

                auto& atom2_pos = get3DCoordinates(*atom2);
                auto cov_rad2 = MolProp::getCovalentRadius(*atom2, 1);
                auto dist = norm2(atom1_pos - atom2_pos);

                if (dist > MIN_BOND_LENGTH && dist <= (cov_rad1 + cov_rad2 + BOND_LENGTH_TOLERANCE))
                    mol.addBond(mol.getAtomIndex(*atom1), mol.getAtomIndex(*atom2));
            }
        }

        // connect residues

        for (auto i : chem_comp.linkAtoms) {
            auto& atom = chem_comp.atoms[i];
            auto res_atom = currResidueAtoms[atom.id];

            if (!res_atom)
                res_atom = currResidueAtoms[atom.altId];

            if (!res_atom)
                continue;

            currResidueLinkAtoms.push_back(res_atom);
            setResidueLinkingAtomFlag(*res_atom, true);
        }

        if (!chem_comp || (currResidueLinkAtoms.size() != chem_comp.linkAtoms.size())) {
            currResidueLinkAtoms.clear();
            
            for (auto a_it = res_as_start_it; a_it != as_it; ++a_it)
                if (mol.containsAtom(*a_it->first))
                    currResidueLinkAtoms.push_back(a_it->first);
        }
        
        bool exit = false;

        for (auto atom1 : prevResidueLinkAtoms) {
            auto& atom1_pos = get3DCoordinates(*atom1);
            auto cov_rad1 = MolProp::getCovalentRadius(*atom1, 1);

            for (auto atom2 : currResidueLinkAtoms) {
                auto& atom2_pos = get3DCoordinates(*atom2);
                auto cov_rad2 = MolProp::getCovalentRadius(*atom2, 1);

                auto dist = norm2(atom1_pos - atom2_pos);

                if (dist > MIN_BOND_LENGTH && dist <= (cov_rad1 + cov_rad2 + BOND_LENGTH_TOLERANCE)) {
                    mol.addBond(mol.getAtomIndex(*atom1), mol.getAtomIndex(*atom2));
                    exit = true;
                    break;
                }
            }

            if (exit)
                break;
        }

        prevResidueLinkAtoms.swap(currResidueLinkAtoms);
    }
}

void Biomol::MMCIFDataReader::createNonStdInterResidueBonds(const MMCIFData& data, Chem::Molecule& mol) const
{
    using namespace MMCIF;
  
    auto struct_cons = data.findCategory(StructConn::NAME);

    if (!struct_cons)
        return;

    auto num_cons = struct_cons->getNumValueRows();

    if (num_cons == 0)
        return;
    
    auto con_types = struct_cons->findItem(StructConn::Item::CONN_TYPE_ID);

    if (!con_types) {
        if (strictErrorChecking)
            throw Base::IOError("MMCIFDataReader: missing mandatory _" + StructConn::NAME + "." + StructConn::Item::CONN_TYPE_ID +
                                " data items");
        return;
    }
    
    auto ptnr1_auth_asym_ids = struct_cons->findItem(StructConn::Item::PTNR1_AUTH_ASYM_ID);
    auto ptnr1_label_asym_ids = struct_cons->findItem(StructConn::Item::PTNR1_LABEL_ASYM_ID);
    auto ptnr1_auth_atom_ids = struct_cons->findItem(StructConn::Item::PTNR1_AUTH_ATOM_ID);
    auto ptnr1_label_atom_ids = struct_cons->findItem(StructConn::Item::PTNR1_LABEL_ATOM_ID);
    auto ptnr1_auth_comp_ids = struct_cons->findItem(StructConn::Item::PTNR1_AUTH_COMP_ID);
    auto ptnr1_label_comp_ids = struct_cons->findItem(StructConn::Item::PTNR1_LABEL_COMP_ID);
    auto ptnr1_auth_seq_ids = struct_cons->findItem(StructConn::Item::PTNR1_AUTH_SEQ_ID);
    auto ptnr1_label_seq_ids = struct_cons->findItem(StructConn::Item::PTNR1_LABEL_SEQ_ID);
    auto ptnr1_ins_codes = struct_cons->findItem(StructConn::Item::PDBX_PTNR1_PDB_INS_CODE);
    auto ptnr2_auth_asym_ids = struct_cons->findItem(StructConn::Item::PTNR2_AUTH_ASYM_ID);
    auto ptnr2_label_asym_ids = struct_cons->findItem(StructConn::Item::PTNR2_LABEL_ASYM_ID);
    auto ptnr2_auth_atom_ids = struct_cons->findItem(StructConn::Item::PTNR2_AUTH_ATOM_ID);
    auto ptnr2_label_atom_ids = struct_cons->findItem(StructConn::Item::PTNR2_LABEL_ATOM_ID);
    auto ptnr2_auth_comp_ids = struct_cons->findItem(StructConn::Item::PTNR2_AUTH_COMP_ID);
    auto ptnr2_label_comp_ids = struct_cons->findItem(StructConn::Item::PTNR2_LABEL_COMP_ID);
    auto ptnr2_auth_seq_ids = struct_cons->findItem(StructConn::Item::PTNR2_AUTH_SEQ_ID);
    auto ptnr2_label_seq_ids = struct_cons->findItem(StructConn::Item::PTNR2_LABEL_SEQ_ID);
    auto ptnr2_ins_codes = struct_cons->findItem(StructConn::Item::PDBX_PTNR2_PDB_INS_CODE);
    
    for (std::size_t i = 0; i < num_cons; i++) {
        if (auto con_type = getValue(con_types, i)) {
            if (Internal::isEqualCI(*con_type, StructConn::Type::SALTBR) ||
                Internal::isEqualCI(*con_type, StructConn::Type::HYDROG) ||
                Internal::isEqualCI(*con_type, StructConn::Type::MISMAT) ||
                Internal::isEqualCI(*con_type, StructConn::Type::METALC))
                continue;

            if (!Internal::isEqualCI(*con_type, StructConn::Type::COVALE) &&
                !Internal::isEqualCI(*con_type, StructConn::Type::COVALE_BASE) &&
                !Internal::isEqualCI(*con_type, StructConn::Type::COVALE_PHOSPHATE) &&
                !Internal::isEqualCI(*con_type, StructConn::Type::COVALE_SUGAR) &&
                !Internal::isEqualCI(*con_type, StructConn::Type::DISULF) &&
                !Internal::isEqualCI(*con_type, StructConn::Type::MODRES)) {

                if (strictErrorChecking)
                    throw Base::IOError("MMCIFDataReader: " + getFQItemName(struct_cons, con_types) +
                                        ": invalid structure connection type specification '" + *con_type +
                                        (num_cons > 1 ? "' at data row " + std::to_string(i) : std::string("'")));
                continue;
            }

        } else {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: " + getFQItemName(struct_cons, con_types) +
                                    ": missing structure connection type specification" +
                                    (num_cons > 1 ? " at data row " + std::to_string(i) : std::string("")));
            continue;
        }
        
        auto ptnr1_atom = getAtom(data, mol,
                                  getValue(ptnr1_auth_asym_ids, i), getValue(ptnr1_auth_atom_ids, i),
                                  getValue(ptnr1_auth_comp_ids, i), getValue(ptnr1_auth_seq_ids, i),
                                  getValue(ptnr1_label_asym_ids, i), getValue(ptnr1_label_atom_ids, i),
                                  getValue(ptnr1_label_comp_ids, i), getValue(ptnr1_label_seq_ids, i),
                                  getValue(ptnr1_ins_codes, i));

        if (!ptnr1_atom) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find first binding partner atom specified in _" + StructConn::NAME +
                                    (num_cons > 1 ? " data at row " + std::to_string(i) : std::string(" data")));
            continue;
        }
        
        auto ptnr2_atom = getAtom(data, mol,
                                  getValue(ptnr2_auth_asym_ids, i), getValue(ptnr2_auth_atom_ids, i),
                                  getValue(ptnr2_auth_comp_ids, i), getValue(ptnr2_auth_seq_ids, i),
                                  getValue(ptnr2_label_asym_ids, i), getValue(ptnr2_label_atom_ids, i),
                                  getValue(ptnr2_label_comp_ids, i), getValue(ptnr2_label_seq_ids, i),
                                  getValue(ptnr2_ins_codes, i));

        if (!ptnr2_atom) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find second binding partner atom specified in _" + StructConn::NAME +
                                    (num_cons > 1 ? " data at row " + std::to_string(i) : std::string(" data")));
            continue;
        }
        
        mol.addBond(mol.getAtomIndex(*ptnr1_atom), mol.getAtomIndex(*ptnr2_atom));
    }
}

void Biomol::MMCIFDataReader::applyDictionaryBondOrders(Chem::Molecule& mol)
{
    if (!applyDictBondOrders || applyDictAtomBonding)
        return;

    std::string bo_cache_key;

    for (auto it = mol.getBondsBegin() + startBondCount, end = mol.getBondsEnd(); it != end; ++it) {
        auto& bond = *it;

        if (hasOrder(bond))
            continue;

        auto& atom1 = bond.getBegin();
        auto& atom2 = bond.getEnd();

        if (getResidueSequenceNumber(atom1) != getResidueSequenceNumber(atom2))
            continue;

        auto& res_code1 = getResidueCode(atom1);
        auto& res_code2 = getResidueCode(atom2);

        if (res_code1 != res_code2)
            continue;

        auto& atom_name1 = getResidueAtomName(atom1);
        auto& atom_name2 = getResidueAtomName(atom2);

        bo_cache_key = res_code1;
        bo_cache_key.push_back('-');
        bo_cache_key.append(atom_name1);
        bo_cache_key.push_back('-');
        bo_cache_key.append(atom_name2);

        auto boc_it = bondOrderCache.find(bo_cache_key);

        if (boc_it != bondOrderCache.end()) {
            setOrder(bond, boc_it->second); 
            continue;
        }

        auto& chem_comp = getChemCompData(res_code1);

        if (!chem_comp)
            continue;

        if (auto order = chem_comp.getBondOrder(atom_name1, atom_name2)) {
            bondOrderCache[bo_cache_key] = order;

            bo_cache_key = res_code1;
            bo_cache_key.push_back('-');
            bo_cache_key.append(atom_name2);
            bo_cache_key.push_back('-');
            bo_cache_key.append(atom_name1);

            bondOrderCache[bo_cache_key] = order;

            setOrder(bond, order);
        }
    }
}

void Biomol::MMCIFDataReader::setMacromoleculeName(const MMCIFData& data, Chem::Molecule& mol) const
{
    auto entry = data.findCategory(MMCIF::Entry::NAME);

    if (!entry)
        return;
    
    auto entry_id = entry->findItem(MMCIF::Entry::Item::ID);

    if (!entry_id)
        return;
    
    if (entry_id->getNumValues() != 1)
        return;

    if (auto* id = getValue(entry_id, 0))
        setName(mol, *id);
}

Chem::Atom* Biomol::MMCIFDataReader::getAtom(const MMCIFData& data, Chem::Molecule& mol,
                                             const std::string* auth_asym_id, const std::string* auth_atom_id,
                                             const std::string* auth_comp_id, const std::string* auth_seq_id,
                                             const std::string* label_asym_id, const std::string* label_atom_id,
                                             const std::string* label_comp_id, const std::string* label_seq_id,
                                             const std::string* ins_code) const
{
    using namespace MMCIF;
  
    auto atom_sites = data.findCategory(AtomSite::NAME);

    if (!atom_sites)
        return nullptr;

    auto auth_asym_ids = atom_sites->findItem(AtomSite::Item::AUTH_ASYM_ID);
    auto label_asym_ids = atom_sites->findItem(AtomSite::Item::LABEL_ASYM_ID);
    auto auth_atom_ids = atom_sites->findItem(AtomSite::Item::AUTH_ATOM_ID);
    auto label_atom_ids = atom_sites->findItem(AtomSite::Item::LABEL_ATOM_ID);
    auto auth_comp_ids = atom_sites->findItem(AtomSite::Item::AUTH_COMP_ID);
    auto label_comp_ids = atom_sites->findItem(AtomSite::Item::LABEL_COMP_ID);
    auto auth_seq_ids = atom_sites->findItem(AtomSite::Item::AUTH_SEQ_ID);
    auto label_seq_ids = atom_sites->findItem(AtomSite::Item::LABEL_SEQ_ID);
    auto ins_codes = atom_sites->findItem(AtomSite::Item::PDBX_PDB_INS_CODE);
    
    for (auto& ase : atomSiteSequence) {
        if (!mol.containsAtom(*ase.first))
            continue;

        if (!valuesMatch(auth_asym_id, auth_asym_ids, ase.second))
            continue;

        if (!valuesMatch(label_asym_id, label_asym_ids, ase.second))
            continue;

        if (!valuesMatch(auth_atom_id, auth_atom_ids, ase.second))
            continue;

        if (!valuesMatch(label_atom_id, label_atom_ids, ase.second))
            continue;

        if (!valuesMatch(auth_comp_id, auth_comp_ids, ase.second))
            continue;

        if (!valuesMatch(label_comp_id, label_comp_ids, ase.second))
            continue;

        if (!valuesMatch(auth_seq_id, auth_seq_ids, ase.second))
            continue;

        if (!valuesMatch(label_seq_id, label_seq_ids, ase.second))
            continue;

        if (!valuesMatch(ins_code, ins_codes, ase.second))
            continue;

        return ase.first;
    }

    return nullptr;
}

const Biomol::ResidueDictionary& Biomol::MMCIFDataReader::getResidueDictionary() const
{
    if (resDictionary)
        return *resDictionary->get();

    return *resDictionary;
}

void Biomol::MMCIFDataReader::getMissingChemCompLinkAtomsFromResDictStructs()
{
    auto& res_dict = getResidueDictionary();
    
    for (auto& ce : chemCompDict) {
        auto& comp = chemCompList[ce.second];

        if (!comp.linkAtoms.empty())
            continue;
        
        auto& comp_id = ce.first;        
        auto dict_struct = res_dict.getStructure(comp_id);

        if (!dict_struct)
            continue;
        
        for (auto& atom : dict_struct->getAtoms()) {
            if (!getResidueLinkingAtomFlag(atom))
                continue;

            auto it = chemCompAtomLookupMap.find({&comp_id, &getResidueAtomName(atom)});

            if (it == chemCompAtomLookupMap.end()) {
                if (!hasResidueAltAtomName(atom))
                    continue;

                it = chemCompAtomLookupMap.find({&comp_id, &getResidueAltAtomName(atom)});

                if (it == chemCompAtomLookupMap.end())
                    continue;
            }
            
            comp.linkAtoms.insert(it->second);
        }
    }
}

void Biomol::MMCIFDataReader::setupChemCompDataFromResDictStruct(ChemComp& chem_comp, const std::string& comp_id)
{
     auto& res_dict = getResidueDictionary();
     auto dict_struct = res_dict.getStructure(comp_id);

     if (!dict_struct)
         return;

     for (auto& atom : dict_struct->getAtoms()) {
         if (getResidueLinkingAtomFlag(atom))
             chem_comp.linkAtoms.insert(chem_comp.atoms.size());

         chem_comp.atoms.emplace_back(&getResidueAtomName(atom), hasResidueAltAtomName(atom) ? &getResidueAltAtomName(atom) : nullptr,
                                      getFormalCharge(atom), getType(atom), getResidueLeavingAtomFlag(atom));
     }

     for (auto& bond : dict_struct->getBonds())
         chem_comp.bonds.emplace_back(dict_struct->getAtomIndex(bond.getBegin()), dict_struct->getAtomIndex(bond.getEnd()),
                                      getOrder(bond));
}

Biomol::MMCIFDataReader::ChemComp& Biomol::MMCIFDataReader::getOrAddChemCompData(const std::string& comp_id)
{
    auto it = chemCompDict.find(comp_id);

    if (it == chemCompDict.end()) {
        assert(chemCompCount <= chemCompList.size());

        chemCompDict.emplace(comp_id, chemCompCount);

        if (chemCompCount == chemCompList.size()) {
            chemCompList.resize(++chemCompCount);

            return chemCompList.back();
        }

        return chemCompList[chemCompCount++].clear();
    }

    return chemCompList[it->second];
}

Biomol::MMCIFDataReader::ChemComp& Biomol::MMCIFDataReader::getChemCompData(const std::string& comp_id)
{
    auto& chem_comp = getOrAddChemCompData(comp_id);

    if (!chem_comp)
        setupChemCompDataFromResDictStruct(chem_comp, comp_id);

    return chem_comp;
}

void Biomol::MMCIFDataReader::readChemComps(const MMCIFData& data, Chem::Molecule& mol)
{
    readChemCompAtoms(data, mol);

    if (readChemCompBonds(data, mol))
        perceiveBondOrders(mol);

    calcAtomCharges(mol);
 
    postprocReadChemComps(data, mol);
}

void Biomol::MMCIFDataReader::readChemCompAtoms(const MMCIFData& data, Chem::Molecule& mol)
{
    using namespace MMCIF;
    
    chemCompAtomLookupMap.clear();
    
    auto comp_atoms = data.findCategory(ChemCompAtom::NAME);

    if (!comp_atoms)
        return;

    auto num_atoms = comp_atoms->getNumValueRows();

    if (num_atoms == 0)
        return;

    auto comp_ids = comp_atoms->findItem(ChemCompAtom::Item::COMP_ID);
    auto ids = comp_atoms->findItem(ChemCompAtom::Item::ATOM_ID);
    auto alt_ids = comp_atoms->findItem(ChemCompAtom::Item::ALT_ATOM_ID);
    auto type_syms = comp_atoms->findItem(ChemCompAtom::Item::TYPE_SYMBOL);
    auto coords_x = comp_atoms->findItem(ChemCompAtom::Item::COORDS_X);
    auto coords_y = comp_atoms->findItem(ChemCompAtom::Item::COORDS_Y);
    auto coords_z = comp_atoms->findItem(ChemCompAtom::Item::COORDS_Z);
    auto ideal_coords_x = comp_atoms->findItem(ChemCompAtom::Item::PDBX_IDEAL_COORDS_X);
    auto ideal_coords_y = comp_atoms->findItem(ChemCompAtom::Item::PDBX_IDEAL_COORDS_Y);
    auto ideal_coords_z = comp_atoms->findItem(ChemCompAtom::Item::PDBX_IDEAL_COORDS_Z);
    auto leaving_flags = comp_atoms->findItem(ChemCompAtom::Item::PDBX_LEAVING_ATOM_FLAG);
    auto arom_flags = comp_atoms->findItem(ChemCompAtom::Item::PDBX_AROM_FLAG);
    auto form_charges = comp_atoms->findItem(ChemCompAtom::Item::CHARGE);
    auto sto_configs = comp_atoms->findItem(ChemCompAtom::Item::PDBX_STEREO_CONFIG);

    Math::Vector3D coords;
    Math::Vector3D ideal_coords;
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        auto& atom = mol.addAtom();
        auto* comp_id = getValue(comp_ids, i);
        
        if (comp_id)
            setResidueCode(atom, *comp_id);
        
        if (auto* id = getValue(ids, i)) {
            setResidueAtomName(atom, *id);
            chemCompAtomLookupMap.emplace(ChemCompAtomID{comp_id, id}, mol.getNumAtoms() - 1);
        }

        if (auto* alt_id = getValue(alt_ids, i))
            setResidueAltAtomName(atom, *alt_id);

        if (auto* type_sym = getValue(type_syms, i)) {
            auto atom_type = Chem::AtomDictionary::getType(*type_sym);

            if (atom_type == Chem::AtomType::UNKNOWN) {
                if (strictErrorChecking)
                    throw Base::IOError("MMCIFDataReader: " + getFQItemName(comp_atoms, type_syms) +
                                        ": unknown atom type symbol '" + *type_sym +
                                        (num_atoms > 1 ? "' at data row " + std::to_string(i) : std::string("'")));

                setSymbol(atom, *type_sym);
                
            } else
                setSymbol(atom, Chem::AtomDictionary::getSymbol(atom_type));

            setType(atom, atom_type);
        }

        long form_charge = 0;
        
        if (getValue(comp_atoms, form_charges, i, form_charge))
            setFormalCharge(atom, form_charge);

        bool arom_flag = false;
        
        if (getValue(comp_atoms, arom_flags, i, arom_flag))
            setAromaticityFlag(atom, arom_flag);

        bool leaving_flag = false;
        
        if (getValue(comp_atoms, leaving_flags, i, leaving_flag))
            setResidueLeavingAtomFlag(atom, leaving_flag);

        bool have_coords = getValue(comp_atoms, coords_x, i, coords[0]) &&
                           getValue(comp_atoms, coords_y, i, coords[1]) &&
                           getValue(comp_atoms, coords_z, i, coords[2]);
        bool have_ideal_coords = getValue(comp_atoms, ideal_coords_x, i, ideal_coords[0]) &&
                                 getValue(comp_atoms, ideal_coords_y, i, ideal_coords[1]) &&
                                 getValue(comp_atoms, ideal_coords_z, i, ideal_coords[2]);

        if (have_coords && have_ideal_coords) {
            Math::Vector3DArray::SharedPointer coords_array_ptr(new Math::Vector3DArray());

            coords_array_ptr->addElement(coords);
            coords_array_ptr->addElement(ideal_coords);

            set3DCoordinatesArray(atom, coords_array_ptr);
            set3DCoordinates(atom, coords);
            
        } else if (have_coords)
            set3DCoordinates(atom, coords);
            
        else if (have_ideal_coords)
            set3DCoordinates(atom, ideal_coords);

        if (auto* sto_config = getValue(sto_configs, i)) {
            if (Internal::isEqualCI(*sto_config, ChemCompAtom::StereoConfig::R))
                setCIPConfiguration(atom, Chem::CIPDescriptor::R);

            else if (Internal::isEqualCI(*sto_config, ChemCompAtom::StereoConfig::S))
                setCIPConfiguration(atom, Chem::CIPDescriptor::S);

            else if (Internal::isEqualCI(*sto_config, ChemCompAtom::StereoConfig::NONE))
                setCIPConfiguration(atom, Chem::CIPDescriptor::NONE);

            else if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: " + getFQItemName(comp_atoms, sto_configs) +
                                    ": unknown atom stereo configuration '" + *sto_config +
                                    (num_atoms > 1 ? "' at data row " + std::to_string(i) : std::string("'")));
        }
    }
}

bool Biomol::MMCIFDataReader::readChemCompBonds(const MMCIFData& data, Chem::Molecule& mol)
{
    using namespace MMCIF;
    
    auto comp_bonds = data.findCategory(ChemCompBond::NAME);

    if (!comp_bonds)
        return false;

    auto num_bonds = comp_bonds->getNumValueRows();

    if (num_bonds == 0)
        return false;

    auto comp_ids = comp_bonds->findItem(ChemCompBond::Item::COMP_ID);
    auto atom_ids_1 = comp_bonds->findItem(ChemCompBond::Item::ATOM_ID_1);
    auto atom_ids_2 = comp_bonds->findItem(ChemCompBond::Item::ATOM_ID_2);
    auto orders = comp_bonds->findItem(ChemCompBond::Item::ORDER);
    auto arom_flags = comp_bonds->findItem(ChemCompBond::Item::PDBX_AROM_FLAG);
    auto sto_configs = comp_bonds->findItem(ChemCompBond::Item::PDBX_STEREO_CONFIG);
    auto undef_bond_orders = false;
    
    for (std::size_t i = 0; i < num_bonds; i++) {
        auto* comp_id = getValue(comp_ids, i);
        auto* atom_id_1 = getValue(atom_ids_1, i);

        if (!atom_id_1)
            continue;

        auto* atom_id_2 = getValue(atom_ids_2, i);

        if (!atom_id_2)
            continue;

        auto it1 = chemCompAtomLookupMap.find({comp_id, atom_id_1});

        if (it1 == chemCompAtomLookupMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find atom with id '" + *atom_id_1 + "' specified in _" + ChemCompBond::NAME +
                                    (num_bonds > 1 ? " data at row " + std::to_string(i) : std::string(" data")));
            continue;
        }

        auto it2 = chemCompAtomLookupMap.find({comp_id, atom_id_2});

        if (it2 == chemCompAtomLookupMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find atom with id '" + *atom_id_2 + "' specified in _" + ChemCompBond::NAME +
                                    (num_bonds > 1 ? " data at row " + std::to_string(i) : std::string(" data")));
            continue;
        }

        auto& bond = mol.addBond(it1->second, it2->second);

        bool arom_flag = false;
        
        if (getValue(comp_bonds, arom_flags, i, arom_flag))
            setAromaticityFlag(bond, arom_flag);

        if (auto* sto_config = getValue(sto_configs, i)) {
            if (Internal::isEqualCI(*sto_config, ChemCompBond::StereoConfig::E))
                setCIPConfiguration(bond, Chem::CIPDescriptor::E);

            else if (Internal::isEqualCI(*sto_config, ChemCompBond::StereoConfig::Z))
                setCIPConfiguration(bond, Chem::CIPDescriptor::Z);

            else if (Internal::isEqualCI(*sto_config, ChemCompBond::StereoConfig::NONE))
                setCIPConfiguration(bond, Chem::CIPDescriptor::NONE);

            else if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: " + getFQItemName(comp_bonds, sto_configs) +
                                    ": invalid bond stereo configuration specification '" + *sto_config +
                                    (num_bonds > 1 ? "' at data row " + std::to_string(i) : std::string("'")));
        }

        if (auto* order = getValue(orders, i)) {
            if (Internal::isEqualCI(*order, ChemCompBond::Order::SINGLE))
                setOrder(bond, 1);
            
            else if (Internal::isEqualCI(*order, ChemCompBond::Order::DOUBLE))
                setOrder(bond, 2);
            
            else if (Internal::isEqualCI(*order, ChemCompBond::Order::TRIPLE))
                setOrder(bond, 3);

            else {
                if (strictErrorChecking &&
                     !Internal::isEqualCI(*order, ChemCompBond::Order::AROMATIC) &&
                     !Internal::isEqualCI(*order, ChemCompBond::Order::DELOCALIZED) &&
                     !Internal::isEqualCI(*order, ChemCompBond::Order::PI) &&
                     !Internal::isEqualCI(*order, ChemCompBond::Order::POLYMERIC) &&
                     !Internal::isEqualCI(*order, ChemCompBond::Order::QUADRUPLE))

                         throw Base::IOError("MMCIFDataReader: " + getFQItemName(comp_bonds, orders) +
                                             ": invalid bond order specification '" + *order +
                                             (num_bonds > 1 ? "' at data row " + std::to_string(i) : std::string("'")));

                undef_bond_orders = true;
            }

        } else
            setOrder(bond, 1);
    }

    return undef_bond_orders;
}

void Biomol::MMCIFDataReader::postprocReadChemComps(const MMCIFData& data, Chem::Molecule& mol) const
{
    auto comps = data.findCategory(MMCIF::ChemComp::NAME);
    auto comp_ids = (comps ? comps->findItem(MMCIF::ChemComp::Item::ID) : nullptr);
    auto comp_names = (comps ? comps->findItem(MMCIF::ChemComp::Item::NAME) : nullptr);
    auto num_comps = (comps && comp_ids && comp_names ? comps->getNumValueRows() : std::size_t(0));
    
    Chem::FragmentList::SharedPointer comps_ptr(new Chem::ComponentSet(mol, !hasComponents(mol) ? std::size_t(0) : startAtomCount));

    for (auto& comp : *comps_ptr) {
        const std::string* comp_id = nullptr;
        
        for (auto& atom : comp.getAtoms()) {
            if (!hasResidueCode(atom)) {
                comp_id = nullptr;
                break;
            }

            if (!comp_id) {
                comp_id = &getResidueCode(atom);
                continue;
            }

            if (*comp_id != getResidueCode(atom)) {
                comp_id = nullptr;
                break;
            }
        }

        if (!comp_id)
            continue;

        setResidueCode(comp, *comp_id);

        for (std::size_t i = 0; i < num_comps; i++) {
            if (!valuesMatch(comp_id, comp_ids, i))
                continue;

            if (auto name = getValue(comp_names, i)) {
                setName(comp, *name);
                break;
            }
        }
    }

    if (hasComponents(mol)) {
        auto& old_comps_ptr = getComponents(mol);

        old_comps_ptr->insertElements(old_comps_ptr->Chem::FragmentList::BaseType::end(),
                                      comps_ptr->Chem::FragmentList::BaseType::begin(),
                                      comps_ptr->Chem::FragmentList::BaseType::end());

        comps_ptr = old_comps_ptr;
        
    } else
        setComponents(mol, comps_ptr);
    
    if (startAtomCount > 0)
        return;

    if (!hasResidueCode(mol)) {
        const std::string* res_code = nullptr;
    
        for (auto& comp : *comps_ptr) {
            if (hasResidueCode(comp)) {
                if (!res_code) {
                    res_code = &getResidueCode(comp);
                    continue;
                }
                
                if (*res_code != getResidueCode(comp)) {
                    res_code = nullptr;
                    break;
                }
            
            } else
                break;
        }

        if (res_code)
            setResidueCode(mol, *res_code);
    }

    if (!hasName(mol)) {
        const std::string* name = nullptr;
    
        for (auto& comp : *comps_ptr) {
            if (hasName(comp)) {
                if (!name) {
                    name = &getName(comp);
                    continue;
                }
                
                if (*name != getName(comp)) {
                    name = nullptr;
                    break;
                }
            
            } else
                break;
        }

        if (name)
            setName(mol, *name);
    }
}

void Biomol::MMCIFDataReader::perceiveBondOrders(Chem::Molecule& mol)
{
    if (!perceiveOrders)
        return;

    if (startBondCount == 0) {
        perceiveSSSR(mol, true);
        setRingFlags(mol, true);

        Chem::perceiveBondOrders(mol, false);
        return;
    }

    readMolGraph.clear();

    std::for_each(mol.getBondsBegin() + startBondCount, mol.getBondsEnd(), 
                  [&](const Chem::Bond& bond) { readMolGraph.addBond(bond); });

    setRingFlags(readMolGraph, true);
    
    Chem::perceiveBondOrders(readMolGraph, false);
}

void Biomol::MMCIFDataReader::calcAtomCharges(Chem::Molecule& mol)
{
    using namespace Chem;

    if (!calcCharges)
        return;

    if (startAtomCount != 0)
        readMolGraph.clear();

    for (Molecule::BondIterator it = mol.getBondsBegin() + startBondCount, end = mol.getBondsEnd(); it != end; ++it) {
        Bond& bond = *it;

        if (hasOrder(bond))
            continue;

        setOrder(bond, 1);

        if (startAtomCount != 0)
            readMolGraph.addBond(bond);
    }

    for (Molecule::AtomIterator it = mol.getAtomsBegin() + startAtomCount, end = mol.getAtomsEnd(); it != end; ++it) {
        Atom& atom = *it;

        if (startAtomCount != 0)
            readMolGraph.addAtom(atom);

        if (hasImplicitHydrogenCount(atom))
            continue;

        if (hasFormalCharge(atom))
            continue;

        setImplicitHydrogenCount(atom, 0);
    }

    if (startAtomCount != 0)
        Chem::calcFormalCharges(readMolGraph, false);
    else
        Chem::calcFormalCharges(mol, false);
}

Biomol::MMCIFData::SharedPointer Biomol::MMCIFDataReader::parseInput(std::istream& is)
{
    if (!hasMoreData(is))
        return MMCIFData::SharedPointer();

    if (!nextToken(is))
        throw Base::IOError("MMCIFDataReader: unexpected end of input while reading data block identifier");
    
    assert(tokenValue.length() >= MMCIF::DATA_BLOCK_ID_PREFIX.length());
 
    MMCIFData::SharedPointer data(new MMCIFData(tokenValue.substr(MMCIF::DATA_BLOCK_ID_PREFIX.length())));
    std::string cat_name, item_name;
    
    while (auto token = nextToken(is)) {
        if (token != PLAIN_STRING) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: invalid data name or keyword");

            continue;
        }
        
        assert(!tokenValue.empty());
        
        if (Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX)) {
            putbackToken(is);
            break;
        }
      
        if (Internal::isEqualCI(tokenValue, MMCIF::LOOP_KEYWORD)) {
            parseLoopSection(is, *data);
            continue;
        }

        if (!extractCategoryandItemNames(cat_name, item_name, strictErrorChecking))
            continue;

        if (!nextToken(is))
            throw Base::IOError("MMCIFDataReader: unexpected end of input while reading data value");

        auto cat = (data->getNumCategories() == 0 ? nullptr : &data->lastCategory());
 
        if (!cat || !Internal::isEqualCI(cat_name, cat->getName()) || (cat->getNumValueRows() > 1))
            cat = &data->addCategory(cat_name);
            
        cat->addItem(item_name).addValue(tokenValue);
    }

    return data;
}

void Biomol::MMCIFDataReader::parseLoopSection(std::istream& is, MMCIFData& data)
{
    MMCIFData::Category* cat = nullptr;
    std::string cat_name, item_name;
    
    while (true) {
        auto token = nextToken(is);
        
        if (!token)
            return;

        assert(!tokenValue.empty());
        
        if (token != PLAIN_STRING) {
            putbackToken(is);
            break;
        }

        if (Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX) ||
            Internal::isEqualCI(tokenValue, MMCIF::LOOP_KEYWORD)) {
            putbackToken(is);
            return;
        }

        if (!extractCategoryandItemNames(cat_name, item_name, false)) {
            putbackToken(is);
            break;
        }

        if (!cat)
            cat = &data.addCategory(cat_name);
        
        else if (!Internal::isEqualCI(cat_name, cat->getName())) {
            putbackToken(is);
            break;
        }
                 
        cat->addItem(item_name);
    }

    if (!cat)
        return;

    for (std::size_t i = 0, num_items = cat->getNumItems(); ; i++) {
        auto item_idx = (i % num_items);
        auto token = nextToken(is);

        if (!token) {
            if (item_idx != 0 && strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: unexpected end of input while reading " + MMCIF::LOOP_KEYWORD + " section data values");

            return;
        }

        assert(!tokenValue.empty());
 
        if (item_idx == 0 && token == PLAIN_STRING &&
            (tokenValue[0] == MMCIF::DATA_NAME_PREFIX ||
             Internal::startsWithCI(tokenValue, MMCIF::DATA_BLOCK_ID_PREFIX) ||
             Internal::isEqualCI(tokenValue, MMCIF::LOOP_KEYWORD))) {

            putbackToken(is);
            return;
        }

        cat->getItem(item_idx).addValue(tokenValue);
    }
}

bool Biomol::MMCIFDataReader::extractCategoryandItemNames(std::string& cat_name, std::string& item_name, bool strict) const
{
    if (tokenValue[0] != MMCIF::DATA_NAME_PREFIX) {
        if (strict)
            throw Base::IOError("MMCIFDataReader: invalid data name");

        return false;
    }

    std::string::size_type cat_pfx_len = tokenValue.find(MMCIF::CATEGORY_NAME_SEPARATOR);

    if (cat_pfx_len == std::string::npos) {
        if (strict)
            throw Base::IOError("MMCIFDataReader: data name without category prefix");

        return false;
    }

    if (cat_pfx_len == (tokenValue.length() - 1)) {
        if (strict)
            throw Base::IOError("MMCIFDataReader: zero-length data item name");

        return false;
    }

    cat_name.assign(tokenValue, 1, cat_pfx_len - 1);
    item_name.assign(tokenValue, cat_pfx_len + 1);
    
    return true;
}

Biomol::MMCIFDataReader::Token Biomol::MMCIFDataReader::nextToken(std::istream& is)
{
    enum State
    {
        START,
        EOL,
        PLAIN_STR,
        QUOTED_STR_1,
        QUOTED_STR_1_END,
        QUOTED_STR_2,
        QUOTED_STR_2_END,
        TXT_FIELD,
        COMMENT
    };

    static constexpr int EOF_ = std::istream::traits_type::eof();
    
    lastStreamPos = is.tellg();
    tokenValue.clear();
    
    auto state = START;
    auto rdbuf = is.rdbuf();
    
    while (true) {
        int tmp = rdbuf->sbumpc();
        char c = (std::istream::traits_type::eq_int_type(tmp, EOF_) ? char(0) : std::istream::traits_type::to_char_type(tmp));

        if (c == '\r') {
            tmp = rdbuf->sgetc();

            if (!std::istream::traits_type::eq_int_type(tmp, EOF_) && std::istream::traits_type::to_char_type(tmp) == MMCIF::END_OF_LINE)
                rdbuf->sbumpc();

            c = MMCIF::END_OF_LINE;
        }

        switch (state) {

            case START:
                if (!c)
                    return EOI;

                switch (c) {

                    case MMCIF::END_OF_LINE:
                        state = EOL;
                        continue;
                        
                    case MMCIF::COMMENT_PREFIX:
                        state = COMMENT;
                        continue;

                    case MMCIF::QUOTED_STRING_DELIMITER_1:
                        state = QUOTED_STR_1;
                        continue;

                    case MMCIF::QUOTED_STRING_DELIMITER_2:
                        state = QUOTED_STR_2;
                        continue;
                        
                    default:
                        if (MMCIF::isSpace(c))
                            continue;

                        tokenValue.push_back(c);
                        state = PLAIN_STR;
                        continue;
                }

            case EOL:
                if (!c)
                    return EOI;
                
                if (c == MMCIF::TEXT_FIELD_DELIMITER)
                    state = TXT_FIELD;

                else {
                    rdbuf->sungetc();
                    state = START;
                }

                continue;
                
            case COMMENT:
                if (!c || c == MMCIF::END_OF_LINE) {
                    if (c)
                        rdbuf->sungetc();

                    state = START;
                }

                continue;
                
            case PLAIN_STR:
                if (!c || MMCIF::isSpace(c)) {
                    if (c)
                        rdbuf->sungetc();

                    return PLAIN_STRING;
                }

                tokenValue.push_back(c);
                continue;
                
            case QUOTED_STR_1:
                if (!c || c == MMCIF::END_OF_LINE)
                    throw Base::IOError("MMCIFDataReader: unexpected end of input while reading quoted string");
                
                if (c == MMCIF::QUOTED_STRING_DELIMITER_1)
                    state = QUOTED_STR_1_END;
                else
                    tokenValue.push_back(c);

                continue;

            case QUOTED_STR_1_END:
                if (!c || MMCIF::isSpace(c)) {
                    if (c)
                        rdbuf->sungetc();

                    return QUOTED_STRING;
                }

                tokenValue.push_back(MMCIF::QUOTED_STRING_DELIMITER_1);
                tokenValue.push_back(c);
                state = QUOTED_STR_1;
                continue;
                    
            case QUOTED_STR_2:
                if (!c || c == MMCIF::END_OF_LINE)
                    throw Base::IOError("MMCIFDataReader: unexpected end of input while reading quoted string");
                
                if (c == MMCIF::QUOTED_STRING_DELIMITER_2)
                    state = QUOTED_STR_2_END;
                else
                    tokenValue.push_back(c);

                continue;

            case QUOTED_STR_2_END:
                if (!c || MMCIF::isSpace(c)) {
                    if (c)
                        rdbuf->sungetc();
                    
                    return QUOTED_STRING;
                }

                tokenValue.push_back(MMCIF::QUOTED_STRING_DELIMITER_2);
                tokenValue.push_back(c);
                state = QUOTED_STR_2;
                continue;
                
            case TXT_FIELD:
                if (!c) 
                    throw Base::IOError("MMCIFDataReader: unexpected end of input while reading text field");

                if (c == MMCIF::TEXT_FIELD_DELIMITER && !tokenValue.empty() && tokenValue.back() == MMCIF::END_OF_LINE) {
                    tokenValue.resize(tokenValue.length() - 1);
                    return TEXT_FIELD;
                }

                tokenValue.push_back(c);
                continue;
                
            default:
                throw Base::IOError("MMCIFDataReader: bad tokenizer state");
        }
    }
}

void Biomol::MMCIFDataReader::putbackToken(std::istream& is) const
{
    is.clear();

    if (!is.seekg(lastStreamPos))
        throw Base::IOError("MMCIFDataReader: setting stram input position failed");
}
