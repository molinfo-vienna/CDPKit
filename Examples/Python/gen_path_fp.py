##
# gen_path_fp.py 
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
import CDPL.Descr as Descr
import CDPL.Util as Util


# generates the binary path fingerprint of the given molecule
def genPathFingerprint(mol: Chem.Molecule, num_bits: int, min_len: int, max_len: int, inc_hs: bool) -> Util.BitSet:
    Chem.calcBasicProperties(mol, False)      # calculate basic molecular properties (if not yet done)

    fp_gen = Descr.PathFingerprintGenerator() # create path fingerprint generator instance
    
    # apply option -H
    if inc_hs:        
        Chem.makeHydrogenComplete(mol)        # make any implicit hydrogens explicit
        fp_gen.includeHydrogens(True)         # default = exclude hydrogens

    fp_gen.setMinPathLength(min_len)          # set min. path length
    fp_gen.setMaxPathLength(max_len)          # set max. path length
    
    fp = Util.BitSet()                        # create fingerprint bitset
    fp.resize(num_bits)                       # set desired fingerprint size

    # generate the fingerprint
    fp_gen.generate(mol, fp)                  

    # if needed, fp could be converted into a numpy single precision float array as follows:
    # fp = numpy.array(fp, dtype=numpy.float32)
    
    return fp
    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates path (aka Daylight) fingerprints for given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Input molecule file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Fingerprint output file')
    parser.add_argument('-n',
                        dest='num_bits',
                        required=False,
                        metavar='<integer>',
                        default=1024,
                        help='Fingerprint size in bits (default: 1024)',
                        type=int)
    parser.add_argument('-l',
                        dest='min_path_len',
                        required=False,
                        metavar='<integer>',
                        default=0,
                        help='Minimum path length to consider (in number of bonds, default: 0)',
                        type=int)
    parser.add_argument('-u',
                        dest='max_path_len',
                        required=False,
                        metavar='<integer>',
                        default=5,
                        help='Maximum path length to consider (in number of bonds, default: 5)',
                        type=int)
    parser.add_argument('-H',
                        dest='inc_hs',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Include hydrogens (by default, the fingerprint is generated for the H-deplete molecular graph)')
 
    return parser.parse_args()
    
def main() -> None:
    args = parseArgs()

    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    # open output file storing the generated fingerprints
    out_file = open(args.out_file, 'w')
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()

    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            try:
                fp = genPathFingerprint(mol, args.num_bits, args.min_path_len, args.max_path_len, args.inc_hs)

                out_file.write(str(fp))
                out_file.write('\n')

            except Exception as e:
                sys.exit('Error: processing of molecule failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading molecule failed: ' + str(e))

    out_file.close()
    sys.exit(0)
        
if __name__ == '__main__':
    main()
