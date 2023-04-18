#!/bin/env python

##
# pharm_align_mols.py 
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
import argparse

import CDPL.Chem as Chem
import CDPL.Pharm as Pharm
import CDPL.Math as Math

    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Aligns a set of input molecules onto a given reference pharmacophore.')

    parser.add_argument('-r',
                        dest='ref_ph4_file',
                        required=True,
                        metavar='<file>',
                        help='Reference pharmacophore input file (*.pml, *.cdf)')
    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Aligned molecule output file (*.pml, *.cdf)')
    parser.add_argument('-n',
                        dest='num_out_almnts',
                        required=False,
                        metavar='<integer>',
                        default=1,
                        help='Number of top-ranked alignment solutions to output per molecule (default: best alignment solution only)',
                        type=int)
    parser.add_argument('-x',
                        dest='exhaustive',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Perform an exhaustive alignment search (default: false)')
    parser.add_argument('-d',
                        dest='min_pose_rmsd',
                        required=False,
                        metavar='<float>',
                        default=0.0,
                        help='Minimum required RMSD between two consecutively output molecule alignment poses (default: 0.0)',
                        type=float)
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    parser.add_argument('-p',
                        dest='pos_only',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Ignore feature orientations, feature position matching only (default: false)')
    parse_args = parser.parse_args()

    return parse_args

# reads and returns the specified alignment reference pharmacophore
def readRefPharmacophore(filename: str) -> Pharm.Pharmacophore:
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine pharmacophore input file format (file extension missing)')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Pharm.PharmacophoreIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:
        sys.exit('Error: unsupported pharmacophore input file format \'%s\'' % name_and_ext[1])

    # create reader instance
    reader = ipt_handler.createReader(filename)

    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()

    try:
        if not reader.read(ph4): # read reference pharmacophore
            sys.exit('Error: reading reference pharmacophore failed')
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading reference pharmacophore failed: ' + str(e))

    return ph4

# returns a Chem.MoleculeReader instance for the specifed input molecule file format
def getMolReaderByFileExt(filename: str) -> Chem.MoleculeReader:
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine molecule input file format (file extension missing)')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Chem.MoleculeIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:
        sys.exit('Error: unsupported molecule input file format \'%s\'' % name_and_ext[1])

    # create and return file reader instance
    return ipt_handler.createReader(filename)

# returns a Chem.MolecularGraphWriter instance for the specifed outut molecule file format
def getMolWriterByFileExt(filename: str) -> Chem.MolecularGraphWriter:
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine molecule output file format (file extension missing)')

    # get output handler for the format specified by the output file's extension
    opt_handler = Chem.MolecularGraphIOManager.getOutputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not opt_handler:
        sys.exit('Error: unsupported molecule output file format \'%s\'' % name_and_ext[1])

    # create and return file writer instance
    return opt_handler.createWriter(filename)

# generates and returns the pharmacophore of the specified molecule
def genPharmacophore(mol: Chem.Molecule) -> Pharm.Pharmacophore:
    Pharm.prepareForPharmacophoreGeneration(mol)       # call utility function preparing the molecule for pharmacophore generation
        
    ph4_gen = Pharm.DefaultPharmacophoreGenerator()    # create an instance of the pharmacophore generator default implementation
    ph4 = Pharm.BasicPharmacophore()                   # create an instance of the default implementation of the Pharm.Pharmacophore interface

    ph4_gen.generate(mol, ph4)                         # generate the pharmacophore

    return ph4

# remove feature orientation informations and set the feature geometry to Pharm.FeatureGeometry.SPHERE
def clearFeatureOrientations(ph4: Pharm.BasicPharmacophore) -> None:
    for ftr in ph4:
        Pharm.clearOrientation(ftr)
        Pharm.setGeometry(ftr, Pharm.FeatureGeometry.SPHERE)

def main() -> None:
    args = parseArgs()

    ref_ph4 = readRefPharmacophore(args.ref_ph4_file) # read the reference pharmacophore

    # if the input molecules are expected to be in a specific format, a reader for this format could be created directly, e.g.
    # reader = Chem.FileSDFMoleculeReader(args.in_file)
    mol_reader = getMolReaderByFileExt(args.in_file) 

    Chem.setMultiConfImportParameter(mol_reader, False) # treat conformers as individual molecules
    
    # if the output molecules have to be stored in a specific format, a writer for this format could be created directly, e.g.
    # writer = Chem.FileSDFMolecularGraphWriter(args.out_file)
    mol_writer = getMolWriterByFileExt(args.out_file) 

    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()

    # create instance of class implementing the pharmacophore alignment algorithm
    almnt = Pharm.PharmacophoreAlignment(True) # True = aligned features have to be within the tolerance spheres of the ref. features

    if args.pos_only:                          # clear feature orientation information
        clearFeatureOrientations(ref_ph4)
    
    almnt.addFeatures(ref_ph4, True)               # set reference features (True = first set = reference)
    almnt.performExhaustiveSearch(args.exhaustive) # set minimum number of top. mapped feature pairs
    
    # create pharmacophore fit score calculator instance
    almnt_score = Pharm.PharmacophoreFitScore()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        i = 1

        while mol_reader.read(mol):
            # compose a simple molecule identifier
            mol_id = Chem.getName(mol).strip() 

            if mol_id == '':
                mol_id = '#' + str(i)  # fallback if name is empty
            else:
                mol_id = '\'%s\' (#%s)' % (mol_id, str(i))

            if not args.quiet:
                print('- Aligning molecule %s...' % mol_id)

            try:
                mol_ph4 = genPharmacophore(mol)    # generate input molecule pharmacophore

                if args.pos_only:                  # clear feature orientation information
                    clearFeatureOrientations(mol_ph4)

                almnt.clearEntities(False)         # clear features of previously aligned pharmacophore
                almnt.addFeatures(mol_ph4, False)  # specify features of the pharmacophore to align

                almnt_solutions = []               # stores the found alignment solutions
                
                while almnt.nextAlignment():                                     # iterate over all alignment solutions that can be found
                    score = almnt_score(ref_ph4, mol_ph4, almnt.getTransform())  # calculate alignment score
                    xform = Math.Matrix4D(almnt.getTransform())                  # make a copy of the alignment transformation (mol. ph4 -> ref. ph4) 

                    almnt_solutions.append((score, xform))

                if not args.quiet:
                    print(' -> Found %s alignment solutions' % str(len(almnt_solutions)))
                
                saved_coords = Math.Vector3DArray()      # create data structure for storing 3D coordinates

                Chem.get3DCoordinates(mol, saved_coords) # save the original atom coordinates

                struct_data = None

                if Chem.hasStructureData(mol):           # get existing structure data if available
                    struct_data = Chem.getStructureData(mol)
                else:                                    # otherwise create and set new structure data
                    struct_data = Chem.StringDataBlock()

                    Chem.setStructureData(mol, strut)

                # add alignment score entry to struct. data
                struct_data.addEntry('<PharmFitScore>', '') 
                
                output_cnt = 0
                last_pose = None
                
                # order solutions by desc. alignment score
                almnt_solutions = sorted(almnt_solutions, key=lambda entry: entry[0], reverse=True)

                # output molecule alignment poses until the max. number of best output solutions has been reached
                for solution in almnt_solutions:
                    if output_cnt == args.num_out_almnts:
                        break

                    curr_pose = Math.Vector3DArray(saved_coords)

                    Math.transform(curr_pose, solution[1])  # transform atom coordinates

                    # check whether the current pose is 'different enough' from
                    # the last pose to qualify for output
                    if args.min_pose_rmsd > 0.0 and last_pose and Math.calcRMSD(last_pose, curr_pose) < args.min_pose_rmsd:
                        continue

                    # apply the transformed atom coordinates
                    Chem.set3DCoordinates(mol, curr_pose)  

                    # store alignment score in the struct. data entry
                    struct_data[len(struct_data) - 1].setData(format(solution[0], '.4f'))     
                    
                    try:
                        if not mol_writer.write(mol): # output the alignment pose of the molecule
                            sys.exit('Error: writing alignment pose of molecule %s failed: %s' % (mol_id, str(e)))

                    except Exception as e: # handle exception raised in case of severe write errors
                        sys.exit('Error: writing alignment pose of molecule %s failed: %s' % (mol_id, str(e)))

                    last_pose = curr_pose
                    output_cnt += 1

                if not args.quiet:
                    print(' -> %s alignment poses saved' % str(output_cnt))

            except Exception as e:
                sys.exit('Error: pharmacophore alignment of molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading input molecule failed: ' + str(e))

    mol_writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
