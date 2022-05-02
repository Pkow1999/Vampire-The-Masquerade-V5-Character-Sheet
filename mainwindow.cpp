#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractButton>
#include <QDir>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLayout>
#include <QRandomGenerator>
#include <QTranslator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Str,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Dex,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Sta,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Sta,&QButtonGroup::buttonClicked,this,&MainWindow::calculateHealth);


    connect(ui->Chr,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Man,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Com,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Com,&QButtonGroup::buttonClicked,this,&MainWindow::calculateWP);

    connect(ui->Int,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Wit,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Res,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Res,&QButtonGroup::buttonClicked,this,&MainWindow::calculateWP);

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
    connect(ui->Discipline1Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDiscpilineCreator);
    connect(ui->Discipline2Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Discipline2Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDiscpilineCreator);
    connect(ui->Discipline3Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Discipline3Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDiscpilineCreator);
    connect(ui->Discipline4Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);
    connect(ui->Discipline4Group,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicDiscpilineCreator);

    connect(ui->Hunger,&QButtonGroup::buttonClicked,this,&MainWindow::dynamicRemoveDots);

    connect(ui->wpModifier,&QSpinBox::valueChanged,this,&MainWindow::calculateWP);
    connect(ui->healthModifier,&QSpinBox::valueChanged,this,&MainWindow::calculateHealth);


    connect(ui->menuChange_Language, &QMenu::triggered,this, &MainWindow::slotLanguageChanged);
    humanityGenerator();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::slotLanguageChanged(QAction *action)
{
    QTranslator translator;
    if(action->objectName() == "actionPolish")
    {
        const QString baseName = "VtM_sheet_pl_PL";
        if (translator.load(":/i18n/" + baseName)) {
            QCoreApplication::installTranslator(&translator);
            setLocale(QLocale::Polish);
        }
    }
    else if(action->objectName() == "actionEnglish")
    {
            const QString baseName = "VtM_sheet_en_US";
            if (translator.load(":/i18n/" + baseName)) {
                QCoreApplication::installTranslator(&translator);
                setLocale(QLocale::English);
            }
    }
    ui->retranslateUi(this);
}

void MainWindow::deleteHealth(int size_)
{
    for(int i = 0; i < size_; i++)
    {
        ui->Health->itemAt(i)->widget()->deleteLater();
    }

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
    }
}
void MainWindow::deleteWP(int size_)
{
    for(int i = 0; i < size_; i++)
    {
        ui->Willpower->itemAt(i)->widget()->deleteLater();
    }
}

void MainWindow::calculateWP()
{
    if(synchro)//najdwidoczniej sygnał mi się z jakiegoś powodu dubluje i pula nie jest usuwana jesli wczytam dwukrotnie plik
    {//ale to w sumie generuje nowy błąd przez co tylko co druga modyfikacja jest pokazywana
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
        synchro = false;//semafor powinien rozwiazac sprawe
    }
    else
    {
        synchro = true;
    }
}
void MainWindow::calculateHealth()
{
    deleteHealth(healthPool);
    healthPool = 3 + countDots(ui->Sta) + ui->healthModifier->value();
    if(healthPool < 0)
        healthPool = 0;
//    for(QAbstractButton *but : bt->group()->buttons())
//    {
//        if(but->isChecked())
//            healthPool++;
//    }
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


void MainWindow::clear()
{
    for(QAbstractButton *bt : ui->buttonGroup->buttons())
    {
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(0)->widget());
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
    for(QAbstractButton *bt : ui->buttonGroup_2->buttons())
    {
        QJsonObject skill;
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
}

void MainWindow::createDices(int size_)
{
    for(int i = 0; i < size_; i++)
    {

        QCheckBox *dynCheck = new QCheckBox();
        QVBoxLayout *dynLayout = new QVBoxLayout();
        dynLayout->setAlignment(Qt::AlignCenter);
        QLabel *dynLabel = new QLabel(QString::number(QRandomGenerator::system()->bounded(10) + 1));
        dynLabel->setStyleSheet("QLabel { font-size : 20px;}");
        dynCheck->setObjectName("czek" + QString::number(i));
        dynCheck->setCheckable(true);
        if(i > counter - hunger - 1)
        {
            dynLabel->setStyleSheet("QLabel { color : red; font-size : 20px;}");
//            dynCheck->setCheckable(false);
//            dynCheck->setEnabled(false);    pod pewnymi warunkami mozna je przerzucac
        }
        dynLayout->addWidget(dynLabel);
        dynLayout->addWidget(dynCheck);
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
            QLabel *lb = qobject_cast<QLabel *>(ui->Rolls->itemAt(i)->layout()->itemAt(0)->widget());
            lb->setText(QString::number(QRandomGenerator::system()->bounded(10) + 1));
            if(lb->styleSheet() == "QLabel { color : red; font-size : 20px;}"){
                lb->setStyleSheet("QLabel { color : purple; font-size: 20px;}");
            }
            else lb->setStyleSheet(" QLabel{color : blue; font-size : 20px;}");
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
        QAbstractButton * but = qobject_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(0)->widget());
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
        json[line->text()] = *array;
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
    willpowerPoints["modifier"] = QString::number(ui->healthModifier->value());
    willpowerPoints["superficial"] = QString::number(countIndicators(ui->Willpower, willpowerPool).first);
    willpowerPoints["agravated"] = QString::number(countIndicators(ui->Willpower, willpowerPool).second);
    array->append(willpowerPoints);
    json["Willpower"] = *array;
    json["Humanity"] = QString::number(countIndicators(ui->HumanityLayout,10).second);
    delete array;

    return json;
}
void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,QObject::tr("Save File"),QDir::currentPath(),QObject::tr("Save files (*.json);"));
    if(filename.isEmpty())
    {
        qWarning() << "Couldn't Save";
        return;
    }
    QFile saveFile(filename);
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
    MainWindow::setWindowTitle(QFileInfo(filename).baseName());

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
    int keyIndex = 0;
    if(json.contains("Discipline") && json["Discipline"].isArray())
    {
        QJsonArray array = json["Discipline"].toArray();
        for(QAbstractButton *bt : ui->buttonGroup_3->buttons())
        {
            QString key = array.first().toObject().keys().at(keyIndex);
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
            keyIndex++;
        }
        return true;
    }
    return false;
}

void MainWindow::on_actionOpen_triggered()
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
}

void MainWindow::dynamicDiscpilineCreator(QAbstractButton *bt)
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


