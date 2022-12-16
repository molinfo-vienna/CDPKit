#!/bin/env python

##
# molprop_atom_physchem_props.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2022 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
import CDPL.MolProp as MolProp


# function called for read molecule
def procMolecule(mol: Chem.MolecularGraph) -> None:
    Chem.calcImplicitHydrogenCounts(mol, False)    # calculate implicit hydrogen counts and set corresponding property for all atoms
    Chem.perceiveHybridizationStates(mol, False)   # perceive atom hybridization and set corresponding property for all atoms
    Chem.perceiveSSSR(mol, False)                  # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setRingFlags(mol, False)                  # perceive cycles and set corresponding atom and bond properties
    Chem.setAromaticityFlags(mol, False)           # perceive aromaticity and set corresponding atom and bond properties
    Chem.calcTopologicalDistanceMatrix(mol, False) # calculate topological distance matrix and store as Chem.MolecularGraph property
                                                   # (required for effective polarizability calculations)
    
    for atom in mol.atoms:
        print('- Atom #%s' % str(atom.getIndex()))
        print('\tHybrid polarizability: %s' % str(MolProp.getHybridPolarizability(atom, mol)))
        print('\tEffective polarizability: %s' % str(MolProp.calcEffectivePolarizability(atom, mol)))
        
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
    
def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input file>' % sys.argv[0])

    # if input are expected to be in a specific format, a reader for the specific format could be create directly,
    # e.g. reader = Chem.FileSDFMoleculeReader(sys.argv[1])
    reader = getReaderByFileExt(sys.argv[1]) 
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        if reader.read(mol):
            try:
                procMolecule(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed:\n' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed:\n' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()

