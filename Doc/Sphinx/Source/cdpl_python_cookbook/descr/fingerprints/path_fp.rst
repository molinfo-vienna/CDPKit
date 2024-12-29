Bond-Path Fingerprints
======================

The script *gen_path_fp.py* generates path (aka Daylight) fingerprints of molecules
read from the specified file.

**Synopsis**

  :program:`python` *gen_path_fp.py* [-h] -i <file> -o <file> [-n <integer>] [-l <integer>] [-u <integer>] [-H]

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    Fingerprint output file
  
**Other options**

 -h, --help

    Show this help message and exit

 -n <integer>

    Fingerprint size in bits (default: 1024)

 -l <integer>

    Minimum path length to consider (in number of bonds, default: 0)

 -u <integer>

    Maximum path length to consider (in number of bonds, default: 5)

 -H

    Include hydrogens (by default, the fingerprint is generated for the H-deplete
    molecular graph)
                
**Code**

.. literalinclude:: /downloads/gen_path_fp.py
   :language: python
   :linenos:
   :lines: 21-

:download:`Download source file</downloads/gen_path_fp.py>`
