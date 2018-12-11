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


REMOVE_FLUORINATED = True
FLUOR_ATOM_COUNT = 9
MIN_HEAVY_ATOM_COUNT = 5
VALID_ATOM_TYPES = [Chem.AtomType.H, Chem.AtomType.C, Chem.AtomType.F, Chem.AtomType.Cl, Chem.AtomType.Br, Chem.AtomType.I, Chem.AtomType.N, Chem.AtomType.O, Chem.AtomType.S, Chem.AtomType.Se, Chem.AtomType.P, Chem.AtomType.Pt, Chem.AtomType.As, Chem.AtomType.Si]    
CARBON_ATOMS_MANDATORY = True
NEUTRALIZE = True
KEEP_ONLY_LARGEST_COMP = True


class Stats:
    pass

def generateSMILES(mol):
    try:
        return Chem.generateSMILES(mol)
    except:
        return ''

def processMolecule(mol, stats):
    Chem.perceiveComponents(mol, False)
    Chem.perceiveSSSR(mol, False)
    Chem.setRingFlags(mol, False)
    Chem.calcImplicitHydrogenCounts(mol, False)
    Chem.perceiveHybridizationStates(mol, False)
    Chem.setAromaticityFlags(mol, False)

    modified = False
    comps = Chem.getComponents(mol)

    if comps.getSize() > 1 and KEEP_ONLY_LARGEST_COMP:
        largest_comp = None

        for comp in comps:
            if largest_comp is None:
                largest_comp = comp
            elif comp.getNumAtoms() > largest_comp.getNumAtoms():
                largest_comp = comp

        Chem.perceiveComponents(largest_comp, False)
        Chem.perceiveSSSR(largest_comp, False)
        Chem.setName(largest_comp, Chem.getName(mol))

        print 'Removed Components from Molecule ' + str(stats.read) + ': ' + generateSMILES(mol) + ' ' + Chem.getName(mol)

        modified = True

        if Chem.hasName(mol):
            Chem.setName(largest_comp, Chem.getName(mol))

        if Chem.hasStructureData(mol):
            Chem.setStructureData(largest_comp, Chem.getStructureData(mol))

        mol = largest_comp

    if Chem.getHeavyAtomCount(mol) < MIN_HEAVY_ATOM_COUNT:
        return None

    if REMOVE_FLUORINATED and Chem.getAtomCount(mol, Chem.AtomType.F) > FLUOR_ATOM_COUNT:
        return None

    carbon_seen = False
    hs_to_remove = list()

    for atom in mol.atoms:
        atom_type = Chem.getType(atom)
        invalid_type = True

        for valid_type in VALID_ATOM_TYPES:
            if Chem.atomTypesMatch(valid_type, atom_type):
                invalid_type = False
                break

        if invalid_type:
            return None

        if atom_type == Chem.AtomType.C:
            carbon_seen = True

        if NEUTRALIZE:
            form_charge = Chem.getFormalCharge(atom)

            if form_charge != 0:
                for nbr_atom in atom.atoms:
                    if Chem.getFormalCharge(nbr_atom) != 0:
                        form_charge = 0
                        break

            if form_charge != 0:
                if form_charge > 0:
                    form_charge -= Chem.getImplicitHydrogenCount(atom)

                    if form_charge < 0:
                        form_charge = 0

                    for nbr_atom in atom.atoms: 
                        if form_charge == 0:
                            break

                        if Chem.getType(nbr_atom) == Chem.AtomType.H:
                            hs_to_remove.append(nbr_atom)
                            form_charge -= 1
                        
                    Chem.setFormalCharge(atom, form_charge)

                else:
                    Chem.setFormalCharge(atom, 0)
                            
                modified = True
    
    if CARBON_ATOMS_MANDATORY and carbon_seen == False:
        return None

    if len(hs_to_remove) > 0:
        for atom in hs_to_remove:
            mol.removeAtom(mol.getAtomIndex(atom))
 
        for atom in mol.atoms:
            Chem.setImplicitHydrogenCount(atom, Chem.calcImplicitHydrogenCount(atom, mol))
            Chem.setHybridizationState(atom, Chem.perceiveHybridizationState(atom, mol))

    if modified:
        stats.modified += 1

    return mol

def cleanStructures():
    if len(sys.argv) < 5:
        print >> sys.stderr, 'Usage:', sys.argv[0], '[input.sdf] [output.sdf] [dropped.sdf] [start_index] [[count]]'
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
            print 'Dropped Molecule ' + str(stats.read) + ': ' + generateSMILES(mol) + ' ' + Chem.getName(mol)
       
        stats.read += 1

        if stats.read % 10000 == 0:
            print 'Processed ' + str(stats.read - offset) + ' Molecules...'

        if count > 0 and (stats.read - offset) >= count:
            break

    print ''
    print '-- Summary --'
    print 'Molecules processed: ' + str(stats.read - offset)
    print 'Molecules dropped: ' + str(stats.dropped)
    print 'Molecules modified: ' + str(stats.modified)

if __name__ == '__main__':
    cleanStructures()
