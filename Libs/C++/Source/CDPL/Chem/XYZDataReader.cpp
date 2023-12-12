/* 
 * XYZDataReader.cpp 
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

#include <algorithm>
#include <istream>
#include <locale>
#include <functional>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Util/SequenceFunctions.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "XYZDataReader.hpp"


using namespace CDPL;


bool Chem::XYZDataReader::readMolecule(std::istream& is, Molecule& mol)
{
    using namespace std::placeholders;
    
    if (!hasMoreData(is))
        return false;

    init(is);

    std::size_t atom_idx_offs = mol.getNumAtoms();
    std::size_t bond_idx_offs = mol.getNumBonds();

    readAtomCount(is);
    readComment(is, mol);
    readAtoms(is, mol);
    postProcess(mol);
    
    if (multiConfImport) {
        MolecularGraph* tgt_molgraph;

        if (atom_idx_offs == 0) {
            tgt_molgraph = &mol;

        } else {
            if (!tmpFragment)
                tmpFragment.reset(new Fragment());
            else
                tmpFragment->clear();

            tgt_molgraph = tmpFragment.get();

            std::for_each(mol.getAtomsBegin() + atom_idx_offs, mol.getAtomsEnd(), std::bind(&Fragment::addAtom, tmpFragment.get(), _1));
            std::for_each(mol.getBondsBegin() + bond_idx_offs, mol.getBondsEnd(), std::bind(&Fragment::addBond, tmpFragment.get(), _1));
            
            tmpFragment->copyProperties(mol);
        }

        MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

        if (!mc_input_proc) {
            for (MolecularGraph::AtomIterator it = tgt_molgraph->getAtomsBegin(), end = tgt_molgraph->getAtomsEnd(); it != end; ++it) {
                Atom& atom = *it;
                Math::Vector3DArray::SharedPointer coords_array(new Math::Vector3DArray());
        
                set3DCoordinatesArray(atom, coords_array);
        
                coords_array->addElement(get3DCoordinates(atom));
            }
            
            while (hasMoreData(is)) {
                std::istream::pos_type last_spos = is.tellg();

                if (!addConformer(is, *tgt_molgraph)) {
                    is.seekg(last_spos);
                    return true;
                }
            }

            return true;
        }

        if (!mc_input_proc->init(*tgt_molgraph))
            return true;

        if (!confTestMolecule)
            confTestMolecule.reset(new BasicMolecule());

        while (hasMoreData(is)) {
            std::istream::pos_type last_spos = is.tellg();
            confTestMolecule->clear();

            readAtomCount(is);
            readComment(is, *confTestMolecule);
            readAtoms(is, *confTestMolecule);
            postProcess(*confTestMolecule);
            
            if (!mc_input_proc->addConformation(*tgt_molgraph, *confTestMolecule)) {
                is.seekg(last_spos);
                return true;
            }
        }
    }

    return true;
}

bool Chem::XYZDataReader::skipMolecule(std::istream& is)
{
    if (!hasMoreData(is))
        return false;

    init(is);

    if (!multiConfImport) {
        readAtomCount(is);
        Internal::skipLines(is, atomCount + 1, "XYZDataReader: error while skipping molecule");
        return true;
    }

    if (!confTargetMolecule)
        confTargetMolecule.reset(new BasicMolecule());
    else
        confTargetMolecule->clear();

    readAtomCount(is);
    readComment(is, *confTargetMolecule);
    readAtoms(is, *confTargetMolecule);

    MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

    if (!mc_input_proc) {
        while (hasMoreData(is)) {
            std::istream::pos_type last_spos = is.tellg();

            if (!readNextConformer(is, *confTargetMolecule, false)) {
                is.seekg(last_spos);
                return true;
            }
        }
        
        return true;
    }

    postProcess(*confTargetMolecule);

    if (!mc_input_proc->init(*confTargetMolecule))
        return true;

    if (!confTestMolecule)
        confTestMolecule.reset(new BasicMolecule());

    while (hasMoreData(is)) {
        std::istream::pos_type last_spos = is.tellg();
        confTestMolecule->clear();

        readAtomCount(is);
        readComment(is, *confTestMolecule);
        readAtoms(is, *confTestMolecule);
        postProcess(*confTestMolecule);
        
        if (!mc_input_proc->isConformation(*confTargetMolecule, *confTestMolecule)) {
            is.seekg(last_spos);
            return true;
        }
    }

    return true;
}

bool Chem::XYZDataReader::hasMoreData(std::istream& is) const
{
    return !std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof());
}

void Chem::XYZDataReader::init(std::istream& is)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
    multiConfImport     = getMultiConfImportParameter(ioBase);
    commentIsName       = getXYZCommentIsNameParameter(ioBase);
    pcvConnectivity     = getXYZPerceiveConnectivityParameter(ioBase);
    pcvBondOrders       = getXYZPerceiveBondOrdersParameter(ioBase);
    calcFormCharges     = getXYZCalcFormalChargesParameter(ioBase);

    if (calcFormCharges)
        pcvBondOrders = true;

    if (pcvBondOrders)
        pcvConnectivity = true;
    
    is.imbue(std::locale::classic());
}

bool Chem::XYZDataReader::addConformer(std::istream& is, MolecularGraph& molgraph)
{
    if (!readNextConformer(is, molgraph, true))
        return false;

    addConformation(molgraph, confCoords);
    return true;
}

bool Chem::XYZDataReader::readNextConformer(std::istream& is, const MolecularGraph& molgraph, bool save_coords)
{
    readAtomCount(is);

    if (molgraph.getNumAtoms() != atomCount)
        return false;

    if (commentIsName) {
        if (Internal::readLine(is, tmpString, "XYZDataReader: error while reading comment line", true) != getName(molgraph))
            return false;
    } else
        Internal::skipLines(is, 1, "XYZDataReader: error while skipping comment line");

    if (save_coords)
        confCoords.resize(molgraph.getNumAtoms());

    for (std::size_t i = 0; i < atomCount; i++) {
        if (!(is >> tmpString))
            throw Base::IOError("XYZDataReader: error while reading atom symbol");

        if (tmpString != getSymbol(molgraph.getAtom(i)))
            return false;

        if (save_coords) {
            Math::Vector3D& coords = confCoords[i];

            if (!(is >> coords(0)))
                throw Base::IOError("XYZDataReader: error while reading atom x coordinate");

            if (!(is >> coords(1)))
                throw Base::IOError("XYZDataReader: error while reading atom y coordinate");

            if (!(is >> coords(2)))
                throw Base::IOError("XYZDataReader: error while reading atom z coordinate");
        }

        Internal::skipLines(is, 1, "XYZDataReader: error while reading atom line");
    }    

    return true;
}

void Chem::XYZDataReader::readAtomCount(std::istream& is)
{
    if (!(is >> atomCount))
        throw Base::IOError("XYZDataReader: error while reading atom count");

    Internal::skipLines(is, 1, "XYZDataReader: error while reading atom count");
}

void Chem::XYZDataReader::readComment(std::istream& is, MolecularGraph& molgraph)
{
    Internal::readLine(is, tmpString, "XYZDataReader: error while reading comment line", true);

    if (commentIsName)
        setName(molgraph, tmpString);
    else
        setComment(molgraph, tmpString);
}

void Chem::XYZDataReader::readAtoms(std::istream& is, Molecule& mol)
{
    confCoords.resize(pcvConnectivity ? atomCount : 1);

    for (std::size_t i = 0; i < atomCount; i++) {
        if (!(is >> tmpString))
            throw Base::IOError("XYZDataReader: error while reading atom symbol");

        Atom& atom = mol.addAtom();

        setSymbol(atom, tmpString);
        setType(atom, AtomDictionary::getType(tmpString));

        Math::Vector3D& coords = confCoords.getData()[pcvConnectivity ? i : std::size_t(0)];  
        
        if (!(is >> coords(0)))
            throw Base::IOError("XYZDataReader: error while reading atom x coordinate");

        if (!(is >> coords(1)))
            throw Base::IOError("XYZDataReader: error while reading atom y coordinate");

        if (!(is >> coords(2)))
            throw Base::IOError("XYZDataReader: error while reading atom z coordinate");

        set3DCoordinates(atom, coords);

        Internal::skipLines(is, 1, "XYZDataReader: error while reading atom line");
    }
}

void Chem::XYZDataReader::postProcess(Molecule& mol)
{
    std::size_t atom_idx_offs = mol.getNumAtoms() - atomCount;
    std::size_t bond_idx_offs = mol.getNumBonds();
    
    if (pcvConnectivity)
        connectAtoms(mol,
                     [this, &mol, atom_idx_offs](const Atom& atom) -> const Math::Vector3D&
                         { return this->confCoords.getData()[mol.getAtomIndex(atom) - atom_idx_offs]; },
                     0.3, atom_idx_offs);

    if (!pcvBondOrders && !calcFormCharges)
        return;
    
    if (atom_idx_offs == 0) {
        if (pcvBondOrders) {
            setRingFlags(mol, true);
            perceiveSSSR(mol, true);
            
            bondOrderCalc.calculate(mol, bondOrders);

            Util::forEachPair(mol.getBondsBegin(), mol.getBondsEnd(), bondOrders.getElementsBegin(), &setOrder);
        }

        if (calcFormCharges) {
            for (auto& atom : mol.getAtoms())
                setImplicitHydrogenCount(atom, 0);

            calcFormalCharges(mol, true);
        }
        
        return;
    }

    if (!tmpFragment)
        tmpFragment.reset(new Fragment());
    else
        tmpFragment->clear();

    using namespace std::placeholders;

    std::for_each(mol.getAtomsBegin() + atom_idx_offs, mol.getAtomsEnd(), std::bind(&Fragment::addAtom, tmpFragment.get(), _1));
    std::for_each(mol.getBondsBegin() + bond_idx_offs, mol.getBondsEnd(), std::bind(&Fragment::addBond, tmpFragment.get(), _1));
    
    if (pcvBondOrders) {
        setRingFlags(*tmpFragment, true);
        perceiveSSSR(*tmpFragment, true);

        bondOrderCalc.calculate(*tmpFragment, bondOrders);
        
        Util::forEachPair(tmpFragment->getBondsBegin(), tmpFragment->getBondsEnd(), bondOrders.getElementsBegin(), &setOrder);
    }

    if (calcFormCharges) {
        for (auto& atom : tmpFragment->getAtoms())
            setImplicitHydrogenCount(atom, 0);
        
        calcFormalCharges(*tmpFragment, true);
    }
}
