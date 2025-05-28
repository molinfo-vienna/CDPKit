PubChem Fingerprints
====================

The script *gen_pubchem_fp.py* generates and outputs the 881 bit PubChem fingerprint of molecules read
from a specified input file.

**Synopsis**

  :program:`python` *gen_pubchem_fp.py* [-h] -i <file> -o <file>

**Mandatory options**
  
 -i <file>

    Input molecule file

 -o <file>

    Fingerprint output file
  
**Other options**

 -h, --help

    Show help message and exit

**Code**

.. literalinclude:: /downloads/gen_pubchem_fp.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_pubchem_fp.py>`
