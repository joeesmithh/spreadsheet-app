#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    
    // Initialize spreadsheet
    spreadsheet = new Spreadsheet(this);
    setCentralWidget(spreadsheet);

    // Initialize menus
    QMenu* fileMenu = createMenu(tr("&File"), createFileMenuActions());
}

MainWindow::~MainWindow()
{
}

std::vector<QAction*> MainWindow::createFileMenuActions()
{
    std::vector<QAction*> actions;

    // Exit program action
    QAction* exitProgramAction = new QAction(tr("E&xit"));
    exitProgramAction->setShortcut(tr("Ctrl+Q"));
    exitProgramAction->setIcon(QIcon(":/images/exit.png"));
    exitProgramAction->setStatusTip(tr("Exit program"));
    exitProgramAction->setToolTip(tr("Exit program"));
    connect(exitProgramAction, &QAction::triggered, this, &MainWindow::exitProgram);
    actions.push_back(exitProgramAction);

    return actions;
}

QMenu* MainWindow::createMenu(const QString& name, const std::vector<QAction*>& actions)
{
    // Initialize menu to main menu bar
    QMenu* menu = QMainWindow::menuBar()->addMenu(name);
    menu->setToolTipsVisible(true);

    // Populate menu with actions in the order they were added to the list
    for (auto i = end(actions); i > begin(actions); i--) {
        menu->addAction(*(i - 1));
    }

    return menu;
}


void MainWindow::exitProgram()
{
    close();
}


