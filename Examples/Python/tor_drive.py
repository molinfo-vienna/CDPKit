#!/bin/env python

##
# tor_drive.py 
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
import CDPL.ConfGen as ConfGen
import CDPL.Util as Util
import CDPL.Math as Math


# generates a conformer ensemble by performing torsion driving on the argument molecule
# using the provided ConfGen.TorsionDriver instance
def performTorsionDriving(mol: Chem.Molecule, tor_driver: ConfGen.TorsionDriver, sub_srch: Chem.SubstructureSearch, args: argparse.Namespace) -> (int, int):
    # check if a fixed substructure pattern has been specified and if there are matches
    if sub_srch != None and sub_srch.findMappings(mol): 
        if not args.quiet:
            print(' -> Found %s fixed substructure pattern match(es)' % str(sub_srch.numMappings))
            
        fixed_substruct = Chem.Fragment()  # will store atoms and bonds of the matched substructure(s)

        # extract all bonds (and associated atoms) of the substructure(s) matched by the pattern
        for mapping in sub_srch:
            for bond in mapping.bondMapping.getValues():
                fixed_substruct.addBond(bond)

        # bond mask for the torsion driver specifying rotatable bonds
        rot_bonds = Util.BitSet(mol.numBonds)

        # in case of a fixed substructure, rotatable bonds have to be identified manually
        for bond in mol.bonds:
            if fixed_substruct.containsBond(bond): # if bond is part of the fixed substruct. -> ignore
                continue
            
            if ConfGen.isRotatableBond(bond, mol, args.rot_term_het_grps):
                rot_bonds.set(bond.getIndex())

        status = tor_driver.setup(mol, rot_bonds)  # setup torsion driver

    else: # without a fixed substructure, let the torsion driver identify rotatable bonds
        if sub_srch != None and not args.quiet:
            print(' -> No fixed substructure pattern matches found!')

        fixed_substruct = None
        status = tor_driver.setup(mol)             # setup torsion driver

    # check if the torsion driver setup was successful
    if status != ConfGen.ReturnCode.SUCCESS: 
        return (status, 0) 

    input_conf = Math.Vector3DArray()

    # get input conformation
    Chem.get3DCoordinates(mol, input_conf, Chem.Atom3DCoordinatesFunctor()) 

    # use input conformation for tor. driving
    tor_driver.addInputCoordinates(input_conf) 

    # perform torsion driving
    status = tor_driver.generateConformers() 

    # check if torsion driving was successful
    if status != ConfGen.ReturnCode.SUCCESS: 
         return (status, 0)
     
    num_confs = tor_driver.numConformers  # get num gen. conformers
    
    if args.max_confs > 0:              
        num_confs = min(args.max_confs, num_confs) # clamp to spec. max. num output confs

    output_confs = []

    # fetch generated confs. up to max. count
    for i in range(num_confs): 
        output_confs.append(tor_driver.getConformer(i)) 

    # if desired, align output conformers
    if args.align_confs:
        if fixed_substruct != None:
            # align on fixed substructure
            alignConformers(fixed_substruct, input_conf, output_confs)
        else:
            # align on whole molecule
            alignConformers(mol, input_conf, output_confs)
            
    # erase existing conformers (if any)
    Chem.clearConformations(mol)

    # transfer output confs. one-by-one to molecule
    for conf in output_confs:  
        Chem.addConformation(mol, conf)
    
    # return status code and the number of generated conformers
    return (status, num_confs)

# aligns a set of conformers on the heavy atoms of a given reference structure (fixed substructure
# or input molecule)
def alignConformers(ref_struct: Chem.AtomContainer, ref_conf: Math.Vector3DArray, confs: []) -> None:
    # first, try to use only the heavy atoms of the reference structure for alignment
    ref_atom_inds = [atom.index for atom in ref_struct.atoms if Chem.getType(atom) != Chem.AtomType.H] 
    num_ref_atoms = len(ref_atom_inds)

    # if num. heavy atoms < 3 (3 atoms are required for a defined orientation) use all atoms
    if num_ref_atoms < 3: 
        ref_atom_inds = [atom.index for atom in ref_struct.atoms] 
        num_ref_atoms = len(ref_atom_inds)

    if num_ref_atoms < 1: # in this case, an alignment is not possible
        return
        
    # create instance of the class implementing Kabsch's alignment algorithm
    kabsch_algo = Math.DKabschAlgorithm()  

    ref_coords = Math.DMatrix(3, num_ref_atoms)   # matrix storing the reference 3D coordinates
    algnd_coords = Math.DMatrix(3, num_ref_atoms) # matrix storing the 3D coordinates to align

    # initialize matrix holding the reference coordinates (stored as columns)
    for i in range(num_ref_atoms):
        coords = ref_conf[ref_atom_inds[i]]
        ref_coords[0, i] = coords[0]
        ref_coords[1, i] = coords[1]
        ref_coords[2, i] = coords[2]
            
    for algnd_conf in confs:   # for each conformer to align
        # fetch coordinates of the atoms on which to align from the current conformer
        for j in range(num_ref_atoms):
            coords = algnd_conf[ref_atom_inds[j]]
            algnd_coords[0, j] = coords[0]
            algnd_coords[1, j] = coords[1]
            algnd_coords[2, j] = coords[2]

        # calculate alignment transformation and, if calc. was successful (should always be the case),
        # apply the transformation to all atom positions assoc. with the current conformation
        if kabsch_algo.align(algnd_coords, ref_coords):
            Math.transform(algnd_conf, Math.Matrix4D(kabsch_algo.transform))
            
def main() -> None:
    args = parseArgs()
    
    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # create writer for the generated conformer ensembles (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # parse the SMARTS pattern describing fixed substructures, if specified
    if args.fix_ptn:
        try:
            sub_srch_ptn = Chem.parseSMARTS(args.fix_ptn)
        except Exception as e:
            sys.exit('Error: parsing of SMARTS pattern failed: %s' % str(e))

        # create and initialize an instance of the class Chem.SubstructureSearch that
        # implements the substructure searching algorithm
        sub_srch = Chem.SubstructureSearch(sub_srch_ptn)
        sub_srch.uniqueMappings = True # report only mappings that differ in matched atoms/bonds
    else:
        sub_srch = None
        
    # create and initialize an instance of the class ConfGen.TorsionDriver which
    # will perform conformer generation by enumerating energetically favorable
    # torsion angle combinations
    tor_driver = ConfGen.TorsionDriver()

    tor_driver.settings.energyWindow = args.e_window                    # apply the -e argument
    tor_driver.settings.sampleHetAtomHydrogens = args.rot_term_het_grps # apply the -r argument
    tor_driver.energyOrdered = True                                     # order generated confs. by energy
    tor_driver.strictForceFieldParam = False                            # be tolerant
    
    # dictionary mapping status codes to human readable strings
    status_to_str = { ConfGen.ReturnCode.UNINITIALIZED                  : 'uninitialized',
                      ConfGen.ReturnCode.FORCEFIELD_SETUP_FAILED        : 'force field setup failed' }
    
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
                print('- Generating conformers for molecule %s...' % mol_id)

            try:
                # prepare the molecule for torsion driving
                ConfGen.prepareForConformerGeneration(mol) 

                # check if all atoms have 3D coordinates, print an error message if not
                if not Chem.hasCoordinates(mol, 3):
                    if args.quiet:
                        print('Error: torsion driving on molecule %s failed: no atom 3D coordinates provided' % mol_id)
                    else:
                        print(' -> Torsion driving failed: no atom 3D coordinates provided')
                    continue
                
                # generate conformer ensemble for read molecule
                status, num_confs = performTorsionDriving(mol, tor_driver, sub_srch, args) 

                # check for severe error reported by status code
                if status != ConfGen.ReturnCode.SUCCESS:
                    if args.quiet:
                        print('Error: torsion driving on molecule %s failed: %s' % (mol_id, status_to_str[status]))
                    else:
                        print(' -> Torsion driving failed: %s' % status_to_str[status])

                elif not args.quiet:  # arrives here only if no severe error occurred
                    print(' -> Generated %s conformer(s)' % str(num_confs))
                        
                # output generated ensemble (if available)
                if num_confs > 0:
                    if not writer.write(mol):   
                        sys.exit('Error: output of generated conformers for molecule %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: torsion driving or output of generated conformers for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates conformer ensembles for the given input molecules by performing torsion driving on the provided 3D structure.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Conformer ensemble output file')
    parser.add_argument('-f',
                        dest='fix_ptn',
                        required=False,
                        metavar='<SMARTS>',
                        help='SMARTS pattern describing substructures that shall be kept fixed during torsion driving')
    parser.add_argument('-e',
                        dest='e_window',
                        required=False,
                        metavar='<float>',
                        type=float,
                        default=20.0,
                        help='Output conformer energy window (default: 20.0)')
    parser.add_argument('-n',
                        dest='max_confs',
                        required=False,
                        metavar='<int>',
                        type=int,
                        default=0,
                        help='Max. output ensemble size (default: 100; if <= 0 -> no limit)')
    parser.add_argument('-a',
                        dest='align_confs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Align generated conformers on the fixed part of the input structure (if specified) or on the whole structure (default: false)')
    parser.add_argument('-r',
                        dest='rot_term_het_grps',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Consider single bonds to terminal hetero atoms (= N, O, or S) as rotatable (default: false)')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
    
    return parser.parse_args()

if __name__ == '__main__':
    main()
