##
# analyze_ph4_ftr_mpg.py 
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


# reads and returns the specified reference pharmacophore
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
    parser = argparse.ArgumentParser(description='Reports information about the perceived matches between the features of a reference pharmacophore and a set of input pharmacophores.')

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
                        help='Feature mapping info output file')
    parser.add_argument('-Q',
                        dest='query_mode',
                        required=False,
                        action='store_true',
                        default=False,
                        help='If specified, only alignments where the positions of the features of the input pharmacophores lie strictly '\
                        'within the tolerance spheres of the reference pharmacophore features will be considered as being valid. Otherwise, '\
                        'alignments where the position of at least one feature of the aligned pairs lies within the tolerance sphere of the '\
                        'other feature are also valid (default: false)')
    parser.add_argument('-x',
                        dest='keep_x_vols',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Do not remove exclusion volumes before processing (default: false)')
    parser.add_argument('-q',
                        dest='quiet',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Disable progress output (default: false)')
 
    return parser.parse_args()

def main() -> None:
    args = parseArgs()

    # read the reference pharmacophore
    ref_ph4 = readRefPharmacophore(args.ref_ph4_file) 

    # will store the processed reference features
    working_ref_ph4 = Pharm.FeatureSet()

    if args.keep_x_vols:
        working_ref_ph4.assign(ref_ph4)
    else:
        Pharm.removeFeaturesWithType(ref_ph4, working_ref_ph4, Pharm.FeatureType.EXCLUSION_VOLUME)

    # will store the processed input features
    working_ipt_ph4 = Pharm.FeatureSet()

    # create reader for input pharmacophores (format specified by file extension)
    ph4_reader = Pharm.PharmacophoreReader(args.in_file) 

    # open output file for writing
    out_file = open(args.out_file, 'w')

    # write output file CSV column headers
    out_file.write('Input Pharm. Index, Ref. Feature Index, Ref. Feature Type, Inp. Feature Index, Inp. Feature Type, Distance Score, Angle Score\n')
    
    # create an instances of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()

    # create an instance of the class implementing the perception and storage of pharmacophore feature mappings 
    ftr_mpg = Pharm.SpatialFeatureMapping(args.query_mode) # arg = True -> input features must be within the tolerance spheres of the ref. features

    # create identity transformation for input pharmacophore features (already aligned)
    id_xform = Math.Matrix4D(Math.DIdentityMatrix(4, 4))
   
    # read and process pharmacphores one after the other until the end of input has been reached
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
                print(f'- Processing input pharmacophore {ph4_id}...')

            try:
                if args.keep_x_vols:
                    working_ipt_ph4.assign(ph4)
                else:
                    Pharm.removeFeaturesWithType(ph4, working_ipt_ph4, Pharm.FeatureType.EXCLUSION_VOLUME)
                
                unmpd_ref_ftrs = set(range(0, working_ref_ph4.numFeatures))
                unmpd_ipt_ftrs = set(range(0, working_ipt_ph4.numFeatures))
            
                ftr_mpg.perceive(working_ref_ph4, working_ipt_ph4, id_xform)

                # output found feature mappings where the features are of the same type
                for ftr_pair in ftr_mpg.items():
                    out_file.write(f'{i - 1}, {ref_ph4.getFeatureIndex(ftr_pair[0])}, {Pharm.getType(ftr_pair[0])}, {ph4.getFeatureIndex(ftr_pair[1])}, '\
                                   f'{Pharm.getType(ftr_pair[1])}, {ftr_mpg.getPositionMatchScore(ftr_pair[0], ftr_pair[1])}, '\
                                   f'{ftr_mpg.getGeometryMatchScore(ftr_pair[0], ftr_pair[1])}\n')
                    
                    unmpd_ref_ftrs.discard(working_ref_ph4.getFeatureIndex(ftr_pair[0]))
                    unmpd_ipt_ftrs.discard(working_ipt_ph4.getFeatureIndex(ftr_pair[1]))

                if not args.quiet:
                    print(f' -> Num. reference features matching input features of the same type: {working_ref_ph4.numFeatures - len(unmpd_ref_ftrs)}')
                    print(f' -> Num. input features matching reference features of the same type: {working_ipt_ph4.numFeatures - len(unmpd_ipt_ftrs)}')
                    
                het_mpd_ref_ftrs = set()
                het_mpd_ipt_ftrs = set()
                
                # output valid (in terms of distance) matches of not yet mapped reference and
                # input features (ignoring the type)
                for ref_ftr_idx in list(unmpd_ref_ftrs):
                    ref_ftr = working_ref_ph4.getFeature(ref_ftr_idx)
                    
                    for ipt_ftr_idx in unmpd_ipt_ftrs:
                        ipt_ftr = working_ipt_ph4.getFeature(ipt_ftr_idx)
                        dist_score = ftr_mpg.getPositionMatchFunction()(ref_ftr, ipt_ftr, id_xform)
                        
                        if dist_score > 0:
                            unmpd_ref_ftrs.discard(ref_ftr_idx)
                            het_mpd_ref_ftrs.add(ref_ftr_idx)
                            het_mpd_ipt_ftrs.add(ipt_ftr_idx)
                            
                            out_file.write(f'{i - 1}, {ref_ph4.getFeatureIndex(ref_ftr)}, {Pharm.getType(ref_ftr)}, {ph4.getFeatureIndex(ipt_ftr)}, '\
                                           f'{Pharm.getType(ipt_ftr)}, {dist_score}, -1\n')

                if not args.quiet:
                    print(f' -> Num. remaining reference features matching input features of any type: {len(het_mpd_ref_ftrs)}')
                    print(f' -> Num. remaining input features matching reference features of any type: {len(het_mpd_ipt_ftrs)}')
                 
                unmpd_ipt_ftrs -= het_mpd_ipt_ftrs

                # output unmapped reference features
                for ref_ftr_idx in unmpd_ref_ftrs:
                    ref_ftr = working_ref_ph4.getFeature(ref_ftr_idx)

                    out_file.write(f'{i - 1}, {ref_ph4.getFeatureIndex(ref_ftr)}, {Pharm.getType(ref_ftr)}, -1, -1, -1, -1\n')

                # output unmapped input features
                for ipt_ftr_idx in unmpd_ipt_ftrs:
                    ipt_ftr = working_ipt_ph4.getFeature(ipt_ftr_idx)

                    out_file.write(f'{i - 1}, -1, -1, {ph4.getFeatureIndex(ipt_ftr)}, {Pharm.getType(ipt_ftr)}, -1, -1\n')

                if not args.quiet:
                    print(f' -> Num. unmatched reference features: {len(unmpd_ref_ftrs)}')
                    print(f' -> Num. unmatched input features: {len(unmpd_ipt_ftrs)}')
             
            except Exception as e:
                sys.exit(f'Error: processing of input parmacophore {ph4_id} failed:\n{str(e)}')

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading input parmacophore failed:\n{str(e)}')

    out_file.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
