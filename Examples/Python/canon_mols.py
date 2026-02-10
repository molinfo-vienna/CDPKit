##
# canon_mols.py 
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


# calcutates a canonical atom numbering for the provided molecular graph and
# then reorders the atoms and bond according to the calculated numbering
def canonicalize(mol: Chem.MolecularGraph, ignore_stereo: bool) -> None:
    # calculate required basic atom and bond properties
    Chem.calcBasicProperties(mol, False)

    # if necessary, do some atom/bond stereochemistry related setup work
    if not ignore_stereo:
        Chem.calcCIPPriorities(mol, False)
        Chem.perceiveAtomStereoCenters(mol, False, True)
        Chem.perceiveBondStereoCenters(mol, False, True)
        Chem.calcAtomStereoDescriptors(mol, False)
        Chem.calcBondStereoDescriptors(mol, False)

    # flags specifying the default set of atom properties considered by the canonicalization algo. implementation
    atom_flags = Chem.CanonicalNumberingCalculator.DEF_ATOM_PROPERTY_FLAGS

    # flags specifying the default set of bond properties considered by the canonicalization algo. implementation
    bond_flags = Chem.CanonicalNumberingCalculator.DEF_BOND_PROPERTY_FLAGS

    # if stereochemistry is not considered then clear the corresponding property flags
    if ignore_stereo:
        atom_flags ^= Chem.AtomPropertyFlag.CONFIGURATION
        bond_flags ^= Chem.BondPropertyFlag.CONFIGURATION

    # calculate canonical atom numbers (numbers will be stored as atom property Chem.AtomProperty.CANONICAL_NUMBER)
    Chem.calcCanonicalNumbering(mol, True, atom_flags, bond_flags)

    # reorder all internal atom and bond lists according to the calculated canonical atom numbering
    Chem.canonicalize(mol, True, True, True)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Canonicalized the atom and bond order of the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Canonicalized molecule output file')
    parser.add_argument('-x',
                        dest='ignore_stereo',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Ignore atom and bond stereochemistry (default: false)')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
      
    return parser.parse_args()

def main() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the canonicalized molecules (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 
 
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    i = 1
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = f'#{i}' # fallback if name is empty
            else:
                mol_id = f'\'{mol_id}\' (#{i})'

            if not args.quiet:
                print(f'- Canonicalizing molecule {mol_id}...')

            try:
                canonicalize(mol, args.ignore_stereo)

                # output the laid out molecule
                if not writer.write(mol):   
                    sys.exit(f'Error: writing molecule {mol_id} failed')
                        
            except Exception as e:
                sys.exit(f'Error: Canonicalization or output of molecule {mol_id} failed:\n{str(e)}')

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading molecule failed:\n{str(e)}')

    writer.close()
    sys.exit(0)

if __name__ == '__main__':
    main()
