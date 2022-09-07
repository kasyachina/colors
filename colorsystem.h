#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QLayout>
#include <colorsystemfield.h>

class colorSystem : public QWidget
{
    Q_OBJECT
public:
    explicit colorSystem(QWidget *parent = nullptr, int number_of_fields = 3);
    virtual ~colorSystem();
signals:

private:
    QLineEdit *numberBoxes[4];
    int size;
    QSlider *controlSlider;
};

