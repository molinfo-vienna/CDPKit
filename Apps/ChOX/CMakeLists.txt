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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

SET(chox_SRCS
    Main.cpp
    MainWindow.cpp
    DataSet.cpp
    DataSetViewControl.cpp
    DataSetView.cpp
    DataSetPageView.cpp
    DataSetPagePainter.cpp
    DataRecordPainter.cpp
    DataSetPrinter.cpp
    DataSetWriter.cpp
    DataSetReader.cpp
    RecentFilesList.cpp
    InputFileFilterList.cpp
    OutputFileFilterList.cpp
    MainWindowList.cpp
    ControlParameter.cpp
    ControlParameterFunctions.cpp
    ControlParameterDefault.cpp
    Utilities.cpp
    Settings.cpp
    SettingsEditWidget.cpp
    TabSettingsEditWidget.cpp
    ColorEditWidget.cpp
    SizeSpecEditWidget.cpp
    SizeAdjustmentEditWidget.cpp
    FontChooserWidget.cpp
    FontChooserDialog.cpp
    FontEditWidget.cpp
    LayoutEditWidget.cpp
    AlignmentEditWidget.cpp
    ArrowStyleEditWidget.cpp
    LineStyleEditWidget.cpp
    CTabVersionEditWidget.cpp
    RecordSeparatorEditWidget.cpp
    SMILESRecordFormatEditWidget.cpp
    AtomColorButton.cpp
    AtomGeneralSettingsEditWidget.cpp
    AtomColorSettingsEditWidget.cpp
    AtomSettingsEditWidget.cpp
    BondSettingsEditWidget.cpp
    ReactionSettingsEditWidget.cpp
    ViewSettingsEditWidget.cpp
    PrintSettingsEditWidget.cpp
    IOSettingsEditWidget.cpp
    MOLFileIOSettingsEditWidget.cpp
    SDFileIOSettingsEditWidget.cpp
    RXNFileIOSettingsEditWidget.cpp
    RDFileIOSettingsEditWidget.cpp
    SMILESIOSettingsEditWidget.cpp
    OtherIOSettingsEditWidget.cpp
    SettingsEditDialog.cpp
    AboutDialog.cpp
    PrintProgressDialog.cpp
    RangeSelectionDialog.cpp
   )

SET(chox_UI_FILES MainWindow.ui)

SET(chox_RESOURCES Resources.qrc)

SET(chox_MOC_HDRS
    MainWindow.hpp 
    DataSet.hpp 
    DataSetView.hpp 
    DataSetViewControl.hpp 
    DataSetPageView.hpp 
    DataSetPrinter.hpp 
    DataSetWriter.hpp 
    DataSetReader.hpp 
    RecentFilesList.hpp 
    MainWindowList.hpp 
    Settings.hpp 
    SettingsEditWidget.hpp 
    TabSettingsEditWidget.hpp
    ColorEditWidget.hpp
    FontEditWidget.hpp
    SizeSpecEditWidget.hpp
    SizeAdjustmentEditWidget.hpp
    LayoutEditWidget.hpp
    AlignmentEditWidget.hpp
    ArrowStyleEditWidget.hpp
    LineStyleEditWidget.hpp
    CTabVersionEditWidget.hpp
    RecordSeparatorEditWidget.hpp
    SMILESRecordFormatEditWidget.hpp
    FontChooserWidget.hpp
    FontChooserDialog.hpp
    AtomColorButton.hpp
    AtomGeneralSettingsEditWidget.hpp
    AtomColorSettingsEditWidget.hpp
    AtomSettingsEditWidget.hpp
    BondSettingsEditWidget.hpp
    ReactionSettingsEditWidget.hpp
    ViewSettingsEditWidget.hpp
    PrintSettingsEditWidget.hpp
    IOSettingsEditWidget.hpp
    MOLFileIOSettingsEditWidget.hpp
    SDFileIOSettingsEditWidget.hpp
    RXNFileIOSettingsEditWidget.hpp
    RDFileIOSettingsEditWidget.hpp
    SMILESIOSettingsEditWidget.hpp
    OtherIOSettingsEditWidget.hpp
    SettingsEditDialog.hpp
    AboutDialog.hpp
    PrintProgressDialog.hpp
    RangeSelectionDialog.hpp 
   )

QT5_WRAP_UI(chox_SRCS ${chox_UI_FILES})
QT5_WRAP_CPP(chox_SRCS ${chox_MOC_HDRS})
QT5_ADD_RESOURCES(chox_SRCS ${chox_RESOURCES})

IF(APPLE)
  ADD_EXECUTABLE(chox MACOSX_BUNDLE ${chox_SRCS} Icons/chox.icns)

  SET_TARGET_PROPERTIES(chox PROPERTIES
                        MACOSX_BUNDLE_BUNDLE_NAME ChOX
                        MACOSX_BUNDLE_BUNDLE_VERSION "${CDPKIT_VERSION}"
                        MACOSX_BUNDLE_ICON_FILE chox.icns
                        MACOSX_BUNDLE_COPYRIGHT "Thomas A. Seidel"
                        MACOSX_BUNDLE_LONG_VERSION_STRING "${CDPKIT_VERSION}"
                        MACOSX_BUNDLE_SHORT_VERSION_STRING "${CDPKIT_VERSION}"
                        OUTPUT_NAME ChOX
                       )

  SET_SOURCE_FILES_PROPERTIES(Icons/chox.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

  CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/MacDeployQt.cmake.in"
  	         "${CMAKE_CURRENT_BINARY_DIR}/MacDeployQt.cmake" 
                 @ONLY
                )
  CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/MacCodeSigning.cmake.in"
  	         "${CMAKE_CURRENT_BINARY_DIR}/MacCodeSigning.cmake" 
                 @ONLY
                )
  TARGET_LINK_LIBRARIES(chox cdpl-chem-static cdpl-molprop-static cdpl-vis-static cdpl-biomol-static cdpl-pharm-static cdpl-confgen-static Qt5::Gui Qt5::Widgets Qt5::PrintSupport)
ELSE(APPLE)
  IF(WIN32)
    IF(MINGW) # resource compilation for mingw
      FIND_PROGRAM(WINDRES_EXECUTABLE NAMES windres.exe windres)

      IF(WINDRES_EXECUTABLE)
        ADD_CUSTOM_COMMAND(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/chox_rc.obj"
                           COMMAND "${WINDRES_EXECUTABLE}" "-I${CMAKE_CURRENT_SOURCE_DIR}/Icons"
                                   "-i${CMAKE_CURRENT_SOURCE_DIR}/Icons/chox.rc"
                                   "-o${CMAKE_CURRENT_BINARY_DIR}/chox_rc.obj")
        SET(chox_SRCS ${chox_SRCS} "${CMAKE_CURRENT_BINARY_DIR}/chox_rc.obj")
      ELSE(WINDRES_EXECUTABLE)
        MESSAGE("!! Warning: windres.exe not found -> can't compile application resource files.")
      ENDIF(WINDRES_EXECUTABLE)
    ENDIF(MINGW)

    ADD_EXECUTABLE(chox WIN32 ${chox_SRCS})
    SET_TARGET_PROPERTIES(chox PROPERTIES OUTPUT_NAME ChOX)

    INCLUDE(WinDeployQt)
    WinDeployQt(chox "${CMAKE_CURRENT_BINARY_DIR}" Applications "${CDPKIT_EXECUTABLE_INSTALL_DIR}")

    SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/ChOX.exe")
  ELSE(WIN32)
    ADD_EXECUTABLE(chox ${chox_SRCS})

    SET_TARGET_PROPERTIES(chox PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

    CONFIGURE_FILE(chox.desktop "${CMAKE_CURRENT_BINARY_DIR}/chox.desktop" COPYONLY)
    CONFIGURE_FILE(Icons/chox.png "${CMAKE_CURRENT_BINARY_DIR}/chox.png" COPYONLY)

    INSTALL(FILES chox.desktop DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
    INSTALL(FILES Icons/chox.png DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
  
    SET(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/chox")
  ENDIF(WIN32)

  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in"
  	         "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                 @ONLY
                )
  TARGET_LINK_LIBRARIES(chox cdpl-chem-shared cdpl-molprop-shared cdpl-vis-shared cdpl-biomol-shared cdpl-pharm-shared cdpl-confgen-shared Qt5::Gui Qt5::Widgets Qt5::PrintSupport)
ENDIF(APPLE)

IF(NOT APPLE)
  INSTALL(TARGETS chox DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT Applications)
ELSE(NOT APPLE)
  INSTALL(TARGETS chox BUNDLE DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
  
  IF(MACDEPLOYQT_EXECUTABLE)
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/MacDeployQt.cmake" COMPONENT Applications)
  ENDIF(MACDEPLOYQT_EXECUTABLE)

  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/MacCodeSigning.cmake" COMPONENT Applications)
ENDIF(NOT APPLE)
