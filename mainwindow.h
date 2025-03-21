#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAbstractButton>
#include <QLayout>
#include <QMainWindow>
#include <QShortcut>
#include <QTranslator>
#include <qnetworkaccessmanager.h>
#include "clanwindow.h"
#include "noteswindow.h"
#include "disciplinewindow.h"

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
    void bolding(QAbstractButton *bt, bool state);
    void calculateHealth();
    void calculateWP();
    void calculateBlood();
    void dynamicRemoveDots(QAbstractButton *bt);
    void slotLanguageChanged(QAction *action);

    void on_rollDices_button_clicked();
    void on_reRollDices_button_clicked();

    bool on_actionSave_triggered();
    void on_actionLoad_triggered();
    void on_useGraphics_stateChanged(int state);

    void dynamicDisciplineCreator(QAbstractButton *bt);
    void humanityChanged();
    void saveWithShortcut();
    void on_actionShow_triggered();

    void on_actionShowBook_triggered();

    void on_actionShowDisciplines_triggered();

    void on_actionGenerate_new_Random_Character_triggered();

    void on_actionEnable_Discord_Webhook_toggled(bool isChecked);
    void replyFinished(QNetworkReply *reply);
    void on_frenzyRoll_button_clicked();

private:

    QTranslator *translator;
    NotesWindow *notesWindow = nullptr;
    ClanWindow *clanWindow = nullptr;
    QVector <DisciplineWindow *> disciplineWindowStack;
    QNetworkAccessManager *manager;
    int diceAmount = 0;
    int hunger = 0;
    int healthPool = 0;
    int willpowerPool = 0;
    QStringList normalDices;
    QStringList hungerDices;
    QStringList poolName;
    QString lastDirectory;
    Ui::MainWindow *ui;
    bool discordIntegration = false;
    bool graphicRepresentation = false;
    QString discordWebhookURL = "";
    QString userName = "";
    QMap<QString, QString> emotesIds;
    void connectAllButtons();
    int countDots(QButtonGroup *grp);
    QPair<int, int> countIndicators(QLayout *layout,int size_);
    QLayout* findParentLayout(QWidget *widget, QLayout *parent);
    QLayout* findParentLayout(QWidget *widget);
    void clear();
    void createDices(bool reRollable, bool includeHunger);
    void deleteDices();
    QJsonObject saveSkills();
    QJsonObject saveAttributes();
    QJsonObject saveRest();
    QJsonObject saveDiscipline();
    void Save(QString directory);
    bool androidSave(QString directory);

    bool loadRest(QJsonObject json);
    bool loadAttributes(QJsonObject json);
    bool loadSkills(QJsonObject json);
    bool loadDiscipline(QJsonObject json);

    bool androidLoad(QJsonObject json);
    QJsonObject saveSkillsAndroid(QButtonGroup *group);
    QJsonObject saveRestAndroid();
    QJsonObject saveDisciplinesAndroid();

    void deleteWP(int size_);
    void deleteHealth(int size_);
    void deleteDiscipline();
    void humanityGenerator();
    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void closeNotes();
    void postDataToDiscord();
    int calculatePool();
    QString getUserName();
    void createSettingsFile(QString filepath);
    int loadSettings(QString filepath);
};
#endif // MAINWINDOW_H
