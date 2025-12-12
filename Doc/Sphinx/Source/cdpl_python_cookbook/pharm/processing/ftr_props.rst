.. index:: single: Pharmacophores; Input
           single: Pharmacophores; Processing
           single: Pharmacophores; Feature Processing
           single: Pharmacophores; Name Property
           single: Pharmacophore Features; 3D Coordinates Property
           single: Pharmacophore Features; Orientation Property
           single: Pharmacophore Features; Orientation Vector Length Property
           single: Pharmacophore Features; Type Property
           single: Pharmacophore Features; Geometry Property
           single: Pharmacophore Features; Tolerance Property
           single: Pharmacophore Features; Weight Property
           single: Pharmacophore Features; Hydrophobicity Property
           single: Pharmacophore Features; Optional Flag Property
           single: Pharmacophore Features; Disabled Flag Property 
           
Retrieving Feature Properties
=============================

The script *print_ph4_ftrs.py* demonstrates how to iterate over the features of pharmacophores
read from a specified input file and query the following feature properties:

 - Type
 - Geometry
 - Tolerance
 - Position
 - Orientation
 - Orientation vector length
 - Weight
 - Hydrophobicity
 - Is optional
 - Is disabled

**Synopsis**

  :program:`python` *print_ph4_ftrs.py* <file>

**Code**

.. literalinclude:: /downloads/print_ph4_ftrs.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/print_ph4_ftrs.py>`
