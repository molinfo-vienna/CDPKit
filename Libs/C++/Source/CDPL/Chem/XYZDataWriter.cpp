/* 
 * XYZDataWriter.cpp 
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

#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Base/DataIOBase.hpp"

#include "XYZDataWriter.hpp"


using namespace CDPL;


namespace
{

    constexpr char    END_OF_LINE  = '\n';
    const std::string UNDEF_SYMBOL = "*";
}


bool Chem::XYZDataWriter::writeMolecularGraph(std::ostream& os, const MolecularGraph& molgraph)
{
    init(os);

    std::size_t num_confs = (multiConfExport ? getNumConformations(molgraph) : 0);

    if (num_confs == 0) {
        multiConfExport = false;

        writeRecord(os, molgraph);

    } else {
        Util::DArray::SharedPointer conf_energies;

        if (writeConfEnergyComment && hasConformerEnergies(molgraph))
            conf_energies = getConformerEnergies(molgraph);

        confCoordinates.resize(molgraph.getNumAtoms());

        for (std::size_t i = 0; i < num_confs; i++) {
            getConformation(molgraph, i, confCoordinates, false);

            if (writeConfEnergyComment && conf_energies && conf_energies->getSize() > i)
                writeRecord(os, molgraph, (*conf_energies)[i]);
            else
                writeRecord(os, molgraph);
        }
    }

    return os.good();
}

void Chem::XYZDataWriter::init(std::ostream& os)
{
    os.imbue(std::locale::classic());

    multiConfExport        = getMultiConfExportParameter(ioBase);
    writeConfEnergyComment = (multiConfExport && getOutputConfEnergyAsCommentParameter(ioBase));
    commentIsName          = getXYZCommentIsNameParameter(ioBase);
    
    os << std::fixed << std::showpoint;
}

void Chem::XYZDataWriter::writeRecord(std::ostream& os, const AtomContainer& cntnr, double energy)
{
     os << cntnr.getNumAtoms() << END_OF_LINE;
     os << energy << END_OF_LINE;

     writeAtomList(os, cntnr);
}

void Chem::XYZDataWriter::writeRecord(std::ostream& os, const MolecularGraph& molgraph)
{
     os << molgraph.getNumAtoms() << END_OF_LINE;
     os << (commentIsName ? getName(molgraph) : getComment(molgraph)) << END_OF_LINE;

     writeAtomList(os, molgraph);
}

void Chem::XYZDataWriter::writeAtomList(std::ostream& os, const AtomContainer& cntnr)
{
    for (std::size_t i = 0, num_atoms = cntnr.getNumAtoms(); i < num_atoms; i++) {
        const Atom& atom = cntnr.getAtom(i);
        const Math::Vector3D& coords = (multiConfExport ? confCoordinates[i] : get3DCoordinates(atom));
        const std::string& symbol = (hasSymbol(atom) ? getSymbol(atom) : getSymbolForType(atom));
        
        os << (!symbol.empty() ? symbol : UNDEF_SYMBOL) << ' ';
        os << coords[0] << ' ' << coords[1] << ' ' << coords[2] << END_OF_LINE;
    }
}
