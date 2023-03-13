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
def genECFP(mol: Chem.Molecule, num_bits: int, radius: int, inc_hs: bool, inc_config: bool) -> Util.BitSet:
    Chem.calcImplicitHydrogenCounts(mol, False)        # calculate implicit hydrogen counts (if not yet done)
    Chem.perceiveHybridizationStates(mol, False)       # perceive atom hybridization states and set corresponding property for all atoms
    Chem.setRingFlags(mol, False)                      # perceive cycles and set corresponding atom and bond properties
    Chem.perceiveSSSR(mol, False)                      # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setAromaticityFlags(mol, False)               # perceive aromaticity and set corresponding atom and bond properties
    
    ecfp_gen = Descr.CircularFingerprintGenerator()    # create ECFP generator instance

    if inc_config:
        ecfp_gen.includeChirality(True)                # allow atom chirality to have an impact on the ECFP generation
        Chem.calcAtomStereoDescriptors(mol, False)     # calculate atom stereo descriptors and set corresponding property for all atoms

    if inc_hs:        
        ecfp_gen.includeHydrogens(True)                # include explicit hydrogens in the ECFP generation
        Chem.makeHydrogenComplete(mol)                 # make any implicit hydrogens explicit
         
    fp = Util.BitSet()                                 # create fingerprint bitset
    fp.resize(num_bits)                                # set desired fingerprint size

    ecfp_gen.setNumIterations(radius)                  # set num. iterations (=atom. env. radius)
    ecfp_gen.generate(mol)                             # extract chracteristic structural features
    ecfp_gen.setFeatureBits(fp)                        # set bits associated with the extracted structural features

    # if needed, fp could be converted into a numpy single precision float array as follows:
    # fp = numpy.array(fp, dtype=numpy.float32)
    
    return fp
    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Calculates extended connectivity fingerprints (ECFPs) for given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Input molecule file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='ECFP fingerprint output file')
    parser.add_argument('-n',
                        dest='num_bits',
                        required=False,
                        metavar='<num. bits>',
                        default=1024,
                        help='Fingerprint size in bits (default: 1024)',
                        type=int)
    parser.add_argument('-r',
                        dest='radius',
                        required=False,
                        metavar='<value>',
                        default=2,
                        help='Max. atom environment radius in number of bonds (default: 2)',
                        type=int)
    parser.add_argument('-y',
                        dest='inc_hs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Do not ignore hydrogens (by default, the fingerprint is generated for the H-deplete molecular graph)')
    parser.add_argument('-c',
                        dest='inc_config',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include atom chirality (by default, atom chirality is not considered)')

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
    
    # if the input molecules are expected to be in a specific format, a reader for this format could be created directly, e.g.
    # reader = Chem.FileSDFMoleculeReader(args.in_file)
    reader = getReaderByFileExt(args.in_file) 

    # open output file storing the generated fingerprints
    out_file = open(args.out_file, 'w')
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()

    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            try:
                fp = genECFP(mol, args.num_bits, args.radius, args.inc_hs, args.inc_config)

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
