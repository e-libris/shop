QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

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
    main.cpp \
    mainwindow.cpp \
    src/get_resources.cpp \
    src/item.cpp \
    src/procreceipt.cpp \
    src/receipt.cpp \
    src/reports.cpp

HEADERS += \
    mainwindow.h \
    src/get_resources.h \
    src/item.h \
    src/procreceipt.h \
    src/receipt.h \
    src/reports.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L/usr/lib/release/ -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L/usr/lib/debug/ -lcurl
else:unix: LIBS += -L/usr/lib/ -lcurl

INCLUDEPATH += /usr/include/curl
DEPENDPATH += /usr/include/curl

DISTFILES += \
    categories.txt \
    convert.sh \
    data/20190705.txt \
    data/20190712.txt \
    data/20190719.txt \
    data/20190726.txt \
    data/20190802.txt \
    data/20190809.txt \
    data/20190816.txt \
    data/20190823.txt \
    data/20190830.txt \
    data/20190906.txt \
    data/20190913.txt \
    data/20190920.txt \
    item_descriptions.txt \
    items.db \
    items_mod.db \
    limited.db \
    master.csv
