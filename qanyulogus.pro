# -*- mode: makefile -*-
#
# QAnyulogus, by Peter Salvi (2008)
#
# Time-stamp: <2008.03.17., 13:47:18 (salvi)>

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += main-window.hh qanyulogus.hh
SOURCES += main.cc main-window.cc qanyulogus.cc
RESOURCES = qanyulogus.qrc
