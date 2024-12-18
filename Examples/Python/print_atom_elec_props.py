#!/bin/env python

##
# print_atom_elec_props.py 
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


# outputs the corresponding properties of each atom of the provided molecule
def outputProperties(mol: Chem.Molecule) -> None:
    Chem.calcBasicProperties(mol, False)       # calculate basic molecular properties (if not yet done)
    Chem.perceivePiElectronSystems(mol, False) # perceive pi electron systems and store info as Chem.MolecularGraph property
                                               # (required for MHMO calculations)

    # calculate sigma charges and electronegativities using the PEOE method and store values as atom properties
    # (prerequisite for MHMO calculations)
    MolProp.calcPEOEProperties(mol, False)  

    # calculate pi charges, electronegativities and other properties by a modified Hueckel MO method and store values as properties
    MolProp.calcMHMOProperties(mol, False)
                
    for atom in mol.atoms:
        print('- Atom #%s' % str(atom.getIndex()))
        print('\tSigma charge: %s' % str(MolProp.getPEOESigmaCharge(atom)))
        print('\tPi charge: %s' % str(MolProp.getMHMOPiCharge(atom)))
        print('\tTotal partial charge: %s' % str(MolProp.calcTotalPartialCharge(atom)))
        print('\tLone-pair electronegativity: %s' % str(MolProp.calcLonePairElectronegativity(atom, mol)))
        print('\tPi electronegativity: %s' % str(MolProp.calcPiElectronegativity(atom, mol)))
        print('\tSigma electronegativity: %s' % str(MolProp.getPEOESigmaElectronegativity(atom)))
        print('\tExerted inductive effect: %s' % str(MolProp.calcInductiveEffect(atom, mol)))
        print('\tFree valence electron count: %s' % str(MolProp.calcFreeValenceElectronCount(atom, mol)))
        print('\tValence electron count: %s' % str(MolProp.calcValenceElectronCount(atom)))

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
