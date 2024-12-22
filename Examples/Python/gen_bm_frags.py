#!/bin/env python

##
# gen_bm_frags.py 
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

    
# performs Bemis-Murcko framework analyis for a given input molecule
def bmAnalyze(molgraph: Chem.MolecularGraph, keep_hs: bool) -> Chem.BemisMurckoAnalyzer:
    Chem.calcBasicProperties(molgraph, False)  # calculate basic molecular properties (if not yet done)
    
    # create an instance of the class implementing the Bemis-Murcko analyis rules
    bm_analyzer = Chem.BemisMurckoAnalyzer()

    # apply -H option
    bm_analyzer.stripHydrogens(not keep_hs)

    # perform analysis
    bm_analyzer.analyze(molgraph)

    return bm_analyzer
    
def getLogMessage(bm_analyzer: Chem.BemisMurckoAnalyzer, mol_id: str) -> str:
    msg =  f'- Molecule {mol_id}\n'
    msg += f'  Frameworks:   {bm_analyzer.getFrameworks().getSize()}\n'
    msg += f'  Ring Systems: {bm_analyzer.getRingSystems().getSize()}\n'
    msg += f'  Linkers:      {bm_analyzer.getLinkers().getSize()}\n'
    msg += f'  Side Chains:  {bm_analyzer.getSideChains().getSize()}'
     
    return msg

def parseArgs() -> argparse.Namespace:
    def strtobool(value: str) -> bool:
        value = value.lower()
        
        if value in ("y", "yes", "on", "1", "true", "t"):
            return True
        
        return False
    
    parser = argparse.ArgumentParser(description='Analyzes the framework of given input molecules according to the rules established by Bemis and Murcko.')

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
    parser.add_argument('-v',
                        dest='verbose',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Verbose output (default: false)')
    parser.add_argument('-m',
                        dest='output_mol',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output the input molecule before the resulting fragments (default: false)')
    parser.add_argument('-H',
                        dest='keep_hs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Keep hydrogen atoms (default: false)')
    parser.add_argument('-f',
                        dest='output_fws',
                        required=False,
                        metavar='<true|false>',
                        type=lambda x:bool(strtobool(x)),
                        default=True,
                        help='Output molecule frameworks (default: true)')
    parser.add_argument('-r',
                        dest='output_rsys',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output molecule ring systems (default: false)')
    parser.add_argument('-s',
                        dest='output_schns',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output molecule side chains (default: false)')
    parser.add_argument('-l',
                        dest='output_lnks',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output ring system linkers (default: false)')
    parser.add_argument('-x',
                        dest='atom_mpg',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Label atoms with atom mapping IDs (default: false)')
    parser.add_argument('-c',
                        dest='carbonize',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output fragments as carbon only skeletons (default: false)')
   
    return parser.parse_args()

# converts all atoms into carbons and equalizes other basic atom/bond properties
def carbonize(molgraph: Chem.MolecularGraph) -> None:
    for atom in molgraph.atoms:
        Chem.setSymbol(atom, 'C')
        Chem.setType(atom, Chem.AtomType.C)
        Chem.clearFormalCharge(atom)
        Chem.setImplicitHydrogenCount(atom, 0)
        Chem.setAromaticityFlag(atom, False)
        Chem.setHybridizationState(atom, Chem.HybridizationState.UNKNOWN)
        Chem.clearStereoDescriptor(atom)
        Chem.clear3DCoordinates(atom)
        Chem.clear3DCoordinatesArray(atom)

    for bond in molgraph.bonds:
        Chem.setOrder(bond, 1)
        Chem.setAromaticityFlag(bond, False)
        Chem.clearStereoDescriptor(bond)
        Chem.set2DStereoFlag(bond, Chem.BondStereoFlag.PLAIN)
        
def outputFragments(frags: Chem.FragmentList, writer: Chem.MolecularGraphWriter, mol_name: str, mol_id: str, frag_type: str) -> None:
    for i in range(len(frags)):
        frag = frags[i]

        # set fragment name encoding the parent molecule and fragment number
        Chem.setName(frag, mol_name + f'_{frag_type}#{i + 1}') 
                        
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

def main() -> None:
    args = parseArgs() # process command line arguments
        
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for output fragments (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 
  
    if args.atom_mpg: # enable atom mapping IDs for SMILES output
        Chem.setSMILESMolOutputAtomMappingIDParameter(writer, True)

    # write canonical SMILES
    Chem.setSMILESOutputCanonicalFormParameter(writer, True)
    
    # create instances of the default implementation of the Chem.Molecule interface for the input molecule
    in_mol = Chem.BasicMolecule()
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
                # perform Bemis-Murcko analysis of in_mol
                bm_analyzer = bmAnalyze(in_mol, args.keep_hs) 

                if args.verbose:
                    print(getLogMessage(bm_analyzer, mol_id))

                # label atoms with atom mapping IDs to see correspondences between fragment and parent molecule atoms
                if args.atom_mpg: 
                    for atom in in_mol.atoms:
                        Chem.setAtomMappingID(atom, atom.getIndex() + 1)

                try:
                    if args.output_mol: # write input molecule before the obtained fragments
                        if not writer.write(in_mol):
                            sys.exit(f'Error: writing molecule {mol_id} failed')

                    if args.carbonize:  # convert all atoms into carbons and equalize other basic atom/bond properties
                        carbonize(in_mol)

                    if args.output_fws:
                        outputFragments(bm_analyzer.getFrameworks(), writer, mol_name, mol_id, 'F')

                    if args.output_rsys:
                        outputFragments(bm_analyzer.getRingSystems(), writer, mol_name, mol_id, 'R')

                    if args.output_lnks:
                        outputFragments(bm_analyzer.getLinkers(), writer, mol_name, mol_id, 'L')
                     
                    if args.output_schns:
                        outputFragments(bm_analyzer.getSideChains(), writer, mol_name, mol_id, 'S')
                             
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
