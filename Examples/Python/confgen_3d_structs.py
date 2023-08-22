#!/bin/env python

##
# confgen_3d_structs.py 
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


import sys
import os
import argparse

import CDPL.Chem as Chem
import CDPL.ConfGen as ConfGen


# generates a low-energy 3D structure of the argument molecule using
# the provided initialized ConfGen.StructureGenerator instance
def gen3DStructure(mol: Chem.Molecule, struct_gen: ConfGen.StructureGenerator) -> int:
    # prepare the molecule for 3D structure generation
    ConfGen.prepareForConformerGeneration(mol) 

    # generate the 3D structure
    status = struct_gen.generate(mol)             
    
    # if sucessful, store the generated conformer ensemble as
    # per atom 3D coordinates arrays (= the way conformers are represented in CDPKit)
    if status == ConfGen.ReturnCode.SUCCESS:
        struct_gen.setCoordinates(mol)                
        
    # return status code
    return status

def main() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the generated 3D structures (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # export only a single 3D structure (in case of multi-conf. input molecules)
    Chem.setMultiConfExportParameter(writer, False)
    
    # create and initialize an instance of the ConfGen.StructureGenerator class which will perform
    # the actual 3D structure generation work
    struct_gen = ConfGen.StructureGenerator()

    struct_gen.settings.timeout = args.max_time * 1000

    # dictionary mapping status codes to human readable strings
    status_to_str = { ConfGen.ReturnCode.UNINITIALIZED                  : 'uninitialized',
                      ConfGen.ReturnCode.TIMEOUT                        : 'max. processing time exceeded',
                      ConfGen.ReturnCode.ABORTED                        : 'aborted',
                      ConfGen.ReturnCode.FORCEFIELD_SETUP_FAILED        : 'force field setup failed',
                      ConfGen.ReturnCode.FORCEFIELD_MINIMIZATION_FAILED : 'force field structure refinement failed',
                      ConfGen.ReturnCode.FRAGMENT_LIBRARY_NOT_SET       : 'fragment library not available',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_FAILED       : 'fragment conformer generation failed',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_TIMEOUT      : 'fragment conformer generation timeout',
                      ConfGen.ReturnCode.FRAGMENT_ALREADY_PROCESSED     : 'fragment already processed',
                      ConfGen.ReturnCode.TORSION_DRIVING_FAILED         : 'torsion driving failed',
                      ConfGen.ReturnCode.CONF_GEN_FAILED                : 'conformer generation failed' }
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    i = 1
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i) # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            if not args.quiet:
                print('- Generating 3D structure of molecule %s...' % mol_id)

            try:
                # generate 3D structure of the read molecule
                status = gen3DStructure(mol, struct_gen) 

                # check for severe error reported by status code
                if status != ConfGen.ReturnCode.SUCCESS:
                    if args.quiet:
                        print('Error: 3D structure generation for molecule %s failed: %s' % (mol_id, status_to_str[status]))
                    else:
                        print(' -> 3D structure generation failed: %s' % status_to_str[status])
                else: 
                    # enforce the output of 3D coordinates in case of MDL file formats
                    Chem.setMDLDimensionality(mol, 3)

                    # output the generated 3D structure                    
                    if not writer.write(mol):   
                        sys.exit('Error: writing 3D structure of molecule %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: 3D structure generation or output for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates conformer ensembles for the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Conformer ensemble output file')
    parser.add_argument('-t',
                        dest='max_time',
                        required=False,
                        metavar='<int>',
                        type=int,
                        default=3600,
                        help='Max. allowed molecule processing time (default: 3600 sec)')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    return parser.parse_args()

if __name__ == '__main__':
    main()
