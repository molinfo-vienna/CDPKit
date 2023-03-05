#!/bin/env python

##
# chem_chembl_preproc.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2023 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
import distutils.util

import CDPL.Chem as Chem

    
# Procedure called from the main loop which performs ChEMBL molecule standardization
# and parent structure extraction (optional) for an input molecule
def process(chembl_proc: Chem.ChEMBLStandardizer, in_mol: Chem.Molecule, out_mol: Chem.Molecule, args: argparse.Namespace) -> Chem.ChEMBLStandardizer.ChangeFlags:
    # here, the standardization is carried out on a copy of the read input molecule
    # (if only one molecule instance gets provided as argument, modifications will be made in-place)
    change_flags = chembl_proc.standardize(in_mol, out_mol, args.proc_excluded)

    # perform parent structure extraction (optional)
    if args.extract_parent:
        change_flags &= ~Chem.ChEMBLStandardizer.EXCLUDED  # clear excluded flag possibly set by the standardization
                                                           # procedure (might change after salt stripping)
        change_flags |= chembl_proc.getParent(out_mol)     # extract parent structure (in-place) and add information
                                                           # about the carried out modifcations
    return change_flags

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Performs molecule standardization as done by the ChEMBL structure curation pipeline')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<input file>',
                        help='Input molecule file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<output file>',
                        help='Output molecule file')
    parser.add_argument('-v',
                        dest='verb_level',
                        required=False,
                        metavar='<0|1|2>',
                        choices=range(0, 3),
                        default=1,
                        help='Verbosity level (default: 1; 0 -> no console output, 1 -> verbose, 2 -> extra verbose)',
                        type=int)
    parser.add_argument('-p',
                        dest='extract_parent',
                        required=False,
                        metavar='<true|false>',
                        type=lambda x:bool(distutils.util.strtobool(x)),
                        default=True,
                        help='Extract parent structure (default: true)')
    parser.add_argument('-d',
                        dest='drop_excluded',
                        required=False,
                        metavar='<true|false>',
                        type=lambda x:bool(distutils.util.strtobool(x)),
                        default=False,
                        help='Drop structures that fulfill the exclusion criterions (default: false)')
    parser.add_argument('-x',
                        dest='proc_excluded',
                        required=False,
                        metavar='<true|false>',
                        type=lambda x:bool(distutils.util.strtobool(x)),
                        default=True,
                        help='Standardize structures that fulfill the exclusion criterions (default: true)')

    parse_args = parser.parse_args()

    return parse_args

def getReaderByFileExt(filename: str) -> Chem.MoleculeReader:
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

def getWriterByFileExt(filename: str) -> Chem.MolecularGraphWriter:
    # get the extension of the output file
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine output file format (file extension missing).')

    # get output handler for the format specified by the output file's extension
    opt_handler = Chem.MolecularGraphIOManager.getOutputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not opt_handler:
        sys.exit('Error: unknown output file format \'%s\'' % name_and_ext[1])

    # create file writer instance
    writer = opt_handler.createWriter(filename)

    # do not update timestamp during MDL output, just for testing purposes!
    Chem.setMDLUpdateTimestampParameter(writer, False) 

    return writer

def getListOfChangesString(change_flags: Chem.ChEMBLStandardizer.ChangeFlags) -> str:
    changes = '   Carried out modifications:'

    if (change_flags & Chem.ChEMBLStandardizer.EXPLICIT_HYDROGENS_REMOVED):
        changes += '\n    * Explicit hydrogens removed'

    if (change_flags & Chem.ChEMBLStandardizer.UNKNOWN_STEREO_STANDARDIZED):
        changes += '\n    * Undefined stereocenter information standardized'
        
    if (change_flags & Chem.ChEMBLStandardizer.BONDS_KEKULIZED):
        changes += '\n    * Kekule structure generated'

    if (change_flags & Chem.ChEMBLStandardizer.STRUCTURE_NORMALIZED):
        changes += '\n    * Functional groups normalized'
        
    if (change_flags & Chem.ChEMBLStandardizer.CHARGES_REMOVED):
        changes += '\n    * Number of charged atoms reduced'
        
    if (change_flags & Chem.ChEMBLStandardizer.TARTRATE_STEREO_CLEARED):
        changes += '\n    * Configuration of chiral tartrate atoms set to undefined'
                
    if (change_flags & Chem.ChEMBLStandardizer.STRUCTURE_2D_CORRECTED):
        changes += '\n    * 2D structure corrected'

    if (change_flags & Chem.ChEMBLStandardizer.ISOTOPE_INFO_CLEARED):
        changes += '\n    * Isotope information cleared'

    if (change_flags & Chem.ChEMBLStandardizer.SALT_COMPONENTS_REMOVED):
        changes += '\n    * Salt components removed'

    if (change_flags & Chem.ChEMBLStandardizer.SOLVENT_COMPONENTS_REMOVED):
        changes += '\n    * Solvent components removed'

    if (change_flags & Chem.ChEMBLStandardizer.DUPLICATE_COMPONENTS_REMOVED):
        changes += '\n    * Duplicate components removed'
        
    return changes
    
def getLogMessage(change_flags: Chem.ChEMBLStandardizer.ChangeFlags, args: argparse.Namespace, mol_id: str) -> str:
    if args.verb_level == 0:
        return None
    
    if (change_flags & Chem.ChEMBLStandardizer.EXCLUDED):
        if args.drop_excluded:
            return ('- Molecule %s: discarded (flagged as excluded)' % mol_id)

        if not args.proc_excluded:
            return ('- Molecule %s: forwarded unchanged (flagged as excluded)' % mol_id)

        if (change_flags & ~Chem.ChEMBLStandardizer.EXCLUDED):
            if args.verb_level == 2:
                return ('- Molecule %s: modified (flagged as excluded)\n%s' % (mol_id, getListOfChangesString(change_flags)))
            
            return ('- Molecule %s: modified (flagged as excluded)' % mol_id)

        return ('- Molecule %s: forwarded unchanged (flagged as excluded)' % mol_id)

    if change_flags:
        if args.verb_level == 2:
            return ('- Molecule %s: modified\n%s' % (mol_id, getListOfChangesString(change_flags)))
                        
        return ('- Molecule %s: modified' % mol_id)
            
    return ('- Molecule %s: forwarded unchanged' % mol_id)

def main() -> None:
    args = parseArgs() # process command line arguments

    # if the input molecules are expected to be in a specific format, a reader for this format could be created directly, e.g.
    # reader = Chem.FileSDFMoleculeReader(args.in_file)
    reader = getReaderByFileExt(args.in_file) 

    # if the output molecules have to be stored in a specific format, a writer for this format could be created directly, e.g.
    # writer = Chem.FileSDFMolecularGraphWriter(args.out_file)
    writer = getWriterByFileExt(args.out_file) 
    
    # create instances of the default implementation of the Chem.Molecule interface for the input and output molecules
    in_mol = Chem.BasicMolecule()
    out_mol = Chem.BasicMolecule()

    # create an instance of CDPKit's ChEMBL structure curation pipeline implementation
    chembl_proc = Chem.ChEMBLStandardizer()
    i = 1
    
    try:
        # read and process molecules one after the other until the end of input has been reached (or a severe error occurs)
        while reader.read(in_mol):
            # compose a molecule identifier
            mol_id = Chem.getName(in_mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty or not available
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))
         
            try:
                # perform standardization and parent structure extraction (optional)
                change_flags = process(chembl_proc, in_mol, out_mol, args) 

                log_msg = getLogMessage(change_flags, args, mol_id)

                if log_msg:
                    print(log_msg)
                
                # check if the excluded flag has been set and take appropriate action
                if (change_flags & Chem.ChEMBLStandardizer.EXCLUDED) and args.drop_excluded:
                    continue
                
                try:
                    # calculate (if not present) some basic properties of the output molecule
                    # that might be required for writing (output format dependent)
                    Chem.calcImplicitHydrogenCounts(out_mol, False)
                    Chem.perceiveHybridizationStates(out_mol, False)
                    Chem.perceiveSSSR(out_mol, False)
                    Chem.setRingFlags(out_mol, False)
                    Chem.setAromaticityFlags(out_mol, False)
                    Chem.perceiveComponents(out_mol, False)
                              
                    # write output molecule
                    if not writer.write(out_mol):
                        sys.exit('Error: Writing molecule %s failed: %s\n' % (mol_id, str(e)))

                except Exception as e: # handle exception raised in case of severe write errors
                    sys.exit('Error: writing molecule %s failed: %s\n' % (mol_id, str(e)))
                
            except Exception as e: # handle exception raised in case of severe structure processing errors
                sys.exit('Error: processing of molecule %s failed: %s\n' % (mol_id, str(e)))

            i += 1
            
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading of molecule %s failed: %s\n' % (str(i), str(e)))

    writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
