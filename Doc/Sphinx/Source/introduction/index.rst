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

.. index:: License

Licensing
---------

The CDPKit source code is released under the terms of the `GNU Lesser General Public License (LGPL) V2.1-or-later <https://www.gnu.org/licenses/old-licenses/lgpl-2.1.en.html>`_.
CDPKit documentation is licensed under the terms of the `GNU Free Documentation License (GFDL) V1.2-or-later <https://www.gnu.org/licenses/old-licenses/fdl-1.2.en.html>`_.

.. index:: Related Software

Related software projects
-------------------------

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

* Source code:
  
  Thomas Seidel, *Chemical Data Processing Toolkit source code repository*, https://github.com/molinfo-vienna/CDPKit
  
* Documentation:
  
  Thomas Seidel, Oliver Wieder, *Chemical Data Processing Toolkit documentation pages*, https://cdpkit.org

.. index:: People, Authors
           
People
------

- `Thomas Seidel <https://cheminfo.univie.ac.at/people/senior-scientists/thomas-seidel>`__ (project founder, main developer)
- `Oliver Wieder <https://cheminfo.univie.ac.at/people/post-doctoral-researchers/oliver-wieder>`__ (documentation)
