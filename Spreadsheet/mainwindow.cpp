#include "stdafx.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    //setWindowIcon(QIcon(":/images/table.png"));
}

MainWindow::~MainWindow()
{}

