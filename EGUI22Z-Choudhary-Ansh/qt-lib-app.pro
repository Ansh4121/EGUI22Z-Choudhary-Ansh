QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    book.cpp \
    dashboard.cpp \
    details.cpp \
    main.cpp \
    login.cpp \
    register.cpp \
    user.cpp

HEADERS += \
    admin.h \
    book.h \
    dashboard.h \
    details.h \
    json.hpp \
    login.h \
    register.h \
    user.h

FORMS += \
    admin.ui \
    dashboard.ui \
    details.ui \
    login.ui \
    register.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    users.json \
    books.json
