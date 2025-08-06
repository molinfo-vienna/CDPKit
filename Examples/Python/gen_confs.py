##
# gen_confs.py 
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


# generates a conformer ensemble of the argument molecule using
# the provided initialized ConfGen.ConformerGenerator instance
def genConfEnsemble(mol: Chem.Molecule, conf_gen: ConfGen.ConformerGenerator, sub_srch: Chem.SubstructureSearch, align_confs: bool, quiet: bool) -> (int, int):
    # prepare the molecule for conformer generation
    ConfGen.prepareForConformerGeneration(mol)

    # check if a fixed substructure pattern has been specified and if there are matches
    if sub_srch != None and sub_srch.findMappings(mol): 
        if not quiet:
            print(' -> Found fixed substructure pattern match')
            
        fixed_substruct = Chem.Fragment()  # will store atoms and bonds of the matched substructure(s)

        # extract all bonds (and associated atoms) of the first substructure matched by the pattern
        for bond in sub_srch.getMapping(0).bondMapping.getValues():
            fixed_substruct.addBond(bond)

        # generate the conformer ensemble keeping the spec. substructure fixed
        status = conf_gen.generate(mol, fixed_substruct)

    else:
        if sub_srch != None and not quiet:
            print(' -> No fixed substructure pattern matches found!')

        fixed_substruct = None

        # generate the conformer ensemble
        status = conf_gen.generate(mol)       
    
    num_confs = conf_gen.getNumConformers()
    
    # if successful, store the generated conformer ensemble as
    # per atom 3D coordinates arrays (= the way conformers are represented in CDPKit)
    # and perform conformer alignment (if requested)
    if status == ConfGen.ReturnCode.SUCCESS or status == ConfGen.ReturnCode.TOO_MUCH_SYMMETRY:
        conf_gen.setConformers(mol)

        # if enabled, perform an alignment of the generated conformers
        # using the coordinates of the first one as reference
        if align_confs:
            if fixed_substruct != None:           # align on fixed substructure atoms
                Chem.alignConformations(mol, fixed_substruct)
            else:
                Chem.alignConformations(mol, mol) # align on all molecule atoms
    else:
        num_confs = 0
        
    # return status code and the number of generated conformers
    return (status, num_confs)
        
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates conformer ensembles for the given input molecules.')

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
    parser.add_argument('-e',
                        dest='e_window',
                        required=False,
                        metavar='<float>',
                        type=float,
                        default=20.0,
                        help='Output conformer energy window (default: 20.0)')
    parser.add_argument('-r',
                        dest='min_rmsd',
                        required=False,
                        metavar='<float>',
                        type=float,
                        default=0.5,
                        help='Output conformer RMSD threshold (default: 0.5)')
    parser.add_argument('-t',
                        dest='max_time',
                        required=False,
                        metavar='<int>',
                        type=int,
                        default=3600,
                        help='Max. allowed molecule processing time (default: 3600 sec)')
    parser.add_argument('-n',
                        dest='max_confs',
                        required=False,
                        metavar='<int>',
                        type=int,
                        default=100,
                        help='Max. output ensemble size (default: 100)')
    parser.add_argument('-f',
                        dest='fix_ptn',
                        required=False,
                        metavar='<SMARTS>',
                        help='SMARTS pattern describing a substructure that shall be kept fixed during conformer generation')
    parser.add_argument('-a',
                        dest='align_confs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Align generated conformers on the fixed part of the input structure (if specified) or on the whole structure (default: false)')
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
        sub_srch.maxNumMappings = 1  # find only only one match
    else:
        sub_srch = None

    # create and initialize an instance of the class ConfGen.ConformerGenerator which
    # will perform the actual conformer ensemble generation work
    conf_gen = ConfGen.ConformerGenerator()

    conf_gen.settings.timeout = args.max_time * 1000          # apply the -t argument
    conf_gen.settings.minRMSD = args.min_rmsd                 # apply the -r argument
    conf_gen.settings.energyWindow = args.e_window            # apply the -e argument
    conf_gen.settings.maxNumOutputConformers = args.max_confs # apply the -n argument

    # dictionary mapping status codes to human readable strings
    status_to_str = { ConfGen.ReturnCode.UNINITIALIZED                  : 'uninitialized',
                      ConfGen.ReturnCode.TIMEOUT                        : 'max. processing time exceeded',
                      ConfGen.ReturnCode.ABORTED                        : 'aborted',
                      ConfGen.ReturnCode.FORCEFIELD_SETUP_FAILED        : 'force field setup failed',
                      ConfGen.ReturnCode.FORCEFIELD_MINIMIZATION_FAILED : 'force field structure refinement failed',
                      ConfGen.ReturnCode.FRAGMENT_LIBRARY_NOT_SET       : 'fragment library not available',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_FAILED       : 'fragment conformer generation failed',
                      ConfGen.ReturnCode.FRAGMENT_CONF_GEN_TIMEOUT      : 'fragment conformer generation timeout',
                      ConfGen.ReturnCode.FRAGMENT_ALREADY_PROCESSED     : 'fragment already processed',
                      ConfGen.ReturnCode.TORSION_DRIVING_FAILED         : 'torsion driving failed',
                      ConfGen.ReturnCode.CONF_GEN_FAILED                : 'conformer generation failed',
                      ConfGen.ReturnCode.NO_FIXED_SUBSTRUCT_COORDS      : 'fixed substructure atoms do not provide 3D coordinates' }
    
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
                # generate conformer ensemble for read molecule
                status, num_confs = genConfEnsemble(mol, conf_gen, sub_srch, args.align_confs, args.quiet) 

                # check for severe error reported by status code
                if status != ConfGen.ReturnCode.SUCCESS and status != ConfGen.ReturnCode.TOO_MUCH_SYMMETRY:
                    if args.quiet:
                        print('Error: conformer ensemble generation for molecule %s failed: %s' % (mol_id, status_to_str[status]))
                    else:
                        print(' -> Conformer ensemble generation failed: %s' % status_to_str[status])

                elif not args.quiet:  # arrives here only if no severe error occurred
                    if status == ConfGen.ReturnCode.TOO_MUCH_SYMMETRY:
                        print(' -> Generated %s conformers (warning: too much top. symmetry - output ensemble may contain duplicates)' % str(num_confs))
                    else:
                        print(' -> Generated %s conformer(s)' % str(num_confs))
                        
                # output generated ensemble (if available)
                if num_confs > 0:
                    if not writer.write(mol):   
                        sys.exit('Error: output of conformer ensemble for molecule %s failed' % mol_id)
                        
            except Exception as e:
                sys.exit('Error: conformer ensemble generation or output for molecule %s failed: %s' % (mol_id, str(e)))

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    writer.close()
    sys.exit(0)

if __name__ == '__main__':
    main()
