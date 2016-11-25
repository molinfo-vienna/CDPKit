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
import os.path
import glob
import CDPL.Base as Base
import CDPL.Chem as Chem
import CDPL.Biomol as Biomol
import CDPL.Math as Math


def process():
    if len(sys.argv) < 3:
        print >> sys.stderr, 'Usage:', sys.argv[0], '[directory with PDB-files] [output.cdf]'
        sys.exit(2)

    cdf_mol = Chem.BasicMolecule()
    pdb_mol = Chem.BasicMolecule()
    pdb_files = glob.glob(sys.argv[1] + '/*.pdb') # TODO: Order by increasing frame-number

    for pdb_file in pdb_files:
        pdb_reader = Biomol.PDBMoleculeReader(Base.FileIOStream(pdb_file, 'r'))

        print '- Processing PDB-file:', os.path.basename(pdb_file), '...'

        pdb_mol.clear();

        if not pdb_reader.read(pdb_mol):
            print '!! Could not read file'
            continue

        Chem.calcImplicitHydrogenCounts(pdb_mol, True)
        Chem.perceiveHybridizationStates(pdb_mol, True)        
        Chem.setAtomSymbolsFromTypes(pdb_mol, False)        
        Chem.setRingFlags(pdb_mol, True)
        Chem.setAromaticityFlags(pdb_mol, True)

        if cdf_mol.numAtoms == 0:
            cdf_mol.assign(pdb_mol)

            for atom in cdf_mol.atoms:
                Chem.set3DCoordinatesArray(atom, Math.Vector3DArray())

        elif cdf_mol.numAtoms != pdb_mol.numAtoms:
            print '!! Atom count mismatch'
            continue

        i = 0

        while i < cdf_mol.numAtoms:
            Chem.get3DCoordinatesArray(cdf_mol.getAtom(i)).addElement(Chem.get3DCoordinates(pdb_mol.getAtom(i)))
            i += 1

    ofs = Base.FileIOStream(sys.argv[2], 'w')
    
    if not Chem.CDFMolecularGraphWriter(ofs).write(cdf_mol):
        print '!! Could not write output file'

if __name__ == '__main__':
    process()
