#pragma once

#include <QDialog>
#include "ui_sortdialog.h"

class SortDialog : public QDialog, public Ui::SortDialog
{
	Q_OBJECT

public:
	SortDialog(QWidget *parent = nullptr);
	~SortDialog();

	/** Populate dialog combo boxes.
		@param first The character from which to begin population
		@param last The character at which to end population */
	void setColumnCombo(QChar first, QChar last);

private:

private slots:
	void on_moreButton_toggled(const bool& isToggled);
	 
};

