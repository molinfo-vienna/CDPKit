.. index:: single: Pharmacophores; Input
           single: Pharmacophores; Processing
           single: Pharmacophores; Feature Property Retrieval
           
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
