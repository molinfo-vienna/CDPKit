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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(cdpl-vis_LIB_SRCS
    AtomProperty.cpp
    BondProperty.cpp
    MolecularGraphProperty.cpp
    ReactionProperty.cpp
    AtomPropertyDefault.cpp
    BondPropertyDefault.cpp
    MolecularGraphPropertyDefault.cpp
    ReactionPropertyDefault.cpp

    ControlParameter.cpp
    ControlParameterDefault.cpp
    ControlParameterFunctions.cpp

    AtomPropertyFunctions.cpp
    BondPropertyFunctions.cpp
    MolecularGraphPropertyFunctions.cpp
    ReactionPropertyFunctions.cpp

    DataFormat.cpp

    StructureView2D.cpp
    ReactionView2D.cpp
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
    EllipsePrimitive2D.cpp
    LinePrimitive2D.cpp
    PolygonPrimitive2D.cpp
    PolylinePrimitive2D.cpp
    LineSegmentListPrimitive2D.cpp
    PointListPrimitive2D.cpp
    TextLabelPrimitive2D.cpp
   )

IF(CAIRO_FOUND)
  SET(cdpl-vis_LIB_SRCS
      ${cdpl-vis_LIB_SRCS}
      CairoRenderer2D.cpp
      CairoFontMetrics.cpp
      ImageWriter.cpp
      CairoPointer.cpp
      StreamWriteFunc.cpp
     )    

  IF(HAVE_CAIRO_PNG_SUPPORT)
    SET(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        PNGMolecularGraphWriter.cpp
        PNGReactionWriter.cpp
       )    
  ENDIF(HAVE_CAIRO_PNG_SUPPORT)

  IF(HAVE_CAIRO_PDF_SUPPORT)
    SET(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        PDFMolecularGraphWriter.cpp
        PDFReactionWriter.cpp
       )    
  ENDIF(HAVE_CAIRO_PDF_SUPPORT)

  IF(HAVE_CAIRO_PS_SUPPORT)
    SET(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        PSMolecularGraphWriter.cpp
        PSReactionWriter.cpp
       )    
  ENDIF(HAVE_CAIRO_PS_SUPPORT)

  IF(HAVE_CAIRO_SVG_SUPPORT)
    SET(cdpl-vis_LIB_SRCS
        ${cdpl-vis_LIB_SRCS}
        SVGMolecularGraphWriter.cpp
        SVGReactionWriter.cpp
       )    
  ENDIF(HAVE_CAIRO_SVG_SUPPORT)

  LINK_LIBRARIES(${CAIRO_LIBRARIES})
  INCLUDE_DIRECTORIES("${CAIRO_INCLUDE_DIR}")
ENDIF(CAIRO_FOUND)

IF(NOT PYPI_PACKAGE_BUILD)
  ADD_LIBRARY(cdpl-vis-static STATIC ${cdpl-vis_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

  TARGET_LINK_LIBRARIES(cdpl-vis-static cdpl-chem-static cdpl-molprop-static cdpl-base-static)

  SET_TARGET_PROPERTIES(cdpl-vis-static PROPERTIES 
    OUTPUT_NAME cdpl-vis
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_VIS_STATIC_LINK")

  INSTALL(TARGETS cdpl-vis-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
ENDIF(NOT PYPI_PACKAGE_BUILD)

ADD_LIBRARY(cdpl-vis-shared SHARED ${cdpl-vis_LIB_SRCS} $<TARGET_OBJECTS:cdpl-internal>)

TARGET_LINK_LIBRARIES(cdpl-vis-shared cdpl-chem-shared cdpl-molprop-shared cdpl-base-shared)

SET_TARGET_PROPERTIES(cdpl-vis-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-vis
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

IF(WIN32)
  SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-vis.dll")
ELSEIF(APPLE)
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-vis.dylib")
ELSE()            
  SET(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-vis.so")
ENDIF(WIN32)

CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

IF(WIN32 AND PYPI_PACKAGE_BUILD)
   INSTALL(TARGETS cdpl-vis-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
ELSE()
  INSTALL(TARGETS cdpl-vis-shared
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
ENDIF(WIN32 AND PYPI_PACKAGE_BUILD)

INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

IF(NOT PYPI_PACKAGE_BUILD AND Qt5Gui_FOUND)
  SET(cdpl-vis-qt_LIB_SRCS
      QtRenderer2D.cpp
      QtFontMetrics.cpp
      QtObjectFactory.cpp
     )

  ADD_LIBRARY(cdpl-vis-qt-static STATIC ${cdpl-vis-qt_LIB_SRCS})

  TARGET_LINK_LIBRARIES(cdpl-vis-qt-static cdpl-vis-static Qt5::Gui)

  SET_TARGET_PROPERTIES(cdpl-vis-qt-static PROPERTIES 
    OUTPUT_NAME cdpl-vis-qt
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_VIS_QT_STATIC_LINK")

  INSTALL(TARGETS cdpl-vis-qt-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)

  ADD_LIBRARY(cdpl-vis-qt-shared SHARED ${cdpl-vis-qt_LIB_SRCS})

  TARGET_LINK_LIBRARIES(cdpl-vis-qt-shared cdpl-vis-shared Qt5::Gui)

  SET_TARGET_PROPERTIES(cdpl-vis-qt-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
    OUTPUT_NAME cdpl-vis-qt
    CLEAN_DIRECT_OUTPUT 1
    INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

  INSTALL(TARGETS cdpl-vis-qt-shared
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)

  IF(APPLE)
    CONFIGURE_FILE(CodeSignLibCDPLVisQt.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/CodeSignLibCDPLVisQt.cmake" @ONLY)
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/CodeSignLibCDPLVisQt.cmake" COMPONENT CDPLSharedLibraries)
  ENDIF(APPLE)
ENDIF(NOT PYPI_PACKAGE_BUILD AND Qt5Gui_FOUND)

IF(CDPL_CXX_UNIT_TESTS_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(CDPL_CXX_UNIT_TESTS_ENABLED)
