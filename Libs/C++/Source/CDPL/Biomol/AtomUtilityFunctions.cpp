/* 
 * AtomUtilityFunctions.cpp 
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

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/ResidueDictionary.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Fragment.hpp"


using namespace CDPL; 


namespace
{

    const std::string C_AA_CARBONYL = "C";
    const std::string C_AA_ALPHA    = "CA";
    const std::string N_AA_AMIDE    = "N";
    const std::string O_AA_ACID     = "O";
    const std::string O_AA_TERMINAL = "OXT";
    const std::string P_NT          = "P";
    const std::string O3_NT         = "O3'";
    const std::string O5_NT         = "O5'";
    const std::string C5_NT         = "C5'";
    const std::string C4_NT         = "C4'";
    const std::string C3_NT         = "C3'";
}


bool Biomol::areInSameResidue(const Chem::Atom& atom1, const Chem::Atom& atom2, unsigned int flags)
{
    if (flags == AtomPropertyFlag::DEFAULT)
        flags = AtomPropertyFlag::RESIDUE_CODE |
            AtomPropertyFlag::RESIDUE_SEQ_NO |
            AtomPropertyFlag::RESIDUE_INS_CODE |
            AtomPropertyFlag::CHAIN_ID |
            AtomPropertyFlag::MODEL_NUMBER;

    if ((flags & AtomPropertyFlag::RESIDUE_SEQ_NO) && getResidueSequenceNumber(atom1) != getResidueSequenceNumber(atom2))
        return false;

    if ((flags & AtomPropertyFlag::RESIDUE_INS_CODE) && getResidueInsertionCode(atom1) != getResidueInsertionCode(atom2))
        return false;

    if ((flags & AtomPropertyFlag::CHAIN_ID) && getChainID(atom1) != getChainID(atom2))
        return false;

    if ((flags & AtomPropertyFlag::MODEL_NUMBER) && getModelNumber(atom1) != getModelNumber(atom2))
        return false;

    if ((flags & AtomPropertyFlag::RESIDUE_CODE) && getResidueCode(atom1) != getResidueCode(atom2))
        return false;

    return true;
}

void Biomol::extractResidueSubstructure(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, 
                                        Chem::Fragment& res_substruct, bool cnctd_only, unsigned int flags, bool append)
{
    using namespace Chem;

    if (flags == AtomPropertyFlag::DEFAULT)
        flags = AtomPropertyFlag::RESIDUE_CODE |
            AtomPropertyFlag::RESIDUE_SEQ_NO |
            AtomPropertyFlag::RESIDUE_INS_CODE |
            AtomPropertyFlag::CHAIN_ID |
            AtomPropertyFlag::MODEL_NUMBER;

    if (!append)
        res_substruct.clear();

    std::string res_code = (flags & AtomPropertyFlag::RESIDUE_CODE) ? getResidueCode(atom) : std::string();
    std::size_t model_no = (flags & AtomPropertyFlag::MODEL_NUMBER) ? getModelNumber(atom) : std::size_t(0);
    long seq_no = (flags & AtomPropertyFlag::RESIDUE_SEQ_NO) ? getResidueSequenceNumber(atom) : IGNORE_SEQUENCE_NO;
    std::string chain_id = (flags & AtomPropertyFlag::CHAIN_ID) ? getChainID(atom) : std::string();
    char ins_code = (flags & AtomPropertyFlag::RESIDUE_INS_CODE) ? getResidueInsertionCode(atom) : ' ';

    res_substruct.addAtom(atom);

    if (!cnctd_only) {
        for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
            const Atom& cand_atom = *it;

            if (res_substruct.containsAtom(cand_atom))
                continue;
 
            if ((flags & AtomPropertyFlag::RESIDUE_SEQ_NO) && seq_no != getResidueSequenceNumber(cand_atom))
                continue;

            if ((flags & AtomPropertyFlag::RESIDUE_INS_CODE) && ins_code != getResidueInsertionCode(cand_atom))
                continue;
            
            if ((flags & AtomPropertyFlag::CHAIN_ID) && chain_id != getChainID(cand_atom))
                continue;

            if ((flags & AtomPropertyFlag::MODEL_NUMBER) && model_no != getModelNumber(cand_atom))
                continue;

            if ((flags & AtomPropertyFlag::RESIDUE_CODE) && res_code != getResidueCode(cand_atom))
                continue;
            
            res_substruct.addAtom(cand_atom);
        }

        for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(), end = molgraph.getBondsEnd(); it != end; ++it) {
            const Bond& bond = *it;

            if (res_substruct.containsAtom(bond.getBegin()) && res_substruct.containsAtom(bond.getEnd()))
                res_substruct.addBond(bond);
        }

        return;
    }

    Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

    for (Atom::ConstBondIterator b_it = atom.getBondsBegin(), b_end = atom.getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
        const Atom& cand_atom = *a_it;
        
        if (!molgraph.containsAtom(cand_atom))
            continue;

        const Bond& bond = *b_it;

        if (!molgraph.containsBond(bond))
            continue;

        if (!res_substruct.containsAtom(cand_atom)) {
            if ((flags & AtomPropertyFlag::RESIDUE_SEQ_NO) && seq_no != getResidueSequenceNumber(cand_atom))
                continue;

            if ((flags & AtomPropertyFlag::RESIDUE_INS_CODE) && ins_code != getResidueInsertionCode(cand_atom))
                continue;
            
            if ((flags & AtomPropertyFlag::CHAIN_ID) && chain_id != getChainID(cand_atom))
                continue;

            if ((flags & AtomPropertyFlag::MODEL_NUMBER) && model_no != getModelNumber(cand_atom))
                continue;

            if ((flags & AtomPropertyFlag::RESIDUE_CODE) && res_code != getResidueCode(cand_atom))
                continue;

            extractResidueSubstructure(cand_atom, molgraph, res_substruct, cnctd_only, flags, true);
        }

        res_substruct.addBond(*b_it);
    }
}

bool Biomol::isPDBBackboneAtom(const Chem::Atom& atom)
{
    if (!ResidueDictionary::isStdResidue(getResidueCode(atom)))
        return false;

    const std::string& label = getResidueAtomName(atom);

    return (label == C_AA_CARBONYL || label == C_AA_ALPHA || label == N_AA_AMIDE || label == O_AA_ACID || label == O_AA_TERMINAL ||
            label == P_NT || label == O3_NT || label == O5_NT || label == C5_NT || label == C4_NT || label == C3_NT);
}


bool Biomol::matchesResidueInfo(const Chem::Atom& atom, const char* res_code, const char* chain_id, long res_seq_no,
                                char ins_code, std::size_t model_no, const char* atom_name, long serial_no)
{
    if (res_code != 0 && (getResidueCode(atom) != res_code))
        return false;

    if (chain_id != 0 && (getChainID(atom) != chain_id))
        return false;

    if (res_seq_no != IGNORE_SEQUENCE_NO && (getResidueSequenceNumber(atom) != res_seq_no))
        return false;

    if (ins_code != 0 && (getResidueInsertionCode(atom) != ins_code))
        return false;
            
    if (model_no != 0 && (getModelNumber(atom) != model_no))
        return false;
 
    if (atom_name != 0 && (getResidueAtomName(atom) != atom_name))
        return false;

    if (serial_no != IGNORE_SERIAL_NO && (getSerialNumber(atom) != serial_no))
        return false;

    return true;
}
