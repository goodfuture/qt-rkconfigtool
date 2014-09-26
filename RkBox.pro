#-------------------------------------------------
#
# Project created by QtCreator 2014-01-25T16:14:36
#
#-------------------------------------------------

QT       += core gui widgets network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RkBox
TEMPLATE = app


SOURCES += main.cpp\
        dropshadowwidget.cpp \
    mainwindow.cpp \
    pushbutton.cpp \
    titlewidget.cpp \
    toolbutton.cpp \
    statusbar.cpp \
    titlemenu.cpp \
    aboutdialog.cpp \
    systemtray.cpp \
    logindialog.cpp \
    logintitle.cpp \
    loginwidget.cpp \
    loginsettingwidget.cpp \
    loadingwidget.cpp \
    promptwidget.cpp \
    paramsettingwidget.cpp \
    switchbutton.cpp \
    styledtableview.cpp \
    modelbasisconfig.cpp \
    delegatebasisconfig.cpp \
    viewbasisconfig.cpp \
    viewanalogconfig.cpp \
    modelanalogconfig.cpp \
    delegateanalogconfig.cpp \
    checkbox.cpp \
    viewserialconfig.cpp \
    delegateserialconfig.cpp \
    modelserialconfig.cpp \
    viewdioconfig.cpp \
    delegatedioconfig.cpp \
    modeldioconfig.cpp \
    switcher.cpp \
    viewdtuconfig.cpp \
    modeldtuconfig.cpp \
    delegatedtuconfig.cpp \
    delegatenetconfig.cpp \
    modelnetconfig.cpp \
    viewnetconfig.cpp \
    viewcomconfig.cpp \
    modelcomconfig.cpp \
    delegatecomconfig.cpp \
    rtdviewwidget.cpp \
    mainpagewidget.cpp \
    historyviewwidget.cpp \
    dataexportwidget.cpp \
    util.cpp \
    appsettings.cpp \
    messagehandler.cpp \
    rkprotocol.cpp \
    rkcrc.cpp \
    msgbox.cpp \
    thread.cpp \
    dockwidget.cpp \
    dockitemwidget.cpp \
    firmwareupgradedialog.cpp \
    dialog.cpp \
    logolabel.cpp \
    roundbutton.cpp \
    codeeditor.cpp \
    versionlabel.cpp \
    dtuloginwidget.cpp \
    dtuconfigwidget.cpp

HEADERS  += dropshadowwidget.h \
    mainwindow.h \
    common.h \
    pushbutton.h \
    titlewidget.h \
    toolbutton.h \
    statusbar.h \
    titlemenu.h \
    aboutdialog.h \
    systemtray.h \
    logindialog.h \
    logintitle.h \
    loginwidget.h \
    loginsettingwidget.h \
    loadingwidget.h \
    promptwidget.h \
    paramsettingwidget.h \
    switchbutton.h \
    styledtableview.h \
    modelbasisconfig.h \
    delegatebasisconfig.h \
    viewbasisconfig.h \
    viewanalogconfig.h \
    modelanalogconfig.h \
    delegateanalogconfig.h \
    checkbox.h \
    viewserialconfig.h \
    delegateserialconfig.h \
    modelserialconfig.h \
    viewdioconfig.h \
    delegatedioconfig.h \
    modeldioconfig.h \
    switcher.h \
    viewdtuconfig.h \
    modeldtuconfig.h \
    delegatedtuconfig.h \
    delegatenetconfig.h \
    modelnetconfig.h \
    viewnetconfig.h \
    viewcomconfig.h \
    modelcomconfig.h \
    delegatecomconfig.h \
    rtdviewwidget.h \
    mainpagewidget.h \
    historyviewwidget.h \
    dataexportwidget.h \
    util.h \
    appsettings.h \
    messagehandler.h \
    rkprotocol.h \
    rkcrc.h \
    msgbox.h \
    thread.h \
    dockwidget.h \
    dockitemwidget.h \
    firmwareupgradedialog.h \
    dialog.h \
    logolabel.h \
    roundbutton.h \
    codeeditor.h \
    versionlabel.h \
    dtuloginwidget.h \
    dtuconfigwidget.h

RESOURCES += \
    Res/Resource.qrc

TRANSLATIONS += ./Res/RkBoxTr_Zh.ts

FORMS +=

RC_FILE += \
    myapp.rc
