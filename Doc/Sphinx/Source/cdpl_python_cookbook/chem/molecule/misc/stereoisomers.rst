.. index:: single: Molecules; Stereoisomer Enumeration
           single: Molecules; Input
           single: Molecules; Output
           single: Molecules; Property Calculation
           single: Molecules; Atom CIP Priority Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Atom Stereo Center Perception
           single: Molecules; Bond Stereo Center Perception
           single: Molecules; Atom Stereo Descriptor Calculation
           single: Molecules; Bond Stereo Descriptor Calculation
           single: Molecules; Components Perception
           single: Molecules; Components Property
           single: Molecules; Name Property
           single: Molecules; Atom Processing
           single: Molecules; Bond Processing
           single: Atoms; Stereo Center Perception
           single: Atoms; Stereo Center Flag Property
           single: Atoms; Stereo Descriptor Calculation
           single: Atoms; Stereo Descriptor Property
           single: Atoms; CIP Priority Calculation
           single: Atoms; CIP Priority Property
           single: Atoms; Symbol Property
           single: Atoms; Type Property
           single: Atoms; Property Calculation
           single: Bonds; Stereo Center Perception
           single: Bonds; Stereo Center Flag Property
           single: Bonds; Stereo Descriptor Calculation
           single: Bonds; Stereo Descriptor Property
           single: Bonds; Property Calculation
           
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
