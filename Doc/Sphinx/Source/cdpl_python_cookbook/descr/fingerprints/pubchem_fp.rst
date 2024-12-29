PubChem Fingerprints
====================

The script *gen_pubchem_fp.py* generates 881 bit PubChem fingerprints of molecules read
from the specified file.

**Synopsis**

  :program:`python` *gen_pubchem_fp.py* [-h] -i <file> -o <file>

**Mandatory options**
  
 -i <file>

    Input molecule file

 -o <file>

    Fingerprint output file
  
**Other options**

 -h, --help

    Show this help message and exit

**Code**

.. literalinclude:: /downloads/gen_pubchem_fp.py
   :language: python
   :linenos:
   :lines: 21-

:download:`Download source file</downloads/gen_pubchem_fp.py>`
