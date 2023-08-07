#ifndef CLANWINDOW_H
#define CLANWINDOW_H

#include <QFrame>

namespace Ui {
class ClanWindow;
}

class ClanWindow : public QFrame
{
    Q_OBJECT

public:
    explicit ClanWindow(QWidget *parent = nullptr);
    ~ClanWindow();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_toggled(bool checked);

private:
    Ui::ClanWindow *ui;
    QPixmap pic;

};

#endif // CLANWINDOW_H
