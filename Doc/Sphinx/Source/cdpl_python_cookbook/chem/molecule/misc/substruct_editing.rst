.. index:: single: Molecules; Substructure Editing
           single: Molecules; Input
           single: Molecules; Output

Editing of Substructures
========================

The script *edit_mols.py* performs modifications on the molecular graph of molecules read from a specified file according
to a provided set of SMARTS/SMILES pattern-based substructure editing rules and writes the results to a given output file.

**Synopsis**

  :program:`python` *edit_mols.py* [-h] -i <file> -o <file> -p <file/string> [-m] [-d] [-c] [-q]

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

 -d

    Remove ordinary explicit hydrogens (default: false)

 -c

    Saturate free valences with explicit hydrogens (default: false)

 -q

    Disable progress output (default: false)

A molecular graph editing operation is specified via a string of one or more SMARTS patterns describing the substructures to edit, optional substructure exclude patterns and a SMILES
string encoding the specific atom and bond modifications to perform. This string of patterns can be specified directly on the command line as value of option *-p*. Alternatively,
the value may also be the path to a file which stores one set of patterns per line and thus allows to specify multiple distinct editing operations which will then be
processed for each input molecule in turn. 

The sequence of whitespace-separated SMARTS/SMILES patterns must be formatted as follows (for examples see below):

*<#Search Patterns> <SMARTS Pattern> ... <#Exclude Patterns> [<SMARTS Pattern> ...] <Editing Result SMILES>*

In the substructure search pattern(s), any atoms to be edited and/or atoms connected by bonds to be modified must be labeled by a unique non-zero integer number (by means of a colon followed
by the integer number at the end of the SMARTS atom specification). These numeric ids are used to establish an unambiguous mapping between the atoms/bonds of the search pattern
and the SMILES string encoding the editing instructions.
As mentioned above, the atom/bond editing operations are all specified by means of a simple SMILES string. For the purpose of substructure editing, the SMILES format has been extended by
additional atom type and bond order symbols that allow to mark atom/bonds for deletion or act as a 'do not change' marker for atom type or bond order.

Editing result SMILES strings have to be composed according to the following rules:

* Atoms of the molecule matching labeled search pattern atoms are referenced by their numeric id (likewise specified by means of a colon followed
  by the integer number at the end of the SMILES atom specification)
* A bond between two labeled atoms in the result SMILES string will be mapped to the bond of the molecule that matched the corresponding bond of the search pattern
* If such a bond of the molecule does not exist it will be created with the specified bond order
* A molecule bond connecting two atoms that match labeled search pattern atoms which is not occurring in the result SMILES string will be left unchanged
* A molecule atom matching a labeled search pattern atom which is not occurring in the result SMILES string will be left unchanged
* A labeled atom in the result SMILES string with a numeric id that does not occur in the search pattern will be created with specified properties (symbol, form. charge, isotope, chirality, ...)
* Any unlabeled atoms in the result SMILES string will be created with the specified properties (symbol, form. charge, isotope, chirality, ...)
* Bonds to/between unlabeled result SMILES string atoms will be created with the specified bond order
* For a mapped molecule atom only those properties (symbol, form. charge, isotope, chirality, ...) that were specified for the corresponding result SMILES string atom will be modified
* The special result SMILES string atom type symbol **x** (only valid in brackets) results in the removal of the mapped molecule atom including any incident bonds
* The special result SMILES string atom type symbol **~** (only valid in brackets) indicates that the type of the mapped molecule atom shall be left unchanged
* The special result SMILES string bond order symbol **x** results in the removal of the mapped molecule bond
* The special result SMILES string bond order symbol **~** indicates that the order of the mapped molecule bond shall be left unchanged
    
**Substructure editing examples**

* *Nitro group standardization*
    | Search pattern:  [#6][N:1](~[O:2])~[O:3]
    | Exclude pattern: [#6][N+](=[O+0])-[O-]
    | Result pattern:  [~+:1](-[~-:2])=[~+0:3]

    **Command line example:**
      
    .. code-block:: shell
           
       $ python edit_mols.py -i wrong_trinitro_benz.sdf -o corr_trinitro_benz.smi -p '1 [#6][N:1](~[O:2])~[O:3] 1 [#6][N+](=[O+0])-[O-] [~+:1](-[~-:2])=[~+0:3]' -d

    .. image:: /graphics/mol_edit_nitro_std.svg
       :scale: 7%
       :alt: Nitro group standardization example

    |
    | :download:`wrong_trinitro_benz.sdf </downloads/wrong_trinitro_benz.sdf>`
    | :download:`corr_trinitro_benz.smi </downloads/corr_trinitro_benz.smi>`
* *Oxidation of primary alcohols to carboxylic acids*
    | Search pattern:  [CD2^3:1]-[OD1]
    | Exclude pattern: -
    | Result pattern:  [~:1]=O

    **Command line example:**
    
    .. code-block:: shell
           
       $ python edit_mols.py -i 3ccz_A_5HI.sdf -o 3ccz_A_5HI_ox.sdf -p '1 [CX2^3:1][OX1] 0 [~:1]=O' -d

    .. image:: /graphics/mol_edit_coh_to_cooh.svg
       :scale: 7%
       :alt: Primary alcohol oxidation example

    |
    | :download:`3ccz_A_5HI.sdf </downloads/3ccz_A_5HI.sdf>`
    | :download:`3ccz_A_5HI_ox.sdf </downloads/3ccz_A_5HI_ox.sdf>`
* *Amide cleavage*
    | Search pattern:  [#6]-[C:1](=O)-[N:2]
    | Exclude pattern: -
    | Result pattern:  [C:1](x[N:2])-O

    **Command line example:**
    
    .. code-block:: shell
           
       $ python edit_mols.py -i cyclosporine.smi -o cyclosporine_cleaved.smi -p '1 [#6]-[C:1](=O)-[N:2] 0 [C:1](x[N:2])-O' -d

    .. image:: /graphics/mol_edit_amide_clvg.svg
       :scale: 7%
       :alt: Amide cleavage example

    |
    | :download:`cyclosporine.smi </downloads/cyclosporine.smi>`
    | :download:`cyclosporine_cleaved.smi </downloads/cyclosporine_cleaved.smi>`
               
**Code**

.. literalinclude:: /downloads/edit_mols.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/edit_mols.py>`
