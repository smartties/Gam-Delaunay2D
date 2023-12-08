

QT += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mesh_Computational_Geometry
TEMPLATE = app

SOURCES += main.cpp\
    circulateur.cpp \
    draw.cpp \
    laplacien.cpp \
        mainwindow.cpp \
    gldisplaywidget.cpp \
    mesh.cpp \
    scene.cpp

HEADERS  += mainwindow.h \
    circulateur.h \
    draw.h \
    gldisplaywidget.h \
    laplacien.h \
    mathtoolbox.h \
    mesh.h \
    scene.h

FORMS    += mainwindow.ui

#---- Uncomment Windows
#LIBS += -lglu32
#LIBS += -lOpengl32

