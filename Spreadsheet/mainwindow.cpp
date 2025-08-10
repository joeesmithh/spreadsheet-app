#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    // Menus
    createActions();
    createMenus();

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
    connect(openAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::open);

    // Save
    saveAction = new QAction("&Save", this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save file"));
    connect(saveAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::save);

    // Save As
    saveAsAction = new QAction("Sa&ve as", this);
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("Save file as"));
    connect(saveAsAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::saveAs);
    connect(getSpreadsheet(), &Spreadsheet::updateStatus, getStatusBar(), &QStatusBar::showMessage);
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



