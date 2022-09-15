#include "colorsystem.h"
#include <QDebug>

colorSystem::colorSystem(QWidget *parent, int numberOfFields, std::vector<std::pair<qreal, qreal>> ranges, QString name, int _id) :
    QWidget(parent), size(numberOfFields), systemId(_id)
{
    blockSignals(true);
    controlSlider = new colorSystemSlider(this);
    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < size; i++)
    {
        fields[i] = new colorSystemField(this, controlSlider, ranges[i].first, ranges[i].second, i);
        values[i] = ranges[i].first;
        connect(fields[i], &colorSystemField::valueChanged, this, &colorSystem::ChangeFieldValue);
        if (i > 0)
        {
            h -> addStretch(30);
        }
        h -> addWidget(fields[i]);
    }
    QVBoxLayout *v = new QVBoxLayout(this);
    nameLabel = new QLabel;
    nameLabel -> setText(name);
    v -> addWidget(nameLabel);
    v -> addLayout(h);
    v -> addWidget(controlSlider);
    blockSignals(false);
}
void colorSystem::BlockAllSignals(bool block)
{
    blockSignals(block);
    for (int i = 0; i < size; i++)
    {
        fields[i]->blockSignals(block);
    }
}
void colorSystem::ChangeFieldValue(int newValue, int fieldId)
{
    values[fieldId] = newValue;
    if (fields[fieldId]->getValue() != newValue)
    {
        fields[fieldId]->ChangeValue(newValue);
    }
    std::vector<int> newValues;
    for (int i = 0; i < size; i++)
    {
        newValues.push_back(values[i]);
        //qDebug() << '[' << values[i];
    }
    //qDebug() << ']';
    emit systemValueChanged(newValues, systemId);
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
RGBSystem::RGBSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 255}, {0, 255}, {0, 255}}, "RGB", id)
{}
ColorSystem RGBSystem::getSystemType() const
{
    return ColorSystem::RGB;
}
CMYKSystem::CMYKSystem(QWidget *parent, int id):colorSystem(parent, 4, {{0, 255}, {0, 255}, {0, 255}, {0, 255}}, "CMYK", id)
{}
ColorSystem CMYKSystem::getSystemType() const
{
    return ColorSystem::CMYK;
}
HSVSystem::HSVSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 360}, {0, 100}, {0, 100}}, "HSV", id)
{}
ColorSystem HSVSystem::getSystemType() const
{
    return ColorSystem::HSV;
}
HLSSystem::HLSSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 360}, {0, 100}, {0, 100}}, "HLS", id)
{}
ColorSystem HLSSystem::getSystemType() const
{
    return ColorSystem::HLS;
}
XYZSystem::XYZSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 95}, {0, 100}, {0, 109}}, "XYZ", id)
{}
ColorSystem XYZSystem::getSystemType() const
{
    return ColorSystem::XYZ;
}
LABSystem::LABSystem(QWidget *parent, int id):colorSystem(parent, 3, {{0, 100}, {-128, 127}, {-128, 127}}, "LAB", id)
{}
ColorSystem LABSystem::getSystemType() const
{
    return ColorSystem::LAB;
}
