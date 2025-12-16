#include "disciplinewindow.h"
#include "ui_disciplinewindow.h"

#include <QDirIterator>
#include <QMouseEvent>

DisciplineWindow::DisciplineWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisciplineWindow)
{
    ui->setupUi(this);
    windowSize = this->size();
    currentPictureRealSize = windowSize;
    lastPictureRealSize = windowSize;
    qWarning() << "C-tor";
    on_discipline_currentIndexChanged(0);
    defaultPictureRealSize = this->currentPicture.size();
}

void DisciplineWindow::loadImages()
{
    QString absolutePath(path);
    absolutePath.append(ui->discipline->currentText()).append('/');
    QDirIterator it(absolutePath, QStringList() << "*.png", QDir::NoFilter, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto picturePath = it.next();
        listOfPicturesPath.push_back(picturePath);
        QFileInfo info(picturePath);
        ui->power->addItem(info.baseName());
    }
}
DisciplineWindow::~DisciplineWindow()
{
    qWarning() <<"Usuwanko";
    delete ui;
}

void DisciplineWindow::resizeEvent(QResizeEvent *event)
{
    currentPictureRealSize = event->size();
    QWidget::resizeEvent(event);
}

void DisciplineWindow::closeEvent(QCloseEvent *event)
{
    qWarning() << "UCIECZKA";
}

void DisciplineWindow::on_discipline_currentIndexChanged(int index)
{
    qWarning() << "Index Changed";
    ui->power->clear();
    qWarning() <<"CLEAR 1";
    listOfPicturesPath.clear();
    qWarning() << "CLEAR 2";

    loadImages();
    if (listOfPicturesPath.empty())
        return;

    currentPicture.load(listOfPicturesPath.front());
    if(currentPicture.size().width() > lastPictureRealSize.width()
        && currentPicture.size().height() == lastPictureRealSize.height())
    {
        this->resize(2 * windowSize.width(), windowSize.height());
    }

    ui->picture->setPixmap(currentPicture);
    ui->picture->setScaledContents(true);
    ui->picture->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    ui->power->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    ui->power->adjustSize();

    this->resize(currentPictureRealSize);
}

void DisciplineWindow::on_power_currentIndexChanged(int index)
{
    qWarning() << index;
    if(index > listOfPicturesPath.size() - 1 || index < 0)
        return;

    lastPictureRealSize = currentPicture.size();
    currentPicture.load(listOfPicturesPath.at(index));

    qDebug() << "DEFAULT SIZE: " << windowSize;
    {
        if(currentPicture.size().width() > lastPictureRealSize.width()
            && currentPicture.size().height() <= lastPictureRealSize.height())
        {
            qDebug() << "WIEKSZE";
            defaultPictureRealSize = lastPictureRealSize;
            this->resize(2 * currentPictureRealSize.width(), currentPictureRealSize.height());
        }
        else if(currentPicture.size().width() < lastPictureRealSize.width()
                 && currentPicture.size().height() >= lastPictureRealSize.height())
        {
            qDebug() << "ZMNIEJSZ";
            defaultPictureRealSize = currentPicture.size();
            this->resize(currentPictureRealSize.width() / 2,currentPictureRealSize.height());
        }
        else
        {
            qDebug() << "ZOSTAW";
            //this->resize(currentSize);
        }
    }
    ui->picture->setPixmap(currentPicture);
}

void DisciplineWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(currentPicture.size().width() > defaultPictureRealSize.width()
            && currentPicture.size().height() == defaultPictureRealSize.height()){
            this->resize(2 * windowSize.width(), windowSize.height());
        }
        else{
            this->resize(windowSize);
        }
    }
}

