##
# edit_mols.py 
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
import pathlib

import CDPL.Chem as Chem


# edits substructures the argument molecule (if found) using the provided
# list of Chem.SubstructureEditor instances
def editMolecule(mol: Chem.Molecule, ed_list: list) -> int:
    # fill free valences with explicit hydrogens
    added_hs = Chem.makeHydrogenComplete(mol)  

    # if hydrogens were added, invalidate perceived components (if present) since they are invalid now
    if added_hs:                               
        Chem.clearComponents(mol)
 
    num_edits = 0

    # perform editing with all Chem.SubstructureEditor instances in turn
    for editor in ed_list:
        num_edits += editor.edit(mol)

    # if struct. changes were made: clear 2D and 3D atom coordinates since they became invalid
    if num_edits > 0 or added_hs:
        # enforce an on-the-fly perception of atom coordinates dimensionality in case of MDL format output
        Chem.setMDLDimensionality(mol, 0)

        for atom in mol.atoms:
            Chem.clear2DCoordinates(atom)
            Chem.clear3DCoordinates(atom)
            Chem.clear3DCoordinatesArray(atom)

    return num_edits

def createSubstructureEditor(ed_ptns: str) -> Chem.SubstructureEditor:
    editor = Chem.SubstructureEditor()
    tokens = ed_ptns.split()
    i = 1

    for j in range(int(tokens[0])):
        editor.addSearchPattern(Chem.parseSMARTS(tokens[i]))
        i += 1
        
    for j in range(int(tokens[i])):
        i += 1
        editor.addExcludePattern(Chem.parseSMARTS(tokens[i]))

    editor.setResultPattern(Chem.parseSMILES(tokens[i + 1]))

    return editor

def createSubstructureEditors(ed_ptns: str) -> list:
    if pathlib.Path(ed_ptns).is_file():
        editors = []

        with open(ed_ptns, 'r') as ed_ptns_file:
            for line in ed_ptns_file.readlines():
                if line.startswith('#'):
                    continue

                editors.append(createSubstructureEditor(line))

        return editors
    
    return [ createSubstructureEditor(ed_ptns) ]

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Performs a 2D structure layout for the given input molecules.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Laid out molecule output file')
    parser.add_argument('-p',
                        dest='patterns',
                        required=True,
                        metavar='<file/string>',
                        help='A string specifiying search, exclude and result patterns or path to a file providing these')
    parser.add_argument('-m',
                        dest='output_mol',
                        required=False,
                        action='store_true',
                        default=False,
                        help='Output input molecule before editing result molecule (default: false)')
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

    # create writer for the generated 3D structures (format specified by file extension)
    writer = Chem.MolecularGraphWriter(args.out_file) 

    # create the list of one or more initialized Chem.SubstructureEditor instances doing the editing work
    ed_list = createSubstructureEditors(args.patterns)
    
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
                mol_id = f'\'{mol_id}\' (#{i})'

            try:
                # write input molecule before the editing result
                if args.output_mol:
                    Chem.calcBasicProperties(mol, False)

                    if not writer.write(mol):
                        sys.exit(f'Error: writing molecule {mol_id} failed')

                # edit the input molecule according to the specified patterns
                num_changes = editMolecule(mol, ed_list)
                
                if not args.quiet:
                    print(f'- Editing molecule {mol_id}: {num_changes} edit(s) performed')

                Chem.calcBasicProperties(mol, False)
                    
                # output the edited molecule
                if not writer.write(mol):   
                    sys.exit(f'Error: writing edited molecule {mol_id} failed')
                        
            except Exception as e:
                sys.exit(f'Error: editing or output of molecule {mol_id} failed: {str(e)}')

            i += 1
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit(f'Error: reading molecule failed: {str(e)}')

    writer.close()
    sys.exit(0)

if __name__ == '__main__':
    main()
