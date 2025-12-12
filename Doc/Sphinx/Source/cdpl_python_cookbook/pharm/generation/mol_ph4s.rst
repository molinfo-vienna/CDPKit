.. index:: single: Molecules; Input
           single: Molecules; Preparation for Pharmacophore Generation
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Name Property
           single: Molecules; Conformer Ensemble Handling
           single: Molecules; Atom 3D Coordinates Processing
           single: Pharmacophores; Output
           single: Pharmacophores; Generation
           single: Pharmacophores; Preparation for Generation
           single: Pharmacophores; Name Property
           single: Atoms; Property Calculation
           single: Bonds; Property Calculation
           single: Data Formats; PML
           single: Data Formats; CDF
           
Plain Molecule Pharmacophores
=============================

The script *gen_mol_ph4s.py* generates pharmacophores of molecules read from a
specified file.

**Synopsis**

  :program:`python` *gen_mol_ph4s.py* [-h] -i <file> -o <file> [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Pharmacophore output file
  
**Other options**

 -h, --help

    Show help message and exit
    
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/gen_mol_ph4s.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_mol_ph4s.py>`
