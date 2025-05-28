##
# print_atom_con_props.py 
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
import CDPL.MolProp as MolProp


# outputs the corresponding properties of each atom of the provided molecular graph
def outputProperties(molgraph: Chem.MolecularGraph) -> None:
    Chem.calcBasicProperties(molgraph, False)       # calculate basic molecular properties (if not yet done)
  
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
    
    for atom in molgraph.atoms:
        print('- Atom #%s' % str(molgraph.getAtomIndex(atom)))
        print('\tNum. connected std. hydrogens (incl. impl. H): %s' % str(MolProp.getOrdinaryHydrogenCount(atom, molgraph)))
        print('\tNum. connected carbon atoms: %s' % str(MolProp.getExplicitAtomCount(atom, molgraph, Chem.AtomType.C)))
        print('\tNum. connected heteroatoms: %s' % str(MolProp.getExplicitAtomCount(atom, molgraph, Chem.AtomType.HET, False)))
        print('\tNum. connected halogens: %s' % str(MolProp.getExplicitAtomCount(atom, molgraph, Chem.AtomType.X, False)))
        print('\tNum. connected heavy atoms: %s' % str(MolProp.getHeavyAtomCount(atom, molgraph)))
        print('\tNum. connected chain atoms (excl. impl. H): %s' % str(MolProp.getExplicitChainAtomCount(atom, molgraph)))
        print('\tNum. connected chain atoms (incl. impl. H): %s' % str(MolProp.getChainAtomCount(atom, molgraph)))
        print('\tNum. connected ring atoms: %s' % str(MolProp.getRingAtomCount(atom, molgraph)))
        print('\tNum. connected aromatic atoms: %s' % str(MolProp.getAromaticAtomCount(atom, molgraph)))
        print('\tNum. incident bonds (excl. impl. H): %s' % str(MolProp.getExplicitBondCount(atom, molgraph)))
        print('\tNum. incident bonds (incl. impl. H): %s' % str(MolProp.getBondCount(atom, molgraph)))
        print('\tNum. incident single bonds (excl. impl. H): %s' % str(MolProp.getExplicitBondCount(atom, molgraph, 1)))
        print('\tNum. incident single bonds (incl. impl. H): %s' % str(MolProp.getBondCount(atom, molgraph, 1)))
        print('\tNum. incident double bonds: %s' % str(MolProp.getBondCount(atom, molgraph, 2)))
        print('\tNum. incident triple bonds: %s' % str(MolProp.getBondCount(atom, molgraph, 3)))
        print('\tNum. incident chain bonds (excl. impl. H): %s' % str(MolProp.getExplicitChainBondCount(atom, molgraph)))
        print('\tNum. incident chain bonds (incl. impl. H): %s' % str(MolProp.getChainBondCount(atom, molgraph)))
        print('\tNum. incident ring bonds (incl. impl. H): %s' % str(MolProp.getRingBondCount(atom, molgraph)))
        print('\tNum. incident aromatic bonds (incl. impl. H): %s' % str(MolProp.getAromaticBondCount(atom, molgraph)))
        print('\tNum. incident heavy atom bonds (incl. impl. H): %s' % str(MolProp.getHeavyBondCount(atom, molgraph)))
        print('\tNum. incident rotatable bonds (incl. impl. H): %s' % str(MolProp.getRotatableBondCount(atom, molgraph, False, False)))
        print('\tValence (excl. impl. H): %s' % str(MolProp.calcExplicitValence(atom, molgraph)))
        print('\tValence (incl. impl. H): %s' % str(MolProp.calcValence(atom, molgraph)))
        print('\tSteric number: %s' % str(MolProp.calcStericNumber(atom, molgraph)))
        print('\tVSEPR coordination geometry: %s' % vsepr_geom_str[MolProp.getVSEPRCoordinationGeometry(atom, molgraph)])

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
