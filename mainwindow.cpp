#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <cstring>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenFile()
{
    QString file = QFileDialog::getOpenFileName(this,trUtf8("Bild öffnen"),
                                                QDir::homePath(),trUtf8("Bilder (*.*)"));
    picOriginal = QImage(file);
    ChangeSize();
}

void MainWindow::ExportFile()
{
    QString filename = QFileDialog::getSaveFileName(this,trUtf8("LCD Speichern"),
                                                QDir::homePath(),trUtf8("LCD Dateien (*.lcd)"));
    QImage picture(picOriginal.scaled(ui->spinWidth->value(), ui->spinHight->value()));
    char pixmap[(picture.height()+7)/8][picture.width()];
    memset(pixmap, 0, (picture.height()+7)/8 * picture.width());

    //Read pixels from image in the array
    for (int x = 0; x < picture.width(); x++)
    {
        for (int y = 0; y < picture.height(); y++)
        {
            QColor myPoint(picture.pixel(picture.width()-1-x,picture.height()-1-y));
            bool pixel = !(myPoint.red() > ui->slidRed->value() ||
                    myPoint.green() > ui->slidGreen->value() ||
                    myPoint.blue() > ui->slidBlue->value());
            char byte = pixmap[y/8][x];
            byte |= pixel<<(y%8);
            pixmap[y/8][x] = byte;
        }
    }


    //Write bits in file
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    file.write(&pixmap[0][0], ((picture.height()+7)/8) * picture.width());

    file.close();

}

void MainWindow::ChangeSize()
{
    QImage picture(picOriginal.scaled(ui->spinWidth->value(), ui->spinHight->value()));

    ui->lblImage->setPixmap(QPixmap::fromImage(picture));
    UpdatePreview();
}

//render Preview
void MainWindow::UpdatePreview()
{
    QImage leftPicture(picOriginal.scaled(ui->spinWidth->value(), ui->spinHight->value()));
    QImage rightPicture(leftPicture.width(), leftPicture.height(), QImage::Format_Mono);
    rightPicture.fill(0);
    for (int y = 0; y < leftPicture.height(); y++)
    {
        for (int x = 0; x < leftPicture.width(); x++)
        {
            QColor myPoint(leftPicture.pixel(x,y));
            rightPicture.setPixel(x,y,(myPoint.red() > ui->slidRed->value() ||
                    myPoint.green() > ui->slidGreen->value() ||
                    myPoint.blue() > ui->slidBlue->value()));
        }
    }

    ui->lblPreview->setPixmap(QPixmap::fromImage(rightPicture));

}
