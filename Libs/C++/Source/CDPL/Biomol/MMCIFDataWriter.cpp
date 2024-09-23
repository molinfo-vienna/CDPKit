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

#include <ostream>

#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
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
    
    const std::string DEF_DATA_BLOCK_ID_PREFIX{"MOL"};
}


bool Biomol::MMCIFDataWriter::writeMolecularGraph(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
    init(os);

    setDataBlockId(molgraph);
    
    if (writeAsChemComp || !genMacromoleculeData(molgraph))
        genChemCompData(molgraph);

    return (os << mmCIFData).good();
}

void Biomol::MMCIFDataWriter::init(std::ostream& os)
{
    strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
    resDictionary       = getResidueDictionaryParameter(ioBase);
    writeAsChemComp     = true; // TODO

    mmCIFData.clear();
    numOutDataBlocks++;
}

bool Biomol::MMCIFDataWriter::genMacromoleculeData(const Chem::MolecularGraph& molgraph)
{
    // TODO
    return false;
}

void Biomol::MMCIFDataWriter::genChemCompData(const Chem::MolecularGraph& molgraph)
{
    using namespace MMCIF;
    
    const std::string& comp_id = getChemCompId(molgraph);

    genChemCompAtomsData(molgraph, comp_id);
    genChemCompBondsData(molgraph, comp_id);
    
    auto& chem_comp = mmCIFData.addCategory(ChemComp::NAME, true);
    auto& comp_id_itm = chem_comp.addItem(ChemComp::Item::ID);
    auto& comp_name = chem_comp.addItem(ChemComp::Item::NAME);
     
    comp_id_itm.addValue(comp_id);
   
    if (hasName(molgraph))
        comp_name.addValue(getName(molgraph));
    else
        comp_name.addValue(MISSING_DATA_VALUE);
}

void Biomol::MMCIFDataWriter::genChemCompAtomsData(const Chem::MolecularGraph& molgraph, const std::string& comp_id)
{
    // TODO
}

void Biomol::MMCIFDataWriter::genChemCompBondsData(const Chem::MolecularGraph& molgraph, const std::string& comp_id)
{
    // TODO
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
