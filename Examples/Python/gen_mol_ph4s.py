##
# gen_mol_ph4s.py 
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
import argparse

import CDPL.Chem as Chem
import CDPL.Pharm as Pharm


# generates the pharmacophore of the argument molecule using
# atom coordinates of the specified conformation
def genPharmacophore(mol: Chem.Molecule, conf_idx: int) -> Pharm.Pharmacophore:
    if conf_idx < 1:                                    # for a new molecule
        Pharm.prepareForPharmacophoreGeneration(mol)    # first call utility function preparing the molecule for pharmacophore generation
        
    ph4_gen = Pharm.DefaultPharmacophoreGenerator()     # create an instance of the pharmacophore generator default implementation
    ph4 = Pharm.BasicPharmacophore()                    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4_name = Chem.getName(mol)                        # use the name of the input molecule as pharmacophore name
    
    if conf_idx >= 0:                                   # if mol is a multi-conf. molecule use atom 3D coordinates of the specified conf.
        ph4_gen.setAtom3DCoordinatesFunction(Chem.AtomConformer3DCoordinatesFunctor(conf_idx))
        ph4_name += '#' + str(conf_idx)                 # and append conformer index to the pharmacophore name
        
    ph4_gen.generate(mol, ph4)          # generate the pharmacophore
    Pharm.setName(ph4, ph4_name)        # set the pharmacophore name

    return ph4

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates pharmacophores of the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Pharmacophore output file')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    return parser.parse_args()

def main() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the generated pharmacophores (format specified by file extension)
    writer = Pharm.FeatureContainerWriter(args.out_file) 
     
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
                print('- Generating pharmacophore of molecule %s...' % mol_id)

            num_confs = Chem.getNumConformations(mol)
            start_conf_idx = 0

            if num_confs == 0:      # test if molecule has conformations
                start_conf_idx = -1 # if not, make sure conformer loop body gets executed

            try:
                for conf_idx in range(start_conf_idx, num_confs): # for each conformer
                    ph4 = genPharmacophore(mol, conf_idx)         # generate pharmacophore

                    if not args.quiet:
                        print(' -> Generated %s features: %s' % (str(ph4.numFeatures), Pharm.generateFeatureTypeHistogramString(ph4)))
                     
                    if not writer.write(ph4):   # output pharmacophore
                        sys.exit('Error: writing generated pharmacophore %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: pharmacophore generation or output for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
