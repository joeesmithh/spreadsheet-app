#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    // Menus
    createActions();
    createMenus();

    // Spreadsheet
    spreadsheet = new Spreadsheet(this);
    setCentralWidget(spreadsheet);

}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    exitProgramAction = new QAction("E&xit", this);
    exitProgramAction->setShortcut(tr("Ctrl+Q"));
    exitProgramAction->setIcon(QIcon(":/images/exit.png"));
    exitProgramAction->setStatusTip(tr("Exit program"));
    exitProgramAction->setToolTip(tr("Exit program"));
    connect(exitProgramAction, &QAction::triggered, this, &MainWindow::exitProgram);
}

void MainWindow::createMenus()
{
    fileMenu = QMainWindow::menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitProgramAction);
}


void MainWindow::exitProgram()
{
    close();
}


