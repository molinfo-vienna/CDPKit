# -*- mode: python; tab-width: 4 -*- 

## 
# GenResidueStructureData.py 
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2008 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
import re
import os
import string
import urllib


def genResidueData():
    
    if len(sys.argv) < 3:
        print >> sys.stderr, 'Usage:', sys.argv[0], '[3-letter residue code input-file] [SDF data output header file]'
        sys.exit(2)

    output = list()

    output.append('/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */\n\n')
    output.append('/*\n')
    output.append(' * ' + os.path.basename(sys.argv[2]) + '\n')
    output.append(' *\n')
    output.append(' * This file is part of the Chemical Data Processing Toolkit\n')
    output.append(' *\n')
    output.append(' * Copyright (C) 2003-2014 Thomas A. Seidel <thomas.seidel@univie.ac.at>\n')
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
    output.append('\tconst char* residueStructureData =\n')
    
    res_atom_name_map = {}
    alt_res_code_map = {}
    res_name_map = {}
    leaving_atoms_map = {}
    res_comp_type_map = {}
    res_code_list = []

    for line in file(sys.argv[1], 'r'):
        res_code = line.strip()
        res_code_list.append(res_code)

        print 'Processing data for residue ' + res_code + ' ....'

        alt_res_code_map[res_code] = res_code
        res_name_map[res_code] = ''

        sdf_req = urllib.urlopen('http://ligand-expo.rcsb.org/reports/' + res_code[0] + '/' + res_code + '/' + res_code + '_ideal.sdf')
        sdf_data = sdf_req.read()
        sdf_lines = sdf_data.splitlines(False)
 
        pdb_req = urllib.urlopen('http://ligand-expo.rcsb.org/reports/' + res_code[0] + '/' + res_code + '/' + res_code + '_ideal.pdb')

        if pdb_req.getcode() == 404:
            pdb_req = urllib.urlopen('http://ligand-expo.rcsb.org/reports/' + res_code[0] + '/' + res_code + '/' + res_code + '_model.pdb')

        pdb_data = pdb_req.read()
  
        if len(pdb_data) == 0:
            pdb_req = urllib.urlopen('http://ligand-expo.rcsb.org/reports/' + res_code[0] + '/' + res_code + '/' + res_code + '_model.pdb')
            pdb_data = pdb_req.read()
        
        pdb_lines = pdb_data.splitlines(False)
        res_atom_names = '\t\t"'
   
        info_req = urllib.urlopen('http://ligand-expo.rcsb.org/pyapps/ldHandler.py?formid=cc-index-search&target=' + res_code + '&operation=ccid')
        info_data = info_req.read()
        info_lines = info_data.splitlines(False)

        atom_name_map_req = urllib.urlopen('http://ligand-expo.rcsb.org/reports/' + res_code[0] + '/' + res_code + '/atom-names.html')
        atom_name_map_data = atom_name_map_req.read()
        atom_name_map_lines = atom_name_map_data.splitlines(False)

        alt_res_code = None
        leaving_atoms = None
        res_name = None
        res_comp_type = None
        line_idx = 0

        for info_line in info_lines:
            line_idx += 1
       
            if info_line.find('Name') != -1:
                next_line = info_lines[line_idx]
                res_name_start_idx = next_line.find('"left">') + 7
                res_name_end_idx = next_line.find('</td>')
                res_name = next_line[res_name_start_idx:res_name_end_idx].replace('<wbr />', '').upper().strip()
                res_name_map[res_code] = res_name
                #print res_name

            elif info_line.find('Component type') != -1:
                next_line = info_lines[line_idx]
                res_comp_type_start_idx = next_line.find('"left">') + 7
                res_comp_type_end_idx = next_line.find('</td>')
                res_comp_type = next_line[res_comp_type_start_idx:res_comp_type_end_idx].strip()
                res_comp_type_map[res_code] = res_comp_type
                #print res_comp_type

            elif info_line.find('Observed leaving atoms') != -1:
                next_line = info_lines[line_idx]
                leaving_atoms_start_idx = next_line.find('"left">') + 7
                leaving_atoms_end_idx = next_line.find('</td>')
                leaving_atoms = next_line[leaving_atoms_start_idx:leaving_atoms_end_idx].replace('<wbr />', '').strip()
                leaving_atoms_map[res_code] = leaving_atoms
                #print leaving_atoms

            elif info_line.find('Replaces') != -1:
                next_line = info_lines[line_idx]
                res_code_start_idx = next_line.find('"left">') + 7
                res_code_end_idx = next_line.find('</td>')
                alt_res_code = next_line[res_code_start_idx:res_code_end_idx].strip()
                alt_res_code_map[res_code] = alt_res_code

        name_count = 0             

        for pdb_line in pdb_lines:
            if not pdb_line.startswith('ATOM'):
                break

            res_atom_name = pdb_line[12:16].strip()
            res_atom_name_map[res_atom_name] = res_atom_name

            if name_count == 10:
                name_count = 0
                res_atom_names += '\\n"\n\t\t"'
            elif name_count != 0:
                res_atom_names += ' '

            res_atom_names += res_atom_name
            name_count += 1

        res_atom_names += '\\n"\n'
        line_idx = 0

        for sdf_line in sdf_lines:
            if line_idx == 0 and res_name:
                output.append('\t\t"' + res_name + '\\n"\n')
                line_idx += 1
                continue

            if sdf_line.strip() == '$$$$':
                 output.append('\t\t"> <Residue Code>\\n"\n')
                 output.append('\t\t"' + res_code + '\\n"\n')
                 output.append('\t\t"\\n"\n')

                 if leaving_atoms:
                     output.append('\t\t"> <Leaving Atoms>\\n"\n')
                     output.append('\t\t"' + leaving_atoms + '\\n"\n')
                     output.append('\t\t"\\n"\n')

                 if res_atom_names != '\t\t"\\n\n':
                     output.append('\t\t"> <Residue Atom Names>\\n"\n')
                     output.append(res_atom_names)
                     output.append('\t\t"\\n"\n')

            output.append('\t\t"' + sdf_line + '\\n"\n')
            line_idx += 1

        line_idx = 0

        while line_idx < len(atom_name_map_lines):
            name_map_line = atom_name_map_lines[line_idx].strip()
       
            if name_map_line.startswith('<td class="rs1-c">'):
                line_idx += 1
                next_line = atom_name_map_lines[line_idx].strip()
                
                v3_name = name_map_line[18:name_map_line.find('</td>')]
                v2_name = next_line[18:next_line.find('</td>')]

#                if v3_name in res_atom_name_map and res_atom_name_map[v3_name] != v3_name and res_atom_name_map[v3_name] != v2_name:
                if res_atom_name_map[v3_name] != v3_name and res_atom_name_map[v3_name] != v2_name:
                    print 'NAME ambiguity for ' + v3_name 

                res_atom_name_map[v3_name] = v2_name

            line_idx += 1


    output[-1] = ';'
    output.append('\n')
    output.append('}\n\n')
    output.append('#endif // ' + inc_guard + '\n')

    file(sys.argv[2], 'w+').writelines(output)

    res_atom_name_list = list(res_atom_name_map.keys())
    res_atom_name_list.sort()

    idx = 1;

    print '' 

    for name in res_atom_name_list:
        print 'const unsigned int ' + name.replace("'", '_').ljust(6) + ' = ' + str(idx) + ';'
        idx += 1;

    print ''    

    for name in res_atom_name_list:
        print '{ "' + name + '", "' + res_atom_name_map[name] + '" },'

    print ''    

    for name in res_atom_name_list:
        name = name.replace("'", '_')
        print '.def_readonly("' + name + '", Chem::ResidueAtomType::' + name + ')'

    print ''    

    idx = 1

    for code in res_code_list:
        if str(code[0]).isdigit():
            code = '_' + code

        print 'const unsigned int ' + code.ljust(6) + ' = ' + str(idx) + ';'
        idx += 1;

    print ''   

    for code in res_code_list:
        res_class = res_comp_type_map[code].replace(' ', '_').replace('-', '_').upper()
        print '{ "' + code + '", "' + alt_res_code_map[code] + '", false, CDPL::Chem::ResidueComponentType::' + res_class + ', "' + res_name_map[code] + '" },'

    print ''   

    for code in res_code_list:
        if str(code[0]).isdigit():
            code = '_' + code

        print '.def_readonly("' + code + '", Chem::ResidueType::' + code + ')'

    print ''   

    #for code in res_code_list:
    #    print code.ljust(6) + '  ' + res_comp_type_map[code]
    #    idx += 1;

if __name__ == '__main__':
    genResidueData()
