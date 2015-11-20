INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(test-suite_SRCS
    Main.cpp
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
    DataFormatTest.cpp
    #ControlParameterFunctionsTest.cpp
    #AtomFunctionsTest.cpp
    #BondFunctionsTest.cpp
    #MolecularGraphFunctionsTest.cpp
    #ReactionFunctionsTest.cpp
    Utilities.cpp
   )

IF(QT4_FOUND)
  SET(test-suite_SRCS
      ${test-suite_SRCS}
      QtRenderer2DTest.cpp
      QtFontMetricsTest.cpp
      QtObjectFactoryTest.cpp
     )	

  LINK_LIBRARIES(${QT_LIBRARIES})
  ADD_DEFINITIONS(${QT_DEFINITIONS})
  INCLUDE_DIRECTORIES(${QT_INCLUDES})
ENDIF(QT4_FOUND)

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

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

ADD_EXECUTABLE(vis-test-suite ${test-suite_SRCS})

TARGET_LINK_LIBRARIES(vis-test-suite cdpl-vis-shared ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

ADD_TEST("CDPL::Vis" "${RUN_CXX_TESTS}" "${CMAKE_CURRENT_BINARY_DIR}/vis-test-suite")
