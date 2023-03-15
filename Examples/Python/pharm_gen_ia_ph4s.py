#!/bin/env python

##
# pharm_gen_ia_ph4s.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2022 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
import CDPL.Biomol as Biomol
import CDPL.Pharm as Pharm
import CDPL.MolProp as MolProp

    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates pharmacophores describing the interactions between a given receptor structure and a set of ligand molecules.')

    parser.add_argument('-r',
                        dest='receptor_file',
                        required=True,
                        metavar='<file>',
                        help='Receptor structure input file (*.mol2, *.pdb, *.mmtf)')
    parser.add_argument('-l',
                        dest='ligands_file',
                        required=True,
                        metavar='<file>',
                        help='Ligand structure input file (*.sdf, *.mol2, *.cdf)')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Pharmacophore output file (*.pml, *.cdf)')
    parser.add_argument('-s',
                        dest='strip_res_list',
                        required=False,
                        metavar='<three-letter code(s)>',
                        nargs='+',
                        help='Whitespace separated list of PDB three-letter codes specifying residues to remove from the receptor structure (e.g. an existing ligand)')
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
    parse_args = parser.parse_args()

    return parse_args

# reads and preprocesses the specified receptor structure
def readAndPrepareReceptorStructure(args: argparse.Namespace) -> Chem.Molecule:
    name_and_ext = os.path.splitext(args.receptor_file)    # get the extension of the input file

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine receptor input file format (file extension missing)')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Chem.MoleculeIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:     # check if CDPKit supports reading molecule data stored in the given format
        sys.exit('Error: receptor input file format \'%s\' not supported' % name_and_ext[1])

    sup_fmts = [ Chem.DataFormat.MOL2,
                 Biomol.DataFormat.PDB,
                 Biomol.DataFormat.MMTF ]
                        
    if ipt_handler.getDataFormat() not in sup_fmts:       # check if the format is supported by this script 
        sys.exit('Error: receptor input file format \'%s\' not supported' % name_and_ext[1])

    reader = ipt_handler.createReader(args.receptor_file) # create file reader instance
    rec_mol = Chem.BasicMolecule()                        # create an instance of the default implementation of the
                                                          # Chem.Molecule interface that will store the receptor struct.
    try:
        if not reader.read(rec_mol):  # read receptor structure
            sys.exit('Error: reading receptor structure failed')

    except Exception as e:
        sys.exit('Error: reading receptor structure failed:\n' + str(e))            

    # preprocess the receptor structure (removal of residues and
    # calculation of properties required by the pharm. generation procedure)
    try:
        # if structure comes from an MOL2 file, convert MOL2 residue data into PDB-style data
        if ipt_handler.getDataFormat() == Chem.DataFormat.MOL2: 
            Biomol.convertMOL2ToPDBResidueInfo(rec_mol, True)

        rem_atoms = False

        # delete atoms belonging to residues that should be stripped
        if args.strip_res_list:            
            atoms_to_rem = Chem.Fragment() # will store the atoms to delete
            res_to_strip = { tlc.upper() for tlc in args.strip_res_list }
        
            for atom in rec_mol.atoms:     # identify and note atoms belonging to the stripped residues
                if Biomol.getResidueCode(atom).upper() in res_to_strip:
                    atoms_to_rem.addAtom(atom)

            if atoms_to_rem.numAtoms > 0:
                rec_mol -= atoms_to_rem    # delete atoms from the receptor structure
                rem_atoms = True

                if not args.quiet:
                    print('! Removed %s atoms from the receptor structure' % str(atoms_to_rem.numAtoms))

        # prepares the receptor structure for pharmacophore generation
        Chem.perceiveSSSR(rec_mol, rem_atoms)
        Chem.setRingFlags(rec_mol, rem_atoms)
        Chem.calcImplicitHydrogenCounts(rec_mol, rem_atoms);
        Chem.perceiveHybridizationStates(rec_mol, rem_atoms);
        Chem.setAromaticityFlags(rec_mol, rem_atoms);

        if Chem.makeHydrogenComplete(rec_mol):                    # make implicit hydrogens (if any) explicit
            Chem.calcHydrogen3DCoordinates(rec_mol)               # calculate 3D coordinates for the added expl. hydrogens
            Biomol.setHydrogenResidueSequenceInfo(rec_mol, False) # set residue information for the added expl. hydrogens

        MolProp.calcAtomHydrophobicities(rec_mol, False)          # calculate atom hydrophobicity values (needed for hydrophobic
                                                                  # pharm. feature generation)
    except Exception as e:
        sys.exit('Error: processing of receptor structure failed: ' + str(e))            

    return rec_mol

# returns a Chem.MoleculeReader instance for the specified ligand input file format
def getLigandMolReaderByFileExt(filename: str) -> Chem.MoleculeReader:
    name_and_ext = os.path.splitext(filename)    # get the extension of the input file

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine ligand input file format (file extension missing)')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Chem.MoleculeIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:
        sys.exit('Error: ligand input file format \'%s\' not supported' % name_and_ext[1])

    return ipt_handler.createReader(filename)    # create and return file reader instance

# returns a Pharm.FeatureContainerWriter for the specified pharmacophore output file format
def getPharmWriterByFileExt(filename: str) -> Pharm.FeatureContainerWriter:
    name_and_ext = os.path.splitext(filename)    # get the extension of the output file

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine pharmacophore output file format (file extension missing)')

    # get output handler for the format specified by the output file's extension
    opt_handler = Pharm.FeatureContainerIOManager.getOutputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not opt_handler:
        sys.exit('Error: pharmacophore output file format \'%s\' not supported' % name_and_ext[1])

    return opt_handler.createWriter(filename)    # create and return file writer instance

def main() -> None:
    args = parseArgs()

    rec_mol = readAndPrepareReceptorStructure(args)             # read and preprocess the specified receptor structure
    lig_reader = getLigandMolReaderByFileExt(args.ligands_file) # get a reader for the ligand structure input file
    ph4_writer = getPharmWriterByFileExt(args.out_file)         # get writer for the pharmacophore output file
 
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
            # compose a simple ligand identifier for messages
            mol_id = Chem.getName(lig_mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty or not available
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            if not args.quiet:
                print('- Generating interaction pharmacophore of molecule %s...' % mol_id)

            try:
                Pharm.prepareForPharmacophoreGeneration(lig_mol) # make ligand ready for pharm. generation

                ph4_gen.generate(lig_mol, rec_mol, ia_ph4, True) # generate the pharmacophore (True = extract ligand environment residues on-the-fly)

                try:
                    if not ph4_writer.write(ia_ph4): # output pharmacophore
                        sys.exit('Error: writing interaction pharmacophore of molecule %s failed: %s' % (mol_id, str(e)))

                except Exception as e:               # handle exception raised in case of severe write errors
                    sys.exit('Error: writing interaction pharmacophore of molecule %s failed: %s' % (mol_id, str(e)))
                
            except Exception as e:                   # handle exception raised in case of severe processing errors
                sys.exit('Error: interaction pharmacophore generation for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
            
    except Exception as e:                           # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule %s failed: %s' % (str(i), str(e)))

    if not args.quiet:
        print('Done!')

    ph4_writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()