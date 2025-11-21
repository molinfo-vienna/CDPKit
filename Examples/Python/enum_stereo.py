##
# enum_stereo.py 
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


# enumerates and outputs stereoisomers of the argument molecule using
# the provided initialized Chem.StereoisomerGenerator instance
def enumStereoisomers(mol: Chem.Molecule, iso_gen: Chem.StereoisomerGenerator, mol_id: str,
                      writer: Chem.MolecularGraphWriter, args: argparse.Namespace) -> int:

    # compute required atom, bond and molecule properties
    Chem.calcBasicProperties(mol, False)
    Chem.perceiveAtomStereoCenters(mol, False, False, not args.inc_inv_n, not args.inc_inv_n)
    Chem.perceiveBondStereoCenters(mol, False, False, True, True, min(8, args.min_ring_size))
    Chem.calcAtomStereoDescriptors(mol, False, 0)
    Chem.calcBondStereoDescriptors(mol, False, 0)
    Chem.calcCIPPriorities(mol, False)
    Chem.perceiveComponents(mol, False)
    Chem.setAtomSymbolsFromTypes(mol, False)

    # setup stereoisomer enumeration for the given molecule
    iso_gen.setup(mol)

    num_gen_iso = 0

    # save original molecule name
    mol_name = Chem.getName(mol) 

    # enumerate all stereoisomers until done
    while args.max_num_iso == 0 or num_gen_iso < args.max_num_iso:
        # apply stereoisomer atom config. descriptors
        for i in range(mol.numAtoms):
            Chem.setStereoDescriptor(mol.atoms[i], iso_gen.atomDescriptors[i])

        # apply stereoisomer bond config. descriptors
        for i in range(mol.numBonds):
            Chem.setStereoDescriptor(mol.bonds[i], iso_gen.bondDescriptors[i])

        num_gen_iso += 1

        # append stereoisomer number suffix to molecule name
        Chem.setName(mol, f'{mol_name}_{num_gen_iso}')

        # write stereoisomer to output file
        if not writer.write(mol):   
            sys.exit(f'Error: output of generated stereoisomer #{num_gen_iso} of molecule {mol_id} failed')

        # generate next stereoisomer (if available)
        if not iso_gen.generate():
            break

    return num_gen_iso
                        
def parseArgs() -> argparse.Namespace:
    def strtobool(value: str) -> bool:
        value = value.lower()
        
        if value in ('y', 'yes', 'on', '1', 'true', 't'):
            return True
        
        return False

    parser = argparse.ArgumentParser(description='Enumerates stereoisomers of the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Stereoisomer output file')
    parser.add_argument('-m',
                        dest='max_num_iso',
                        required=False,
                        metavar='<int>',
                        type=int,
                        default=0,
                        help='Maximum number of output stereoisomers per molecule (default: 0, must be >= 0, 0 disables limit)')
    parser.add_argument('-a',
                        dest='enum_atom_cfg',
                        required=False,
                        metavar='<true|false>',
                        type=lambda x:bool(strtobool(x)),
                        default=True,
                        help='Enumerate configurations of atom stereocenters (default: true)')
    parser.add_argument('-b',
                        dest='enum_bond_cfg',
                        required=False,
                        metavar='<true|false>',
                        type=lambda x:bool(strtobool(x)),
                        default=True,
                        help='Enumerate configurations of bond stereocenters (default: true)')
    parser.add_argument('-s',
                        dest='inc_spec_ctrs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include specified atom/bond stereocenters (default: false)')
    parser.add_argument('-x',
                        dest='inc_sym_ctrs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include atom/bond stereocenters with topological symmetry (default: false)')
    parser.add_argument('-n',
                        dest='inc_inv_n',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include invertible nitrogen stereocenters (default: false)')
    parser.add_argument('-g',
                        dest='inc_bh_atoms',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include bridgehead atom stereocenters (default: false)')
    parser.add_argument('-r',
                        dest='inc_ring_bonds',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include ring bond stereocenters (default: false)')
    parser.add_argument('-R',
                        dest='min_ring_size',
                        required=False,
                        metavar='<int>',
                        type=int,
                        default=8,
                        help='Minimum size of rings below which the configuration of member bonds shall not be\
                              altered (only effective if option -r is true; default: 8)')
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

    # create writer for the generated stereoisomers (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # create and initialize an instance of the class Chem.StereoisomerGenerator which
    # will perform the actual stereoisomer enumeration work
    iso_gen = Chem.StereoisomerGenerator()

    iso_gen.enumAtomConfig = args.enum_atom_cfg      # apply option -a
    iso_gen.enumBondConfig = args.enum_atom_cfg      # apply option -b
    iso_gen.incSpecifiedCenters = args.inc_spec_ctrs # apply option -s
    iso_gen.incSymmetricCenters = args.inc_sym_ctrs  # apply option -x
    iso_gen.incBridgeheadAtoms = args.inc_bh_atoms   # apply option -g
    iso_gen.incInvertibleNitrogens = args.inc_inv_n  # apply option -n
    iso_gen.incRingBonds = args.inc_ring_bonds       # apply option -r
    iso_gen.minRingSize = args.min_ring_size         # apply option -R
    
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
                print(f'- Enumerating stereoisomers for molecule {mol_id}...')

            try:
                # enumerate and output stereoisomers of the read molecule
                num_gen = enumStereoisomers(mol, iso_gen, mol_id, writer, args) 

                if not args.quiet:  # arrives here only if no severe error occurred
                    print(f' -> Generated {num_gen} isomer(s)')
                        
            except Exception as e:
                sys.exit(f'Error: enumerating stereoisomers of molecule {mol_id} failed:\n' + str(e))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed:\n' + str(e))

    writer.close()
    sys.exit(0)

if __name__ == '__main__':
    main()
