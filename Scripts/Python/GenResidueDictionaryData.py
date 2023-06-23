## 
# GenResidueDictionaryData.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##


from __future__ import print_function 

import sys
import string

from CDPL.Chem import *
from CDPL.Biomol import *
from CDPL.Base import *


def genResidueDictionaryData():
    
    if len(sys.argv) < 4:
        print('Usage:', sys.argv[0], '[PDB Component Directory mmCIF input file] [residue entry output file] [residue structure output file]', file=sys.stderr)
        sys.exit(2)

    comp_type_map = { 'other' : 'OTHER', \
                      'non-polymer' : 'NON_POLYMER', \
                      'l-peptide cooh carboxy terminus' : 'PEPTIDE_CARBOXY_TERMINUS', \
                      'd-peptide nh3 amino terminus' : 'PEPTIDE_AMINO_TERMINUS', \
                      'l-peptide nh3 amino terminus' : 'PEPTIDE_AMINO_TERMINUS', \
                      'rna oh 3 prime terminus' : 'RNA_HYDROXY_TERMINUS', \
                      'dna oh 3 prime terminus' : 'DNA_HYDROXY_TERMINUS', \
                      'peptide linking' : 'PEPTIDE_LINKING', \
                      'l-peptide linking' : 'PEPTIDE_LINKING', \
                      'd-peptide linking' : 'PEPTIDE_LINKING', \
                      'l-beta-peptide, c-gamma linking' : 'BETA_PEPTIDE_LINKING', \
                      'd-beta-peptide, c-gamma linking' : 'BETA_PEPTIDE_LINKING', \
                      'l-gamma-peptide, c-delta linking' : 'GAMMA_PEPTIDE_LINKING', \
                      'd-gamma-peptide, c-delta linking' : 'GAMMA_PEPTIDE_LINKING', \
                      'peptide-like' : 'PEPTIDE_LIKE', \
                      'rna linking' : 'RNA_LINKING', \
                      'dna linking' : 'DNA_LINKING', \
                      'l-rna linking' : 'RNA_LINKING', \
                      'l-dna linking' : 'DNA_LINKING', \
                      'l-saccharide 1,4 and 1,4 linking' : 'SACCHARIDE_LINKING', \
                      'd-saccharide 1,4 and 1,4 linking' : 'SACCHARIDE_LINKING', \
                      'l-saccharide' : 'SACCHARIDE', \
                      'd-saccharide' : 'SACCHARIDE', \
                      'saccharide' : 'SACCHARIDE' \
    }

    output = list()

    output.append('const ResidueDataEntry residueData[] = {\n')
  
    cif_file = file(sys.argv[1], 'r')

    struct_os = FileIOStream(sys.argv[3], 'wb');
    struct_wtr = CDFMolecularGraphWriter(struct_os)
    struct = BasicMolecule()
    struct_idx = 0

    while True:
        line = skipToLine('data_', cif_file)

        if not line:
            break

        code = line[5:8].strip()

        print('Processing entry ' + code + ' ...', file=sys.stderr)
        
        ##########

        line = skipToLine('_chem_comp.name', cif_file)

        if not line:
            break

        comp_name = line[len('_chem_comp.name'):].strip().strip('"')
   
        ##########

        line = skipToLine('_chem_comp.type', cif_file)

        if not line:
            break

        comp_type = line[len('_chem_comp.type'):].strip().strip('"').lower()

        if comp_type not in comp_type_map:
            print('Unsupported component type: ' + comp_type, file=sys.stderr)
            comp_type = 'OTHER'
        else:
            comp_type = comp_type_map[comp_type]

        ##########

        line = skipToLine('_chem_comp.pdbx_release_status', cif_file)

        if not line:
            break

        rel_status = line[len('_chem_comp.pdbx_release_status'):].strip()

        if rel_status != 'REL' and rel_status != 'OBS':
            print('Skipping record because relase status != REL or OBS'  , file=sys.stderr)
            continue

        obsolete = 'false'
     
        if rel_status == 'OBS':
            obsolete = 'true'

        ##########

        line = skipToLine('_chem_comp.pdbx_replaced_by', cif_file)

        if not line:
            break

        replaced_by_code = line[len('_chem_comp.pdbx_replaced_by'):].strip().strip('"').replace(' ', '').replace('?', '')

        line = skipToLine('_chem_comp.pdbx_replaces', cif_file)

        if not line:
            break

        replaces_code = line[len('_chem_comp.pdbx_replaces'):].strip().strip('"').replace(' ', '').replace('?', '')

        ##########

        line = skipToLine('_chem_comp.three_letter_code', cif_file)

        if not line:
            break

        code = line[len('_chem_comp.three_letter_code'):].strip()
 
        line = skipToLine('#', cif_file)

        if not line:
            break

        ########## ATOMS

        struct.clear()

        setName(struct, code)

        atom_count = 0
        bond_count = 0
        name_to_index = {}

        line = cif_file.readline()

        if not line:
            break

        line = line.strip()
        loop_entry = line.startswith('loop_')

        if loop_entry:
            line = cif_file.readline()

            if not line:
                break

            line = line.strip()

        have_atoms = line.startswith('_chem_comp_atom.')

        if have_atoms:
            if not loop_entry:
                #print('Found single atom entry: ' + code, file=sys.stderr)

                line = skipToLine('_chem_comp_atom.atom_id', cif_file)

                if not line:
                    break

                atom_id = line[len('_chem_comp_atom.atom_id'):].strip()

                line = cif_file.readline()

                if not line:
                    break

                alt_atom_id = line[len('_chem_comp_atom.alt_atom_id'):].strip()

                line = cif_file.readline()

                if not line:
                    break

                symbol = line[len('_chem_comp_atom.type_symbol'):].strip().capitalize()

                line = cif_file.readline()

                if not line:
                    break

                charge = line[len('_chem_comp_atom.charge'):].strip()

                line = skipToLine('_chem_comp_atom.pdbx_leaving_atom_flag', cif_file)

                if not line:
                    break

                lvg_atom = line[len('_chem_comp_atom.pdbx_leaving_atom_flag'):].strip()

                if charge == '?':
                    charge = '0'

                atom = struct.addAtom()

                setSymbol(atom, symbol)

                if atom_id.startswith('"') and atom_id.endswith('"'):
                    atomid = atomid[1:-1]

                setResidueAtomName(atom, atom_id)

                if alt_atom_id.startswith('"') and alt_atom_id.endswith('"'):
                    alt_atomid = alt_atomid[1:-1]

                setResidueAltAtomName(atom, alt_atom_id)

                if charge != '0':
                    setFormalCharge(atom, int(charge))

                set3DCoordinates(atom, (0.0, 0.0, 0.0))

                if lvg_atom == 'Y':
                    setResidueLeavingAtomFlag(atom, True)

                line = skipToLine('#', cif_file)

                if not line:
                    break

            else:       # MULTIPLE ATOMS
                line = skipToLine('_chem_comp_atom.pdbx_ordinal', cif_file)

                if not line:
                    break

                while True:
                    line = cif_file.readline()

                    if not line:
                        break

                    if line.startswith('#'):
                        break

                    if line.find('"N ') != -1:
                        line = line.replace('"N ', '"N@')

                    if line.find('"O ') != -1:
                        line = line.replace('"O ', '"O@')

                    if line.find('"H ') != -1:
                        line = line.replace('"H ', '"H@')

                    if line.find('"HN ') != -1:
                        line = line.replace('"HN ', '"HN@')

                    if line.find('"C ') != -1:
                        line = line.replace('"C ', '"C@')

                    if line.find('"1H ') != -1:
                        line = line.replace('"1H ', '"1H@')

                    if line.find('"2H ') != -1:
                        line = line.replace('"2H ', '"2H@')

                    if line.find('"3H ') != -1:
                        line = line.replace('"3H ', '"3H@')

                    fields = line.split();
                    charge = fields[4]

                    if charge == '?':
                        charge = '0'

                    symbol = fields[3].capitalize()

                    x = fields[12].replace('?', '0')
                    y = fields[13].replace('?', '0')
                    z = fields[14].replace('?', '0')

                    atom = struct.addAtom()

                    setSymbol(atom, symbol)

                    name_to_index[fields[1]] = atom_count

                    if fields[1].startswith('"') and fields[1].endswith('"'):
                        fields[1] = fields[1][1:-1]

                    setResidueAtomName(atom, fields[1])

                    if fields[2].startswith('"') and fields[2].endswith('"'):
                        fields[2] = fields[2][1:-1]

                    setResidueAltAtomName(atom, fields[2].replace('@', ' '))
                  
                    if charge != '0':
                        setFormalCharge(atom, int(charge))

                    set3DCoordinates(atom, (float(x), float(y), float(z)))

                    if fields[7] == 'Y':
                        setResidueLeavingAtomFlag(atom, True)

                    atom_count += 1

                if not line:
                    break

            ########## BONDS
   
            line = cif_file.readline()

            if not line:
                break

            line = line.strip()
            loop_entry = line.startswith('loop_')

            if loop_entry:
                line = cif_file.readline()

                if not line:
                    break

                line = line.strip()

            have_bonds = line.startswith('_chem_comp_bond.')

            if have_bonds:
                if not loop_entry: # SINGLE BOND
                    #print('Found single bond entry: ' + code, file=sys.stderr)

                    line = skipToLine('_chem_comp_bond.atom_id_1', cif_file)

                    if not line:
                        break

                    atom_id_1 = line[len('_chem_comp_bond.atom_id_1'):].strip()

                    line = cif_file.readline()

                    if not line:
                        break

                    atom_id_2 = line[len('_chem_comp_bond.atom_id_2'):].strip()

                    line = cif_file.readline()

                    if not line:
                        break

                    value_order = line[len('_chem_comp_bond.value_order'):].strip()

                    order = '1'

                    if value_order == 'DOUB':
                        order = '2'
                    elif value_order == 'TRIP':
                        order = '3'
                    elif value_order != 'SING':
                        print('found bond with order ' + value_order, file=sys.stderr)

                    bond = struct.addBond(name_to_index[atom_id_1], name_to_index[atom_id_2])

                    setOrder(bond, int(order))

                    bond_count = 1

                else: # MULTIPLE BONDS
                    line = skipToLine('_chem_comp_bond.pdbx_ordinal', cif_file)

                    if not line:
                        break

                    while True:
                        line = cif_file.readline()

                        if not line:
                            break

                        if line.startswith('#'):
                            break

                        fields = line.split()

                        atom1_idx = name_to_index[fields[1]]
                        atom2_idx = name_to_index[fields[2]]

                        order = '1'

                        if fields[3] == 'DOUB':
                            order = '2'
                        elif fields[3] == 'TRIP':
                            order = '3'
                        elif fields[3] != 'SING':
                            print('found bond with order ' + fields[3], file=sys.stderr)

                        bond = struct.addBond(atom1_idx, atom2_idx)

                        setOrder(bond, int(order))

                        bond_count += 1

                    if not line:
                        break

        #if not have_atoms:
        #    print('Entry with NO atoms: ' + code, file=sys.stderr)

        #if not have_bonds:
        #    print('Entry with NO bonds: ' + code, file=sys.stderr)

        comp_name = comp_name.replace('"', '\\"')

        setAtomTypesFromSymbols(struct, True)

        struct_wtr.write(struct)

        output.append('\t{ "' + code + '", "' + replaces_code + '", "' + replaced_by_code + '", ResidueType::' + comp_type + ', ' + obsolete + ', "' + comp_name + '", ' + str(struct_idx) + ' },\n')

        struct_idx += 1

        #break ###### 

    output.append('};\n')
    output.append('\nconst std::size_t NUM_RESIDUE_ENTRIES = ' + str(struct_idx) + ';\n')
    output.append('\nconst std::size_t RESIDUE_STRUCTURE_DATA_LEN = ' + str(struct_os.tell()) + ';\n')

    open(sys.argv[2], 'w').writelines(output);
  
    struct_os.flush()
    struct_os.close()


def skipToLine(prefix, in_file):
    while True: 
        line = in_file.readline()

        if not line:
            return line

        if not line.startswith(prefix):
            continue

        return line    


if __name__ == '__main__':
    genResidueDictionaryData()
