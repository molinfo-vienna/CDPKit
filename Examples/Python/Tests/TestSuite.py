##
# TestSuite.py  
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


import sys
import os
import subprocess


def testDataFilePath(fname):
    return os.path.join(os.environ['CDPKIT_TEST_DATA_DIR'], fname)

def outputFilePath(fname):
    return os.path.join(os.environ['CURR_BINARY_DIR'], fname)

def checkScriptOutput(script_name, args):
    script_dir = os.environ['PYTHON_EXAMPLES_DIR']
    script_path = os.path.join(script_dir, script_name + '.py')

    print('Checking output of script \'%s.py\'...' % (script_name), end=' ', file=sys.stderr)

    try:
        result = subprocess.run([ sys.executable, script_path ] + args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=True)
        output = result.stdout.decode('ascii').replace('\r\n', '\n')
        exp_output = open(os.path.join(os.path.join(script_dir, 'Tests'), script_name + '.out'), 'r').read()

        if output == exp_output:
            print('ok', file=sys.stderr)
            return False

        print('\nScript output check FAILED:\nExpected output = \'%s\'\nReceived output = \'%s\'' % (exp_output, output), file=sys.stderr)
        return True
    
    except Exception as e:
        print('\nScript execution FAILED:\n' + str(e), file=sys.stderr)
        return True

def checkScriptFileOutput(script_name, out_file, args):
    script_dir = os.environ['PYTHON_EXAMPLES_DIR']
    script_path = os.path.join(script_dir, script_name + '.py')

    print('Checking output of script \'%s.py\'...' % (script_name), end=' ', file=sys.stderr)

    try:
        result = subprocess.run([ sys.executable, script_path ] + args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=True)
        output = open(out_file, 'r').read()
        exp_output = open(os.path.join(os.path.join(script_dir, 'Tests'), script_name + '.out'), 'r').read()

        if output == exp_output:
            print('ok', file=sys.stderr)
            return False

        print('\nScript output check FAILED:\nExpected output = \'%s\'\nReceived output = \'%s\'' % (exp_output, output), file=sys.stderr)
        return True
    
    except Exception as e:
        print('\nScript execution FAILED:\n' + str(e), file=sys.stderr)
        return True

def checkScriptExecution(script_name, args):
    script_dir = os.environ['PYTHON_EXAMPLES_DIR']
    script_path = os.path.join(script_dir, script_name + '.py')

    print('Checking execution of script \'%s.py\'...' % (script_name), end=' ', file=sys.stderr)

    try:
        subprocess.run([ sys.executable, script_path ] + args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=True)

        print('ok', file=sys.stderr)
        return False
    
    except Exception as e:
        print('\nScript execution FAILED:\n' + str(e), file=sys.stderr)
        return True

if __name__ == '__main__':
    errors = False
    
    errors |= checkScriptOutput('seq_mol_input', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('extract_atom_envs', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('sd_proc', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptFileOutput('clean_mol_db', outputFilePath('clean_mol_db.smi'),
                                    [ '-i', testDataFilePath('ChEMBLStandardizerTestData.sdf.gz'), '-o', outputFilePath('clean_mol_db.smi'),
                                      '-a', 'C,H,N,O,S,P,F,Cl,Br,I', '-m', 'C,A:3', '-c', '-s' ])
    errors |= checkScriptFileOutput('chembl_preproc', outputFilePath('chembl_preproc.sdf'),
                                    [ '-i', testDataFilePath('ChEMBLStandardizerTestData.sdf'), '-o', outputFilePath('chembl_preproc.sdf') ])
    errors |= checkScriptFileOutput('prot_phys_cond', outputFilePath('prot_phys_cond.smi'),
                                    [ '-i', testDataFilePath('ChEMBLStandardizerTestData.sdf'), '-o', outputFilePath('prot_phys_cond.smi') ])
    errors |= checkScriptFileOutput('substruct_filter', outputFilePath('substruct_filter.smi'),
                                    [ '-i', testDataFilePath('ChEMBLStandardizerTestData.sdf'), '-o', outputFilePath('substruct_filter.smi'),
                                      '-p', 'c1ccccc1' ])
 
    errors |= checkScriptFileOutput('gen_mol_ph4s', outputFilePath('gen_mol_ph4s.pml'),
                                    [ '-i', testDataFilePath('1dwc_MIT.sdf'), '-o', outputFilePath('gen_mol_ph4s.pml') ])
    errors |= checkScriptOutput('gen_ia_ph4s',
                                    [ '-r', testDataFilePath('1ke6.pdb'), '-l', testDataFilePath('1ke6_B_LS2.sdf'), '-s', 'LS2',
                                      '-o', outputFilePath('gen_ia_ph4s.pml'), '-x' ])
    errors |= checkScriptFileOutput('align_mols_to_ph4', outputFilePath('align_mols_to_ph4.sdf'),
                                    [ '-r', outputFilePath('gen_ia_ph4s.pml'), '-i', testDataFilePath('LS1.sdf'),
                                      '-o', outputFilePath('align_mols_to_ph4.sdf'), '-n', '10', '-d', '0.5' ])
    errors |= checkScriptOutput('seq_ph4_input', [ testDataFilePath('1dwc_MIT_ph4.pml') ])
    errors |= checkScriptOutput('print_ph4_ftrs', [ testDataFilePath('1dwc_MIT_ph4.cdf') ])

    errors |= checkScriptOutput('print_atom_con_props', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('print_atom_class_props', [ testDataFilePath('Morphine.jme') ])
    errors |= checkScriptOutput('print_atom_elem_props', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('print_atom_elec_props', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('print_atom_physchem_props', [ testDataFilePath('Citalopram.sdf') ])

    errors |= checkScriptFileOutput('gen_ecfp', outputFilePath('test.out'),
                                    [ '-i', testDataFilePath('Citalopram.sdf'), '-o', outputFilePath('test.out'), '-y', '-c' ])
    errors |= checkScriptOutput('gen_fame_fp', [ testDataFilePath('Citalopram.sdf') ])

    errors |= checkScriptOutput('calc_mmff94_charges', [ testDataFilePath('Citalopram.sdf') ])

    errors |= checkScriptFileOutput('tor_drive', outputFilePath('test.mol2'),
                                    [ '-i', testDataFilePath('Citalopram.sdf'), '-o', outputFilePath('test.mol2'), '-a', '-q', '-n', '20', '-f', 'c1cccc2c1C(C)OC2' ])
    errors |= checkScriptFileOutput('gen_confs', outputFilePath('test.mol2'),
                                    [ '-i', testDataFilePath('1ke7_ligands.sdf'), '-o', outputFilePath('test.mol2'), '-r', '0.3', '-n', '10', '-e', '10' ])
    errors |= checkScriptFileOutput('gen_3d_structs', outputFilePath('test.mol2'),
                                    [ '-i', testDataFilePath('1ke7_ligands.sdf'), '-o', outputFilePath('test.mol2') ])
    
    sys.exit(errors)
