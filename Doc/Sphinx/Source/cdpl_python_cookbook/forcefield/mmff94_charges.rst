.. index:: single: Molecules; Input
           single: Molecules; MMFF94 Atom Typing
           single: Molecules; MMFF94 Bond Typing
           single: Molecules; MMFF94 Partial Charge Calculation
           single: Molecules; MMFF94 Aromatic Ring Set Property
           single: Molecules; MMFF94 Aromaticity Perception
           single: Molecules; Aromaticity Perception
           single: Molecules; Atom Hybridization State Perception
           single: Molecules; Atom Implicit Hydrogen Count Calculation
           single: Molecules; Atom Processing
           single: Molecules; Atom Property Calculation
           single: Molecules; Atom Ring Membership Detection
           single: Molecules; Hydrogen Completion
           single: Molecules; Bond Property Calculation
           single: Molecules; Bond Ring Membership Detection
           single: Molecules; Property Calculation
           single: Molecules; SSSR Perception
           single: Molecules; SSSR Property
           single: Atoms; Aromaticity Flag Property
           single: Atoms; Aromaticity Perception
           single: Atoms; Hybridization State Perception
           single: Atoms; Hybridization State Property
           single: Atoms; Implicit Hydrogen Count Calculation
           single: Atoms; Implicit Hydrogen Count Property
           single: Atoms; MMFF94 Atom Typing
           single: Atoms; MMFF94 Numeric Type Property
           single: Atoms; MMFF94 Partial Charge Calculation
           single: Atoms; MMFF94 Partial Charge Property
           single: Atoms; MMFF94 Symbolic Type Property
           single: Atoms; Property Calculation
           single: Atoms; Ring Flag Property
           single: Atoms; Ring Membership Detection
           single: Bonds; Aromaticity Flag Property
           single: Bonds; Aromaticity Perception
           single: Bonds; MMFF94 Bond Type Index Property
           single: Bonds; MMFF94 Bond Typing
           single: Bonds; Property Calculation
           single: Bonds; Ring Flag Property
           single: Bonds; Ring Membership Detection
           single: Force Fields; MMFF94 Atom Typing
           single: Force Fields; MMFF94 Bond Typing
           single: Force Fields; MMFF94 Partial Charge Calculation
           single: Force Fields; MMFF94 Aromaticity Perception
           
MMFF94 Atom Charges
===================

The script *calc_mmff94_charges.py* demosntrates how to calculate MMFF94 atom charges
:cite:`https://doi.org/10.1002/(SICI)1096-987X(199604)17:5/6<490::AID-JCC1>3.0.CO;2-P` for molecules
read from a specified input file.

**Synopsis**

  :program:`python` *calc_mmff94_charges.py* <file>

**Code**

.. literalinclude:: /downloads/calc_mmff94_charges.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/calc_mmff94_charges.py>`
