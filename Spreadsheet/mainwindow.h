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

    // Menus
    QMenu* fileMenu;

    Spreadsheet* spreadsheet;

    // Initialize actions
    void createActions();

    // Initialize menus
    void createMenus();

private slots:
    void exitProgram();

     
};

