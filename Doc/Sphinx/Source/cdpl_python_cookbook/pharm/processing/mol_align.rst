Molecule to Reference Pharmacophore Alignment
=============================================

The script *align_mols_to_ph4.py* overlays a set of input molecules with a given reference pharmacophore and outputs
the molecules translated/rotated to the calculated alignment pose(s).

**Synopsis**

  :program:`python` *align_mols_to_ph4.py* [-h] -r <file> -i <file> -o <file> [-n <integer>] [-x] [-d <float>] [-q] [-p]

**Mandatory options**

 -r <file>

    Reference pharmacophore input file (\*.pml, \*.cdf)

 -i <file>

    Molecule input file

 -o <file>

    Aligned molecule output file
  
**Other options**

 -h, --help

    Show help message and exit
 
 -n <integer>

    Number of top-ranked alignment solutions to output per molecule (default: best
    alignment solution only)

 -x

    Perform an exhaustive alignment search (default: false)

 -d <float>

    Minimum required RMSD between two consecutively output molecule alignment poses
    (default: 0.0)

 -q

    Disable progress output (default: false)

 -p

    Ignore feature orientations, feature position matching only (default: false)

**Code**

.. literalinclude:: /downloads/align_mols_to_ph4.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/align_mols_to_ph4.py>`
