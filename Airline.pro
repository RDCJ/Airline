TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        adjlist.cpp \
        adjmatrix.cpp \
        def.cpp \
        main.cpp

DISTFILES +=

RESOURCES +=

HEADERS += \
    Node.h \
    adjlist.h \
    adjmatrix.h \
    def.h
