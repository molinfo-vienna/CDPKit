.. index:: single: Descriptors; Receptor Binding Pocket Descriptor Generation
           single: Molecules; Descriptor Generation
           single: Molecules; Input
           single: Molecules; MMFF94 Atom Typing
           single: Molecules; MMFF94 Bond Typing
           single: Molecules; MMFF94 Partial Charge Calculation
           single: Molecules; MMFF94 Aromaticity Perception
           single: Molecules; MMFF94 Aromatic Ring Set Property
           single: Molecules; Property Calculation
           single: Molecules; Atom Processing
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Fragments
           single: Molecules; Atom Processing
           single: Molecules; Structure Manipulation
           single: Molecules; Atom Hybridization State Perception
           single: Molecules; Atom Implicit Hydrogen Count Calculation
           single: Molecules; Aromaticity Perception
           single: Molecules; SSSR Perception
           single: Molecules; SSSR Property
           single: Molecules; Hydrogen Completion
           single: Molecules; Hydrogen 3D Coordinates Calculation
           single: Molecules; Atom Ring Membership Detection
           single: Molecules; Bond Ring Membership Detection
           single: Atoms; Property Calculation
           single: Atoms; Chain ID Property
           single: Atoms; Residue Three-Letter Code Property
           single: Atoms; Residue Sequence Number Property
           single: Atoms; Aromaticity Flag Property
           single: Atoms; Aromaticity Perception
           single: Atoms; Ring Flag Property
           single: Atoms; Ring Membership Detection
           single: Atoms; Hybridization State Perception
           single: Atoms; Hybridization State Property
           single: Atoms; Implicit Hydrogen Count Calculation
           single: Atoms; Implicit Hydrogen Count Property
           single: Atoms; MMFF94 Numeric Type Property
           single: Atoms; MMFF94 Symbolic Type Property
           single: Atoms; MMFF94 Partial Charge Property
           single: Atoms; MMFF94 Atom Typing
           single: Atoms; MMFF94 Partial Charge Calculation
           single: Bonds; Property Calculation
           single: Bonds; MMFF94 Bond Typing
           single: Bonds; MMFF94 Bond Type Index Property
           single: Bonds; Aromaticity Flag Property
           single: Bonds; Aromaticity Perception
           single: Bonds; Ring Flag Property
           single: Bonds; Ring Membership Detection
           single: Biological Macromolecules; Input
           single: Biological Macromolecules; Processing
           single: Biological Macromolecules; Binding Site Characterization
           single: Biological Macromolecules; Residue Processing
           single: Biological Macromolecules; Primary Structure Analysis
           single: Force Fields; MMFF94 Atom Typing
           single: Force Fields; MMFF94 Bond Typing
           single: Force Fields; MMFF94 Partial Charge Calculation
           single: Force Fields; MMFF94 Aromaticity Perception
           single: Data Formats; PDB
           single: Data Formats; mmCIF
           single: Data Formats; MMTF
           single: Data Formats; MOL2
           
Receptor Binding Pocket Descriptor
==================================

The script *gen_kuvek_bp_descr.py* generates and outputs a binding pocket shape/electrostatics descriptor for a given receptor structure according to the procedure devised by Kuvek et al.

**Synopsis**

  :program:`python` *gen_kuvek_bp_descr.py*  [-h] -i <file> -o <file> -c <float> <float> <float> [-r <float>] [-x <float> <float>] [-y <float> <float>] [-z <float> <float>] [-s <res-id> [<res-id> ...]] [-n <int>] [-t] [-p] [-q]

**Mandatory options**

 -i <file>

    Receptor structure input file (.mol2, .pdb, .mmtf, .cif, .mmcif)

 -o <file>

    Descriptor output file

 -c <float> <float> <float>
    
**Other options**

 -h, --help

    Show help message and exit
 
 -n <integer>

    Number of intersection test vectors (default: 492)

 -r <float>

    Probe sphere radius (default: 20.0)

 **-s <res-id> [<res-id> ...]**

    Whitespace separated list of identifiers of residues to remove from the receptor structure (e.g. an existing ligand).
    Residue identifiers consist of three components separated by an underscore: [chain id]_[tlc]_[res. seq. no.].
    The individual components are optional and the whole string is interpreted as a regular expression that gets matched against the residue id of
    each receptor atom. Examples: HOH -> rem. all waters, A_MET -> remove all MET residues of chain A,
    _300$ -> remove all residues with sequ. number 300

 -x <float> <float>

    Allowed test vector x coordinate range. If a test vector is outside of this range then the associated descr. element will not be output (default: [-1.0, 1.0])
    
 -y <float> <float>

    Allowed test vector y coordinate range. If a test vector is outside of this range then the associated descr. element will not be output (default: [-1.0, 1.0])

 -z <float> <float>

    Allowed test vector z coordinate range. If a test vector is outside of this range then the associated descr. element will not be output (default: [-1.0, 1.0])
  
 -t

    Output test vector x, y and z coordinates for each descriptor element (default: false)

 -p

    Output test vector atom intersection point x, y and z coordinates for each descriptor element (default: false)
    
 -q

    Disable progress output (default: false)

**Code**

.. literalinclude:: /downloads/gen_kuvek_bp_descr.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/gen_kuvek_bp_descr.py>`
