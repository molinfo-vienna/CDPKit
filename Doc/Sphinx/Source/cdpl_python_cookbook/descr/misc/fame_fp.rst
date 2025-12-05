.. index:: single: Descriptors; FAME Atom Environment Fingerprint Generation
           single: Molecules; FAME Atom Environment Fingerprint Generation
           single: Molecules; Atom Environment Extraction
           single: Molecules; Input
           single: Molecules; Fragment
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Topological Distance Matrix Generation
           single: Molecules; Topological Distance Matrix Property
           single: Molecules; Atom Processing
           single: Molecules; Sybyl Atom Type Perception
           single: Atoms; Property Calculation
           single: Atoms; Sybyl Type Property
           single: Atoms; Descriptor Generation
           single: Atoms; Sybyl Type Perception
           single: Atoms; Environment Extraction
           single: Bonds; Property Calculation
           
FAME Atom Environment Fingerprint
=================================

The script *gen_fame_fp.py* generates and outputs the FAME environment descriptor
:cite:`doi:10.1021/acs.jcim.9b00376,doi:10.1021/acs.jcim.3c01588`
for each atom of molecules read from a specified input file.

**Synopsis**

  :program:`python` *gen_fame_fp.py* <file>

**Code**

.. literalinclude:: /downloads/gen_fame_fp.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_fame_fp.py>`
