.. index:: single: Biological Macromolecules; Input
           single: Biological Macromolecules; Processing
           single: Biological Macromolecules; Ligand Interaction Analysis
           single: Biological Macromolecules; Residue Processing
           single: Biological Macromolecules; Primary Structure Analysis
           single: Molecules; Pharmacophore Generation
           single: Molecules; Atom Processing
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Structure Manipulation
           single: Molecules; Property Calculation
           single: Molecules; Fragments
           single: Molecules; Atom Hybridization State Perception
           single: Molecules; Atom Implicit Hydrogen Count Calculation
           single: Molecules; Aromaticity Perception
           single: Molecules; SSSR Perception
           single: Molecules; SSSR Property
           single: Molecules; Hydrogen Completion
           single: Molecules; Hydrogen 3D Coordinates Calculation
           single: Molecules; Atom Ring Membership Perception
           single: Molecules; Bond Ring Membership Perception
           single: Molecules; Atom Hydrophobicity Calculation
           single: Molecules; Preparation for Pharmacophore Generation
           single: Atoms; Property Calculation
           single: Atoms; Chain ID Property
           single: Atoms; Residue Three-Letter Code Property
           single: Atoms; Residue Sequence Number Property
           single: Atoms; Aromaticity Flag Property
           single: Atoms; Aromaticity Perception
           single: Atoms; Ring Flag Property
           single: Atoms; Ring Membership Perception
           single: Atoms; Hybridization State Perception
           single: Atoms; Hybridization State Property
           single: Atoms; Implicit Hydrogen Count Calculation
           single: Atoms; Implicit Hydrogen Count Property
           single: Atoms; Hydrophobicity Calculation
           single: Atoms; Hydrophobicity Property
           single: Bonds; Property Calculation
           single: Bonds; Aromaticity Flag Property
           single: Bonds; Aromaticity Perception
           single: Bonds; Ring Flag Property
           single: Bonds; Ring Membership Perception
           single: Pharmacophores; Output
           single: Pharmacophores; Generation
           single: Pharmacophores; Preparation for Generation
           single: Pharmacophores; Processing
           single: Pharmacophore Features; Type Property
           single: Pharmacophore Features; Substructure Property
           single: Pharmacophore Features; Environment Residue Info Property
           single: Data Formats; MMTF
           single: Data Formats; MOL2
           single: Data Formats; PDB
           single: Data Formats; mmCIF
           single: Data Formats; PML
           single: Data Formats; CDF
           
Ligand-receptor Interaction Pharmacophores
==========================================

The script *gen_ia_ph4s.py* generates pharmacophores describing the interactions between a given receptor structure and a set of
ligand molecules.

**Synopsis**

  :program:`python` *gen_ia_ph4s.py* [-h] -r <file> -l <file> -o <file> [-i <file>] [-s <res-id> [<res-id> ...]] [-q] [-x]

**Mandatory options**

 -r <file>

    Receptor structure input file (\*.mol2, \*.pdb, \*.mmtf, \*.cif, \*.mmcif)

 -l <file>

    Ligand structure input file (\*.sdf, \*.mol2, \*.cdf)

 -o <file>

    Pharmacophore output file (\*.pml, \*.cdf)

**Other options**

 -h, --help

    Show help message and exit

 -i
 
    Interaction data output file
 
 **-s <res-id> [<res-id> ...]**

    Whitespace separated list of identifiers of residues to remove from the receptor structure (e.g. an existing ligand).
    Residue identifiers consist of three components separated by an underscore: [chain id]_[tlc]_[res. seq. no.].
    The individual components are optional and the whole string is interpreted as a regular expression that gets matched against the residue id of
    each receptor atom. Examples: HOH -> rem. all waters, A_MET -> remove all MET residues of chain A,
    _300$ -> remove all residues with sequ. number 300

 -q

    Disable progress output (default: false)

 -x

    Generate exclusion volumes (default: false)
  
**Code**

.. literalinclude:: /downloads/gen_ia_ph4s.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_ia_ph4s.py>`
