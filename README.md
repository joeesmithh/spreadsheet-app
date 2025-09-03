## Spreadsheet App
This is a simple spreadsheet app created and heavily guided by [C++ GUI Programming with Qt 4 By Jasmin Blanchette, Mark Summerfield](https://books.google.com.jm/books?id=tSCR_4LH2KsC&printsec=frontcover#v=onepage&q&f=false) to learn Qt Widget app development.

<br>
<div align="center">
    <img width="75%" src="https://i.imgur.com/UQcI1s1.png"/>
</div>
<br>

## Features
<table>
    <tr align="left">
        <th width="1%">Feature</th>
        <th width="20%">Hotkey</th>
        <th>Description</th>
    </tr>
    <tr>
        <td><strong>Save</strong></td>
        <td><code>Ctrl + S</code></td>
        <td>Save existing spreadsheet to custom .ms file.
            <br>
            Opens <strong>Save As</strong> dialog if no file exists.
        </td>
    </tr>
    <tr>
        <td><strong>Save As</strong></td>
        <td><code>Ctrl + Shift + S</code></td>
        <td>Save spreadsheet to custom .ms file via popup file menu.</td>
    </tr>
    <tr>
        <td><strong>Load</strong></td>
        <td><code>Ctrl + O</code></td>
        <td>Open a spreadsheet from .ms file via popup file menu.</td>
    </tr>
    <tr>
        <td><strong>New File</strong></td>
        <td><code>Ctrl + N</code></td>
        <td>Create a blank spreadsheet file.</td>
    </tr>
    <tr>
        <td><strong>Modification Detection</strong></td>
        <td></td>
        <td>If a spreadsheet contains unsaved changes, a warning dialog appears before closing the program, creating, or opening a new spreadsheet.</td>
    </tr>
    <tr>
        <td><strong>Settings</strong></td>
        <td></td>
        <td>
            Save and load various program settings to system registry under <code>joeesmithh/Spreadsheet</code>.
            <br>
            <br>
            <table>
                <tr><th>Settings</th></tr>
                <tr><td>Window Size</td></tr>
                <tr><td>Fullscreen State</td></tr>
            </table>
        </td>
    </tr>
</table>