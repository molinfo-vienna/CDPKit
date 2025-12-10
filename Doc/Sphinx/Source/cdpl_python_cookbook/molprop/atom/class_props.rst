.. index:: single: Molecules; Input
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; H-Bond Acceptor Atom Type Perceptions
           single: Molecules; H-Bond Donor Atom Type Perceptions
           single: Molecules; Atom Processing
           single: Atoms; Property Calculation
           single: Atoms; H-Bond Acceptor Type Property
           single: Atoms; H-Bond Acceptor Type Perception
           single: Atoms; H-Bond Donor Type Property
           single: Atoms; H-Bond Donor Type Perception
           single: Atoms; Hydrogen Type Inquiry
           single: Atoms; Unsaturatedness Check
           single: Atoms; Heavy Atom Check
           single: Atoms; H-Bond Acceptor Check
           single: Atoms; H-Bond Donor Check
           single: Atoms; Carbonyl-type Carbon Check
           single: Atoms; Amide-type Carbon Check
           single: Atoms; Amide-type Nitrogen Check
           single: Atoms; Invertible Nitrogen Check
           single: Atoms; Planar Nitrogen Check
           single: Atoms; Spiro Center Check
           single: Atoms; Bridgehead Atom Check
           single: Bonds; Property Calculation
           
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
