Classification Properties
=========================

The script *print_atom_class_props.py* demonstrates how to iterate over the atoms of molecules
read from a specified input file and retrieve the following atom classification properties:

 - Is std. hydrogen
 - Is heavy atom
 - Is unsaturated
 - Is H-bond acceptor
 - H-bond acceptor type
 - Is H-bond donor
 - H-bond donor type
 - Is carbonyl carbon
 - Is amide carbon
 - Is amide nitrogen
 - Is invertible nitrogen
 - Is planar nitrogen
 - Is spiro center
 - Is bridgehead

**Synopsis**

  :program:`python` *print_atom_class_props.py* <file>

**Code**

.. literalinclude:: /downloads/print_atom_class_props.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/print_atom_class_props.py>`
