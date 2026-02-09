.. index:: single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Stereo Center Perception
           single: Molecules; Atom Stereo Center Perception
           single: Molecules; Bond Stereo Center Perception
           single: Molecules; Atom Stereo Descriptor Calculation
           single: Molecules; Bond Stereo Descriptor Calculation
           single: Molecules; Canonicalization
           single: Molecules; Atom Canonical Number Calculation
           single: Molecules; Input
           single: Molecules; Output
           single: Atoms; Stereo Center Perception
           single: Atoms; Stereo Center Flag Property
           single: Atoms; Stereo Descriptor Calculation
           single: Atoms; Stereo Descriptor Property
           single: Atoms; Canonical Number Property
           single: Atoms; Property Calculation
           single: Bonds; Stereo Center Perception
           single: Bonds; Stereo Center Flag Property
           single: Bonds; Stereo Descriptor Calculation
           single: Bonds; Stereo Descriptor Property
           single: Bonds; Property Calculation
           
Atom/Bond Order Canonicalization
================================

The script *canon_mols.py* reads molecules from a given input file, canonicalizes the atom and bond order and writes the result to the specified output file.

**Synopsis**

  :program:`python` *canon_mols.py* [-h] -i <file> -o <file> [-d] [-c] [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Canonicalized molecule output file

**Other options**

 -h, --help

    Show help message and exit

 -x

    Ignore atom and bond stereochemistry (default: false)
    
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/canon_mols.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/canon_mols.py>`
