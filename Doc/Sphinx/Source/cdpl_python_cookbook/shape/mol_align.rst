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
   :lines: 21-

:download:`Download source file</downloads/align_mols_by_shape.py>`
