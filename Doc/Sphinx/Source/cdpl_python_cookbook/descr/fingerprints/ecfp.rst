.. index:: single: Descriptors; ECFP Fingerprint Generation
           single: Descriptors; Morgan Fingerprint Generation
           single: Molecules; Descriptor Generation
           single: Molecules; Fingerprint Generation
           single: Molecules; Input
           single: Molecules; ECFP Fingerprint Generation
           single: Molecules; Morgan Fingerprint Generation
           single: Molecules; Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Atom CIP Priority Calculation
           single: Molecules; Hydrogen Completion
           single: Molecules; Atom Stereo Center Perception
           single: Molecules; Atom Stereo Descriptor Calculation
           single: Atoms; Property Calculation
           single: Atoms; Stereo Center Perception
           single: Atoms; Stereo Center Flag Property
           single: Atoms; Stereo Descriptor Calculation
           single: Atoms; Stereo Descriptor Property
           single: Atoms; CIP Priority Calculation
           single: Atoms; CIP Priority Property
           single: Bonds; Property Calculation
           
Extended Connectivity Fingerprint (ECFP)
========================================

The script *gen_ecfp.py* generates and outputs the *Extended Connectivity Fingerprint* (ECFP) :cite:`doi:10.1021/ci100050t` of molecules
read from a specified input file.

**Synopsis**

  :program:`python` *gen_ecfp.py* [-h] -i <file> -o <file> [-n <integer>] [-r <integer>] [-y] [-c]

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    Fingerprint output file

**Other options**

 -h, --help

    Show help message and exit
 
 -n <integer>

    Fingerprint size in bits (default: 1024)

 -r <integer>

    Max. atom environment radius in number of bonds (default: 2)

 -y

    Do not ignore hydrogens (by default, the fingerprint is generated for the H-deplete
    molecular graph)

 -c

    Include atom chirality (by default, atom chirality is not considered)

**Code**

.. literalinclude:: /downloads/gen_ecfp.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_ecfp.py>`
