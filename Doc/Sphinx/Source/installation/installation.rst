Installation
============

.. contents:: CDPKit offers two primary installation methods:
   :local:
   :depth: 1

Installation from source
------------------------

To install CDPKit from source, follow the steps outlined below:

Prerequisites and Dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Mandatory
  
  - C++11 compliant compiler
  - cmake (V >= 3.17)
  - boost-devel (V >= 1.63)
  - python-devel 3.x and Python interpreter

- Optional
  
  - Qt5-devel
  - cairo-devel (V >= 1.14)
  - sqlite-devel V3
  - sphinx (V >= 4.5)
  - sphinx-rtd-theme
  - sphinxcontrib.bibtex
  - doxygen (V >= 1.8.5)

.. note::

   Ensure you have a working Python environment. CDPKit is primarily used with Python, so ensure Python 3.x is installed on your system.

Building and Installing CDPKit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Generate the makefiles using cmake:

.. code-block:: bash

   mkdir <BUILD-DIR>
   cd <BUILD-DIR>
   cmake <CDPKIT-SOURCE-DIR>

Once the makefiles are generated without errors, start the build process:

.. code-block:: bash

   make
                
After a successful build:

.. code-block:: bash

   make install

This will install CDPKit in the ``/opt`` directory. To specify a different installation location, use ``-DCMAKE_INSTALL_PREFIX=<INSTALL-DIR>`` with the :program:`cmake` command.

Installation via :program:`pip` (CDPL Python bindings only)
-----------------------------------------------------------

Using :program:`pip` will compile the sources on-the-fly (this may take some time) to build and install the CDPL Python bindings.

Prerequisites and Dependencies
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

- Mandatory
  
  - C++11 compliant compiler
  - boost-devel (V >= 1.63)
  - python-devel and Python interpreter (V >= 3.6)

- Optional
  
  - Qt5-devel
  - cairo-devel (V >= 1.14)
  - sqlite-devel V3

Installing CDPL Python bindings via :program:`pip`
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To install directly from the GitHub repository:

.. code-block:: bash

   pip install git+https://github.com/molinfo-vienna/CDPKit.git

Alternatively, to install from a local directory containing the CDPKit sources, navigate to the CDPKit source code folder and run:

.. code-block:: bash

   pip install .
