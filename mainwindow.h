#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lcdimage.h"

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
    void OpenFile();
    void ExportFile();
    void ChangeSize();
    void UpdatePreview();

private:
    Ui::MainWindow *ui;
    QImage picOriginal;

    LcdImage myImage;
};

#endif // MAINWINDOW_H
