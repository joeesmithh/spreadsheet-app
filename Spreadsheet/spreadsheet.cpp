#include "stdafx.h"
#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget* parent)
	: QTableWidget(parent), hasUnsavedChanges(false), mainFile(tr(""))
{
	setupUi(this);
	reset();

	// Cell change = modification
	connect(this, &QTableWidget::cellChanged, this, &Spreadsheet::onCellChanged);
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

	setFile("");
}

void Spreadsheet::setFile(const QString& filePath)
{
	mainFile = filePath;
	emit fileChanged(getStrippedFileName(mainFile));
}

void Spreadsheet::setUnsavedChanges(const bool& state)
{
	hasUnsavedChanges = state;
	emit unsavedChanges(state);
}

QString Spreadsheet::getStrippedFileName(const QString& fileName) const
{
	QFileInfo fileInfo(fileName);
	return fileInfo.baseName();
}

void Spreadsheet::onOpenTriggered()
{
	// Get file name
	QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), tr("."), tr("Mysheet (*.ms)"));

	if (!filePath.isNull())
	{
		// Open file
		QFile file(filePath);

		if (file.open(QIODevice::ReadOnly))
		{
			// Open file stream
			QDataStream fileStream(&file);

			// TODO: Validate file type

			clearContents();

			int row;
			int column;
			QString text;

			while (!fileStream.atEnd())
			{
				fileStream >> row;
				fileStream >> column;
				fileStream >> text;

				QTableWidgetItem* item = new QTableWidgetItem(text);
				setItem(row, column, item);
			}

			setFile(filePath);
			setUnsavedChanges(false);
			emit spreadsheetMessage(tr("Opened %1").arg(getStrippedFileName(filePath)));
		}

	}
}

void Spreadsheet::onSaveTriggered()
{
	if (mainFile.isEmpty())
	{
		// Select file for writing
		onSaveAsTriggered();
	}
	else
	{
		QFile file(mainFile);

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

			setUnsavedChanges(false);
			emit spreadsheetMessage(tr("Saved %1").arg(getStrippedFileName(mainFile)));
		}
	}
}

void Spreadsheet::onSaveAsTriggered()
{
	QString filePath =
		QFileDialog::getSaveFileName(this, tr("Save File"), tr("."), tr("Mysheet (*.ms)"));

	if (!filePath.isNull())
	{
		setFile(filePath);
		onSaveTriggered();
	}
}

void Spreadsheet::onCellChanged()
{
	setUnsavedChanges(true);
}


