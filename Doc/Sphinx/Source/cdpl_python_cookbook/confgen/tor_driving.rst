Torsion Driving
===============

The script *tor_drive.py* generates a conformer ensemble for each molecule read from the specified input file by performing torsion
driving on the provided 3D structure and writes the resulting ensembles to the desired output file.

**Synopsis**

  :program:`python` *tor_drive.py* [-h] -i <file> -o <file> [-f <SMARTS>] [-e <float>] [-n <int>] [-a] [-r] [-q]

**Mandatory options**

 -i <file>

    Molecule input file
    
 -o <file>

    Conformer ensemble output file
  
**Other options**

 -h, --help

    Show help message and exit

 -f <SMARTS>

    SMARTS pattern describing substructures that shall be kept fixed during torsion driving

 -e <float>

    Output conformer energy window (default: 20.0)

 -n <int>

    Max. output ensemble size (default: 100; if <= 0 -> no limit)

 -a

    Align generated conformers on the fixed part of the input structure (if specified) or
    on the whole structure (default: false)

 -r

    Consider single bonds to terminal hetero atoms (= N, O, or S) as rotatable (default:
    false)

 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/tor_drive.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/tor_drive.py>`
