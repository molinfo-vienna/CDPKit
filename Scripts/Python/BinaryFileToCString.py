# -*- mode: python; tab-width: 4 -*- 

## 
# BinaryFileToCString.py 
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


def convert():
    if len(sys.argv) < 3:
        print >> sys.stderr, 'Usage:', sys.argv[0], '[input file] [output file]'
        sys.exit(2)

    in_file = open(sys.argv[1], 'rb')
    out_file = open(sys.argv[2], 'w')

    out_file.write('"')

    char_cnt = 0

    for c in in_file.read():
        out_file.write('\\x{0:02x}'.format(ord(c)))
        char_cnt += 1

        if char_cnt % 20 == 0:
            out_file.write('"\n"')
    
    out_file.write('";')
    out_file.flush()
    out_file.close()
    in_file.close()

if __name__ == '__main__':
    convert()
