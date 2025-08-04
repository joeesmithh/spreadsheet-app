#pragma once

#include <QtWidgets/QDialog>
#include "ui_finddialog.h"

class FindDialog : public QDialog, public Ui::FindDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

private:

private slots:
    void on_closeButton_clicked();
    void on_findButton_clicked();
    void on_lineEdit_textChanged(const QString &text);
     
};

