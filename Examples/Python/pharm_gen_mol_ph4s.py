#!/bin/env python

##
# pharm_gen_mol_ph4s.py 
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
import CDPL.Pharm as Pharm


# generates the pharmacophore of a given molecule
def genPharmacophore(mol: Chem.Molecule) -> Pharm.Pharmacophore:
    Pharm.prepareForPharmacophoreGeneration(mol)       # call utility function preparing the molecule for pharmacophore generation
        
    ph4_gen = Pharm.DefaultPharmacophoreGenerator()    # create an instance of the pharmacophore generator default implementation
    ph4 = Pharm.BasicPharmacophore()                   # create an instance of the default implementation of the Pharm.Pharmacophore interface

    ph4_gen.generate(mol, ph4)                         # generate the pharmacophore

    Pharm.setName(ph4, Chem.getName(mol))              # set the pharmacophore's name to the name of the input molecule

    return ph4
    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates pharmacophores of the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<input file>',
                        help='Input molecule file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<output file>',
                        help='Pharmacophore output file')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
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

def getWriterByFileExt(filename: str) -> Pharm.FeatureContainerWriter:
    # get the extension of the output file
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine output file format (file extension missing).')

    # get output handler for the format specified by the output file's extension
    opt_handler = Pharm.FeatureContainerIOManager.getOutputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not opt_handler:
        sys.exit('Error: unknown output file format \'%s\'' % name_and_ext[1])

    # return file writer instance
    return opt_handler.createWriter(filename)
    
def main() -> None:
    args = parseArgs()
    
    # if the input molecules are expected to be in a specific format, a reader for this format could be created directly, e.g.
    # reader = Chem.FileSDFMoleculeReader(args.in_file)
    reader = getReaderByFileExt(args.in_file) 

    # if the output pharmacophores have to be stored in a specific format, a writer for this format could be created directly, e.g.
    # writer = Pharm.FilePMLFeatureContainerWriter(args.out_file)
    writer = getWriterByFileExt(args.out_file) 
     
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    i = 1
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            if not args.quiet:
                print('- Generating pharmacophore of molecule %s...' % mol_id)

            try:
                ph4 = genPharmacophore(mol) # generate pharmacophore
                
                if not writer.write(ph4):   # output pharmacophore
                    sys.exit('Error: writing generated pharmacophore %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: pharmacophore generation or output for molecule %s failed:\n%s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed:\n' + str(e))

    writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
