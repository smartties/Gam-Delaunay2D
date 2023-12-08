/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gldisplaywidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    GLDisplayWidget *GLViewerWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QCheckBox *show2DcheckBox;
    QPushButton *map2D0Pb;
    QPushButton *map3D0Pb;
    QPushButton *map2D1Pb;
    QPushButton *map3D1Pb;
    QPushButton *map2D2Pb;
    QPushButton *map3D2Pb;
    QPushButton *map2D3Pb;
    QCheckBox *show3DcheckBox;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QPushButton *insertPointDelaunay;
    QPushButton *insertPoint;
    QPushButton *computeDelaunay;
    QPushButton *resetPb;
    QPushButton *exitPushButton;
    QCheckBox *laplaceXPb;
    QCheckBox *laplaceYPb;
    QCheckBox *courburePb;
    QCheckBox *linesPb;
    QCheckBox *voronoiPb;
    QCheckBox *laplaceZPb;
    QPushButton *exportToOff;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1218, 690);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        GLViewerWidget = new GLDisplayWidget(centralWidget);
        GLViewerWidget->setObjectName("GLViewerWidget");
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(GLViewerWidget->sizePolicy().hasHeightForWidth());
        GLViewerWidget->setSizePolicy(sizePolicy1);
        formLayoutWidget = new QWidget(GLViewerWidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(0, 10, 341, 171));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName("formLayout");
        show2DcheckBox = new QCheckBox(formLayoutWidget);
        show2DcheckBox->setObjectName("show2DcheckBox");
        show2DcheckBox->setChecked(false);

        formLayout->setWidget(0, QFormLayout::LabelRole, show2DcheckBox);

        map2D0Pb = new QPushButton(formLayoutWidget);
        map2D0Pb->setObjectName("map2D0Pb");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(map2D0Pb->sizePolicy().hasHeightForWidth());
        map2D0Pb->setSizePolicy(sizePolicy2);
        map2D0Pb->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(1, QFormLayout::LabelRole, map2D0Pb);

        map3D0Pb = new QPushButton(formLayoutWidget);
        map3D0Pb->setObjectName("map3D0Pb");
        sizePolicy2.setHeightForWidth(map3D0Pb->sizePolicy().hasHeightForWidth());
        map3D0Pb->setSizePolicy(sizePolicy2);
        map3D0Pb->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(1, QFormLayout::FieldRole, map3D0Pb);

        map2D1Pb = new QPushButton(formLayoutWidget);
        map2D1Pb->setObjectName("map2D1Pb");
        sizePolicy2.setHeightForWidth(map2D1Pb->sizePolicy().hasHeightForWidth());
        map2D1Pb->setSizePolicy(sizePolicy2);
        map2D1Pb->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(2, QFormLayout::LabelRole, map2D1Pb);

        map3D1Pb = new QPushButton(formLayoutWidget);
        map3D1Pb->setObjectName("map3D1Pb");
        sizePolicy2.setHeightForWidth(map3D1Pb->sizePolicy().hasHeightForWidth());
        map3D1Pb->setSizePolicy(sizePolicy2);
        map3D1Pb->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(2, QFormLayout::FieldRole, map3D1Pb);

        map2D2Pb = new QPushButton(formLayoutWidget);
        map2D2Pb->setObjectName("map2D2Pb");
        sizePolicy2.setHeightForWidth(map2D2Pb->sizePolicy().hasHeightForWidth());
        map2D2Pb->setSizePolicy(sizePolicy2);
        map2D2Pb->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(3, QFormLayout::LabelRole, map2D2Pb);

        map3D2Pb = new QPushButton(formLayoutWidget);
        map3D2Pb->setObjectName("map3D2Pb");
        sizePolicy2.setHeightForWidth(map3D2Pb->sizePolicy().hasHeightForWidth());
        map3D2Pb->setSizePolicy(sizePolicy2);
        map3D2Pb->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(3, QFormLayout::FieldRole, map3D2Pb);

        map2D3Pb = new QPushButton(formLayoutWidget);
        map2D3Pb->setObjectName("map2D3Pb");
        sizePolicy2.setHeightForWidth(map2D3Pb->sizePolicy().hasHeightForWidth());
        map2D3Pb->setSizePolicy(sizePolicy2);
        map2D3Pb->setMinimumSize(QSize(150, 0));

        formLayout->setWidget(4, QFormLayout::LabelRole, map2D3Pb);

        show3DcheckBox = new QCheckBox(formLayoutWidget);
        show3DcheckBox->setObjectName("show3DcheckBox");
        show3DcheckBox->setChecked(false);

        formLayout->setWidget(0, QFormLayout::FieldRole, show3DcheckBox);

        formLayoutWidget_2 = new QWidget(GLViewerWidget);
        formLayoutWidget_2->setObjectName("formLayoutWidget_2");
        formLayoutWidget_2->setGeometry(QRect(0, 180, 341, 172));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName("formLayout_2");
        insertPointDelaunay = new QPushButton(formLayoutWidget_2);
        insertPointDelaunay->setObjectName("insertPointDelaunay");
        sizePolicy2.setHeightForWidth(insertPointDelaunay->sizePolicy().hasHeightForWidth());
        insertPointDelaunay->setSizePolicy(sizePolicy2);
        insertPointDelaunay->setMinimumSize(QSize(150, 0));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, insertPointDelaunay);

        insertPoint = new QPushButton(formLayoutWidget_2);
        insertPoint->setObjectName("insertPoint");
        sizePolicy2.setHeightForWidth(insertPoint->sizePolicy().hasHeightForWidth());
        insertPoint->setSizePolicy(sizePolicy2);
        insertPoint->setMinimumSize(QSize(150, 0));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, insertPoint);

        computeDelaunay = new QPushButton(formLayoutWidget_2);
        computeDelaunay->setObjectName("computeDelaunay");
        sizePolicy2.setHeightForWidth(computeDelaunay->sizePolicy().hasHeightForWidth());
        computeDelaunay->setSizePolicy(sizePolicy2);
        computeDelaunay->setMinimumSize(QSize(150, 0));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, computeDelaunay);

        resetPb = new QPushButton(formLayoutWidget_2);
        resetPb->setObjectName("resetPb");
        sizePolicy2.setHeightForWidth(resetPb->sizePolicy().hasHeightForWidth());
        resetPb->setSizePolicy(sizePolicy2);
        resetPb->setMinimumSize(QSize(150, 0));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, resetPb);

        exitPushButton = new QPushButton(formLayoutWidget_2);
        exitPushButton->setObjectName("exitPushButton");
        sizePolicy2.setHeightForWidth(exitPushButton->sizePolicy().hasHeightForWidth());
        exitPushButton->setSizePolicy(sizePolicy2);
        exitPushButton->setMinimumSize(QSize(150, 0));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, exitPushButton);

        laplaceXPb = new QCheckBox(formLayoutWidget_2);
        laplaceXPb->setObjectName("laplaceXPb");
        laplaceXPb->setChecked(false);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, laplaceXPb);

        laplaceYPb = new QCheckBox(formLayoutWidget_2);
        laplaceYPb->setObjectName("laplaceYPb");
        laplaceYPb->setChecked(false);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, laplaceYPb);

        courburePb = new QCheckBox(formLayoutWidget_2);
        courburePb->setObjectName("courburePb");
        courburePb->setChecked(false);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, courburePb);

        linesPb = new QCheckBox(formLayoutWidget_2);
        linesPb->setObjectName("linesPb");
        linesPb->setChecked(false);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, linesPb);

        voronoiPb = new QCheckBox(formLayoutWidget_2);
        voronoiPb->setObjectName("voronoiPb");
        voronoiPb->setChecked(false);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, voronoiPb);

        laplaceZPb = new QCheckBox(formLayoutWidget_2);
        laplaceZPb->setObjectName("laplaceZPb");
        laplaceZPb->setChecked(false);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, laplaceZPb);

        exportToOff = new QPushButton(formLayoutWidget_2);
        exportToOff->setObjectName("exportToOff");
        sizePolicy2.setHeightForWidth(exportToOff->sizePolicy().hasHeightForWidth());
        exportToOff->setSizePolicy(sizePolicy2);
        exportToOff->setMinimumSize(QSize(150, 0));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, exportToOff);


        verticalLayout_2->addWidget(GLViewerWidget);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);
        QObject::connect(exitPushButton, &QPushButton::released, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mesh_Computational_Geometry", nullptr));
        show2DcheckBox->setText(QCoreApplication::translate("MainWindow", "2D                ", nullptr));
        map2D0Pb->setText(QCoreApplication::translate("MainWindow", "alpes_poisson.txt", nullptr));
        map3D0Pb->setText(QCoreApplication::translate("MainWindow", "queen.off", nullptr));
        map2D1Pb->setText(QCoreApplication::translate("MainWindow", "alpes_random_2.txt", nullptr));
        map3D1Pb->setText(QCoreApplication::translate("MainWindow", "cube", nullptr));
        map2D2Pb->setText(QCoreApplication::translate("MainWindow", "noise_poisson.txt", nullptr));
        map3D2Pb->setText(QCoreApplication::translate("MainWindow", "tetra", nullptr));
        map2D3Pb->setText(QCoreApplication::translate("MainWindow", "noise_random_1.txt", nullptr));
        show3DcheckBox->setText(QCoreApplication::translate("MainWindow", "3D", nullptr));
        insertPointDelaunay->setText(QCoreApplication::translate("MainWindow", "Insert + delaunay ", nullptr));
        insertPoint->setText(QCoreApplication::translate("MainWindow", "Insert random", nullptr));
        computeDelaunay->setText(QCoreApplication::translate("MainWindow", "process delaunay", nullptr));
        resetPb->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        exitPushButton->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        laplaceXPb->setText(QCoreApplication::translate("MainWindow", "Laplacien X", nullptr));
        laplaceYPb->setText(QCoreApplication::translate("MainWindow", "Laplacien Y", nullptr));
        courburePb->setText(QCoreApplication::translate("MainWindow", "Courbure", nullptr));
        linesPb->setText(QCoreApplication::translate("MainWindow", "GL_LINES", nullptr));
        voronoiPb->setText(QCoreApplication::translate("MainWindow", "Voronoi", nullptr));
        laplaceZPb->setText(QCoreApplication::translate("MainWindow", "Laplacien Z", nullptr));
        exportToOff->setText(QCoreApplication::translate("MainWindow", "Export to obj.off", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
