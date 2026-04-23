## 
# PostProcPythonTutorialDoc.py 
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


def process():
    if len(sys.argv) < 2:
        print('Usage:', sys.argv[0], '[*.rst file]', file=sys.stderr)
        sys.exit(2)

    with open(sys.argv[1], 'r+') as rst_file:
        in_lines = rst_file.readlines()
        out_lines = []

        for line in in_lines:
            if line == '.. parsed-literal::\n' or line == '::\n':
                out_lines.append('.. code-block:: text\n')
            elif line == '.. code:: ipython3\n':
                out_lines.append('.. code:: python3\n')
            else:
                out_lines.append(line)

        rst_file.seek(0)
        rst_file.truncate()
        rst_file.writelines(out_lines)
        
if __name__ == '__main__':
    process()
