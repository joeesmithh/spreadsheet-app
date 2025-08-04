#pragma once

#include <QtWidgets/QDialog>
#include "ui_gotocelldialog.h"

class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
    Q_OBJECT

public:
    GoToCellDialog(QWidget *parent = nullptr);
    ~GoToCellDialog();

private:

public slots:
    void on_lineEdit_textChanged(const QString& text);
};

