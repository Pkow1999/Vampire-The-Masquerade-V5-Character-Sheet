QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

QT += network
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = ankh.ico

SOURCES += \
    src/clanwindow.cpp \
    src/disciplinewindow.cpp \
    src/main.cpp \
    src/noteswindow.cpp \
    src/discordconfig.cpp \
    src/discordsender.cpp \
    src/mainwindow.cpp \
    src/statsmanager.cpp

HEADERS += \
    src/rollstatus.hpp \
    src/errorcodes.hpp \
    src/clanwindow.h \
    src/disciplinewindow.h \
    src/noteswindow.h \
    src/discordconfig.h \
    src/discordsender.h \
    src/mainwindow.h \
    src/statsmanager.h

FORMS += \
    src/clanwindow.ui \
    src/disciplinewindow.ui \
    src/noteswindow.ui \
    src/mainwindow.ui

TRANSLATIONS += \
    VtM_sheet_pl_PL.ts \
    VtM_sheet_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES = resources.qrc
DISTFILES += \
    VtM_sheet_en_US.ts \
    ankh.ico \
