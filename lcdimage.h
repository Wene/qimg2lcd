#ifndef LCDIMAGE_H
#define LCDIMAGE_H

#include <QObject>
#include <QtGui>

class LcdImage : public QObject
{
Q_OBJECT
public:
    explicit LcdImage(QObject *parent = 0);
    int getWidth();
    int getHeight();
    int getRedLimit();
    int getGreenLimit();
    int getBlueLimit();
    QImage getImgPreview();
    QImage getLcdPreview();
    bool getInvert();

signals:

public slots:
    void saveAsLcd();
    void LoadFile(QString);
    void setWidth(int);
    void setHeight(int);
    void setInvert(bool);
    void setColorLimit(int, int, int);

private:
    bool invert;
    QImage fullImage;
    int width, height;
    int redLimit, greenLimit, blueLimit;

};

#endif // LCDIMAGE_H
