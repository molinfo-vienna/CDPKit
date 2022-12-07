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

        print('\nOutput check FAILED: expected output = \'%s\', received output = \'%s\'' % (exp_output, output), file=sys.stderr)
        return True
    
    except Exception as e:
        print('\nScript execution FAILED: ' + str(e), file=sys.stderr)
        return True

def dataFile(fname):
    return os.path.join(os.environ['CDPKIT_TEST_DATA_DIR'], fname)


if __name__ == '__main__':
    errors = False
    
    errors |= checkScriptOutput('seq_mol_input', [ dataFile('Citalopram.sdf') ])

    sys.exit(errors)