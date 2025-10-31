Pharmacophore 3D Visualization
==============================

The script *gen_ph4_3d_vis.py* generates 3D visual representations of pharmacophores
read from an input file and writes the resulting vector graphics data to one or more
(in case of multiple input pharmacophores) output file(s).


**Synopsis**

  :program:`python` *gen_ph4_3d_vis.py* [-h] -i <file> -o <file> [-c] [-d]

**Mandatory options**

 -i <file>

    Input pharmacophore file (.pml, .cdf)
    
 -o <file>

    3D visualization data output file (.r3d, .stl, .ply, .wrl)
  
**Other options**

 -h, --help

    Show help message and exit

 -c

    Do not output spheres representing the feature centers (default: false)

 -d
 
    Make vector and plane features undirected (default: false)

**Example**

Generation of a Raster3D file for the pharmacophore of ligand MIT
(complex `1DWC <https://www.rcsb.org/structure/1DWC>`_ ):

.. code-block:: shell
           
   $ python gen_ph4_3d_vis.py -i 1dwc_MIT_ph4.pml -o 1dwc_MIT_ph4.r3d

| :download:`1dwc_MIT.sdf </downloads/1dwc_MIT.sdf>`
| :download:`1dwc_MIT_ph4.pml </downloads/1dwc_MIT_ph4.pml>`
| :download:`1dwc_MIT_ph4.r3d </downloads/1dwc_MIT_ph4.r3d>`
    
.. figure:: /graphics/pymol_MIT_ph4_vis.png
   :scale: 50%
   :alt: PyMOL visualization example

   PyMOL displaying the structure and pharmacophore of ligand MIT

**Code**

.. literalinclude:: /downloads/gen_ph4_3d_vis.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_ph4_3d_vis.py>`
