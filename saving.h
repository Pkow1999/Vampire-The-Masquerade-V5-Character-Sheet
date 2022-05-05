#ifndef SAVING_H
#define SAVING_H

#include <QJsonObject>
#include "mainwindow.h"


class Saving
{
public:
    Saving();
    QJsonObject saveAttributes(MainWindow *ui);
};

#endif // SAVING_H
