.. index:: single: Molecules; Input
           single: Molecules; Output
           single: Molecules; Gaussian Shape-based Alignment
           single: Molecules; Gaussian Shape-based Alignment Scoring
           single: Molecules; Structure Data Processing
           single: Molecules; Structure Data Manipulation
           single: Molecules; Structure Data Property
           single: Molecules; Gaussian Shape Generation
           single: Molecules; Preparation for Pharmacophore Generation
           single: Molecules; Conformer Ensemble Handling
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Name Property
           single: Molecules; Atom 3D Coordinates Processing
           single: Molecules; Atom 3D Coordinates Manipulation
           single: Molecules; Atom 3D Coordinates Transformation
           single: Atoms; Property Calculation
           single: Bonds; Property Calculation
           
Gaussian Shape-based Molecule Alignment
=======================================

The script *align_mols_by_shape.py* overlays a set of input molecules with a given reference molecule based
on their Gaussian shape representations and outputs the molecules translated/rotated to the calculated alignment pose(s).

**Synopsis**

  :program:`python` *align_mols_by_shape.py* [-h] -r <file> -i <file> -o <file> [-s <string>] [-p] [-f] [-m <integer>] [-q]

**Mandatory options**

 -r <file>

    Reference molecule input file

 -i <file>

    Molecule input file

 -o <file>

    Aligned molecule output file
  
**Other options**

 -h, --help

    Show help message and exit

 -p

    Regard pharmacophoric (= color) features (default: false)
 
 -f

    Perform a fast but less accurate shape alignment (default: false)

 -s <string>

    Scoring function to use for assessing computed alignments (default: ShapeTanimotoScore, valid other values:
    TotalOverlapTanimotoScore, ColorTanimotoScore, TanimotoComboScore, TotalOverlapTverskyScore, ShapeTverskyScore,
    ColorTverskyScore, TverskyComboScore, ReferenceTotalOverlapTverskyScore, ReferenceShapeTverskyScore, ReferenceColorTverskyScore,
    ReferenceTverskyComboScore, AlignedTotalOverlapTverskyScore, AlignedShapeTverskyScore, AlignedColorTverskyScore, AlignedTverskyComboScore)

 -m <integer>

    Maximum order of the Gaussian sphere overlap products (only effective in absence of option -f, default: 4)

 -d <float>

    Minimum required RMSD between two consecutively output molecule alignment poses
    (default: 0.0)

 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/align_mols_by_shape.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/align_mols_by_shape.py>`
