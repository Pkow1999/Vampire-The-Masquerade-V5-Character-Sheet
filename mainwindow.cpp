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
#include <algorithm>

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
    for(QAbstractButton *bt : ui->buttonGroup_2->buttons())//skille
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
    deleteDices(counter);
    healthPool = 0;
    willpowerPool = 0;
    counter = 0;
    hunger = 0;
}

void MainWindow::createDices(int size_)
{
    for(int i = 0; i < size_; i++)
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
        dynCheck->setCheckable(true);
        if(i > counter - hunger - 1)
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
        }
        dynLayout->addWidget(dynLabel);
        dynLayout->addWidget(dynCheck);
        dynLayout->setAlignment(dynLabel, Qt::AlignCenter);
        dynLayout->setAlignment(dynCheck, Qt::AlignCenter);
        ui->Rolls->addLayout(dynLayout);
    }
}

void MainWindow::deleteDices(int size_)
{
    for(int i = 0; i < size_; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            ui->Rolls->itemAt(i)->layout()->itemAt(j)->widget()->deleteLater();
        }
        ui->Rolls->itemAt(i)->layout()->deleteLater();
    }
}

void MainWindow::on_pushButton_clicked()//roll dices
{
    deleteDices(counter);
    counter = 0;
    hunger = countDots(ui->Hunger);

    for(int i = 0; i < ui->buttonGroup->buttons().size(); i++)
    {
        if(ui->buttonGroup->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest drugi element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup->buttons().at(i)->focusWidget())->layout()->itemAt(1)->layout()->itemAt(0)->widget());
            counter += countDots(bt->group());
        }
    }

    for(int i = 0; i < ui->buttonGroup_2->buttons().size(); i++)
    {
        if(ui->buttonGroup_2->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest trzeci(!) element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup_2->buttons().at(i)->focusWidget())->layout()->itemAt(2)->layout()->itemAt(0)->widget());
            counter += countDots(bt->group());
        }
    }

    for(int i = 0; i < ui->buttonGroup_3->buttons().size(); i++)
    {
        if(ui->buttonGroup_3->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest trzeci(!) element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = qobject_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup_3->buttons().at(i)->focusWidget())->layout()->itemAt(2)->layout()->itemAt(0)->widget());
            counter += countDots(bt->group());
        }
    }

    counter += ui->diceModifier->value();
    ui->label_2->setText(QString::number(counter) + tr(" Dices"));
    createDices(counter);
}



void MainWindow::on_pushButton_2_clicked()//re roll / reroll dices
{
    for(int i = 0; i < counter; i++)
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
        }
    }
}

QJsonObject MainWindow::saveSkills()
{
    QJsonObject json;
    for(QAbstractButton *bt : ui->buttonGroup_2->buttons())
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
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = qobject_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
        int dots = countDots(but->group());
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
bool MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Save File"),QDir::currentPath(),QObject::tr("Save files (*.json);"));
    if(filename.isEmpty())
    {
        qWarning() << "Couldn't Save";
        return false;
    }
    lastDirectory = filename;
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
        for(QAbstractButton *bt : ui->buttonGroup_2->buttons())
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

void MainWindow::on_actionLoad_triggered()
{

    QString filename = QFileDialog::getOpenFileName(this,QObject::tr("Open Save"),QDir::currentPath(),QObject::tr("Save files (*.json);"));
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
        Save(lastDirectory);
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
    QList<QAbstractButton *> bagWithSkills = QList<QAbstractButton *>(ui->buttonGroup_2->buttons());


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
    connect(ui->buttonGroup_2,&QButtonGroup::buttonToggled,this,&MainWindow::bolding);
    connect(ui->buttonGroup_3,&QButtonGroup::buttonToggled,this,&MainWindow::bolding);
   //
}

