Conformer Ensembles
===================

The script *gen_confs.py* generates a conformer ensemble :cite:`doi:10.1021/acs.jcim.3c00563` for each molecule read from
the specified input file and writes the resulting ensembles to the specified output file.

**Synopsis**

  :program:`python` *gen_confs.py* [-h] -i <file> -o <file> [-e <float>] [-r <float>] [-t <int>] [-n <int>] [-q]

**Mandatory options**

 -i <file>
 
    Molecule input file

 -o <file>

    Conformer ensemble output file
  
**Other options**

 -h, --help

    Show help message and exit
 
 -e <float>

    Output conformer energy window (default: 20.0)

 -r <float>

    Output conformer RMSD threshold (default: 0.5)

 -t <int>

    Max. allowed molecule processing time (default: 3600 sec)

 -n <int>

    Max. output ensemble size (default: 100)

 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/gen_confs.py
   :language: python
   :linenos:
   :lines: 21-

:download:`Download source file</downloads/gen_confs.py>`
