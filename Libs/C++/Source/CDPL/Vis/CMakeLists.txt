INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

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
    Font.cpp
    Rectangle2D.cpp
    Line2D.cpp
    PointArray2D.cpp
    LinePrimitive2D.cpp
    PolygonPrimitive2D.cpp
    PolylinePrimitive2D.cpp
    LineSegmentListPrimitive2D.cpp
    PointListPrimitive2D.cpp
    TextLabelPrimitive2D.cpp
   )

IF(Qt5Gui_FOUND)
  SET(cdpl-vis_LIB_SRCS
      ${cdpl-vis_LIB_SRCS}
      QtRenderer2D.cpp
      QtFontMetrics.cpp
      QtObjectFactory.cpp
     )	

  LINK_LIBRARIES(Qt5::Gui)
ENDIF(Qt5Gui_FOUND)

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

ADD_LIBRARY(cdpl-vis-static STATIC ${cdpl-vis_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-vis-static cdpl-chem-static cdpl-base-static)

SET_TARGET_PROPERTIES(cdpl-vis-static PROPERTIES 
                      OUTPUT_NAME cdpl-vis
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_VIS_STATIC_LINK;CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

INSTALL(TARGETS cdpl-vis-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-vis-shared SHARED ${cdpl-vis_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-vis-shared cdpl-chem-shared cdpl-base-shared)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-vis-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Vis
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-vis-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-vis
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-vis.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-vis-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
