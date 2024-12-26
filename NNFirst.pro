#QT += gui core widgets


QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NNFirst
TEMPLATE = app
#CONFIG += c++17 console
#CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
`
SOURCES += \
        main.cpp \
    heron.cpp \
    heronfield.cpp \
    imagedecorder.cpp \
    numberrecognizer.cpp \
    tensor.cpp \
    convlayer.cpp \
    maxpoolinglayer.cpp \
    chnetwork.cpp \
    filemanager.cpp \
    resultviewer.cpp

HEADERS += \
    heron.h \
    heronfield.h \
    imagedecorder.h \
    numberrecognizer.h \
    tensor.h \
    convlayer.h \
    maxpoolinglayer.h \
    chnetwork.h \
    filemanager.h \
    resultviewer.h












DISTFILES += \
    data/convData.txt \
    data/heronFieldData.txt

