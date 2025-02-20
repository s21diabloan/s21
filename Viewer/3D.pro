QT += core gui opengl widgets openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    objcontroller.cpp \
    objmodel.cpp \
    objview.cpp \
    ./giflib/gif.cpp \
    reset_command.cpp \
    sourses/movetransformationstrategy.cpp \
    sourses/rotatetransformationstrategy.cpp \
    sourses/scaletransformationstrategy.cpp \
    sourses/settingsfacade.cpp

HEADERS += \
    mainwindow.h \
    objcontroller.h \
    objmodel.h \
    objview.h \
    ./giflib/gif.hpp \
    reset_command.hpp \
    sourses/movetransformationstrategy.h \
    sourses/rotatetransformationstrategy.h \
    sourses/scaletransformationstrategy.h \
    sourses/settingsfacade.h \
    sourses/transformationstrategy.h

FORMS += \
    mainwindow.ui

# Настройки для Windows (для OpenGL)
win32: LIBS += -lopengl32 -lglu32

# Настройки для UNIX-подобных систем (Linux и macOS)
unix: LIBS += -lGL -lGLU

# Настройки компиляции и линковки
INCLUDEPATH += .
DEPENDPATH += .

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
