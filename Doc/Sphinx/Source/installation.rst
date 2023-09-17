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

Installers for macOS (DMG-file, Apple Silicon processors only), Linux x86_64 (self-extracting archive) and Windows 10 (graphical installer
based on `NSIS <https://nsis.sourceforge.io/Download>`_) can be downloaded from the `Releases <https://github.com/molinfo-vienna/CDPKit/releases>`_
page of the `CDPKit GitHub repository <https://github.com/molinfo-vienna/CDPKit>`_. These installer packages will provide everything CDPKit has to offer
which comprises:

- Command line tools and GUI-based applications
- CDPL binaries for dynamic linking
- CDPL binaries for static linking
- CDPL C++ header files
- CDPL Python bindings
- CDPL Python examples
- Offline CDPKit documentation
  
The installers incorporate and install all external dependencies of CDPKit. Thus, after finishing the installation process, no additional
software packages need to be installed. 

.. note::

   After the installation process has finished, the **PATH** environment variable needs to be edited to include the full path to the :file:`Bin` folder
   below the CDPKit installation directory. Furthermore, to enable the use of the CDPL Python bindings, the **PYTHONPATH** environment variable
   must include the full path to the corresponding :file:`Python` subfolder. 

.. _install_from_source:

Installation from source
------------------------

Build requirements
^^^^^^^^^^^^^^^^^^

Compilation of the CDPKit source code requires a properly set up build environment. This includes a C++ compiler toolchain that supports the C++11 standard,
the `CMake <https://cmake.org/>`_ makefile generator, and the development version of several software libraries. The following table provides a complete
list of the CDPKit build requirements and dependencies:

==========================  =============  =================================================================================================
Build requirement           Version        Comment
==========================  =============  =================================================================================================
C++11 compliant compiler    -              mandatory, tested: :program:`gcc` V4.8+, :program:`Apple Clang` V12.0+ , and :program:`MSVC` V1930+
cmake                       3.17+          mandatory
Python interpreter          3.6+           mandatory
boost-devel                 1.63+          mandatory
boost-python3-devel         1.63+          optional, required for building CDPL Python bindings
python-devel                3.6+           optional, required for building CDPL Python bindings
Qt5-devel                   5.6+           optional, required for building Qt rendering backend and GUI application
cairo-devel                 1.14+          optional, required for building cairo rendering backend
sphinx-build                4.5+           optional, required for generating CDPKit documentation pages
sphinx-rtd-theme            1.0.0+         optional, required for generating CDPKit documentation pages
sphinx-inline-tabs          2021.4.11b8+   optional, required for generating CDPKit documentation pages
sphinxcontrib-bibtex        2.5.5+         optional, required for generating CDPKit documentation pages
doxygen                     1.8.5+         optional, required for generating C++ and Python API documentation
==========================  =============  =================================================================================================

Build environment setup
^^^^^^^^^^^^^^^^^^^^^^^

.. rubric:: Linux

Package managers on modern Linux systems usually provide all listed software packages in the required minimum versions.

.. rubric:: macOS

On macOS (*Big Sur* is the minimum supported version) the recommended way to install everything that is needed for a successful build
is to use the `Homebrew <https://brew.sh/index>`_ package manager.

.. rubric:: Windows

On Windows (8/10/11) the fastest way to get started is to set up a :program:`MinGW` build environment by installing packages
from the `MSYS2 <https://www.msys2.org/>`_ software distribution. However, a major flaw here is that the built CDPL Python bindings
will only work with the Python interpreter shipped by MSYS2.
In order to make the CDPL Python bindings work with an official Python distribution obtained from https://www.python.org, a CDPKit build by means
of Microsoft's Visual C++ compiler (:program:`MSVC`) toolchain is required.

------

`Sphinx <https://www.sphinx-doc.org/en/master/>`_ and all listed extensions can be installed via the Python package installer :program:`pip`.

Build system configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^

The configuration and generation of the build system files is performed by the command :command:`cmake`.
In the following :file:`<BUILD-DIR>` refers to the directory that will contain the CDPKit build ouput and :file:`<SOURCE-DIR>` is the directory
providing the CDPKit source code. 
The description of the build steps on Windows depends on whether the build environment is based on MSYS2 (employing the :program:`MinGW gcc` port
as C++ compiler) or utilizes the :program:`MSVC` toolset.

.. tab:: Linux and macOS

         Open a terminal and execute:
            
         .. code-block:: bash

                         $ mkdir <BUILD-DIR>
                         $ cd <BUILD-DIR>
                         $ cmake <SOURCE-DIR>

.. tab:: Windows/MinGW

         Open a `MSYS2 MinGW 64-bit <https://www.msys2.org/docs/terminals>`_ command prompt and execute:

         .. code-block:: bash
                         
                         $ mkdir <BUILD-DIR>
                         $ cd <BUILD-DIR>
                         $ cmake <SOURCE-DIR> -G "MinGW Makefiles"

.. tab:: Windows/MSVC

         Open a `x64 Native Tools Command Promp <https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170>`_ via the
         Windows start menu and execute:

         .. code-block:: console

                         > mkdir <BUILD-DIR>
                         > cd <BUILD-DIR>
                         > cmake <SOURCE-DIR> -G "NMake Makefiles"

If :command:`cmake` is executed as shown above the default build type will be ``Release``. Configuring for a different build type can be achieved via the argument
*-DCMAKE_BUILD_TYPE=<BUILD-TYPE>* on the cmake command line. Possible values of ``<BUILD-TYPE>`` are:

- Debug
- Release
- RelWithDebInfo
- MinSizeRel

Compilation
^^^^^^^^^^^

.. tab:: Linux and macOS
            
         .. code-block:: bash

                         $ make

.. tab:: Windows/MinGW

         .. code-block:: bash
                         
                         $ mingw32-make
                         
.. tab:: Windows/MSVC

         .. code-block:: console

                         > nmake
 
   
Installation of the generated binaries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After a successful build

.. tab:: Linux and macOS
         
         .. code-block:: bash

                         $  make install

.. tab:: Windows/MinGW

         .. code-block:: bash
                         
                         $ mingw32-make install
                         
.. tab:: Windows/MSVC

         .. code-block:: console

                         > nmake install

will install CDPKit in a platform specific default directory (Linux: :file:`/opt`, macOS: :file:`/Users/Shared`, and
Windows: :file:`C:\\Program Files`). A different installation location can be specified by the argument
*-DCMAKE_INSTALL_PREFIX=<INSTALL-DIR>* on the :program:`cmake` command line (see above).

.. _install_via_pip:

Installation via :program:`pip` (CDPL Python bindings only)
-----------------------------------------------------------

:program:`pip` will compile the sources on-the-fly (this may take some time) to build and install the CDPL Python bindings.

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
