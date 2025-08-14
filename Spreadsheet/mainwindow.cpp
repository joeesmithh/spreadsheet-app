#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    // Initialize Window Elements
    getSpreadsheet();
    getMenuBar();
    getStatusBar();

    // Menus
    createActions();
    createMenus();

    // Window
    handleFileChanged("New File");
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    // Exit
    exitProgramAction = new QAction(QIcon(":/images/exit.png"), "E&xit", this);
    exitProgramAction->setShortcut(tr("Ctrl+Q"));
    exitProgramAction->setStatusTip(tr("Exit program"));
    exitProgramAction->setToolTip(tr("Exit program"));
    connect(exitProgramAction, &QAction::triggered, this, &MainWindow::exitProgram);

    // Open
    openAction = new QAction(tr("&Open"), this);
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip("Open existing file");
    connect(openAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::handleOpen);

    // Save
    saveAction = new QAction("&Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::handleSave);

    // Save As
    saveAsAction = new QAction("Sa&ve as", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save file as"));
    connect(saveAsAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::handleSaveAs);
}

void MainWindow::createMenus()
{
    fileMenu = getMenuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitProgramAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
}

Spreadsheet* MainWindow::getSpreadsheet()
{
    if (spreadsheet == nullptr)
    {
        spreadsheet = new Spreadsheet(this);

        connect(spreadsheet, &Spreadsheet::fileChanged, this, &MainWindow::handleFileChanged);
        connect(spreadsheet, &Spreadsheet::updateStatus, getStatusBar(), &QStatusBar::showMessage);

        setCentralWidget(spreadsheet);
    }

    return spreadsheet;
}

QMenuBar* MainWindow::getMenuBar()
{
    if (menuBar == nullptr) {menuBar = QMainWindow::menuBar();}

    return menuBar;
}

QStatusBar* MainWindow::getStatusBar()
{
    if (statusBar == nullptr)
    {
        statusBar = QMainWindow::statusBar();
    }

    return statusBar;
}


void MainWindow::exitProgram()
{
    close();
}

void MainWindow::handleFileChanged(const QString& fileName)
{
    setWindowTitle(tr("%1[*] - Spreadsheet").arg(fileName));
}



