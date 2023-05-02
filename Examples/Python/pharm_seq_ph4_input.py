#!/bin/env python

##
# pharm_seq_ph4_input.py 
#
# This file is part of the Pharmical Data Processing Toolkit
#
# Copyright (C) 2003-2022 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

import CDPL.Pharm as Pharm


# function called for each read pharmacophore
def procPharmacophore(ph4: Pharm.Pharmacophore) -> None: 
    print('Read pharmacophore \'%s\' comprising %s features' % (Pharm.getName(ph4), str(ph4.numFeatures)))

def getReaderByFileExt(filename: str) -> Pharm.PharmacophoreReader:
    # get the extension of the input file
    name_and_ext = os.path.splitext(filename)

    if name_and_ext[1] == '':
        sys.exit('Error: could not determine pharmacophore input file format (file extension missing)')

    # get input handler for the format specified by the input file's extension
    ipt_handler = Pharm.PharmacophoreIOManager.getInputHandlerByFileExtension(name_and_ext[1][1:].lower())

    if not ipt_handler:
        sys.exit('Error: unsupported pharmacophore input file format \'%s\'' % name_and_ext[1])

    # create and return file reader instance
    return ipt_handler.createReader(filename)
    
def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input pharm. file>' % sys.argv[0])

    # if the input pharmacophores are expected to be in a specific format, a reader for this format could be created directly, e.g.
    # reader = Pharm.FileCDFPharmacophoreReader(sys.argv[1])
    reader = getReaderByFileExt(sys.argv[1]) 
    
    # create an instance of the default implementation of the Pharm.Pharmacophore interface
    ph4 = Pharm.BasicPharmacophore()
    
    # read and process pharmacophores one after the other until the end of input has been reached
    try:
        while reader.read(ph4): 
            try:
                procPharmacophore(ph4)
            except Exception as e:
                sys.exit('Error: processing of pharmacophore failed: ' + str(e))
                
    except Exception as e: # handle exception raised in case of severe read errors
        sys.exit('Error: reading pharmacophore failed: ' + str(e))

    sys.exit(0)
        
if __name__ == '__main__':
    main()
