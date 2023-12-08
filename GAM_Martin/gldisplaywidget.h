#ifndef GLDISPLAYWIDGET_H
#define GLDISPLAYWIDGET_H

#include <QOpenGLWidget>
#include <QtWidgets>
#include <QTimer>

#include "scene.h"

class GLDisplayWidget : public QOpenGLWidget
{
public:
    explicit GLDisplayWidget(QWidget *parent = NULL);

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void reloadModel(std::string name, bool is2D)
    {
        if(is2D)
            scene.Load2Dpoints(name);
        else
            scene.load3DModel(name);
    }
    void openMeshFile(const std::string &path)
    {
       if(scene.mMesh.hasPointinfini)scene.mMesh.loadPointsTxt(path);
        else scene.mMesh.loadMeshOff(path);
    }

    void processDelaunay()
    {
        scene.mMesh.processDelaunay();
    }


    Mesh &getMesh()
    {
        return scene.mMesh;
    }

    void insertionDePointDelaunay();
    void insertionDePoint();
    void insertionDePoint(const Vertex &vtx);

protected:

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private:

    QTimer _timer;
    float posCamX = 0.f, posCamY = 0.f, posCamZ= 0.f;
    float angleRotCamX, angleRotCamY;
    QPoint lastPosM;
    Scene scene;
};

#endif // GLDISPLAYWIDGET_H
