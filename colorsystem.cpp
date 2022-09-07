#include "colorsystem.h"

colorSystem::colorSystem(QWidget *parent, int numberOfFields) : QWidget(parent), size(numberOfFields)
{
    //QGridLayout g(this);
    controlSlider = new QSlider(Qt::Horizontal, this);
    QHBoxLayout h;
    for (int i = 0; i < size; i++)
    {
        numberBoxes[i] = new colorSystemField(this, controlSlider);
        h.addWidget(numberBoxes[i]);
    }
    QVBoxLayout v;
    v.addLayout(&h);
    v.addWidget(controlSlider);
    this -> setLayout(&v);
    //g.addWidget(controlSlider, 1, 0, 1, size);
}
colorSystem::~colorSystem()
{
    for (int i = 0; i < size; i++)
    {
        delete numberBoxes[i];
    }
    delete controlSlider;
}
