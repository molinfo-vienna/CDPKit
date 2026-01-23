##
# align_ph4s_to_ph4.py 
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

import CDPL.Pharm as Pharm
import CDPL.Math as Math


# reads and returns the specified alignment reference pharmacophore
def readRefPharmacophore(filename: str) -> Pharm.Pharmacophore:
    # create pharmacophore reader instance
    reader = Pharm.PharmacophoreReader(filename)

    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()

    try:
        if not reader.read(ph4): # read reference pharmacophore
            sys.exit('Error: reading reference pharmacophore failed')
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading reference pharmacophore failed:\n{str(e)}')

    return ph4

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Aligns a set of input pharmacophores onto a given reference pharmacophore.')

    parser.add_argument('-r',
                        dest='ref_ph4_file',
                        required=True,
                        metavar='<file>',
                        help='Reference pharmacophore input file (*.pml, *.cdf)')
    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Pharmacophore input file (*.pml, *.cdf)')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Aligned pharmacophore output file (*.pml, *.cdf)')
    parser.add_argument('-s',
                        dest='score_out_file',
                        required=False,
                        metavar='<file>',
                        help='Pharmacophore alignment score output file')
    parser.add_argument('-n',
                        dest='num_out_almnts',
                        required=False,
                        metavar='<integer>',
                        default=1,
                        help='Number of top-ranked alignment solutions to output per pharmacophore (default: best alignment solution only)',
                        type=int)
    parser.add_argument('-x',
                        dest='exhaustive',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Perform an exhaustive alignment search (default: false)')
    parser.add_argument('-d',
                        dest='min_score_diff',
                        required=False,
                        metavar='<float>',
                        default=0.0,
                        help='Minimum required score difference between two consecutively output pharmacophore alignment poses (default: 0.0)',
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

    return parser.parse_args()

def main() -> None:
    args = parseArgs()

    # read the reference pharmacophore
    ref_ph4 = readRefPharmacophore(args.ref_ph4_file) 

    # create reader for input pharmacophores (format specified by file extension)
    ph4_reader = Pharm.PharmacophoreReader(args.in_file) 
  
    # create writer for aligned pharmacophores (format specified by file extension)
    ph4_writer = Pharm.FeatureContainerWriter(args.out_file) 

    if args.score_out_file:
        score_out_file = open(args.score_out_file, 'w')
    
    # create an instances of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()
    out_ph4 = Pharm.BasicPharmacophore()

    # create an instance of the class implementing the pharmacophore alignment algorithm
    almnt = Pharm.PharmacophoreAlignment(True) # True = aligned features have to be within the tolerance spheres of the ref. features

    if args.pos_only:                          # clear feature orientation information
        Pharm.clearOrientations(ref_ph4)
    
    almnt.addFeatures(ref_ph4, True)               # set reference features (True = first set = reference)
    almnt.performExhaustiveSearch(args.exhaustive) # set minimum number of top. mapped feature pairs
    
    # create pharmacophore fit score calculator instance
    almnt_score = Pharm.PharmacophoreFitScore()
    
    # read and process molecules one after the other until the end of input has been reached
    try:
        i = 1

        while ph4_reader.read(ph4):
            # compose a simple parmacophore identifier
            ph4_id = Pharm.getName(ph4).strip() 

            if ph4_id == '':
                ph4_id = f'#{i}'       # fallback if name is empty
            else:
                ph4_id = f'\'{ph4_id}\' (#{i})'

            if not args.quiet:
                print(f'- Aligning pharmacophore {ph4_id}...')

            try:
                if args.pos_only:                  # clear feature orientation information
                    Pharm.clearOrientations(ph4)

                almnt.clearEntities(False)         # clear features of previously aligned pharmacophore
                almnt.addFeatures(ph4, False)      # specify features of the pharmacophore to align

                almnt_solutions = []               # stores the found alignment solutions
                
                while almnt.nextAlignment():                                     # iterate over all alignment solutions that can be found
                    score = almnt_score(ref_ph4, ph4, almnt.getTransform())      # calculate alignment score
                    xform = Math.Matrix4D(almnt.getTransform())                  # make a copy of the alignment transformation (mol. ph4 -> ref. ph4) 

                    almnt_solutions.append((score, xform))

                if not args.quiet:
                    print(f' -> Found {len(almnt_solutions)} alignment solution(s)')
                
                output_cnt = 0
                last_solution = None
                
                # order solutions by desc. alignment score
                almnt_solutions = sorted(almnt_solutions, key=lambda entry: entry[0], reverse=True)

                # output parmacophore alignment poses until the max. number of best output solutions has been reached
                for solution in almnt_solutions:
                    if output_cnt == args.num_out_almnts:
                        break

                    # check whether the current pose's score is 'different enough' from
                    # the one of the last pose to qualify for output
                    if args.min_score_diff > 0.0 and last_solution and ((solution[0] - last_solution[0]) < args.min_score_diff):
                        continue
                    
                    # create a copy of the input pharmacophore
                    out_ph4.assign(ph4)

                    # apply alignment transformation to the output pharmacophore
                    Pharm.transform3DCoordinates(out_ph4, solution[1])
                    
                    try:
                        if not ph4_writer.write(out_ph4): # output the alignment pose of the parmacophore
                            sys.exit(f'Error: writing alignment pose of parmacophore {ph4_id} failed')

                        if args.score_out_file:
                            score_out_file.write(f'{solution[0]}\n')

                    except Exception as e: # handle exception raised in case of severe write errors
                        sys.exit(f'Error: writing alignment pose of parmacophore {ph4_id} failed:\n{str(e)}')

                    last_solution = solution
                    output_cnt += 1

                if not args.quiet:
                    print(f' -> {output_cnt} alignment pose(s) saved')

            except Exception as e:
                sys.exit(f'Error: alignment of parmacophore {ph4_id} failed:\n{str(e)}')

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading input parmacophore failed:\n{str(e)}')

    if args.score_out_file:
        score_out_file.close()
        
    ph4_writer.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
