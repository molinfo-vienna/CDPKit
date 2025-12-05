.. index:: single: Molecules; 3D Structure Generation
           single: Molecules; Atom 3D Coordinates Calculation
           single: Molecules; Input
           single: Molecules; Output
           single: Molecules; Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Name Property
           single: Molecules; Atom 3D Coordinates Manipulation
           single: Atoms; 3D Coordinates Property
           single: Atoms; 3D Coordinates Calculation
           single: Atoms; Property Calculation
           single: Bonds; Property Calculation
           single: Data Formats; MDL SD-Files
           
Single Low-energy 3D Structures
===============================

The script *gen_3d_structs.py* generates a single low energy 3D stucture for each molecule read from
the specified input file and writes the resulting structure to the desired output file.

**Synopsis**

  :program:`python` *gen_3d_structs.py* [-h] -i <file> -o <file> [-t <int>] [-q]

**Mandatory options**

 -i <file>

    Molecule input file
    
 -o <file>

    Conformer ensemble output file
  
**Other options**

 -h, --help

    Show help message and exit

 -t <int>

    Max. allowed molecule processing time (default: 3600 sec)

 -q
 
    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/gen_3d_structs.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_3d_structs.py>`
