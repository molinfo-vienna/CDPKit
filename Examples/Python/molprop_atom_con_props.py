#!/bin/env python

##
# molprop_atom_con_props.py 
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
    Chem.calcImplicitHydrogenCounts(mol, False)  # calculate implicit hydrogen counts and set corresponding property for all atoms
    Chem.perceiveHybridizationStates(mol, False) # perceive atom hybridization and set corresponding property for all atoms
    Chem.perceiveSSSR(mol, False)                # perceive smallest set of smallest rings and store as Chem.MolecularGraph property
    Chem.setRingFlags(mol, False)                # perceive cycles and set corresponding atom and bond properties
    Chem.setAromaticityFlags(mol, False)         # perceive aromaticity and set corresponding atom and bond properties

    vsepr_geom_str = { MolProp.CoordinationGeometry.UNDEF                  : 'UNDEF',
	               MolProp.CoordinationGeometry.NONE                   : 'NONE',
	               MolProp.CoordinationGeometry.LINEAR                 : 'LINEAR',
	               MolProp.CoordinationGeometry.TRIGONAL_PLANAR        : 'TRIGONAL_PLANAR',
	               MolProp.CoordinationGeometry.TETRAHEDRAL            : 'TETRAHEDRAL',
	               MolProp.CoordinationGeometry.TRIGONAL_BIPYRAMIDAL   : 'TRIGONAL_BIPYRAMIDAL',
	               MolProp.CoordinationGeometry.OCTAHEDRAL             : 'OCTAHEDRAL',
	               MolProp.CoordinationGeometry.PENTAGONAL_BIPYRAMIDAL : 'PENTAGONAL_BIPYRAMIDAL',
	               MolProp.CoordinationGeometry.SQUARE_ANTIPRISMATIC   : 'SQUARE_ANTIPRISMATIC',
	               MolProp.CoordinationGeometry.BENT                   : 'BENT',
	               MolProp.CoordinationGeometry.TRIGONAL_PYRAMIDAL     : 'TRIGONAL_PYRAMIDAL',
	               MolProp.CoordinationGeometry.SQUARE_PLANAR          : 'SQUARE_PLANAR',
	               MolProp.CoordinationGeometry.SQUARE_PYRAMIDAL       : 'SQUARE_PYRAMIDAL',
	               MolProp.CoordinationGeometry.T_SHAPED               : 'T_SHAPED',
	               MolProp.CoordinationGeometry.SEESAW                 : 'SEESAW',
	               MolProp.CoordinationGeometry.PENTAGONAL_PYRAMIDAL   : 'PENTAGONAL_PYRAMIDAL',
	               MolProp.CoordinationGeometry.PENTAGONAL_PLANAR      : 'PENTAGONAL_PLANAR' }
    
    for atom in mol.atoms:
        print('- Atom #%s' % str(atom.getIndex()))
        print('\tNum. connected std. hydrogens (incl. impl. H): %s' % str(MolProp.getOrdinaryHydrogenCount(atom, mol)))
        print('\tNum. connected carbon atoms: %s' % str(MolProp.getExplicitAtomCount(atom, mol, Chem.AtomType.C)))
        print('\tNum. connected heteroatoms: %s' % str(MolProp.getExplicitAtomCount(atom, mol, Chem.AtomType.HET, False)))
        print('\tNum. connected halogens: %s' % str(MolProp.getExplicitAtomCount(atom, mol, Chem.AtomType.X, False)))
        print('\tNum. connected heavy atoms: %s' % str(MolProp.getHeavyAtomCount(atom, mol)))
        print('\tNum. connected chain atoms (excl. impl. H): %s' % str(MolProp.getExplicitChainAtomCount(atom, mol)))
        print('\tNum. connected chain atoms (incl. impl. H): %s' % str(MolProp.getChainAtomCount(atom, mol)))
        print('\tNum. connected ring atoms: %s' % str(MolProp.getRingAtomCount(atom, mol)))
        print('\tNum. connected aromatic atoms: %s' % str(MolProp.getAromaticAtomCount(atom, mol)))
        print('\tNum. incident bonds (excl. impl. H): %s' % str(MolProp.getExplicitBondCount(atom, mol)))
        print('\tNum. incident bonds (incl. impl. H): %s' % str(MolProp.getBondCount(atom, mol)))
        print('\tNum. incident single bonds (excl. impl. H): %s' % str(MolProp.getExplicitBondCount(atom, mol, 1)))
        print('\tNum. incident single bonds (incl. impl. H): %s' % str(MolProp.getBondCount(atom, mol, 1)))
        print('\tNum. incident double bonds: %s' % str(MolProp.getBondCount(atom, mol, 2)))
        print('\tNum. incident triple bonds: %s' % str(MolProp.getBondCount(atom, mol, 3)))
        print('\tNum. incident chain bonds (excl. impl. H): %s' % str(MolProp.getExplicitChainBondCount(atom, mol)))
        print('\tNum. incident chain bonds (incl. impl. H): %s' % str(MolProp.getChainBondCount(atom, mol)))
        print('\tNum. incident ring bonds (incl. impl. H): %s' % str(MolProp.getRingBondCount(atom, mol)))
        print('\tNum. incident aromatic bonds (incl. impl. H): %s' % str(MolProp.getAromaticBondCount(atom, mol)))
        print('\tNum. incident heavy atom bonds (incl. impl. H): %s' % str(MolProp.getHeavyBondCount(atom, mol)))
        print('\tNum. incident rotatable bonds (incl. impl. H): %s' % str(MolProp.getRotatableBondCount(atom, mol, False, False)))
        print('\tValence (excl. impl. H): %s' % str(MolProp.calcExplicitValence(atom, mol)))
        print('\tValence (incl. impl. H): %s' % str(MolProp.calcValence(atom, mol)))
        print('\tSteric number: %s' % str(MolProp.calcStericNumber(atom, mol)))
        print('\tVSEPR coordination geometry: %s' % vsepr_geom_str[MolProp.getVSEPRCoordinationGeometry(atom, mol)])
        
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

