.. index:: single: Molecules; ChEMBL Structure Curation
           single: Molecules; Structure Manipulation
           single: Molecules; Input
           single: Molecules; Output
           single: Molecules; Name Property
           single: Molecules; Property Calculation
           single: Molecules; Atom Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; Bond Property Calculation
           single: Molecules; SSSR Perception
           single: Molecules; SSSR Property
           single: Molecules; Aromaticity Perception
           single: Molecules; Atom Ring Membership Detection
           single: Molecules; Bond Ring Membership Detection
           single: Molecules; Components Perception
           single: Molecules; Components Property
           single: Molecules; Atom Hybridization State Perception
           single: Molecules; Atom Implicit Hydrogen Count Calculation
           single: Atoms; Implicit Hydrogen Count Property
           single: Atoms; Implicit Hydrogen Count Calculation
           single: Atoms; Ring Flag Property
           single: Atoms; Ring Membership Detection
           single: Atoms; Hybridization State Property
           single: Atoms; Hybridization State Perception
           single: Atoms; Aromaticity Flag Property
           single: Atoms; Aromaticity Perception
           single: Atoms; Property Calculation
           single: Bonds; Ring Flag Property
           single: Bonds; Ring Membership Detection
           single: Bonds; Aromaticity Flag Property
           single: Bonds; Aromaticity Perception
           single: Bonds; Property Calculation
           single: Data Formats; MDL SD-Files
           single: Data Formats; SMILES
           
ChEMBL Structure Curation Pipeline
==================================

The script *chembl_preproc.py* Performs molecule standardization according to the ChEMBL structure
curation pipeline workflow :cite:`Bento2020`.

**Synopsis**

  :program:`python` *chembl_preproc.py* [-h] -i <file> -o <file> [-v <0|1|2>] [-p <true|false>] [-d] [-x <true|false>]

**Mandatory options**

 -i <file>

    Input molecule file

 -o <file>

    Output molecule file
  
**Other options**

 -h, --help

    Show help message and exit

 -i <file>

    Input molecule file

 -o <file>

    Output molecule file

 -v <0|1|2>

    Verbosity level (default: 1; 0 -> no console output, 1 -> verbose, 2 -> extra verbose)

 -p <true|false>

    Extract parent structure (default: true)

 -d

    Drop structures that fulfill the exclusion criterions (default: false)

 -x <true|false>

    Standardize structures that fulfill the exclusion criterions (default: true)
  
**Code**

.. literalinclude:: /downloads/chembl_preproc.py
   :language: python
   :linenos:
   :lines: 19-

:download:`Download source file</downloads/chembl_preproc.py>`
