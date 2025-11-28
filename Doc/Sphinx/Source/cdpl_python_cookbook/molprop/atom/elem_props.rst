.. index:: single: Molecules; Input
           single: Molecules; Atom Property Calculation
           single: Molecules; Atom Property Retrieval

Chemical Element Properties
===========================

The script *print_atom_elem_props.py* demonstrates how to iterate over the atoms of molecules
read from a specified input file and retrieve the following properties associated with the chemical
element of each atom:

 - Atomic weight
 - IUPAC group
 - Periodic table period
 - VdW radius
 - Covalent radius (bond order=1)
 - Covalent radius (bond order=2)
 - Covalent radius (bond order=3)
 - Allred Rochow electronegativity
 - Element name
 - Valence electron count
 - Is supported chemical element
 - Is main group element
 - Is metal
 - Is transition metal
 - Is non-metal
 - Is semi-metal
 - Is halogen
 - Is noble gas

**Synopsis**

  :program:`python` *print_atom_elem_props.py* <file>

**Code**

.. literalinclude:: /downloads/print_atom_elem_props.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/print_atom_elem_props.py>`
