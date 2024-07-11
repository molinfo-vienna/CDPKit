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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

set(chox_SRCS
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
    SubstructSearchUtilsToolBar.cpp
    SubstructHighlightingPatternsEditWidget.cpp
    SubstructHighlightingPatternsEditAction.cpp
    SubstructHighlightingProcessor.cpp
    SubstructSearchQueryEditDialog.cpp
    SubstructSearchHitsActionDialog.cpp
    SubstructSearchProcessor.cpp
   )

set(chox_UI_FILES MainWindow.ui)

set(chox_RESOURCES Resources.qrc)

set(chox_MOC_HDRS
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
    SubstructSearchUtilsToolBar.hpp
    SubstructHighlightingPatternsEditWidget.hpp
    SubstructHighlightingPatternsEditAction.hpp
    SubstructHighlightingProcessor.hpp
    SubstructSearchQueryEditDialog.hpp
    SubstructSearchHitsActionDialog.hpp
    SubstructSearchProcessor.hpp
   )

qt5_wrap_ui(chox_SRCS ${chox_UI_FILES})
qt5_wrap_cpp(chox_SRCS ${chox_MOC_HDRS})
qt5_add_resources(chox_SRCS ${chox_RESOURCES})

if(APPLE)
  add_executable(chox MACOSX_BUNDLE ${chox_SRCS} Icons/chox.icns)

  set_target_properties(chox PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME ChOX
    MACOSX_BUNDLE_BUNDLE_VERSION "${CDPKIT_VERSION}"
    MACOSX_BUNDLE_ICON_FILE chox.icns
    MACOSX_BUNDLE_COPYRIGHT "Thomas Seidel"
    MACOSX_BUNDLE_LONG_VERSION_STRING "${CDPKIT_VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${CDPKIT_VERSION}"
    OUTPUT_NAME ChOX)

  set_source_files_properties(Icons/chox.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MacDeployQt.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MacDeployQt.cmake" @ONLY)
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/MacCodeSigning.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MacCodeSigning.cmake" @ONLY)
  target_link_libraries(chox cdpl-chem-static cdpl-molprop-static cdpl-vis-static cdpl-vis-qt-static cdpl-biomol-static
    cdpl-pharm-static cdpl-confgen-static Qt5::Gui Qt5::Widgets Qt5::PrintSupport)
else(APPLE)
  if(WIN32)
    set(chox_SRCS ${chox_SRCS} Icons/chox.rc)

    add_executable(chox WIN32 ${chox_SRCS})
    set_target_properties(chox PROPERTIES OUTPUT_NAME ChOX)

    set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/ChOX.exe")

    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/WinDeployQt.cmake.in"
      "${CMAKE_CURRENT_BINARY_DIR}/WinDeployQt.cmake" @ONLY)
  else(WIN32)
    add_executable(chox ${chox_SRCS})

    set_target_properties(chox PROPERTIES INSTALL_RPATH "${CDPKIT_EXECUTABLE_INSTALL_RPATH}")

    configure_file(chox.desktop.in "${CMAKE_CURRENT_BINARY_DIR}/chox.desktop" @ONLY)
    configure_file(qt.conf.in "${CMAKE_CURRENT_BINARY_DIR}/_qt.conf" @ONLY)

    if(EXISTS "${QT_BIN_DIR}/../plugins")
      install(DIRECTORY "${QT_BIN_DIR}/../plugins/iconengines" DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}/plugins")
      install(DIRECTORY "${QT_BIN_DIR}/../plugins/imageformats" DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}/plugins")
      install(DIRECTORY "${QT_BIN_DIR}/../plugins/platforminputcontexts" DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}/plugins")
      install(DIRECTORY "${QT_BIN_DIR}/../plugins/platforms" DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}/plugins" FILES_MATCHING PATTERN "libqxcb.*")
      install(DIRECTORY "${QT_BIN_DIR}/../plugins/printsupport" DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}/plugins")
      install(DIRECTORY "${QT_BIN_DIR}/../plugins/xcbglintegrations" DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}/plugins")

      install(FILES "${CMAKE_CURRENT_BINARY_DIR}/_qt.conf" DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" RENAME "qt.conf" COMPONENT Applications)
      install(FILES "${CMAKE_CURRENT_BINARY_DIR}/chox.desktop" DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
      install(FILES Icons/chox.png DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
      
      set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/plugins/platforms/libqxcb.so")

      configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/InstallQtPlatformModuleRuntimeDependencies.cmake" @ONLY)

      install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallQtPlatformModuleRuntimeDependencies.cmake" COMPONENT Applications)
    else()
      message("!! Warning: Qt plugins directory not found -> can't fully deploy Qt applications.")
    endif(EXISTS "${QT_BIN_DIR}/../plugins")
  
    set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/chox")
  endif(WIN32)

  configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)
  target_link_libraries(chox cdpl-chem-shared cdpl-molprop-shared cdpl-vis-shared cdpl-vis-qt-shared cdpl-biomol-shared
    cdpl-pharm-shared cdpl-confgen-shared Qt5::Gui Qt5::Widgets Qt5::PrintSupport)
endif(APPLE)

if(NOT APPLE)
  install(TARGETS chox DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
  install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT Applications)

  if(WIN32 AND WINDEPLOYQT_EXECUTABLE)
    install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/WinDeployQt.cmake" COMPONENT Applications)
  endif(WIN32 AND WINDEPLOYQT_EXECUTABLE)
else(NOT APPLE)
  install(TARGETS chox BUNDLE DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT Applications)
  
  if(MACDEPLOYQT_EXECUTABLE)
    install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/MacDeployQt.cmake" COMPONENT Applications)
  endif(MACDEPLOYQT_EXECUTABLE)

  install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/MacCodeSigning.cmake" COMPONENT Applications)
endif(NOT APPLE)
