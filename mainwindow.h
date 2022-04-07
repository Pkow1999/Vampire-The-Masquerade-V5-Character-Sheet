#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QMainWindow>

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
    void func(QAbstractButton *bt);
    void on_pushButton_clicked();
    void slotLanguageChanged(QAction *action);

    void on_pushButton_2_clicked();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

private:
    int counter = 0;
    int hunger = 0;
    Ui::MainWindow *ui;
    int countDots(QButtonGroup *grp);
};
#endif // MAINWINDOW_H
