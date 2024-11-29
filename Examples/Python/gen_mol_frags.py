#!/bin/env python

##
# gen_mol_frags.py 
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

    
# splits a given input molecule into fragments using the provided Chem.FragmentGenerator instance implementing
# the fragmentation rules
def genFragments(frag_gen: Chem.FragmentGenerator, in_mol: Chem.Molecule, out_frags: Chem.FragmentList) -> None:
    Chem.initSubstructureSearchTarget(in_mol, False) # calculate required properties

    frag_gen.generate(in_mol, out_frags)

def getLogMessage(verb_level: int, mol_id: str, num_frags: int, frag_gen: Chem.FragmentGenerator) -> str:
    if verb_level == 0:
        return None

    if num_frags <= 1:
        return  f'- Molecule {mol_id}: no fragmentation'

    msg = f'- Molecule {mol_id}: {num_frags} fragments'

    if verb_level < 2:
        return msg

    msg += '\n  Cut bonds (Rule ID, Bond index, Atom#1 index, Atom#2 index, Fragment#1 index, Fragment#2 index):'
    
    # gather information about the bonds that were split during fragmentation
    for i in range(frag_gen.numFragmentLinks):
        frag_link = frag_gen.getFragmentLink(i)
        msg += (f'\n  {frag_link.ruleID}, {frag_link.bond.index}, {frag_link.bond.begin.index}, '
                f'{frag_link.bond.end.index}, {frag_link.fragment1Index}, {frag_link.fragment2Index}')
    
    return msg

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Performs molecule fragmentation using BRICS or RECAP rules')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Input molecule file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Fragment output file')
    parser.add_argument('-r',
                        dest='rule_set',
                        required=True,
                        metavar='<string>',
                        help='Fragmentation rule set (BRICS or RECAP)')
    parser.add_argument('-v',
                        dest='verb_level',
                        required=False,
                        metavar='<0|1|2>',
                        choices=range(0, 3),
                        default=1,
                        help='Verbosity level (default: 1; 0 -> no console output, 1 -> verbose, 2 -> extra verbose)',
                        type=int)
    parser.add_argument('-m',
                        dest='output_mol',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output the fragmented molecule before its fragments (default: false)')
    parser.add_argument('-b',
                        dest='inc_split_bonds',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include bonds that were split during fragmentation in the obtained fragments (default: false)')
    parser.add_argument('-x',
                        dest='atom_mpg',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Label atoms with atom mapping IDs (default: false)')

    return parser.parse_args()

def main() -> None:
    args = parseArgs() # process command line arguments
    
    # create an instance of the class implementing the desired fragmentation rule set
    if args.rule_set.lower() == "brics":
        frag_gen = Chem.BRICSFragmentGenerator()
    elif args.rule_set.lower() == "recap":
        frag_gen = Chem.RECAPFragmentGenerator()
    else:
        sys.exit('Error: invalid fragmentation rule set')

    frag_gen.includeSplitBonds(args.inc_split_bonds) # apply -b option
        
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for output fragments (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 
  
    if args.atom_mpg: # enable atom mapping IDs for SMILES output
        Chem.setSMILESMolOutputAtomMappingIDParameter(writer, True)
    
    # create instances of the default implementation of the Chem.Molecule interface for the input molecule
    in_mol = Chem.BasicMolecule()

    # create instances of the Chem.FragmentList data structure storing the generated fragments
    out_frags = Chem.FragmentList()
        
    i = 1
    
    try:
        # read and process molecules one after the other until the end of input has been reached (or a severe error occurs)
        while reader.read(in_mol):
            # compose a molecule identifier
            mol_name = Chem.getName(in_mol).strip() 

            if mol_name == '':
                mol_name = f'Mol#{i}'
                mol_id = f'#{i}'  # fallback if name is empty or not available
            else:
                mol_id = f'\'{mol_name}\' (#{i})'
         
            try:
                # perform molecule fragmentation
                genFragments(frag_gen, in_mol, out_frags) 

                log_msg = getLogMessage(args.verb_level, mol_id, len(out_frags), frag_gen)

                if log_msg:
                    print(log_msg)

                if args.atom_mpg: # label atoms with atom mapping IDs to see correspondences between fragment and parent molecule atoms
                    for atom in in_mol.atoms:
                        Chem.setAtomMappingID(atom, atom.getIndex() + 1)

                try:
                    if args.output_mol: # write input molecule before the generated fragments
                        if not writer.write(in_mol):
                            sys.exit(f'Error: writing molecule {mol_id} failed')

                    for j in range(len(out_frags)):
                        frag = out_frags[j]

                        # set fragment name encoding the parent molecule and fragment number
                        Chem.setName(frag, mol_name + f'_F#{j + 1}') 
                        
                        # calculate (if not present) some basic properties of the output fragments
                        # that might be required for writing (output format dependent)
                        Chem.perceiveSSSR(frag, False)
                        Chem.perceiveComponents(frag, False)

                        try:
                            # write fragment
                            if not writer.write(frag):
                                sys.exit('Error: writing fragment of molecule {mol_id} failed')
                        except Exception as e: # handle exception raised in case of severe write errors
                             sys.exit(f'Error: writing fragment of molecule {mol_id} failed: {str(e)}')
                             
                except Exception as e: # handle exception raised in case of severe write errors
                    sys.exit(f'Error: writing molecule {mol_id} failed: {str(e)}')
                
            except Exception as e: # handle exception raised in case of severe structure processing errors
                sys.exit(f'Error: processing of molecule {mol_id} failed: {str(e)}')

            i += 1
            
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading of molecule {mol_id} failed: {str(e)}')

    writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
