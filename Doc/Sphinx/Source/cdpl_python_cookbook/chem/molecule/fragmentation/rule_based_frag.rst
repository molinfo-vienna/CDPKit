Rule-based Fragmentation
========================

The script *gen_mol_frags.py* performs molecule fragmentation according to BRICS or RECAP rules.

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

    Show this help message and exit

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
   :lines: 21-

:download:`Download source file</downloads/gen_mol_frags.py>`
