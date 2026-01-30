.. index:: single: Pharmacophores; Input
           single: Pharmacophores; Processing
           single: Pharmacophores; Alignment
           single: Pharmacophores; Generation
           single: Pharmacophores; Preparation for Generation
           single: Pharmacophores; Feature Processing
           single: Pharmacophores; Alignment Scoring
           single: Pharmacophore Features; Orientation Property
           single: Pharmacophore Features; Geometry Property
           single: Pharmacophore Features; Type Property
           single: Molecules; Input
           single: Molecules; Output
           single: Molecules; Pharmacophore-based Alignment
           single: Molecules; Structure Data Processing
           single: Molecules; Structure Data Manipulation
           single: Molecules; Structure Data Property
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Preparation for Pharmacophore Generation
           single: Molecules; Conformer Ensemble Handling
           single: Molecules; Name Property
           single: Molecules; Atom 3D Coordinates Processing
           single: Molecules; Atom 3D Coordinates Manipulation
           single: Molecules; Atom 3D Coordinates Transformation
           single: Atoms; Property Calculation
           single: Atoms; 3D Coordinates Property
           single: Bonds; Property Calculation
           single: Data Formats; PML
           single: Data Formats; CDF
           
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
