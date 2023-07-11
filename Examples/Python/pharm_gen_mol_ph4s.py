#!/bin/env python

##
# pharm_gen_mol_ph4s.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2022 Thomas Seidel <thomas.seidel@univie.ac.at>
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


# generates the pharmacophore of the argument molecule using
# atom coordinates of the specified conformation
def genPharmacophore(mol: Chem.Molecule, conf_idx: int) -> Pharm.Pharmacophore:
    if conf_idx < 1:                                    # for a new molecule
        Pharm.prepareForPharmacophoreGeneration(mol)    # first call utility function preparing the molecule for pharmacophore generation
        
    ph4_gen = Pharm.DefaultPharmacophoreGenerator()     # create an instance of the pharmacophore generator default implementation
    ph4 = Pharm.BasicPharmacophore()                    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4_name = Chem.getName(mol)                        # use the name of the input molecule as pharmacophore name
    
    if conf_idx >= 0:                                   # if mol is a multi-conf. molecule use atom 3D coordinates of the specified conf.
        ph4_gen.setAtom3DCoordinatesFunction(Chem.AtomConformer3DCoordinatesFunctor(conf_idx))
        ph4_name += '#' + str(conf_idx)                 # and append conformer index to the pharmacophore name
        
    ph4_gen.generate(mol, ph4)          # generate the pharmacophore
    Pharm.setName(ph4, ph4_name)        # set the pharmacophore name

    return ph4

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates pharmacophores of the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Pharmacophore output file')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    parse_args = parser.parse_args()

    return parse_args

# returns a Chem.MoleculeReader instance for the specified molecule input file format
def getMolReaderByFileExt(filename: str) -> Chem.MoleculeReader:
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine molecule input file format (file extension missing)')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Chem.MoleculeIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:
        sys.exit('Error: unsupported molecule input file format \'%s\'' % name_and_ext[1])

    # create and return file reader instance
    return ipt_handler.createReader(filename)

# returns a Pharm.FeatureContainerWriter instance for the specified pharmacophore output file format
def getPharmWriterByFileExt(filename: str) -> Pharm.FeatureContainerWriter:
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine pharmacophore output file format (file extension missing)')

    # get output handler for the format specified by the output file's extension
    opt_handler = Pharm.FeatureContainerIOManager.getOutputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not opt_handler:
        sys.exit('Error: unsupported pharmacophore output file format \'%s\'' % name_and_ext[1])

    # create and return file writer instance
    return opt_handler.createWriter(filename)

def main() -> None:
    args = parseArgs()
    
    # if the input molecules are expected to be in a specific format, a reader for this format could be created directly, e.g.
    # reader = Chem.FileSDFMoleculeReader(args.in_file)
    reader = getMolReaderByFileExt(args.in_file) 

    # if the output pharmacophores have to be stored in a specific format, a writer for this format could be created directly, e.g.
    # writer = Pharm.FilePMLFeatureContainerWriter(args.out_file)
    writer = getPharmWriterByFileExt(args.out_file) 
     
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    i = 1
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            if not args.quiet:
                print('- Generating pharmacophore of molecule %s...' % mol_id)

            num_confs = Chem.getNumConformations(mol)
            start_conf_idx = 0

            if num_confs == 0:         # test if molecule has conformations
                start_conf_idx = -1    # if not, make sure conformer loop body gets executed

            try:
                for conf_idx in range(start_conf_idx, num_confs):  # for each conformer
                    ph4 = genPharmacophore(mol, conf_idx)          # generate pharmacophore

                    if not args.quiet:
                        print(' -> Generated %s features: %s' % (str(ph4.numFeatures), Pharm.generateFeatureTypeHistogramString(ph4)))
                     
                    if not writer.write(ph4):   # output pharmacophore
                        sys.exit('Error: writing generated pharmacophore %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: pharmacophore generation or output for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
