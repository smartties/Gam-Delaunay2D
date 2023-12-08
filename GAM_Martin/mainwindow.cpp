#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Martin Delaunay");

    connect(ui->map2D0Pb, SIGNAL(clicked()), this, SLOT(onLoad2Dmap0()));
    connect(ui->map2D1Pb, SIGNAL(clicked()), this, SLOT(onLoad2Dmap1()));
    connect(ui->map2D2Pb, SIGNAL(clicked()), this, SLOT(onLoad2Dmap2()));
    connect(ui->map2D3Pb, SIGNAL(clicked()), this, SLOT(onLoad2Dmap3()));

    connect(ui->map3D0Pb, SIGNAL(clicked()), this, SLOT(onLoad3Dmap0()));
    connect(ui->map3D1Pb, SIGNAL(clicked()), this, SLOT(onLoad3Dmap1()));
    connect(ui->map3D2Pb, SIGNAL(clicked()), this, SLOT(onLoad3Dmap2()));


    connect(ui->laplaceXPb, SIGNAL(clicked()), this, SLOT(onLapX()));
    connect(ui->laplaceYPb, SIGNAL(clicked()), this, SLOT(onLapY()));
    connect(ui->laplaceZPb, SIGNAL(clicked()), this, SLOT(onLapZ()));
    connect(ui->courburePb, SIGNAL(clicked()), this, SLOT(onCourbure()));


    connect(ui->computeDelaunay, SIGNAL(clicked()), this, SLOT(onProcessDel()));
    connect(ui->insertPoint, SIGNAL(clicked()), this, SLOT(onInsertRng()));
    connect(ui->insertPointDelaunay, SIGNAL(clicked()), this, SLOT(onInsertwithDel()));

    connect(ui->resetPb, SIGNAL(clicked()), this, SLOT(onReset()));

    connect(ui->linesPb, SIGNAL(clicked()), this, SLOT(onLines()));

    connect(ui->exportToOff, SIGNAL(clicked()), this, SLOT(onExport()));

    ui->courburePb->setCheckState(Qt::Checked);
    ui->linesPb->setCheckState(Qt::Checked);
    ui->show2DcheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->show2DcheckBox->setFocusPolicy(Qt::NoFocus);
    ui->show3DcheckBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->show3DcheckBox->setFocusPolicy(Qt::NoFocus);


    ui->voronoiPb->setHidden(true);

    onLines();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onReset()
{
    ui->GLViewerWidget->reloadModel("none", true);
    update2D3D();
}

void MainWindow::onLoad2Dmap0()
{
    ui->GLViewerWidget->reloadModel("alpes_poisson.txt", true);
    update2D3D();
}
void MainWindow::onLoad2Dmap1()
{
    ui->GLViewerWidget->reloadModel("alpes_random_2.txt", true);
    update2D3D();
}
void MainWindow::onLoad2Dmap2()
{
    ui->GLViewerWidget->reloadModel("noise_poisson.txt", true);
    update2D3D();
}
void MainWindow::onLoad2Dmap3()
{
    ui->GLViewerWidget->reloadModel("noise_random_1.txt", true);
    update2D3D();
}

void MainWindow::onLoad3Dmap0()
{
    ui->GLViewerWidget->reloadModel("queen.off", false);
    update2D3D();
}
void MainWindow::onLoad3Dmap1()
{
    ui->GLViewerWidget->reloadModel("cube.off", false);
    update2D3D();
}
void MainWindow::onLoad3Dmap2()
{
    ui->GLViewerWidget->reloadModel("tetra.off", false);
    update2D3D();
}


void MainWindow::onLapX()
{
    ui->laplaceXPb->setCheckState(Qt::Checked);
    ui->laplaceYPb->setCheckState(Qt::Unchecked);
    ui->laplaceZPb->setCheckState(Qt::Unchecked);
    ui->courburePb->setCheckState(Qt::Unchecked);

    ui->GLViewerWidget->getMesh().flagLaplacien = COMPUTE_LAPLACIEN_X;
    ui->GLViewerWidget->getMesh().generateTopology();
    ui->GLViewerWidget->getMesh().computeLaplacien();
}
void MainWindow::onLapY()
{
    ui->laplaceXPb->setCheckState(Qt::Unchecked);
    ui->laplaceYPb->setCheckState(Qt::Checked);
    ui->laplaceZPb->setCheckState(Qt::Unchecked);
    ui->courburePb->setCheckState(Qt::Unchecked);

    ui->GLViewerWidget->getMesh().flagLaplacien = COMPUTE_LAPLACIEN_Y;
    ui->GLViewerWidget->getMesh().generateTopology();
    ui->GLViewerWidget->getMesh().computeLaplacien();
}
void MainWindow::onLapZ()
{
    ui->laplaceXPb->setCheckState(Qt::Unchecked);
    ui->laplaceYPb->setCheckState(Qt::Unchecked);
    ui->laplaceZPb->setCheckState(Qt::Checked);
    ui->courburePb->setCheckState(Qt::Unchecked);

    ui->GLViewerWidget->getMesh().flagLaplacien = COMPUTE_LAPLACIEN_Z;
    ui->GLViewerWidget->getMesh().generateTopology();
    ui->GLViewerWidget->getMesh().computeLaplacien();
}
void MainWindow::onCourbure()
{
    ui->laplaceXPb->setCheckState(Qt::Unchecked);
    ui->laplaceYPb->setCheckState(Qt::Unchecked);
    ui->laplaceZPb->setCheckState(Qt::Unchecked);
    ui->courburePb->setCheckState(Qt::Checked);

    ui->GLViewerWidget->getMesh().flagLaplacien = COMPUTE_COURBURE;
    ui->GLViewerWidget->getMesh().generateTopology();
    ui->GLViewerWidget->getMesh().computeLaplacien();
}



void MainWindow::onLines()
{
    Draw::typeRender = !Draw::typeRender;

    update2D3D();
}

void MainWindow::onExport()
{
    ui->GLViewerWidget->getMesh().writeMeshOff("obj.off");
}

void MainWindow::update2D3D()
{
    ui->computeDelaunay->setHidden(!ui->GLViewerWidget->getMesh().hasPointinfini);
    ui->insertPoint->setHidden(!ui->GLViewerWidget->getMesh().hasPointinfini);
    ui->insertPointDelaunay->setHidden(!ui->GLViewerWidget->getMesh().hasPointinfini);

    ui->show2DcheckBox->setCheckState( ui->GLViewerWidget->getMesh().hasPointinfini ? Qt::Checked : Qt::Unchecked);
    ui->show3DcheckBox->setCheckState( !ui->GLViewerWidget->getMesh().hasPointinfini ? Qt::Checked : Qt::Unchecked);
}


void MainWindow::onInsertRng()
{
    ui->GLViewerWidget->insertionDePoint();
}

void MainWindow::onInsertwithDel()
{
    ui->GLViewerWidget->insertionDePointDelaunay();
}

void MainWindow::onProcessDel()
{
    ui->GLViewerWidget->processDelaunay();
}

