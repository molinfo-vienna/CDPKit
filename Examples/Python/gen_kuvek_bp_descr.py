##
# gen_kuvek_bp_descr.py 
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
import re

import CDPL.Chem as Chem
import CDPL.Biomol as Biomol
import CDPL.ForceField as ForceField
import CDPL.Descr as Descr
import CDPL.Math as Math


# reads and preprocesses the specified receptor structure
def readAndPrepareReceptorStructure(args: argparse.Namespace) -> Chem.Molecule:
    sup_fmts = [ Chem.DataFormat.MOL2,
                 Biomol.DataFormat.PDB,
                 Biomol.DataFormat.MMTF,
                 Biomol.DataFormat.MMCIF ]

    # create reader for receptor structure (format specified by file extension)
    reader = Chem.MoleculeReader(args.receptor_file) 
                           
    if reader.getDataFormat() not in sup_fmts:   # check if the format is supported by this script
        sys.exit('Error: receptor input file format not supported')
    
    rec_mol = Chem.BasicMolecule()    # create an instance of the default implementation of the
                                      # Chem.Molecule interface that will store the receptor struct.
    try:
        if not reader.read(rec_mol):  # read receptor structure
            sys.exit('Error: reading receptor structure failed')

    except Exception as e:
        sys.exit(f'Error: reading receptor structure failed:\n{str(e)}')            

    # preprocess the receptor structure (removal of residues and
    # calculation of properties required by the pharm. generation procedure)
    try:
        rem_atoms = False

        # delete atoms belonging to residues that should be stripped
        if args.strip_res_list:            
            atoms_to_rem = Chem.Fragment() # will store the atoms to delete
            res_to_strip_ptns = { re.compile(tlc, re.IGNORECASE) for tlc in args.strip_res_list }

            # identify and note atoms belonging to the stripped residues
            for atom in rec_mol.atoms:
                # compose identifier of the residue the atom belongs to
                atom_res_id = f'{Biomol.getChainID(atom).upper()}_{Biomol.getResidueCode(atom).upper()}_{Biomol.getResidueSequenceNumber(atom)}'

                # check if atom belongs to an excluded residue
                for res_ptn in res_to_strip_ptns:
                    if res_ptn.search(atom_res_id):
                        atoms_to_rem.addAtom(atom)
                        break

            if atoms_to_rem.numAtoms > 0:
                rec_mol -= atoms_to_rem    # delete atoms from the receptor structure
                rem_atoms = True

                if not args.quiet:
                    print(f'! Removed {atoms_to_rem.numAtoms} atom(s) from the receptor structure')

        # calc required receptor structure properties
        Chem.perceiveSSSR(rec_mol, rem_atoms)
        Chem.setRingFlags(rec_mol, rem_atoms)
        Chem.calcImplicitHydrogenCounts(rec_mol, rem_atoms)
        Chem.perceiveHybridizationStates(rec_mol, rem_atoms)
        Chem.setAromaticityFlags(rec_mol, rem_atoms)

        if Chem.makeHydrogenComplete(rec_mol):                    # make implicit hydrogens (if any) explicit
            Chem.calcHydrogen3DCoordinates(rec_mol)               # calculate 3D coordinates for the added expl. hydrogens
            Biomol.setHydrogenResidueSequenceInfo(rec_mol, False) # set residue information for the added expl. hydrogens

        # calc MMFF94 partial charges
        ForceField.perceiveMMFF94AromaticRings(rec_mol, False)        # perceive aromatic rings according to the MMFF94 aroamticity model and store data as Chem.MolecularGraph property
        ForceField.assignMMFF94AtomTypes(rec_mol, False, False)       # perceive MMFF94 atom types (tolerant mode) set corresponding property for all atoms
        ForceField.assignMMFF94BondTypeIndices(rec_mol, False, False) # perceive MMFF94 bond types (tolerant mode) set corresponding property for all bonds
        ForceField.calcMMFF94AtomCharges(rec_mol, False, False)       # calculate MMFF94 atom charges (tolerant mode) set corresponding property for all atoms

    except Exception as e:
        sys.exit(f'Error: processing of receptor structure failed:\n{str(e)}')            

    return rec_mol
   
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates a binding pocket shape/electrostatics descriptor for a given receptor '\
                                    'structure according to the procedure devised by Kuvek et al.')

    parser.add_argument('-i',
                        dest='receptor_file',
                        required=True,
                        metavar='<file>',
                        help='Receptor structure input file (*.mol2, *.pdb, *.mmtf, *.cif, *.mmcif)')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Descriptor output file')
    parser.add_argument('-s',
                        dest='strip_res_list',
                        required=False,
                        metavar='<three-letter code>',
                        nargs='+',
                        help='Whitespace separated list of PDB three-letter codes specifying residues to remove from the receptor structure (e.g. an existing ligand)')
    parser.add_argument('-c',
                        dest='sphere_ctr',
                        required=True,
                        metavar='<float>',
                        nargs='+',
                        type=float,
                        help='Whitespace separated list of probe sphere center x, y and z coordinates')
    parser.add_argument('-r',
                        dest='sphere_rad',
                        required=False,
                        metavar='<float>',
                        type=float,
                        default=20.0,
                        help='Probe sphere radius (default: 20.0)')
    parser.add_argument('-n',
                        dest='num_test_vecs',
                        required=False,
                        metavar='<integer>',
                        type=int,
                        default=492,
                        help='Number of intersection test vectors (default: 492)')
    parser.add_argument('-t',
                        dest='write_test_vecs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output test vector x, y and z coordinates for each descriptor element (default: false)')
    parser.add_argument('-p',
                        dest='write_inters_pts',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output test vector atom intersection point x, y and z coordinates for each descriptor element (default: false)')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')

    return parser.parse_args()

def main() -> None:
    args = parseArgs()

    if len(args.sphere_ctr) != 3:
        sys.exit('Error: sphere center coordinates missing or incomplete')       
    
    # read and preprocess the receptor structure
    rec_mol = readAndPrepareReceptorStructure(args)

    # create and initialize an instance of the class Descr.KuvekPocketDescriptorCalculator which
    # will perform the descriptor generation
    descr_calc = Descr.KuvekPocketDescriptorCalculator()

    descr_calc.sphereRadius = args.sphere_rad       # apply the -r argument
    descr_calc.numTestVectors = args.num_test_vecs  # apply the -n argument

    # modify the atom charge function to retrieve MMFF94 partial charges
    descr_calc.atomChargeFunction = ForceField.getMMFF94Charge

    # vector that will store the binding pocket descriptor values
    descr = Math.DVector()

    try:
        descr_calc.calculate(args.sphere_ctr, rec_mol, descr)
        
        with open(args.out_file, 'w') as out_file:
            for i in range(descr_calc.numTestVectors):
                out_file.write(f'{descr(i * 2):.4f} {descr(i * 2 + 1):.4f}')
                
                if args.write_test_vecs:
                    tv = descr_calc.getTestVector(i)
                    out_file.write(f' {tv(0):.4f} {tv(1):.4f} {tv(2):.4f}')

                if args.write_inters_pts:
                    ip = descr_calc.getTestVector(i) * descr(i * 2)
                    out_file.write(f' {ip(0):.4f} {ip(1):.4f} {ip(2):.4f}')
                    
                out_file.write('\n')
         
    except Exception as e:    # handle exception raised in case of severe errors
        sys.exit(f'Error: descriptor calculation failed:\n{str(e)}')
   
    if not args.quiet:
        print('Done!')

    sys.exit(0)
        
if __name__ == '__main__':
    main()
