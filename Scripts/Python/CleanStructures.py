# -*- mode: python; tab-width: 4 -*- 

## 
# CleanStructures.py 
#
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

class Stats:
    pass

def processMolecule(mol, stats):
    Chem.perceiveComponents(mol, False)
    Chem.perceiveSSSR(mol, False)
    Chem.setRingFlags(mol, False)
    Chem.calcImplicitHydrogenCounts(mol, False)
    Chem.perceiveHybridizationStates(mol, False)
    Chem.setAromaticityFlags(mol, False)

    if Chem.getAtomCount(mol, Chem.AtomType.F) > 9:
        return None

    modified = False
    comps = Chem.getComponents(mol)

    if comps.getSize() > 1:
        largest_comp = None

        for comp in comps:
            if largest_comp is None:
                largest_comp = comp
            elif comp.getNumAtoms() > largest_comp.getNumAtoms():
                largest_comp = comp

        Chem.perceiveComponents(largest_comp, False)
        Chem.perceiveSSSR(largest_comp, False)
        Chem.setName(largest_comp, Chem.getName(mol))

        print 'Removed Components from Molecule ' + Chem.generateSMILES(mol) + ' ' + Chem.getName(mol)

        modified = True
        mol = largest_comp

    for atom in mol.atoms:
        if Chem.getType(atom) == Chem.AtomType.C and Chem.getFormalCharge(atom) != 0:
            Chem.setFormalCharge(atom, 0)
            Chem.setImplicitHydrogenCount(atom, Chem.calcImplicitHydrogenCount(atom, mol))
            Chem.setHybridizationState(atom, Chem.perceiveHybridizationState(atom, mol))
            modified = True

    if modified:
        stats.modified += 1

    return mol

def cleanStructures():
    if len(sys.argv) < 4:
        print >> sys.stderr, 'Usage:', sys.argv[0], '[input *.smi] [output *.smi] [dropped *.smi]'
        sys.exit(2)

    ifs = Base.FileIOStream(sys.argv[1], 'r')
    ofs = Base.FileIOStream(sys.argv[2], 'w')
    dofs = Base.FileIOStream(sys.argv[3], 'w')

    reader = Chem.SMILESMoleculeReader(ifs)
    writer = Chem.SMILESMolecularGraphWriter(ofs)
    dwriter = Chem.SMILESMolecularGraphWriter(dofs)
    mol = Chem.BasicMolecule()
    
    Chem.setSMILESRecordFormatParameter(reader, 'S:N$')
    Chem.setSMILESRecordFormatParameter(writer, 'S:N$')
    Chem.setSMILESRecordFormatParameter(dwriter, 'S:N$')

    stats = Stats()
    stats.read = 0
    stats.dropped = 0
    stats.modified = 0

    while reader.read(mol):
        stats.read += 1;
        proc_mol = processMolecule(mol, stats)

        if proc_mol:
            writer.write(proc_mol)
        else:
            stats.dropped += 1
            dwriter.write(mol)
            print 'Dropped Molecule ' + Chem.generateSMILES(mol) + ' ' + Chem.getName(mol)

        mol.clear()
      
        if stats.read % 10000 == 0:
            print 'Processed ' + str(stats.read) + ' Molecules...'

    print ''
    print '-- Summary --'
    print 'Molecules processed: ' + str(stats.read)
    print 'Molecules dropped: ' + str(stats.dropped)
    print 'Molecules modified: ' + str(stats.modified)

if __name__ == '__main__':
    cleanStructures()
