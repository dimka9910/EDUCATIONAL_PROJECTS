QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += printsupport

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    analysiswindow.cpp \
    datamanager.cpp \
    digitalfiltersdialog.cpp \
    dspFilters/Bessel.cpp \
    dspFilters/Biquad.cpp \
    dspFilters/Butterworth.cpp \
    dspFilters/Cascade.cpp \
    dspFilters/ChebyshevI.cpp \
    dspFilters/ChebyshevII.cpp \
    dspFilters/Custom.cpp \
    dspFilters/Design.cpp \
    dspFilters/Documentation.cpp \
    dspFilters/Elliptic.cpp \
    dspFilters/Filter.cpp \
    dspFilters/Legendre.cpp \
    dspFilters/Param.cpp \
    dspFilters/PoleFilter.cpp \
    dspFilters/RBJ.cpp \
    dspFilters/RootFinder.cpp \
    dspFilters/State.cpp \
    exqcustomplot.cpp \
    fftdialog.cpp \
    graphitemmodel.cpp \
    kissfft-master/kiss_fft.c \
    main.cpp \
    mainwindow.cpp \
    record.cpp \
    recordstreeview.cpp \
    recordtreemodel.cpp

HEADERS += \
    analysiswindow.h \
    datamanager.h \
    digitalfiltersdialog.h \
    dspFilters/Bessel.h \
    dspFilters/Biquad.h \
    dspFilters/Butterworth.h \
    dspFilters/Cascade.h \
    dspFilters/ChebyshevI.h \
    dspFilters/ChebyshevII.h \
    dspFilters/Common.h \
    dspFilters/Custom.h \
    dspFilters/Design.h \
    dspFilters/Dsp.h \
    dspFilters/Elliptic.h \
    dspFilters/Filter.h \
    dspFilters/Layout.h \
    dspFilters/Legendre.h \
    dspFilters/MathSupplement.h \
    dspFilters/Params.h \
    dspFilters/PoleFilter.h \
    dspFilters/RBJ.h \
    dspFilters/RootFinder.h \
    dspFilters/SmoothedFilter.h \
    dspFilters/State.h \
    dspFilters/Types.h \
    dspFilters/Utilities.h \
    exqcustomplot.h \
    fftdialog.h \
    global.h \
    graphitemmodel.h \
    importfileinterface.h \
    kissfft-master/_kiss_fft_guts.h \
    kissfft-master/kiss_fft.h \
    kissfft-master/kissfft.hh \
    mainwindow.h \
    record.h \
    recordstreeview.h \
    recordtreemodel.h

FORMS += \
    analysiswindow.ui \
    digitalfiltersdialog.ui \
    fftdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    kissfft-master/.gitignore \
    kissfft-master/CHANGELOG \
    kissfft-master/COPYING \
    kissfft-master/README \
    kissfft-master/README.simd \
    kissfft-master/TIPS \
    test15.pro.user
