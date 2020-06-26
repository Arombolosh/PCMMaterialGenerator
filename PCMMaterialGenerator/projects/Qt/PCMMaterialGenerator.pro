# remember to set DYLD_FALLBACK_LIBRARY_PATH on MacOSX
# set LD_LIBRARY_PATH on Linux

TARGET = PCMMaterialGenerator
TEMPLATE = app

QT += xml core gui network printsupport widgets


INCLUDEPATH = \
	../../src


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

