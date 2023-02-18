#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QScreen>
#include <QTranslator>

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "VtM_sheet_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    QSize screenSize = qApp->screens()[0]->size();
    if(screenSize.width() < 1920)
        w.resize(screenSize / 1.5);
    w.show();
    return a.exec();
}
