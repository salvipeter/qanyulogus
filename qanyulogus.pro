# -*- mode: makefile -*-
#
# QAnyulogus, by Peter Salvi (2008)

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += main-window.hh qanyulogus.hh hungarian-sort-filter-proxy-model.hh
SOURCES += main.cc main-window.cc qanyulogus.cc \
	hungarian-sort-filter-proxy-model.cc
RESOURCES = qanyulogus.qrc

# Type specification for Mac OS X
QMAKE_INFO_PLIST = Info.plist
