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
    connect(ui->Str,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->Dex,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->Sta,&QButtonGroup::buttonClicked,this,&MainWindow::func);

    connect(ui->Chr,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->Com,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->Man,&QButtonGroup::buttonClicked,this,&MainWindow::func);

    connect(ui->Int,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->Wit,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->Res,&QButtonGroup::buttonClicked,this,&MainWindow::func);

    connect(ui->TalentsGroup,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_2,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_3,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_4,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_5,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_6,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_7,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_8,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_9,&QButtonGroup::buttonClicked,this,&MainWindow::func);

    connect(ui->TalentsGroup_10,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_11,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_12,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_13,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_14,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_15,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_16,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_17,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_18,&QButtonGroup::buttonClicked,this,&MainWindow::func);

    connect(ui->TalentsGroup_19,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_20,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_21,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_22,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_23,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_24,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_25,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_26,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->TalentsGroup_27,&QButtonGroup::buttonClicked,this,&MainWindow::func);
    connect(ui->Hunger,&QButtonGroup::buttonClicked,this,&MainWindow::func);

    connect(ui->menuChange_Language, &QMenu::triggered,this, &MainWindow::slotLanguageChanged);
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

void MainWindow::func(QAbstractButton *bt)
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
        QAbstractButton * but = static_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(0)->widget());
        for(QAbstractButton *dot : but->group()->buttons())
        {
            dot->setChecked(false);
        }
    }
    for(QAbstractButton *bt : ui->buttonGroup_2->buttons())
    {
        QJsonObject skill;
        QAbstractButton * but = static_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
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
            dynCheck->setCheckable(false);
            dynCheck->setEnabled(false);
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

void MainWindow::on_pushButton_clicked()
{
    deleteDices(counter);
    counter = 0;
    hunger = countDots(ui->Hunger);

    for(int i = 0; i < ui->buttonGroup->buttons().size(); i++)
    {
        if(ui->buttonGroup->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest drugi element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = static_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup->buttons().at(i)->focusWidget())->layout()->itemAt(1)->layout()->itemAt(0)->widget());
            counter += countDots(bt->group());
        }
    }

    for(int i = 0; i < ui->buttonGroup_2->buttons().size(); i++)
    {
        if(ui->buttonGroup_2->buttons().at(i)->isChecked())
        {
            //znajdujemy dokladnego parrenta naszego przycisku, nastepnie sprawdzamy jaki jest trzeci(!) element (ktorym sa radio buttony) i z tych radio buttonow przechodzimy na do grupy ktora tworza aby zliczyc ile sie swieci
            QAbstractButton * bt = static_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup_2->buttons().at(i)->focusWidget())->layout()->itemAt(2)->layout()->itemAt(0)->widget());
            counter += countDots(bt->group());
        }
    }

    counter += ui->spinBox->value();
    ui->label_2->setText(QString::number(counter) + tr(" Dices"));
    createDices(counter);
}



void MainWindow::on_pushButton_2_clicked()
{
    for(int i = 0; i < counter - hunger; i++)
    {
        QAbstractButton *bt = static_cast<QAbstractButton *>(ui->Rolls->itemAt(i)->layout()->itemAt(1)->widget());
        if(bt->isChecked())
        {
            QLabel *lb = static_cast<QLabel *>(ui->Rolls->itemAt(i)->layout()->itemAt(0)->widget());
            lb->setText(QString::number(QRandomGenerator::system()->bounded(10) + 1));
        }
    }
}

QJsonObject MainWindow::saveSkills()
{
    QJsonObject json;
    for(QAbstractButton *bt : ui->buttonGroup_2->buttons())
    {
        QJsonObject skill;
        QAbstractButton * but = static_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(2)->layout()->itemAt(0)->widget());
        QLineEdit * line = static_cast<QLineEdit *>(findParentLayout(bt)->itemAt(1)->widget());
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
        QAbstractButton * but = static_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(0)->widget());
        int dots = countDots(but->group());
        json[bt->text()] = QString::number(dots);
    }
    return json;
}
QJsonObject MainWindow::saveRest()
{
    QJsonObject json;
    QLabel *hungerLabel = static_cast<QLabel *>(ui->verticalLayout_4->itemAt(0)->widget());
    json[hungerLabel->text()] = QString::number(countDots(ui->Hunger));
    json["LANGUAGEOPTION"] = locale().languageToString(locale().language());
    return json;
}
void MainWindow::on_actionSave_triggered()
{
    QString filename = QFileDialog::getSaveFileName(nullptr,QObject::tr("Save File"),QDir::currentPath(),QObject::tr("Save files (*.json);"));
    if(filename.isEmpty())
    {
        qWarning() << "Couldn't Save";
        return;
    }
    QFile saveFile(filename);
    QJsonObject json;

    QJsonArray *array = new QJsonArray();
    array->append(saveAttributes());
    json["Attributes"] = *array;
    array->pop_back();

    array->append(saveSkills());
    json["Skills"] = *array;
    array->pop_back();

    array->append(saveRest());
    json["Rest"] = *array;
    delete array;


    if (!saveFile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }
    saveFile.write(QJsonDocument(json).toJson());
    saveFile.close();
}
bool MainWindow::loadRest(QJsonObject json)
{
    if(json.contains("Rest") && json["Rest"].isArray())
    {
        QJsonArray restArray = json["Rest"].toArray();
        if(restArray.first()["LANGUAGEOPTION"].isString())
        {
            if(restArray.first()["LANGUAGEOPTION"].toString() == "Polish")
                ui->actionPolish->trigger();
            if(restArray.first()["LANGUAGEOPTION"].toString() == "English")
                ui->actionEnglish->trigger();
        }

        QLabel *hungerLabel = static_cast<QLabel *>(ui->verticalLayout_4->itemAt(0)->widget());
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

                    QAbstractButton * but = static_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(dots - 1)->widget());
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
                    QLineEdit *line = static_cast<QLineEdit *>(lay->itemAt(1)->widget());
                    line->setText(skillArray.first()["specialization"].toString());
                    QAbstractButton * but = static_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
                    but->click();
                }
            }
        }
        return true;
    }
    return false;
}

void MainWindow::on_actionOpen_triggered()
{

   QString filename = QFileDialog::getOpenFileName(nullptr,QObject::tr("Open Save"),QDir::currentPath(),QObject::tr("Save files (*.json);"));
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
   if(!loadRest(json))
   {
       qWarning("Couldn't load Language/Hunger");
       return;
   }
   if(!loadAttributes(json))
   {
       qWarning("Couldn't load Attributes");
       return;
   }
   if(!loadSkills(json))
   {
       qWarning("Couldn't load Skills");
       return;
   }
}


