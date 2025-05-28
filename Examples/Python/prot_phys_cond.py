##
# prot_phys_cond.py 
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
import argparse

import CDPL.Chem as Chem


def processMolecules() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the output of matching molecules (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # create and initialize an instance of the class Chem.ProtonationStateStandardizer which
    # implements the protonation state generation algorithm
    prot_state_gen = Chem.ProtonationStateStandardizer()
    
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
                print('- Processing molecule %s...' % mol_id)

            try:
                # protonate/deprotonate functional groups for phys. conditions
                prot_state_gen.standardize(mol, Chem.ProtonationStateStandardizer.PHYSIOLOGICAL_CONDITION_STATE)

                # enforce an update of the molecule components list (structure might have changed)
                Chem.perceiveComponents(mol, True)
                
                # output the processed input molecule                 
                if not writer.write(mol):   
                    sys.exit('Error: output of molecule failed')
                        
            except Exception as e:
                sys.exit('Error: processing or output of molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates likely protonation states at phys. conditions for a set of\
                                                  given input molecules and then writes the resulting structures to the\
                                                  specified output file.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule output file')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    return parser.parse_args()

if __name__ == '__main__':
    processMolecules()
