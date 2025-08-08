#include "stdafx.h"
#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent)
	: QTableWidget(parent)
{
	setupUi(this);
}

Spreadsheet::~Spreadsheet()
{}

