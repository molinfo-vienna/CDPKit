#!/bin/env python

##
# extract_atom_envs.py 
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

import CDPL.Chem as Chem


# extracts the structural environments of the atoms in the specified molecular graph and outputs them as SMILES strings
def printEnvironments(molgraph: Chem.MolecularGraph) -> None:
    Chem.calcBasicProperties(molgraph, False)  # calculate basic molecular properties (if not yet done)
   
    frag = Chem.Fragment()                     # for storing extracted atom environments
    
    print('- Atom environments (radius = 3 bonds)')
    
    for atom in molgraph.atoms:
        Chem.getEnvironment(atom, molgraph, 3, frag)     # extract environment of atom reaching out up to three bonds
        Chem.perceiveComponents(frag, False)             # perceive molecular graph components (required for SMILES generation)

        smiles = Chem.generateSMILES(frag, False, False) # generate non-canonical SMILES string with explicit hydrogen atoms
        
        print('Atom #%s: %s' % (str(molgraph.getAtomIndex(atom)), smiles))

def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <mol. input file>' % sys.argv[0])

    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(sys.argv[1]) 
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol): 
            try:
                printEnvironments(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
