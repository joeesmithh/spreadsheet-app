#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "spreadsheet.h"
#include <vector>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    
    // Actions
    QAction* exitProgramAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;

    // UI Elements
    QMenuBar* menuBar;
    QStatusBar* statusBar;
    Spreadsheet* spreadsheet;
    QMenu* fileMenu;

    // Initialize actions
    void createActions();

    // Initialize menus
    void createMenus();

    Spreadsheet* getSpreadsheet();
    QMenuBar* getMenuBar();
    QStatusBar* getStatusBar();

private slots:
    void exitProgram();
    

     
};

