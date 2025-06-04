Rule-based Editing of Substructures
===================================

The script *edit_mols.py* performs modifications on the molecular graph of molecules read from a specfied file according
to a prvided set of substructure editing rules and writes the results to a given output file.

**Synopsis**

  :program:`python` *edit_mols.py* [-h] -i <file> -o <file> -p <file/string> [-m] [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Edited molecule output file

 -p <file/string>

    A string specifiying search, exclude and result patterns or path to a file providing these
  
**Other options**

 -h, --help

    Show help message and exit

 -m

    Output input molecule before editing result molecule (default: false)

 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/edit_mols.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/edit_mols.py>`
