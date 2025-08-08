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
    
    Spreadsheet* spreadsheet;

    void initializeSpreadsheet(Spreadsheet* spreadsheet);

    /** Create the actions with which to populate the 'File' menu.
        @returns A vector list of the menu actions. */
    std::vector<QAction*> createFileMenuActions();

    /** Create, populate, and add a menu to the main menu bar.
        @param name The name of the menu.
        @param actions The actions with which to populate the menu. */
    QMenu* createMenu(const QString& name, const std::vector<QAction*>& actions);

private slots:
    void exitProgram();

     
};

