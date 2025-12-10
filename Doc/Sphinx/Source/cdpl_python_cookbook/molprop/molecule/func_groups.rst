.. index:: single: Molecules; Functional Group Analysis
           single: Molecules; Functional Group Perception
           single: Molecules; Input
           single: Molecules; Fragments
           single: Molecules; Name Property
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Atoms; Property Calculation
           single: Bonds; Property Calculation
           
Functional Groups
=================

The script *count_func_groups.py* perceives the functional groups of molecules
read from a specified input file using Ertl's algorithm :cite:`ertl2017`
and outputs the abundances of the detected functional groups as a CSV-file.

**Synopsis**

  :program:`python` *count_func_groups.py* [-h] -i <file> -o <file> [-v <0|1|2|3>] [-m]

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    Functional group abundance output file

**Other options**

 -h, --help

    Show help message and exit
 
 -v <0|1|2|3>

    Verbosity level (default: 1; 0 -> no console output, 1 -> info, 2 ->
    verbose, 3 -> extra verbose)

 -m

    Consider all possible types of aromatic nitrogens as pyridine nitrogen
    (default: false)
          
**Code**

.. literalinclude:: /downloads/count_func_groups.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/count_func_groups.py>`
