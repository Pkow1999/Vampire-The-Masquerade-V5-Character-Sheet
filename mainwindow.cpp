#include "clanwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mainwindow.h>
#include <QAbstractButton>
#include <QDir>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLayout>
#include <QRandomGenerator>
#include <QTranslator>
#include <QMessageBox>
#include <QCloseEvent>
#include <QScrollArea>
#include <QNetworkAccessManager>
#include <QHttpPart>
#include <QNetworkReply>


QString MainWindow::notesText;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    translator = new QTranslator();
    ui->setupUi(this);

    connectAllButtons();

    humanityGenerator();

    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this, SLOT(saveWithShortcut()));

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, &MainWindow::replyFinished);
}
MainWindow::~MainWindow()
{
    clear();
    ui->HumanityLayout->deleteLater();
    qWarning() <<"destruktor glowny";
    QApplication::quit();
    delete translator;
    delete ui;
}

void MainWindow::bolding(QAbstractButton *bt, bool state)
{

    if(bt->group()->objectName() != "buttonGroup_3")
    {
        QFont font = bt->font();
        font.setBold(state);
        bt->setFont(font);
    }
    else
    {
        QFont font = findParentLayout(bt)->itemAt(1)->widget()->font();
        font.setBold(state);
        findParentLayout(bt)->itemAt(1)->widget()->setFont(font);
    }
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if (event->size().width() == event->oldSize().width()) {
            return;
        }
}
void MainWindow::slotLanguageChanged(QAction *action)
{
    if(action->objectName() == "actionPolish")
    {
        const QString baseName = "VtM_sheet_pl_PL";
        if (translator->load(":/i18n/" + baseName)) {
            QCoreApplication::removeTranslator(translator);
            QCoreApplication::installTranslator(translator);
            setLocale(QLocale::Polish);
        }
    }
    else if(action->objectName() == "actionEnglish")
    {
        const QString baseName = "VtM_sheet_en_US";
        if (translator->load(":/i18n/" + baseName)) {
            QCoreApplication::removeTranslator(translator);
            QCoreApplication::installTranslator(translator);
            setLocale(QLocale::English);
        }
    }
    ui->retranslateUi(this);
    calculateBlood();
    humanityChanged();
}

void MainWindow::deleteHealth(int size_)
{
    for(int i = 0; i < size_; i++)
    {
        ui->Health->itemAt(ui->Health->count() - 1)->widget()->deleteLater();
        ui->Health->removeWidget(ui->Health->itemAt(ui->Health->count() - 1)->widget());
    }

}

void MainWindow::deleteDiscipline()
{
    for(QAbstractButton *bt : ui->buttonGroup_3->buttons())
    {
        QLineEdit *line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        line->clear();
    }


    ui->Discipline1Group->buttons().first()->click();
    if(ui->Discipline1Group->buttons().first()->isChecked()) ui->Discipline1Group->buttons().first()->click();

    ui->Discipline2Group->buttons().first()->click();
    if(ui->Discipline2Group->buttons().first()->isChecked()) ui->Discipline2Group->buttons().first()->click();

    ui->Discipline3Group->buttons().first()->click();
    if(ui->Discipline3Group->buttons().first()->isChecked()) ui->Discipline3Group->buttons().first()->click();

    ui->Discipline4Group->buttons().first()->click();
    if(ui->Discipline4Group->buttons().first()->isChecked()) ui->Discipline4Group->buttons().first()->click();

}

void MainWindow::humanityGenerator()
{
    for(int i = 0; i < 10; i++)
    {
        QCheckBox *dynCheck = new QCheckBox();
        dynCheck->setCheckable(true);
        dynCheck->setTristate(true);
        QString checkBoxStyle("QCheckBox::indicator::unchecked {background-image : url(images/checkbox_unchecked.png); }"
                              "QCheckBox::indicator::unchecked::hover {background-image : url(images/checkbox_unchecked_hover.png); }"
                              "QCheckBox::indicator::unchecked::pressed {background-image : url(images/checkbox_unchecked_pressed.png); }"

                              "QCheckBox::indicator::indeterminate {background-image : url(images/checkbox_indeterminate.png); }"
                              "QCheckBox::indicator::indeterminate::hover {background-image : url(images/checkbox_indeterminate_hover.png); }"
                              "QCheckBox::indicator::indeterminate::pressed {background-image : url(images/checkbox_indeterminate_pressed.png); }"

                              "QCheckBox::indicator::checked {background-image : url(images/checkbox_humanity_checked.png); }"
                              "QCheckBox::indicator::checked::hover {background-image : url(images/checkbox_humanity_checked_hover.png); }"
                              "QCheckBox::indicator::checked::pressed {background-image : url(images/checkbox_humanity_checked_pressed.png); }"

                              "QCheckBox::indicator {width: 16; height: 16 }");
        dynCheck->setStyleSheet(checkBoxStyle);
        dynCheck->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        dynCheck->setAutoExclusive(false);
        ui->HumanityLayout->addWidget(dynCheck);
        connect(dynCheck,&QCheckBox::stateChanged,this,&MainWindow::humanityChanged);
    }
    humanityChanged();
}
void MainWindow::deleteWP(int size_)
{
    for(int i = 0; i < size_; i++)
    {
        ui->Willpower->itemAt(ui->Willpower->count() - 1)->widget()->deleteLater();
        ui->Willpower->removeWidget(ui->Willpower->itemAt(ui->Willpower->count() - 1)->widget());
    }
}

void MainWindow::calculateWP()
{
    deleteWP(willpowerPool);
    willpowerPool = countDots(ui->Com) + countDots(ui->Res) + ui->wpModifier->value();
    if(willpowerPool < 0)
        willpowerPool = 0;
    for(int i = 0; i < willpowerPool; i++)
    {
        QCheckBox *dynCheck = new QCheckBox();
        dynCheck->setCheckable(true);
        dynCheck->setTristate(true);
        QString checkBoxStyle("QCheckBox::indicator::unchecked {background-image : url(images/checkbox_unchecked.png); }"
                              "QCheckBox::indicator::unchecked::hover {background-image : url(images/checkbox_unchecked_hover.png); }"
                              "QCheckBox::indicator::unchecked::pressed {background-image : url(images/checkbox_unchecked_pressed.png); }"

                              "QCheckBox::indicator::indeterminate {background-image : url(images/checkbox_indeterminate.png); }"
                              "QCheckBox::indicator::indeterminate::hover {background-image : url(images/checkbox_indeterminate_hover.png); }"
                              "QCheckBox::indicator::indeterminate::pressed {background-image : url(images/checkbox_indeterminate_pressed.png); }"

                              "QCheckBox::indicator::checked {background-image : url(images/checkbox_checked.png); }"
                              "QCheckBox::indicator::checked::hover {background-image : url(images/checkbox_checked_hover.png); }"
                              "QCheckBox::indicator::checked::pressed {background-image : url(images/checkbox_checked_pressed.png); }"

                              "QCheckBox::indicator {width: 16; height: 16 }");
        dynCheck->setStyleSheet(checkBoxStyle);
        dynCheck->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        dynCheck->setAutoExclusive(false);
        ui->Willpower->addWidget(dynCheck);
    }
}

void MainWindow::calculateBlood()
{
    int bloodPotency = countDots(ui->BloodPotencyGroup);
    ui->BloodPotency->setText(QString::number(bloodPotency /2 + bloodPotency % 2 + 1));
    ui->MendAmount->setText(QString::number(bloodPotency < 6 ? bloodPotency / 2 + 1 : bloodPotency / 2));
    ui->PowerBonus->setText(QString::number(bloodPotency / 2));
    ui->RouseReRoll->setText(tr("Level ") + QString::number(bloodPotency > 0 ? bloodPotency /2 + bloodPotency % 2 : 0));
    ui->BaneSevarity->setText(QString::number(bloodPotency > 0 ? bloodPotency /2 + bloodPotency % 2 + 1 : 0 ));



    if(bloodPotency > 0)
        ui->BloodPotency->setText(ui->BloodPotency->text() + tr(" dices"));
    else
        ui->BloodPotency->setText(ui->BloodPotency->text() + tr(" die"));

    if(bloodPotency > 3)
        ui->PowerBonus->setText(ui->PowerBonus->text() + tr(" dices"));
    else
        ui->PowerBonus->setText(ui->PowerBonus->text() + tr(" die"));

    if(bloodPotency > 1)
        ui->MendAmount->setText(ui->MendAmount->text() + tr(" superficial damage"));
    else
        ui->MendAmount->setText(ui->MendAmount->text() + tr(" superficial damage"));

    if(bloodPotency > 2)
        ui->RouseReRoll->setText(ui->RouseReRoll->text() + tr(" and Lower"));
}

void MainWindow::calculateHealth()
{
    deleteHealth(healthPool);
    healthPool = 3 + countDots(ui->Sta) + ui->healthModifier->value();
    if(healthPool < 0)
        healthPool = 0;
    for(int i = 0; i < healthPool; i++)
    {
        QCheckBox *dynCheck = new QCheckBox();
        dynCheck->setCheckable(true);
        dynCheck->setTristate(true);
        QString checkBoxStyle("QCheckBox::indicator::unchecked {background-image : url(images/checkbox_unchecked.png); }"
                              "QCheckBox::indicator::unchecked::hover {background-image : url(images/checkbox_unchecked_hover.png); }"
                              "QCheckBox::indicator::unchecked::pressed {background-image : url(images/checkbox_unchecked_pressed.png); }"

                              "QCheckBox::indicator::indeterminate {background-image : url(images/checkbox_indeterminate.png); }"
                              "QCheckBox::indicator::indeterminate::hover {background-image : url(images/checkbox_indeterminate_hover.png); }"
                              "QCheckBox::indicator::indeterminate::pressed {background-image : url(images/checkbox_indeterminate_pressed.png); }"

                              "QCheckBox::indicator::checked {background-image : url(images/checkbox_checked.png); }"
                              "QCheckBox::indicator::checked::hover {background-image : url(images/checkbox_checked_hover.png); }"
                              "QCheckBox::indicator::checked::pressed {background-image : url(images/checkbox_checked_pressed.png); }"

                              "QCheckBox::indicator {width: 16; height: 16 }");
        dynCheck->setStyleSheet(checkBoxStyle);
        dynCheck->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
        dynCheck->setAutoExclusive(false);
        ui->Health->addWidget(dynCheck);
    }
}

void MainWindow::dynamicRemoveDots(QAbstractButton *bt)
{
    if(bt->isChecked())
    {
        for(int i = 0; i < bt->group()->buttons().size(); i++)
        {
            if(bt->group()->buttons().at(i)->objectName() == bt->objectName())
                break;
            bt->group()->buttons().at(i)->setChecked(true);
        }
    }
    else
    {
        int del = 0;
        for(int i = 0; i < bt->group()->buttons().size(); i++)
        {
            if(bt->group()->buttons().at(i)->objectName() == bt->objectName())
            {
                del = i;
                break;
            }
        }
        for(int i = del; i < bt->group()->buttons().size(); i++)
        {
            bt->group()->buttons().at(i)->setChecked(false);
        }
    }
    if(MainWindow::windowTitle().toStdString()[MainWindow::windowTitle().toStdString().size() - 1] != '*')
        MainWindow::setWindowTitle(MainWindow::windowTitle() + "*");
}
int MainWindow::countDots(QButtonGroup *grp)
{
    int counter = 0;
    for(int i = 0; i < grp->buttons().size(); i++)
    {
        if(grp->buttons().at(i)->isChecked())
        {
            counter++;
        }
        else
        {
            break;
        }
    }
    return counter;
}

QPair<int, int> MainWindow::countIndicators(QLayout *layout,int size_)
{
    int superficial = 0;
    int agravated = 0;
    for(int i = 0; i < size_; i++)
    {
        QCheckBox *check = qobject_cast<QCheckBox *>(layout->itemAt(i)->widget());
        if(check->checkState() == Qt::CheckState::Checked)
            agravated++;
        if(check->checkState() == Qt::CheckState::PartiallyChecked)
            superficial++;
    }
    return QPair<int,int>(superficial, agravated);
}

QLayout* MainWindow::findParentLayout(QWidget* w, QLayout* topLevelLayout)
{
    for (QObject* qo: topLevelLayout->children())
    {
        QLayout* layout = qobject_cast<QLayout*>(qo);
        if (layout != nullptr)
        {
            if (layout->indexOf(w) > -1)
                return layout;
            else if (!layout->children().isEmpty())
            {
                layout = findParentLayout(w, layout);
                if (layout != nullptr)
                    return layout;
            }
        }
    }
    return nullptr;
}

QLayout* MainWindow::findParentLayout(QWidget* w)
{
    if (w->parentWidget() != nullptr)
        if (w->parentWidget()->layout() != nullptr)
            return findParentLayout(w, w->parentWidget()->layout());
    return nullptr;
}

//funkcja dealokujaca i czyszczaca wszystkie dane
void MainWindow::clear()
{
    for(QAbstractButton *bt : ui->buttonGroup->buttons())//atrybuty
    {
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(0)->widget());//magiczny syf do wyciagniecia przycisku z atrybutami
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
    for(QAbstractButton *bt : ui->MentalSkillsGroup->buttons())//skille
    {
        QLineEdit *line = qobject_cast<QLineEdit *> (findParentLayout(bt)->itemAt(1)->widget());
        line->clear();
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
    for(QAbstractButton *bt : ui->SocialSkillsGroup->buttons())//skille
    {
        QLineEdit *line = qobject_cast<QLineEdit *> (findParentLayout(bt)->itemAt(1)->widget());
        line->clear();
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
    for(QAbstractButton *bt : ui->PhysicalSkillsGroup->buttons())//skille
    {
        QLineEdit *line = qobject_cast<QLineEdit *> (findParentLayout(bt)->itemAt(1)->widget());
        line->clear();
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
    for(QAbstractButton *bt : ui->buttonGroup_3->buttons())//dyscypliny
    {
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
    for(QAbstractButton *bt : ui->BloodPotencyGroup->buttons())//bloodpotency
    {
        bt->setChecked(false);
    }

    deleteHealth(healthPool);
    deleteWP(willpowerPool);
    deleteDiscipline();
    deleteDices();
    healthPool = 0;
    willpowerPool = 0;
    diceAmount = 0;
    hunger = 0;
}

//create dices from the dice amount
void MainWindow::createDices(bool reRollable, bool includeHunger)
{
    normalDices.clear();
    hungerDices.clear();
    ui->label_2->setText(QString::number(diceAmount) + tr(" Dices"));
    for(int i = 0; i < diceAmount; i++)
    {
        QCheckBox *dynCheck = new QCheckBox();
        QVBoxLayout *dynLayout = new QVBoxLayout();
        int generatedNumber = QRandomGenerator::system()->bounded(10) + 1;
        QLabel *dynLabel = new QLabel();
        dynLabel->setAlignment(Qt::AlignCenter);
        if (ui->useGraphics->isChecked())
        {
            QPixmap pixmap;
            if(generatedNumber > 5 && generatedNumber < 10)
            {
                pixmap = QPixmap("images/normal-success.png");

            }
            else if(generatedNumber == 10)
            {
                pixmap = QPixmap("images/normal-crit.png");
            }
            else
            {
                pixmap = QPixmap("images/normal-fail.png");
            }
            pixmap = pixmap.scaled(pixmap.width()/2, pixmap.height()/2);
            dynLabel->setPixmap(pixmap);
            dynLabel->setMask(pixmap.mask());
        }
        else
        {
            dynLabel->setText(QString::number(generatedNumber));
            dynLabel->setStyleSheet("QLabel { font-size : 20px;}");
        }
        dynCheck->setObjectName("czek" + QString::number(i));
        dynCheck->setCheckable(reRollable);
        dynCheck->setEnabled(reRollable);
        if(i > diceAmount - hunger - 1 && includeHunger)
        {
            if (ui->useGraphics->isChecked())
            {
                QPixmap pixmap;
                if(generatedNumber > 5 && generatedNumber < 10)
                {
                    pixmap = QPixmap("images/red-success.png");

                }
                else if(generatedNumber == 10)
                {
                    pixmap = QPixmap("images/red-crit.png");
                }
                else if(generatedNumber == 1)
                {
                    pixmap = QPixmap("images/bestial-fail.png");
                }
                else
                {
                    pixmap = QPixmap("images/red-fail.png");
                }
                pixmap = pixmap.scaled(pixmap.width()/2, pixmap.height()/2);
                dynLabel->setPixmap(pixmap);
                dynLabel->setMask(pixmap.mask());
            }
            dynLabel->setStyleSheet("QLabel { color : red; font-size : 20px;}");
            hungerDices.append(QString::number(generatedNumber));
        }
        else{
            normalDices.append(QString::number(generatedNumber));
        }
        dynLayout->addWidget(dynLabel);
        dynLayout->addWidget(dynCheck);
        dynLayout->setAlignment(dynCheck, Qt::AlignCenter);
        dynLayout->setAlignment(dynLabel, Qt::AlignCenter);
        ui->Rolls->addLayout(dynLayout);
    }
}

void MainWindow::deleteDices()
{
    for(int i = 0; i < diceAmount; i++)
    {

        for(int j = 0; j < 2; j++)
        {
            ui->Rolls->itemAt(i)->layout()->itemAt(j)->widget()->deleteLater();
        }
        ui->Rolls->itemAt(i)->layout()->deleteLater();
    }
}

void MainWindow::on_rollDices_button_clicked()//roll dices
{
    //delete last amount of dices and prepare for the new one
    deleteDices();

    hunger = countDots(ui->Hunger);

    diceAmount = calculatePool();
    diceAmount += ui->diceModifier->value();
    if(ui->diceModifier->value()) {
        if(!poolName.empty())
            poolName.append(tr("Modifier %1").arg(QString::number(ui->diceModifier->value())));
        else
            poolName.append(tr("%1 Dices").arg(QString::number(ui->diceModifier->value())));
    }
    createDices(true, true);


    if(discordIntegration){
        postDataToDiscord();
    }
}

int MainWindow::calculatePool()
{
    int pool = 0;
    poolName.clear();
    //Atrybuty
    for(int i = 0; i < ui->buttonGroup->buttons().size(); i++)
    {
        if(ui->buttonGroup->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest drugi element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup->buttons().at(i)->focusWidget())->layout()->itemAt(1)->layout()->itemAt(0)->widget());
            pool += countDots(bt->group());
            poolName.append(ui->buttonGroup->buttons().at(i)->text());
        }
    }
    //Prawe skille
    for(int i = 0; i < ui->MentalSkillsGroup->buttons().size(); i++)
    {
        if(ui->MentalSkillsGroup->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest trzeci(!) element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->MentalSkillsGroup->buttons().at(i)->focusWidget())->layout()->itemAt(2)->layout()->itemAt(0)->widget());
            pool += countDots(bt->group());
            poolName.append(ui->MentalSkillsGroup->buttons().at(i)->text());

        }
    }
    //Srodkowe skille
    for(int i = 0; i < ui->SocialSkillsGroup->buttons().size(); i++)
    {
        if(ui->SocialSkillsGroup->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest trzeci(!) element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->SocialSkillsGroup->buttons().at(i)->focusWidget())->layout()->itemAt(2)->layout()->itemAt(0)->widget());
            pool += countDots(bt->group());
            poolName.append(ui->SocialSkillsGroup->buttons().at(i)->text());

        }
    }
    //Lewe skille
    for(int i = 0; i < ui->PhysicalSkillsGroup->buttons().size(); i++)
    {
        if(ui->PhysicalSkillsGroup->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest trzeci(!) element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->PhysicalSkillsGroup->buttons().at(i)->focusWidget())->layout()->itemAt(2)->layout()->itemAt(0)->widget());
            pool += countDots(bt->group());
            poolName.append(ui->PhysicalSkillsGroup->buttons().at(i)->text());

        }
    }
    //dyscypliny
    for(int i = 0; i < ui->buttonGroup_3->buttons().size(); i++)
    {
        if(ui->buttonGroup_3->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest trzeci(!) element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup_3->buttons().at(i)->focusWidget())->layout()->itemAt(2)->layout()->itemAt(0)->widget());
            pool += countDots(bt->group());

            QLineEdit *disciplineNameLine =qobject_cast<QLineEdit *>(findParentLayout(ui->buttonGroup_3->buttons().at(i)->focusWidget())->layout()->itemAt(1)->widget());
            poolName.append(disciplineNameLine->text());

        }
    }
    return pool;
}

void MainWindow::on_reRollDices_button_clicked()//re roll / reroll dices
{
    poolName.clear();
    poolName.append(tr("Reroll"));
    for(int i = 0; i < diceAmount; i++)
    {
        QAbstractButton *bt = qobject_cast<QAbstractButton *>(ui->Rolls->itemAt(i)->layout()->itemAt(1)->widget());
        if(bt->isChecked())
        {
            int generatedNumber = QRandomGenerator::system()->bounded(10) + 1;
            if(ui->useGraphics->isChecked())
            {
                QLabel *lb = qobject_cast<QLabel *>(ui->Rolls->itemAt(i)->layout()->itemAt(0)->widget());
                QPixmap pixmap;
                if(generatedNumber > 5 && generatedNumber < 10)
                {
                    pixmap = QPixmap("images/normal-success.png");

                }
                else if(generatedNumber == 10)
                {
                    pixmap = QPixmap("images/normal-crit.png");
                }
                else if(generatedNumber == 1 && lb->styleSheet() == "QLabel { color : red; font-size : 20px;}")
                {
                    pixmap = QPixmap("images/bestial-fail.png");
                }
                else
                {
                    pixmap = QPixmap("images/normal-fail.png");
                }
                auto mask = pixmap.createMaskFromColor(QColor(0,0,0,0), Qt::MaskInColor);
                QColor colour;

                if(lb->styleSheet() == "QLabel { color : red; font-size : 20px;}"){
                    colour = QColor(100,0,255);
                }
                else colour = QColor(0,0,255);


                pixmap.fill(colour);
                pixmap.setMask(mask);
                pixmap = pixmap.scaled(pixmap.width()/2, pixmap.height()/2);
                lb->setPixmap(pixmap);
                lb->setMask(pixmap.mask());
            }
            else
            {
                QLabel *lb = qobject_cast<QLabel *>(ui->Rolls->itemAt(i)->layout()->itemAt(0)->widget());
                lb->setText(QString::number(generatedNumber));
                if(lb->styleSheet() == "QLabel { color : red; font-size : 20px;}"){
                    lb->setStyleSheet("QLabel { color : purple; font-size: 20px;}");
                }
                else lb->setStyleSheet(" QLabel{color : blue; font-size : 20px;}");
            }

            if(normalDices.size() > i)
            {
                qDebug() << i << normalDices;
                normalDices.replace(i, QString::number(generatedNumber));
            }
            else
            {
                qDebug() << i << i - normalDices.size() << normalDices;
                hungerDices.replace(i - normalDices.size(), QString::number(generatedNumber));
            }
        }
    }


    if(discordIntegration){
        postDataToDiscord();
    }
}

QJsonObject MainWindow::saveSkills()
{
    QJsonObject json;
    for(QAbstractButton *bt : ui->MentalSkillsGroup->buttons())
    {
        QJsonObject skill;
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        int dots = countDots(but->group());
        skill["specialization"] = line->text();
        skill["dots"] = QString::number(dots);
        QJsonArray *array = new QJsonArray();
        array->append(skill);
        json[bt->text()] = *array;
        delete array;
    }
    for(QAbstractButton *bt : ui->SocialSkillsGroup->buttons())
    {
        QJsonObject skill;
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        int dots = countDots(but->group());
        skill["specialization"] = line->text();
        skill["dots"] = QString::number(dots);
        QJsonArray *array = new QJsonArray();
        array->append(skill);
        json[bt->text()] = *array;
        delete array;
    }
    for(QAbstractButton *bt : ui->PhysicalSkillsGroup->buttons())
    {
        QJsonObject skill;
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        int dots = countDots(but->group());
        skill["specialization"] = line->text();
        skill["dots"] = QString::number(dots);
        QJsonArray *array = new QJsonArray();
        array->append(skill);
        json[bt->text()] = *array;
        delete array;
    }
    return json;
}

QJsonObject MainWindow::saveAttributes()
{
    QJsonObject json;
    for(QAbstractButton *bt : ui->buttonGroup->buttons())
    {
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(0)->widget());//magiczny syf do wyciagniecia przycisku z atrybutami
        int dots = countDots(but->group());
        json[bt->text()] = QString::number(dots);
    }
    return json;
}
QJsonObject MainWindow::saveDiscipline()
{
    QJsonObject json;
    for(QAbstractButton *bt : ui->buttonGroup_3->buttons())
    {
        QJsonArray *array = new QJsonArray();
        QJsonArray *discp = new QJsonArray();
        QAbstractButton * butDots = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        int dots = countDots(butDots->group());
        QJsonObject discipline;
        discipline["dots"] = QString::number(dots);
        QLayout *lay = bt->parentWidget()->layout()->itemAt(1)->layout();
        for(int i = 0; i < lay->count(); i++)
        {
            QLineEdit *linePower = qobject_cast<QLineEdit* > (lay->itemAt(i)->widget());
            discp->append(linePower->text());
        }
        discipline["powers"] = *discp;
        array->append(discipline);
        if(json.contains(line->text()) && line->text() != "")
        {
            json[line->text() + "."] = *array;
        }
        else json[line->text()] = *array;
        delete array;
        delete discp;
    }
    return json;
}
QJsonObject MainWindow::saveRest()
{
    QJsonObject json;
    QLabel *hungerLabel = qobject_cast<QLabel *>(ui->verticalLayout_4->itemAt(0)->widget());
    json[hungerLabel->text()] = QString::number(countDots(ui->Hunger));

    QJsonArray *array = new QJsonArray();
    QJsonObject healthPoints;
    healthPoints["modifier"] = QString::number(ui->healthModifier->value());
    healthPoints["superficial"] = QString::number(countIndicators(ui->Health, healthPool).first);
    healthPoints["agravated"] = QString::number(countIndicators(ui->Health, healthPool).second);
    array->append(healthPoints);
    json["Health"] = *array;
    array->pop_back();

    QJsonObject willpowerPoints;
    willpowerPoints["modifier"] = QString::number(ui->wpModifier->value());
    willpowerPoints["superficial"] = QString::number(countIndicators(ui->Willpower, willpowerPool).first);
    willpowerPoints["agravated"] = QString::number(countIndicators(ui->Willpower, willpowerPool).second);
    array->append(willpowerPoints);
    json["Willpower"] = *array;
    json["Humanity"] = QString::number(countIndicators(ui->HumanityLayout,10).second);
    json["Stains"] = QString::number(countIndicators(ui->HumanityLayout,10).first);
    json["Blood Potency"] = QString::number(countDots(ui->BloodPotencyGroup));
    json["Notes"] = notesText;
    delete array;

    return json;
}
void MainWindow::Save(QString directory)
{
    QFile saveFile(directory);
    QJsonObject json;
    QJsonObject mainJson;
    mainJson["Language"] = locale().languageToString(locale().language());
    QJsonArray *array = new QJsonArray();
    array->append(saveAttributes());
    json["Attributes"] = *array;
    array->pop_back();

    array->append(saveSkills());
    json["Skills"] = *array;
    array->pop_back();

    array->append(saveRest());
    json["Rest"] = *array;
    array->pop_back();


    array->append(saveDiscipline());
    json["Discipline"] = *array;
    array->pop_back();

    array->append(json);
    mainJson["Statistics"] = *array;

    delete array;

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }
    saveFile.write(QJsonDocument(mainJson).toJson());
    saveFile.close();
    MainWindow::setWindowTitle(QFileInfo(directory).baseName());

}

bool MainWindow::androidSave(QString directory)//TODO
{
    QFile saveFile(directory);
    QJsonObject mainJson;
    mainJson["Language"] = locale().languageToString(locale().language());
    QJsonObject jsonAtr = saveAttributes();
    mainJson["Attributes"] = jsonAtr;

    QJsonObject mentalSkills = saveSkillsAndroid(ui->MentalSkillsGroup);
    QJsonObject socialSkills = saveSkillsAndroid(ui->SocialSkillsGroup);
    QJsonObject physicalSkills = saveSkillsAndroid(ui->PhysicalSkillsGroup);

    mainJson["Mental Skills"] = mentalSkills;
    mainJson["Social Skills"] = socialSkills;
    mainJson["Physical Skills"] = physicalSkills;

    mainJson["Indicators"] = saveRestAndroid();

    QJsonObject personalData;
    personalData["Blood Potency"] = QString::number(countDots(ui->BloodPotencyGroup));
    mainJson["Personal Data"] = personalData;

    mainJson["Disciplines"] = saveDisciplinesAndroid();

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }
    saveFile.write(QJsonDocument(mainJson).toJson());
    saveFile.close();
    MainWindow::setWindowTitle(QFileInfo(directory).baseName());

    return true;
}
bool MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Save File"),
                                                    QDir::currentPath(),
                                                    QObject::tr("Save files for Windows (*.json);;Save files for Android (*.sav); "));
    if(filename.isEmpty())
    {
        qWarning() << "Couldn't Save";
        return false;
    }

    lastDirectory = filename;

    if(filename.endsWith(".sav"))
    {
        auto previousLocale = locale();
        ui->actionEnglish->trigger();

        if(!androidSave(filename))
        {
            qWarning("Saving Failed");
            return false;
        }

        setLocale(previousLocale);
        return true;
    }
    Save(filename);
    return true;
}
bool MainWindow::loadRest(QJsonObject json)
{
    if(json.contains("Rest") && json["Rest"].isArray())
    {
        QJsonArray restArray = json["Rest"].toArray();
        QLabel *hungerLabel = qobject_cast<QLabel *>(ui->verticalLayout_4->itemAt(0)->widget());
        if(restArray.first()[hungerLabel->text()].isString())
        {
            int dots = restArray.first()[hungerLabel->text()].toString().toInt();
            if(dots > 0)
            {
                for(QAbstractButton *but : ui->Hunger->buttons())//CZEMU TO DIALA A NIE DZIALA ui->Hunger->button(dots - 1) ?!?!?!!?
                {//najwidoczniej id nie ustawia sie samo czy cos...
                    if(dots == 0)
                        break;
                    dots--;
                    but->click();
                }
            }
        }
        if(restArray.first()["Health"].isArray())
        {
            QJsonArray healthArray = restArray.first()["Health"].toArray();
            int modifier = healthArray.first()["modifier"].toString().toInt();
            int agravated = healthArray.first()["agravated"].toString().toInt();
            int superficial = healthArray.first()["superficial"].toString().toInt();
            ui->healthModifier->setValue(modifier);
            calculateHealth();
            for(int i = 0 ; i < agravated + superficial; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Health->itemAt(i)->widget());
                but->click();
            }
            for(int i = 0 ; i < agravated; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Health->itemAt(i)->widget());
                but->click();
            }
        }
        if(restArray.first()["Willpower"].isArray())
        {
            QJsonArray willpowerArray = restArray.first()["Willpower"].toArray();
            int modifier = willpowerArray.first()["modifier"].toString().toInt();
            int agravated = willpowerArray.first()["agravated"].toString().toInt();
            int superficial = willpowerArray.first()["superficial"].toString().toInt();
            ui->wpModifier->setValue(modifier);
            calculateWP();
            for(int i = 0 ; i < agravated + superficial; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Willpower->itemAt(i)->widget());
                but->click();
            }
            for(int i = 0 ; i < agravated; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Willpower->itemAt(i)->widget());
                but->click();
            }
        }
        if(restArray.first()["Humanity"].isString())
        {
            int hum = restArray.first()["Humanity"].toString().toInt();
            for(int i = 0; i < hum; i++)
            {
                QCheckBox *czek = qobject_cast <QCheckBox * >(ui->HumanityLayout->itemAt(i)->widget());
                czek->setCheckState(Qt::CheckState::Checked);
            }
        }
        if(restArray.first()["Stains"].isString())
        {
            int stains = restArray.first()["Stains"].toString().toInt();
            for(int i = 0; i < stains; i++)
            {
                QCheckBox *czek = qobject_cast <QCheckBox * >(ui->HumanityLayout->itemAt(9 - i)->widget());
                czek->setCheckState(Qt::CheckState::PartiallyChecked);
            }
        }
        if(restArray.first()["Blood Potency"].isString())
        {
            int blood = restArray.first()["Blood Potency"].toString().toInt();
            for(QAbstractButton *bt : ui->BloodPotencyGroup->buttons())
            {
                if(blood > 0)
                {
                    bt->click();
                    blood--;
                }
            }
        }
        if(restArray.first()["Notes"].isString())
        {
            notesText = restArray.first()["Notes"].toString();
        }
        return true;
    }
    return false;
}


bool MainWindow::loadAttributes(QJsonObject json)
{
    if(json.contains("Attributes") && json["Attributes"].isArray())
    {
        QJsonArray attributesArray = json["Attributes"].toArray();
        for(QAbstractButton *bt : ui->buttonGroup->buttons())
        {
            if(attributesArray.first()[bt->text()].isString())
            {
                int dots = attributesArray.first()[bt->text()].toString().toInt();
                if(dots > 0)
                {

                    QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }
            }
        }
        return true;
    }
    return false;

}
bool MainWindow::loadSkills(QJsonObject json)
{
    if(json.contains("Skills") && json["Skills"].isArray())
    {
        QJsonArray array = json["Skills"].toArray();
        for(QAbstractButton *bt : ui->MentalSkillsGroup->buttons())
        {
            if(array.first()[bt->text()].isArray())
            {
                QJsonArray skillArray = array.first()[bt->text()].toArray();
                int dots = skillArray.first()["dots"].toString().toInt();
                if(dots > 0)
                {
                    QLayout *lay = findParentLayout(bt);
                    QLineEdit *line = qobject_cast<QLineEdit *>(lay->itemAt(1)->widget());
                    line->setText(skillArray.first()["specialization"].toString());
                    QAbstractButton * but = qobject_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }
            }
        }
        for(QAbstractButton *bt : ui->SocialSkillsGroup->buttons())
        {
            if(array.first()[bt->text()].isArray())
            {
                QJsonArray skillArray = array.first()[bt->text()].toArray();
                int dots = skillArray.first()["dots"].toString().toInt();
                if(dots > 0)
                {
                    QLayout *lay = findParentLayout(bt);
                    QLineEdit *line = qobject_cast<QLineEdit *>(lay->itemAt(1)->widget());
                    line->setText(skillArray.first()["specialization"].toString());
                    QAbstractButton * but = qobject_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }
            }
        }
        for(QAbstractButton *bt : ui->PhysicalSkillsGroup->buttons())
        {
            if(array.first()[bt->text()].isArray())
            {
                QJsonArray skillArray = array.first()[bt->text()].toArray();
                int dots = skillArray.first()["dots"].toString().toInt();
                if(dots > 0)
                {
                    QLayout *lay = findParentLayout(bt);
                    QLineEdit *line = qobject_cast<QLineEdit *>(lay->itemAt(1)->widget());
                    line->setText(skillArray.first()["specialization"].toString());
                    QAbstractButton * but = qobject_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }
            }
        }
        return true;
    }
    return false;
}

bool MainWindow::loadDiscipline(QJsonObject json)
{
    if(json.contains("Discipline") && json["Discipline"].isArray())
    {
        QJsonArray array = json["Discipline"].toArray();
        QStringList keyList = array.first().toObject().keys();
        if(keyList.first() == "")
            keyList.swapItemsAt(0,keyList.size() - 1);
        for(QAbstractButton *bt : ui->buttonGroup_3->buttons())
        {
            if(keyList.isEmpty())
                break;
            QString key = keyList.first();
            keyList.pop_front();
            QLineEdit *line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
            if(array.first()[key].isArray())
            {
                line->setText(key);
                QJsonArray discipline = array.first()[key].toArray();
                if(discipline.first()["dots"].isString())
                {
                    int dots = discipline.first()["dots"].toString().toInt();
                    if(dots > 0)
                    {
                        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                        but->click();
                        QLayout *lay = bt->parentWidget()->layout()->itemAt(1)->layout();
                        QJsonArray powers = discipline.first()["powers"].toArray();
                        for(int i = 0 ; i < dots; i++)
                        {
                            QLineEdit *power = qobject_cast <QLineEdit *> (lay->itemAt(i)->widget());
                            power->setText(powers.first().toString());
                            powers.pop_front();
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}

bool MainWindow::androidLoad(QJsonObject json)
{
    if(json.contains("Attributes") && json["Attributes"].isObject())
    {
        auto attributesJson = json["Attributes"].toObject();
        for(QAbstractButton *bt : ui->buttonGroup->buttons())
        {
            if(attributesJson.contains(bt->text()) && attributesJson[bt->text()].isString())
            {
                size_t dots = attributesJson[bt->text()].toString().toInt();
                if(dots > 0)
                {
                    QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }
            }
        }
    }
    if(json.contains("Mental Skills") && json["Mental Skills"].isObject())
    {
        auto mentalSkillsJson = json["Mental Skills"].toObject();
        for(QAbstractButton *bt : ui->MentalSkillsGroup->buttons())
        {
            if(mentalSkillsJson.contains(bt->text()) && mentalSkillsJson[bt->text()].isObject())
            {
                QJsonObject details = mentalSkillsJson[bt->text()].toObject();
                size_t dots = 0;
                QString spec = "";
                if(details.contains("dots") && details["dots"].isString())
                {
                    dots = details["dots"].toString().toInt();
                }
                if(details.contains("specializations") && details["specializations"].isString())
                {
                    spec = details["specializations"].toString();
                }
                if(dots != 0)
                {
                    QLayout *lay = findParentLayout(bt);
                    QLineEdit *line = qobject_cast<QLineEdit *>(lay->itemAt(1)->widget());
                    line->setText(spec);

                    QAbstractButton * but = qobject_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }

            }
        }
    }
    if(json.contains("Physical Skills") && json["Physical Skills"].isObject())
    {
        auto physicalSkillsJson = json["Physical Skills"].toObject();
        for(QAbstractButton *bt : ui->PhysicalSkillsGroup->buttons())
        {
            if(physicalSkillsJson.contains(bt->text()) && physicalSkillsJson[bt->text()].isObject())
            {
                QJsonObject details = physicalSkillsJson[bt->text()].toObject();
                size_t dots = 0;
                QString spec = "";
                if(details.contains("dots") && details["dots"].isString())
                {
                    dots = details["dots"].toString().toInt();
                }
                if(details.contains("specializations") && details["specializations"].isString())
                {
                    spec = details["specializations"].toString();
                }
                if(dots != 0)
                {
                    QLayout *lay = findParentLayout(bt);
                    QLineEdit *line = qobject_cast<QLineEdit *>(lay->itemAt(1)->widget());
                    line->setText(spec);

                    QAbstractButton * but = qobject_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }

            }
        }
    }
    if(json.contains("Social Skills") && json["Social Skills"].isObject())
    {
        auto socialSkillsJson = json["Social Skills"].toObject();
        //auto skillsJson = mentalSkillsJson;
        for(QAbstractButton *bt : ui->SocialSkillsGroup->buttons())
        {
            if(socialSkillsJson.contains(bt->text()) && socialSkillsJson[bt->text()].isObject())
            {
                QJsonObject details = socialSkillsJson[bt->text()].toObject();
                size_t dots = 0;
                QString spec = "";
                if(details.contains("dots") && details["dots"].isString())
                {
                    dots = details["dots"].toString().toInt();
                }
                if(details.contains("specializations") && details["specializations"].isString())
                {
                    spec = details["specializations"].toString();
                }
                if(dots != 0)
                {
                    QLayout *lay = findParentLayout(bt);
                    QLineEdit *line = qobject_cast<QLineEdit *>(lay->itemAt(1)->widget());
                    line->setText(spec);

                    QAbstractButton * but = qobject_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }

            }
        }
    }
    if(json.contains("Indicators") && json["Indicators"].isObject())
    {
        auto indicatorsJson = json["Indicators"].toObject();
        if(indicatorsJson.contains("health") && indicatorsJson["health"].isObject())
        {
            auto healthJson = indicatorsJson["health"].toObject();
            size_t modifier = healthJson["modifier"].toString().toInt();
            size_t agravated = healthJson["agravated"].toString().toInt();
            size_t superficial = healthJson["superficial"].toString().toInt();
            ui->healthModifier->setValue(modifier);
            calculateHealth();
            for(size_t i = 0 ; i < agravated + superficial; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Health->itemAt(i)->widget());
                but->click();
            }
            for(size_t i = 0 ; i < agravated; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Health->itemAt(i)->widget());
                but->click();
            }

        }
        if(indicatorsJson.contains("willpower") && indicatorsJson["willpower"].isObject())
        {
            auto willpowerJson = indicatorsJson["willpower"].toObject();
            size_t modifier = indicatorsJson["modifier"].toString().toInt();
            size_t agravated = indicatorsJson["agravated"].toString().toInt();
            size_t superficial = indicatorsJson["superficial"].toString().toInt();
            ui->wpModifier->setValue(modifier);
            calculateWP();
            for(size_t i = 0 ; i < agravated + superficial; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Willpower->itemAt(i)->widget());
                but->click();
            }
            for(size_t i = 0 ; i < agravated; i++)
            {
                QAbstractButton *but = qobject_cast <QAbstractButton *> (ui->Willpower->itemAt(i)->widget());
                but->click();
            }

        }
        if(indicatorsJson.contains("humanity") && indicatorsJson["humanity"].isString())
        {
            size_t humanityValue = indicatorsJson["humanity"].toString().toInt();
            for(size_t i = 0; i < humanityValue; i++)
            {
                QCheckBox *czek = qobject_cast <QCheckBox * >(ui->HumanityLayout->itemAt(i)->widget());
                czek->setCheckState(Qt::CheckState::Checked);
            }
        }
        if(indicatorsJson.contains("stains") && indicatorsJson["stains"].isString())
        {
            size_t stains = indicatorsJson["stains"].toString().toInt();
            for(size_t i = 0; i < stains; i++)
            {
                QCheckBox *czek = qobject_cast <QCheckBox * >(ui->HumanityLayout->itemAt(9 - i)->widget());
                czek->setCheckState(Qt::CheckState::Checked);
            }
        }
        if(indicatorsJson.contains("hunger") && indicatorsJson["hunger"].isString())
        {
            size_t hungerValue = indicatorsJson["hunger"].toString().toInt();
            if(hungerValue > 0)
            {
                for(QAbstractButton *but : ui->Hunger->buttons())
                {
                    if(hungerValue == 0)
                        break;
                    hungerValue--;
                    but->click();
                }
            }
        }
    }
    if(json.contains("Personal Data") && json["Personal Data"].isObject())
    {
        auto personalDataJson = json["Personal Data"].toObject();
        if(personalDataJson.contains("Blood Potency") && personalDataJson["Blood Potency"].isString())
        {
            size_t bloodValue = personalDataJson["Blood Potency"].toString().toInt();
            for(QAbstractButton *bt : ui->BloodPotencyGroup->buttons())
            {
                if(bloodValue > 0)
                {
                    bt->click();
                    bloodValue--;
                }
            }
        }
        QJsonDocument doc(personalDataJson);
        QString strJson(doc.toJson(QJsonDocument::Indented));
        notesText = strJson.sliced(2, strJson.size() - 4);
    }
    if(json.contains("Loresheets") && json["Loresheets"].isObject())
    {
        auto loresheetsJson = json["Loresheets"].toObject();
        QJsonDocument doc(loresheetsJson);
        QString strJson(doc.toJson(QJsonDocument::Indented));
        notesText += "\n\nLoresheets:\n\n";
        notesText += strJson.sliced(2, strJson.size() - 4);
    }
    if(json.contains("Merits and Flaws") && json["Merits and Flaws"].isObject())
    {
        auto meritsAndFlawsJson = json["Merits and Flaws"].toObject();
        QJsonDocument doc(meritsAndFlawsJson);
        QString strJson(doc.toJson(QJsonDocument::Indented));
        notesText += "\n\nMerits & Flaws:\n\n";
        notesText += strJson.sliced(2, strJson.size() - 4);
    }
    if(json.contains("Disciplines") && json["Disciplines"].isObject())
    {
        auto disciplinesJson = json["Disciplines"].toObject();
        QStringList keyList = disciplinesJson.keys();
        for(QAbstractButton *bt : ui->buttonGroup_3->buttons())
        {
            if(keyList.isEmpty())
                break;
            QString key = keyList.first();
            keyList.pop_front();
            QLineEdit *line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
            if(disciplinesJson[key].isObject())
            {
                line->setText(key);
                QJsonObject disciplineDetails = disciplinesJson[key].toObject();
                if(disciplineDetails.contains("dots") && disciplineDetails["dots"].isString())
                {
                    size_t dots = disciplineDetails["dots"].toString().toInt();
                    if(dots > 0)
                    {
                        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                        but->click();
                        QLayout *lay = bt->parentWidget()->layout()->itemAt(1)->layout();
                        QJsonArray powers = disciplineDetails["powers"].toArray();
                        for(size_t i = 0 ; i < dots; i++)
                        {
                            QLineEdit *power = qobject_cast <QLineEdit *> (lay->itemAt(i)->widget());
                            power->setText(powers.first().toString());
                            powers.pop_front();
                        }
                    }
                }
            }
        }
    }
    return true;
}

QJsonObject MainWindow::saveSkillsAndroid(QButtonGroup *group)
{
    QJsonObject json;
    for(auto bt : group->buttons())
    {
        QJsonObject skill;
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        int dots = countDots(but->group());
        skill["specializations"] = line->text();
        skill["dots"] = QString::number(dots);
        json[bt->text()] = skill;
    }
    return json;
}

QJsonObject MainWindow::saveRestAndroid()
{

    QJsonObject json;

    json["hunger"] = QString::number(countDots(ui->Hunger));
    json["humanity"] = QString::number(countIndicators(ui->HumanityLayout,10).second);

    QJsonObject healthPoints;
    healthPoints["modifier"] = QString::number(ui->healthModifier->value());
    healthPoints["superficial"] = QString::number(countIndicators(ui->Health, healthPool).first);
    healthPoints["agravated"] = QString::number(countIndicators(ui->Health, healthPool).second);
    json["health"] = healthPoints;

    QJsonObject willpowerPoints;
    willpowerPoints["modifier"] = QString::number(ui->wpModifier->value());
    willpowerPoints["superficial"] = QString::number(countIndicators(ui->Willpower, willpowerPool).first);
    willpowerPoints["agravated"] = QString::number(countIndicators(ui->Willpower, willpowerPool).second);
    json["willpower"] = willpowerPoints;

    return json;
}

QJsonObject MainWindow::saveDisciplinesAndroid()
{
    QJsonObject json;
    for(QAbstractButton *bt : ui->buttonGroup_3->buttons())
    {
        QJsonArray discp = QJsonArray();
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        int dots = countDots(but->group());
        QJsonObject discipline;
        discipline["dots"] = QString::number(dots);
        QLayout *lay = bt->parentWidget()->layout()->itemAt(1)->layout();
        for(int i = 0; i < lay->count(); i++)
        {
            QLineEdit *linePower = qobject_cast<QLineEdit* > (lay->itemAt(i)->widget());
            discp.append(linePower->text());
        }
        discipline["powers"] = discp;

        json[line->text()] = discipline;
    }
    return json;
}
void MainWindow::on_actionLoad_triggered()
{

    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Open Save"),
                                                    QDir::currentPath(),
                                                    QObject::tr("Save files for Windows (*.json);;Save files for Android (*.sav); "));
    if(filename.isEmpty())
    {
        qWarning("Name of the save file is empty.");
        return;
    }
    QFile loadFile(filename);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();



    clear();
    closeNotes();
    if(filename.endsWith(".sav"))
    {
        ui->actionEnglish->trigger();
        if(!androidLoad(json))
        {
            qWarning("Loading Failed");
            return;
        }
    }
    else
    {
        if(json.contains("Language") && json["Language"].isString())
        {
            if(json["Language"] == "Polish")
                ui->actionPolish->trigger();
            if(json["Language"] == "English")
                ui->actionEnglish->trigger();
        }
        else
        {
            qWarning("Couldn't find language");
            ui->actionEnglish->trigger();
            return;
        }
        if(json.contains("Statistics") && json["Statistics"].isArray())
        {
            QJsonArray array = json["Statistics"].toArray();
            if(!loadAttributes(array.first().toObject()))
            {
                qWarning("Couldn't load Attributes");
                return;
            }
            if(!loadSkills(array.first().toObject()))
            {
                qWarning("Couldn't load Skills");
                return;
            }
            if(!loadRest(array.first().toObject()))
            {
                qWarning("Couldn't load Rest");
                return;
            }
            if(!loadDiscipline(array.first().toObject()))
            {
                qWarning("Couldn't load Disciplines");
                return;
            }
        }
    }

    MainWindow::setWindowTitle(QFileInfo(filename).baseName());
    lastDirectory = filename;
}

void MainWindow::dynamicDisciplineCreator(QAbstractButton *bt)
{
    QLayout *lay = bt->parentWidget()->layout()->itemAt(1)->layout();
    int size_ = countDots(bt->group());
    if(lay->count() > size_)
    {
        while(lay->count() != size_)
        {
            lay->itemAt(lay->count() - 1)->widget()->deleteLater();
            lay->removeWidget(lay->itemAt(lay->count() - 1)->widget());
        }
    }
    if(lay->count() < size_)
    {
        while(lay->count() != size_)
        {
            lay->addWidget(new QLineEdit());
        }
    }
}

void MainWindow::humanityChanged()//nienawidze tego, ale nie chce mi się ogarniać algorytmu do tego, mam wrazenie ze to by zajelo zbyt duzo czasu
{
    unsigned short hum = countIndicators(ui->HumanityLayout,10).second;
    QString text;
    if(hum == 10)
    {
        text = tr("You don't need Blush of Life.\nYou can have sex.\nYou can keep watch at day like mortal.\nYou can eat normal food.\nDamage from sunlight are split by half.");
    }
    else if(hum == 9)
    {
        text = tr("You don't need Blush of Life.\nYou can have sex.\nYou can awaken 1 hour before the sunrise and keep watch 1h after sunset.\nYou can eat raw meat and drink.\n");
    }
    else if(hum == 8)
    {
        text = tr("You roll 2 dices for Blush of Life.\nYou can have sex with Blush of Life.\nYou can drink wine with Blush of Life.\nYou can awaken 1 hour before the sunrise.");
    }
    else if(hum == 7)
    {
        text = tr("You can not have sex but you can fake it with Dexterity + Charisma.\nUnless you use Blush of Life foods and drinks makes you vomit.");
    }
    else if(hum == 6)
    {
        text = tr("You can not have sex but you can fake it with Dexterity + Charisma with 1 die penalty.\nEven with Blush Of Life foods and drinks make you vomit.");
    }
    else if(hum == 5)
    {
        text = tr("You can not have sex but you can fake it with Dexterity + Charisma with 2 dice penalty.\nYou suffer 1 die penalty when interacting with humans.");
    }
    else if(hum == 4)
    {
        text = tr("You can not have sex but you can fake it with Dexterity + Charisma with 2 dice penalty.\nYou suffer 2 dice penalty when interacting with humans.");
    }
    else if(hum == 3)
    {
        text = tr("You can no longer have sex.\nYou suffer 4 dice penalty when interacting with humans.");
    }
    else if(hum == 2)
    {
        text = tr("You can no longer have sex.\nYou suffer 6 dice penalty when interacting with humans.");
    }
    else if(hum == 1)
    {
        text = tr("You can no longer have sex.\nYou suffer 8 dice penalty when interacting with humans.");
    }
    else
    {
        text = tr("You have become the beast, you have no longer have control over your character.");
    }
    ui->humanityText->setText(text);
}

void MainWindow::saveWithShortcut()
{
    if(lastDirectory.isEmpty()){
        on_actionSave_triggered();
    }
    else{
        if(lastDirectory.endsWith(".sav"))
        {
            androidSave(lastDirectory);
        }
        else
        {
            Save(lastDirectory);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(MainWindow::windowTitle().toStdString()[MainWindow::windowTitle().toStdString().size() - 1] == '*')
    {
        int ret = QMessageBox::question(this, tr("Warning"), tr("Character Sheet has been modified.\nDo you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel, QMessageBox::Save);
        if(ret == QMessageBox::Save)
        {
            if(on_actionSave_triggered()){
                event->accept();
            }
            else{
                event->ignore();
            }
        }
        else if(ret == QMessageBox::Discard)
        {
            event->accept();
        }
        else if(ret == QMessageBox::Cancel)
        {
            event->ignore();
        }
    }
    if(event->isAccepted())
        closeNotes();
    if(clanWindow != nullptr && clanWindow->isEnabled() && event->isAccepted())
    {
        clanWindow->close();
        clanWindow->deleteLater();
    }
    foreach (auto wind, disciplineWindowStack) {
        wind->deleteLater();
    }
    qWarning() << "WYCHODZE z głównego programu";
}

void MainWindow::on_actionShow_triggered()
{
    if(notesWindow == nullptr)
        notesWindow = new NotesWindow(this);
    notesWindow->show();


}

void MainWindow::on_actionShowBook_triggered()
{
    if(clanWindow == nullptr)
        clanWindow = new ClanWindow();
    clanWindow->show();
}

void MainWindow::closeNotes()
{
    if(notesWindow != nullptr && notesWindow->isEnabled())
    {
        notesWindow->close();
        notesWindow->deleteLater();
    }
    notesWindow = nullptr;
    notesText.clear();
}

void MainWindow::postDataToDiscord()
{
    QString poolToSend = poolName.join("+");
    QString normalDicesToSend;
    QString hungerDicesToSend;
    if(!graphicRepresentation){
        //data = QString(tr("```%1 rolls: %2\nNormal dices: %3\nHunger dices: %4```")).arg(userName, poolName.join("+"), normalDices.join(" "), hungerDices.join(" "));
        normalDicesToSend = normalDices.join("  ");
        hungerDicesToSend = hungerDices.join("  ");
    }
    else{
        QStringList normalDiceGraphic;
        QStringList hungerDiceGraphic;
        for(const QString& value : normalDices){
            if(value.toInt() == 10)
                normalDiceGraphic.append(emotesIds.value("NormalCritical"));
            else if(value.toInt() < 10 && value.toInt() > 5)
                normalDiceGraphic.append(emotesIds.value("NormalSuccess"));
            else
                normalDiceGraphic.append(emotesIds.value("NormalFailure"));
        }

        for(const QString& value : hungerDices){
            if(value.toInt() == 10)
                hungerDiceGraphic.append(emotesIds.value("RedCritical"));
            else if(value.toInt() < 10 && value.toInt() > 5)
                hungerDiceGraphic.append(emotesIds.value("RedSuccess"));
            else if(value.toInt() == 1)
                hungerDiceGraphic.append(emotesIds.value("BestialFailure"));
            else
                hungerDiceGraphic.append(emotesIds.value("RedFailure"));
        }
        normalDicesToSend = normalDiceGraphic.join("   ");
        hungerDicesToSend = hungerDiceGraphic.join("   ");
        //data = QString(tr("%1 rolls: %2\n%3\n%4").arg(userName, poolName.join("+"), normalDiceGraphic.join(" "), hungerDiceGraphic.join(" ")));
    }
    sendData(poolToSend, normalDicesToSend, hungerDicesToSend);

}

void MainWindow::sendData(QString& poolFormatted, QString& normalDicesFormatted, QString& hungerDicesFormatted){
    QUrl url = QUrl(discordWebhookURL);
    QNetworkRequest request;
    request.setUrl(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/json");
    QByteArray postData;
    QString inlineString = "true";
    if(!useInline)
        inlineString = "false";
    postData.append(
        QString(
            "{\"embeds\": [{"
                "\"title\":" + tr("\"%1 rolls:\",").arg(userName) +
                "\"description\": \"%1\","
                "\"fields\": ["
                 "{"
                    +tr("\"name\": \"Normal Dices\",")+
                    "\"value\": \"%2\","
                    "\"inline\": %4"
                 "},"
                 "{"
                    +tr("\"name\": \"Hunger Dices\",")+
                    "\"value\": \"%3\","
                    "\"inline\": %4"
                 "}"
               "]"
             "}]"
            "}").arg(poolFormatted, normalDicesFormatted, hungerDicesFormatted, inlineString).toUtf8()
    );
    QNetworkReply *reply = manager->post(request, postData);
}

void MainWindow::on_useGraphics_stateChanged(int state) // TODO
{
/* TODO
    switch(state){
    case Qt::Unchecked:

        break;
    case Qt::Checked:

        break;
    }
    */
}


void MainWindow::on_actionShowDisciplines_triggered()
{    

    foreach (auto window, disciplineWindowStack) {
        if(!window->isVisible()){
            qWarning() << "Okienko jest niewidoczne, dealokowanie pamięci";
            disciplineWindowStack.removeOne(window);
            window->deleteLater();
        }
    }
    disciplineWindowStack.push_back(new DisciplineWindow());
    disciplineWindowStack.back()->show();
}


void MainWindow::on_actionGenerate_new_Random_Character_triggered()
{
    int ret = QMessageBox::information(this, tr("Warning"), tr("This option will generate a completely new character!\n All previous informations will be erased!\n Do you wish to continue?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(ret == QMessageBox::No)
        return;

    QList<size_t> skills_JACK = {3, 2,2,2,2,2,2,2,2, 1,1,1,1,1,1,1,1,1,1};
    QList<size_t> skills_BALANCED = {3,3,3, 2,2,2,2,2, 1,1,1,1,1,1,1,1};
    QList<size_t> skills_SPEC = {4, 3,3,3, 2,2,2, 1,1,1};
    QList<size_t> LUT_skills;
    QList<size_t> LUT_attributes = {4, 3,3,3, 2,2,2,2, 1};


    QList<QAbstractButton *> bagWithAttributes = QList<QAbstractButton *>(ui->buttonGroup->buttons());

    QList<QAbstractButton *> bagWithSkills = QList<QAbstractButton *>(ui->MentalSkillsGroup->buttons());
    for(auto skill : ui->SocialSkillsGroup->buttons())
        bagWithSkills.push_back(skill);
    for(auto skill : ui->PhysicalSkillsGroup->buttons())
        bagWithSkills.push_back(skill);
    QMessageBox msgBox;
    msgBox.setText(tr("Skill distribution: "));
    msgBox.setInformativeText(tr("Which skill distribution would you like to use?"));
    QPushButton *jackButton = msgBox.addButton(tr(" Jack of All Trades "), QMessageBox::AcceptRole);
    QPushButton *balancedButton = msgBox.addButton(tr(" Balanced "), QMessageBox::AcceptRole);
    QPushButton *specialistButton = msgBox.addButton(tr(" Specialist "), QMessageBox::AcceptRole);
    QPushButton *abortButton = msgBox.addButton(QMessageBox::Abort);
    msgBox.exec();

    if(msgBox.clickedButton() == abortButton)
    {
        return;
    }
    else {
        clear();
        if(msgBox.clickedButton() == jackButton){
            LUT_skills = skills_JACK;
        }
        else if(msgBox.clickedButton() == balancedButton){
            LUT_skills = skills_BALANCED;
        }
        else if(msgBox.clickedButton() == specialistButton){
            LUT_skills = skills_SPEC;
        }
        for(auto &atrValue : LUT_attributes)
        {
            //magiczny syf do wyciagniecia przycisku (kropki) o odpowiedniej wartosci ze zrandomizowanym atrybutem
            QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bagWithAttributes.takeAt(QRandomGenerator::global()->generate() % bagWithAttributes.count()))->itemAt(1)->layout()->itemAt(atrValue - 1)->widget());
            but->click();
        }
        for(auto &skillValue : LUT_skills)
        {
            //magiczny syf do wyciagniecia przycisku (kropki) o odpowiedniej wartosci ze zrandomizowanym skillem
            QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bagWithSkills.takeAt(QRandomGenerator::global()->generate() % bagWithSkills.count()))->itemAt(2)->layout()->itemAt(skillValue - 1)->widget());
            but->click();
        }
    }

}

void MainWindow::connectAllButtons()
{
   //connecting all checkboxes to automatically adjust amount of checked dots
    connect(ui->Str,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Dex,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Sta,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);

    connect(ui->Chr,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Man,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Com,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);


    connect(ui->Int,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Wit,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Res,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);


    connect(ui->TalentsGroup,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_2,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_3,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_4,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_5,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_6,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_7,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_8,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_9,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);

    connect(ui->TalentsGroup_10,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_11,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_12,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_13,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_14,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_15,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_16,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_17,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_18,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);

    connect(ui->TalentsGroup_19,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_20,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_21,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_22,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_23,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_24,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_25,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_26,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->TalentsGroup_27,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);

    connect(ui->Discipline1Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Discipline1Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDisciplineCreator);
    connect(ui->Discipline2Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Discipline2Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDisciplineCreator);
    connect(ui->Discipline3Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Discipline3Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDisciplineCreator);
    connect(ui->Discipline4Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Discipline4Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDisciplineCreator);

    connect(ui->Hunger,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->BloodPotencyGroup,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
   //


   //generating data to the blood table
    connect(ui->BloodPotencyGroup,&QButtonGroup::buttonClicked,this,&MainWindow::calculateBlood);
   //

   //calculating indicators based on stats and modifiers
    connect(ui->Sta,&QButtonGroup::buttonClicked,this,&MainWindow::calculateHealth);
    connect(ui->Res,&QButtonGroup::buttonClicked,this,&MainWindow::calculateWP);
    connect(ui->Com,&QButtonGroup::buttonClicked,this,&MainWindow::calculateWP);

    connect(ui->wpModifier,&QSpinBox::valueChanged,this,&MainWindow::calculateWP);
    connect(ui->healthModifier,&QSpinBox::valueChanged,this,&MainWindow::calculateHealth);
   //

   //trigger for changing language
    connect(ui->menuChange_Language, &QMenu::triggered,this, &MainWindow::slotLanguageChanged);
   //

   //bolding of checked skills/attributes/disciplines
    connect(ui->buttonGroup,&QButtonGroup::buttonToggled,this,&MainWindow::bolding);
    connect(ui->MentalSkillsGroup,&QButtonGroup::buttonToggled,this,&MainWindow::bolding);
    connect(ui->SocialSkillsGroup,&QButtonGroup::buttonToggled,this,&MainWindow::bolding);
    connect(ui->PhysicalSkillsGroup,&QButtonGroup::buttonToggled,this,&MainWindow::bolding);
    connect(ui->buttonGroup_3,&QButtonGroup::buttonToggled,this,&MainWindow::bolding);
   //
}




void MainWindow::on_actionEnable_Discord_Webhook_toggled(bool isChecked)
{
    if(isChecked){
        QString settingsFilePath = QDir::currentPath() + "/settings.json";
        QFileInfo fileInfo(settingsFilePath);
        if(!fileInfo.exists() || !fileInfo.isFile()){
            QMessageBox warningBox;
            warningBox.setText(tr("Settings file could not be found, created new"));
            warningBox.exec();
            createSettingsFile(settingsFilePath);
            ui->actionEnable_Discord_Webhook->setChecked(false);
            return;
        }
        //load
        if(loadSettings(settingsFilePath) != 0){
            ui->actionEnable_Discord_Webhook->setChecked(false);
            return;
        }
    }else{
        discordWebhookURL = "";
        graphicRepresentation = false;
        emotesIds.clear();
        userName = "";
    }
    discordIntegration = isChecked;
}

void MainWindow::createSettingsFile(QString filepath){
    QFile settingsFile(filepath);
    if (!settingsFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return;
    }
    QJsonObject jsonSettings{
        {"DiscordWebhookURL", ""},
        {"Username", getUserName()},
        {"GraphicalRepresentation", false},
        {"UseInline", false},
        {"EmotesIds", QJsonObject{
                {"NormalSuccess", ""},
                {"NormalFailure", ""},
                {"NormalCritical", ""},
                {"RedSuccess", ""},
                {"RedFailure", ""},
                {"RedCritical", ""},
                {"BestialFailure", ""}
            }
        },
    };
    settingsFile.write(QJsonDocument(jsonSettings).toJson());
    settingsFile.close();
}

int MainWindow::loadSettings(QString filepath){
    QFile loadFile(filepath);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        QMessageBox warningBox;
        warningBox.setText(tr("Discord webhook url is missing. Please update information"));
        warningBox.exec();
        ui->actionEnable_Discord_Webhook->setChecked(false);
        return -1;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();
    if(json.contains("DiscordWebhookURL") && json["DiscordWebhookURL"].isString())
        discordWebhookURL = json["DiscordWebhookURL"].toString();
    if(discordWebhookURL.isEmpty()){
        QMessageBox warningBox;
        warningBox.setText(tr("Discord webhook url is missing. Please update information"));
        warningBox.exec();
        ui->actionEnable_Discord_Webhook->setChecked(false);
        return -2;
    }
    if(json.contains("GraphicalRepresentation") && json["GraphicalRepresentation"].isBool())
        graphicRepresentation = json["GraphicalRepresentation"].toBool();

    if(graphicRepresentation){
        if(json.contains("EmotesIds") && json["EmotesIds"].isObject()){
            qDebug() << "I am in";
            QJsonObject emotes = json["EmotesIds"].toObject();
            for(const QString& key : emotes.keys()){
                qDebug() << "inserting: " << key << " as " << emotes.value(key).toString();
                emotesIds.insert(key, emotes.value(key).toString());
            }
            if(emotesIds.size() != 7 && emotesIds.values().contains("")){
                QMessageBox warningBox;
                warningBox.setText(tr("Some emotes ids are missing"));
                warningBox.exec();
                ui->actionEnable_Discord_Webhook->setChecked(false);
                return -3;
            }
        }
    }
    if(json.contains("UseInline") && json["UseInline"].isBool())
        useInline = json["UseInline"].toBool();

    if(json.contains("Username") && json["Username"].isString())
        userName = json["Username"].toString();

    return 0;
}
QString MainWindow::getUserName(){
    QString name = qgetenv("USER");
    if (name.isEmpty())
        name = qgetenv("USERNAME");
    return name;
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    if(reply->error()){
        qDebug() << reply->errorString();
        QMessageBox warningBox;
        warningBox.setText(tr("There was a problem with Discord Webhook.\n%1").arg(reply->errorString()));
        warningBox.exec();
    }
    reply->deleteLater();
}


void MainWindow::on_frenzyRoll_button_clicked()
{
    poolName.clear();
    poolName.append(tr("Frenzy roll"));
    int willpowerSuperficialDMG = countIndicators(ui->Willpower, willpowerPool).first;
    int willpowerAggravatedDMG = countIndicators(ui->Willpower, willpowerPool).second;
    int willpowerModifier = ui->wpModifier->value();
    int humanityNumber = countIndicators(ui->HumanityLayout,10).second;
    int resolveNumber = countDots(ui->Res);
    int composureNumber = countDots(ui->Com);

    int remainingWillpower = resolveNumber + composureNumber + willpowerModifier - willpowerAggravatedDMG - willpowerSuperficialDMG;
    int frenzyPool = remainingWillpower + (humanityNumber / 3);

    deleteDices();
    diceAmount = frenzyPool;
    createDices(false, false);
    if(discordIntegration){
        postDataToDiscord();
    }

}

