.. index:: single: Molecules; Protonation State Standardization
           single: Molecules; Input
           single: Molecules; Output

Generating Protonation States at Physiological pH
=================================================

The script *prot_phys_cond.py* generates likely protonation states at phys. conditions for
a set of given input molecules and then writes the resulting structures to the specified output file.

**Synopsis**

  :program:`python` *prot_phys_cond.py* [-h] -i <file> -o <file> [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Molecule output file

**Other options**

 -h, --help

    Show help message and exit
    
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/prot_phys_cond.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/prot_phys_cond.py>`
