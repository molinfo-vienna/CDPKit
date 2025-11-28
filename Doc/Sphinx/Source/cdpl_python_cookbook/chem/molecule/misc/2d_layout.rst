.. index:: single: Molecules; 2D Coordinates Calculation
           single: Molecules; Input
           single: Molecules; Output

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
