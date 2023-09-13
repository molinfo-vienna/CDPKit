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

Installers for *macOS* (DMG-file, Apple Silicon processors only), *Linux x86_64* (self-extracting archive) and *Windows 10* (graphical installer
based on `NSIS <https://nsis.sourceforge.io/Download>`_) can be downloaded from the `Releases <https://github.com/molinfo-vienna/CDPKit/releases>`_
page of the `CDPKit GitHub repository <https://github.com/molinfo-vienna/CDPKit>`_. 
The installers also provide the external dependencies of CDPKit (except system libraries). Thus, after finishing the installation process, no additional
software packages have to be installed. 

.. note::

   After the installation process has finished, the ``PATH`` environment variable needs to be edited to include the full path to the **Bin** folder
   below the CDPKit installation directory. Furthermore, to enable the use of the CDPL Python bindings, the ``PYTHONPATH`` environment variable
   must include the full path to the corresponding **Python** subfolder. 

.. _install_from_source:

Installation from source
------------------------

Build requirements
^^^^^^^^^^^^^^^^^^

Compilation of the CDPKit source code requires a properly set up build environment. This includes a C++ compiler toolchain that supports the C++11 standard
(as do current versions of :program:`gcc` and (Apple) :program:`Clang`), the `CMake <https://cmake.org/>`_  makefile generator, and the
development version of several software libraries. The following table provides a complete list of the CDPKit build requirements and dependencies:

==========================  =============  ==========================================================================
Build requirement           Version        Comment
==========================  =============  ==========================================================================
C++11 compliant compiler    -              mandatory
cmake                       >=3.17         mandatory
Python interpreter          3.x            mandatory
boost-devel                 >=1.63         mandatory
boost-python3-devel         >=1.63         optional, required for building CDPL Python bindings
python-devel                3.x            optional, required for building CDPL Python bindings
Qt5-devel                   5.x            optional, required for building Qt rendering backend and GUI application
cairo-devel                 >=1.14         optional, required for building cairo rendering backend
sphinx-build                >=4.5          optional, required for generating CDPKit documentation pages
sphinx-rtd-theme            >=1.0.0        optional, required for generating CDPKit documentation pages
sphinx-inline-tabs          >=2021.4.11b8  optional, required for generating CDPKit documentation pages
sphinxcontrib-bibtex        >=2.5.5        optional, required for generating CDPKit documentation pages
doxygen                     >=1.8.5        optional, required for generating C++ and Python API documentation
==========================  =============  ==========================================================================

Package managers on modern *Linux* systems usually provide all listed software packages in the required minimum versions. 
On *macOS* (version 11.x or higher) the recommended (tested and working) way to install the packages is to use the `Homebrew <https://brew.sh/index>`_ package manager.
*Windows 8/10/11* all packages can be obtained from the `MSYS2 <https://www.msys2.org/>`_ software distribution.
`Sphinx <https://www.sphinx-doc.org/en/master/>`_ and all listed extensions can be installed via :program:`pip`.

Build system configuration and compilation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The configuration and generation of the build system files is performed by the program :program:`cmake`.
In the following `<BUILD-DIR>` refers to the directory that will contain the CDPKit build ouput and `<SOURCE-DIR>` is the directory
providing the CDPKit source code. 
The description of the corresponding build steps on *Windows* assumes that all required software packages were obtained from
the *MSYS2* distribution and that the *MinGW* :program:`gcc` port is used as C++ compiler.

.. rubric:: Linux and macOS

Open a :program:`shell` session and execute:
            
.. code-block:: bash

   $ mkdir <BUILD-DIR>
   $ cd <BUILD-DIR>
   $ cmake <SOURCE-DIR>

.. rubric:: Windows

Open a `MSYS2 MinGW 64-bit command prompt <https://www.msys2.org/docs/terminals>`_ and execute:

.. code-block:: bash

   $ mkdir <BUILD-DIR>
   $ cd <BUILD-DIR>
   $ cmake <SOURCE-DIR> -G "MinGW Makefiles"
   
-----
               
If :program:`cmake` is executed as shown above the default build type will be *Release*. Configuring
for a different build type can be achieved via the argument `-DCMAKE_BUILD_TYPE=<BUILD-TYPE>` on the
:program:`cmake` command line. Possible values of `<BUILD-TYPE>` are:

- Debug
- Release
- RelWithDebInfo
- MinSizeRel

Compilation
^^^^^^^^^^^

If the makefiles have been generated without errors, the compilation process is started by executing

.. rubric:: Linux and macOS

.. code-block:: bash

   $ make

.. rubric:: Windows

.. code-block:: bash

   $ mingw32-make
   
Installation of the generated binaries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After a successful build

.. code-block:: bash

   $  make install

on *Linux* and *macOS*, or

.. code-block:: bash

   $  mingw32-make install

on *Windows*, will install CDPKit in a platform specific default directory (*Linux:* **/opt/**, *macOS:* **/Users/Shared/**, and *Windows:* **C:\\Program Files\\**).
A different installation location can be specified by the argument `-DCMAKE_INSTALL_PREFIX=<INSTALL-DIR>` on
the :program:`cmake` command line (see above).

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

Installing CDPL Python bindings via :program:`pip`
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To install directly from the GitHub repository:

.. code-block:: bash

   $  pip install git+https://github.com/molinfo-vienna/CDPKit.git

Alternatively, to install from a local directory containing the CDPKit sources, navigate to the CDPKit source code folder and run:

.. code-block:: bash

   $  pip install .
