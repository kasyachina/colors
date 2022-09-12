#include "colorsystem.h"
#include <QDebug>

colorSystem::colorSystem(QWidget *parent, int numberOfFields, std::vector<std::pair<qreal, qreal>> ranges) : QWidget(parent), size(numberOfFields)
{
    controlSlider = new colorSystemSlider(this);
    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < size; i++)
    {
        fields[i] = new colorSystemField(this, controlSlider, ranges[i].first, ranges[i].second, i);
        connect(fields[i], &colorSystemField::valueChanged, this, &colorSystem::ChangeFieldValue);
        if (i > 0)
        {
            h -> addStretch(30);
        }
        h -> addWidget(fields[i]);
    }
    QVBoxLayout *v = new QVBoxLayout(this);
    nameLabel = new QLabel;
    nameLabel -> setText("Sample color system:");
    v -> addWidget(nameLabel);
    v -> addLayout(h);
    v -> addWidget(controlSlider);
}
void colorSystem::ChangeFieldValue(int newValue, int id)
{
    values[id] = newValue;
    if (fields[id]->getValue() != newValue)
    {
        fields[id]->ChangeValue(newValue);
    }

    std::vector<int> newValues;
    for (int i = 0; i < size; i++)
    {
        newValues.push_back(values[i]);
        qDebug() << '[' << values[i];
    }
    qDebug() << ']';
    emit systemValueChanged(newValues);
}
colorSystem::~colorSystem()
{
    for (int i = 0; i < size; i++)
    {
        delete fields[i];
    }
    delete controlSlider;
    delete nameLabel;
}
