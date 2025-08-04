#include "stdafx.h"
#include "sortdialog.h"
#include <QDebug>

SortDialog::SortDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	// Additional sorts desabled by default
	secondaryGroupBox->setVisible(false);
	tertiaryGroupBox->setVisible(false);

	// Auto resize based on additional sort presence
	layout()->setSizeConstraint(QLayout::SetFixedSize);

	// Invoke column population
	setColumnCombo('A', 'Z');
}

SortDialog::~SortDialog()
{}

void SortDialog::on_moreButton_toggled(const bool& isToggled) {
	moreButton->setText(isToggled ? "More <<<" : "More >>>");
}

void SortDialog::setColumnCombo(QChar first, QChar last)
{
	// Clear all combo options
	primaryColumnCombo->clear();
	secondaryColumnCombo->clear();
	tertiaryColumnCombo->clear();

	// Ensure primary combo box same size as additional combos with "None" option
	secondaryColumnCombo->addItem("None");
	tertiaryColumnCombo->addItem("None");
	primaryColumnCombo->setFixedSize(secondaryColumnCombo->sizeHint());

	// Populate combo boxes
	QChar curChar = first;
	while (curChar <= last) {
		primaryColumnCombo->addItem(QString(curChar));
		secondaryColumnCombo->addItem(QString(curChar));
		tertiaryColumnCombo->addItem(QString(curChar));

		curChar = QChar::fromUcs2(curChar.unicode() + 1);
	}
}

