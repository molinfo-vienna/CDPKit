Installing CDPKit
=================

.. index:: Installation

CDPKit can be installed in different ways:

- :ref:`By means of an official binary installer package <installation_via_installer_package>`. This
  is the best approach for most users. It will provide a full-featured stable CDPKit version
  and pre-built installers are available for most platforms.

- :ref:`Build and install from source <installation_from_source>`. This is the best option for users who want the
  latest-and-greatest features and aren't afraid of compiling C++ code and/or run brand-new software.
  This is also needed for users who run an operating system version for which no installer has been
  provided and for users who wish to contribute to the project.

- :ref:`Installation via pip <installation_using_pip>`.
  :program:`pip` will only install the CDPL Python bindings. This is the best option for users who
  only want to develop or run Python software that uses CDPL functionality.

.. _installation_via_installer_package:

Installation via installer package
----------------------------------

Installers for macOS (DMG-file, *Apple Silicon* processors only), Linux x86_64 (self-extracting archive) and Windows 10 (graphical installer
based on `NSIS <https://nsis.sourceforge.io/Download>`_) can be downloaded from the `Releases <https://github.com/molinfo-vienna/CDPKit/releases>`_
page of the `CDPKit GitHub repository <https://github.com/molinfo-vienna/CDPKit>`_. These installer packages will provide everything CDPKit has to offer:

- Command line tools and GUI applications
- CDPL binaries for dynamic linking
- CDPL binaries for static linking
- CDPL C++ header files
- CDPL Python bindings
- Python example scripts
- Offline CDPKit documentation
  
Installations of CDPKit are self-contained, i.e., after finishing the installation process no additional
software packages have to be installed. 

.. note::

   After the installation process the **PATH** environment variable needs to be edited to include the full path to the :file:`Bin` folder
   below the CDPKit installation directory. Furthermore, to enable the use of the CDPL Python bindings, the **PYTHONPATH** environment variable
   must include the full path to the corresponding :file:`Python` subfolder. 

.. _installation_from_source:

Installation from source
------------------------

Build requirements
^^^^^^^^^^^^^^^^^^

Compilation of the CDPKit sources requires a properly set up build environment. This includes a C++ compiler toolchain that supports the C++17 standard,
the `CMake <https://cmake.org/>`_ makefile generator, and the development version of several software libraries. The following table provides a complete
list of the CDPKit build requirements and dependencies:

=============================  =============  ================================================================================
Build requirement              Version        Comment
=============================  =============  ================================================================================
C++17 compliant compiler [#]_  \-             mandatory
cmake                          3.17+          mandatory
Python interpreter             3.6+           mandatory
boost-devel                    1.63+          mandatory
boost-python3-devel            1.63+          optional, required for building CDPL Python bindings
python-devel                   3.6+           optional, required for building CDPL Python bindings
NumPy                          1.17+          optional, recommended to be installed for CDPL Python NumPy-conversion features
Qt5-devel                      5.6+           optional, required for building Qt rendering backend and GUI applications
cairo-devel                    1.14+          optional, required for building cairo rendering backend
Sphinx                         4.5+           optional, required for generating CDPKit documentation pages
sphinx-rtd-theme               1.0.0+         optional, required for generating CDPKit documentation pages
sphinx-inline-tabs             2021.4.11b8+   optional, required for generating CDPKit documentation pages
sphinx-sitemap                 2.5.1+         optional, required for generating CDPKit documentation pages
sphinxcontrib-bibtex           2.5.5+         optional, required for generating CDPKit documentation pages
docs-versions-menu             0.5.2+         optional, required for generating CDPKit documentation pages
Doxygen                        1.8.5+         optional, required for generating C++ and Python API documentation
=============================  =============  ================================================================================

.. [#] Known to work: :program:`gcc` V4.8+, :program:`Apple Clang` V12.0+ , and :program:`MSVC` V1930+

Build environment setup
^^^^^^^^^^^^^^^^^^^^^^^

.. rubric:: Linux

Package managers on modern Linux systems usually provide all listed software packages in the required minimum versions.

.. rubric:: macOS

On macOS (*Big Sur* is the minimum supported version) the best way to install everything needed for a successful build
is to use the `Homebrew <https://brew.sh/index>`_ or `MacPorts <https://ports.macports.org>`_ (recommended) package
distributions.

.. rubric:: Windows

On Windows (8/10/11) the least error prone way to get started is to set up a :program:`MinGW` build environment by installing packages
from the `MSYS2 <https://www.msys2.org/>`_ software distribution. However, the downside heare is that the built CDPL Python bindings
will only work with the Python interpreter shipped with MSYS2.
In order to make the CDPL Python bindings work with an official Python distribution obtained from https://www.python.org, a build using
Microsoft's Visual C++ compiler (:program:`MSVC`) toolchain is required. 

Recommended sources for the software packages listed above are:

- *MSVC*: https://visualstudio.microsoft.com/vs/features/cplusplus
- *CMake*: https://cmake.org/download
- *Python*: https://www.python.org/downloads/windows
- *Qt5*: https://www.qt.io/download
- *boost*: https://sourceforge.net/projects/boost/files/boost-binaries
- *cairo*: https://github.com/preshing/cairo-windows
- *Doxygen*: https://www.doxygen.nl/download.html

Build system configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^

The configuration and generation of the build system files is performed by the command :command:`cmake`.
In the following :file:`<BUILD-DIR>` refers to the directory that will contain the CDPKit build ouput and :file:`<SOURCE-DIR>`
refers to the directory hosting the CDPKit source tree. 
The description of the build steps on Windows depends on whether the build environment is based on MSYS2 (employing the :program:`MinGW gcc` port
as C++ compiler) or utilizes the :program:`MSVC` toolset.

.. tab:: Linux and macOS

         Open a terminal and execute:
            
         .. code-block:: shell

                         $ mkdir <BUILD-DIR>
                         $ cd <BUILD-DIR>
                         $ cmake <SOURCE-DIR>

.. tab:: Windows/MinGW

         Open a `MSYS2 MinGW 64-bit <https://www.msys2.org/docs/terminals>`_ command prompt and execute:

         .. code-block:: shell
                         
                         $ mkdir <BUILD-DIR>
                         $ cd <BUILD-DIR>
                         $ cmake <SOURCE-DIR> -G "MinGW Makefiles"

.. tab:: Windows/MSVC

         Open a `x64 Native Tools Command Promp <https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170>`_ via the
         Windows start menu and execute:

         .. code-block:: shell

                         > mkdir <BUILD-DIR>
                         > cd <BUILD-DIR>
                         > cmake <SOURCE-DIR> -DCMAKE_PREFIX_PATH=/path/to/Qt/installation/subdir/msvc<VER>_64 -D_CAIRO_LIBDIR=/path/to/cairo/lib/dir -D_CAIRO_INCLUDEDIR=/path/to/cairo/include/dir -G "NMake Makefiles"

If :command:`cmake` is executed as shown above the default build type will be ``Release``. Configuring for a different build type can be achieved via the argument
*-DCMAKE_BUILD_TYPE=<BUILD-TYPE>* on the :command:`cmake` command line. Possible values of ``<BUILD-TYPE>`` are:

- Debug
- Releasex
- RelWithDebInfo
- MinSizeRel

Compilation
^^^^^^^^^^^

If the build system configuration step proceeded without errors

.. tab:: Linux and macOS
            
         .. code-block:: shell

                         $ make

.. tab:: Windows/MinGW

         .. code-block:: shell
                         
                         $ mingw32-make
                         
.. tab:: Windows/MSVC

         .. code-block:: shell

                         > nmake

will start the build process.
                         
Build of HTML documentation
^^^^^^^^^^^^^^^^^^^^^^^^^^^

This step is optional and needs to be carried out only if a build of offline CDPKit documentation pages
is required or desired. If the documentation should be installed together with the built binaries then this step must be
executed *before* carrying out the installation procedure (see next section).
Mandatory for a successful build is the availability of the `Sphinx <https://www.sphinx-doc.org/en/master>`_ documentation generator
plus the listed extensions (see `Build requirements`_). Furthermore, for generating CDPL C++ and Python API-documentation (optional),
the program `Doxygen <https://www.doxygen.nl>`_ has to be installed.

.. hint::

   Sphinx and its extensions can be installed via the Python package installer :program:`pip`.

If all prerequisites are fulfilled

.. tab:: Linux and macOS
            
         .. code-block:: shell

                         $ make doc

.. tab:: Windows/MinGW

         .. code-block:: shell
                         
                         $ mingw32-make doc
                         
.. tab:: Windows/MSVC

         .. code-block:: shell

                         > nmake doc

should successfully build the CDPKit documentation pages which can then be found in :file:`<BUILD-DIR>/Doc/html`.
   
Installation of the generated binaries
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

If the previous steps proceeded without errors 

.. tab:: Linux and macOS
         
         .. code-block:: shell

                         $  make install

.. tab:: Windows/MinGW

         .. code-block:: shell
                         
                         $ mingw32-make install
                         
.. tab:: Windows/MSVC

         .. code-block:: shell

                         > nmake install

will install CDPKit in a platform specific default directory (Linux: :file:`/opt`, macOS: :file:`/Users/Shared`, and
Windows: :file:`C:\\Program Files`). A different installation location can be specified by the argument
*-DCMAKE_INSTALL_PREFIX=<INSTALL-DIR>* on the :program:`cmake` command line (see `Build system configuration`_).

.. index:: pip, PyPI

.. _installation_using_pip:
           
Installation using :program:`pip`
---------------------------------

.. note::
   
   :program:`pip` will only install the CDPL Python bindings. This is the recommended option for users who
   only want to develop or run Python software that uses CDPL functionality.

Installation of the latest binary release
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The latest binary release of the CDPL Python bindings deposited on `PyPI <https://pypi.org/project/CDPKit>`_
can be installed by issuing the following command in a terminal session:

.. code-block:: shell
                
                $ pip install cdpkit
                
If no `wheel <https://packaging.python.org/en/latest/specifications/binary-distribution-format/#binary-distribution-format>`_ file
for the platform (defined by OS, processor architecture and Python version) the command was executed on is available, an on-the-fly build of
the CDPKit sources is attempted. This will only proceed without errors if a proper build environment has been set up (see next section).

Installation via a build of the sources
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

For a successful build of the CDPL Python bindings the information provided in section `Installation from source`_ applies also
here. However, since a full-featured CDPKit build is not required the list of requirements is a bit shorter:

=============================  =============  ================================================================================
Build requirement              Version        Comment
=============================  =============  ================================================================================
C++17 compliant compiler       \-             mandatory
Python interpreter             3.6+           mandatory, implicitly fulfilled
boost-devel                    1.63+          mandatory
boost-python3-devel            1.63+          mandatary
python-devel                   3.6+           mandatory
NumPy                          1.17+          optional, will be installed automatically (listed as :program:`pip` installation requirement)
cairo-devel                    1.14+          optional, required for building cairo rendering backend
=============================  =============  ================================================================================

.. rubric:: Option 1: Build the CDPKit sources deposited on `PyPI <https://pypi.org/project/CDPKit>`_

This will be done automatically if no pre-built binary package is available (see previous section) or can be enforced
by adding the argument *--no-binary :all:*:

.. code-block:: shell

                $ pip install cdpkit --no-binary :all:
            
.. rubric:: Option 2: Installation of the current development version by specifying the GitHub repository URL

.. code-block:: shell

                $ pip install git+https://github.com/molinfo-vienna/CDPKit.git

.. rubric:: Option 3: Installation under specification of a local directory containing the CDPKit sources

Enter (:command:`cd`) the CDPKit source code folder and then from within the folder run

.. code-block:: shell
                
                $ pip install .

