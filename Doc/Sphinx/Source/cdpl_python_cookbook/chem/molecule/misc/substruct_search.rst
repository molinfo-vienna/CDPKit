.. index:: single: Molecules; Substructure Matching
           single: Molecules; Input
           single: Molecules; Output

Testing for the Presence of Substructures
=========================================

The script *substruct_filter.py* reads molecules from an input file and writes all molecules that match
the specified SMARTS substructure pattern to the output file.

**Synopsis**

  :program:`python` *substruct_filter.py* [-h] -i <file> -o <file> -p <SMARTS> [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Molecule output file

 -p <SMARTS>

    SMARTS pattern describing the substructure to search for
  
**Other options**

 -h, --help

    Show help message and exit
  
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/substruct_filter.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/substruct_filter.py>`
