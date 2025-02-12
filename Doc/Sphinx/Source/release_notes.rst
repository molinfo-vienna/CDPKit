.. index:: Release Notes

Release Notes
=============

Release V1.2.2
--------------

.. rubric:: Bug Fixes

- Fix for an issue leading to a segmentation fault during the parsing of partially invalid SMILES/SMARTS strings that occurs
  if a ring closure at a chiral atom cannot be completed due to either missing or erroneously placed closure bond numbers
- Fix for a bug in the command line tool :doc:`structgen </applications/structgen>` that led to process termination due
  to a *Base::ItemNotFound* exception which was thrown when the set time limit got exceeded without having generated a
  complete set of 3D atom coordinates

.. rubric:: New Functionality and Features
                        
- The command line tool :doc:`psdcreate </applications/psdreate>` now offers the possibility to process only a subset of the input molecules
  which can be specified by means of a start (option **-s**) and an end molecule index (option **-e**)
- The command line tool :doc:`psdscreen </applications/psdscreen>` now offers a new option **-r** that allows to specify a report file in which
  sceening hit molecule information will be written as lines of tab-separated values (i.e., without any mol. structure data).
  The new option can be used in additon or instead of option **-o** which, as before, specifies an output file for saving
  aligned hit molecule structures

.. rubric:: Improvements

- Reduction of RAM consumption when querying pharmacophore feature count data stored in \*.psd files
- Reduction of pharmacophore screening database (PSD) file sizes by ~55% due to the introduction of
  more compact molecule/pharmacophore data storage formats
- Additional Python cookbook script demonstrating how to use the stereoisomer enumeration functionality
     
.. rubric:: API Changes
             
- Added new setter/getter method pair *outputZeroBasedIndices(bool)/outputZeroBasedIndices()* to class *Pharm::FileScreeningHitCollector*
  that allows to control whether any indices (mol. index, conf. index, etc.) stored as SD-entries of output molecules shall be zero- or one-based

Release V1.2.1
--------------

.. rubric:: Bug Fixes

- Fix for function *Pharm::removePositionalDuplicates(Pharmacophore&)* which erroneously retained
  the duplicate features (to be removed) instead of the desired features all having unique position and type

.. rubric:: Improvements

- New implementation of Greene's algorithm for the calculation of atom hydrophobicities which
  is now more correct and ~100 times faster than the previous one
- Additional Python cookbook scripts
- Documentation updates
- All disk space consumed by an existing pharmacophore screening database (PSD) that is specified as
  destination file for a new database to be created by the tool :doc:`subsearch </applications/psdcreate>` is now
  completely freed and not just internally marked as unallocated space
  
Release V1.2.0
--------------

.. rubric:: New Functionality and Features

- New utility functions for the manipulation of pharmacophore data
- New command line tool :doc:`subsearch </applications/subsearch>` for substructure searching on molecular data files with support
  for multiple query substructures and customizable logical expressions
- Added support for the I/O of molecular structure data in CML format
- Added support for the I/O of macromolecular structure data in mmCIF format
- New atom classification functions for the detection of bridgehead atoms and spirocenters in complex ring systems
- The residue database now also provides parent structure and single letter code information for a query residue
- New class implementing substructure searching with multiple query substructures that can be combined by boolean expressions
- New class implementing the generation of variably sized hashed 2D and 3D pharmacophore fingerprints
- New class implementing the generation of 881 bit PubChem fingerprints
- New class implementing the generation of 166 bit MACCS key fingerprints
- New class implementing the perception of the extended smallest set of smallest rings of molecular graphs (ESSSR)
- New class implementing the visualization of multiple molecules as separate 2D structure diagrams arranged in a grid of arbitrary size
- New 2D graphics primitive for the rendering of multi-line text blocks supporting several options for the styling of individual text fragments
- New control-parameter allowing to customize the resolution of 2D structure/reaction depictions saved in a pixel-based output format
- Support for atom and bond highlighting in 2D structure/reaction depictions
- Support for the rendering of custom atom and bond labels in 2D structure/reaction depictions
  
.. rubric:: Improvements

- Improved the visual appearance of command line tool progress bars
- Additional Python cookbook scripts
- Sphinx documentation updates
- Improved support for different Python installation flavors on macOS (the help provided by Yakov Pechersky is greatly appreciated)
- Perception of atom/bond stereochemistry from input 3D coordinates in the conformer generation molecule preprocessing stage
  now does not require the presence of explicit hydrogens anymore
- Updated PDB/mmCIF residue dictionary which now features 44906 chemical components
- CDPL Python bindings now support NumPy V≥2.0
- Program :doc:`ChOX </applications/chox>` now uses the same file open/save dialog instance for all opened main windows
- Program :doc:`ChOX </applications/chox>` now supports basic cut/copy/paste as well as drag and drop operations
- Program :doc:`ChOX </applications/chox>` now allows to perform substructure searching with logical combinations of SMARTS patterns
- Program :doc:`ChOX </applications/chox>` now allows to highlight substructures defined by SMARTS patterns
- The SDF data reader (class *Chem::SDFMoleculeReader*) now also accepts input data that do not end with a newline character
- Made the MOL2 data reader (class *Chem::MOL2MoleculeReader*) more tolerant regarding missing sections
- Extended the set of supported chemical elements to atomic number 114
- Control-parameter *Vis::BACKGROUND_COLOR* was replaced by *Vis::BACKGROUND_BRUSH* which now allows to also
  specify a background fill pattern (see class *Vis::Brush*) for 2D structure renderings
- Class *Vis::CairoRenderer2D* now supports the rendering of overlined, underlined and striked-out text
- Support for setting the image output scaling factor in the program :doc:`ChOX </applications/chox>`

.. rubric:: Bug Fixes

- Fixed an issue concerning the calculation of pharmacophore fit scores that previously also considered mappings
  of multiple query features to the same target feature. Now, more correctly, the best score that could be calculated
  for all possible one-to-one feature mappings is reported.
- Fixed a bug in program :doc:`ChOX </applications/chox>` that prevented the successful saving of data in \*.psd format
- Fixed the missing support for certain chemical element symbols in class *Chem::SMARTSMoleculeReader*
- Fixed a bug in class *Math::RegularSpatialGrid* that caused an erroneous transformation of world to grid-local coordinates
- Fixed a problem in *Chem::RECAPFragmentGenerator* that lead to the generation of too few fragments for H-depleted molecules
- Fixed a problem in *Chem::BRICSFragmentGenerator* that lead to the generation of too few fragments for H-depleted molecules
- Fixed an issue with the calculation of text bounds in the implementation of classes *Vis::CairoFontMetrics* and *Vis::QtFontMetrics*
  that lead to too small bounding boxes in the presence of leading and/or trailing whitespace
- Fixed an issue with whitespace-only data elements that were missing in the DOM-trees generated by the internally
  used RapidXml XML-parser library
- Fixed an issue in program :doc:`ChOX </applications/chox>` where the background color setting of 2D structure/reaction depictions got ignored
  when saving data in an image output format
- Fixed several minor bugs in Python cookbook scripts

.. rubric:: API Changes

- New setter/getter method pair *groupReferenceFeatures()/referenceFeaturesGrouped()* in class *Pharm::PharmacophoreFitScore* for controlling
  whether multiple directed features of the same type at the same position shall be considered as independent individual features or as different
  orientation options of a single feature
- New utility functions *Pharm::clearOrientations()*, *Pharm::removePositionalDuplicates()*, *Pharm::removeFeaturesWithType()*
  for the manipulation of pharmacophore data
- Unified the naming of control-parameters and associated functions in namespaces *Chem*, *Pharm*, *Grid*, and *Biomol*
- Renamed function *MolProp::isCarbonylLikeAtom()* into *MolProp::isCarbonylLike()*
- Renamed function *MolProp::isAmideCenterAtom()* into *MolProp::isAmideCenter()*
- New atom classification functions *MolProp::isBridgehead()* and *MolProp::isSpiroCenter()*
- New control-parameters, properties and associated functions in namespace *Chem* for CML data I/O
- New constants in namespace *Biomol::ResidueType* which now fully cover the set of residue types defined by the mmCIF/PDBX specification
- Renamed some previously PDB format-specific control-parameters and associated functions in namespace *Biomol* for 
  dual-use by the mmCIF data I/O code
- New class *Biomol::MMCIFMoleculeReader* for reading macromolecular data in mmCIF format
- New class *Biomol::MMCIFMolecularGraphWriter* for writing macromolecular data in mmCIF format
- New class *Chem::CMLMoleculeReader* for reading molecular data in CML format
- New class *Chem::CMLMolecularGraphWriter* for writing molecular data in CML format
- New data format descriptors in namespaces *Chem::DataFormat* and *Biomol::DataFormat*
- New class *Biomol::MMCIFData* for the in-memory storage and postprocessing of mmCIF formatted input data
- Added new method *getParentCode()* to classes *Biomol::ResidueDictionary* and *Biomol::ResidueDictionary::Entry* for the
  lookup of residue parent structure information
- Added new method *getOneLetterCode()* to classes *Biomol::ResidueDictionary* and *Biomol::ResidueDictionary::Entry* for the
  lookup of residue single letter codes
- New control-parameters, atom properties and associated functions in namespace *Biomol* for mmCIF data I/O 
- Removed function *Biomol::convertMOL2ToPDBResidueInfo()* (the conversion of MOL2 substructure to
  PDB residue/sequence information is now carried out automatically)
- New class *Chem::MultiSubstructureSearch* for performing substructure searching with multiple query substructures that
  can be combined by boolean expressions
- New classes *Descr::NPoint2DPharmacophoreFingerprintGenerator* and *Descr::NPoint3DPharmacophoreFingerprintGenerator*
  for the generation of variably sized hashed 2D and 3D pharmacophore fingerprints
- Removed methods *setNumBits()* and *getNumBits()* of class *Descr::PathFingerprintGenerator* (fp-length is now
  implicitly given by the size of the *Util::BitSet* instance provided as argument to method *generate()*)
- New class *Descr::PubChemFingerprintGenerator* for the generation of 881 bit PubChem fingerprints
- New class *Chem::ExtendedSSSR* for the perception of the extended smallest set of smallest rings (ESSSR)
- New class *Descr::MACCSFingerprintGenerator* for the generation of 166 bit MACCS key fingerprints
- New class *Vis::StructureGridView2D* for the visualization of molecules as 2D structure diagrams 
  arranged in a grid of arbitrary size
- New class *Vis::TextBlockPrimitive2D* for the rendering of multi-line text blocks supporting
  several options for the styling of individual text fragments
- New control-parameter *Vis::OUTPUT_SCLAING_FACTOR* that allows to achieve higher resolutions of 2D structure/reaction
  depictions saved in pixel-based output formats
- New control-parameters, properties and associated functions in namespace *Vis* for the rendering of custom atom and bond labels
  in 2D structure/reaction depictions  
- New control-parameters, properties and associated functions in namespace *Vis* for the customization of the atom and bond highlighting
  style in 2D structure/reaction depictions
- Additional constants in namespace *Chem::AtomType* increasing the coverage of chemical elements up to atomic number 114

.. rubric:: Miscellaneous Changes
  
- CDPL Python bindings wheel files for Linux are now built for a `manylinux_2_28 <https://github.com/pypa/manylinux>`_ environment
- Updated embedded MessagePack library to version 6.1.1
- Updated embedded SQLite3 database to version 3.46.1
- Updated embedded MMTF library to version 1.1.0
- Updated the internally used RapidXml XML-parser library to version 1.13
- Unit test case updates for functionality in namespace *CDPL::Vis*

Release V1.1.1
--------------

.. rubric:: Improvements
            
- Significantly improved the generation of 2D coordinates for macrocyclic structures

.. rubric:: Bug Fixes

- Fixed an issue with the generation of conformers under application of a fixed substructure template where the generated
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
