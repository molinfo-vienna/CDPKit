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


import CDPL.Chem as Chem
import sys


class TautomerCB():

    def __init__(self, outfile):
        self.writer = Chem.FileSDFMolecularGraphWriter(outfile)
        Chem.setCoordinatesDimensionParameter(self.writer, 0)
        Chem.setMultiConfExportParameter(self.writer, False)
        self.count = 0

    def __call__(self, tautomer):
        Chem.perceiveHybridizationStates(tautomer, True);
        Chem.generateHydrogen3DCoordinates(tautomer, False);

        if not self.writer.write(tautomer):
            return False

        self.count += 1
        return True


def process():
    if len(sys.argv) < 3:
        print >> sys.stderr, 'Usage:', sys.argv[0], '[input.sdf] [output.sdf]'
        sys.exit(2)

    m = Chem.BasicMolecule()
    r = Chem.FileSDFMoleculeReader(sys.argv[1])
    Chem.setMultiConfImportParameter(r, False)

    tg = Chem.DefaultTautomerGenerator()
    tgcb = TautomerCB(sys.argv[2])
    
    tg.setMode(Chem.DefaultTautomerGenerator.TOPOLOGICALLY_UNIQUE) # depends on what you want to have!
    tg.setCallbackFunction(tgcb)
    i = 0

    while r.read(m):
        Chem.clearMDLDimensionality(m)

        print >> sys.stderr, '- Processing input molecule', i, '...'

        Chem.calcImplicitHydrogenCounts(m, False)
        Chem.makeHydrogenComplete(m)
        Chem.calcImplicitHydrogenCounts(m, True)
        Chem.setAtomSymbolsFromTypes(m, False)

        Chem.perceiveComponents(m, False)
        Chem.perceiveSSSR(m, False)

        Chem.perceiveHybridizationStates(m, False)
        Chem.setRingFlags(m, False)
        Chem.setAromaticityFlags(m, False)

        tg.generate(m)

        print >> sys.stderr, '   -> Generated', tgcb.count, 'tautomers'

        m.clear()
        tgcb.count = 0
        i += 1


if __name__ == '__main__':
    process()
