#include "saving.h"
#include <QAbstractButton>

Saving::Saving()
{

}

QJsonObject Saving::saveAttributes(MainWindow *ui)
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
