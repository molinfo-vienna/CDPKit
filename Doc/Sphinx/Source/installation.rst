Installing CDPKit
=================

.. index:: Installation

CDPKit can be installed in different ways:

- :ref:`Install the latest official binary release <install_official_release>`. This
  is the best approach for most users. It will provide a full-featured stable CDPKit version
  and pre-built installers are available for most platforms.

- :ref:`Build and install from source <install_from_source>`. This is the best option for users who want the
  latest-and-greatest features and aren't afraid of compiling C++ code and/or run brand-new software.
  This is also needed for users who run an operating system version for which no installer has been
  provided and for users who wish to contribute to the project.

- :ref:`Installation via pip <install_via_pip>`.
  :program:`pip` will only install the CDPL Python bindings. This is the best option for users who
  only want to develop or run Python software that uses CDPL functionality.

.. _install_official_release:

Install official binary release
-------------------------------

Installers for macOS (DMG-file, Apple A1 and A2 processors only), Linux x86_64 (self-extracting archive) and Windows 10 (graphical installer
based on `NSIS <https://nsis.sourceforge.io/Download>`_) can be downloaded from the `Releases <https://github.com/molinfo-vienna/CDPKit/releases>`_
page of the `CDPKit GitHub repository <https://github.com/molinfo-vienna/CDPKit>`_. 
The installers also provide all non-system software libraries CDPKit is depending on. Thus, after finishing the installation process, CDPKit should
work without having to install additional software packages. 

.. note::

   After the installation process has finished the ``PATH`` environment variable has to be edited and include the full path to the **Bin** subfolder
   of the CDPKit installation directory. Furthermore, in order to be able to use the CDPL Python bindings, the ``PYTHONPATH`` environment variable
   must include the full path to the corresponding **Python** subfolder.

.. _install_from_source:

Installation from source
------------------------

Build requirements
^^^^^^^^^^^^^^^^^^

CDPKit relies on several external software libraries and requires a properly set-up build environment. The following
table summarizes the dependencies of CDPKit which must installed on the build host for a successful compilation of
the CDPKit sources:

==========================  =======  ==========================================================================
Build requirement           Version  Comment
==========================  =======  ==========================================================================
C++11 compliant compiler    ..       mandatory
cmake                       >=3.17   mandatory
Python interpreter          3.x      mandatory
boost-devel                 >=1.63   mandatory
boost-python3-devel         >=1.63   optional, required for building CDPL Python bindings
python-devel                3.x      optional, required for building CDPL Python bindings
Qt5-devel                   5.x      optional, required for building Qt rendering backend and GUI application
cairo-devel                 >=1.14   optional, required for building cairo rendering backend
sqlite-devel                3        optional, required for pharmacophore screening functionality
sphinx                      >=4.5    optional, required for generating CDPKit documentation pages
sphinx-rtd-theme            >=1.0.0  optional, required for generating CDPKit documentation pages
sphinxcontrib.bibtex        >=2.5.5  optional, required for generating CDPKit documentation pages
doxygen                     >=1.8.5  optional, required for generating C++ and Python API documentation
==========================  =======  ==========================================================================


Building and installing CDPKit
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Generate the makefiles using :program:`cmake`:

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

This will install CDPKit in the ``/opt`` directory. To specify a different installation location, provide `-DCMAKE_INSTALL_PREFIX=<INSTALL-DIR>` as argument of the :program:`cmake` command.

.. _install_via_pip:

Installation via :program:`pip` (CDPL Python bindings only)
-----------------------------------------------------------

Using :program:`pip` will compile the sources on-the-fly (this may take some time) to build and install the CDPL Python bindings.

Prerequisites and dependencies
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
