#include "stdafx.h"
#include "finddialog.h"
#include <iostream>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
}

FindDialog::~FindDialog()
{}

void FindDialog::on_findButton_clicked()
{
    std::cout << lineEdit->text().toStdString() << std::endl;
}

void FindDialog::on_lineEdit_textChanged(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}

void FindDialog::on_closeButton_clicked() {
    accept();
}