#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QShortcut>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();
    void on_actionExit_triggered();
    void onTextChanged();
    bool askToSave(); // return False if cancel was selected, otherwise true
    void on_actionFont_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();
    void on_actionBold_toggled(bool arg1);

    void on_actionItalic_toggled(bool arg1);

    void on_actionUnderline_toggled(bool arg1);

    void on_actionDarkMode_triggered();

private:
    Ui::MainWindow *ui;
    QString currentFile;
    bool isModified = false;
    bool isDarkMode = false;

    QShortcut *shortcutCopy;
    QShortcut *shortcutPaste;
    QShortcut *shortcutCut;
    QShortcut *shortcutUndo;
    QShortcut *shortcutSave;
    QShortcut *shortcutOpen;
    QShortcut *shortcutNew;
};
#endif // MAINWINDOW_H
