QT += gui core

CONFIG += c++17 console
CONFIG -= app_bundle

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
    convolutionalheronfield.cpp \
    chflayer.cpp \
    tensor.cpp \
    convlayer.cpp \
    maxpoolinglayer.cpp \
    chnetwork.cpp \
    filemanager.cpp

HEADERS += \
    heron.h \
    heronfield.h \
    imagedecorder.h \
    numberrecognizer.h \
    convolutionalheronfield.h \
    chflayer.h \
    tensor.h \
    convlayer.h \
    maxpoolinglayer.h \
    chnetwork.h \
    filemanager.h

DISTFILES += \
    data/nums/Arial_0.bmp \
    data/nums/Arial_1.bmp \
    data/nums/Arial_2.bmp \
    data/nums/Arial_3.bmp \
    data/nums/Arial_4.bmp \
    data/nums/Arial_5.bmp \
    data/nums/Arial_6.bmp \
    data/nums/Arial_7.bmp \
    data/nums/Arial_8.bmp \
    data/nums/Arial_9.bmp \
    data/nums/Bookman Old Style_0.bmp \
    data/nums/Bookman Old Style_1.bmp \
    data/nums/Bookman Old Style_2.bmp \
    data/nums/Bookman Old Style_3.bmp \
    data/nums/Bookman Old Style_4.bmp \
    data/nums/Bookman Old Style_5.bmp \
    data/nums/Bookman Old Style_6.bmp \
    data/nums/Bookman Old Style_7.bmp \
    data/nums/Bookman Old Style_8.bmp \
    data/nums/Bookman Old Style_9.bmp \
    data/nums/Calibri_0.bmp \
    data/nums/Calibri_1.bmp \
    data/nums/Calibri_2.bmp \
    data/nums/Calibri_3.bmp \
    data/nums/Calibri_4.bmp \
    data/nums/Calibri_5.bmp \
    data/nums/Calibri_6.bmp \
    data/nums/Calibri_7.bmp \
    data/nums/Calibri_8.bmp \
    data/nums/Calibri_9.bmp \
    data/nums/Cambria_0.bmp \
    data/nums/Cambria_1.bmp \
    data/nums/Cambria_2.bmp \
    data/nums/Cambria_3.bmp \
    data/nums/Cambria_4.bmp \
    data/nums/Cambria_5.bmp \
    data/nums/Cambria_6.bmp \
    data/nums/Cambria_7.bmp \
    data/nums/Cambria_8.bmp \
    data/nums/Cambria_9.bmp \
    data/nums/Century_0.bmp \
    data/nums/Century_1.bmp \
    data/nums/Century_2.bmp \
    data/nums/Century_3.bmp \
    data/nums/Century_4.bmp \
    data/nums/Century_5.bmp \
    data/nums/Century_6.bmp \
    data/nums/Century_7.bmp \
    data/nums/Century_8.bmp \
    data/nums/Century_9.bmp \
    data/nums/Comic Sans MS_0.bmp \
    data/nums/Comic Sans MS_1.bmp \
    data/nums/Comic Sans MS_2.bmp \
    data/nums/Comic Sans MS_3.bmp \
    data/nums/Comic Sans MS_4.bmp \
    data/nums/Comic Sans MS_5.bmp \
    data/nums/Comic Sans MS_6.bmp \
    data/nums/Comic Sans MS_7.bmp \
    data/nums/Comic Sans MS_8.bmp \
    data/nums/Comic Sans MS_9.bmp \
    data/nums/Consolas_0.bmp \
    data/nums/Consolas_1.bmp \
    data/nums/Consolas_2.bmp \
    data/nums/Consolas_3.bmp \
    data/nums/Consolas_4.bmp \
    data/nums/Consolas_5.bmp \
    data/nums/Consolas_6.bmp \
    data/nums/Consolas_7.bmp \
    data/nums/Consolas_8.bmp \
    data/nums/Consolas_9.bmp \
    data/nums/Impact_0.bmp \
    data/nums/Impact_1.bmp \
    data/nums/Impact_2.bmp \
    data/nums/Impact_3.bmp \
    data/nums/Impact_4.bmp \
    data/nums/Impact_5.bmp \
    data/nums/Impact_6.bmp \
    data/nums/Impact_7.bmp \
    data/nums/Impact_8.bmp \
    data/nums/Impact_9.bmp \
    data/nums/Informal Roman_0.bmp \
    data/nums/Informal Roman_1.bmp \
    data/nums/Informal Roman_2.bmp \
    data/nums/Informal Roman_3.bmp \
    data/nums/Informal Roman_4.bmp \
    data/nums/Informal Roman_5.bmp \
    data/nums/Informal Roman_6.bmp \
    data/nums/Informal Roman_7.bmp \
    data/nums/Informal Roman_8.bmp \
    data/nums/Informal Roman_9.bmp \
    data/nums/Kristen ITC_0.bmp \
    data/nums/Kristen ITC_1.bmp \
    data/nums/Kristen ITC_2.bmp \
    data/nums/Kristen ITC_3.bmp \
    data/nums/Kristen ITC_4.bmp \
    data/nums/Kristen ITC_5.bmp \
    data/nums/Kristen ITC_6.bmp \
    data/nums/Kristen ITC_7.bmp \
    data/nums/Kristen ITC_8.bmp \
    data/nums/Kristen ITC_9.bmp \
    data/nums/Lucida Fax_0.bmp \
    data/nums/Lucida Fax_1.bmp \
    data/nums/Lucida Fax_2.bmp \
    data/nums/Lucida Fax_3.bmp \
    data/nums/Lucida Fax_4.bmp \
    data/nums/Lucida Fax_5.bmp \
    data/nums/Lucida Fax_6.bmp \
    data/nums/Lucida Fax_7.bmp \
    data/nums/Lucida Fax_8.bmp \
    data/nums/Lucida Fax_9.bmp \
    data/nums/Maiandra GD_0.bmp \
    data/nums/Maiandra GD_1.bmp \
    data/nums/Maiandra GD_2.bmp \
    data/nums/Maiandra GD_3.bmp \
    data/nums/Maiandra GD_4.bmp \
    data/nums/Maiandra GD_5.bmp \
    data/nums/Maiandra GD_6.bmp \
    data/nums/Maiandra GD_7.bmp \
    data/nums/Maiandra GD_8.bmp \
    data/nums/Maiandra GD_9.bmp \
    data/nums/Microsoft JhengHei_0.bmp \
    data/nums/Microsoft JhengHei_1.bmp \
    data/nums/Microsoft JhengHei_2.bmp \
    data/nums/Microsoft JhengHei_3.bmp \
    data/nums/Microsoft JhengHei_4.bmp \
    data/nums/Microsoft JhengHei_5.bmp \
    data/nums/Microsoft JhengHei_6.bmp \
    data/nums/Microsoft JhengHei_7.bmp \
    data/nums/Microsoft JhengHei_8.bmp \
    data/nums/Microsoft JhengHei_9.bmp \
    data/nums/Microsoft Sans Serif_0.bmp \
    data/nums/Microsoft Sans Serif_1.bmp \
    data/nums/Microsoft Sans Serif_2.bmp \
    data/nums/Microsoft Sans Serif_3.bmp \
    data/nums/Microsoft Sans Serif_4.bmp \
    data/nums/Microsoft Sans Serif_5.bmp \
    data/nums/Microsoft Sans Serif_6.bmp \
    data/nums/Microsoft Sans Serif_7.bmp \
    data/nums/Microsoft Sans Serif_8.bmp \
    data/nums/Microsoft Sans Serif_9.bmp \
    data/nums/Poor Richard_0.bmp \
    data/nums/Poor Richard_1.bmp \
    data/nums/Poor Richard_2.bmp \
    data/nums/Poor Richard_3.bmp \
    data/nums/Poor Richard_4.bmp \
    data/nums/Poor Richard_5.bmp \
    data/nums/Poor Richard_6.bmp \
    data/nums/Poor Richard_7.bmp \
    data/nums/Poor Richard_8.bmp \
    data/nums/Poor Richard_9.bmp \
    data/nums/Segoe UI_0.bmp \
    data/nums/Segoe UI_1.bmp \
    data/nums/Segoe UI_2.bmp \
    data/nums/Segoe UI_3.bmp \
    data/nums/Segoe UI_4.bmp \
    data/nums/Segoe UI_5.bmp \
    data/nums/Segoe UI_6.bmp \
    data/nums/Segoe UI_7.bmp \
    data/nums/Segoe UI_8.bmp \
    data/nums/Segoe UI_9.bmp \
    data/nums/SimSun_0.bmp \
    data/nums/SimSun_1.bmp \
    data/nums/SimSun_2.bmp \
    data/nums/SimSun_3.bmp \
    data/nums/SimSun_4.bmp \
    data/nums/SimSun_5.bmp \
    data/nums/SimSun_6.bmp \
    data/nums/SimSun_7.bmp \
    data/nums/SimSun_8.bmp \
    data/nums/SimSun_9.bmp \
    data/nums/Symbol_0.bmp \
    data/nums/Symbol_1.bmp \
    data/nums/Symbol_2.bmp \
    data/nums/Symbol_3.bmp \
    data/nums/Symbol_4.bmp \
    data/nums/Symbol_5.bmp \
    data/nums/Symbol_6.bmp \
    data/nums/Symbol_7.bmp \
    data/nums/Symbol_8.bmp \
    data/nums/Symbol_9.bmp \
    data/nums/Tahoma_0.bmp \
    data/nums/Tahoma_1.bmp \
    data/nums/Tahoma_2.bmp \
    data/nums/Tahoma_3.bmp \
    data/nums/Tahoma_4.bmp \
    data/nums/Tahoma_5.bmp \
    data/nums/Tahoma_6.bmp \
    data/nums/Tahoma_7.bmp \
    data/nums/Tahoma_8.bmp \
    data/nums/Tahoma_9.bmp \
    data/nums/Times_0.bmp \
    data/nums/Times_1.bmp \
    data/nums/Times_2.bmp \
    data/nums/Times_3.bmp \
    data/nums/Times_4.bmp \
    data/nums/Times_5.bmp \
    data/nums/Times_6.bmp \
    data/nums/Times_7.bmp \
    data/nums/Times_8.bmp \
    data/nums/Times_9.bmp \
    data/nums/Verdana_0.bmp \
    data/nums/Verdana_1.bmp \
    data/nums/Verdana_2.bmp \
    data/nums/Verdana_3.bmp \
    data/nums/Verdana_4.bmp \
    data/nums/Verdana_5.bmp \
    data/nums/Verdana_6.bmp \
    data/nums/Verdana_7.bmp \
    data/nums/Verdana_8.bmp \
    data/nums/Verdana_9.bmp
