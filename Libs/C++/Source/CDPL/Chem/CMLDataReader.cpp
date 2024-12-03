/* 
 * CMLDataReader.cpp 
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

#include <istream>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/DefaultMultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "CMLDataReader.hpp"
#include "CMLFormatData.hpp"


using namespace CDPL;


namespace
{

    inline std::string_view nextToken(const char* str, std::size_t str_len, std::size_t& offs)
    {
        for ( ; offs < str_len && std::isspace(str[offs]); offs++);

        auto start = offs;
        
        for ( ; offs < str_len && !std::isspace(str[offs]); offs++);

        return std::string_view(str + start, offs - start);
    }

    inline bool nameMatches(const char* name, std::size_t name_len, const std::string& query)
    {
        if (query.length() > name_len)
            return false;

        if (query.length() == name_len)
            return (query == name);

        if (std::string_view(name + (name_len - query.length()), query.length()) != query)
            return false;

        return (name[name_len - query.length() - 1] == ':');
    }
}


bool Chem::CMLDataReader::readMolecule(std::istream& is, Molecule& mol)
{
    if (!hasMoreData(is))
        return false;

    init();
   
    auto atom_idx_offs = mol.getNumAtoms();
    auto bond_idx_offs = mol.getNumBonds();

    doReadMolecule(is, mol);

    if (!multiConfImport)
        return true;

    MolecularGraph* tgt_molgraph;

    if (atom_idx_offs == 0) {
        tgt_molgraph = &mol;

    } else {
        if (!confTargetFragment)
            confTargetFragment.reset(new Fragment());
        else
            confTargetFragment->clear();

        tgt_molgraph = confTargetFragment.get();

        std::for_each(mol.getAtomsBegin() + atom_idx_offs, mol.getAtomsEnd(), 
                      [&](const Chem::Atom& atom) { confTargetFragment->addAtom(atom); });

        std::for_each(mol.getBondsBegin() + bond_idx_offs, mol.getBondsEnd(), 
                      [&](const Chem::Bond& bond) { confTargetFragment->addBond(bond); });

        tgt_molgraph->copyProperties(mol);
    }

    MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

    if (!mc_input_proc)
        mc_input_proc.reset(new DefaultMultiConfMoleculeInputProcessor());
    
    if (!mc_input_proc->init(*tgt_molgraph))
        return true;

    if (!confTestMolecule)
        confTestMolecule.reset(new BasicMolecule());

    for (std::istream::pos_type last_spos = is.tellg(); hasMoreData(is); last_spos = is.tellg()) {
        confTestMolecule->clear();

        doReadMolecule(is, *confTestMolecule);

        if (!mc_input_proc->addConformation(*tgt_molgraph, *confTestMolecule)) {
            is.seekg(last_spos);
            return true;
        }
    }

    return true;
}

bool Chem::CMLDataReader::skipMolecule(std::istream& is)
{
    if (!hasMoreData(is))
        return false;

    init();

    if (!multiConfImport) {
        readMoleculeData(is, false);
        return true;
    }

    if (!confTargetMolecule)
        confTargetMolecule.reset(new BasicMolecule());
    else
        confTargetMolecule->clear();

    doReadMolecule(is, *confTargetMolecule);

    MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

    if (!mc_input_proc)
        mc_input_proc.reset(new DefaultMultiConfMoleculeInputProcessor());
    
    if (!mc_input_proc->init(*confTargetMolecule))
        return true;

    if (!confTestMolecule)
        confTestMolecule.reset(new BasicMolecule());
   
    for (std::istream::pos_type last_spos = is.tellg(); hasMoreData(is); last_spos = is.tellg()) {
        confTestMolecule->clear();

        doReadMolecule(is, *confTestMolecule);

        if (!mc_input_proc->isConformation(*confTargetMolecule, *confTestMolecule)) {
            is.seekg(last_spos);
            return true;
        }
    }

    return true;
}

bool Chem::CMLDataReader::hasMoreData(std::istream& is)
{
    using namespace Internal;
    
    while (getNextXMLTag(is, tagInfo, "CMLDataReader"))
        if ((tagInfo.name == CML::Element::MOLECULE) && (tagInfo.type != XMLTagInfo::END)) {
            is.seekg(tagInfo.streamPos);
            checkStreamState(is, "CMLDataReader");
            return true;
        }
    
    return false;
}

void Chem::CMLDataReader::init()
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
    multiConfImport     = getMultiConfImportParameter(ioBase);
}

void Chem::CMLDataReader::doReadMolecule(std::istream& is, Molecule& mol)
{
    readMoleculeData(is, true);

    molDocument.parse<0>(&molData[0]);
    
    auto mol_node = getChildNode(&molDocument, CML::Element::MOLECULE);

    if (!mol_node)
        throw Base::IOError("CMLDataReader: <" + CML::Element::MOLECULE + "> element not found");

    readMolecule(mol_node, mol, true);
}

void Chem::CMLDataReader::readMoleculeData(std::istream& is, bool save_data)
{
    using namespace Internal;

    if (save_data)
        molData.clear();
    
    std::size_t mol_elem_cnt = 0;

    do {
        if (!getNextXMLTag(is, tagInfo, "CMLDataReader", save_data ? &molData : nullptr))
            throw Base::IOError("CMLDataReader: unexpected end of input");
        
        if (tagInfo.name != CML::Element::MOLECULE)
            continue;
        
        switch (tagInfo.type) {

            case XMLTagInfo::START:
                mol_elem_cnt++;
                break;

            case XMLTagInfo::END:
                if (mol_elem_cnt > 0)
                    mol_elem_cnt--;

            default:
                break;
        }

    } while (mol_elem_cnt > 0);
}

void Chem::CMLDataReader::readMolecule(const XMLNode* mol_node, Molecule& mol, bool top_level)
{
    atomIDtoIndexMap.clear();
    stereoAtoms.clear();
    stereoBonds.clear();

    auto init_atom_count = mol.getNumAtoms();
    auto init_bond_count = mol.getNumBonds();
    
    if (auto atom_array = getChildNode(mol_node, CML::Element::ATOM_ARRAY))
        readAtoms(atom_array, mol);

    if (auto bond_array = getChildNode(mol_node, CML::Element::BOND_ARRAY))
        readBonds(bond_array, mol);

    if (!stereoAtoms.empty())
        postprocStereoAtoms(mol);

    if (!stereoBonds.empty())
         postprocStereoBonds(mol);
    
    if (!top_level) {
        auto count_attr = mol_node->first_attribute(CML::Attribute::COUNT.c_str());

        if (!count_attr)
            return;

        auto count = Internal::parseNumber<std::size_t>(count_attr->value(), count_attr->value() + count_attr->value_size(),
                                                        "CMLDataReader: error while parsing child molecule count", strictErrorChecking);
        if (count <= 1)
            return;

        if (!readMolGraph)
            readMolGraph.reset(new Fragment());
        else
            readMolGraph->clear();

        std::for_each(mol.getAtomsBegin() + init_atom_count, mol.getAtomsEnd(), 
                      [&](const Chem::Atom& atom) { readMolGraph->addAtom(atom); });

        std::for_each(mol.getBondsBegin() + init_bond_count, mol.getBondsEnd(), 
                      [&](const Chem::Bond& bond) { readMolGraph->addBond(bond); });

        for (std::size_t i = 1; i < count; i++)
            mol += *readMolGraph;
        
        return;
    }

    if (auto title_attr = mol_node->first_attribute(CML::Attribute::TITLE.c_str()))
        Chem::setName(mol, title_attr->value());
    
    for (auto node = mol_node->first_node(); node; node = node->next_sibling())
        if (nameMatches(node->name(), node->name_size(), CML::Element::NAME))
            setName(node, mol);
        else if (nameMatches(node->name(), node->name_size(), CML::Element::PROPERTY))
            addProperty(node, mol);
}

void Chem::CMLDataReader::readAtoms(const XMLNode* atom_arr_node, Molecule& mol)
{
    readArrayStyleAtoms(atom_arr_node, mol);
    
    for (auto node = atom_arr_node->first_node(); node; node = node->next_sibling())
        if (nameMatches(node->name(), node->name_size(), CML::Element::ATOM))
            addAtom(node, mol);
}

void Chem::CMLDataReader::readArrayStyleAtoms(const XMLNode* atom_arr_node, Molecule& mol)
{
    using namespace Internal;
    
    const XMLAttribute* attrs[] = {
        atom_arr_node->first_attribute(CML::Attribute::ATOM_ID_ARRAY.c_str()),
        atom_arr_node->first_attribute(CML::Attribute::ELEMENT_TYPE_ARRAY.c_str()),
        atom_arr_node->first_attribute(CML::Attribute::FORMAL_CHARGE_ARRAY.c_str()),
        atom_arr_node->first_attribute(CML::Attribute::X2_ARRAY.c_str()),
        atom_arr_node->first_attribute(CML::Attribute::Y2_ARRAY.c_str()),
        atom_arr_node->first_attribute(CML::Attribute::X3_ARRAY.c_str()),
        atom_arr_node->first_attribute(CML::Attribute::Y3_ARRAY.c_str()),
        atom_arr_node->first_attribute(CML::Attribute::Z3_ARRAY.c_str())
    };

    constexpr std::size_t NUM_ATTR = sizeof(attrs) / sizeof(const XMLAttribute*);
   
    bool have_atom_data = false;
        
    for (auto attr : attrs) 
        if (attr) {
            have_atom_data = true;
            break;
        }

    if (!have_atom_data)
        return;
        
    std::size_t value_offs[NUM_ATTR] = { 0 };
    std::string_view value[NUM_ATTR];
        
    while (true) {
        for (std::size_t i = 0; i < NUM_ATTR; i++)
            if (attrs[i]) {
                value[i] = nextToken(attrs[i]->value(), attrs[i]->value_size(), value_offs[i]);
                    
                if (value[i].empty())
                    return;
            }

        auto atom_idx = mol.getNumAtoms();
            
        if (!value[0].empty() && !atomIDtoIndexMap.emplace(value[0], atom_idx).second && strictErrorChecking)
            throw Base::IOError("CMLDataReader: duplicate atom id '" + std::string(value[0]) + '\'');
  
        auto& atom = mol.addAtom();

        if (!value[1].empty()) {
            setSymbol(atom, std::string(value[1]));
            setType(atom, getTypeForSymbol(atom));
        }

        if (!value[2].empty())
            setFormalCharge(atom, parseNumber<long>(value[2].data(), value[2].data() + value[2].size(),
                                                    "CMLDataReader: error while parsing formal atom charge", strictErrorChecking));

        if (!value[3].empty() && !value[4].empty())
            set2DCoordinates(atom, {parseNumber<double>(value[3].data(), value[3].data() + value[3].size(),
                                                        "CMLDataReader: error while parsing atom 2D x-coordinate", strictErrorChecking),
                                    parseNumber<double>(value[4].data(), value[4].data() + value[4].size(),
                                                        "CMLDataReader: error while parsing atom 2D y-coordinate", strictErrorChecking)});

        if (!value[5].empty() && !value[6].empty() && !value[7].empty())
            set3DCoordinates(atom, {parseNumber<double>(value[5].data(), value[5].data() + value[5].size(),
                                                        "CMLDataReader: error while parsing atom 3D x-coordinate", strictErrorChecking),
                                    parseNumber<double>(value[6].data(), value[6].data() + value[6].size(),
                                                        "CMLDataReader: error while parsing atom 3D y-coordinate", strictErrorChecking),
                                    parseNumber<double>(value[7].data(), value[7].data() + value[7].size(),
                                                        "CMLDataReader: error while parsing atom 3D z-coordinate", strictErrorChecking)});
    }
}

void Chem::CMLDataReader::addAtom(const XMLNode* atom_node, Molecule& mol)
{
    using namespace Internal;

    auto atom_idx = mol.getNumAtoms();
    auto& atom = mol.addAtom();

    if (auto id_attr = atom_node->first_attribute(CML::Attribute::ID.c_str()))
        if (!atomIDtoIndexMap.emplace(id_attr->value(), atom_idx).second && strictErrorChecking)
            throw Base::IOError("CMLDataReader: duplicate atom id '" + std::string(id_attr->value()) + '\'');
    
    if (auto type_attr = atom_node->first_attribute(CML::Attribute::ELEMENT_TYPE.c_str())) {
        setSymbol(atom, type_attr->value());
        setType(atom, getTypeForSymbol(atom));
    }

    if (auto charge_attr = atom_node->first_attribute(CML::Attribute::FORMAL_CHARGE.c_str()))
        setFormalCharge(atom, parseNumber<long>(charge_attr->value(), charge_attr->value() + charge_attr->value_size(),
                                                "CMLDataReader: error while parsing formal atom charge", strictErrorChecking));

    if (auto spin_mul_attr = atom_node->first_attribute(CML::Attribute::SPIN_MULTIPLICITY.c_str())) {
        auto spin_mul = parseNumber<std::size_t>(spin_mul_attr->value(), spin_mul_attr->value() + spin_mul_attr->value_size(),
                                                 "CMLDataReader: error while parsing atom spin multiplicity", strictErrorChecking);
        if (spin_mul > 0)
            setUnpairedElectronCount(atom, spin_mul - 1);
    }

    if (auto iso_attr = atom_node->first_attribute(CML::Attribute::ISOTOPE.c_str()))
        setIsotope(atom, parseNumber<std::size_t>(iso_attr->value(), iso_attr->value() + iso_attr->value_size(),
                                                  "CMLDataReader: error while parsing atom isotope", strictErrorChecking));
       
    if (auto x2_attr = atom_node->first_attribute(CML::Attribute::X2.c_str()))
        if (auto y2_attr = atom_node->first_attribute(CML::Attribute::Y2.c_str()))
            set2DCoordinates(atom, {parseNumber<double>(x2_attr->value(), x2_attr->value() + x2_attr->value_size(),
                                                        "CMLDataReader: error while parsing atom 2D x-coordinate", strictErrorChecking),
                                    parseNumber<double>(y2_attr->value(), y2_attr->value() + y2_attr->value_size(),
                                                        "CMLDataReader: error while parsing atom 2D y-coordinate", strictErrorChecking)});

    if (auto x3_attr = atom_node->first_attribute(CML::Attribute::X3.c_str()))
        if (auto y3_attr = atom_node->first_attribute(CML::Attribute::Y3.c_str()))
            if (auto z3_attr = atom_node->first_attribute(CML::Attribute::Z3.c_str()))
                set3DCoordinates(atom, {parseNumber<double>(x3_attr->value(), x3_attr->value() + x3_attr->value_size(),
                                                            "CMLDataReader: error while parsing atom 3D x-coordinate", strictErrorChecking),
                                        parseNumber<double>(y3_attr->value(), y3_attr->value() + y3_attr->value_size(),
                                                            "CMLDataReader: error while parsing atom 3D y-coordinate", strictErrorChecking),
                                        parseNumber<double>(z3_attr->value(), z3_attr->value() + z3_attr->value_size(),
                                                            "CMLDataReader: error while parsing atom 3D z-coordinate", strictErrorChecking)});
    
    if (auto parity_node = getChildNode(atom_node, CML::Element::ATOM_PARITY))
        stereoAtoms.emplace_back(atom_idx, parity_node);
}

void Chem::CMLDataReader::readBonds(const XMLNode* bond_arr_node, Molecule& mol)
{
    auto init_bond_count = mol.getNumBonds();
    auto undef_orders = readArrayStyleBonds(bond_arr_node, mol);
    
    for (auto node = bond_arr_node->first_node(); node; node = node->next_sibling())
        if (nameMatches(node->name(), node->name_size(), CML::Element::BOND))
            undef_orders |= addBond(node, mol);

    if (undef_orders)
        perceiveBondOrders(mol, init_bond_count);
}

bool Chem::CMLDataReader::readArrayStyleBonds(const XMLNode* bond_arr_node, Molecule& mol) const
{
    using namespace Internal;
    
    const XMLAttribute* attrs[] = {
        bond_arr_node->first_attribute(CML::Attribute::REF_ATOM1_ARRAY.c_str()),
        bond_arr_node->first_attribute(CML::Attribute::REF_ATOM2_ARRAY.c_str()),
        bond_arr_node->first_attribute(CML::Attribute::ORDER_ARRAY.c_str())
    };

    if (!attrs[0] || !attrs[1]) {
        if (strictErrorChecking && (attrs[0] || attrs[1]))
            throw Base::IOError("CMLDataReader: missing '" + CML::Attribute::REF_ATOM1_ARRAY +
                                "' or '" + CML::Attribute::REF_ATOM2_ARRAY + "' attribute");

        return false;
    }
    
    constexpr std::size_t NUM_ATTR = sizeof(attrs) / sizeof(const XMLAttribute*);
        
    std::size_t value_offs[NUM_ATTR] = { 0 };
    std::string_view value[NUM_ATTR];
    auto undef_orders = false;
    
    while (true) {
        for (std::size_t i = 0; i < NUM_ATTR; i++)
            if (attrs[i]) {
                value[i] = nextToken(attrs[i]->value(), attrs[i]->value_size(), value_offs[i]);
                    
                if (value[i].empty())
                    return undef_orders;
            }

        std::size_t atom_inds[2];
        auto invalid = false;
        
        for (std::size_t i = 0; i < 2; i++) {
            auto atom_idx = atomIDtoIndexMap.find(value[i]);

            if (atom_idx == atomIDtoIndexMap.end()) {
                if (strictErrorChecking)
                    throw Base::IOError("CMLDataReader: bond atom with id '" + std::string(value[i]) + "' not found");
        
                invalid = true;
                break;
            }

            atom_inds[i] = atom_idx->second;
        }

        if (invalid)
            continue;

        if (value[2].empty()) {
            mol.addBond(atom_inds[0], atom_inds[1]);
            undef_orders = true;
            continue;
        }

        if (value[2] == CML::BondOrder::H_BOND)
            continue;

        auto& bond = mol.addBond(atom_inds[0], atom_inds[1]);
        
        if ((value[2] == CML::BondOrder::SINGLE_1) ||
            (value[2] == CML::BondOrder::SINGLE_2))
            setOrder(bond, 1);

        else if ((value[2] == CML::BondOrder::DOUBLE_1) ||
                 (value[2] == CML::BondOrder::DOUBLE_2))
            setOrder(bond, 2);
        
        else if ((value[2] == CML::BondOrder::TRIPLE_1) ||
                 (value[2] == CML::BondOrder::TRIPLE_2))
            setOrder(bond, 3);

        else if (strictErrorChecking && (value[2] != CML::BondOrder::PARTIAL01) &&
                 (value[2] != CML::BondOrder::PARTIAL12) && (value[2] != CML::BondOrder::PARTIAL23) &&
                 (value[2] != CML::BondOrder::AROMATIC) && (value[2] != CML::BondOrder::UNKNOWN))
            throw Base::IOError("CMLDataReader: invalid bond order '" + std::string(value[2]));

        else
            undef_orders = true;
    }
    
    return undef_orders;
}

bool Chem::CMLDataReader::addBond(const XMLNode* bond_node, Molecule& mol)
{
    auto atom_refs_attr = bond_node->first_attribute(CML::Attribute::REF_ATOMS2.c_str());

    if (!atom_refs_attr) {
        if (strictErrorChecking)
            throw Base::IOError("CMLDataReader: bond element missing '" + CML::Attribute::REF_ATOMS2 + "' attribute");
        
        return false;
    }

    std::size_t atom_inds[2];

    for (std::size_t i = 0, atom_id_offs = 0; i < 2; i++) {
        auto atom_id = nextToken(atom_refs_attr->value(), atom_refs_attr->value_size(), atom_id_offs);

        if (atom_id.empty()) {
            if (strictErrorChecking)
                throw Base::IOError("CMLDataReader: bond atom id" + std::to_string(i + 1) + " not specified");
        
            return false;
        }
     
        auto atom_idx = atomIDtoIndexMap.find(atom_id);

        if (atom_idx == atomIDtoIndexMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("CMLDataReader: bond atom with id '" + std::string(atom_id) + "' not found");
        
            return false;
        }

        atom_inds[i] = atom_idx->second;
    }
    
    std::size_t order = 0;
    
    if (auto order_attr = bond_node->first_attribute(CML::Attribute::ORDER.c_str())) {
        if (order_attr->value() == CML::BondOrder::H_BOND)
            return false;

        if ((order_attr->value() == CML::BondOrder::SINGLE_1) ||
            (order_attr->value() == CML::BondOrder::SINGLE_2))
            order = 1;

        else if ((order_attr->value() == CML::BondOrder::DOUBLE_1) ||
            (order_attr->value() == CML::BondOrder::DOUBLE_2))
            order = 2;
        
        else if ((order_attr->value() == CML::BondOrder::TRIPLE_1) ||
            (order_attr->value() == CML::BondOrder::TRIPLE_2))
            order = 3;

        else if (strictErrorChecking && (order_attr->value() != CML::BondOrder::PARTIAL01) &&
                 (order_attr->value() != CML::BondOrder::PARTIAL12) && (order_attr->value() != CML::BondOrder::PARTIAL23) &&
                 (order_attr->value() != CML::BondOrder::AROMATIC) && (order_attr->value() != CML::BondOrder::UNKNOWN))
            throw Base::IOError("CMLDataReader: invalid bond order '" + std::string(order_attr->value()));
    }
    
    auto& bond = mol.addBond(atom_inds[0], atom_inds[1]);

    if (order > 0)
        setOrder(bond, order);

    if (auto stereo_node = getChildNode(bond_node, CML::Element::BOND_STEREO))
        stereoBonds.emplace_back(bond.getIndex(), stereo_node);
    
    return (order == 0);
}

void Chem::CMLDataReader::setName(const XMLNode* name_node, Molecule& mol) const
{
    Chem::setName(mol, name_node->value());
}

void Chem::CMLDataReader::addProperty(const XMLNode* prop_node, Molecule& mol) const
{
    auto title_attr = prop_node->first_attribute(CML::Attribute::TITLE.c_str());

    if (!title_attr)
        return;

    auto value_attr = getChildNode(prop_node, CML::Element::SCALAR);

    if (!value_attr)
        return;

    StringDataBlock::SharedPointer props;

    if (hasStructureData(mol))
        props = getStructureData(mol);

    else {
        props.reset(new StringDataBlock());
        setStructureData(mol, props);
    }

    props->addEntry(title_attr->value(), value_attr->value());
}

void Chem::CMLDataReader::postprocStereoAtoms(Molecule& mol) const
{
    for (auto& sa : stereoAtoms) {
        auto par_node = sa.second;
        auto atom_refs_attr = par_node->first_attribute(CML::Attribute::REF_ATOMS4.c_str());

        if (!atom_refs_attr) {
            if (strictErrorChecking)
                throw Base::IOError("CMLDataReader: atom parity reference atom ids not specified");

            continue;
        }

        std::size_t ref_atom_inds[4];
        std::size_t num_ref_atoms = 0;
        
        for (std::size_t i = 0, atom_id_offs = 0; i < 4; i++, num_ref_atoms++) {
            auto atom_id = nextToken(atom_refs_attr->value(), atom_refs_attr->value_size(), atom_id_offs);

            if (atom_id.empty()) {
                if (strictErrorChecking)
                    throw Base::IOError("CMLDataReader: atom parity reference atom " + std::to_string(i + 1) + " id not specified");

                break;
            }
     
            auto atom_idx = atomIDtoIndexMap.find(atom_id);

            if (atom_idx == atomIDtoIndexMap.end()) {
                if (strictErrorChecking)
                    throw Base::IOError("CMLDataReader: atom parity reference atom with id '" + std::string(atom_id) + "' not found");
        
                break;
            }

            ref_atom_inds[i] = atom_idx->second;
        }

        if (num_ref_atoms != 4)
            continue;
        
        auto parity = Internal::parseNumber<int>(par_node->value(), par_node->value() + par_node->value_size(),
                                                 "CMLDataReader: error while parsing atom parity value", strictErrorChecking);
        if (parity == 0)
            continue;
            
        auto config = (parity < 0 ? AtomConfiguration::R : AtomConfiguration::S);
        auto& atom = mol.getAtom(sa.first);
        
        auto descr = (ref_atom_inds[3] != sa.first ?
                      StereoDescriptor(config, mol.getAtom(ref_atom_inds[0]), mol.getAtom(ref_atom_inds[1]),
                                       mol.getAtom(ref_atom_inds[2]), mol.getAtom(ref_atom_inds[3])) :
                      StereoDescriptor(config, mol.getAtom(ref_atom_inds[0]), mol.getAtom(ref_atom_inds[1]),
                                       mol.getAtom(ref_atom_inds[2])));

        if (!descr.isValid(atom)) {
            if (strictErrorChecking)
                throw Base::IOError("CMLDataReader: invalid atom parity reference atom sequence");

           continue;
        }
        
        setStereoDescriptor(atom, descr);
    }
}

void Chem::CMLDataReader::postprocStereoBonds(Molecule& mol) const
{
     for (auto& sb : stereoBonds)
         postprocStereoBond(sb.second, mol.getBond(sb.first), mol);
}

void Chem::CMLDataReader::postprocStereoBond(const XMLNode* stereo_node, Bond& bond, Molecule& mol) const
{
    if (auto atom_refs_attr = stereo_node->first_attribute(CML::Attribute::REF_ATOMS2.c_str())) {
        std::size_t atom_inds[2];

        for (std::size_t i = 0, atom_id_offs = 0; i < 2; i++) {
            auto atom_id = nextToken(atom_refs_attr->value(), atom_refs_attr->value_size(), atom_id_offs);

            if (atom_id.empty()) {
                if (strictErrorChecking)
                    throw Base::IOError("CMLDataReader: stereo bond atom " + std::to_string(i + 1) + " id not specified");
        
                return;
            }
     
            auto atom_idx = atomIDtoIndexMap.find(atom_id);

            if (atom_idx == atomIDtoIndexMap.end()) {
                if (strictErrorChecking)
                    throw Base::IOError("CMLDataReader: stereo bond atom with id '" + std::string(atom_id) + "' not found");
        
                return;
            }

            atom_inds[i] = atom_idx->second;
        }
    
        auto stereo_flag = BondStereoFlag::PLAIN;

        if (stereo_node->value() == CML::BondStereo::WEDGED)
            stereo_flag = BondStereoFlag::UP;

        else if (stereo_node->value() == CML::BondStereo::HATCHED)
            stereo_flag = BondStereoFlag::DOWN;

        else {
            if (strictErrorChecking)
                throw Base::IOError("CMLDataReader: invalid bond stereo specification '" + std::string(stereo_node->value()) + '\'');

            return;
        }

        if ((mol.getAtomIndex(bond.getBegin()) == atom_inds[0]) && (mol.getAtomIndex(bond.getEnd()) == atom_inds[1]))
            set2DStereoFlag(bond, stereo_flag);

        else if ((mol.getAtomIndex(bond.getBegin()) == atom_inds[1]) && (mol.getAtomIndex(bond.getEnd()) == atom_inds[1]))
            set2DStereoFlag(bond, stereo_flag == BondStereoFlag::UP ? BondStereoFlag::REVERSE_UP : BondStereoFlag::REVERSE_DOWN);
                
        else if (strictErrorChecking)
            throw Base::IOError("CMLDataReader: invalid stereo bond atom ids");
        
        return;
    }

    auto atom_refs_attr = stereo_node->first_attribute(CML::Attribute::REF_ATOMS4.c_str());

    if (!atom_refs_attr) {
        if (strictErrorChecking)
            throw Base::IOError("CMLDataReader: bond stereo reference atom ids not specified");
        
        return;
    }

    std::size_t ref_atom_inds[4];

    for (std::size_t i = 0, atom_id_offs = 0; i < 4; i++) {
        auto atom_id = nextToken(atom_refs_attr->value(), atom_refs_attr->value_size(), atom_id_offs);

        if (atom_id.empty()) {
            if (strictErrorChecking)
                throw Base::IOError("CMLDataReader: bond stereo reference atom " + std::to_string(i + 1) + " id not specified");
        
            return;
        }
     
        auto atom_idx = atomIDtoIndexMap.find(atom_id);

        if (atom_idx == atomIDtoIndexMap.end()) {
            if (strictErrorChecking)
                throw Base::IOError("CMLDataReader: bond stereo reference atom with id '" + std::string(atom_id) + "' not found");
        
            return;
        }

        ref_atom_inds[i] = atom_idx->second;
    }

    auto config = BondConfiguration::UNDEF;

    if (stereo_node->value() == CML::BondStereo::CIS)
        config = BondConfiguration::CIS;

    else if (stereo_node->value() == CML::BondStereo::TRANS)
        config = BondConfiguration::TRANS;

    else {
        if (strictErrorChecking)
            throw Base::IOError("CMLDataReader: invalid bond stereo specification '" + std::string(stereo_node->value()) + '\'');
        
        return;
    }

    StereoDescriptor descr(config, mol.getAtom(ref_atom_inds[0]), mol.getAtom(ref_atom_inds[1]),
                           mol.getAtom(ref_atom_inds[2]), mol.getAtom(ref_atom_inds[3]));

    if (!descr.isValid(bond)) {
        if (strictErrorChecking)
            throw Base::IOError("CMLDataReader: invalid bond stereo reference atom sequence");

        return;
    }

    setStereoDescriptor(bond, descr);
}

void Chem::CMLDataReader::perceiveBondOrders(Molecule& mol, std::size_t bond_offs)
{
    if (bond_offs == 0) {
        perceiveSSSR(mol, true);
        setRingFlags(mol, true);

        Chem::perceiveBondOrders(mol, false);
        return;
    }

    if (!readMolGraph)
        readMolGraph.reset(new Fragment());
    else
        readMolGraph->clear();

    std::for_each(mol.getBondsBegin() + bond_offs, mol.getBondsEnd(), 
                  [&](const Chem::Bond& bond) { readMolGraph->addBond(bond); });

    setRingFlags(*readMolGraph, true);
    
    Chem::perceiveBondOrders(*readMolGraph, false);
}
            
const Chem::CMLDataReader::XMLNode* Chem::CMLDataReader::getChildNode(const XMLNode* prnt_node, const std::string& name) const
{
    for (auto node = prnt_node->first_node(); node; node = node->next_sibling())
        if (nameMatches(node->name(), node->name_size(), name))
            return node;

    return nullptr;
}
