Ligand-receptor Interaction Pharmacophores
==========================================

The script *gen_ia_ph4s.py* generates pharmacophores describing the interactions between a given receptor structure and a set of
provided ligand molecules.

**Synopsis**

  :program:`python` *gen_ia_ph4s.py* [-h] -r <file> -l <file> -o <file> [-s <three-letter code> [<three-letter code> ...]] [-q] [-x]

**Mandatory options**

 -r <file>

    Receptor structure input file (\*.mol2, \*.pdb, \*.mmtf, \*.cif, \*.mmcif)

 -l <file>

    Ligand structure input file (\*.sdf, \*.mol2, \*.cdf)

 -o <file>

    Pharmacophore output file (\*.pml, \*.cdf)

**Other options**

 -h, --help

    Show this help message and exit
 
 **-s <three-letter code> [<three-letter code> ...]**

    Whitespace separated list of PDB three-letter codes specifying residues to
    remove from the receptor structure (e.g. an existing ligand)

 -q

    Disable progress output (default: false)

 -x

    Generate exclusion volumes (default: false)
  
**Code**

.. literalinclude:: /downloads/gen_ia_ph4s.py
   :language: python
   :linenos:
   :lines: 21-

:download:`Download source file</downloads/gen_ia_ph4s.py>`
