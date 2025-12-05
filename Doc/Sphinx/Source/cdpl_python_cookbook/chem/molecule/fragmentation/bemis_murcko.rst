.. index:: single: Molecules; Bemis-Murcko Scaffold Analysis
           single: Molecules; Input
           single: Molecules; Output
           single: Molecules; Fragments
           single: Molecules; SSSR Perception
           single: Molecules; SSSR Property
           single: Molecules; Components Perception
           single: Molecules; Components Property
           single: Molecules; Name Property
           single: Atoms; Type Property
           single: Atoms; Symbol Property
           single: Atoms; Formal Charge Property
           single: Atoms; Implicit Hydrogen Count Property
           single: Atoms; Aromaticity Flag Property
           single: Atoms; Hybridization State Property
           single: Atoms; Stereo Descriptor Property
           single: Atoms; 3D Coordinates Property
           single: Atoms; 3D Coordinates Array Property
           single: Atoms; Atom Mapping ID Property
           single: Bonds; Order Property
           single: Bonds; Aromaticity Flag Property
           single: Bonds; Stereo Descriptor Property
           single: Bonds; 2D Stereo Flag Property
           single: Data Formats; SMILES

Bemis-Murcko Framework Analysis
===============================

The script *gen_bm_frags.py* analyzes the framework of input molecules according to the rules established by Bemis and
Murcko :cite:`doi:10.1021/jm9602928`.

**Synopsis**

  :program:`python` *gen_bm_frags.py* [-h] -i <file> -o <file> [-v] [-m] [-H] [-f <true|false>] [-r] [-s] [-l] [-x] [-c]

**Mandatory options**

 -i <file>

    Input molecule file
  
 -o <file>

    Fragment output file

**Other options**

 -h, --help

    Show help message and exit

 -v
 
    Verbose output (default: false)
    
 -m

    Output the input molecule before the resulting fragments (default: false)
    
 -H
 
    Keep hydrogen atoms (default: false)
    
 -f <true|false>

    Output molecule frameworks (default: true)
    
 -r
 
    Output molecule ring systems (default: false)
    
 -s
 
    Output molecule side chains (default: false)
    
 -l
 
    Output ring system linkers (default: false)
    
 -x
 
    Label atoms with atom mapping IDs (default: false)
    
 -c
  
    Transform fragments into carbon skeletons (default: false)

**Code**

.. literalinclude:: /downloads/gen_bm_frags.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_bm_frags.py>`
