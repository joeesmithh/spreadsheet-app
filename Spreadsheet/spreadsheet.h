#pragma once

#include <QWidget>
#include "ui_spreadsheet.h"

class Spreadsheet : public QTableWidget, public Ui::SpreadsheetClass
{
	Q_OBJECT

public:
	Spreadsheet(QWidget* parent = nullptr);
	~Spreadsheet();

private:

	QString currentFile;

	enum
	{
		MinRowCount = 999, MinColumnCount = 26
	};

	void reset();

signals:
	void updateStatus(const QString& file, const int& timeout);

public slots:

	/** Reset the spreadsheet. */
	void handleOpen();
	void handleSave();
	void handleSaveAs();
};

