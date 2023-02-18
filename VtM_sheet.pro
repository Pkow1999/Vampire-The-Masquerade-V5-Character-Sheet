QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = ankh.ico

SOURCES += \
    clanwindow.cpp \
    disciplinewindow.cpp \
    main.cpp \
    noteswindow.cpp \
    mainwindow.cpp

HEADERS += \
    clanwindow.h \
    disciplinewindow.h \
    noteswindow.h \
    mainwindow.h

FORMS += \
    clanwindow.ui \
    disciplinewindow.ui \
    noteswindow.ui \
    mainwindow.ui

TRANSLATIONS += \
    VtM_sheet_pl_PL.ts \
    VtM_sheet_en_US.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    VtM_sheet_en_US.ts \
    ankh.ico \
    images/Banu Haqim.png \
    images/Brujah.png \
    images/Cienkokrwiści.png \
    images/Gangrel.png \
    images/Hecata.png \
    images/Lasombra.png \
    images/Malkavian.png \
    images/Ministerium.png \
    images/Nosferatu.png \
    images/Parias.png \
    images/Ravnos.png \
    images/Salubri.png \
    images/Torreador.png \
    images/Tremere.png \
    images/Tzimisce.png \
    images/Ventrue.png \
    images/bestial-fail.png \
    images/checkbox_checked.png \
    images/checkbox_checked_hover.png \
    images/checkbox_checked_pressed.png \
    images/checkbox_humanity_checked.png \
    images/checkbox_humanity_checked_hover.png \
    images/checkbox_humanity_checked_pressed.png \
    images/checkbox_indeterminate.png \
    images/checkbox_indeterminate_hover.png \
    images/checkbox_indeterminate_pressed.png \
    images/checkbox_unchecked.png \
    images/checkbox_unchecked_hover.png \
    images/checkbox_unchecked_pressed.png \
    images/normal-crit.png \
    images/normal-fail.png \
    images/normal-success.png \
    images/red-crit.png \
    images/red-fail.png \
    images/red-success.png
