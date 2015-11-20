# -*- mode: python; tab-width: 4 -*- 

## 
# GenResidueDictionaryData.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2015 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


import sys
import os
import string


def genResidueDictionaryData():
    
    if len(sys.argv) < 3:
        print >> sys.stderr, 'Usage:', sys.argv[0], '[PDB Component Directory mmCIF innput file] [data output header file]'
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

    output.append('/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */\n\n')
    output.append('/*\n')
    output.append(' * ' + os.path.basename(sys.argv[2]) + '\n')
    output.append(' *\n')
    output.append(' * This file is part of the Chemical Data Processing Toolkit\n')
    output.append(' *\n')
    output.append(' * Copyright (C) 2003-2015 Thomas A. Seidel <thomas.seidel@univie.ac.at>\n')
    output.append(' *\n')
    output.append(' * This library is free software; you can redistribute it and/or\n')
    output.append(' * modify it under the terms of the GNU Lesser General Public\n')
    output.append(' * License as published by the Free Software Foundation; either\n')
    output.append(' * version 2 of the License, or (at your option) any later version.\n')
    output.append(' *\n')
    output.append(' * This library is distributed in the hope that it will be useful,\n')
    output.append(' * but WITHOUT ANY WARRANTY; without even the implied warranty of\n')
    output.append(' * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU\n')
    output.append(' * Lesser General Public License for more details.\n')
    output.append(' *\n')
    output.append(' * You should have received a copy of the GNU Lesser General Public License\n')
    output.append(' * along with this library; see the file COPYING. If not, write to\n')
    output.append(' * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,\n')
    output.append(' * Boston, MA 02111-1307, USA.\n')
    output.append(' */\n')
    output.append('\n\n')

    root_and_ext = os.path.splitext(os.path.basename(sys.argv[2]))
    inc_guard = 'CDPL_CHEM_' + string.upper(root_and_ext[0]) + '_' + string.upper(string.lstrip(root_and_ext[1], '.'))

    output.append('#ifndef ' + inc_guard + '\n')
    output.append('#define ' + inc_guard + '\n')
    output.append('\n\n')
    output.append('namespace\n')
    output.append('{\n\n')

    output.append('\tstruct ResidueDataEntry\n')
    output.append('\t{\n\n')
    output.append('\t\tconst char*  code;\n')
    output.append('\t\tconst char*  replacesCode;\n')
    output.append('\t\tconst char*  replacedByCode;\n')
    output.append('\t\tunsigned int type;\n')
    output.append('\t\tbool         obsolete;\n')
    output.append('\t\tstd::size_t  numAtoms;\n')
    output.append('\t\tconst char** atomNames;\n')
    output.append('\t\tstd::size_t  numLeavingAtoms;\n')
    output.append('\t\tstd::size_t* leavingAtoms;\n')
    output.append('\t\tconst char*  name;\n')
    output.append('\t\tconst char*  jmeString;\n')
    output.append('\t};\n\n')

    output.append('\textern const char* atomNames[];\n')
    output.append('\textern std::size_t leavingAtoms[];\n\n')

    output.append('\tResidueDataEntry residueData[] = {\n')
  
    cif_file = file(sys.argv[1], 'r')

    atom_names_offset = 0
    lvg_atoms_offset = 0

    atom_names = []
    lvg_atoms = []

    while True:
        line = skipToLine('data_', cif_file)

        if not line:
            break

        code = line[5:8].strip()

        print 'Processing data for component ' + code + ' ...'
        
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
            print 'Unsupported component type: ' + comp_type
            comp_type = 'OTHER'
        else:
            comp_type = comp_type_map[comp_type]

        ##########

        line = skipToLine('_chem_comp.pdbx_release_status', cif_file)

        if not line:
            break

        rel_status = line[len('_chem_comp.pdbx_release_status'):].strip()

        if rel_status != 'REL' and rel_status != 'OBS':
            print 'Skipping record because relase status != REL or OBS'  
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

        jme_string = ''
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
                #print 'Found single atom entry: ' + code

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

                atom_names.append(atom_id)
                atom_names.append(alt_atom_id)

                if charge == '?':
                    charge = '0'

                if int(charge) > 0:
                    charge = '+' + charge
                elif charge == '0':
                    charge = ''

                jme_string += ' ' + symbol + charge + ' 0 0 0'

                if lvg_atom == 'Y':
                    lvg_atoms.append(0)

                atom_count = 1

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

                    atom_names.append(fields[1])
                    atom_names.append(fields[2].replace('@', ' '))

                    charge = fields[4]

                    if charge == '?':
                        charge = '0'

                    if int(charge) > 0:
                        charge = '+' + charge
                    elif charge == '0':
                        charge = ''

                    symbol = fields[3].capitalize()

                    x = fields[12].replace('?', '0')
                    y = fields[13].replace('?', '0')
                    z = fields[14].replace('?', '0')

                    jme_string += ' ' + symbol + charge + ' ' + x + ' ' + y + ' ' + z

                    if fields[7] == 'Y':
                        lvg_atoms.append(atom_count)

                    name_to_index[fields[1]] = atom_count
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
                    #print 'Found single bond entry: ' + code

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
                        print 'found bond with order ' + value_order

                    jme_string += ' ' + str(name_to_index[atom_id_1] + 1) + ' ' + str(name_to_index[atom_id_2] + 1) + ' ' + order
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

                        atom1_idx = name_to_index[fields[1]] + 1
                        atom2_idx = name_to_index[fields[2]] + 1

                        order = '1'

                        if fields[3] == 'DOUB':
                            order = '2'
                        elif fields[3] == 'TRIP':
                            order = '3'
                        elif fields[3] != 'SING':
                            print 'found bond with order ' + fields[3]

                        jme_string += ' ' + str(atom1_idx) + ' ' + str(atom2_idx) + ' ' + order
                        bond_count += 1

                    if not line:
                        break

        #if not have_atoms:
        #    print 'Entry with NO atoms: ' + code

        #if not have_bonds:
        #    print 'Entry with NO bonds: ' + code

        jme_string = str(atom_count) + ' ' + str(bond_count) + jme_string

        comp_name = comp_name.replace('"', '\\"')

        output.append('\t\t{ "' + code + '", "' + replaces_code + '", "' + replaced_by_code + '", CDPL::Chem::ResidueType::' + comp_type + ', ' + obsolete + ', ' + \
                      str(atom_count) + ', atomNames + ' + str(atom_names_offset)+ ', ' + \
                      str(len(lvg_atoms) - lvg_atoms_offset) + ', leavingAtoms + ' + str(lvg_atoms_offset) + \
                      ', "' + comp_name + '", "' + jme_string + '" },\n')

        atom_names_offset = len(atom_names)
        lvg_atoms_offset = len(lvg_atoms)

        #break ###### 

    output.append('\t};\n\n')

    lvg_atom_array = ''
    count = 0

    for lvg_atom in lvg_atoms:
        if not lvg_atom_array:
            lvg_atom_array = '\tstd::size_t leavingAtoms[] = {\n\t\t'
        else:
            lvg_atom_array += ', '

        if count == 15:
            count = 0
            lvg_atom_array += '\n\t\t'

        count += 1
        lvg_atom_array += str(lvg_atom)

    if not lvg_atom_array:
        lvg_atom_array = '};\n'
    else:
        lvg_atom_array += '\n\t};\n'

    atom_name_array = ''
    count = 0

    for name in atom_names:
        if name[0] == "'" and name[-1] == "'":
            name = name[1:-1]
        elif name[0] == '"' and name[-1] == '"':
            name = name[1:-1]

        if name.find('"') != -1:
            name = name.replace('"', '\\"')

        if not atom_name_array:
            atom_name_array = '\tconst char* atomNames[] = {\n\t\t'
        else:
            atom_name_array += ', '

        if count == 15:
            count = 0
            atom_name_array += '\n\t\t'

        count += 1
        atom_name_array += '"' + name + '"'

    atom_name_array += '\n\t};\n\n'
            
    output.append(atom_name_array)
    output.append(lvg_atom_array)

    output.append('}\n\n')
    output.append('#endif // ' + inc_guard + '\n')

    file(sys.argv[2], 'w+').writelines(output)

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
