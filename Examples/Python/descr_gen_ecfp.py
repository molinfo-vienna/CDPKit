#!/bin/env python

##
# descr_gen_ecfp.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2022 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
import os
import argparse

import CDPL.Chem as Chem
import CDPL.Descr as Descr
import CDPL.Util as Util


# generate ECFP for read molecule
def genECFP(mol: Chem.Molecule, num_bits: int, radius: int, strip_hs: bool) -> Util.BitSet:
    if strip_hs:
        if Chem.makeHydrogenDeplete(mol):              # remove all presents hydrogen atoms
            Chem.calcImplicitHydrogenCounts(mol, True) # recalculate implicit hydrogen counts if hydrogens were removed
    else:
        Chem.calcImplicitHydrogenCounts(mol, False)    # calculate implicit hydrogen counts (if not yet done)
        Chem.makeHydrogenComplete(mol)                 # add explicit hydrogens to atoms having an implicit hydrogen count > 0

    Chem.perceiveHybridizationStates(mol, False)       # perceive atom hybridization and set corresponding property for all atoms
    Chem.setRingFlags(mol, False)                      # perceive cycles and set corresponding atom and bond properties
    Chem.perceiveSSSR(mol, False)                      # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setAromaticityFlags(mol, False)               # perceive aromaticity and set corresponding atom and bond properties
    
    ecfp_gen = Descr.CircularFingerprintGenerator()
    fp = Util.BitSet()

    ecfp_gen.setNumIterations(radius)
    ecfp_gen.setNumBits(num_bits)
    ecfp_gen.generate(mol, fp)

    return fp
    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Calculates extended connectivity fingerprints (ECFPs) for given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<input file>',
                        help='Input molecule file',
                        nargs=1)
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<output file>',
                        help='Fingerprint output file',
                        nargs=1)
    parser.add_argument('-n',
                        dest='num_bits',
                        required=False,
                        metavar='<num. bits>',
                        default=1024,
                        help='Fingerprint size in bits',
                        nargs=1,
                        type=int)
    parser.add_argument('-r',
                        dest='radius',
                        required=False,
                        metavar='<radius>',
                        default=2,
                        help='Max. atom environment radius in number of bonds',
                        nargs=1,
                        type=int)
    parser.add_argument('-s',
                        dest='strip_hs',
                        required=False,
                        action='store_true',
                        help='Strip hydrogens (by default, molecules will be hydrogen completed)')

    parse_args = parser.parse_args()

    return parse_args

def getReaderByFileExt(filename: str) -> Chem.MoleculeReader:
    # get the extension of the input file
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine input file format (file extension missing).')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Chem.MoleculeIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:
        sys.exit('Error: unknown input file format \'%s\'' % name_and_ext[1])

    # return file reader instance
    return ipt_handler.createReader(filename)
    
def main() -> None:
    args = parseArgs()
    
    # if input are expected to be in a specific format, a reader for the specific format could be create directly,
    # e.g. reader = Chem.FileSDFMoleculeReader(sys.argv[1])
    reader = getReaderByFileExt(args.in_file[0]) 

    # open output file storing the generated fingerprints
    out_file = open(args.out_file[0], 'w')
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        if reader.read(mol):
            try:
                fp = genECFP(mol, args.num_bits, args.radius, args.strip_hs)

                out_file.write(str(fp))
                out_file.write('\n')

            except Exception as e:
                sys.exit('Error: processing of molecule failed:\n' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed:\n' + str(e))

    out_file.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
