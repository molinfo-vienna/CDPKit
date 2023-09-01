Introduction
============

.. index:: About

About
-----

The *Chemical Data Processing Toolkit* (CDPKit) is an open-source cheminformatics software toolkit implemented in C++. In addition to the C++ API a Python-interfacing layer is provided that allows to use all of CDPKit's functionality from Python scripts.
CDPKit features a high-quality and well-tested modular implementation of basic functionality typically required by any higher-level software application in the field of cheminformatics. 
This includes data structures for the representation and analysis of chemical structures and reactions, routines for the I/O of small molecule, macromolecular and reaction data in different file formats (MDL Mol, SDF, Rxn, RDF, Mol2, PDB, MMTF, SMILES, SMARTS, etc.), functionality for ring and aromaticity perception, pharmacophore generation, substructure searching, max. common substructure searching, molecular fingerprinting, molecule fragment generation (RECAP :cite:`doi:10.1021/ci970429i`, BRICS :cite:`https://doi.org/10.1002/cmdc.200800178`), 2D structure layout and visualization, 3D structure and conformer generation :cite:`doi:10.1021/acs.jcim.3c00563`, physicochemical property prediction, and so on.

At its core, CDPKit provides a set of command line tools and software libraries (CDPL) that enable researchers to work with molecular data in a systematic and efficient manner, allow a seamless integration with other software and databases, and to develop their own C++ or Python cheminformatics software applications.

CDPKit integrates especially well with machine learning and data mining libraries, enabling scientists to build predictive models for various molecular 
properties. This makes it a valuable toolkit for developing software in the field of computational drug discovery, where machine learning is employed to predict the biological activity, toxicity, 
and other properties of potential drug candidates. An integration example can be found in the source code of the software described in :cite:t:`molecules26206185`.

.. **Oliver's Text**

.. CDPKit is an open-source cheminformatics software toolkit implemented in C++. 
.. In addition to the C++ API, a Python-interfacing layer is provided that allows users to harness all of CDPKit's functionality from Python code. 
.. CDPKit boasts a high-quality, well-tested, and modular implementation of basic functionality typically required by any higher-level 
.. software application in the realm of cheminformatics. 

.. Key Features
.. ^^^^^^^^^^^^

.. CDPKit offers a vast range of functionality beyond the basic usage example shown above. Some areas to explore include:

.. - Substructure Searching 
..   CDPKit provides powerful methods to search for substructures within molecules.

.. - Descriptor Calculation 
..   With CDPKit, you can calculate various molecular descriptors, such as Lipinski's Rule-of-Five properties, topological fingerprints, and much more. 
..   These descriptors are pivotal for modeling molecular properties and predicting biological activities.

.. - Chemical Reactions 
..   CDPKit fully supports chemical reactions, offering dedicated data structures and functionality for I/O, reaction substructure search, 
..   2D visualization, reaction transformations, and more.

.. - Machine Learning Integration 
..   Seamlessly integrate CDPKit with machine learning libraries like scikit-learn, PyTorch, and TensorFlow. Utilize CDPKit for 
..   preprocessing molecular data, extracting features, and building predictive models for diverse chemical properties.

.. Data Handling and Analysis
.. ^^^^^^^^^^^^^^^^^^^^^^^^^^

.. CDPKit features include data structures for the representation and analysis of chemical structures, routines for the I/O of small 
.. molecule and macromolecular data in various file formats (MDL Mol and SDF, Mol2, PDB, MMTF, SMILES, etc.), ring and aromaticity perception, 
.. pharmacophore generation, substructure searching, molecular fingerprinting, molecule fragment generation (RECAP, BRICS), 2D structure layout and 
.. visualization, 3D structure and conformer generation (`CONFORT <https://www.researchsquare.com/article/rs-1597257/v1>`_), physicochemical property prediction, and more.

.. Integration and Utility
.. ^^^^^^^^^^^^^^^^^^^^^^^

.. At its core, CDPKit delivers a suite of command line tools and software libraries (CDPL) that empower researchers to work with 
.. molecular data systematically and efficiently. This ensures seamless integration with other software and databases. 
.. Moreover, CDPKit's integration with various machine learning and data mining libraries enables scientists to construct predictive models 
.. for molecular properties. This positions it as a valuable asset in computational drug discovery, where machine learning is harnessed 
.. to predict the biological activity, site of metabolism prediction, toxicity, and other attributes of potential drug candidates. 
.. An example of this integration is showcased in the source code of this `publication <https://www.mdpi.com/1420-3049/26/20/6185>`_.

.. index:: License

Licensing
---------

The CDPKit source code is released under the terms of the `GNU Lesser General Public License (LGPL) V2.1-or-later <https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html>`_.
CDPKit documentation is licensed under the terms of the `GNU Free Documentation License (GFDL) V1.2-or-later <https://www.gnu.org/licenses/old-licenses/fdl-1.2.en.html>`_.

.. index:: Related Software

Related software projects
-------------------------

- `Python scripts for the generation of GRAIL datasets <https://github.com/molinfo-vienna/GRAIL-Scripts>`_ :cite:`doi:10.1021/acs.jctc.8b00495`

.. index:: Publications
           
Scientific publications
-----------------------

.. bibliography::
   :list: bullet
   :filter: False

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

Source code:
  Thomas Seidel, *Chemical Data Processing Toolkit source code repository*, https://github.com/molinfo-vienna/CDPKit
  
Documentation:
  Thomas Seidel, Oliver Wieder, *Chemical Data Processing Toolkit documentation pages*, https://cdpkit.org

.. index:: People, Authors
           
People
------

- `Thomas Seidel <https://cheminfo.univie.ac.at/people/senior-scientists/thomas-seidel>`__ (project founder, main developer)
- `Oliver Wieder <https://cheminfo.univie.ac.at/people/post-doctoral-researchers/oliver-wieder>`__ (documentation)
