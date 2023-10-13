#!/bin/env python

##
# sd_proc.py 
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


# retrieves and prints the MDL structure data of the given molecule
def printStructureData(mol: Chem.Molecule) -> None: 
    if not Chem.hasStructureData(mol):        # is a structure data property available?
        print('Error: no structure data available for molecule \'%s\'' % Chem.getName(mol))
        return

    struct_data = Chem.getStructureData(mol)  # retrieve structure data
    
    print('Structure data (%s entries) of molecule \'%s\':\n' % (str(len(struct_data)), Chem.getName(mol)))

    i = 1
    
    for entry in struct_data:                 # iterate of structure data entries consisting of a header line and the actual data
        print('----- Entry %s -----' % str(i))
        print('Header: ' + entry.header)
        print('Data: ' + entry.data)

        i += 1
    
def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input SD-file>' % sys.argv[0])

    # create reader for MDL SD-files
    reader = Chem.FileSDFMoleculeReader(sys.argv[1])
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol): 
            try:
                printStructureData(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
