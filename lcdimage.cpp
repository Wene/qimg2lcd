#include "lcdimage.h"
#include <QtGui>

LcdImage::LcdImage(QObject *parent) :
    QObject(parent)
{
    // initialize default Values
    invert = false;
    redLimit = 128;
    greenLimit = 128;
    blueLimit = 128;
    height = 68;
    width = 96;
    fullImage = QImage();
}

int LcdImage::getHeight()
{
    return height;
}

int LcdImage::getWidth()
{
    return width;
}

bool LcdImage::getInvert()
{
    return invert;
}

int LcdImage::getRedLimit()
{
    return redLimit;
}

int LcdImage::getGreenLimit()
{
    return greenLimit;
}

int LcdImage::getBlueLimit()
{
    return blueLimit;
}

QImage LcdImage::getImgPreview()
{
    return fullImage.scaled(width,height);
}

void LcdImage::LoadFile(QString filename)
{
    fullImage = QImage(filename);
}

void LcdImage::setWidth(int w)
{
    width = w;
}

void LcdImage::setHeight(int h)
{
    height = h;
}

void LcdImage::setInvert(bool inv)
{
    invert = inv;
}

void LcdImage::setColorLimit(int r, int g, int b)
{
    if (r < 0)
    {
        redLimit = 0;
    }
    else if (r > 255)
    {
        redLimit = 255;
    }
    else
    {
        redLimit = r;
    }

    if (g < 0)
    {
        greenLimit = 0;
    }
    else if (g > 255)
    {
        greenLimit = 255;
    }
    else
    {
        greenLimit = g;
    }

    if (b < 0)
    {
        blueLimit = 0;
    }
    else if (b > 255)
    {
        blueLimit = 255;
    }
    else
    {
        blueLimit = b;
    }
}

void LcdImage::saveAsLcd()
{
    //export to LCD file -> to be done
}
