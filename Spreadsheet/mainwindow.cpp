#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	setupUi(this);

	// Initialize window elements
	getSpreadsheet();
	getMenuBar();
	getStatusBar();

	// Menus
	createActions();
	createMenus();
}

MainWindow::~MainWindow()
{}

void MainWindow::closeEvent(QCloseEvent* event)
{
	// Prompt save before closing
	if (getSpreadsheet()->getUnsavedChanges())
	{
		int result = QMessageBox::warning(this,
										  tr("Before you exit!"),
										  tr("You have unsaved changes!\n"
											 "Would you like to save before exiting?"),
										  QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
										  QMessageBox::Save);

		switch (result)
		{
			case QMessageBox::Save:							// Save changes
				if (!getSpreadsheet()->onSaveTriggered())
					event->ignore();
				break;
			case QMessageBox::Cancel:						// Close dialog
				event->ignore();
				break;
			case QMessageBox::Discard:						// Discard changes
				break;
		}
	}
}

void MainWindow::createActions()
{
	// New File
	newFileAction = new QAction(QIcon(tr(":/images/new.png")), tr("&New File"), this);
	newFileAction->setShortcut(QKeySequence::New);
	newFileAction->setStatusTip(tr("Create a new file"));
	connect(newFileAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::onNewFileTriggered);

	// Open
	openAction = new QAction(QIcon(tr(":/images/open.png")), tr("&Open"), this);
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open existing file"));
	connect(openAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::onOpenTriggered);

	// Save
	saveAction = new QAction(QIcon(tr(":/images/save.png")), tr("&Save"), this);
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save file"));
	connect(saveAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::onSaveTriggered);

	// Save As
	saveAsAction = new QAction(tr("Sa&ve as"), this);
	saveAsAction->setShortcut(QKeySequence::SaveAs);
	saveAsAction->setStatusTip(tr("Save file as"));
	connect(saveAsAction, &QAction::triggered, getSpreadsheet(), &Spreadsheet::onSaveAsTriggered);

	// Exit
	exitAction = new QAction(QIcon(tr(":/images/exit.png")), tr("E&xit"), this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit program"));
	exitAction->setToolTip(tr("Exit program"));
	connect(exitAction, &QAction::triggered, this, &MainWindow::onExitTriggered);
}

void MainWindow::createMenus()
{
	fileMenu = getMenuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newFileAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	fileMenu->addAction(exitAction);
}

Spreadsheet* MainWindow::getSpreadsheet()
{
	if (spreadsheet == nullptr)
	{
		spreadsheet = new Spreadsheet(this);

		connect(spreadsheet, &Spreadsheet::fileChanged, this, &MainWindow::onFileChanged);
		connect(spreadsheet, &Spreadsheet::spreadsheetMessage, this, &MainWindow::onSpreadsheetMessage);
		connect(spreadsheet, &Spreadsheet::unsavedChanges, this, &QWidget::setWindowModified);

		setCentralWidget(spreadsheet);

		spreadsheet->reset();
	}

	return spreadsheet;
}

QMenuBar* MainWindow::getMenuBar()
{
	if (menuBar == nullptr)
	{
		menuBar = QMainWindow::menuBar();
	}

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


void MainWindow::onExitTriggered()
{
	close();
}

void MainWindow::onFileChanged(const QString& fileName)
{
	QString displayFileName = fileName.isEmpty() ? tr("New File") : fileName;
	setWindowTitle(tr("Spreadsheet - %1 [*]").arg(displayFileName));
}

void MainWindow::onSpreadsheetMessage(const QString& thing)
{
	getStatusBar()->showMessage(thing, MESSAGE_TIMEOUT);
}



