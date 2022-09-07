#include "colorsystem.h"

colorSystem::colorSystem(QWidget *parent, int numberOfFields) : QWidget(parent), size(numberOfFields)
{
    controlSlider = new QSlider(Qt::Horizontal, this);
    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < size; i++)
    {
        numberBoxes[i] = new colorSystemField(this, controlSlider);
        if (i > 0)
        {
            h -> addStretch(30);
        }
        h -> addWidget(numberBoxes[i]);
    }
    QVBoxLayout *v = new QVBoxLayout(this);
    nameLabel = new QLabel;
    nameLabel -> setText("Sample color system:");
    v -> addWidget(nameLabel);
    v -> addLayout(h);
    v -> addWidget(controlSlider);
}
colorSystem::~colorSystem()
{
    for (int i = 0; i < size; i++)
    {
        delete numberBoxes[i];
    }
    delete controlSlider;
    delete nameLabel;
}
