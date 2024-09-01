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

#include <boost/functional/hash.hpp>

#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/ComponentSet.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
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
}


enum Biomol::MMCIFDataReader::Token : int
{
    EOI = 0,
    PLAIN_STRING,
    QUOTED_STRING,
    TEXT_FIELD
};


std::size_t Biomol::MMCIFDataReader::CompAtomIDHash::operator()(const CompAtomID& atom_id) const
{
    std::size_t h = 0;

    if (atom_id.first)
        boost::hash_combine(h, *atom_id.first);

    boost::hash_combine(h, *atom_id.second);

    return h;
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
    auto data = parseInput(is);

    if (!data)
        return false;

    if (data->findCategory(MMCIF::AtomSite::NAME))
        readMacromolecule(*data, mol);
    else if (data->findCategory(MMCIF::ChemComp::NAME))
        readChemComponents(*data, mol);
        
    setMMCIFData(mol, data);

    if (!hasName(mol))
        setName(mol, data->getID());
    
    return true;
}

void Biomol::MMCIFDataReader::init(std::istream& is)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);

    is.imbue(std::locale::classic());
}

void Biomol::MMCIFDataReader::readMacromolecule(const MMCIFData& data, Chem::Molecule& mol)
{
}

void Biomol::MMCIFDataReader::readChemComponents(const MMCIFData& data, Chem::Molecule& mol)
{
    using namespace MMCIF;

    auto prev_num_atoms = mol.getNumAtoms();
    
    readComponentAtoms(data, mol);

    if (readComponentBonds(data, mol))
        kekulizeBonds(mol);

    if (!hasComponents(mol))
        prev_num_atoms = 0;

    auto comps = data.findCategory(ChemComp::NAME);
    auto comp_ids = (comps ? comps->findItem(ChemComp::Item::ID) : nullptr);
    auto comp_names = (comps ? comps->findItem(ChemComp::Item::NAME) : nullptr);
    auto num_comps = (comps && comp_ids && comp_names ? comps->getNumValueRows() : std::size_t(0));
    
    Chem::FragmentList::SharedPointer comps_ptr(new Chem::ComponentSet(mol, prev_num_atoms));

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
            auto id = getValue(comp_ids, i);

            if (!id)
                continue;

            auto name = getValue(comp_names, i);

            if (!name)
                continue;

            if (*id == *comp_id) {
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
    } else
        setComponents(mol, comps_ptr);
    
    if (prev_num_atoms == 0 && num_comps == 1) {
        if (!hasResidueCode(mol))
            if (auto res_code = getValue(comp_ids, 0))
                setResidueCode(mol, *res_code);

        if (!hasName(mol))
            if (auto name = getValue(comp_names, 0))
                setName(mol, *name);
    }
    
    if (prev_num_atoms == 0 && !hasName(mol))
        setName(mol, data.getID());
}

void Biomol::MMCIFDataReader::readComponentAtoms(const MMCIFData& data, Chem::Molecule& mol)
{
    using namespace MMCIF;
    
    compAtomLookupMap.clear();
    
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

    long int_val = 0;
    bool bool_val = 0;
    Math::Vector3D coords;
    Math::Vector3D ideal_coords;
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        auto& atom = mol.addAtom();
        auto* comp_id = getValue(comp_ids, i);
        
        if (comp_id)
            setResidueCode(atom, *comp_id);
        
        if (auto* id = getValue(ids, i)) {
            setResidueAtomName(atom, *id);
            compAtomLookupMap.emplace(CompAtomID{comp_id, id}, mol.getNumAtoms() - 1);
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

        if (getValue(comp_atoms, form_charges, i, int_val))
            setFormalCharge(atom, int_val);

        if (getValue(comp_atoms, arom_flags, i, bool_val))
            setAromaticityFlag(atom, bool_val);

        if (getValue(comp_atoms, leaving_flags, i, bool_val))
            setResidueLeavingAtomFlag(atom, bool_val);

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
            
        } else if (have_coords) {
            set3DCoordinates(atom, coords);
            
        } else if (have_ideal_coords) {
            set3DCoordinates(atom, ideal_coords);
        }

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

bool Biomol::MMCIFDataReader::readComponentBonds(const MMCIFData& data, Chem::Molecule& mol)
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

        auto it1 = compAtomLookupMap.find({comp_id, atom_id_1});

        if (it1 == compAtomLookupMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find atom with id '" + *atom_id_1 + "' specified in _" + comp_bonds->getName() +
                                    (num_bonds > 1 ? " data at row " + std::to_string(i) : std::string(" data")));

            continue;
        }

        auto it2 = compAtomLookupMap.find({comp_id, atom_id_2});

        if (it2 == compAtomLookupMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("MMCIFDataReader: could not find atom with id '" + *atom_id_2 + "' specified in _" + comp_bonds->getName() +
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

                         throw Base::IOError("MMCIFDataReader: " + getFQItemName(comp_bonds, sto_configs) +
                                             ": invalid bond order specification '" + *order +
                                             (num_bonds > 1 ? "' at data row " + std::to_string(i) : std::string("'")));

                undef_bond_orders = true;
            }

        } else
            setOrder(bond, 1);
    }

    return undef_bond_orders;
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
