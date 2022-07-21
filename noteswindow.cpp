#include "noteswindow.h"
#include "ui_noteswindow.h"
#include "mainwindow.h"
NotesWindow::NotesWindow(QWidget *parent) :
    ui(new Ui::NotesWindow)
{
    parentWindow = parent;
    qWarning() <<"Konstruktor NOTATEK";
    qWarning() <<MainWindow::notesText;
    ui->setupUi(this);
    ui->notes->setPlainText(MainWindow::notesText);
}

NotesWindow::~NotesWindow()
{
    qWarning() <<"destruktor notatek";
    delete ui;
}

void NotesWindow::on_notes_textChanged()
{
    MainWindow::notesText = ui->notes->toPlainText();
    if(parentWindow->windowTitle().toStdString()[parentWindow->windowTitle().toStdString().size() - 1] != '*')
        parentWindow->setWindowTitle(parentWindow->windowTitle() + "*");
}

void NotesWindow::closeEvent(QCloseEvent *event)
{
    MainWindow::notesText = ui->notes->toPlainText();
    qWarning() << "wychodze z notatek";
}
