.. index:: single: Molecules; Stereoisomer Enumeration
           single: Molecules; Input
           single: Molecules; Output

Enumeration of Stereoisomers
============================

The script *enum_stereo.py* reads molecules from a given input file, enumerates all possible stereoisomers and writes the result to the specified output file.

**Synopsis**

  :program:`python` *enum_stereo.py* [-h] -i <file> -o <file> [-q]

**Mandatory options**

 -i <file>

    Molecule input file

 -o <file>

    Stereoisomer output file

**Other options**

 -h, --help

    Show help message and exit

 -m <int>

    Maximum number of output stereoisomers per molecule (default: 0, must be >= 0, 0 disables limit)

 -a <true|false>

    Enumerate configurations of atom stereocenters (default: true)

 -b <true|false>

    Enumerate configurations of bond stereocenters (default: true)

 -s

    Include specified atom/bond stereocenters (default: false)

 -x

    Include atom/bond stereocenters with topological symmetry (default: false)

 -n

    Include invertible nitrogen stereocenters (default: false)

 -g

    Include bridgehead atom stereocenters (default: false)

 -r

    Include ring bond stereocenters (default: false)

 -R <int>

    Minimum size of rings below which the configuration of member bonds shall not be
    altered (only effective if option -r has been specified; default: 8)
    
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/enum_stereo.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/enum_stereo.py>`
