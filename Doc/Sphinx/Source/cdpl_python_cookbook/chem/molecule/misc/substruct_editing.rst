=====================================
 Rule-based Editing of Substructures
=====================================

The script *edit_mols.py* performs modifications on the molecular graph of molecules read from a specified file according
to a provided set of SMARTS/SMILES pattern-based substructure editing rules and writes the results to a given output file.

**Synopsis**

  :program:`python` *edit_mols.py* [-h] -i <file> -o <file> -p <file/string> [-m] [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Edited molecule output file

 -p <file/string>

    A string specifying search, (optional) exclude and result patterns or path to a file providing these (one set per line)
  
**Other options**

 -h, --help

    Show help message and exit

 -m

    Output input molecule before the resulting edited molecule (default: false)

 -q

    Disable progress output (default: false)

**Examples**

* *Nitro group standardization*
    - Search Pattern:  [#6][N:1](~[O:2])~[O:3]
    - Exclude Pattern: [#6][N+](=[O+0])-[O-]
    - Result Pattern:  [~+:1](-[~-:2])=[~+0:3]
      
      .. image:: /graphics/mol_edit_nitro_std.svg
         :scale: 9%
         :alt: Nitro standardization
* *Use case 2*
    - Search Pattern:  
    - Exclude Pattern: 
    - Result Pattern:  
      
      .. image:: /graphics/mol_edit_nitro_std.svg
         :scale: 9%
         :alt: Nitro standardization
* *Use case 3*
    - Search Pattern:  
    - Exclude Pattern: 
    - Result Pattern:  

      .. image:: /graphics/mol_edit_nitro_std.svg
         :scale: 9%
         :alt: Nitro standardization

**Code**

.. literalinclude:: /downloads/edit_mols.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/edit_mols.py>`
