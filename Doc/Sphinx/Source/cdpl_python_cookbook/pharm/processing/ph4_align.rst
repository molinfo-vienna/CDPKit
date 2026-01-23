.. index:: single: Pharmacophores; Input
           single: Pharmacophores; Output
           single: Pharmacophores; Processing
           single: Pharmacophores; Alignment
           single: Pharmacophores; Alignment Scoring
           single: Pharmacophore Features; Orientation Property
           single: Pharmacophore Features; Geometry Property
           single: Data Formats; PML
           single: Data Formats; CDF
           
Pharmacophore to Pharmacophore Alignment
========================================

The script *align_ph4s_to_ph4.py* overlays a set of input pharmacophores with a given reference pharmacophore and then writes the calculated alignment pose(s) to a specified output file.

**Synopsis**

  :program:`python` *align_ph4s_to_ph4.py* [-h] -r <file> -i <file> -o <file> [-s <file>] [-n <integer>] [-x] [-d <float>] [-q] [-p]

**Mandatory options**

 -r <file>

    Reference pharmacophore input file (\*.pml, \*.cdf)

 -i <file>

    Pharmacophore input file (\*.pml, \*.cdf)

 -o <file>

    Aligned pharmacophore output file (\*.pml, \*.cdf)
  
**Other options**

 -h, --help

    Show help message and exit

 -s <file>

    Pharmacophore alignment score output file
    
 -n <integer>

    Number of top-ranked alignment solutions to output per input pharmacophore (default: best
    alignment solution only)

 -x

    Perform an exhaustive alignment search (default: false)

 -d <float>

    Minimum required score difference between two consecutively output pharmacophore alignment poses
    (default: 0.0)

 -q

    Disable progress output (default: false)

 -p

    Ignore feature orientations, feature position matching only (default: false)

**Code**

.. literalinclude:: /downloads/align_ph4s_to_ph4.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/align_ph4s_to_ph4.py>`
