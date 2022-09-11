#include "colorsystem.h"

colorSystem::colorSystem(QWidget *parent, int numberOfFields, std::vector<std::pair<qreal, qreal>> ranges) : QWidget(parent), size(numberOfFields)
{
    controlSlider = new colorSystemSlider(this);
    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < size; i++)
    {
        numberBoxes[i] = new colorSystemField(this, controlSlider, ranges[i].first, ranges[i].second);
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
