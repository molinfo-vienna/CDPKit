##
# gen_ph4_3d_vis.py 
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
import os
import argparse

import CDPL.Util as Util
import CDPL.Pharm as Pharm
import CDPL.Vis as Vis


def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates 3D vector graphics representations of pharmacophores for the display by external programs.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Input pharmacophore file (*.pml, *.cdf)')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='3D visualization data output file (*.r3d, *.stl, *.ply, *.wrl)')
    parser.add_argument('-c',
                        dest='no_ftr_ctrs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Do not output spheres representing the feature centers (default: false)')
    parser.add_argument('-d',
                        dest='no_ftr_dir',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Make vector and plane features undirected (default: false)')
    
    return parser.parse_args()
    
def main() -> None:
    args = parseArgs()

    # create reader for input pharmacophores (format specified by file extension)
    reader = Pharm.PharmacophoreReader(args.in_file) 
    
    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()

    # instantiate class implementing the creation of visual 3D
    # representations of Pharm.FeatureContainer objects
    ph4_3d_repr_factory = Vis.FeatureContainerObject3DFactory()

    # apply the value of option -c
    Vis.setShowFeatureCentersParameter(ph4_3d_repr_factory, not args.no_ftr_ctrs)
    
    out_file, out_file_ext = os.path.splitext(args.out_file)
    
    # read and process pharmacophores one after the other until the end of input has been reached
    try:
        i = 1
        
        while reader.read(ph4):
            try:
                if args.no_ftr_dir:                       # if pharm. features shall be output without orientation information (option -d)
                    Pharm.clearOrientations(ph4)          # clear orientation property of all features
                    Pharm.removePositionalDuplicates(ph4) # and reduce multiple features having the same type and position to one feature

                # create writer for the output file (file format determined by the file extension)
                writer = Vis.Object3DWriter(f'{out_file}_{i}{out_file_ext}')

                # generate the 3D visual representation of the read pharmacophore
                ph4_3d_repr = ph4_3d_repr_factory.create(ph4)

                # output the generated visualization data
                if not writer.write(ph4_3d_repr):
                    sys.exit('Error: output of pharmacophore visualization data failed')

                i += 1
                writer.close()
    
            except Exception as e:
                sys.exit('Error: generation or output of pharmacophore visualization data failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading pharmacophore failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
