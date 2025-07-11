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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CDPKIT_EXTERNAL_DIR}")

set(cdpl-vis_LIB_SRCS
    AtomProperty.cpp
    BondProperty.cpp
    MolecularGraphProperty.cpp
    ReactionProperty.cpp
    Object3DProperty.cpp
    AtomPropertyDefault.cpp
    BondPropertyDefault.cpp
    MolecularGraphPropertyDefault.cpp
    ReactionPropertyDefault.cpp
    Object3DPropertyDefault.cpp
    
    ControlParameter.cpp
    ControlParameterDefault.cpp
    ControlParameterFunctions.cpp

    AtomPropertyFunctions.cpp
    BondPropertyFunctions.cpp
    MolecularGraphPropertyFunctions.cpp
    ReactionPropertyFunctions.cpp
    Object3DPropertyFunctions.cpp
    
    MolecularGraphPrepareFor2DVisualizationFunction.cpp
    ReactionPrepareFor2DVisualizationFunction.cpp    
    DataFormat.cpp

    Object3D.cpp
    TriangleMesh3D.cpp
    
    StructureView2D.cpp
    ReactionView2D.cpp
    StructureGridView2D.cpp
    StructureView2DParameters.cpp
    ReactionView2DParameters.cpp
    SizeSpecification.cpp
    AtomColorTable.cpp
    Pen.cpp
    Brush.cpp
    Color.cpp
    ColorTable.cpp    
    Font.cpp
    Rectangle2D.cpp
    Line2D.cpp
    PointArray2D.cpp
    Path2D.cpp
    EllipsePrimitive2D.cpp
    LinePrimitive2D.cpp
    PolygonPrimitive2D.cpp
    PolylinePrimitive2D.cpp
    LineSegmentListPrimitive2D.cpp
    PointListPrimitive2D.cpp
    PathPrimitive2D.cpp
    ClipPathPrimitive2D.cpp
    TextLabelPrimitive2D.cpp
    TextBlockPrimitive2D.cpp
   )

if(CAIRO_FOUND)
  set(cdpl-vis_LIB_SRCS
      ${cdpl-vis_LIB_SRCS}
      CairoRenderer2D.cpp
      CairoFontMetrics.cpp
      ImageWriter.cpp
      CairoPointer.cpp
      StreamWriteFunc.cpp
     )    

  if(HAVE_CAIRO_PNG_SUPPORT)
    set(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        PNGMolecularGraphWriter.cpp
        PNGReactionWriter.cpp
       )    
  endif(HAVE_CAIRO_PNG_SUPPORT)

  if(HAVE_CAIRO_PDF_SUPPORT)
    set(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        PDFMolecularGraphWriter.cpp
        PDFReactionWriter.cpp
       )    
  endif(HAVE_CAIRO_PDF_SUPPORT)

  if(HAVE_CAIRO_PS_SUPPORT)
    set(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        PSMolecularGraphWriter.cpp
        PSReactionWriter.cpp
       )    
  endif(HAVE_CAIRO_PS_SUPPORT)

  if(HAVE_CAIRO_SVG_SUPPORT)
    set(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        SVGMolecularGraphWriter.cpp
        SVGReactionWriter.cpp
       )    
  endif(HAVE_CAIRO_SVG_SUPPORT)

  include_directories("${CAIRO_INCLUDE_DIR}")
endif(CAIRO_FOUND)

if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-vis-static STATIC ${cdpl-vis_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

  target_link_libraries(cdpl-vis-static cdpl-chem-static cdpl-molprop-static cdpl-base-static)

  if(CAIRO_FOUND)
    target_link_libraries(cdpl-vis-static Cairo::Library)
  endif(CAIRO_FOUND)
  
  target_include_directories(cdpl-vis-static
    PUBLIC
    "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

  set_target_properties(cdpl-vis-static PROPERTIES 
    OUTPUT_NAME cdpl-vis
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_VIS_STATIC_LINK")

  install(TARGETS cdpl-vis-static EXPORT ExportedTargets
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-vis-shared SHARED ${cdpl-vis_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

target_link_libraries(cdpl-vis-shared PUBLIC cdpl-chem-shared cdpl-molprop-shared cdpl-base-shared)

if(CAIRO_FOUND)
  target_link_libraries(cdpl-vis-shared PRIVATE Cairo::Library)
endif(CAIRO_FOUND)

target_include_directories(cdpl-vis-shared
  PUBLIC
  "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
  "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

set_target_properties(cdpl-vis-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-vis
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-vis.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-vis.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-vis.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-vis-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-vis-shared EXPORT ExportedTargets
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(NOT PYPI_PACKAGE_BUILD AND Qt5Gui_FOUND)
  set(cdpl-vis-qt_LIB_SRCS
      QtRenderer2D.cpp
      QtFontMetrics.cpp
      QtObjectFactory.cpp
     )

  add_library(cdpl-vis-qt-static STATIC ${cdpl-vis-qt_LIB_SRCS})

  target_link_libraries(cdpl-vis-qt-static cdpl-vis-static Qt5::Gui)
  target_include_directories(cdpl-vis-qt-static
    PUBLIC
    "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

  set_target_properties(cdpl-vis-qt-static PROPERTIES 
    OUTPUT_NAME cdpl-vis-qt
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_VIS_QT_STATIC_LINK")

  install(TARGETS cdpl-vis-qt-static EXPORT ExportedTargets
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)

  add_library(cdpl-vis-qt-shared SHARED ${cdpl-vis-qt_LIB_SRCS})

  target_link_libraries(cdpl-vis-qt-shared cdpl-vis-shared Qt5::Gui)
  target_include_directories(cdpl-vis-qt-shared
    PUBLIC
    "$<BUILD_INTERFACE:${CDPL_INCLUDE_DIR};${CDPL_CONFIG_HEADER_INCLUDE_DIR}>"
    "$<INSTALL_INTERFACE:${CDPKIT_INCLUDE_INSTALL_DIR}>")

  set_target_properties(cdpl-vis-qt-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
    OUTPUT_NAME cdpl-vis-qt
    CLEAN_DIRECT_OUTPUT 1
    INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

  install(TARGETS cdpl-vis-qt-shared EXPORT ExportedTargets
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)

  if(APPLE)
    configure_file(CodeSignLibCDPLVisQt.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CodeSignLibCDPLVisQt.cmake" @ONLY)
    install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/CodeSignLibCDPLVisQt.cmake" COMPONENT CDPLSharedLibraries)
  endif(APPLE)
endif(NOT PYPI_PACKAGE_BUILD AND Qt5Gui_FOUND)

if(CDPKIT_BUILD_CXX_UNIT_TESTS)
  add_subdirectory(Tests)
endif(CDPKIT_BUILD_CXX_UNIT_TESTS)
