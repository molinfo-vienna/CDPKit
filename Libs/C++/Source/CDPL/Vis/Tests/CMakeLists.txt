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

set(test-suite_SRCS
    Main.cpp
    ConvenienceHeaderTest.cpp
    FontTest.cpp
    BrushTest.cpp
    PenTest.cpp
    ColorTest.cpp
    SizeSpecificationTest.cpp
    ColorTableTest.cpp
    AtomColorTableTest.cpp
    PointArray2DTest.cpp
    Line2DTest.cpp
    Rectangle2DTest.cpp
    Path2DTest.cpp
    StructureView2DTest.cpp
    ReactionView2DTest.cpp
    LinePrimitive2DTest.cpp
    PolygonPrimitive2DTest.cpp
    PolylinePrimitive2DTest.cpp
    LineSegmentListPrimitive2DTest.cpp
    PointListPrimitive2DTest.cpp
    TextLabelPrimitive2DTest.cpp
    EllipsePrimitive2DTest.cpp
    PathPrimitive2DTest.cpp
    ClipPathPrimitive2DTest.cpp
    DataFormatTest.cpp
    Utilities.cpp
   )

if(Qt5Gui_FOUND)
  set(test-suite_SRCS
      ${test-suite_SRCS}
      QtRenderer2DTest.cpp
      QtFontMetricsTest.cpp
      QtObjectFactoryTest.cpp
     )    

  link_libraries(cdpl-vis-qt-static Qt5::Gui Qt5::Widgets)
endif(Qt5Gui_FOUND)

if(CAIRO_FOUND)
  if(HAVE_CAIRO_PNG_SUPPORT)
    set(test-suite_SRCS
        ${test-suite_SRCS}
        CairoRenderer2DTest.cpp
        CairoFontMetricsTest.cpp
        PNGMolecularGraphWriterTest.cpp
        PNGReactionWriterTest.cpp
        PNGMolecularGraphOutputHandlerTest.cpp
        PNGReactionOutputHandlerTest.cpp 
       )    
  endif(HAVE_CAIRO_PNG_SUPPORT)

  if(HAVE_CAIRO_PDF_SUPPORT)
    set(test-suite_SRCS
        ${test-suite_SRCS}
        PDFMolecularGraphWriterTest.cpp
        PDFReactionWriterTest.cpp
        PDFMolecularGraphOutputHandlerTest.cpp
        PDFReactionOutputHandlerTest.cpp 
       )    
  endif(HAVE_CAIRO_PDF_SUPPORT)

  if(HAVE_CAIRO_PS_SUPPORT)
    set(test-suite_SRCS
        ${test-suite_SRCS}
        PSMolecularGraphWriterTest.cpp
        PSReactionWriterTest.cpp
        PSMolecularGraphOutputHandlerTest.cpp
        PSReactionOutputHandlerTest.cpp 
       )    
  endif(HAVE_CAIRO_PS_SUPPORT)

  if(HAVE_CAIRO_SVG_SUPPORT)
    set(test-suite_SRCS
        ${test-suite_SRCS}
        SVGMolecularGraphWriterTest.cpp
        SVGReactionWriterTest.cpp
        SVGMolecularGraphOutputHandlerTest.cpp
        SVGReactionOutputHandlerTest.cpp 
       )    
  endif(HAVE_CAIRO_SVG_SUPPORT)

  link_libraries(${CAIRO_LIBRARIES})
  include_directories("${CAIRO_INCLUDE_DIR}")
endif(CAIRO_FOUND)

set(CMAKE_BUILD_TYPE "Debug")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

add_executable(vis-test-suite ${test-suite_SRCS})

target_link_libraries(vis-test-suite cdpl-vis-shared cdpl-vis-qt-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Vis" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/vis-test-suite")
