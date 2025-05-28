##
# count_func_goups.py 
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
import CDPL.MolProp as MolProp

    
# extracts all functional groups of a given input molecule using the provided MolProp.FunctionalGroupsList instance
# and updates their global counts
def extractFunctionalGroups(func_grp_list: MolProp.FunctionalGroupList, in_mol: Chem.Molecule, func_grp_counts: dict, merge_aro_n: bool) -> int:
    Chem.calcBasicProperties(in_mol, False) # calculate required properties 

    func_grp_list.extract(in_mol) # perceive and extract functional groups of the molecule

    for fg in func_grp_list:      # iterate over the functional groups
        name = Chem.getName(fg)

        # if requested, regard all possible types of arom. nitrogens as pyridine N
        if merge_aro_n and (name == '[n+]' or name == 'n[R]'):
            name = 'n'              # change to pyridine nitrogen type
            Chem.setName(fg, name)  # save modified name for later use

        if name in func_grp_counts: # update the global number of times this functional group was encountered
            func_grp_counts[name] += 1
        else:
            func_grp_counts[name] = 1
    
    return len(func_grp_list)
    
def getLogMessage(verb_level: int, mol_id: str, func_grp_list: MolProp.FunctionalGroupList) -> str:
    if verb_level <= 1:
        return None

    if len(func_grp_list) == 0:
        return  f'- Molecule {mol_id}: no functional groups'
    
    if verb_level == 2:
        return f'- Molecule {mol_id}: {len(func_grp_list)} functional group(s)'

    fg_names = [Chem.getName(fg) for fg in func_grp_list].__str__().replace('[', '').replace(']', '').replace('\'', '')
    
    return f'- Molecule {mol_id}: {fg_names}'

    
def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Perceives the functional groups of molecules read from a specified \
    input file and outputs the abundances as a CSV-file.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Input molecule file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Functional group abundance output file')
    parser.add_argument('-v',
                        dest='verb_level',
                        required=False,
                        metavar='<0|1|2|3>',
                        choices=range(0, 4),
                        default=1,
                        help='Verbosity level (default: 1; 0 -> no console output, 1 -> info, 2 -> verbose, 3 -> extra verbose)',
                        type=int)
    parser.add_argument('-m',
                        dest='merge_arom_n',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Consider all possible types of aromatic nitrogens as pyridine nitrogen (default: false)')

    return parser.parse_args()

def main() -> None:
    args = parseArgs() # process command line arguments
    
    # create instance of the class implementing Ertl's alorithm for functional group perception
    func_grp_list = MolProp.FunctionalGroupList()

    # create reader for input molecules (format specified by file extension)
    reader = Chem.MoleculeReader(args.in_file) 
    
    # create instances of the default implementation of the Chem.Molecule interface for the input molecule
    in_mol = Chem.BasicMolecule()
        
    i = 0
    tot_func_grp_count = 0
    func_grp_counts = {}

    try:
        # read and process molecules one after the other until the end of input has been reached (or a severe error occurs)
        while reader.read(in_mol):
            # compose a molecule identifier
            mol_name = Chem.getName(in_mol).strip() 

            if mol_name == '':
                mol_name = f'Mol#{i + 1}'
                mol_id = f'#{i + 1}'  # fallback if name is empty or not available
            else:
                mol_id = f'\'{mol_name}\' (#{i + 1})'
         
            try:
                # extract the functional groups of the read molecule
                tot_func_grp_count += extractFunctionalGroups(func_grp_list, in_mol, func_grp_counts, args.merge_arom_n) 

                # generate log message
                log_msg = getLogMessage(args.verb_level, mol_id, func_grp_list)

                if log_msg:
                    print(log_msg)
                
            except Exception as e: # handle exception raised in case of severe structure processing errors
                sys.exit(f'Error: processing of molecule {mol_id} failed: {str(e)}')

            i += 1
            
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading of molecule {mol_id} failed: {str(e)}')

    with open(args.out_file, 'w') as out_file:
        out_file.write('Functional Group,Count,Percentage\n')

        for count, name in sorted( ((v,k) for k,v in func_grp_counts.items()), reverse=True):
            out_file.write(f'{name},{count},{count / tot_func_grp_count * 100.0:.3f}\n')

    if args.verb_level >= 1:
        print(f'Processed {i} molecules(s)')
        print(f'Found {tot_func_grp_count} functional group(s)')
            
    sys.exit(0)
        
if __name__ == '__main__':
    main()
