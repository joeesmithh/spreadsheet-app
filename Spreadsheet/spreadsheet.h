#pragma once

#include <QWidget>
#include "ui_spreadsheet.h"

class Spreadsheet : public QTableWidget, public Ui::SpreadsheetClass
{
	Q_OBJECT

private:

	enum
	{
		MinRowCount = 999, MinColumnCount = 26
	};
	
	// State
	bool hasUnsavedChanges;
	QString mainFile;

	/** Reset the spreadsheet and all its data. */
	void reset();

	/** Change the main spreadsheet file.
	@param fileName Name of new file. */
	void setFile(const QString& fileName);

	/** Set hasUnsavedChanges member and emit unsavedChanges signal.
		@param state New modified state.  */
	void setUnsavedChanges(const bool& state);

	/** Extract base file name from file path.
		@param filePath The file's full path.
		@return The base file name. */
	QString getStrippedFileName(const QString& filePath) const;

	/** Determines whether the program can continue in light of unsaved changes.
		@return True if the program can safely continue, false otherwise. */
	bool canContinue();

public:
	Spreadsheet(QWidget* parent = nullptr);
	~Spreadsheet();

	/** Does the spreadsheet file have any unsaved changes?
		@return True if there are unsaved changes, false otherwise. */
	bool getUnsavedChanges() const;

signals:
	/** Indicate something has occurred within the spreadsheet.
		@param message Message to send. */
	void spreadsheetMessage(const QString& message);

	/** Indicate spreadsheet file has changed.
		@param filePath Path of new file. */
	void fileChanged(const QString& filePath);

	/** Indicate spreadsheet unsaved changes.
		@param isChanged Are there any unsaved changes? */
	void unsavedChanges(const bool& isChanged);

public slots:
	/** Handle Open action.
		@return True if successfully opened, false otherwise. */
	bool onOpenTriggered();

	/** Handle Save action.
		@return True if successfully saved, false otherwise. */
	bool onSaveTriggered();

	/** Handle Save As action.
		@return True if successfully saved as chosen file, false otherwise. */
	bool onSaveAsTriggered();

	/** Handle cell alteration. */
	void onCellChanged();
};

