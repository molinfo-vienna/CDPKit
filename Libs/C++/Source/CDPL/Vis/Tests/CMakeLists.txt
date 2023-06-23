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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
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
    StructureView2DTest.cpp
    ReactionView2DTest.cpp
    LinePrimitive2DTest.cpp
    PolygonPrimitive2DTest.cpp
    PolylinePrimitive2DTest.cpp
    LineSegmentListPrimitive2DTest.cpp
    PointListPrimitive2DTest.cpp
    TextLabelPrimitive2DTest.cpp
    EllipsePrimitive2DTest.cpp
    DataFormatTest.cpp
    #ControlParameterFunctionsTest.cpp
    #AtomFunctionsTest.cpp
    #BondFunctionsTest.cpp
    #MolecularGraphFunctionsTest.cpp
    #ReactionFunctionsTest.cpp
    Utilities.cpp
   )

IF(Qt5Gui_FOUND)
  SET(test-suite_SRCS
      ${test-suite_SRCS}
      QtRenderer2DTest.cpp
      QtFontMetricsTest.cpp
      QtObjectFactoryTest.cpp
     )	

  LINK_LIBRARIES(Qt5::Gui Qt5::Widgets)
ENDIF(Qt5Gui_FOUND)

IF(CAIRO_FOUND)
  IF(HAVE_CAIRO_PNG_SUPPORT)
    SET(test-suite_SRCS
        ${test-suite_SRCS}
        CairoRenderer2DTest.cpp
        CairoFontMetricsTest.cpp
        PNGMolecularGraphWriterTest.cpp
        PNGReactionWriterTest.cpp
        PNGMolecularGraphOutputHandlerTest.cpp
        PNGReactionOutputHandlerTest.cpp 
       )	
  ENDIF(HAVE_CAIRO_PNG_SUPPORT)

  IF(HAVE_CAIRO_PDF_SUPPORT)
    SET(test-suite_SRCS
        ${test-suite_SRCS}
        PDFMolecularGraphWriterTest.cpp
        PDFReactionWriterTest.cpp
        PDFMolecularGraphOutputHandlerTest.cpp
        PDFReactionOutputHandlerTest.cpp 
       )	
  ENDIF(HAVE_CAIRO_PDF_SUPPORT)

  IF(HAVE_CAIRO_PS_SUPPORT)
    SET(test-suite_SRCS
        ${test-suite_SRCS}
        PSMolecularGraphWriterTest.cpp
        PSReactionWriterTest.cpp
        PSMolecularGraphOutputHandlerTest.cpp
        PSReactionOutputHandlerTest.cpp 
       )	
  ENDIF(HAVE_CAIRO_PS_SUPPORT)

  IF(HAVE_CAIRO_SVG_SUPPORT)
    SET(test-suite_SRCS
        ${test-suite_SRCS}
        SVGMolecularGraphWriterTest.cpp
        SVGReactionWriterTest.cpp
        SVGMolecularGraphOutputHandlerTest.cpp
        SVGReactionOutputHandlerTest.cpp 
       )	
  ENDIF(HAVE_CAIRO_SVG_SUPPORT)

  LINK_LIBRARIES(${CAIRO_LIBRARIES})
  INCLUDE_DIRECTORIES("${CAIRO_INCLUDE_DIR}")
ENDIF(CAIRO_FOUND)

SET(CMAKE_BUILD_TYPE "Debug")

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(vis-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(vis-test-suite cdpl-vis-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Vis" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/vis-test-suite")
