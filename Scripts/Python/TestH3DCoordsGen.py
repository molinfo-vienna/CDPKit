# -*- mode: python; tab-width: 4 -*- 

## 
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2008 Thomas A. Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##


import sys
import CDPL.Base as Base
import CDPL.Chem as Chem


def performTest():
    if len(sys.argv) < 3:
        print >> sys.stderr, 'Usage:', sys.argv[0], 'input.sdf output.sdf'
        sys.exit(2)

    ifs = Base.FileIOStream(sys.argv[1], 'r')
    ofs = Base.FileIOStream(sys.argv[2], 'w')

    reader = Chem.SDFMoleculeReader(ifs)
    writer = Chem.SDFMolecularGraphWriter(ofs)

    mol = Chem.BasicMolecule()

    Chem.setMultiConfImportParameter(reader, False)
    Chem.setMultiConfExportParameter(writer, False)
    
    if reader.read(mol):
        Chem.makeHydrogenDeplete(mol)
        Chem.calcImplicitHydrogenCounts(mol, True)
        Chem.perceiveHybridizationStates(mol, True)        

        Chem.makeHydrogenComplete(mol)
        Chem.setAtomSymbolsFromTypes(mol, False)        
        Chem.calcImplicitHydrogenCounts(mol, True)
        Chem.perceiveHybridizationStates(mol, True)        
        Chem.generateHydrogen3DCoordinates(mol, False)        

        Chem.perceiveComponents(mol, True)
        Chem.perceiveSSSR(mol, True)
        Chem.setRingFlags(mol, True)
        Chem.setAromaticityFlags(mol, True)

        if not writer.write(mol):
            print 'Could not write output molecule'

    else:
            print 'Could not read input molecule'

if __name__ == '__main__':
    performTest()
