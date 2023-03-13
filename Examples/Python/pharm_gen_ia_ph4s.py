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
    parser = argparse.ArgumentParser(description='Generates pharmacophores of the given input molecules.')

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

def readAndPrepareReceptorStructure(args: argparse.Namespace) -> Chem.Molecule:
    # get the extension of the input file
    name_and_ext = os.path.splitext(args.receptor_file)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine receptor file format (file extension missing).')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Chem.MoleculeIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:     # check if CDPKit supports reading molecule data stored in the given format
        sys.exit('Error: receptor file format \'%s\' not supported' % name_and_ext[1])

    sup_fmts = [ Chem.DataFormat.MOL2,
                 Biomol.DataFormat.PDB,
                 Biomol.DataFormat.MMTF ]
                        
    if ipt_handler.getDataFormat() not in sup_fmts:       # check if the format is supported by this script 
        sys.exit('Error: receptor file format \'%s\' not supported' % name_and_ext[1])

    reader = ipt_handler.createReader(args.receptor_file) # create file reader instance
                        
    # create an instance of the default implementation of the Chem.Molecule interface
    rec_mol = Chem.BasicMolecule()

    # read the receptor structure
    try:
        if not reader.read(rec_mol):  # read receptor structure
            sys.exit('Error: reading receptor structure failed')

    except Exception as e:
        sys.exit('Error: reading receptor structure failed:\n' + str(e))            

    # preprocess the receptor structure (removal of residues and
    # calculation of properties needed by later pharm. generation)
    try:
        # if structure comes from an MOL2 file, convert MOL2 residue data into PDB-style data
        if ipt_handler.getDataFormat() == Chem.DataFormat.MOL2: 
            Biomol.convertMOL2ToPDBResidueInfo(rec_mol, True)

        rem_atoms = False

        # remove atoms belonging to residues that should be stripped
        if args.strip_res_list:
            atoms_to_rem = Chem.Fragment() # stores the atoms to remove
            res_to_strip = { tlc.upper() for tlc in args.strip_res_list }
        
            for atom in rec_mol.atoms:     # identify all atoms to remove
                if Biomol.getResidueCode(atom).upper() in res_to_strip:
                    atoms_to_rem.addAtom(atom)

            if atoms_to_rem.numAtoms > 0:
                rec_mol -= atoms_to_rem    # remove atoms
                rem_atoms = True

                if not args.quiet:
                    print('Removed %s atoms from the receptor structure' % str(atoms_to_rem.numAtoms), file=sys.stdout)

        # prepare the receptor structure for pharmacophore generation
        Chem.perceiveSSSR(rec_mol, rem_atoms)
        Chem.setRingFlags(rec_mol, rem_atoms)
        Chem.calcImplicitHydrogenCounts(rec_mol, rem_atoms);
        Chem.perceiveHybridizationStates(rec_mol, rem_atoms);
        Chem.setAromaticityFlags(rec_mol, rem_atoms);

        if Chem.makeHydrogenComplete(rec_mol):
            Chem.calcHydrogen3DCoordinates(rec_mol)
            Biomol.setHydrogenResidueSequenceInfo(rec_mol, False)

        MolProp.calcAtomHydrophobicities(rec_mol, False)
        
    except Exception as e:
        sys.exit('Error: processing of receptor structure failed:\n' + str(e))            

    return rec_mol
                        
def getMolReaderByFileExt(filename: str) -> Chem.MoleculeReader:
    # get the extension of the input file
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine input file format (file extension missing).')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Chem.MoleculeIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:
        sys.exit('Error: unknown input file format \'%s\'' % name_and_ext[1])

    # return file reader instance
    return ipt_handler.createReader(filename)

def getPharmWriterByFileExt(filename: str) -> Pharm.FeatureContainerWriter:
    # get the extension of the output file
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine output file format (file extension missing).')

    # get output handler for the format specified by the output file's extension
    opt_handler = Pharm.FeatureContainerIOManager.getOutputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not opt_handler:
        sys.exit('Error: unknown output file format \'%s\'' % name_and_ext[1])

    # return file writer instance
    return opt_handler.createWriter(filename)
    
def main() -> None:
    args = parseArgs()

    # read and preprocess the specified receptor structure
    rec_mol = readAndPrepareReceptorStructure(args) 

    # if the output pharmacophores have to be stored in a specific format, a writer for this format
    # could be created directly, e.g.
    # writer = Pharm.FilePMLFeatureContainerWriter(args.out_file)
    writer = getPharmWriterByFileExt(args.out_file) 
 
    writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
