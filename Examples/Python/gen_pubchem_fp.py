##
# gen_pubchem_fp.py 
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


# generates the PubChem fingerprint of the given molecular graph
def genPubChemFingerprint(molgraph: Chem.MolecularGraph) -> Util.BitSet:
    Chem.calcBasicProperties(molgraph, False)    # calculate basic molecular properties (if not yet done)
   
    fp_gen = Descr.PubChemFingerprintGenerator() # create PubChem fingerprint generator instance
    fp = Util.BitSet()                           # create Util.BitSet instance storing the generated fingerprint

    # generate the PubChem fingerprint
    fp_gen.generate(molgraph, fp)

    # if needed, fp could be converted into a numpy single precision float array as follows:
    # fp = numpy.array(fp, dtype=numpy.float32)

    return fp
    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Generates 881 bit PubChem fingerprints for given input molecules.')

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
                fp = genPubChemFingerprint(mol)

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
