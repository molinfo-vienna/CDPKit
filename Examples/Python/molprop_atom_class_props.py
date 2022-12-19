#!/bin/env python

##
# molprop_atom_class_props.py 
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
def procMolecule(molgraph: Chem.MolecularGraph) -> None:
    Chem.calcImplicitHydrogenCounts(molgraph, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
    Chem.perceiveHybridizationStates(molgraph, False) # perceive atom hybridization states and set corresponding property for all atoms
    Chem.perceiveSSSR(molgraph, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setRingFlags(molgraph, False)                # perceive cycles and set corresponding atom and bond properties
    Chem.setAromaticityFlags(molgraph, False)         # perceive aromaticity and set corresponding atom and bond properties

    for atom in molgraph.atoms:
        print('- Atom #%s' % str(molgraph.getAtomIndex(atom)))
        print('\tIs std. hydrogen: %s' % str(MolProp.isOrdinaryHydrogen(atom, molgraph)))
        print('\tIs heavy atom: %s' % str(MolProp.isHeavy(atom)))
        print('\tIs unsaturated: %s' % str(MolProp.isUnsaturated(atom, molgraph)))
        print('\tIs hydrogen acceptor: %s' % str(MolProp.isHydrogenAcceptor(atom, molgraph)))
        print('\tIs hydrogen donor: %s' % str(MolProp.isHydrogenDonor(atom, molgraph)))
        print('\tIs carbonyl carbon: %s' % str(MolProp.isCarbonylLikeAtom(atom, molgraph, True, True)))
        print('\tIs amide carbon: %s' % str(MolProp.isAmideCenterAtom(atom, molgraph, True, True)))
        print('\tIs amide nitrogen: %s' % str(MolProp.isAmideNitrogen(atom, molgraph, True, True)))
        print('\tIs invertible nitrogen: %s' % str(MolProp.isInvertibleNitrogen(atom, molgraph)))
        print('\tIs planar nitrogen: %s' % str(MolProp.isPlanarNitrogen(atom, molgraph)))
        
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

    # if the input molecules are expected to be in a specific format, a reader for this format could be create directly, e.g.
    # reader = Chem.FileSDFMoleculeReader(sys.argv[1])
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

