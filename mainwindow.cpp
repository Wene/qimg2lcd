#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <cstring>
#include "lcdimage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myImage.setWidth(ui->spinWidth->value());
    myImage.setHeight(ui->spinHight->value());

    myImage.setColorLimit(ui->slidRed->value(),
                          ui->slidGreen->value(),
                          ui->slidBlue->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenFile()
{
    QString filename = QFileDialog::getOpenFileName(this,trUtf8("Bild öffnen"),
                                                QDir::homePath(),trUtf8("Bilder (*.*)"));
    myImage.LoadFile(filename);
    UpdatePreview();
}

void MainWindow::ExportFile()
{
    QString filename = QFileDialog::getSaveFileName(this,trUtf8("LCD Speichern"),
                                                QDir::homePath(),trUtf8("LCD Dateien (*.lcd)"));
    myImage.saveAsLcd(filename);
}

void MainWindow::ChangeSize()
{
    myImage.setWidth(ui->spinWidth->value());
    myImage.setHeight(ui->spinHight->value());
    UpdatePreview();
}

void MainWindow::UpdatePreview()
{
    ui->lblPreview->setPixmap(QPixmap::fromImage(myImage.getLcdPreview()));
    ui->lblImage->setPixmap(QPixmap::fromImage(myImage.getImgPreview()));
}
