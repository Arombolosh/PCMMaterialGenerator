# remember to set DYLD_FALLBACK_LIBRARY_PATH on MacOSX
# set LD_LIBRARY_PATH on Linux

TARGET = PCMMaterialGenerator
TEMPLATE = app

# this pri must be sourced from all our applications
include( ../../../externals/IBK/projects/Qt/IBK.pri )

QT += xml core gui network printsupport widgets

LIBS += -L../../../lib$${DIR_PREFIX} \
	-lIBK


INCLUDEPATH = \
	../../src \
	../../../externals/IBK/src #\
	#../../../externals/Materials/src


TRANSLATIONS += ../../resources/translations/PCMMaterialGenerator.ts
CODECFORSRC = UTF-8

#RESOURCES += \
#	../../resources/PVTool.qrc

SOURCES += \
	../../src/MainWindow.cpp \
	../../src/main.cpp

HEADERS += \
	../../src/MainWindow.h

FORMS += \
	../../src/MainWindow.ui

