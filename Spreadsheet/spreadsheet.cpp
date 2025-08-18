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
	setUnsavedChanges(false);
}

void Spreadsheet::setFile(const QString& filePath)
{
	mainFile = filePath;
	emit fileChanged(getStrippedFileName(filePath));
}

bool Spreadsheet::getUnsavedChanges() const
{
	return hasUnsavedChanges;
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

bool Spreadsheet::canContinue()
{
	// Safe to continue if no unsaved changes
	if (!hasUnsavedChanges)
	{
		return true;
	}

	// Message box prompt
	int result = QMessageBox::warning(this,
									  tr("Save your work!"),
									  tr("You have unsaved changes.\n"
										 "Would you like to save before proceeding?"),
									  QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
									  QMessageBox::Save);

	switch (result)
	{
		case QMessageBox::Save:			// Save changes
			return onSaveTriggered();
		case QMessageBox::Cancel:		// Cancel dialog
			return false;
		case QMessageBox::Discard:		// Discard changes
			return true;
	}
}

bool Spreadsheet::onNewFileTriggered()
{
	if (canContinue())
	{
		reset();
		return true;
	}

	return false;
}

bool Spreadsheet::onOpenTriggered()
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

			// Usaved changes dialog
			if (canContinue())
			{
				// Clear cell data
				clearContents();

				// Read data from file
				int row, column;
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
				return true;
			}
		}
	}

	return false;
}

bool Spreadsheet::onSaveTriggered()
{
	if (mainFile.isEmpty())
	{
		// Select file for writing
		return onSaveAsTriggered();
	}
	else
	{
		QFile file(mainFile);

		// Open file for writing
		if (file.open(QIODeviceBase::WriteOnly))
		{
			// Write data
			QDataStream fileStream(&file);
			for (int row = 0; row < MinRowCount; row++)
			{
				for (int col = 0; col < MinColumnCount; col++)
				{
					// Write item to file
					QTableWidgetItem* curItem = item(row, col);
					if (curItem != nullptr)
					{
						fileStream << row << col << (item(row, col)->text());
					}
				}
			}

			setUnsavedChanges(false);
			emit spreadsheetMessage(tr("Saved %1").arg(getStrippedFileName(mainFile)));
			return true;
		}

		return false;
	}
}

bool Spreadsheet::onSaveAsTriggered()
{
	QString filePath =
		QFileDialog::getSaveFileName(this, tr("Save File"), tr("."), tr("Mysheet (*.ms)"));

	if (!filePath.isNull())
	{
		setFile(filePath);
		return onSaveTriggered();
	}

	return false;
}

void Spreadsheet::onCellChanged()
{
	setUnsavedChanges(true);
}


