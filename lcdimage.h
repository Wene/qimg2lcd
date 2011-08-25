#ifndef LCDIMAGE_H
#define LCDIMAGE_H

#include <QObject>

class LcdImage : public QObject
{
Q_OBJECT
public:
    explicit LcdImage(QObject *parent = 0);

signals:

public slots:
    void saveAsLcd();
    void LoadFile(QString);
    void setWidth(int);
    void setHight(int);

public:
    int getWidth();
    int getHight();


};

#endif // LCDIMAGE_H
