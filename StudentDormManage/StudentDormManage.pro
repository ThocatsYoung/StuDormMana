#-------------------------------------------------
#
# Project created by QtCreator 2017-04-28T21:34:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudentDormManage
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    people.cpp \
    room.cpp \
    student_information_edit_dialog.cpp \
    dormlistmodel.cpp \
    studentlistmodel.cpp \
    formforrulebreakrecord.cpp \
    dialog_rulebreak_add.cpp \
    record_rulebreak.cpp \
    dialog_login.cpp \
    mainwindow_data_manager.cpp \
    read_from_file.cpp \
    dialog_dorm_edit.cpp \
    dialog_user_info.cpp \
    dialog_user_show.cpp

HEADERS  += mainwindow.h \
    people.h \
    room.h \
    student_information_edit_dialog.h \
    dormlistmodel.h \
    studentlistmodel.h \
    formforrulebreakrecord.h \
    dialog_rulebreak_add.h \
    record_rulebreak.h \
    dialog_login.h \
    read_from_file.h \
    mainwindow_data_manager.h \
    dialog_dorm_edit.h \
    dialog_user_info.h \
    dialog_user_show.h

FORMS    += mainwindow.ui \
    student_information_edit_dialog.ui \
    formforrulebreakrecord.ui \
    dialog_rulebreak_add.ui \
    dialog_login.ui \
    mainwindow_data_manager.ui \
    dialog_dorm_edit.ui \
    dialog_user_info.ui \
    dialog_user_show.ui

SUBDIRS += \
    ../StudentClass/StudentClass.pro

RESOURCES +=
