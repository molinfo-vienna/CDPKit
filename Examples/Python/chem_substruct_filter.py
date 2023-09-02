#!/bin/env python

##
# chem_substruct_filter.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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
import argparse

import CDPL.Chem as Chem


def filterMolecules() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the output of matching molecules (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    try:
        sub_srch_ptn = Chem.parseSMARTS(args.smarts_ptn)

        Chem.initSubstructureSearchQuery(sub_srch_ptn, False)

    except Exception as e:
        sys.exit('Error: parsing of SMARTS pattern failed: %s' % str(e))

    # create and initialize an instance of the class Chem.SubstructureSearch that
    # implements the substructure searching algorithm
    substr_srch = Chem.SubstructureSearch(sub_srch_ptn)

    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()
    i = 1
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i) # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            if not args.quiet:
                print('- Searching for a matching substructure in molecule %s...' % mol_id)

            try:
                Chem.initSubstructureSearchTarget(mol, False)

                if substr_srch.mappingExists(mol):
                    if not args.quiet:
                        print(' -> substructure found, forwarding molecule to output file')

                    # output the matched molecule                 
                    if not writer.write(mol):   
                        sys.exit('Error: output of molecule failed')

                elif not args.quiet: 
                    print(' -> substructure not found')
                        
            except Exception as e:
                sys.exit('Error: substructure search or output of molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Writes input molecules that match the specified SMARTS substructure pattern to an output file.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule output file')
    parser.add_argument('-p',
                        dest='smarts_ptn',
                        required=True,
                        metavar='<SMARTS>',
                        help='SMARTS pattern describing the substructure to search for')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    return parser.parse_args()

if __name__ == '__main__':
    filterMolecules()