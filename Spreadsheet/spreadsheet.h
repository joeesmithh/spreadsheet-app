#pragma once

#include <QWidget>
#include "ui_spreadsheet.h"

class Spreadsheet : public QTableWidget, public Ui::SpreadsheetClass
{
	Q_OBJECT

private:

	QString fileName;

	enum
	{
		MinRowCount = 999, MinColumnCount = 26
	};

	/** Reset the spreadsheet. */
	void reset();
	QString getStrippedFileName(const QString& fileName) const;

public:
	Spreadsheet(QWidget* parent = nullptr);
	~Spreadsheet();

signals:
	void updateStatus(const QString& file, const int& timeout);
	void fileChanged(const QString& fileName);

public slots:

	void handleOpen();
	void handleSave();
	void handleSaveAs();
};

