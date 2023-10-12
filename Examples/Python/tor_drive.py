#!/bin/env python

##
# tor_drive.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with
# or without fee is hereby granted.
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
# TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
# NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
##


import sys
import os
import argparse

import CDPL.Chem as Chem
import CDPL.ConfGen as ConfGen


# generates a conformer ensemble of the argument molecule by torsion driving
# using the provided ConfGen.TorsionDriver instance
def performTorsionDriving(mol: Chem.Molecule, conf_gen: ConfGen.TorsionDriver) -> (int, int):
    # prepare the molecule for conformer generation
    ConfGen.prepareForConformerGeneration(mol) 

    # generate the conformer ensemble
    status = conf_gen.generate(mol)             
    num_confs = conf_gen.getNumConformers()
    
    # if sucessful, store the generated conformer ensemble as
    # per atom 3D coordinates arrays (= the way conformers are represented in CDPKit)
    if status == ConfGen.ReturnCode.SUCCESS or status == ConfGen.ReturnCode.TOO_MUCH_SYMMETRY:
        conf_gen.setConformers(mol)                
    else:
        num_confs = 0
        
    # return status code and the number of generated conformers
    return (status, num_confs)

def main() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the generated conformer ensembles (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # create and initialize an instance of the class ConfGen.TorsionDriver which
    # will perform conformer generation by enumerating energetically favorable
    # torsion angle combinations
    tor_driver = ConfGen.TorsionDriver()

    tor_driver.settings.energyWindow = args.e_window            # apply the -e argument

    # dictionary mapping status codes to human readable strings
    status_to_str = { ConfGen.ReturnCode.UNINITIALIZED                  : 'uninitialized',
                      ConfGen.ReturnCode.FORCEFIELD_SETUP_FAILED        : 'force field setup failed',
                      ConfGen.ReturnCode.TORSION_DRIVING_FAILED         : 'torsion driving failed' }
    
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
                print('- Generating conformers for molecule %s...' % mol_id)

            try:
                # generate conformer ensemble for read molecule
                status, num_confs = genConfEnsemble(mol, conf_gen) 

                # check for severe error reported by status code
                if status != ConfGen.ReturnCode.SUCCESS and status != ConfGen.ReturnCode.TOO_MUCH_SYMMETRY:
                    if args.quiet:
                        print('Error: torsion driving on molecule %s failed: %s' % (mol_id, status_to_str[status]))
                    else:
                        print(' -> Torsion driving failed: %s' % status_to_str[status])

                elif not args.quiet:  # arrives here only if no severe error occurred
                    print(' -> Generated %s conformers' % str(num_confs))
                        
                # output generated ensemble (if available)
                if num_confs > 0:
                    if not writer.write(mol):   
                        sys.exit('Error: output of conformer ensemble for molecule %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: torsion driving or output of conformers for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates conformer ensembles for the given input molecules by performing torsion driving on the provided 3D structure.')

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
    parser.add_argument('-e',
                        dest='e_window',
                        required=False,
                        metavar='<float>',
                        type=float,
                        default=20.0,
                        help='Output conformer energy window (default: 20.0)')
    parser.add_argument('-n',
                        dest='max_confs',
                        required=False,
                        metavar='<int>',
                        type=int,
                        help='Max. output ensemble size (default: 100)')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    return parser.parse_args()

if __name__ == '__main__':
    main()
