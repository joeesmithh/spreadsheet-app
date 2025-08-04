#include "stdafx.h"
#include "mainwindow.h"
#include "sortdialog.h"
#include "finddialog.h"
#include "gotocelldialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
