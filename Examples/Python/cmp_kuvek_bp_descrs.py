##
# cmp_kuvek_bp_descr.py 
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
import numpy as np


def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Calculates the various similarity measures defined by Kuvek et al. for two binding pocket shape/electrostatics descriptors')

    parser.add_argument('-i',
                        dest='descr_files',
                        required=True,
                        metavar='<file>',
                        nargs=2,
                        help='Binding pocket descriptor files')
    parser.add_argument('-d',
                        dest='shape_charge_wt_split',
                        required=False,
                        metavar='<float>',
                        default=0.0,
                        type=float,
                        help='Whitespace separated list of probe sphere center x, y and z coordinates')

    return parser.parse_args()

def main() -> None:
    args = parseArgs()

    shape_descr1 = np.loadtxt(args.descr_files[0], usecols=0)
    charge_descr1 = np.loadtxt(args.descr_files[0], usecols=1)
    shape_descr2 = np.loadtxt(args.descr_files[1], usecols=0)
    charge_descr2 = np.loadtxt(args.descr_files[1], usecols=1)
  
    shape_stddev = np.std(shape_descr1 + shape_descr2)
    charge_stddev = np.std(charge_descr1 + charge_descr2)

    n = len(shape_descr1)
    shape_rmsd = (np.square(shape_descr1 - shape_descr2).sum() / n) ** 0.5
    charge_rmsd = (np.square(charge_descr1 - charge_descr2).sum() / n) ** 0.5

    ws = 2 / (2 + args.shape_charge_wt_split)
    wc = (1 + args.shape_charge_wt_split) * ws

    shape_charge_rmsd = ((ws * np.square((shape_descr1 - shape_descr2) / shape_stddev).sum() +
                          wc * np.square((charge_descr1 - charge_descr2) / charge_stddev).sum()) / n) ** 0.5
    
    print(f'Shape RMSD: {shape_rmsd}')
    print(f'Charge RMSD: {charge_rmsd}')
    print(f'Shape and Charge RMSD: {shape_charge_rmsd}')
      
if __name__ == '__main__':
    main()
