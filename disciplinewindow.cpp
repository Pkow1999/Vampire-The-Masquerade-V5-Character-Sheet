#include "disciplinewindow.h"
#include "ui_disciplinewindow.h"

#include <QDirIterator>
#include <QMouseEvent>

DisciplineWindow::DisciplineWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DisciplineWindow)
{
    ui->setupUi(this);
    defaultSize = this->size();
    currentSize = defaultSize;
    lastPicSize = defaultSize;
    qWarning() << "C-tor";
    on_discipline_currentIndexChanged(0);

}

DisciplineWindow::~DisciplineWindow()
{
    qWarning() <<"Usuwanko";
    delete ui;
}

void DisciplineWindow::resizeEvent(QResizeEvent *event)
{
    currentSize = event->size();
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
    Files.clear();
    qWarning() << "CLEAR 2";
    QString absolutePath(path);
    qWarning() << "Path: " << absolutePath.append(ui->discipline->currentText()).append('/');
    QDirIterator it(absolutePath, QStringList() << "*.png", QDir::NoFilter, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        auto item = it.next();
        Files.push_back(item);
        QFileInfo info(item);
        ui->power->addItem(info.baseName());
    }
    qWarning() << "LOADING COMPLETE";
    if (Files.empty())
        return;
    pic.load(Files.front());
    if(pic.size().width() > 933)
    {
        this->resize(2 * defaultSize.width(), defaultSize.height());
    }
    ui->picture->setPixmap(pic);
    ui->picture->setScaledContents(true);
    ui->picture->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->power->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    ui->power->adjustSize();
}

void DisciplineWindow::on_power_currentIndexChanged(int index)
{
    qWarning() << index;
    if(index > Files.size() - 1 || index < 0)
        return;
    lastPicSize = pic.size();
    pic.load(Files.at(index));

    qDebug() << "DEFAULT SIZE: " << defaultSize;
    //if(this->size() == defaultSize || this->size().width() == 2 * defaultSize.width())
    {
        if(pic.size().width() > 933 && lastPicSize.width() == 933)
        {
            qDebug() << "WIEKSZE";
            this->resize(2 * currentSize.width(), currentSize.height());
        }
        else if(pic.size().width() == 933 && lastPicSize.width() > 933)
        {
            qDebug() << "ZMNIEJSZ";
            this->resize(currentSize.width() / 2,currentSize.height());
        }
        else
        {
            qDebug() << "ZOSTAW";
            this->resize(currentSize);
        }
    }
    ui->picture->setPixmap(pic);
}

void DisciplineWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(pic.size().width() > 933){
            this->resize(2 * defaultSize.width(), defaultSize.height());
        }
        else{
            this->resize(defaultSize);
        }
    }
}

