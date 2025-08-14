#include "stdafx.h"
#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget* parent)
	: QTableWidget(parent)
{
	setupUi(this);
	reset();
}

Spreadsheet::~Spreadsheet()
{}

void Spreadsheet::reset()
{
	// Remove headers
	setRowCount(0);
	setColumnCount(0);

	// Create headers
	setRowCount(MinRowCount);
	setColumnCount(MinColumnCount);

	// Create header labels
	for (int i = 0; i < MinColumnCount; i++)
	{
		QTableWidgetItem* header = new QTableWidgetItem(QChar('A' + i));
		setHorizontalHeaderItem(i, header);
	}

	fileName = "";

	emit fileChanged(getStrippedFileName(fileName));
}

QString Spreadsheet::getStrippedFileName(const QString& fileName) const
{
	QFileInfo fileInfo(fileName);
	return fileInfo.baseName();
}

void Spreadsheet::handleOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), tr("."), tr("Mysheet (*.ms)"));

	if (!fileName.isNull())
	{
		clearContents();

		Spreadsheet::fileName = fileName;

		QFile file(fileName);

		if (file.open(QIODevice::ReadOnly))
		{
			QDataStream fileStream(&file);

			while (!fileStream.atEnd())
			{
				int row;
				int column;
				QString text;

				fileStream >> row;
				fileStream >> column;
				fileStream >> text;

				QTableWidgetItem* item = new QTableWidgetItem(text);
				setItem(row, column, item);
			}
		}
		
		emit fileChanged(getStrippedFileName(fileName));
		emit updateStatus(tr("Opened %1").arg(getStrippedFileName(fileName)), 2000);
	}
}	

void Spreadsheet::handleSave()
{
	if (fileName.isEmpty())
	{
		// Select file for writing
		handleSaveAs();
	}
	else
	{
		QFile file(fileName);

		// Open file for writing
		if (file.open(QIODeviceBase::WriteOnly))
		{
			QDataStream fileStream(&file);
			
			for (int row = 0; row < MinRowCount; row++)
			{
				for (int col = 0; col < MinColumnCount; col++)
				{
					// Write item
					QTableWidgetItem* curItem = item(row, col);
					if (curItem != nullptr)
					{
						fileStream << row << col << (item(row, col)->text());
					}
				}
			}

			emit fileChanged(getStrippedFileName(fileName));
			emit updateStatus(tr("Saved %1").arg(getStrippedFileName(fileName)), 2000);
		}
	}
}

void Spreadsheet::handleSaveAs()
{
	fileName =
		QFileDialog::getSaveFileName(this, tr("Save File"), tr("."), tr("Mysheet (*.ms)"));

	handleSave();
}


