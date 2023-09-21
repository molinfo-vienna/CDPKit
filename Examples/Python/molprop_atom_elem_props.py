#!/bin/env python

##
# molprop_atom_elem_props.py 
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
import os

import CDPL.Chem as Chem
import CDPL.MolProp as MolProp


# outputs the corresponding properties of each atom of the provided molecular graph
def outputProperties(molgraph: Chem.MolecularGraph) -> None:
    for atom in molgraph.atoms:
        print('- Atom #%s' % str(molgraph.getAtomIndex(atom)))
        print('\tAtomic weight: %s' % str(MolProp.getAtomicWeight(atom)))
        print('\tPTE IUPAC group: %s' % str(MolProp.getIUPACGroup(atom)))
        print('\tPTE period: %s' % str(MolProp.getPeriod(atom)))
        print('\tVdW radius: %s' % str(MolProp.getVdWRadius(atom)))
        print('\tCovalent radius (bond order=1): %s' % str(MolProp.getCovalentRadius(atom, 1)))
        print('\tCovalent radius (bond order=2): %s' % str(MolProp.getCovalentRadius(atom, 2)))
        print('\tCovalent radius (bond order=3): %s' % str(MolProp.getCovalentRadius(atom, 3)))
        print('\tAllred Rochow electronegativity: %s' % str(MolProp.getAllredRochowElectronegativity(atom)))
        print('\tElement name: %s' % MolProp.getElementName(atom))
        print('\tValence electron count: %s' % str(MolProp.getElementValenceElectronCount(atom)))
        print('\tAtom type specifies chemical element: %s' % str(MolProp.isChemicalElement(atom)))
        print('\tIs main group element: %s' % str(MolProp.isMainGroupElement(atom)))
        print('\tIs metal: %s' % str(MolProp.isMetal(atom)))
        print('\tIs transition metal: %s' % str(MolProp.isTransitionMetal(atom)))
        print('\tIs non-metal: %s' % str(MolProp.isNonMetal(atom)))
        print('\tIs semi-metal: %s' % str(MolProp.isSemiMetal(atom)))
        print('\tIs halogen: %s' % str(MolProp.isHalogen(atom)))
        print('\tIs noble gas: %s' % str(MolProp.isNobleGas(atom)))

def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input mol. file>' % sys.argv[0])

    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(sys.argv[1]) 
  
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            try:
                outputProperties(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
