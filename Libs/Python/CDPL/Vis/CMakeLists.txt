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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB PYTHON_FILES "*.py")

foreach(PYTHON_FILE ${PYTHON_FILES})
  configure_file("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
endforeach(PYTHON_FILE)

set(vis_MOD_SRCS
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
    Path2DExport.cpp
    Path2DConverterExport.cpp
    ColorTableExport.cpp
    AtomColorTableExport.cpp
    
    GraphicsPrimitive2DExport.cpp
    View2DExport.cpp
    Renderer2DExport.cpp
    StructureView2DExport.cpp
    ReactionView2DExport.cpp
    StructureGridView2DExport.cpp
    LinePrimitive2DExport.cpp
    PolygonPrimitive2DExport.cpp
    PolylinePrimitive2DExport.cpp
    LineSegmentListPrimitive2DExport.cpp
    PointListPrimitive2DExport.cpp
    TextLabelPrimitive2DExport.cpp
    TextBlockPrimitive2DExport.cpp
    EllipsePrimitive2DExport.cpp
    PathPrimitive2DExport.cpp
    ClipPathPrimitive2DExport.cpp

    Object3DExport.cpp
    Shape3DExport.cpp
    TriangleMesh3DExport.cpp
    Shape3DVisitorExport.cpp
    
    MolecularGraphFunctionExport.cpp
    AtomFunctionExport.cpp
    BondFunctionExport.cpp
    ReactionFunctionExport.cpp
    Object3DFunctionExport.cpp
    ControlParameterFunctionExport.cpp

    MolecularGraphPropertyExport.cpp
    AtomPropertyExport.cpp
    BondPropertyExport.cpp
    ReactionPropertyExport.cpp
    Object3DPropertyExport.cpp
    MolecularGraphPropertyDefaultExport.cpp
    AtomPropertyDefaultExport.cpp
    BondPropertyDefaultExport.cpp
    ReactionPropertyDefaultExport.cpp
    Object3DPropertyDefaultExport.cpp
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

if(HAVE_CAIRO_PNG_SUPPORT)
  set(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      PNGMolecularGraphWriterExport.cpp
      PNGReactionWriterExport.cpp
      PNGMolecularGraphOutputHandlerExport.cpp
      PNGReactionOutputHandlerExport.cpp
     )    
endif(HAVE_CAIRO_PNG_SUPPORT)

if(HAVE_CAIRO_PDF_SUPPORT)
  set(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      PDFMolecularGraphWriterExport.cpp
      PDFReactionWriterExport.cpp
      PDFMolecularGraphOutputHandlerExport.cpp
      PDFReactionOutputHandlerExport.cpp
     )    
endif(HAVE_CAIRO_PDF_SUPPORT)

if(HAVE_CAIRO_PS_SUPPORT)
  set(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      PSMolecularGraphWriterExport.cpp
      PSReactionWriterExport.cpp
      PSMolecularGraphOutputHandlerExport.cpp
      PSReactionOutputHandlerExport.cpp
     )    
endif(HAVE_CAIRO_PS_SUPPORT)

if(HAVE_CAIRO_SVG_SUPPORT)
  set(vis_MOD_SRCS
      ${vis_MOD_SRCS}
      SVGMolecularGraphWriterExport.cpp
      SVGReactionWriterExport.cpp
      SVGMolecularGraphOutputHandlerExport.cpp
      SVGReactionOutputHandlerExport.cpp
     )    
endif(HAVE_CAIRO_SVG_SUPPORT)

add_library(_vis MODULE ${vis_MOD_SRCS})

target_link_libraries(_vis cdpl-vis-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_vis PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_vis PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Vis/_vis.pyd")
else(WIN32)
  set_target_properties(_vis PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Vis/_vis.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Vis" COMPONENT CDPLPythonModules)
install(TARGETS _vis DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Vis" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
