#!/bin/env python

##
# clean_mol_db.py 
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
import CDPL.MolProp as MolProp

    
# performs a (optional) standardization of the argument molecule and then checks whether
# it fulfills certain user-defined criteria for inclusion/exclusion
def processMolecule(mol: Chem.Molecule, args: argparse.Namespace) -> tuple:
    chgs_mod = False

    if args.min_charges:
        # will store the 'uncharged' version of the argument mol
        res_mol = Chem.BasicMolecule() 

        # minimize the number of charged atoms using the corresponding functionality implemented
        # in class Chem.ProtonationStateStandardizer
        chgs_mod = Chem.ProtonationStateStandardizer().standardize(mol, res_mol, Chem.ProtonationStateStandardizer.MIN_CHARGED_ATOM_COUNT)

        # if changes were made then from now on use the 'uncharged' molecule for further checks
        if chgs_mod:  
            mol = res_mol
        
    comps_strpd = False
    
    if args.strip_comps:
        # perceive components (if not done already)
        comps = Chem.perceiveComponents(mol, False) 

        # find largest component (regarding heavy atom count) but only if multi-comp. molecule
        if comps.size > 1:    # check if multi-comp. molecule
            lgst_comp = None
            lgst_comp_hvy_atom_count = 0

            for comp in Chem.getComponents(mol):                 # for each component
                hvy_atom_count = MolProp.getHeavyAtomCount(comp) # calc. non-hydrogen atom count

                if hvy_atom_count > lgst_comp_hvy_atom_count:    # check if the largest comp. so far has been found
                    lgst_comp_hvy_atom_count = hvy_atom_count    # if so, store for later use
                    lgst_comp = comp

            # if the input molecule has structure data then pass them on (for SDF output)
            if Chem.hasStructureData(mol):                       
                Chem.setStructureData(lgst_comp, Chem.getStructureData(mol))

            # for further checks use only the identified largest component 
            comps_strpd = True
            mol = lgst_comp

    # calc. implicit hydrogen counts (if not done already)
    Chem.calcImplicitHydrogenCounts(mol, False)
    
    # create instance of class MolProp.ElementHistogram for storing the per-element atom counts
    # of the molecule (or its largest comp.)
    elem_histo = MolProp.ElementHistogram()              

    # get per-element atom counts
    MolProp.generateElementHistogram(mol, elem_histo, False)    

    # check if the found chem. elements are all in the set of allowed elements (if specified)
    if not checkAllowedElements(elem_histo, args.allowed_elements):    
        return (None, 'prohibited element detected')

    # check if none of the found chem. elements is in the set of excluded elements (if specified)
    if not checkExcludedElements(elem_histo, args.excluded_elements):
        return (None, 'prohibited element detected')

    # check if all specified minium chem. element atom counts are reached
    if not checkMinAtomCounts(elem_histo, args.min_atom_counts):
        return (None, 'minimum atom counts not reached')

    # check if none of the specified maximum chem. element atom counts gets exceeded
    if not checkMaxAtomCounts(elem_histo, args.max_atom_counts):
        return (None, 'maximum atom count exceeded')

    log_msg = None
    
    if chgs_mod:
        log_msg = 'reduced charged atom count'

    if comps_strpd:
        if log_msg:
            log_msg += ', removed components'
        else:
            log_msg = 'removed components'
            
    return (mol, log_msg)

# checks if all found chem. elements are in the set of allowed elements (if specified)
def checkAllowedElements(elem_histo: MolProp.ElementHistogram, elem_list: list) -> bool:
    if not elem_list:
        return True

    for atom_type in elem_histo.getKeys():
        allowed = False
        
        for all_atom_type in elem_list:
            if Chem.atomTypesMatch(all_atom_type, atom_type):
                allowed = True
                break

        if not allowed:
            return False

    return True

# checks if none of the found chem. elements is in the set of excluded elements (if specified)
def checkExcludedElements(elem_histo: MolProp.ElementHistogram, elem_list: list) -> bool:
    if not elem_list:
        return True

    for atom_type in elem_histo.getKeys():
        for x_atom_type in elem_list:
            if Chem.atomTypesMatch(x_atom_type, atom_type):
                return False

    return True

# return the total number of atoms matching the specified atom type (element or generic type)
def getNumAtomsOfType(elem_histo: MolProp.ElementHistogram, qry_atom_type: int) -> int:
    tot_count = 0

    for atom_type, count in elem_histo.getEntries():
        # check if the elem. histogram entry matches the specified atom type (element or generic type)
        # if so, add the stored count the total count
        if Chem.atomTypesMatch(qry_atom_type, atom_type):  
            tot_count += count

    return tot_count

# checks if all the specified minium counts of atoms matching a particular element or
# generic type are reached
def checkMinAtomCounts(elem_histo: MolProp.ElementHistogram, atom_counts: dict) -> bool:
    if not atom_counts:
        return True
    
    for atom_type, min_count in atom_counts.items():
        if getNumAtomsOfType(elem_histo, atom_type) < min_count:
            return False

    return True

# checks if none of the specified maximum counts of atoms matching a particular element or
# generic type gets exceeded
def checkMaxAtomCounts(elem_histo: MolProp.ElementHistogram, atom_counts: dict) -> bool:
    if not atom_counts:
        return True
    
    for atom_type, max_count in atom_counts.items():
        if getNumAtomsOfType(elem_histo, atom_type) > max_count:
            return False

    return True

# converts a comma separated list of chem. element/generic type symbols into a list of the
# corresponding numeric atom types defined in Chem.AtomType
def parseElementList(elem_list: str) -> list:
    if not elem_list:
        return []
    
    atom_types = []
    
    for elem in elem_list.split(','):
        elem = elem.strip()
        
        if not elem: # zero length?
            continue
        
        atom_type = Chem.AtomDictionary.getType(elem)

        if atom_type == Chem.AtomType.UNKNOWN:
            sys.exit('Error: unknown chemical element/generic type \'%s\'' % elem)

        atom_types.append(atom_type)
            
    return atom_types

# converts a comma separated list of chem. element (or generic type) symbol/count pairs (sep. by colon) into a dictionary
# mapping the corresponding numeric atom types (defined in Chem.AtomType) to an integer number
def parseElementCountList(elem_count_list: str) -> dict:
    if not elem_count_list:
        return {}
    
    atom_type_counts = {}
    
    for elem_count in elem_count_list.split(','):
        elem_count = elem_count.strip()
        
        if not elem_count: # zero length?
            continue
        
        elem_count = elem_count.split(':')
        elem_count[0] = elem_count[0].strip()
        atom_type = Chem.AtomDictionary.getType(elem_count[0])
        
        if atom_type == Chem.AtomType.UNKNOWN:
            sys.exit('Error: unknown chemical element/generic type \'%s\'' % elem_count[0])

        count = 1
        
        if len(elem_count) > 1: # has count spec.?
            count = int(elem_count[1])
            
        atom_type_counts[atom_type] = count
            
    return atom_type_counts
                                
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Strips compounds that fulfill particular user-defined criteria from a molecule database.')

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
    parser.add_argument('-d',
                        dest='disc_file',
                        required=False,
                        metavar='<file>',
                        help='Discarded molecule output file')
    parser.add_argument('-s',
                        dest='strip_comps',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Keep only the largest molecule component (default: false)')
    parser.add_argument('-c',
                        dest='min_charges',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Minimize number of charged atoms (default: false)')
    parser.add_argument('-x',
                        dest='excluded_elements',
                        required=False,
                        metavar="<element list>",
                        help='List of excluded chem. elements (default: no elements are excluded)')
    parser.add_argument('-a',
                        dest='allowed_elements',
                        required=False,
                        metavar="<element list>",
                        help='List of allowed chem. elements (default: all elements are allowed)')
    parser.add_argument('-m',
                        dest='min_atom_counts',
                        required=False,
                        metavar="<element count list>",
                        help='Minimum chem. element specific atom counts (default: no count limits)')
    parser.add_argument('-M',
                        dest='max_atom_counts',
                        required=False,
                        metavar="<element count list>",
                        help='Maximum chem. element specific atom counts (default: no count limits)')
    parser.add_argument('-v',
                        dest='verb_level',
                        required=False,
                        metavar='<0|1|2|3>',
                        choices=range(0, 4),
                        default=1,
                        help='Verbosity level (default: 1; 0 -> no console output, 1 -> print summary, 2 -> verbose, 3 -> extra verbose)',
                        type=int)

    return parser.parse_args()

def main() -> None:
    args = parseArgs() # process command line arguments

    # convert specified lists of chem. element/gen. type symbols into a corresponding list of
    # numeric atom types (defined in Chem.Atomtype)
    args.allowed_elements  = parseElementList(args.allowed_elements)
    args.excluded_elements = parseElementList(args.excluded_elements)

    # convert specified comma separated lists of chem. element (or generic type) symbol/count pairs (sep. by colon) into
    # corresponding dictionaries mapping numeric atom types (defined in Chem.AtomType) to integers
    args.min_atom_counts = parseElementCountList(args.min_atom_counts)
    args.max_atom_counts = parseElementCountList(args.max_atom_counts)
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for molecules passing the checks (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # write canonical SMILES
    Chem.setSMILESOutputCanonicalFormParameter(writer, True)
    
    if args.disc_file:
        # create writer for sorted out molecules (format specified by file extension)
        disc_writer = Chem.MolecularGraphWriter(args.disc_file)
        # write canonical SMILES
        Chem.setSMILESOutputCanonicalFormParameter(disc_writer, True)
    else:
        disc_writer = None
        
    # create instances of the default implementation of the Chem.Molecule interface for the input and output molecules
    in_mol = Chem.BasicMolecule()

    i = 0
    num_changed = 0
    num_disc = 0
    
    try:
        # read and process molecules one after the other until the end of input has been reached (or a severe error occurs)
        while reader.read(in_mol):
            # compose a molecule identifier
            mol_id = Chem.getName(in_mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i + 1)  # fallback if name is empty or not available
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i + 1))
            
            try:
                # process input molecule
                out_mol, log_msg = processMolecule(in_mol, args) 
                
                if not out_mol:         # check whether the molecule has been sorted out
                    if args.verb_level > 1 and log_msg:
                        print('- Molecule %s: discarded, %s' % (mol_id, log_msg))

                    num_disc += 1
                        
                    if not disc_writer: # check whether discarded molecules should be saved to a separate file
                        i += 1
                        continue

                    # write discarded molecule to the specified target file
                    out_mol = in_mol
                    out_mol_writer = disc_writer
                else:
                    if log_msg:
                        if args.verb_level > 1 :
                            print('- Molecule %s: %s' % (mol_id, log_msg))
                            
                        num_changed += 1
                    else:
                        if args.verb_level > 2:
                            print('- Molecule %s: left unchanged' % mol_id)

                    # molecule passed all checks and needs to be written to the regular output file
                    out_mol_writer = writer
                    
                try:
                    # calculate (if not already present) some basic properties of the output molecule
                    # that might be required for writing (output format dependent)
                    Chem.calcImplicitHydrogenCounts(out_mol, False)
                    Chem.perceiveHybridizationStates(out_mol, False)
                    Chem.perceiveSSSR(out_mol, False)
                    Chem.setRingFlags(out_mol, False)
                    Chem.setAromaticityFlags(out_mol, False)
                    Chem.perceiveComponents(out_mol, False)
                              
                    # output molecule
                    if not out_mol_writer.write(out_mol):
                        sys.exit('Error: writing molecule %s failed' % mol_id)

                except Exception as e: # handle exception raised in case of severe write errors
                    sys.exit('Error: writing molecule %s failed: %s' % (mol_id, str(e)))

                i += 1
                
            except Exception as e: # handle exception raised in case of severe processing errors
                sys.exit('Error: processing of molecule %s failed: %s' % (mol_id, str(e)))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading of molecule %s failed: %s' % (str(i), str(e)))

    if args.verb_level > 0:
        print('Summary:')
        print(' - %s molecules processed' % str(i))
        print(' - %s modified ' % str(num_changed))
        print(' - %s discarded' % str(num_disc))
        
    writer.close()
    sys.exit(0)

if __name__ == '__main__':
    main()
