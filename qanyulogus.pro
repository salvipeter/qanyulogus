# -*- mode: makefile -*-
#
# QAnyulogus, by Peter Salvi (2008)

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += opener-application.hh main-window.hh qanyulogus.hh \
	hungarian-sort-filter-proxy-model.hh
SOURCES += opener-application.cc main.cc main-window.cc qanyulogus.cc \
	hungarian-sort-filter-proxy-model.cc
RESOURCES = qanyulogus.qrc

# Disable command line arguments on Mac (they not conform with the Open event)
mac {
  DEFINES += DISABLE_COMMAND_LINE
}

# Type specification for Mac OS X
QMAKE_INFO_PLIST = Info.plist

# ... and we also have to do some manual processing on Mac:
# mkdir qanyulogus.app/Contents/Resources
# cp images/*.icns qanyulogus.app/Contents/Resources/
