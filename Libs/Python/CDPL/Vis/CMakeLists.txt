INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
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
    MolecularGraphFunctionExport.cpp
    AtomFunctionExport.cpp
    BondFunctionExport.cpp
    ReactionFunctionExport.cpp
    ControlParameterFunctionExport.cpp
    MolecularGraphPropertyExport.cpp
    AtomPropertyExport.cpp
    BondPropertyExport.cpp
    ReactionPropertyExport.cpp
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
