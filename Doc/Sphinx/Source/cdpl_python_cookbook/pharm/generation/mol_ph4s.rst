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
   :lines: 21-

:download:`Download source file</downloads/gen_mol_ph4s.py>`
