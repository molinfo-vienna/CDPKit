##
# calc_mmff94_charges.py 
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
import CDPL.ForceField as ForceField


# calculates and outputs the MMFF94 charges of the atoms of the provided molecular graph
def calcAndOutputCharges(mol: Chem.Molecule) -> None:
    Chem.calcImplicitHydrogenCounts(mol, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
    Chem.makeHydrogenComplete(mol)               # make all implicit hydrogens explicit
    Chem.perceiveHybridizationStates(mol, False) # perceive atom hybridization states and set corresponding property for all atoms
    Chem.perceiveSSSR(mol, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setRingFlags(mol, False)                # perceive cycles and set corresponding atom and bond properties
    Chem.setAromaticityFlags(mol, False)         # perceive aromaticity and set corresponding atom and bond properties
  
    ForceField.perceiveMMFF94AromaticRings(mol, False)        # perceive aromatic rings according to the MMFF94 aroamticity model and store data as Chem.MolecularGraph property
    ForceField.assignMMFF94AtomTypes(mol, False, False)       # perceive MMFF94 atom types (tolerant mode) set corresponding property for all atoms
    ForceField.assignMMFF94BondTypeIndices(mol, False, False) # perceive MMFF94 bond types (tolerant mode) set corresponding property for all bonds
    ForceField.calcMMFF94AtomCharges(mol, False, False)       # calculate MMFF94 atom charges (tolerant mode) set corresponding property for all atoms

    print('- MMFF94 partial charges')
    
    for atom in mol.atoms:
        print('Atom #%s: %s' % (str(atom.getIndex()), str(ForceField.getMMFF94Charge(atom))))

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
                calcAndOutputCharges(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed:\n' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed:\n' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
