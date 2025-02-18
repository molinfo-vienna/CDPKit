/* 
 * MainWindow.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <algorithm>
#include <cmath>
#include <functional>

#include <QFileDialog>
#include <QStatusBar>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QMenu>
#include <QSettings>
#include <QAction>
#include <QDesktopWidget>
#include <QPrinter>
#include <QRect>
#include <QCloseEvent>

#include "CDPL/Vis/ControlParameterFunctions.hpp"
#include "CDPL/Vis/ControlParameter.hpp"
#include "CDPL/Vis/Alignment.hpp"
#include "CDPL/Vis/SizeAdjustment.hpp"
#include "CDPL/Vis/ArrowStyle.hpp"
#include "CDPL/Vis/LayoutStyle.hpp"
#include "CDPL/Vis/LayoutDirection.hpp"

#include "MainWindow.hpp"
#include "DataSet.hpp"
#include "DataSetView.hpp"
#include "DataSetViewControl.hpp"
#include "DataSetPageView.hpp"
#include "DataSetPrinter.hpp"
#include "DataSetWriter.hpp"
#include "DataSetReader.hpp"
#include "RecentFilesList.hpp"
#include "MainWindowList.hpp"
#include "FileOpenDialog.hpp"
#include "FileSaveDialog.hpp"
#include "ControlParameter.hpp"
#include "ControlParameterFunctions.hpp"
#include "Settings.hpp"
#include "SettingsEditDialog.hpp"
#include "AboutDialog.hpp"
#include "RangeSelectionDialog.hpp"
#include "SubstructSearchUtilsToolBar.hpp"
#include "SubstructHighlightingProcessor.hpp"
#include "SubstructSearchProcessor.hpp"
#include "Clipboard.hpp"
#include "ClipboardData.hpp"


ChOX::MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags f):
    QMainWindow(parent, f)
{
    init();
}

ChOX::MainWindow::~MainWindow()
{
    destroy();
}

void ChOX::MainWindow::init()
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAcceptDrops(true);
    
    uiMainWindow.setupUi(this);

    rangeSelectionDialog = 0;
    settingsEditDialog = 0;
    windowListGroup = 0;
    
    settings = new Settings(this);
    dataSet = new DataSet(this);
    dataSetView = new DataSetView(this, *settings, *dataSet);
    dataSetViewControl = new DataSetViewControl(this, *dataSetView);
    substructHilightingProc = new SubstructHighlightingProcessor(&dataSetView->getPageView(), *settings);

    dataSetViewControl->addAction(uiMainWindow.viewShowPropertyTableAction);
    
    addToolBar(dataSetViewControl);

    auto subsrch_proc = new SubstructSearchProcessor(this, *dataSet, *settings);
    auto subsrch_tb = new SubstructSearchUtilsToolBar(this, *settings);

    connect(subsrch_proc, SIGNAL(substructSearchEnabled(bool)), subsrch_tb, SLOT(enableSubstructSearch(bool)));
    connect(subsrch_tb, SIGNAL(performSubstructSearch()), subsrch_proc, SLOT(performSubstructSearch()));
                
    addToolBar(subsrch_tb);

    setCentralWidget(dataSetView);
    setupContextMenu();

//----

    viewInfoLabel = new QLabel(this);
    statusMessageLabel = new QLabel(this);

    viewInfoLabel->setAlignment(Qt::AlignLeft);
    viewInfoLabel->setMinimumWidth(100);

    statusBar()->addPermanentWidget(statusMessageLabel, 1);
    statusBar()->addPermanentWidget(viewInfoLabel, 0);

//----

    //uiMainWindow.windowMenu->addMenu(tr("Tool&bars"), createDockWindowMenu(OnlyToolBars), -1, 0);

//----

    DataSetPageView* page_view = &dataSetView->getPageView();

    connect(uiMainWindow.addPageRowAction, SIGNAL(triggered()), page_view, SLOT(addRow()));
    connect(uiMainWindow.deletePageRowAction, SIGNAL(triggered()), page_view, SLOT(deleteRow()));
    connect(uiMainWindow.addPageColumnAction, SIGNAL(triggered()), page_view, SLOT(addColumn()));
    connect(uiMainWindow.deletePageColumnAction, SIGNAL(triggered()), page_view, SLOT(deleteColumn()));

// +++

    connect(page_view, SIGNAL(numRowsChanged(int)), this, SLOT(handleNumRowsChange(int)));
    connect(page_view, SIGNAL(numColumnsChanged(int)), this, SLOT(handleNumColumnsChange(int)));

// +++

    connect(page_view, SIGNAL(numRowsChanged(int)), this, SLOT(handleViewSettingsChange(int)));
    connect(page_view, SIGNAL(numColumnsChanged(int)), this, SLOT(handleViewSettingsChange(int)));
    connect(page_view, SIGNAL(pageOffsetChanged(int)), this, SLOT(handleViewSettingsChange(int)));

// +++

    connect(dataSet, SIGNAL(sizeChanged(int)), this, SLOT(handleDataSetSizeChange(int)));
    connect(dataSet, SIGNAL(sizeChanged(int)), this, SLOT(handleViewSettingsChange(int)));

// +++

    connect(dataSet, SIGNAL(selectionStatusChanged(bool)), this, SLOT(handleSelectionStatusChange(bool)));

// +++

    uiMainWindow.editUndoAction->setEnabled(false);
    uiMainWindow.editRedoAction->setEnabled(false);
    
    connect(uiMainWindow.editUndoAction, SIGNAL(triggered()), dataSet, SLOT(undo()));
    connect(uiMainWindow.editRedoAction, SIGNAL(triggered()), dataSet, SLOT(redo()));

    connect(dataSet, SIGNAL(undoStatusChanged(bool)), uiMainWindow.editUndoAction, SLOT(setEnabled(bool)));
    connect(dataSet, SIGNAL(redoStatusChanged(bool)), uiMainWindow.editRedoAction, SLOT(setEnabled(bool)));

    connect(uiMainWindow.editClearAction, SIGNAL(triggered()), dataSet, SLOT(clear()));
    connect(uiMainWindow.editSelectAllAction, SIGNAL(triggered()), dataSet, SLOT(selectAll()));
    connect(uiMainWindow.editInvertSelectionAction, SIGNAL(triggered()), dataSet, SLOT(invertSelection()));
    //connect(uiMainWindow.editRemoveSelectionAction, SIGNAL(triggered()), dataSet, SLOT(removeSelected()));
    
// +++
    
    connect(&Clipboard::get(), SIGNAL(dataAvailable(bool)), uiMainWindow.editPasteAction, SLOT(setEnabled(bool)));
    
    connect(uiMainWindow.editCutAction, SIGNAL(triggered()), this, SLOT(cutRecords()));
    connect(uiMainWindow.editCopyAction, SIGNAL(triggered()), this, SLOT(copyRecords()));
    connect(uiMainWindow.editPasteAction, SIGNAL(triggered()), this, SLOT(pasteRecords()));

    uiMainWindow.editPasteAction->setEnabled(Clipboard::get().checkDataAvailability());

// +++

    connect(page_view, SIGNAL(recordNoVisibilityChanged(bool)), uiMainWindow.viewShowRecordNumbersAction, SLOT(setChecked(bool)));
    connect(page_view, SIGNAL(gridVisibilityChanged(bool)), uiMainWindow.viewShowGridAction, SLOT(setChecked(bool)));
    connect(page_view, SIGNAL(recordNameVisibilityChanged(bool)), uiMainWindow.viewShowRecordNamesAction, SLOT(setChecked(bool)));

    connect(uiMainWindow.viewShowGridAction, SIGNAL(toggled(bool)), page_view, SLOT(showGrid(bool)));
    connect(uiMainWindow.viewShowRecordNumbersAction, SIGNAL(toggled(bool)), page_view, SLOT(showRecordNumbers(bool)));
    connect(uiMainWindow.viewShowRecordNamesAction, SIGNAL(toggled(bool)), page_view, SLOT(showRecordNames(bool)));

// +++

    connect(settings, SIGNAL(controlParamChanged(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)), 
            this, SLOT(handleControlParamChange(const CDPL::Base::LookupKey&, const CDPL::Base::Any&)));

// +++

    connect(dataSet, SIGNAL(fileListChanged()), this, SLOT(updateCaption()));

// +++

    connect(statusBar(), SIGNAL(messageChanged(const QString&)), this, SLOT(showStatusMessage(const QString&)));

// +++

    connect(uiMainWindow.clearRecentFilesAction, SIGNAL(triggered()), &RecentFilesList::get(), SLOT(clear()));
    connect(uiMainWindow.recentFilesMenu, SIGNAL(triggered(QAction*)), this, SLOT(recentFileSelected(QAction*)));
    connect(&RecentFilesList::get(), SIGNAL(entriesChanged()), this, SLOT(setupRecentFilesMenu()));

// +++

    connect(uiMainWindow.windowMenu, SIGNAL(aboutToShow()), this, SLOT(setupWindowMenu()));

//----

    handleNumRowsChange(1);
    handleNumColumnsChange(1);
    handleViewSettingsChange(0);
    handleDataSetSizeChange(0);
    handleSelectionStatusChange(false);

    showStatusMessage(QString());
    setupRecentFilesMenu();
    updateCaption();

//----

    QSettings win_settings;

    win_settings.beginGroup("General/MainWindow");

    restoreState(win_settings.value("State").toByteArray());
    resize(win_settings.value("Size", QSize(640, 480)).toSize());
    move(win_settings.value("Pos", QPoint(200, 200)).toPoint());

    win_settings.endGroup();

    settings->load();

//----

    MainWindowList::get().addWindow(this);
}

void ChOX::MainWindow::setupContextMenu()
{
    contextMenu = new QMenu(this);

    contextMenu->addAction(uiMainWindow.editUndoAction);
    contextMenu->addAction(uiMainWindow.editRedoAction);

    contextMenu->addSeparator();

    contextMenu->addAction(uiMainWindow.editCutAction);
    contextMenu->addAction(uiMainWindow.editCopyAction);
    contextMenu->addAction(uiMainWindow.editPasteAction);
    //contextMenu->addAction(uiMainWindow.editRemoveSelectionAction);
    contextMenu->addAction(uiMainWindow.editClearAction);

    contextMenu->addSeparator();
        
    contextMenu->addAction(uiMainWindow.editSelectAllAction);
    contextMenu->addAction(uiMainWindow.editSelectRangeAction);
    contextMenu->addAction(uiMainWindow.editInvertSelectionAction);

    contextMenu->addSeparator();

    contextMenu->addMenu(uiMainWindow.viewHorAlignmentMenu);    
    contextMenu->addMenu(uiMainWindow.viewVerAlignmentMenu);

    contextMenu->addSeparator();

    contextMenu->addMenu(uiMainWindow.viewSizeAdjustmentMenu);

    contextMenu->addSeparator();

    contextMenu->addMenu(uiMainWindow.viewReactionMenu);
    contextMenu->addMenu(uiMainWindow.viewAtomMenu);
    contextMenu->addMenu(uiMainWindow.viewBondMenu);
 
    contextMenu->addSeparator();

    contextMenu->addAction(uiMainWindow.editSettingsAction);
    contextMenu->addAction(uiMainWindow.editSaveSettingsAction);

    contextMenu->addSeparator();

    contextMenu->addAction(uiMainWindow.editAppendFilesAction);
    contextMenu->addAction(uiMainWindow.fileSaveAsAction);
    contextMenu->addAction(uiMainWindow.fileSaveSelectionAsAction);

    contextMenu->addSeparator();

    contextMenu->addAction(uiMainWindow.filePrintAction);

    dataSetView->getPageView().setContextMenu(contextMenu);
}

void ChOX::MainWindow::destroy()
{}

void ChOX::MainWindow::fileNew()
{
    ChOX::MainWindow* new_win = new ChOX::MainWindow(0, 0);

    new_win->show();
}

void ChOX::MainWindow::fileOpen()
{
    auto& dialog = FileOpenDialog::get(*dataSet, true);

    dialog.setWindowTitle(tr("ChOX - Open File(s)"));

    if (dialog.exec() == QDialog::Accepted) {
        if (dataSet->getFileNames().empty())
            openFiles(dialog.selectedFiles());

        else {
            ChOX::MainWindow* new_win = new ChOX::MainWindow(0, 0);

            new_win->show();
            new_win->openFiles(dialog.selectedFiles());
        }
    }
}

void ChOX::MainWindow::fileSaveAs()
{
    auto& dialog = FileSaveDialog::get(*dataSet);

    dialog.setWindowTitle(tr("ChOX - Save Records As"));

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        DataSetWriter data_writer(*dataSet, this, dialog.selectedFiles().first(),
                                  dialog.selectedNameFilter(), *settings, false);

        connect(&data_writer, SIGNAL(errorMessage(const QString&)), this, SLOT(showErrorMessage(const QString&)));
        connect(&data_writer, SIGNAL(errorMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));
        connect(&data_writer, SIGNAL(statusMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));

        data_writer.setRecordDataVisitor(substructHilightingProc);
        data_writer.write();
    }
}

void ChOX::MainWindow::fileSaveSelectionAs()
{
    auto& dialog = FileSaveDialog::get(*dataSet);

    dialog.setWindowTitle(tr("ChOX - Save Selected Records As"));

    if (dialog.exec() == QDialog::Accepted && !dialog.selectedFiles().isEmpty()) {
        DataSetWriter data_writer(*dataSet, this, dialog.selectedFiles().first(),
                                  dialog.selectedNameFilter(), *settings, true);

        connect(&data_writer, SIGNAL(errorMessage(const QString&)), this, SLOT(showErrorMessage(const QString&)));
        connect(&data_writer, SIGNAL(errorMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));
        connect(&data_writer, SIGNAL(statusMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));

        data_writer.setRecordDataVisitor(substructHilightingProc);
        data_writer.write();
    }
}

void ChOX::MainWindow::fileAppend()
{
    auto& dialog = FileOpenDialog::get(*dataSet, false);

    dialog.setWindowTitle(tr("ChOX - Append File(s)"));

    if (dialog.exec() == QDialog::Accepted) 
        openFiles(dialog.selectedFiles());
}

bool ChOX::MainWindow::openFiles(const QStringList& file_names)
{
    QStringList::ConstIterator files_end = file_names.end();
    bool success = false;

    for (QStringList::ConstIterator it = file_names.begin(); it != files_end; ++it) {
        DataSetReader data_reader(*dataSet, this, *it, *settings);

        connect(&data_reader, SIGNAL(errorMessage(const QString&)), this, SLOT(showErrorMessage(const QString&)));
        connect(&data_reader, SIGNAL(errorMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));
        connect(&data_reader, SIGNAL(statusMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));

        if (data_reader.read()) {
            ChOX::RecentFilesList::get().addEntry(*it);
            success = true;
        }
    }

    return success;
}

void ChOX::MainWindow::filePrint()
{
    QPrinter printer;
    printer.setCreator("ChOX");

    ChOX::DataSetPrinter data_printer(*settings, *dataSet);

    connect(&data_printer, SIGNAL(errorMessage(const QString&)), this, SLOT(showErrorMessage(const QString&)));
    connect(&data_printer, SIGNAL(errorMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));
    connect(&data_printer, SIGNAL(statusMessage(const QString&)), this, SLOT(showStatusMessage(const QString&)));

    data_printer.setRecordDataVisitor(substructHilightingProc);
    data_printer.print(this, printer);
}

void ChOX::MainWindow::fileQuit()
{
    qApp->closeAllWindows();
}

void ChOX::MainWindow::pasteRecords()
{
    Clipboard::get().getData(this, *dataSet, dataSetView->getPageView().getPageOffset());
}

void ChOX::MainWindow::cutRecords()
{
    Clipboard::get().putSelectedData(*dataSet);

    dataSet->removeSelected();
}

void ChOX::MainWindow::copyRecords()
{
    Clipboard::get().putSelectedData(*dataSet);
}

void ChOX::MainWindow::selectRecordRange()
{
    if (!rangeSelectionDialog)
        rangeSelectionDialog = new ChOX::RangeSelectionDialog(this, *dataSet);

    rangeSelectionDialog->exec();
}

void ChOX::MainWindow::editSettings()
{
    if (!settingsEditDialog)
        settingsEditDialog = new ChOX::SettingsEditDialog(this, *settings);

    settingsEditDialog->exec();
}

void ChOX::MainWindow::saveSettings()
{
    settings->save();
}

void ChOX::MainWindow::helpAbout()
{
    QDialog* dlg = new ChOX::AboutDialog(this);

    dlg->exec();
}

void ChOX::MainWindow::handleNumColumnsChange(int num_cols)
{
    uiMainWindow.deletePageColumnAction->setDisabled(num_cols <= 1);
}

void ChOX::MainWindow::handleNumRowsChange(int num_rows)
{
    uiMainWindow.deletePageRowAction->setDisabled(num_rows <= 1);
}

void ChOX::MainWindow::handleDataSetSizeChange(int new_size)
{
    uiMainWindow.editClearAction->setEnabled(new_size > 0 || !dataSet->getFileNames().empty());
    uiMainWindow.editSelectAllAction->setEnabled(new_size > 0);
    uiMainWindow.editSelectRangeAction->setEnabled(new_size > 0);
    uiMainWindow.editInvertSelectionAction->setEnabled(new_size > 0);
    
    uiMainWindow.filePrintAction->setEnabled(new_size > 0);

    uiMainWindow.fileSaveAsAction->setEnabled(new_size > 0);
}

void ChOX::MainWindow::handleSelectionStatusChange(bool selected)
{
    uiMainWindow.editCutAction->setEnabled(selected);
    uiMainWindow.editCopyAction->setEnabled(selected);
    //uiMainWindow.editRemoveSelectionAction->setEnabled(selected);
    uiMainWindow.fileSaveSelectionAsAction->setEnabled(selected);
}

void ChOX::MainWindow::handleViewSettingsChange(int)
{
    if (dataSet->getSize() == 0) {
        viewInfoLabel->setText(tr("Nothing to Display"));
        return;
    }

    ChOX::DataSetPageView& page_view = dataSetView->getPageView();

    viewInfoLabel->setText(tr("Showing %1-%2 of %3")
                           .arg(page_view.getPageOffset() + 1)
                           .arg(std::min(page_view.getPageOffset() + page_view.getNumColumns() * page_view.getNumRows(), 
                                         dataSet->getSize()))
                           .arg(dataSet->getSize()));
}

void ChOX::MainWindow::showErrorMessage(const QString& msg)
{
    QMessageBox::critical(this, QString("ChOX - ") + tr("Error"), msg, QMessageBox::Ok, 
                          QMessageBox::NoButton, QMessageBox::NoButton); 
}

void ChOX::MainWindow::showStatusMessage(const QString& msg)
{
    if (msg.isEmpty())
        statusMessageLabel->setText(tr("Ready.")); 
    else
        statusMessageLabel->setText(msg);

    qApp->processEvents();
}


void ChOX::MainWindow::updateCaption()
{
    const QStringList& file_list = dataSet->getFileNames();

    if (file_list.empty()) {
        setWindowTitle("ChOX - " + tr("Nothing to display"));
        return;
    }

    QString caption("ChOX - ");

    for (QStringList::ConstIterator it = file_list.begin(); it != file_list.end(); ) {
        caption.append("'" + QFileInfo(*it).fileName() + "'");

        if (++it != file_list.end())
            caption.append(" + ");
    }

    setWindowTitle(caption);
}

void ChOX::MainWindow::recentFileSelected(QAction* action)
{
    if (action == uiMainWindow.clearRecentFilesAction)
        return;

    QStringList files;

    files.append(action->text());

    if (dataSet->getFileNames().empty())
        openFiles(files);

    else {
        ChOX::MainWindow* new_win = new ChOX::MainWindow(0);

        new_win->show();
        new_win->openFiles(files);
    }
}

void ChOX::MainWindow::setupRecentFilesMenu()
{
    std::for_each(recentFilesMenuActions.begin(), recentFilesMenuActions.end(), 
                  std::bind(&QWidget::removeAction, uiMainWindow.recentFilesMenu, std::placeholders::_1));

    recentFilesMenuActions.clear();

    const QStringList& recent_files =  ChOX::RecentFilesList::get().getEntries();

    if (recent_files.empty()) {
        uiMainWindow.recentFilesMenu->setEnabled(false);
        return;
    }

    uiMainWindow.recentFilesMenu->setEnabled(true);

    QAction* first_action = uiMainWindow.recentFilesMenu->actions().first();

    QStringList::ConstIterator list_end = recent_files.end();

    for (QStringList::ConstIterator it = recent_files.begin(); it != list_end; ++it) {
        QAction* action = new QAction(*it, uiMainWindow.recentFilesMenu);

        uiMainWindow.recentFilesMenu->insertAction(first_action, action); 

        recentFilesMenuActions.push_back(action);
    }
}

void ChOX::MainWindow::closeEvent(QCloseEvent* e)
{
    QSettings win_settings;

    win_settings.beginGroup("General/MainWindow");

    win_settings.setValue("State", saveState());
    win_settings.setValue("Size", size());
    win_settings.setValue("Pos", pos());
    
    win_settings.endGroup();

    //settings->save();

    QMainWindow::closeEvent(e);
}

void ChOX::MainWindow::setupWindowMenu()
{
    using namespace ChOX;

    if (windowListGroup) {
        QList<QAction*> actions = windowListGroup->actions();

        std::for_each(actions.begin(), actions.end(), 
                      std::bind(&QWidget::removeAction, uiMainWindow.windowMenu, std::placeholders::_1));

        windowListGroup->deleteLater();
    }

    windowListGroup = new QActionGroup(this);

    const MainWindowList& win_list = MainWindowList::get();

    MainWindowList::ConstIterator list_end = win_list.getEnd();
    int i = 1;

    for (MainWindowList::ConstIterator it = win_list.getBegin(); it != list_end; ++it, i++) {
        ChOX::MainWindow* win = *it;
        QString menu_txt = QString("%1 - %2").arg(i).arg(win->windowTitle());

        QAction* action = new QAction(windowListGroup);

        action->setText(menu_txt);
        action->setCheckable(true);

        if (win == this)
            action->setChecked(true);

        connect(action, SIGNAL(triggered()), win, SLOT(setWindowActive()));
    }
    
    uiMainWindow.windowMenu->addActions(windowListGroup->actions());
}

void ChOX::MainWindow::tileWindows()
{
    using namespace ChOX;

    const QRect& avail_geom = QApplication::desktop()->availableGeometry();

    int num_wins = MainWindowList::get().getNumWindows();
    int num_wins_per_col = int(rint(std::sqrt(double(num_wins))));
    int num_wins_per_row = int(std::ceil(double(num_wins) / num_wins_per_col));

    int win_width = int(double(avail_geom.width()) / num_wins_per_row);
    int win_height = int(double(avail_geom.height()) / num_wins_per_col);

    int free_space = num_wins_per_col * num_wins_per_row - num_wins;

    for (int i = 0, win_idx = 0; i < num_wins_per_col && win_idx < num_wins; i++) {
        for (int j = 0; j < num_wins_per_row && win_idx < num_wins; j++, win_idx++) {
            ChOX::MainWindow* win = MainWindowList::get().getWindow(win_idx);

            if (free_space > 0 && num_wins_per_row - j > 1) {
                win->resize(2 * win_width - (win->frameSize().width() - win->size().width()), 
                            win_height - (win->frameSize().height() - win->size().height()));

                win->move(j * win_width + avail_geom.left(), i * win_height + avail_geom.top());

                j++;
                free_space--;
                
            } else {
                win->resize(win_width - (win->frameSize().width() - win->size().width()), 
                            win_height - (win->frameSize().height() - win->size().height()));

                win->move(j * win_width + avail_geom.left(), i * win_height + avail_geom.top());
            }

            win->showNormal();
        }
    }
}

void ChOX::MainWindow::cascadeWindows()
{
    using namespace ChOX;

    const QRect& avail_geom = QApplication::desktop()->availableGeometry();

    const MainWindowList& win_list = MainWindowList::get();

    int num_wins = win_list.getNumWindows();
    int xy_shift = frameSize().height() - height();
    int win_width = avail_geom.width() - num_wins * xy_shift;
    int win_height = avail_geom.height() - num_wins * xy_shift;

    int x_pos = avail_geom.left();
    int y_pos = avail_geom.top();

    MainWindowList::ConstIterator list_end = win_list.getEnd();
    
    for (MainWindowList::ConstIterator it = win_list.getBegin(); it != list_end; ++it) {
        ChOX::MainWindow* win = *it;

        if (win == this)
            continue;

        win->resize(win_width - (win->frameSize().width() - win->size().width()), 
                    win_height - (win->frameSize().height() - win->size().height()));
        win->move(x_pos, y_pos);

        win->showNormal();

        win->raise();

        x_pos += xy_shift;
        y_pos += xy_shift;
    }

    resize(win_width - (frameSize().width() - width()), win_height - (frameSize().height() - height()));
    move(x_pos, y_pos);

    setWindowActive();
}

void ChOX::MainWindow::setWindowActive()
{
    activateWindow();
    raise();
}

void ChOX::MainWindow::handleSizeAdjustmentChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewSizeAdjustmentActionGroup->blockSignals(true);

    switch (getSizeAdjustmentParameter(*settings)) {

        case SizeAdjustment::BEST_FIT:
            uiMainWindow.viewBestFitSizeAdjustmentAction->setChecked(true); 
            break;

        case SizeAdjustment::NONE:
            uiMainWindow.viewNoSizeAdjustmentAction->setChecked(true); 
            break;

        default:
            uiMainWindow.viewVisibilitySizeAdjustmentAction->setChecked(true); 

    }

    uiMainWindow.viewSizeAdjustmentActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleAlignmentChange()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int alignment = getAlignmentParameter(*settings);

    uiMainWindow.viewVerAlignmentActionGroup->blockSignals(true);

    switch (alignment & Alignment::V_ALIGNMENT_MASK) {

        case Alignment::TOP:
            uiMainWindow.viewTopAlignmentAction->setChecked(true);
            break;

        case Alignment::BOTTOM:
            uiMainWindow.viewBottomAlignmentAction->setChecked(true);
            break;

        default:
            uiMainWindow.viewVerCenterAlignmentAction->setChecked(true);
    }

    uiMainWindow.viewVerAlignmentActionGroup->blockSignals(false);

    uiMainWindow.viewHorAlignmentActionGroup->blockSignals(true);

    switch (alignment & Alignment::H_ALIGNMENT_MASK) {

        case Alignment::LEFT:
            uiMainWindow.viewLeftAlignmentAction->setChecked(true);
            break;

        case Alignment::RIGHT:
            uiMainWindow.viewRightAlignmentAction->setChecked(true);
            break;

        default:
            uiMainWindow.viewHorCenterAlignmentAction->setChecked(true);
    }

    uiMainWindow.viewHorAlignmentActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleArrowStyleChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewArrowStyleActionGroup->blockSignals(true);

    switch (getReactionArrowStyleParameter(*settings)) {

        case ArrowStyle::NONE:
            uiMainWindow.viewNoReactionArrowAction->setChecked(true); 
            break;

        case ArrowStyle::REACTION_HOLLOW:
            uiMainWindow.viewHollowReactionArrowAction->setChecked(true); 
            break;

        default:
            uiMainWindow.viewStandardReactionArrowAction->setChecked(true); 
    }

    uiMainWindow.viewArrowStyleActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleComponentLayoutChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewComponentLayoutActionGroup->blockSignals(true);

    switch (getReactionComponentLayoutParameter(*settings)) {

        case LayoutStyle::LINEAR:            
            uiMainWindow.viewLinearComponentLayoutStyleAction->setChecked(true); 
            uiMainWindow.viewComponentLayoutDirActionGroup->setEnabled(true);
            break;

        default:
            uiMainWindow.viewPackedComponentLayoutStyleAction->setChecked(true); 
            uiMainWindow.viewComponentLayoutDirActionGroup->setEnabled(false);
    }

    uiMainWindow.viewComponentLayoutActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleComponentLayoutDirChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewComponentLayoutDirActionGroup->blockSignals(true);

    switch (getReactionComponentLayoutDirectionParameter(*settings)) {

        case LayoutDirection::HORIZONTAL:
            uiMainWindow.viewHorComponentLayoutDirAction->setChecked(true); 
            break;

        default:
            uiMainWindow.viewVerComponentLayoutDirAction->setChecked(true); 
    }

    uiMainWindow.viewComponentLayoutDirActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleReactantVisibilityChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewShowReactantsAction->blockSignals(true);
    uiMainWindow.viewShowReactantsAction->setChecked(getShowReactionReactantsParameter(*settings));
    uiMainWindow.viewShowReactantsAction->blockSignals(false);
}

void ChOX::MainWindow::handleAgentVisibilityChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewShowAgentsAction->blockSignals(true);
    uiMainWindow.viewShowAgentsAction->setChecked(getShowReactionAgentsParameter(*settings));
    uiMainWindow.viewShowAgentsAction->blockSignals(false);
}

void ChOX::MainWindow::handleProductVisibilityChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewShowProductsAction->blockSignals(true);
    uiMainWindow.viewShowProductsAction->setChecked(getShowReactionProductsParameter(*settings));
    uiMainWindow.viewShowProductsAction->blockSignals(false);
}

void ChOX::MainWindow::handleAgentAlignmentChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewAgentAlignmentActionGroup->blockSignals(true);

    unsigned int alignment = getReactionAgentAlignmentParameter(*settings);

    switch (alignment & Alignment::V_ALIGNMENT_MASK) {

        case Alignment::TOP:
            uiMainWindow.viewTopAgentAlignmentAction->setChecked(true);
            break;

        case Alignment::BOTTOM:
            uiMainWindow.viewBottomAgentAlignmentAction->setChecked(true);
            break;

        default:
            uiMainWindow.viewCenterAgentAlignmentAction->setChecked(true);
    }

    uiMainWindow.viewAgentAlignmentActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleAgentLayoutChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewAgentLayoutActionGroup->blockSignals(true);

    switch (getReactionAgentLayoutParameter(*settings)) {

        case LayoutStyle::LINEAR:            
            uiMainWindow.viewLinearAgentLayoutStyleAction->setChecked(true); 
            uiMainWindow.viewAgentLayoutDirActionGroup->setEnabled(true);
            break;

        default:
            uiMainWindow.viewPackedAgentLayoutStyleAction->setChecked(true); 
            uiMainWindow.viewAgentLayoutDirActionGroup->setEnabled(false);
    }

    uiMainWindow.viewAgentLayoutActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleAgentLayoutDirChange()
{
    using namespace CDPL;
    using namespace Vis;

    uiMainWindow.viewAgentLayoutDirActionGroup->blockSignals(true);

    switch (getReactionAgentLayoutDirectionParameter(*settings)) {

        case LayoutDirection::HORIZONTAL:
            uiMainWindow.viewHorAgentLayoutDirAction->setChecked(true); 
            break;

        default:
            uiMainWindow.viewVerAgentLayoutDirAction->setChecked(true); 
    }

    uiMainWindow.viewAgentLayoutDirActionGroup->blockSignals(false);
}

void ChOX::MainWindow::handleControlParamChange(const CDPL::Base::LookupKey& key, const CDPL::Base::Any& val)
{
    using namespace CDPL;

    if (key == ControlParameter::SUBSTRUCT_HIGHLIGHTING_ENABLED) {
        uiMainWindow.viewEnableSubstructHighlightingAction->blockSignals(true);
        uiMainWindow.viewEnableSubstructHighlightingAction->setChecked(getSubstructHighlightingEnabledParameter(*settings));
        uiMainWindow.viewEnableSubstructHighlightingAction->blockSignals(false);
        return;
    }

    if (key == ControlParameter::SHOW_PROPERTY_TABLE) {
        uiMainWindow.viewShowPropertyTableAction->blockSignals(true);
        bool show = getShowPropertyTableParameter(*settings);
        
        uiMainWindow.viewShowPropertyTableAction->setChecked(show);
        dataSetView->showProperties(show);
        
        uiMainWindow.viewShowPropertyTableAction->blockSignals(false);
        return;
    }
    
    if (key == Vis::ControlParameter::SIZE_ADJUSTMENT) {
        handleSizeAdjustmentChange();
        return;
    }

    if (key == Vis::ControlParameter::ALIGNMENT) {
        handleAlignmentChange();
        return;
    }

    if (key == Vis::ControlParameter::REACTION_ARROW_STYLE) {
        handleArrowStyleChange();
        return;
    }

    if (key == Vis::ControlParameter::REACTION_COMPONENT_LAYOUT) {
        handleComponentLayoutChange();
        return;
    }

    if (key == Vis::ControlParameter::REACTION_COMPONENT_LAYOUT_DIRECTION) {
        handleComponentLayoutDirChange();
        return;
    }

    if (key == Vis::ControlParameter::SHOW_REACTION_REACTANTS) {
        handleReactantVisibilityChange();
        return;
    }

    if (key == Vis::ControlParameter::SHOW_REACTION_AGENTS) {
        handleAgentVisibilityChange();
        return;
    }

    if (key == Vis::ControlParameter::SHOW_REACTION_PRODUCTS) {
        handleProductVisibilityChange();
        return;
    }

    if (key == Vis::ControlParameter::REACTION_AGENT_ALIGNMENT) {
        handleAgentAlignmentChange();
        return;
    }

    if (key == Vis::ControlParameter::REACTION_AGENT_LAYOUT) {
        handleAgentLayoutChange();
        return;
    }

    if (key == Vis::ControlParameter::REACTION_AGENT_LAYOUT_DIRECTION) {
        handleAgentLayoutDirChange();
        return;
    }

    if (key == Vis::ControlParameter::SHOW_REACTION_PLUS_SIGNS) {
        uiMainWindow.viewShowReactionPlusSignsAction->blockSignals(true);
        uiMainWindow.viewShowReactionPlusSignsAction->setChecked(Vis::getShowReactionPlusSignsParameter(*settings));
        uiMainWindow.viewShowReactionPlusSignsAction->blockSignals(false);

        return;
    }

    if (key == Vis::ControlParameter::SHOW_CARBONS) {
        uiMainWindow.viewShowCarbonsAction->blockSignals(true);
        uiMainWindow.viewShowCarbonsAction->setChecked(Vis::getShowCarbonsParameter(*settings));
        uiMainWindow.viewShowCarbonsAction->blockSignals(false);

        return;
    }
 
    if (key == Vis::ControlParameter::SHOW_CHARGES) {
        uiMainWindow.viewShowChargesAction->blockSignals(true);
        uiMainWindow.viewShowChargesAction->setChecked(Vis::getShowChargesParameter(*settings));
        uiMainWindow.viewShowChargesAction->blockSignals(false);

        return;
    }
 
    if (key == Vis::ControlParameter::SHOW_ISOTOPES) {
        uiMainWindow.viewShowIsotopesAction->blockSignals(true);
        uiMainWindow.viewShowIsotopesAction->setChecked(Vis::getShowIsotopesParameter(*settings));
        uiMainWindow.viewShowIsotopesAction->blockSignals(false);

        return;
    }    
 
    if (key == Vis::ControlParameter::SHOW_EXPLICIT_HYDROGENS) {
        uiMainWindow.viewShowExplicitHsAction->blockSignals(true);
        uiMainWindow.viewShowExplicitHsAction->setChecked(Vis::getShowExplicitHydrogensParameter(*settings));
        uiMainWindow.viewShowExplicitHsAction->blockSignals(false);

        return;
    }

    if (key == Vis::ControlParameter::SHOW_HYDROGEN_COUNTS) {
        uiMainWindow.viewShowHCountsAction->blockSignals(true);
        uiMainWindow.viewShowHCountsAction->setChecked(Vis::getShowHydrogenCountsParameter(*settings));
        uiMainWindow.viewShowHCountsAction->blockSignals(false);

        uiMainWindow.viewShowNonCHCountsAction->setEnabled(!uiMainWindow.viewShowHCountsAction->isChecked());

        return;
    }
 
    if (key == Vis::ControlParameter::SHOW_NON_CARBON_HYDROGEN_COUNTS) {
        uiMainWindow.viewShowNonCHCountsAction->blockSignals(true);
        uiMainWindow.viewShowNonCHCountsAction->setChecked(Vis::getShowNonCarbonHydrogenCountsParameter(*settings));
        uiMainWindow.viewShowNonCHCountsAction->blockSignals(false);

        return;
    } 
    
    if (key == Vis::ControlParameter::SHOW_ATOM_QUERY_INFOS) {
        uiMainWindow.viewShowAtomQueryInfosAction->blockSignals(true);
        uiMainWindow.viewShowAtomQueryInfosAction->setChecked(Vis::getShowAtomQueryInfosParameter(*settings));
        uiMainWindow.viewShowAtomQueryInfosAction->blockSignals(false);

        return;
    } 
    
    if (key == Vis::ControlParameter::SHOW_ATOM_REACTION_INFOS) {
        uiMainWindow.viewShowAtomReactionInfosAction->blockSignals(true);
        uiMainWindow.viewShowAtomReactionInfosAction->setChecked(Vis::getShowAtomReactionInfosParameter(*settings));
        uiMainWindow.viewShowAtomReactionInfosAction->blockSignals(false);

        return;
    }
 
    if (key == Vis::ControlParameter::SHOW_RADICAL_ELECTRONS) {
        uiMainWindow.viewShowRadicalElectronsAction->blockSignals(true);
        uiMainWindow.viewShowRadicalElectronsAction->setChecked(Vis::getShowRadicalElectronsParameter(*settings));
        uiMainWindow.viewShowRadicalElectronsAction->blockSignals(false);

        return;
    }
    
    if (key == Vis::ControlParameter::SHOW_ATOM_CONFIGURATION_LABELS) {
        uiMainWindow.viewShowAtomConfigLabelsAction->blockSignals(true);
        uiMainWindow.viewShowAtomConfigLabelsAction->setChecked(Vis::getShowAtomConfigurationLabelsParameter(*settings));
        uiMainWindow.viewShowAtomConfigLabelsAction->blockSignals(false);

        return;
    }
 
    if (key == Vis::ControlParameter::SHOW_BOND_REACTION_INFOS) {
        uiMainWindow.viewShowBondReactionInfosAction->blockSignals(true);
        uiMainWindow.viewShowBondReactionInfosAction->setChecked(Vis::getShowBondReactionInfosParameter(*settings));
        uiMainWindow.viewShowBondReactionInfosAction->blockSignals(false);

        return;
    }
 
    if (key == Vis::ControlParameter::SHOW_BOND_QUERY_INFOS) {
        uiMainWindow.viewShowBondQueryInfosAction->blockSignals(true);
        uiMainWindow.viewShowBondQueryInfosAction->setChecked(Vis::getShowBondQueryInfosParameter(*settings));
        uiMainWindow.viewShowBondQueryInfosAction->blockSignals(false);

        return;
    }
 
    if (key == Vis::ControlParameter::SHOW_STEREO_BONDS) {
        uiMainWindow.viewShowBondStereoAction->blockSignals(true);
        uiMainWindow.viewShowBondStereoAction->setChecked(Vis::getShowStereoBondsParameter(*settings));
        uiMainWindow.viewShowBondStereoAction->blockSignals(false);

        return;
    }

    if (key == Vis::ControlParameter::SHOW_BOND_CONFIGURATION_LABELS) {
        uiMainWindow.viewShowBondConfigLabelsAction->blockSignals(true);
        uiMainWindow.viewShowBondConfigLabelsAction->setChecked(Vis::getShowBondConfigurationLabelsParameter(*settings));
        uiMainWindow.viewShowBondConfigLabelsAction->blockSignals(false);
    }
}

void ChOX::MainWindow::viewSubstructHighlightingChanged()
{
    setSubstructHighlightingEnabledParameter(*settings, uiMainWindow.viewEnableSubstructHighlightingAction->isChecked());
}

void ChOX::MainWindow::viewPropertyTableVisibilityChanged()
{
    setShowPropertyTableParameter(*settings, uiMainWindow.viewShowPropertyTableAction->isChecked());
}

void ChOX::MainWindow::viewAlignmentChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int alignment = Alignment::NONE;

    if (uiMainWindow.viewLeftAlignmentAction->isChecked()) 
        alignment = Alignment::LEFT;
    else if (uiMainWindow.viewRightAlignmentAction->isChecked()) 
        alignment = Alignment::RIGHT;
    else
        alignment = Alignment::H_CENTER;

    if (uiMainWindow.viewTopAlignmentAction->isChecked()) 
        alignment |= Alignment::TOP;
    else if (uiMainWindow.viewBottomAlignmentAction->isChecked()) 
        alignment |= Alignment::BOTTOM;
    else
        alignment |= Alignment::V_CENTER;

    setAlignmentParameter(*settings, alignment);
}

void ChOX::MainWindow::viewSizeAdjustmentChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int adjust;

    if (uiMainWindow.viewBestFitSizeAdjustmentAction->isChecked()) 
        adjust = SizeAdjustment::BEST_FIT;
    else if (uiMainWindow.viewNoSizeAdjustmentAction->isChecked()) 
        adjust = SizeAdjustment::NONE;
    else
        adjust = SizeAdjustment::IF_REQUIRED;

    setSizeAdjustmentParameter(*settings, adjust);
}

void ChOX::MainWindow::reactionArrowStyleChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int style;

    if (uiMainWindow.viewNoReactionArrowAction->isChecked()) 
        style = ArrowStyle::NONE;
    else if (uiMainWindow.viewHollowReactionArrowAction->isChecked()) 
        style = ArrowStyle::REACTION_HOLLOW;
    else
        style = ArrowStyle::REACTION_SOLID;

    setReactionArrowStyleParameter(*settings, style);
}

void ChOX::MainWindow::reactionAgentAlignmentChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int alignment;

    if (uiMainWindow.viewTopAgentAlignmentAction->isChecked()) 
        alignment = Alignment::TOP;
    else if (uiMainWindow.viewBottomAgentAlignmentAction->isChecked()) 
        alignment = Alignment::BOTTOM;
    else
        alignment = Alignment::V_CENTER;

    setReactionAgentAlignmentParameter(*settings, alignment);
}

void ChOX::MainWindow::reactionAgentLayoutStyleChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int layout;

    if (uiMainWindow.viewLinearAgentLayoutStyleAction->isChecked()) 
        layout = LayoutStyle::LINEAR;
    else 
        layout = LayoutStyle::PACKED;

    setReactionAgentLayoutParameter(*settings, layout);
}

void ChOX::MainWindow::reactionAgentLayoutDirChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int dir;

    if (uiMainWindow.viewHorAgentLayoutDirAction->isChecked()) 
        dir = LayoutDirection::HORIZONTAL;
    else 
        dir = LayoutDirection::VERTICAL;

    setReactionAgentLayoutDirectionParameter(*settings, dir);
}

void ChOX::MainWindow::reactionCompLayoutStyleChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int layout;

    if (uiMainWindow.viewLinearComponentLayoutStyleAction->isChecked()) 
        layout = LayoutStyle::LINEAR;
    else 
        layout = LayoutStyle::PACKED;

    setReactionComponentLayoutParameter(*settings, layout);
}

void ChOX::MainWindow::reactionCompLayoutDirChanged()
{
    using namespace CDPL;
    using namespace Vis;

    unsigned int dir;

    if (uiMainWindow.viewHorComponentLayoutDirAction->isChecked()) 
        dir = LayoutDirection::HORIZONTAL;
    else
        dir = LayoutDirection::VERTICAL;

    setReactionComponentLayoutDirectionParameter(*settings, dir);
}

void ChOX::MainWindow::viewReactionSettingsChanged(bool checked)
{
    using namespace CDPL;
    using namespace Vis;

    const QObject* source = sender();

    if (source == uiMainWindow.viewShowReactantsAction)
        setShowReactionReactantsParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowProductsAction)
        setShowReactionProductsParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowAgentsAction)
        setShowReactionAgentsParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowReactionPlusSignsAction) 
        setShowReactionPlusSignsParameter(*settings, checked);
}

void ChOX::MainWindow::viewBondSettingsChanged(bool checked)
{
    using namespace CDPL;
    using namespace Vis;

    const QObject* source = sender();

    if (source == uiMainWindow.viewShowBondQueryInfosAction) 
        setShowBondQueryInfosParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowBondReactionInfosAction) 
        setShowBondReactionInfosParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowBondStereoAction) 
        setShowStereoBondsParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowBondConfigLabelsAction) 
        setShowBondConfigurationLabelsParameter(*settings, checked);
}

void ChOX::MainWindow::viewAtomSettingsChanged(bool checked)
{
    using namespace CDPL;
    using namespace Vis;

    const QObject* source = sender();

    if (source == uiMainWindow.viewShowCarbonsAction)
        setShowCarbonsParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowChargesAction)
        setShowChargesParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowIsotopesAction)
        setShowIsotopesParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowExplicitHsAction)
        setShowExplicitHydrogensParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowHCountsAction) 
        setShowHydrogenCountsParameter(*settings, checked);
        
    else if (source == uiMainWindow.viewShowNonCHCountsAction)
        setShowNonCarbonHydrogenCountsParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowAtomQueryInfosAction)
        setShowAtomQueryInfosParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowAtomReactionInfosAction)
        setShowAtomReactionInfosParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowRadicalElectronsAction)
        setShowRadicalElectronsParameter(*settings, checked);

    else if (source == uiMainWindow.viewShowAtomConfigLabelsAction)
        setShowAtomConfigurationLabelsParameter(*settings, checked);
}

void ChOX::MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
    if (ClipboardData::canHandle(e->mimeData()))
        e->acceptProposedAction();
}

void ChOX::MainWindow::dropEvent(QDropEvent* e)
{
    ClipboardData::extract(this, e->mimeData(), *dataSet, dataSetView->getPageView().getPageOffset());
    
    e->acceptProposedAction();
}
