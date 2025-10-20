##
# gen_ph4_fp.py 
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
import CDPL.Pharm as Pharm


# generates the binary pharmacophore fingerprint of the given molecule
def genPharmFingerprint(mol: Chem.Molecule, num_bits: int, bin_size: float, dim: int) -> Util.BitSet:
    Pharm.prepareForPharmacophoreGeneration(mol)  # prepare molecule for pharmacophore generation

    if dim == 2:
        fp_gen = Descr.NPoint2DPharmacophoreFingerprintGenerator() # create 2D pham. fingerprint generator instance
    else:
        fp_gen = Descr.NPoint3DPharmacophoreFingerprintGenerator() # create 3D pham. fingerprint generator instance

    fp_gen.setBinSize(bin_size) # set feature distance bin size
        
    fp = Util.BitSet()          # create fingerprint bitset
    fp.resize(num_bits)         # set desired fingerprint size

    fp_gen.generate(mol, fp)    # generate the fingerprint

    # if needed, fp could be converted into a numpy single precision float array as follows:
    # fp = numpy.array(fp, dtype=numpy.float32)
    
    return fp
    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates 2D or 3D pharmacophore fingerprints for given input molecules.')

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
                        default=4096,
                        help='Fingerprint size in bits (default: 4096)',
                        type=int)
    parser.add_argument('-d',
                        dest='dim',
                        required=False,
                        metavar='<integer>',
                        default=2,
                        choices=[2, 3],
                        help='Type of feature distances to consider: 2 -> topological distance, 3 -> 3D distance (default: 2)',
                        type=int)
    parser.add_argument('-b',
                        dest='bin_size',
                        required=False,
                        metavar='<float>',
                        default=2.0,
                        help='Feature distance bin size (default: 2.0)',
                        type=float)
  
    return parser.parse_args()
    
def main() -> None:
    args = parseArgs()

    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 

    if args.dim == 3:
        # disable reading of multi. conf. molecules -> each conf. will be read as separate molecule
        Chem.setMultiConfImportParameter(reader, False)
    
    # open output file storing the generated fingerprints
    out_file = open(args.out_file, 'w')
    
    # create an instance of the default implementation of the Chem.Molecule interface
    mol = Chem.BasicMolecule()

    # read and process molecules one after the other until the end of input has been reached
    try:
        while reader.read(mol):
            try:
                fp = genPharmFingerprint(mol, args.num_bits, args.bin_size, args.dim)

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
