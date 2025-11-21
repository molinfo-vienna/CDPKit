##
# align_mols_by_shape.py 
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
import CDPL.Shape as Shape
import CDPL.Pharm as Pharm


# reads and returns the specified alignment reference molecule
def readRefMolecule(filename: str) -> Chem.Molecule:
    # create molecule reader instance
    reader = Chem.MoleculeReader(filename)

    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()

    try:
        if not reader.read(mol): # read reference molecule
            sys.exit('Error: reading reference molecule failed')
                
    except Exception as e:       # handle exception raised in case of severe read errors
        sys.exit('Error: reading reference molecule failed:\n' + str(e))

    return mol

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Aligns a set of input molecules onto a given reference molecule by means of Gaussian shape alignment.')

    parser.add_argument('-r',
                        dest='ref_mol_file',
                        required=True,
                        metavar='<file>',
                        help='Reference molecule input file')
    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Aligned molecule output file')
    parser.add_argument('-s',
                        dest='scoring_func',
                        required=False,
                        default='ShapeTanimotoScore',
                        metavar='<string>',
                        help='Scoring function to use for assessing computed alignments (default: ShapeTanimotoScore, valid other \
                        values: TotalOverlapTanimotoScore, ColorTanimotoScore, TanimotoComboScore, TotalOverlapTverskyScore, \
                        ShapeTverskyScore, ColorTverskyScore, TverskyComboScore, ReferenceTotalOverlapTverskyScore, \
                        ReferenceShapeTverskyScore, ReferenceColorTverskyScore, ReferenceTverskyComboScore, \
                        AlignedTotalOverlapTverskyScore, AlignedShapeTverskyScore, AlignedColorTverskyScore, \
                        AlignedTverskyComboScore)')
    parser.add_argument('-p',
                        dest='inc_ph4_ftrs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Regard pharmacophoric (= color) features (default: false)')
    parser.add_argument('-f',
                        dest='fast',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Perform a fast but less accurate shape alignment (default: false)')
    parser.add_argument('-m',
                        dest='max_order',
                        required=False,
                        metavar='<integer>',
                        default=4,
                        help='Maximum order of the Gaussian sphere overlap products (only effective in absence of option -f, default: 4)',
                        type=int)
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
  
    return parser.parse_args()

def main() -> None:
    args = parseArgs()

    # read the reference molecule
    ref_mol = readRefMolecule(args.ref_mol_file) 

    # if necessary, prepare the ref. molecule for pharm. feature perception
    if args.inc_ph4_ftrs:
        Pharm.prepareForPharmacophoreGeneration(ref_mol)
    
    # create reader for input molecules (format specified by file extension)
    mol_reader = Chem.MoleculeReader(args.in_file) 

    Chem.setMultiConfImportParameter(mol_reader, False) # treat input molecule conformers as individual molecules
    
    # create writer for aligned molecules (format specified by file extension)
    mol_writer = Chem.MolecularGraphWriter(args.out_file) 

    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()

    # create an instance of the specified alignment scoring function
    scoring_func = getattr(Shape, args.scoring_func)()

    # create an instance of the class implementing the Gaussian shape alignment algorithm
    if args.fast:
        almnt = Shape.FastGaussianShapeAlignment()
    else:
        almnt = Shape.GaussianShapeAlignment()

         # check and apply value of the -d option
        if args.max_order <= 0:
            sys.exit('Error: -d argument value has to be > 0')
            
        almnt.setMaxOrder(args.max_order)

    # set scoring functions
    almnt.setScoringFunction(scoring_func)
    almnt.setResultCompareFunction(scoring_func)
    
    # create and setup an instance of the class implementing Gaussian shape generation from molecular graphs
    shape_gen = Shape.GaussianShapeGenerator()

    shape_gen.generatePharmacophoreShape(args.inc_ph4_ftrs) # apply -p option
    shape_gen.multiConformerMode(False)                     # only one shape per molecule (input molecule conformers are read separately)

    # set the alignment reference shape
    almnt.addReferenceShapes(shape_gen.generate(ref_mol))
    
    # read and process input molecules one after the other until the end of input has been reached
    try:
        i = 1

        while mol_reader.read(mol):
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty
            else:
                mol_id = f'\'{mol_id}\' (#{i})'

            if not args.quiet:
                print(f'- Aligning molecule {mol_id}...')

            try:
                # if necessary, prepare the molecule to align for pharm. feature perception
                if args.inc_ph4_ftrs:
                    Pharm.prepareForPharmacophoreGeneration(mol)

                mol_shape = shape_gen.generate(mol) # generate Gaussian shape of input molecule to align

                if not almnt.align(mol_shape):      # perform the shape alignment and check for errors
                    if not args.quiet:
                        print(' -> alignment failed')
                        continue
                
                if Chem.hasStructureData(mol):      # get existing structure data if available
                    struct_data = Chem.getStructureData(mol)
                else:                               # otherwise create and set new structure data
                    struct_data = Chem.StringDataBlock()

                    Chem.setStructureData(mol, struct_data)

                # add alignment score entry to struct. data
                struct_data.addEntry(f'<{args.scoring_func}>', format(almnt[0].getScore(), '.4f')) 

                if not args.quiet:
                    print(f' -> computed alignment with score {almnt[0].getScore()}')

                # transform input molecule coordinates according to the computed shape alignment
                Chem.transform3DCoordinates(mol, almnt[0].getTransform())
                 
                try:
                    if not mol_writer.write(mol): # output the alignment pose of the molecule
                        sys.exit(f'Error: writing alignment pose of molecule {mol_id} failed')

                except Exception as e:            # handle exception raised in case of severe write errors
                    sys.exit(f'Error: writing alignment pose of molecule {mol_id} failed:\n{str(e)}')

            except Exception as e:
                sys.exit(f'Error: shape alignment of molecule {mol_id} failed:\n{str(e)}')

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading input molecule failed:\n{str(e)}')

    mol_writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
