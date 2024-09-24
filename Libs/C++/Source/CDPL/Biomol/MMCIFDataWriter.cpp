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

#include <boost/algorithm/string.hpp>

#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"
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

        return std::to_string(val);
    }
    
    const std::string DEF_DATA_BLOCK_ID_PREFIX{"MOL"};
    const std::string DEF_ENTITY_ID{"1"};
}


bool Biomol::MMCIFDataWriter::writeMolecularGraph(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    init(os);

    setDataBlockId(molgraph);
    
    if (outputAsChemComp || !genMacromoleculeData(molgraph))
        genChemCompData(molgraph);

    return (os << mmCIFData).good();
}

void Biomol::MMCIFDataWriter::init(std::ostream& os)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
    resDictionary       = getResidueDictionaryParameter(ioBase);
    outputAsChemComp    = getMMCIFOutputBiopolymersAsChemCompParameter(ioBase);

    mmCIFData.clear();
    numOutDataBlocks++;
}

bool Biomol::MMCIFDataWriter::genMacromoleculeData(const Chem::MolecularGraph& molgraph)
{
    if (!genAtomSiteData(molgraph))
        return false;

    return true;
}

bool Biomol::MMCIFDataWriter::genAtomSiteData(const Chem::MolecularGraph& molgraph)
{
    using namespace MMCIF;
    
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

        //if (hasEntityID(atom))
        //    return false;

        atomSites.push_back(&atom);
    }

    std::sort(atomSites.begin(), atomSites.end(), [](const Chem::Atom* atom1, const Chem::Atom* atom2) {
        auto model_id1 = getModelNumber(*atom1);
        auto model_id2 = getModelNumber(*atom2);

        if (model_id1 < model_id2)
            return true;

        if (model_id1 > model_id2)
            return false;

        return (getSerialNumber(*atom1) < getSerialNumber(*atom2));
    });

    auto& atom_sites = mmCIFData.addCategory(AtomSite::NAME);
    auto& pdb_groups = atom_sites.addItem(AtomSite::Item::GROUP_PDB);
    auto& serial_nos = atom_sites.addItem(AtomSite::Item::ID);
    auto& type_syms = atom_sites.addItem(AtomSite::Item::TYPE_SYMBOL);
    auto& atom_alt_loc_ids = atom_sites.addItem(AtomSite::Item::LABEL_ALT_ID);
    auto& atom_ids = atom_sites.addItem(AtomSite::Item::LABEL_ATOM_ID);
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
    auto& auth_chain_ids = atom_sites.addItem(AtomSite::Item::AUTH_ASYM_ID);
    auto& model_nos = atom_sites.addItem(AtomSite::Item::PDBX_PDB_MODEL_NUM);

    std::size_t serial = 1;

    for (auto atom : atomSites) {
        serial_nos.addValue(std::to_string(serial++));
        
        auto& res_code = getResidueCode(*atom);
        
        pdb_groups.addValue(hasHeteroAtomFlag(*atom) ? getHeteroAtomFlag(*atom) ? AtomSite::PDBGroup::HET_ATOM : AtomSite::PDBGroup::ATOM :
                            ResidueDictionary::isStdResidue(res_code) ? AtomSite::PDBGroup::HET_ATOM : AtomSite::PDBGroup::ATOM);
      
        tmpString = (hasSymbol(*atom) ? getSymbol(*atom) : MISSING_DATA_VALUE);

        boost::to_upper(tmpString);
        
        type_syms.addValue(tmpString);
        atom_ids.addValue(getResidueAtomName(*atom));
        atom_alt_loc_ids.addValue(hasAltLocationID(*atom) ? std::string(1, getAltLocationID(*atom)) : UNDEFINED_DATA_VALUE);
        comp_ids.addValue(res_code);
        res_seq_nos.addValue(std::to_string(getResidueSequenceNumber(*atom)));
        chain_ids.addValue(getChainID(*atom));
        entity_ids.addValue(DEF_ENTITY_ID);
        ins_codes.addValue(hasResidueInsertionCode(*atom) ? std::string(1, getResidueInsertionCode(*atom)) : MISSING_DATA_VALUE);

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
        
        occupancies.addValue(hasOccupancy(*atom) ? toString(getOccupancy(*atom)) : MISSING_DATA_VALUE);
        b_factors.addValue(hasBFactor(*atom) ? toString(getBFactor(*atom)) : MISSING_DATA_VALUE);
        auth_chain_ids.addValue(chain_ids.getValue(auth_chain_ids.getNumValues()));
        form_charges.addValue(hasFormalCharge(*atom) ? std::to_string(getFormalCharge(*atom)) : MISSING_DATA_VALUE);
        model_nos.addValue(std::to_string(getModelNumber(*atom)));
    }
 
    return true;
}

void Biomol::MMCIFDataWriter::genChemCompData(const Chem::MolecularGraph& molgraph)
{
    using namespace MMCIF;
    
    const std::string& comp_id = getChemCompId(molgraph);

    genChemCompAtomsData(molgraph, comp_id);
    genChemCompBondsData(molgraph, comp_id);
    
    auto& chem_comp = mmCIFData.addCategory(ChemComp::NAME, true);

    chem_comp.addItem(ChemComp::Item::ID).addValue(comp_id);
   
    if (hasName(molgraph))
        chem_comp.addItem(ChemComp::Item::NAME).addValue(getName(molgraph));
    else
        chem_comp.addItem(ChemComp::Item::NAME).addValue(MISSING_DATA_VALUE);
}

void Biomol::MMCIFDataWriter::genChemCompAtomsData(const Chem::MolecularGraph& molgraph, const std::string& comp_id)
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
        
        tmpString = (hasSymbol(atom) ? getSymbol(atom) : MISSING_DATA_VALUE);

        boost::to_upper(tmpString);
        
        type_syms.addValue(tmpString);

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
        
        leaving_flags.addValue(hasResidueLeavingAtomFlag(atom) ? getResidueLeavingAtomFlag(atom) ? TRUE_FLAG : FALSE_FLAG : MISSING_DATA_VALUE);
        arom_flags.addValue(hasAromaticityFlag(atom) ? getAromaticityFlag(atom) ? TRUE_FLAG : FALSE_FLAG : MISSING_DATA_VALUE);
        form_charges.addValue(hasFormalCharge(atom) ? std::to_string(getFormalCharge(atom)) : MISSING_DATA_VALUE);

        if (!hasCIPConfiguration(atom))
            sto_configs.addValue(MISSING_DATA_VALUE);

        else {
            switch (getCIPConfiguration(atom)) {

                case Chem::CIPDescriptor::R:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::R);
                    continue;
                    
                case Chem::CIPDescriptor::S:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::S);
                    continue;
                    
                case Chem::CIPDescriptor::NONE:
                    sto_configs.addValue(ChemCompAtom::StereoConfig::NONE);
                    continue;

                case Chem::CIPDescriptor::NS:
                case Chem::CIPDescriptor::UNDEF:
                    sto_configs.addValue(MISSING_DATA_VALUE);
                    continue;
                    
                default:
                    sto_configs.addValue(UNDEFINED_DATA_VALUE);
            }
        }
    }

    auto num_atoms = molgraph.getNumAtoms();
    
    for (std::size_t i = 0; i < num_atoms; i++)
        if (ids.getValue(i).empty())
            ids.setValue(i, createUniqueAtomId(molgraph.getAtom(i), molgraph, chemCompAtomIds[0], tmpString));

    bool have_missing_alt_ids = false;
    
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
            alt_ids.setValue(i, createUniqueAtomId(molgraph.getAtom(i), molgraph, chemCompAtomIds[1], tmpString));
}

void Biomol::MMCIFDataWriter::genChemCompBondsData(const Chem::MolecularGraph& molgraph, const std::string& comp_id)
{
    using namespace MMCIF;

    auto& comp_bonds = mmCIFData.addCategory(ChemCompBond::NAME);
    auto& comp_ids = comp_bonds.addItem(ChemCompBond::Item::COMP_ID);
    auto& atom_ids_1 = comp_bonds.addItem(ChemCompBond::Item::ATOM_ID_1);
    auto& atom_ids_2 = comp_bonds.addItem(ChemCompBond::Item::ATOM_ID_2);
    auto& orders = comp_bonds.addItem(ChemCompBond::Item::ORDER);
    auto& arom_flags = comp_bonds.addItem(ChemCompBond::Item::PDBX_AROM_FLAG);
    auto& sto_configs = comp_bonds.addItem(ChemCompBond::Item::PDBX_STEREO_CONFIG);

    auto& comp_atoms = mmCIFData.getCategory(ChemCompAtom::NAME);
    auto& atom_ids = comp_atoms.getItem(ChemCompAtom::Item::ATOM_ID);
    
    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;

        comp_ids.addValue(comp_id);

        atom_ids_1.addValue(atom_ids.getValue(molgraph.getAtomIndex(atom1)));
        atom_ids_2.addValue(atom_ids.getValue(molgraph.getAtomIndex(atom2)));

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
        
        arom_flags.addValue(hasAromaticityFlag(bond) ? getAromaticityFlag(bond) ? TRUE_FLAG : FALSE_FLAG : MISSING_DATA_VALUE);

        if (!hasCIPConfiguration(bond))
            sto_configs.addValue(MISSING_DATA_VALUE);

        else {
            switch (getCIPConfiguration(bond)) {

                case Chem::CIPDescriptor::E:
                    sto_configs.addValue(ChemCompBond::StereoConfig::E);
                    continue;
                    
                case Chem::CIPDescriptor::Z:
                    sto_configs.addValue(ChemCompBond::StereoConfig::Z);
                    continue;
                    
                case Chem::CIPDescriptor::NONE:
                    sto_configs.addValue(ChemCompBond::StereoConfig::NONE);
                    continue;

                case Chem::CIPDescriptor::NS:
                case Chem::CIPDescriptor::UNDEF:
                    sto_configs.addValue(MISSING_DATA_VALUE);
                    continue;
                    
                default:
                    sto_configs.addValue(UNDEFINED_DATA_VALUE);
            }
        }
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

std::string Biomol::MMCIFDataWriter::getChemCompId(const Chem::MolecularGraph& molgraph)
{
    if (hasResidueCode(molgraph))
        return stripWS(getResidueCode(molgraph), tmpString);
    
    return mmCIFData.getID();
}

const std::string& Biomol::MMCIFDataWriter::createUniqueAtomId(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph,
                                                               const AtomIdSet& id_set, std::string& id) const
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
