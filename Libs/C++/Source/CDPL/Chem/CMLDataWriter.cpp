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
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"
#include "CDPL/Internal/AtomContainerFunctions.hpp"

#include "CMLDataWriter.hpp"
#include "CMLFormatData.hpp"


using namespace CDPL;


namespace
{

    const std::string MOLECULE_ID_PREFIX = "m";
    const std::string ATOM_ID_PREFIX     = "a";
    const std::string BOND_ID_PREFIX     = "b";
} // namespace


Chem::CMLDataWriter::CMLDataWriter(const Base::DataIOBase& io_base):
    ioBase(io_base), startDoc(true)
{}

bool Chem::CMLDataWriter::writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph)
{
    getControlParams();
    
    if (startDoc) {
        startDocument(os);

        startDoc = false;
        molId = 1;
    }

    startMoleculeElement(os, molgraph);
    writeName(os, molgraph);
    writeAtoms(os, molgraph);
    writeBonds(os, molgraph);
    writeProperties(os, molgraph);
    endMoleculeElement(os);
    
    return os.good();
}

void Chem::CMLDataWriter::close(std::ostream& os)
{
    if (startDoc)
        return;

    endDocument(os);
    startDoc = true;
}

void Chem::CMLDataWriter::getControlParams()
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
}

void Chem::CMLDataWriter::startDocument(std::ostream& os) const
{
    os << CML::DOC_PROLOG << '\n';
}

void Chem::CMLDataWriter::endDocument(std::ostream& os) const
{
    os << CML::DOC_EPILOG << '\n';
}

void Chem::CMLDataWriter::startMoleculeElement(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;
    
    beginXMLStartTag(os, CML::Element::MOLECULE, 1);

    writeXMLAttribute(os, CML::Attribute::ID, MOLECULE_ID_PREFIX + std::to_string(molId++));

    if (auto form_charge = getNetFormalCharge(molgraph))
        writeXMLAttribute(os, CML::Attribute::FORMAL_CHARGE, form_charge);

    endXMLStartTag(os);
}

void Chem::CMLDataWriter::endMoleculeElement(std::ostream& os) const
{
    Internal::writeXMLEndTag(os, CML::Element::MOLECULE, 1);
}

void Chem::CMLDataWriter::writeName(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;

    if (!hasName(molgraph))
        return;

    beginXMLStartTag(os, CML::Element::NAME, 2);
    endXMLStartTag(os, false, false);
    
    os << escapeXMLData(getName(molgraph), tmpString[0], false);
    
    writeXMLEndTag(os, CML::Element::NAME, 0);
}

void Chem::CMLDataWriter::writeAtoms(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;

    if (molgraph.getNumAtoms() == 0)
        return;
    
    beginXMLStartTag(os, CML::Element::ATOM_ARRAY, 2);
    endXMLStartTag(os);

    for (auto& atom : molgraph.getAtoms()) {
        beginXMLStartTag(os, CML::Element::ATOM, 3);

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
        
        if (auto iso = getIsotope(atom))
            writeXMLAttribute(os, CML::Attribute::ISOTOPE, iso);

        if (auto form_chg = getFormalCharge(atom))
            writeXMLAttribute(os, CML::Attribute::FORMAL_CHARGE, form_chg);

        if (auto unp_el_count = getUnpairedElectronCount(atom))
            writeXMLAttribute(os, CML::Attribute::SPIN_MULTIPLICITY, (unp_el_count + 1));
            
        if (has2DCoordinates(atom)) {
            auto& coords = get2DCoordinates(atom);

            writeXMLAttribute(os, CML::Attribute::X2, coords[0]);
            writeXMLAttribute(os, CML::Attribute::Y2, coords[1]);
        }

        if (has3DCoordinates(atom)) {
            auto& coords = get3DCoordinates(atom);

            writeXMLAttribute(os, CML::Attribute::X3, coords[0]);
            writeXMLAttribute(os, CML::Attribute::Y3, coords[1]);
            writeXMLAttribute(os, CML::Attribute::Z3, coords[2]);
        }
        
        if (writeAtomParity(os, atom, molgraph))
            writeXMLEndTag(os, CML::Element::ATOM, 3);
        else
            endXMLStartTag(os, true);
    }
    
    Internal::writeXMLEndTag(os, CML::Element::ATOM_ARRAY, 2);
}

bool Chem::CMLDataWriter::writeAtomParity(std::ostream& os, const Atom& atom, const MolecularGraph& molgraph)
{
    using namespace Internal;
    
    const auto& stereo_desc = calcStereoDescriptor(atom, molgraph, 0);
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

    beginXMLStartTag(os, CML::Element::ATOM_PARITY, 4);

    writeXMLAttribute(os, CML::Attribute::REF_ATOMS4, tmpString[0]);
    
    endXMLStartTag(os, false, false);

    os << parity;
    
    writeXMLEndTag(os, CML::Element::ATOM_PARITY, 0);

    return true;
}
    
void Chem::CMLDataWriter::writeBonds(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;

    if (molgraph.getNumBonds() == 0)
        return;

    std::size_t bond_id = 0;
    auto have_2d_coords = hasCoordinates(molgraph, 2);
    
    for (auto& bond : molgraph.getBonds()) {
        auto& atom1 = bond.getBegin();

        if (!molgraph.containsAtom(atom1))
            continue;

        auto& atom2 = bond.getEnd();

        if (!molgraph.containsAtom(atom2))
            continue;
        
        if (bond_id == 0) {
            beginXMLStartTag(os, CML::Element::BOND_ARRAY, 2);
            endXMLStartTag(os);
        }

        beginXMLStartTag(os, CML::Element::BOND, 3);

        writeXMLAttribute(os, CML::Attribute::ID, BOND_ID_PREFIX + std::to_string(++bond_id));
        writeXMLAttribute(os, CML::Attribute::REF_ATOMS2, getAtomId(atom1, molgraph, tmpString[0]) +
                       ' ' + getAtomId(atom2, molgraph, tmpString[1]));

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
                                                                 
        if (writeBondStereo(os, bond, molgraph, have_2d_coords))
            writeXMLEndTag(os, CML::Element::BOND, 3);
        else
            endXMLStartTag(os, true);
    }

    if (bond_id > 0)
        Internal::writeXMLEndTag(os, CML::Element::BOND_ARRAY, 2);
}

bool Chem::CMLDataWriter::writeBondStereo(std::ostream& os, const Bond& bond, const MolecularGraph& molgraph, bool write_sf)
{
    using namespace Internal;

    auto order = getOrder(bond);
    const std::string* stereo = nullptr;
    
    if (order == 1) {
        if (!write_sf)
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

        beginXMLStartTag(os, CML::Element::BOND_STEREO, 4);

        writeXMLAttribute(os, CML::Attribute::REF_ATOMS2,
                          getAtomId(swap_atoms ? bond.getEnd() : bond.getBegin(), molgraph, tmpString[0]) +
                          ' ' + getAtomId(swap_atoms ? bond.getBegin() : bond.getEnd(), molgraph, tmpString[1]));
    
    } else if (order == 2) {
        const auto& stereo_desc = calcStereoDescriptor(bond, molgraph, 0);
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

        beginXMLStartTag(os, CML::Element::BOND_STEREO, 4);
        
        writeXMLAttribute(os, CML::Attribute::REF_ATOMS4, tmpString[0]);

    } else
        return false;

    endXMLStartTag(os, false, false);

    os << *stereo;
    
    writeXMLEndTag(os, CML::Element::BOND_STEREO, 0);

    return true;
}

void Chem::CMLDataWriter::writeProperties(std::ostream& os, const MolecularGraph& molgraph)
{
    using namespace Internal;

    auto& struct_data = getStructureData(molgraph);

    if (!struct_data || struct_data->isEmpty())
        return;

    for (auto& item : *struct_data) {
        beginXMLStartTag(os, CML::Element::PROPERTY, 2);

        writeXMLAttribute(os, CML::Attribute::TITLE, escapeXMLData(item.getHeader(), tmpString[0], true));
        
        endXMLStartTag(os);
        
        beginXMLStartTag(os, CML::Element::SCALAR, 3);

        writeXMLAttribute(os, CML::Attribute::UNIT, CML::AttributeValue::STRING_PROP_UNIT);
        writeXMLAttribute(os, CML::Attribute::DATA_TYPE, CML::AttributeValue::STRING_PROP_DATA_TYPE);

        endXMLStartTag(os, false, false);

        os << escapeXMLData(item.getData(), tmpString[0], false);

        writeXMLEndTag(os, CML::Element::SCALAR, 0);
                
        writeXMLEndTag(os, CML::Element::PROPERTY, 2);
    }
}

const std::string& Chem::CMLDataWriter::getAtomId(const Atom& atom, const MolecularGraph& molgraph, std::string& id_str) const
{
    id_str = ATOM_ID_PREFIX;

    id_str.append(std::to_string(molgraph.getAtomIndex(atom) + 1));

    return id_str;
}
