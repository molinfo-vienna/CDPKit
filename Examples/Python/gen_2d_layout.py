##
# gen_2d_layout.py 
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
import CDPL.Math as Math
import CDPL.Util as Util


# computes a 2D structure layout of the argument molecule using the provided
# Chem.Atom2DCoordinatesCalculator and Chem.BondStereoFlagCalculator instances
def gen2DLayout(mol: Chem.Molecule, coords_calc: Chem.Atom2DCoordinatesCalculator, bs_flags_calc: Chem.BondStereoFlagCalculator, args: argparse.Namespace) -> None:
    # calculate several properties required for 2D structure layout
    Chem.calcBasicProperties(mol, False) 
    Chem.calcCIPPriorities(mol, False)
    Chem.perceiveAtomStereoCenters(mol, False, True)
    Chem.perceiveBondStereoCenters(mol, False, True)
    Chem.calcAtomStereoDescriptors(mol, False)
    Chem.calcBondStereoDescriptors(mol, False)

    changes = False
    
    if args.rem_h:   # remove ordinary (with standard form. charge, isotope, connectivity) hydrogens, if desired
        changes = Chem.makeOrdinaryHydrogenDeplete(mol, Chem.AtomPropertyFlag.ISOTOPE | Chem.AtomPropertyFlag.FORMAL_CHARGE | Chem.AtomPropertyFlag.EXPLICIT_BOND_COUNT, True)
    elif args.add_h: # make hydrogen complete, if desired
        changes = Chem.makeHydrogenComplete(mol)

    if changes:      # if expl. hydrogen count has changed -> recompute dependent properties
        Chem.perceiveComponents(mol, True)
        Chem.calcTopologicalDistanceMatrix(mol, True)
        Chem.calcAtomStereoDescriptors(mol, True, 0, False)
        Chem.calcBondStereoDescriptors(mol, True, 0, False)
    else:
        Chem.calcTopologicalDistanceMatrix(mol, False)

    coords = Math.Vector2DArray() # will store the computed 2D coordinates
    bs_flags = Util.UIArray()     # will store the computed bond stereo flags (up, down) specifying atom (and bond) configurations

    # calculate 2D coordinates
    coords_calc.calculate(mol, coords)

    # store calculated 2D coordinates as corr. atom properties
    Chem.set2DCoordinates(mol, coords)

    # calculate bond stereo flags for the given 2D coordinates
    bs_flags_calc.calculate(mol, bs_flags)

    # store bond stereo flags as corr. bond properties 
    for i in range(mol.numBonds):
        Chem.set2DStereoFlag(mol.getBond(i), bs_flags[i])
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Performs a 2D structure layout for the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Laid out molecule output file')
    parser.add_argument('-d',
                        dest='rem_h',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Remove ordinary explicit hydrogens (default: false)')
    parser.add_argument('-c',
                        dest='add_h',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Saturate free valences with explicit hydrogens (default: false)')
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

    # create writer for the generated 3D structures (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 
 
    # create and initialize an instance of the class Chem.Atom2DCoordinatesCalculator which will
    # perform the 2D coordinates calculation
    coords_calc = Chem.Atom2DCoordinatesCalculator()

    # create and initialize an instance of the class Chem.BondStereoFlagsCalculator which will
    # perform the calculation 2D bond stereo flags (= up, down, ...)
    bs_flags_calc = Chem.BondStereoFlagCalculator()
    
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
                mol_id = f'\'{mol_id}\' (#{i})'

            if not args.quiet:
                print(f'- Computing 2D layout of molecule {mol_id}...')

            try:
                # generate a 2D structure layout of the read molecule
                gen2DLayout(mol, coords_calc, bs_flags_calc, args) 

                # enforce the output of 2D coordinates in case of MDL file formats
                Chem.setMDLDimensionality(mol, 2)

                # output the laid out molecule
                if not writer.write(mol):   
                    sys.exit(f'Error: writing molecule {mol_id} failed')
                        
            except Exception as e:
                sys.exit(f'Error: 2D structure layout generation or output for molecule {mol_id} failed: {str(e)}')

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading molecule failed: {str(e)}')

    writer.close()
    sys.exit(0)

if __name__ == '__main__':
    main()
