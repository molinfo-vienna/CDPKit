#!/bin/env python

##
# gen_fame_fp.py 
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
import numpy

import CDPL.Chem as Chem


# generates the FAME descriptor for a given atom of the provided molecular graph
def genFAMEDescriptor(ctr_atom: Chem.Atom, molgraph: Chem.MolecularGraph, radius: int) -> numpy.array:
    env = Chem.Fragment()                                                      # for storing of extracted environment atoms
    descr = numpy.zeros((Chem.SybylAtomType.MAX_TYPE + 1) * (radius + 1))
    
    Chem.getEnvironment(ctr_atom, molgraph, radius, env)                       # extract environment of center atom reaching
                                                                               # out up to 'radius' bonds
    for atom in env.atoms:                                                     # iterate over extracted environment atoms
        sybyl_type = Chem.getSybylType(atom)                                   # retrieve Sybyl type of environment atom
        top_dist = Chem.getTopologicalDistance(ctr_atom, atom, molgraph)       # get top. distance between center atom and environment atom
        descr[top_dist * (Chem.SybylAtomType.MAX_TYPE + 1) + sybyl_type] += 1  # instead of 1 (= Sybyl type presence) also any other numeric atom
                                                                               # property could be summed up here
    return descr
        
# function called for each read molecule
def procMolecule(molgraph: Chem.MolecularGraph) -> None: 
    Chem.calcBasicProperties(molgraph, False)            # calculate basic molecular properties (if not yet done)
    Chem.perceiveSybylAtomTypes(molgraph, False)         # perceive Sybyl atom types and set corresponding property for all atoms
    Chem.calcTopologicalDistanceMatrix(molgraph, False)  # calculate topological distance matrix and store as Chem.MolecularGraph property
   
    for atom in molgraph.atoms:
        descr = genFAMEDescriptor(atom, molgraph, 5)     # generate atom environment descriptor using a radius of five bonds

        print(descr)

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
                procMolecule(mol)
            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
