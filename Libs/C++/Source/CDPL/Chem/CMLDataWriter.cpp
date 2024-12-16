/* 
 * CMLDataWriter.cpp 
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

#include <ostream>
#include <locale>

#include <boost/algorithm/string.hpp>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/StringDataBlock.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"
#include "CDPL/Internal/AtomContainerFunctions.hpp"

#include "CMLDataWriter.hpp"
#include "CMLFormatData.hpp"


using namespace CDPL;


namespace
{

    inline bool containsWS(const std::string& str)
    {
        for (auto c : str)
            if (std::isspace(c, std::locale::classic()))
                return true;
        
        return false;
    }
    
    const std::string MOLECULE_ID_PREFIX = "m";
    const std::string ATOM_ID_PREFIX     = "a";
    const std::string BOND_ID_PREFIX     = "b";
} // namespace


Chem::CMLDataWriter::CMLDataWriter(const Base::DataIOBase& io_base):
    ioBase(io_base), startDoc(true)
{}

bool Chem::CMLDataWriter::writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph)
{
    init(os);
    
    if (startDoc) {
        startDocument(os);

        startDoc = false;
        molId = 1;
    }

    std::size_t num_confs = (multiConfExport ? getNumConformations(molgraph) : 0);
    auto have_2d_coords = hasCoordinates(molgraph, 2);
    
    if (num_confs == 0) {
        multiConfExport = false;

        writeMoleculeData(os, molgraph, have_2d_coords, 0);
        
    } else {
        for (std::size_t i = 0; i < num_confs; i++) {
            getConformation(molgraph, i, confCoordinates, false);
            writeMoleculeData(os, molgraph, have_2d_coords, i);
        }
    }

    return os.good();
}

void Chem::CMLDataWriter::close(std::ostream& os)
{
    if (startDoc)
        return;

    endDocument(os);
    startDoc = true;
}

void Chem::CMLDataWriter::init(std::ostream& os)
{
    outputXMLDecl    = getCMLOutputXMLDeclarationParameter(ioBase);
    elemNamespace    = getCMLOutputElementNamespaceParameter(ioBase);
    outputMolName    = getCMLOutputMoleculeNameParameter(ioBase);
    outputStructData = getCMLOutputStructureDataParameter(ioBase);
    outputAtomParity = getCMLOutputAtomParityParameter(ioBase);
    outputSBStereo   = getCMLOutputSingleBondStereoParameter(ioBase);
    outputDBStereo   = getCMLOutputDoubleBondStereoParameter(ioBase);
    outputKekulized  = getCMLOutputKekuleFormParameter(ioBase);
    outputIsotope    = getCMLOutputIsotopeParameter(ioBase);
    outputSpinMult   = getCMLOutputSpinMultiplicityParameter(ioBase);
    compactAtomData  = getCMLOutputCompactAtomDataParameter(ioBase);
    compactBondData  = getCMLOutputCompactBondDataParameter(ioBase);
    multiConfExport  = getMultiConfExportParameter(ioBase);

    if (multiConfExport)
        confIdxSuffixPattern = getConfIndexNameSuffixPatternParameter(ioBase);

    os.imbue(std::locale::classic());
}

void Chem::CMLDataWriter::startDocument(std::ostream& os) const
{
    if (outputXMLDecl)
        os << CML::XML_DECLARATION;

    Internal::beginXMLStartTag(os, CML::Element::CML, 0, elemNamespace);

    os << " xmlns";

    if (!elemNamespace.empty())
        os << ':' << elemNamespace;

    os << CML::CML_DECLARATIONS;
}

void Chem::CMLDataWriter::endDocument(std::ostream& os) const
{
    Internal::writeXMLEndTag(os, CML::Element::CML, 0, elemNamespace);
}

void Chem::CMLDataWriter::writeMoleculeData(std::ostream& os, const MolecularGraph& molgraph, bool have_2d_coords, std::size_t conf_idx)
{
    startMoleculeElement(os, molgraph);

    if (outputMolName)
        writeName(os, molgraph, conf_idx);

    writeAtoms(os, molgraph);
    writeBonds(os, molgraph, have_2d_coords);

    if (outputStructData)
        writeProperties(os, molgraph);

    endMoleculeElement(os);
}

void Chem::CMLDataWriter::startMoleculeElement(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;
    
    beginXMLStartTag(os, CML::Element::MOLECULE, 1, elemNamespace);

    writeXMLAttribute(os, CML::Attribute::ID, MOLECULE_ID_PREFIX + std::to_string(molId++));

    if (auto form_charge = getNetFormalCharge(molgraph))
        writeXMLAttribute(os, CML::Attribute::FORMAL_CHARGE, form_charge);

    endXMLStartTag(os);
}

void Chem::CMLDataWriter::endMoleculeElement(std::ostream& os) const
{
    Internal::writeXMLEndTag(os, CML::Element::MOLECULE, 1, elemNamespace);
}

void Chem::CMLDataWriter::writeName(std::ostream& os, const MolecularGraph& molgraph, std::size_t conf_idx)
{
    using namespace Internal;

    if (!multiConfExport || confIdxSuffixPattern.empty()) {
        if (!hasName(molgraph))
            return;

        beginXMLStartTag(os, CML::Element::NAME, 2, elemNamespace);
        endXMLStartTag(os, false, false);
        
        os << escapeXMLData(getName(molgraph), tmpString[0], false);
    
        writeXMLEndTag(os, CML::Element::NAME, 0, elemNamespace);
        return;
    }

    tmpString[0] = getName(molgraph);
    tmpString[1] = boost::replace_all_copy(confIdxSuffixPattern, "%I%", std::to_string(conf_idx + 1));

    if (tmpString[1] != confIdxSuffixPattern) 
        tmpString[0].append(tmpString[1]);
                               
    beginXMLStartTag(os, CML::Element::NAME, 2, elemNamespace);
    endXMLStartTag(os, false, false);
        
    os << escapeXMLData(tmpString[0], tmpString[1], false);
    
    writeXMLEndTag(os, CML::Element::NAME, 0, elemNamespace);
}

void Chem::CMLDataWriter::writeAtoms(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;

    if (molgraph.getNumAtoms() == 0)
        return;

    calcAtomStereoDescriptors(molgraph);
    
    beginXMLStartTag(os, CML::Element::ATOM_ARRAY, 2, elemNamespace);

    if (compactAtomData && writeAtomsCompact(os, molgraph))
        return;
    
    endXMLStartTag(os);

    for (auto& atom : molgraph.getAtoms()) {
        beginXMLStartTag(os, CML::Element::ATOM, 3, elemNamespace);

        writeXMLAttribute(os, CML::Attribute::ID, getAtomId(atom, molgraph, tmpString[0]));

        if (hasSymbol(atom))
            writeXMLAttribute(os, CML::Attribute::ELEMENT_TYPE, getSymbol(atom));
            
        else if (hasType(atom)) {
            auto& symbol = AtomDictionary::getSymbol(getType(atom));
            
            if (symbol.empty())
                writeXMLAttribute(os, CML::Attribute::ELEMENT_TYPE, CML::AtomType::DUMMY_1);
            else
                writeXMLAttribute(os, CML::Attribute::ELEMENT_TYPE, escapeXMLData(symbol, tmpString[0], true));

        } else
              writeXMLAttribute(os, CML::Attribute::ELEMENT_TYPE, CML::AtomType::DUMMY_1);

        if (outputIsotope)
            if (auto iso = getIsotope(atom))
                writeXMLAttribute(os, CML::Attribute::ISOTOPE, iso);

        if (auto form_chg = getFormalCharge(atom))
            writeXMLAttribute(os, CML::Attribute::FORMAL_CHARGE, form_chg);

        if (outputSpinMult)
            if (auto unp_el_count = getUnpairedElectronCount(atom))
                writeXMLAttribute(os, CML::Attribute::SPIN_MULTIPLICITY, (unp_el_count + 1));
            
        if (has2DCoordinates(atom)) {
            auto& coords = get2DCoordinates(atom);

            writeXMLAttribute(os, CML::Attribute::X2, coords[0]);
            writeXMLAttribute(os, CML::Attribute::Y2, coords[1]);
        }

        auto* coords = (multiConfExport ? &confCoordinates[molgraph.getAtomIndex(atom)] :
                        has3DCoordinates(atom) ? &get3DCoordinates(atom) : nullptr);
        
        if (coords) {
            writeXMLAttribute(os, CML::Attribute::X3, (*coords)[0]);
            writeXMLAttribute(os, CML::Attribute::Y3, (*coords)[1]);
            writeXMLAttribute(os, CML::Attribute::Z3, (*coords)[2]);
        }
        
        if (outputAtomParity && writeAtomParity(os, atom, molgraph))
            writeXMLEndTag(os, CML::Element::ATOM, 3, elemNamespace);
        else
            endXMLStartTag(os, true);
    }
    
    Internal::writeXMLEndTag(os, CML::Element::ATOM_ARRAY, 2, elemNamespace);
}

bool Chem::CMLDataWriter::writeAtomParity(std::ostream& os, const Atom& atom, const MolecularGraph& molgraph)
{
    using namespace Internal;
    
    auto& stereo_desc = atomStereoDescrs[molgraph.getAtomIndex(atom)];
    auto num_ref_atoms = stereo_desc.getNumReferenceAtoms();

    if (num_ref_atoms < 3)
        return false;

    int parity = 0;

    switch (stereo_desc.getConfiguration()) {

        case AtomConfiguration::S:
            parity = 1;
            break;

        case AtomConfiguration::R:
            parity = -1;
            break;

        default:
            return false;
    }

    auto ref_atoms = stereo_desc.getReferenceAtoms();

    getAtomId(*ref_atoms[0], molgraph, tmpString[0]);
    
    for (std::size_t i = 1; i < num_ref_atoms; i++) {
        tmpString[0].push_back(' ');
        tmpString[0].append(getAtomId(*ref_atoms[i], molgraph, tmpString[1]));
    }

    if (num_ref_atoms == 3) {
        tmpString[0].push_back(' ');
        tmpString[0].append(getAtomId(atom, molgraph, tmpString[1]));
    }

    endXMLStartTag(os, false);

    beginXMLStartTag(os, CML::Element::ATOM_PARITY, 4, elemNamespace);

    writeXMLAttribute(os, CML::Attribute::REF_ATOMS4, tmpString[0]);
    
    endXMLStartTag(os, false, false);

    os << parity;
    
    writeXMLEndTag(os, CML::Element::ATOM_PARITY, 0, elemNamespace);

    return true;
}

bool Chem::CMLDataWriter::writeAtomsCompact(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;
    
    std::size_t num_charges = 0;
    std::size_t num_2d_coords = 0;
    std::size_t num_3d_coords = 0;
    auto num_atoms = molgraph.getNumAtoms();
    
    for (std::size_t i = 0; i < num_atoms; i++) {
        if (outputAtomParity) {
             auto& stereo_desc = atomStereoDescrs[i];
   
             if (stereo_desc.getNumReferenceAtoms() >= 3)
                 switch (stereo_desc.getConfiguration()) {

                     case AtomConfiguration::S:
                     case AtomConfiguration::R:
                         return false;
                 }
        }

        auto& atom = molgraph.getAtom(i);
        
        if (outputSpinMult && (getUnpairedElectronCount(atom) > 0))
            return false;

        if (outputIsotope && (getIsotope(atom) > 0))
            return false;

        if (getFormalCharge(atom) != 0)
            num_charges++;
        
        if (has2DCoordinates(atom))
            num_2d_coords++;

        if (multiConfExport || has3DCoordinates(atom))
            num_3d_coords++;
    }

    if ((num_2d_coords > 0) && (num_2d_coords != num_atoms))
        return false;

    if ((num_3d_coords > 0) && (num_3d_coords != num_atoms))
        return false;

    auto first_atom = true;

    for (auto& str : tmpString)
        str.clear();
    
    for (auto& atom : molgraph.getAtoms()) {
        if (!first_atom) {
            tmpString[1].push_back(' ');
            tmpString[2].push_back(' ');

            if (num_charges > 0)
                tmpString[3].push_back(' ');

            if (num_2d_coords > 0) {
                tmpString[4].push_back(' ');
                tmpString[5].push_back(' ');
            }

            if (num_3d_coords > 0) {
                tmpString[6].push_back(' ');
                tmpString[7].push_back(' ');
                tmpString[8].push_back(' ');
            }
            
        } else
            first_atom = false;

        tmpString[1].append(getAtomId(atom, molgraph, tmpString[0]));
        
        if (hasSymbol(atom)) {
            auto& symbol = getSymbol(atom);

            if (containsWS(symbol))
                return false;
            
            tmpString[2].append(symbol);
            
        } else if (hasType(atom)) {
            auto& symbol = AtomDictionary::getSymbol(getType(atom));
            
            if (symbol.empty())
                return false;

            if (containsWS(symbol))
                return false;
            
            tmpString[2].append(escapeXMLData(symbol, tmpString[0], true));

        } else
            tmpString[2].append(CML::AtomType::DUMMY_1);

        if (num_charges > 0)
            tmpString[3].append(std::to_string(getFormalCharge(atom)));

        if (num_2d_coords > 0) {
            auto& coords = get2DCoordinates(atom);

            tmpString[4].append(std::to_string(coords[0]));
            tmpString[5].append(std::to_string(coords[1]));
        }
        
        if (num_3d_coords > 0) {
            auto& coords = (multiConfExport ? confCoordinates[molgraph.getAtomIndex(atom)] : get3DCoordinates(atom));

            tmpString[6].append(std::to_string(coords[0]));
            tmpString[7].append(std::to_string(coords[1]));
            tmpString[8].append(std::to_string(coords[2]));
        }
    }

    writeXMLAttribute(os, CML::Attribute::ATOM_ID_ARRAY, tmpString[1]);
    writeXMLAttribute(os, CML::Attribute::ELEMENT_TYPE_ARRAY, tmpString[2]);

    if (num_charges > 0)
        writeXMLAttribute(os, CML::Attribute::FORMAL_CHARGE_ARRAY, tmpString[3]);
    
    if (num_2d_coords > 0) {
        writeXMLAttribute(os, CML::Attribute::X2_ARRAY, tmpString[4]);
        writeXMLAttribute(os, CML::Attribute::Y2_ARRAY, tmpString[5]);
    }

    if (num_3d_coords > 0) {
        writeXMLAttribute(os, CML::Attribute::X3_ARRAY, tmpString[6]);
        writeXMLAttribute(os, CML::Attribute::Y3_ARRAY, tmpString[7]);
        writeXMLAttribute(os, CML::Attribute::Z3_ARRAY, tmpString[8]);
    }

    endXMLStartTag(os, true);
    
    return true;
}

void Chem::CMLDataWriter::calcAtomStereoDescriptors(const MolecularGraph& molgraph)
{
    if (!outputAtomParity)
        return;
    
    auto num_atoms = molgraph.getNumAtoms();
    
    if (atomStereoDescrs.size() < num_atoms)
        atomStereoDescrs.resize(num_atoms, StereoDescriptor(0));

    for (std::size_t i = 0; i < num_atoms; i++)
        atomStereoDescrs[i] = calcStereoDescriptor(molgraph.getAtom(i), molgraph, 0);
}
           
void Chem::CMLDataWriter::writeBonds(std::ostream& os, const MolecularGraph& molgraph, bool have_2d_coords)
{
    using namespace Internal;

    if (molgraph.getNumBonds() == 0)
        return;

    calcBondStereoDescriptors(molgraph);

    if (compactBondData && writeBondsCompact(os, molgraph, have_2d_coords))
        return;
    
    std::size_t bond_id = 0;
    
    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;
        
        if (bond_id == 0) {
            beginXMLStartTag(os, CML::Element::BOND_ARRAY, 2, elemNamespace);
            endXMLStartTag(os);
        }

        beginXMLStartTag(os, CML::Element::BOND, 3, elemNamespace);

        writeXMLAttribute(os, CML::Attribute::ID, BOND_ID_PREFIX + std::to_string(++bond_id));
        writeXMLAttribute(os, CML::Attribute::REF_ATOMS2, getAtomId(atom1, molgraph, tmpString[0]) +
                       ' ' + getAtomId(atom2, molgraph, tmpString[1]));

        if (!outputKekulized && getAromaticityFlag(bond))
            writeXMLAttribute(os, CML::Attribute::ORDER, CML::BondOrder::AROMATIC);

        else {
            switch (getOrder(bond)) {

                case 1:
                    writeXMLAttribute(os, CML::Attribute::ORDER, CML::BondOrder::SINGLE_1);
                    break;

                case 2:
                    writeXMLAttribute(os, CML::Attribute::ORDER, CML::BondOrder::DOUBLE_1);
                    break;

                case 3:
                    writeXMLAttribute(os, CML::Attribute::ORDER, CML::BondOrder::TRIPLE_1);
                    break;

                default:
                    writeXMLAttribute(os, CML::Attribute::ORDER, CML::BondOrder::UNKNOWN);
            }
        }

        if ((outputSBStereo || outputDBStereo) && writeBondStereo(os, bond, molgraph, have_2d_coords))
            writeXMLEndTag(os, CML::Element::BOND, 3, elemNamespace);
        else
            endXMLStartTag(os, true);
    }

    if (bond_id > 0)
        Internal::writeXMLEndTag(os, CML::Element::BOND_ARRAY, 2, elemNamespace);
}

bool Chem::CMLDataWriter::writeBondStereo(std::ostream& os, const Bond& bond, const MolecularGraph& molgraph, bool write_sf)
{
    using namespace Internal;

    auto order = getOrder(bond);
    const std::string* stereo = nullptr;
    
    if (order == 1) {
        if (!outputSBStereo || !write_sf)
            return false;
        
        bool swap_atoms = false;
        
        switch (get2DStereoFlag(bond)) {

            case BondStereoFlag::UP:
                stereo = &CML::BondStereo::WEDGED;
                break;

            case BondStereoFlag::REVERSE_UP:
                stereo = &CML::BondStereo::WEDGED;
                swap_atoms = true;
                break;
                
            case BondStereoFlag::DOWN:
                stereo = &CML::BondStereo::HATCHED;
                break;

            case BondStereoFlag::REVERSE_DOWN:
                stereo = &CML::BondStereo::HATCHED;
                swap_atoms = true;
                break;
                
            default:
                return false;
        }

        endXMLStartTag(os, false);

        beginXMLStartTag(os, CML::Element::BOND_STEREO, 4, elemNamespace);

        writeXMLAttribute(os, CML::Attribute::REF_ATOMS2,
                          getAtomId(swap_atoms ? bond.getEnd() : bond.getBegin(), molgraph, tmpString[0]) +
                          ' ' + getAtomId(swap_atoms ? bond.getBegin() : bond.getEnd(), molgraph, tmpString[1]));
    
    } else if (order == 2) {
        if (!outputDBStereo)
            return false;
        
        const auto& stereo_desc = bondStereoDescrs[molgraph.getBondIndex(bond)];
        auto num_ref_atoms = stereo_desc.getNumReferenceAtoms();

        if (num_ref_atoms != 4)
            return false;

        switch (stereo_desc.getConfiguration()) {

            case BondConfiguration::CIS:
                stereo = &CML::BondStereo::CIS;
                break;

            case BondConfiguration::TRANS:
                stereo = &CML::BondStereo::TRANS;
                break;

            default:
                return false;
        }

        auto ref_atoms = stereo_desc.getReferenceAtoms();

        getAtomId(*ref_atoms[0], molgraph, tmpString[0]);
    
        for (std::size_t i = 1; i < 4; i++) {
            tmpString[0].push_back(' ');
            tmpString[0].append(getAtomId(*ref_atoms[i], molgraph, tmpString[1]));
        }

        endXMLStartTag(os, false);

        beginXMLStartTag(os, CML::Element::BOND_STEREO, 4, elemNamespace);
        
        writeXMLAttribute(os, CML::Attribute::REF_ATOMS4, tmpString[0]);

    } else
        return false;

    endXMLStartTag(os, false, false);

    os << *stereo;
    
    writeXMLEndTag(os, CML::Element::BOND_STEREO, 0, elemNamespace);

    return true;
}

bool Chem::CMLDataWriter::writeBondsCompact(std::ostream& os, const MolecularGraph& molgraph, bool have_2d_coords)
{
    using namespace Internal;
 
    auto num_bonds = molgraph.getNumBonds();
    std::size_t num_valid_bonds = 0;
    
    for (std::size_t i = 0; i < num_bonds; i++) {
        auto& bond = molgraph.getBond(i);

        if (!molgraph.containsAtom(bond.getBegin()))
            continue;

        if (!molgraph.containsAtom(bond.getEnd()))
            continue;

        num_valid_bonds++;

        auto order = getOrder(bond);
        
        if (outputDBStereo && (order == 2)) {
             auto& stereo_desc = bondStereoDescrs[i];
   
             if (stereo_desc.getNumReferenceAtoms() != 4)
                 continue;
                 
             switch (stereo_desc.getConfiguration()) {

                 case BondConfiguration::CIS:
                 case BondConfiguration::TRANS:
                     return false;
             }
        }

        if (have_2d_coords && outputSBStereo && (order == 1))
            switch (get2DStereoFlag(bond)) {

                case BondStereoFlag::UP:
                case BondStereoFlag::REVERSE_UP:
                case BondStereoFlag::DOWN:
                case BondStereoFlag::REVERSE_DOWN:
                     return false;
             }
    }

    if (num_valid_bonds == 0)
        return true;
    
    std::size_t bond_id = 0;

    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;
        
        if (bond_id > 0) {
            for (auto i = 0; i <= 4; i++)
                tmpString[i].push_back(' ');

        } else {
            for (auto i = 0; i <= 4; i++)
                tmpString[i].clear();

            beginXMLStartTag(os, CML::Element::BOND_ARRAY, 2, elemNamespace);
        }

        tmpString[1].append(BOND_ID_PREFIX + std::to_string(++bond_id));
        tmpString[2].append(getAtomId(atom1, molgraph, tmpString[0]));
        tmpString[3].append(getAtomId(atom2, molgraph, tmpString[0]));

        if (!outputKekulized && getAromaticityFlag(bond))
            tmpString[4].append(CML::BondOrder::AROMATIC);

        else {
            switch (getOrder(bond)) {

                case 1:
                    tmpString[4].append(CML::BondOrder::SINGLE_1);
                    break;

                case 2:
                    tmpString[4].append(CML::BondOrder::DOUBLE_1);
                    break;

                case 3:
                    tmpString[4].append(CML::BondOrder::TRIPLE_1);
                    break;

                default:
                    tmpString[4].append(CML::BondOrder::UNKNOWN);
            }
        }
    }

    writeXMLAttribute(os, CML::Attribute::BOND_ID_ARRAY, tmpString[1]);
    writeXMLAttribute(os, CML::Attribute::REF_ATOM1_ARRAY, tmpString[2]);
    writeXMLAttribute(os, CML::Attribute::REF_ATOM2_ARRAY, tmpString[3]);
    writeXMLAttribute(os, CML::Attribute::ORDER_ARRAY, tmpString[4]);

    endXMLStartTag(os, true);
    
    return true;
}

void Chem::CMLDataWriter::calcBondStereoDescriptors(const MolecularGraph& molgraph)
{
    if (!outputDBStereo)
        return;
    
    auto num_bonds = molgraph.getNumBonds();
    
    if (bondStereoDescrs.size() < num_bonds)
        bondStereoDescrs.resize(num_bonds, StereoDescriptor(0));

    for (std::size_t i = 0; i < num_bonds; i++) {
        auto& bond = molgraph.getBond(i);

        if (getOrder(bond) != 2) {
            bondStereoDescrs[i] = StereoDescriptor(0);
            continue;
        }
        
        bondStereoDescrs[i] = calcStereoDescriptor(bond, molgraph, 0);
    }
}

void Chem::CMLDataWriter::writeProperties(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;

    if (!hasStructureData(molgraph))
        return;
 
    auto& struct_data = getStructureData(molgraph);

    if (!struct_data || struct_data->isEmpty())
        return;

    for (auto& item : *struct_data) {
        beginXMLStartTag(os, CML::Element::PROPERTY, 2, elemNamespace);

        writeXMLAttribute(os, CML::Attribute::TITLE, escapeXMLData(item.getHeader(), tmpString[0], true));
        
        endXMLStartTag(os);
        
        beginXMLStartTag(os, CML::Element::SCALAR, 3, elemNamespace);

        writeXMLAttribute(os, CML::Attribute::UNIT, CML::AttributeValue::STRING_PROP_UNIT);
        writeXMLAttribute(os, CML::Attribute::DATA_TYPE, CML::AttributeValue::STRING_PROP_DATA_TYPE);

        endXMLStartTag(os, false, false);

        os << escapeXMLData(item.getData(), tmpString[0], false);

        writeXMLEndTag(os, CML::Element::SCALAR, 0, elemNamespace);
        writeXMLEndTag(os, CML::Element::PROPERTY, 2, elemNamespace);
    }
}

const std::string& Chem::CMLDataWriter::getAtomId(const Atom& atom, const MolecularGraph& molgraph, std::string& id_str) const
{
    id_str = ATOM_ID_PREFIX;

    id_str.append(std::to_string(molgraph.getAtomIndex(atom) + 1));

    return id_str;
}
