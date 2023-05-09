# -*- mode: python; tab-width: 4 -*- 

## 
# RemoveStructures.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


from __future__ import print_function 

import sys

import CDPL.Base as Base
import CDPL.Chem as Chem


class Stats:
    pass

def setupMolecule(mol):
    Chem.perceiveComponents(mol, False)
    Chem.perceiveSSSR(mol, False)
    Chem.setRingFlags(mol, False)
    Chem.calcImplicitHydrogenCounts(mol, False)
    Chem.perceiveHybridizationStates(mol, False)
    Chem.setAromaticityFlags(mol, False)
    Chem.calcCIPPriorities(mol, False)
    Chem.calcAtomCIPConfigurations(mol, False)
    Chem.calcBondCIPConfigurations(mol, False)

def process():
    if len(sys.argv) < 4:
        print('Usage:', sys.argv[0], '[input.sdf] [exclude-molecules.sdf] [output.sdf]', file=sys.stderr)
        sys.exit(2)

    ifs = Base.FileIOStream(sys.argv[1], 'r')
    xifs = Base.FileIOStream(sys.argv[2], 'r')
    ofs = Base.FileIOStream(sys.argv[3], 'w')

    reader = Chem.SDFMoleculeReader(ifs)
    xreader = Chem.SDFMoleculeReader(xifs)
    writer = Chem.SDFMolecularGraphWriter(ofs)
    mol = Chem.BasicMolecule()
   
    Chem.setMultiConfImportParameter(reader, False)
    Chem.setMultiConfImportParameter(xreader, False)
    Chem.setMultiConfExportParameter(writer, False)

    stats = Stats()
    stats.read = 0
    stats.dropped = 0

    xhashes = set()

    while xreader.read(mol):
        setupMolecule(mol)

        hashcode = Chem.calcHashCode(mol)
        xhashes.add(hashcode)

    while reader.read(mol):
        #print('Processing Molecule ' + str(stats.read)
        setupMolecule(mol)

        hashcode = Chem.calcHashCode(mol)

        if hashcode in xhashes:
            stats.dropped += 1
            print('Dropped Molecule ' + str(stats.read) + ': ' + Chem.generateSMILES(mol) + ' ' + Chem.getName(mol), file=sys.stderr)
        else:
            writer.write(mol)

        stats.read += 1

        if stats.read % 10000 == 0:
            print('Processed ' + str(stats.read) + ' Molecules...', file=sys.stderr)

    print('', file=sys.stderr)
    print('-- Summary --', file=sys.stderr)
    print('Molecules processed: ' + str(stats.read), file=sys.stderr)
    print('Molecules dropped: ' + str(stats.dropped), file=sys.stderr)

if __name__ == '__main__':
    process()
