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

import CDPL.Chem as Chem
import CDPL.Biomol as Biomol


def genResidueDictionaryData():
    
    if len(sys.argv) < 4:
        print('Usage:', sys.argv[0], '[PDB Component Directory mmCIF input file] [residue entry output file] [residue structure output file]', file=sys.stderr)
        sys.exit(2)

    comp_type_map = { 'other' : 'OTHER', \
                      'non-polymer' : 'NON_POLYMER', \
                      'l-peptide cooh carboxy terminus' : 'L_PEPTIDE_CARBOXY_TERMINUS', \
                      'd-peptide nh3 amino terminus' : 'D_PEPTIDE_AMINO_TERMINUS', \
                      'l-peptide nh3 amino terminus' : 'L_PEPTIDE_AMINO_TERMINUS', \
                      'rna oh 3 prime terminus' : 'RNA_3_HYDROXY_TERMINUS', \
                      'rna oh 5 prime terminus' : 'RNA_5_HYDROXY_TERMINUS', \
                      'dna oh 3 prime terminus' : 'DNA_3_HYDROXY_TERMINUS', \
                      'dna oh 5 prime terminus' : 'DNA_5_HYDROXY_TERMINUS', \
                      'peptide linking' : 'PEPTIDE_LINKING', \
                      'l-peptide linking' : 'L_PEPTIDE_LINKING', \
                      'd-peptide linking' : 'D_PEPTIDE_LINKING', \
                      'l-beta-peptide, c-gamma linking' : 'L_BETA_PEPTIDE_LINKING', \
                      'd-beta-peptide, c-gamma linking' : 'D_BETA_PEPTIDE_LINKING', \
                      'l-gamma-peptide, c-delta linking' : 'L_GAMMA_PEPTIDE_LINKING', \
                      'd-gamma-peptide, c-delta linking' : 'D_GAMMA_PEPTIDE_LINKING', \
                      'peptide-like' : 'PEPTIDE_LIKE', \
                      'rna linking' : 'RNA_LINKING', \
                      'dna linking' : 'DNA_LINKING', \
                      'l-rna linking' : 'L_RNA_LINKING', \
                      'l-dna linking' : 'L_DNA_LINKING', \
                      'l-saccharide 1,4 and 1,4 linking' : 'L_SACCHARIDE_1_4_LINKING', \
                      'd-saccharide 1,4 and 1,4 linking' : 'D_SACCHARIDE_1_4_LINKING', \
                      'l-saccharide, alpha linking' : 'L_SACCHARIDE_ALPHA_LINKING', \
                      'l-saccharide, beta linking' : 'L_SACCHARIDE_BETA_LINKING', \
                      'd-saccharide, alpha linking' : 'D_SACCHARIDE_ALPHA_LINKING', \
                      'd-saccharide, beta linking' : 'D_SACCHARIDE_BETA_LINKING', \
                      'l-saccharide' : 'L_SACCHARIDE', \
                      'd-saccharide' : 'D_SACCHARIDE', \
                      'saccharide' : 'SACCHARIDE' \
    }

    output = list()

    output.append('// clang-format off\nconst ResidueDataEntry RESIDUE_DATA[] = {\n')

    comp_reader = Biomol.FileMMCIFMoleculeReader(sys.argv[1])
    comp_writer = Chem.FileCDFGZMolecularGraphWriter(sys.argv[3])
    comp = Chem.BasicMolecule()
    comp_idx = 0

    while comp_reader.read(comp):
        comp_name = Chem.getName(comp).replace('\n', '').replace('"', '\\"')
        cif_data = Biomol.getMMCIFData(comp)
        
        try:
            Chem.perceiveSSSR(comp, False)
            Chem.setRingFlags(comp, False)
            Chem.calcImplicitHydrogenCounts(comp, False)
            Chem.perceiveHybridizationStates(comp, False)
            Chem.setAromaticityFlags(comp, False)
            Chem.perceiveAtomStereoCenters(comp, False, False)
            Chem.perceiveBondStereoCenters(comp, False, False)
            Chem.calcAtomStereoDescriptors(comp, False, 3)
            Chem.calcBondStereoDescriptors(comp, False, 3)
        except Exception as e:
            print(f'!! Calculating stereodescriptors for entry {cif_data.id} failed: {e.what()}', file=sys.stderr)
            
        Chem.clearComponents(comp)
        Chem.clearSSSR(comp)
        Chem.clearAromaticSubstructure(comp)
        Chem.clearName(comp)
        
        for atom in comp.atoms:
            if Chem.getFormalCharge(atom) == 0:
                Chem.clearFormalCharge(atom)

            Chem.clearImplicitHydrogenCount(atom)
            Chem.clearHybridizationState(atom)
            Chem.clear3DCoordinates(atom)
            Chem.clear3DCoordinatesArray(atom)
            Chem.clearCIPConfiguration(atom)
            Chem.clearAromaticityFlag(atom)
            Chem.clearRingFlag(atom)
            Chem.clearStereoCenterFlag(atom)

            if Chem.getType(atom) != Chem.AtomType.UNKNOWN:
                Chem.clearSymbol(atom)

            Biomol.clearResidueCode(atom)

            if not Biomol.getResidueLeavingAtomFlag(atom):
                Biomol.clearResidueLeavingAtomFlag(atom)

        for bond in comp.bonds:
            Chem.clearCIPConfiguration(bond)
            Chem.clearAromaticityFlag(bond)
            Chem.clearRingFlag(bond)
            Chem.clearStereoCenterFlag(bond)

        #print('Processing dictionary entry ' + cif_data.id + ' ...', file=sys.stderr)

        cif_comp_data = cif_data.findCategory('chem_comp')

        if not cif_comp_data:
            print(f'!! Skipping entry {cif_data.id} because category _chem_comp could not be found'  , file=sys.stderr)

        rel_status = cif_comp_data.findItem('pdbx_release_status')

        if rel_status:
            rel_status = rel_status.getValue(0).replace('?', '').replace('.', '')
        else:
            print(f'!! Skipping entry {cif_data.id} because release status is unknown'  , file=sys.stderr)
            continue

        if rel_status != 'REL' and rel_status != 'OBS':
            print(f'!! Skipping entry {cif_data.id} because release status != REL or OBS'  , file=sys.stderr)
            continue

        obsolete = 'false'
     
        if rel_status == 'OBS':
            obsolete = 'true'
            
        comp_type = cif_comp_data.findItem('type')

        if comp_type:
            comp_type = comp_type.getValue(0).lower().replace('?', '').replace('.', '')

            if comp_type not in comp_type_map:
                print(f'!! Entry {cif_data.id} has unsupported component type: ' + comp_type, file=sys.stderr)
                comp_type = 'OTHER'
            else:
                comp_type = comp_type_map[comp_type]
        else:
            print(f'! Entry {cif_data.id} lacking component type', file=sys.stderr)
            comp_type = 'OTHER'
            
        replaced_by_code = cif_comp_data.findItem('pdbx_replaced_by')

        if replaced_by_code:
            replaced_by_code = replaced_by_code.getValue(0).replace('?', '').replace('.', '')
        else:
            replaced_by_code = ''
            
        replaces_code = cif_comp_data.findItem('pdbx_replaces')

        if replaces_code:
            replaces_code = replaces_code.getValue(0).replace('?', '').replace('.', '')
        else:
            replaces_code = ''
            
        code = cif_data.id
        
        comp_writer.write(comp)

        output.append('    { "' + code + '", "' + replaces_code + '", "' + replaced_by_code + '", ResidueType::' + comp_type + ', ' + obsolete + ', "' + comp_name + '", ' + str(comp_idx) + ' },\n')

        comp_idx += 1

    output.append('};\n// clang-format on\n')

    open(sys.argv[2], 'w').writelines(output);
  
    comp_writer.close()

    print(f'Generated residue dictionary comprising {comp_idx} entries', file=sys.stderr)

if __name__ == '__main__':
    genResidueDictionaryData()
