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

    /** Interrupt QWidget close requests.
        @param The event requesting the close. */
    void closeEvent(QCloseEvent* event);

    void resizeEvent(QResizeEvent* event);

private:
    
    const int MESSAGE_TIMEOUT = 2000;
    const QString ORGANIZATION_NAME = tr("joeesmithh");
    const QString PROGRAM_NAME = tr("Spreadsheet");

    QSize unmaximizedSize;

    // Actions
    QAction* exitAction;
    QAction* newFileAction;
    QAction* openAction;
    QAction* saveAction;
    QAction* saveAsAction;

    // UI Elements
    Spreadsheet* spreadsheet;
    QMenuBar* menuBar;
    QStatusBar* statusBar;
    QMenu* fileMenu;

    /** Initializes window menu actions. */
    void createActions();

    /** Initializes window menus */
    void createMenus();

    /** Save settings to registry. */
    void saveSettings();

    /** Load settings from registry. */
    void loadSettings();

    /** Get spreadsheet member, initializing if needed.
        @return Pointer to central spreadsheet widget member. */
    Spreadsheet* getSpreadsheet();

    /** Get main window menu bar member, initializing if needed.
        @return Pointer to main window menu bar member. */
    QMenuBar* getMenuBar();

    /** Get main window status bar member, initializing if needed. 
        @return Pointer to main window status bar member. */
    QStatusBar* getStatusBar();

public slots:
    /** Handle exit action. */
    void onExitTriggered();

    /** Handle spreadsheet file change. */
    void onFileChanged(const QString& fileName);

    /** Handle spreadsheet message. */
    void onSpreadsheetMessage(const QString& thing);
};

