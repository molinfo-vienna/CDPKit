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

        print 'Removed Components from Molecule ' + str(stats.read) + ': ' + Chem.generateSMILES(mol) + ' ' + Chem.getName(mol)

        modified = True

        if Chem.hasName(mol):
            Chem.setName(largest_comp, Chem.getName(mol))

        if Chem.hasMDLStructureData(mol):
            Chem.setMDLStructureData(largest_comp, Chem.getMDLStructureData(mol))

        mol = largest_comp

    if Chem.getHeavyAtomCount(mol) < 5:
        return None

    if Chem.getAtomCount(mol, Chem.AtomType.F) > 9:
        return None

    valid_atom_types = [Chem.AtomType.H, Chem.AtomType.C, Chem.AtomType.F, Chem.AtomType.Cl, Chem.AtomType.Br, Chem.AtomType.I, Chem.AtomType.N, Chem.AtomType.O, Chem.AtomType.S, Chem.AtomType.Se, Chem.AtomType.P, Chem.AtomType.Pt, Chem.AtomType.As]    

    carbon_seen = False

    for atom in mol.atoms:
        atom_type = Chem.getType(atom)

        if atom_type not in valid_atom_types:
            #print 'Invalid atom type: ' + str(Chem.getType(atom))
            return None

        if atom_type == Chem.AtomType.C:
            carbon_seen = True

        if atom_type == Chem.AtomType.C and Chem.getFormalCharge(atom) != 0:
            Chem.setFormalCharge(atom, 0)
            Chem.setImplicitHydrogenCount(atom, Chem.calcImplicitHydrogenCount(atom, mol))
            Chem.setHybridizationState(atom, Chem.perceiveHybridizationState(atom, mol))
            modified = True

    if carbon_seen == False:
        return None

    if modified:
        stats.modified += 1

    return mol

def cleanStructures():
    if len(sys.argv) < 5:
        print >> sys.stderr, 'Usage:', sys.argv[0], 'input.sdf output.sdf dropped.sdf start_index [count]'
        sys.exit(2)

    ifs = Base.FileIOStream(sys.argv[1], 'r')
    ofs = Base.FileIOStream(sys.argv[2], 'w')
    dofs = Base.FileIOStream(sys.argv[3], 'w')
    offset = int(sys.argv[4])
    count = 0

    if len(sys.argv) > 5:
        count = int(sys.argv[5])

    reader = Chem.SDFMoleculeReader(ifs)
    writer = Chem.SDFMolecularGraphWriter(ofs)
    dwriter = Chem.SDFMolecularGraphWriter(dofs)
    mol = Chem.BasicMolecule()
    
    #Chem.setSMILESRecordFormatParameter(reader, 'S:N$')
    #Chem.setSMILESRecordFormatParameter(writer, 'S:N$')
    #Chem.setSMILESRecordFormatParameter(dwriter, 'S:N$')

    stats = Stats()
    stats.read = 0
    stats.dropped = 0
    stats.modified = 0

    Chem.setMultiConfImportParameter(reader, False)
    Chem.setMultiConfExportParameter(writer, False)
    Chem.setMultiConfExportParameter(dwriter, False)

    print 'Skipping Molecules to Start Index ' + str(offset)
    reader.setRecordIndex(offset)

    stats.read = offset
    #print 'Finished Setting Record Index'
    
    while reader.read(mol):
        #print 'Processing Molecule ' + str(stats.read)
        proc_mol = processMolecule(mol, stats)

        if proc_mol:
            writer.write(proc_mol)
        else:
            stats.dropped += 1
            dwriter.write(mol)
            print 'Dropped Molecule ' + str(stats.read) + ': ' + Chem.generateSMILES(mol) + ' ' + Chem.getName(mol)

        mol.clear()
      
        stats.read += 1;

        if stats.read % 10000 == 0:
            print 'Processed ' + str(stats.read) + ' Molecules...'

        if count > 0 and stats.read - offset >= count:
            break

    print ''
    print '-- Summary --'
    print 'Molecules processed: ' + str(stats.read)
    print 'Molecules dropped: ' + str(stats.dropped)
    print 'Molecules modified: ' + str(stats.modified)

if __name__ == '__main__':
    cleanStructures()
