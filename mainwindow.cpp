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
            qDebug() << i;
        }
        qDebug() << "END";
    }
}


