##
# gen_ia_ph4s.py 
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
import os

import CDPL.Chem as Chem
import CDPL.Biomol as Biomol
import CDPL.Pharm as Pharm
import CDPL.MolProp as MolProp


# reads and preprocesses the specified receptor structure
def readAndPrepareReceptorStructure(args: argparse.Namespace) -> Chem.Molecule:
    # create reader for receptor structure (format specified by file extension)
    reader = Chem.MoleculeReader(args.receptor_file) 
    
    sup_fmts = [ Chem.DataFormat.MOL2,
                 Biomol.DataFormat.PDB,
                 Biomol.DataFormat.MMTF,
                 Biomol.DataFormat.MMCIF ]
                        
    if reader.getDataFormat() not in sup_fmts:   # check if the format is supported by this script
        sys.exit('Error: receptor input file format not supported')

    rec_mol = Chem.BasicMolecule()    # create an instance of the default implementation of the
                                      # Chem.Molecule interface that will store the receptor struct.
    try:
        if not reader.read(rec_mol):  # read receptor structure
            sys.exit('Error: reading receptor structure failed')

    except Exception as e:
        sys.exit('Error: reading receptor structure failed:\n' + str(e))            

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
                    print('! Removed %s atoms from the receptor structure' % str(atoms_to_rem.numAtoms))

        # prepares the receptor structure for pharmacophore generation
        Chem.perceiveSSSR(rec_mol, rem_atoms)
        Chem.setRingFlags(rec_mol, rem_atoms)
        Chem.calcImplicitHydrogenCounts(rec_mol, rem_atoms)
        Chem.perceiveHybridizationStates(rec_mol, rem_atoms)
        Chem.setAromaticityFlags(rec_mol, rem_atoms)

        if Chem.makeHydrogenComplete(rec_mol):                    # make implicit hydrogens (if any) explicit
            Chem.calcHydrogen3DCoordinates(rec_mol)               # calculate 3D coordinates for the added expl. hydrogens
            Biomol.setHydrogenResidueSequenceInfo(rec_mol, False) # set residue information for the added expl. hydrogens

        MolProp.calcAtomHydrophobicities(rec_mol, False)          # calculate atom hydrophobicity values (needed for hydrophobic
                                                                  # pharm. feature generation)
    except Exception as e:
        sys.exit('Error: processing of receptor structure failed:\n' + str(e))            

    return rec_mol

# outputs useful information about the ligand atoms and pocket residues that are involved in the
# interactions described by generated pharmacophoric features
def outputInteractionData(ligand_idx: int, lig_mol: Chem.MolecularGraph, ia_ph4: Pharm.FeatureContainer, out_file) -> None:
    for ftr in ia_ph4:
        if Pharm.getType(ftr) == Pharm.FeatureType.EXCLUSION_VOLUME: # only regular features cover ligand atoms
            continue
        
        lig_atom_inds = None
        lig_substruct = Pharm.getSubstructure(ftr)

        # generate ligand atom index list
        for atom_idx in sorted(lig_mol.getAtomIndex(atom) for atom in lig_substruct.atoms):
            if lig_atom_inds:
                lig_atom_inds = f'{lig_atom_inds}, {atom_idx}'
            else:
                lig_atom_inds = str(atom_idx)

        out_file.write(f'{ligand_idx}\t{ia_ph4.getFeatureIndex(ftr)}\t{Pharm.getType(ftr)}\t{lig_atom_inds}\t{Pharm.getEnvironmentResidueInfo(ftr)}\n')

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates pharmacophores describing the interactions between a given receptor structure and a set of ligand molecules.')

    parser.add_argument('-r',
                        dest='receptor_file',
                        required=True,
                        metavar='<file>',
                        help='Receptor structure input file (*.mol2, *.pdb, *.mmtf, *.cif, *.mmcif)')
    parser.add_argument('-l',
                        dest='ligands_file',
                        required=True,
                        metavar='<file>',
                        help='Ligand structure input file (*.sdf, *.mol2, *.cdf)')
    parser.add_argument('-o',
                        dest='ph4_out_file',
                        required=True,
                        metavar='<file>',
                        help='Pharmacophore output file (*.pml, *.cdf)')
    parser.add_argument('-i',
                        dest='ia_out_file',
                        required=False,
                        metavar='<file>',
                        help='Interaction data output file')
    parser.add_argument('-s',
                        dest='strip_res_list',
                        required=False,
                        metavar='<res-id>',
                        nargs='+',
                        help='Whitespace separated list of identifiers of residues to remove from the receptor structure (e.g. an existing ligand). '\
                        'Residue identifiers consist of three components separated by an underscore: [chain id]_[tlc]_[res. seq. no.]. '\
                        'The individual components are optional and the whole string is interpreted '\
                        'as a regular expression that gets matched against the residue id of '\
                        'each receptor atom. Examples: HOH -> rem. all waters, A_MET -> remove all MET residues of chain A, '\
                        '_300$ -> remove all residues with sequ. number 300')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    parser.add_argument('-x',
                        dest='gen_x_vols',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Generate exclusion volumes (default: false)')

    return parser.parse_args()

def main() -> None:
    args = parseArgs()

    # read and preprocess the receptor structure
    rec_mol = readAndPrepareReceptorStructure(args)

    # create reader for the ligand input file (format specified by file extension)
    lig_reader = Chem.MoleculeReader(args.ligands_file)

     # create writer for the generated pharmacophores (format specified by file extension)
    ph4_writer = Pharm.FeatureContainerWriter(args.ph4_out_file)

    if args.ia_out_file:
        ia_out_file = open(args.ia_out_file, 'w')
        
        # write TSV file column headers
        ia_out_file.write('Input Ligand Index\tPharm. Feature Index\tPharm. Feature Type\tLigand Atom Indices\tPocket Residues\n')

    lig_mol = Chem.BasicMolecule()          # create an instance of the default implementation of the
                                            # Chem.Molecule interface that will store the ligand structures
    ia_ph4 = Pharm.BasicPharmacophore()     # create an instance of the default implementation of the Pharm.Pharmacophore
                                            # interface that will store the generated pharmacophores

    ph4_gen = Pharm.InteractionPharmacophoreGenerator() # create an instance of the pharmacophore generator

    ph4_gen.addExclusionVolumes(args.gen_x_vols)        # specify whether to generate exclusion volume spheres 
                                                        # on pharm. feature atoms of interacting residues
    try:
        i = 1

        # read and process ligand molecules one after the other until the end of input has been reached (or a severe error occurs)
        while lig_reader.read(lig_mol):
            mol_id = Chem.getName(lig_mol).strip()

            # compose a ligand identifier (for messages) and a name for the created pharmacophore
            if mol_id == '':   # fallback if ligand name is empty or not available
                pharm_id = f'{os.path.splitext(os.path.basename(args.ligands_file))[0]}#{i}'
                mol_id = f'#{i}'  
            else:
                pharm_id = mol_id
                mol_id = f'\'{mol_id}\' (#{i})'

            if not args.quiet:
                print('- Generating interaction pharmacophore of molecule %s...' % mol_id)

            try:
                Pharm.prepareForPharmacophoreGeneration(lig_mol) # make ligand ready for pharm. generation

                ph4_gen.generate(lig_mol, rec_mol, ia_ph4, True) # generate the pharmacophore (True = extract ligand environment residues on-the-fly)

                Pharm.setName(ia_ph4, pharm_id)                  # set pharmacophore name
                
                if not args.quiet:
                     print(' -> Generated %s features: %s' % (str(ia_ph4.numFeatures), Pharm.generateFeatureTypeHistogramString(ia_ph4)))

                if args.ia_out_file:                             # if desired, output interaction data 
                     outputInteractionData(i - 1, lig_mol, ia_ph4, ia_out_file)
                    
                try:
                    if not ph4_writer.write(ia_ph4): # output pharmacophore
                        sys.exit('Error: writing interaction pharmacophore of molecule %s failed' % mol_id)

                except Exception as e:               # handle exception raised in case of severe write errors
                    sys.exit('Error: writing interaction pharmacophore of molecule %s failed:\n%s' % (mol_id, str(e)))
                
            except Exception as e:                   # handle exception raised in case of severe processing errors
                sys.exit('Error: interaction pharmacophore generation for molecule %s failed:\n%s' % (mol_id, str(e)))

            i += 1
            
    except Exception as e:                           # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule %s failed:\n%s' % (str(i), str(e)))

    if not args.quiet:
        print('Done!')
        
    if args.ia_out_file:
        ia_out_file.close()

    ph4_writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
