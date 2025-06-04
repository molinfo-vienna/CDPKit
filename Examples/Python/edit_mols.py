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


# exhaustively edits matching substructures of the argument molecule according to the 
# given editing specifications that are represented by the provided corresponding list
# of initialized Chem.SubstructureEditor instances
def editMolecule(mol: Chem.Molecule, ed_list: list) -> int:
    # fill free valences with explicit hydrogens
    added_hs = Chem.makeHydrogenComplete(mol)  

    # if hydrogens were added clear the molecular graph components property (if present) since it became invalid
    if added_hs:                               
        Chem.clearComponents(mol)
 
    num_edits = 0

    # perform editing with all provided Chem.SubstructureEditor instances
    for editor in ed_list:
        num_edits += editor.edit(mol)

    # if struct. changes were made clear 2D and 3D atom coordinates since they became invalid
    if num_edits > 0 or added_hs:
        Chem.setMDLDimensionality(mol, 0)        # indicate for output in *.sdf or *.mol format that there are no atom coordinates

        for atom in mol.atoms:
            Chem.clear2DCoordinates(atom)        # clear 2D coordinates property
            Chem.clear3DCoordinates(atom)        # clear 3D coordinates property
            Chem.clear3DCoordinatesArray(atom)   # clear conformer ensemble 3D coordinates 

    return num_edits

# creates and initializes a Chem.SubstructureEditor instance as specified
# by the given string of substructure search, exclude (optional) and editing result patterns
# in the format <#Search Patterns> <Search Pattern SMARTS> ...  <#Exclude Patterns> [<Exclude Pattern SMARTS> ...] <Result Pattern SMILES>
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

# processes the value of the argument -p which is either the path to a file containing multiple lines
# of substructure editing specifications (one per line) or a string directly specifying a complete set
# of search, exclude (optional) and result patterns (see above)
def createSubstructureEditors(ed_ptns: str) -> list:
    if pathlib.Path(ed_ptns).is_file():  # if the argument value is a path to an existing file process it line by line
        editors = []

        with open(ed_ptns, 'r') as ed_ptns_file:
            for line in ed_ptns_file.readlines():
                if line.startswith('#'): # lines starting with '#' ar comment lines
                    continue

                editors.append(createSubstructureEditor(line))

        return editors

    # at this point the argument value specifies a set of search, exclude (optional) and result patterns
    return [ createSubstructureEditor(ed_ptns) ] 

def parseArgs() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description='Performs modifications on the molecular graph of input molecules according \
    to a given set of substructure editing patterns.')

    parser.add_argument('-i',
                        dest='in_file',
                        required=True,
                        metavar='<file>',
                        help='Molecule input file')
    parser.add_argument('-o',
                        dest='out_file',
                        required=True,
                        metavar='<file>',
                        help='Edited molecule output file')
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
                    print(f'- Editing molecule {mol_id}: {num_changes} edit(s)')

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
