.. index:: single: Descriptors;  Receptor Binding Pocket Descriptor Generation
           single: Molecules; Input
           single: Molecules; MMFF94 Atom Typing
           single: Molecules; MMFF94 Bond Typing
           single: Molecules; MMFF94 Partial Charge Calculation
           single: Biological Macromolecules; Input
           single: Biological Macromolecules; Processing
           single: Biological Macromolecules; Binding Site Characterization
           single: Force Fields; MMFF94 Atom Typing
           single: Force Fields; MMFF94 Bond Typing
           single: Force Fields; MMFF94 Partial Charge Calculation

Receptor Binding Pocket Descriptor
==================================

The script *gen_kuvek_bp_descr.py* generates and outputs a binding pocket shape/electrostatics descriptor for a given receptor structure according to the procedure devised by Kuvek et al.

**Synopsis**

  :program:`python` *gen_kuvek_bp_descr.py*  [-h] -i <file> -o <file> -c <float> <float> <float> [-r <float>] [-s <three-letter code> [<three-letter code> ...]] [-n <int>] [-t] [-q]

**Mandatory options**

 -i <file>

    Receptor structure input file (.mol2, .pdb, .mmtf, .cif, .mmcif)

 -o <file>

    Descriptor output file

**Other options**

 -h, --help

    Show help message and exit
 
 -n <integer>

    Number of intersection test vectors (default: 492)

 -r <float>

    Probe sphere radius (default: 20.0)

 **-s <three-letter code> [<three-letter code> ...]**

    Whitespace separated list of PDB three-letter codes specifying residues to
    remove from the receptor structure (e.g. an existing ligand)
                        
 -t

    Output test vector x, y and z coordinates for each descriptor element (default: false)

 -p

    Output test vector atom intersection point x, y and z coordinates for each descriptor element  (default: false)
    
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/gen_kuvek_bp_descr.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_kuvek_bp_descr.py>`
