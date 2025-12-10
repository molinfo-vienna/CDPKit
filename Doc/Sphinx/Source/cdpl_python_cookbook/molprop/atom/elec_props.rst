.. index:: single: Molecules; Input
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Hueckel Molecular Orbital Calculations
           single: Molecules; PEOE Charges Calculation
           single: Molecules; Pi Electron System Perception
           single: Molecules; Pi Electron System List Property
           single: Molecules; Atom Processing
           single: Atoms; Property Calculation
           single: Atoms; PEOE Sigma Charge Property
           single: Atoms; PEOE Sigma Electronegativity Property
           single: Atoms; MHMO Pi Charge Property
           single: Atoms; Total Partial Charge Calculation
           single: Atoms; Lone-pair Electronegativity Calculation
           single: Atoms; Pi Electronegativity Calculation
           single: Atoms; Exerted Inductive Effect Calculation
           single: Atoms; Valence Electron Count Calculation
           single: Bonds; Property Calculation
           
Partial Charges And Other Electronic Properties
===============================================

The script *print_atom_elec_props.py* demonstrates how to iterate over the atoms of molecules
read from a specified input file and calculate the following electronic atom properties:

 - Sigma charge
 - Pi charge
 - Total partial charge
 - Lone-pair electronegativity
 - Pi electronegativity
 - Sigma electronegativity
 - Exerted inductive effect
 - Free valence electron count
 - Valence electron count

**Synopsis**

  :program:`python` *print_atom_elec_props.py* <file>

**Code**

.. literalinclude:: /downloads/print_atom_elec_props.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/print_atom_elec_props.py>`
