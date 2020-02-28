# -*- mode: CMake -*-

##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
ENDFOREACH(PYTHON_FILE)

SET(vis_MOD_SRCS
    Module.cpp
    SizeSpecificationExport.cpp
    ColorExport.cpp
    PenExport.cpp
    BrushExport.cpp
    FontExport.cpp
    FontMetricsExport.cpp
    Line2DExport.cpp
    Rectangle2DExport.cpp
    PointArray2DExport.cpp
    ColorTableExport.cpp
    AtomColorTableExport.cpp
    GraphicsPrimitive2DExport.cpp
    View2DExport.cpp
    Renderer2DExport.cpp
    StructureView2DExport.cpp
    ReactionView2DExport.cpp
    LinePrimitive2DExport.cpp
    PolygonPrimitive2DExport.cpp
    PolylinePrimitive2DExport.cpp
    LineSegmentListPrimitive2DExport.cpp
    PointListPrimitive2DExport.cpp
    TextLabelPrimitive2DExport.cpp
    EllipsePrimitive2DExport.cpp

    MolecularGraphFunctionExport.cpp
    AtomFunctionExport.cpp
    BondFunctionExport.cpp
    ReactionFunctionExport.cpp
    ControlParameterFunctionExport.cpp

    MolecularGraphPropertyExport.cpp
    AtomPropertyExport.cpp
    BondPropertyExport.cpp
    ReactionPropertyExport.cpp
    MolecularGraphPropertyDefaultExport.cpp
    AtomPropertyDefaultExport.cpp
    BondPropertyDefaultExport.cpp
    ReactionPropertyDefaultExport.cpp
    ControlParameterExport.cpp
    ControlParameterDefaultExport.cpp

    DataFormatExport.cpp
    AlignmentExport.cpp
    ArrowStyleExport.cpp
    LayoutDirectionExport.cpp
    LayoutStyleExport.cpp
    SizeAdjustmentExport.cpp

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

IF(HAVE_CAIRO_PNG_SUPPORT)
  SET(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      PNGMolecularGraphWriterExport.cpp
      PNGReactionWriterExport.cpp
      PNGMolecularGraphOutputHandlerExport.cpp
      PNGReactionOutputHandlerExport.cpp
     )	
ENDIF(HAVE_CAIRO_PNG_SUPPORT)

IF(HAVE_CAIRO_PDF_SUPPORT)
  SET(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      PDFMolecularGraphWriterExport.cpp
      PDFReactionWriterExport.cpp
      PDFMolecularGraphOutputHandlerExport.cpp
      PDFReactionOutputHandlerExport.cpp
     )	
ENDIF(HAVE_CAIRO_PDF_SUPPORT)

IF(HAVE_CAIRO_PS_SUPPORT)
  SET(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      PSMolecularGraphWriterExport.cpp
      PSReactionWriterExport.cpp
      PSMolecularGraphOutputHandlerExport.cpp
      PSReactionOutputHandlerExport.cpp
     )	
ENDIF(HAVE_CAIRO_PS_SUPPORT)

IF(HAVE_CAIRO_SVG_SUPPORT)
  SET(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      SVGMolecularGraphWriterExport.cpp
      SVGReactionWriterExport.cpp
      SVGMolecularGraphOutputHandlerExport.cpp
      SVGReactionOutputHandlerExport.cpp
     )	
ENDIF(HAVE_CAIRO_SVG_SUPPORT)

ADD_LIBRARY(_vis MODULE ${vis_MOD_SRCS})

TARGET_LINK_LIBRARIES(_vis cdpl-vis-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_vis PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_vis PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_vis PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_vis PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_vis.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_vis PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Vis" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _vis DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Vis" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
