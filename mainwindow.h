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
    void OpenFile();
    void ExportFile();
    void ChangeSize();
    void UpdatePreview();

private:
    Ui::MainWindow *ui;
    QImage picOriginal;
};

#endif // MAINWINDOW_H
