#ifndef DISCIPLINEWINDOW_H
#define DISCIPLINEWINDOW_H

#include "qregularexpression.h"
#include <QWidget>

namespace Ui {
class DisciplineWindow;
}

class DisciplineWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DisciplineWindow(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event);
    ~DisciplineWindow();

private slots:
    void on_discipline_currentIndexChanged(int index);

    void on_power_currentIndexChanged(int index);

private:
    Ui::DisciplineWindow *ui;
    QString path = "images/disciplines/";
    QVector <QString> Files;
    QPixmap pic;
    const QSize defaultSize = QSize(349,505);

    // QWidget interface
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
};

#endif // DISCIPLINEWINDOW_H
