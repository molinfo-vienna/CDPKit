.. index:: single: Molecules; Atom 2D Coordinates Calculation
           single: Molecules; Bond 2D Stereo Flag Calculation
           single: Molecules; 2D Structure Layout Generation
           single: Molecules; Atom 2D Coordinates Manipulation
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Stereo Center Perception
           single: Molecules; Atom Stereo Center Perception
           single: Molecules; Bond Stereo Center Perception
           single: Molecules; Atom Stereo Descriptor Calculation
           single: Molecules; Bond Stereo Descriptor Calculation
           single: Molecules; Components Perception
           single: Molecules; Components Property
           single: Molecules; Topological Distance Matrix Generation
           single: Molecules; Topological Distance Matrix Property
           single: Molecules; Input
           single: Molecules; Output
           single: Atoms; Stereo Center Perception
           single: Atoms; Stereo Center Flag Property
           single: Atoms; Stereo Descriptor Calculation
           single: Atoms; Stereo Descriptor Property
           single: Atoms; 2D Coordinates Property
           single: Atoms; 2D Coordinates Calculation
           single: Atoms; Property Calculation
           single: Bonds; Stereo Center Perception
           single: Bonds; Stereo Center Flag Property
           single: Bonds; Stereo Descriptor Calculation
           single: Bonds; Stereo Descriptor Property
           single: Bonds; 2D Stereo Flag Property
           single: Bonds; 2D Stereo Flag Calculation
           single: Bonds; Property Calculation
           single: Data Formats; MDL SD-Files
           
2D Structure Generation
=======================

The script *gen_2d_layout.py* reads molecules from a given input file, computes a 2D layout and writes the result to the specified output file.

**Synopsis**

  :program:`python` *gen_2d_layout.py* [-h] -i <file> -o <file> [-d] [-c] [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Laid out molecule output file

**Other options**

 -h, --help

    Show help message and exit

 -d

    Remove ordinary explicit hydrogens (default: false)

 -c

    Saturate free valences with explicit hydrogens (default: false)
    
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/gen_2d_layout.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_2d_layout.py>`
