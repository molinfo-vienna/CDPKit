.. index:: single: Descriptors; PubChem Fingerprint Generation
           single: Molecules; PubChem Fingerprint Generation
           single: Molecules; Descriptor Generation
           single: Molecules; Fingerprint Generation
           single: Molecules; Input
           single: Molecules; Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Atom Property Calculation
           single: Atoms; Property Calculation
           single: Bonds; Property Calculation
           
PubChem Fingerprint
===================

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
