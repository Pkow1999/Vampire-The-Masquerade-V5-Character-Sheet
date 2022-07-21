#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QLayout>
#include <QMainWindow>
#include <QShortcut>
#include "noteswindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    static QString notesText;
    ~MainWindow();
private slots:
    void calculateHealth();
    void calculateWP();
    void calculateBlood();
    void dynamicRemoveDots(QAbstractButton *bt);
    void on_pushButton_clicked();
    void slotLanguageChanged(QAction *action);

    void on_pushButton_2_clicked();

    bool on_actionSave_triggered();
    void on_actionLoad_triggered();
    void dynamicDiscpilineCreator(QAbstractButton *bt);
    void humanityChanged();
    void saveWithShortcut();
    void on_actionShow_triggered();

private:
    NotesWindow *newWindow = nullptr;
    int counter = 0;
    int hunger = 0;
    int healthPool = 0;
    int willpowerPool = 0;
    QString lastDirectory;
    Ui::MainWindow *ui;
    int countDots(QButtonGroup *grp);
    QPair<int, int> countIndicators(QLayout *layout,int size_);
    QLayout* findParentLayout(QWidget *widget, QLayout *parent);
    QLayout* findParentLayout(QWidget *widget);
    void clear();
    void createDices(int size_);
    void deleteDices(int size_);
    QJsonObject saveSkills();
    QJsonObject saveAttributes();
    QJsonObject saveRest();
    QJsonObject saveDiscipline();
    void Save(QString directory);
    bool loadRest(QJsonObject json);
    bool loadAttributes(QJsonObject json);
    bool loadSkills(QJsonObject json);
    bool loadDiscipline(QJsonObject json);
    void deleteWP(int size_);
    void deleteHealth(int size_);
    void deleteDiscipline();
    void humanityGenerator();
    void closeEvent(QCloseEvent *event);
};
#endif // MAINWINDOW_H
