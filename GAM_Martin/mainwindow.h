#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void onInsertRng();
    void onInsertwithDel();
    void onProcessDel();

    void onReset();
    void onLoad2Dmap0();
    void onLoad2Dmap1();
    void onLoad2Dmap2();
    void onLoad2Dmap3();

    void onLoad3Dmap0();
    void onLoad3Dmap1();
    void onLoad3Dmap2();


    void onLapX();
    void onLapY();
    void onLapZ();
    void onCourbure();
    void onLines();


    void onExport();

    void update2D3D();


private:
    Ui::MainWindow *ui;
    std::string _path, _path2D;
};

#endif // MAINWINDOW_H
