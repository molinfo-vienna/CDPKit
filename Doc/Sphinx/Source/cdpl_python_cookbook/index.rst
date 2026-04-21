.. index:: single: Python; Code Snippets
           single: Python; Examples
           single: Python; Cookbook

CDPL Python Cookbook
====================

This 'cookbook' provides a set of scripts that demonstrate how often occurring tasks in cheminformatics can be accomplished
with Python code that utilizes functionality offered by the CDPL. To be able to understand the CDPL-specific parts of the code
it is highly recommended to first have an in-depth look at the :doc:`../cdpl_python_tutorial/index` which imparts valuable
knowledge regarding basic concepts and the work with fundamental data structures.

All scripts are ready-to-run and have been designed to be executed on the command line. Most of the scripts require arguments to
be specified (e.g. path to input/output files). Information on required/supported arguments can be obtained by running the scripts
without arguments.

The source code provided by this cookbook may be used without restrictions for any purpose under the terms of the
`Zero-Clause BSD License (0BSD) <https://opensource.org/license/0bsd>`_.

.. note::
   The scripts require a properly set up installation of the CDPL Python bindings.
   Please visit section :doc:`../installation` for further information.

.. tip::
   To quickly find cookbook scripts that cover a certain topic or utilize a particular package/class/method/function it is advisable to use
   the built-in search functionality and/or consult the page `index <../genindex.html>`_.

.. toctree::
   :maxdepth: 4
   :numbered:
      
   chem/index
   pharm/index
   molprop/index
   descr/index
   confgen/index
   forcefield/index
   shape/index
   vis/index
.. biomol/index
