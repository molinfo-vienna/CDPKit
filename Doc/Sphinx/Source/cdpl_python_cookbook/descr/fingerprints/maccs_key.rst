.. index:: single: Descriptors; MDL MACCS Key Generation
           single: Molecules; Descriptor Generation
           single: Molecules; Fingerprint Generation
           single: Molecules; Input
           single: Molecules; MDL MACCS Key Generation
           single: Molecules; Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Atom Property Calculation
           single: Atoms; Property Calculation
           single: Bonds; Property Calculation

MDL MACCS Key
=============

The script *gen_maccs_key.py* generates and outputs the 166 bit MACCS key of molecules read from a specified input file.

**Synopsis**

  :program:`python` *gen_maccs_key.py* [-h] -i <file> -o <file>

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    MACCS key output file
  
**Other options**

 -h, --help

    Show help message and exit

**Code**

.. literalinclude:: /downloads/gen_maccs_key.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_maccs_key.py>`
