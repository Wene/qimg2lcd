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

QImage LcdImage::getLcdPreview()
{
    QImage colorImage(fullImage.scaled(width, height));
    QImage monoImage(width, height, QImage::Format_Mono);
    monoImage.fill(0);
    if (invert)                                 //invert the color in monoImage.setPixel() with "!"
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                QColor myPoint(colorImage.pixel(x,y));
                monoImage.setPixel(x,y,!(myPoint.red() > redLimit ||
                                         myPoint.green() > greenLimit ||
                                         myPoint.blue() > blueLimit));
            }
        }

    }
    else
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                QColor myPoint(colorImage.pixel(x,y));
                monoImage.setPixel(x,y,(myPoint.red() > redLimit ||
                                        myPoint.green() > greenLimit ||
                                        myPoint.blue() > blueLimit));
            }
        }
    }
    return monoImage;
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

void LcdImage::saveAsLcd(QString filename)
{
    QImage picture = getLcdPreview();
    char pixmap[(height+7)/8][width];
    memset(pixmap, 0, (height+7)/8 * width);

    //Read pixels from image in the array
    if (invert)                                 //invert the color with bool pixel = !(...)
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                bool pixel = !(picture.pixel(width-1-x,height-1-y) == qRgb(0,0,0));

                char byte = pixmap[y/8][x];     //get Byte from array
                byte |= pixel<<(y%8);           //set bit in byte
                pixmap[y/8][x] = byte;          //write byte back to array
            }
        }
    }
    else
    {
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                bool pixel = (picture.pixel(width-1-x,height-1-y) == qRgb(0,0,0));

                char byte = pixmap[y/8][x];     //get Byte from array
                byte |= pixel<<(y%8);           //set bit in byte
                pixmap[y/8][x] = byte;          //write byte back to array
            }
        }
    }


    //Write bits in file
    QFile file(filename);
    file.open(QIODevice::WriteOnly);

    file.write(&pixmap[0][0], ((height+7)/8) * width);

    file.close();
}

