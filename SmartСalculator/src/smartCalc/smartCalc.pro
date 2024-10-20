QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES +=  main.cpp \
    creditcalc.cpp \
    graph.cpp \
    mainwindow.cpp \
      ../s21_calc.c \
      ../s21_stack.c \
      ../s21_creditcalc.c\
     ../s21_calc_X.c \
    qcustomplot.cpp


HEADERS += mainwindow.h\
      ../s21_calc.h \
      ../s21_stack.h \
      creditcalc.h \
      graph.h \
      qcustomplot.h

FORMS += \
    creditcalc.ui \
    graph.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
