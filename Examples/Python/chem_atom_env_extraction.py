#!/bin/env python

##
# chem_atom_env_extraction.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2022 Thomas Seidel <thomas.seidel@univie.ac.at>
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

import CDPL.Chem as Chem


# extracts the structural environments of the atoms in the specified molecular graph and outputs them as SMILES strings
def printEnvironments(molgraph: Chem.MolecularGraph) -> None: 
    Chem.calcImplicitHydrogenCounts(molgraph, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
    Chem.perceiveHybridizationStates(molgraph, False) # perceive atom hybridization states and set corresponding property for all atoms
    Chem.perceiveSSSR(molgraph, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setRingFlags(molgraph, False)                # perceive cycles and set corresponding atom and bond properties
    Chem.setAromaticityFlags(molgraph, False)         # perceive aromaticity and set corresponding atom and bond properties

    frag = Chem.Fragment()                            # for storing extracted atom environments
    
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
