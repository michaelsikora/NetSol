#-------------------------------------------------
#
# Project created by QtCreator 2018-02-18T05:57:38
#
#-------------------------------------------------

QT       += widgets serialport
requires(qtConfig(combobox))

TARGET = NetsolApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    settingsdialog.cpp \
    console.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    settingsdialog.h \
    console.h \
    mainwindow.h \
    settingsdialog.h \
    xmlsyntaxhighlighter.h

FORMS += \
        mainwindow.ui \
    settingsdialog.ui

RESOURCES += \
    terminal.qrc

# This is an example that was tested for including a third party c++ library
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/soundtouch_dll-1.9.2/ -lSoundTouchDll_x64
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/soundtouch_dll-1.9.2/ -lSoundTouchDll_x64
#else:unix: LIBS += -L$$PWD/../../lib/soundtouch_dll-1.9.2/ -lSoundTouchDll_x64

#INCLUDEPATH += $$PWD/../../lib/soundtouch_dll-1.9.2
#DEPENDPATH += $$PWD/../../lib/soundtouch_dll-1.9.2

#win32:CONFIG(release, debug|release): LIBS += -L"A:/QtApps/BasicResearchApplication/lib/" -llibsndfile-1
#else:win32:CONFIG(debug, debug|release): LIBS += -L"A:/QtApps/BasicResearchApplication/lib/" -llibsndfile-1
#else:unix: LIBS += -L'A:/QtApps/BasicResearchApplication/lib/' -llibsndfile-1

#INCLUDEPATH += $$quote("A:/QtApps/BasicResearchApplication/include")
#DEPENDPATH += $$quote("A:/QtApps/BasicResearchApplication/include")

target.path = A:\QtApps/BasicResearchApplication/bin/
INSTALLS += target

DISTFILES += \
    stylesheet.qss \
    CANconfig.xml
