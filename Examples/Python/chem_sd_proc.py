#!/bin/env python

##
# chem_sd_proc.py 
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


# function called for each read molecule
def procMolecule(mol: Chem.Molecule) -> None: 
    if not Chem.hasStructureData(mol):        # is a structure data property available?
        print('Error: structure data not available for molecule \'%s\'!' % Chem.getName(mol))
        return

    struct_data = Chem.getStructureData(mol)  # retrieve structure data
    
    print('Structure data (%s entries) for molecule \'%s\':\n' % (str(len(struct_data)), Chem.getName(mol)))

    i = 1
    
    for entry in struct_data:                 # iterate of structure data entries consisting of a header line and the actual data
        print('----- Entry %s -----' % str(i))
        print('Header: ' + entry.header)
        print('Data: ' + entry.data)

        i += 1
    
def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input file>' % sys.argv[0])

    # create reader for MDL SD-files
    reader = Chem.FileSDFMoleculeReader(sys.argv[1])
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol): 
            try:
                procMolecule(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed:\n' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed:\n' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
