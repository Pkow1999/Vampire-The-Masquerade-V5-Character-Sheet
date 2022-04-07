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
    qDebug() << action->objectName();
    qDebug() << QLocale().name();
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




void MainWindow::on_pushButton_clicked()
{
    for(int i = 0; i < counter; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            ui->Rolls->itemAt(i)->layout()->itemAt(j)->widget()->deleteLater();
        }
        ui->Rolls->itemAt(i)->layout()->deleteLater();
    }

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
    for(int i = 0; i < counter; i++)
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
    for(QAbstractButton *bt : ui->buttonGroup->buttons())
    {
        QAbstractButton * but = static_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(0)->widget());
        int dots = countDots(but->group());
        json[bt->text()] = QString::number(dots);
    }
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
    }
    if (!saveFile.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open save file.");
            return;
        }
    saveFile.write(QJsonDocument(json).toJson());
    saveFile.close();
}


void MainWindow::on_actionOpen_triggered()
{

   QString filename = QFileDialog::getOpenFileName(nullptr,QObject::tr("Open Save"),QDir::currentPath(),QObject::tr("Save files (*.json);"));
   clear();
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
   for(QAbstractButton *bt : ui->buttonGroup->buttons())
   {
       if(json.contains(bt->text()) && json[bt->text()].isString())
       {
           int dots = json[bt->text()].toString().toInt();
           if(dots > 0)
           {
               QAbstractButton * but = static_cast<QAbstractButton *>(findParentLayout(bt)->itemAt(1)->layout()->itemAt(dots - 1)->widget());
               but->click();
           }
       }
   }

   for(QAbstractButton *bt : ui->buttonGroup_2->buttons())
   {
       if(json.contains(bt->text()) && json[bt->text()].isArray())
       {
           QJsonArray skillsArray = json[bt->text()].toArray();
           int dots = skillsArray.first()["dots"].toString().toInt();
           if(dots > 0)
           {
               QLayout *lay = findParentLayout(bt);
               QLineEdit *line = static_cast<QLineEdit *>(lay->itemAt(1)->widget());
               line->setText(skillsArray.first()["specialization"].toString());
               QAbstractButton * but = static_cast<QAbstractButton *>(lay->itemAt(2)->layout()->itemAt(dots - 1)->widget());
               but->click();
           }
       }
   }
}


