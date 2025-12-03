##
# substruct_filter.py 
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


def filterMolecules() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the output of matching molecules (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # parse the substructure SMARTS pattern
    try:
        sub_srch_ptn = Chem.parseSMARTS(args.smarts_ptn)
    except Exception as e:
        sys.exit('Error: parsing of SMARTS pattern failed:\n%s' % str(e))

    # create and initialize an instance of the class Chem.SubstructureSearch that
    # implements the substructure searching algorithm
    substr_srch = Chem.SubstructureSearch(sub_srch_ptn)

    # special settings for option -m
    if args.mark_matched_atoms:
        # store only the first found substructure mapping
        substr_srch.setMaxNumMappings(1)
         # in case of SMILES output: write atom-atom mapping ids, if available
        Chem.setSMILESMolOutputAtomMappingIDParameter(writer, True)
    
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
                print('- Searching for a matching substructure in molecule %s...' % mol_id)

            try:
                Chem.initSubstructureSearchTarget(mol, False)

                if args.mark_matched_atoms:
                    found_match = substr_srch.findMappings(mol)  # for option -m atom-atom mapping data are required
                else:
                    found_match = substr_srch.mappingExists(mol) # if option -m is false, information that a mapping exists is sufficient
                    
                if found_match:
                    if not args.quiet:
                        print(' -> substructure found, forwarding molecule to output file')

                    # processing for option -m
                    if args.mark_matched_atoms:
                        for ap in substr_srch.getMapping(0).atomMapping.items(): # for each [ptn. atom, mol. atom] pair of the found substructure match
                            if Chem.hasAtomMappingID(ap[0]):                                 # if the pattern atom has an atom-atom mapping id
                                Chem.setAtomMappingID(ap[1], Chem.getAtomMappingID(ap[0]))   # set the id of the matched molecule atom to the same value
                        
                    # output the matched molecule
                    if not writer.write(mol):   
                        sys.exit('Error: output of molecule failed')

                elif not args.quiet: 
                    print(' -> substructure not found')
                        
            except Exception as e:
                sys.exit('Error: substructure search or output of molecule %s failed:\n%s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed:\n' + str(e))

    writer.close()
    sys.exit(0)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Writes input molecules that match the specified SMARTS substructure pattern to an output file.')

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
    parser.add_argument('-p',
                        dest='smarts_ptn',
                        required=True,
                        metavar='<SMARTS>',
                        help='SMARTS pattern describing the substructure to search for')
    parser.add_argument('-m',
                        dest='mark_matched_atoms',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Set atom mapping ids of output molecule atoms to the ids of the matching SMARTS pattern atoms (default: false)')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    return parser.parse_args()

if __name__ == '__main__':
    filterMolecules()
