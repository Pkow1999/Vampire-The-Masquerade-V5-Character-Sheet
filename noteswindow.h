#ifndef NOTESWINDOW_H
#define NOTESWINDOW_H

#include <QFrame>

namespace Ui {
class NotesWindow;
}

class NotesWindow : public QFrame
{
    Q_OBJECT

public:
    explicit NotesWindow(QWidget *parent = nullptr);
    ~NotesWindow();    
    QString getNotes();
private slots:
    void on_notes_textChanged();

private:
    Ui::NotesWindow *ui;
    QWidget *parentWindow;
    void closeEvent(QCloseEvent *event);
};

#endif // NOTESWINDOW_H
