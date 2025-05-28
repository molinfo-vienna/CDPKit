2D and 3D Pharmacophore Fingerprints
====================================

The script *gen_ph4_fp.py* generates and outputs the 2D or 3D pharmacophore fingerprint of molecules
read from a specified input file.

**Synopsis**

  :program:`python` *gen_ph4_fp.py* [-h] -i <file> -o <file> [-n <integer>] [-d <integer>] [-b <float>]

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    Fingerprint output file
  
**Other options**

 -h, --help

    Show help message and exit

 -n <integer>

    Fingerprint size in bits (default: 4096)

 -d <integer>

    Type of feature distances to consider: 2 -> topological distance, 3 -> 3D distance
    (default: 2)

 -b <float>

    Feature distance bin size (default: 1.0)

**Code**

.. literalinclude:: /downloads/gen_ph4_fp.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_ph4_fp.py>`
