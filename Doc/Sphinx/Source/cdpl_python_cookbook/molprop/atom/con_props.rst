.. index:: single: Molecules; Input
           single: Molecules; Atom Property Calculation
           single: Molecules; Atom Property Retrieval

Connectivity Properties
=======================

The script *print_atom_con_props.py* demonstrates how to iterate over the atoms of molecules
read from a specified input file and retrieve the following atom properties:

 - Num. connected std. hydrogens (incl. impl. H)
 - Num. connected carbon atoms
 - Num. connected heteroatoms
 - Num. connected halogens
 - Num. connected heavy atoms
 - Num. connected chain atoms (excl. impl. H)
 - Num. connected chain atoms (incl. impl. H)
 - Num. connected ring atoms
 - Num. connected aromatic atoms
 - Num. incident bonds (excl. impl. H)
 - Num. incident bonds (incl. impl. H)
 - Num. incident single bonds (excl. impl. H)
 - Num. incident single bonds (incl. impl. H)
 - Num. incident double bonds
 - Num. incident triple bonds
 - Num. incident chain bonds (excl. impl. H)
 - Num. incident chain bonds (incl. impl. H)
 - Num. incident ring bonds (incl. impl. H)
 - Num. incident aromatic bonds (incl. impl. H)
 - Num. incident heavy atom bonds (incl. impl. H)
 - Num. incident rotatable bonds (incl. impl. H)
 - Valence (excl. impl. H)
 - Valence (incl. impl. H)
 - Steric number
 - VSEPR coordination geometry

**Synopsis**

  :program:`python` *print_atom_con_props.py*

**Code**

.. literalinclude:: /downloads/print_atom_con_props.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/print_atom_con_props.py>`
