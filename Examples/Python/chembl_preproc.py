#!/bin/env python

##
# chembl_preproc.py 
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

    
# performs ChEMBL molecule standardization and parent structure extraction (optional)
# for a given input molecule using a provided Chem.ChEMBLStandardizer instance
def standardize(chembl_proc: Chem.ChEMBLStandardizer, in_mol: Chem.Molecule, out_mol: Chem.Molecule, args: argparse.Namespace) -> Chem.ChEMBLStandardizer.ChangeFlags:
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

def parseArgs() -> argparse.Namespace:
    def strtobool(value: str) -> bool:
        value = value.lower()
        
        if value in ("y", "yes", "on", "1", "true", "t"):
            return True
        
        return False
    
    parser = argparse.ArgumentParser(description='Performs molecule standardization according to the ChEMBL structure curation pipeline workflow.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Input molecule file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
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
                        type=lambda x:bool(strtobool(x)),
                        default=True,
                        help='Extract parent structure (default: true)')
    parser.add_argument('-d',
                        dest='drop_excluded',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Drop structures that fulfill the exclusion criterions (default: false)')
    parser.add_argument('-x',
                        dest='proc_excluded',
                        required=False,
                        metavar='<true|false>',
                        type=lambda x:bool(strtobool(x)),
                        default=True,
                        help='Standardize structures that fulfill the exclusion criterions (default: true)')

    return parser.parse_args()

def main() -> None:
    args = parseArgs() # process command line arguments

    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for output molecules (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # do not update timestamp for output in an MDL format, just for testing purposes!
    Chem.setMDLUpdateTimestampParameter(writer, False)

    # write canonical SMILES
    Chem.setSMILESOutputCanonicalFormParameter(writer, True)
    
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
                change_flags = standardize(chembl_proc, in_mol, out_mol, args) 

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
                        sys.exit('Error: writing molecule %s failed' % mol_id)

                except Exception as e: # handle exception raised in case of severe write errors
                    sys.exit('Error: writing molecule %s failed: %s' % (mol_id, str(e)))
                
            except Exception as e: # handle exception raised in case of severe structure processing errors
                sys.exit('Error: processing of molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
            
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading of molecule %s failed: %s' % (str(i), str(e)))

    writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
