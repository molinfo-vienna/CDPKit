.. index:: Release Notes

Release Notes
=============

Release V1.1.1
--------------

.. rubric:: Improvements
            
- Significantly improved the generation of 2D coordinates for macrocyclic structures

.. rubric:: Bug Fixes

- Fixed an issue with the generatinon of conformers under application of a fixed substructure template where the generated
  conformers sometimes displayed the mirror image of the specified 3D template structure
- The command line tools :doc:`structgen </applications/structgen>` and :doc:`confgen </applications/confgen>` erroneously
  used the already reserved letter **p** as shortcut for the option *--fixed-substr-min-atoms*. The new shortcut is **~**
   
.. rubric:: Miscellaneous Changes 

- Rewrote code that uses the boost filesystem library to use C++17 equivalents
- Compiling CDPKit now requires a compiler with C++17 support

Release V1.1.0
--------------

.. rubric:: New Functionality and Features

- The tool :doc:`tautgen </applications/tautgen>` provides two new tautomer generation modes ``BEST_SCORING`` and ``BEST_SCORING_UNIQUE``
  (the new default mode) for generating only the chemically most reasonable tautomers
- New option in class *Chem::TautomerGenerator* that allows to suppress the output of generated tautomers
  which represent just a different resonance structure of a previously reported tautomeric form
- New :doc:`structgen </applications/structgen>` feature that allows to enforce a particular 3D structure for defined parts of the input molecules
- New :doc:`confgen </applications/confgen>` feature that allows to specify substructures of the input molecules that
  shall adopt a particular conformation which is then kept 'fixed' during conformer generation
  (more information and examples can be found :ref:`here <confgen_notes_v1_1>`)
- Conformer generator settings now allow to specify rotatable bond count dependent values for RMSD threshold, energy window and
  max. output ensemble size 
- The pharmacophore screening application :doc:`psdscreen </applications/psdscreen>` provides a new option *--unique-hits*
  which enforces that a database molecule matched by multiple query pharmacophores is saved only once to the output hit list
- New Python example script for database preparation
- New Python example script demonstrating how the torsion driving functionality can be used for conformer sampling
- The visual molecule and reaction data inspection tool :doc:`ChOX </applications/chox>` now allows to display atom and bond configuration labels
- The 2D molecule structure rendering code (implemented by class *Vis::StructureView2D*) now
  allows to display atom and bond configuration labels
- Full implementation of the CIP sequence rule stack for the correct labeling of atom and bond stereocenters (new class *Chem::CIPConfigurationLabeler*)
- Support for reading/writing molecular structures in XYZ format (classes *Chem::XYZMoleculeReader* and *Chem::XYZMolecularGraphWriter*)
- New command line application :doc:`isogen </applications/isogen>` for the enumeration of R/S and E/Z stereoisomers of molecules
- New class *Chem::StereoisomerGenerator* for the exhaustive enumeration of R/S and E/Z stereoisomers
- New 2D drawing primitives (classes *Vis::Path2D* and *Vis::PathPrimitive2D*) and support for clipping operations (class *Vis::ClipPathPrimitive2D*)
- New class *Chem::BemisMurckoAnalyzer* for the extraction of Bemis-Murcko scaffolds
- New functions for the alignment conformers
- New utility functions *Chem::calcBasicProperties()* that ease the recurring task of initializing *Chem::MolecularGraph*
  and *Chem::Reaction* instances for further processing
   
.. rubric:: Improvements

- Overhaul of the tautomer generation code for increased efficiency and flexibility
- The output conformer ensemble compilation process now strives for higher energetic diversity among the picked conformers which, on average,
  leads to higher accuracy in the reproduction of experimental structures (benchmarking results can be found :ref:`here <confgen_notes_v1_1>`)
- Update of the torsion library used for systematic conformer generation (more information can be found :ref:`here <confgen_notes_v1_1>`)
- Systematic conformer sampling speed optimizations
- Reduction of the memory footprint of the conformer generation procedure which could become unacceptably large
  under some circumstances
- Documentation updates and corrections
- Refactoring of stereochemistry related code
- Cleanup of the CDPL Python bindings code
- When deep copying *Chem::Reaction* or *Chem::Molecule* instances, values of properties referencing atoms and/or bonds (e.g. stereodescriptors, SSSR)
  now get automatically translated to values referencing the corresponding atoms/bonds of the copying target
- Cleanup of CDPL C++ header files
- Added support for building CDPL Python bindings :program:`pip` installer wheel files under Windows
- Added support for building manylinux2014 compliant CDPL Python bindings :program:`pip` installer wheel files
- Build system cleanup
   
.. rubric:: Bug Fixes

- Fixed bugs in classes *Chem::MaxCommonAtomSubstructureSearch* and *Chem::MaxCommonBondSubstructureSearch* that led to a
  loss of expected matches
- Fix for a bug in the SMARTS parser that lead to the storage of wrong bond directions
- Bond direction specifications (up/down) in SMILES and SMARTS strings are now correctly interpreted
- Fixed a bug that may lead to the generation of conformers with wrong geometries at exocyclic double bonds
- Fixed a bug in the :doc:`shapescreen </applications/shapescreen>` tool that lead to the calculation of erroneous similarity scores
  when option *--score-only* was set 
- Fix for a minor bug that affected the indentation of SD-file property entries
- Function overload resolution order fixes in the *CDPL.Math* Python package
- Prevented the throwing of exceptions when the env. variable **LC_ALL** has not been initialized

.. rubric:: API Changes 

- New getter/setter method pair in class *Chem::TautomerGenerator* for suppressing the output of generated tautomers
  which represent just a different resonance structure of a previously reported tautomer
- Data structures with names *ForceField::MMFF94XXXInteractionData* were renamed into *ForceField::MMFF94XXXInteractionList*
  (XXX = force field interaction type)
- New class *ForceField::ElasticPotential* plus elastic potential energy and gradient calculation functions
- New class *Chem::CIPConfigurationLabeler* for the labeling of atom and bond stereocenters
- New class *Chem::StereoisomerGenerator* for the exhaustive enumeration of R/S and E/Z stereoisomers
- New classes *Chem::XYZMoleculeReader* and *Chem::XYZMolecularGraphWriter* implementing reading and writing
  of molecule data in XYZ format
- New 2D drawing primitives (classes *Vis::Path2D* and *Vis::PathPrimitive2D*) and support for clipping operations
  (class *Vis::ClipPathPrimitive2D*)
- New class *Chem::BemisMurckoAnalyzer* for the extraction of Bemis-Murcko scaffolds
- New *CDPL::Chem* functions for the alignment conformers
- Python exports of *Util::Map* and *Util::MultiMap* do not provide the properties *keys*, *values*, and *entries* anymore.
  They were replaced by the corresponding methods *keys()*, *values()* and *items()*
- The *MolProp::getAtomCount()* function has been extended by a *strict* argument which, if set to ``false``, instructs
  the accounting procedure to regard the meaning of generic atom types (e.g. any halogen)
- New utility functions *Chem::calcBasicProperties()* for a more comfortable initialization of *Chem::MolecularGraph*
  and *Chem::Reaction instances* for further processing
- Code in class *GRAIL::GRAILDescriptorCalculator* now calculates a shorter GRAIL descriptor (35 elements) with
  not further subdivided H-bond donor/acceptor feature types
- Class *GRAIL::GRAILDescriptorCalculator* was renamed into *GRAIL::GRAILXDescriptorCalculator*

Release V1.0.0
--------------

 **- Initial release -**
