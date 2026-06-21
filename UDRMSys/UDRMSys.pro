QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dormitory.cpp \
    DormitoryException.cpp \
    Meal.cpp \
    Menu.cpp \
    Person.cpp \
    Restaurant.cpp \
    Room.cpp \
    Student.cpp \
    University.cpp \
    main.cpp \
    mainwindow.cpp \
    restaurantdialog.cpp \
    studentdialog.cpp

HEADERS += \
    Dormitory.h \
    DormitoryException.h \
    Meal.h \
    Menu.h \
    Person.h \
    Restaurant.h \
    Room.h \
    Student.h \
    University.h \
    mainwindow.h \
    restaurantdialog.h \
    studentdialog.h

FORMS += \
    mainwindow.ui \
    restaurantdialog.ui \
    studentdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
