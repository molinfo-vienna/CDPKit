/* 
 * MMCIFDataWriter.cpp 
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

#include <cmath>
#include <algorithm>
#include <locale>

#include <boost/functional/hash.hpp>
#include <boost/algorithm/string.hpp>

#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/ResidueType.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/MolProp/MolecularGraphFunctions.hpp"
#include "CDPL/MolProp/AtomContainerFunctions.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"

#include "MMCIFDataWriter.hpp"
#include "MMCIFFormatData.hpp"


using namespace CDPL;


namespace
{

    const std::string& stripWS(const std::string& in_str, std::string& out_str)
    {
        out_str.clear();
        
        for (auto c : in_str)
            if (!Biomol::MMCIF::isSpace(c))
                out_str.push_back(c);

        return out_str;
    }

    inline std::string toString(double val)
    {
        if (std::isnan(val) || std::isinf(val))
            return Biomol::MMCIF::MISSING_DATA_VALUE;

        const auto& str = std::to_string(val);

        if (str.length() < 4)
            return str;

        auto rbeg = str.rbegin();
        auto rend = str.rend();

        if (std::find_if(rbeg, rend, [](char c) { return ((c == 'e') || (c == 'E')); }) != rend)
            return str;

        if (str.find('.') == std::string::npos)
            return str;
     
        auto rit = std::find_if(rbeg, rend, [](char c) { return (c != '0'); });

        if (rit == rbeg)
            return str;

        if ((*rit == '.') && (--rit == rbeg))
            return str;
        
        return std::string(rend.base(), rit.base());
    }
    
    inline long getResidueID(const Chem::Atom& atom)
    {
        using namespace Biomol;
        
        return (getResidueSequenceNumber(atom) * (1 << (sizeof(char) * 8)) + getResidueInsertionCode(atom));
    }

    void outputSymbol(const Chem::Atom& atom, Biomol::MMCIFData::Item& item)
    {
        if (hasSymbol(atom)) {
            auto& symbol = getSymbol(atom);
            
            if (Chem::AtomDictionary::isChemicalElement(Chem::AtomDictionary::getType(symbol, false)))
                item.addValue(boost::to_upper_copy(symbol));
            else
                item.addValue(symbol);

        } else {
            auto type = getType(atom);

            if ((type == Chem::AtomType::UNKNOWN) || (type > Chem::AtomType::MAX_TYPE))
                item.addValue(Biomol::MMCIF::MISSING_DATA_VALUE);
            else
                item.addValue(boost::to_upper_copy(Chem::AtomDictionary::getSymbol(type)));
        }
    }

    template <typename AE>
    std::size_t arrayElemSum(const std::size_t* array, const AE& elem_inds)
    {
        std::size_t sum = 0;

        for (auto i : elem_inds)
            sum += array[i];
        
        return sum;
    }
    
    typedef std::unordered_map<unsigned int, std::string> ResidueTypeToStringMap;

    ResidueTypeToStringMap resTypeToStringMap{
      { Biomol::ResidueType::UNKNOWN, Biomol::MMCIF::MISSING_DATA_VALUE },
      { Biomol::ResidueType::OTHER, Biomol::MMCIF::ChemComp::Type::OTHER },
      { Biomol::ResidueType::NON_POLYMER, Biomol::MMCIF::ChemComp::Type::NON_POLYMER },
      { Biomol::ResidueType::L_PEPTIDE_CARBOXY_TERMINUS, Biomol::MMCIF::ChemComp::Type::L_PEPTIDE_CARBOXY_TERMINUS },
      { Biomol::ResidueType::D_PEPTIDE_AMINO_TERMINUS, Biomol::MMCIF::ChemComp::Type::D_PEPTIDE_AMINO_TERMINUS },
      { Biomol::ResidueType::L_PEPTIDE_AMINO_TERMINUS, Biomol::MMCIF::ChemComp::Type::L_PEPTIDE_AMINO_TERMINUS },
      { Biomol::ResidueType::RNA_3_HYDROXY_TERMINUS, Biomol::MMCIF::ChemComp::Type::RNA_3_HYDROXY_TERMINUS },
      { Biomol::ResidueType::RNA_5_HYDROXY_TERMINUS, Biomol::MMCIF::ChemComp::Type::RNA_5_HYDROXY_TERMINUS },
      { Biomol::ResidueType::DNA_3_HYDROXY_TERMINUS, Biomol::MMCIF::ChemComp::Type::DNA_3_HYDROXY_TERMINUS },
      { Biomol::ResidueType::DNA_5_HYDROXY_TERMINUS, Biomol::MMCIF::ChemComp::Type::DNA_5_HYDROXY_TERMINUS },
      { Biomol::ResidueType::PEPTIDE_LINKING, Biomol::MMCIF::ChemComp::Type::PEPTIDE_LINKING },
      { Biomol::ResidueType::L_PEPTIDE_LINKING, Biomol::MMCIF::ChemComp::Type::L_PEPTIDE_LINKING },
      { Biomol::ResidueType::D_PEPTIDE_LINKING, Biomol::MMCIF::ChemComp::Type::D_PEPTIDE_LINKING },
      { Biomol::ResidueType::L_BETA_PEPTIDE_LINKING, Biomol::MMCIF::ChemComp::Type::L_BETA_PEPTIDE_LINKING },
      { Biomol::ResidueType::D_BETA_PEPTIDE_LINKING, Biomol::MMCIF::ChemComp::Type::D_BETA_PEPTIDE_LINKING },
      { Biomol::ResidueType::L_GAMMA_PEPTIDE_LINKING, Biomol::MMCIF::ChemComp::Type::L_GAMMA_PEPTIDE_LINKING },
      { Biomol::ResidueType::D_GAMMA_PEPTIDE_LINKING, Biomol::MMCIF::ChemComp::Type::D_GAMMA_PEPTIDE_LINKING },
      { Biomol::ResidueType::PEPTIDE_LIKE, Biomol::MMCIF::ChemComp::Type::PEPTIDE_LIKE },
      { Biomol::ResidueType::RNA_LINKING, Biomol::MMCIF::ChemComp::Type::RNA_LINKING },
      { Biomol::ResidueType::DNA_LINKING, Biomol::MMCIF::ChemComp::Type::DNA_LINKING },
      { Biomol::ResidueType::L_RNA_LINKING, Biomol::MMCIF::ChemComp::Type::L_RNA_LINKING },
      { Biomol::ResidueType::L_DNA_LINKING, Biomol::MMCIF::ChemComp::Type::L_DNA_LINKING },
      { Biomol::ResidueType::L_SACCHARIDE_1_4_LINKING, Biomol::MMCIF::ChemComp::Type::L_SACCHARIDE_1_4_LINKING },
      { Biomol::ResidueType::D_SACCHARIDE_1_4_LINKING, Biomol::MMCIF::ChemComp::Type::D_SACCHARIDE_1_4_LINKING },
      { Biomol::ResidueType::L_SACCHARIDE_ALPHA_LINKING, Biomol::MMCIF::ChemComp::Type::L_SACCHARIDE_ALPHA_LINKING },
      { Biomol::ResidueType::L_SACCHARIDE_BETA_LINKING, Biomol::MMCIF::ChemComp::Type::L_SACCHARIDE_BETA_LINKING },
      { Biomol::ResidueType::D_SACCHARIDE_ALPHA_LINKING, Biomol::MMCIF::ChemComp::Type::D_SACCHARIDE_ALPHA_LINKING },
      { Biomol::ResidueType::D_SACCHARIDE_BETA_LINKING, Biomol::MMCIF::ChemComp::Type::D_SACCHARIDE_BETA_LINKING },
      { Biomol::ResidueType::L_SACCHARIDE, Biomol::MMCIF::ChemComp::Type::L_SACCHARIDE },
      { Biomol::ResidueType::D_SACCHARIDE, Biomol::MMCIF::ChemComp::Type::D_SACCHARIDE },
      { Biomol::ResidueType::SACCHARIDE, Biomol::MMCIF::ChemComp::Type::SACCHARIDE }
    };

    constexpr std::size_t L_PEPTIDE_RES_TYPES[] = {
        Biomol::ResidueType::PEPTIDE_LINKING,
        Biomol::ResidueType::L_PEPTIDE_LINKING,
        Biomol::ResidueType::L_GAMMA_PEPTIDE_LINKING,
        Biomol::ResidueType::NON_POLYMER
    };

    constexpr std::size_t D_PEPTIDE_RES_TYPES[] = {
        Biomol::ResidueType::PEPTIDE_LINKING,
        Biomol::ResidueType::D_PEPTIDE_LINKING,
        Biomol::ResidueType::D_GAMMA_PEPTIDE_LINKING,
        Biomol::ResidueType::NON_POLYMER
    };

    constexpr std::size_t POLYDEOXYRIBONUCLEOTIDE_RES_TYPES[] = {
        Biomol::ResidueType::DNA_LINKING,
        Biomol::ResidueType::L_DNA_LINKING,
        Biomol::ResidueType::NON_POLYMER
    };

    constexpr std::size_t POLYRIBONUCLEOTIDE_RES_TYPES[] = {
        Biomol::ResidueType::RNA_LINKING,
        Biomol::ResidueType::L_RNA_LINKING,
        Biomol::ResidueType::NON_POLYMER
    };

    constexpr std::size_t POLYNUCLEOTIDE_HYBRID_RES_TYPES[] = {
        Biomol::ResidueType::RNA_LINKING,
        Biomol::ResidueType::DNA_LINKING,
        Biomol::ResidueType::L_RNA_LINKING,
        Biomol::ResidueType::L_DNA_LINKING,
        Biomol::ResidueType::NON_POLYMER
    };

    const std::string DEF_DATA_BLOCK_ID_PREFIX    = "MOL";
    const std::string WATER_ENTITY_DESCR          = "water";
    const std::string DISULF_BOND_ID_PREFIX       = Biomol::MMCIF::StructConn::Type::DISULF;
    const std::string COVAL_BOND_ID_PREFIX        = Biomol::MMCIF::StructConn::Type::COVALE;

    constexpr std::size_t MAX_OLC_SEQ_LINE_LENGTH = 80;
    constexpr double      WATER_WEIGHT            = 18.015;
}


bool Biomol::MMCIFDataWriter::Entity::StringPtrLessCmpFunc::operator()(const std::string* str1, const std::string* str2) const
{
    return (*str1 < *str2);
}


std::size_t Biomol::MMCIFDataWriter::ChemComp::BondIDHashFunc::operator()(const BondID& bond_id) const
{
    std::size_t h = 0;

    boost::hash_combine(h, *bond_id.first);
    boost::hash_combine(h, *bond_id.second);

    return h;
}


bool Biomol::MMCIFDataWriter::ChemComp::BondIDCmpFunc::operator()(const BondID& bond_id1, const BondID& bond_id2) const
{
    return ((*bond_id1.first == *bond_id2.first) && (*bond_id1.second == *bond_id2.second));
}


bool Biomol::MMCIFDataWriter::CIStringPtrLessCmpFunc::operator()(const std::string* str1, const std::string* str2) const
{
    return std::lexicographical_compare(str1->begin(), str1->end(), str2->begin(), str2->end(), [](char c1, char c2) {
        return (std::tolower(c1, std::locale::classic()) < std::tolower(c2, std::locale::classic()));
    });
}


Biomol::MMCIFDataWriter::MMCIFDataWriter(const Base::DataIOBase& io_base):
    ioBase(io_base), numOutDataBlocks(0)
{}

bool Biomol::MMCIFDataWriter::writeMolecularGraph(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    init(os);

    setDataBlockId(molgraph);
    
    if (outputAsChemComp || !outputMacromolData(molgraph))
        outputChemCompData(molgraph);

    if (dataPostprocFunc)
        dataPostprocFunc(mmCIFData, molgraph);
    
    return (os << mmCIFData).good();
}

void Biomol::MMCIFDataWriter::init(std::ostream& os)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
    resDictionary       = getResidueDictionaryParameter(ioBase);
    dataPostprocFunc    = getMMCIFOutputDataPostprocFunctionParameter(ioBase);
    outputAsChemComp    = getMMCIFOutputBiopolymersAsChemCompParameter(ioBase);

    mmCIFData.clear();
    numOutDataBlocks++;
}

bool Biomol::MMCIFDataWriter::outputMacromolData(const Chem::MolecularGraph& molgraph)
{
    if (!prepAtomSiteData(molgraph))
        return false;

    prepMacromolCompData();
    prepStructConnData(molgraph);
    prepEntityData(molgraph);

    outputAtomSiteData(molgraph);
    outputAtomTypeData();
    outputStructConnData(molgraph);
    outputMacromolCompData();
    outputEntityPolySeqData();
    outputEntityPolyData();
    outputEntityData();    
    outputEntryData();
    outputMacromolCompAtomData();
    outputMacromolCompBondData();
            
    return true;
}

void Biomol::MMCIFDataWriter::outputEntryData()
{
    mmCIFData.addCategory(MMCIF::Entry::NAME, true).addItem(MMCIF::Entry::Item::ID).addValue(mmCIFData.getID());
}

void Biomol::MMCIFDataWriter::outputEntityData()
{
    auto& entity_cat = mmCIFData.addCategory(MMCIF::Entity::NAME, true);
    auto& ids = entity_cat.addItem(MMCIF::Entity::Item::ID);
    auto& types = entity_cat.addItem(MMCIF::Entity::Item::TYPE);
    auto& src_methods = entity_cat.addItem(MMCIF::Entity::Item::SRC_METHOD);
    auto& descriptions = entity_cat.addItem(MMCIF::Entity::Item::PDBX_DESCRIPTION);
    auto& weights = entity_cat.addItem(MMCIF::Entity::Item::FORMULA_WEIGHT);
    auto& counts = entity_cat.addItem(MMCIF::Entity::Item::PDBX_NUM_MOLECULES);
    auto& details = entity_cat.addItem(MMCIF::Entity::Item::DETAILS);

    for (auto& entity : entities) {
        ids.addValue(entity.id);
        types.addValue(*entity.type);
        details.addValue(MMCIF::MISSING_DATA_VALUE);
        src_methods.addValue(*entity.srcMethod);
        descriptions.addValue(*entity.descr);
        counts.addValue(std::to_string(entity.count));
        weights.addValue(toString(entity.weight));
    }
}

void Biomol::MMCIFDataWriter::outputEntityPolyData()
{
    using namespace MMCIF;

    auto& entity_poly = mmCIFData.addCategory(EntityPoly::NAME, true);
    auto& entity_ids = entity_poly.addItem(EntityPoly::Item::ENTITY_ID);
    auto& types = entity_poly.addItem(EntityPoly::Item::TYPE);
    auto& nstd_lkg_flags = entity_poly.addItem(EntityPoly::Item::NSTD_LINKAGE);
    auto& nstd_mon_flags = entity_poly.addItem(EntityPoly::Item::NSTD_MONOMER);
    auto& olc_seqs = entity_poly.addItem(EntityPoly::Item::PDBX_SEQ_ONE_LETTER_CODE);
    auto& can_olc_seqs = entity_poly.addItem(EntityPoly::Item::PDBX_SEQ_ONE_LETTER_CODE_CAN);
    auto& strand_ids = entity_poly.addItem(EntityPoly::Item::PDBX_STRAND_ID);
    auto& target_ids = entity_poly.addItem(EntityPoly::Item::PDBX_TARGET_ID);
 
    std::string olc_seq;
    std::string can_olc_seq;
    
    for (auto& entity : entities) {
        if (entity.resSequence.size() <= 1)
            continue;

        entity_ids.addValue(entity.id);
        
        auto has_nstd_mon = genEntityPolySeqStrings(entity, olc_seq, can_olc_seq);
       
        olc_seqs.addValue(std::move(olc_seq));
        can_olc_seqs.addValue(std::move(can_olc_seq));
        types.addValue(getPolymerEntityType(entity));
        nstd_lkg_flags.addValue(MISSING_DATA_VALUE);  // TODO
        nstd_mon_flags.addValue(boost::to_lower_copy(has_nstd_mon ? TRUE_FLAG_2 : FALSE_FLAG_2));
     
        tmpString.clear();

        for (auto chain_id : entity.chains) {
            if (!tmpString.empty())
                tmpString.push_back(',');

            tmpString.append(*chain_id);
        }

        if (tmpString.empty())
            strand_ids.addValue(UNDEFINED_DATA_VALUE);
        else
            strand_ids.addValue(std::move(tmpString));
        
        target_ids.addValue(MISSING_DATA_VALUE);
    }
}

void Biomol::MMCIFDataWriter::outputEntityPolySeqData()
{
    using namespace MMCIF;

    auto& entity_seq = mmCIFData.addCategory(EntityPolySeq::NAME, true);
    auto& entity_ids = entity_seq.addItem(EntityPolySeq::Item::ENTITY_ID);
    auto& res_seq_nums = entity_seq.addItem(EntityPolySeq::Item::NUM);
    auto& mon_ids = entity_seq.addItem(EntityPolySeq::Item::MON_ID);
    auto& hetero_flags = entity_seq.addItem(EntityPolySeq::Item::HETERO);

    std::string false_flag(boost::to_lower_copy(MMCIF::FALSE_FLAG_1));
    
    for (auto& entity : entities) {
        if (entity.resSequence.size() <= 1)
            continue;
        
        for (auto& res : entity.resSequence) {
            entity_ids.addValue(entity.id);
            res_seq_nums.addValue(std::to_string(res.second));
            mon_ids.addValue(*res.first);
            hetero_flags.addValue(false_flag);
        }
    }
}

void Biomol::MMCIFDataWriter::outputStructConnData(const Chem::MolecularGraph& molgraph)
{
    using namespace MMCIF;

    if (disulfBonds.empty() && nonStdBonds.empty())
        return;
    
    auto& struct_cons = mmCIFData.addCategory(StructConn::NAME, true);
    auto& ids = struct_cons.addItem(StructConn::Item::ID);
    auto& type_ids = struct_cons.addItem(StructConn::Item::CONN_TYPE_ID);
    auto& lvg_flags = struct_cons.addItem(StructConn::Item::PDBX_LEAVING_ATOM_FLAG);
    auto& pdb_ids = struct_cons.addItem(StructConn::Item::PDBX_PDB_ID);
    auto& ptnr1_asym_ids = struct_cons.addItem(StructConn::Item::PTNR1_LABEL_ASYM_ID);
    auto& ptnr1_comp_ids = struct_cons.addItem(StructConn::Item::PTNR1_LABEL_COMP_ID);
    auto& ptnr1_seq_ids = struct_cons.addItem(StructConn::Item::PTNR1_LABEL_SEQ_ID);
    auto& ptnr1_atom_ids = struct_cons.addItem(StructConn::Item::PTNR1_LABEL_ATOM_ID);
    auto& pdbx_ptnr1_alt_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR1_LABEL_ALT_ID);
    auto& ptnr1_ins_codes = struct_cons.addItem(StructConn::Item::PDBX_PTNR1_PDB_INS_CODE);
    auto& ptnr1_std_comp_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR1_STD_COMP_ID);
    auto& ptnr1_syms = struct_cons.addItem(StructConn::Item::PTNR1_SYMMETRY);
    auto& ptnr2_asym_ids = struct_cons.addItem(StructConn::Item::PTNR2_LABEL_ASYM_ID);
    auto& ptnr2_comp_ids = struct_cons.addItem(StructConn::Item::PTNR2_LABEL_COMP_ID);
    auto& ptnr2_seq_ids = struct_cons.addItem(StructConn::Item::PTNR2_LABEL_SEQ_ID);
    auto& ptnr2_atom_ids = struct_cons.addItem(StructConn::Item::PTNR2_LABEL_ATOM_ID);
    auto& pdbx_ptnr2_alt_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR2_LABEL_ALT_ID);
    auto& ptnr2_ins_codes = struct_cons.addItem(StructConn::Item::PDBX_PTNR2_PDB_INS_CODE);
    auto& ptnr1_auth_asym_ids = struct_cons.addItem(StructConn::Item::PTNR1_AUTH_ASYM_ID);
    auto& ptnr1_auth_comp_ids = struct_cons.addItem(StructConn::Item::PTNR1_AUTH_COMP_ID);
    auto& ptnr1_auth_seq_ids = struct_cons.addItem(StructConn::Item::PTNR1_AUTH_SEQ_ID);
    auto& ptnr2_auth_asym_ids = struct_cons.addItem(StructConn::Item::PTNR2_AUTH_ASYM_ID);
    auto& ptnr2_auth_comp_ids = struct_cons.addItem(StructConn::Item::PTNR2_AUTH_COMP_ID);
    auto& ptnr2_auth_seq_ids = struct_cons.addItem(StructConn::Item::PTNR2_AUTH_SEQ_ID);
    auto& ptnr2_syms = struct_cons.addItem(StructConn::Item::PTNR2_SYMMETRY);
    auto& ptnr3_atom_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR3_LABEL_ATOM_ID);
    auto& ptnr3_seq_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR3_LABEL_SEQ_ID);
    auto& ptnr3_comp_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR3_LABEL_COMP_ID);
    auto& ptnr3_asym_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR3_LABEL_ASYM_ID);
    auto& ptnr3_alt_ids = struct_cons.addItem(StructConn::Item::PDBX_PTNR3_LABEL_ALT_ID);
    auto& ptnr3_ins_codes = struct_cons.addItem(StructConn::Item::PDBX_PTNR3_PDB_INS_CODE);
    auto& details = struct_cons.addItem(StructConn::Item::DETAILS);
    auto& dist_values = struct_cons.addItem(StructConn::Item::PDBX_DIST_VALUE);
    auto& orders = struct_cons.addItem(StructConn::Item::PDBX_VALUE_ORDER);
    auto& roles = struct_cons.addItem(StructConn::Item::PDBX_ROLE);

    auto& struct_con_types = mmCIFData.addCategory(StructConnType::NAME, true);
    auto& sct_id = struct_con_types.addItem(StructConnType::Item::ID);
    auto& sct_crit = struct_con_types.addItem(StructConnType::Item::CRITERIA);
    auto& sct_ref = struct_con_types.addItem(StructConnType::Item::REFERENCE);

    if (!disulfBonds.empty()) {
        sct_id.addValue(StructConn::Type::DISULF);
        sct_crit.addValue(MISSING_DATA_VALUE);
        sct_ref.addValue(MISSING_DATA_VALUE);
    }

    if (!nonStdBonds.empty()) {
        sct_id.addValue(StructConn::Type::COVALE);
        sct_crit.addValue(MISSING_DATA_VALUE);
        sct_ref.addValue(MISSING_DATA_VALUE);
    }

    for (int i = 0; i < 2; i++) {
        auto& bond_set = (i == 0 ? disulfBonds : nonStdBonds);
        auto& id_pfx = (i == 0 ? DISULF_BOND_ID_PREFIX : COVAL_BOND_ID_PREFIX);
        auto& type_id = (i == 0 ? StructConn::Type::DISULF : StructConn::Type::COVALE);
        std::size_t id = 1;
        
        for (auto bond : bond_set) {
            auto& atom1 = bond->getBegin();
            auto& atom2 = bond->getEnd();
            
            ids.addValue(id_pfx + std::to_string(id++));
            type_ids.addValue(type_id);
            
            if (has3DCoordinates(atom1) && has3DCoordinates(atom2))
                dist_values.addValue(std::to_string(length(get3DCoordinates(atom1) - get3DCoordinates(atom2))));
            else
                dist_values.addValue(MISSING_DATA_VALUE);

            if (i) {
                switch (hasMissingLeavingAtomNbrs(atom1, *bond, molgraph) + hasMissingLeavingAtomNbrs(atom2, *bond, molgraph)) {

                    case 1:
                        lvg_flags.addValue(StructConn::LeavingAtomFlag::ONE);
                        break;

                    case 2:
                        lvg_flags.addValue(StructConn::LeavingAtomFlag::BOTH);
                        break;

                    default:
                        lvg_flags.addValue(StructConn::LeavingAtomFlag::NONE);
                }
                
            } else
                lvg_flags.addValue(MISSING_DATA_VALUE);

            switch (getOrder(*bond)) {

                case 1:
                    orders.addValue(StructConn::Order::SINGLE);
                    break;
                    
                case 2:
                    orders.addValue(StructConn::Order::DOUBLE);
                    break;
                    
                case 3:
                    orders.addValue(StructConn::Order::TRIPLE);
                    break;
                    
                default:
                    orders.addValue(MISSING_DATA_VALUE);
            }

            auto& atom1_asym_id = getChainID(atom1);
            auto& atom2_asym_id = getChainID(atom2);
            
            ptnr1_asym_ids.addValue(atom1_asym_id);
            ptnr1_auth_asym_ids.addValue(atom1_asym_id);
            ptnr2_asym_ids.addValue(atom2_asym_id);
            ptnr2_auth_asym_ids.addValue(atom2_asym_id);

            auto& atom1_comp_id = getResidueCode(atom1);
            auto& atom2_comp_id = getResidueCode(atom2);
            
            ptnr1_comp_ids.addValue(atom1_comp_id);
            ptnr1_auth_comp_ids.addValue(atom1_comp_id);
            ptnr2_comp_ids.addValue(atom2_comp_id);
            ptnr2_auth_comp_ids.addValue(atom2_comp_id);            

            tmpString = std::to_string(getResidueSequenceNumber(atom1));
                
            ptnr1_seq_ids.addValue(tmpString);
            ptnr1_auth_seq_ids.addValue(std::move(tmpString));

            tmpString = std::to_string(getResidueSequenceNumber(atom2));
    
            ptnr2_seq_ids.addValue(tmpString);
            ptnr2_auth_seq_ids.addValue(std::move(tmpString));
            
            ptnr1_atom_ids.addValue(getResidueAtomName(atom1));
            ptnr2_atom_ids.addValue(getResidueAtomName(atom2));
            ptnr1_ins_codes.addValue(hasResidueInsertionCode(atom1) ? std::string(1, getResidueInsertionCode(atom1)) : MISSING_DATA_VALUE);
            ptnr2_ins_codes.addValue(hasResidueInsertionCode(atom1) ? std::string(1, getResidueInsertionCode(atom2)) : MISSING_DATA_VALUE);
            
            pdbx_ptnr1_alt_ids.addValue(MISSING_DATA_VALUE);
            ptnr1_std_comp_ids.addValue(MISSING_DATA_VALUE);
            ptnr1_syms.addValue(MISSING_DATA_VALUE);
            pdbx_ptnr2_alt_ids.addValue(MISSING_DATA_VALUE);
            ptnr2_syms.addValue(MISSING_DATA_VALUE);
            pdb_ids.addValue(MISSING_DATA_VALUE);
            ptnr3_atom_ids.addValue(MISSING_DATA_VALUE);
            ptnr3_seq_ids.addValue(MISSING_DATA_VALUE);
            ptnr3_comp_ids.addValue(MISSING_DATA_VALUE);
            ptnr3_asym_ids.addValue(MISSING_DATA_VALUE);
            ptnr3_alt_ids.addValue(MISSING_DATA_VALUE);
            ptnr3_ins_codes.addValue(MISSING_DATA_VALUE);
            details.addValue(MISSING_DATA_VALUE);
            roles.addValue(MISSING_DATA_VALUE);
        }
    }
}

void Biomol::MMCIFDataWriter::outputAtomTypeData()
{
    using namespace MMCIF;

    auto& atom_site_type_syms = mmCIFData.getCategory(AtomSite::NAME).getItem(AtomSite::Item::TYPE_SYMBOL);
    
    seenAtomTypes.clear();
    seenAtomTypes.insert(atom_site_type_syms.begin(), atom_site_type_syms.end());
    
    auto& type_syms = mmCIFData.addCategory(AtomType::NAME, true).addItem(AtomType::Item::SYMBOL);

    for (auto& type_sym : seenAtomTypes) {
        if ((type_sym == MISSING_DATA_VALUE) || ((type_sym == UNDEFINED_DATA_VALUE)))
            continue;
        
        type_syms.addValue(type_sym);
    }
}

void Biomol::MMCIFDataWriter::outputAtomSiteData(const Chem::MolecularGraph& molgraph)
{
    using namespace MMCIF;
    
    auto& atom_sites = mmCIFData.addCategory(AtomSite::NAME);
    auto& pdb_groups = atom_sites.addItem(AtomSite::Item::GROUP_PDB);
    auto& serial_nos = atom_sites.addItem(AtomSite::Item::ID);
    auto& type_syms = atom_sites.addItem(AtomSite::Item::TYPE_SYMBOL);
    auto& atom_ids = atom_sites.addItem(AtomSite::Item::LABEL_ATOM_ID);
    auto& atom_alt_loc_ids = atom_sites.addItem(AtomSite::Item::LABEL_ALT_ID);
    auto& comp_ids = atom_sites.addItem(AtomSite::Item::LABEL_COMP_ID);
    auto& chain_ids = atom_sites.addItem(AtomSite::Item::LABEL_ASYM_ID);
    auto& entity_ids = atom_sites.addItem(AtomSite::Item::LABEL_ENTITY_ID);
    auto& res_seq_nos = atom_sites.addItem(AtomSite::Item::LABEL_SEQ_ID);
    auto& ins_codes = atom_sites.addItem(AtomSite::Item::PDBX_PDB_INS_CODE);
    auto& coords_x = atom_sites.addItem(AtomSite::Item::COORDS_X);
    auto& coords_y = atom_sites.addItem(AtomSite::Item::COORDS_Y);
    auto& coords_z = atom_sites.addItem(AtomSite::Item::COORDS_Z);
    auto& occupancies = atom_sites.addItem(AtomSite::Item::OCCUPANCY);
    auto& b_factors = atom_sites.addItem(AtomSite::Item::B_ISO_OR_EQUIV);
    auto& form_charges = atom_sites.addItem(AtomSite::Item::PDBX_FORMAL_CHARGE);
    auto& auth_res_seq_nos = atom_sites.addItem(AtomSite::Item::AUTH_SEQ_ID);
    auto& auth_comp_ids = atom_sites.addItem(AtomSite::Item::AUTH_COMP_ID);
    auto& auth_chain_ids = atom_sites.addItem(AtomSite::Item::AUTH_ASYM_ID);
    auto& auth_atom_ids = atom_sites.addItem(AtomSite::Item::AUTH_ATOM_ID);
    auto& model_nos = atom_sites.addItem(AtomSite::Item::PDBX_PDB_MODEL_NUM);

    std::size_t serial = 1;

    for (auto atom : atomSites) {
        serial_nos.addValue(std::to_string(serial++));
        
        auto& res_code = getResidueCode(*atom);
        auto is_het_atom = (hasHeteroAtomFlag(*atom) ? getHeteroAtomFlag(*atom) : !getChemCompData(&res_code).isStdRes);
        
        pdb_groups.addValue(is_het_atom ? AtomSite::PDBGroup::HET_ATOM : AtomSite::PDBGroup::ATOM);
        outputSymbol(*atom, type_syms);

        auto& id = getResidueAtomName(*atom);
        
        atom_ids.addValue(id);
        auth_atom_ids.addValue(id);
        comp_ids.addValue(res_code);
        auth_comp_ids.addValue(res_code);
        res_seq_nos.addValue(std::to_string(getResidueSequenceNumber(*atom)));
        auth_res_seq_nos.addValue(res_seq_nos.getValue(res_seq_nos.getNumValues() - 1));
        chain_ids.addValue(getChainID(*atom));
        ins_codes.addValue(hasResidueInsertionCode(*atom) ? std::string(1, getResidueInsertionCode(*atom)) : MISSING_DATA_VALUE);
        entity_ids.addValue(entities[atomEntityIndices[molgraph.getAtomIndex(*atom)] - 1].id);
        occupancies.addValue(hasOccupancy(*atom) ? toString(getOccupancy(*atom)) : MISSING_DATA_VALUE);
        b_factors.addValue(hasBFactor(*atom) ? toString(getBFactor(*atom)) : MISSING_DATA_VALUE);
        auth_chain_ids.addValue(chain_ids.getValue(auth_chain_ids.getNumValues()));
        form_charges.addValue(hasFormalCharge(*atom) ? std::to_string(getFormalCharge(*atom)) : MISSING_DATA_VALUE);
        model_nos.addValue(hasModelNumber(*atom) ? std::to_string(getModelNumber(*atom)) : MISSING_DATA_VALUE);

        if (has3DCoordinatesArray(*atom)) {
            auto& coords_array = *get3DCoordinatesArray(*atom);
            auto num_confs = coords_array.getSize();
                
            if (num_confs > 1) {
                num_confs = std::min(std::size_t(26), num_confs);
                auto curr_row_idx = serial_nos.getNumValues() - 1;
                std::size_t i = 0; 
                    
                while (true) {
                    auto& coords = coords_array[i];

                    coords_x.addValue(toString(coords[0]));
                    coords_y.addValue(toString(coords[1]));
                    coords_z.addValue(toString(coords[2]));

                    atom_alt_loc_ids.addValue(std::string(1, 'A' + char(i)));

                    if (++i == num_confs)
                        break;
                    
                    serial_nos.addValue(std::to_string(serial++));
                    pdb_groups.addValue(std::string(pdb_groups.getValue(curr_row_idx)));
                    type_syms.addValue(std::string(type_syms.getValue(curr_row_idx)));
                    atom_ids.addValue(id);
                    auth_atom_ids.addValue(id);
                    comp_ids.addValue(res_code);
                    auth_comp_ids.addValue(res_code);
                    res_seq_nos.addValue(std::string(res_seq_nos.getValue(curr_row_idx)));
                    auth_res_seq_nos.addValue(std::string(auth_res_seq_nos.getValue(curr_row_idx)));
                    chain_ids.addValue(std::string(chain_ids.getValue(curr_row_idx)));
                    ins_codes.addValue(std::string(ins_codes.getValue(curr_row_idx)));
                    entity_ids.addValue(std::string(entity_ids.getValue(curr_row_idx)));
                    occupancies.addValue(std::string(occupancies.getValue(curr_row_idx)));
                    b_factors.addValue(std::string(b_factors.getValue(curr_row_idx)));
                    auth_chain_ids.addValue(std::string(auth_chain_ids.getValue(curr_row_idx)));
                    form_charges.addValue(std::string(form_charges.getValue(curr_row_idx)));
                    model_nos.addValue(std::string(model_nos.getValue(curr_row_idx++)));
                }
                
                continue;
            }
        }

        atom_alt_loc_ids.addValue(UNDEFINED_DATA_VALUE);
        
        if (has3DCoordinates(*atom)) {
            auto& coords = get3DCoordinates(*atom);

            coords_x.addValue(toString(coords[0]));
            coords_y.addValue(toString(coords[1]));
            coords_z.addValue(toString(coords[2]));

        } else {
            coords_x.addValue(MISSING_DATA_VALUE);
            coords_y.addValue(MISSING_DATA_VALUE);
            coords_z.addValue(MISSING_DATA_VALUE);
        }
    }
}

void Biomol::MMCIFDataWriter::outputMacromolCompData()
{
    if (chemCompDict.empty())
        return;
    
    auto& comps = mmCIFData.addCategory(MMCIF::ChemComp::NAME, true);
    auto& ids = comps.addItem(MMCIF::ChemComp::Item::ID);
    auto& types = comps.addItem(MMCIF::ChemComp::Item::TYPE);
    auto& mon_nstd_flags = comps.addItem(MMCIF::ChemComp::Item::MON_NSTD_FLAG);
    auto& names = comps.addItem(MMCIF::ChemComp::Item::NAME);
    auto& pdbx_synonyms = comps.addItem(MMCIF::ChemComp::Item::PDBX_SYNONYMS);
    auto& formulas = comps.addItem(MMCIF::ChemComp::Item::FORMULA);
    auto& weights = comps.addItem(MMCIF::ChemComp::Item::FORMULA_WEIGHT);

    for (auto& e : chemCompDict) {
        auto& comp = *e.second;

        ids.addValue(*e.first);

        auto it = resTypeToStringMap.find(comp.type);

        types.addValue(it == resTypeToStringMap.end() ? MMCIF::MISSING_DATA_VALUE : it->second);

        if (comp.isStdRes)
            mon_nstd_flags.addValue(boost::to_lower_copy(MMCIF::TRUE_FLAG_1));

        else if (!comp.unknown) {
            if ((comp.type == ResidueType::NON_POLYMER) || (comp.type == ResidueType::OTHER) || !comp.parent)
                mon_nstd_flags.addValue(MMCIF::UNDEFINED_DATA_VALUE);
            else
                mon_nstd_flags.addValue(boost::to_lower_copy(MMCIF::FALSE_FLAG_1));
        } else
            mon_nstd_flags.addValue(MMCIF::MISSING_DATA_VALUE);

        names.addValue(*comp.name);
        pdbx_synonyms.addValue(MMCIF::MISSING_DATA_VALUE);
        formulas.addValue(!comp.formula.empty() ? comp.formula : MMCIF::MISSING_DATA_VALUE);
            
        if (comp.weight >= 0.0)
            weights.addValue(toString(comp.weight));
        else
            weights.addValue(MMCIF::MISSING_DATA_VALUE);
    }
}

void Biomol::MMCIFDataWriter::outputMacromolCompAtomData()
{
    using namespace MMCIF;

    auto& comp_atoms = mmCIFData.addCategory(ChemCompAtom::NAME);
    auto& comp_ids = comp_atoms.addItem(ChemCompAtom::Item::COMP_ID);
    auto& ids = comp_atoms.addItem(ChemCompAtom::Item::ATOM_ID);
    auto& type_syms = comp_atoms.addItem(ChemCompAtom::Item::TYPE_SYMBOL);
    auto& arom_flags = comp_atoms.addItem(ChemCompAtom::Item::PDBX_AROM_FLAG);
    auto& sto_configs = comp_atoms.addItem(ChemCompAtom::Item::PDBX_STEREO_CONFIG);
    auto& ordinals = comp_atoms.addItem(ChemCompAtom::Item::PDBX_ORDINAL);

    std::size_t ordinal = 1;

    for (auto& e : chemCompDict) {
        auto& comp_id = *e.first;
        auto& comp = *e.second;

        for (auto& atom : comp.atoms) {
            comp_ids.addValue(comp_id);
            ids.addValue(*atom.id);
            arom_flags.addValue(atom.aromatic ? TRUE_FLAG_1 : FALSE_FLAG_1);
            type_syms.addValue(boost::to_upper_copy(*atom.symbol));
            
            switch (atom.config) {

                case Chem::CIPDescriptor::R:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::R);
                    break;

                case Chem::CIPDescriptor::S:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::S);
                    break;

                case Chem::CIPDescriptor::NONE:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::NONE);
                    break;

                case Chem::CIPDescriptor::NS:
                case Chem::CIPDescriptor::UNDEF:
                    sto_configs.addValue(MISSING_DATA_VALUE);
                    break;

                default:
                    sto_configs.addValue(UNDEFINED_DATA_VALUE);
            }

            ordinals.addValue(std::to_string(ordinal++));
        }
    }
}

void Biomol::MMCIFDataWriter::outputMacromolCompBondData()
{
    using namespace MMCIF;

    auto& comp_bonds = mmCIFData.addCategory(ChemCompBond::NAME);
    auto& comp_ids = comp_bonds.addItem(ChemCompBond::Item::COMP_ID);
    auto& atom1_ids = comp_bonds.addItem(ChemCompBond::Item::ATOM_ID_1);
    auto& atom2_ids = comp_bonds.addItem(ChemCompBond::Item::ATOM_ID_2);
    auto& orders = comp_bonds.addItem(ChemCompBond::Item::ORDER);
    auto& arom_flags = comp_bonds.addItem(ChemCompBond::Item::PDBX_AROM_FLAG);
    auto& sto_configs = comp_bonds.addItem(ChemCompBond::Item::PDBX_STEREO_CONFIG);
    auto& ordinals = comp_bonds.addItem(ChemCompBond::Item::PDBX_ORDINAL);

    std::size_t ordinal = 1;

    for (auto& e : chemCompDict) {
        auto& comp_id = *e.first;
        auto& comp = *e.second;

        for (auto& bond : comp.bonds) {
            comp_ids.addValue(comp_id);
            atom1_ids.addValue(*bond.atom1Id);
            atom2_ids.addValue(*bond.atom2Id);

            switch (bond.order) {

                case 1:
                    orders.addValue(ChemCompBond::Order::SINGLE);
                    break;
                
                case 2:
                    orders.addValue(ChemCompBond::Order::DOUBLE);
                    break;

                case 3:
                    orders.addValue(ChemCompBond::Order::TRIPLE);
                    break;
 
                default:
                    orders.addValue(MISSING_DATA_VALUE);
            }
        
            arom_flags.addValue(bond.aromatic < 0 ? MISSING_DATA_VALUE : bond.aromatic ? TRUE_FLAG_1 : FALSE_FLAG_1);
    
            switch (bond.config) {

                case Chem::CIPDescriptor::E:
                    sto_configs.addValue(ChemCompBond::StereoConfig::E);
                    break;
                    
                case Chem::CIPDescriptor::Z:
                    sto_configs.addValue(ChemCompBond::StereoConfig::Z);
                    break;
                    
                case Chem::CIPDescriptor::NONE:
                    sto_configs.addValue(ChemCompBond::StereoConfig::NONE);
                    break;

                case Chem::CIPDescriptor::NS:
                case Chem::CIPDescriptor::UNDEF:
                    sto_configs.addValue(MISSING_DATA_VALUE);
                    break;
                    
                default:
                    sto_configs.addValue(UNDEFINED_DATA_VALUE);
            }
        
            ordinals.addValue(std::to_string(ordinal++));
        }
    }
}

bool Biomol::MMCIFDataWriter::prepAtomSiteData(const Chem::MolecularGraph& molgraph)
{
    atomSites.clear();

    for (auto& atom : molgraph.getAtoms()) {
        if (!hasSerialNumber(atom))
            return false;

        if (!hasChainID(atom))
            return false;

        if (!hasResidueSequenceNumber(atom))
            return false;

        if (!hasResidueCode(atom))
            return false;

        if (!hasResidueAtomName(atom))
            return false;

        atomSites.push_back(&atom);
    }

    if (atomSites.empty())
        return false;

    std::sort(atomSites.begin(), atomSites.end(), [](const Chem::Atom* atom1, const Chem::Atom* atom2) {
        auto model_id1 = getModelNumber(*atom1);
        auto model_id2 = getModelNumber(*atom2);

        if (model_id1 < model_id2)
            return true;

        if (model_id1 > model_id2)
            return false;

        return (getSerialNumber(*atom1) < getSerialNumber(*atom2));
    });

    uniqueAtomResIds.resize(molgraph.getNumAtoms());

    std::size_t unique_res_id = 1;
    auto curr_res_code = &getResidueCode(*atomSites.front());
    auto curr_chain_id = &getChainID(*atomSites.front());
    auto curr_res_id = getResidueID(*atomSites.front());
    
    for (auto atom : atomSites) {
        auto res_code = &getResidueCode(*atom);
        auto chain_id = &getChainID(*atom);
        auto res_id = getResidueID(*atom);

        if ((res_id != curr_res_id) || (*chain_id != *curr_chain_id) || !Internal::isEqualCI(*res_code, *curr_res_code)) {
            curr_res_code = res_code;
            curr_chain_id = chain_id;
            curr_res_id = res_id;
            unique_res_id++;
        }

        uniqueAtomResIds[molgraph.getAtomIndex(*atom)] = unique_res_id;
    }
    
    return true;
}

void Biomol::MMCIFDataWriter::prepMacromolCompData()
{
    chemCompDict.clear();
    
    for (auto atom : atomSites)
        getChemCompData(&getResidueCode(*atom));

    auto& res_dict = getResidueDictionary();
    
    for (auto& e : chemCompDict) {
        auto& comp = *e.second;
        auto& code = *e.first;
        
        comp.name = &MMCIF::MISSING_DATA_VALUE;
        comp.type = ResidueType::UNKNOWN;
        comp.isStdRes = ResidueDictionary::isStdResidue(code);
        
        auto res_struct = res_dict.getStructure(code);

        if (!res_struct)
            continue;

        for (auto& atom : res_struct->getAtoms()) {
            auto atom_id = &getResidueAtomName(atom);
            auto alt_atom_id = (hasResidueAltAtomName(atom) ? &getResidueAltAtomName(atom) : nullptr);
            std::size_t num_lvg_nbrs = 0;
            
            if (getResidueLinkingAtomFlag(atom)) {
                comp.linkAtomIds.emplace(atom_id);

                if (alt_atom_id)
                    comp.linkAtomIds.emplace(alt_atom_id);

                for (auto& nbr_atom : atom.getAtoms())
                    if (getResidueLeavingAtomFlag(nbr_atom))
                        num_lvg_nbrs++;
                
            } else if (getResidueLeavingAtomFlag(atom)) {
                comp.leavingAtomIds.emplace(atom_id);

                if (alt_atom_id)
                    comp.leavingAtomIds.emplace(alt_atom_id);
            }

            comp.atoms.emplace_back(atom_id, alt_atom_id, &getSymbol(atom),
                                    hasCIPConfiguration(atom) ? getCIPConfiguration(atom) : Chem::CIPDescriptor::UNDEF,
                                    getAromaticityFlag(atom), num_lvg_nbrs);

        }
        
        for (auto& bond : res_struct->getBonds()) {
            auto& atom1 = bond.getBegin();
            auto& atom2 = bond.getEnd();
            auto atom_1_id = &getResidueAtomName(atom1);
            auto atom_1_alt_id = (hasResidueAltAtomName(atom1) ? &getResidueAltAtomName(atom1) : atom_1_id);
            auto atom_2_id = &getResidueAtomName(atom2);
            auto atom_2_alt_id = (hasResidueAltAtomName(atom2) ? &getResidueAltAtomName(atom2) : atom_2_id);

            comp.bondIds.emplace(atom_1_id, atom_2_id);
            comp.bondIds.emplace(atom_1_alt_id, atom_2_id);
            comp.bondIds.emplace(atom_1_id, atom_2_alt_id);
            comp.bondIds.emplace(atom_1_alt_id, atom_2_alt_id);
            comp.bondIds.emplace(atom_2_id, atom_1_id);
            comp.bondIds.emplace(atom_2_alt_id, atom_1_id);
            comp.bondIds.emplace(atom_2_id, atom_1_alt_id);
            comp.bondIds.emplace(atom_2_alt_id, atom_1_alt_id);

            comp.bonds.emplace_back(atom_1_id, atom_2_id, getOrder(bond),
                                    hasCIPConfiguration(bond) ? getCIPConfiguration(bond) : Chem::CIPDescriptor::UNDEF,
                                    getAromaticityFlag(bond));
        }

        comp.unknown = false;
        
        auto& name = getName(*res_struct);

        if (!name.empty())
            comp.name = &name;

        auto& parent = res_dict.getParentCode(code);

        if (!parent.empty())
            comp.parent = &parent;

        auto& olc = res_dict.getOneLetterCode(code);

        if (!olc.empty())
            comp.oneLetterCode = &olc;
        
        comp.type = res_dict.getType(code);
        comp.weight = MolProp::calcMass(*res_struct);

        MolProp::generateMolecularFormula(*res_struct, comp.formula, " ");

        auto net_charge = MolProp::getNetFormalCharge(*res_struct);

        if (net_charge != 0) {
            comp.formula.push_back(' ');
            comp.formula.append(std::to_string(net_charge));
        }
    }
}

void Biomol::MMCIFDataWriter::prepStructConnData(const Chem::MolecularGraph& molgraph)
{
    disulfBonds.clear();
    nonStdBonds.clear();
    
    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        long res_id1 = uniqueAtomResIds[molgraph.getAtomIndex(atom1)];
        long res_id2 = uniqueAtomResIds[molgraph.getAtomIndex(atom2)];

        if (res_id1 == res_id2) {
            auto& comp = getChemCompData(&getResidueCode(atom1));
            
            if (comp.bondIds.find({&getResidueAtomName(atom1), &getResidueAtomName(atom2)}) != comp.bondIds.end())
                continue;

        } else if (std::abs(res_id1 - res_id2) == 1) {
            auto& comp1 = getChemCompData(&getResidueCode(atom1));
            auto& comp2 = getChemCompData(&getResidueCode(atom1));

            if (comp1.isStdRes && comp2.isStdRes &&
                (comp1.linkAtomIds.find(&getResidueAtomName(atom1)) != comp1.linkAtomIds.end()) &&
                (comp2.linkAtomIds.find(&getResidueAtomName(atom2)) != comp2.linkAtomIds.end()))
                continue;
        }

        if ((getOrder(bond) == 1) && (getType(atom1) == Chem::AtomType::S) && (getType(atom2) == Chem::AtomType::S))
            disulfBonds.insert(&bond);
        else
            nonStdBonds.insert(&bond);
    }
}

void Biomol::MMCIFDataWriter::prepEntityData(const Chem::MolecularGraph& molgraph)
{
    static const auto H_WEIGHT = Chem::AtomDictionary::getAtomicWeight(Chem::AtomType::H, 0);
    
    entities.clear();
    atomEntityIndices.assign(molgraph.getNumAtoms(), 0);
 
    for (auto atom : atomSites) {
        auto atom_idx = molgraph.getAtomIndex(*atom);
        
        if (atomEntityIndices[atom_idx])
            continue;

        auto model_no = getModelNumber(*atom);
        auto& chain_id = getChainID(*atom);

        entityAtoms.clear();
        
        getEntityAtoms(*atom, molgraph, model_no, chain_id);

        Entity* entity = nullptr;
        bool is_water = false;

        if (entityAtoms.size() <= 3) {
            std::size_t o_count = 0;
            std::size_t h_count = 0;

            for (auto atom : entityAtoms) {
                switch (getType(*atom)) {

                    case Chem::AtomType::O:
                        o_count++;
                        break;

                    case Chem::AtomType::H:
                        h_count++;
                        break;
                }
            }

            is_water = ((o_count == 1) && ((o_count + h_count) == entityAtoms.size()));
        }
        
        if (is_water) {
            for (auto& e : entities)
                if (*e.type == MMCIF::Entity::Type::WATER) {
                    if (e.modelNo == model_no)
                        e.count++;
                   
                    entity = &e;
                    break;
                }

            if (!entity) {
                entity = new Entity();

                entities.push_back(entity);

                entity->index = entities.size();
                entity->id = std::to_string(entities.size());
                entity->modelNo = model_no;
                entity->weight = WATER_WEIGHT;
                entity->descr = &WATER_ENTITY_DESCR;
                entity->type = &MMCIF::Entity::Type::WATER;
                entity->srcMethod = &MMCIF::Entity::Source::NATURAL;
            }

        } else {
            std::sort(entityAtoms.begin(), entityAtoms.end(), [](const Chem::Atom* atom1, const Chem::Atom* atom2) {
                return (getSerialNumber(*atom1) < getSerialNumber(*atom2));
            });

            auto& first_atom = *entityAtoms.front();
            auto curr_res_id = getResidueID(first_atom);
            auto weight = 0.0;

            entityResSequence.clear();
            entityResSequence.emplace_back(&getResidueCode(first_atom), getResidueSequenceNumber(first_atom));

            for (auto atom : entityAtoms) {
                weight += H_WEIGHT * getImplicitHydrogenCount(*atom) + Chem::AtomDictionary::getAtomicWeight(getType(*atom), 0);
                    
                auto res_id = getResidueID(*atom);

                if (res_id != curr_res_id) {
                    entityResSequence.emplace_back(&getResidueCode(*atom), getResidueSequenceNumber(*atom));
                    curr_res_id = res_id;
                }
            }

            for (auto& e : entities)
                if (((e.type == &MMCIF::Entity::Type::NON_POLYMER) && Internal::isEqualCI(*e.resSequence.front().first, getResidueCode(first_atom))) ||
                    std::equal(entityResSequence.begin(), entityResSequence.end(), e.resSequence.begin(), e.resSequence.end(),
                               [](const Entity::ResidueID& id1, const Entity::ResidueID& id2) {
                                   return ((id1.second == id2.second) && Internal::isEqualCI(*id1.first, *id2.first));
                               })) {

                    if (e.modelNo == model_no) {
                        e.count++;

                        if (entityResSequence.size() > 1)
                            e.chains.insert(&chain_id);
                    }

                    if (e.type != &MMCIF::Entity::Type::NON_POLYMER)
                        e.weight = std::max(e.weight, weight);
                    
                    entity = &e;
                    break;
                }

            if (!entity) {
                entity = new Entity();

                entities.push_back(entity);

                entity->index = entities.size();
                entity->id = std::to_string(entities.size());
                entity->modelNo = model_no;

                if (entityResSequence.size() > 1) {
                    entity->type = &MMCIF::Entity::Type::POLYMER;
                    entity->srcMethod = &MMCIF::MISSING_DATA_VALUE;
                    entity->descr = &MMCIF::MISSING_DATA_VALUE;                    
                    entity->weight = weight;
                    
                    entity->chains.insert(&chain_id);
                      
                } else {
                    auto& comp = getChemCompData(entityResSequence.front().first);
             
                    entity->descr = comp.name;
                    entity->weight = (comp.weight >= 0.0 ? comp.weight : weight);
                    entity->srcMethod = (!comp.unknown ? &MMCIF::Entity::Source::SYNTHETIC : &MMCIF::MISSING_DATA_VALUE);
                    entity->type = &MMCIF::Entity::Type::NON_POLYMER;
                }
                
                entity->resSequence.swap(entityResSequence);
            }
        }

        for (auto atom : entityAtoms)
            atomEntityIndices[molgraph.getAtomIndex(*atom)] = entity->index;
    }
}

void Biomol::MMCIFDataWriter::getEntityAtoms(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                             std::size_t model_no, const std::string& chain_id)
{
    auto atom_idx = molgraph.getAtomIndex(atom);

    if (atomEntityIndices[atom_idx] != 0)
        return;

    if (getModelNumber(atom) != model_no) {
        if (strictErrorChecking)
            throw Base::IOError("MMCIFDataWriter: encountered inconsistent atom site model number assignment");
        
        return;
    }

    if (getChainID(atom) != chain_id)
        return;
    
    atomEntityIndices[atom_idx] = 1;

    entityAtoms.push_back(&atom);

    auto b_it = atom.getBondsBegin();
    auto ss_bonds_end = disulfBonds.end();
    
    for (auto a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        auto& bond = *b_it;
     
        if (!molgraph.containsBond(bond))
            continue;

        if (disulfBonds.find(&bond) != ss_bonds_end)
            continue;
        
        auto& nbr_atom = *a_it;

        if (!molgraph.containsAtom(nbr_atom))
            continue;
        
        getEntityAtoms(nbr_atom, molgraph, model_no, chain_id);
    }
}

bool Biomol::MMCIFDataWriter::genEntityPolySeqStrings(const Entity& entity, std::string& olc_seq, std::string& can_olc_seq)
{
    static const std::unordered_set<std::string,
                                    Internal::CIStringHashFunc,
                                    Internal::CIStringCmpFunc>
        oneLetterCodeExclSet{ "DA", "DC", "DG", "DT", "MSE", "SEP", "TPO", "PTR", "PCA", "UNK", "ACE", "NH2" };

    std::size_t line_res_count = 0;
    auto has_nstd_mon = false;
    auto& res_dict = getResidueDictionary();
   
    olc_seq.clear();
    can_olc_seq.clear();

    for (auto& e : entity.resSequence) {
        if (line_res_count++ >= MAX_OLC_SEQ_LINE_LENGTH) {
            olc_seq.push_back('\n');
            can_olc_seq.push_back('\n');
            line_res_count = 0;
        }

        auto& comp = getChemCompData(e.first);

        if (comp.unknown) {
            olc_seq.push_back('(');
            olc_seq.append(*e.first);
            olc_seq.push_back(')');
            can_olc_seq.push_back('X');
            has_nstd_mon = true;
            continue;
        }

        if (!comp.isStdRes)
            has_nstd_mon = true;

        if (!comp.isStdRes || !comp.oneLetterCode || (oneLetterCodeExclSet.find(*e.first) != oneLetterCodeExclSet.end())) {
            olc_seq.push_back('(');
            olc_seq.append(*e.first);
            olc_seq.push_back(')');

        } else
            olc_seq.append(*comp.oneLetterCode);

        if (comp.oneLetterCode) {
            can_olc_seq.append(*comp.oneLetterCode);
            continue;
        }

        if (!comp.parent) {
            can_olc_seq.push_back('X');
            continue;
        }

        auto comma_pos = comp.parent->find(',');

        if (comma_pos != std::string::npos) {
            can_olc_seq.push_back('(');

            for (std::string::size_type substr_start = 0;;) {
                if (substr_start != 0)
                    can_olc_seq.push_back(',');

                auto& pnt_olc = res_dict.getOneLetterCode(comp.parent->substr(substr_start, comma_pos));

                if (!pnt_olc.empty())
                    can_olc_seq.append(pnt_olc);
                else
                    can_olc_seq.push_back('X');

                if (comma_pos == std::string::npos)
                    break;

                substr_start = comma_pos + 1;
                comma_pos    = comp.parent->find(',', substr_start);
            }

            can_olc_seq.push_back(')');
            continue;
        }

        auto& pnt_olc = res_dict.getOneLetterCode(*comp.parent);

        if (!pnt_olc.empty())
            can_olc_seq.append(pnt_olc);
        else
            can_olc_seq.push_back('X');
    }

    boost::to_upper(olc_seq);
    boost::to_upper(can_olc_seq);

    return has_nstd_mon;
}

const std::string& Biomol::MMCIFDataWriter::getPolymerEntityType(const Entity& entity)
{
    using namespace MMCIF;
    
    std::size_t res_type_histo[ResidueType::MAX_TYPE + 1] = {};

    for (auto& e : entity.resSequence)
        res_type_histo[getChemCompData(e.first).type]++;

    auto num_res = entity.resSequence.size();

    if (arrayElemSum(res_type_histo, L_PEPTIDE_RES_TYPES) == num_res)
        return EntityPoly::Type::POLYPEPTIDE_L;

    if (arrayElemSum(res_type_histo, D_PEPTIDE_RES_TYPES) == num_res)
        return EntityPoly::Type::POLYPEPTIDE_D;

    if (arrayElemSum(res_type_histo, POLYDEOXYRIBONUCLEOTIDE_RES_TYPES) == num_res)
        return EntityPoly::Type::POLYDEOXYRIBONUCLEOTIDE;

    if (arrayElemSum(res_type_histo, POLYRIBONUCLEOTIDE_RES_TYPES) == num_res)
        return EntityPoly::Type::POLYRIBONUCLEOTIDE;

    if (arrayElemSum(res_type_histo, POLYNUCLEOTIDE_HYBRID_RES_TYPES) == num_res)
        return EntityPoly::Type::POLYNUCLEOTIDE_HYBRID;
    
    return MISSING_DATA_VALUE;
}

void Biomol::MMCIFDataWriter::outputChemCompData(const Chem::MolecularGraph& molgraph)
{
    const std::string& comp_id = getChemCompId(molgraph);

    outputChemCompAtomData(molgraph, comp_id);
    outputChemCompBondData(molgraph, comp_id);
    
    auto& comp = mmCIFData.addCategory(MMCIF::ChemComp::NAME, true);

    comp.addItem(MMCIF::ChemComp::Item::ID).addValue(comp_id);
   
    if (hasName(molgraph))
        comp.addItem(MMCIF::ChemComp::Item::NAME).addValue(getName(molgraph));
    else
        comp.addItem(MMCIF::ChemComp::Item::NAME).addValue(MMCIF::MISSING_DATA_VALUE);
}

void Biomol::MMCIFDataWriter::outputChemCompAtomData(const Chem::MolecularGraph& molgraph, const std::string& comp_id)
{
    using namespace MMCIF;

    chemCompAtomIds[0].clear();
    chemCompAtomIds[1].clear();
    
    auto& comp_atoms = mmCIFData.addCategory(ChemCompAtom::NAME);
    auto& comp_ids = comp_atoms.addItem(ChemCompAtom::Item::COMP_ID);
    auto& ids = comp_atoms.addItem(ChemCompAtom::Item::ATOM_ID);
    auto& alt_ids = comp_atoms.addItem(ChemCompAtom::Item::ALT_ATOM_ID);
    auto& type_syms = comp_atoms.addItem(ChemCompAtom::Item::TYPE_SYMBOL);
    auto& coords_x = comp_atoms.addItem(ChemCompAtom::Item::COORDS_X);
    auto& coords_y = comp_atoms.addItem(ChemCompAtom::Item::COORDS_Y);
    auto& coords_z = comp_atoms.addItem(ChemCompAtom::Item::COORDS_Z);
    auto& leaving_flags = comp_atoms.addItem(ChemCompAtom::Item::PDBX_LEAVING_ATOM_FLAG);
    auto& arom_flags = comp_atoms.addItem(ChemCompAtom::Item::PDBX_AROM_FLAG);
    auto& form_charges = comp_atoms.addItem(ChemCompAtom::Item::CHARGE);
    auto& sto_configs = comp_atoms.addItem(ChemCompAtom::Item::PDBX_STEREO_CONFIG);
    auto& ordinals = comp_atoms.addItem(ChemCompAtom::Item::PDBX_ORDINAL);

    std::size_t ordinal = 1;
    
    for (auto& atom : molgraph.getAtoms()) {
        comp_ids.addValue(comp_id);
        
        if (hasResidueAtomName(atom)) {
            auto& name = getResidueAtomName(atom);

            if (chemCompAtomIds[0].insert(&name).second)
                ids.addValue(name);
            else
                ids.addValue(std::string());

        } else
            ids.addValue(std::string());

        if (hasResidueAltAtomName(atom)) {
            auto& name = getResidueAltAtomName(atom);

            if (chemCompAtomIds[1].insert(&name).second)
                alt_ids.addValue(name);
            else
                alt_ids.addValue(std::string());

        } else
            alt_ids.addValue(std::string());

        outputSymbol(atom, type_syms);

        if (has3DCoordinates(atom)) {
            auto& coords = get3DCoordinates(atom);

            coords_x.addValue(toString(coords[0]));
            coords_y.addValue(toString(coords[1]));
            coords_z.addValue(toString(coords[2]));

        } else {
            coords_x.addValue(MISSING_DATA_VALUE);
            coords_y.addValue(MISSING_DATA_VALUE);
            coords_z.addValue(MISSING_DATA_VALUE);
        }
        
        leaving_flags.addValue(hasResidueLeavingAtomFlag(atom) ? getResidueLeavingAtomFlag(atom) ? TRUE_FLAG_1 : FALSE_FLAG_1 : MISSING_DATA_VALUE);
        arom_flags.addValue(hasAromaticityFlag(atom) ? getAromaticityFlag(atom) ? TRUE_FLAG_1 : FALSE_FLAG_1 : MISSING_DATA_VALUE);
        form_charges.addValue(hasFormalCharge(atom) ? std::to_string(getFormalCharge(atom)) : MISSING_DATA_VALUE);

        if (!hasCIPConfiguration(atom))
            sto_configs.addValue(MISSING_DATA_VALUE);

        else {
            switch (getCIPConfiguration(atom)) {

                case Chem::CIPDescriptor::R:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::R);
                    break;
                    
                case Chem::CIPDescriptor::S:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::S);
                    break;
                    
                case Chem::CIPDescriptor::NONE:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::NONE);
                    break;

                case Chem::CIPDescriptor::NS:
                case Chem::CIPDescriptor::UNDEF:
                    sto_configs.addValue(MISSING_DATA_VALUE);
                    break;
                    
                default:
                    sto_configs.addValue(UNDEFINED_DATA_VALUE);
            }
        }

        ordinals.addValue(std::to_string(ordinal++));
    }

    auto num_atoms = molgraph.getNumAtoms();
    
    for (std::size_t i = 0; i < num_atoms; i++)
        if (ids.getValue(i).empty())
            ids.setValue(i, createUniqueAtomID(molgraph.getAtom(i), molgraph, chemCompAtomIds[0], tmpString));

    auto have_missing_alt_ids = false;
    
    for (std::size_t i = 0; i < num_atoms; i++)
        if (alt_ids.getValue(i).empty()) {
            auto& id = ids.getValue(i);

            if (chemCompAtomIds[1].insert(&id).second)
                alt_ids.setValue(i, id);
            else
                have_missing_alt_ids = true;
        }

    if (!have_missing_alt_ids)
        return;

    for (std::size_t i = 0; i < num_atoms; i++)
        if (alt_ids.getValue(i).empty())
            alt_ids.setValue(i, createUniqueAtomID(molgraph.getAtom(i), molgraph, chemCompAtomIds[1], tmpString));
}

void Biomol::MMCIFDataWriter::outputChemCompBondData(const Chem::MolecularGraph& molgraph, const std::string& comp_id)
{
    using namespace MMCIF;

    auto& comp_bonds = mmCIFData.addCategory(ChemCompBond::NAME);
    auto& comp_ids = comp_bonds.addItem(ChemCompBond::Item::COMP_ID);
    auto& atom1_ids = comp_bonds.addItem(ChemCompBond::Item::ATOM_ID_1);
    auto& atom2_ids = comp_bonds.addItem(ChemCompBond::Item::ATOM_ID_2);
    auto& orders = comp_bonds.addItem(ChemCompBond::Item::ORDER);
    auto& arom_flags = comp_bonds.addItem(ChemCompBond::Item::PDBX_AROM_FLAG);
    auto& sto_configs = comp_bonds.addItem(ChemCompBond::Item::PDBX_STEREO_CONFIG);
    auto& ordinals = comp_bonds.addItem(ChemCompBond::Item::PDBX_ORDINAL);

    auto& comp_atoms = mmCIFData.getCategory(ChemCompAtom::NAME);
    auto& atom_ids = comp_atoms.getItem(ChemCompAtom::Item::ATOM_ID);

    std::size_t ordinal = 1;
    
    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        comp_ids.addValue(comp_id);

        atom1_ids.addValue(atom_ids.getValue(molgraph.getAtomIndex(atom1)));
        atom2_ids.addValue(atom_ids.getValue(molgraph.getAtomIndex(atom2)));

        switch (getOrder(bond)) {

            case 1:
                orders.addValue(ChemCompBond::Order::SINGLE);
                break;
                
            case 2:
                orders.addValue(ChemCompBond::Order::DOUBLE);
                break;

            case 3:
                orders.addValue(ChemCompBond::Order::TRIPLE);
                break;
 
            default:
                orders.addValue(MISSING_DATA_VALUE);
        }
        
        arom_flags.addValue(hasAromaticityFlag(bond) ? getAromaticityFlag(bond) ? TRUE_FLAG_1 : FALSE_FLAG_1 : MISSING_DATA_VALUE);

        if (!hasCIPConfiguration(bond))
            sto_configs.addValue(MISSING_DATA_VALUE);

        else {
            switch (getCIPConfiguration(bond)) {

                case Chem::CIPDescriptor::E:
                    sto_configs.addValue(ChemCompBond::StereoConfig::E);
                    break;
                    
                case Chem::CIPDescriptor::Z:
                    sto_configs.addValue(ChemCompBond::StereoConfig::Z);
                    break;
                    
                case Chem::CIPDescriptor::NONE:
                    sto_configs.addValue(ChemCompBond::StereoConfig::NONE);
                    break;

                case Chem::CIPDescriptor::NS:
                case Chem::CIPDescriptor::UNDEF:
                    sto_configs.addValue(MISSING_DATA_VALUE);
                    break;
                    
                default:
                    sto_configs.addValue(UNDEFINED_DATA_VALUE);
            }
        }

        ordinals.addValue(std::to_string(ordinal++));
    }
}

void Biomol::MMCIFDataWriter::setDataBlockId(const Chem::MolecularGraph& molgraph)
{
    if (hasMMCIFData(molgraph)) {
        stripWS(getMMCIFData(molgraph)->getID(), tmpString);

        if (!tmpString.empty() && tmpString.length() <= MMCIF::MAX_DATA_BLOCK_ID_LENGTH) {
            mmCIFData.setID(tmpString);
            return;
        }
    }

    if (hasResidueCode(molgraph)) {
        stripWS(getResidueCode(molgraph), tmpString);

        if (!tmpString.empty() && tmpString.length() <= MMCIF::MAX_DATA_BLOCK_ID_LENGTH) {
            mmCIFData.setID(tmpString);
            return;
        }
    }

    if (hasName(molgraph)) {
        stripWS(getName(molgraph), tmpString);

        if (!tmpString.empty() && tmpString.length() <= MMCIF::MAX_DATA_BLOCK_ID_LENGTH) {
            mmCIFData.setID(tmpString);
            return;
        }
    }

    mmCIFData.setID(DEF_DATA_BLOCK_ID_PREFIX + std::to_string(numOutDataBlocks));
}

bool Biomol::MMCIFDataWriter::hasMissingLeavingAtomNbrs(const Chem::Atom& atom, const Chem::Bond& bond, const Chem::MolecularGraph& molgraph)
{
    auto& comp = getChemCompData(&getResidueCode(atom));
    auto& atom_id = getResidueAtomName(atom);

    if (comp.linkAtomIds.find(&atom_id) == comp.linkAtomIds.end())
        return false;

    std::size_t max_num_lvg_atoms = 0;

    for (auto& comp_atom : comp.atoms)
        if ((atom_id == *comp_atom.id) || (comp_atom.altId && (atom_id == *comp_atom.altId))) {
            max_num_lvg_atoms = comp_atom.numLvgNbrs;
            break;
        }
    
    std::size_t num_lvg_atoms = 0;
    auto a_it = atom.getAtomsBegin();

    for (auto b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
        if (&(*b_it) == &bond)
            continue;
        
        if (!molgraph.containsBond(*b_it))
            continue;

        if (!molgraph.containsAtom(*a_it))
            continue;

        auto nbr_id = &getResidueAtomName(*a_it);

        if (comp.bondIds.find({&atom_id, nbr_id}) == comp.bondIds.end())
            continue;
        
        if (comp.leavingAtomIds.find(nbr_id) != comp.leavingAtomIds.end())
            num_lvg_atoms++;
    }
        
    return (num_lvg_atoms < max_num_lvg_atoms);
}

const Biomol::ResidueDictionary& Biomol::MMCIFDataWriter::getResidueDictionary() const
{
     if (resDictionary)
        return *resDictionary->get();

     return *ResidueDictionary::get();
}
      
Biomol::MMCIFDataWriter::ChemComp& Biomol::MMCIFDataWriter::getChemCompData(const std::string* comp_id)
{
    auto& comp_ptr = chemCompDict[comp_id];

    if (!comp_ptr)
        comp_ptr.reset(new ChemComp());
  
    return *comp_ptr;
}

std::string Biomol::MMCIFDataWriter::getChemCompId(const Chem::MolecularGraph& molgraph)
{
    if (hasResidueCode(molgraph))
        return stripWS(getResidueCode(molgraph), tmpString);
    
    return mmCIFData.getID();
}

const std::string& Biomol::MMCIFDataWriter::createUniqueAtomID(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                               const AtomIDSet& id_set, std::string& id) const
{
    id = getSymbol(atom);

    boost::to_upper(id);

    std::size_t sym_len = id.size();

    for (std::size_t i = molgraph.getAtomIndex(atom) + 1, num_atoms = molgraph.getNumAtoms(); i < (num_atoms * num_atoms); i += num_atoms) {
        id.append(std::to_string(i));

        if (id_set.find(&id) == id_set.end())
            return id;

        id.resize(sym_len);
    }

    throw Base::IOError("MMCIFDataWriter: could not create unique id for atom #" + std::to_string(molgraph.getAtomIndex(atom)));
}
