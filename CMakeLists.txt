##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##

cmake_minimum_required(VERSION 3.17.0 FATAL_ERROR)
cmake_policy(SET CMP0057 NEW)

set(CMAKE_COLOR_MAKEFILE ON)

file(STRINGS Version CDPKIT_VERSION)

string(REGEX MATCH "([0-9]+)\.([0-9]+)\.([0-9]+)" MATCH_RES ${CDPKIT_VERSION})

set(CDPKIT_VERSION_MAJOR ${CMAKE_MATCH_1})
set(CDPKIT_VERSION_MINOR ${CMAKE_MATCH_2})
set(CDPKIT_VERSION_PATCH ${CMAKE_MATCH_3})

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Setting build type to 'Release' as none was specified")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

project(CDPKit VERSION ${CDPKIT_VERSION} HOMEPAGE_URL "https://cdpkit.org")

set(PROJECT_NAME_WITH_VERSION "${PROJECT_NAME}-${CDPKIT_VERSION}")

if(NOT DEFINED CDPL_CXX_UNIT_TESTS_ENABLED)
  set(CDPL_CXX_UNIT_TESTS_ENABLED FALSE CACHE BOOL "Enable/disable build of c++ unit tests")
endif()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DCDPL_MATH_CHECKS_DISABLE")

if(MSVC)
  add_compile_definitions("BOOST_ALL_DYN_LINK" "BOOST_IOSTREAMS_NO_LIB" "_USE_MATH_DEFINES")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-deprecated-declarations")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -fvisibility-inlines-hidden")
endif(MSVC)

set(CMAKE_CXX_STANDARD 17)

if(APPLE) 
  find_program(CODESIGN_EXECUTABLE codesign REQUIRED)

  if(NOT CDPKIT_CODE_SIGNING_IDENTITY)
    set(CDPKIT_CODE_SIGNING_IDENTITY "-")
  endif(NOT CDPKIT_CODE_SIGNING_IDENTITY)

  set(CDPKIT_DEF_INSTALL_DIR "/Users/Shared}")
elseif(WIN32)
  set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
  set(CMAKE_STATIC_LIBRARY_PREFIX "lib")
  set(CMAKE_IMPORT_LIBRARY_PREFIX "lib")
  set(CDPKIT_DEF_INSTALL_DIR "C:/Program Files") 
else()
  set(CDPKIT_DEF_INSTALL_DIR "/opt")
endif(APPLE)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT) 
  set(CMAKE_INSTALL_PREFIX "${CDPKIT_DEF_INSTALL_DIR}" CACHE PATH "Install path prefix, prepended onto install directories" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

set(CDPKIT_MIN_BOOST_VERSION "1.63.0")

set(CDPKIT_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Data")
set(CDPKIT_TEST_DATA_DIR "${CDPKIT_DATA_DIR}/Testing")
set(CDPKIT_BUILTIN_DATA_DIR "${CDPKIT_DATA_DIR}/Builtin")
set(CDPKIT_EXTERNAL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/External")
set(CDPKIT_CMAKE_SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/CMake")
set(CDPKIT_PYTHON_SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/Python")
set(CDPKIT_SHELL_SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Scripts/Shell")
set(CDPKIT_DOC_GRAPHICS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Doc/Graphics")
set(CDPKIT_EXAMPLES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Examples")

if(PYPI_PACKAGE_BUILD)
  set(CDPKIT_PYTHON_INSTALL_DIR "Libs/Python")
  set(CDPKIT_LIBRARY_INSTALL_DIR "Libs/Python/CDPL")
  set(CDPKIT_EXECUTABLE_INSTALL_DIR "Libs/Python/CDPL")
else()
  set(CDPKIT_PYTHON_INSTALL_DIR Python)
  set(CDPKIT_LIBRARY_INSTALL_DIR Libs)
  set(CDPKIT_EXECUTABLE_INSTALL_DIR Bin)
endif(PYPI_PACKAGE_BUILD)

set(CDPKIT_INCLUDE_INSTALL_DIR Include)
set(CDPKIT_DOC_INSTALL_DIR Doc)
set(CDPKIT_EXAMPLES_INSTALL_DIR Examples)
set(CDPKIT_COMPILER_ID ${CMAKE_CXX_COMPILER_ID})
set(CDPKIT_COMPILER_VERSION ${CMAKE_CXX_COMPILER_VERSION})
set(CDPKIT_BUILD_SYSTEM ${CMAKE_SYSTEM})

set(CMAKE_MODULE_PATH "${CDPKIT_CMAKE_SCRIPTS_DIR}")

set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_MACOSX_RPATH TRUE)

if(APPLE)
  set(CDPKIT_EXECUTABLE_INSTALL_RPATH "@executable_path/../${CDPKIT_LIBRARY_INSTALL_DIR}")
  set(CDPKIT_LIBRARY_INSTALL_RPATH "@loader_path")

  if(PYPI_PACKAGE_BUILD)
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH1 "@loader_path")
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH2 "@loader_path/..")
  else()
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH1 "@loader_path/../../${CDPKIT_LIBRARY_INSTALL_DIR}")
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH2 "@loader_path/../../../${CDPKIT_LIBRARY_INSTALL_DIR}")
  endif(PYPI_PACKAGE_BUILD)
else()
  set(CDPKIT_EXECUTABLE_INSTALL_RPATH "$ORIGIN/../${CDPKIT_LIBRARY_INSTALL_DIR}")
  set(CDPKIT_LIBRARY_INSTALL_RPATH "$ORIGIN")

  if(PYPI_PACKAGE_BUILD)
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH1 "$ORIGIN")
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH2 "$ORIGIN/..")
  else()
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH1 "$ORIGIN/../../${CDPKIT_LIBRARY_INSTALL_DIR}")
    set(CDPKIT_PYTHON_MODULE_INSTALL_RPATH2 "$ORIGIN/../../../${CDPKIT_LIBRARY_INSTALL_DIR}")
  endif(PYPI_PACKAGE_BUILD)
endif(APPLE)

set(CDPL_VERSION "${CDPKIT_VERSION}")
set(CDPL_SO_VERSION "${CDPKIT_VERSION_MAJOR}.${CDPKIT_VERSION_MINOR}")

set(APPS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Apps")
set(CDPL_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libs/C++/Source")
set(CDPL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libs/C++/Include")
set(CDPL_CONFIG_HEADER_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Include")
set(CDPL_PYTHON_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/Python")

set(CDPL_BASE_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Base")
set(CDPL_CHEM_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Chem")
set(CDPL_UTIL_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Util")
set(CDPL_MATH_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Math")
set(CDPL_VIS_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Vis")
set(CDPL_PHARM_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Pharm")
set(CDPL_BIOMOL_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Biomol")
set(CDPL_GRID_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Grid")
set(CDPL_FORCEFIELD_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/ForceField")
set(CDPL_CONFGEN_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/ConfGen")
set(CDPL_GRAIL_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/GRAIL")
set(CDPL_MOLPROP_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/MolProp")
set(CDPL_DESCR_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Descr")
set(CDPL_SHAPE_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Libs/C++/Source/CDPL/Shape")
set(CDPL_CXX_API_DOC_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/Doc/Doxygen/C++-API")

if(NOT PYPI_PACKAGE_BUILD)
  if(WIN32)
    set(RUN_CXX_TESTS "${CMAKE_CURRENT_BINARY_DIR}/RunCXXTests.bat")
    set(RUN_CXX_TESTS_IN "${CDPKIT_SHELL_SCRIPTS_DIR}/RunCXXTests.bat.in")
    set(RUN_PYTHON_TESTS "${CMAKE_CURRENT_BINARY_DIR}/RunPythonTests.bat")
    set(RUN_PYTHON_TESTS_IN "${CDPKIT_SHELL_SCRIPTS_DIR}/RunPythonTests.bat.in")
  else(WIN32)
    set(RUN_CXX_TESTS "${CMAKE_CURRENT_BINARY_DIR}/RunCXXTests.sh")
    set(RUN_CXX_TESTS_IN "${CDPKIT_SHELL_SCRIPTS_DIR}/RunCXXTests.sh.in")
    set(RUN_PYTHON_TESTS "${CMAKE_CURRENT_BINARY_DIR}/RunPythonTests.sh")
    set(RUN_PYTHON_TESTS_IN "${CDPKIT_SHELL_SCRIPTS_DIR}/RunPythonTests.sh.in")
  endif(WIN32)
endif(NOT PYPI_PACKAGE_BUILD)

find_package(Python3 REQUIRED Interpreter OPTIONAL_COMPONENTS Development NumPy)

set(PYTHONINTERP_FOUND ${Python3_Interpreter_FOUND})
set(PYTHONLIBS_FOUND ${Python3_Development_FOUND})
set(PYTHON_EXECUTABLE ${Python3_EXECUTABLE})
set(PYTHON_LIBRARIES ${Python3_LIBRARIES})
set(PYTHON_INCLUDE_DIRS ${Python3_INCLUDE_DIRS})
set(NUMPY_FOUND ${Python3_NumPy_FOUND})
set(NUMPY_INCLUDE_DIRS ${Python3_NumPy_INCLUDE_DIRS})

if(NOT PYTHONLIBS_FOUND AND PYPI_MANYLINUX_PACKAGE_BUILD)
  set(PYTHONLIBS_FOUND TRUE)
  set(PYTHON_LIBRARIES "")
endif(NOT PYTHONLIBS_FOUND AND PYPI_MANYLINUX_PACKAGE_BUILD)

if(UNIX AND PYPI_MANYLINUX_PACKAGE_BUILD)
  find_program(PATCHELF_EXECUTABLE patchelf)
endif(UNIX AND PYPI_MANYLINUX_PACKAGE_BUILD)

if(NOT PYPI_PACKAGE_BUILD)
  configure_file("${RUN_PYTHON_TESTS_IN}" "${RUN_PYTHON_TESTS}" @ONLY)
endif(NOT PYPI_PACKAGE_BUILD)

find_package(Threads)

if(NOT Threads_FOUND)
  message("!! Warning: Multi-threading support not available -> commandline applications won't be built.")
endif(NOT Threads_FOUND)

set(Boost_USE_MULTITHREAD ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_ADDITIONAL_VERSIONS "1.74.0" "1.75.0" "1.76.0" "1.77.0" "1.78.0" "1.79.0" "1.80.0" "1.82.0" "1.83.0" "1.84.0")

if(PYPI_PACKAGE_BUILD)
  find_package(Boost ${CDPKIT_MIN_BOOST_VERSION} REQUIRED iostreams filesystem system)
else()
  find_package(Boost ${CDPKIT_MIN_BOOST_VERSION} REQUIRED iostreams filesystem system OPTIONAL_COMPONENTS program_options unit_test_framework)
  
  if(NOT Boost_PROGRAM_OPTIONS_FOUND)
    message("!! Warning: Boost program_options library not found -> commandline applications won't be built.")
  endif(NOT Boost_PROGRAM_OPTIONS_FOUND)

  if(NOT Boost_UNIT_TEST_FRAMEWORK_FOUND)
    message("!! Warning: Boost unit_test_framework not found -> can't build and run C++ unit test cases.")
    set(CDPL_CXX_UNIT_TESTS_ENABLED FALSE)
  else(NOT Boost_UNIT_TEST_FRAMEWORK_FOUND)
    configure_file("${RUN_CXX_TESTS_IN}" "${RUN_CXX_TESTS}" @ONLY)
  endif(NOT Boost_UNIT_TEST_FRAMEWORK_FOUND)
endif(PYPI_PACKAGE_BUILD)

if(NOT BOOST_PYTHON_VERSIONS)
  set(BOOST_PYTHON_VERSIONS  "3" "35" "36" "37" "38" "39" "310" "311" "312")
endif(NOT BOOST_PYTHON_VERSIONS)

foreach(PYTHON_VERSION ${BOOST_PYTHON_VERSIONS})
  find_package(Boost ${CDPKIT_MIN_BOOST_VERSION} QUIET OPTIONAL_COMPONENTS python${PYTHON_VERSION})            

  if(Boost_PYTHON${PYTHON_VERSION}_FOUND)
    set(Boost_PYTHON_FOUND TRUE)
    set(Boost_PYTHON_LIBRARY ${Boost_PYTHON${PYTHON_VERSION}_LIBRARY})
    break()
  endif(Boost_PYTHON${PYTHON_VERSION}_FOUND)
endforeach()

if(Boost_PYTHON_FOUND AND PYTHONLIBS_FOUND)
  set(BUILD_PYTHON_MODULES TRUE)
  set(PYTHON_TESTS_ENABLED TRUE)
else(Boost_PYTHON_FOUND AND PYTHONLIBS_FOUND)
  if(PYPI_PACKAGE_BUILD)
    message(FATAL_ERROR "!! Python library and/or Boost python library not found.")    
  else()
    message("!! Warning: Python library and/or Boost python library not found -> can't build CDPL Python bindings.")    
  endif(PYPI_PACKAGE_BUILD)

  set(BUILD_PYTHON_MODULES FALSE)
  set(PYTHON_TESTS_ENABLED FALSE)
endif(Boost_PYTHON_FOUND AND PYTHONLIBS_FOUND)

if(NOT PYPI_PACKAGE_BUILD)
  find_package(Qt5Gui PATHS "/opt/homebrew/opt/qt@5" "/usr/local/opt/qt@5")
  find_package(Qt5Widgets PATHS "/opt/homebrew/opt/qt@5" "/usr/local/opt/qt@5")
  find_package(Qt5PrintSupport PATHS "/opt/homebrew/opt/qt@5" "/usr/local/opt/qt@5")

  if(NOT Qt5Gui_FOUND)
    message("!! Warning: Qt5 not found -> can't build Qt rendering backend and Qt applications.")
  else()
    get_target_property(_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT_BIN_DIR "${_QMAKE_EXECUTABLE}" DIRECTORY)

    if(APPLE)
      find_program(MACDEPLOYQT_EXECUTABLE macdeployqt HINTS "${QT_BIN_DIR}")

      if(NOT MACDEPLOYQT_EXECUTABLE)
        message("!! Warning: macdeployqt not found -> can't fully deploy Qt applications.")
      endif(NOT MACDEPLOYQT_EXECUTABLE)
    elseif(WIN32)
      find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")

      if(NOT WINDEPLOYQT_EXECUTABLE)
        message("!! Warning: windeployqt not found -> can't fully deploy Qt applications.")
      endif(NOT WINDEPLOYQT_EXECUTABLE)
    endif(APPLE)
  endif(NOT Qt5Gui_FOUND)
endif(NOT PYPI_PACKAGE_BUILD)

find_package(Cairo)

if(NOT CAIRO_FOUND)
  message("!! Warning: CAIRO library not found -> can't build Cairo rendering backend.")
else(NOT CAIRO_FOUND)
  include(CheckFunctionExists)

  set(CMAKE_REQUIRED_INCLUDES "${CAIRO_INCLUDE_DIR}")
  set(CMAKE_REQUIRED_LIBRARIES "${CAIRO_LIBRARIES}")

  check_function_exists(cairo_surface_write_to_png_stream HAVE_CAIRO_PNG_SUPPORT)
  check_function_exists(cairo_ps_surface_create HAVE_CAIRO_PS_SUPPORT)
  check_function_exists(cairo_pdf_surface_create HAVE_CAIRO_PDF_SUPPORT)
  check_function_exists(cairo_svg_surface_create HAVE_CAIRO_SVG_SUPPORT)
endif(NOT CAIRO_FOUND)

if(BUILD_PYTHON_MODULES)
  if(NOT NUMPY_FOUND)
    message("!! Warning: NumPy python package not found -> CDPL.Math NDArray support won't be built.")
  endif(NOT NUMPY_FOUND)
endif(BUILD_PYTHON_MODULES)

if(NOT PYPI_PACKAGE_BUILD)
  find_package(Doxygen)

  if(NOT DOXYGEN_EXECUTABLE)
    message("!! Warning: Doxygen not found -> can't generate CDPL API documentation.")
    set(HAVE_DOT NO)
  else(NOT DOXYGEN_EXECUTABLE)
    if(DOXYGEN_DOT_EXECUTABLE)
      set(HAVE_DOT YES)
    else(DOXYGEN_DOT_EXECUTABLE)
      set(HAVE_DOT NO)
    endif(DOXYGEN_DOT_EXECUTABLE)
  endif(NOT DOXYGEN_EXECUTABLE)

  if(APPLE)
    if(EXISTS "/opt/homebrew/opt/sphinx-doc")
      set(Sphinx_DIR "/opt/homebrew/opt/sphinx-doc")
    elseif(EXISTS "/usr/local/opt/sphinx-doc")
      set(Sphinx_DIR "/usr/local/opt/sphinx-doc")
    endif()
  endif(APPLE)

  find_package(Sphinx COMPONENTS build)

  if(NOT SPHINX_FOUND)
    message("!! Warning: Sphinx not found -> can't generate dependent documentation.")
  endif(NOT SPHINX_FOUND)
endif(NOT PYPI_PACKAGE_BUILD)

include(CheckTypeSize)

check_type_size("long int" SIZEOF_LONG_INT)
check_type_size("unsigned int" SIZEOF_UNSIGNED_INT)
check_type_size("float" SIZEOF_FLOAT)
check_type_size("double" SIZEOF_DOUBLE)
check_type_size("size_t" SIZEOF_SIZE_T)

if(SIZEOF_LONG_INT LESS 4)
  message(FATAL_ERROR "sizeof(long int) < 4.")
endif(SIZEOF_LONG_INT LESS 4)

if(SIZEOF_UNSIGNED_INT LESS 4)
  message(FATAL_ERROR "sizeof(unsigned int) < 4.")
endif(SIZEOF_UNSIGNED_INT LESS 4)

if(NOT SIZEOF_FLOAT EQUAL 4)
  message(FATAL_ERROR "sizeof(float) != 4.")
endif(NOT SIZEOF_FLOAT EQUAL 4)

if(NOT SIZEOF_DOUBLE EQUAL 8)
  message(FATAL_ERROR "sizeof(double) != 8.")
endif(NOT SIZEOF_DOUBLE EQUAL 8)

if(SIZEOF_SIZE_T LESS 4)
  message(FATAL_ERROR "sizeof(size_t) < 4.")
endif(SIZEOF_SIZE_T LESS 4)

include(CheckCXXSourceCompiles)

check_cxx_source_compiles("#include <cstdint>\nint main() { std::uint64_t i; std::uint32_t j; std::uint8_t k; return 0; }" FIXED_WIDTH_UINT_TYPES)

if(NOT FIXED_WIDTH_UINT_TYPES)
  message(FATAL_ERROR "Required fixed width integer types not available.")
endif(NOT FIXED_WIDTH_UINT_TYPES)

set(HAVE_CAIRO ${CAIRO_FOUND})
set(HAVE_QT ${Qt5Gui_FOUND})
set(HAVE_NUMPY ${NUMPY_FOUND})

configure_file("${CDPL_INCLUDE_DIR}/CDPL/Config.hpp.in" "${CDPL_CONFIG_HEADER_INCLUDE_DIR}/CDPL/Config.hpp") 
configure_file("${CDPL_INCLUDE_DIR}/CDPL/Version.hpp.in" "${CDPL_CONFIG_HEADER_INCLUDE_DIR}/CDPL/Version.hpp") 

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/GenerateBuildInfoHeader.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/GenerateBuildInfoHeader.cmake" @ONLY)
add_custom_target(gen-build-info-header ALL
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/GenerateBuildInfoHeader.cmake")

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/CMakeUninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/CMakeUninstall.cmake" @ONLY)
add_custom_target(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/CMakeUninstall.cmake")

include_directories("${CDPL_INCLUDE_DIR}" "${CDPL_CONFIG_HEADER_INCLUDE_DIR}" "${Boost_INCLUDE_DIR}")

if(NOT PYPI_PACKAGE_BUILD)
  install(FILES ChangeLog.txt DESTINATION "." COMPONENT Documentation)
  install(FILES COPYING DESTINATION "." COMPONENT CDPLSharedLibraries)
endif(NOT PYPI_PACKAGE_BUILD)
    
# CPack related setup
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME_WITH_VERSION}")
set(CPACK_PACKAGE_VENDOR "Thomas Seidel/University of Vienna")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR "${CDPKIT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CDPKIT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${CDPKIT_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION "${CDPKIT_VERSION}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "${PROJECT_NAME}")
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME_WITH_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_PACKAGE_DEFAULT_LOCATION "${CDPKIT_DEF_INSTALL_DIR}")
set(CPACK_PACKAGING_INSTALL_PREFIX "/")
set(CPACK_PACKAGE_RELOCATABLE TRUE) 
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME_WITH_VERSION}")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_IGNORE_FILES "/[.]git/;.*#$;.*~$;cscope.*")

set(CPACK_COMPONENTS_ALL 
  Documentation
  Examples
  CDPLSharedLibraries
  CDPLImportLibraries
  CDPLStaticLibraries
  CDPLHeaderFiles
  CDPLPythonModules
  Applications 
)
  
if(WIN32)
  set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Applications")
  set(CPACK_COMPONENT_CDPLSTATICLIBRARIES_DISPLAY_NAME "Static Libraries")
  set(CPACK_COMPONENT_CDPLSHAREDLIBRARIES_DISPLAY_NAME "Dynamic Runtime Libraries")
  set(CPACK_COMPONENT_CDPLHEADERFILES_DISPLAY_NAME "Header Files")
  set(CPACK_COMPONENT_DOCUMENTATION_DISPLAY_NAME "Documentation")
  set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Python Examples")
  set(CPACK_COMPONENT_CDPLPYTHONMODULES_DISPLAY_NAME "Python Bindings")

  set(CPACK_COMPONENT_CDPLHEADERFILES_GROUP CXXDevelopment)
  set(CPACK_COMPONENT_CDPLSTATICLIBRARIES_GROUP CXXDevelopment)
  set(CPACK_COMPONENT_CDPLPYTHONMODULES_GROUP PythonDevelopment)
  set(CPACK_COMPONENT_EXAMPLES_GROUP PythonDevelopment)

  set(CPACK_COMPONENT_GROUP_CXXDEVELOPMENT_DISPLAY_NAME "CDPL C++ Development")
  set(CPACK_COMPONENT_GROUP_PYTHONDEVELOPMENT_DISPLAY_NAME "CDPL Python Development")

  set(CPACK_COMPONENT_APPLICATIONS_DEPENDS CDPLSharedLibraries)
  set(CPACK_COMPONENT_CDPLPYTHONMODULES_DEPENDS CDPLSharedLibraries)

  set(CPACK_COMPONENT_CDPLIMPORTLIBRARIES_DISPLAY_NAME "DLL Import Libraries")
  set(CPACK_COMPONENT_CDPLIMPORTLIBRARIES_GROUP CXXDevelopment)

  set(CPACK_GENERATOR "NSIS")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME_WITH_VERSION}-Win-${CMAKE_CXX_COMPILER_ID}-${CMAKE_SYSTEM_PROCESSOR}")
  set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "${PROJECT_NAME}")
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL TRUE)
  set(CPACK_NSIS_MODIFY_PATH FALSE)
  set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME}")
  set(CPACK_PACKAGE_EXECUTABLES "chox;ChOX")
  set(CPACK_CREATE_DESKTOP_LINKS "ChOX")
  set(CPACK_NSIS_URL_INFO_ABOUT "https://cdpkit.org")
  set(CPACK_NSIS_CONTACT "Thomas Seidel <thomas.seidel@univie.ac.at>")
  set(CPACK_NSIS_MENU_LINKS
    "${CDPKIT_DOC_INSTALL_DIR}/index.html" "Documentation"
    "Uninstall" "Uninstall CDPKit"
    )

elseif(APPLE)
  set(CPACK_GENERATOR "DragNDrop")
  set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME_WITH_VERSION}-macOS-${CMAKE_SYSTEM_PROCESSOR}")
  set(CPACK_PACKAGING_INSTALL_PREFIX "/${PROJECT_NAME}")
  
else()
  set(CPACK_AT_SIGN "@")
  set(CPACK_RESOURCE_FILE_LICENSE_CONTENT "@CPACK_RESOURCE_FILE_LICENSE_CONTENT@")

  configure_file("${CDPKIT_SHELL_SCRIPTS_DIR}/CPackSTGZHeader.sh.in" "${CMAKE_CURRENT_BINARY_DIR}/CPackSTGZHeader.sh" @ONLY)

  unset(CPACK_RESOURCE_FILE_LICENSE_CONTENT)

  set(CPACK_GENERATOR "STGZ")
  set(CPACK_STGZ_HEADER_FILE "${CMAKE_CURRENT_BINARY_DIR}/CPackSTGZHeader.sh")
endif(WIN32)

include(CPack)

if(NOT PYPI_PACKAGE_BUILD)
  include(CTest)
endif(NOT PYPI_PACKAGE_BUILD)

add_subdirectory(External) 
add_subdirectory(Libs)

if(NOT PYPI_PACKAGE_BUILD)
  add_subdirectory(Apps)
  add_subdirectory(Doc)
  add_subdirectory(Examples)
endif(NOT PYPI_PACKAGE_BUILD)

if(WIN32)
  set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT CDPLSharedLibraries)
  set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${CDPKIT_EXECUTABLE_INSTALL_DIR})
  
  include(InstallRequiredSystemLibraries)
endif(WIN32)
