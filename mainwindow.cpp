#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractButton>
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


}
MainWindow::~MainWindow()
{
    delete ui;
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
QLayout* findParentLayout(QWidget* w, QLayout* topLevelLayout)
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

QLayout* findParentLayout(QWidget* w)
{
    if (w->parentWidget() != nullptr)
        if (w->parentWidget()->layout() != nullptr)
            return findParentLayout(w, w->parentWidget()->layout());
    return nullptr;
}


void MainWindow::on_pushButton_clicked()
{
    int counter = 0;
    for(int i = 0; i < ui->buttonGroup->buttons().size(); i++)
    {
        if(ui->buttonGroup->buttons().at(i)->isChecked())
        {
            QAbstractButton * bt = static_cast<QAbstractButton *>(findParentLayout(ui->buttonGroup->buttons().at(i)->focusWidget())->layout()->itemAt(1)->layout()->itemAt(0)->widget());
            qDebug() << countDots(bt->group());
        }
    }
}

