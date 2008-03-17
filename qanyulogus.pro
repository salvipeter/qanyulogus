# -*- mode: makefile -*-
#
# QAnyulogus, by Peter Salvi (2008)
#
# Time-stamp: <2008.03.17., 19:31:36 (salvi)>

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += main-window.hh qanyulogus.hh hungarian-sort-filter-proxy-model.hh
SOURCES += main.cc main-window.cc qanyulogus.cc \
	hungarian-sort-filter-proxy-model.cc
RESOURCES = qanyulogus.qrc
