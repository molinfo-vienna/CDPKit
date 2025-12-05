.. index:: single: Molecules; Rule-based Fragmentation
           single: Molecules; BRICS Fragmentation
           single: Molecules; RECAP Fragmentation
           single: Molecules; Fragments
           single: Molecules; Input
           single: Molecules; Output
           single: Molecules; SSSR Perception
           single: Molecules; SSSR Property
           single: Molecules; Components Perception
           single: Molecules; Components Property
           single: Molecules; Name Property
           single: Atoms; Atom Mapping ID Property
           single: Data Formats; SMILES

Rule-based Fragmentation
========================

The script *gen_mol_frags.py* performs molecule fragmentation according to BRICS :cite:`https://doi.org/10.1002/cmdc.200800178`
or RECAP rules :cite:`doi:10.1021/ci970429i`.

**Synopsis**

  :program:`python` *gen_mol_frags.py* [-h] -i <file> -o <file> -r <string> [-v <0|1|2>] [-m] [-b] [-x]

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    Fragment output file

 -r <string>

    Fragmentation rule set (BRICS or RECAP)
  
**Other options**

 -h, --help

    Show help message and exit

 -v <0|1|2>

    Verbosity level (default: 1; 0 -> no console output, 1 -> verbose, 2 -> extra verbose)

 -m

    Output the fragmented molecule before its fragments (default: false)

 -b

    Include bonds that were split during fragmentation in the obtained fragments (default: false)

 -x

    Label atoms with atom mapping IDs (default: false)

**Code**

.. literalinclude:: /downloads/gen_mol_frags.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_mol_frags.py>`
