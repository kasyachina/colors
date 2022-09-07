#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLayout>
#include <colorsystemfield.h>
#include <QLabel>

class colorSystem : public QWidget
{
    Q_OBJECT
public:
    explicit colorSystem(QWidget *parent = nullptr, int number_of_fields = 3);
    virtual ~colorSystem();
signals:

private:
    colorSystemField *numberBoxes[4];
    QLabel *nameLabel;
    int size;
    QSlider *controlSlider;
};

