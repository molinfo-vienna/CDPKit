.. index:: Introduction

Introduction
============

.. index:: About

About
-----

*CDPKit* (short for *Chemical Data Processing Toolkit*) is an open-source cheminformatics toolkit implemented in C++. 
CDPKit comprises a suite of software tools and a programming library called the *Chemical Data Processing Library* (CDPL) which
provides a high-quality and well-tested modular implementation of basic functionality typically required by any higher-level
software application in the field of cheminformatics.
In addition to the CDPL C++ API, an equivalent Python-interfacing layer is provided that allows to harness all of CDPL's
functionality easily from Python code. 

.. index:: Key Features

.. rubric:: Key Features

- Data structures for the representation and processing of molecules, chemical reactions and pharmacophores
- Routines for all typical cheminformatics pre-processing tasks (e.g. ring and aromaticity perception, stereochemistry processing, ...)
- Powerful methods for molecule and reaction substructure searching
- Readers/writers for various file formats (MDL Mol, SDF, Rxn, RDF, Mol2, PDB, MMTF, SMILES, SMARTS, etc.) allowing the I/O of
  small molecule, macromolecular, reaction and pharmacophore data 
- Molecule fragmentation algorithms (RECAP :cite:`doi:10.1021/ci970429i`, BRICS :cite:`https://doi.org/10.1002/cmdc.200800178`)
- Generation of molecule and pharmacophore fingerprints (e.g. ECFP :cite:`doi:10.1021/ci100050t`)
- Large collection of implemented chemical structure descriptors
- 2D structure layout and rendering of molecules and reactions
- Gaussian shape-based molecule alignment and descriptor calculation :cite:`https://doi.org/10.1002/(SICI)1096-987X(19961115)17:14<1653::AID-JCC7>3.0.CO;2-K`
- Pharmacophore generation, alignment and screening
- 3D structure and conformer generation :cite:`doi:10.1021/acs.jcim.3c00563`
- Prediction of a wide panel of physicochemical properties
- Full-blown test-suite compliant implementation of the MMFF94 :cite:`https://doi.org/10.1002/(SICI)1096-987X(199604)17:5/6<490::AID-JCC1>3.0.CO;2-P` force field
- Runs without flaws on Linux, macOS and Windows
- C++ implementation follows best practices for a maximum of robustness and speed
- ... and many more ...

.. rubric:: Machine Learning Integration
            
CDPKit seamlessly integrates with machine learning libraries like `scikit-learn <https://scikit-learn.org>`_, `PyTorch <https://pytorch.org/>`_, 
and `TensorFlow <https://www.tensorflow.org/>`_. Utilizing CDPKit for tasks like molecular data I/O, feature extraction, descriptor calculations, and so on,
greatly aids scientists that intend to build ML models for the prediction of physicochemical properties, biological activity, site of metabolism ,
toxicity, and other attributes of potential drug candidates. An example of such an integration with ML methods is showcased in the 
source code of the software described in :cite:t:`molecules26206185`.

.. index:: License

License
-------

The CDPKit source code is released under the terms of the `GNU Lesser General Public License (LGPL) V2.1-or-later <https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html>`_.
CDPKit documentation is licensed under the terms of the `GNU Free Documentation License (GFDL) V1.2-or-later <https://www.gnu.org/licenses/old-licenses/fdl-1.2.en.html>`_.
Code snippets in tutorials and the source code of CDPL programming examples are distributed under the terms of the `Zero-Clause BSD License (0BSD) <https://opensource.org/license/0bsd>`_.

.. index:: Related Software

Related software
----------------

Examples of software projects using CDPKit functionality:

- `FAME.AL: Site-of-metabolism prediction with active learning <https://github.com/molinfo-vienna/FAME.AL>`_ :cite:`doi:10.1021/acs.jcim.3c01588`
- `Python scripts for the generation of GRAIL datasets <https://github.com/molinfo-vienna/GRAIL-Scripts>`_ :cite:`doi:10.1021/acs.jctc.8b00495`
- `Scripts implementing the Common Hits Approach (CHA) <https://github.com/molinfo-vienna/commonHitsApproach>`_ :cite:`doi:10.1021/acs.jcim.6b00674`
- `Workflow scripts for the generation of receptor-based pharmacophore models (apo2ph4) <https://github.com/molinfo-vienna/apo2ph4>`_ :cite:`ph15091122`
- `Analysis of MD-trajectories of ligand-receptor complexes regarding the frequency of observable non-bonding interactions <https://github.com/molinfo-vienna/Ligand-Interaction-Maps>`_
- `Implementation of the QPhAR algorithm <https://github.com/StefanKohlbacher/QuantPharmacophore>`_ :cite:`doi:10.1021/acs.jcim.6b00674`

.. index:: Publications
           
Scientific publications
-----------------------

Published scientific work that relies on CDPKit functionality:

.. bibliography::
   :list: bullet
   :filter: False

   doi:10.1021/acs.jcim.3c01588
   doi:10.1021/acs.jcim.3c00563
   molecules26206185
   doi:10.1021/acs.jcim.2c00814
   ph15091122
   Kohlbacher2021
   doi:10.1021/acs.jctc.8b00495
   doi:10.1021/acs.jcim.6b00674

.. index:: Citing
           
How to cite
-----------

- *Source code:* Thomas Seidel, *Chemical Data Processing Toolkit source code repository*, https://github.com/molinfo-vienna/CDPKit
- *Documentation:* Thomas Seidel, Oliver Wieder, *Chemical Data Processing Toolkit documentation pages*, https://cdpkit.org

.. index:: People, Authors
           
People
------

- `Thomas Seidel <https://cheminfo.univie.ac.at/people/senior-scientists/thomas-seidel>`__ (project founder, main developer)
- `Oliver Wieder <https://cheminfo.univie.ac.at/people/post-doctoral-researchers/oliver-wieder>`__ (documentation)
