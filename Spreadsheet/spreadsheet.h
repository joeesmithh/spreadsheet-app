#pragma once

#include <QWidget>
#include "ui_spreadsheet.h"

class Spreadsheet : public QTableWidget, public Ui::SpreadsheetClass
{
	Q_OBJECT

public:
	Spreadsheet(QWidget *parent = nullptr);
	~Spreadsheet();

private:
	 
};

