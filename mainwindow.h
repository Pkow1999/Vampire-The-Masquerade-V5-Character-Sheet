#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QList>
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

private:
    Ui::MainWindow *ui;
    int countDots(QButtonGroup *grp);
};
#endif // MAINWINDOW_H
