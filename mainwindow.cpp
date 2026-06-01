#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QFontDialog>
#include <QRegularExpression>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::onTextChanged);
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged, this, &MainWindow::onTextChanged);
    ui->actionBold->setCheckable(true);
    ui->actionItalic->setCheckable(true);
    ui->actionUnderline->setCheckable(true);

    shortcutCopy = new QShortcut(QKeySequence("Ctrl+C"), this);
    connect(shortcutCopy, &QShortcut::activated, this, &MainWindow::on_actionCopy_triggered);

    shortcutPaste = new QShortcut(QKeySequence("Ctrl+V"), this);
    connect(shortcutPaste, &QShortcut::activated, this, &MainWindow::on_actionPaste_triggered);

    shortcutCut = new QShortcut(QKeySequence("Ctrl+X"), this);
    connect(shortcutCut, &QShortcut::activated, this, &MainWindow::on_actionCut_triggered);

    shortcutUndo = new QShortcut(QKeySequence("Ctrl+Z"), this);
    connect(shortcutUndo, &QShortcut::activated, this, &MainWindow::on_actionUndo_triggered);

    shortcutSave = new QShortcut(QKeySequence("Ctrl+S"), this);
    connect(shortcutSave, &QShortcut::activated, this, &MainWindow::on_actionSave_triggered);

    shortcutOpen = new QShortcut(QKeySequence("Ctrl+O"), this);
    connect(shortcutOpen, &QShortcut::activated, this, &MainWindow::on_actionOpen_triggered);

    shortcutNew = new QShortcut(QKeySequence("Ctrl+N"), this);
    connect(shortcutNew, &QShortcut::activated, this, &MainWindow::on_actionOpen_triggered);
}

MainWindow::~MainWindow()
{
    delete shortcutCopy;
    delete shortcutPaste;
    delete shortcutCut;
    delete shortcutUndo;
    delete shortcutSave;
    delete shortcutOpen;
    delete shortcutNew;
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    if(!askToSave())
        return;
    currentFile.clear();
    ui->textEdit->setText(QString());
    setWindowTitle("New file");
}

void MainWindow::on_actionOpen_triggered()
{
    if(!askToSave())
        return;
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file", "", "Text (*.txt);;"
                                                                               "Code (*.cpp, *.h, *.py, "
                                                                               "*.js, *.cs, *.sh, *.bash);;"
                                                                               "HTML (*.html);;All files (*.*)");
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    setWindowTitle(fileName);
    isModified = false;
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName;
    if(currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save", "", "Text (*.txt);;"
                                                                  "Code (*.cpp, *.h, *.py, "
                                                                  "*.js, *.cs, *.sh, *.bash);;"
                                                                  "HTML (*.html);;All files (*.*)");
        if(fileName.isEmpty())
            return;
        currentFile = fileName;
    }
    else
        fileName = currentFile;

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    isModified = false;
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as", "", "Text (*.txt);;"
                                                                         "Code (*.cpp, *.h, *.py, "
                                                                         "*.js, *.cs, *.sh, *.bash);;"
                                                                         "HTML (*.html);;All files (*.*)");
    if(fileName.isEmpty())
        return;

    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    isModified = false;
    file.close();
}

void MainWindow::on_actionExit_triggered()
{
    if(!askToSave())
        return;
    QApplication::quit();
}

void MainWindow::onTextChanged()
{
    QString title = currentFile.isEmpty() ? "New file" : currentFile;
    setWindowTitle(title + "*");
    isModified = true;

    // licznik słów i znaków
    QString text = ui->textEdit->toPlainText();
    int words = text.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts).count();
    int chars = text.length();
    statusBar()->showMessage(QString("Words: %1  |  Characters: %2").arg(words).arg(chars));

    // podświetlanie bieżącej linii
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(QColor(isDarkMode == true ? "#2d2d2d" : "#fffacd"));
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = ui->textEdit->textCursor();
    selection.cursor.clearSelection();
    ui->textEdit->setExtraSelections({selection});
}

bool MainWindow::askToSave()
{
    if(isModified)
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Unsaved work", "Do you want to save file?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(reply == QMessageBox::Yes)
        {
            on_actionSave_triggered();
            return true;
        }
        else if(reply == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::on_actionFont_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if(fontSelected)
        ui->textEdit->setFont(font);
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionBold_toggled(bool checked)
{
    QTextCharFormat fmt;
    fmt.setFontWeight(checked ? QFont::Bold : QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionItalic_toggled(bool checked)
{
    QTextCharFormat fmt;
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionUnderline_toggled(bool checked)
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionDarkMode_triggered()
{
    isDarkMode = !isDarkMode;
    if(isDarkMode)
    {
        ui->textEdit->setStyleSheet("QTextEdit {background-color: #1e1e1e; color: #d4d4d4;}");
        ui->actionDarkMode->setIcon(QIcon(":/images/sun.png"));

        // set selection to dark
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(QColor("#2d2d2d"));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = ui->textEdit->textCursor();
        selection.cursor.clearSelection();
        ui->textEdit->setExtraSelections({selection});
    }
    else
    {
        ui->textEdit->setStyleSheet("");
        ui->actionDarkMode->setIcon(QIcon(":/images/moon.png"));

        // set selection to light
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(QColor("#fffacd"));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = ui->textEdit->textCursor();
        selection.cursor.clearSelection();
        ui->textEdit->setExtraSelections({selection});
    }
}

