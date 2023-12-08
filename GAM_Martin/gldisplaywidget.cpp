#include "gldisplaywidget.h"
#ifdef __APPLE__
    #include <glu.h>
#else
    #include <GL/glu.h>
#endif

#include "QDebug"

#include <sstream>

GLDisplayWidget::GLDisplayWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    connect( &_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.start(15);
}

void GLDisplayWidget::initializeGL()
{
    glClearColor(0.25, 0.25, 0.25, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

void GLDisplayWidget::insertionDePointDelaunay()
{
    int w = 5;
    Vertex p = Vertex(-generateRandomNumber<float>(-w, w),
                       generateRandomNumber<float>(-w, w), 0.f);

    scene.mMesh.insertionDePointDelaunay(p);
}


void GLDisplayWidget::insertionDePoint()
{
    int w = 5;
    Vertex p = Vertex(-generateRandomNumber<float>(-w, w),
                       generateRandomNumber<float>(-w, w), 0.f);
    scene.mMesh.insertionDePoint(p);
}


void GLDisplayWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5,  0,0,0,   0,1,0);
    glTranslated(posCamX, posCamY, posCamZ);

    glRotatef(angleRotCamY, 1.0f, 0.0f, 0.0f);
    glRotatef(angleRotCamX, 0.0f, 1.0f, 0.0f);

    glColor3f(0.25, 1 ,0);


    scene.draw();
    scene.drawAxis();
}

void GLDisplayWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.f, (GLfloat)width/(GLfloat)height, 0.1f, 1000.f);

    update();
}

void GLDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if(event && event->isBeginEvent())
        lastPosM = event->pos();
}

void GLDisplayWidget::insertionDePoint(const Vertex &vtx)
{
    scene.mMesh.insertionDePoint(vtx);
}


void GLDisplayWidget::mouseMoveEvent(QMouseEvent *event)
{
    int moveX = event->x() - lastPosM.x();
    int moveY = event->y() - lastPosM.y();

    if( event != NULL )
    {
        angleRotCamX += moveX;
        angleRotCamY += moveY;
        lastPosM = event->pos();
        update();
    }
}


void GLDisplayWidget::wheelEvent(QWheelEvent *event)
{
    QPoint wheel = event->angleDelta();

    if (!wheel.isNull())
    {
        if(wheel.x() > 0 || wheel.y() > 0)
            posCamZ += 1.f/3.f;
        else
            posCamZ -= 1.f/3.f;
    }
}

