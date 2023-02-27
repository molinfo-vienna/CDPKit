# -*- mode: python; tab-width: 4 -*-

##
# TestSuite.py  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
        result = subprocess.run([ sys.executable, script_path ] + args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, capture_output=False, check=True)
        output = result.stdout.decode('ascii').replace('\r\n', '\n')
        exp_output = open(os.path.join(os.path.join(script_dir, 'Tests'), script_name + '.out'), 'r').read()

        if output == exp_output:
            print('OK', file=sys.stderr)
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
        result = subprocess.run([ sys.executable, script_path ] + args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, capture_output=False, check=True)
        output = open(out_file, 'r').read()
        exp_output = open(os.path.join(os.path.join(script_dir, 'Tests'), script_name + '.out'), 'r').read()

        if output == exp_output:
            print('OK', file=sys.stderr)
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
        subprocess.run([ sys.executable, script_path ] + args, capture_output=False, check=True)

        print('OK', file=sys.stderr)
        return False
    
    except Exception as e:
        print('\nScript execution FAILED:\n' + str(e), file=sys.stderr)
        return True


if __name__ == '__main__':
    errors = False
    
    errors |= checkScriptOutput('chem_seq_mol_input', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('chem_atom_env_extraction', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('chem_sd_proc', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptFileOutput('chem_chembl_preproc', outputFilePath('chem_chembl_preproc.sdf'),
                                    [ '-i', testDataFilePath('ChEMBLStandardizerTestData.sdf'), '-o', outputFilePath('chem_chembl_preproc.sdf') ])

    errors |= checkScriptOutput('molprop_atom_con_props', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('molprop_atom_class_props', [ testDataFilePath('Morphine.jme') ])
    errors |= checkScriptOutput('molprop_atom_elem_props', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('molprop_atom_elec_props', [ testDataFilePath('Citalopram.sdf') ])
    errors |= checkScriptOutput('molprop_atom_physchem_props', [ testDataFilePath('Citalopram.sdf') ])

    errors |= checkScriptFileOutput('descr_gen_ecfp', outputFilePath('test.out'),
                                    [ '-i', testDataFilePath('Citalopram.sdf'), '-o', outputFilePath('test.out'), '-y', '-c' ])
    errors |= checkScriptOutput('descr_gen_fame_fp', [ testDataFilePath('Citalopram.sdf') ])

    errors |= checkScriptOutput('forcefield_mmff94_charges', [ testDataFilePath('Citalopram.sdf') ])
        
    sys.exit(errors)
