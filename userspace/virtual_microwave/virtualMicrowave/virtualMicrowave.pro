QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../src/displayControl/displayControl.cpp \
    ../../src/microwave/microwave.cpp \
    ../../src/states/IMState.cpp \
    ../../src/states/cooking.cpp \
    ../../src/states/idle.cpp \
    ../../src/states/init.cpp \
    ../../src/states/memorySetup.cpp \
    ../../src/states/timeSetup.cpp \
    ../../src/utils/bounce.cpp \
    ../../src/utils/logging.cpp \
    ../../src/utils/memoryHandler.cpp \
    ../../src/utils/utils.cpp \
    main.cpp \
    virtualMicrowave.cpp

HEADERS += \
    ../../src/displayControl/displayControl.h \
    ../../src/event.h \
    ../../src/hardware/display_abstraction.h \
    ../../src/hardware/memory_abstraction.h \
    ../../src/hardware/statusChecker_abstraction.h \
    ../../src/microwave/microwave.h \
    ../../src/states/IMState.h \
    ../../src/states/cooking.h \
    ../../src/states/idle.h \
    ../../src/states/init.h \
    ../../src/states/memorySetup.h \
    ../../src/states/timeSetup.h \
    ../../src/utils/bounce.h \
    ../../src/utils/logging.h \
    ../../src/utils/memoryHandler.h \
    ../../src/utils/utils.h \
    virtualMicrowave.h

FORMS += \
    virtualMicrowave.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
