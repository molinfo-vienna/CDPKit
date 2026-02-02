.. index:: single: Pharmacophores; Input
           single: Pharmacophores; Processing
           single: Pharmacophores; Alignment Processing
           single: Pharmacophores; Feature Mapping
           single: Pharmacophore Features; Position Property
           single: Pharmacophore Features; Type Property
           single: Data Formats; PML
           single: Data Formats; CDF
           
Pharmacophore Feature Mapping Analysis
======================================

The script *analyze_ph4_ftr_mpg.py* reports information about the perceived matches between the features of a reference pharmacophore and a set of input pharmacophores.

**Synopsis**

  :program:`python` *analyze_ph4_ftr_mpg.py* [-h] -r <file> -i <file> -o <file> [-x] [-Q] [-q] [-p]

**Mandatory options**

 -r <file>

    Reference pharmacophore input file (\*.pml, \*.cdf)

 -i <file>

    Pharmacophore input file (\*.pml, \*.cdf)

 -o <file>

    Feature mapping info output file
  
**Other options**

 -h, --help

    Show help message and exit

 -x

    Do not remove exclusion volumes before processing (default: false)

 -d <float>

    Minimum required score difference between two consecutively output pharmacophore alignment poses
    (default: 0.0)

 -Q

    If specified, only alignments where the positions of the features of the input pharmacophores lie strictly
    within the tolerance spheres of the reference pharmacophore features will be considered as being valid.
    Otherwise, alignments where the position of at least one feature of the aligned pairs lies within the tolerance
    sphere of the other feature are also valid (default: false)

 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/analyze_ph4_ftr_mpg.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/analyze_ph4_ftr_mpg.py>`
