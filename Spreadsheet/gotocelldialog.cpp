#include "stdafx.h"
#include "gotocelldialog.h"
#include <QDebug>

GoToCellDialog::GoToCellDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    this->setFixedSize(this->size()); // disable window resizing

    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false); // OK button disabled by default

    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}"); // Declare regular expression such that input can only be a cell location
    lineEdit->setValidator(new QRegularExpressionValidator(regExp, this)); // Register regular expression as valid input

    connect(buttonBox, &QDialogButtonBox::accepted, this, &GoToCellDialog::accept); // Close dialog, dialog result = QDialog::Accepted = 1
    connect(buttonBox, &QDialogButtonBox::rejected, this, &GoToCellDialog::reject); // Close dialog, dialog result = QDialog::Rejected = 0
    
}

GoToCellDialog::~GoToCellDialog()
{}

void GoToCellDialog::on_lineEdit_textChanged(const QString& text) {
    buttonBox->button(QDialogButtonBox::Ok)->setEnabled(lineEdit->hasAcceptableInput()); // Enable OK button if valid input
}

