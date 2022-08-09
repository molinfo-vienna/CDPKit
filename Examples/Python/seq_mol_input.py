#!/bin/env python

##
# seq_mol_input.py 
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

import CDPL.Chem as Chem


# function called for each read molecule
def procMolecule(mol: Chem.Molecule) -> None: 
    print('Processing molecule consisting of {!s} atoms and {!s} bonds'.format(mol.numAtoms, mol.numBonds))

def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input SD-file>' % sys.argv[0])

    # create a reader instance for SD-files providing the filename as constructor argument
    reader = Chem.FileSDFMoleculeReader(sys.argv[1])

    # create an instance of the default implementation of the Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol): 
            procMolecule(mol)
    except: # handle exception raised in case of severe read errors
        print('Error while reading molecule!', file=sys.stderr)
        return
        
if __name__ == '__main__':
    main()
