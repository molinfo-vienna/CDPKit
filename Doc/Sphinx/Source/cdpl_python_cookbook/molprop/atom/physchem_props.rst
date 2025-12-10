.. index:: single: Molecules; Input
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Atom Processing
           single: Molecules; Topological Distance Matrix Generation
           single: Molecules; Topological Distance Matrix Property
           single: Atoms; Property Calculation
           single: Atoms; Hybrid Polarizability Query
           single: Atoms; Effective Polarizability Calculation
           single: Bonds; Property Calculation
           
Physicochemical Properties
==========================

The script *print_atom_physchem_props.py* demonstrates how to iterate over the atoms of molecules
read from a specified input file and calculate the following physicochemical atom properties:

 - Hybrid polarizability
 - Effective polarizability

**Synopsis**

  :program:`python` *print_atom_physchem_props.py* <file>

**Code**

.. literalinclude:: /downloads/print_atom_physchem_props.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/print_atom_physchem_props.py>`
