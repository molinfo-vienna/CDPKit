##
# seq_ph4_input.py 
#
# This file is part of the Pharmical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# Permission to use, copy, modify, and/or distribute this software for any purpose with
# or without fee is hereby granted.
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
# TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
# NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
# IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
# CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
##


import sys

import CDPL.Pharm as Pharm


# function called for each read pharmacophore
def procPharmacophore(ph4: Pharm.Pharmacophore) -> None: 
    print('Read pharmacophore \'%s\' comprising %s features' % (Pharm.getName(ph4), str(ph4.numFeatures)))

def main() -> None:
    if len(sys.argv) < 2:
        sys.exit('Usage: %s <input pharm. file>' % sys.argv[0])

    # create reader for input pharmacophores (format specified by file extension)
    reader = Pharm.PharmacophoreReader(sys.argv[1]) 
 
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
